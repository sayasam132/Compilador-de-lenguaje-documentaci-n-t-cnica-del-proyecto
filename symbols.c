#include "symbols.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tope de la pila de scopes */
ScopeLevel *current_scope = NULL;

/*
 * push_scope: crea un nuevo nivel vacio y lo pone en el tope.
 * Se llama al encontrar '{' en el parser.
 */
void push_scope(void) {
    ScopeLevel *s = (ScopeLevel *)malloc(sizeof(ScopeLevel));
    s->table       = NULL;
    s->prev        = current_scope;
    current_scope  = s;
}

/*
 * pop_scope: destruye el nivel del tope y baja al anterior.
 * Se llama al encontrar '}' en el parser.
 */
void pop_scope(void) {
    if (!current_scope) return;

    /* liberar todas las entradas del scope actual */
    SymbolEntry *e = current_scope->table;
    while (e) {
        SymbolEntry *tmp = e->next;
        if (e->data_type == TYPE_WORD && e->data.s_value)
            free(e->data.s_value);
        free(e->identifier);
        free(e);
        e = tmp;
    }

    /* bajar un nivel */
    ScopeLevel *old = current_scope;
    current_scope   = current_scope->prev;
    free(old);
}

/*
 * create_entry: inserta un nuevo nodo en la tabla del scope actual.
 * Si el nombre ya existe EN ESTE NIVEL, reporta colision y retorna NULL.
 */
SymbolEntry *create_entry(const char *name) {
    if (!current_scope) {
        fprintf(stderr, "[ERROR] No hay scope activo.\n");
        return NULL;
    }

    /* verificar colision en el nivel actual */
    SymbolEntry *e = current_scope->table;
    while (e) {
        if (strcmp(e->identifier, name) == 0) {
            fprintf(stderr, "[ERROR] Variable '%s' ya declarada en este nivel.\n", name);
            return NULL;
        }
        e = e->next;
    }

    /* insertar al frente, igual que antes */
    SymbolEntry *node = (SymbolEntry *)malloc(sizeof(SymbolEntry));
    node->data_type    = TYPE_NUM;
    node->data.i_value = 0;
    node->identifier   = strdup(name);
    node->next         = current_scope->table;
    current_scope->table = node;
    return node;
}

/*
 * find_entry: busca desde el tope hacia la base.
 * El primer match gana — asi funciona el shadowing.
 */
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