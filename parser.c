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
#line 1 "proiect.y"

#include <iostream>
#include <vector>
#include "SymbolTable.h"
#include <cstring>
//#include <variant>
#include <string>
#include <stdio.h>
#include <stack>
#include <queue>
//#include "class.h"
using namespace std;
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);

enum Type
{
    OPERATOR,
    NUMBER,
    IDENTIFIER,
    OTHER
};

struct Expr{
    const char* type;
    const char* name;
    const char* value;
     int intvalue;
    float floatvalue;
    bool boolvalue;
    char charvalue;
    char *strvalue;
};


struct root_data
{
    char op;
    struct Expr *expr_ptr;
    int number;
    char *other;
};
class ASTnode
{
    int exprtype;
    struct root_data *root;
    ASTnode *left;
    ASTnode *right;

    ASTnode *BuildAST(struct root_data *root, ASTnode *left, ASTnode *right, int type)
    {
        ASTnode *newnode = new ASTnode;
        newnode->root = root;
        newnode->exprtype = type;
        newnode->left = left;
        newnode->right = right;
        return newnode;
    }
    int Eval(ASTnode *node)
    {
        if (node->exprtype == Type::NUMBER)
            return node->root->number;
        else if (node->exprtype == Type::IDENTIFIER)
            return node->root->expr_ptr->intvalue;
        else if (node->exprtype == Type::OPERATOR)
        {
            if (node->root->op == '+')
                return Eval(node->left) + Eval(node->right);
            else if (node->root->op == '-')
                return Eval(node->left) - Eval(node->right);
            else if (node->root->op == '*')
                return Eval(node->left) * Eval(node->right);
            else if (node->root->op == '/')
                return Eval(node->left) / Eval(node->right);
            else if (node->root->op == '%')
                return Eval(node->left) % Eval(node->right);
        }
        else if (node->exprtype == Type::OTHER)
            return 0;
    }
    stack<ASTnode*> stiva_noduri;
    void delete_ast(ASTnode *root)
    {
        if (root != NULL)
        {
            if (root->root->other != NULL)
            {
                free(root->root->other);
            } // exprptr nu este dealocat, e pointer la variabila din tabelul de simboluri
            free(root->root);
            delete_ast(root->left);
            delete_ast(root->right);
            delete root;
        }
    }
    void delete_stack()
    {
        while(!stiva_noduri.empty())
        {
            delete_ast(stiva_noduri.top());
            stiva_noduri.pop();
        }
    }
    void build_ast_stack(char oper)
    {
        struct root_data* data=(struct root_data*)calloc(1,sizeof(struct root_data));
        data->op=oper;

        if(stiva_noduri.size()>=2)
        {
            ASTnode* right=stiva_noduri.top();
            stiva_noduri.pop();

            ASTnode* left=stiva_noduri.top();
            stiva_noduri.pop();
            //construieste un nod dou folosind cele doua noduri extrase si operatorul
            ASTnode* root=BuildAST(data,left,right,Type::OPERATOR);
            stiva_noduri.push(root);
        }
        else {
            cout<<"Eror, not enough nodes on the stack for operator "<<oper<<endl;
        }
    }
};

 class SymbolTable listSymbols;
 stack<const char *> scopeStack;
 queue<char *> listTypeParamQueue;
 vector<int> listavalori;

 const char* currentClass;

vector<Expr*> globalParamList;

 

#line 211 "parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_WHILE = 5,                      /* WHILE  */
  YYSYMBOL_FOR = 6,                        /* FOR  */
  YYSYMBOL_CLASS = 7,                      /* CLASS  */
  YYSYMBOL_CONSTANT = 8,                   /* CONSTANT  */
  YYSYMBOL_RETURN = 9,                     /* RETURN  */
  YYSYMBOL_EVAL = 10,                      /* EVAL  */
  YYSYMBOL_TYPEOF = 11,                    /* TYPEOF  */
  YYSYMBOL_BEGIN_PROGR = 12,               /* BEGIN_PROGR  */
  YYSYMBOL_END_PROGR = 13,                 /* END_PROGR  */
  YYSYMBOL_ASSIGN = 14,                    /* ASSIGN  */
  YYSYMBOL_LOGIC_AND = 15,                 /* LOGIC_AND  */
  YYSYMBOL_LOGIC_OR = 16,                  /* LOGIC_OR  */
  YYSYMBOL_LESS = 17,                      /* LESS  */
  YYSYMBOL_LESS_EQ = 18,                   /* LESS_EQ  */
  YYSYMBOL_GRT = 19,                       /* GRT  */
  YYSYMBOL_GRT_EQ = 20,                    /* GRT_EQ  */
  YYSYMBOL_EQ = 21,                        /* EQ  */
  YYSYMBOL_NOT_EQ = 22,                    /* NOT_EQ  */
  YYSYMBOL_NOT = 23,                       /* NOT  */
  YYSYMBOL_INT = 24,                       /* INT  */
  YYSYMBOL_FLOAT = 25,                     /* FLOAT  */
  YYSYMBOL_CHAR = 26,                      /* CHAR  */
  YYSYMBOL_STRING = 27,                    /* STRING  */
  YYSYMBOL_BOOL = 28,                      /* BOOL  */
  YYSYMBOL_ID = 29,                        /* ID  */
  YYSYMBOL_CLASS_ID = 30,                  /* CLASS_ID  */
  YYSYMBOL_FUN_ID = 31,                    /* FUN_ID  */
  YYSYMBOL_BOOLEAN = 32,                   /* BOOLEAN  */
  YYSYMBOL_NR_INT = 33,                    /* NR_INT  */
  YYSYMBOL_NR_FLOAT = 34,                  /* NR_FLOAT  */
  YYSYMBOL_35_ = 35,                       /* '+'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_37_ = 37,                       /* '*'  */
  YYSYMBOL_38_ = 38,                       /* '/'  */
  YYSYMBOL_39_ = 39,                       /* '%'  */
  YYSYMBOL_40_ = 40,                       /* '{'  */
  YYSYMBOL_41_ = 41,                       /* '}'  */
  YYSYMBOL_42_ = 42,                       /* '['  */
  YYSYMBOL_43_ = 43,                       /* ']'  */
  YYSYMBOL_44_ = 44,                       /* '('  */
  YYSYMBOL_45_ = 45,                       /* ')'  */
  YYSYMBOL_46_ = 46,                       /* ';'  */
  YYSYMBOL_47_ = 47,                       /* '.'  */
  YYSYMBOL_48_ = 48,                       /* ','  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_progr = 50,                     /* progr  */
  YYSYMBOL_declarations_glob_variable = 51, /* declarations_glob_variable  */
  YYSYMBOL_functions_glob_def = 52,        /* functions_glob_def  */
  YYSYMBOL_class_list = 53,                /* class_list  */
  YYSYMBOL_main_fun = 54,                  /* main_fun  */
  YYSYMBOL_begin_progr = 55,               /* begin_progr  */
  YYSYMBOL_end_progr = 56,                 /* end_progr  */
  YYSYMBOL_decl = 57,                      /* decl  */
  YYSYMBOL_variable = 58,                  /* variable  */
  YYSYMBOL_array_decl = 59,                /* array_decl  */
  YYSYMBOL_array_init = 60,                /* array_init  */
  YYSYMBOL_array_usage = 61,               /* array_usage  */
  YYSYMBOL_dimensiune = 62,                /* dimensiune  */
  YYSYMBOL_variable_decl = 63,             /* variable_decl  */
  YYSYMBOL_variable_def = 64,              /* variable_def  */
  YYSYMBOL_constant_def = 65,              /* constant_def  */
  YYSYMBOL_tip_variabila = 66,             /* tip_variabila  */
  YYSYMBOL_class_def = 67,                 /* class_def  */
  YYSYMBOL_class_header = 68,              /* class_header  */
  YYSYMBOL_class_body = 69,                /* class_body  */
  YYSYMBOL_data_members = 70,              /* data_members  */
  YYSYMBOL_memmber_functions = 71,         /* memmber_functions  */
  YYSYMBOL_object_decl = 72,               /* object_decl  */
  YYSYMBOL_object_usage = 73,              /* object_usage  */
  YYSYMBOL_obj_id = 74,                    /* obj_id  */
  YYSYMBOL_field_or_method_call = 75,      /* field_or_method_call  */
  YYSYMBOL_function_def = 76,              /* function_def  */
  YYSYMBOL_function_header = 77,           /* function_header  */
  YYSYMBOL_function_def_class = 78,        /* function_def_class  */
  YYSYMBOL_function_class_header = 79,     /* function_class_header  */
  YYSYMBOL_function_body = 80,             /* function_body  */
  YYSYMBOL_apel_functie = 81,              /* apel_functie  */
  YYSYMBOL_list_param = 82,                /* list_param  */
  YYSYMBOL_param = 83,                     /* param  */
  YYSYMBOL_lista_valori = 84,              /* lista_valori  */
  YYSYMBOL_valoare = 85,                   /* valoare  */
  YYSYMBOL_call_list = 86,                 /* call_list  */
  YYSYMBOL_list = 87,                      /* list  */
  YYSYMBOL_EXPRESII = 88,                  /* EXPRESII  */
  YYSYMBOL_EXPR = 89,                      /* EXPR  */
  YYSYMBOL_EXPR_BOOL = 90,                 /* EXPR_BOOL  */
  YYSYMBOL_EXPR_COMP = 91,                 /* EXPR_COMP  */
  YYSYMBOL_RIGHT_VALUE = 92,               /* RIGHT_VALUE  */
  YYSYMBOL_LEFT_VALUE = 93,                /* LEFT_VALUE  */
  YYSYMBOL_block = 94,                     /* block  */
  YYSYMBOL_statement = 95,                 /* statement  */
  YYSYMBOL_statement_conditions = 96,      /* statement_conditions  */
  YYSYMBOL_eval_statement = 97,            /* eval_statement  */
  YYSYMBOL_typeof_statement = 98           /* typeof_statement  */
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
#define YYFINAL  32
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   387

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  113
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  238

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


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
       2,     2,     2,     2,     2,     2,     2,    39,     2,     2,
      44,    45,    37,    35,    48,    36,    47,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    43,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   190,   190,   191,   192,   193,   194,   195,   196,   197,
     200,   201,   203,   204,   206,   207,   209,   212,   214,   216,
     217,   219,   220,   221,   222,   223,   225,   246,   267,   292,
     301,   311,   314,   338,   363,   391,   392,   393,   394,   395,
     401,   404,   418,   421,   422,   424,   425,   428,   435,   439,
     454,   463,   471,   474,   476,   494,   495,   521,   523,   586,
     587,   590,   591,   592,   593,   596,   597,   600,   605,   610,
     613,   615,   623,   637,   640,   659,   660,   661,   664,   665,
     666,   674,   684,   688,   691,   692,   693,   694,   695,   697,
     698,   699,   700,   701,   702,   704,   706,   716,   717,   721,
     722,   725,   734,   744,   745,   746,   747,   748,   751,   752,
     753,   754,   756,   758
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "WHILE",
  "FOR", "CLASS", "CONSTANT", "RETURN", "EVAL", "TYPEOF", "BEGIN_PROGR",
  "END_PROGR", "ASSIGN", "LOGIC_AND", "LOGIC_OR", "LESS", "LESS_EQ", "GRT",
  "GRT_EQ", "EQ", "NOT_EQ", "NOT", "INT", "FLOAT", "CHAR", "STRING",
  "BOOL", "ID", "CLASS_ID", "FUN_ID", "BOOLEAN", "NR_INT", "NR_FLOAT",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'{'", "'}'", "'['", "']'", "'('",
  "')'", "';'", "'.'", "','", "$accept", "progr",
  "declarations_glob_variable", "functions_glob_def", "class_list",
  "main_fun", "begin_progr", "end_progr", "decl", "variable", "array_decl",
  "array_init", "array_usage", "dimensiune", "variable_decl",
  "variable_def", "constant_def", "tip_variabila", "class_def",
  "class_header", "class_body", "data_members", "memmber_functions",
  "object_decl", "object_usage", "obj_id", "field_or_method_call",
  "function_def", "function_header", "function_def_class",
  "function_class_header", "function_body", "apel_functie", "list_param",
  "param", "lista_valori", "valoare", "call_list", "list", "EXPRESII",
  "EXPR", "EXPR_BOOL", "EXPR_COMP", "RIGHT_VALUE", "LEFT_VALUE", "block",
  "statement", "statement_conditions", "eval_statement",
  "typeof_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-97)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-104)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     178,     5,   329,   -97,   -97,   -97,   -97,   -97,   -97,   -10,
      29,   185,   104,   178,   -97,   275,     4,   -97,   -97,   -97,
     -97,   -97,   -97,   118,   -97,   299,   -97,    16,   275,     0,
      40,   -97,   -97,   104,   -97,    45,   -97,    64,    68,   185,
     104,   -97,   -97,    60,    66,    77,    89,    96,    76,   100,
     -97,   -97,   123,   133,   144,   -97,   168,   266,   150,   -97,
     -97,   -97,   -97,     2,   157,   161,   173,    81,   -97,   176,
     275,   -97,   212,   -97,   -97,   -97,   104,   -97,   -97,   300,
     300,   329,   145,   145,   199,   -97,    91,   192,   -97,   -97,
     -97,   145,   -97,   -97,   195,   -97,   145,    -6,   290,   -97,
     197,   329,   211,   208,   221,   275,   -97,   145,   -97,   192,
     -97,   -97,   300,   -97,   -97,   330,   323,    42,   -97,    56,
     222,   241,   145,   -97,   228,   237,   -97,   246,   -97,   -97,
       3,   -97,   -97,   -97,   -97,   270,   307,   -97,   -97,   255,
     -97,    37,   -97,   -97,   291,   -97,   282,   -97,   289,   -97,
     301,    58,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   300,   300,   294,   295,   300,   327,   301,
     -97,   -97,   303,   -97,    91,   321,   302,   322,   325,   290,
     324,   -97,   -97,   -97,   -97,   -97,   -97,   -97,   -97,   -97,
     -97,   209,   209,   -97,   -97,   -97,   -97,   328,   275,   275,
      10,   199,   -97,   333,   254,   334,   -97,   -97,   290,   131,
     140,   145,   326,   331,   -97,   -97,    22,   -97,    90,   366,
     -97,   273,   -97,   -97,   -97,   254,   332,   335,   336,   -97,
     -97,   275,   337,   225,   275,   -97,   234,   -97
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,    17,    35,    36,    37,    38,    39,     0,
       0,     0,     0,     0,     9,     0,     0,    19,    23,    24,
      22,    21,    25,     0,    14,     0,    20,     0,     0,     0,
       0,    47,     1,     0,     5,     0,     4,     0,     0,     0,
       0,     8,    15,     0,     0,     0,     0,     0,    96,     0,
     105,    98,     0,    97,     0,   102,     0,     0,     0,   104,
     106,   107,    10,    32,     0,     0,     0,     0,    12,     0,
      57,    41,     0,     3,    11,    13,     0,     6,     7,     0,
       0,     0,     0,     0,     0,    49,     0,    50,    52,    48,
      51,     0,    18,    16,     0,    99,     0,     0,     0,    43,
       0,     0,     0,    42,     0,     0,    53,     0,     2,    81,
      87,    80,     0,    83,    82,     0,    73,     0,    86,     0,
       0,     0,     0,    95,     0,     0,    31,     0,    71,    72,
       0,    69,   101,   100,    33,     0,     0,    63,    64,     0,
      62,     0,    59,    40,     0,    44,     0,    45,     0,    34,
      73,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     112,   113,    29,    58,     0,    26,     0,    61,     0,     0,
       0,    46,    55,    79,    88,    89,    90,    91,    92,    93,
      94,    74,    75,    76,    77,    78,    84,    85,     0,     0,
       0,     0,    70,     0,     0,     0,    54,    60,     0,     0,
       0,     0,     0,     0,    67,    68,     0,    65,     0,   108,
     110,     0,    30,    27,    28,     0,     0,     0,     0,    66,
      56,     0,     0,     0,     0,   109,     0,   111
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -97,   -97,   358,    -1,   -97,    87,   -97,   -97,    36,   -14,
     -96,   -97,   -15,   172,   -97,   297,   -95,    21,   363,   -97,
     -97,   -97,   -97,   -93,   -97,   -97,   -97,    12,   -97,   276,
     -97,   277,   -11,   175,   201,   -97,   159,   -97,   213,   -76,
     -94,   -71,   -97,   -61,   -97,    -7,   -56,   -97,   -97,   -97
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    10,    11,    12,    13,    14,    15,    93,    50,    17,
      18,    19,   113,   127,    20,    21,    22,    52,    24,    25,
      66,    67,   103,    26,    53,    54,    89,    27,    28,   104,
     105,    69,   114,   141,   142,   216,   217,   130,   131,   115,
     116,   117,   118,   124,    56,    70,    58,    59,    60,    61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,    94,   137,   138,    55,   140,   123,   123,    57,   119,
      33,    65,    40,    51,    94,   123,    96,    55,   150,    31,
     134,    23,   125,    30,    38,   163,   164,   135,   169,    32,
     132,   149,    23,    37,    23,    29,    16,   136,    76,    88,
      71,   151,    51,    90,    97,    38,    55,    35,   173,    16,
      62,   174,    38,   102,    37,    51,   211,   163,   164,    55,
      23,    37,    68,   224,   191,   192,   193,   194,   195,    72,
     225,   163,   164,   163,   164,    35,   185,   186,   187,   188,
     189,   190,   178,   137,   138,   179,   140,   165,    38,     2,
      51,    74,   196,   197,    55,    64,   200,    37,    34,    36,
      41,   166,   121,   184,    79,     4,     5,     6,     7,     8,
      80,   101,   137,   138,    75,   140,     3,   221,    84,   139,
      73,    81,   144,    85,   128,   129,    77,    78,     4,     5,
       6,     7,     8,    82,    43,   226,    44,    45,   179,     2,
      83,    46,    47,    43,    86,    44,    45,    63,     2,    64,
      46,    47,    63,    94,    94,     4,     5,     6,     7,     8,
      48,     9,    49,   108,     4,     5,     6,     7,     8,    48,
       9,    49,   219,    87,   109,    49,    49,    94,   111,  -103,
      94,   220,    91,    51,    51,     1,     2,    55,    55,   122,
       3,   209,   210,     2,    51,    51,    95,     3,    55,    55,
     139,    98,     4,     5,     6,     7,     8,    99,     9,     4,
       5,     6,     7,     8,   100,     9,    51,   106,    51,    51,
      55,    51,    55,    55,   233,    55,   107,   236,    43,   139,
      44,    45,   126,     2,    84,    46,    47,    43,   101,    44,
      45,   133,     2,   143,    46,    47,   160,   161,   162,     4,
       5,     6,     7,     8,    48,     9,    49,   145,     4,     5,
       6,     7,     8,    48,     9,    49,   235,   147,   167,    43,
     168,    44,    45,   170,     2,   237,    46,    47,    43,    92,
      44,    45,   171,     2,   177,    46,    47,   214,   215,   172,
       4,     5,     6,     7,     8,    48,     9,    49,     2,     4,
       5,     6,     7,     8,    48,     9,    49,     2,   158,   159,
     160,   161,   162,   175,     4,     5,     6,     7,     8,   228,
       9,   176,   180,     4,     5,     6,     7,     8,   181,   109,
     182,    49,   110,   111,   198,   199,   158,   159,   160,   161,
     162,    96,   204,   163,   112,   201,   183,   152,   153,   154,
     155,   156,   157,     4,     5,     6,     7,     8,   158,   159,
     160,   161,   162,   203,   205,   206,   213,   135,   208,   222,
     227,    39,   230,   212,   223,   231,    42,   234,   120,   146,
     207,   232,   148,   218,   229,     0,     0,   202
};

static const yytype_int16 yycheck[] =
{
      15,    57,    98,    98,    15,    98,    82,    83,    15,    80,
      11,    25,    13,    28,    70,    91,    14,    28,   112,    29,
      96,     0,    83,     2,    12,    15,    16,    33,   122,     0,
      91,   107,    11,    12,    13,    30,     0,    43,    39,    54,
      40,   112,    57,    54,    42,    33,    57,    11,    45,    13,
      46,    48,    40,    67,    33,    70,    46,    15,    16,    70,
      39,    40,    46,    41,   158,   159,   160,   161,   162,    29,
      48,    15,    16,    15,    16,    39,   152,   153,   154,   155,
     156,   157,    45,   179,   179,    48,   179,    45,    76,     8,
     105,    46,   163,   164,   105,    31,   167,    76,    11,    12,
      13,    45,    81,    45,    44,    24,    25,    26,    27,    28,
      44,    30,   208,   208,    46,   208,    12,   211,    42,    98,
      33,    44,   101,    47,    33,    34,    39,    40,    24,    25,
      26,    27,    28,    44,     3,    45,     5,     6,    48,     8,
      44,    10,    11,     3,    44,     5,     6,    29,     8,    31,
      10,    11,    29,   209,   210,    24,    25,    26,    27,    28,
      29,    30,    31,    76,    24,    25,    26,    27,    28,    29,
      30,    31,    41,    29,    29,    31,    31,   233,    33,    46,
     236,    41,    14,   198,   199,     7,     8,   198,   199,    44,
      12,   198,   199,     8,   209,   210,    46,    12,   209,   210,
     179,    44,    24,    25,    26,    27,    28,    46,    30,    24,
      25,    26,    27,    28,    41,    30,   231,    41,   233,   234,
     231,   236,   233,   234,   231,   236,    14,   234,     3,   208,
       5,     6,    33,     8,    42,    10,    11,     3,    30,     5,
       6,    46,     8,    46,    10,    11,    37,    38,    39,    24,
      25,    26,    27,    28,    29,    30,    31,    46,    24,    25,
      26,    27,    28,    29,    30,    31,    41,    46,    46,     3,
      29,     5,     6,    45,     8,    41,    10,    11,     3,    13,
       5,     6,    45,     8,    29,    10,    11,    33,    34,    43,
      24,    25,    26,    27,    28,    29,    30,    31,     8,    24,
      25,    26,    27,    28,    29,    30,    31,     8,    35,    36,
      37,    38,    39,    43,    24,    25,    26,    27,    28,    46,
      30,    14,    31,    24,    25,    26,    27,    28,    46,    29,
      41,    31,    32,    33,    40,    40,    35,    36,    37,    38,
      39,    14,    40,    15,    44,    42,    45,    17,    18,    19,
      20,    21,    22,    24,    25,    26,    27,    28,    35,    36,
      37,    38,    39,    42,    42,    40,    33,    33,    44,    43,
       4,    13,    40,   201,    43,    40,    13,    40,    81,   103,
     179,    45,   105,   208,   225,    -1,    -1,   174
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,    12,    24,    25,    26,    27,    28,    30,
      50,    51,    52,    53,    54,    55,    57,    58,    59,    60,
      63,    64,    65,    66,    67,    68,    72,    76,    77,    30,
      66,    29,     0,    52,    54,    57,    54,    66,    76,    51,
      52,    54,    67,     3,     5,     6,    10,    11,    29,    31,
      57,    61,    66,    73,    74,    81,    93,    94,    95,    96,
      97,    98,    46,    29,    31,    58,    69,    70,    46,    80,
      94,    40,    29,    54,    46,    46,    52,    54,    54,    44,
      44,    44,    44,    44,    42,    47,    44,    29,    61,    75,
      81,    14,    13,    56,    95,    46,    14,    42,    44,    46,
      41,    30,    58,    71,    78,    79,    41,    14,    54,    29,
      32,    33,    44,    61,    81,    88,    89,    90,    91,    90,
      64,    66,    44,    88,    92,    92,    33,    62,    33,    34,
      86,    87,    92,    46,    88,    33,    43,    59,    65,    66,
      72,    82,    83,    46,    66,    46,    78,    46,    80,    88,
      89,    90,    17,    18,    19,    20,    21,    22,    35,    36,
      37,    38,    39,    15,    16,    45,    45,    46,    29,    89,
      45,    45,    43,    45,    48,    43,    14,    29,    45,    48,
      31,    46,    41,    45,    45,    88,    88,    88,    88,    88,
      88,    89,    89,    89,    89,    89,    90,    90,    40,    40,
      90,    42,    87,    42,    40,    42,    40,    83,    44,    94,
      94,    46,    62,    33,    33,    34,    84,    85,    82,    41,
      41,    89,    43,    43,    41,    48,    45,     4,    46,    85,
      40,    40,    45,    94,    40,    41,    94,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    50,    50,    50,    50,    50,    50,    50,
      51,    51,    52,    52,    53,    53,    54,    55,    56,    57,
      57,    58,    58,    58,    58,    58,    59,    59,    60,    61,
      61,    62,    63,    64,    65,    66,    66,    66,    66,    66,
      67,    68,    69,    70,    70,    71,    71,    72,    73,    74,
      75,    75,    75,    76,    77,    78,    79,    80,    81,    82,
      82,    83,    83,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    87,    88,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    90,    90,    90,    90,    90,    91,
      91,    91,    91,    91,    91,    92,    93,    93,    93,    94,
      94,    95,    95,    95,    95,    95,    95,    95,    96,    96,
      96,    96,    97,    98
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     3,     2,     2,     3,     3,     2,     1,
       2,     3,     2,     3,     1,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     8,     8,     4,
       7,     1,     2,     4,     5,     1,     1,     1,     1,     1,
       4,     3,     2,     2,     3,     2,     3,     2,     2,     2,
       1,     1,     1,     3,     6,     3,     7,     1,     4,     1,
       3,     2,     1,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     3,     3,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     2,
       3,     3,     1,     1,     1,     1,     1,     1,     7,    11,
       7,    12,     4,     4
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
  case 2: /* progr: class_list declarations_glob_variable functions_glob_def main_fun  */
#line 190 "proiect.y"
                                                                         {printf("The programme is correct!\n");}
#line 1488 "parser.c"
    break;

  case 3: /* progr: declarations_glob_variable functions_glob_def main_fun  */
#line 191 "proiect.y"
                                                              {printf("The programme is correct!\n");}
#line 1494 "parser.c"
    break;

  case 4: /* progr: functions_glob_def main_fun  */
#line 192 "proiect.y"
                                   {printf("The programme is correct!\n");}
#line 1500 "parser.c"
    break;

  case 5: /* progr: declarations_glob_variable main_fun  */
#line 193 "proiect.y"
                                           {printf("The programme is correct!\n");}
#line 1506 "parser.c"
    break;

  case 6: /* progr: class_list declarations_glob_variable main_fun  */
#line 194 "proiect.y"
                                                      {printf("The programme is correct!\n");}
#line 1512 "parser.c"
    break;

  case 7: /* progr: class_list functions_glob_def main_fun  */
#line 195 "proiect.y"
                                              {printf("The programme is correct!\n");}
#line 1518 "parser.c"
    break;

  case 8: /* progr: class_list main_fun  */
#line 196 "proiect.y"
                           {printf("The programme is correct!\n");}
#line 1524 "parser.c"
    break;

  case 9: /* progr: main_fun  */
#line 197 "proiect.y"
                {printf("The programme is correct!\n");}
#line 1530 "parser.c"
    break;

  case 16: /* main_fun: begin_progr block end_progr  */
#line 209 "proiect.y"
                                       { }
#line 1536 "parser.c"
    break;

  case 17: /* begin_progr: BEGIN_PROGR  */
#line 212 "proiect.y"
                            {scopeStack.push("main");}
#line 1542 "parser.c"
    break;

  case 18: /* end_progr: END_PROGR  */
#line 214 "proiect.y"
                    {{if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} }}
#line 1548 "parser.c"
    break;

  case 26: /* array_decl: tip_variabila ID '[' NR_INT ']'  */
#line 225 "proiect.y"
                                             {
                        
                         const char* scope ="";
                         if(!scopeStack.empty()){ //ma aflu in scope ul global
                          
                           scope=scopeStack.top(); //clasa/tipul func

                                if(!listSymbols.existsVar((yyvsp[-3].String),scope)){
                              listSymbols.addArray((yyvsp[-4].tip_data),(yyvsp[-3].String),(yyvsp[-1].Int),scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                              if(!listSymbols.existsVar((yyvsp[-3].String),scope)){
                              listSymbols.addArray((yyvsp[-4].tip_data),(yyvsp[-3].String),(yyvsp[-1].Int),scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                    
                     }
#line 1574 "parser.c"
    break;

  case 27: /* array_decl: tip_variabila ID '[' NR_INT ']' '[' NR_INT ']'  */
#line 246 "proiect.y"
                                                            {
                   const char* scope ="";
                         if(!scopeStack.empty()){ //ma aflu in scope ul clasa
                          
                             scope=scopeStack.top(); //clasa

                                if(!listSymbols.existsVar((yyvsp[-6].String),scope)){
                              listSymbols.addArray((yyvsp[-7].tip_data),(yyvsp[-6].String),(yyvsp[-4].Int),(yyvsp[-1].Int),scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                              if(!listSymbols.existsVar((yyvsp[-6].String),scope)){
                              listSymbols.addArray((yyvsp[-7].tip_data),(yyvsp[-6].String),(yyvsp[-4].Int),(yyvsp[-1].Int),scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                     }
#line 1598 "parser.c"
    break;

  case 28: /* array_init: tip_variabila ID '[' ']' ASSIGN '{' lista_valori '}'  */
#line 267 "proiect.y"
                                                                  { 
          /* Logică inițializare */
              const char* scope ="";

                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                           scope=scopeStack.top(); //clasa
                         
                                if(!listSymbols.existsVar((yyvsp[-6].String),scope)){
                              listSymbols.initArray(listavalori,(yyvsp[-7].tip_data),(yyvsp[-6].String),listavalori.size(),scope);
               
                                }
                              else{
                                   printf("Error at decl array 1\n"); }
                         }else {
                              if(!listSymbols.existsVar((yyvsp[-6].String),scope)){
                               listSymbols.initArray(listavalori,(yyvsp[-7].tip_data),(yyvsp[-6].String),listavalori.size(),scope);
                                }
                              else{
                                   printf("Error at decl array 2\n"); }
                         }
               listavalori.clear();   // Elimină toate elementele din vector
               listavalori.shrink_to_fit();  // Reduc capacitatea vectorului
          }
#line 1627 "parser.c"
    break;

  case 32: /* variable_decl: tip_variabila ID  */
#line 314 "proiect.y"
                                {
                   
                          const char* scope ="";
                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                           scope=scopeStack.top(); //clasa/functia/main
                              
                                if(!listSymbols.existsVar((yyvsp[0].String),scope)){
                              listSymbols.addVar((yyvsp[-1].tip_data),(yyvsp[0].String),scope);
                                }
                              else{
                                   printf("Error at decl var\n%s %s",(yyvsp[-1].tip_data),(yyvsp[0].String)); }
                         }else {
                              if(!listSymbols.existsVar((yyvsp[0].String),scope)){
                              listSymbols.addVar((yyvsp[-1].tip_data),(yyvsp[0].String),scope);
                                }
                              else{
                                   printf("Error at decl var\n%s %s",(yyvsp[-1].tip_data),(yyvsp[0].String)); }
                         }

                         //verific daca nu cumva este data membru;
                       //free($2);
                    }
#line 1655 "parser.c"
    break;

  case 33: /* variable_def: tip_variabila ID ASSIGN EXPRESII  */
#line 338 "proiect.y"
                                                {      
                        const char* scope ="";
                         //const char* myCStr="" ;
                          //string exprVal;

                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                           scope=scopeStack.top(); //clasa
               
                                if(!listSymbols.existsVar((yyvsp[-2].String),scope)){
                              listSymbols.addVar((yyvsp[-3].tip_data),(yyvsp[-2].String),(yyvsp[0].String),scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                              if(!listSymbols.existsVar((yyvsp[-2].String),scope)){
                              listSymbols.addVar((yyvsp[-3].tip_data),(yyvsp[-2].String),(yyvsp[0].String),scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                        printf("Definitia variabilei: %s de tipul %s cu valoarea initiala\n", (yyvsp[-2].String), (yyvsp[-3].tip_data));
                        // Aici, expr ar trebui să fie evaluată și valoarea să fie stocată/atribuită variabilei
                    }
#line 1684 "parser.c"
    break;

  case 34: /* constant_def: CONSTANT tip_variabila ID ASSIGN EXPRESII  */
#line 363 "proiect.y"
                                                         {
                    const char* scope ="";
                   //  const char* myCStr ="";
                    // string exprVal="";
         

                                                // Presupunem că $5 este un Expr*
                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                           scope=scopeStack.top(); //clasa

                                if(!listSymbols.existsVar((yyvsp[-3].tip_data),scope)){
                              listSymbols.addVar(true,(yyvsp[-3].tip_data),(yyvsp[-2].String),(yyvsp[0].String),scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                              if(!listSymbols.existsVar((yyvsp[-3].tip_data),scope)){
                              listSymbols.addVar(true,(yyvsp[-3].tip_data),(yyvsp[-2].String),(yyvsp[0].String),scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                    
                    //trebuie adaugat ca si o constanta,direct cu valoarea ei ,nr
               }
#line 1715 "parser.c"
    break;

  case 35: /* tip_variabila: INT  */
#line 391 "proiect.y"
                      {(yyval.tip_data)=(yyvsp[0].tip_data);}
#line 1721 "parser.c"
    break;

  case 36: /* tip_variabila: FLOAT  */
#line 392 "proiect.y"
                      {(yyval.tip_data)=(yyvsp[0].tip_data);}
#line 1727 "parser.c"
    break;

  case 37: /* tip_variabila: CHAR  */
#line 393 "proiect.y"
                      {(yyval.tip_data)=(yyvsp[0].tip_data);}
#line 1733 "parser.c"
    break;

  case 38: /* tip_variabila: STRING  */
#line 394 "proiect.y"
                       {(yyval.tip_data)=(yyvsp[0].tip_data);}
#line 1739 "parser.c"
    break;

  case 39: /* tip_variabila: BOOL  */
#line 395 "proiect.y"
                      {(yyval.tip_data)=(yyvsp[0].tip_data);}
#line 1745 "parser.c"
    break;

  case 40: /* class_def: class_header class_body '}' ';'  */
#line 401 "proiect.y"
                                            { if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} cout<<"de 1"<<endl;}
#line 1751 "parser.c"
    break;

  case 41: /* class_header: CLASS CLASS_ID '{'  */
#line 404 "proiect.y"
                                   { 
             
               scopeStack.push((yyvsp[-1].String));

             if(!listSymbols.existsClass((yyvsp[-1].String))){
                  listSymbols.addClass((yyvsp[-1].String));
             }else{
               printf("Eror,already class exists\n");
             }

             }
#line 1767 "parser.c"
    break;

  case 47: /* object_decl: CLASS_ID ID  */
#line 428 "proiect.y"
                          {/*cod pentru declararea unui obiect al clasei*/
                     if(listSymbols.addObjInClass((yyvsp[-1].String),(yyvsp[0].String))){
                       
                    }else { cout<<"Eror decl obj"<<(yyvsp[0].String)<<endl;}
               
               }
#line 1778 "parser.c"
    break;

  case 48: /* object_usage: obj_id field_or_method_call  */
#line 435 "proiect.y"
                                            {
               currentClass = nullptr; // Setează pointerul la nullptr după eliberarea memoriei
                  /*// Cod pentru utilizarea unui câmp sau apelarea unei metode a obiectului*/}
#line 1786 "parser.c"
    break;

  case 49: /* obj_id: ID '.'  */
#line 439 "proiect.y"
              {
               //const char* className=scopeStack.top();          
               //daca apelz obiectul in main,clasa curenta va fi deja scoasa din scope
                 currentClass =listSymbols.gettypeObj((yyvsp[-1].String)).c_str();
               
                if(strcmp(currentClass,"")!=0){
                    //exist obiectul
                         (yyval.NameClas) = currentClass;
                         cout<<(yyval.NameClas)<<endl; // Alocăm și setăm numele clasei
                    }else{
                         cout<<"Eror class is not decl"; (yyval.NameClas) = nullptr;}

                }
#line 1804 "parser.c"
    break;

  case 50: /* field_or_method_call: ID  */
#line 454 "proiect.y"
                          { /* Accesare câmp */
                     //const char* className = $<NameClas>-1;// Obțineți numele clasei transmis
                     const char* fieldName = (yyvsp[0].String);  
                     cout<<currentClass<<" tipul obj: "<<(yyvsp[0].String)<<endl;
                    if(listSymbols.existsVar((yyvsp[0].String),currentClass)){
                              //l am accesat
                    }else { cout<<"Nu exista acest camp in clasa "<<currentClass<<endl;}
                         }
#line 1817 "parser.c"
    break;

  case 51: /* field_or_method_call: apel_functie  */
#line 463 "proiect.y"
                                   {for(Expr* expr : globalParamList){
                          delete expr; 
                          expr=nullptr;
                          
                        }
                        cout<<"S-a dealocat globalParamList"<<endl;}
#line 1828 "parser.c"
    break;

  case 52: /* field_or_method_call: array_usage  */
#line 471 "proiect.y"
                                   {}
#line 1834 "parser.c"
    break;

  case 53: /* function_def: function_header function_body '}'  */
#line 474 "proiect.y"
                                                 { if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} }
#line 1840 "parser.c"
    break;

  case 54: /* function_header: tip_variabila FUN_ID '(' list_param ')' '{'  */
#line 476 "proiect.y"
                                                              {
                    scopeStack.push((yyvsp[-4].String));
                    //const char* scopeFun=scopeStack.top();
                    const char* scope="";
                  vector<const char *> paramTypes;
                  // Presupunând că $4 este lista de parametri obținută din list_param                     
                    while(!listTypeParamQueue.empty())
                   {
                   const char*  param=listTypeParamQueue.front();
                   listTypeParamQueue.pop();
                   paramTypes.push_back(param);
                   }
                  
                   if(!listSymbols.existsFunc((yyvsp[-5].tip_data),(yyvsp[-4].String),paramTypes,scope)){
                    listSymbols.addFunc((yyvsp[-5].tip_data),(yyvsp[-4].String),paramTypes,scope);
                   }else { cout<<"Eror at func decl: "<<(yyvsp[-5].tip_data)<<" "<<(yyvsp[-4].String)<<endl ;}
               }
#line 1862 "parser.c"
    break;

  case 55: /* function_def_class: function_class_header function_body '}'  */
#line 494 "proiect.y"
                                                             {}
#line 1868 "parser.c"
    break;

  case 56: /* function_class_header: CLASS_ID tip_variabila FUN_ID '(' list_param ')' '{'  */
#line 495 "proiect.y"
                                                                            {
                    
                    
                    //partea de lista a parametrilor
                    vector<const char*> paramTypes;  
                    while(!listTypeParamQueue.empty())
                    {
                    const char* param=listTypeParamQueue.front();
                    listTypeParamQueue.pop();
                    paramTypes.push_back(param);
                    }
                    const char* classId ="";

                     if(!scopeStack.empty()) //am clase in stiva
                    {
                      classId=scopeStack.top();
                      cout<<classId<<" "<<endl;
                      if(!listSymbols.existsFunc((yyvsp[-5].tip_data),(yyvsp[-4].String),paramTypes,classId)){
                        listSymbols.addFunc((yyvsp[-5].tip_data),(yyvsp[-4].String),paramTypes,classId);
                      }
                      else{
                         cout<<"Eror at func decl: "<<(yyvsp[-6].String)<<" "<<(yyvsp[-5].tip_data)<<" "<<(yyvsp[-4].String)<<endl ;
                      }
                    }else {cout<<"error la stiva";}       
               }
#line 1898 "parser.c"
    break;

  case 57: /* function_body: block  */
#line 521 "proiect.y"
                      {}
#line 1904 "parser.c"
    break;

  case 58: /* apel_functie: FUN_ID '(' call_list ')'  */
#line 523 "proiect.y"
                                        { 

                    vector<const char*> paramTypes;
                    cout<<"GLobal param types  "<<endl;
                    
                    for(Expr* expr : globalParamList){
                         cout<<expr->type<<" "<<expr->intvalue<<" "<<expr->floatvalue<<"|";
                         paramTypes.push_back(expr->type);
                         // delete expr; 
                         //expr = nullptr;
                         // Dacă este necesar, aici puteți și elibera memoria alocată pentru expr
                    }
                    if(currentClass==nullptr || *currentClass == '\0')
                    {
                          cout<<"HELLO"<<endl;
                    const char * scope="";
                    
                    string typeFunc = listSymbols.getTypeFunc(scope,(yyvsp[-3].String),paramTypes,scope);  /*scope="" inseamna ca e global*/
                        cout<<typeFunc<<endl;
                        if(typeFunc == ""){
                              cout<<"Eror cant call inexistent fun"<<endl;
                              (yyval.String)=nullptr;
                        }else{
                         cout<<"Can call fun "<<(yyvsp[-3].String)<<endl;
                         const char* returnType = typeFunc.c_str();
                         (yyval.String)=(char*)returnType;
                        }
                    //$$ trebuie sa prineasca return type ul,pt a puea asigna functia;
                    }else { //apel de metoda
                     cout<<"HELLO1"<<endl;
                         const char * scope="";
                           string typeFunc = listSymbols.getTypeFunc(scope,(yyvsp[-3].String),paramTypes,currentClass);  /*scope="" inseamna ca e global*/
                        if(typeFunc == ""){
                              cout<<"Eror cant call inexistent fun"<<endl;
                              (yyval.String)=nullptr;
                        }else{
                         cout<<"Can call fun "<<(yyvsp[-3].String)<<" tipul metodei: "<<currentClass<<endl;
                         const char* returnType = typeFunc.c_str();
                         (yyval.String)=(char*)returnType;
                        }

                    }
                      //if(globalParamList.size()>0)

                     globalParamList.clear(); // Cuat
               }
#line 1955 "parser.c"
    break;

  case 59: /* list_param: param  */
#line 586 "proiect.y"
                   { listTypeParamQueue.push((yyvsp[0].String)); printf("|%s|\n",(yyvsp[0].String));}
#line 1961 "parser.c"
    break;

  case 60: /* list_param: list_param ',' param  */
#line 587 "proiect.y"
                                   {listTypeParamQueue.push((yyvsp[0].String)); printf("|%s|\n",(yyvsp[0].String));}
#line 1967 "parser.c"
    break;

  case 61: /* param: tip_variabila ID  */
#line 590 "proiect.y"
                         {(yyval.String) = (yyvsp[-1].tip_data); }
#line 1973 "parser.c"
    break;

  case 65: /* lista_valori: valoare  */
#line 596 "proiect.y"
                       {}
#line 1979 "parser.c"
    break;

  case 66: /* lista_valori: lista_valori ',' valoare  */
#line 597 "proiect.y"
                                 {}
#line 1985 "parser.c"
    break;

  case 67: /* valoare: NR_INT  */
#line 600 "proiect.y"
                 {/*std::string expresie = std::to_string($1); // 
                    const char* plvar_stringm = expresie.c_str();
                    $$=(char*)var_string;*/
                    listavalori.push_back((yyvsp[0].Int));
                    }
#line 1995 "parser.c"
    break;

  case 68: /* valoare: NR_FLOAT  */
#line 605 "proiect.y"
                    {/* std::string expresie = std::to_string($1); // 
                    const char* var_string = expresie.c_str();
                    $$=(char*)var_string;*/}
#line 2003 "parser.c"
    break;

  case 69: /* call_list: list  */
#line 610 "proiect.y"
                 { globalParamList.push_back((yyvsp[0].expr));
                   cout<<"LIST: "<<(yyvsp[0].expr)->type<<" "<<(yyvsp[0].expr)->floatvalue<<endl;;
                    }
#line 2011 "parser.c"
    break;

  case 70: /* call_list: call_list ',' list  */
#line 613 "proiect.y"
                               {globalParamList.push_back((yyvsp[0].expr)); cout<<"LIST: "<<(yyvsp[0].expr)->type<<" "<<(yyvsp[0].expr)->floatvalue<<endl;}
#line 2017 "parser.c"
    break;

  case 71: /* list: NR_INT  */
#line 615 "proiect.y"
                  {
                Expr* newExpr = new Expr();
                newExpr->type = "int";
                newExpr->intvalue = (yyvsp[0].Int);
                (yyval.expr) = newExpr;
               
              
          }
#line 2030 "parser.c"
    break;

  case 72: /* list: NR_FLOAT  */
#line 623 "proiect.y"
                    {Expr* newExpr = new Expr();
                newExpr->type = "float";
                newExpr->floatvalue = (yyvsp[0].Float);
                (yyval.expr) = newExpr;
               
          }
#line 2041 "parser.c"
    break;

  case 73: /* EXPRESII: EXPR  */
#line 637 "proiect.y"
                {  (yyval.String)=(yyvsp[0].String);}
#line 2047 "parser.c"
    break;

  case 74: /* EXPR: EXPR '+' EXPR  */
#line 640 "proiect.y"
                           {
        /*  Expr* expr1= new Expr(); 
          expr1->type= $1->type;
          Expr* expr2= new Expr(); 
          expr2->type = $3->type;
          /*
          Expr* expr1 = $1;
          Expr* expr2 = $3;

          if(strcmp(expr1->type,expr2->type)!=0){
              cout<<"Eror type do not match"; // yyerror("Operand types do not match.");
               $$=nullptr;
          }
          else{
               $$->type=expr1->type;*/
                   // Implementați logica pentru o expresie validă}
        // Setarea $$ la o nouă instanță Expr cu tipul corespunzător
          
          }
#line 2071 "parser.c"
    break;

  case 75: /* EXPR: EXPR '-' EXPR  */
#line 659 "proiect.y"
                          {}
#line 2077 "parser.c"
    break;

  case 77: /* EXPR: EXPR '/' EXPR  */
#line 661 "proiect.y"
                          { 
                //eroare de impartire la 0 printf("Error,devide by 0\n");
          }
#line 2085 "parser.c"
    break;

  case 78: /* EXPR: EXPR '%' EXPR  */
#line 664 "proiect.y"
                          {}
#line 2091 "parser.c"
    break;

  case 79: /* EXPR: '(' EXPR ')'  */
#line 665 "proiect.y"
                         {(yyval.String) = (yyvsp[-1].String);}
#line 2097 "parser.c"
    break;

  case 80: /* EXPR: NR_INT  */
#line 666 "proiect.y"
                   { std::string expresie = std::to_string((yyvsp[0].Int)); // Convertiți numărul în șir de caractere
                    const char* nr_in_string = expresie.c_str();
                   (yyval.String)=(char*)nr_in_string;
                   /* $$->type="int";
                    $$->intvalue=$1;
                    cout<<" aaaaaaaa "<<$1;*/
                    }
#line 2109 "parser.c"
    break;

  case 81: /* EXPR: ID  */
#line 674 "proiect.y"
               {
              /* const char* varType = listSymbols.getTypeOfVariable($1);
               if(varType!=nullptr){
                    //var a fost gasita
                    cout<<"Type var : "<<varType<<endl;
                    $$->type=varType;
               }else{
                    cout<<"Eror var dosent def";
               }*/(yyval.String)=(yyvsp[0].String);
           }
#line 2124 "parser.c"
    break;

  case 82: /* EXPR: apel_functie  */
#line 684 "proiect.y"
                         {for(Expr* expr : globalParamList){
                          delete expr; 
                          expr=nullptr; }
                        cout<<"S-a dealoc GPL"<<endl;}
#line 2133 "parser.c"
    break;

  case 88: /* EXPR_BOOL: '(' EXPR_BOOL ')'  */
#line 695 "proiect.y"
                               {(yyval.String) = (yyvsp[-1].String);}
#line 2139 "parser.c"
    break;

  case 99: /* block: statement ';'  */
#line 721 "proiect.y"
                     {printf("statement\n");}
#line 2145 "parser.c"
    break;

  case 101: /* statement: LEFT_VALUE ASSIGN RIGHT_VALUE  */
#line 725 "proiect.y"
                                        {
             /*     Expr* leftExpr = $1;
               Expr* rightExpr = $3;
               if (strcmp(leftExpr->type, rightExpr->type) != 0) {
                   yyerror("Type mismatch in assignment.");
               } else {
                   // Continuați procesarea instrucțiunii de atribuire
               }*/
          }
#line 2159 "parser.c"
    break;

  case 102: /* statement: apel_functie  */
#line 734 "proiect.y"
                        { 
          if ((yyvsp[0].String) == nullptr){cout<<"Eror"<<endl;}
          for(Expr* expr : globalParamList){
                          delete expr; 
                          expr=nullptr;
                          
                        }
                        cout<<"S-a deal GPL STMT"<<endl;
          }
#line 2173 "parser.c"
    break;

  case 108: /* statement_conditions: IF '(' EXPR_BOOL ')' '{' block '}'  */
#line 751 "proiect.y"
                                                         {}
#line 2179 "parser.c"
    break;

  case 110: /* statement_conditions: WHILE '(' EXPR_BOOL ')' '{' block '}'  */
#line 753 "proiect.y"
                                                      { }
#line 2185 "parser.c"
    break;

  case 111: /* statement_conditions: FOR '(' variable_def ';' EXPR_BOOL ';' EXPR ';' ')' '{' block '}'  */
#line 754 "proiect.y"
                                                                                  { }
#line 2191 "parser.c"
    break;


#line 2195 "parser.c"

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

#line 760 "proiect.y"


void yyerror(const char * s){
printf("error: %s at line:%d\n",s,yylineno);
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse();
     
     listSymbols.printSymbolTable("out.txt");
    
}
