#include <stdio.h>
#include <stdlib.h>
#include "scope.h"
#include "interpreter.h"
#include "ast.h"

int      yyparse(void);
extern FILE *yyin;
ASTNode *build_program(void);

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

    if (result == 0) {
        ASTNode *program = build_program();
        if (program) {
            interpreter_run(program);
            ast_free(program);
        }
    }

    interpreter_destroy();
    pop_scope();

    if (argc > 1) fclose(yyin);
    return result;
}
