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

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <cassert>
#include "utilities.h"
#include "symbol_table.h"

using namespace std;

#define BUCKET_SIZE 11

extern int line_count;
extern int error_count;
int syntax_error_line;
SymbolTable *sym;
extern FILE* yyin;
vector<Param> current_function_parameters;
string func_return_type;

ofstream treeout, errorout, logout;

void yyerror(const string& s) {
	//logout << "Error at line no " << line_count << " : syntax error" << endl;
	syntax_error_line = line_count;
}
int yyparse(void);
int yylex(void);

inline void print_grammar_rule(const string& parent, const string& children) {
	logout << parent << " : " << children << " " << endl;
}

inline void free_s(SymbolInfo* s)	{
	if (s != nullptr) {
		delete s;
		s = nullptr;
	}
}

inline bool check_type_specifier(const string& ty, const string& name) {
	if (ty == "VOID") {
		show_error(SEMANTIC, VOID_TYPE, name, errorout);
		return false;
	}
	return true;
}

inline string type_cast(const string& s1, const string& s2) {
	if (s1 == "VOID" || s2 == "VOID" || s1 == "ERROR" || s2 == "ERROR") return "ERROR";
	else if (s1 == "FLOAT" || s2 == "FLOAT") return "FLOAT";
	else return "INT";
}

inline bool is_zero(const string& str) {
	// already guaranteed to be a valid number from lexer, so no need to check that again
	for (char c : str) {
		if (c != '0' && c != 'e' && c != 'E') return false;
	}
	return true;
}

void insert_function(const string& func_name, const string& type_specifier, const vector<Param>& param_list, bool is_definition) {
	if (is_definition) {
		current_function_parameters.clear();
		current_function_parameters = param_list;
	}
	SymbolInfo* function = new SymbolInfo(func_name, "FUNCTION", type_specifier);
	if (is_definition) function->set_func_type(DEFINITION);
	else {
		function->set_func_type(DECLARATION);
	}
	function->set_param_list(param_list);

	if (function->get_func_type() == DEFINITION) {
		// no parameter can be nameless in a function definition
		for (int i = 0; i < param_list.size(); i++) {
			if (param_list[i].name == "") {
				show_error(SEMANTIC, PARAM_NAMELESS, function->get_name(), errorout);
				free_s(function);
				return; // returning as any such function is not acceptable
			}
		}
		// just check the types of the parameters
		SymbolInfo* og_func = sym->search(function->get_name(), 'A');
		if (og_func == nullptr) {
			// this is both declaration and definition then
			sym->insert(function);
		}
		else {
			if (og_func->get_func_type() == NONE) {
				// same name variable already present with this name
				show_error(SEMANTIC, DIFFERENT_REDECLARATION, function->get_name(), errorout);
			}
			else if (og_func->get_func_type() == DEFINITION) {
				// function definition already exists
				show_error(SEMANTIC, FUNC_REDEFINITION, function->get_name(), errorout);
			}
			// already declaration exists
			else if (og_func->get_data_type() != type_specifier) {
				// return type mismatch
				show_error(SEMANTIC, CONFLICTING_TYPE, function->get_name(), errorout);
			}
			else if (og_func->get_param_list().size() != param_list.size()) {
				// parameter size mismatch
				show_error(SEMANTIC, CONFLICTING_TYPE, function->get_name(), errorout);
			}
			else {
				// defintion param type and declaraion param type mismatch check
				vector<Param> og_list = og_func->get_param_list();
				vector<Param> now_list = function->get_param_list();
				for (int i = 0; i < og_list.size(); i++) {
					if (og_list[i].data_type != now_list[i].data_type) {
						show_error(SEMANTIC, CONFLICTING_TYPE, function->get_name(), errorout);
					}
				}
			}
			og_func->set_func_type(DEFINITION); // set the func type to definition
			free_s(function);
		}
	}
	else {
		// if it is a function definition, the check is done in lcurls -> LCURL, check there
		// but if prototype, check not done there
		for (int i = 0; i < param_list.size(); i++) {
			for (int j = i + 1; j < param_list.size(); j++) {
				// checking if any two parameters have same name except both being ""
				if (param_list[i].name == "") continue;
				if (param_list[i].name == param_list[j].name) {
					show_error(SEMANTIC, PARAM_REDEFINITION, param_list[i].name, errorout);
					free_s(function);
					return; // returning as any such function is not acceptable
				}
			}
		}
		// this is just a prototype
		SymbolInfo* og_func = sym->search(function->get_name(), 'A');
		if (og_func == nullptr) {
			// this is both declaration and definition then
			sym->insert(function);
		}
		else {
			if (og_func->get_func_type() == NONE) {
				// same name variable already present with this name
				show_error(SEMANTIC, DIFFERENT_REDECLARATION, function->get_name(), errorout);
			}
			else if (og_func->get_func_type() != NONE) {
				// function definition already exists
				show_error(SEMANTIC, FUNC_REDEFINITION, function->get_name(), errorout);
			}
			free_s(function);
		}
	}
}

void insert_symbols(const string& type, const vector<Param>& param_list) {
	string str = "";
	vector<Param> cur_list = param_list;
	for (int i = 0; i < cur_list.size(); i++) {
		str += cur_list[i].name;
		if (i != cur_list.size() - 1) str += ", ";
	}
	bool ok = check_type_specifier(type, str);
	if (ok) {
		for (int i = 0; i < cur_list.size(); i++) {
			// now we will set the data_type of all these symbols to $1
			cur_list[i].data_type = type;
			// cerr << cur_list[i].data_type << " " << cur_list[i].name << endl;
			SymbolInfo* res = sym->search(cur_list[i].name, 'C');
			if (res == nullptr) {
				SymbolInfo* new_sym = new SymbolInfo(cur_list[i].name, "ID", cur_list[i].data_type);
				if (cur_list[i].is_array) new_sym->set_array(true);
				sym->insert(new_sym);
			}
			else if (res->get_data_type() != cur_list[i].data_type) {
				// cerr << "Previous: " << res->get_data_type() << " current: " << cur_list[i].data_type << " " << cur_list[i].name << " line: " << line_count << endl; 
				show_error(SEMANTIC, CONFLICTING_TYPE, cur_list[i].name, errorout);
			}
			else {
				show_error(SEMANTIC, VARIABLE_REDEFINITION, cur_list[i].name, errorout);
			}
		}
	}
}

SymbolInfo* create_error_token(const string& rule) {
	SymbolInfo* error_token = new SymbolInfo("", "error");
	error_token->set_rule(rule);
	error_token->set_line(syntax_error_line, syntax_error_line);
	error_token->set_terminal(true);
	return error_token;
}


#line 269 "y.tab.c"

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
    THEN = 258,                    /* THEN  */
    IF = 259,                      /* IF  */
    ELSE = 260,                    /* ELSE  */
    FOR = 261,                     /* FOR  */
    LOOP = 262,                    /* LOOP  */
    WHILE = 263,                   /* WHILE  */
    DO = 264,                      /* DO  */
    BREAK = 265,                   /* BREAK  */
    RETURN = 266,                  /* RETURN  */
    SWITCH = 267,                  /* SWITCH  */
    CASE = 268,                    /* CASE  */
    DEFAULT = 269,                 /* DEFAULT  */
    CONTINUE = 270,                /* CONTINUE  */
    PRINTLN = 271,                 /* PRINTLN  */
    ADDOP = 272,                   /* ADDOP  */
    INCOP = 273,                   /* INCOP  */
    DECOP = 274,                   /* DECOP  */
    RELOP = 275,                   /* RELOP  */
    ASSIGNOP = 276,                /* ASSIGNOP  */
    LOGICOP = 277,                 /* LOGICOP  */
    BITOP = 278,                   /* BITOP  */
    NOT = 279,                     /* NOT  */
    LPAREN = 280,                  /* LPAREN  */
    RPAREN = 281,                  /* RPAREN  */
    LCURL = 282,                   /* LCURL  */
    RCURL = 283,                   /* RCURL  */
    LSQUARE = 284,                 /* LSQUARE  */
    RSQUARE = 285,                 /* RSQUARE  */
    COMMA = 286,                   /* COMMA  */
    SEMICOLON = 287,               /* SEMICOLON  */
    INT = 288,                     /* INT  */
    CHAR = 289,                    /* CHAR  */
    FLOAT = 290,                   /* FLOAT  */
    DOUBLE = 291,                  /* DOUBLE  */
    VOID = 292,                    /* VOID  */
    CONST_INT = 293,               /* CONST_INT  */
    CONST_FLOAT = 294,             /* CONST_FLOAT  */
    ID = 295,                      /* ID  */
    MULOP = 296                    /* MULOP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define THEN 258
#define IF 259
#define ELSE 260
#define FOR 261
#define LOOP 262
#define WHILE 263
#define DO 264
#define BREAK 265
#define RETURN 266
#define SWITCH 267
#define CASE 268
#define DEFAULT 269
#define CONTINUE 270
#define PRINTLN 271
#define ADDOP 272
#define INCOP 273
#define DECOP 274
#define RELOP 275
#define ASSIGNOP 276
#define LOGICOP 277
#define BITOP 278
#define NOT 279
#define LPAREN 280
#define RPAREN 281
#define LCURL 282
#define RCURL 283
#define LSQUARE 284
#define RSQUARE 285
#define COMMA 286
#define SEMICOLON 287
#define INT 288
#define CHAR 289
#define FLOAT 290
#define DOUBLE 291
#define VOID 292
#define CONST_INT 293
#define CONST_FLOAT 294
#define ID 295
#define MULOP 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 204 "parser.y"

	SymbolInfo* symbol_info;

#line 408 "y.tab.c"

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
  YYSYMBOL_THEN = 3,                       /* THEN  */
  YYSYMBOL_IF = 4,                         /* IF  */
  YYSYMBOL_ELSE = 5,                       /* ELSE  */
  YYSYMBOL_FOR = 6,                        /* FOR  */
  YYSYMBOL_LOOP = 7,                       /* LOOP  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_DO = 9,                         /* DO  */
  YYSYMBOL_BREAK = 10,                     /* BREAK  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_SWITCH = 12,                    /* SWITCH  */
  YYSYMBOL_CASE = 13,                      /* CASE  */
  YYSYMBOL_DEFAULT = 14,                   /* DEFAULT  */
  YYSYMBOL_CONTINUE = 15,                  /* CONTINUE  */
  YYSYMBOL_PRINTLN = 16,                   /* PRINTLN  */
  YYSYMBOL_ADDOP = 17,                     /* ADDOP  */
  YYSYMBOL_INCOP = 18,                     /* INCOP  */
  YYSYMBOL_DECOP = 19,                     /* DECOP  */
  YYSYMBOL_RELOP = 20,                     /* RELOP  */
  YYSYMBOL_ASSIGNOP = 21,                  /* ASSIGNOP  */
  YYSYMBOL_LOGICOP = 22,                   /* LOGICOP  */
  YYSYMBOL_BITOP = 23,                     /* BITOP  */
  YYSYMBOL_NOT = 24,                       /* NOT  */
  YYSYMBOL_LPAREN = 25,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 26,                    /* RPAREN  */
  YYSYMBOL_LCURL = 27,                     /* LCURL  */
  YYSYMBOL_RCURL = 28,                     /* RCURL  */
  YYSYMBOL_LSQUARE = 29,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 30,                   /* RSQUARE  */
  YYSYMBOL_COMMA = 31,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 32,                 /* SEMICOLON  */
  YYSYMBOL_INT = 33,                       /* INT  */
  YYSYMBOL_CHAR = 34,                      /* CHAR  */
  YYSYMBOL_FLOAT = 35,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 36,                    /* DOUBLE  */
  YYSYMBOL_VOID = 37,                      /* VOID  */
  YYSYMBOL_CONST_INT = 38,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 39,               /* CONST_FLOAT  */
  YYSYMBOL_ID = 40,                        /* ID  */
  YYSYMBOL_MULOP = 41,                     /* MULOP  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_start = 43,                     /* start  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_unit = 45,                      /* unit  */
  YYSYMBOL_func_declaration = 46,          /* func_declaration  */
  YYSYMBOL_func_definition = 47,           /* func_definition  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_49_2 = 49,                      /* $@2  */
  YYSYMBOL_50_3 = 50,                      /* $@3  */
  YYSYMBOL_parameter_list = 51,            /* parameter_list  */
  YYSYMBOL_compound_statement = 52,        /* compound_statement  */
  YYSYMBOL_var_declaration = 53,           /* var_declaration  */
  YYSYMBOL_type_specifier = 54,            /* type_specifier  */
  YYSYMBOL_declaration_list = 55,          /* declaration_list  */
  YYSYMBOL_statements = 56,                /* statements  */
  YYSYMBOL_statement = 57,                 /* statement  */
  YYSYMBOL_expression_statement = 58,      /* expression_statement  */
  YYSYMBOL_variable = 59,                  /* variable  */
  YYSYMBOL_expression = 60,                /* expression  */
  YYSYMBOL_logic_expression = 61,          /* logic_expression  */
  YYSYMBOL_rel_expression = 62,            /* rel_expression  */
  YYSYMBOL_simple_expression = 63,         /* simple_expression  */
  YYSYMBOL_term = 64,                      /* term  */
  YYSYMBOL_unary_expression = 65,          /* unary_expression  */
  YYSYMBOL_factor = 66,                    /* factor  */
  YYSYMBOL_argument_list = 67,             /* argument_list  */
  YYSYMBOL_arguments = 68,                 /* arguments  */
  YYSYMBOL_lcurls = 69                     /* lcurls  */
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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   197

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  145

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   219,   219,   230,   236,   244,   250,   256,   262,   271,
     279,   288,   298,   298,   308,   308,   317,   317,   328,   338,
     348,   357,   368,   376,   384,   394,   401,   410,   420,   426,
     432,   440,   448,   456,   463,   472,   478,   486,   492,   498,
     504,   510,   517,   523,   530,   538,   547,   562,   568,   575,
     584,   599,   625,   632,   660,   667,   690,   697,   712,   719,
     731,   738,   779,   790,   806,   815,   822,   855,   861,   867,
     873,   890,   909,   916,   924,   933,   941,   950
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
  "\"end of file\"", "error", "\"invalid token\"", "THEN", "IF", "ELSE",
  "FOR", "LOOP", "WHILE", "DO", "BREAK", "RETURN", "SWITCH", "CASE",
  "DEFAULT", "CONTINUE", "PRINTLN", "ADDOP", "INCOP", "DECOP", "RELOP",
  "ASSIGNOP", "LOGICOP", "BITOP", "NOT", "LPAREN", "RPAREN", "LCURL",
  "RCURL", "LSQUARE", "RSQUARE", "COMMA", "SEMICOLON", "INT", "CHAR",
  "FLOAT", "DOUBLE", "VOID", "CONST_INT", "CONST_FLOAT", "ID", "MULOP",
  "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "$@1", "$@2", "$@3", "parameter_list",
  "compound_statement", "var_declaration", "type_specifier",
  "declaration_list", "statements", "statement", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", "lcurls", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-68)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-73)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     142,   -68,   -68,   -68,   -68,    10,    34,   -68,   -68,   -68,
     -68,     2,   -68,   -68,   -20,   -16,    65,   -68,    94,    -8,
       7,     3,   -68,    37,    33,   -15,    42,    44,   -68,    60,
      58,   -68,    71,    67,   103,   -68,   -68,    68,   -68,    71,
     -68,   -68,    77,   -68,    71,    79,    78,   -68,   -10,    86,
      88,    71,    97,   144,   101,   144,   144,   144,   -68,   -68,
     -68,   -68,    43,   -68,   -68,    14,   117,   -68,   -68,   167,
      98,   -68,   110,    83,   105,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   144,   134,    20,   144,   107,   108,     1,   -68,
     -68,   121,   144,   144,   124,   128,   -68,   -68,   -68,   -68,
     144,   -68,   144,   144,   144,   144,   137,   134,   143,   138,
     -68,   139,   -68,   -68,   150,   136,   140,   -68,   -68,   105,
     161,   -68,    20,   144,   172,    20,   149,   -68,   -68,   144,
     -68,   182,   163,   165,   -68,   -68,   -68,    20,    20,   144,
     -68,   -68,   166,   159,   -68
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     8,    28,    29,    30,     0,     0,     4,     6,     7,
       5,     0,     1,     3,     0,    33,     0,    27,     0,     0,
       0,     0,    25,     0,    16,     0,    21,     0,    26,    31,
      14,    11,     0,    12,     0,    20,    34,     0,    10,     0,
      77,    17,     0,     9,     0,    19,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    24,    47,
      68,    69,    50,    39,    37,     0,     0,    35,    38,    65,
       0,    52,    54,    56,    58,    60,    64,    13,    18,    32,
      23,    49,     0,     0,     0,     0,     0,     0,    65,    62,
      63,     0,    74,     0,    33,     0,    22,    36,    70,    71,
       0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
      46,     0,    67,    76,     0,     0,     0,    53,    55,    59,
      57,    61,     0,     0,     0,     0,     0,    66,    73,     0,
      51,    41,     0,     0,    43,    45,    75,     0,     0,     0,
      42,    40,     0,     0,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -68,   -68,   -68,   187,   -68,   -68,   -68,   -68,   -68,   -68,
      48,     8,    73,   -68,   -68,   -61,   -66,   -54,   -53,   -67,
      92,    91,    93,   -49,   -68,   -68,   -68,   146
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,     9,    44,    39,    32,    25,
      63,    64,    65,    16,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,   114,   115,    42
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      86,    88,    88,    14,    91,    97,    89,    90,    10,    18,
      12,    33,    17,    19,    10,    14,    34,   107,    80,    98,
      99,    95,    81,   108,    49,   113,    50,    51,    52,   106,
      27,    53,   109,   117,    -2,     1,    54,    55,    88,    28,
     116,   123,    15,    29,    56,    57,    88,    40,    88,    88,
      88,    88,    59,     2,    94,     3,   121,     4,    60,    61,
      62,   131,   136,    30,   134,    31,    20,     2,    92,     3,
     132,     4,    93,    11,    36,    88,   140,   141,    48,    11,
      41,    49,    35,    50,    51,    52,   142,    47,    53,    37,
      38,    26,    77,    54,    55,    23,    21,    22,    40,    43,
     103,    56,    57,   104,    40,    58,    46,    45,    79,    59,
       2,    82,     3,    83,     4,    60,    61,    62,    95,    78,
      24,    49,    85,    50,    51,    52,    87,     2,    53,     3,
     101,     4,   102,    54,    55,    95,     2,   128,     3,   110,
       4,    56,    57,     1,    40,    96,   105,   112,   111,    59,
       2,    55,     3,    19,     4,    60,    61,    62,    56,    57,
      81,    55,   -72,   122,   125,   126,    59,   129,    56,    57,
     130,   124,    60,    61,    62,     2,   127,     3,   103,     4,
     133,   135,    60,    61,    62,    98,    99,   137,   100,   138,
     139,   144,   143,    13,   118,   120,   119,    84
};

static const yytype_uint8 yycheck[] =
{
      53,    55,    56,     1,    57,    66,    55,    56,     0,    25,
       0,    26,    32,    29,     6,     1,    31,    83,    28,    18,
      19,     1,    32,    84,     4,    92,     6,     7,     8,    82,
      38,    11,    85,   100,     0,     1,    16,    17,    92,    32,
      93,   107,    40,    40,    24,    25,   100,    27,   102,   103,
     104,   105,    32,    33,    40,    35,   105,    37,    38,    39,
      40,   122,   129,    26,   125,    32,     1,    33,    25,    35,
     123,    37,    29,     0,    30,   129,   137,   138,     1,     6,
      32,     4,    40,     6,     7,     8,   139,    39,    11,    29,
      32,    18,    44,    16,    17,     1,    31,    32,    27,    32,
      17,    24,    25,    20,    27,    28,    38,    34,    30,    32,
      33,    25,    35,    25,    37,    38,    39,    40,     1,    40,
      26,     4,    25,     6,     7,     8,    25,    33,    11,    35,
      32,    37,    22,    16,    17,     1,    33,     1,    35,    32,
      37,    24,    25,     1,    27,    28,    41,    26,    40,    32,
      33,    17,    35,    29,    37,    38,    39,    40,    24,    25,
      32,    17,    26,    26,    26,    26,    32,    31,    24,    25,
      30,    28,    38,    39,    40,    33,    26,    35,    17,    37,
       8,    32,    38,    39,    40,    18,    19,     5,    21,    26,
      25,    32,    26,     6,   102,   104,   103,    51
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    33,    35,    37,    43,    44,    45,    46,    47,
      53,    54,     0,    45,     1,    40,    55,    32,    25,    29,
       1,    31,    32,     1,    26,    51,    54,    38,    32,    40,
      26,    32,    50,    26,    31,    40,    30,    29,    32,    49,
      27,    52,    69,    32,    48,    54,    38,    52,     1,     4,
       6,     7,     8,    11,    16,    17,    24,    25,    28,    32,
      38,    39,    40,    52,    53,    54,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    52,    40,    30,
      28,    32,    25,    25,    69,    25,    60,    25,    59,    65,
      65,    60,    25,    29,    40,     1,    28,    57,    18,    19,
      21,    32,    22,    17,    20,    41,    60,    58,    57,    60,
      32,    40,    26,    61,    67,    68,    60,    61,    62,    64,
      63,    65,    26,    58,    28,    26,    26,    26,     1,    31,
      30,    57,    60,     8,    57,    32,    61,     5,    26,    25,
      57,    57,    60,    26,    32
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    45,    46,
      46,    46,    48,    47,    49,    47,    50,    47,    51,    51,
      51,    51,    52,    52,    52,    53,    53,    53,    54,    54,
      54,    55,    55,    55,    55,    56,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    58,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    65,    66,    66,    66,    66,    66,
      66,    66,    67,    67,    67,    68,    68,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     6,
       6,     5,     0,     7,     0,     7,     0,     6,     4,     3,
       2,     1,     3,     3,     2,     3,     4,     3,     1,     1,
       1,     3,     6,     1,     4,     1,     2,     1,     1,     1,
       7,     5,     7,     5,     9,     5,     3,     1,     2,     2,
       1,     4,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     2,     2,     1,     1,     4,     3,     1,     1,
       2,     2,     1,     2,     0,     3,     1,     1
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
  switch (yykind)
    {
    case YYSYMBOL_IF: /* IF  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1572 "y.tab.c"
        break;

    case YYSYMBOL_ELSE: /* ELSE  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1581 "y.tab.c"
        break;

    case YYSYMBOL_FOR: /* FOR  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1590 "y.tab.c"
        break;

    case YYSYMBOL_LOOP: /* LOOP  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1599 "y.tab.c"
        break;

    case YYSYMBOL_WHILE: /* WHILE  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1608 "y.tab.c"
        break;

    case YYSYMBOL_DO: /* DO  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1617 "y.tab.c"
        break;

    case YYSYMBOL_BREAK: /* BREAK  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1626 "y.tab.c"
        break;

    case YYSYMBOL_RETURN: /* RETURN  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1635 "y.tab.c"
        break;

    case YYSYMBOL_SWITCH: /* SWITCH  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1644 "y.tab.c"
        break;

    case YYSYMBOL_CASE: /* CASE  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1653 "y.tab.c"
        break;

    case YYSYMBOL_DEFAULT: /* DEFAULT  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1662 "y.tab.c"
        break;

    case YYSYMBOL_CONTINUE: /* CONTINUE  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1671 "y.tab.c"
        break;

    case YYSYMBOL_PRINTLN: /* PRINTLN  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1680 "y.tab.c"
        break;

    case YYSYMBOL_ADDOP: /* ADDOP  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1689 "y.tab.c"
        break;

    case YYSYMBOL_INCOP: /* INCOP  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1698 "y.tab.c"
        break;

    case YYSYMBOL_DECOP: /* DECOP  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1707 "y.tab.c"
        break;

    case YYSYMBOL_RELOP: /* RELOP  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1716 "y.tab.c"
        break;

    case YYSYMBOL_ASSIGNOP: /* ASSIGNOP  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1725 "y.tab.c"
        break;

    case YYSYMBOL_LOGICOP: /* LOGICOP  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1734 "y.tab.c"
        break;

    case YYSYMBOL_BITOP: /* BITOP  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1743 "y.tab.c"
        break;

    case YYSYMBOL_NOT: /* NOT  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1752 "y.tab.c"
        break;

    case YYSYMBOL_LPAREN: /* LPAREN  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1761 "y.tab.c"
        break;

    case YYSYMBOL_RPAREN: /* RPAREN  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1770 "y.tab.c"
        break;

    case YYSYMBOL_LCURL: /* LCURL  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1779 "y.tab.c"
        break;

    case YYSYMBOL_RCURL: /* RCURL  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1788 "y.tab.c"
        break;

    case YYSYMBOL_LSQUARE: /* LSQUARE  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1797 "y.tab.c"
        break;

    case YYSYMBOL_RSQUARE: /* RSQUARE  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1806 "y.tab.c"
        break;

    case YYSYMBOL_COMMA: /* COMMA  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1815 "y.tab.c"
        break;

    case YYSYMBOL_SEMICOLON: /* SEMICOLON  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1824 "y.tab.c"
        break;

    case YYSYMBOL_INT: /* INT  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1833 "y.tab.c"
        break;

    case YYSYMBOL_CHAR: /* CHAR  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1842 "y.tab.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1851 "y.tab.c"
        break;

    case YYSYMBOL_DOUBLE: /* DOUBLE  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1860 "y.tab.c"
        break;

    case YYSYMBOL_VOID: /* VOID  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1869 "y.tab.c"
        break;

    case YYSYMBOL_CONST_INT: /* CONST_INT  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1878 "y.tab.c"
        break;

    case YYSYMBOL_CONST_FLOAT: /* CONST_FLOAT  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1887 "y.tab.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1896 "y.tab.c"
        break;

    case YYSYMBOL_MULOP: /* MULOP  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1905 "y.tab.c"
        break;

    case YYSYMBOL_start: /* start  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1914 "y.tab.c"
        break;

    case YYSYMBOL_program: /* program  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1923 "y.tab.c"
        break;

    case YYSYMBOL_unit: /* unit  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1932 "y.tab.c"
        break;

    case YYSYMBOL_func_declaration: /* func_declaration  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1941 "y.tab.c"
        break;

    case YYSYMBOL_func_definition: /* func_definition  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1950 "y.tab.c"
        break;

    case YYSYMBOL_parameter_list: /* parameter_list  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1959 "y.tab.c"
        break;

    case YYSYMBOL_compound_statement: /* compound_statement  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1968 "y.tab.c"
        break;

    case YYSYMBOL_var_declaration: /* var_declaration  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1977 "y.tab.c"
        break;

    case YYSYMBOL_type_specifier: /* type_specifier  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1986 "y.tab.c"
        break;

    case YYSYMBOL_declaration_list: /* declaration_list  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 1995 "y.tab.c"
        break;

    case YYSYMBOL_statements: /* statements  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2004 "y.tab.c"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2013 "y.tab.c"
        break;

    case YYSYMBOL_expression_statement: /* expression_statement  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2022 "y.tab.c"
        break;

    case YYSYMBOL_variable: /* variable  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2031 "y.tab.c"
        break;

    case YYSYMBOL_expression: /* expression  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2040 "y.tab.c"
        break;

    case YYSYMBOL_logic_expression: /* logic_expression  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2049 "y.tab.c"
        break;

    case YYSYMBOL_rel_expression: /* rel_expression  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2058 "y.tab.c"
        break;

    case YYSYMBOL_simple_expression: /* simple_expression  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2067 "y.tab.c"
        break;

    case YYSYMBOL_term: /* term  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2076 "y.tab.c"
        break;

    case YYSYMBOL_unary_expression: /* unary_expression  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2085 "y.tab.c"
        break;

    case YYSYMBOL_factor: /* factor  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2094 "y.tab.c"
        break;

    case YYSYMBOL_argument_list: /* argument_list  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2103 "y.tab.c"
        break;

    case YYSYMBOL_arguments: /* arguments  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2112 "y.tab.c"
        break;

    case YYSYMBOL_lcurls: /* lcurls  */
#line 208 "parser.y"
            {  
	// handles error tokens and start symbol
	free_s(((*yyvaluep).symbol_info));
}
#line 2121 "y.tab.c"
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
  case 2: /* start: program  */
#line 219 "parser.y"
                {
		print_grammar_rule("start", "program");
		(yyval.symbol_info) = new SymbolInfo("", "start");
		(yyval.symbol_info)->set_rule("start : program");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
		(yyval.symbol_info)->print_tree_node(treeout);
		// the following is being handled in %destructor
		// free_s($$);
	}
#line 2402 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 230 "parser.y"
                       {
		print_grammar_rule("program", "program unit");
		(yyval.symbol_info) = new SymbolInfo("", "program");	
		(yyval.symbol_info)->set_rule("program : program unit");
		(yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2413 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 236 "parser.y"
               {
		print_grammar_rule("program", "unit");
		(yyval.symbol_info) = new SymbolInfo("", "program");
		(yyval.symbol_info)->set_rule("program : unit");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2424 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 244 "parser.y"
                       {
		print_grammar_rule("unit", "var_declaration");
		(yyval.symbol_info) = new SymbolInfo("", "unit");
		(yyval.symbol_info)->set_rule("unit : var_declaration");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2435 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 250 "parser.y"
                       {
		print_grammar_rule("unit", "func_declaration");
		(yyval.symbol_info) = new SymbolInfo("", "unit");
		(yyval.symbol_info)->set_rule("unit : func_declaration");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2446 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 256 "parser.y"
                      {
		print_grammar_rule("unit", "func_definition");
		(yyval.symbol_info) = new SymbolInfo("", "unit");
		(yyval.symbol_info)->set_rule("unit : func_definition");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2457 "y.tab.c"
    break;

  case 8: /* unit: error  */
#line 262 "parser.y"
                {
		show_error(SYNTAX, S_UNIT, "", errorout);
		(yyval.symbol_info) = new SymbolInfo("", "unit");
		(yyval.symbol_info)->set_rule("unit : error");
		(yyval.symbol_info)->set_line(syntax_error_line, syntax_error_line);
		(yyval.symbol_info)->set_terminal(true);
	}
#line 2469 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 271 "parser.y"
                                                                            {
		print_grammar_rule("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		current_function_parameters.clear(); // resetting for this function
		(yyval.symbol_info) = new SymbolInfo("", "func_declaration");
		insert_function((yyvsp[-4].symbol_info)->get_name(), (yyvsp[-5].symbol_info)->get_data_type(), (yyvsp[-2].symbol_info)->get_param_list(), false);
		(yyval.symbol_info)->set_rule("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		(yyval.symbol_info)->add_child((yyvsp[-5].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-4].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2482 "y.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN error RPAREN SEMICOLON  */
#line 279 "parser.y"
                                                          {
		print_grammar_rule("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		current_function_parameters.clear();
		(yyval.symbol_info) = new SymbolInfo("", "func_declaration");
		insert_function((yyvsp[-4].symbol_info)->get_name(), (yyvsp[-5].symbol_info)->get_data_type(), {}, false);
		(yyval.symbol_info)->set_rule("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
		SymbolInfo* error_token = create_error_token("parameter_list : error");
		(yyval.symbol_info)->add_child((yyvsp[-5].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-4].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child(error_token); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2496 "y.tab.c"
    break;

  case 11: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 288 "parser.y"
                                                    {
		print_grammar_rule("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");
		current_function_parameters.clear();
		(yyval.symbol_info) = new SymbolInfo("", "func_declaration");
		insert_function((yyvsp[-3].symbol_info)->get_name(), (yyvsp[-4].symbol_info)->get_data_type(), {}, false);
		(yyval.symbol_info)->set_rule("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
		(yyval.symbol_info)->add_child((yyvsp[-4].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2509 "y.tab.c"
    break;

  case 12: /* $@1: %empty  */
#line 298 "parser.y"
                                                                 { 
			func_return_type = (yyvsp[-4].symbol_info)->get_data_type(); 
			insert_function((yyvsp[-3].symbol_info)->get_name(), (yyvsp[-4].symbol_info)->get_data_type(), (yyvsp[-1].symbol_info)->get_param_list(), true); }
#line 2517 "y.tab.c"
    break;

  case 13: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 301 "parser.y"
                                   {
		print_grammar_rule("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		(yyval.symbol_info) = new SymbolInfo("", "func_definition");
		(yyval.symbol_info)->set_rule("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		// notice that compound_statement is not $6, it is $7
		(yyval.symbol_info)->add_child((yyvsp[-6].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-5].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-4].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2529 "y.tab.c"
    break;

  case 14: /* $@2: %empty  */
#line 308 "parser.y"
                                                { func_return_type = (yyvsp[-4].symbol_info)->get_data_type(); }
#line 2535 "y.tab.c"
    break;

  case 15: /* func_definition: type_specifier ID LPAREN error RPAREN $@2 compound_statement  */
#line 308 "parser.y"
                                                                                                               {
		// not inserting the function if any error occurs in parameter list
		// print_grammar_rule("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		(yyval.symbol_info) = new SymbolInfo("", "func_definition");
		show_error(SYNTAX, S_PARAM_FUNC_DEFINITION, "", errorout, syntax_error_line);
		SymbolInfo* error_token = create_error_token("parameter_list : error");
		(yyval.symbol_info)->set_rule("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		(yyval.symbol_info)->add_child((yyvsp[-6].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-5].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-4].symbol_info)); (yyval.symbol_info)->add_child(error_token); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2549 "y.tab.c"
    break;

  case 16: /* $@3: %empty  */
#line 317 "parser.y"
                                          { 
			func_return_type = (yyvsp[-3].symbol_info)->get_data_type();
			insert_function((yyvsp[-2].symbol_info)->get_name(), (yyvsp[-3].symbol_info)->get_data_type(), {}, true); }
#line 2557 "y.tab.c"
    break;

  case 17: /* func_definition: type_specifier ID LPAREN RPAREN $@3 compound_statement  */
#line 320 "parser.y"
                                   {
		print_grammar_rule("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
		(yyval.symbol_info) = new SymbolInfo("", "func_definition");
		(yyval.symbol_info)->set_rule("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
		(yyval.symbol_info)->add_child((yyvsp[-5].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-4].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2568 "y.tab.c"
    break;

  case 18: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 328 "parser.y"
                                                        {
		print_grammar_rule("parameter_list", "parameter_list COMMA type_specifier ID");
		(yyval.symbol_info) = new SymbolInfo("", "parameter_list");
		(yyval.symbol_info)->set_param_list((yyvsp[-3].symbol_info)->get_param_list());
		(yyval.symbol_info)->add_param((yyvsp[0].symbol_info)->get_name(), (yyvsp[-1].symbol_info)->get_data_type());
		check_type_specifier((yyvsp[-1].symbol_info)->get_data_type(), (yyvsp[0].symbol_info)->get_name());
		current_function_parameters = (yyval.symbol_info)->get_param_list();
		(yyval.symbol_info)->set_rule("parameter_list : parameter_list COMMA type_specifier ID");
		(yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2583 "y.tab.c"
    break;

  case 19: /* parameter_list: parameter_list COMMA type_specifier  */
#line 338 "parser.y"
                                              {
		print_grammar_rule("parameter_list", "parameter_list COMMA type_specifier");
		(yyval.symbol_info) = new SymbolInfo("", "parameter_list");
		(yyval.symbol_info)->set_param_list((yyvsp[-2].symbol_info)->get_param_list());
		(yyval.symbol_info)->add_param("", (yyvsp[0].symbol_info)->get_data_type());
		check_type_specifier((yyvsp[0].symbol_info)->get_data_type(), "");
		current_function_parameters = (yyval.symbol_info)->get_param_list();
		(yyval.symbol_info)->set_rule("parameter_list : parameter_list COMMA type_specifier");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2598 "y.tab.c"
    break;

  case 20: /* parameter_list: type_specifier ID  */
#line 348 "parser.y"
                            {
		print_grammar_rule("parameter_list", "type_specifier ID");
		(yyval.symbol_info) = new SymbolInfo("", "parameter_list");
		(yyval.symbol_info)->add_param((yyvsp[0].symbol_info)->get_name(), (yyvsp[-1].symbol_info)->get_data_type());
		check_type_specifier((yyvsp[-1].symbol_info)->get_data_type(), (yyvsp[0].symbol_info)->get_name());
		current_function_parameters = (yyval.symbol_info)->get_param_list();
		(yyval.symbol_info)->set_rule("parameter_list : type_specifier ID");
		(yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2612 "y.tab.c"
    break;

  case 21: /* parameter_list: type_specifier  */
#line 357 "parser.y"
                         {
		print_grammar_rule("parameter_list", "type_specifier");
		(yyval.symbol_info) = new SymbolInfo("", "parameter_list");
		(yyval.symbol_info)->add_param("", (yyvsp[0].symbol_info)->get_data_type());
		check_type_specifier((yyvsp[0].symbol_info)->get_data_type(), "");
		current_function_parameters = (yyval.symbol_info)->get_param_list();
		(yyval.symbol_info)->set_rule("parameter_list : type_specifier");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2626 "y.tab.c"
    break;

  case 22: /* compound_statement: lcurls statements RCURL  */
#line 368 "parser.y"
                                             {
		print_grammar_rule("compound_statement", "LCURL statements RCURL");
		(yyval.symbol_info) = new SymbolInfo("", "compound_statement");
		sym->print('A', logout);
		sym->exit_scope();
		(yyval.symbol_info)->set_rule("compound_statement : LCURL statements RCURL");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2639 "y.tab.c"
    break;

  case 23: /* compound_statement: lcurls error RCURL  */
#line 376 "parser.y"
                             {
		print_grammar_rule("compound_statement", "LCURL RCURL");
		(yyval.symbol_info) = new SymbolInfo("", "compound_statement");
		sym->print('A', logout);
		sym->exit_scope();
		(yyval.symbol_info)->set_rule("compound_statement : LCURL RCURL");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2652 "y.tab.c"
    break;

  case 24: /* compound_statement: lcurls RCURL  */
#line 384 "parser.y"
                       {
		print_grammar_rule("compound_statement", "LCURL RCURL");
		(yyval.symbol_info) = new SymbolInfo("", "compound_statement");
		sym->print('A', logout);
		sym->exit_scope();
		(yyval.symbol_info)->set_rule("compound_statement : LCURL RCURL");
		(yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2665 "y.tab.c"
    break;

  case 25: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 394 "parser.y"
                                                            {
		print_grammar_rule("var_declaration", "type_specifier declaration_list SEMICOLON");
		(yyval.symbol_info) = new SymbolInfo("", "var_declaration", (yyvsp[-2].symbol_info)->get_data_type());
		insert_symbols((yyvsp[-2].symbol_info)->get_data_type(), (yyvsp[-1].symbol_info)->get_param_list());
		(yyval.symbol_info)->set_rule("var_declaration : type_specifier declaration_list SEMICOLON");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2677 "y.tab.c"
    break;

  case 26: /* var_declaration: type_specifier declaration_list error SEMICOLON  */
#line 401 "parser.y"
                                                          {
		print_grammar_rule("var_declaration", "type_specifier declaration_list SEMICOLON");	
		(yyval.symbol_info) = new SymbolInfo("", "var_declaration", (yyvsp[-3].symbol_info)->get_data_type());
		insert_symbols((yyvsp[-3].symbol_info)->get_data_type(), (yyvsp[-2].symbol_info)->get_param_list());
		show_error(SYNTAX, S_DECL_VAR_DECLARATION, "", errorout, syntax_error_line);
		(yyval.symbol_info)->set_rule("var_declaration : type_specifier declaration_list SEMICOLON");
		(yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));

	}
#line 2691 "y.tab.c"
    break;

  case 27: /* var_declaration: type_specifier error SEMICOLON  */
#line 410 "parser.y"
                                         {
		print_grammar_rule("var_declaration", "type_specifier declaration_list SEMICOLON");
		(yyval.symbol_info) = new SymbolInfo("", "var_declaration", (yyvsp[-2].symbol_info)->get_data_type());
		show_error(SYNTAX, S_DECL_VAR_DECLARATION, "", errorout, syntax_error_line);
		(yyval.symbol_info)->set_rule("var_declaration : type_specifier declaration_list SEMICOLON");
		SymbolInfo* error_token = create_error_token("declaration_list : error");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child(error_token); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2704 "y.tab.c"
    break;

  case 28: /* type_specifier: INT  */
#line 420 "parser.y"
                     {
		print_grammar_rule("type_specifier", "INT");
		(yyval.symbol_info) = new SymbolInfo("", "type_specifier", "int");
		(yyval.symbol_info)->set_rule("type_specifier : INT");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2715 "y.tab.c"
    break;

  case 29: /* type_specifier: FLOAT  */
#line 426 "parser.y"
                {
		print_grammar_rule("type_specifier", "FLOAT");
		(yyval.symbol_info) = new SymbolInfo("", "type_specifier", "float");
		(yyval.symbol_info)->set_rule("type_specifier : FLOAT");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2726 "y.tab.c"
    break;

  case 30: /* type_specifier: VOID  */
#line 432 "parser.y"
               {
		print_grammar_rule("type_specifier", "VOID");
		(yyval.symbol_info) = new SymbolInfo("", "type_specifier", "void");
		(yyval.symbol_info)->set_rule("type_specifier : VOID");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2737 "y.tab.c"
    break;

  case 31: /* declaration_list: declaration_list COMMA ID  */
#line 440 "parser.y"
                                             {
		print_grammar_rule("declaration_list", "declaration_list COMMA ID");
		(yyval.symbol_info) = new SymbolInfo("", "declaration_list");
		(yyval.symbol_info)->set_param_list((yyvsp[-2].symbol_info)->get_param_list());
		(yyval.symbol_info)->add_param((yyvsp[0].symbol_info)->get_name(), "");
		(yyval.symbol_info)->set_rule("declaration_list : declaration_list COMMA ID");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2750 "y.tab.c"
    break;

  case 32: /* declaration_list: declaration_list COMMA ID LSQUARE CONST_INT RSQUARE  */
#line 448 "parser.y"
                                                              {
		print_grammar_rule("declaration_list", "declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
		(yyval.symbol_info) = new SymbolInfo("", "declaration_list");
		(yyval.symbol_info)->set_param_list((yyvsp[-5].symbol_info)->get_param_list());
		(yyval.symbol_info)->add_param((yyvsp[-3].symbol_info)->get_name(), "ID", true);
		(yyval.symbol_info)->set_rule("declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
		(yyval.symbol_info)->add_child((yyvsp[-5].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-4].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2763 "y.tab.c"
    break;

  case 33: /* declaration_list: ID  */
#line 456 "parser.y"
             {
		print_grammar_rule("declaration_list", "ID");
		(yyval.symbol_info) = new SymbolInfo("", "declaration_list");
		(yyval.symbol_info)->add_param((yyvsp[0].symbol_info)->get_name(), "ID");
		(yyval.symbol_info)->set_rule("declaration_list : ID");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2775 "y.tab.c"
    break;

  case 34: /* declaration_list: ID LSQUARE CONST_INT RSQUARE  */
#line 463 "parser.y"
                                       {
		print_grammar_rule("declaration_list", "ID LSQUARE CONST_INT RSQUARE");
		(yyval.symbol_info) = new SymbolInfo("", "declaration_list");
		(yyval.symbol_info)->add_param((yyvsp[-3].symbol_info)->get_name(), "ID", true);
		(yyval.symbol_info)->set_rule("declaration_list : ID LSQUARE CONST_INT RSQUARE");
		(yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2787 "y.tab.c"
    break;

  case 35: /* statements: statement  */
#line 472 "parser.y"
                       {
		print_grammar_rule("statements", "statement");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "statements");
		(yyval.symbol_info)->set_rule("statements : statement");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2798 "y.tab.c"
    break;

  case 36: /* statements: statements statement  */
#line 478 "parser.y"
                               {
		print_grammar_rule("statements", "statements statement");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[-1].symbol_info)->get_name(), "statements");
		(yyval.symbol_info)->set_rule("statements : statements statement");
		(yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2809 "y.tab.c"
    break;

  case 37: /* statement: var_declaration  */
#line 486 "parser.y"
                            {
		print_grammar_rule("statement", "var_declaration");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "statement", (yyvsp[0].symbol_info)->get_data_type());
		(yyval.symbol_info)->set_rule("statement : var_declaration");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2820 "y.tab.c"
    break;

  case 38: /* statement: expression_statement  */
#line 492 "parser.y"
                               {
		print_grammar_rule("statement", "expression_statement");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "statement", (yyvsp[0].symbol_info)->get_data_type());
		(yyval.symbol_info)->set_rule("statement : expression_statement");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2831 "y.tab.c"
    break;

  case 39: /* statement: compound_statement  */
#line 498 "parser.y"
                             {
		print_grammar_rule("statement", "compound_statement");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "statement", (yyvsp[0].symbol_info)->get_data_type());
		(yyval.symbol_info)->set_rule("statement : compound_statement");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2842 "y.tab.c"
    break;

  case 40: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 504 "parser.y"
                                                                                           {
		print_grammar_rule("statement", "FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		(yyval.symbol_info) = new SymbolInfo("", "statement");
		(yyval.symbol_info)->set_rule("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		(yyval.symbol_info)->add_child((yyvsp[-6].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-5].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-4].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2853 "y.tab.c"
    break;

  case 41: /* statement: IF LPAREN expression RPAREN statement  */
#line 510 "parser.y"
                                                           {
		// use the precedence of THEN here
		print_grammar_rule("statement", "IF LPAREN expression RPAREN statement %prec THEN");
		(yyval.symbol_info) = new SymbolInfo("", "statement");
		(yyval.symbol_info)->set_rule("statement : IF LPAREN expression RPAREN statement");
		(yyval.symbol_info)->add_child((yyvsp[-4].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2865 "y.tab.c"
    break;

  case 42: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 517 "parser.y"
                                                               {
		print_grammar_rule("statement", "IF LPAREN expression RPAREN statement ELSE statement");
		(yyval.symbol_info) = new SymbolInfo("", "statement");
		(yyval.symbol_info)->set_rule("statement : IF LPAREN expression RPAREN statement ELSE statement");
		(yyval.symbol_info)->add_child((yyvsp[-6].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-5].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-4].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2876 "y.tab.c"
    break;

  case 43: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 523 "parser.y"
                                                   {
		print_grammar_rule("statement", "WHILE LPAREN expression RPAREN statement");
		(yyval.symbol_info) = new SymbolInfo("", "statement");
		(yyval.symbol_info)->set_rule("statement : WHILE LPAREN expression RPAREN statement");
		(yyval.symbol_info)->add_child((yyvsp[-4].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));

	}
#line 2888 "y.tab.c"
    break;

  case 44: /* statement: LOOP lcurls statement RCURL WHILE LPAREN expression RPAREN SEMICOLON  */
#line 530 "parser.y"
                                                                             {
		print_grammar_rule("statement", "LOOP LCURL statement RCURL WHILE LPAREN expression RPAREN SEMICOLON");
		(yyval.symbol_info) = new SymbolInfo("", "statement");
		(yyval.symbol_info)->set_rule("statement : LOOP LCURL statement RCURL WHILE LPAREN expression RPAREN SEMICOLON");
		(yyval.symbol_info)->add_child((yyvsp[-8].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-7].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-6].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-5].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-4].symbol_info));
		(yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
		
	}
#line 2901 "y.tab.c"
    break;

  case 45: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 538 "parser.y"
                                             {
		print_grammar_rule("statement", "PRINTLN LPAREN ID RPAREN SEMICOLON");
		(yyval.symbol_info) = new SymbolInfo("", "statement");
		if (sym->search((yyvsp[-2].symbol_info)->get_name(), 'A') == nullptr) {
			show_error(SEMANTIC, UNDECLARED_VARIABLE, (yyvsp[-2].symbol_info)->get_name(), errorout);
		}
		(yyval.symbol_info)->set_rule("statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
		(yyval.symbol_info)->add_child((yyvsp[-4].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2915 "y.tab.c"
    break;

  case 46: /* statement: RETURN expression SEMICOLON  */
#line 547 "parser.y"
                                      {
		print_grammar_rule("statement", "RETURN expression SEMICOLON");
		(yyval.symbol_info) = new SymbolInfo("", "statement");
		(yyval.symbol_info)->set_rule("statement : RETURN expression SEMICOLON");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
		// adding return type check here
		if (func_return_type == "VOID") {
			show_error(SEMANTIC, RETURNING_IN_VOID, "", errorout);
		}
		else if (func_return_type == "INT" && (yyvsp[-1].symbol_info)->get_data_type() == "FLOAT") {
			show_error(WARNING, FLOAT_TO_INT, "", errorout);
		}
	}
#line 2933 "y.tab.c"
    break;

  case 47: /* expression_statement: SEMICOLON  */
#line 562 "parser.y"
                                 {
		print_grammar_rule("expression_statement", "SEMICOLON");
		(yyval.symbol_info) = new SymbolInfo("", "expression_statement");
		(yyval.symbol_info)->set_rule("expression_statement : SEMICOLON");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2944 "y.tab.c"
    break;

  case 48: /* expression_statement: expression SEMICOLON  */
#line 568 "parser.y"
                               {
		print_grammar_rule("expression_statement", "expression SEMICOLON");
		(yyval.symbol_info) = new SymbolInfo("", "expression_statement");
		(yyval.symbol_info)->set_data_type((yyvsp[-1].symbol_info)->get_data_type()); // result of an expression will have a certain data type
		(yyval.symbol_info)->set_rule("expression_statement : expression SEMICOLON");
		(yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2956 "y.tab.c"
    break;

  case 49: /* expression_statement: error SEMICOLON  */
#line 575 "parser.y"
                          {
		show_error(SYNTAX, S_EXP_STATEMENT, "", errorout, syntax_error_line);
		(yyval.symbol_info) = new SymbolInfo("", "expression_statement");
		(yyval.symbol_info)->set_rule("expression_statement : expression SEMICOLON");
		SymbolInfo* error_token = create_error_token("expression : error");
		(yyval.symbol_info)->add_child(error_token); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2968 "y.tab.c"
    break;

  case 50: /* variable: ID  */
#line 584 "parser.y"
              {
		print_grammar_rule("variable", "ID");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "VARIABLE", (yyvsp[0].symbol_info)->get_data_type());
		
		SymbolInfo* res = sym->search((yyvsp[0].symbol_info)->get_name(), 'A');
		if (res == nullptr) {
			show_error(SEMANTIC, UNDECLARED_VARIABLE, (yyvsp[0].symbol_info)->get_name(), errorout);
		}
		else {
			(yyval.symbol_info)->set_data_type(res->get_data_type());
			(yyval.symbol_info)->set_array(res->is_array());
		}
		(yyval.symbol_info)->set_rule("variable : ID");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 2988 "y.tab.c"
    break;

  case 51: /* variable: ID LSQUARE expression RSQUARE  */
#line 599 "parser.y"
                                        {
		print_grammar_rule("variable", "ID LSQUARE expression RSQUARE");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[-3].symbol_info)->get_name(), "VARIABLE", (yyvsp[-3].symbol_info)->get_data_type());
		
		SymbolInfo* res = sym->search((yyvsp[-3].symbol_info)->get_name(), 'A');
		// it has to be an array now
		if (res == nullptr) {
			show_error(SEMANTIC, UNDECLARED_VARIABLE, (yyvsp[-3].symbol_info)->get_name(), errorout);
		}
		else if (!res->is_array()) {
			// declared as a normal variable, but used like an array, so error
			show_error(SEMANTIC, ERROR_AS_ARRAY, (yyvsp[-3].symbol_info)->get_name(), errorout);
		}
		else if ((yyvsp[-1].symbol_info)->get_data_type() != "INT") {
			// array index is not an integer, so error
			show_error(SEMANTIC, INDEX_NOT_INT, (yyvsp[-3].symbol_info)->get_name(), errorout);
		}
		else {
			(yyval.symbol_info)->set_data_type(res->get_data_type());
			(yyval.symbol_info)->set_array(false); // if a is an int array, a[5] is also an int, but not an array
		}
		(yyval.symbol_info)->set_rule("variable : ID LSQUARE expression RSQUARE");
		(yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3017 "y.tab.c"
    break;

  case 52: /* expression: logic_expression  */
#line 625 "parser.y"
                              {
		print_grammar_rule("expression", "logic_expression");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "expression", (yyvsp[0].symbol_info)->get_data_type());
		(yyval.symbol_info)->set_array((yyvsp[0].symbol_info)->is_array());
		(yyval.symbol_info)->set_rule("expression : logic_expression");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3029 "y.tab.c"
    break;

  case 53: /* expression: variable ASSIGNOP logic_expression  */
#line 632 "parser.y"
                                             {
		print_grammar_rule("expression", "variable ASSIGNOP logic_expression");
		(yyval.symbol_info) = new SymbolInfo("", "expression");
		if ((yyvsp[-2].symbol_info)->is_array() && !(yyvsp[0].symbol_info)->is_array()) {
			show_error(SEMANTIC, ARRAY_AS_VAR, (yyvsp[-2].symbol_info)->get_name(), errorout);
		}
		else if ((yyvsp[-2].symbol_info)->get_data_type() == "VOID" || (yyvsp[0].symbol_info)->get_data_type() == "VOID") {
			show_error(SEMANTIC, VOID_USAGE, "", errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
		}
		else if ((yyvsp[-2].symbol_info)->get_data_type() == "ERROR" || (yyvsp[0].symbol_info)->get_data_type() == "ERROR") {
			// show_error(SEMANTIC, TYPE_ERROR, "", errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
		}
		else if ((yyvsp[-2].symbol_info)->get_data_type() == "INT") {
			if ((yyvsp[0].symbol_info)->get_data_type() == "FLOAT") {
				show_error(WARNING, FLOAT_TO_INT, "", errorout);
			}
			(yyval.symbol_info)->set_data_type("INT");
		}
		else {
			(yyval.symbol_info)->set_data_type("FLOAT");
		}
		(yyval.symbol_info)->set_rule("expression : variable ASSIGNOP logic_expression");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3060 "y.tab.c"
    break;

  case 54: /* logic_expression: rel_expression  */
#line 660 "parser.y"
                                  {
		print_grammar_rule("logic_expression", "rel_expression");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "logic_expression", (yyvsp[0].symbol_info)->get_data_type());
		(yyval.symbol_info)->set_array((yyvsp[0].symbol_info)->is_array());
		(yyval.symbol_info)->set_rule("logic_expression : rel_expression");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3072 "y.tab.c"
    break;

  case 55: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 667 "parser.y"
                                                {
		print_grammar_rule("logic_expression", "rel_expression LOGICOP rel_expression");
		(yyval.symbol_info) = new SymbolInfo("", "logic_expression");
		if ((yyvsp[-2].symbol_info)->get_data_type() == "VOID" || (yyvsp[0].symbol_info)->get_data_type() == "VOID") {
			show_error(SEMANTIC, VOID_USAGE, "", errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
		}
		else if ((yyvsp[-2].symbol_info)->get_data_type() == "ERROR" || (yyvsp[0].symbol_info)->get_data_type() == "ERROR") {
			// show_error(SEMANTIC, TYPE_ERROR, "", errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
		}
		else if ((yyvsp[-2].symbol_info)->get_data_type() == "FLOAT" || (yyvsp[0].symbol_info)->get_data_type() == "FLOAT") {
			show_error(WARNING, LOGICAL_FLOAT, "", errorout);
			(yyval.symbol_info)->set_data_type("INT");
		}
		else {
			(yyval.symbol_info)->set_data_type("INT");
		}
		(yyval.symbol_info)->set_rule("logic_expression : rel_expression LOGICOP rel_expression");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3098 "y.tab.c"
    break;

  case 56: /* rel_expression: simple_expression  */
#line 690 "parser.y"
                                   {
		print_grammar_rule("rel_expression", "simple_expression");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "rel_expression", (yyvsp[0].symbol_info)->get_data_type());
		(yyval.symbol_info)->set_array((yyvsp[0].symbol_info)->is_array()); // will need in function argument type checking
		(yyval.symbol_info)->set_rule("rel_expression : simple_expression");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3110 "y.tab.c"
    break;

  case 57: /* rel_expression: simple_expression RELOP simple_expression  */
#line 697 "parser.y"
                                                    {
		print_grammar_rule("rel_expression", "simple_expression RELOP simple_expression");
		(yyval.symbol_info) = new SymbolInfo("", "rel_expression");
		if ((yyvsp[-2].symbol_info)->get_data_type() == "VOID" || (yyvsp[0].symbol_info)->get_data_type() == "VOID") {
			show_error(SEMANTIC, VOID_USAGE, "", errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
		}
		else {
			(yyval.symbol_info)->set_data_type("INT"); // result of any comparison should be boolean in fact
		}
		(yyval.symbol_info)->set_rule("rel_expression : simple_expression RELOP simple_expression");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3128 "y.tab.c"
    break;

  case 58: /* simple_expression: term  */
#line 712 "parser.y"
                         {
		print_grammar_rule("simple_expression", "term");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "simple_expression", (yyvsp[0].symbol_info)->get_data_type());
		(yyval.symbol_info)->set_array((yyvsp[0].symbol_info)->is_array());
		(yyval.symbol_info)->set_rule("simple_expression : term");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3140 "y.tab.c"
    break;

  case 59: /* simple_expression: simple_expression ADDOP term  */
#line 719 "parser.y"
                                       {
		print_grammar_rule("simple_expression", "simple_expression ADDOP term");
		(yyval.symbol_info) = new SymbolInfo("", "simple_expression");
		if ((yyvsp[-2].symbol_info)->get_data_type() == "VOID" || (yyvsp[0].symbol_info)->get_data_type() == "VOID") {
			show_error(SEMANTIC, VOID_USAGE, "", errorout);
		}
		(yyval.symbol_info)->set_data_type(type_cast((yyvsp[-2].symbol_info)->get_data_type(), (yyvsp[0].symbol_info)->get_data_type()));
		(yyval.symbol_info)->set_rule("simple_expression : simple_expression ADDOP term");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3155 "y.tab.c"
    break;

  case 60: /* term: unary_expression  */
#line 731 "parser.y"
                        {
		print_grammar_rule("term", "unary_expression");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "term", (yyvsp[0].symbol_info)->get_data_type());
		(yyval.symbol_info)->set_array((yyvsp[0].symbol_info)->is_array());
		(yyval.symbol_info)->set_rule("term : unary_expression");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3167 "y.tab.c"
    break;

  case 61: /* term: term MULOP unary_expression  */
#line 738 "parser.y"
                                      {
		print_grammar_rule("term", "term MULOP unary_expression");
		(yyval.symbol_info) = new SymbolInfo("", "term");
		if ((yyvsp[-2].symbol_info)->get_data_type() == "VOID" || (yyvsp[0].symbol_info)->get_data_type() == "VOID") {
			show_error(SEMANTIC, VOID_USAGE, "", errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
		}
		else if ((yyvsp[-2].symbol_info)->get_data_type() == "ERROR" || (yyvsp[0].symbol_info)->get_data_type() == "ERROR") {
			// show_error(SEMANTIC, TYPE_ERROR, "", errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
		}
		else if ((yyvsp[-1].symbol_info)->get_name() == "%") {
			if ((yyvsp[-2].symbol_info)->get_data_type() == "FLOAT" || (yyvsp[0].symbol_info)->get_data_type() == "FLOAT") {
				show_error(SEMANTIC, MOD_OPERAND, "", errorout);
				(yyval.symbol_info)->set_data_type("ERROR");
			}
			else if (is_zero((yyvsp[0].symbol_info)->get_name())) {
				show_error(WARNING, MOD_BY_ZERO, "", errorout);
				(yyval.symbol_info)->set_data_type("ERROR");
			}
			else {
				(yyval.symbol_info)->set_data_type("INT");
			}
		}
		else if ((yyvsp[-1].symbol_info)->get_name() == "/") {
			if (is_zero((yyvsp[0].symbol_info)->get_name())) {
				show_error(WARNING, DIV_BY_ZERO, "", errorout);
				(yyval.symbol_info)->set_data_type("ERROR");
			}
			else {
				(yyval.symbol_info)->set_data_type(type_cast((yyvsp[-2].symbol_info)->get_data_type(), (yyvsp[0].symbol_info)->get_data_type()));
			}
		}
		else if ((yyvsp[-1].symbol_info)->get_name() == "*") {
			(yyval.symbol_info)->set_data_type(type_cast((yyvsp[-2].symbol_info)->get_data_type(), (yyvsp[0].symbol_info)->get_data_type()));
		}
		(yyval.symbol_info)->set_rule("term : term MULOP unary_expression");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3211 "y.tab.c"
    break;

  case 62: /* unary_expression: ADDOP unary_expression  */
#line 779 "parser.y"
                                          {
		print_grammar_rule("unary_expression", "ADDOP unary_expression");
		(yyval.symbol_info) = new SymbolInfo("", "unary_expression");
		if ((yyvsp[0].symbol_info)->get_data_type() == "VOID") {
			show_error(SEMANTIC, VOID_USAGE, "", errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
		}
		else (yyval.symbol_info)->set_data_type((yyvsp[0].symbol_info)->get_data_type());
		(yyval.symbol_info)->set_rule("unary_expression : ADDOP unary_expression");
		(yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3227 "y.tab.c"
    break;

  case 63: /* unary_expression: NOT unary_expression  */
#line 790 "parser.y"
                               {
		print_grammar_rule("unary_expression", "NOT unary_expression");
		(yyval.symbol_info) = new SymbolInfo("", "unary_expression");
		bool ok = true;
		if ((yyvsp[0].symbol_info)->get_data_type() == "VOID") {
			show_error(SEMANTIC, VOID_USAGE, "", errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
			ok = false;
		}
		else if ((yyvsp[0].symbol_info)->get_data_type() == "FLOAT") {
			show_error(WARNING, BITWISE_FLOAT, "", errorout);
		}
		if (ok) (yyval.symbol_info)->set_data_type("INT");
		(yyval.symbol_info)->set_rule("unary_expression : NOT unary_expression");
		(yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3248 "y.tab.c"
    break;

  case 64: /* unary_expression: factor  */
#line 806 "parser.y"
                 {
		print_grammar_rule("unary_expression", "factor");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "unary_expression", (yyvsp[0].symbol_info)->get_data_type());
		(yyval.symbol_info)->set_array((yyvsp[0].symbol_info)->is_array());
		(yyval.symbol_info)->set_rule("unary_expression : factor");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3260 "y.tab.c"
    break;

  case 65: /* factor: variable  */
#line 815 "parser.y"
                  {
		print_grammar_rule("factor", "variable");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "factor", (yyvsp[0].symbol_info)->get_data_type());
		(yyval.symbol_info)->set_array((yyvsp[0].symbol_info)->is_array());
		(yyval.symbol_info)->set_rule("factor : variable");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3272 "y.tab.c"
    break;

  case 66: /* factor: ID LPAREN argument_list RPAREN  */
#line 822 "parser.y"
                                         {
		print_grammar_rule("factor", "ID LPAREN argument_list RPAREN");
		(yyval.symbol_info) = new SymbolInfo("", "factor");
		SymbolInfo* res = sym->search((yyvsp[-3].symbol_info)->get_name(), 'A');
		if (res == nullptr) {
			show_error(SEMANTIC, UNDECLARED_FUNCTION, (yyvsp[-3].symbol_info)->get_name(), errorout);
		}
		else if (res->get_func_type() == NONE) {
			show_error(SEMANTIC, NOT_A_FUNCTION, (yyvsp[-3].symbol_info)->get_name(), errorout);
		}
		else if (res->get_param_list().size() < (yyvsp[-1].symbol_info)->get_param_list().size()) {
			show_error(SEMANTIC, TOO_MANY_ARGUMENTS, (yyvsp[-3].symbol_info)->get_name(), errorout);
		}
		else if (res->get_param_list().size() > (yyvsp[-1].symbol_info)->get_param_list().size()) {
			show_error(SEMANTIC, TOO_FEW_ARGUMENTS, (yyvsp[-3].symbol_info)->get_name(), errorout);
		}
		else {
			vector<Param> now = res->get_param_list();
			vector<Param> they = (yyvsp[-1].symbol_info)->get_param_list();
			for (int i = 0; i < now.size(); i++) {
				if ((now[i].data_type != they[i].data_type) || (now[i].is_array != they[i].is_array)) {
					// cerr << "Function: " << res->get_name() << endl;
					// cerr << "original: " << now[i].data_type << " given: " << they[i].data_type << " name: " << now[i].name << " line " << line_count << endl;
					string str = to_string(i + 1);
					str += " of \'" + (yyvsp[-3].symbol_info)->get_name() + "\'";
					show_error(SEMANTIC, ARG_TYPE_MISMATCH, str, errorout);
				}
			}
			(yyval.symbol_info)->set_data_type(res->get_data_type());
		}
		(yyval.symbol_info)->set_rule("factor : ID LPAREN argument_list RPAREN");
		(yyval.symbol_info)->add_child((yyvsp[-3].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3310 "y.tab.c"
    break;

  case 67: /* factor: LPAREN expression RPAREN  */
#line 855 "parser.y"
                                   {
		print_grammar_rule("factor", "LPAREN expression RPAREN");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[-1].symbol_info)->get_name(), "factor", (yyvsp[-1].symbol_info)->get_data_type());
		(yyval.symbol_info)->set_rule("factor : LPAREN expression RPAREN");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3321 "y.tab.c"
    break;

  case 68: /* factor: CONST_INT  */
#line 861 "parser.y"
                    {
		print_grammar_rule("factor", "CONST_INT");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "factor", "INT");
		(yyval.symbol_info)->set_rule("factor : CONST_INT");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3332 "y.tab.c"
    break;

  case 69: /* factor: CONST_FLOAT  */
#line 867 "parser.y"
                      {
		print_grammar_rule("factor", "CONST_FLOAT");
		(yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->get_name(), "factor", "FLOAT");
		(yyval.symbol_info)->set_rule("factor : CONST_FLOAT");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3343 "y.tab.c"
    break;

  case 70: /* factor: variable INCOP  */
#line 873 "parser.y"
                         {
		print_grammar_rule("factor", "variable INCOP");
		(yyval.symbol_info) = new SymbolInfo("", "factor");
		if ((yyvsp[-1].symbol_info)->get_data_type() == "VOID") {
			show_error(SEMANTIC, VOID_USAGE, (yyvsp[-1].symbol_info)->get_name(), errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
		}
		else if ((yyvsp[-1].symbol_info)->get_data_type() == "ERROR") {
			// show_error(SEMANTIC, TYPE_ERROR, $1->get_name(), errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
		}
		else {
			(yyval.symbol_info)->set_data_type((yyvsp[-1].symbol_info)->get_data_type());
		}
		(yyval.symbol_info)->set_rule("factor : variable INCOP");
		(yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3365 "y.tab.c"
    break;

  case 71: /* factor: variable DECOP  */
#line 890 "parser.y"
                         {
		print_grammar_rule("factor", "variable DECOP");
		(yyval.symbol_info) = new SymbolInfo("", "factor");
		if ((yyvsp[-1].symbol_info)->get_data_type() == "VOID") {
			show_error(SEMANTIC, VOID_USAGE, "", errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
		}
		else if ((yyvsp[-1].symbol_info)->get_data_type() == "ERROR") {
			// show_error(SEMANTIC, TYPE_ERROR, "", errorout);
			(yyval.symbol_info)->set_data_type("ERROR");
		}
		else {
			(yyval.symbol_info)->set_data_type((yyvsp[-1].symbol_info)->get_data_type());
		}
		(yyval.symbol_info)->set_rule("factor : variable DECOP");
		(yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3387 "y.tab.c"
    break;

  case 72: /* argument_list: arguments  */
#line 909 "parser.y"
                          {
		print_grammar_rule("argument_list", "arguments");
		(yyval.symbol_info) = new SymbolInfo("", "argument_list");
		(yyval.symbol_info)->set_param_list((yyvsp[0].symbol_info)->get_param_list());
		(yyval.symbol_info)->set_rule("argument_list : arguments");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3399 "y.tab.c"
    break;

  case 73: /* argument_list: arguments error  */
#line 916 "parser.y"
                          {
		print_grammar_rule("argument_list", "arguments");
		show_error(SYNTAX, S_ARG_LIST, "", errorout, syntax_error_line);
		(yyval.symbol_info) = new SymbolInfo("", "argument_list");
		(yyval.symbol_info)->set_param_list((yyvsp[-1].symbol_info)->get_param_list());
		(yyval.symbol_info)->set_rule("argument_list : arguments");
		(yyval.symbol_info)->add_child((yyvsp[-1].symbol_info));
	}
#line 3412 "y.tab.c"
    break;

  case 74: /* argument_list: %empty  */
#line 924 "parser.y"
          {
		// empty argument list, as one of the example of the sample suggests
		print_grammar_rule("argument_list", "");
		(yyval.symbol_info) = new SymbolInfo("", "argument_list");
		(yyval.symbol_info)->set_rule("argument_list : ");
		(yyval.symbol_info)->set_line(line_count, line_count);
	}
#line 3424 "y.tab.c"
    break;

  case 75: /* arguments: arguments COMMA logic_expression  */
#line 933 "parser.y"
                                             {
		print_grammar_rule("arguments", "arguments COMMA logic_expression");
		(yyval.symbol_info) = new SymbolInfo("", "arguments");
		(yyval.symbol_info)->set_param_list((yyvsp[-2].symbol_info)->get_param_list());
		(yyval.symbol_info)->add_param((yyvsp[0].symbol_info)->get_name(), (yyvsp[0].symbol_info)->get_data_type(), (yyvsp[0].symbol_info)->is_array());
		(yyval.symbol_info)->set_rule("arguments : arguments COMMA logic_expression");
		(yyval.symbol_info)->add_child((yyvsp[-2].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[-1].symbol_info)); (yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3437 "y.tab.c"
    break;

  case 76: /* arguments: logic_expression  */
#line 941 "parser.y"
                           {
		print_grammar_rule("arguments", "logic_expression");
		(yyval.symbol_info) = new SymbolInfo("", "arguments");
		(yyval.symbol_info)->add_param((yyvsp[0].symbol_info)->get_name(), (yyvsp[0].symbol_info)->get_data_type(), (yyvsp[0].symbol_info)->is_array());
		(yyval.symbol_info)->set_rule("arguments : logic_expression");
		(yyval.symbol_info)->add_child((yyvsp[0].symbol_info));
	}
#line 3449 "y.tab.c"
    break;

  case 77: /* lcurls: LCURL  */
#line 950 "parser.y"
               {
		(yyval.symbol_info) = (yyvsp[0].symbol_info);
		sym->enter_scope();
		// why am I inserting symbols here? so that the parameters can be recognized in the newly created scope
		// but remember, in case of function prototypes, even though I am not inserting the symbols, I am still checking in 
		// insert_function() whether two non-empty names are same or not
		for (const Param& they : current_function_parameters) {
			if (they.name == "") {// nameless, no need to insert 
				// show_error(SYNTAX, S_PARAM_NAMELESS, "", errorout);
				continue;
			}
			SymbolInfo* another = new SymbolInfo(they.name, "ID", they.data_type);
			another->set_array(they.is_array);
			if (!sym->insert(another)) {
				// insertion failed
				show_error(SEMANTIC, PARAM_REDEFINITION, another->get_name(), errorout);
				// in sample output, after any failure, the next arguments are not inserted to the symbol table
				// so we will break the loop
				free_s(another);
				break;
			}
		}
		current_function_parameters.clear();
	}
#line 3478 "y.tab.c"
    break;


#line 3482 "y.tab.c"

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

#line 976 "parser.y"


int main(int argc,char *argv[]) {	
	if (argc < 2) {
		cout << "Please Provide Input File\n";
		exit(1);
	}
	FILE *fp;
	if((fp = fopen(argv[1], "r")) == NULL) {
		cout << "Cannot Open Input File\n";
		exit(1);
	}

	treeout.open("parsetree.txt");
	errorout.open("error.txt");
	logout.open("log.txt");

	sym = new SymbolTable(BUCKET_SIZE);

	yyin = fp;
	yyparse();

	fclose(yyin);
	delete sym;
	current_function_parameters.clear();

	logout << "Total Lines: " << line_count << endl;
	logout << "Total Errors: " << error_count << endl;
	treeout.close();
	errorout.close();
	logout.close();
	return 0;
}

