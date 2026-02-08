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
#line 1 "./parser.y"

/*
 * CS-4145 Section 71
 * Assignment 2: C- recognizer + AST builder
 * File: parsey.y - Bison parser file
 * Author: Jacob A. Geldbach
 * Date: 09/16/2025
 */
#include "scanType.h"  /* token_data_t */
#include <stdio.h>
#include <cstring>
#include "globals.h"
#include "util.h"
#include "symbolTable.h"
#include "semantic.h"

#include "ourgetopt.h"  /* ourgetopt() */

extern int yylex();
extern FILE *yyin;
extern int line_num;		/* Error line number from the scanner */
int func_decl_saved_line_num;
char *saved_name;


ExpType saved_exp_type;
extern int num_errors;    	    /* Error count */
extern int num_warnings;    	/* warning count */
TreeNode *syntaxTree;

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    printf("ERROR(%d): %s\n", line_num, msg);
    num_errors++;
}


#line 110 "./parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_NUMBERCONST = 4,                /* NUMBERCONST  */
  YYSYMBOL_CHARCONST = 5,                  /* CHARCONST  */
  YYSYMBOL_STRINGCONST = 6,                /* STRINGCONST  */
  YYSYMBOL_BOOL = 7,                       /* BOOL  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_CHAR = 9,                       /* CHAR  */
  YYSYMBOL_TRUE = 10,                      /* TRUE  */
  YYSYMBOL_FALSE = 11,                     /* FALSE  */
  YYSYMBOL_STATIC = 12,                    /* STATIC  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_THEN = 15,                      /* THEN  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_BREAK = 17,                     /* BREAK  */
  YYSYMBOL_TO = 18,                        /* TO  */
  YYSYMBOL_BY = 19,                        /* BY  */
  YYSYMBOL_DO = 20,                        /* DO  */
  YYSYMBOL_FOR = 21,                       /* FOR  */
  YYSYMBOL_WHILE = 22,                     /* WHILE  */
  YYSYMBOL_ASGN = 23,                      /* ASGN  */
  YYSYMBOL_ADDASS = 24,                    /* ADDASS  */
  YYSYMBOL_SUBASS = 25,                    /* SUBASS  */
  YYSYMBOL_MULASS = 26,                    /* MULASS  */
  YYSYMBOL_DIVASS = 27,                    /* DIVASS  */
  YYSYMBOL_INC = 28,                       /* INC  */
  YYSYMBOL_DEC = 29,                       /* DEC  */
  YYSYMBOL_OR = 30,                        /* OR  */
  YYSYMBOL_AND = 31,                       /* AND  */
  YYSYMBOL_NOT = 32,                       /* NOT  */
  YYSYMBOL_LT = 33,                        /* LT  */
  YYSYMBOL_LEQ = 34,                       /* LEQ  */
  YYSYMBOL_GT = 35,                        /* GT  */
  YYSYMBOL_GEQ = 36,                       /* GEQ  */
  YYSYMBOL_EQ = 37,                        /* EQ  */
  YYSYMBOL_NEQ = 38,                       /* NEQ  */
  YYSYMBOL_PLUS = 39,                      /* PLUS  */
  YYSYMBOL_MINUS = 40,                     /* MINUS  */
  YYSYMBOL_TIMES = 41,                     /* TIMES  */
  YYSYMBOL_DIV = 42,                       /* DIV  */
  YYSYMBOL_MOD = 43,                       /* MOD  */
  YYSYMBOL_TERNARY = 44,                   /* TERNARY  */
  YYSYMBOL_CHSIGN = 45,                    /* CHSIGN  */
  YYSYMBOL_SIZEOF = 46,                    /* SIZEOF  */
  YYSYMBOL_LPAREN = 47,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 48,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 49,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 50,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 51,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 52,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 53,                     /* COMMA  */
  YYSYMBOL_COLON = 54,                     /* COLON  */
  YYSYMBOL_SEMI = 55,                      /* SEMI  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_program = 57,                   /* program  */
  YYSYMBOL_decl_list = 58,                 /* decl_list  */
  YYSYMBOL_decl = 59,                      /* decl  */
  YYSYMBOL_var_decl = 60,                  /* var_decl  */
  YYSYMBOL_scoped_var_decl = 61,           /* scoped_var_decl  */
  YYSYMBOL_var_decl_list = 62,             /* var_decl_list  */
  YYSYMBOL_var_decl_init = 63,             /* var_decl_init  */
  YYSYMBOL_var_decl_id = 64,               /* var_decl_id  */
  YYSYMBOL_type_spec = 65,                 /* type_spec  */
  YYSYMBOL_func_decl = 66,                 /* func_decl  */
  YYSYMBOL_params = 67,                    /* params  */
  YYSYMBOL_param_list = 68,                /* param_list  */
  YYSYMBOL_param_type_list = 69,           /* param_type_list  */
  YYSYMBOL_param_id_list = 70,             /* param_id_list  */
  YYSYMBOL_param_id = 71,                  /* param_id  */
  YYSYMBOL_stmt = 72,                      /* stmt  */
  YYSYMBOL_matched_stmt = 73,              /* matched_stmt  */
  YYSYMBOL_unmatched_stmt = 74,            /* unmatched_stmt  */
  YYSYMBOL_matched_select_stmt = 75,       /* matched_select_stmt  */
  YYSYMBOL_unmatched_select_stmt = 76,     /* unmatched_select_stmt  */
  YYSYMBOL_exp_stmt = 77,                  /* exp_stmt  */
  YYSYMBOL_compound_stmt = 78,             /* compound_stmt  */
  YYSYMBOL_local_decls = 79,               /* local_decls  */
  YYSYMBOL_stmt_list = 80,                 /* stmt_list  */
  YYSYMBOL_matched_iter_stmt = 81,         /* matched_iter_stmt  */
  YYSYMBOL_unmatched_iter_stmt = 82,       /* unmatched_iter_stmt  */
  YYSYMBOL_iter_range = 83,                /* iter_range  */
  YYSYMBOL_return_stmt = 84,               /* return_stmt  */
  YYSYMBOL_break_stmt = 85,                /* break_stmt  */
  YYSYMBOL_exp = 86,                       /* exp  */
  YYSYMBOL_assign_op = 87,                 /* assign_op  */
  YYSYMBOL_simple_exp = 88,                /* simple_exp  */
  YYSYMBOL_and_exp = 89,                   /* and_exp  */
  YYSYMBOL_unary_rel_exp = 90,             /* unary_rel_exp  */
  YYSYMBOL_rel_exp = 91,                   /* rel_exp  */
  YYSYMBOL_rel_op = 92,                    /* rel_op  */
  YYSYMBOL_sum_exp = 93,                   /* sum_exp  */
  YYSYMBOL_sum_op = 94,                    /* sum_op  */
  YYSYMBOL_mul_exp = 95,                   /* mul_exp  */
  YYSYMBOL_mul_op = 96,                    /* mul_op  */
  YYSYMBOL_unary_exp = 97,                 /* unary_exp  */
  YYSYMBOL_unary_op = 98,                  /* unary_op  */
  YYSYMBOL_factor = 99,                    /* factor  */
  YYSYMBOL_mutable = 100,                  /* mutable  */
  YYSYMBOL_immutable = 101,                /* immutable  */
  YYSYMBOL_call = 102,                     /* call  */
  YYSYMBOL_args = 103,                     /* args  */
  YYSYMBOL_arg_list = 104,                 /* arg_list  */
  YYSYMBOL_constant = 105                  /* constant  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   222

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  172

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   310


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    64,    64,    67,    79,    82,    83,    86,    96,   105,
     115,   127,   130,   135,   138,   144,   153,   154,   155,   158,
     169,   181,   182,   185,   197,   200,   210,   222,   225,   232,
     241,   242,   245,   246,   247,   248,   249,   250,   253,   254,
     257,   267,   274,   284,   285,   290,   299,   311,   314,   326,
     330,   337,   351,   358,   372,   378,   387,   391,   398,   404,
     412,   419,   426,   429,   430,   431,   432,   433,   436,   444,
     447,   455,   458,   465,   468,   476,   479,   480,   481,   482,
     483,   484,   487,   495,   498,   499,   502,   510,   513,   514,
     515,   518,   525,   528,   529,   530,   533,   534,   537,   548,
     556,   557,   558,   561,   569,   570,   573,   585,   588,   594,
     600,   607,   613
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "NUMBERCONST",
  "CHARCONST", "STRINGCONST", "BOOL", "INT", "CHAR", "TRUE", "FALSE",
  "STATIC", "IF", "ELSE", "THEN", "RETURN", "BREAK", "TO", "BY", "DO",
  "FOR", "WHILE", "ASGN", "ADDASS", "SUBASS", "MULASS", "DIVASS", "INC",
  "DEC", "OR", "AND", "NOT", "LT", "LEQ", "GT", "GEQ", "EQ", "NEQ", "PLUS",
  "MINUS", "TIMES", "DIV", "MOD", "TERNARY", "CHSIGN", "SIZEOF", "LPAREN",
  "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "COMMA", "COLON",
  "SEMI", "$accept", "program", "decl_list", "decl", "var_decl",
  "scoped_var_decl", "var_decl_list", "var_decl_init", "var_decl_id",
  "type_spec", "func_decl", "params", "param_list", "param_type_list",
  "param_id_list", "param_id", "stmt", "matched_stmt", "unmatched_stmt",
  "matched_select_stmt", "unmatched_select_stmt", "exp_stmt",
  "compound_stmt", "local_decls", "stmt_list", "matched_iter_stmt",
  "unmatched_iter_stmt", "iter_range", "return_stmt", "break_stmt", "exp",
  "assign_op", "simple_exp", "and_exp", "unary_rel_exp", "rel_exp",
  "rel_op", "sum_exp", "sum_op", "mul_exp", "mul_op", "unary_exp",
  "unary_op", "factor", "mutable", "immutable", "call", "args", "arg_list",
  "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-109)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      94,   -34,  -109,  -109,  -109,    14,    94,  -109,  -109,    18,
    -109,    51,  -109,  -109,   -35,    28,  -109,    -5,    47,     5,
       7,  -109,    51,    39,    63,  -109,   167,    22,    16,  -109,
      37,    51,    29,    56,    41,  -109,   -14,  -109,  -109,  -109,
    -109,  -109,   167,  -109,  -109,  -109,   167,    85,    88,  -109,
    -109,   182,    70,  -109,    24,  -109,  -109,  -109,  -109,  -109,
      64,    47,  -109,  -109,  -109,    37,  -109,   167,   167,  -109,
      72,    85,   168,   167,   167,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,    24,    24,  -109,  -109,  -109,    24,  -109,
    -109,  -109,    97,  -109,  -109,    73,    74,    79,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,   167,    88,  -109,    -8,
      70,  -109,    51,  -109,    63,    35,  -109,   167,  -109,  -109,
      63,    34,   167,   143,    71,   130,   167,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
      82,  -109,    40,  -109,   -10,  -109,    84,  -109,   111,   -11,
    -109,  -109,   119,  -109,   167,   119,  -109,   128,   123,   -12,
    -109,  -109,   119,   119,   167,  -109,  -109,  -109,  -109,    -4,
     167,    85
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    16,    18,    17,     0,     2,     4,     5,     0,
       6,    22,     1,     3,    14,     0,    11,    13,     0,     0,
      21,    24,    22,     0,     0,     7,     0,    29,    25,    27,
       0,     0,     0,     0,    14,    10,    99,   108,   109,   110,
     111,   112,     0,    93,    94,    95,     0,    12,    69,    71,
      73,    75,    83,    87,     0,    92,    96,    97,   101,   102,
       0,     0,    47,    20,    23,     0,    15,   105,     0,    72,
       0,    62,    96,     0,     0,    76,    77,    78,    79,    80,
      81,    84,    85,     0,     0,    88,    89,    90,     0,    91,
      28,    26,    49,    19,   107,     0,   104,     0,   100,    63,
      64,    65,    66,    67,    60,    61,     0,    68,    70,    74,
      82,    86,     0,    46,     0,     0,   103,     0,    98,    59,
       0,     0,     0,     0,     0,     0,     0,    45,    44,    48,
      30,    31,    33,    39,    35,    34,    32,    38,    36,    37,
       0,   106,     0,     9,     0,    56,     0,    58,     0,     0,
      43,     8,     0,    57,     0,     0,    41,    30,     0,     0,
      50,    52,     0,     0,     0,    40,    42,    51,    53,    54,
       0,    55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -109,  -109,  -109,   139,  -109,  -109,  -103,   126,  -109,     2,
    -109,   133,  -109,   121,  -109,    95,     6,   -64,  -108,  -109,
    -109,  -109,   -23,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
     -43,  -109,   -26,    89,   -38,  -109,  -109,    78,  -109,    80,
    -109,   -44,  -109,  -109,   -45,  -109,  -109,  -109,  -109,  -109
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,   113,    15,    16,    17,    18,
      10,    19,    20,    21,    28,    29,   129,   130,   131,   132,
     133,   134,   135,    92,   115,   136,   137,   158,   138,   139,
     140,   106,    71,    48,    49,    50,    83,    51,    84,    52,
      88,    53,    54,    55,    56,    57,    58,    95,    96,    59
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      47,    72,     9,    70,    69,   152,   164,    63,     9,   155,
      89,   121,    22,    11,    12,   170,    23,   142,    73,    73,
      73,    14,    72,    72,    94,    97,    73,    36,    37,    38,
      39,    81,    82,    67,    40,    41,   108,    68,    36,    37,
      38,    39,    93,    33,   111,    40,    41,   161,   122,    26,
      27,   123,   124,    30,   166,   168,   125,   126,     2,     3,
       4,    72,    31,   119,    43,    44,    34,    42,    45,    61,
      72,    46,    72,    60,   141,    43,    44,    65,    72,    45,
     146,    24,    46,    25,    62,   127,    62,    24,   157,   143,
     128,   160,    23,    24,   114,   151,   144,     1,   165,   167,
     149,     2,     3,     4,     2,     3,     4,    72,    66,   112,
      72,    85,    86,    87,   120,    73,    90,    72,    72,    74,
      98,   116,    36,    37,    38,    39,   147,   117,   159,    40,
      41,   118,   122,   148,   154,   123,   124,   150,   169,   153,
     125,   126,   162,   163,   171,    13,    36,    37,    38,    39,
      35,    42,    64,    40,    41,    32,    91,     0,   156,    43,
      44,   109,   107,    45,   110,     0,    46,     0,    62,     0,
      36,    37,    38,    39,   128,    42,     0,    40,    41,     0,
       0,     0,     0,    43,    44,     0,     0,    45,     0,     0,
      46,    99,   100,   101,   102,   103,   104,   105,   145,    42,
       0,     0,     0,     0,     0,     0,     0,    43,    44,     0,
       0,    45,     0,     0,    46,    75,    76,    77,    78,    79,
      80,    81,    82
};

static const yytype_int16 yycheck[] =
{
      26,    46,     0,    46,    42,    15,    18,    30,     6,    20,
      54,   114,    47,    47,     0,    19,    51,   120,    30,    30,
      30,     3,    67,    68,    67,    68,    30,     3,     4,     5,
       6,    39,    40,    47,    10,    11,    74,    51,     3,     4,
       5,     6,    65,     4,    88,    10,    11,   155,    13,    54,
       3,    16,    17,    48,   162,   163,    21,    22,     7,     8,
       9,   106,    55,   106,    40,    41,     3,    32,    44,    53,
     115,    47,   117,    51,   117,    40,    41,    48,   123,    44,
     123,    53,    47,    55,    49,    50,    49,    53,   152,    55,
      55,   155,    51,    53,    92,    55,   122,     3,   162,   163,
     126,     7,     8,     9,     7,     8,     9,   152,    52,    12,
     155,    41,    42,    43,   112,    30,    52,   162,   163,    31,
      48,    48,     3,     4,     5,     6,    55,    53,   154,    10,
      11,    52,    13,     3,    23,    16,    17,    55,   164,    55,
      21,    22,    14,    20,   170,     6,     3,     4,     5,     6,
      24,    32,    31,    10,    11,    22,    61,    -1,   152,    40,
      41,    83,    73,    44,    84,    -1,    47,    -1,    49,    -1,
       3,     4,     5,     6,    55,    32,    -1,    10,    11,    -1,
      -1,    -1,    -1,    40,    41,    -1,    -1,    44,    -1,    -1,
      47,    23,    24,    25,    26,    27,    28,    29,    55,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    -1,
      -1,    44,    -1,    -1,    47,    33,    34,    35,    36,    37,
      38,    39,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     7,     8,     9,    57,    58,    59,    60,    65,
      66,    47,     0,    59,     3,    62,    63,    64,    65,    67,
      68,    69,    47,    51,    53,    55,    54,     3,    70,    71,
      48,    55,    67,     4,     3,    63,     3,     4,     5,     6,
      10,    11,    32,    40,    41,    44,    47,    88,    89,    90,
      91,    93,    95,    97,    98,    99,   100,   101,   102,   105,
      51,    53,    49,    78,    69,    48,    52,    47,    51,    90,
      86,    88,   100,    30,    31,    33,    34,    35,    36,    37,
      38,    39,    40,    92,    94,    41,    42,    43,    96,    97,
      52,    71,    79,    78,    86,   103,   104,    86,    48,    23,
      24,    25,    26,    27,    28,    29,    87,    89,    90,    93,
      95,    97,    12,    61,    65,    80,    48,    53,    52,    86,
      65,    62,    13,    16,    17,    21,    22,    50,    55,    72,
      73,    74,    75,    76,    77,    78,    81,    82,    84,    85,
      86,    86,    62,    55,    88,    55,    86,    55,     3,    88,
      55,    55,    15,    55,    23,    20,    72,    73,    83,    88,
      73,    74,    14,    20,    18,    73,    74,    73,    74,    88,
      19,    88
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    60,    61,    61,
      62,    62,    63,    63,    64,    64,    65,    65,    65,    66,
      66,    67,    67,    68,    68,    69,    70,    70,    71,    71,
      72,    72,    73,    73,    73,    73,    73,    73,    74,    74,
      75,    76,    76,    77,    77,    78,    79,    79,    80,    80,
      81,    81,    82,    82,    83,    83,    84,    84,    85,    86,
      86,    86,    86,    87,    87,    87,    87,    87,    88,    88,
      89,    89,    90,    90,    91,    91,    92,    92,    92,    92,
      92,    92,    93,    93,    94,    94,    95,    95,    96,    96,
      96,    97,    97,    98,    98,    98,    99,    99,   100,   100,
     101,   101,   101,   102,   103,   103,   104,   104,   105,   105,
     105,   105,   105
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     4,     3,
       3,     1,     3,     1,     1,     4,     1,     1,     1,     6,
       5,     1,     0,     3,     1,     2,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       6,     4,     6,     2,     1,     4,     2,     0,     2,     0,
       4,     6,     4,     6,     3,     5,     2,     3,     2,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     4,     1,
       3,     1,     1,     4,     1,     0,     3,     1,     1,     1,
       1,     1,     1
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
  case 2: /* program: decl_list  */
#line 64 "./parser.y"
                        { syntaxTree = (yyvsp[0].tree_node); }
#line 1346 "./parser.tab.c"
    break;

  case 3: /* decl_list: decl_list decl  */
#line 67 "./parser.y"
                             {
                TreeNode * t = (yyvsp[-1].tree_node);
                if (t != NULL) {
                    while (t->sibling != NULL) {    /* decl_list, so iterate to the tail of the list */
                        t = t->sibling;             
                    }
                    t->sibling = (yyvsp[0].tree_node);                /* append new decl to the end of the list */
                    (yyval.tree_node) = (yyvsp[-1].tree_node);                        /* assign the starting tree_node *, front of the list, to left-hand side */
                } else {
                    (yyval.tree_node) = (yyvsp[0].tree_node);                        /* if first decl, assign to left-hand side */
                }
            }
#line 1363 "./parser.tab.c"
    break;

  case 4: /* decl_list: decl  */
#line 79 "./parser.y"
                       { (yyval.tree_node) = (yyvsp[0].tree_node);                       /* first decl, assign to left-hand side */ }
#line 1369 "./parser.tab.c"
    break;

  case 5: /* decl: var_decl  */
#line 82 "./parser.y"
                       { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1375 "./parser.tab.c"
    break;

  case 6: /* decl: func_decl  */
#line 83 "./parser.y"
                            { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1381 "./parser.tab.c"
    break;

  case 7: /* var_decl: type_spec var_decl_list SEMI  */
#line 86 "./parser.y"
                                           {
                TreeNode * t = (yyvsp[-1].tree_node);
                while (t != NULL) {               /* var_decl_list, so iterate through the list */
                    t->type = (yyvsp[-2].type);                 /* set type_spec terminal type for each var_decl */
                    t = t->sibling;               /* move to next var_decl in the list */
                }
                (yyval.tree_node) = (yyvsp[-1].tree_node);                         /* assign the starting tree_node *, front of the list, to left-hand side */
            }
#line 1394 "./parser.tab.c"
    break;

  case 8: /* scoped_var_decl: STATIC type_spec var_decl_list SEMI  */
#line 96 "./parser.y"
                                                          {
                        TreeNode * t = (yyvsp[-1].tree_node);
                        while (t != NULL) {                 /* var_decl_list, so iterate through the list */
                            t->type = (yyvsp[-2].type);                   /* set type_spec terminal type for each var_decl */
                            t->isStatic = true;             /* mark as static */
                            t = t->sibling;                 /* move to next var_decl in the list */
                        }
                        (yyval.tree_node) = (yyvsp[-1].tree_node);                          /* assign the starting tree_node *, front of the list, to left-hand side */
                    }
#line 1408 "./parser.tab.c"
    break;

  case 9: /* scoped_var_decl: type_spec var_decl_list SEMI  */
#line 105 "./parser.y"
                                                           {
                        TreeNode * t = (yyvsp[-1].tree_node);
                        while (t != NULL) {                 /* var_decl_list, so iterate through the list */
                            t->type = (yyvsp[-2].type);                   /* set type_spec terminal type for each var_decl */
                            t = t->sibling;                 /* move to next var_decl in the list */
                        }
                        (yyval.tree_node) = (yyvsp[-1].tree_node);                          /* assign the starting tree_node *, front of the list, to left-hand side */
                    }
#line 1421 "./parser.tab.c"
    break;

  case 10: /* var_decl_list: var_decl_list COMMA var_decl_init  */
#line 115 "./parser.y"
                                                        {
                        TreeNode * t = (yyvsp[-2].tree_node);
                        if (t != NULL) {
                            while (t->sibling != NULL) {        /* var_decl_list, so iterate to the tail of the list */
                                t = t->sibling;
                            }
                            t->sibling = (yyvsp[0].tree_node);                    /* append new var_decl_init to the end of the list */   
                            (yyval.tree_node) = (yyvsp[-2].tree_node);                            /* assign the starting tree_node *, front of the list, to left-hand side */
                        } else {
                            (yyval.tree_node) = (yyvsp[0].tree_node);                            /* if first var_decl_init, assign to left-hand side */
                        }
                    }
#line 1438 "./parser.tab.c"
    break;

  case 11: /* var_decl_list: var_decl_init  */
#line 127 "./parser.y"
                                        { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1444 "./parser.tab.c"
    break;

  case 12: /* var_decl_init: var_decl_id COLON simple_exp  */
#line 130 "./parser.y"
                                                   { 
                        TreeNode * t = (yyvsp[-2].tree_node);
                        t->child[0] = (yyvsp[0].tree_node);   /* simple_exp */
                        (yyval.tree_node) = t;             /* assign new TreeNode* to left-hand side */
                    }
#line 1454 "./parser.tab.c"
    break;

  case 13: /* var_decl_init: var_decl_id  */
#line 135 "./parser.y"
                                      { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1460 "./parser.tab.c"
    break;

  case 14: /* var_decl_id: ID  */
#line 138 "./parser.y"
                         {
                        TreeNode * t = newDeclNode(VarK);
                        t->attr.name = (yyvsp[0].token_data)->svalue;  /* ID name comes from token_data_t svalue member */
                        t->lineno = (yyvsp[0].token_data)->line_num;  /* set variable declaration line number to that of when the ID was scanned */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 1471 "./parser.tab.c"
    break;

  case 15: /* var_decl_id: ID LBRACKET NUMBERCONST RBRACKET  */
#line 144 "./parser.y"
                                                           {
                        TreeNode * t = newDeclNode(VarK);
                        t->attr.name = (yyvsp[-3].token_data)->svalue;          /* ID name comes from token_data_t svalue member */
                        t->isArray = true;                  /* mark as array variable */
                        t->lineno = (yyvsp[-3].token_data)->line_num;           /* set variable declaration line number to that of when the ID was scanned */
                        (yyval.tree_node) = t;                             /* assign new TreeNode to left-hand side */
                    }
#line 1483 "./parser.tab.c"
    break;

  case 16: /* type_spec: BOOL  */
#line 153 "./parser.y"
                           { (yyval.type) = Boolean; }
#line 1489 "./parser.tab.c"
    break;

  case 17: /* type_spec: CHAR  */
#line 154 "./parser.y"
                               { (yyval.type) = Char; }
#line 1495 "./parser.tab.c"
    break;

  case 18: /* type_spec: INT  */
#line 155 "./parser.y"
                               { (yyval.type) = Integer; }
#line 1501 "./parser.tab.c"
    break;

  case 19: /* func_decl: type_spec ID LPAREN params RPAREN compound_stmt  */
#line 158 "./parser.y"
                                                                      {
                        TreeNode * t = newDeclNode(FuncK);
                        t->type = (yyvsp[-5].type);                               /* type_spec terminal type */
                        t->attr.name = strdup((yyvsp[-4].token_data)->svalue);          /* ID name comes from token_data_t svalue member */
                        t->lineno = (yyvsp[-4].token_data)->line_num;                   /* set function declaration line number to that of when the function name was scanned */
                        t->child[0] = (yyvsp[-2].tree_node);                           /* params */
                        t->child[1] = (yyvsp[0].tree_node);                           /* compound_stmt */
                        t->child[1]->param_sibling = t->child[0];   /* set param_sibling of compound_stmt to params for scoping purposes during semantic analysis */

                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 1517 "./parser.tab.c"
    break;

  case 20: /* func_decl: ID LPAREN params RPAREN compound_stmt  */
#line 169 "./parser.y"
                                                                {
                        TreeNode * t = newDeclNode(FuncK);
                        t->type = Void;                     /* default to Void type if no type_spec */
                        t->attr.name = strdup((yyvsp[-4].token_data)->svalue);  /* ID name comes from token_data_t svalue member */
                        t->lineno = (yyvsp[-4].token_data)->line_num;           /* set function declaration line number to that of when the function name was scanned */
                        t->child[0] = (yyvsp[-2].tree_node);           /* params */
                        t->child[1] = (yyvsp[0].tree_node);           /* compound_stmt */
                        t->child[1]->param_sibling = t->child[0];   /* set param_sibling of compound_stmt to params for scoping purposes during semantic analysis */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 1532 "./parser.tab.c"
    break;

  case 21: /* params: param_list  */
#line 181 "./parser.y"
                                 { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1538 "./parser.tab.c"
    break;

  case 22: /* params: %empty  */
#line 182 "./parser.y"
                          { (yyval.tree_node) = NULL; }
#line 1544 "./parser.tab.c"
    break;

  case 23: /* param_list: param_list SEMI param_type_list  */
#line 185 "./parser.y"
                                                      {
                        TreeNode * t = (yyvsp[-2].tree_node);
                        if (t != NULL) {
                            while (t->sibling != NULL) {    /* param_list, so iterate to the tail of the list */
                                t = t->sibling;
                            }
                            t->sibling = (yyvsp[0].tree_node);                /* append new param_type_list to the end of the list */ 
                            (yyval.tree_node) = (yyvsp[-2].tree_node);                        /* assign the starting tree_node *, front of the list, to left-hand side */
                        } else {
                            (yyval.tree_node) = (yyvsp[0].tree_node);                        /* if first param_type_list, assign to left-hand side */
                        }
                    }
#line 1561 "./parser.tab.c"
    break;

  case 24: /* param_list: param_type_list  */
#line 197 "./parser.y"
                                      { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1567 "./parser.tab.c"
    break;

  case 25: /* param_type_list: type_spec param_id_list  */
#line 200 "./parser.y"
                                              {
                        TreeNode * t = (yyvsp[0].tree_node);
                        while (t != NULL) {               /* param_id_list, so iterate through the list */
                            t->type = (yyvsp[-1].type);                 /* set type_spec terminal type for each param_id */
                            t = t->sibling;               /* move to next param_id in the list */
                        }
                        (yyval.tree_node) = (yyvsp[0].tree_node);                         /* assign the starting tree_node *, front of the list, to left-hand side */
                    }
#line 1580 "./parser.tab.c"
    break;

  case 26: /* param_id_list: param_id_list COMMA param_id  */
#line 210 "./parser.y"
                                                   {
                        TreeNode * t = (yyvsp[-2].tree_node);
                        if (t != NULL) {
                            while (t->sibling != NULL) {    /* param_id_list, so iterate to the tail of the list */
                                t = t->sibling;
                            }
                            t->sibling = (yyvsp[0].tree_node);                /* append new param_id to the end of the list */
                            (yyval.tree_node) = (yyvsp[-2].tree_node);                        /* assign the starting tree_node *, front of the list, to left-hand side */
                        } else {
                            (yyval.tree_node) = (yyvsp[0].tree_node);                        /* if first param_id, assign to left-hand side */
                        }
                    }
#line 1597 "./parser.tab.c"
    break;

  case 27: /* param_id_list: param_id  */
#line 222 "./parser.y"
                               { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1603 "./parser.tab.c"
    break;

  case 28: /* param_id: ID LBRACKET RBRACKET  */
#line 225 "./parser.y"
                                           {
                        TreeNode * t = newDeclNode(ParamK);
                        t->attr.name = (yyvsp[-2].token_data)->svalue;  /* ID name comes from token_data_t svalue member */
                        t->isArray = true;          /* mark as array parameter */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 1615 "./parser.tab.c"
    break;

  case 29: /* param_id: ID  */
#line 232 "./parser.y"
                         {
                        TreeNode * t = newDeclNode(ParamK);
                        t->attr.name = (yyvsp[0].token_data)->svalue;  /* ID name comes from token_data_t svalue member */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->isInitialized = true;    /* parameters are considered initialized */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 1627 "./parser.tab.c"
    break;

  case 30: /* stmt: matched_stmt  */
#line 241 "./parser.y"
                                   { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1633 "./parser.tab.c"
    break;

  case 31: /* stmt: unmatched_stmt  */
#line 242 "./parser.y"
                                     { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1639 "./parser.tab.c"
    break;

  case 32: /* matched_stmt: matched_iter_stmt  */
#line 245 "./parser.y"
                                        { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1645 "./parser.tab.c"
    break;

  case 33: /* matched_stmt: matched_select_stmt  */
#line 246 "./parser.y"
                                          { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1651 "./parser.tab.c"
    break;

  case 34: /* matched_stmt: compound_stmt  */
#line 247 "./parser.y"
                                    { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1657 "./parser.tab.c"
    break;

  case 35: /* matched_stmt: exp_stmt  */
#line 248 "./parser.y"
                               { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1663 "./parser.tab.c"
    break;

  case 36: /* matched_stmt: return_stmt  */
#line 249 "./parser.y"
                                  { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1669 "./parser.tab.c"
    break;

  case 37: /* matched_stmt: break_stmt  */
#line 250 "./parser.y"
                                 { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1675 "./parser.tab.c"
    break;

  case 38: /* unmatched_stmt: unmatched_iter_stmt  */
#line 253 "./parser.y"
                                          { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1681 "./parser.tab.c"
    break;

  case 39: /* unmatched_stmt: unmatched_select_stmt  */
#line 254 "./parser.y"
                                            { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1687 "./parser.tab.c"
    break;

  case 40: /* matched_select_stmt: IF simple_exp THEN matched_stmt ELSE matched_stmt  */
#line 257 "./parser.y"
                                                                        {
                        TreeNode * t = newStmtNode(IfK);
                        t->child[0] = (yyvsp[-4].tree_node);   /* simple_exp */
                        t->child[1] = (yyvsp[-2].tree_node);   /* matched_stmt for THEN */
                        t->child[2] = (yyvsp[0].tree_node);   /* matched_stmt for ELSE */
                        t->lineno = (yyvsp[-4].tree_node)->lineno;  /* set if statement line number to that of when the simple_exp was scanned */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 1700 "./parser.tab.c"
    break;

  case 41: /* unmatched_select_stmt: IF simple_exp THEN stmt  */
#line 267 "./parser.y"
                                                  {
                            TreeNode * t = newStmtNode(IfK);
                            t->child[0] = (yyvsp[-2].tree_node);   /* simple_exp */
                            t->child[1] = (yyvsp[0].tree_node);   /* matched_stmt for THEN */
                            t->lineno = (yyvsp[-2].tree_node)->lineno;  /* set if statement line number to that of when the simple_exp was scanned */
                            (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                        }
#line 1712 "./parser.tab.c"
    break;

  case 42: /* unmatched_select_stmt: IF simple_exp THEN matched_stmt ELSE unmatched_stmt  */
#line 274 "./parser.y"
                                                                              {
                            TreeNode * t = newStmtNode(IfK);
                            t->child[0] = (yyvsp[-4].tree_node);   /* simple_exp */
                            t->child[1] = (yyvsp[-2].tree_node);   /* matched_stmt for THEN */
                            t->child[2] = (yyvsp[0].tree_node);   /* unmatched_stmt for ELSE */
                            t->lineno = (yyvsp[-4].tree_node)->lineno;  /* set if statement line number to that of when the simple_exp was scanned */
                            (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                        }
#line 1725 "./parser.tab.c"
    break;

  case 43: /* exp_stmt: exp SEMI  */
#line 284 "./parser.y"
                               { (yyval.tree_node) = (yyvsp[-1].tree_node); }
#line 1731 "./parser.tab.c"
    break;

  case 44: /* exp_stmt: SEMI  */
#line 285 "./parser.y"
                           { 
                        (yyval.tree_node) = NULL;             /* empty exp_stmt represented by ExpK node with no children */
                    }
#line 1739 "./parser.tab.c"
    break;

  case 45: /* compound_stmt: LBRACE local_decls stmt_list RBRACE  */
#line 290 "./parser.y"
                                                          {
                        TreeNode * t = newStmtNode(CompoundK);
                        t->lineno = (yyvsp[-3].token_data)->line_num;   /* set compound statement line number to that of when the '{' was scanned */
                        t->child[0] = (yyvsp[-2].tree_node);           /* local_decls */
                        t->child[1] = (yyvsp[-1].tree_node);           /* stmt_list */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 1751 "./parser.tab.c"
    break;

  case 46: /* local_decls: local_decls scoped_var_decl  */
#line 299 "./parser.y"
                                                  { 
                        TreeNode * t = (yyvsp[-1].tree_node);
                        if (t != NULL) {
                            while (t->sibling != NULL) {    /* local_decls, so iterate to the tail of the list */
                                t = t->sibling;
                            }
                            t->sibling = (yyvsp[0].tree_node);                /* append new scoped_var_decl to the end of the list */
                            (yyval.tree_node) = (yyvsp[-1].tree_node);                        /* assign the starting tree_node *, front of the list, to left-hand side */
                        } else {
                            (yyval.tree_node) = (yyvsp[0].tree_node);                        /* if first scoped_var_decl, assign to left-hand side */    
                        }
                    }
#line 1768 "./parser.tab.c"
    break;

  case 47: /* local_decls: %empty  */
#line 311 "./parser.y"
                      {(yyval.tree_node) = NULL; }
#line 1774 "./parser.tab.c"
    break;

  case 48: /* stmt_list: stmt_list stmt  */
#line 314 "./parser.y"
                                     {
                        TreeNode * t = (yyvsp[-1].tree_node);
                        if (t != NULL) {
                            while (t->sibling != NULL) {    /* stmt_list, so iterate to the tail of the list */
                                t = t->sibling;
                            }
                            t->sibling = (yyvsp[0].tree_node);                /* append new stmt to the end of the list */
                            (yyval.tree_node) = (yyvsp[-1].tree_node);                        /* assign the starting tree_node *, front of the list, to left-hand side */
                        } else {
                            (yyval.tree_node) = (yyvsp[0].tree_node);                        /* if first stmt, assign to left-hand side */
                        }
                    }
#line 1791 "./parser.tab.c"
    break;

  case 49: /* stmt_list: %empty  */
#line 326 "./parser.y"
                      { (yyval.tree_node) = NULL; }
#line 1797 "./parser.tab.c"
    break;

  case 50: /* matched_iter_stmt: WHILE simple_exp DO matched_stmt  */
#line 330 "./parser.y"
                                                       {
                        TreeNode * t = newStmtNode(WhileK);
                        t->child[0] = (yyvsp[-2].tree_node);   /* simple_exp */
                        t->child[1] = (yyvsp[0].tree_node);   /* matched_stmt */
                        t->lineno = (yyvsp[-2].tree_node)->lineno;  /* set while loop line number to that of when the simple_exp was scanned */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 1809 "./parser.tab.c"
    break;

  case 51: /* matched_iter_stmt: FOR ID ASGN iter_range DO matched_stmt  */
#line 337 "./parser.y"
                                                             {
                        TreeNode * t = newStmtNode(ForK);
                        TreeNode * init = newExpNode(InitK);
                        init->attr.name = (yyvsp[-4].token_data)->svalue;    /* ID name comes from token_data_t svalue member */
                        init->type = Integer;
                        t->child[0] = init;              /* loop variable ID and iter_range become siblings */
                        t->child[1] = (yyvsp[-2].tree_node);                /* iter_range */
                        t->child[2] = (yyvsp[0].tree_node);                /* matched_stmt becomes the first child of the iter_range child */
                        t->lineno = (yyvsp[-2].tree_node)->lineno;          /* set for loop line number to that of when the iter_range was scanned */
                        init->lineno = (yyvsp[-2].tree_node)->lineno;          /* set loop variable ID line number to that of when the iter_range was scanned */
                        (yyval.tree_node) = t;                          /* assign new TreeNode to left-hand side */
                    }
#line 1826 "./parser.tab.c"
    break;

  case 52: /* unmatched_iter_stmt: WHILE simple_exp DO unmatched_stmt  */
#line 351 "./parser.y"
                                                         {
                        TreeNode * t = newStmtNode(WhileK);
                        t->child[0] = (yyvsp[-2].tree_node);   /* simple_exp */
                        t->child[1] = (yyvsp[0].tree_node);   /* unmatched_stmt */
                        t->lineno = (yyvsp[-2].tree_node)->lineno;  /* set while loop line number to that of when the simple_exp was scanned */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 1838 "./parser.tab.c"
    break;

  case 53: /* unmatched_iter_stmt: FOR ID ASGN iter_range DO unmatched_stmt  */
#line 358 "./parser.y"
                                                               {
                        TreeNode * t = newStmtNode(ForK);
                        TreeNode * init = newExpNode(InitK);
                        init->attr.name = (yyvsp[-4].token_data)->svalue;  /* ID name comes from token_data_t svalue member */
                        init->type = Integer;
                        t->child[0] = init;            /* loop variable ID and iter_range become siblings */
                        t->child[1] = (yyvsp[-2].tree_node);                /* iter_range */
                        t->child[2] = (yyvsp[0].tree_node);                /* unmatched_stmt */
                        t->lineno = (yyvsp[-2].tree_node)->lineno;          /* set for loop line number to that of when the iter_range was scanned */
                        init->lineno = (yyvsp[-2].tree_node)->lineno;     /* set loop variable ID line number to that of when the iter_range was scanned */
                        (yyval.tree_node) = t;                          /* assign new TreeNode to left-hand side */
                    }
#line 1855 "./parser.tab.c"
    break;

  case 54: /* iter_range: simple_exp TO simple_exp  */
#line 372 "./parser.y"
                                               {
                        TreeNode * t = newStmtNode(RangeK);
                        t->child[0] = (yyvsp[-2].tree_node);   /* start expression */
                        t->child[1] = (yyvsp[0].tree_node);   /* end expression */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 1866 "./parser.tab.c"
    break;

  case 55: /* iter_range: simple_exp TO simple_exp BY simple_exp  */
#line 378 "./parser.y"
                                                             {
                        TreeNode * t = newStmtNode(RangeK);
                        t->child[0] = (yyvsp[-4].tree_node);   /* start expression */
                        t->child[1] = (yyvsp[-2].tree_node);   /* end expression */
                        t->child[2] = (yyvsp[0].tree_node);   /* step expression */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 1878 "./parser.tab.c"
    break;

  case 56: /* return_stmt: RETURN SEMI  */
#line 387 "./parser.y"
                                  {
                        TreeNode * t = newStmtNode(ReturnK);
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 1887 "./parser.tab.c"
    break;

  case 57: /* return_stmt: RETURN exp SEMI  */
#line 391 "./parser.y"
                                      {
                        TreeNode * t = newStmtNode(ReturnK);
                        t->child[0] = (yyvsp[-1].tree_node);   /* exp */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 1897 "./parser.tab.c"
    break;

  case 58: /* break_stmt: BREAK SEMI  */
#line 398 "./parser.y"
                                 {
                        TreeNode * t = newStmtNode(BreakK);
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 1906 "./parser.tab.c"
    break;

  case 59: /* exp: mutable assign_op exp  */
#line 404 "./parser.y"
                                            { 
                        TreeNode * t = newExpNode(AssignK);
                        t->child[0] = (yyvsp[-2].tree_node);   /* mutable */
                        t->child[1] = (yyvsp[0].tree_node);   /* exp */
                        t->attr.op = (yyvsp[-1].op);    /* assignment operator from assign_op */
                        
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 1919 "./parser.tab.c"
    break;

  case 60: /* exp: mutable INC  */
#line 412 "./parser.y"
                                  { 
                        TreeNode * t = newExpNode(AssignK);
                        t->child[0] = (yyvsp[-1].tree_node);   /* mutable */
                        t->attr.op = INC;   /* increment operator */
                        t->type = Integer;  /* set type to Integer for increment operator */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 1931 "./parser.tab.c"
    break;

  case 61: /* exp: mutable DEC  */
#line 419 "./parser.y"
                                  { 
                        TreeNode * t = newExpNode(AssignK);
                        t->child[0] = (yyvsp[-1].tree_node);   /* mutable */
                        t->attr.op = DEC;   /* decrement operator */
                        t->type = Integer;  /* set type to Integer for decrement operator */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 1943 "./parser.tab.c"
    break;

  case 62: /* exp: simple_exp  */
#line 426 "./parser.y"
                                 { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1949 "./parser.tab.c"
    break;

  case 63: /* assign_op: ASGN  */
#line 429 "./parser.y"
                             { (yyval.op) = ASGN; }
#line 1955 "./parser.tab.c"
    break;

  case 64: /* assign_op: ADDASS  */
#line 430 "./parser.y"
                             { (yyval.op) = ADDASS; }
#line 1961 "./parser.tab.c"
    break;

  case 65: /* assign_op: SUBASS  */
#line 431 "./parser.y"
                             { (yyval.op) = SUBASS; }
#line 1967 "./parser.tab.c"
    break;

  case 66: /* assign_op: MULASS  */
#line 432 "./parser.y"
                             { (yyval.op) = MULASS; }
#line 1973 "./parser.tab.c"
    break;

  case 67: /* assign_op: DIVASS  */
#line 433 "./parser.y"
                             { (yyval.op) = DIVASS; }
#line 1979 "./parser.tab.c"
    break;

  case 68: /* simple_exp: simple_exp OR and_exp  */
#line 436 "./parser.y"
                                            {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = OR;        /* OR operator */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->child[0] = (yyvsp[-2].tree_node);       /* left operand */
                        t->child[1] = (yyvsp[0].tree_node);       /* right operand */
                        (yyval.tree_node) = t;
                    }
#line 1992 "./parser.tab.c"
    break;

  case 69: /* simple_exp: and_exp  */
#line 444 "./parser.y"
                              { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1998 "./parser.tab.c"
    break;

  case 70: /* and_exp: and_exp AND unary_rel_exp  */
#line 447 "./parser.y"
                                                {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = AND;       /* AND operator */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->child[0] = (yyvsp[-2].tree_node);       /* left operand */
                        t->child[1] = (yyvsp[0].tree_node);       /* right operand */
                        (yyval.tree_node) = t;
                    }
#line 2011 "./parser.tab.c"
    break;

  case 71: /* and_exp: unary_rel_exp  */
#line 455 "./parser.y"
                                    { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2017 "./parser.tab.c"
    break;

  case 72: /* unary_rel_exp: NOT unary_rel_exp  */
#line 458 "./parser.y"
                                        {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = NOT;   /* NOT operator */
                        t->child[0] = (yyvsp[0].tree_node);   /* operand */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        (yyval.tree_node) = t;
                    }
#line 2029 "./parser.tab.c"
    break;

  case 73: /* unary_rel_exp: rel_exp  */
#line 465 "./parser.y"
                              { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2035 "./parser.tab.c"
    break;

  case 74: /* rel_exp: sum_exp rel_op sum_exp  */
#line 468 "./parser.y"
                                             {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = (yyvsp[-1].op);        /* relational operator from rel_op */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->child[0] = (yyvsp[-2].tree_node);       /* left operand */
                        t->child[1] = (yyvsp[0].tree_node);       /* right operand */
                        (yyval.tree_node) = t;
                    }
#line 2048 "./parser.tab.c"
    break;

  case 75: /* rel_exp: sum_exp  */
#line 476 "./parser.y"
                              { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2054 "./parser.tab.c"
    break;

  case 76: /* rel_op: LT  */
#line 479 "./parser.y"
                            { (yyval.op) = LT; }
#line 2060 "./parser.tab.c"
    break;

  case 77: /* rel_op: LEQ  */
#line 480 "./parser.y"
                            { (yyval.op) = LEQ; }
#line 2066 "./parser.tab.c"
    break;

  case 78: /* rel_op: GT  */
#line 481 "./parser.y"
                            { (yyval.op) = GT; }
#line 2072 "./parser.tab.c"
    break;

  case 79: /* rel_op: GEQ  */
#line 482 "./parser.y"
                            { (yyval.op) = GEQ; }
#line 2078 "./parser.tab.c"
    break;

  case 80: /* rel_op: EQ  */
#line 483 "./parser.y"
                            { (yyval.op) = EQ; }
#line 2084 "./parser.tab.c"
    break;

  case 81: /* rel_op: NEQ  */
#line 484 "./parser.y"
                            { (yyval.op) = NEQ; }
#line 2090 "./parser.tab.c"
    break;

  case 82: /* sum_exp: sum_exp sum_op mul_exp  */
#line 487 "./parser.y"
                                             {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = (yyvsp[-1].op);        /* sum operator from sum_op */
                        t->type = UndefinedType;
                        t->child[0] = (yyvsp[-2].tree_node);       /* left operand */
                        t->child[1] = (yyvsp[0].tree_node);       /* right operand */
                        (yyval.tree_node) = t;
                    }
#line 2103 "./parser.tab.c"
    break;

  case 83: /* sum_exp: mul_exp  */
#line 495 "./parser.y"
                              { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2109 "./parser.tab.c"
    break;

  case 84: /* sum_op: PLUS  */
#line 498 "./parser.y"
                           { (yyval.op) = PLUS; }
#line 2115 "./parser.tab.c"
    break;

  case 85: /* sum_op: MINUS  */
#line 499 "./parser.y"
                            { (yyval.op) = MINUS; }
#line 2121 "./parser.tab.c"
    break;

  case 86: /* mul_exp: mul_exp mul_op unary_exp  */
#line 502 "./parser.y"
                                               {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = (yyvsp[-1].op);            /* multiplication operator from mul_op */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->child[0] = (yyvsp[-2].tree_node);           /* left operand */
                        t->child[1] = (yyvsp[0].tree_node);           /* right operand */
                        (yyval.tree_node) = t;
                    }
#line 2134 "./parser.tab.c"
    break;

  case 87: /* mul_exp: unary_exp  */
#line 510 "./parser.y"
                                { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2140 "./parser.tab.c"
    break;

  case 88: /* mul_op: TIMES  */
#line 513 "./parser.y"
                            { (yyval.op) = TIMES; }
#line 2146 "./parser.tab.c"
    break;

  case 89: /* mul_op: DIV  */
#line 514 "./parser.y"
                            { (yyval.op) = DIV; }
#line 2152 "./parser.tab.c"
    break;

  case 90: /* mul_op: MOD  */
#line 515 "./parser.y"
                            { (yyval.op) = MOD; }
#line 2158 "./parser.tab.c"
    break;

  case 91: /* unary_exp: unary_op unary_exp  */
#line 518 "./parser.y"
                                         {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = (yyvsp[-1].op);            /* unary operator from unary_op */
                        t->type = UndefinedType;    
                        t->child[1] = (yyvsp[0].tree_node);           /* operand */
                        (yyval.tree_node) = t;
                    }
#line 2170 "./parser.tab.c"
    break;

  case 92: /* unary_exp: factor  */
#line 525 "./parser.y"
                             { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2176 "./parser.tab.c"
    break;

  case 93: /* unary_op: MINUS  */
#line 528 "./parser.y"
                                { (yyval.op) = CHSIGN; }
#line 2182 "./parser.tab.c"
    break;

  case 94: /* unary_op: TIMES  */
#line 529 "./parser.y"
                                { (yyval.op) = SIZEOF; }
#line 2188 "./parser.tab.c"
    break;

  case 95: /* unary_op: TERNARY  */
#line 530 "./parser.y"
                                { (yyval.op) = TERNARY; }
#line 2194 "./parser.tab.c"
    break;

  case 96: /* factor: mutable  */
#line 533 "./parser.y"
                                { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2200 "./parser.tab.c"
    break;

  case 97: /* factor: immutable  */
#line 534 "./parser.y"
                                { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2206 "./parser.tab.c"
    break;

  case 98: /* mutable: ID LBRACKET exp RBRACKET  */
#line 537 "./parser.y"
                                               {
                        TreeNode * t = newExpNode(OpK);
                        TreeNode * id = newExpNode(IdK);    /* create tree_node for first child */
                        id->attr.name = (yyvsp[-3].token_data)->svalue;     /* ID name comes from token_data_t svalue member */
                        id->isArray = true;             /* mark as array access */
                        t->attr.op = LBRACKET;          /* array access operator */
                        t->child[0] = id;               
                        t->child[1] = (yyvsp[-1].tree_node);               /* index expression */
                        t->type = UndefinedType;             /* set type to that of the lhs */
                        (yyval.tree_node) = t;                         /* assign new TreeNode to left-hand side */
                    }
#line 2222 "./parser.tab.c"
    break;

  case 99: /* mutable: ID  */
#line 548 "./parser.y"
                         {
                        TreeNode * t = newExpNode(IdK);
                        t->attr.name = (yyvsp[0].token_data)->svalue;  /* ID name comes from token_data_t svalue member */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 2233 "./parser.tab.c"
    break;

  case 100: /* immutable: LPAREN exp RPAREN  */
#line 556 "./parser.y"
                                        { (yyval.tree_node) = (yyvsp[-1].tree_node); }
#line 2239 "./parser.tab.c"
    break;

  case 101: /* immutable: call  */
#line 557 "./parser.y"
                           { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2245 "./parser.tab.c"
    break;

  case 102: /* immutable: constant  */
#line 558 "./parser.y"
                               { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2251 "./parser.tab.c"
    break;

  case 103: /* call: ID LPAREN args RPAREN  */
#line 561 "./parser.y"
                                            {
                        TreeNode * t = newExpNode(CallK);
                        t->attr.name = (yyvsp[-3].token_data)->svalue;  /* ID name comes from token_data_t svalue member */
                        t->child[0] = (yyvsp[-1].tree_node);           /* args */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 2262 "./parser.tab.c"
    break;

  case 104: /* args: arg_list  */
#line 569 "./parser.y"
                               { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2268 "./parser.tab.c"
    break;

  case 105: /* args: %empty  */
#line 570 "./parser.y"
                      { (yyval.tree_node) = NULL; }
#line 2274 "./parser.tab.c"
    break;

  case 106: /* arg_list: arg_list COMMA exp  */
#line 573 "./parser.y"
                                         {
                        TreeNode * t = (yyvsp[-2].tree_node);
                        if (t != NULL) {
                            while (t->sibling != NULL) {
                                t = t->sibling;
                            }
                            t->sibling = (yyvsp[0].tree_node);
                            (yyval.tree_node) = (yyvsp[-2].tree_node); 
                        } else {
                            (yyval.tree_node) = (yyvsp[0].tree_node);
                        }
                    }
#line 2291 "./parser.tab.c"
    break;

  case 107: /* arg_list: exp  */
#line 585 "./parser.y"
                          { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2297 "./parser.tab.c"
    break;

  case 108: /* constant: NUMBERCONST  */
#line 588 "./parser.y"
                                  {
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Integer;          /* set type to Integer */
                        t->attr.value = (yyvsp[0].token_data)->nvalue; /* value from token_data_t nvalue member */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 2308 "./parser.tab.c"
    break;

  case 109: /* constant: CHARCONST  */
#line 594 "./parser.y"
                                {
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Char;             /* set type to Char */
                        t->attr.cvalue = (yyvsp[0].token_data)->cvalue; /* value from token_data_t cvalue member */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 2319 "./parser.tab.c"
    break;

  case 110: /* constant: STRINGCONST  */
#line 600 "./parser.y"
                                  {
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Char;                 /* set type to String */
                        t->isArray = true;            /* mark as array to represent string */
                        t->attr.string = (yyvsp[0].token_data)->svalue;    /* string from token_data_t svalue member */
                        (yyval.tree_node) = t;                         /* assign new TreeNode to left-hand side */
                    }
#line 2331 "./parser.tab.c"
    break;

  case 111: /* constant: TRUE  */
#line 607 "./parser.y"
                           { 
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Boolean;          /* set type to Boolean */
                        t->attr.value = 1;          /* TRUE represented as 1 */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 2342 "./parser.tab.c"
    break;

  case 112: /* constant: FALSE  */
#line 613 "./parser.y"
                            { 
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Boolean;          /* set type to Boolean */
                        t->attr.value = 0;          /* FALSE represented as 0 */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 2353 "./parser.tab.c"
    break;


#line 2357 "./parser.tab.c"

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

#line 621 "./parser.y"


extern int yydebug;
int main(int argc, char *argv[])
{
    char opt;
    char *optstring = "pdPD"; // Options: a, b (requires an argument), c (requires an argument)
    int printTreeFlag = 0;
    int printTreeTypeFlag = 0;
    int symbolDebugFlag = 0;
    int args = 0;
    while ((opt = ourGetopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'p':
                printTreeFlag = 1;
                args++;
                break;
            case 'd':
                yydebug = 1;
                args++;
                break;
            case 'P':
                printTreeTypeFlag = 1;
                args++;
                break;
            case 'D':
                symbolDebugFlag = 1;
                args++;
                break;
            case '?':
                fprintf(stderr, "Unknown option -%c.\n", optopt);
                break;
        }
    }

    if (argc-args > 1) {
        if ((yyin = fopen(argv[argc - 1], "r"))) {
            // file open successful
        }
        else {
            // failed to open fie
            printf("ERROR: failed to open \'%s\'\n", argv[argc - 1]);
            exit(1);
        }
    }

    /* Parse */
    num_errors = 0;
    num_warnings = 0;
    yyparse();

    SymbolTable *symbol_table = new SymbolTable();      /* Create the symbol table */ 
                                                        /* This also default enters us into the Global scope */
    if (symbolDebugFlag) {
        symbol_table->debug(true);                   /* Enable debug mode for the symbol table */
    }

    semantic_analysis(syntaxTree, symbol_table);        /* Perform semantic analysis and build the symbol table */
        
    if (printTreeFlag) {
        printTree(syntaxTree, false); /* Print the syntax tree */
    }

    if (printTreeTypeFlag) {
        printTree(syntaxTree, true); /* Print the syntax tree with types */
    }

    TreeNode * main_func_node = (TreeNode *) symbol_table->lookupGlobal("main");
    
    if (main_func_node != NULL) {
        if (main_func_node->nodekind == DeclK && main_func_node->subkind.decl == FuncK) {
            /* Main function found */
        }
        else {
            printf("ERROR(LINKER): A function named 'main()' must be defined.\n");
            num_errors++;
        }
    }
    else {
        printf("ERROR(LINKER): A function named 'main()' must be defined.\n");
        num_errors++;
    }

    
    printf("Number of warnings: %d\n", num_warnings);
    printf("Number of errors: %d\n", num_errors);

    return 0;
}

/*


*/
