#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include "symbols.h"

/* ── Valor en tiempo de ejecucion ───────────────────────── */
typedef struct {
    DataType type;
    union {
        int    i_value;
        double d_value;
        char   c_value;
        char  *s_value;
        int    b_value;
    } val;
} RuntimeVal;

/* ── Resultado de evaluacion (con flag de return) ────────── */
typedef struct {
    RuntimeVal value;
    int        is_return;  /* 1 si se ejecuto un return      */
} EvalResult;

/* ── Registro de una funcion definida ────────────────────── */
typedef struct {
    char     *name;
    DataType  return_type;
    char    **param_names;
    DataType *param_types;
    int       param_count;
    ASTNode  *body;        /* AST_BLOCK del cuerpo           */
} FuncDef;

/* ── Tabla de funciones del interprete ───────────────────── */
typedef struct {
    FuncDef *defs;
    int      count;
    int      capacity;
} FuncTable;

/* ── API del interprete ──────────────────────────────────── */
void       interpreter_init(void);
void       interpreter_run(ASTNode *program);
void       interpreter_destroy(void);

/* Evaluacion de un nodo (publica para recursion) */
EvalResult eval(ASTNode *node);

#endif /* INTERPRETER_H */
