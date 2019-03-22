/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

	#include <iostream>
	#include <string>
	using namespace std;

	extern int yylineno;

	extern "C" void yyerror(string msg);
	extern int yylex(void);

	Symbol_Table* local_symbol_table;
	Table_Scope current_scope = global;
	bool ast_error = false;

#line 81 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    NAME = 259,
    ASSIGN = 260,
    FLOAT = 261,
    INTEGER_NUMBER = 262,
    DOUBLE_NUMBER = 263,
    VOID = 264,
    LESS_THAN = 265,
    GREATER_THAN = 266,
    LESS_THAN_EQUAL = 267,
    GREATER_THAN_EQUAL = 268,
    EQUAL = 269,
    NOT_EQUAL = 270,
    AND = 271,
    OR = 272,
    NOT = 273,
    WHILE = 274,
    IF = 275,
    ELSE = 276,
    DO = 277,
    UMINUS = 279
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "parser.y" /* yacc.c:355  */

	int 	integer_value;
	double  double_value;
	string  *string_value;

	list<Ast *> * ast_list;
	Ast * ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	Basic_Block * basic_block;
	Procedure * procedure;

#line 158 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 175 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   157

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  110

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      31,    32,    28,    26,    36,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    25,    35,
       2,     2,     2,    24,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    34,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    75,    75,    75,    87,    87,   102,   106,   112,   113,
     120,   124,   125,   129,   137,   150,   158,   174,   175,   179,
     182,   183,   184,   185,   186,   190,   194,   201,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   233,   248,   251,
     257,   263,   270,   276,   282,   287
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "NAME", "ASSIGN", "FLOAT",
  "INTEGER_NUMBER", "DOUBLE_NUMBER", "VOID", "LESS_THAN", "GREATER_THAN",
  "LESS_THAN_EQUAL", "GREATER_THAN_EQUAL", "EQUAL", "NOT_EQUAL", "AND",
  "OR", "NOT", "WHILE", "IF", "ELSE", "DO", "\"then\"", "'?'", "':'",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "'('", "')'", "'{'", "'}'", "';'",
  "','", "$accept", "program", "$@1", "procedure", "$@2",
  "optional_variable_declaration_list", "variable_declaration_list",
  "variable_declaration", "declaration", "integer_variable_list",
  "float_variable_list", "optional_statement_list", "statement_list_basic",
  "statement_list_basic1", "statement_list", "assignment_statement",
  "conditional_statement", "expression", "variable", "constant",
  "if_statement", "if_else_statement", "while_statement",
  "do_while_statement", "sequence", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,    63,    58,    43,    45,    42,    47,
     279,    40,    41,   123,   125,    59,    44
};
# endif

#define YYPACT_NINF -48

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-48)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      11,    -2,     2,    10,   -48,    11,   -48,   -17,   -48,     0,
     -48,     3,   -48,    37,   -48,   -48,    15,    44,    45,   -48,
     -48,   -48,    27,    39,    36,    11,   -48,    40,   -48,    41,
      52,    40,    40,    51,   -48,   -48,    40,   -48,    81,   -48,
     -48,   -48,   -48,   -48,    43,    43,    68,    21,   -48,   -48,
      43,   -48,   -48,    43,    43,    43,   108,   107,   -48,   -48,
     113,    64,   -48,    60,    53,   -48,   -13,   122,    79,    43,
      43,    43,    40,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    40,    43,   -48,   -48,   -48,   -48,    80,
      87,   -48,   107,   107,   107,   107,   107,   107,   -13,   -13,
     -48,   -48,    82,   125,    43,    40,    69,   107,   -48,   -48
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     0,     0,     2,     7,     8,     0,    13,    11,
      15,    12,     1,     0,     9,    10,     0,     0,     0,     3,
      14,    16,     0,     0,     0,     6,     4,    17,    47,     0,
       0,     0,     0,     0,    25,    54,    18,    20,     0,    23,
      24,    21,    22,    19,     0,     0,     0,     0,     5,    26,
       0,    48,    49,     0,     0,     0,     0,     0,    38,    39,
       0,     0,    55,     0,     0,    37,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    27,    34,    40,    35,    36,
       0,    52,    28,    32,    29,    30,    31,    33,    42,    43,
      44,    45,    50,     0,     0,     0,     0,    46,    51,    53
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -48,   -48,   -48,   -48,   -48,    84,   -48,   105,   -48,   -48,
     -48,   -48,   -25,   -48,    91,   -48,   -32,   -47,   -27,   -48,
     -48,   -48,   -48,   -48,   -30
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,    13,    19,    27,     4,     5,     6,     7,     9,
      11,    33,    34,    35,    36,    37,    63,    57,    58,    59,
      39,    40,    41,    42,    43
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      38,    46,     8,    64,    38,    38,    10,    66,    68,    38,
      12,    49,    56,    60,     1,    81,    82,     2,    15,    20,
      38,    65,    49,    67,    90,    28,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,    16,    88,    89,    17,
      29,    30,    91,    31,    28,    38,    18,    28,    21,    22,
      51,    52,   103,   102,    32,    62,    38,   107,    23,    29,
      30,    53,    31,    73,    74,    75,    76,    77,    78,    25,
      54,    24,    44,    32,    55,   108,    69,    70,    38,    79,
      80,    81,    82,    45,    71,    48,    50,    61,    85,    73,
      74,    75,    76,    77,    78,    84,    69,    73,    74,    75,
      76,    77,    78,   105,   109,    79,    80,    81,    82,    26,
      14,    87,   104,    79,    80,    81,    82,    73,    74,    75,
      76,    77,    78,    47,    69,    70,     0,     0,     0,    69,
      70,     0,    71,    79,    80,    81,    82,    71,    69,    70,
      72,    69,    70,     0,     0,    83,    71,     0,     0,    71,
       0,     0,     0,     0,    86,     0,     0,   106
};

static const yytype_int8 yycheck[] =
{
      27,    31,     4,    50,    31,    32,     4,    54,    55,    36,
       0,    36,    44,    45,     3,    28,    29,     6,    35,     4,
      47,    53,    47,    55,    71,     4,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    36,    69,    70,    36,
      19,    20,    72,    22,     4,    72,     9,     4,     4,     4,
       7,     8,    84,    83,    33,    34,    83,   104,    31,    19,
      20,    18,    22,    10,    11,    12,    13,    14,    15,    33,
      27,    32,    31,    33,    31,   105,    16,    17,   105,    26,
      27,    28,    29,    31,    24,    34,     5,    19,    35,    10,
      11,    12,    13,    14,    15,    31,    16,    10,    11,    12,
      13,    14,    15,    21,    35,    26,    27,    28,    29,    25,
       5,    32,    25,    26,    27,    28,    29,    10,    11,    12,
      13,    14,    15,    32,    16,    17,    -1,    -1,    -1,    16,
      17,    -1,    24,    26,    27,    28,    29,    24,    16,    17,
      32,    16,    17,    -1,    -1,    32,    24,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    32
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,    38,    42,    43,    44,    45,     4,    46,
       4,    47,     0,    39,    44,    35,    36,    36,     9,    40,
       4,     4,     4,    31,    32,    33,    42,    41,     4,    19,
      20,    22,    33,    48,    49,    50,    51,    52,    55,    57,
      58,    59,    60,    61,    31,    31,    61,    51,    34,    49,
       5,     7,     8,    18,    27,    31,    53,    54,    55,    56,
      53,    19,    34,    53,    54,    53,    54,    53,    54,    16,
      17,    24,    32,    10,    11,    12,    13,    14,    15,    26,
      27,    28,    29,    32,    31,    35,    32,    32,    53,    53,
      54,    61,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    61,    53,    25,    21,    32,    54,    61,    35
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    39,    38,    41,    40,    42,    42,    43,    43,
      44,    45,    45,    46,    46,    47,    47,    48,    48,    49,
      50,    50,    50,    50,    50,    51,    51,    52,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    55,    56,    56,
      57,    58,    59,    60,    61,    61
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     0,     9,     0,     1,     1,     2,
       2,     2,     2,     1,     3,     1,     3,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     1,     1,
       3,     2,     3,     3,     3,     3,     5,     1,     1,     1,
       5,     7,     5,     7,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 75 "parser.y" /* yacc.c:1646  */
    {
		program_object.set_global_table( *(yyvsp[0].symbol_table));
		current_scope = local;
	}
#line 1338 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 79 "parser.y" /* yacc.c:1646  */
    {
		program_object.set_procedure((yyvsp[0].procedure), yylineno);
		current_scope = global;
	}
#line 1347 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 87 "parser.y" /* yacc.c:1646  */
    {
		local_symbol_table = (yyvsp[0].symbol_table);
	}
#line 1355 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 90 "parser.y" /* yacc.c:1646  */
    {
		if (ast_error) exit(1);
		(yyval.procedure) = new Procedure(void_data_type, *(yyvsp[-7].string_value), yylineno);
		(yyval.procedure)->set_local_list( *(yyvsp[-3].symbol_table));
		(yyval.procedure)->set_ast_list( *(yyvsp[-1].ast_list));
	}
#line 1366 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 102 "parser.y" /* yacc.c:1646  */
    {
		(yyval.symbol_table) = new Symbol_Table();
		(yyval.symbol_table)->set_table_scope(current_scope);
	}
#line 1375 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 106 "parser.y" /* yacc.c:1646  */
    {
		(yyval.symbol_table) = (yyvsp[0].symbol_table);
	}
#line 1383 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 112 "parser.y" /* yacc.c:1646  */
    { (yyval.symbol_table) = (yyvsp[0].symbol_table); }
#line 1389 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 113 "parser.y" /* yacc.c:1646  */
    {
		(yyval.symbol_table) = (yyvsp[-1].symbol_table);
		(yyval.symbol_table)->append_list( *(yyvsp[0].symbol_table), yylineno);
	}
#line 1398 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 120 "parser.y" /* yacc.c:1646  */
    { (yyval.symbol_table) = (yyvsp[-1].symbol_table); }
#line 1404 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 124 "parser.y" /* yacc.c:1646  */
    { (yyval.symbol_table) = (yyvsp[0].symbol_table); }
#line 1410 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 125 "parser.y" /* yacc.c:1646  */
    { (yyval.symbol_table) = (yyvsp[0].symbol_table); }
#line 1416 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 129 "parser.y" /* yacc.c:1646  */
    {
		Symbol_Table_Entry* variable = new Symbol_Table_Entry( *(yyvsp[0].string_value), int_data_type, yylineno);
		variable->set_symbol_scope(current_scope);
		
		(yyval.symbol_table) = new Symbol_Table();
		(yyval.symbol_table)->set_table_scope(current_scope);
		(yyval.symbol_table)->push_symbol(variable);
	}
#line 1429 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 137 "parser.y" /* yacc.c:1646  */
    {
		Symbol_Table_Entry* variable = new Symbol_Table_Entry( *(yyvsp[0].string_value), int_data_type, yylineno);
		variable->set_symbol_scope(current_scope);

		(yyval.symbol_table) = (yyvsp[-2].symbol_table);
		Symbol_Table* temp_table = new Symbol_Table();
		temp_table->set_table_scope(current_scope);
		temp_table->push_symbol(variable);
		(yyval.symbol_table)->append_list( *temp_table, yylineno);
	}
#line 1444 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 150 "parser.y" /* yacc.c:1646  */
    {
		Symbol_Table_Entry* variable = new Symbol_Table_Entry( *(yyvsp[0].string_value), double_data_type, yylineno);
		variable->set_symbol_scope(current_scope);
		
		(yyval.symbol_table) = new Symbol_Table();
		(yyval.symbol_table)->set_table_scope(current_scope);
		(yyval.symbol_table)->push_symbol(variable);
	}
#line 1457 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 158 "parser.y" /* yacc.c:1646  */
    {
		Symbol_Table_Entry* variable = new Symbol_Table_Entry( *(yyvsp[0].string_value), double_data_type, yylineno);
		variable->set_symbol_scope(current_scope);

		(yyval.symbol_table) = (yyvsp[-2].symbol_table);
		Symbol_Table* temp_table = new Symbol_Table();
		temp_table->set_table_scope(current_scope);
		temp_table->push_symbol(variable);
		(yyval.symbol_table)->append_list( *temp_table, yylineno);
	}
#line 1472 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 174 "parser.y" /* yacc.c:1646  */
    { (yyval.ast_list) = new list<Ast *>(); }
#line 1478 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 175 "parser.y" /* yacc.c:1646  */
    { (yyval.ast_list) = (yyvsp[0].ast_list); }
#line 1484 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 179 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 1490 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval.ast)=(yyvsp[0].ast); }
#line 1496 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 183 "parser.y" /* yacc.c:1646  */
    { (yyval.ast)=(yyvsp[0].ast); }
#line 1502 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 184 "parser.y" /* yacc.c:1646  */
    { (yyval.ast)=(yyvsp[0].ast); }
#line 1508 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 185 "parser.y" /* yacc.c:1646  */
    { (yyval.ast)=(yyvsp[0].ast); }
#line 1514 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 186 "parser.y" /* yacc.c:1646  */
    { (yyval.ast)=(yyvsp[0].ast); }
#line 1520 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 190 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast_list) = new list<Ast *>();
		(yyval.ast_list)->push_back((yyvsp[0].ast));
	}
#line 1529 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 194 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast_list) = (yyvsp[-1].ast_list);
		(yyval.ast_list)->push_back((yyvsp[0].ast));
	}
#line 1538 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 201 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new Assignment_Ast((yyvsp[-3].ast), (yyvsp[-1].ast), yylineno);
		if (!(yyval.ast)->check_ast()) ast_error = true;
	}
#line 1547 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 208 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Relational_Expr_Ast((yyvsp[-2].ast), less_than, (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1553 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 209 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Relational_Expr_Ast((yyvsp[-2].ast), less_equalto, (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1559 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 210 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Relational_Expr_Ast((yyvsp[-2].ast), greater_equalto, (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1565 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 211 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Relational_Expr_Ast((yyvsp[-2].ast), equalto, (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1571 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 212 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Relational_Expr_Ast((yyvsp[-2].ast), greater_than, (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1577 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 213 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Relational_Expr_Ast((yyvsp[-2].ast), not_equalto, (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1583 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 214 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1589 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 215 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Logical_Expr_Ast((yyvsp[-2].ast), _logical_and, (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1595 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 216 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Logical_Expr_Ast((yyvsp[-2].ast), _logical_or, (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1601 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 217 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Logical_Expr_Ast(NULL, _logical_not, (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1607 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 221 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1613 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 222 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1619 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 223 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1625 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 224 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new UMinus_Ast((yyvsp[0].ast), NULL, yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1631 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 225 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Plus_Ast((yyvsp[-2].ast), (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1637 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 226 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Minus_Ast((yyvsp[-2].ast), (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1643 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 227 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Mult_Ast((yyvsp[-2].ast), (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1649 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 228 "parser.y" /* yacc.c:1646  */
    {  (yyval.ast) = new Divide_Ast((yyvsp[-2].ast), (yyvsp[0].ast), yylineno); if (!(yyval.ast)->check_ast()) ast_error = true; }
#line 1655 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 229 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = new Conditional_Expression_Ast((yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast), yylineno); }
#line 1661 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 233 "parser.y" /* yacc.c:1646  */
    {
		if (local_symbol_table->variable_in_symbol_list_check( *(yyvsp[0].string_value))) {
			(yyval.ast) = new Name_Ast( *(yyvsp[0].string_value), local_symbol_table->get_symbol_table_entry( *(yyvsp[0].string_value)), yylineno);
		}
		else if (program_object.variable_in_symbol_list_check( *(yyvsp[0].string_value))) {
			(yyval.ast) = new Name_Ast( *(yyvsp[0].string_value), program_object.get_symbol_table_entry( *(yyvsp[0].string_value)), yylineno);
		}
		else {
			yyerror("Variable has not been declared");
			exit(1);
		}
	}
#line 1678 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 248 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new Number_Ast<int>((yyvsp[0].integer_value), int_data_type, yylineno);
	}
#line 1686 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 251 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new Number_Ast<double>((yyvsp[0].double_value), double_data_type, yylineno);
	}
#line 1694 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 257 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new Selection_Statement_Ast((yyvsp[-2].ast), (yyvsp[0].ast), NULL, yylineno);
	}
#line 1702 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 264 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new Selection_Statement_Ast((yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast), yylineno);
	}
#line 1710 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 270 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new Iteration_Statement_Ast((yyvsp[-2].ast), (yyvsp[0].ast), yylineno, false);
	}
#line 1718 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 276 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new Iteration_Statement_Ast((yyvsp[-2].ast), (yyvsp[-5].ast), yylineno, true);
	}
#line 1726 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 282 "parser.y" /* yacc.c:1646  */
    {
		auto seq = new Sequence_Ast(yylineno);
		seq->ast_push_back((yyvsp[0].ast));
		(yyval.ast) = seq;
	}
#line 1736 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 287 "parser.y" /* yacc.c:1646  */
    {
		auto seq = new Sequence_Ast(yylineno);
		for (const auto &child_ast: *(yyvsp[-1].ast_list)) {
			seq->ast_push_back(child_ast);
		}
		(yyval.ast) = seq;
	}
#line 1748 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 1752 "parser.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 296 "parser.y" /* yacc.c:1906  */


void yyerror(string msg) {
	cout << "cs316: Error: Line: " << yylineno << ": " << msg << endl;
}
