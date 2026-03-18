# ── Variables ──────────────────────────────────────────────
TARGET  = compiler

LEX_SRC = lexer.l
YAC_SRC = parser.y
SYM_SRC = symbols.c
HLP_SRC = parser_helper.c

LEX_OUT = lex.yy.c
YAC_OUT = y.tab.c
YAC_HDR = y.tab.h

CC      = gcc
LEX     = flex
YACC    = yacc -d
CFLAGS  = -Wall -Wno-unused-function

# ── Reglas ─────────────────────────────────────────────────

# 1. Enlaza todo en el ejecutable final
$(TARGET): $(YAC_OUT) $(LEX_OUT) $(SYM_SRC) $(HLP_SRC)
	$(CC) $(CFLAGS) $(YAC_OUT) $(LEX_OUT) $(SYM_SRC) $(HLP_SRC) -o $(TARGET)

# 2. Genera el lexer en C (depende del header de yacc)
$(LEX_OUT): $(LEX_SRC) $(YAC_HDR)
	$(LEX) $(LEX_SRC)

# 3. Genera el parser en C y su header
$(YAC_OUT) $(YAC_HDR): $(YAC_SRC)
	$(YACC) $(YAC_SRC)

# ── Utilidades ─────────────────────────────────────────────
clean:
	rm -f $(TARGET) $(LEX_OUT) $(YAC_OUT) $(YAC_HDR)

run: $(TARGET)
	./$(TARGET) source.ws
