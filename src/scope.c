#include "scope.h"
#include <stdlib.h>
#include <string.h>

ScopeLevel *current_scope = NULL;

void push_scope(void) {
    ScopeLevel *s = (ScopeLevel *)malloc(sizeof(ScopeLevel));
    s->table      = NULL;
    s->prev       = current_scope;
    current_scope = s;
}

void pop_scope(void) {
    if (!current_scope) return;

    SymbolEntry *e = current_scope->table;
    while (e) {
        SymbolEntry *tmp = e->next;
        if (e->data_type == TYPE_WORD && e->data.s_value)
            free(e->data.s_value);
        free(e->identifier);
        free(e);
        e = tmp;
    }

    ScopeLevel *old = current_scope;
    current_scope   = current_scope->prev;
    free(old);
}
