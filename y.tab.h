/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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

#line 158 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
