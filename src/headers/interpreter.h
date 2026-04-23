#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include "symbols.h"

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

typedef struct {
    RuntimeVal value;
    int        is_return;
} EvalResult;

typedef struct {
    char     *name;
    DataType  return_type;
    char    **param_names;
    DataType *param_types;
    int       param_count;
    ASTNode  *body;
} FuncDef;

typedef struct {
    FuncDef *defs;
    int      count;
    int      capacity;
} FuncTable;

void       interpreter_init(void);
void       interpreter_run(ASTNode *program);
void       interpreter_destroy(void);
EvalResult eval(ASTNode *node);

#endif /* INTERPRETER_H */
