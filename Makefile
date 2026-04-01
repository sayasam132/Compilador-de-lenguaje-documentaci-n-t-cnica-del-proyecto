# ── Variables ──────────────────────────────────────────────
TARGET  = compiler

LEX_SRC = lexer.l
YAC_SRC = parser.y
SYM_SRC = symbols.c
HLP_SRC = parser_helper.c
AST_SRC = ast.c
INT_SRC = interpreter.c

LEX_OUT = lex.yy.c
YAC_OUT = y.tab.c
YAC_HDR = y.tab.h

CC      = gcc
LEX     = flex
YACC    = bison -d -y
CFLAGS  = -Wall -Wno-unused-function -Wno-unused-variable

# ── Reglas ─────────────────────────────────────────────────

$(TARGET): $(YAC_OUT) $(LEX_OUT) $(SYM_SRC) $(HLP_SRC) $(AST_SRC) $(INT_SRC)
	$(CC) $(CFLAGS) $(YAC_OUT) $(LEX_OUT) $(SYM_SRC) $(HLP_SRC) $(AST_SRC) $(INT_SRC) -o $(TARGET)

$(LEX_OUT): $(LEX_SRC) $(YAC_HDR)
	$(LEX) $(LEX_SRC)

$(YAC_OUT) $(YAC_HDR): $(YAC_SRC)
	$(YACC) $(YAC_SRC)


# ── Utilidades ─────────────────────────────────────────────

clean:
	rm -f $(TARGET) $(LEX_OUT) $(YAC_OUT) $(YAC_HDR)

run: $(TARGET)
	./$(TARGET) source.ws

