#include "interpreter.h"
#include "type_coercion.h"
#include "scope.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FuncTable func_table;

static EvalResult make_result(RuntimeVal v, int is_ret) {
    EvalResult r;
    r.value     = v;
    r.is_return = is_ret;
    return r;
}

static RuntimeVal zero_val(void) {
    RuntimeVal v;
    v.type        = TYPE_NUM;
    v.val.i_value = 0;
    return v;
}

void interpreter_init(void) {
    func_table.defs     = NULL;
    func_table.count    = 0;
    func_table.capacity = 0;
}

void interpreter_destroy(void) {
    for (int i = 0; i < func_table.count; i++) {
        free(func_table.defs[i].name);
        for (int j = 0; j < func_table.defs[i].param_count; j++)
            free(func_table.defs[i].param_names[j]);
        free(func_table.defs[i].param_names);
        free(func_table.defs[i].param_types);
    }
    free(func_table.defs);
}

static void register_func(FuncDeclNode *fd) {
    for (int i = 0; i < func_table.count; i++) {
        if (strcmp(func_table.defs[i].name, fd->name) == 0) {
            fprintf(stderr, "[ERROR] Funcion '%s' ya definida\n", fd->name);
            return;
        }
    }
    if (func_table.count == func_table.capacity) {
        func_table.capacity = func_table.capacity ? func_table.capacity * 2 : 8;
        func_table.defs = realloc(func_table.defs,
                                  sizeof(FuncDef) * func_table.capacity);
    }
    FuncDef *def     = &func_table.defs[func_table.count++];
    def->name        = strdup(fd->name);
    def->return_type = fd->return_type;
    def->param_count = fd->param_count;
    def->body        = fd->body;
    if (fd->param_count > 0) {
        def->param_names = malloc(sizeof(char *)   * fd->param_count);
        def->param_types = malloc(sizeof(DataType) * fd->param_count);
        for (int i = 0; i < fd->param_count; i++) {
            def->param_names[i] = strdup(fd->param_names[i]);
            def->param_types[i] = fd->param_types[i];
        }
    } else {
        def->param_names = NULL;
        def->param_types = NULL;
    }
}

static FuncDef *find_func(const char *name) {
    for (int i = 0; i < func_table.count; i++)
        if (strcmp(func_table.defs[i].name, name) == 0)
            return &func_table.defs[i];
    return NULL;
}

static int is_truthy(RuntimeVal v) {
    switch (v.type) {
        case TYPE_NUM:    return v.val.i_value != 0;
        case TYPE_DEC:    return v.val.d_value != 0.0;
        case TYPE_LETTER: return v.val.c_value != 0;
        case TYPE_BOOL:   return v.val.b_value != 0;
        case TYPE_WORD:
            fprintf(stderr, "[ERROR] No se puede usar word como condicion\n");
            return 0;
        default: return 0;
    }
}

static double rval_to_double(RuntimeVal v) {
    switch (v.type) {
        case TYPE_NUM:    return (double)v.val.i_value;
        case TYPE_DEC:    return v.val.d_value;
        case TYPE_LETTER: return (double)v.val.c_value;
        case TYPE_BOOL:   return (double)v.val.b_value;
        default:          return 0.0;
    }
}

static void print_runtime_val(RuntimeVal v) {
    SymbolEntry tmp;
    tmp.data_type = v.type;
    switch (v.type) {
        case TYPE_NUM:    tmp.data.i_value = v.val.i_value; break;
        case TYPE_DEC:    tmp.data.d_value = v.val.d_value; break;
        case TYPE_LETTER: tmp.data.c_value = v.val.c_value; break;
        case TYPE_WORD:   tmp.data.s_value = v.val.s_value; break;
        case TYPE_BOOL:   tmp.data.b_value = v.val.b_value; break;
    }
    print_entry(&tmp);
}

EvalResult eval(ASTNode *node) {
    if (!node) return make_result(zero_val(), 0);

    switch (node->type) {

    case AST_PROGRAM: {
        for (int i = 0; i < node->data.block.count; i++) {
            EvalResult r = eval(node->data.block.stmts[i]);
            if (r.is_return) return r;
        }
        return make_result(zero_val(), 0);
    }

    case AST_BLOCK: {
        push_scope();
        EvalResult last = make_result(zero_val(), 0);
        for (int i = 0; i < node->data.block.count; i++) {
            last = eval(node->data.block.stmts[i]);
            if (last.is_return) { pop_scope(); return last; }
        }
        pop_scope();
        return last;
    }

    case AST_LITERAL: {
        RuntimeVal v;
        v.type = node->data.literal.type;
        switch (v.type) {
            case TYPE_NUM:    v.val.i_value = node->data.literal.val.i_value; break;
            case TYPE_DEC:    v.val.d_value = node->data.literal.val.d_value; break;
            case TYPE_LETTER: v.val.c_value = node->data.literal.val.c_value; break;
            case TYPE_WORD:   v.val.s_value = node->data.literal.val.s_value; break;
            case TYPE_BOOL:   v.val.b_value = node->data.literal.val.b_value; break;
        }
        return make_result(v, 0);
    }

    case AST_IDENTIFIER: {
        const char *name = node->data.identifier;
        SymbolEntry *e = find_entry(name);
        if (!e) {
            fprintf(stderr, "[ERROR] Variable '%s' no declarada\n", name);
            return make_result(zero_val(), 0);
        }
        RuntimeVal v;
        v.type = e->data_type;
        switch (v.type) {
            case TYPE_NUM:    v.val.i_value = e->data.i_value; break;
            case TYPE_DEC:    v.val.d_value = e->data.d_value; break;
            case TYPE_LETTER: v.val.c_value = e->data.c_value; break;
            case TYPE_WORD:   v.val.s_value = e->data.s_value; break;
            case TYPE_BOOL:   v.val.b_value = e->data.b_value; break;
        }
        return make_result(v, 0);
    }

    case AST_VAR_DECL: {
        VarDeclNode *vd = &node->data.var_decl;
        EvalResult rhs  = eval(vd->value);
        SymbolEntry *e  = create_entry(vd->name);
        if (!e) return make_result(zero_val(), 0);
        e->data_type = vd->type;
        if (vd->type == TYPE_WORD) {
            e->data.s_value = rhs.value.val.s_value
                              ? strdup(rhs.value.val.s_value) : strdup("");
        } else {
            assign_numeric_value(e, vd->type, rval_to_double(rhs.value));
        }
        return make_result(zero_val(), 0);
    }

    case AST_SHOW: {
        SymbolEntry *e = find_entry(node->data.show.name);
        if (!e) fprintf(stderr, "[ERROR] Variable '%s' no declarada\n",
                        node->data.show.name);
        else    print_entry(e);
        return make_result(zero_val(), 0);
    }

    case AST_BINARY_OP: {
        EvalResult lhs = eval(node->data.binary_op.left);
        EvalResult rhs = eval(node->data.binary_op.right);
        int is_double  = (lhs.value.type == TYPE_DEC ||
                          rhs.value.type == TYPE_DEC);
        double l = rval_to_double(lhs.value);
        double r = rval_to_double(rhs.value);
        /* Comparaciones: devuelven bool */
        switch (node->data.binary_op.op) {
            case OP_EQ:  { RuntimeVal v; v.type = TYPE_BOOL; v.val.b_value = (l == r); return make_result(v, 0); }
            case OP_NEQ: { RuntimeVal v; v.type = TYPE_BOOL; v.val.b_value = (l != r); return make_result(v, 0); }
            case OP_LT:  { RuntimeVal v; v.type = TYPE_BOOL; v.val.b_value = (l <  r); return make_result(v, 0); }
            case OP_GT:  { RuntimeVal v; v.type = TYPE_BOOL; v.val.b_value = (l >  r); return make_result(v, 0); }
            case OP_LE:  { RuntimeVal v; v.type = TYPE_BOOL; v.val.b_value = (l <= r); return make_result(v, 0); }
            case OP_GE:  { RuntimeVal v; v.type = TYPE_BOOL; v.val.b_value = (l >= r); return make_result(v, 0); }
            default: break;
        }

        /* Aritmetica */
        double result;
        switch (node->data.binary_op.op) {
            case OP_ADD: result = l + r; break;
            case OP_SUB: result = l - r; break;
            case OP_MUL: result = l * r; break;
            case OP_DIV:
                if (r == 0) { fprintf(stderr, "[ERROR] Division entre cero\n"); result = 0; }
                else        { result = l / r; }
                break;
            default: result = 0; break;
        }
        RuntimeVal v;
        if (is_double) { v.type = TYPE_DEC; v.val.d_value = result; }
        else           { v.type = TYPE_NUM; v.val.i_value = (int)result; }
        return make_result(v, 0);
    }

    case AST_FUNC_DECL:
        return make_result(zero_val(), 0);

    case AST_FUNC_CALL: {
        FuncCallNode *fc = &node->data.func_call;
        FuncDef *def = find_func(fc->name);
        if (!def) {
            fprintf(stderr, "[ERROR] Funcion '%s' no definida\n", fc->name);
            return make_result(zero_val(), 0);
        }
        if (fc->arg_count != def->param_count) {
            fprintf(stderr, "[ERROR] '%s': esperaba %d args, recibio %d\n",
                    fc->name, def->param_count, fc->arg_count);
            return make_result(zero_val(), 0);
        }
        RuntimeVal *arg_vals = malloc(sizeof(RuntimeVal) * (fc->arg_count + 1));
        for (int i = 0; i < fc->arg_count; i++)
            arg_vals[i] = eval(fc->args[i]).value;

        push_scope();

        for (int i = 0; i < def->param_count; i++) {
            SymbolEntry *p = create_entry(def->param_names[i]);
            if (!p) continue;
            p->data_type = def->param_types[i];
            if (def->param_types[i] == TYPE_WORD)
                p->data.s_value = arg_vals[i].val.s_value
                                  ? strdup(arg_vals[i].val.s_value) : strdup("");
            else
                assign_numeric_value(p, def->param_types[i],
                                     rval_to_double(arg_vals[i]));
        }
        free(arg_vals);

        EvalResult ret = eval(def->body);
        pop_scope();
        ret.is_return = 0;
        return ret;
    }

    case AST_RETURN: {
        EvalResult r = eval(node->data.ret.value);
        r.is_return = 1;
        return r;
    }

    case AST_IF: {
        EvalResult cond = eval(node->data.if_stmt.condition);
        if (is_truthy(cond.value)) {
            return eval(node->data.if_stmt.then_body);
        } else if (node->data.if_stmt.else_body) {
            return eval(node->data.if_stmt.else_body);
        }
        return make_result(zero_val(), 0);
    }

    default:
        fprintf(stderr, "[ERROR] Nodo AST desconocido: %d\n", node->type);
        return make_result(zero_val(), 0);
    }
}

void interpreter_run(ASTNode *program) {
    for (int i = 0; i < program->data.block.count; i++) {
        ASTNode *stmt = program->data.block.stmts[i];
        if (stmt && stmt->type == AST_FUNC_DECL)
            register_func(&stmt->data.func_decl);
    }
    for (int i = 0; i < program->data.block.count; i++) {
        ASTNode *stmt = program->data.block.stmts[i];
        if (stmt && stmt->type != AST_FUNC_DECL)
            eval(stmt);
    }
}
