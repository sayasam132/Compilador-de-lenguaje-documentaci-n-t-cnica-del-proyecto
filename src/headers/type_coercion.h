#ifndef TYPE_COERCION_H
#define TYPE_COERCION_H

#include "symbols.h"

void assign_numeric_value(SymbolEntry *entry, DataType type, double value);
void assign_string_value(SymbolEntry *entry, DataType type, char *value);
void print_entry(SymbolEntry *entry);

#endif /* TYPE_COERCION_H */
