#include "type_coercion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void assign_numeric_value(SymbolEntry *entry, DataType type, double value) {
    entry->data_type = type;
    switch (type) {
        case TYPE_NUM:    entry->data.i_value = (int)value;  break;
        case TYPE_DEC:    entry->data.d_value = value;        break;
        case TYPE_LETTER: entry->data.c_value = (char)value; break;
        case TYPE_BOOL:   entry->data.b_value = (int)value;  break;
        case TYPE_WORD:
            printf("[ERROR] No se puede asignar un numero a tipo word\n");
            break;
    }
}

void assign_string_value(SymbolEntry *entry, DataType type, char *value) {
    if (type == TYPE_WORD) {
        entry->data_type = TYPE_WORD;
        if (entry->data.s_value) free(entry->data.s_value);
        entry->data.s_value = strdup(value);
        free(value);
    } else {
        printf("[ERROR] No se puede asignar una cadena a tipo no-word\n");
        free(value);
    }
}

void print_entry(SymbolEntry *entry) {
    switch (entry->data_type) {
        case TYPE_NUM:    printf("%d\n",   entry->data.i_value); break;
        case TYPE_DEC:    printf("%f\n",   entry->data.d_value); break;
        case TYPE_LETTER: printf("%c\n",   entry->data.c_value); break;
        case TYPE_WORD:   printf("%s\n",   entry->data.s_value ? entry->data.s_value : ""); break;
        case TYPE_BOOL:   printf("%s\n",   entry->data.b_value ? "yes" : "no"); break;
    }
}
