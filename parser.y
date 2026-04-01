%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"
#include "parser_helper.h"
#include "ast.h"
#include "interpreter.h"

int  yylex(void);
void yyerror(const char *s);
extern FILE *yyin;

/*     Lista dinamica de sentencias del programa global     */
static ASTNode **g_stmts = NULL;
static int       g_count = 0;
static int       g_cap   = 0;

static void g_push(ASTNode *n) {
    if (!n) return;
    if (g_count == g_cap) {
        g_cap   = g_cap ? g_cap * 2 : 16;
        g_stmts = realloc(g_stmts, sizeof(ASTNode *) * g_cap);
    }
    g_stmts[g_count++] = n;
}

/*     Pila de contextos para cuerpos de funciones           */
#define MAX_FUNC_DEPTH 32
static ASTNode **f_stmts[MAX_FUNC_DEPTH];
static int       f_count[MAX_FUNC_DEPTH];
static int       f_cap  [MAX_FUNC_DEPTH];
static int       f_depth = -1;

static void f_begin(void) {
    f_depth++;
    f_stmts[f_depth] = NULL;
    f_count[f_depth] = 0;
    f_cap  [f_depth] = 0;
}

static void f_push(ASTNode *n) {
    if (!n || f_depth < 0) return;
    if (f_count[f_depth] == f_cap[f_depth]) {
        f_cap[f_depth]   = f_cap[f_depth] ? f_cap[f_depth] * 2 : 8;
        f_stmts[f_depth] = realloc(f_stmts[f_depth],
                                   sizeof(ASTNode *) * f_cap[f_depth]);
    }
    f_stmts[f_depth][f_count[f_depth]++] = n;
}

static ASTNode *f_end(void) {
    ASTNode *blk = ast_block(f_stmts[f_depth], f_count[f_depth]);
    f_depth--;
    return blk;
}
%}

/*    Union                                                  */
%union {
    int      i_val;
    double   f_val;
    char     c_val;
    int      b_val;
    char    *s_val;
    int      type_tag;
    struct ASTNode *node;
    struct {
        struct ASTNode **list;
        int count;
        int cap;
    } node_list;
    struct {
        char **names;
        int  *types;
        int   count;
        int   cap;
    } param_list;
}

/*    Tokens                                                 */
%token LET AS SHOW ASSIGN SEMI LPAREN RPAREN
%token T_NUM T_DEC T_LETTER T_WORD T_BOOL
%token PLUS MINUS STAR SLASH LBRACE RBRACE
%token FUNC RETURN ARROW COMMA LBRACKET RBRACKET

/*    Tokens con valor                                       */
%token <s_val>   IDENTIFIER
%token <i_val>   INT_LIT
%token <f_val>   FLOAT_LIT
%token <c_val>   CHAR_LIT
%token <b_val>   BOOL_LIT
%token <s_val>   STRING_LIT

/*    Precedencia                                            */
%left  PLUS MINUS
%left  STAR SLASH

/*    Tipos de no-terminales                                 */
%type <type_tag>   num_type
%type <node>       expr
%type <node_list>  arg_list arg_list_ne
%type <param_list> param_list param_list_ne

%%

/*    Programa global                                        */
program
    : program global_stmt
    | /* vacio */
    ;

global_stmt
    /*    Declaracion de variable: let nombre as tipo = expr; */
    : LET IDENTIFIER AS num_type ASSIGN expr SEMI
        { g_push(ast_var_decl($2, (DataType)$4, $6)); free($2); }
    | LET IDENTIFIER AS T_WORD ASSIGN STRING_LIT SEMI
        { g_push(ast_var_decl($2, TYPE_WORD, ast_literal_string($6)));
          free($2); free($6); }
    | LET IDENTIFIER AS T_BOOL ASSIGN BOOL_LIT SEMI
        { g_push(ast_var_decl($2, TYPE_BOOL, ast_literal_bool($6)));
          free($2); }

    /*    Mostrar variable: show nombre;                     */
    | SHOW IDENTIFIER SEMI
        { g_push(ast_show($2)); free($2); }

    /*    Bloque { } global                                  */
    | LBRACE { push_scope(); } program RBRACE { pop_scope(); }

    /*    Declaracion de funcion                             */
    | FUNC IDENTIFIER LPAREN param_list RPAREN
      ARROW LBRACKET num_type RBRACKET
      LBRACE { f_begin(); } func_stmts RBRACE
      {
          ASTNode *body = f_end();
          g_push(ast_func_decl($2, (DataType)$8,
                               $4.names, (DataType *)$4.types, $4.count,
                               body));
          for (int i = 0; i < $4.count; i++) free($4.names[i]);
          free($4.names);
          free($4.types);
          free($2);
      }
    ;

/*    Sentencias dentro de una funcion                       */
func_stmts
    : func_stmts func_stmt
    | /* vacio */
    ;

func_stmt
    : LET IDENTIFIER AS num_type ASSIGN expr SEMI
        { f_push(ast_var_decl($2, (DataType)$4, $6)); free($2); }
    | LET IDENTIFIER AS T_WORD ASSIGN STRING_LIT SEMI
        { f_push(ast_var_decl($2, TYPE_WORD, ast_literal_string($6)));
          free($2); free($6); }
    | LET IDENTIFIER AS T_BOOL ASSIGN BOOL_LIT SEMI
        { f_push(ast_var_decl($2, TYPE_BOOL, ast_literal_bool($6)));
          free($2); }
    | SHOW IDENTIFIER SEMI
        { f_push(ast_show($2)); free($2); }
    | RETURN expr SEMI
        { f_push(ast_return($2)); }
    ;

/*    Tipo de dato                                            */
num_type
    : T_NUM    { $$ = TYPE_NUM;    }
    | T_DEC    { $$ = TYPE_DEC;    }
    | T_LETTER { $$ = TYPE_LETTER; }
    ;

/*    Parametros formales: [num]x, [dec]y                    */
param_list
    : param_list_ne { $$ = $1; }
    | /* vacio */ {
        $$.names = NULL; $$.types = NULL;
        $$.count = 0;    $$.cap   = 0;
    }
    ;

param_list_ne
    : LBRACKET num_type RBRACKET IDENTIFIER {
        $$.names    = malloc(sizeof(char *) * 4);
        $$.types    = malloc(sizeof(int)    * 4);
        $$.count    = 1;
        $$.cap      = 4;
        $$.names[0] = strdup($4);
        $$.types[0] = $2;
        free($4);
    }
    | param_list_ne COMMA LBRACKET num_type RBRACKET IDENTIFIER {
        $$ = $1;
        if ($$.count == $$.cap) {
            $$.cap   = $$.cap * 2;
            $$.names = realloc($$.names, sizeof(char *) * $$.cap);
            $$.types = realloc($$.types, sizeof(int)    * $$.cap);
        }
        $$.names[$$.count] = strdup($6);
        $$.types[$$.count] = $4;
        $$.count++;
        free($6);
    }
    ;

/*    Argumentos en llamada                                   */
arg_list
    : arg_list_ne { $$ = $1; }
    | /* vacio */ { $$.list = NULL; $$.count = 0; $$.cap = 0; }
    ;

arg_list_ne
    : expr {
        $$.list    = malloc(sizeof(ASTNode *) * 4);
        $$.count   = 1;
        $$.cap     = 4;
        $$.list[0] = $1;
    }
    | arg_list_ne COMMA expr {
        $$ = $1;
        if ($$.count == $$.cap) {
            $$.cap  = $$.cap * 2;
            $$.list = realloc($$.list, sizeof(ASTNode *) * $$.cap);
        }
        $$.list[$$.count++] = $3;
    }
    ;

/*    Expresiones                                             */
expr
    : INT_LIT                           { $$ = ast_literal_int($1);    }
    | FLOAT_LIT                         { $$ = ast_literal_double($1); }
    | CHAR_LIT                          { $$ = ast_literal_char($1);   }
    | BOOL_LIT                          { $$ = ast_literal_bool($1);   }
    | IDENTIFIER LPAREN arg_list RPAREN { $$ = ast_func_call($1, $3.list, $3.count); free($1); }
    | IDENTIFIER                        { $$ = ast_identifier($1); free($1); }
    | expr PLUS  expr                   { $$ = ast_binary_op(OP_ADD, $1, $3); }
    | expr MINUS expr                   { $$ = ast_binary_op(OP_SUB, $1, $3); }
    | expr STAR  expr                   { $$ = ast_binary_op(OP_MUL, $1, $3); }
    | expr SLASH expr                   { $$ = ast_binary_op(OP_DIV, $1, $3); }
    | LPAREN expr RPAREN                { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "[ERROR] %s\n", s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "[ERROR] No se pudo abrir: %s\n", argv[1]);
            return 1;
        }
        yyin = f;
    }

    push_scope();
    interpreter_init();

    int result = yyparse();

    if (result == 0 && g_count > 0) {
        ASTNode *program = ast_program(g_stmts, g_count);
        interpreter_run(program);
        ast_free(program);
    }

    interpreter_destroy();
    pop_scope();

    if (argc > 1) fclose(yyin);
    return result;
}