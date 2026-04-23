#ifndef AST_H
#define AST_H

#include "symbols.h"

typedef enum {
    AST_PROGRAM,
    AST_VAR_DECL,
    AST_SHOW,
    AST_BINARY_OP,
    AST_LITERAL,
    AST_IDENTIFIER,
    AST_FUNC_DECL,
    AST_FUNC_CALL,
    AST_BLOCK,
    AST_RETURN,
    AST_IF
} ASTNodeType;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE
} OpType;

typedef struct ASTNode ASTNode;

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

typedef struct {
    OpType   op;
    ASTNode *left;
    ASTNode *right;
} BinaryOpNode;

typedef struct {
    char    *name;
    DataType type;
    ASTNode *value;
} VarDeclNode;

typedef struct {
    char *name;
} ShowNode;

typedef struct {
    char     *name;
    DataType  return_type;
    char    **param_names;
    DataType *param_types;
    int       param_count;
    ASTNode  *body;
} FuncDeclNode;

typedef struct {
    char     *name;
    ASTNode **args;
    int       arg_count;
} FuncCallNode;

typedef struct {
    ASTNode **stmts;
    int       count;
} BlockNode;

typedef struct {
    ASTNode *value;
} ReturnNode;

typedef struct {
    ASTNode *condition;
    ASTNode *then_body;
    ASTNode *else_body;  /* NULL si no hay else */
} IfNode;

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
        IfNode       if_stmt;
        char        *identifier;
    } data;
};

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
ASTNode *ast_if(ASTNode *cond, ASTNode *then_body, ASTNode *else_body);

void ast_free(ASTNode *node);

#endif /* AST_H */
