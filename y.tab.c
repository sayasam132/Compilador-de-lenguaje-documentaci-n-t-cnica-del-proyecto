/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"
#include "parser_helper.h"
#include "ast.h"
#include "interpreter.h"

int  yylex(void);
void yyerror(const char *s);
extern FILE *yyin;

/* ─── Lista dinamica de sentencias del programa global ─── */
static ASTNode **g_stmts = NULL;
static int       g_count = 0;
static int       g_cap   = 0;

static void g_push(ASTNode *n) {
    if (!n) return;
    if (g_count == g_cap) {
        g_cap   = g_cap ? g_cap * 2 : 16;
        g_stmts = realloc(g_stmts, sizeof(ASTNode *) * g_cap);
    }
    g_stmts[g_count++] = n;
}

/* ─── Lista dinamica de sentencias de una funcion ────────
 * Usamos una pila de contextos para funciones anidadas     */
#define MAX_FUNC_DEPTH 32
static ASTNode **f_stmts[MAX_FUNC_DEPTH];
static int       f_count[MAX_FUNC_DEPTH];
static int       f_cap  [MAX_FUNC_DEPTH];
static int       f_depth = -1;          /* -1 = no estamos en funcion */

static void f_begin(void) {
    f_depth++;
    f_stmts[f_depth] = NULL;
    f_count[f_depth] = 0;
    f_cap  [f_depth] = 0;
}

static void f_push(ASTNode *n) {
    if (!n || f_depth < 0) return;
    if (f_count[f_depth] == f_cap[f_depth]) {
        f_cap[f_depth]   = f_cap[f_depth] ? f_cap[f_depth] * 2 : 8;
        f_stmts[f_depth] = realloc(f_stmts[f_depth],
                                   sizeof(ASTNode *) * f_cap[f_depth]);
    }
    f_stmts[f_depth][f_count[f_depth]++] = n;
}

static ASTNode *f_end(void) {
    ASTNode *blk = ast_block(f_stmts[f_depth], f_count[f_depth]);
    f_depth--;
    return blk;
}

#line 130 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LET = 258,                     /* LET  */
    AS = 259,                      /* AS  */
    SHOW = 260,                    /* SHOW  */
    ASSIGN = 261,                  /* ASSIGN  */
    SEMI = 262,                    /* SEMI  */
    LPAREN = 263,                  /* LPAREN  */
    RPAREN = 264,                  /* RPAREN  */
    T_NUM = 265,                   /* T_NUM  */
    T_DEC = 266,                   /* T_DEC  */
    T_LETTER = 267,                /* T_LETTER  */
    T_WORD = 268,                  /* T_WORD  */
    T_BOOL = 269,                  /* T_BOOL  */
    PLUS = 270,                    /* PLUS  */
    MINUS = 271,                   /* MINUS  */
    STAR = 272,                    /* STAR  */
    SLASH = 273,                   /* SLASH  */
    LBRACE = 274,                  /* LBRACE  */
    RBRACE = 275,                  /* RBRACE  */
    VAR = 276,                     /* VAR  */
    PRINT = 277,                   /* PRINT  */
    FUNC = 278,                    /* FUNC  */
    RETURN = 279,                  /* RETURN  */
    ARROW = 280,                   /* ARROW  */
    COLON = 281,                   /* COLON  */
    COMMA = 282,                   /* COMMA  */
    LBRACKET = 283,                /* LBRACKET  */
    RBRACKET = 284,                /* RBRACKET  */
    IDENTIFIER = 285,              /* IDENTIFIER  */
    INT_LIT = 286,                 /* INT_LIT  */
    FLOAT_LIT = 287,               /* FLOAT_LIT  */
    CHAR_LIT = 288,                /* CHAR_LIT  */
    BOOL_LIT = 289,                /* BOOL_LIT  */
    STRING_LIT = 290               /* STRING_LIT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define LET 258
#define AS 259
#define SHOW 260
#define ASSIGN 261
#define SEMI 262
#define LPAREN 263
#define RPAREN 264
#define T_NUM 265
#define T_DEC 266
#define T_LETTER 267
#define T_WORD 268
#define T_BOOL 269
#define PLUS 270
#define MINUS 271
#define STAR 272
#define SLASH 273
#define LBRACE 274
#define RBRACE 275
#define VAR 276
#define PRINT 277
#define FUNC 278
#define RETURN 279
#define ARROW 280
#define COLON 281
#define COMMA 282
#define LBRACKET 283
#define RBRACKET 284
#define IDENTIFIER 285
#define INT_LIT 286
#define FLOAT_LIT 287
#define CHAR_LIT 288
#define BOOL_LIT 289
#define STRING_LIT 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 61 "parser.y"

    int      i_val;
    double   f_val;
    char     c_val;
    int      b_val;
    char    *s_val;
    int      type_tag;
    struct ASTNode *node;
    struct {
        struct ASTNode **list;
        int count;
        int cap;
    } node_list;
    struct {
        char **names;
        int  *types;
        int   count;
        int   cap;
    } param_list;

#line 274 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LET = 3,                        /* LET  */
  YYSYMBOL_AS = 4,                         /* AS  */
  YYSYMBOL_SHOW = 5,                       /* SHOW  */
  YYSYMBOL_ASSIGN = 6,                     /* ASSIGN  */
  YYSYMBOL_SEMI = 7,                       /* SEMI  */
  YYSYMBOL_LPAREN = 8,                     /* LPAREN  */
  YYSYMBOL_RPAREN = 9,                     /* RPAREN  */
  YYSYMBOL_T_NUM = 10,                     /* T_NUM  */
  YYSYMBOL_T_DEC = 11,                     /* T_DEC  */
  YYSYMBOL_T_LETTER = 12,                  /* T_LETTER  */
  YYSYMBOL_T_WORD = 13,                    /* T_WORD  */
  YYSYMBOL_T_BOOL = 14,                    /* T_BOOL  */
  YYSYMBOL_PLUS = 15,                      /* PLUS  */
  YYSYMBOL_MINUS = 16,                     /* MINUS  */
  YYSYMBOL_STAR = 17,                      /* STAR  */
  YYSYMBOL_SLASH = 18,                     /* SLASH  */
  YYSYMBOL_LBRACE = 19,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 20,                    /* RBRACE  */
  YYSYMBOL_VAR = 21,                       /* VAR  */
  YYSYMBOL_PRINT = 22,                     /* PRINT  */
  YYSYMBOL_FUNC = 23,                      /* FUNC  */
  YYSYMBOL_RETURN = 24,                    /* RETURN  */
  YYSYMBOL_ARROW = 25,                     /* ARROW  */
  YYSYMBOL_COLON = 26,                     /* COLON  */
  YYSYMBOL_COMMA = 27,                     /* COMMA  */
  YYSYMBOL_LBRACKET = 28,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 29,                  /* RBRACKET  */
  YYSYMBOL_IDENTIFIER = 30,                /* IDENTIFIER  */
  YYSYMBOL_INT_LIT = 31,                   /* INT_LIT  */
  YYSYMBOL_FLOAT_LIT = 32,                 /* FLOAT_LIT  */
  YYSYMBOL_CHAR_LIT = 33,                  /* CHAR_LIT  */
  YYSYMBOL_BOOL_LIT = 34,                  /* BOOL_LIT  */
  YYSYMBOL_STRING_LIT = 35,                /* STRING_LIT  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_program = 37,                   /* program  */
  YYSYMBOL_global_stmt = 38,               /* global_stmt  */
  YYSYMBOL_39_1 = 39,                      /* $@1  */
  YYSYMBOL_40_2 = 40,                      /* $@2  */
  YYSYMBOL_func_stmts = 41,                /* func_stmts  */
  YYSYMBOL_func_stmt = 42,                 /* func_stmt  */
  YYSYMBOL_num_type = 43,                  /* num_type  */
  YYSYMBOL_param_list = 44,                /* param_list  */
  YYSYMBOL_param_list_ne = 45,             /* param_list_ne  */
  YYSYMBOL_arg_list = 46,                  /* arg_list  */
  YYSYMBOL_arg_list_ne = 47,               /* arg_list_ne  */
  YYSYMBOL_expr = 48                       /* expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   150

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  44
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  125

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   112,   112,   113,   118,   120,   123,   126,   130,   132,
     135,   138,   142,   142,   147,   145,   162,   163,   167,   169,
     171,   173,   175,   181,   182,   183,   188,   189,   196,   205,
     221,   222,   226,   232,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LET", "AS", "SHOW",
  "ASSIGN", "SEMI", "LPAREN", "RPAREN", "T_NUM", "T_DEC", "T_LETTER",
  "T_WORD", "T_BOOL", "PLUS", "MINUS", "STAR", "SLASH", "LBRACE", "RBRACE",
  "VAR", "PRINT", "FUNC", "RETURN", "ARROW", "COLON", "COMMA", "LBRACKET",
  "RBRACKET", "IDENTIFIER", "INT_LIT", "FLOAT_LIT", "CHAR_LIT", "BOOL_LIT",
  "STRING_LIT", "$accept", "program", "global_stmt", "$@1", "$@2",
  "func_stmts", "func_stmt", "num_type", "param_list", "param_list_ne",
  "arg_list", "arg_list_ne", "expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-46)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -46,    33,   -46,   -27,   -18,   -46,   -10,   -12,    -6,   -46,
      19,    24,   -46,     4,    27,    29,    93,   -46,    45,   104,
     -46,     7,   -46,   -46,   -46,    34,    35,    40,   -46,    16,
      18,    20,    -5,    42,    30,    36,    28,    -4,    43,    46,
      57,    59,    44,    47,    82,    85,    -4,   100,   -46,   -46,
     -46,   -46,    63,   103,   113,   118,    96,    97,    -5,   -46,
     -46,    -7,    -4,   -46,    -4,    -4,    -4,    -4,    92,    94,
      -4,   -46,    -5,   101,   -46,   120,   106,   105,    -3,    -3,
     -46,   -46,   124,   125,    67,   107,   108,   -46,    -4,   -46,
     -46,   -46,   115,   -46,   105,   -46,   -46,    39,   109,   110,
     -46,   111,   112,    -4,   -46,   131,   134,   116,   136,    79,
      -5,   -46,    -5,   -46,   -46,   139,   117,    -4,   119,    83,
     141,   -46,    -4,    95,   -46
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     1,     0,     0,    12,     0,     0,     0,     2,
       0,     0,     3,     0,     0,     0,     0,     7,     0,     0,
      11,    27,    23,    24,    25,     0,     0,     0,    13,     0,
       0,     0,     0,     0,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    39,    34,    35,
      36,    37,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     0,    31,     4,     0,     0,     0,     0,     0,     0,
       0,    28,     0,     0,    44,     0,    30,    32,    40,    41,
      42,    43,     0,     0,     0,     0,     0,    38,     0,     9,
      10,     8,     0,    29,    33,    14,    17,     0,     0,     0,
      15,     0,     0,     0,    16,     0,     0,     0,     0,     0,
       0,    21,     0,    20,    22,     0,     0,     0,     0,     0,
       0,    19,     0,     0,    18
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -46,   138,   -46,   -46,   -46,   -46,   -46,   -19,   -46,   -46,
     -46,   -46,   -45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     9,    12,    96,    97,   104,    27,    33,    34,
      75,    76,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      31,    61,    74,    10,    46,    22,    23,    24,    64,    65,
      66,    67,    11,    41,    66,    67,    13,    77,    14,    78,
      79,    80,    81,    16,    15,    84,    47,    48,    49,    50,
      51,    17,    19,     2,    20,    32,     3,    21,     4,    73,
      35,    36,    98,    94,    99,    38,    37,    39,     3,    40,
       4,    42,     5,    85,     6,     7,     8,    43,   109,   100,
     101,   102,    45,   103,     5,    28,     6,     7,     8,    57,
      63,    44,   119,    53,    91,    58,    54,   123,    64,    65,
      66,    67,    64,    65,    66,    67,   114,    55,    56,    59,
     121,   115,    60,   116,    64,    65,    66,    67,    64,    65,
      66,    67,   124,    22,    23,    24,    25,    26,    62,    68,
      64,    65,    66,    67,    22,    23,    24,    29,    30,    69,
      64,    65,    66,    67,    70,    72,    71,    82,    83,    87,
      86,    89,    90,    88,    95,   110,    92,   107,    93,   105,
     106,   111,   108,   113,   112,   117,   118,   122,     0,   120,
      18
};

static const yytype_int8 yycheck[] =
{
      19,    46,     9,    30,     8,    10,    11,    12,    15,    16,
      17,    18,    30,    32,    17,    18,    26,    62,    30,    64,
      65,    66,    67,     4,    30,    70,    30,    31,    32,    33,
      34,     7,    28,     0,     7,    28,     3,     8,     5,    58,
       6,     6,     3,    88,     5,    29,     6,    29,     3,    29,
       5,     9,    19,    72,    21,    22,    23,    27,   103,    20,
      21,    22,    34,    24,    19,    20,    21,    22,    23,    25,
       7,    35,   117,    30,     7,    28,    30,   122,    15,    16,
      17,    18,    15,    16,    17,    18,     7,    30,    29,     7,
       7,   110,     7,   112,    15,    16,    17,    18,    15,    16,
      17,    18,     7,    10,    11,    12,    13,    14,     8,     6,
      15,    16,    17,    18,    10,    11,    12,    13,    14,     6,
      15,    16,    17,    18,     6,    28,    30,    35,    34,     9,
      29,     7,     7,    27,    19,     4,    29,    26,    30,    30,
      30,     7,    30,     7,    28,     6,    29,     6,    -1,    30,
      12
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    37,     0,     3,     5,    19,    21,    22,    23,    38,
      30,    30,    39,    26,    30,    30,     4,     7,    37,    28,
       7,     8,    10,    11,    12,    13,    14,    43,    20,    13,
      14,    43,    28,    44,    45,     6,     6,     6,    29,    29,
      29,    43,     9,    27,    35,    34,     8,    30,    31,    32,
      33,    34,    48,    30,    30,    30,    29,    25,    28,     7,
       7,    48,     8,     7,    15,    16,    17,    18,     6,     6,
       6,    30,    28,    43,     9,    46,    47,    48,    48,    48,
      48,    48,    35,    34,    48,    43,    29,     9,    27,     7,
       7,     7,    29,    30,    48,    19,    40,    41,     3,     5,
      20,    21,    22,    24,    42,    30,    30,    26,    30,    48,
       4,     7,    28,     7,     7,    43,    43,     6,    29,    48,
      30,     7,     6,    48,     7
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    37,    38,    38,    38,    38,    38,    38,
      38,    38,    39,    38,    40,    38,    41,    41,    42,    42,
      42,    42,    42,    43,    43,    43,    44,    44,    45,    45,
      46,    46,    47,    47,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     7,     7,     7,     3,     9,     9,
       9,     3,     0,     4,     0,    13,     2,     0,     9,     7,
       3,     3,     3,     1,     1,     1,     1,     0,     4,     6,
       1,     0,     1,     3,     1,     1,     1,     1,     4,     1,
       3,     3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 4: /* global_stmt: LET IDENTIFIER AS num_type ASSIGN expr SEMI  */
#line 119 "parser.y"
        { g_push(ast_var_decl((yyvsp[-5].s_val), (DataType)(yyvsp[-3].type_tag), (yyvsp[-1].node))); free((yyvsp[-5].s_val)); }
#line 1377 "y.tab.c"
    break;

  case 5: /* global_stmt: LET IDENTIFIER AS T_WORD ASSIGN STRING_LIT SEMI  */
#line 121 "parser.y"
        { g_push(ast_var_decl((yyvsp[-5].s_val), TYPE_WORD, ast_literal_string((yyvsp[-1].s_val))));
          free((yyvsp[-5].s_val)); free((yyvsp[-1].s_val)); }
#line 1384 "y.tab.c"
    break;

  case 6: /* global_stmt: LET IDENTIFIER AS T_BOOL ASSIGN BOOL_LIT SEMI  */
#line 124 "parser.y"
        { g_push(ast_var_decl((yyvsp[-5].s_val), TYPE_BOOL, ast_literal_bool((yyvsp[-1].b_val))));
          free((yyvsp[-5].s_val)); }
#line 1391 "y.tab.c"
    break;

  case 7: /* global_stmt: SHOW IDENTIFIER SEMI  */
#line 127 "parser.y"
        { g_push(ast_show((yyvsp[-1].s_val))); free((yyvsp[-1].s_val)); }
#line 1397 "y.tab.c"
    break;

  case 8: /* global_stmt: VAR COLON LBRACKET num_type RBRACKET IDENTIFIER ASSIGN expr SEMI  */
#line 131 "parser.y"
        { g_push(ast_var_decl((yyvsp[-3].s_val), (DataType)(yyvsp[-5].type_tag), (yyvsp[-1].node))); free((yyvsp[-3].s_val)); }
#line 1403 "y.tab.c"
    break;

  case 9: /* global_stmt: VAR COLON LBRACKET T_WORD RBRACKET IDENTIFIER ASSIGN STRING_LIT SEMI  */
#line 133 "parser.y"
        { g_push(ast_var_decl((yyvsp[-3].s_val), TYPE_WORD, ast_literal_string((yyvsp[-1].s_val))));
          free((yyvsp[-3].s_val)); free((yyvsp[-1].s_val)); }
#line 1410 "y.tab.c"
    break;

  case 10: /* global_stmt: VAR COLON LBRACKET T_BOOL RBRACKET IDENTIFIER ASSIGN BOOL_LIT SEMI  */
#line 136 "parser.y"
        { g_push(ast_var_decl((yyvsp[-3].s_val), TYPE_BOOL, ast_literal_bool((yyvsp[-1].b_val))));
          free((yyvsp[-3].s_val)); }
#line 1417 "y.tab.c"
    break;

  case 11: /* global_stmt: PRINT IDENTIFIER SEMI  */
#line 139 "parser.y"
        { g_push(ast_show((yyvsp[-1].s_val))); free((yyvsp[-1].s_val)); }
#line 1423 "y.tab.c"
    break;

  case 12: /* $@1: %empty  */
#line 142 "parser.y"
             { push_scope(); }
#line 1429 "y.tab.c"
    break;

  case 13: /* global_stmt: LBRACE $@1 program RBRACE  */
#line 142 "parser.y"
                                              { pop_scope(); }
#line 1435 "y.tab.c"
    break;

  case 14: /* $@2: %empty  */
#line 147 "parser.y"
             { f_begin(); }
#line 1441 "y.tab.c"
    break;

  case 15: /* global_stmt: FUNC IDENTIFIER LPAREN param_list RPAREN ARROW LBRACKET num_type RBRACKET LBRACE $@2 func_stmts RBRACE  */
#line 148 "parser.y"
      {
          ASTNode *body = f_end();
          g_push(ast_func_decl((yyvsp[-11].s_val), (DataType)(yyvsp[-5].type_tag),
                               (yyvsp[-9].param_list).names, (DataType *)(yyvsp[-9].param_list).types, (yyvsp[-9].param_list).count,
                               body));
          for (int i = 0; i < (yyvsp[-9].param_list).count; i++) free((yyvsp[-9].param_list).names[i]);
          free((yyvsp[-9].param_list).names);
          free((yyvsp[-9].param_list).types);
          free((yyvsp[-11].s_val));
      }
#line 1456 "y.tab.c"
    break;

  case 18: /* func_stmt: VAR COLON LBRACKET num_type RBRACKET IDENTIFIER ASSIGN expr SEMI  */
#line 168 "parser.y"
        { f_push(ast_var_decl((yyvsp[-3].s_val), (DataType)(yyvsp[-5].type_tag), (yyvsp[-1].node))); free((yyvsp[-3].s_val)); }
#line 1462 "y.tab.c"
    break;

  case 19: /* func_stmt: LET IDENTIFIER AS num_type ASSIGN expr SEMI  */
#line 170 "parser.y"
        { f_push(ast_var_decl((yyvsp[-5].s_val), (DataType)(yyvsp[-3].type_tag), (yyvsp[-1].node))); free((yyvsp[-5].s_val)); }
#line 1468 "y.tab.c"
    break;

  case 20: /* func_stmt: PRINT IDENTIFIER SEMI  */
#line 172 "parser.y"
        { f_push(ast_show((yyvsp[-1].s_val))); free((yyvsp[-1].s_val)); }
#line 1474 "y.tab.c"
    break;

  case 21: /* func_stmt: SHOW IDENTIFIER SEMI  */
#line 174 "parser.y"
        { f_push(ast_show((yyvsp[-1].s_val))); free((yyvsp[-1].s_val)); }
#line 1480 "y.tab.c"
    break;

  case 22: /* func_stmt: RETURN expr SEMI  */
#line 176 "parser.y"
        { f_push(ast_return((yyvsp[-1].node))); }
#line 1486 "y.tab.c"
    break;

  case 23: /* num_type: T_NUM  */
#line 181 "parser.y"
               { (yyval.type_tag) = TYPE_NUM;    }
#line 1492 "y.tab.c"
    break;

  case 24: /* num_type: T_DEC  */
#line 182 "parser.y"
               { (yyval.type_tag) = TYPE_DEC;    }
#line 1498 "y.tab.c"
    break;

  case 25: /* num_type: T_LETTER  */
#line 183 "parser.y"
               { (yyval.type_tag) = TYPE_LETTER; }
#line 1504 "y.tab.c"
    break;

  case 26: /* param_list: param_list_ne  */
#line 188 "parser.y"
                    { (yyval.param_list) = (yyvsp[0].param_list); }
#line 1510 "y.tab.c"
    break;

  case 27: /* param_list: %empty  */
#line 189 "parser.y"
                  {
        (yyval.param_list).names = NULL; (yyval.param_list).types = NULL;
        (yyval.param_list).count = 0;    (yyval.param_list).cap   = 0;
    }
#line 1519 "y.tab.c"
    break;

  case 28: /* param_list_ne: LBRACKET num_type RBRACKET IDENTIFIER  */
#line 196 "parser.y"
                                            {
        (yyval.param_list).names    = malloc(sizeof(char *) * 4);
        (yyval.param_list).types    = malloc(sizeof(int)    * 4);
        (yyval.param_list).count    = 1;
        (yyval.param_list).cap      = 4;
        (yyval.param_list).names[0] = strdup((yyvsp[0].s_val));
        (yyval.param_list).types[0] = (yyvsp[-2].type_tag);
        free((yyvsp[0].s_val));
    }
#line 1533 "y.tab.c"
    break;

  case 29: /* param_list_ne: param_list_ne COMMA LBRACKET num_type RBRACKET IDENTIFIER  */
#line 205 "parser.y"
                                                                {
        (yyval.param_list) = (yyvsp[-5].param_list);
        if ((yyval.param_list).count == (yyval.param_list).cap) {
            (yyval.param_list).cap   = (yyval.param_list).cap * 2;
            (yyval.param_list).names = realloc((yyval.param_list).names, sizeof(char *) * (yyval.param_list).cap);
            (yyval.param_list).types = realloc((yyval.param_list).types, sizeof(int)    * (yyval.param_list).cap);
        }
        (yyval.param_list).names[(yyval.param_list).count] = strdup((yyvsp[0].s_val));
        (yyval.param_list).types[(yyval.param_list).count] = (yyvsp[-2].type_tag);
        (yyval.param_list).count++;
        free((yyvsp[0].s_val));
    }
#line 1550 "y.tab.c"
    break;

  case 30: /* arg_list: arg_list_ne  */
#line 221 "parser.y"
                  { (yyval.node_list) = (yyvsp[0].node_list); }
#line 1556 "y.tab.c"
    break;

  case 31: /* arg_list: %empty  */
#line 222 "parser.y"
                  { (yyval.node_list).list = NULL; (yyval.node_list).count = 0; (yyval.node_list).cap = 0; }
#line 1562 "y.tab.c"
    break;

  case 32: /* arg_list_ne: expr  */
#line 226 "parser.y"
           {
        (yyval.node_list).list    = malloc(sizeof(ASTNode *) * 4);
        (yyval.node_list).count   = 1;
        (yyval.node_list).cap     = 4;
        (yyval.node_list).list[0] = (yyvsp[0].node);
    }
#line 1573 "y.tab.c"
    break;

  case 33: /* arg_list_ne: arg_list_ne COMMA expr  */
#line 232 "parser.y"
                             {
        (yyval.node_list) = (yyvsp[-2].node_list);
        if ((yyval.node_list).count == (yyval.node_list).cap) {
            (yyval.node_list).cap  = (yyval.node_list).cap * 2;
            (yyval.node_list).list = realloc((yyval.node_list).list, sizeof(ASTNode *) * (yyval.node_list).cap);
        }
        (yyval.node_list).list[(yyval.node_list).count++] = (yyvsp[0].node);
    }
#line 1586 "y.tab.c"
    break;

  case 34: /* expr: INT_LIT  */
#line 244 "parser.y"
                                           { (yyval.node) = ast_literal_int((yyvsp[0].i_val));    }
#line 1592 "y.tab.c"
    break;

  case 35: /* expr: FLOAT_LIT  */
#line 245 "parser.y"
                                           { (yyval.node) = ast_literal_double((yyvsp[0].f_val)); }
#line 1598 "y.tab.c"
    break;

  case 36: /* expr: CHAR_LIT  */
#line 246 "parser.y"
                                           { (yyval.node) = ast_literal_char((yyvsp[0].c_val));   }
#line 1604 "y.tab.c"
    break;

  case 37: /* expr: BOOL_LIT  */
#line 247 "parser.y"
                                           { (yyval.node) = ast_literal_bool((yyvsp[0].b_val));   }
#line 1610 "y.tab.c"
    break;

  case 38: /* expr: IDENTIFIER LPAREN arg_list RPAREN  */
#line 248 "parser.y"
                                           { (yyval.node) = ast_func_call((yyvsp[-3].s_val), (yyvsp[-1].node_list).list, (yyvsp[-1].node_list).count); free((yyvsp[-3].s_val)); }
#line 1616 "y.tab.c"
    break;

  case 39: /* expr: IDENTIFIER  */
#line 249 "parser.y"
                                           { (yyval.node) = ast_identifier((yyvsp[0].s_val)); free((yyvsp[0].s_val)); }
#line 1622 "y.tab.c"
    break;

  case 40: /* expr: expr PLUS expr  */
#line 250 "parser.y"
                                           { (yyval.node) = ast_binary_op(OP_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1628 "y.tab.c"
    break;

  case 41: /* expr: expr MINUS expr  */
#line 251 "parser.y"
                                           { (yyval.node) = ast_binary_op(OP_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1634 "y.tab.c"
    break;

  case 42: /* expr: expr STAR expr  */
#line 252 "parser.y"
                                           { (yyval.node) = ast_binary_op(OP_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1640 "y.tab.c"
    break;

  case 43: /* expr: expr SLASH expr  */
#line 253 "parser.y"
                                           { (yyval.node) = ast_binary_op(OP_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1646 "y.tab.c"
    break;

  case 44: /* expr: LPAREN expr RPAREN  */
#line 254 "parser.y"
                                           { (yyval.node) = (yyvsp[-1].node); }
#line 1652 "y.tab.c"
    break;


#line 1656 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 257 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "[ERROR] %s\n", s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "[ERROR] No se pudo abrir: %s\n", argv[1]);
            return 1;
        }
        yyin = f;
    }

    push_scope();
    interpreter_init();

    int result = yyparse();

    if (result == 0 && g_count > 0) {
        ASTNode *program = ast_program(g_stmts, g_count);
        interpreter_run(program);
        ast_free(program);
    }

    interpreter_destroy();
    pop_scope();

    if (argc > 1) fclose(yyin);
    return result;
}
