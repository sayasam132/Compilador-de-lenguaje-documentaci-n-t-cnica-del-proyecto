# ── Variables ──────────────────────────────────────────────
TARGET  = compiler

LEX_SRC = lexer.l
YAC_SRC = parser.y

SRC_DIR = src
HDR_DIR = src/headers

LEX_OUT = lex.yy.c
YAC_OUT = y.tab.c
YAC_HDR = y.tab.h

CC     = gcc
LEX    = flex
YACC   = bison -d -y
CFLAGS = -Wall -Wno-unused-function -Wno-unused-variable -I$(HDR_DIR)

SRCS = $(YAC_OUT) $(LEX_OUT) \
       $(SRC_DIR)/symbols.c  $(SRC_DIR)/scope.c \
       $(SRC_DIR)/type_coercion.c $(SRC_DIR)/ast.c \
       $(SRC_DIR)/interpreter.c   $(SRC_DIR)/main.c

# ── Reglas ─────────────────────────────────────────────────

$(TARGET): $(YAC_OUT) $(LEX_OUT)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

$(LEX_OUT): $(LEX_SRC) $(YAC_HDR)
	$(LEX) $(LEX_SRC)

$(YAC_OUT) $(YAC_HDR): $(YAC_SRC)
	$(YACC) $(YAC_SRC)

# ── Utilidades ─────────────────────────────────────────────

clean:
	rm -f $(TARGET) $(LEX_OUT) $(YAC_OUT) $(YAC_HDR)

run: $(TARGET)
	./$(TARGET) source.español

test: $(TARGET)
	@bash test/run_tests.sh
