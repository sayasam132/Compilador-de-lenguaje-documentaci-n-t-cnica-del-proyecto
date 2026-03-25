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

/*
 * Un nivel de la pila de scopes.
 * Cada bloque { } tiene su propia tabla (lista enlazada de SymbolEntry).
 */
typedef struct ScopeLevel {
    SymbolEntry       *table; /* lista de variables de este nivel */
    struct ScopeLevel *prev;  /* nivel anterior (mas abajo en la pila) */
} ScopeLevel;

extern ScopeLevel *current_scope; /* tope de la pila */

/* Gestion de scopes */
void         push_scope(void);
void         pop_scope(void);

/* Operaciones de simbolos — mismas firmas que antes */
SymbolEntry *create_entry(const char *name);
SymbolEntry *find_entry(const char *name);

#endif /* SYMBOLS_H */