%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"
#include "parser_helper.h"

int  yylex(void);
void yyerror(const char *s);
extern FILE *yyin;
%}

/* ── Union de valores semanticos ───────────────────────── */
%union {
    int    i_val;    /* INT_LIT              */
    double f_val;    /* FLOAT_LIT y expr     */
    char   c_val;    /* CHAR_LIT             */
    int    b_val;    /* BOOL_LIT             */
    char  *s_val;    /* STRING_LIT           */
    int    type_tag; /* tipos de dato        */
    struct SymbolEntry *entry; /* IDENTIFIER */
}

/* ── Tokens sin valor ──────────────────────────────────── */
%token LET AS SHOW ASSIGN SEMI LPAREN RPAREN
%token T_NUM T_DEC T_LETTER T_WORD T_BOOL
%token PLUS MINUS STAR SLASH
%token LBRACE RBRACE                             /* { y } para bloques */

/* ── Tokens con valor ──────────────────────────────────── */
%token <entry> IDENTIFIER
%token <i_val> INT_LIT
%token <f_val> FLOAT_LIT
%token <c_val> CHAR_LIT
%token <b_val> BOOL_LIT
%token <s_val> STRING_LIT

/* ── Precedencia de operadores (menor a mayor) ─────────── */
%left  PLUS MINUS
%left  STAR SLASH

/* ── Tipos de no-terminales ────────────────────────────── */
%type <type_tag> num_type
%type <f_val>    expr

%%

/* ── Programa: lista de sentencias ─────────────────────── */
program
    : program statement
    | /* vacio */
    ;

/* ── Una sentencia termina en ; ────────────────────────── */
statement
    : declaration SEMI
    | show_stmt   SEMI
    | block
    ;

/*
 * block: un bloque { } abre un scope nuevo al entrar
 * y lo cierra al salir. Las variables declaradas adentro
 * mueren cuando el bloque termina.
 */
block
    : LBRACE { push_scope(); } program RBRACE { pop_scope(); }
    ;

/*
 * num_type: tipos que pueden usarse en expresiones.
 * word y bool se manejan en reglas separadas porque
 * no participan en aritmetica.
 */
num_type
    : T_NUM    { $$ = TYPE_NUM;    }
    | T_DEC    { $$ = TYPE_DEC;    }
    | T_LETTER { $$ = TYPE_LETTER; }
    ;

/*
 * declaration: tres formas segun el tipo.
 *
 *   let nombre as num    = expr;
 *   let nombre as word   = "cadena";
 *   let nombre as bool   = yes/no;
 */
declaration
    : LET IDENTIFIER AS num_type ASSIGN expr {
        $2->data_type = (DataType)$4;
        assign_numeric_value($2, (DataType)$4, $6);
    }
    | LET IDENTIFIER AS T_WORD ASSIGN STRING_LIT {
        $2->data_type = TYPE_WORD;
        assign_string_value($2, TYPE_WORD, $6);
    }
    | LET IDENTIFIER AS T_BOOL ASSIGN BOOL_LIT {
        $2->data_type = TYPE_BOOL;
        $2->data.b_value = $6;
    }
    ;

/*
 * expr: expresiones aritmeticas.
 * Soporta literales, variables, +, -, *, / y parentesis.
 */
expr
    : INT_LIT              { $$ = (double)$1; }
    | FLOAT_LIT            { $$ = $1;          }
    | CHAR_LIT             { $$ = (double)$1;  }
    | BOOL_LIT             { $$ = (double)$1;  }
    | IDENTIFIER {
        switch ($1->data_type) {
            case TYPE_NUM:    $$ = (double)$1->data.i_value; break;
            case TYPE_DEC:    $$ = $1->data.d_value;          break;
            case TYPE_LETTER: $$ = (double)$1->data.c_value;  break;
            case TYPE_BOOL:   $$ = (double)$1->data.b_value;  break;
            case TYPE_WORD:
                printf("[ERROR] No se puede operar con tipo word\n");
                $$ = 0;
                break;
        }
    }
    | expr PLUS  expr { $$ = $1 + $3; }
    | expr MINUS expr { $$ = $1 - $3; }
    | expr STAR  expr { $$ = $1 * $3; }
    | expr SLASH expr {
        if ($3 == 0) {
            printf("[ERROR] Division entre cero\n");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | LPAREN expr RPAREN { $$ = $2; }
    ;

/* show nombre; — imprime el valor de la variable */
show_stmt
    : SHOW IDENTIFIER { print_entry($2); }
    ;

%%

/* ── Manejo de errores sintacticos ─────────────────────── */
void yyerror(const char *s) {
    fprintf(stderr, "[ERROR] %s\n", s);
}

/* ── Punto de entrada ──────────────────────────────────── */
int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "[ERROR] No se pudo abrir el archivo: %s\n", argv[1]);
            return 1;
        }
        yyin = f;
    }

    push_scope();        /* abre el scope global antes de parsear */

    int result = yyparse();

    pop_scope();         /* limpia el scope global al terminar */

    if (result == 0) {
        printf("[OK] Compilacion exitosa\n");
    }
    return result;
}