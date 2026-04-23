#ifndef SCOPE_H
#define SCOPE_H

#include "symbols.h"

typedef struct ScopeLevel {
    SymbolEntry       *table;
    struct ScopeLevel *prev;
} ScopeLevel;

extern ScopeLevel *current_scope;

void push_scope(void);
void pop_scope(void);

#endif /* SCOPE_H */
