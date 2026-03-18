#include "symbols.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Inicio de la lista enlazada (tabla de simbolos) */
SymbolEntry *root_table = NULL;

/*
 * create_entry: crea un nuevo nodo con el nombre dado
 * y lo inserta al inicio de la lista.
 */
SymbolEntry *create_entry(const char *name) {
    SymbolEntry *node = (SymbolEntry *)malloc(sizeof(SymbolEntry));
    node->data_type    = TYPE_NUM;
    node->data.i_value = 0;
    node->identifier   = strdup(name);
    node->next         = root_table;
    root_table         = node;
    return node;
}

/*
 * find_entry: recorre la lista buscando el nodo
 * cuyo identificador coincida con 'name'.
 * Retorna NULL si no existe.
 */
SymbolEntry *find_entry(const char *name) {
    SymbolEntry *cur = root_table;
    while (cur) {
        if (strcmp(cur->identifier, name) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}
