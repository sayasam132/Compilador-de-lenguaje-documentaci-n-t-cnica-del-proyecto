%{
#include "y.tab.h"
#include "symbols.h"
#include <string.h>
#include <stdlib.h>
%}

%option nounput
%option noinput

DIGIT   [0-9]
LETTER  [a-zA-Z_]
ID      {LETTER}({LETTER}|{DIGIT})*
WS      [ \t\r\n]+
INT_NUM {DIGIT}+
FLT_NUM {DIGIT}+"."{DIGIT}+
STRING  \"(\\.|[^"\\])*\"
COMMENT      "--"[^\n]*
COMMENT_BLOCK "---"([^-]|-[^-]|--[^-])*"---"

%%

{WS}            { }
{COMMENT}       { }    /* -- comentario de una linea  */
{COMMENT_BLOCK} { }    /* --- comentario de bloque --- */

"let"       { return LET;     }
"as"        { return AS;      }
"show"      { return SHOW;    }

"num"       { return T_NUM;    }
"dec"       { return T_DEC;    }
"letter"    { return T_LETTER; }
"word"      { return T_WORD;   }
"bool"      { return T_BOOL;   }

"yes"       { yylval.b_val = 1; return BOOL_LIT; }
"no"        { yylval.b_val = 0; return BOOL_LIT; }

"="         { return ASSIGN;  }
";"         { return SEMI;    }
"+"         { return PLUS;    }
"-"         { return MINUS;   }
"*"         { return STAR;    }
"/"         { return SLASH;   }
"("         { return LPAREN;  }
")"         { return RPAREN;  }
"{"         { return LBRACE;  }
"}"         { return RBRACE;  }

{FLT_NUM}   { yylval.f_val = atof(yytext); return FLOAT_LIT; }
{INT_NUM}   { yylval.i_val = atoi(yytext); return INT_LIT;   }

"'"."'"     { yylval.c_val = yytext[1];    return CHAR_LIT;  }

{STRING}    {
    yylval.s_val = strndup(yytext + 1, strlen(yytext) - 2);
    return STRING_LIT;
}

{ID}        {
    SymbolEntry *node = find_entry(yytext);
    if (!node) node = create_entry(yytext);
    yylval.entry = node;
    return IDENTIFIER;
}

%%

int yywrap(void) { return 1; }
