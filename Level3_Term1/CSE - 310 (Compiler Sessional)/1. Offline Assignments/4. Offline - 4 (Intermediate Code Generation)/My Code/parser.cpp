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
#line 1 "2005076.y"

#include <sstream>
#include "2005076_parserFunctions.cpp"

int yyparse(void);
int yylex(void);
extern FILE* yyin;

ofstream assem_code;
int stack_offset;

void syntax_error(string error){
	log_out<<"Error at line : " << line_number <<" : "<< "syntax error\n";
}

// void yyerror(char *s)
// {
// 	//write your code
// }

void yyerror(const string& s) {
	syntaxError_line = line_number;
	log_out<< "Error at line no " << syntaxError_line << " : syntax error\n";
}
string stored_fReturnType;
string current_function;

SymbolInfo* function_params = new SymbolInfo();




#line 104 "parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_RETURN = 7,                     /* RETURN  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_FLOAT = 9,                      /* FLOAT  */
  YYSYMBOL_VOID = 10,                      /* VOID  */
  YYSYMBOL_CONST_INT = 11,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 12,               /* CONST_FLOAT  */
  YYSYMBOL_ADDOP = 13,                     /* ADDOP  */
  YYSYMBOL_RELOP = 14,                     /* RELOP  */
  YYSYMBOL_ASSIGNOP = 15,                  /* ASSIGNOP  */
  YYSYMBOL_INCOP = 16,                     /* INCOP  */
  YYSYMBOL_MULOP = 17,                     /* MULOP  */
  YYSYMBOL_LOGICOP = 18,                   /* LOGICOP  */
  YYSYMBOL_DECOP = 19,                     /* DECOP  */
  YYSYMBOL_NOT = 20,                       /* NOT  */
  YYSYMBOL_LPAREN = 21,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 22,                    /* RPAREN  */
  YYSYMBOL_LCURL = 23,                     /* LCURL  */
  YYSYMBOL_RCURL = 24,                     /* RCURL  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 26,                 /* SEMICOLON  */
  YYSYMBOL_LTHIRD = 27,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 28,                    /* RTHIRD  */
  YYSYMBOL_ID = 29,                        /* ID  */
  YYSYMBOL_PRINTLN = 30,                   /* PRINTLN  */
  YYSYMBOL_LOWER_THAN_ELSE = 31,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_start = 33,                     /* start  */
  YYSYMBOL_program = 34,                   /* program  */
  YYSYMBOL_unit = 35,                      /* unit  */
  YYSYMBOL_func_declaration = 36,          /* func_declaration  */
  YYSYMBOL_func_definition = 37,           /* func_definition  */
  YYSYMBOL_38_1 = 38,                      /* $@1  */
  YYSYMBOL_39_2 = 39,                      /* $@2  */
  YYSYMBOL_parameter_list = 40,            /* parameter_list  */
  YYSYMBOL_compound_statement = 41,        /* compound_statement  */
  YYSYMBOL_var_declaration = 42,           /* var_declaration  */
  YYSYMBOL_type_specifier = 43,            /* type_specifier  */
  YYSYMBOL_declaration_list = 44,          /* declaration_list  */
  YYSYMBOL_statements = 45,                /* statements  */
  YYSYMBOL_statement = 46,                 /* statement  */
  YYSYMBOL_expression_statement = 47,      /* expression_statement  */
  YYSYMBOL_variable = 48,                  /* variable  */
  YYSYMBOL_expression = 49,                /* expression  */
  YYSYMBOL_logic_expression = 50,          /* logic_expression  */
  YYSYMBOL_rel_expression = 51,            /* rel_expression  */
  YYSYMBOL_simple_expression = 52,         /* simple_expression  */
  YYSYMBOL_term = 53,                      /* term  */
  YYSYMBOL_unary_expression = 54,          /* unary_expression  */
  YYSYMBOL_factor = 55,                    /* factor  */
  YYSYMBOL_argument_list = 56,             /* argument_list  */
  YYSYMBOL_arguments = 57,                 /* arguments  */
  YYSYMBOL_left_curl = 58                  /* left_curl  */
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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   170

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    62,    62,    78,    85,    95,   101,   107,   113,   121,
     131,   144,   144,   164,   164,   186,   205,   221,   236,   254,
     266,   280,   316,   323,   330,   341,   351,   368,   376,   395,
     401,   410,   417,   424,   431,   438,   445,   452,   459,   470,
     481,   487,   497,   512,   532,   540,   550,   559,   577,   586,
     597,   606,   620,   629,   672,   686,   702,   714,   723,   734,
     742,   749,   756,   773,   794,   803,   812,   825,   839
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "FOR",
  "WHILE", "RETURN", "INT", "FLOAT", "VOID", "CONST_INT", "CONST_FLOAT",
  "ADDOP", "RELOP", "ASSIGNOP", "INCOP", "MULOP", "LOGICOP", "DECOP",
  "NOT", "LPAREN", "RPAREN", "LCURL", "RCURL", "COMMA", "SEMICOLON",
  "LTHIRD", "RTHIRD", "ID", "PRINTLN", "LOWER_THAN_ELSE", "$accept",
  "start", "program", "unit", "func_declaration", "func_definition", "$@1",
  "$@2", "parameter_list", "compound_statement", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", "left_curl", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-76)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      54,   -76,   -76,   -76,   -76,    18,    51,   -76,   -76,   -76,
     -76,    -3,   -76,   -76,     7,    32,    15,    25,    19,   -76,
      27,    24,    61,    52,    66,   -76,    69,    71,    99,   -76,
     -76,   100,   -76,   -76,    65,   -76,    69,    83,    82,    94,
      97,   104,     1,   -76,   -76,     1,     1,     1,   -76,   -76,
      20,   114,   -76,   -76,    91,    93,   -76,   -76,     0,    95,
     -76,   118,    70,   120,   -76,   -76,   -76,   -76,   -76,     1,
     141,     1,   112,    63,   -76,   -76,   117,     1,     1,   111,
     116,   -76,   -76,     1,   -76,   -76,   -76,     1,     1,     1,
       1,   123,   141,   124,   -76,   -76,   -76,   126,   130,   128,
     127,   -76,   -76,   120,   144,   -76,   121,     1,   121,   -76,
       1,   -76,   132,   155,   138,   -76,   -76,   -76,   121,   121,
     -76,   -76
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     8,    22,    23,    24,     0,     0,     4,     6,     7,
       5,     0,     1,     3,    27,     0,     0,     0,     0,    21,
      13,     0,    18,     0,    25,    10,     0,    11,     0,    17,
      28,     0,    68,    14,     0,     9,     0,    16,     0,     0,
       0,     0,     0,    60,    61,     0,     0,     0,    20,    40,
      42,     0,    33,    31,     0,     0,    29,    32,    57,     0,
      44,    46,    48,    50,    52,    56,    12,    15,    26,     0,
       0,     0,     0,    57,    54,    55,     0,    65,     0,     0,
      27,    19,    30,     0,    62,    63,    41,     0,     0,     0,
       0,     0,     0,     0,    39,    59,    67,     0,    64,     0,
       0,    45,    47,    51,    49,    53,     0,     0,     0,    58,
       0,    43,     0,    35,     0,    37,    66,    38,     0,     0,
      36,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   -76,   157,   -76,   -76,   -76,   -76,   -76,   -16,
      81,    11,   -76,   -76,   -52,   -63,   -45,   -38,   -75,    77,
      76,    78,   -40,   -76,   -76,   -76,   -76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,     9,    36,    26,    21,    52,
      53,    54,    15,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    97,    98,    34
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      73,    73,    96,    82,    72,    74,    75,    92,   101,    76,
      33,    11,    43,    44,    45,    83,    84,    11,    12,    85,
      66,    46,    47,     2,     3,     4,    14,    22,    16,   107,
      50,    91,    73,    93,    17,   116,    23,    20,    73,    37,
      99,    77,    73,    73,    73,    73,    27,    78,    24,    28,
     105,    -2,     1,    25,   113,     1,   115,    18,    19,     2,
       3,     4,     2,     3,     4,    73,   120,   121,    39,   114,
      40,    41,    42,     2,     3,     4,    43,    44,    45,    84,
      30,    10,    85,    88,    89,    46,    47,    10,    32,    48,
      29,    49,    32,    31,    50,    51,    39,    35,    40,    41,
      42,     2,     3,     4,    43,    44,    45,     2,     3,     4,
      68,    38,    67,    46,    47,    69,    32,    81,    70,    49,
      80,    86,    50,    51,    39,    71,    40,    41,    42,     2,
       3,     4,    43,    44,    45,    79,    87,    90,    94,    95,
     100,    46,    47,    17,    32,   106,   108,    49,   109,   112,
      50,    51,    43,    44,    45,   110,   111,    88,   117,   118,
     119,    46,    47,    13,   102,   104,   103,    49,     0,     0,
      50
};

static const yytype_int8 yycheck[] =
{
      45,    46,    77,    55,    42,    45,    46,    70,    83,    47,
      26,     0,    11,    12,    13,    15,    16,     6,     0,    19,
      36,    20,    21,     8,     9,    10,    29,    16,    21,    92,
      29,    69,    77,    71,    27,   110,    11,    22,    83,    28,
      78,    21,    87,    88,    89,    90,    22,    27,    29,    25,
      90,     0,     1,    26,   106,     1,   108,    25,    26,     8,
       9,    10,     8,     9,    10,   110,   118,   119,     3,   107,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    16,
      28,     0,    19,    13,    14,    20,    21,     6,    23,    24,
      29,    26,    23,    27,    29,    30,     3,    26,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     8,     9,    10,
      28,    11,    29,    20,    21,    21,    23,    24,    21,    26,
      29,    26,    29,    30,     3,    21,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    21,    18,    17,    26,    22,
      29,    20,    21,    27,    23,    22,    22,    26,    22,    22,
      29,    30,    11,    12,    13,    25,    28,    13,    26,     4,
      22,    20,    21,     6,    87,    89,    88,    26,    -1,    -1,
      29
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     8,     9,    10,    33,    34,    35,    36,    37,
      42,    43,     0,    35,    29,    44,    21,    27,    25,    26,
      22,    40,    43,    11,    29,    26,    39,    22,    25,    29,
      28,    27,    23,    41,    58,    26,    38,    43,    11,     3,
       5,     6,     7,    11,    12,    13,    20,    21,    24,    26,
      29,    30,    41,    42,    43,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    41,    29,    28,    21,
      21,    21,    49,    48,    54,    54,    49,    21,    27,    21,
      29,    24,    46,    15,    16,    19,    26,    18,    13,    14,
      17,    49,    47,    49,    26,    22,    50,    56,    57,    49,
      29,    50,    51,    53,    52,    54,    22,    47,    22,    22,
      25,    28,    22,    46,    49,    46,    50,    26,     4,    22,
      46,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    36,
      36,    38,    37,    39,    37,    40,    40,    40,    40,    41,
      41,    42,    43,    43,    43,    44,    44,    44,    44,    45,
      45,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      47,    47,    48,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    53,    53,    54,    54,    54,    55,    55,    55,
      55,    55,    55,    55,    56,    56,    57,    57,    58
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     6,
       5,     0,     7,     0,     6,     4,     3,     2,     1,     3,
       2,     3,     1,     1,     1,     3,     6,     1,     4,     1,
       2,     1,     1,     1,     7,     5,     7,     5,     5,     3,
       1,     2,     1,     4,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     2,     2,     1,     1,     4,     3,
       1,     1,     2,     2,     1,     0,     3,     1,     1
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
  switch (yykind)
    {
    case YYSYMBOL_IF: /* IF  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 982 "parser.cpp"
        break;

    case YYSYMBOL_ELSE: /* ELSE  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 991 "parser.cpp"
        break;

    case YYSYMBOL_FOR: /* FOR  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1000 "parser.cpp"
        break;

    case YYSYMBOL_WHILE: /* WHILE  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1009 "parser.cpp"
        break;

    case YYSYMBOL_RETURN: /* RETURN  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1018 "parser.cpp"
        break;

    case YYSYMBOL_INT: /* INT  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1027 "parser.cpp"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1036 "parser.cpp"
        break;

    case YYSYMBOL_VOID: /* VOID  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1045 "parser.cpp"
        break;

    case YYSYMBOL_CONST_INT: /* CONST_INT  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1054 "parser.cpp"
        break;

    case YYSYMBOL_CONST_FLOAT: /* CONST_FLOAT  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1063 "parser.cpp"
        break;

    case YYSYMBOL_ADDOP: /* ADDOP  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1072 "parser.cpp"
        break;

    case YYSYMBOL_RELOP: /* RELOP  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1081 "parser.cpp"
        break;

    case YYSYMBOL_ASSIGNOP: /* ASSIGNOP  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1090 "parser.cpp"
        break;

    case YYSYMBOL_INCOP: /* INCOP  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1099 "parser.cpp"
        break;

    case YYSYMBOL_MULOP: /* MULOP  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1108 "parser.cpp"
        break;

    case YYSYMBOL_LOGICOP: /* LOGICOP  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1117 "parser.cpp"
        break;

    case YYSYMBOL_DECOP: /* DECOP  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1126 "parser.cpp"
        break;

    case YYSYMBOL_NOT: /* NOT  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1135 "parser.cpp"
        break;

    case YYSYMBOL_LPAREN: /* LPAREN  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1144 "parser.cpp"
        break;

    case YYSYMBOL_RPAREN: /* RPAREN  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1153 "parser.cpp"
        break;

    case YYSYMBOL_LCURL: /* LCURL  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1162 "parser.cpp"
        break;

    case YYSYMBOL_RCURL: /* RCURL  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1171 "parser.cpp"
        break;

    case YYSYMBOL_COMMA: /* COMMA  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1180 "parser.cpp"
        break;

    case YYSYMBOL_SEMICOLON: /* SEMICOLON  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1189 "parser.cpp"
        break;

    case YYSYMBOL_LTHIRD: /* LTHIRD  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1198 "parser.cpp"
        break;

    case YYSYMBOL_RTHIRD: /* RTHIRD  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1207 "parser.cpp"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1216 "parser.cpp"
        break;

    case YYSYMBOL_PRINTLN: /* PRINTLN  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1225 "parser.cpp"
        break;

    case YYSYMBOL_start: /* start  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1234 "parser.cpp"
        break;

    case YYSYMBOL_program: /* program  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1243 "parser.cpp"
        break;

    case YYSYMBOL_unit: /* unit  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1252 "parser.cpp"
        break;

    case YYSYMBOL_func_declaration: /* func_declaration  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1261 "parser.cpp"
        break;

    case YYSYMBOL_func_definition: /* func_definition  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1270 "parser.cpp"
        break;

    case YYSYMBOL_parameter_list: /* parameter_list  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1279 "parser.cpp"
        break;

    case YYSYMBOL_compound_statement: /* compound_statement  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1288 "parser.cpp"
        break;

    case YYSYMBOL_var_declaration: /* var_declaration  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1297 "parser.cpp"
        break;

    case YYSYMBOL_type_specifier: /* type_specifier  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1306 "parser.cpp"
        break;

    case YYSYMBOL_declaration_list: /* declaration_list  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1315 "parser.cpp"
        break;

    case YYSYMBOL_statements: /* statements  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1324 "parser.cpp"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1333 "parser.cpp"
        break;

    case YYSYMBOL_expression_statement: /* expression_statement  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1342 "parser.cpp"
        break;

    case YYSYMBOL_variable: /* variable  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1351 "parser.cpp"
        break;

    case YYSYMBOL_expression: /* expression  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1360 "parser.cpp"
        break;

    case YYSYMBOL_logic_expression: /* logic_expression  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1369 "parser.cpp"
        break;

    case YYSYMBOL_rel_expression: /* rel_expression  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1378 "parser.cpp"
        break;

    case YYSYMBOL_simple_expression: /* simple_expression  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1387 "parser.cpp"
        break;

    case YYSYMBOL_term: /* term  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1396 "parser.cpp"
        break;

    case YYSYMBOL_unary_expression: /* unary_expression  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1405 "parser.cpp"
        break;

    case YYSYMBOL_factor: /* factor  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1414 "parser.cpp"
        break;

    case YYSYMBOL_argument_list: /* argument_list  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1423 "parser.cpp"
        break;

    case YYSYMBOL_arguments: /* arguments  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1432 "parser.cpp"
        break;

    case YYSYMBOL_left_curl: /* left_curl  */
#line 40 "2005076.y"
           {
	free_symbol(((*yyvaluep).symbolInfo));
	//cout<<$$->getName() + " deleted in y file\n";
}
#line 1441 "parser.cpp"
        break;

      default:
        break;
    }
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
  case 2: /* start: program  */
#line 63 "2005076.y"
        {
		//write your code in this block in all the similar blocks below
		log_CFG_rule("start", "program");
		(yyval.symbolInfo) = new SymbolInfo("start", "start");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "start : program";
		//$$->print_inParseTree(parseTree, 0);
		//free_symbol($$);

		traverse((yyval.symbolInfo));

		cout<<"after traverse\n";
	}
#line 1723 "parser.cpp"
    break;

  case 3: /* program: program unit  */
#line 78 "2005076.y"
                       {
		log_CFG_rule("program", "program unit");
		(yyval.symbolInfo) = new SymbolInfo("program", "program");
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo));
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "program : program unit";
	}
#line 1735 "parser.cpp"
    break;

  case 4: /* program: unit  */
#line 85 "2005076.y"
              {
		log_CFG_rule("program", "unit");
		(yyval.symbolInfo) = new SymbolInfo("program", "program");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "program : unit";
	}
#line 1746 "parser.cpp"
    break;

  case 5: /* unit: var_declaration  */
#line 95 "2005076.y"
                      {
		log_CFG_rule("unit", "var_declaration");
		(yyval.symbolInfo) = new SymbolInfo("unit", "unit");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "unit : var_declaration";
	}
#line 1757 "parser.cpp"
    break;

  case 6: /* unit: func_declaration  */
#line 101 "2005076.y"
                      {
		log_CFG_rule("unit", "func_declaration");
		(yyval.symbolInfo) = new SymbolInfo("unit", "unit");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "unit : func_declaration";
	}
#line 1768 "parser.cpp"
    break;

  case 7: /* unit: func_definition  */
#line 107 "2005076.y"
                     {
		log_CFG_rule("unit", "func_definition");
		(yyval.symbolInfo) = new SymbolInfo("unit", "unit");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "unit : func_definition";
	}
#line 1779 "parser.cpp"
    break;

  case 8: /* unit: error  */
#line 113 "2005076.y"
               {
		(yyval.symbolInfo) = new SymbolInfo("unit", "unit");
		cout<<"Error occured\n";
	}
#line 1788 "parser.cpp"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 121 "2005076.y"
                                                                           {
		log_CFG_rule("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		(yyval.symbolInfo) = new SymbolInfo("func_declaration1", "func_declaration");
		(yyval.symbolInfo)->add_branch((yyvsp[-5].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-4].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); 
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON";
		function_token((yyvsp[-4].symbolInfo)->getName(),"DECLARATION", (yyvsp[-5].symbolInfo)->getType(), (yyvsp[-2].symbolInfo)->parameter_list);
		stored_fParam.clear();

	}
#line 1803 "parser.cpp"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 131 "2005076.y"
                                                   {
		log_CFG_rule("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");
		(yyval.symbolInfo) = new SymbolInfo("func_declaration2", "func_declaration");
		(yyval.symbolInfo)->add_branch((yyvsp[-4].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); 
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON";
		function_token((yyvsp[-3].symbolInfo)->getName(),"DECLARATION", (yyvsp[-4].symbolInfo)->getType(), {});
		stored_fParam.clear();
	}
#line 1817 "parser.cpp"
    break;

  case 11: /* $@1: %empty  */
#line 144 "2005076.y"
                                                                 {
		stored_fReturnType = (yyvsp[-4].symbolInfo)->type_specifier;
		//function_token($2->getName(),"DEFINITION", $1->getType(), $4->parameter_list);
		(yyvsp[-3].symbolInfo)->type_specifier = (yyvsp[-4].symbolInfo)->type_specifier;
		(yyvsp[-3].symbolInfo)->parameter_list = function_params->parameter_list;
		(yyvsp[-3].symbolInfo)->is_function = true;
		current_function = (yyvsp[-3].symbolInfo)->getName();
		symbol_table->insert((yyvsp[-3].symbolInfo));

		stored_fParam.clear();
	}
#line 1833 "parser.cpp"
    break;

  case 12: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 155 "2005076.y"
                          {
		log_CFG_rule("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-5].symbolInfo)->getName(), "func_definition");
		(yyval.symbolInfo)->add_branch((yyvsp[-6].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-5].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-4].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); 
		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement";


	}
#line 1847 "parser.cpp"
    break;

  case 13: /* $@2: %empty  */
#line 164 "2005076.y"
                                          {
		stored_fReturnType = (yyvsp[-3].symbolInfo)->type_specifier;
		//function_token($2->getName(),"DEFINITION", $1->getType(), {});
		(yyvsp[-2].symbolInfo)->type_specifier = (yyvsp[-3].symbolInfo)->type_specifier;
		(yyvsp[-2].symbolInfo)->parameter_list = function_params->parameter_list;
		(yyvsp[-2].symbolInfo)->is_function = true;
		current_function = (yyvsp[-2].symbolInfo)->getName();
		symbol_table->insert((yyvsp[-2].symbolInfo));

		stored_fParam.clear();
	}
#line 1863 "parser.cpp"
    break;

  case 14: /* func_definition: type_specifier ID LPAREN RPAREN $@2 compound_statement  */
#line 175 "2005076.y"
                          {
		log_CFG_rule("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-4].symbolInfo)->getName(), "func_definition");
		(yyval.symbolInfo)->add_branch((yyvsp[-5].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-4].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); 
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "func_definition : type_specifier ID LPAREN RPAREN compound_statement";
	}
#line 1875 "parser.cpp"
    break;

  case 15: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 186 "2005076.y"
                                                        {
		log_CFG_rule("parameter_list", "parameter_list COMMA type_specifier ID");
		(yyval.symbolInfo) = new SymbolInfo("null", "parameter_list");
		(yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "parameter_list : parameter_list COMMA type_specifier ID";

		(yyval.symbolInfo)->parameter_list = (yyvsp[-3].symbolInfo)->parameter_list;
		Parameter extraParam((yyvsp[0].symbolInfo)->getName(), (yyvsp[-1].symbolInfo)->type_specifier);
		(yyval.symbolInfo)->add_param(extraParam);
		(yyvsp[0].symbolInfo)->type_specifier = (yyvsp[-1].symbolInfo)->type_specifier;
		function_params->parameter_list = (yyval.symbolInfo)->parameter_list;

		stored_fParam = (yyval.symbolInfo)->parameter_list;
		if( (yyvsp[-1].symbolInfo)->type_specifier == "VOID"){
			print_error("Variable or field \'"+(yyvsp[0].symbolInfo)->getName()+"\' declared void", "none", line_number);
		}

		
	}
#line 1899 "parser.cpp"
    break;

  case 16: /* parameter_list: parameter_list COMMA type_specifier  */
#line 205 "2005076.y"
                                             {
		log_CFG_rule("parameter_list", "parameter_list COMMA type_specifier ID");
		(yyval.symbolInfo) = new SymbolInfo("parameter_list", "parameter_list");
		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "parameter_list : parameter_list COMMA type_specifier";

		(yyval.symbolInfo)->parameter_list = (yyvsp[-2].symbolInfo)->parameter_list;
		Parameter extraParam("ID", (yyvsp[0].symbolInfo)->type_specifier);
		(yyval.symbolInfo)->add_param(extraParam);
		function_params->parameter_list = (yyval.symbolInfo)->parameter_list;

		stored_fParam = (yyval.symbolInfo)->parameter_list;
		if( (yyvsp[0].symbolInfo)->type_specifier == "VOID"){
			print_error("Variable or field declared void", "none", line_number);
		}
	}
#line 1920 "parser.cpp"
    break;

  case 17: /* parameter_list: type_specifier ID  */
#line 221 "2005076.y"
                           {
		log_CFG_rule("parameter_list", "type_specifier ID");
		(yyval.symbolInfo) = new SymbolInfo("parameter_list", "parameter_list");
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "parameter_list : type_specifier ID";

		Parameter extraParam((yyvsp[0].symbolInfo)->getName(), (yyvsp[-1].symbolInfo)->type_specifier);
		(yyval.symbolInfo)->add_param(extraParam);
		function_params->parameter_list = (yyval.symbolInfo)->parameter_list;

		stored_fParam = (yyval.symbolInfo)->parameter_list;
		if( (yyvsp[-1].symbolInfo)->type_specifier == "VOID"){
			print_error("Variable or field \'"+(yyvsp[0].symbolInfo)->getName()+"\' declared void", "none", line_number);
		}
	}
#line 1940 "parser.cpp"
    break;

  case 18: /* parameter_list: type_specifier  */
#line 236 "2005076.y"
                        {
		log_CFG_rule("parameter_list", "type_specifier");
		(yyval.symbolInfo) = new SymbolInfo("parameter_list", "parameter_list");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "parameter_list : type_specifier";

		Parameter extraParam("none", (yyvsp[0].symbolInfo)->type_specifier);
		(yyval.symbolInfo)->add_param(extraParam);
		function_params->parameter_list = (yyval.symbolInfo)->parameter_list;

		stored_fParam = (yyval.symbolInfo)->parameter_list;
		if( (yyvsp[0].symbolInfo)->type_specifier == "VOID"){
			print_error("Variable or field declared void", "none", line_number);
		}
	}
#line 1960 "parser.cpp"
    break;

  case 19: /* compound_statement: left_curl statements RCURL  */
#line 254 "2005076.y"
                                               {
		log_CFG_rule("compound_statement", "LCURL statements RCURL");
		(yyval.symbolInfo) = new SymbolInfo("comp_statement1", "compound_statement");
		
		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "compound_statement : LCURL statements RCURL";
		(yyval.symbolInfo)->offset = symbol_table->currentScope->stack_offset;

		log_out<<symbol_table -> print_currentScope();
		symbol_table -> exitScope();

	}
#line 1977 "parser.cpp"
    break;

  case 20: /* compound_statement: left_curl RCURL  */
#line 266 "2005076.y"
                         {
		log_CFG_rule("compound_statement", "LCURL RCURL");
		(yyval.symbolInfo) = new SymbolInfo("compound_statement", "compound_statement");
		
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "compound_statement : LCURL RCURL";
		(yyval.symbolInfo)->offset = symbol_table->currentScope->stack_offset;

		log_out<<symbol_table -> print_currentScope();
		symbol_table -> exitScope();
	}
#line 1993 "parser.cpp"
    break;

  case 21: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 280 "2005076.y"
                                                           {
		log_CFG_rule("var_declaration", "type_specifier declaration_list SEMICOLON");
		(yyval.symbolInfo) = new SymbolInfo("var_dec", "var_declaration");

		(yyval.symbolInfo)->type_specifier = (yyvsp[-2].symbolInfo)->type_specifier;
		//symbol_tokens($1->type_specifier, $2->parameter_list);

		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); 
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); 
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "var_declaration : type_specifier declaration_list SEMICOLON";

		if(symbol_table->currentScope->get_scopeID()=="1"){
			(yyval.symbolInfo)->is_global = true;
		}
		else (yyval.symbolInfo)->is_global = false;
		for(SymbolInfo* si : (yyvsp[-1].symbolInfo)->dec_List){
			si->type_specifier = (yyvsp[-2].symbolInfo)->type_specifier;
			symbol_table->insert(si);
			if(symbol_table->currentScope->get_scopeID() == "1"){
				global_variables.push_back(si);
				si->offset = 0;
				si->is_global = true;
			}
			else{
				stack_offset = symbol_table->currentScope->stack_offset;
				si->is_global = false;
				if(si->isArray) symbol_table->currentScope->stack_offset = stack_offset - 2*si->array_size;
				else symbol_table->currentScope->stack_offset = stack_offset - 2;
				si->offset = symbol_table->currentScope->stack_offset;
			}
		}
	}
#line 2031 "parser.cpp"
    break;

  case 22: /* type_specifier: INT  */
#line 316 "2005076.y"
                     {
		log_CFG_rule("type_specifier", "INT");
		(yyval.symbolInfo) = new SymbolInfo("null", "type_specifier");
		(yyval.symbolInfo)->type_specifier = "INT";
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "type_specifier : INT";
	}
#line 2043 "parser.cpp"
    break;

  case 23: /* type_specifier: FLOAT  */
#line 323 "2005076.y"
               {
		log_CFG_rule("type_specifier", "FLOAT");
		(yyval.symbolInfo) = new SymbolInfo("null", "type_specifier");
		(yyval.symbolInfo)->type_specifier = "FLOAT";
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "type_specifier : FLOAT";
	}
#line 2055 "parser.cpp"
    break;

  case 24: /* type_specifier: VOID  */
#line 330 "2005076.y"
              {
		log_CFG_rule("type_specifier", "VOID");
		(yyval.symbolInfo) = new SymbolInfo("null", "type_specifier");
		(yyval.symbolInfo)->type_specifier = "VOID";
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "type_specifier : VOID";
	}
#line 2067 "parser.cpp"
    break;

  case 25: /* declaration_list: declaration_list COMMA ID  */
#line 341 "2005076.y"
                                            {
		log_CFG_rule("declaration_list", "declaration_list COMMA ID");
		(yyval.symbolInfo) = new SymbolInfo("null", "declaration_list");
		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo));
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "declaration_list : declaration_list COMMA ID";

		(yyval.symbolInfo)->dec_List = (yyvsp[-2].symbolInfo)->dec_List;
		(yyval.symbolInfo)->dec_List.push_back((yyvsp[0].symbolInfo));
	}
#line 2082 "parser.cpp"
    break;

  case 26: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 351 "2005076.y"
                                                           {
		log_CFG_rule("declaration_list", "declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		(yyval.symbolInfo) = new SymbolInfo("null", "declaration_list");
		(yyval.symbolInfo)->add_branch((yyvsp[-5].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-4].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo));
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE";

		(yyval.symbolInfo)->dec_List = (yyvsp[-5].symbolInfo)->dec_List;
		(yyvsp[-3].symbolInfo)->isArray = true;
		string str = (yyvsp[-1].symbolInfo)->getName();
		istringstream istr(str);
		int k;
		istr>>k;
		(yyvsp[-3].symbolInfo)->array_size = k;
		(yyval.symbolInfo)->dec_List.push_back((yyvsp[-3].symbolInfo));

	}
#line 2104 "parser.cpp"
    break;

  case 27: /* declaration_list: ID  */
#line 368 "2005076.y"
            {
		log_CFG_rule("declaration_list", "ID");
		(yyval.symbolInfo) = new SymbolInfo("dec_list3", "declaration_list");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "declaration_list : ID";

		(yyval.symbolInfo)->dec_List.push_back((yyvsp[0].symbolInfo));
	}
#line 2117 "parser.cpp"
    break;

  case 28: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 376 "2005076.y"
                                    {
		log_CFG_rule("declaration_list", "ID LSQUARE CONST_INT RSQUARE");
		(yyval.symbolInfo) = new SymbolInfo("declaration_list", "declaration_list");
		(yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo));
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "declaration_list : ID LSQUARE CONST_INT RSQUARE";

		(yyvsp[-3].symbolInfo)->isArray = true;
		string str = (yyvsp[-1].symbolInfo)->getName();

		istringstream istr(str);
		int k;
		istr >> k;
		(yyvsp[-3].symbolInfo)->array_size = k;
		(yyval.symbolInfo)->dec_List.push_back((yyvsp[-3].symbolInfo));
	}
#line 2138 "parser.cpp"
    break;

  case 29: /* statements: statement  */
#line 395 "2005076.y"
                      {
		log_CFG_rule("statements", "statement");
		(yyval.symbolInfo) = new SymbolInfo("statements1", "statements");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "statements : statement";
	}
#line 2149 "parser.cpp"
    break;

  case 30: /* statements: statements statement  */
#line 401 "2005076.y"
                              {
		log_CFG_rule("statements", "statements statement");
		(yyval.symbolInfo) = new SymbolInfo("statements2", "statements");
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "statements : statements statement";
	}
#line 2160 "parser.cpp"
    break;

  case 31: /* statement: var_declaration  */
#line 410 "2005076.y"
                           {
		log_CFG_rule("statement", "var_declaration");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "statement");
		(yyval.symbolInfo)->type_specifier = (yyvsp[0].symbolInfo)->type_specifier;
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "statement : var_declaration";
	}
#line 2172 "parser.cpp"
    break;

  case 32: /* statement: expression_statement  */
#line 417 "2005076.y"
                              {
		log_CFG_rule("statement", "expression_statement");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "statement");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "statement : expression_statement";
		(yyval.symbolInfo)->type_specifier = (yyvsp[0].symbolInfo)->type_specifier;
	}
#line 2184 "parser.cpp"
    break;

  case 33: /* statement: compound_statement  */
#line 424 "2005076.y"
                            {
		log_CFG_rule("statement", "compound_statement");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "statement");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "statement : compound_statement";
		(yyval.symbolInfo)->type_specifier = (yyvsp[0].symbolInfo)->type_specifier;
	}
#line 2196 "parser.cpp"
    break;

  case 34: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 431 "2005076.y"
                                                                                          {
		log_CFG_rule("statement", "FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		(yyval.symbolInfo) = new SymbolInfo("statement", "statement");
		(yyval.symbolInfo)->add_branch((yyvsp[-6].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-5].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-4].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); 
		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo)); 
		(yyval.symbolInfo)->grammar_rule = "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement";
	}
#line 2208 "parser.cpp"
    break;

  case 35: /* statement: IF LPAREN expression RPAREN statement  */
#line 438 "2005076.y"
                                                                     {
		log_CFG_rule("statement", "IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE");
		(yyval.symbolInfo) = new SymbolInfo("statement", "statement");
		(yyval.symbolInfo)->add_branch((yyvsp[-4].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); 
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "statement : IF LPAREN expression RPAREN statement";
	}
#line 2220 "parser.cpp"
    break;

  case 36: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 445 "2005076.y"
                                                              {
		log_CFG_rule("statement", "IF LPAREN expression RPAREN statement ELSE statement");
		(yyval.symbolInfo) = new SymbolInfo("statement", "statement");
		(yyval.symbolInfo)->add_branch((yyvsp[-6].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-5].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-4].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo));
		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "statement : IF LPAREN expression RPAREN statement ELSE statement";
	}
#line 2232 "parser.cpp"
    break;

  case 37: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 452 "2005076.y"
                                                  {
		log_CFG_rule("statement", "WHILE LPAREN expression RPAREN statement");
		(yyval.symbolInfo) = new SymbolInfo("statement", "statement");
		(yyval.symbolInfo)->add_branch((yyvsp[-4].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo));
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "statement : WHILE LPAREN expression RPAREN statement";
	}
#line 2244 "parser.cpp"
    break;

  case 38: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 459 "2005076.y"
                                            {
		log_CFG_rule("statement", "PRINTLN LPAREN ID RPAREN SEMICOLON");
		(yyval.symbolInfo) = new SymbolInfo("statement_println", "statement");
		(yyval.symbolInfo)->add_branch((yyvsp[-4].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo));
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "statement : PRINTLN LPAREN ID RPAREN SEMICOLON";

		auto temp = symbol_table->lookUp((yyvsp[-2].symbolInfo)->getName());
		(yyval.symbolInfo)->offset = temp->offset;
		(yyval.symbolInfo)->is_global = temp->is_global;
	}
#line 2260 "parser.cpp"
    break;

  case 39: /* statement: RETURN expression SEMICOLON  */
#line 470 "2005076.y"
                                     {
		log_CFG_rule("statement", "RETURN expression SEMICOLON");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-2].symbolInfo)->getName(), "statement");
		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "statement : RETURN expression SEMICOLON";

		(yyvsp[-2].symbolInfo)->setName(current_function);
	}
#line 2273 "parser.cpp"
    break;

  case 40: /* expression_statement: SEMICOLON  */
#line 481 "2005076.y"
                                {
		log_CFG_rule("expression_statement", "SEMICOLON");
		(yyval.symbolInfo) = new SymbolInfo("expression_statement", "expression_statement");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "expression_statement : SEMICOLON";
	}
#line 2284 "parser.cpp"
    break;

  case 41: /* expression_statement: expression SEMICOLON  */
#line 487 "2005076.y"
                              {
		log_CFG_rule("expression_statement", "expression SEMICOLON");
		(yyval.symbolInfo) = new SymbolInfo("expr_stmnt1", "expression_statement");
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "expression_statement : expression SEMICOLON";
		(yyval.symbolInfo)->type_specifier = (yyvsp[-1].symbolInfo)->type_specifier;
	}
#line 2296 "parser.cpp"
    break;

  case 42: /* variable: ID  */
#line 497 "2005076.y"
              {
		log_CFG_rule("variable", "ID");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "VARIABLE");
		(yyval.symbolInfo)->type_specifier = (yyvsp[0].symbolInfo)->type_specifier;
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "variable : ID";

		SymbolInfo* temp = symbol_table ->lookUp((yyvsp[0].symbolInfo)->getName());
		if(temp != nullptr){
			(yyval.symbolInfo)->isArray = temp->isArray;
			(yyval.symbolInfo)->offset = temp->offset;
			(yyval.symbolInfo)->is_global = temp->is_global;
		}
		
	}
#line 2316 "parser.cpp"
    break;

  case 43: /* variable: ID LTHIRD expression RTHIRD  */
#line 512 "2005076.y"
                                      {
		log_CFG_rule("variable", "ID LSQUARE expression RSQUARE");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-3].symbolInfo)->getName(), "VARIABLE");
		(yyval.symbolInfo)->type_specifier = (yyvsp[-3].symbolInfo)->type_specifier;
		(yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "variable : ID LSQUARE expression RSQUARE";

		SymbolInfo* temp = symbol_table->lookUp((yyvsp[-3].symbolInfo)->getName());
		if(temp != nullptr){
			temp->isArray = true;
			(yyval.symbolInfo)->isArray = temp->isArray;
			(yyval.symbolInfo)->offset = temp->offset;
			(yyval.symbolInfo)->is_global = temp->is_global;
		}
		(yyval.symbolInfo)->isArray = true;

	}
#line 2338 "parser.cpp"
    break;

  case 44: /* expression: logic_expression  */
#line 532 "2005076.y"
                             {
			log_CFG_rule("expression", "logic_expression");
			(yyval.symbolInfo) = new SymbolInfo("expression", "expression");

			(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)->grammar_rule = "expression : logic_expression";

 	}
#line 2351 "parser.cpp"
    break;

  case 45: /* expression: variable ASSIGNOP logic_expression  */
#line 540 "2005076.y"
                                            {
		log_CFG_rule("expression", "variable ASSIGNOP logic_expression");
		(yyval.symbolInfo) = new SymbolInfo("expression2", "expression");

		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "expression : variable ASSIGNOP logic_expression";
	}
#line 2363 "parser.cpp"
    break;

  case 46: /* logic_expression: rel_expression  */
#line 550 "2005076.y"
                                  {
		log_CFG_rule("logic_expression", "rel_expression");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "logic_expression");
		(yyval.symbolInfo)->type_specifier = (yyvsp[0].symbolInfo)->type_specifier;
		(yyval.symbolInfo)->isArray = (yyvsp[0].symbolInfo)->isArray;

		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "logic_expression : rel_expression";
	}
#line 2377 "parser.cpp"
    break;

  case 47: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 559 "2005076.y"
                                               {
		log_CFG_rule("logic_expression", "rel_expression LOGICOP rel_expression");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-2].symbolInfo)->getName(), "logic_expression");

		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "logic_expression : rel_expression LOGICOP rel_expression";

		if((yyvsp[-2].symbolInfo)->type_specifier == "FLOAT" || (yyvsp[0].symbolInfo)->type_specifier == "FLOAT"){
			print_error("Warning: Operands of bitwise operation should be integers", "none", line_number);
			(yyval.symbolInfo)->type_specifier = "INT";
		}
		else {
			(yyval.symbolInfo)->type_specifier = "INT";
		}
	}
#line 2397 "parser.cpp"
    break;

  case 48: /* rel_expression: simple_expression  */
#line 577 "2005076.y"
                                   {
		log_CFG_rule("rel_expression", "simple_expression");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "rel_expression");

		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "rel_expression : simple_expression";
		(yyval.symbolInfo)->type_specifier = (yyvsp[0].symbolInfo)->type_specifier;
		(yyval.symbolInfo)->isArray = (yyvsp[0].symbolInfo)->isArray;
	}
#line 2411 "parser.cpp"
    break;

  case 49: /* rel_expression: simple_expression RELOP simple_expression  */
#line 586 "2005076.y"
                                                        {
		log_CFG_rule("rel_expression", "simple_expression RELOP simple_expression");
		(yyval.symbolInfo) = new SymbolInfo("", "rel_expression");
		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "rel_expression : simple_expression RELOP simple_expression";

		(yyval.symbolInfo)->type_specifier = "INT";
	}
#line 2424 "parser.cpp"
    break;

  case 50: /* simple_expression: term  */
#line 597 "2005076.y"
                         {
		log_CFG_rule("simple_expression", "term");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "simple_expression");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "simple_expression : term";

		(yyval.symbolInfo)->type_specifier = (yyvsp[0].symbolInfo)->type_specifier;
		(yyval.symbolInfo)->isArray = (yyvsp[0].symbolInfo)->isArray;
	}
#line 2438 "parser.cpp"
    break;

  case 51: /* simple_expression: simple_expression ADDOP term  */
#line 606 "2005076.y"
                                       {
		log_CFG_rule("simple_expression", "simple_expression ADDOP term");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-2].symbolInfo)->getName(), "simple_expression");
		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "simple_expression : simple_expression ADDOP term";

		if((yyvsp[-2].symbolInfo)->type_specifier == "VOID" || (yyvsp[0].symbolInfo)->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
		}
		(yyval.symbolInfo)->type_specifier = casting((yyvsp[-2].symbolInfo)->type_specifier, (yyvsp[0].symbolInfo)->type_specifier);
	}
#line 2454 "parser.cpp"
    break;

  case 52: /* term: unary_expression  */
#line 620 "2005076.y"
                        {
		log_CFG_rule("term", "unary_expression");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "term");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "term : unary_expression";

		(yyval.symbolInfo)->type_specifier = (yyvsp[0].symbolInfo)->type_specifier;
		(yyval.symbolInfo)->isArray = (yyvsp[0].symbolInfo)->isArray;
	}
#line 2468 "parser.cpp"
    break;

  case 53: /* term: term MULOP unary_expression  */
#line 629 "2005076.y"
                                  {
		log_CFG_rule("term", "term MULOP unary_expression");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-2].symbolInfo)->getName(), "term");
		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "term : term MULOP unary_expression";

		if((yyvsp[-2].symbolInfo)->type_specifier == "VOID" || (yyvsp[0].symbolInfo)->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			(yyval.symbolInfo)->type_specifier = "error_type";
		}
		else if((yyvsp[-2].symbolInfo)->type_specifier == "error_type" || (yyvsp[0].symbolInfo)->type_specifier == "error_type"){
			(yyval.symbolInfo)->type_specifier = "error_type";
		}
		else if((yyvsp[-1].symbolInfo)->getName() == "%"){
			if((yyvsp[-2].symbolInfo)->type_specifier == "FLOAT" || (yyvsp[0].symbolInfo)->type_specifier == "FLOAT"){
				print_error("Operands of modulus must be integers", "none", line_number);
				(yyval.symbolInfo)->type_specifier = "error_type";
			}
			else if((yyvsp[0].symbolInfo)->getName() == "0"){
				print_error("Warning: division by zero", "none", line_number);
				(yyval.symbolInfo)->type_specifier = "error_type";
			}
			else{
				(yyval.symbolInfo)->type_specifier = "INT";
			}
		}
		else if((yyvsp[-1].symbolInfo)->getName() == "/"){
			if((yyvsp[0].symbolInfo)->getName() == "0"){
				print_error("Warning: division by zero", "none", line_number);
				(yyval.symbolInfo)->type_specifier = "error_type";
			}
			else{
				(yyval.symbolInfo)->type_specifier = casting((yyvsp[-2].symbolInfo)->type_specifier, (yyvsp[0].symbolInfo)->type_specifier);
			}
		}
		else if((yyvsp[-1].symbolInfo)->getName() == "*"){
			(yyval.symbolInfo)->type_specifier = casting((yyvsp[-2].symbolInfo)->type_specifier, (yyvsp[0].symbolInfo)->type_specifier);
		}

	}
#line 2513 "parser.cpp"
    break;

  case 54: /* unary_expression: ADDOP unary_expression  */
#line 672 "2005076.y"
                                         {
		log_CFG_rule("unary_expression", "ADDOP unary_expression");
		(yyval.symbolInfo) = new SymbolInfo("", "unary_expression");
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "unary_expression : ADDOP unary_expression";

		if((yyvsp[0].symbolInfo)->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			(yyval.symbolInfo)->type_specifier = "error_type";
		}
		else{
			(yyval.symbolInfo)->type_specifier = (yyvsp[0].symbolInfo)->type_specifier;
		}
	}
#line 2532 "parser.cpp"
    break;

  case 55: /* unary_expression: NOT unary_expression  */
#line 686 "2005076.y"
                              {
		log_CFG_rule("unary_expression", "NOT unary_expression");
		(yyval.symbolInfo) = new SymbolInfo("", "unary_expression");
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "unary_expression : NOT unary_expression";

		(yyval.symbolInfo)->type_specifier = "INT";
		if((yyvsp[0].symbolInfo)->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			(yyval.symbolInfo)->type_specifier = "error_type";
		}
		else if((yyvsp[0].symbolInfo)->type_specifier == "FLOAT"){
			print_error("Operands of bitwise operation should be integers", "none", line_number);
		}

	}
#line 2553 "parser.cpp"
    break;

  case 56: /* unary_expression: factor  */
#line 702 "2005076.y"
                {
		log_CFG_rule("unary_expression", "factor");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "unary_expression");

		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "unary_expression : factor";
		(yyval.symbolInfo)->type_specifier = (yyvsp[0].symbolInfo)->type_specifier;
		(yyval.symbolInfo)->isArray = (yyvsp[0].symbolInfo)->isArray;
	}
#line 2567 "parser.cpp"
    break;

  case 57: /* factor: variable  */
#line 714 "2005076.y"
                  {
		log_CFG_rule("factor", "variable");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "factor");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "factor : variable";

		(yyval.symbolInfo)->type_specifier = (yyvsp[0].symbolInfo)->type_specifier;
		(yyval.symbolInfo)->isArray = (yyvsp[0].symbolInfo)->isArray;
	}
#line 2581 "parser.cpp"
    break;

  case 58: /* factor: ID LPAREN argument_list RPAREN  */
#line 723 "2005076.y"
                                        {
		log_CFG_rule("factor", "ID LPAREN argument_list RPAREN");
		(yyval.symbolInfo) = new SymbolInfo("", "factor");
		(yyval.symbolInfo)->add_branch((yyvsp[-3].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "factor : ID LPAREN argument_list RPAREN";

		SymbolInfo* temp = symbol_table->lookUp((yyvsp[-3].symbolInfo)->getName());
		(yyval.symbolInfo)->type_specifier = temp->type_specifier;

		//$1->parameter_list = $3->parameter_list;
	}
#line 2597 "parser.cpp"
    break;

  case 59: /* factor: LPAREN expression RPAREN  */
#line 734 "2005076.y"
                                  {
		log_CFG_rule("factor", "LPAREN expression RPAREN");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-1].symbolInfo)->getName(), "factor");
		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "factor : LPAREN expression RPAREN";

		(yyval.symbolInfo)->type_specifier = (yyvsp[-1].symbolInfo)->type_specifier;
	}
#line 2610 "parser.cpp"
    break;

  case 60: /* factor: CONST_INT  */
#line 742 "2005076.y"
                   {
		log_CFG_rule("factor", "CONST_INT");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "factor");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "factor : CONST_INT";
		(yyval.symbolInfo)->type_specifier = "INT";
	}
#line 2622 "parser.cpp"
    break;

  case 61: /* factor: CONST_FLOAT  */
#line 749 "2005076.y"
                     {
		log_CFG_rule("factor", "CONST_FLOAT");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "factor");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "factor : CONST_FLOAT";
		(yyval.symbolInfo)->type_specifier = "FLOAT";
	}
#line 2634 "parser.cpp"
    break;

  case 62: /* factor: variable INCOP  */
#line 756 "2005076.y"
                        {
		log_CFG_rule("factor", "variable INCOP");
		(yyval.symbolInfo) = new SymbolInfo("", "factor");
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "factor : variable INCOP";

		if((yyvsp[-1].symbolInfo)->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			(yyval.symbolInfo)->type_specifier = "error_type";
		}
		else if((yyvsp[-1].symbolInfo)->type_specifier == "error_type"){
			(yyval.symbolInfo)->type_specifier = "error_type";
		}
		else{
			(yyval.symbolInfo)->type_specifier = (yyvsp[-1].symbolInfo)->type_specifier;
		}
	}
#line 2656 "parser.cpp"
    break;

  case 63: /* factor: variable DECOP  */
#line 773 "2005076.y"
                        {
		log_CFG_rule("factor", "variable DECOP");
		(yyval.symbolInfo) = new SymbolInfo("", "factor");
		(yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "factor : variable DECOP";

		if((yyvsp[-1].symbolInfo)->type_specifier == "VOID"){
			print_error("Void cannot be used in expression", "none", line_number);
			(yyval.symbolInfo)->type_specifier = "error_type";
		}
		else if((yyvsp[-1].symbolInfo)->type_specifier == "error_type"){
			(yyval.symbolInfo)->type_specifier = "error_type";
		}
		else{
			(yyval.symbolInfo)->type_specifier = (yyvsp[-1].symbolInfo)->type_specifier;
		}
	}
#line 2678 "parser.cpp"
    break;

  case 64: /* argument_list: arguments  */
#line 794 "2005076.y"
                         {
		log_CFG_rule("argument_list", "arguments");
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getName(), "argument_list");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "argument_list : arguments";

		(yyval.symbolInfo)->parameter_list = (yyvsp[0].symbolInfo)->parameter_list;
		(yyval.symbolInfo)->offset = (yyvsp[0].symbolInfo)->offset;
	}
#line 2692 "parser.cpp"
    break;

  case 65: /* argument_list: %empty  */
#line 803 "2005076.y"
          {
		log_CFG_rule("argument_list", "");
		(yyval.symbolInfo) = new SymbolInfo("null", "argument_list");
		(yyval.symbolInfo)->grammar_rule = "argument_list : ";
		(yyval.symbolInfo)->startLine = line_number;
		(yyval.symbolInfo)->endLine = line_number;
	}
#line 2704 "parser.cpp"
    break;

  case 66: /* arguments: arguments COMMA logic_expression  */
#line 812 "2005076.y"
                                            {
		log_CFG_rule("arguments", "arguments COMMA logic_expression");
		(yyval.symbolInfo) = new SymbolInfo("null", "arguments");
		(yyval.symbolInfo)->add_branch((yyvsp[-2].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[-1].symbolInfo)); (yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "arguments : arguments COMMA logic_expression";

		(yyval.symbolInfo)->parameter_list = (yyvsp[-2].symbolInfo)->parameter_list;
		Parameter extraParam((yyvsp[0].symbolInfo)->getName(), (yyvsp[0].symbolInfo)->type_specifier);
		extraParam.array_type = (yyvsp[0].symbolInfo)->isArray;
		(yyval.symbolInfo)->add_param(extraParam);

		(yyval.symbolInfo)->offset = (yyvsp[-2].symbolInfo)->offset+2;
	}
#line 2722 "parser.cpp"
    break;

  case 67: /* arguments: logic_expression  */
#line 825 "2005076.y"
                          {
		log_CFG_rule("arguments", "logic_expression");
		(yyval.symbolInfo) = new SymbolInfo("null", "arguments");
		(yyval.symbolInfo)->add_branch((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)->grammar_rule = "arguments : logic_expression";

		Parameter extraParam((yyvsp[0].symbolInfo)->getName(), (yyvsp[0].symbolInfo)->type_specifier);
		extraParam.array_type = (yyvsp[0].symbolInfo)->isArray;
		(yyval.symbolInfo)->add_param(extraParam);

		(yyval.symbolInfo)->offset = 2;
	}
#line 2739 "parser.cpp"
    break;

  case 68: /* left_curl: LCURL  */
#line 839 "2005076.y"
                 {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		symbol_table -> enterScope();
		int st_off = 2;
		for(int k=function_params->parameter_list.size()-1; k>=0; k-- ){
			Parameter param = function_params->parameter_list[k];
			if(param.param_name == "") continue;
			SymbolInfo* extra = new SymbolInfo(param.param_name, "ID");
			forDelete.push_back(extra);
			extra->isArray = param.array_type;
			extra->type_specifier = param.dataType;

			st_off += 2;
			extra->offset = st_off;
			bool temp = symbol_table->insert(extra);
			if(temp == false){
				print_error("Redefinition of parameter", extra->getName(), line_number);
				free_symbol(extra);
				break;
			}
		}
		stored_fParam.clear();
		function_params->parameter_list.clear();
		symbol_table->currentScope->stack_offset = 0;
	}
#line 2769 "parser.cpp"
    break;


#line 2773 "parser.cpp"

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

#line 868 "2005076.y"

int main(int argc,char *argv[])
{
	FILE *fp;

	if (argc < 2) {
		cout << "Enter Input File\n";
		exit(1);
	}

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}
	assem_code.open("2005076_code.asm");

	symbol_table = new SymbolTable(symbolTable_size);
	//cout<<symbol_table->currentScope->get_scopeID()<<"\n";


	yyin=fp;
	yyparse();
	
	end_parse();
	code_optimizer();

	fclose(yyin);
	
	return 0;
}

