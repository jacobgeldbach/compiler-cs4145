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

#ifndef YY_YY_SRC_PARSER_TAB_H_INCLUDED
# define YY_YY_SRC_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
    ID = 258,                      /* ID  */
    NUMBERCONST = 259,             /* NUMBERCONST  */
    CHARCONST = 260,               /* CHARCONST  */
    STRINGCONST = 261,             /* STRINGCONST  */
    BOOL = 262,                    /* BOOL  */
    INT = 263,                     /* INT  */
    CHAR = 264,                    /* CHAR  */
    TRUE = 265,                    /* TRUE  */
    FALSE = 266,                   /* FALSE  */
    STATIC = 267,                  /* STATIC  */
    IF = 268,                      /* IF  */
    ELSE = 269,                    /* ELSE  */
    THEN = 270,                    /* THEN  */
    RETURN = 271,                  /* RETURN  */
    BREAK = 272,                   /* BREAK  */
    TO = 273,                      /* TO  */
    BY = 274,                      /* BY  */
    DO = 275,                      /* DO  */
    FOR = 276,                     /* FOR  */
    WHILE = 277,                   /* WHILE  */
    ASGN = 278,                    /* ASGN  */
    ADDASS = 279,                  /* ADDASS  */
    SUBASS = 280,                  /* SUBASS  */
    MULASS = 281,                  /* MULASS  */
    DIVASS = 282,                  /* DIVASS  */
    INC = 283,                     /* INC  */
    DEC = 284,                     /* DEC  */
    OR = 285,                      /* OR  */
    AND = 286,                     /* AND  */
    NOT = 287,                     /* NOT  */
    LT = 288,                      /* LT  */
    LEQ = 289,                     /* LEQ  */
    GT = 290,                      /* GT  */
    GEQ = 291,                     /* GEQ  */
    EQ = 292,                      /* EQ  */
    NEQ = 293,                     /* NEQ  */
    PLUS = 294,                    /* PLUS  */
    MINUS = 295,                   /* MINUS  */
    TIMES = 296,                   /* TIMES  */
    DIV = 297,                     /* DIV  */
    MOD = 298,                     /* MOD  */
    TERNARY = 299,                 /* TERNARY  */
    CHSIGN = 300,                  /* CHSIGN  */
    SIZEOF = 301,                  /* SIZEOF  */
    LPAREN = 302,                  /* LPAREN  */
    RPAREN = 303,                  /* RPAREN  */
    LBRACE = 304,                  /* LBRACE  */
    RBRACE = 305,                  /* RBRACE  */
    LBRACKET = 306,                /* LBRACKET  */
    RBRACKET = 307,                /* RBRACKET  */
    COMMA = 308,                   /* COMMA  */
    COLON = 309,                   /* COLON  */
    SEMI = 310                     /* SEMI  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 40 "src/parser.y"

    ExpType type;
    token_data_t *token_data;
    TreeNode *tree_node;
    OpKind op;

#line 126 "src/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_TAB_H_INCLUDED  */
