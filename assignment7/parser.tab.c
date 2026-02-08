/* A Bison parser, made by GNU Bison 3.8.1.  */

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
#define YYBISON 30801

/* Bison version string.  */
#define YYBISON_VERSION "3.8.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

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
#include "yyerror.h"
#include "semantic.h"
#include "ourgetopt.h"  /* ourgetopt() */
#include "code_generation.h"

extern int yylex();
extern FILE *yyin;
extern int line_num;		/* Error line number from the scanner */
extern bool syntax_errors;
int func_decl_saved_line_num;
char *saved_name;

ExpType saved_exp_type;
TreeNode *syntaxTree;
TreeNode *io_library_ast;
SymbolTable *symbol_table;
code_generation_linearized_node_t *code_generation_linearized_list_head = NULL;


#line 105 "src/parser.tab.c"

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
  YYSYMBOL_END = 56,                       /* END  */
  YYSYMBOL_57_ = 57,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 58,                  /* $accept  */
  YYSYMBOL_program = 59,                   /* program  */
  YYSYMBOL_decl_list = 60,                 /* decl_list  */
  YYSYMBOL_decl = 61,                      /* decl  */
  YYSYMBOL_var_decl = 62,                  /* var_decl  */
  YYSYMBOL_scoped_var_decl = 63,           /* scoped_var_decl  */
  YYSYMBOL_var_decl_list = 64,             /* var_decl_list  */
  YYSYMBOL_var_decl_init = 65,             /* var_decl_init  */
  YYSYMBOL_var_decl_id = 66,               /* var_decl_id  */
  YYSYMBOL_type_spec = 67,                 /* type_spec  */
  YYSYMBOL_func_decl = 68,                 /* func_decl  */
  YYSYMBOL_params = 69,                    /* params  */
  YYSYMBOL_param_list = 70,                /* param_list  */
  YYSYMBOL_param_type_list = 71,           /* param_type_list  */
  YYSYMBOL_param_id_list = 72,             /* param_id_list  */
  YYSYMBOL_param_id = 73,                  /* param_id  */
  YYSYMBOL_stmt = 74,                      /* stmt  */
  YYSYMBOL_matched_stmt = 75,              /* matched_stmt  */
  YYSYMBOL_unmatched_stmt = 76,            /* unmatched_stmt  */
  YYSYMBOL_matched_select_stmt = 77,       /* matched_select_stmt  */
  YYSYMBOL_unmatched_select_stmt = 78,     /* unmatched_select_stmt  */
  YYSYMBOL_exp_stmt = 79,                  /* exp_stmt  */
  YYSYMBOL_compound_stmt = 80,             /* compound_stmt  */
  YYSYMBOL_local_decls = 81,               /* local_decls  */
  YYSYMBOL_stmt_list = 82,                 /* stmt_list  */
  YYSYMBOL_matched_iter_stmt = 83,         /* matched_iter_stmt  */
  YYSYMBOL_unmatched_iter_stmt = 84,       /* unmatched_iter_stmt  */
  YYSYMBOL_iter_range = 85,                /* iter_range  */
  YYSYMBOL_return_stmt = 86,               /* return_stmt  */
  YYSYMBOL_break_stmt = 87,                /* break_stmt  */
  YYSYMBOL_exp = 88,                       /* exp  */
  YYSYMBOL_assign_op = 89,                 /* assign_op  */
  YYSYMBOL_simple_exp = 90,                /* simple_exp  */
  YYSYMBOL_and_exp = 91,                   /* and_exp  */
  YYSYMBOL_unary_rel_exp = 92,             /* unary_rel_exp  */
  YYSYMBOL_rel_exp = 93,                   /* rel_exp  */
  YYSYMBOL_rel_op = 94,                    /* rel_op  */
  YYSYMBOL_sum_exp = 95,                   /* sum_exp  */
  YYSYMBOL_sum_op = 96,                    /* sum_op  */
  YYSYMBOL_mul_exp = 97,                   /* mul_exp  */
  YYSYMBOL_mul_op = 98,                    /* mul_op  */
  YYSYMBOL_unary_exp = 99,                 /* unary_exp  */
  YYSYMBOL_unary_op = 100,                 /* unary_op  */
  YYSYMBOL_factor = 101,                   /* factor  */
  YYSYMBOL_mutable = 102,                  /* mutable  */
  YYSYMBOL_immutable = 103,                /* immutable  */
  YYSYMBOL_call = 104,                     /* call  */
  YYSYMBOL_args = 105,                     /* args  */
  YYSYMBOL_arg_list = 106,                 /* arg_list  */
  YYSYMBOL_constant = 107                  /* constant  */
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   670

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  156
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  246

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   311


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
       2,     2,     2,     2,     2,     2,     2,     2,    57,     2,
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
      55,    56
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    60,    60,    63,    76,    79,    80,    81,    84,    95,
      96,    99,   110,   122,   136,   137,   138,   141,   159,   160,
     163,   170,   178,   179,   182,   183,   184,   187,   198,   209,
     210,   211,   212,   215,   216,   219,   232,   233,   234,   237,
     245,   248,   262,   263,   264,   267,   276,   286,   287,   290,
     291,   292,   293,   294,   295,   298,   299,   302,   310,   311,
     312,   315,   322,   332,   333,   334,   337,   347,   360,   363,
     376,   380,   399,   423,   424,   425,   426,   429,   445,   468,
     469,   472,   478,   485,   486,   487,   490,   494,   500,   503,
     509,   517,   524,   531,   532,   533,   534,   535,   538,   539,
     540,   541,   542,   545,   553,   554,   557,   565,   566,   569,
     576,   577,   580,   587,   590,   591,   592,   593,   594,   595,
     598,   606,   607,   610,   611,   614,   622,   623,   626,   627,
     628,   631,   639,   640,   643,   644,   645,   648,   649,   652,
     662,   670,   671,   672,   673,   676,   682,   685,   686,   689,
     703,   704,   707,   714,   721,   729,   736
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
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
  "SEMI", "END", "':'", "$accept", "program", "decl_list", "decl",
  "var_decl", "scoped_var_decl", "var_decl_list", "var_decl_init",
  "var_decl_id", "type_spec", "func_decl", "params", "param_list",
  "param_type_list", "param_id_list", "param_id", "stmt", "matched_stmt",
  "unmatched_stmt", "matched_select_stmt", "unmatched_select_stmt",
  "exp_stmt", "compound_stmt", "local_decls", "stmt_list",
  "matched_iter_stmt", "unmatched_iter_stmt", "iter_range", "return_stmt",
  "break_stmt", "exp", "assign_op", "simple_exp", "and_exp",
  "unary_rel_exp", "rel_exp", "rel_op", "sum_exp", "sum_op", "mul_exp",
  "mul_op", "unary_exp", "unary_op", "factor", "mutable", "immutable",
  "call", "args", "arg_list", "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-145)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-149)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     154,   229,   -14,  -145,  -145,  -145,    36,   608,  -145,  -145,
     157,  -145,    61,    18,   156,  -145,    -4,    17,  -145,  -145,
     437,   105,   192,  -145,   296,     9,   255,  -145,   296,    56,
     272,    43,     8,  -145,  -145,    30,  -145,    72,   132,  -145,
    -145,  -145,  -145,  -145,   321,  -145,  -145,  -145,   341,    92,
     115,  -145,  -145,   606,    98,  -145,    83,  -145,  -145,  -145,
    -145,  -145,  -145,    77,    61,  -145,    92,    96,   120,   121,
    -145,     7,   232,    56,   133,  -145,   273,   366,    72,  -145,
     376,   142,    92,   421,   386,   411,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,   181,   578,  -145,  -145,  -145,   623,
      72,  -145,  -145,   128,   279,  -145,  -145,  -145,  -145,  -145,
     140,   376,  -145,   149,   147,   152,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,   366,  -145,  -145,  -145,   431,    72,   115,
      72,  -145,    63,    72,    98,    72,  -145,  -145,  -145,  -145,
     260,  -145,  -145,   456,  -145,  -145,   376,  -145,   186,  -145,
     284,   104,   376,  -145,   284,   208,   141,   476,    11,   155,
     285,   501,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,   159,   239,  -145,  -145,    15,
      12,   331,  -145,   165,  -145,  -145,   203,    -1,    62,  -145,
    -145,   202,   249,   249,  -145,  -145,   521,   202,   249,   546,
     307,   501,  -145,   213,  -145,  -145,   217,    21,   215,    27,
    -145,  -145,  -145,    81,    29,   221,    70,   249,   249,   247,
     202,   249,   566,   202,   202,   521,   202,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,    72,    53,   250,   277,   275,
     591,   202,   202,   202,    72,    92
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    24,    26,    25,     0,     0,     4,     5,
       0,     6,    16,    20,     0,    14,    19,     0,     1,     3,
      29,    20,     0,    23,     0,     0,     0,     9,     0,    31,
       0,     0,    33,    36,    10,     0,     8,     0,   140,   152,
     153,   154,   155,   156,     0,   134,   135,   136,     0,    18,
     104,   107,   110,   113,   121,   126,     0,   132,   137,   138,
     142,   143,    22,     0,    15,    13,    17,    40,    46,    39,
      42,     0,     0,    30,     0,   146,     0,     0,   111,   109,
     144,     0,    93,   137,     0,     0,   114,   115,   116,   117,
     118,   119,   123,   124,     0,     0,   128,   129,   130,     0,
     133,   131,    21,     0,     0,    32,    68,    28,    37,    35,
       0,     0,   150,     0,   147,     0,    98,    99,   100,   101,
     102,    97,    96,     0,   141,    91,    92,     0,   105,   103,
     108,   106,   112,   122,   120,   127,   125,    45,    43,    41,
      70,    27,   145,     0,   139,    94,    95,    90,     0,    67,
       0,     0,   151,   149,     0,     0,     0,     0,     0,     0,
       0,     0,    66,    64,    69,    47,    48,    50,    56,    52,
      51,    49,    55,    53,    54,     0,     0,    12,    65,    58,
       0,     0,    86,     0,    89,    76,     0,    74,     0,    63,
      11,     0,     0,     0,    88,    87,     0,     0,     0,     0,
       0,     0,    59,     0,    79,    61,    47,     0,     0,     0,
      73,    71,    77,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    60,    80,    57,
      62,    84,    75,    72,    78,    83,    81,     0,     0,     0,
       0,     0,     0,     0,    85,    82
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -145,  -145,  -145,   302,  -145,  -145,    -7,   286,  -145,     2,
    -145,   268,  -145,   243,  -145,   207,   123,  -144,   -86,  -145,
    -145,  -145,   -43,  -145,  -145,  -145,  -145,    93,  -145,  -145,
     -42,   236,   -23,   245,   -21,  -145,  -145,   240,  -145,   228,
    -145,   -45,  -145,  -145,   -24,  -145,  -145,  -145,  -145,  -145
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     6,     7,     8,     9,   149,    14,    15,    16,    30,
      11,    31,    32,    33,    69,    70,   164,   211,   166,   167,
     168,   169,   170,   140,   151,   171,   172,   208,   173,   174,
     175,   123,    82,    50,    51,    52,    94,    53,    95,    54,
      99,    55,    56,    57,    83,    59,    60,   113,   114,    61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      58,    49,    10,    22,    58,    66,    81,   165,   105,    10,
      62,   101,   181,    63,    38,    39,    40,    41,    29,   197,
      58,    42,    43,    79,     3,     4,     5,   193,   107,   191,
     192,    73,    58,    17,   112,   115,    18,     3,     4,     5,
     219,   220,    84,    44,   224,   222,    75,   202,   203,   206,
      28,    45,    46,   210,   136,    47,   106,    84,    48,    84,
      58,    58,    75,    72,   131,   -34,   182,   141,    75,    25,
      58,    58,   240,   227,   229,    58,   232,   233,   -34,   237,
     238,   145,   198,    84,   100,   147,    38,    39,    40,    41,
     226,    71,    84,    42,    43,   191,   223,   227,   229,   233,
      84,   153,    92,    93,   -38,   156,   204,    38,    39,    40,
      41,   -38,   212,    23,    42,    43,   183,   157,    24,    75,
     158,   159,    84,    45,    46,   160,   161,    47,    75,   102,
      48,   228,   230,    58,   180,   234,    44,    58,   188,    96,
      97,    98,   150,   155,    45,    46,    85,   176,    47,   -44,
     154,    48,    35,   106,   162,     1,    25,     2,    20,   163,
      21,     3,     4,     5,   116,   117,   118,   119,   120,   121,
     122,   103,    58,   209,   104,    58,   214,    58,   216,    76,
     137,   110,    37,    77,    38,    39,    40,    41,    75,   106,
     124,    42,    43,     3,     4,     5,   178,   142,    58,   236,
     143,    58,   209,   156,   144,    38,    39,    40,    41,    26,
     184,    27,    42,    43,   189,   199,    58,   245,   158,   159,
     195,    45,    46,   200,   201,    47,   196,   217,    48,    -7,
      12,   218,    13,   108,    44,   221,    -7,    -7,    -7,     3,
       4,     5,    45,    46,   225,    26,    47,    36,   231,    48,
     156,   106,    38,    39,    40,    41,    64,   163,    13,    42,
      43,    26,   157,   177,   241,   158,   159,     3,     4,     5,
     160,   161,   148,    67,   111,    68,    38,    39,    40,    41,
     138,    44,    68,    42,    43,    12,   185,    13,   186,    45,
      46,   242,    26,    47,   190,   243,    48,    37,   106,    38,
      39,    40,    41,    74,   163,    44,    42,    43,   185,    19,
     215,   139,    65,    45,    46,   109,   205,    47,   239,   127,
      48,  -148,    78,   134,    38,    39,    40,    41,    44,   129,
       0,    42,    43,     0,   132,     0,    45,    46,     0,     0,
      47,     0,    80,    48,    38,    39,    40,    41,     0,     0,
       0,    42,    43,    44,   116,   117,   118,   119,   120,   121,
     122,    45,    46,     0,     0,    47,     0,   111,    48,    38,
      39,    40,    41,    44,     0,     0,    42,    43,    75,     0,
       0,    45,    46,     0,     0,    47,   194,   128,    48,    38,
      39,    40,    41,     0,     0,     0,    42,    43,    44,   116,
     117,   118,   119,   120,   121,   122,    45,    46,     0,     0,
      47,     0,   130,    48,    38,    39,    40,    41,    44,     0,
       0,    42,    43,    75,     0,     0,    45,    46,     0,     0,
      47,     0,   146,    48,    38,    39,    40,    41,     0,     0,
       0,    42,    43,    44,   116,   117,   118,   119,   120,   125,
     126,    45,    46,     0,     0,    47,     0,   152,    48,    38,
      39,    40,    41,    44,     0,     0,    42,    43,     0,     0,
       0,    45,    46,     0,     0,    47,     0,   179,    48,    38,
      39,    40,    41,     0,     0,     0,    42,    43,    44,    23,
     -16,     0,    34,     0,    24,     0,    45,    46,     0,     0,
      47,     0,   187,    48,    38,    39,    40,    41,    44,     0,
       0,    42,    43,     0,     0,     0,    45,    46,     0,     0,
      47,     0,   207,    48,    38,    39,    40,    41,     0,     0,
       0,    42,    43,    44,     0,     0,     0,     0,     0,     0,
       0,    45,    46,     0,     0,    47,     0,   213,    48,    38,
      39,    40,    41,    44,     0,     0,    42,    43,     0,     0,
       0,    45,    46,     0,     0,    47,     0,   235,    48,    38,
      39,    40,    41,     0,     0,     0,    42,    43,    44,   133,
       0,    38,    39,    40,    41,     0,    45,    46,    42,    43,
      47,     0,   244,    48,    38,    39,    40,    41,    44,     0,
       0,    42,    43,     0,     0,     0,    45,    46,    -2,     1,
      47,     2,     0,    48,     0,     3,     4,     5,    45,    46,
       0,     0,    47,    44,   135,    48,    38,    39,    40,    41,
       0,    45,    46,    42,    43,    47,     0,     0,    48,    86,
      87,    88,    89,    90,    91,    92,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45,    46,     0,     0,    47,     0,     0,
      48
};

static const yytype_int16 yycheck[] =
{
      24,    24,     0,    10,    28,    28,    48,   151,     1,     7,
       1,    56,     1,     4,     3,     4,     5,     6,     1,    20,
      44,    10,    11,    44,     7,     8,     9,    15,    71,    14,
      15,     1,    56,    47,    76,    77,     0,     7,     8,     9,
      19,    20,    30,    32,    15,    18,    47,   191,   192,   193,
      54,    40,    41,   197,    99,    44,    49,    30,    47,    30,
      84,    85,    47,    55,    85,    48,    55,   110,    47,    51,
      94,    95,    19,   217,   218,    99,   220,   221,    48,   223,
     224,   123,    20,    30,     1,   127,     3,     4,     5,     6,
      20,    48,    30,    10,    11,    14,    15,   241,   242,   243,
      30,   143,    39,    40,    48,     1,   192,     3,     4,     5,
       6,    55,   198,    52,    10,    11,   158,    13,    57,    47,
      16,    17,    30,    40,    41,    21,    22,    44,    47,    52,
      47,   217,   218,   157,   157,   221,    32,   161,   161,    41,
      42,    43,   140,   150,    40,    41,    31,   154,    44,    53,
     148,    47,    47,    49,    50,     1,    51,     3,     1,    55,
       3,     7,     8,     9,    23,    24,    25,    26,    27,    28,
      29,    51,   196,   196,    53,   199,   199,   201,   201,    47,
      52,    48,     1,    51,     3,     4,     5,     6,    47,    49,
      48,    10,    11,     7,     8,     9,    55,    48,   222,   222,
      53,   225,   225,     1,    52,     3,     4,     5,     6,    53,
      55,    55,    10,    11,    55,    13,   240,   240,    16,    17,
      55,    40,    41,    21,    22,    44,    23,    14,    47,     0,
       1,    14,     3,     1,    32,    20,     7,     8,     9,     7,
       8,     9,    40,    41,    23,    53,    44,    55,     1,    47,
       1,    49,     3,     4,     5,     6,     1,    55,     3,    10,
      11,    53,    13,    55,    14,    16,    17,     7,     8,     9,
      21,    22,    12,     1,     1,     3,     3,     4,     5,     6,
       1,    32,     3,    10,    11,     1,     1,     3,     3,    40,
      41,    14,    53,    44,    55,    20,    47,     1,    49,     3,
       4,     5,     6,    35,    55,    32,    10,    11,     1,     7,
       3,   104,    26,    40,    41,    72,   193,    44,   225,    83,
      47,    48,     1,    95,     3,     4,     5,     6,    32,    84,
      -1,    10,    11,    -1,    94,    -1,    40,    41,    -1,    -1,
      44,    -1,     1,    47,     3,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    32,    23,    24,    25,    26,    27,    28,
      29,    40,    41,    -1,    -1,    44,    -1,     1,    47,     3,
       4,     5,     6,    32,    -1,    -1,    10,    11,    47,    -1,
      -1,    40,    41,    -1,    -1,    44,    55,     1,    47,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    32,    23,
      24,    25,    26,    27,    28,    29,    40,    41,    -1,    -1,
      44,    -1,     1,    47,     3,     4,     5,     6,    32,    -1,
      -1,    10,    11,    47,    -1,    -1,    40,    41,    -1,    -1,
      44,    -1,     1,    47,     3,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    32,    23,    24,    25,    26,    27,    28,
      29,    40,    41,    -1,    -1,    44,    -1,     1,    47,     3,
       4,     5,     6,    32,    -1,    -1,    10,    11,    -1,    -1,
      -1,    40,    41,    -1,    -1,    44,    -1,     1,    47,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    32,    52,
      53,    -1,    55,    -1,    57,    -1,    40,    41,    -1,    -1,
      44,    -1,     1,    47,     3,     4,     5,     6,    32,    -1,
      -1,    10,    11,    -1,    -1,    -1,    40,    41,    -1,    -1,
      44,    -1,     1,    47,     3,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    -1,    -1,    44,    -1,     1,    47,     3,
       4,     5,     6,    32,    -1,    -1,    10,    11,    -1,    -1,
      -1,    40,    41,    -1,    -1,    44,    -1,     1,    47,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    32,     1,
      -1,     3,     4,     5,     6,    -1,    40,    41,    10,    11,
      44,    -1,     1,    47,     3,     4,     5,     6,    32,    -1,
      -1,    10,    11,    -1,    -1,    -1,    40,    41,     0,     1,
      44,     3,    -1,    47,    -1,     7,     8,     9,    40,    41,
      -1,    -1,    44,    32,     1,    47,     3,     4,     5,     6,
      -1,    40,    41,    10,    11,    44,    -1,    -1,    47,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    41,    -1,    -1,    44,    -1,    -1,
      47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     7,     8,     9,    59,    60,    61,    62,
      67,    68,     1,     3,    64,    65,    66,    47,     0,    61,
       1,     3,    64,    52,    57,    51,    53,    55,    54,     1,
      67,    69,    70,    71,    55,    47,    55,     1,     3,     4,
       5,     6,    10,    11,    32,    40,    41,    44,    47,    90,
      91,    92,    93,    95,    97,    99,   100,   101,   102,   103,
     104,   107,     1,     4,     1,    65,    90,     1,     3,    72,
      73,    48,    55,     1,    69,    47,    47,    51,     1,    92,
       1,    88,    90,   102,    30,    31,    33,    34,    35,    36,
      37,    38,    39,    40,    94,    96,    41,    42,    43,    98,
       1,    99,    52,    51,    53,     1,    49,    80,     1,    71,
      48,     1,    88,   105,   106,    88,    23,    24,    25,    26,
      27,    28,    29,    89,    48,    28,    29,    89,     1,    91,
       1,    92,    95,     1,    97,     1,    99,    52,     1,    73,
      81,    80,    48,    53,    52,    88,     1,    88,    12,    63,
      67,    82,     1,    88,    67,    64,     1,    13,    16,    17,
      21,    22,    50,    55,    74,    75,    76,    77,    78,    79,
      80,    83,    84,    86,    87,    88,    64,    55,    55,     1,
      90,     1,    55,    88,    55,     1,     3,     1,    90,    55,
      55,    14,    15,    15,    55,    55,    23,    20,    20,    13,
      21,    22,    75,    75,    76,    74,    75,     1,    85,    90,
      75,    75,    76,     1,    90,     3,    90,    14,    14,    19,
      20,    20,    18,    15,    15,    23,    20,    75,    76,    75,
      76,     1,    75,    75,    76,     1,    90,    75,    75,    85,
      19,    14,    14,    20,     1,    90
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    58,    59,    60,    60,    61,    61,    61,    62,    62,
      62,    63,    63,    64,    64,    64,    64,    65,    65,    65,
      66,    66,    66,    66,    67,    67,    67,    68,    68,    68,
      68,    68,    68,    69,    69,    70,    70,    70,    70,    71,
      71,    72,    72,    72,    72,    73,    73,    74,    74,    75,
      75,    75,    75,    75,    75,    76,    76,    77,    77,    77,
      77,    78,    78,    79,    79,    79,    80,    81,    81,    82,
      82,    83,    83,    83,    83,    83,    83,    84,    84,    84,
      84,    85,    85,    85,    85,    85,    86,    86,    86,    87,
      88,    88,    88,    88,    88,    88,    88,    88,    89,    89,
      89,    89,    89,    90,    90,    90,    91,    91,    91,    92,
      92,    92,    93,    93,    94,    94,    94,    94,    94,    94,
      95,    95,    95,    96,    96,    97,    97,    97,    98,    98,
      98,    99,    99,    99,   100,   100,   100,   101,   101,   102,
     102,   103,   103,   103,   103,   104,   104,   105,   105,   106,
     106,   106,   107,   107,   107,   107,   107
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     3,
       3,     4,     3,     3,     1,     3,     1,     3,     3,     1,
       1,     4,     3,     2,     1,     1,     1,     6,     5,     2,
       4,     3,     5,     1,     0,     3,     1,     3,     1,     2,
       2,     3,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     6,     2,     4,
       6,     4,     6,     2,     1,     2,     4,     2,     0,     2,
       0,     4,     6,     4,     2,     6,     2,     4,     6,     4,
       6,     3,     5,     3,     3,     5,     2,     3,     3,     2,
       3,     2,     2,     1,     3,     3,     2,     2,     1,     1,
       1,     1,     1,     3,     1,     3,     3,     1,     3,     2,
       1,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     1,     1,     3,     1,     3,     1,     1,
       1,     2,     1,     2,     1,     1,     1,     1,     1,     4,
       1,     3,     1,     1,     2,     4,     2,     1,     0,     3,
       1,     3,     1,     1,     1,     1,     1
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
#line 60 "src/parser.y"
                        { syntaxTree = (yyvsp[0].tree_node); }
#line 1736 "src/parser.tab.c"
    break;

  case 3: /* decl_list: decl_list decl  */
#line 63 "src/parser.y"
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
#line 1754 "src/parser.tab.c"
    break;

  case 4: /* decl_list: decl  */
#line 76 "src/parser.y"
                       { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1760 "src/parser.tab.c"
    break;

  case 5: /* decl: var_decl  */
#line 79 "src/parser.y"
                       { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1766 "src/parser.tab.c"
    break;

  case 6: /* decl: func_decl  */
#line 80 "src/parser.y"
                            { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1772 "src/parser.tab.c"
    break;

  case 7: /* decl: error  */
#line 81 "src/parser.y"
                    { (yyval.tree_node) = NULL; }
#line 1778 "src/parser.tab.c"
    break;

  case 8: /* var_decl: type_spec var_decl_list SEMI  */
#line 84 "src/parser.y"
                                           {
                TreeNode * t = (yyvsp[-1].tree_node);

                while (t != NULL) {               /* var_decl_list, so iterate through the list */
                    t->type = (yyvsp[-2].type);                 /* set type_spec terminal type for each var_decl */
                    t->var_kind = Global;          /* set variable kind to Global */
                    t = t->sibling;               /* move to next var_decl in the list */
                }
                (yyval.tree_node) = (yyvsp[-1].tree_node);                         /* assign the starting tree_node *, front of the list, to left-hand side */
                yyerrok;
            }
#line 1794 "src/parser.tab.c"
    break;

  case 9: /* var_decl: error var_decl_list SEMI  */
#line 95 "src/parser.y"
                                       { (yyval.tree_node) = NULL; yyerrok; }
#line 1800 "src/parser.tab.c"
    break;

  case 10: /* var_decl: type_spec error SEMI  */
#line 96 "src/parser.y"
                                   { (yyval.tree_node) = NULL; yyerrok; yyerrok; }
#line 1806 "src/parser.tab.c"
    break;

  case 11: /* scoped_var_decl: STATIC type_spec var_decl_list SEMI  */
#line 99 "src/parser.y"
                                                          {
                        TreeNode * t = (yyvsp[-1].tree_node);
                        while (t != NULL) {                 /* var_decl_list, so iterate through the list */
                            t->type = (yyvsp[-2].type);                   /* set type_spec terminal type for each var_decl */
                            t->isStatic = true;             /* mark as static */
                            t->var_kind = LocalStatic;      /* set variable kind to LocalStatic */
                            t = t->sibling;                 /* move to next var_decl in the list */
                        }
                        (yyval.tree_node) = (yyvsp[-1].tree_node);                          /* assign the starting tree_node *, front of the list, to left-hand side */
                        yyerrok;
                    }
#line 1822 "src/parser.tab.c"
    break;

  case 12: /* scoped_var_decl: type_spec var_decl_list SEMI  */
#line 110 "src/parser.y"
                                                           {
                        TreeNode * t = (yyvsp[-1].tree_node);
                        while (t != NULL) {                 /* var_decl_list, so iterate through the list */
                            t->type = (yyvsp[-2].type);                   /* set type_spec terminal type for each var_decl */
                            t->var_kind = Local;            /* mark as Local reference type */
                            t = t->sibling;                 /* move to next var_decl in the list */
                        }
                        (yyval.tree_node) = (yyvsp[-1].tree_node);                          /* assign the starting tree_node *, front of the list, to left-hand side */
                        yyerrok;
                    }
#line 1837 "src/parser.tab.c"
    break;

  case 13: /* var_decl_list: var_decl_list COMMA var_decl_init  */
#line 122 "src/parser.y"
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
                        yyerrok;
                    }
#line 1856 "src/parser.tab.c"
    break;

  case 14: /* var_decl_list: var_decl_init  */
#line 136 "src/parser.y"
                                        { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1862 "src/parser.tab.c"
    break;

  case 15: /* var_decl_list: var_decl_list COMMA error  */
#line 137 "src/parser.y"
                                                { (yyval.tree_node) = NULL; }
#line 1868 "src/parser.tab.c"
    break;

  case 16: /* var_decl_list: error  */
#line 138 "src/parser.y"
                                                { (yyval.tree_node) = NULL; }
#line 1874 "src/parser.tab.c"
    break;

  case 17: /* var_decl_init: var_decl_id COLON simple_exp  */
#line 141 "src/parser.y"
                                                   { 
                        TreeNode * t = (yyvsp[-2].tree_node);
                        TreeNode * init = (yyvsp[0].tree_node);
                        
                        init->initializer = true;
                        if ((yyvsp[0].tree_node)->subkind.exp == ConstantK) {
                            /* If the initializer is a constant, set the variable's isInitializedWithConstant flag to true */
                            init->isConstant = true;
                        }
                        
                        if (t != NULL) {
                            t->isInitialized = true;        /* mark as initialized */
                            t->child[0] = init;             /* simple_exp */
                        }

                        init->param_sibling = t;        /* tie the initializer to the variable it is initiallizing */
                        (yyval.tree_node) = t;                         /* assign new TreeNode* to left-hand side */
                    }
#line 1897 "src/parser.tab.c"
    break;

  case 18: /* var_decl_init: error ':' simple_exp  */
#line 159 "src/parser.y"
                                            { (yyval.tree_node) = NULL; yyerrok; }
#line 1903 "src/parser.tab.c"
    break;

  case 19: /* var_decl_init: var_decl_id  */
#line 160 "src/parser.y"
                                                { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 1909 "src/parser.tab.c"
    break;

  case 20: /* var_decl_id: ID  */
#line 163 "src/parser.y"
                         {
                        TreeNode * t = newDeclNode(VarK);
                        t->attr.name = (yyvsp[0].token_data)->svalue;  /* ID name comes from token_data_t svalue member */
                        t->lineno = (yyvsp[0].token_data)->line_num;   /* set variable declaration line number to that of when the ID was scanned */
                        t->dataword_size = 1;       /* default dataword size to 1 */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 1921 "src/parser.tab.c"
    break;

  case 21: /* var_decl_id: ID LBRACKET NUMBERCONST RBRACKET  */
#line 170 "src/parser.y"
                                                           {
                        TreeNode * t = newDeclNode(VarK);
                        t->attr.name = (yyvsp[-3].token_data)->svalue;          /* ID name comes from token_data_t svalue member */
                        t->isArray = true;                  /* mark as array variable */
                        t->lineno = (yyvsp[-3].token_data)->line_num;           /* set variable declaration line number to that of when the ID was scanned */
                        t->dataword_size = (yyvsp[-1].token_data)->nvalue + 1;  /* set dataword size to the size specified by the NUMBERCONST + 1 as arrays first dataword will be the size of the array itself */
                        (yyval.tree_node) = t;                             /* assign new TreeNode to left-hand side */
                    }
#line 1934 "src/parser.tab.c"
    break;

  case 22: /* var_decl_id: ID LBRACKET error  */
#line 178 "src/parser.y"
                                                { (yyval.tree_node) = NULL; }
#line 1940 "src/parser.tab.c"
    break;

  case 23: /* var_decl_id: error RBRACKET  */
#line 179 "src/parser.y"
                                                { (yyval.tree_node) = NULL; yyerrok; }
#line 1946 "src/parser.tab.c"
    break;

  case 24: /* type_spec: BOOL  */
#line 182 "src/parser.y"
                           { (yyval.type) = Boolean; }
#line 1952 "src/parser.tab.c"
    break;

  case 25: /* type_spec: CHAR  */
#line 183 "src/parser.y"
                               { (yyval.type) = Char; }
#line 1958 "src/parser.tab.c"
    break;

  case 26: /* type_spec: INT  */
#line 184 "src/parser.y"
                               { (yyval.type) = Integer; }
#line 1964 "src/parser.tab.c"
    break;

  case 27: /* func_decl: type_spec ID LPAREN params RPAREN compound_stmt  */
#line 187 "src/parser.y"
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
#line 1980 "src/parser.tab.c"
    break;

  case 28: /* func_decl: ID LPAREN params RPAREN compound_stmt  */
#line 198 "src/parser.y"
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
#line 1996 "src/parser.tab.c"
    break;

  case 29: /* func_decl: type_spec error  */
#line 209 "src/parser.y"
                                                                    { (yyval.tree_node) = NULL; }
#line 2002 "src/parser.tab.c"
    break;

  case 30: /* func_decl: type_spec ID LPAREN error  */
#line 210 "src/parser.y"
                                                                    { (yyval.tree_node) = NULL; }
#line 2008 "src/parser.tab.c"
    break;

  case 31: /* func_decl: ID LPAREN error  */
#line 211 "src/parser.y"
                                                                    { (yyval.tree_node) = NULL; }
#line 2014 "src/parser.tab.c"
    break;

  case 32: /* func_decl: ID LPAREN params RPAREN error  */
#line 212 "src/parser.y"
                                                                    { (yyval.tree_node) = NULL; }
#line 2020 "src/parser.tab.c"
    break;

  case 33: /* params: param_list  */
#line 215 "src/parser.y"
                                 { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2026 "src/parser.tab.c"
    break;

  case 34: /* params: %empty  */
#line 216 "src/parser.y"
                          { (yyval.tree_node) = NULL; }
#line 2032 "src/parser.tab.c"
    break;

  case 35: /* param_list: param_list SEMI param_type_list  */
#line 219 "src/parser.y"
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
#line 2050 "src/parser.tab.c"
    break;

  case 36: /* param_list: param_type_list  */
#line 232 "src/parser.y"
                                                { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2056 "src/parser.tab.c"
    break;

  case 37: /* param_list: param_list SEMI error  */
#line 233 "src/parser.y"
                                                { (yyval.tree_node) = NULL; }
#line 2062 "src/parser.tab.c"
    break;

  case 38: /* param_list: error  */
#line 234 "src/parser.y"
                                                { (yyval.tree_node) = NULL; }
#line 2068 "src/parser.tab.c"
    break;

  case 39: /* param_type_list: type_spec param_id_list  */
#line 237 "src/parser.y"
                                              {
                        TreeNode * t = (yyvsp[0].tree_node);
                        while (t != NULL) {               /* param_id_list, so iterate through the list */
                            t->type = (yyvsp[-1].type);                 /* set type_spec terminal type for each param_id */
                            t = t->sibling;               /* move to next param_id in the list */
                        }
                        (yyval.tree_node) = (yyvsp[0].tree_node);                         /* assign the starting tree_node *, front of the list, to left-hand side */
                    }
#line 2081 "src/parser.tab.c"
    break;

  case 40: /* param_type_list: type_spec error  */
#line 245 "src/parser.y"
                                                { (yyval.tree_node) = NULL; }
#line 2087 "src/parser.tab.c"
    break;

  case 41: /* param_id_list: param_id_list COMMA param_id  */
#line 248 "src/parser.y"
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
                        yyerrok;
                    }
#line 2106 "src/parser.tab.c"
    break;

  case 42: /* param_id_list: param_id  */
#line 262 "src/parser.y"
                                                    { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2112 "src/parser.tab.c"
    break;

  case 43: /* param_id_list: param_id_list COMMA error  */
#line 263 "src/parser.y"
                                                    { (yyval.tree_node) = NULL; }
#line 2118 "src/parser.tab.c"
    break;

  case 44: /* param_id_list: error  */
#line 264 "src/parser.y"
                                                    { (yyval.tree_node) = NULL; }
#line 2124 "src/parser.tab.c"
    break;

  case 45: /* param_id: ID LBRACKET RBRACKET  */
#line 267 "src/parser.y"
                                           {
                        TreeNode * t = newDeclNode(ParamK);
                        t->attr.name = (yyvsp[-2].token_data)->svalue;  /* ID name comes from token_data_t svalue member */
                        t->isArray = true;          /* mark as array parameter */
                        t->var_kind = Parameter;
                        t->dataword_size = 1;      /* all param dataword_size will be 1 since pass by reference */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 2138 "src/parser.tab.c"
    break;

  case 46: /* param_id: ID  */
#line 276 "src/parser.y"
                         {
                        TreeNode * t = newDeclNode(ParamK);
                        t->attr.name = (yyvsp[0].token_data)->svalue;  /* ID name comes from token_data_t svalue member */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->var_kind = Parameter;
                        t->dataword_size = 1;      /* all param dataword_size will be 1 since pass by reference */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 2151 "src/parser.tab.c"
    break;

  case 47: /* stmt: matched_stmt  */
#line 286 "src/parser.y"
                                   { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2157 "src/parser.tab.c"
    break;

  case 48: /* stmt: unmatched_stmt  */
#line 287 "src/parser.y"
                                     { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2163 "src/parser.tab.c"
    break;

  case 49: /* matched_stmt: matched_iter_stmt  */
#line 290 "src/parser.y"
                                        { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2169 "src/parser.tab.c"
    break;

  case 50: /* matched_stmt: matched_select_stmt  */
#line 291 "src/parser.y"
                                          { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2175 "src/parser.tab.c"
    break;

  case 51: /* matched_stmt: compound_stmt  */
#line 292 "src/parser.y"
                                    { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2181 "src/parser.tab.c"
    break;

  case 52: /* matched_stmt: exp_stmt  */
#line 293 "src/parser.y"
                               { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2187 "src/parser.tab.c"
    break;

  case 53: /* matched_stmt: return_stmt  */
#line 294 "src/parser.y"
                                  { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2193 "src/parser.tab.c"
    break;

  case 54: /* matched_stmt: break_stmt  */
#line 295 "src/parser.y"
                                 { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2199 "src/parser.tab.c"
    break;

  case 55: /* unmatched_stmt: unmatched_iter_stmt  */
#line 298 "src/parser.y"
                                          { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2205 "src/parser.tab.c"
    break;

  case 56: /* unmatched_stmt: unmatched_select_stmt  */
#line 299 "src/parser.y"
                                            { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2211 "src/parser.tab.c"
    break;

  case 57: /* matched_select_stmt: IF simple_exp THEN matched_stmt ELSE matched_stmt  */
#line 302 "src/parser.y"
                                                                        {
                        TreeNode * t = newStmtNode(IfK);
                        t->child[0] = (yyvsp[-4].tree_node);   /* simple_exp */
                        t->child[1] = (yyvsp[-2].tree_node);   /* matched_stmt for THEN */
                        t->child[2] = (yyvsp[0].tree_node);   /* matched_stmt for ELSE */
                        t->lineno = (yyvsp[-4].tree_node)->lineno;  /* set if statement line number to that of when the simple_exp was scanned */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 2224 "src/parser.tab.c"
    break;

  case 58: /* matched_select_stmt: IF error  */
#line 310 "src/parser.y"
                                                                        { (yyval.tree_node) = NULL; }
#line 2230 "src/parser.tab.c"
    break;

  case 59: /* matched_select_stmt: IF error ELSE matched_stmt  */
#line 311 "src/parser.y"
                                                                        { (yyval.tree_node) = NULL; yyerrok; }
#line 2236 "src/parser.tab.c"
    break;

  case 60: /* matched_select_stmt: IF error THEN matched_stmt ELSE matched_stmt  */
#line 312 "src/parser.y"
                                                                        { (yyval.tree_node) = NULL; yyerrok; }
#line 2242 "src/parser.tab.c"
    break;

  case 61: /* unmatched_select_stmt: IF simple_exp THEN stmt  */
#line 315 "src/parser.y"
                                                  {
                            TreeNode * t = newStmtNode(IfK);
                            t->child[0] = (yyvsp[-2].tree_node);   /* simple_exp */
                            t->child[1] = (yyvsp[0].tree_node);   /* matched_stmt for THEN */
                            t->lineno = (yyvsp[-2].tree_node)->lineno;  /* set if statement line number to that of when the simple_exp was scanned */
                            (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                        }
#line 2254 "src/parser.tab.c"
    break;

  case 62: /* unmatched_select_stmt: IF simple_exp THEN matched_stmt ELSE unmatched_stmt  */
#line 322 "src/parser.y"
                                                                              {
                            TreeNode * t = newStmtNode(IfK);
                            t->child[0] = (yyvsp[-4].tree_node);   /* simple_exp */
                            t->child[1] = (yyvsp[-2].tree_node);   /* matched_stmt for THEN */
                            t->child[2] = (yyvsp[0].tree_node);   /* unmatched_stmt for ELSE */
                            t->lineno = (yyvsp[-4].tree_node)->lineno;  /* set if statement line number to that of when the simple_exp was scanned */
                            (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                        }
#line 2267 "src/parser.tab.c"
    break;

  case 63: /* exp_stmt: exp SEMI  */
#line 332 "src/parser.y"
                               { (yyval.tree_node) = (yyvsp[-1].tree_node); }
#line 2273 "src/parser.tab.c"
    break;

  case 64: /* exp_stmt: SEMI  */
#line 333 "src/parser.y"
                           { (yyval.tree_node) = NULL; }
#line 2279 "src/parser.tab.c"
    break;

  case 65: /* exp_stmt: error SEMI  */
#line 334 "src/parser.y"
                                 { (yyval.tree_node) = NULL; yyerrok; }
#line 2285 "src/parser.tab.c"
    break;

  case 66: /* compound_stmt: LBRACE local_decls stmt_list RBRACE  */
#line 337 "src/parser.y"
                                                          {
                        TreeNode * t = newStmtNode(CompoundK);
                        t->lineno = (yyvsp[-3].token_data)->line_num;   /* set compound statement line number to that of when the '{' was scanned */
                        t->child[0] = (yyvsp[-2].tree_node);           /* local_decls */
                        t->child[1] = (yyvsp[-1].tree_node);           /* stmt_list */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                        yyerrok;
                    }
#line 2298 "src/parser.tab.c"
    break;

  case 67: /* local_decls: local_decls scoped_var_decl  */
#line 347 "src/parser.y"
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
#line 2316 "src/parser.tab.c"
    break;

  case 68: /* local_decls: %empty  */
#line 360 "src/parser.y"
                      {(yyval.tree_node) = NULL; }
#line 2322 "src/parser.tab.c"
    break;

  case 69: /* stmt_list: stmt_list stmt  */
#line 363 "src/parser.y"
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
#line 2340 "src/parser.tab.c"
    break;

  case 70: /* stmt_list: %empty  */
#line 376 "src/parser.y"
                      { (yyval.tree_node) = NULL; }
#line 2346 "src/parser.tab.c"
    break;

  case 71: /* matched_iter_stmt: WHILE simple_exp DO matched_stmt  */
#line 380 "src/parser.y"
                                                       {
                        TreeNode * t = newStmtNode(WhileK);
                        t->child[0] = (yyvsp[-2].tree_node);   /* simple_exp */
                        t->child[1] = (yyvsp[0].tree_node);   /* matched_stmt */
                        
                        if (t->child[1] != NULL) {
                            t->child[1]->isLoop = true;
                        }

                        if ((yyvsp[-2].tree_node) != NULL) {
                            t->lineno = (yyvsp[-2].tree_node)->lineno;  /* set while loop line number to that of when the simple_exp was scanned */
                        }

                        if ((yyvsp[0].tree_node) != NULL) {
                            t->child[1]->param_sibling = t->child[0]; /* set param_sibling of compound_stmt to params for scoping purposes during semantic analysis */
                        }

                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 2370 "src/parser.tab.c"
    break;

  case 72: /* matched_iter_stmt: FOR ID ASGN iter_range DO matched_stmt  */
#line 399 "src/parser.y"
                                                             {
                        TreeNode * t = newStmtNode(ForK);
                        TreeNode * init = newDeclNode(VarK);
                        init->isInitialized = true;      /* loop variable is initialized by the iter_range */
                        init->attr.name = (yyvsp[-4].token_data)->svalue;    /* ID name comes from token_data_t svalue member */
                        init->type = Integer;
                        init->var_kind = Local;
                        init->dataword_size = 1;
                        t->var_kind = None;
                        t->child[0] = init;              /* loop variable ID and iter_range become siblings */
                        t->child[1] = (yyvsp[-2].tree_node);                /* iter_range */
                        t->child[2] = (yyvsp[0].tree_node);                /* matched_stmt becomes the first child of the iter_range child */
                        if (t->child[2] != NULL) {
                            t->child[2]->isLoop = true;
                        }

                        if ((yyvsp[0].tree_node) != NULL) {
                            t->child[2]->param_sibling = t->child[0]; /* set param_sibling of compound_stmt to params for scoping purposes during semantic analysis */
                        }
                        
                        t->lineno = (yyvsp[-5].token_data)->line_num;          /* set for loop line number to that of when the iter_range was scanned */
                        init->lineno = (yyvsp[-4].token_data)->line_num;     /* set loop variable ID line number to that of when the iter_range was scanned */
                        (yyval.tree_node) = t;                          /* assign new TreeNode to left-hand side */
                    }
#line 2399 "src/parser.tab.c"
    break;

  case 73: /* matched_iter_stmt: WHILE error DO matched_stmt  */
#line 423 "src/parser.y"
                                                            { (yyval.tree_node) = NULL; yyerrok; }
#line 2405 "src/parser.tab.c"
    break;

  case 74: /* matched_iter_stmt: WHILE error  */
#line 424 "src/parser.y"
                                                            { (yyval.tree_node) = NULL; }
#line 2411 "src/parser.tab.c"
    break;

  case 75: /* matched_iter_stmt: FOR ID ASGN error DO matched_stmt  */
#line 425 "src/parser.y"
                                                            { (yyval.tree_node) = NULL; yyerrok; }
#line 2417 "src/parser.tab.c"
    break;

  case 76: /* matched_iter_stmt: FOR error  */
#line 426 "src/parser.y"
                                                            { (yyval.tree_node) = NULL; }
#line 2423 "src/parser.tab.c"
    break;

  case 77: /* unmatched_iter_stmt: WHILE simple_exp DO unmatched_stmt  */
#line 429 "src/parser.y"
                                                         {
                        TreeNode * t = newStmtNode(WhileK);
                        t->child[0] = (yyvsp[-2].tree_node);   /* simple_exp */
                        t->child[1] = (yyvsp[0].tree_node);   /* unmatched_stmt */
                        t->lineno = (yyvsp[-3].token_data)->line_num;  /* set while loop line number to that of when the simple_exp was scanned */
                        
                        if ((yyvsp[-2].tree_node) != NULL) {
                            t->lineno = (yyvsp[-2].tree_node)->lineno;  /* set while loop line number to that of when the simple_exp was scanned */
                        }

                        if (t->child[1] != NULL) {
                            t->child[1]->isLoop = true;
                        }

                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 2444 "src/parser.tab.c"
    break;

  case 78: /* unmatched_iter_stmt: FOR ID ASGN iter_range DO unmatched_stmt  */
#line 445 "src/parser.y"
                                                               {
                        TreeNode * t = newStmtNode(ForK);
                        TreeNode * init = newDeclNode(VarK);
                        init->isInitialized = true;      /* loop variable is initialized by the iter_range */
                        init->attr.name = (yyvsp[-4].token_data)->svalue;  /* ID name comes from token_data_t svalue member */
                        init->type = Integer;
                        init->var_kind = Local;
                        init->dataword_size = 1;

                        t->var_kind = None;
                        t->child[0] = init;            /* loop variable ID and iter_range become siblings */
                        t->child[1] = (yyvsp[-2].tree_node);                /* iter_range */
                        t->child[2] = (yyvsp[0].tree_node);                /* unmatched_stmt */
                        t->child[2]->param_sibling = t->child[0]; /* set param_sibling of compound_stmt to params for scoping purposes during semantic analysis */
                        t->lineno = (yyvsp[-5].token_data)->line_num;          /* set for loop line number to that of when the iter_range was scanned */
                        init->lineno = (yyvsp[-4].token_data)->line_num;     /* set loop variable ID line number to that of when the iter_range was scanned */
                        
                        if (t->child[2] != NULL) {
                            t->child[2]->isLoop = true;
                        }

                        (yyval.tree_node) = t;                          /* assign new TreeNode to left-hand side */
                    }
#line 2472 "src/parser.tab.c"
    break;

  case 79: /* unmatched_iter_stmt: IF error THEN unmatched_stmt  */
#line 468 "src/parser.y"
                                                                        { (yyval.tree_node) = NULL; yyerrok; }
#line 2478 "src/parser.tab.c"
    break;

  case 80: /* unmatched_iter_stmt: IF error THEN matched_stmt ELSE unmatched_stmt  */
#line 469 "src/parser.y"
                                                                        { (yyval.tree_node) = NULL; yyerrok; }
#line 2484 "src/parser.tab.c"
    break;

  case 81: /* iter_range: simple_exp TO simple_exp  */
#line 472 "src/parser.y"
                                               {
                        TreeNode * t = newStmtNode(RangeK);
                        t->child[0] = (yyvsp[-2].tree_node);   /* start expression */
                        t->child[1] = (yyvsp[0].tree_node);   /* end expression */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 2495 "src/parser.tab.c"
    break;

  case 82: /* iter_range: simple_exp TO simple_exp BY simple_exp  */
#line 478 "src/parser.y"
                                                             {
                        TreeNode * t = newStmtNode(RangeK);
                        t->child[0] = (yyvsp[-4].tree_node);   /* start expression */
                        t->child[1] = (yyvsp[-2].tree_node);   /* end expression */
                        t->child[2] = (yyvsp[0].tree_node);   /* step expression */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 2507 "src/parser.tab.c"
    break;

  case 83: /* iter_range: simple_exp TO error  */
#line 485 "src/parser.y"
                                                        { (yyval.tree_node) = NULL; }
#line 2513 "src/parser.tab.c"
    break;

  case 84: /* iter_range: error BY error  */
#line 486 "src/parser.y"
                                                        { (yyval.tree_node) = NULL; yyerrok; }
#line 2519 "src/parser.tab.c"
    break;

  case 85: /* iter_range: simple_exp TO simple_exp BY error  */
#line 487 "src/parser.y"
                                                        { (yyval.tree_node) = NULL; }
#line 2525 "src/parser.tab.c"
    break;

  case 86: /* return_stmt: RETURN SEMI  */
#line 490 "src/parser.y"
                                  {
                        TreeNode * t = newStmtNode(ReturnK);
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 2534 "src/parser.tab.c"
    break;

  case 87: /* return_stmt: RETURN exp SEMI  */
#line 494 "src/parser.y"
                                      {
                        TreeNode * t = newStmtNode(ReturnK);
                        t->child[0] = (yyvsp[-1].tree_node);   /* exp */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                        yyerrok;
                    }
#line 2545 "src/parser.tab.c"
    break;

  case 88: /* return_stmt: RETURN error SEMI  */
#line 500 "src/parser.y"
                                        { (yyval.tree_node) = NULL; yyerrok; }
#line 2551 "src/parser.tab.c"
    break;

  case 89: /* break_stmt: BREAK SEMI  */
#line 503 "src/parser.y"
                                 {
                        TreeNode * t = newStmtNode(BreakK);
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 2560 "src/parser.tab.c"
    break;

  case 90: /* exp: mutable assign_op exp  */
#line 509 "src/parser.y"
                                            { 
                        TreeNode * t = newExpNode(AssignK);
                        t->child[0] = (yyvsp[-2].tree_node);   /* mutable */
                        t->child[1] = (yyvsp[0].tree_node);   /* exp */
                        t->attr.op = (yyvsp[-1].op);    /* assignment operator from assign_op */
                        
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 2573 "src/parser.tab.c"
    break;

  case 91: /* exp: mutable INC  */
#line 517 "src/parser.y"
                                  { 
                        TreeNode * t = newExpNode(AssignK);
                        t->child[0] = (yyvsp[-1].tree_node);   /* mutable */
                        t->attr.op = INC;   /* increment operator */
                        t->type = Integer;  /* set type to Integer for increment operator */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 2585 "src/parser.tab.c"
    break;

  case 92: /* exp: mutable DEC  */
#line 524 "src/parser.y"
                                  { 
                        TreeNode * t = newExpNode(AssignK);
                        t->child[0] = (yyvsp[-1].tree_node);   /* mutable */
                        t->attr.op = DEC;   /* decrement operator */
                        t->type = Integer;  /* set type to Integer for decrement operator */
                        (yyval.tree_node) = t;             /* assign new TreeNode to left-hand side */
                    }
#line 2597 "src/parser.tab.c"
    break;

  case 93: /* exp: simple_exp  */
#line 531 "src/parser.y"
                                 { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2603 "src/parser.tab.c"
    break;

  case 94: /* exp: error assign_op exp  */
#line 532 "src/parser.y"
                                                { (yyval.tree_node) = NULL; yyerrok; }
#line 2609 "src/parser.tab.c"
    break;

  case 95: /* exp: mutable assign_op error  */
#line 533 "src/parser.y"
                                                { (yyval.tree_node) = NULL; }
#line 2615 "src/parser.tab.c"
    break;

  case 96: /* exp: error DEC  */
#line 534 "src/parser.y"
                                                { (yyval.tree_node) = NULL; yyerrok; }
#line 2621 "src/parser.tab.c"
    break;

  case 97: /* exp: error INC  */
#line 535 "src/parser.y"
                                                { (yyval.tree_node) = NULL; yyerrok; }
#line 2627 "src/parser.tab.c"
    break;

  case 98: /* assign_op: ASGN  */
#line 538 "src/parser.y"
                             { (yyval.op) = ASGN; }
#line 2633 "src/parser.tab.c"
    break;

  case 99: /* assign_op: ADDASS  */
#line 539 "src/parser.y"
                             { (yyval.op) = ADDASS; }
#line 2639 "src/parser.tab.c"
    break;

  case 100: /* assign_op: SUBASS  */
#line 540 "src/parser.y"
                             { (yyval.op) = SUBASS; }
#line 2645 "src/parser.tab.c"
    break;

  case 101: /* assign_op: MULASS  */
#line 541 "src/parser.y"
                             { (yyval.op) = MULASS; }
#line 2651 "src/parser.tab.c"
    break;

  case 102: /* assign_op: DIVASS  */
#line 542 "src/parser.y"
                             { (yyval.op) = DIVASS; }
#line 2657 "src/parser.tab.c"
    break;

  case 103: /* simple_exp: simple_exp OR and_exp  */
#line 545 "src/parser.y"
                                            {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = OR;        /* OR operator */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->child[0] = (yyvsp[-2].tree_node);       /* left operand */
                        t->child[1] = (yyvsp[0].tree_node);       /* right operand */
                        (yyval.tree_node) = t;
                    }
#line 2670 "src/parser.tab.c"
    break;

  case 104: /* simple_exp: and_exp  */
#line 553 "src/parser.y"
                              { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2676 "src/parser.tab.c"
    break;

  case 105: /* simple_exp: simple_exp OR error  */
#line 554 "src/parser.y"
                                          { (yyval.tree_node) = NULL; }
#line 2682 "src/parser.tab.c"
    break;

  case 106: /* and_exp: and_exp AND unary_rel_exp  */
#line 557 "src/parser.y"
                                                {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = AND;       /* AND operator */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->child[0] = (yyvsp[-2].tree_node);       /* left operand */
                        t->child[1] = (yyvsp[0].tree_node);       /* right operand */
                        (yyval.tree_node) = t;
                    }
#line 2695 "src/parser.tab.c"
    break;

  case 107: /* and_exp: unary_rel_exp  */
#line 565 "src/parser.y"
                                    { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2701 "src/parser.tab.c"
    break;

  case 108: /* and_exp: and_exp AND error  */
#line 566 "src/parser.y"
                                        { (yyval.tree_node) = NULL; }
#line 2707 "src/parser.tab.c"
    break;

  case 109: /* unary_rel_exp: NOT unary_rel_exp  */
#line 569 "src/parser.y"
                                        {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = NOT;   /* NOT operator */
                        t->child[0] = (yyvsp[0].tree_node);   /* operand */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        (yyval.tree_node) = t;
                    }
#line 2719 "src/parser.tab.c"
    break;

  case 110: /* unary_rel_exp: rel_exp  */
#line 576 "src/parser.y"
                                        { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2725 "src/parser.tab.c"
    break;

  case 111: /* unary_rel_exp: NOT error  */
#line 577 "src/parser.y"
                                        { (yyval.tree_node) = NULL; }
#line 2731 "src/parser.tab.c"
    break;

  case 112: /* rel_exp: sum_exp rel_op sum_exp  */
#line 580 "src/parser.y"
                                             {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = (yyvsp[-1].op);        /* relational operator from rel_op */
                        t->child[0] = (yyvsp[-2].tree_node);       /* left operand */
                        t->child[1] = (yyvsp[0].tree_node);       /* right operand */
                        (yyval.tree_node) = t;
                    }
#line 2743 "src/parser.tab.c"
    break;

  case 113: /* rel_exp: sum_exp  */
#line 587 "src/parser.y"
                              { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2749 "src/parser.tab.c"
    break;

  case 114: /* rel_op: LT  */
#line 590 "src/parser.y"
                            { (yyval.op) = LT; }
#line 2755 "src/parser.tab.c"
    break;

  case 115: /* rel_op: LEQ  */
#line 591 "src/parser.y"
                            { (yyval.op) = LEQ; }
#line 2761 "src/parser.tab.c"
    break;

  case 116: /* rel_op: GT  */
#line 592 "src/parser.y"
                            { (yyval.op) = GT; }
#line 2767 "src/parser.tab.c"
    break;

  case 117: /* rel_op: GEQ  */
#line 593 "src/parser.y"
                            { (yyval.op) = GEQ; }
#line 2773 "src/parser.tab.c"
    break;

  case 118: /* rel_op: EQ  */
#line 594 "src/parser.y"
                            { (yyval.op) = EQ; }
#line 2779 "src/parser.tab.c"
    break;

  case 119: /* rel_op: NEQ  */
#line 595 "src/parser.y"
                            { (yyval.op) = NEQ; }
#line 2785 "src/parser.tab.c"
    break;

  case 120: /* sum_exp: sum_exp sum_op mul_exp  */
#line 598 "src/parser.y"
                                             {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = (yyvsp[-1].op);        /* sum operator from sum_op */
                        t->type = UndefinedType;
                        t->child[0] = (yyvsp[-2].tree_node);       /* left operand */
                        t->child[1] = (yyvsp[0].tree_node);       /* right operand */
                        (yyval.tree_node) = t;
                    }
#line 2798 "src/parser.tab.c"
    break;

  case 121: /* sum_exp: mul_exp  */
#line 606 "src/parser.y"
                              { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2804 "src/parser.tab.c"
    break;

  case 122: /* sum_exp: sum_exp sum_op error  */
#line 607 "src/parser.y"
                                           { (yyval.tree_node) = NULL; }
#line 2810 "src/parser.tab.c"
    break;

  case 123: /* sum_op: PLUS  */
#line 610 "src/parser.y"
                           { (yyval.op) = PLUS; }
#line 2816 "src/parser.tab.c"
    break;

  case 124: /* sum_op: MINUS  */
#line 611 "src/parser.y"
                            { (yyval.op) = MINUS; }
#line 2822 "src/parser.tab.c"
    break;

  case 125: /* mul_exp: mul_exp mul_op unary_exp  */
#line 614 "src/parser.y"
                                               {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = (yyvsp[-1].op);            /* multiplication operator from mul_op */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        t->child[0] = (yyvsp[-2].tree_node);           /* left operand */
                        t->child[1] = (yyvsp[0].tree_node);           /* right operand */
                        (yyval.tree_node) = t;
                    }
#line 2835 "src/parser.tab.c"
    break;

  case 126: /* mul_exp: unary_exp  */
#line 622 "src/parser.y"
                                { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2841 "src/parser.tab.c"
    break;

  case 127: /* mul_exp: mul_exp mul_op error  */
#line 623 "src/parser.y"
                                           { (yyval.tree_node) = NULL; }
#line 2847 "src/parser.tab.c"
    break;

  case 128: /* mul_op: TIMES  */
#line 626 "src/parser.y"
                            { (yyval.op) = TIMES; }
#line 2853 "src/parser.tab.c"
    break;

  case 129: /* mul_op: DIV  */
#line 627 "src/parser.y"
                            { (yyval.op) = DIV; }
#line 2859 "src/parser.tab.c"
    break;

  case 130: /* mul_op: MOD  */
#line 628 "src/parser.y"
                            { (yyval.op) = MOD; }
#line 2865 "src/parser.tab.c"
    break;

  case 131: /* unary_exp: unary_op unary_exp  */
#line 631 "src/parser.y"
                                         {
                        TreeNode * t = newExpNode(OpK);
                        t->attr.op = (yyvsp[-1].op);            /* unary operator from unary_op */
                        t->type = UndefinedType;
                        t->child[0] = NULL;         /* unary operator has no left operand */
                        t->child[1] = (yyvsp[0].tree_node);           /* operand */
                        (yyval.tree_node) = t;
                    }
#line 2878 "src/parser.tab.c"
    break;

  case 132: /* unary_exp: factor  */
#line 639 "src/parser.y"
                             { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2884 "src/parser.tab.c"
    break;

  case 133: /* unary_exp: unary_op error  */
#line 640 "src/parser.y"
                                     { (yyval.tree_node) = NULL; }
#line 2890 "src/parser.tab.c"
    break;

  case 134: /* unary_op: MINUS  */
#line 643 "src/parser.y"
                                { (yyval.op) = CHSIGN; }
#line 2896 "src/parser.tab.c"
    break;

  case 135: /* unary_op: TIMES  */
#line 644 "src/parser.y"
                                { (yyval.op) = SIZEOF; }
#line 2902 "src/parser.tab.c"
    break;

  case 136: /* unary_op: TERNARY  */
#line 645 "src/parser.y"
                                { (yyval.op) = TERNARY; }
#line 2908 "src/parser.tab.c"
    break;

  case 137: /* factor: mutable  */
#line 648 "src/parser.y"
                                { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2914 "src/parser.tab.c"
    break;

  case 138: /* factor: immutable  */
#line 649 "src/parser.y"
                                { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2920 "src/parser.tab.c"
    break;

  case 139: /* mutable: ID LBRACKET exp RBRACKET  */
#line 652 "src/parser.y"
                                               {
                        TreeNode * t = newExpNode(OpK);
                        TreeNode * id = newExpNode(IdK);    /* create tree_node for first child */
                        id->attr.name = (yyvsp[-3].token_data)->svalue;     /* ID name comes from token_data_t svalue member */
                        t->attr.op = LBRACKET;          /* array access operator */
                        t->child[0] = id;               
                        t->child[1] = (yyvsp[-1].tree_node);               /* index expression */
                        t->type = UndefinedType;             /* set type to that of the lhs */
                        (yyval.tree_node) = t;                         /* assign new TreeNode to left-hand side */
                    }
#line 2935 "src/parser.tab.c"
    break;

  case 140: /* mutable: ID  */
#line 662 "src/parser.y"
                         {
                        TreeNode * t = newExpNode(IdK);
                        t->attr.name = (yyvsp[0].token_data)->svalue;  /* ID name comes from token_data_t svalue member */
                        t->type = UndefinedType;    /* set type to UndefinedType for now, will be set during semantic analysis */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 2946 "src/parser.tab.c"
    break;

  case 141: /* immutable: LPAREN exp RPAREN  */
#line 670 "src/parser.y"
                                        { (yyval.tree_node) = (yyvsp[-1].tree_node); yyerrok; }
#line 2952 "src/parser.tab.c"
    break;

  case 142: /* immutable: call  */
#line 671 "src/parser.y"
                           { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2958 "src/parser.tab.c"
    break;

  case 143: /* immutable: constant  */
#line 672 "src/parser.y"
                               { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2964 "src/parser.tab.c"
    break;

  case 144: /* immutable: LPAREN error  */
#line 673 "src/parser.y"
                                   { (yyval.tree_node) = NULL; }
#line 2970 "src/parser.tab.c"
    break;

  case 145: /* call: ID LPAREN args RPAREN  */
#line 676 "src/parser.y"
                                            {
                        TreeNode * t = newExpNode(CallK);
                        t->attr.name = (yyvsp[-3].token_data)->svalue;  /* ID name comes from token_data_t svalue member */
                        t->child[0] = (yyvsp[-1].tree_node);           /* args */
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 2981 "src/parser.tab.c"
    break;

  case 146: /* call: error LPAREN  */
#line 682 "src/parser.y"
                                            { (yyval.tree_node) = NULL; yyerrok; }
#line 2987 "src/parser.tab.c"
    break;

  case 147: /* args: arg_list  */
#line 685 "src/parser.y"
                               { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 2993 "src/parser.tab.c"
    break;

  case 148: /* args: %empty  */
#line 686 "src/parser.y"
                      { (yyval.tree_node) = NULL; }
#line 2999 "src/parser.tab.c"
    break;

  case 149: /* arg_list: arg_list COMMA exp  */
#line 689 "src/parser.y"
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
                        yyerrok;
                    }
#line 3018 "src/parser.tab.c"
    break;

  case 150: /* arg_list: exp  */
#line 703 "src/parser.y"
                          { (yyval.tree_node) = (yyvsp[0].tree_node); }
#line 3024 "src/parser.tab.c"
    break;

  case 151: /* arg_list: arg_list COMMA error  */
#line 704 "src/parser.y"
                                           { (yyval.tree_node) = NULL; }
#line 3030 "src/parser.tab.c"
    break;

  case 152: /* constant: NUMBERCONST  */
#line 707 "src/parser.y"
                                  {
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Integer;          /* set type to Integer */
                        t->attr.value = (yyvsp[0].token_data)->nvalue; /* value from token_data_t nvalue member */
                        t->isConstant = true;
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 3042 "src/parser.tab.c"
    break;

  case 153: /* constant: CHARCONST  */
#line 714 "src/parser.y"
                                {
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Char;             /* set type to Char */
                        t->attr.cvalue = (yyvsp[0].token_data)->cvalue; /* value from token_data_t cvalue member */
                        t->isConstant = true;
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 3054 "src/parser.tab.c"
    break;

  case 154: /* constant: STRINGCONST  */
#line 721 "src/parser.y"
                                  {
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Char;                 /* set type to String */
                        t->isArray = true;            /* mark as array to represent string */
                        t->attr.string = (yyvsp[0].token_data)->svalue;    /* string from token_data_t svalue member */
                        t->isConstant = true;
                        (yyval.tree_node) = t;                         /* assign new TreeNode to left-hand side */
                    }
#line 3067 "src/parser.tab.c"
    break;

  case 155: /* constant: TRUE  */
#line 729 "src/parser.y"
                           { 
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Boolean;          /* set type to Boolean */
                        t->attr.value = 1;          /* TRUE represented as 1 */
                        t->isConstant = true;
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 3079 "src/parser.tab.c"
    break;

  case 156: /* constant: FALSE  */
#line 736 "src/parser.y"
                            { 
                        TreeNode * t = newExpNode(ConstantK);
                        t->type = Boolean;          /* set type to Boolean */
                        t->attr.value = 0;          /* FALSE represented as 0 */
                        t->isConstant = true;
                        (yyval.tree_node) = t;                     /* assign new TreeNode to left-hand side */
                    }
#line 3091 "src/parser.tab.c"
    break;


#line 3095 "src/parser.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 745 "src/parser.y"


extern int yydebug;
int main(int argc, char *argv[])
{
    char opt;
    char *optstring = "pdPDM"; // Options: a, b (requires an argument), c (requires an argument)
    int printTreeFlag = 0;
    int printTreeTypeFlag = 0;
    int symbolDebugFlag = 0;
    int printTreeMemoryFlag = 0;
    int args = 0;
    char *file_name;
    
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
            case 'M':
                printTreeMemoryFlag = 1;
                args++;
                break;
            case '?':
                fprintf(stderr, "Unknown option -%c.\n", optopt);
                break;
        }
    }
    
    num_errors = 0;
    num_warnings = 0;

    initErrorProcessing();

    if (argc-args > 1) {
        if ((yyin = fopen(argv[argc - 1], "r"))) {
            file_name = argv[1];

            // file open successful
        }
        else {
            // failed to open fie
            printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[argc - 1]);
            
            num_errors++;
            printf("Number of warnings: %d\n", num_warnings);
            printf("Number of errors: %d\n", num_errors);
            return 1;
        }
    }

    /* Parse */
    yyparse();

    if (syntax_errors == false) {
        symbol_table = new SymbolTable();              /* Create the symbol table */ 
    
        io_library_ast = init_io_library_ast();                     /* Initialize the I/O library AST and populate the symbol table with I/O functions */
    
        semantic_analysis(io_library_ast, symbol_table);            /* Perform semantic analysis on the I/O library AST to populate the symbol table with this libraries function decls */

        /* This also default enters us into the Global scope */
        if (symbolDebugFlag) {
            symbol_table->debug(true);                              /* Enable debug mode for the symbol table */
        }

        semantic_analysis(syntaxTree, symbol_table);                /* Perform semantic analysis and build the symbol table */
            
        /* Check for unused functions in the global scope */
        symbol_table->applyToAll(check_if_used);

        print_all_found_errors();

        TreeNode * main_func_node = (TreeNode *) symbol_table->lookupGlobal("main");
    
        if (main_func_node != NULL) {
            if (main_func_node->nodekind == DeclK && main_func_node->subkind.decl == FuncK) {    
                /* Main function found, can't have params */
                if (main_func_node->child[0] != NULL) {
                    printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
                    num_errors++;
                }
            }
            else {
                printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
                num_errors++;
            }
        }
        else {
            printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
            num_errors++;
        }
    }
    
    if (num_errors == 0 && syntax_errors == false) {
        if (printTreeFlag) {
            printTree(syntaxTree, false, false); /* Print the syntax tree */
        }

        if (printTreeTypeFlag) {
            printTree(syntaxTree, true, false); /* Print the syntax tree with types no memory usage*/
        }

        if (printTreeMemoryFlag) {
            printTree(io_library_ast, true, true); /* Print the I/O library syntax tree memory usage and types */
            printTree(syntaxTree, true, true); /* Print the syntax tree memory usage and types */
        }

        if (!printTreeFlag && !printTreeTypeFlag && !printTreeMemoryFlag) {
            code_generation_linearized_list_head = initialize_code_generation_list(syntaxTree);
            
            linearize_ast(syntaxTree, symbol_table);
            append_linearized_node(NULL, CG_InitEnter, current_head);
            append_linearized_node(NULL, CG_GlobalsEnter, current_head);
            append_globals_on_current_head();
            append_linearized_node(NULL, CG_GlobalsLeave, current_head);
            append_linearized_node(NULL, CG_InitLeave, current_head);
            //generate_init_enter(syntaxTree, symbol_table);

            //generate_globals_statics_enter(syntaxTree, symbol_table);
            //generate_globals_statics_leave(syntaxTree, symbol_table);

            //generate_init_leave(syntaxTree, symbol_table);

            init_code_file(file_name);
            generate_code(code_generation_linearized_list_head, symbol_table);
        }

        print_goffset();
    }


    printf("Number of warnings: %d\n", num_warnings);
    printf("Number of errors: %d\n", num_errors);   
    
    return 0;
}

/*


*/
