#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static ASTNode *new_node(ASTNodeType type) {
    ASTNode *n = (ASTNode *)calloc(1, sizeof(ASTNode));
    if (!n) { fprintf(stderr, "[ERROR] Sin memoria para nodo AST\n"); exit(1); }
    n->type = type;
    return n;
}

ASTNode *ast_program(ASTNode **stmts, int count) {
    ASTNode *n = new_node(AST_PROGRAM);
    n->data.block.stmts = stmts;
    n->data.block.count = count;
    return n;
}

ASTNode *ast_var_decl(const char *name, DataType type, ASTNode *value) {
    ASTNode *n = new_node(AST_VAR_DECL);
    n->data.var_decl.name  = strdup(name);
    n->data.var_decl.type  = type;
    n->data.var_decl.value = value;
    return n;
}

ASTNode *ast_show(const char *name) {
    ASTNode *n = new_node(AST_SHOW);
    n->data.show.name = strdup(name);
    return n;
}

ASTNode *ast_binary_op(OpType op, ASTNode *left, ASTNode *right) {
    ASTNode *n = new_node(AST_BINARY_OP);
    n->data.binary_op.op    = op;
    n->data.binary_op.left  = left;
    n->data.binary_op.right = right;
    return n;
}

ASTNode *ast_literal_int(int v) {
    ASTNode *n = new_node(AST_LITERAL);
    n->data.literal.type        = TYPE_NUM;
    n->data.literal.val.i_value = v;
    return n;
}

ASTNode *ast_literal_double(double v) {
    ASTNode *n = new_node(AST_LITERAL);
    n->data.literal.type        = TYPE_DEC;
    n->data.literal.val.d_value = v;
    return n;
}

ASTNode *ast_literal_char(char v) {
    ASTNode *n = new_node(AST_LITERAL);
    n->data.literal.type        = TYPE_LETTER;
    n->data.literal.val.c_value = v;
    return n;
}

ASTNode *ast_literal_string(char *v) {
    ASTNode *n = new_node(AST_LITERAL);
    n->data.literal.type        = TYPE_WORD;
    n->data.literal.val.s_value = strdup(v);
    return n;
}

ASTNode *ast_literal_bool(int v) {
    ASTNode *n = new_node(AST_LITERAL);
    n->data.literal.type        = TYPE_BOOL;
    n->data.literal.val.b_value = v;
    return n;
}

ASTNode *ast_identifier(const char *name) {
    ASTNode *n = new_node(AST_IDENTIFIER);
    n->data.identifier = strdup(name);
    return n;
}

ASTNode *ast_func_decl(const char *name, DataType ret_type,
                       char **param_names, DataType *param_types,
                       int param_count, ASTNode *body) {
    ASTNode *n = new_node(AST_FUNC_DECL);
    n->data.func_decl.name        = strdup(name);
    n->data.func_decl.return_type = ret_type;
    n->data.func_decl.body        = body;
    n->data.func_decl.param_count = param_count;

    if (param_count > 0) {
        n->data.func_decl.param_names = malloc(sizeof(char *) * param_count);
        n->data.func_decl.param_types = malloc(sizeof(DataType) * param_count);
        for (int i = 0; i < param_count; i++) {
            n->data.func_decl.param_names[i] = strdup(param_names[i]);
            n->data.func_decl.param_types[i] = param_types[i];
        }
    } else {
        n->data.func_decl.param_names = NULL;
        n->data.func_decl.param_types = NULL;
    }
    return n;
}

ASTNode *ast_func_call(const char *name, ASTNode **args, int arg_count) {
    ASTNode *n = new_node(AST_FUNC_CALL);
    n->data.func_call.name      = strdup(name);
    n->data.func_call.args      = args;
    n->data.func_call.arg_count = arg_count;
    return n;
}

ASTNode *ast_block(ASTNode **stmts, int count) {
    ASTNode *n = new_node(AST_BLOCK);
    n->data.block.stmts = stmts;
    n->data.block.count = count;
    return n;
}

ASTNode *ast_return(ASTNode *value) {
    ASTNode *n = new_node(AST_RETURN);
    n->data.ret.value = value;
    return n;
}

ASTNode *ast_if(ASTNode *cond, ASTNode *then_body, ASTNode *else_body) {
    ASTNode *n = new_node(AST_IF);
    n->data.if_stmt.condition = cond;
    n->data.if_stmt.then_body = then_body;
    n->data.if_stmt.else_body = else_body;
    return n;
}

void ast_free(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case AST_PROGRAM:
        case AST_BLOCK:
            for (int i = 0; i < node->data.block.count; i++)
                ast_free(node->data.block.stmts[i]);
            free(node->data.block.stmts);
            break;
        case AST_VAR_DECL:
            free(node->data.var_decl.name);
            ast_free(node->data.var_decl.value);
            break;
        case AST_SHOW:
            free(node->data.show.name);
            break;
        case AST_BINARY_OP:
            ast_free(node->data.binary_op.left);
            ast_free(node->data.binary_op.right);
            break;
        case AST_LITERAL:
            if (node->data.literal.type == TYPE_WORD)
                free(node->data.literal.val.s_value);
            break;
        case AST_IDENTIFIER:
            free(node->data.identifier);
            break;
        case AST_FUNC_DECL:
            free(node->data.func_decl.name);
            for (int i = 0; i < node->data.func_decl.param_count; i++)
                free(node->data.func_decl.param_names[i]);
            free(node->data.func_decl.param_names);
            free(node->data.func_decl.param_types);
            ast_free(node->data.func_decl.body);
            break;
        case AST_FUNC_CALL:
            free(node->data.func_call.name);
            for (int i = 0; i < node->data.func_call.arg_count; i++)
                ast_free(node->data.func_call.args[i]);
            free(node->data.func_call.args);
            break;
        case AST_RETURN:
            ast_free(node->data.ret.value);
            break;
        case AST_IF:
            ast_free(node->data.if_stmt.condition);
            ast_free(node->data.if_stmt.then_body);
            ast_free(node->data.if_stmt.else_body);
            break;
    }

    free(node);
}
