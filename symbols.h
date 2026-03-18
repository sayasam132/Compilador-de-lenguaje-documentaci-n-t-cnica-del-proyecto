#ifndef SYMBOLS_H
#define SYMBOLS_H

/*
 * Tipos de datos del lenguaje propio.
 * Equivalencias:
 *   num    -> int
 *   dec    -> double
 *   letter -> char
 *   word   -> char*
 *   bool   -> int (1 = yes, 0 = no)
 */
typedef enum {
    TYPE_NUM,
    TYPE_DEC,
    TYPE_LETTER,
    TYPE_WORD,
    TYPE_BOOL
} DataType;

/*
 * Nodo de la tabla de simbolos.
 * Lista enlazada simple — cada variable declarada
 * es un nodo que apunta al siguiente.
 */
typedef struct SymbolEntry {
    DataType  data_type;
    char     *identifier;
    union {
        int    i_value; /* num    */
        double d_value; /* dec    */
        char   c_value; /* letter */
        char  *s_value; /* word   */
        int    b_value; /* bool   */
    } data;
    struct SymbolEntry *next;
} SymbolEntry;

extern SymbolEntry *root_table;

SymbolEntry *create_entry(const char *name);
SymbolEntry *find_entry(const char *name);

#endif /* SYMBOLS_H */
