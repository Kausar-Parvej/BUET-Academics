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
#line 7 "parser.y"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <vector>

int yylex(void);
extern FILE *yyin;
void yyerror(const char *message);

int getOpcodeID(std::string opcode);
int getRegisterID(std::string reg);
char getHexChar(int number);
void writeBin(std::ofstream &out, std::string str);

std::string isa;

int instructionCounter = 0;
std::map<std::string, int> map;

std::stringstream instructionBuffer;
std::vector<std::string> instructions;


#line 97 "y.tab.c"

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
/* "%code requires" blocks.  */
#line 1 "parser.y"

	#include <iostream>
	#include <fstream>

#line 137 "y.tab.c"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ADD = 258,                     /* ADD  */
    ADDI = 259,                    /* ADDI  */
    SUB = 260,                     /* SUB  */
    SUBI = 261,                    /* SUBI  */
    AND = 262,                     /* AND  */
    ANDI = 263,                    /* ANDI  */
    OR = 264,                      /* OR  */
    ORI = 265,                     /* ORI  */
    SLL = 266,                     /* SLL  */
    SRL = 267,                     /* SRL  */
    NOR = 268,                     /* NOR  */
    SW = 269,                      /* SW  */
    LW = 270,                      /* LW  */
    BEQ = 271,                     /* BEQ  */
    BNEQ = 272,                    /* BNEQ  */
    J = 273,                       /* J  */
    REGISTER = 274,                /* REGISTER  */
    COMMA = 275,                   /* COMMA  */
    COLON = 276,                   /* COLON  */
    LPAREN = 277,                  /* LPAREN  */
    RPAREN = 278,                  /* RPAREN  */
    LABEL = 279,                   /* LABEL  */
    INT = 280,                     /* INT  */
    PUSH = 281,                    /* PUSH  */
    POP = 282                      /* POP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ADD 258
#define ADDI 259
#define SUB 260
#define SUBI 261
#define AND 262
#define ANDI 263
#define OR 264
#define ORI 265
#define SLL 266
#define SRL 267
#define NOR 268
#define SW 269
#define LW 270
#define BEQ 271
#define BNEQ 272
#define J 273
#define REGISTER 274
#define COMMA 275
#define COLON 276
#define LPAREN 277
#define RPAREN 278
#define LABEL 279
#define INT 280
#define PUSH 281
#define POP 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef std::string YYSTYPE;
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
  YYSYMBOL_ADD = 3,                        /* ADD  */
  YYSYMBOL_ADDI = 4,                       /* ADDI  */
  YYSYMBOL_SUB = 5,                        /* SUB  */
  YYSYMBOL_SUBI = 6,                       /* SUBI  */
  YYSYMBOL_AND = 7,                        /* AND  */
  YYSYMBOL_ANDI = 8,                       /* ANDI  */
  YYSYMBOL_OR = 9,                         /* OR  */
  YYSYMBOL_ORI = 10,                       /* ORI  */
  YYSYMBOL_SLL = 11,                       /* SLL  */
  YYSYMBOL_SRL = 12,                       /* SRL  */
  YYSYMBOL_NOR = 13,                       /* NOR  */
  YYSYMBOL_SW = 14,                        /* SW  */
  YYSYMBOL_LW = 15,                        /* LW  */
  YYSYMBOL_BEQ = 16,                       /* BEQ  */
  YYSYMBOL_BNEQ = 17,                      /* BNEQ  */
  YYSYMBOL_J = 18,                         /* J  */
  YYSYMBOL_REGISTER = 19,                  /* REGISTER  */
  YYSYMBOL_COMMA = 20,                     /* COMMA  */
  YYSYMBOL_COLON = 21,                     /* COLON  */
  YYSYMBOL_LPAREN = 22,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 23,                    /* RPAREN  */
  YYSYMBOL_LABEL = 24,                     /* LABEL  */
  YYSYMBOL_INT = 25,                       /* INT  */
  YYSYMBOL_PUSH = 26,                      /* PUSH  */
  YYSYMBOL_POP = 27,                       /* POP  */
  YYSYMBOL_YYACCEPT = 28,                  /* $accept  */
  YYSYMBOL_start = 29,                     /* start  */
  YYSYMBOL_program = 30,                   /* program  */
  YYSYMBOL_unit = 31,                      /* unit  */
  YYSYMBOL_labels = 32,                    /* labels  */
  YYSYMBOL_33_1 = 33,                      /* $@1  */
  YYSYMBOL_34_2 = 34,                      /* $@2  */
  YYSYMBOL_instruction = 35,               /* instruction  */
  YYSYMBOL_rtype_instruction = 36,         /* rtype_instruction  */
  YYSYMBOL_37_3 = 37,                      /* $@3  */
  YYSYMBOL_38_4 = 38,                      /* $@4  */
  YYSYMBOL_39_5 = 39,                      /* $@5  */
  YYSYMBOL_40_6 = 40,                      /* $@6  */
  YYSYMBOL_41_7 = 41,                      /* $@7  */
  YYSYMBOL_rtype_params = 42,              /* rtype_params  */
  YYSYMBOL_itype_instruction = 43,         /* itype_instruction  */
  YYSYMBOL_44_8 = 44,                      /* $@8  */
  YYSYMBOL_45_9 = 45,                      /* $@9  */
  YYSYMBOL_46_10 = 46,                     /* $@10  */
  YYSYMBOL_47_11 = 47,                     /* $@11  */
  YYSYMBOL_48_12 = 48,                     /* $@12  */
  YYSYMBOL_49_13 = 49,                     /* $@13  */
  YYSYMBOL_50_14 = 50,                     /* $@14  */
  YYSYMBOL_51_15 = 51,                     /* $@15  */
  YYSYMBOL_itype_params = 52,              /* itype_params  */
  YYSYMBOL_branch_params = 53,             /* branch_params  */
  YYSYMBOL_memory_params = 54,             /* memory_params  */
  YYSYMBOL_stype_instruction = 55,         /* stype_instruction  */
  YYSYMBOL_56_16 = 56,                     /* $@16  */
  YYSYMBOL_57_17 = 57,                     /* $@17  */
  YYSYMBOL_jtype_instruction = 58,         /* jtype_instruction  */
  YYSYMBOL_59_18 = 59,                     /* $@18  */
  YYSYMBOL_push_instruction = 60,          /* push_instruction  */
  YYSYMBOL_pop_instruction = 61            /* pop_instruction  */
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
#define YYFINAL  51
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   101

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  98

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   282


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
      25,    26,    27
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    37,    37,    62,    64,    66,    68,    71,    71,    73,
      73,    76,    78,    80,    82,    84,    86,    89,    89,    91,
      91,    93,    93,    95,    95,    97,    97,   100,   107,   107,
     109,   109,   111,   111,   113,   113,   115,   115,   117,   117,
     119,   119,   121,   121,   124,   131,   138,   145,   145,   147,
     147,   150,   150,   157,   169,   186
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
  "\"end of file\"", "error", "\"invalid token\"", "ADD", "ADDI", "SUB",
  "SUBI", "AND", "ANDI", "OR", "ORI", "SLL", "SRL", "NOR", "SW", "LW",
  "BEQ", "BNEQ", "J", "REGISTER", "COMMA", "COLON", "LPAREN", "RPAREN",
  "LABEL", "INT", "PUSH", "POP", "$accept", "start", "program", "unit",
  "labels", "$@1", "$@2", "instruction", "rtype_instruction", "$@3", "$@4",
  "$@5", "$@6", "$@7", "rtype_params", "itype_instruction", "$@8", "$@9",
  "$@10", "$@11", "$@12", "$@13", "$@14", "$@15", "itype_params",
  "branch_params", "memory_params", "stype_instruction", "$@16", "$@17",
  "jtype_instruction", "$@18", "push_instruction", "pop_instruction", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-9)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -3,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    34,    -2,
      18,    -3,    -9,    22,    -9,    -9,    -9,    -9,    -9,    -9,
      -9,     0,     1,     0,     1,     0,     1,     0,     1,     1,
       1,     0,     3,     3,    23,    23,    -8,    20,    -9,    35,
      -9,    -9,    -9,    -9,    -9,    24,    -9,    38,    -9,    -9,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    40,    -9,
      -9,    41,    -9,    -9,    -9,    -9,    43,    42,    45,    46,
      44,    47,    48,    -9,    50,    52,    51,    54,    -9,    49,
      53,    56,    55,    -9,    -9,    57,    -9,    -9
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    17,    28,    19,    30,    21,    32,    23,    34,    47,
      49,    25,    42,    40,    36,    38,    51,     9,     0,     0,
       0,     2,     4,     0,     5,    11,    12,    13,    14,    15,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    53,     0,
      55,     1,     3,     7,     6,     0,    18,     0,    29,    20,
      31,    22,    33,    24,    35,    48,    50,    26,     0,    43,
      41,     0,    37,    39,    52,    10,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     0,     0,     0,    54,     0,
       0,     0,     0,    27,    44,     0,    45,    46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -9,    -9,    -9,    60,    -9,    -9,    -9,    59,    -9,    -9,
      -9,    -9,    -9,    -9,    10,    -9,    -9,    -9,    -9,    -9,
      -9,    -9,    -9,    -9,    16,    31,    58,    -9,    -9,    -9,
      -9,    -9,    -9,    -9
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    20,    21,    22,    23,    77,    47,    24,    25,    31,
      33,    35,    37,    41,    56,    26,    32,    34,    36,    38,
      44,    45,    43,    42,    58,    72,    69,    27,    39,    40,
      28,    46,    29,    30
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    74,    50,    51,    55,
      57,    17,    68,    18,    19,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    75,    71,    59,    78,    61,    53,    63,    18,    19,
      60,    67,    62,    48,    64,    65,    66,    76,    79,    49,
      80,    81,    82,    83,    84,    85,    87,     0,    93,    86,
      89,    88,    90,    91,    92,    95,    73,     0,    94,    96,
      97,    52,    54,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70
};

static const yytype_int8 yycheck[] =
{
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    24,    19,     0,    19,
      19,    24,    19,    26,    27,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    21,    19,    33,    20,    35,    24,    37,    26,    27,
      34,    41,    36,    19,    38,    39,    40,    22,    20,    25,
      20,    20,    19,    21,    19,    19,    19,    -1,    19,    25,
      20,    23,    20,    22,    20,    19,    45,    -1,    25,    24,
      23,    21,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    24,    26,    27,
      29,    30,    31,    32,    35,    36,    43,    55,    58,    60,
      61,    37,    44,    38,    45,    39,    46,    40,    47,    56,
      57,    41,    51,    50,    48,    49,    59,    34,    19,    25,
      19,     0,    31,    24,    35,    19,    42,    19,    52,    42,
      52,    42,    52,    42,    52,    52,    52,    42,    19,    54,
      54,    19,    53,    53,    24,    21,    22,    33,    20,    20,
      20,    20,    19,    21,    19,    19,    25,    19,    23,    20,
      20,    22,    20,    19,    25,    19,    24,    23
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    28,    29,    30,    30,    31,    31,    33,    32,    34,
      32,    35,    35,    35,    35,    35,    35,    37,    36,    38,
      36,    39,    36,    40,    36,    41,    36,    42,    44,    43,
      45,    43,    46,    43,    47,    43,    48,    43,    49,    43,
      50,    43,    51,    43,    52,    53,    54,    56,    55,    57,
      55,    59,    58,    60,    60,    61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     0,     4,     0,
       3,     1,     1,     1,     1,     1,     1,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     5,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     5,     5,     6,     0,     3,     0,
       3,     0,     3,     2,     5,     2
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
  case 2: /* start: program  */
#line 37 "parser.y"
               {

	char beqCode =  getHexChar(getOpcodeID("beq"));
	char bneqCode =  getHexChar(getOpcodeID("bneq"));
	char jCode = getHexChar(getOpcodeID("j"));

	int index = 0;
	for (auto i = instructions.begin(); i != instructions.end(); ++i, ++index) {
		std::string &instruction = *i;
		if (instruction[0] == beqCode || instruction[0] == bneqCode) {
			std::string label = instruction.substr(3);
			int destination = map[label];
			int offset = destination - index - 1;
			int signedOffset = (16 + offset) % 16;

			instruction = instruction.substr(0, 3) + getHexChar(signedOffset);
		}
		else if (instruction[0] == jCode) {
			std::string label = instruction.substr(1);
			int destination = map[label];
			instruction = std::string("") + instruction[0] + getHexChar((destination >> 4) & 0xF) + getHexChar(destination & 0xF) + "0";
		}
	}
}
#line 1333 "y.tab.c"
    break;

  case 5: /* unit: instruction  */
#line 66 "parser.y"
                  { ++instructionCounter; }
#line 1339 "y.tab.c"
    break;

  case 6: /* unit: labels instruction  */
#line 68 "parser.y"
                           { ++instructionCounter; }
#line 1345 "y.tab.c"
    break;

  case 7: /* $@1: %empty  */
#line 71 "parser.y"
                     { map[yyvsp[0]] = instructionCounter; }
#line 1351 "y.tab.c"
    break;

  case 9: /* $@2: %empty  */
#line 73 "parser.y"
              { map[yyvsp[0]] = instructionCounter; }
#line 1357 "y.tab.c"
    break;

  case 17: /* $@3: %empty  */
#line 89 "parser.y"
                       { instructionBuffer << getHexChar(getOpcodeID("add")); }
#line 1363 "y.tab.c"
    break;

  case 19: /* $@4: %empty  */
#line 91 "parser.y"
            { instructionBuffer << getHexChar(getOpcodeID("sub")); }
#line 1369 "y.tab.c"
    break;

  case 21: /* $@5: %empty  */
#line 93 "parser.y"
            { instructionBuffer << getHexChar(getOpcodeID("and")); }
#line 1375 "y.tab.c"
    break;

  case 23: /* $@6: %empty  */
#line 95 "parser.y"
           { instructionBuffer << getHexChar(getOpcodeID("or")); }
#line 1381 "y.tab.c"
    break;

  case 25: /* $@7: %empty  */
#line 97 "parser.y"
            { instructionBuffer << getHexChar(getOpcodeID("nor")); }
#line 1387 "y.tab.c"
    break;

  case 27: /* rtype_params: REGISTER COMMA REGISTER COMMA REGISTER  */
#line 100 "parser.y"
                                                     {
	instructionBuffer << getHexChar(getRegisterID(yyvsp[-2])) << getHexChar(getRegisterID(yyvsp[0])) << getHexChar(getRegisterID(yyvsp[-4]));
	instructions.push_back(instructionBuffer.str());
	instructionBuffer.str(std::string());
}
#line 1397 "y.tab.c"
    break;

  case 28: /* $@8: %empty  */
#line 107 "parser.y"
                        { instructionBuffer << getHexChar(getOpcodeID("addi")); }
#line 1403 "y.tab.c"
    break;

  case 30: /* $@9: %empty  */
#line 109 "parser.y"
             { instructionBuffer << getHexChar(getOpcodeID("subi")); }
#line 1409 "y.tab.c"
    break;

  case 32: /* $@10: %empty  */
#line 111 "parser.y"
             { instructionBuffer << getHexChar(getOpcodeID("andi")); }
#line 1415 "y.tab.c"
    break;

  case 34: /* $@11: %empty  */
#line 113 "parser.y"
            { instructionBuffer << getHexChar(getOpcodeID("ori")); }
#line 1421 "y.tab.c"
    break;

  case 36: /* $@12: %empty  */
#line 115 "parser.y"
            { instructionBuffer << getHexChar(getOpcodeID("beq")); }
#line 1427 "y.tab.c"
    break;

  case 38: /* $@13: %empty  */
#line 117 "parser.y"
             { instructionBuffer << getHexChar(getOpcodeID("bneq")); }
#line 1433 "y.tab.c"
    break;

  case 40: /* $@14: %empty  */
#line 119 "parser.y"
           { instructionBuffer << getHexChar(getOpcodeID("lw")); }
#line 1439 "y.tab.c"
    break;

  case 42: /* $@15: %empty  */
#line 121 "parser.y"
           { instructionBuffer << getHexChar(getOpcodeID("sw")); }
#line 1445 "y.tab.c"
    break;

  case 44: /* itype_params: REGISTER COMMA REGISTER COMMA INT  */
#line 124 "parser.y"
                                                {
	instructionBuffer << getHexChar(getRegisterID(yyvsp[-2])) << getHexChar(getRegisterID(yyvsp[-4])) << getHexChar(atoi(yyvsp[0].c_str()));
	instructions.push_back(instructionBuffer.str());
	instructionBuffer.str(std::string());
}
#line 1455 "y.tab.c"
    break;

  case 45: /* branch_params: REGISTER COMMA REGISTER COMMA LABEL  */
#line 131 "parser.y"
                                                   {
	instructionBuffer << getHexChar(getRegisterID(yyvsp[-4])) << getHexChar(getRegisterID(yyvsp[-2])) << yyvsp[0];
	instructions.push_back(instructionBuffer.str());
	instructionBuffer.str(std::string());
}
#line 1465 "y.tab.c"
    break;

  case 46: /* memory_params: REGISTER COMMA INT LPAREN REGISTER RPAREN  */
#line 138 "parser.y"
                                                         {
	instructionBuffer << getHexChar(getRegisterID(yyvsp[-1])) << getHexChar(getRegisterID(yyvsp[-5])) << getHexChar(atoi(yyvsp[-3].c_str()));
	instructions.push_back(instructionBuffer.str());
	instructionBuffer.str(std::string());
}
#line 1475 "y.tab.c"
    break;

  case 47: /* $@16: %empty  */
#line 145 "parser.y"
                       { instructionBuffer << getHexChar(getOpcodeID("sll")); }
#line 1481 "y.tab.c"
    break;

  case 49: /* $@17: %empty  */
#line 147 "parser.y"
            { instructionBuffer << getHexChar(getOpcodeID("srl")); }
#line 1487 "y.tab.c"
    break;

  case 51: /* $@18: %empty  */
#line 150 "parser.y"
                     { instructionBuffer << getHexChar(getOpcodeID("j")); }
#line 1493 "y.tab.c"
    break;

  case 52: /* jtype_instruction: J $@18 LABEL  */
#line 150 "parser.y"
                                                                                  {
	instructionBuffer << yyvsp[0];
	instructions.push_back(instructionBuffer.str());
	instructionBuffer.str(std::string());
}
#line 1503 "y.tab.c"
    break;

  case 53: /* push_instruction: PUSH REGISTER  */
#line 157 "parser.y"
                                {
	instructionBuffer << getHexChar(getOpcodeID("sw")) << getHexChar(getRegisterID("$sp")) << getHexChar(getRegisterID(yyvsp[0])) << "0";
	instructions.push_back(instructionBuffer.str());
	instructionBuffer.str(std::string());
	
	instructionBuffer << getHexChar(getOpcodeID("subi")) << getHexChar(getRegisterID("$sp")) << getHexChar(getRegisterID("$sp")) << "1";
	instructions.push_back(instructionBuffer.str());
	instructionBuffer.str(std::string());

	++instructionCounter;
}
#line 1519 "y.tab.c"
    break;

  case 54: /* push_instruction: PUSH INT LPAREN REGISTER RPAREN  */
#line 169 "parser.y"
                                        {
		instructionBuffer << getHexChar(getOpcodeID("lw")) << getHexChar(getRegisterID(yyvsp[-1])) << getHexChar(getRegisterID("$x0")) << getHexChar(atoi(yyvsp[-3].c_str()));
		instructions.push_back(instructionBuffer.str());
		instructionBuffer.str(std::string());

		instructionBuffer << getHexChar(getOpcodeID("sw")) << getHexChar(getRegisterID("$sp")) << getHexChar(getRegisterID("$x0")) << "0";
		instructions.push_back(instructionBuffer.str());
		instructionBuffer.str(std::string());
		
		instructionBuffer << getHexChar(getOpcodeID("subi")) << getHexChar(getRegisterID("$sp")) << getHexChar(getRegisterID("$sp")) << "1";
		instructions.push_back(instructionBuffer.str());
		instructionBuffer.str(std::string());

		instructionCounter += 2;
	}
#line 1539 "y.tab.c"
    break;

  case 55: /* pop_instruction: POP REGISTER  */
#line 186 "parser.y"
                              {
	instructionBuffer << getHexChar(getOpcodeID("addi")) << getHexChar(getRegisterID("$sp")) << getHexChar(getRegisterID("$sp")) << "1";
	instructions.push_back(instructionBuffer.str());
	instructionBuffer.str(std::string());
	
	instructionBuffer << getHexChar(getOpcodeID("lw")) << getHexChar(getRegisterID("$sp")) << getHexChar(getRegisterID(yyvsp[0])) << "0";
	instructions.push_back(instructionBuffer.str());
	instructionBuffer.str(std::string());

	++instructionCounter;
}
#line 1555 "y.tab.c"
    break;


#line 1559 "y.tab.c"

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

#line 199 "parser.y"


int main(int argc, char **argv) {
	if (argc != 3 && argc != 4) {
		std::cout << "Wrong usage" << std::endl;
		std::cout << "Sample usage: ./assembler.out [--safe-init] <assembly_file_path> <isa_string>" << std::endl;
		return 1;
	}

	isa = argv[argc == 3? 2 : 3];

	yyin = fopen(argv[argc == 3? 1 : 2], "r");
	if (!yyin) {
		std::cout << "File not found" << std::endl;
		return 1;
	}

	if (argc == 4) {
		if (std::string(argv[1]) == "--safe-init") {
			// clear $zero by performing $zero = $zero sub $zero
			instructionBuffer << getHexChar(getOpcodeID("sub")) << getHexChar(getRegisterID("$zero")) << getHexChar(getRegisterID("$zero")) << getHexChar(getRegisterID("$zero"));
			instructions.insert(instructions.begin(), instructionBuffer.str());
			instructionBuffer.str(std::string());

			//set $sp to F by performing $sp = $sp | 0xF
			instructionBuffer << getHexChar(getOpcodeID("ori")) << getHexChar(getRegisterID("$sp")) << getHexChar(getRegisterID("$sp")) << "F";
			instructions.insert(instructions.begin(), instructionBuffer.str());
			instructionBuffer.str(std::string());
		} else {
			std::cout << "Unknown flag " << argv[1] << std::endl;
			exit(1);
		}

		instructionCounter += 2;

	}

	yyparse();


	std::ofstream hexFile("hex.txt");
	std::ofstream binFile("out.bin");
	int counter = 0;
	for (auto i = instructions.begin(); i != instructions.end(); ++i) {
		//hexFile << *i << std::endl;
		hexFile <<"0x"<< *i << ",";
		writeBin(binFile, *i);
		counter++;
		if(counter == 16){
			hexFile<<"\n";
			counter = 0;
		}
	}
	hexFile<<"\n\n\t counter : "<<counter<<"\n";
	hexFile.close();

	fclose(yyin);
	return 0;
}

void yyerror(const char *message) {
	std::cout << "Syntax error: " << message << std::endl;
}

int getOpcodeID(std::string opcode) {
	std::string list[] = {"add", "addi", "sub", "subi", "and", "andi", "or", "ori", "sll", "srl", "nor", "sw", "lw", "beq", "bneq", "j"};

	int index = -1;
	for (int i = 0; i < isa.length(); ++i) {
		if (list[i] == opcode) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		std::cout << "Could not find " << opcode << std::endl;
		exit(1);
	}

	char idChar = 'A' + index;

	return isa.find(idChar);
}

int getRegisterID(std::string reg) {
	if (reg == "$zero") return 0;
	else if (reg == "$t0") return 1;
	else if (reg == "$t1") return 2;
	else if (reg == "$t2") return 3;
	else if (reg == "$t3") return 4;
	else if (reg == "$t4") return 5;
	else if (reg == "$sp") return 6;
	else if (reg == "$x0") return 7;
	else {
		std::cout << "Cannot find register id for " << reg << std::endl;
		exit(1);
	}
}

char getHexChar(int number) {
	return number < 10? '0' + number : number - 10 + 'A';
}

int getDec(char hex) {
	return isalpha(hex)? hex - 'A' + 10: hex - '0';
}

void writeBin(std::ofstream &out, std::string str) {
	unsigned char x = getDec(str[0]) * 16 + getDec(str[1]);
	unsigned char y = getDec(str[2]) * 16 + getDec(str[3]);
	out << x << y;
}
