#ifndef SYMBOLS_H
#define SYMBOLS_H

typedef enum {
    TYPE_NUM,
    TYPE_DEC,
    TYPE_LETTER,
    TYPE_WORD,
    TYPE_BOOL
} DataType;

typedef struct SymbolEntry {
    DataType  data_type;
    char     *identifier;
    union {
        int    i_value;
        double d_value;
        char   c_value;
        char  *s_value;
        int    b_value;
    } data;
    struct SymbolEntry *next;
} SymbolEntry;

SymbolEntry *create_entry(const char *name);
SymbolEntry *find_entry(const char *name);

#endif /* SYMBOLS_H */
