#include "symbols.h"
#include "scope.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SymbolEntry *create_entry(const char *name) {
    if (!current_scope) {
        fprintf(stderr, "[ERROR] No hay scope activo.\n");
        return NULL;
    }

    SymbolEntry *e = current_scope->table;
    while (e) {
        if (strcmp(e->identifier, name) == 0) {
            fprintf(stderr, "[ERROR] Variable '%s' ya declarada en este nivel.\n", name);
            return NULL;
        }
        e = e->next;
    }

    SymbolEntry *node = (SymbolEntry *)malloc(sizeof(SymbolEntry));
    node->data_type    = TYPE_NUM;
    node->data.i_value = 0;
    node->identifier   = strdup(name);
    node->next         = current_scope->table;
    current_scope->table = node;
    return node;
}

SymbolEntry *find_entry(const char *name) {
    ScopeLevel *scope = current_scope;
    while (scope) {
        SymbolEntry *e = scope->table;
        while (e) {
            if (strcmp(e->identifier, name) == 0) return e;
            e = e->next;
        }
        scope = scope->prev;
    }
    return NULL;
}
