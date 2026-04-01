#include "parser_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * assign_numeric_value:
 * Convierte el valor double recibido al tipo correcto
 * y lo guarda en el campo correspondiente del union.
 */
void assign_numeric_value(SymbolEntry *entry, DataType type, double value) {
    entry->data_type = type;
    switch (type) {
        case TYPE_NUM:    entry->data.i_value = (int)value;    break;
        case TYPE_DEC:    entry->data.d_value = value;          break;
        case TYPE_LETTER: entry->data.c_value = (char)value;   break;
        case TYPE_BOOL:   entry->data.b_value = (int)value;    break;
        case TYPE_WORD:
            printf("[ERROR] No se puede asignar un numero a tipo word\n");
            break;
    }
}

/*
 * assign_string_value:
 * Solo acepta TYPE_WORD. Libera el valor anterior si existia,
 * luego copia la nueva cadena con strdup.
 */
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

/*
 * print_entry:
 * Imprime el valor de la variable con el formato correcto
 * segun su tipo. Los booleanos se imprimen como yes/no.
 */
void print_entry(SymbolEntry *entry) {
    switch (entry->data_type) {
        case TYPE_NUM:    printf("%d\n",   entry->data.i_value); break;
        case TYPE_DEC:    printf("%f\n", entry->data.d_value); break;
        case TYPE_LETTER: printf("%c\n",   entry->data.c_value); break;
        case TYPE_WORD:   printf("%s\n",   entry->data.s_value ? entry->data.s_value : ""); break;
        case TYPE_BOOL:   printf("%s\n",   entry->data.b_value ? "yes" : "no"); break;
    }
}