#ifndef PARSER_HELPER_H
#define PARSER_HELPER_H

#include "symbols.h"

/* Asigna un valor numerico a una variable segun su tipo */
void assign_numeric_value(SymbolEntry *entry, DataType type, double value);

/* Asigna un valor de cadena a una variable de tipo word */
void assign_string_value(SymbolEntry *entry, DataType type, char *value);

/* Imprime el valor de una variable segun su tipo */
void print_entry(SymbolEntry *entry);

#endif /* PARSER_HELPER_H */
