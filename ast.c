#ifndef AST_H
#define AST_H

#include "symbols.h"

/*    Tipos de nodos del AST                                 */
typedef enum {
    AST_PROGRAM,      /* raiz: lista de sentencias           */
    AST_VAR_DECL,     /* let/var: declaracion de variable    */
    AST_SHOW,         /* show/print: imprimir variable        */
    AST_BINARY_OP,    /* expresion binaria (+, -, *, /)      */
    AST_LITERAL,      /* valor literal (int, dec, char, ...)  */
    AST_IDENTIFIER,   /* referencia a variable               */
    AST_FUNC_DECL,    /* declaracion de funcion              */
    AST_FUNC_CALL,    /* llamada a funcion                   */
    AST_BLOCK,        /* bloque de sentencias { }            */
    AST_RETURN        /* sentencia return                    */
} ASTNodeType;

/*    Operadores binarios                                    */
typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV
} OpType;

/* Forward declaration */
typedef struct ASTNode ASTNode;

/*    Valor literal                                          */
typedef struct {
    DataType type;
    union {
        int    i_value;
        double d_value;
        char   c_value;
        char  *s_value;
        int    b_value;
    } val;
} LiteralVal;

/*    Nodo binario: izquierda OP derecha                     */
typedef struct {
    OpType   op;
    ASTNode *left;
    ASTNode *right;
} BinaryOpNode;

/*    Declaracion de variable                                */
typedef struct {
    char    *name;     /* nombre de la variable             */
    DataType type;     /* tipo declarado                    */
    ASTNode *value;    /* expresion inicial (puede ser NULL) */
} VarDeclNode;

/*    Sentencia show/print                                   */
typedef struct {
    char *name;        /* nombre de la variable a imprimir  */
} ShowNode;

/*    Declaracion de funcion                                 */
typedef struct {
    char     *name;
    DataType  return_type;
    char    **param_names;   /* nombres de parametros        */
    DataType *param_types;   /* tipos de parametros          */
    int       param_count;
    ASTNode  *body;          /* bloque de sentencias         */
} FuncDeclNode;

/*    Llamada a funcion                                      */
typedef struct {
    char     *name;
    ASTNode **args;
    int       arg_count;
} FuncCallNode;

/*    Bloque { }                                             */
typedef struct {
    ASTNode **stmts;
    int       count;
} BlockNode;

/*    Return                                                 */
typedef struct {
    ASTNode *value;    /* expresion a retornar (NULL = void) */
} ReturnNode;

/*    Nodo principal del AST                                 */
struct ASTNode {
    ASTNodeType type;
    union {
        LiteralVal   literal;
        BinaryOpNode binary_op;
        VarDeclNode  var_decl;
        ShowNode     show;
        FuncDeclNode func_decl;
        FuncCallNode func_call;
        BlockNode    block;
        ReturnNode   ret;
        char        *identifier;  /* nombre para AST_IDENTIFIER */
    } data;
};

/*    Funciones de construccion del AST                      */
ASTNode *ast_program(ASTNode **stmts, int count);
ASTNode *ast_var_decl(const char *name, DataType type, ASTNode *value);
ASTNode *ast_show(const char *name);
ASTNode *ast_binary_op(OpType op, ASTNode *left, ASTNode *right);
ASTNode *ast_literal_int(int v);
ASTNode *ast_literal_double(double v);
ASTNode *ast_literal_char(char v);
ASTNode *ast_literal_string(char *v);
ASTNode *ast_literal_bool(int v);
ASTNode *ast_identifier(const char *name);
ASTNode *ast_func_decl(const char *name, DataType ret_type,
                       char **param_names, DataType *param_types,
                       int param_count, ASTNode *body);
ASTNode *ast_func_call(const char *name, ASTNode **args, int arg_count);
ASTNode *ast_block(ASTNode **stmts, int count);
ASTNode *ast_return(ASTNode *value);

/*    Memoria                                                 */
void ast_free(ASTNode *node);

#endif /* AST_H */