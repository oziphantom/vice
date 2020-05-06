/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "mon_parse.y" /* yacc.c:337  */

/* -*- C -*-
 *
 * mon_parse.y - Parser for the VICE built-in monitor.
 *
 * Written by
 *  Daniel Sladic <sladic@eecg.toronto.edu>
 *  Andreas Boose <viceteam@t-online.de>
 *  Thomas Giesel <skoe@directbox.com>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"

#if !defined(MACOS_COMPILE) && !(defined(__OS2__) && defined(IDE_COMPILE))
#ifdef __GNUC__
#undef alloca
#ifndef ANDROID_COMPILE
#define        alloca(n)       __builtin_alloca (n)
#endif
#else
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#else  /* Not HAVE_ALLOCA_H.  */
#if !defined(_AIX) && !defined(WINCE)
#ifndef _MSC_VER
extern char *alloca();
#else
#define alloca(n)   _alloca(n)
#endif  /* MSVC */
#endif /* Not AIX and not WINCE.  */
#endif /* HAVE_ALLOCA_H.  */
#endif /* GCC.  */
#endif /* MACOS OS2 */

/* SunOS 4.x specific stuff */
#if defined(sun) || defined(__sun)
#  if !defined(__SVR4) && !defined(__svr4__)
#    ifdef __sparc__
#      define YYFREE
#    endif
#  endif
#endif

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "asm.h"
#include "console.h"
#include "lib.h"
#include "machine.h"
#include "mon_breakpoint.h"
#include "mon_command.h"
#include "mon_disassemble.h"
#include "mon_drive.h"
#include "mon_file.h"
#include "mon_memmap.h"
#include "mon_memory.h"
#include "mon_register.h"
#include "mon_util.h"
#include "montypes.h"
#include "resources.h"
#include "types.h"
#include "uimon.h"

#ifdef AMIGA_MORPHOS
#undef REG_PC
#endif

#define join_ints(x,y) (LO16_TO_HI16(x)|y)
#define separate_int1(x) (HI16_TO_LO16(x))
#define separate_int2(x) (LO16(x))

static int yyerror(char *s);
static int temp;
static int resolve_datatype(unsigned guess_type, const char *num);
static int resolve_range(enum t_memspace memspace, MON_ADDR range[2],
                         const char *num);

#ifdef __IBMC__
static void __yy_memcpy (char *to, char *from, int count);
#endif

/* Defined in the lexer */
extern int new_cmd, opt_asm;
extern void free_buffer(void);
extern void make_buffer(char *str);
extern int yylex(void);
extern int cur_len, last_len;

#define ERR_ILLEGAL_INPUT 1     /* Generic error as returned by yacc.  */
#define ERR_RANGE_BAD_START 2
#define ERR_RANGE_BAD_END 3
#define ERR_BAD_CMD 4
#define ERR_EXPECT_CHECKNUM 5
#define ERR_EXPECT_END_CMD 6
#define ERR_MISSING_CLOSE_PAREN 7
#define ERR_INCOMPLETE_COND_OP 8
#define ERR_EXPECT_FILENAME 9
#define ERR_ADDR_TOO_BIG 10
#define ERR_IMM_TOO_BIG 11
#define ERR_EXPECT_STRING 12
#define ERR_UNDEFINED_LABEL 13
#define ERR_EXPECT_DEVICE_NUM 14
#define ERR_EXPECT_ADDRESS 15
#define ERR_INVALID_REGISTER 16

#define BAD_ADDR (new_addr(e_invalid_space, 0))
#define CHECK_ADDR(x) ((x) == addr_mask(x))

#define YYDEBUG 1


#line 204 "mon_parse.c" /* yacc.c:337  */
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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_MON_PARSE_H_INCLUDED
# define YY_YY_MON_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    H_NUMBER = 258,
    D_NUMBER = 259,
    O_NUMBER = 260,
    B_NUMBER = 261,
    CONVERT_OP = 262,
    B_DATA = 263,
    H_RANGE_GUESS = 264,
    D_NUMBER_GUESS = 265,
    O_NUMBER_GUESS = 266,
    B_NUMBER_GUESS = 267,
    BAD_CMD = 268,
    MEM_OP = 269,
    IF = 270,
    MEM_COMP = 271,
    MEM_DISK8 = 272,
    MEM_DISK9 = 273,
    MEM_DISK10 = 274,
    MEM_DISK11 = 275,
    EQUALS = 276,
    TRAIL = 277,
    CMD_SEP = 278,
    LABEL_ASGN_COMMENT = 279,
    CMD_LOG = 280,
    CMD_LOGNAME = 281,
    CMD_SIDEFX = 282,
    CMD_DUMMY = 283,
    CMD_RETURN = 284,
    CMD_BLOCK_READ = 285,
    CMD_BLOCK_WRITE = 286,
    CMD_UP = 287,
    CMD_DOWN = 288,
    CMD_LOAD = 289,
    CMD_SAVE = 290,
    CMD_VERIFY = 291,
    CMD_IGNORE = 292,
    CMD_HUNT = 293,
    CMD_FILL = 294,
    CMD_MOVE = 295,
    CMD_GOTO = 296,
    CMD_REGISTERS = 297,
    CMD_READSPACE = 298,
    CMD_WRITESPACE = 299,
    CMD_RADIX = 300,
    CMD_MEM_DISPLAY = 301,
    CMD_BREAK = 302,
    CMD_BBREAK = 303,
    CMD_TRACE = 304,
    CMD_IO = 305,
    CMD_BRMON = 306,
    CMD_COMPARE = 307,
    CMD_DUMP = 308,
    CMD_UNDUMP = 309,
    CMD_EXIT = 310,
    CMD_DELETE = 311,
    CMD_CONDITION = 312,
    CMD_COMMAND = 313,
    CMD_ASSEMBLE = 314,
    CMD_DISASSEMBLE = 315,
    CMD_NEXT = 316,
    CMD_STEP = 317,
    CMD_PRINT = 318,
    CMD_DEVICE = 319,
    CMD_HELP = 320,
    CMD_WATCH = 321,
    CMD_DISK = 322,
    CMD_QUIT = 323,
    CMD_CHDIR = 324,
    CMD_BANK = 325,
    CMD_LOAD_LABELS = 326,
    CMD_SAVE_LABELS = 327,
    CMD_ADD_LABEL = 328,
    CMD_DEL_LABEL = 329,
    CMD_SHOW_LABELS = 330,
    CMD_CLEAR_LABELS = 331,
    CMD_RECORD = 332,
    CMD_MON_STOP = 333,
    CMD_PLAYBACK = 334,
    CMD_CHAR_DISPLAY = 335,
    CMD_SPRITE_DISPLAY = 336,
    CMD_TEXT_DISPLAY = 337,
    CMD_SCREENCODE_DISPLAY = 338,
    CMD_ENTER_DATA = 339,
    CMD_ENTER_BIN_DATA = 340,
    CMD_KEYBUF = 341,
    CMD_BLOAD = 342,
    CMD_BSAVE = 343,
    CMD_SCREEN = 344,
    CMD_UNTIL = 345,
    CMD_CPU = 346,
    CMD_YYDEBUG = 347,
    CMD_BACKTRACE = 348,
    CMD_SCREENSHOT = 349,
    CMD_PWD = 350,
    CMD_DIR = 351,
    CMD_RESOURCE_GET = 352,
    CMD_RESOURCE_SET = 353,
    CMD_LOAD_RESOURCES = 354,
    CMD_SAVE_RESOURCES = 355,
    CMD_ATTACH = 356,
    CMD_DETACH = 357,
    CMD_MON_RESET = 358,
    CMD_TAPECTRL = 359,
    CMD_CARTFREEZE = 360,
    CMD_CPUHISTORY = 361,
    CMD_MEMMAPZAP = 362,
    CMD_MEMMAPSHOW = 363,
    CMD_MEMMAPSAVE = 364,
    CMD_COMMENT = 365,
    CMD_LIST = 366,
    CMD_STOPWATCH = 367,
    RESET = 368,
    CMD_EXPORT = 369,
    CMD_AUTOSTART = 370,
    CMD_AUTOLOAD = 371,
    CMD_MAINCPU_TRACE = 372,
    CMD_LABEL_ASGN = 373,
    L_PAREN = 374,
    R_PAREN = 375,
    ARG_IMMEDIATE = 376,
    REG_A = 377,
    REG_X = 378,
    REG_Y = 379,
    COMMA = 380,
    INST_SEP = 381,
    L_BRACKET = 382,
    R_BRACKET = 383,
    LESS_THAN = 384,
    REG_U = 385,
    REG_S = 386,
    REG_PC = 387,
    REG_PCR = 388,
    REG_B = 389,
    REG_C = 390,
    REG_D = 391,
    REG_E = 392,
    REG_H = 393,
    REG_L = 394,
    REG_AF = 395,
    REG_BC = 396,
    REG_DE = 397,
    REG_HL = 398,
    REG_IX = 399,
    REG_IY = 400,
    REG_SP = 401,
    REG_IXH = 402,
    REG_IXL = 403,
    REG_IYH = 404,
    REG_IYL = 405,
    PLUS = 406,
    MINUS = 407,
    STRING = 408,
    FILENAME = 409,
    R_O_L = 410,
    OPCODE = 411,
    LABEL = 412,
    BANKNAME = 413,
    CPUTYPE = 414,
    MON_REGISTER = 415,
    COND_OP = 416,
    RADIX_TYPE = 417,
    INPUT_SPEC = 418,
    CMD_CHECKPT_ON = 419,
    CMD_CHECKPT_OFF = 420,
    TOGGLE = 421,
    MASK = 422
  };
#endif
/* Tokens.  */
#define H_NUMBER 258
#define D_NUMBER 259
#define O_NUMBER 260
#define B_NUMBER 261
#define CONVERT_OP 262
#define B_DATA 263
#define H_RANGE_GUESS 264
#define D_NUMBER_GUESS 265
#define O_NUMBER_GUESS 266
#define B_NUMBER_GUESS 267
#define BAD_CMD 268
#define MEM_OP 269
#define IF 270
#define MEM_COMP 271
#define MEM_DISK8 272
#define MEM_DISK9 273
#define MEM_DISK10 274
#define MEM_DISK11 275
#define EQUALS 276
#define TRAIL 277
#define CMD_SEP 278
#define LABEL_ASGN_COMMENT 279
#define CMD_LOG 280
#define CMD_LOGNAME 281
#define CMD_SIDEFX 282
#define CMD_DUMMY 283
#define CMD_RETURN 284
#define CMD_BLOCK_READ 285
#define CMD_BLOCK_WRITE 286
#define CMD_UP 287
#define CMD_DOWN 288
#define CMD_LOAD 289
#define CMD_SAVE 290
#define CMD_VERIFY 291
#define CMD_IGNORE 292
#define CMD_HUNT 293
#define CMD_FILL 294
#define CMD_MOVE 295
#define CMD_GOTO 296
#define CMD_REGISTERS 297
#define CMD_READSPACE 298
#define CMD_WRITESPACE 299
#define CMD_RADIX 300
#define CMD_MEM_DISPLAY 301
#define CMD_BREAK 302
#define CMD_BBREAK 303
#define CMD_TRACE 304
#define CMD_IO 305
#define CMD_BRMON 306
#define CMD_COMPARE 307
#define CMD_DUMP 308
#define CMD_UNDUMP 309
#define CMD_EXIT 310
#define CMD_DELETE 311
#define CMD_CONDITION 312
#define CMD_COMMAND 313
#define CMD_ASSEMBLE 314
#define CMD_DISASSEMBLE 315
#define CMD_NEXT 316
#define CMD_STEP 317
#define CMD_PRINT 318
#define CMD_DEVICE 319
#define CMD_HELP 320
#define CMD_WATCH 321
#define CMD_DISK 322
#define CMD_QUIT 323
#define CMD_CHDIR 324
#define CMD_BANK 325
#define CMD_LOAD_LABELS 326
#define CMD_SAVE_LABELS 327
#define CMD_ADD_LABEL 328
#define CMD_DEL_LABEL 329
#define CMD_SHOW_LABELS 330
#define CMD_CLEAR_LABELS 331
#define CMD_RECORD 332
#define CMD_MON_STOP 333
#define CMD_PLAYBACK 334
#define CMD_CHAR_DISPLAY 335
#define CMD_SPRITE_DISPLAY 336
#define CMD_TEXT_DISPLAY 337
#define CMD_SCREENCODE_DISPLAY 338
#define CMD_ENTER_DATA 339
#define CMD_ENTER_BIN_DATA 340
#define CMD_KEYBUF 341
#define CMD_BLOAD 342
#define CMD_BSAVE 343
#define CMD_SCREEN 344
#define CMD_UNTIL 345
#define CMD_CPU 346
#define CMD_YYDEBUG 347
#define CMD_BACKTRACE 348
#define CMD_SCREENSHOT 349
#define CMD_PWD 350
#define CMD_DIR 351
#define CMD_RESOURCE_GET 352
#define CMD_RESOURCE_SET 353
#define CMD_LOAD_RESOURCES 354
#define CMD_SAVE_RESOURCES 355
#define CMD_ATTACH 356
#define CMD_DETACH 357
#define CMD_MON_RESET 358
#define CMD_TAPECTRL 359
#define CMD_CARTFREEZE 360
#define CMD_CPUHISTORY 361
#define CMD_MEMMAPZAP 362
#define CMD_MEMMAPSHOW 363
#define CMD_MEMMAPSAVE 364
#define CMD_COMMENT 365
#define CMD_LIST 366
#define CMD_STOPWATCH 367
#define RESET 368
#define CMD_EXPORT 369
#define CMD_AUTOSTART 370
#define CMD_AUTOLOAD 371
#define CMD_MAINCPU_TRACE 372
#define CMD_LABEL_ASGN 373
#define L_PAREN 374
#define R_PAREN 375
#define ARG_IMMEDIATE 376
#define REG_A 377
#define REG_X 378
#define REG_Y 379
#define COMMA 380
#define INST_SEP 381
#define L_BRACKET 382
#define R_BRACKET 383
#define LESS_THAN 384
#define REG_U 385
#define REG_S 386
#define REG_PC 387
#define REG_PCR 388
#define REG_B 389
#define REG_C 390
#define REG_D 391
#define REG_E 392
#define REG_H 393
#define REG_L 394
#define REG_AF 395
#define REG_BC 396
#define REG_DE 397
#define REG_HL 398
#define REG_IX 399
#define REG_IY 400
#define REG_SP 401
#define REG_IXH 402
#define REG_IXL 403
#define REG_IYH 404
#define REG_IYL 405
#define PLUS 406
#define MINUS 407
#define STRING 408
#define FILENAME 409
#define R_O_L 410
#define OPCODE 411
#define LABEL 412
#define BANKNAME 413
#define CPUTYPE 414
#define MON_REGISTER 415
#define COND_OP 416
#define RADIX_TYPE 417
#define INPUT_SPEC 418
#define CMD_CHECKPT_ON 419
#define CMD_CHECKPT_OFF 420
#define TOGGLE 421
#define MASK 422

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 135 "mon_parse.y" /* yacc.c:352  */

    MON_ADDR a;
    MON_ADDR range[2];
    int i;
    REG_ID reg;
    CONDITIONAL cond_op;
    cond_node_t *cond_node;
    RADIXTYPE rt;
    ACTION action;
    char *str;
    asm_mode_addr_info_t mode;

#line 594 "mon_parse.c" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MON_PARSE_H_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  322
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1793

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  176
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  322
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  648

#define YYUNDEFTOK  2
#define YYMAXUTOK   422

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     172,   173,   170,   168,     2,   169,     2,   171,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   175,     2,
       2,     2,     2,     2,   174,     2,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   199,   199,   200,   201,   204,   205,   208,   209,   210,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   228,   230,   232,   234,   236,   238,   240,
     242,   244,   246,   248,   250,   252,   254,   256,   258,   260,
     262,   264,   266,   268,   270,   272,   274,   276,   279,   281,
     283,   286,   291,   296,   298,   300,   302,   304,   306,   308,
     310,   312,   314,   318,   325,   324,   327,   329,   331,   335,
     337,   339,   341,   343,   345,   347,   349,   351,   353,   355,
     357,   359,   361,   363,   365,   367,   369,   371,   373,   377,
     386,   388,   407,   411,   414,   423,   426,   435,   440,   442,
     444,   446,   448,   450,   452,   454,   456,   458,   460,   464,
     466,   471,   478,   486,   493,   505,   509,   511,   529,   531,
     533,   535,   537,   541,   543,   545,   547,   549,   551,   553,
     555,   557,   559,   561,   563,   565,   567,   569,   571,   573,
     575,   577,   579,   581,   583,   585,   589,   591,   593,   595,
     597,   599,   601,   603,   605,   607,   609,   611,   613,   615,
     617,   619,   621,   623,   625,   627,   631,   633,   635,   639,
     641,   645,   649,   652,   653,   656,   657,   660,   661,   664,
     665,   668,   669,   672,   678,   686,   687,   690,   694,   695,
     698,   699,   702,   703,   705,   709,   710,   713,   718,   723,
     733,   734,   737,   738,   739,   740,   741,   744,   746,   748,
     749,   750,   751,   752,   753,   754,   757,   758,   760,   765,
     767,   769,   771,   775,   781,   787,   793,   801,   802,   805,
     806,   809,   810,   813,   814,   815,   818,   819,   822,   823,
     824,   825,   828,   829,   830,   833,   834,   835,   836,   837,
     840,   841,   842,   845,   855,   856,   859,   866,   877,   888,
     896,   915,   921,   929,   937,   939,   941,   942,   943,   944,
     945,   946,   947,   949,   951,   953,   955,   956,   957,   958,
     959,   960,   961,   962,   963,   964,   965,   966,   967,   968,
     969,   970,   971,   972,   973,   975,   976,   991,   995,   999,
    1003,  1007,  1011,  1015,  1019,  1023,  1035,  1050,  1054,  1058,
    1062,  1066,  1070,  1074,  1078,  1082,  1094,  1099,  1107,  1108,
    1109,  1110,  1114
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "H_NUMBER", "D_NUMBER", "O_NUMBER",
  "B_NUMBER", "CONVERT_OP", "B_DATA", "H_RANGE_GUESS", "D_NUMBER_GUESS",
  "O_NUMBER_GUESS", "B_NUMBER_GUESS", "BAD_CMD", "MEM_OP", "IF",
  "MEM_COMP", "MEM_DISK8", "MEM_DISK9", "MEM_DISK10", "MEM_DISK11",
  "EQUALS", "TRAIL", "CMD_SEP", "LABEL_ASGN_COMMENT", "CMD_LOG",
  "CMD_LOGNAME", "CMD_SIDEFX", "CMD_DUMMY", "CMD_RETURN", "CMD_BLOCK_READ",
  "CMD_BLOCK_WRITE", "CMD_UP", "CMD_DOWN", "CMD_LOAD", "CMD_SAVE",
  "CMD_VERIFY", "CMD_IGNORE", "CMD_HUNT", "CMD_FILL", "CMD_MOVE",
  "CMD_GOTO", "CMD_REGISTERS", "CMD_READSPACE", "CMD_WRITESPACE",
  "CMD_RADIX", "CMD_MEM_DISPLAY", "CMD_BREAK", "CMD_BBREAK", "CMD_TRACE",
  "CMD_IO", "CMD_BRMON", "CMD_COMPARE", "CMD_DUMP", "CMD_UNDUMP",
  "CMD_EXIT", "CMD_DELETE", "CMD_CONDITION", "CMD_COMMAND", "CMD_ASSEMBLE",
  "CMD_DISASSEMBLE", "CMD_NEXT", "CMD_STEP", "CMD_PRINT", "CMD_DEVICE",
  "CMD_HELP", "CMD_WATCH", "CMD_DISK", "CMD_QUIT", "CMD_CHDIR", "CMD_BANK",
  "CMD_LOAD_LABELS", "CMD_SAVE_LABELS", "CMD_ADD_LABEL", "CMD_DEL_LABEL",
  "CMD_SHOW_LABELS", "CMD_CLEAR_LABELS", "CMD_RECORD", "CMD_MON_STOP",
  "CMD_PLAYBACK", "CMD_CHAR_DISPLAY", "CMD_SPRITE_DISPLAY",
  "CMD_TEXT_DISPLAY", "CMD_SCREENCODE_DISPLAY", "CMD_ENTER_DATA",
  "CMD_ENTER_BIN_DATA", "CMD_KEYBUF", "CMD_BLOAD", "CMD_BSAVE",
  "CMD_SCREEN", "CMD_UNTIL", "CMD_CPU", "CMD_YYDEBUG", "CMD_BACKTRACE",
  "CMD_SCREENSHOT", "CMD_PWD", "CMD_DIR", "CMD_RESOURCE_GET",
  "CMD_RESOURCE_SET", "CMD_LOAD_RESOURCES", "CMD_SAVE_RESOURCES",
  "CMD_ATTACH", "CMD_DETACH", "CMD_MON_RESET", "CMD_TAPECTRL",
  "CMD_CARTFREEZE", "CMD_CPUHISTORY", "CMD_MEMMAPZAP", "CMD_MEMMAPSHOW",
  "CMD_MEMMAPSAVE", "CMD_COMMENT", "CMD_LIST", "CMD_STOPWATCH", "RESET",
  "CMD_EXPORT", "CMD_AUTOSTART", "CMD_AUTOLOAD", "CMD_MAINCPU_TRACE",
  "CMD_LABEL_ASGN", "L_PAREN", "R_PAREN", "ARG_IMMEDIATE", "REG_A",
  "REG_X", "REG_Y", "COMMA", "INST_SEP", "L_BRACKET", "R_BRACKET",
  "LESS_THAN", "REG_U", "REG_S", "REG_PC", "REG_PCR", "REG_B", "REG_C",
  "REG_D", "REG_E", "REG_H", "REG_L", "REG_AF", "REG_BC", "REG_DE",
  "REG_HL", "REG_IX", "REG_IY", "REG_SP", "REG_IXH", "REG_IXL", "REG_IYH",
  "REG_IYL", "PLUS", "MINUS", "STRING", "FILENAME", "R_O_L", "OPCODE",
  "LABEL", "BANKNAME", "CPUTYPE", "MON_REGISTER", "COND_OP", "RADIX_TYPE",
  "INPUT_SPEC", "CMD_CHECKPT_ON", "CMD_CHECKPT_OFF", "TOGGLE", "MASK",
  "'+'", "'-'", "'*'", "'/'", "'('", "')'", "'@'", "':'", "$accept",
  "top_level", "command_list", "end_cmd", "command", "machine_state_rules",
  "register_mod", "symbol_table_rules", "asm_rules", "$@1", "memory_rules",
  "checkpoint_rules", "checkpoint_control_rules", "monitor_state_rules",
  "monitor_misc_rules", "disk_rules", "cmd_file_rules", "data_entry_rules",
  "monitor_debug_rules", "rest_of_line", "opt_rest_of_line", "filename",
  "device_num", "mem_op", "opt_mem_op", "register", "reg_list", "reg_asgn",
  "checkpt_num", "address_opt_range", "address_range", "opt_address",
  "address", "opt_sep", "memspace", "memloc", "memaddr", "expression",
  "opt_if_cond_expr", "cond_expr", "cond_operand", "data_list",
  "data_element", "hunt_list", "hunt_element", "value", "d_number",
  "guess_default", "number", "assembly_instr_list", "assembly_instruction",
  "post_assemble", "asm_operand_mode", "index_reg", "index_ureg", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,    43,    45,
      42,    47,    40,    41,    64,    58
};
# endif

#define YYPACT_NINF -478

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-478)))

#define YYTABLE_NINF -202

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1211,   122,  -478,  -478,    47,    12,    49,    62,   199,   122,
     122,   526,   526,    12,    12,    12,   451,  1574,  1574,  1574,
     943,   173,    81,   918,  1176,  -150,  1176,   943,  1574,    12,
      12,   199,   989,   451,   451,  1197,   466,   526,   526,   122,
     659,   237,  1176,  -141,   199,  -141,   261,   233,   233,  1197,
     296,  1139,  1139,    12,   199,    12,   466,   466,   466,   466,
    1197,   199,  -141,    12,    12,   199,   466,   176,   199,   199,
      12,   199,  -133,  -117,  -101,    12,    12,    12,   122,   526,
     -29,   199,   526,   199,   526,    12,  -133,   286,   209,   199,
      12,    12,   -56,    91,  1615,   989,   989,   102,  1381,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,    96,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,   122,  -478,   -14,
      37,  -478,  -478,  -478,  -478,  -478,  -478,   199,  -478,  -478,
    -478,   199,   199,  -478,   199,  -478,  -478,   863,   863,  -478,
    -478,   122,  -478,   122,   499,   553,   499,  -478,  -478,  -478,
    -478,  -478,   526,  -478,  -478,  -478,   -29,   -29,   -29,  -478,
    -478,  -478,   -29,   -29,  -478,   199,   -29,  -478,   126,   372,
    -478,   164,   199,  -478,   -29,  -478,   199,  -478,   720,  -478,
    -478,   129,  1574,   139,  -478,  1574,  -478,   199,   -29,   199,
     199,  -478,   379,  -478,   199,   143,    23,   201,  -478,   199,
    -478,   122,  -478,   122,    37,   199,  -478,  -478,   199,  -478,
    1574,   199,  -478,   199,   199,  -478,   316,   199,   -29,   199,
     -29,   -29,   199,   -29,  -478,   199,  -478,   199,   199,  -478,
     199,  -478,   199,  -478,   199,  -478,   199,  -478,   199,   696,
    -478,   199,   499,   499,  -478,  -478,   199,   199,  -478,  -478,
    -478,   526,  -478,  -478,   199,   199,     6,   199,   199,   122,
      37,  -478,   122,   122,  -478,  -478,   122,  -478,  -478,   122,
     -29,   199,   498,  -478,   199,   382,   199,  -478,  -478,  1668,
    1668,   199,  1197,  1522,  1331,    39,   -30,  1010,  1331,    48,
    -478,    58,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,    69,  -478,  -478,   199,
    -478,   199,  -478,  -478,  -478,    11,  -478,   122,   122,   122,
     122,  -478,  -478,  -478,  -478,  -478,    76,   968,    37,    37,
    -478,   753,  1346,  1504,  1379,  -478,   122,   662,  1197,  1217,
     696,  1197,  -478,  1331,  1331,   380,  -478,  -478,  -478,  1574,
    -478,  -478,   196,  1574,   196,  -478,  1197,  -478,  -478,  -478,
     677,   199,    59,  -478,    64,  -478,    37,    37,  -478,  -478,
    -478,   196,  -478,  -478,  -478,  -478,    67,  -478,    12,  -478,
      12,    79,  -478,    83,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  1594,  -478,  -478,  -478,   753,  1538,  -478,
    -478,  -478,   122,  -478,  -478,   199,  -478,  -478,    37,  -478,
      37,    37,    37,   728,   122,  -478,  -478,  -478,  -478,  1331,
    -478,  1331,  -478,   306,   106,   119,   121,   128,   147,   148,
     -69,  -478,   217,  -478,  -478,  -478,  -478,   290,    65,  -478,
     144,   634,   146,   149,   -64,  -478,   217,   217,  1643,  -478,
    -478,  -478,  -478,  -104,  -104,  -478,  -478,   199,  1197,   199,
    -478,  -478,   199,  -478,   199,  -478,   199,   199,    37,  -478,
    -478,   421,  -478,  -478,  -478,  -478,  -478,  1594,   199,  -478,
    -478,   199,   677,   199,   196,   199,   199,   677,  1556,  -478,
      94,  -478,  -478,  -478,   199,   150,   159,   199,  -478,  -478,
     199,   199,   199,   199,   199,   199,  -478,   696,   199,  -478,
     199,    37,  -478,  -478,  -478,  -478,  -478,  -478,   199,    37,
     199,   199,   199,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
     161,  -114,  -478,   217,  -478,   137,   217,   638,   -42,   217,
     217,   596,   174,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,   111,  -478,   199,  -478,  -478,    24,
     125,  -478,   151,  -478,  -478,    64,    64,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,   683,   181,   190,  -478,  -478,   204,   217,
     208,  -478,   -22,   215,   216,   225,   228,   194,  -478,  -478,
    -478,  1197,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,   212,  -478,   232,  -478,  -478,   238,  -478,  -478,
    -478,  -478,  -478,  -478,   221,  -478,  -478,  -478
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,    22,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   174,     0,     0,     0,     0,     0,     0,     0,
     201,     0,     0,     0,     0,     0,   174,     0,     0,     0,
       0,     0,     0,     0,   276,     0,     0,     0,     2,     5,
      10,    47,    11,    13,    12,    14,    15,    16,    17,    18,
      19,    20,    21,     0,   245,   246,   247,   248,   244,   243,
     242,   202,   203,   204,   205,   206,   183,     0,   237,     0,
       0,   215,   249,   236,     9,     8,     7,     0,   114,   176,
     175,     0,     0,   110,     0,   112,    35,     0,     0,   200,
      42,     0,    44,     0,     0,     0,     0,   189,   238,   241,
     240,   239,     0,   188,   193,   199,   201,   201,   201,   197,
     207,   208,   201,   201,    28,     0,   201,    48,     0,     0,
     186,     0,     0,   117,   201,    75,     0,   190,   201,   180,
      90,   181,     0,   182,    97,     0,    29,     0,   201,     0,
       0,   121,     9,   105,     0,     0,     0,     0,    68,     0,
      40,     0,    38,     0,     0,     0,   172,   125,     0,    95,
       0,     0,   120,     0,     0,    23,     0,     0,   201,     0,
     201,   201,     0,   201,    59,     0,    61,     0,     0,   167,
       0,    77,     0,    79,     0,    81,     0,    83,     0,     0,
     170,     0,     0,     0,    46,    93,     0,     0,    31,   171,
     130,     0,   132,   173,     0,     0,     0,     0,     0,     0,
       0,   139,     0,     0,   142,    33,     0,    84,    85,     0,
     201,     0,     9,   158,     0,   177,     0,   145,   119,     0,
       0,     0,     0,     0,     0,   277,     0,     0,     0,   278,
     279,   280,   281,   282,   285,   288,   289,   290,   291,   292,
     293,   294,   283,   286,   284,   287,   257,   253,    99,     0,
     101,     0,     1,     6,     3,     0,   184,     0,     0,     0,
       0,   127,   113,   115,   109,   111,   201,     0,     0,     0,
     178,   201,   150,     0,     0,   102,     0,     0,     0,     0,
       0,     0,    27,     0,     0,     0,    50,    49,   116,     0,
      74,   179,   217,     0,   217,    30,     0,    36,    37,   104,
       0,     0,     0,    66,     0,    67,     0,     0,   124,   118,
     126,   217,   123,   128,    25,    24,     0,    52,     0,    54,
       0,     0,    56,     0,    58,    60,   166,   168,    76,    78,
      80,    82,   230,     0,   228,   229,   129,   201,     0,    92,
      32,   133,     0,   131,   135,     0,   137,   138,     0,   161,
       0,     0,     0,     0,     0,   143,   159,   144,   162,     0,
     164,     0,   122,     0,     0,     0,     0,     0,     0,     0,
       0,   256,     0,   318,   319,   322,   321,     0,   301,   320,
       0,     0,     0,     0,     0,   295,     0,     0,     0,    98,
     100,   214,   213,   209,   210,   211,   212,     0,     0,     0,
      43,    45,     0,   151,     0,   155,     0,     0,     0,   235,
     234,     0,   232,   233,   192,   194,   198,     0,     0,   187,
     185,     0,     0,     0,   217,     0,     0,     0,     0,   223,
       0,   222,   224,   108,     0,   255,   254,     0,    41,    39,
       0,     0,     0,     0,     0,     0,   169,     0,     0,   153,
       0,     0,   136,   160,   140,   141,    34,    86,     0,     0,
       0,     0,     0,    62,   266,   267,   268,   269,   270,   271,
     262,     0,   303,     0,   299,   297,     0,     0,     0,     0,
       0,     0,   316,   302,   304,   258,   259,   260,   305,   261,
     296,   156,   195,   157,   146,   149,   148,   154,   103,    72,
     231,    71,    69,    73,   216,    89,     0,    96,    70,     0,
       0,   226,     0,   106,   107,     0,   252,    65,    94,    26,
      51,    53,    55,    57,   227,   147,   152,   134,    87,    88,
     163,   165,    63,     0,     0,     0,   300,   298,     0,     0,
       0,   311,     0,     0,     0,     0,     0,     0,    91,   221,
     220,     0,   219,   218,   250,   251,   272,   265,   273,   274,
     275,   263,     0,   313,     0,   309,   307,     0,   312,   314,
     315,   306,   317,   225,     0,   310,   308,   264
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -478,  -478,  -478,   574,   274,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,   211,
     288,    60,   213,  -478,   -21,    -5,  -478,    21,   480,    22,
       9,  -276,    27,   945,   -17,  -296,  -478,    82,  -267,  -477,
    -478,    34,  -140,  -478,   -93,  -478,  -478,  -478,   110,  -478,
    -367,  -478,  -478,   459,   -68
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    97,    98,   138,    99,   100,   101,   102,   103,   374,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   218,
     264,   141,   284,   191,   192,   128,   179,   180,   162,   186,
     187,   467,   188,   468,   129,   169,   170,   285,   493,   500,
     501,   403,   404,   481,   482,   131,   163,   132,   171,   505,
     113,   507,   317,   448,   449
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     168,   168,   168,   176,   181,   195,   168,   506,   193,   604,
     176,   168,   461,   139,   216,   574,   178,   605,   176,   168,
     579,   220,   263,   215,   371,   619,   166,   172,   173,   226,
     228,   230,   176,   233,   235,   237,   265,   198,   134,   168,
     168,   168,   168,   176,   167,   167,   167,   175,   134,   168,
     134,   540,   266,   486,   197,   167,   541,   486,   209,   135,
     136,   551,   207,   134,   552,   472,   329,   330,   476,   135,
     136,   135,   136,   154,   155,   156,   231,  -196,   242,   244,
     246,   248,   134,   130,   135,   136,   611,   249,   256,   199,
     200,   147,   148,   443,   444,   134,   149,   495,  -196,  -196,
     445,   446,   322,   135,   136,   623,   636,   227,   229,   612,
     291,   133,   292,   238,   510,   240,   135,   136,   324,   133,
     133,   214,   447,   252,   253,   114,   115,   116,   117,   637,
     261,   518,   118,   119,   120,   267,   268,   269,   121,   122,
     123,   124,   125,   361,   620,   280,   326,   354,   149,   133,
     289,   290,   622,   189,   114,   115,   116,   117,   370,   415,
     270,   118,   119,   120,   442,   134,   140,   121,   122,   123,
     124,   125,   363,   456,   134,   168,  -201,   134,   168,   327,
     328,   329,   330,   457,   462,   582,   135,   136,   133,   121,
     122,   123,   124,   125,   458,   135,   136,   133,   135,   136,
     134,   149,   134,   168,   316,   327,   328,   329,   330,   325,
     134,   492,   504,   137,   362,   142,   545,   364,   624,   625,
      94,   135,   136,   135,   136,   511,   534,   576,   144,   336,
     337,   135,   136,   338,   139,   339,   514,   133,   134,   535,
     515,   536,   381,   182,   327,   328,   329,   330,   537,   121,
     122,   123,   124,   125,   221,   582,   223,   133,   133,   135,
     136,   133,   134,   133,   133,   133,   133,   538,   539,   546,
     497,   549,   582,   251,   550,   176,   585,   121,   122,   123,
     124,   125,   126,   135,   136,   586,   603,   282,   607,   114,
     115,   116,   117,   376,   127,   377,   118,   119,   120,   617,
     621,   631,   121,   122,   123,   124,   125,   134,   135,   136,
     632,   126,   121,   122,   123,   124,   125,   134,   642,   433,
     176,   133,   286,   133,   326,   498,   168,   176,   135,   136,
     532,   176,   633,   126,   176,   257,   635,   644,   135,   136,
     443,   444,   168,   638,   639,   647,   168,   445,   446,   176,
     178,   418,   474,   640,   420,   421,   641,   -64,   422,   405,
     645,   423,   133,   133,   469,   499,   646,   341,   343,   344,
     167,   477,   323,   134,   281,   484,   490,   594,   488,   133,
    -189,   491,   133,   133,   487,   494,   133,   140,   570,   133,
     560,   168,   216,   496,   135,   136,   121,   122,   123,   124,
     125,  -189,  -189,   440,   441,     0,   168,   454,   455,   463,
     464,   465,   466,   443,   444,     0,     0,   520,     0,   224,
     445,   446,   134,     0,   114,   115,   116,   117,   478,     0,
       0,   118,   119,   120,     0,   167,     0,   133,   133,   133,
     133,   149,   543,   135,   136,   528,   126,     0,   512,     0,
     513,   176,   157,   232,     0,   158,   133,   483,   127,     0,
     405,   159,   160,   161,   489,   407,   408,   134,     0,   114,
     115,   116,   117,     0,  -201,   164,   118,   119,   120,     0,
     502,   176,   121,   122,   123,   124,   125,   499,   135,   136,
       0,     0,   499,     0,   521,   562,     0,   355,     0,  -178,
     340,     0,   114,   115,   116,   117,   529,     0,     0,   118,
     119,   120,   204,   205,   206,   121,   122,   123,   124,   125,
    -178,  -178,   133,     0,     0,   581,     0,   134,     0,  -201,
    -201,  -201,  -201,     0,   133,     0,  -201,  -201,  -201,   530,
     126,   531,  -201,  -201,  -201,  -201,  -201,     0,   135,   136,
     327,   328,   329,   330,   342,     0,   114,   115,   116,   117,
       0,     0,     0,   118,   119,   120,     0,     0,   559,   121,
     122,   123,   124,   125,   479,   319,   321,   499,     0,     0,
     143,   145,   146,     0,     0,   150,   152,     0,   480,     0,
       0,   483,     0,     0,   174,   177,   183,   185,   190,     0,
     194,   196,   502,     0,   176,   201,   203,   502,     0,     0,
     208,   210,   212,     0,     0,   217,   219,     0,   222,     0,
     225,     0,     0,   165,     0,   234,   236,   405,   239,     0,
     241,   243,   245,   247,     0,   250,     0,     0,     0,   254,
     255,   258,   259,   260,     0,   262,     0,     0,   643,     0,
       0,   149,     0,   271,     0,   274,   275,   277,   278,   126,
       0,   283,   287,   288,     0,   114,   115,   116,   117,   318,
     320,   127,   118,   119,   120,   121,   122,   123,   124,   125,
     114,   115,   116,   117,     0,     0,  -201,   118,   119,   120,
       0,     0,   502,   121,   122,   123,   124,   125,  -201,   114,
     115,   116,   117,     0,   331,     0,   118,   119,   120,     0,
       0,   332,     0,   126,     0,   333,   334,     0,   335,   443,
     444,  -191,     0,     0,     0,   127,   445,   446,   615,   134,
       0,   114,   115,   116,   117,  -191,   345,   164,   118,   119,
     120,     0,  -191,  -191,   121,   122,   123,   124,   125,   352,
     135,   136,     0,   356,  -196,   357,   358,   443,   444,     0,
     360,   443,   444,     0,   445,   446,     0,     0,   445,   446,
       0,   365,     0,   367,   368,  -196,  -196,     0,   369,     0,
       0,   373,     0,   375,     0,     0,   547,     0,   378,   379,
     609,     0,   380,     0,     0,   382,   497,   383,   384,     0,
     385,   387,     0,   389,     0,   626,   392,   627,     0,   394,
       0,   395,   396,     0,   397,   479,   398,     0,   399,     0,
     400,     0,   401,     0,     0,   406,   628,   629,   630,   480,
     409,   410,     0,     0,     0,   411,     0,   126,   413,   414,
       0,   416,   417,     0,   419,   149,     0,     0,     0,   402,
       0,   498,     0,     0,     0,   425,     0,     0,   426,     0,
     427,     0,     0,   428,   430,   432,   114,   115,   116,   117,
       0,     0,     0,   118,   119,   120,     0,     0,   149,   121,
     122,   123,   124,   125,     0,   165,     0,     0,     0,     0,
       0,     0,     0,   459,     0,   460,   327,   328,   329,   330,
       0,   542,     0,     0,     0,     0,   544,     0,     0,     0,
     548,     0,   470,   471,     0,   553,   554,     0,     0,   134,
       0,   114,   115,   116,   117,     0,     0,   164,   118,   119,
     120,     0,     0,     0,   121,   122,   123,   124,   125,     0,
     135,   136,     0,     0,   134,   503,   114,   115,   116,   117,
     508,   509,     0,   118,   119,   120,   151,   153,     0,   121,
     122,   123,   124,   125,     0,   135,   136,     0,     0,     0,
       0,   114,   115,   116,   117,     0,     0,   516,   118,   119,
     120,     0,   211,   213,   121,   122,   123,   124,   125,   522,
     202,     0,   523,   158,   524,   525,   526,   527,     0,   159,
     160,   161,   606,     0,     0,   608,   610,   533,   613,   614,
     616,   135,   136,   114,   115,   116,   117,     0,     0,     0,
     118,   119,   120,   126,   272,   273,     0,   276,     0,   279,
       0,   327,   328,   329,   330,   127,     0,     0,     0,     0,
       0,   561,     0,   563,     0,     0,   564,     0,   565,     0,
     566,   567,   568,     0,     0,   569,     0,     0,     0,     0,
       0,   571,   572,     0,     0,   573,     0,   575,   634,   577,
     578,     0,     0,     0,   583,   165,     0,     0,   584,     0,
     184,   587,     0,     0,   588,   589,   590,   591,   592,   593,
       0,     0,   595,     0,   596,   597,     0,     0,     0,     0,
     165,     0,   598,   599,   600,   601,   602,   346,     0,     0,
       0,   347,   348,   349,     0,     0,     0,   350,   351,     0,
       0,   353,     0,     0,     0,   165,     0,     0,     0,   359,
       0,     0,   450,   348,     0,   451,   327,   328,   329,   330,
     134,     0,     0,   366,   452,     0,   453,     0,     0,     0,
     618,   372,     0,     0,     0,   121,   122,   123,   124,   125,
       0,   135,   136,     0,     0,     0,     0,     0,     0,     0,
       0,   386,     0,   388,     0,   390,   391,   134,   393,  -182,
    -182,  -182,  -182,     0,     0,  -182,  -182,  -182,  -182,     0,
     189,     0,  -182,  -182,  -182,  -182,  -182,     0,   135,   136,
     114,   115,   116,   117,     0,     0,   412,   118,   119,   120,
       0,     0,     0,   121,   122,   123,   124,   125,     1,     0,
     114,   115,   116,   117,     2,   424,   485,   118,   119,   120,
       0,     0,     0,     3,   429,   431,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     0,     0,    22,    23,    24,    25,
      26,    27,     0,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,     0,    89,    90,    91,    92,    93,
       0,     0,     0,  -182,   114,   115,   116,   117,     0,     0,
       0,   118,   119,   120,     0,     0,     0,  -178,   517,  -178,
    -178,  -178,  -178,     0,   165,  -178,  -178,  -178,  -178,     0,
       0,     0,  -178,  -178,  -178,  -178,  -178,    94,     0,     0,
       0,     0,     0,     0,     0,    95,    96,     0,     0,     0,
     475,     0,   114,   115,   116,   117,     0,     0,     1,   118,
     119,   120,     0,     0,     2,   121,   122,   123,   124,   125,
       0,  -196,  -196,     0,     0,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     0,     0,    22,    23,    24,    25,
      26,    27,   517,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,     0,    89,    90,    91,    92,    93,
       0,     0,     0,  -178,   149,   473,     0,   114,   115,   116,
     117,     0,     0,   164,   118,   119,   120,     0,     0,     0,
     121,   122,   123,   124,   125,   114,   115,   116,   117,     0,
       0,     0,   118,   119,   120,     0,   165,     0,     0,   519,
       0,   114,   115,   116,   117,    95,    96,   164,   118,   119,
     120,     0,     0,     0,   121,   122,   123,   124,   125,   114,
     115,   116,   117,     0,     0,     0,   118,   119,   120,     0,
       0,     0,   121,   122,   123,   124,   125,   114,   115,   116,
     117,     0,     0,   164,   118,   119,   120,     0,     0,     0,
     121,   122,   123,   124,   125,   134,     0,  -201,  -201,  -201,
    -201,     0,     0,     0,  -201,  -201,  -201,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   135,   136,   114,   115,
     116,   117,     0,     0,     0,   118,   119,   120,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   114,   115,   116,   117,
       0,     0,     0,   118,   119,   120,     0,     0,     0,     0,
       0,   165,     0,   434,   435,   436,   437,   438,   439,   134,
       0,  -201,  -201,  -201,  -201,     0,     0,     0,  -201,  -201,
    -201,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,   136,     0,     0,     0,   165,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   165,   580,     0,     0,     0,     0,   149,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   165,     0,     0,   293,     0,   294,   295,     0,     0,
     296,     0,   297,     0,   298,     0,     0,  -201,     0,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   555,   556,     0,     0,
       0,     0,     0,   445,   557,   558,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149
};

static const yytype_int16 yycheck[] =
{
      17,    18,    19,    20,    21,    26,    23,   374,   158,   123,
      27,    28,     1,     1,   155,   492,    21,   131,    35,    36,
     497,    42,   155,    40,     1,     1,    17,    18,    19,    46,
      47,    48,    49,    50,    51,    52,   153,    28,     1,    56,
      57,    58,    59,    60,    17,    18,    19,    20,     1,    66,
       1,   120,   153,   349,    27,    28,   125,   353,    36,    22,
      23,   125,    35,     1,   128,   341,   170,   171,   344,    22,
      23,    22,    23,    13,    14,    15,    49,     1,    56,    57,
      58,    59,     1,     1,    22,    23,   128,    60,    66,    29,
      30,     9,    10,   123,   124,     1,   125,   364,    22,    23,
     130,   131,     0,    22,    23,   582,   128,    47,    48,   151,
     166,     1,    21,    53,   381,    55,    22,    23,    22,     9,
      10,    39,   152,    63,    64,     3,     4,     5,     6,   151,
      70,   407,    10,    11,    12,    75,    76,    77,    16,    17,
      18,    19,    20,    14,   120,    85,   160,    21,   125,    39,
      90,    91,     1,    14,     3,     4,     5,     6,    15,   153,
      78,    10,    11,    12,   125,     1,   154,    16,    17,    18,
      19,    20,   193,   125,     1,   192,   153,     1,   195,   168,
     169,   170,   171,   125,   173,   161,    22,    23,    78,    16,
      17,    18,    19,    20,   125,    22,    23,    87,    22,    23,
       1,   125,     1,   220,    94,   168,   169,   170,   171,   127,
       1,    15,   153,   166,   192,   166,   151,   195,   585,   586,
     156,    22,    23,    22,    23,   158,   120,   494,   166,   147,
     148,    22,    23,   151,     1,   153,   157,   127,     1,   120,
     157,   120,   220,   162,   168,   169,   170,   171,   120,    16,
      17,    18,    19,    20,    43,   161,    45,   147,   148,    22,
      23,   151,     1,   153,   154,   155,   156,   120,   120,   125,
     119,   125,   161,    62,   125,   292,   126,    16,    17,    18,
      19,    20,   160,    22,    23,   126,   125,     1,   151,     3,
       4,     5,     6,   211,   172,   213,    10,    11,    12,   125,
     175,   120,    16,    17,    18,    19,    20,     1,    22,    23,
     120,   160,    16,    17,    18,    19,    20,     1,   124,   292,
     337,   211,   113,   213,   160,   174,   343,   344,    22,    23,
      24,   348,   128,   160,   351,   159,   128,   125,    22,    23,
     123,   124,   359,   128,   128,   124,   363,   130,   131,   366,
     355,   269,   343,   128,   272,   273,   128,   156,   276,   249,
     128,   279,   252,   253,   337,   370,   128,   154,   155,   156,
     343,   344,    98,     1,    86,   348,   355,   517,   351,   269,
       1,   359,   272,   273,   350,   363,   276,   154,   481,   279,
     458,   408,   155,   366,    22,    23,    16,    17,    18,    19,
      20,    22,    23,   293,   294,    -1,   423,   297,   298,   327,
     328,   329,   330,   123,   124,    -1,    -1,   408,    -1,   158,
     130,   131,     1,    -1,     3,     4,     5,     6,   346,    -1,
      -1,    10,    11,    12,    -1,   408,    -1,   327,   328,   329,
     330,   125,   152,    22,    23,   423,   160,    -1,   388,    -1,
     390,   468,     1,   157,    -1,     4,   346,   347,   172,    -1,
     350,    10,    11,    12,   354,   252,   253,     1,    -1,     3,
       4,     5,     6,    -1,   158,     9,    10,    11,    12,    -1,
     370,   498,    16,    17,    18,    19,    20,   492,    22,    23,
      -1,    -1,   497,    -1,   412,   468,    -1,   125,    -1,     1,
       1,    -1,     3,     4,     5,     6,   424,    -1,    -1,    10,
      11,    12,    32,    33,    34,    16,    17,    18,    19,    20,
      22,    23,   412,    -1,    -1,   498,    -1,     1,    -1,     3,
       4,     5,     6,    -1,   424,    -1,    10,    11,    12,   429,
     160,   431,    16,    17,    18,    19,    20,    -1,    22,    23,
     168,   169,   170,   171,     1,    -1,     3,     4,     5,     6,
      -1,    -1,    -1,    10,    11,    12,    -1,    -1,   458,    16,
      17,    18,    19,    20,   153,    95,    96,   582,    -1,    -1,
       6,     7,     8,    -1,    -1,    11,    12,    -1,   167,    -1,
      -1,   481,    -1,    -1,    20,    21,    22,    23,    24,    -1,
      26,    27,   492,    -1,   621,    31,    32,   497,    -1,    -1,
      36,    37,    38,    -1,    -1,    41,    42,    -1,    44,    -1,
      46,    -1,    -1,   157,    -1,    51,    52,   517,    54,    -1,
      56,    57,    58,    59,    -1,    61,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    71,    -1,    -1,   621,    -1,
      -1,   125,    -1,    79,    -1,    81,    82,    83,    84,   160,
      -1,    87,    88,    89,    -1,     3,     4,     5,     6,    95,
      96,   172,    10,    11,    12,    16,    17,    18,    19,    20,
       3,     4,     5,     6,    -1,    -1,   160,    10,    11,    12,
      -1,    -1,   582,    16,    17,    18,    19,    20,   172,     3,
       4,     5,     6,    -1,   130,    -1,    10,    11,    12,    -1,
      -1,   137,    -1,   160,    -1,   141,   142,    -1,   144,   123,
     124,     1,    -1,    -1,    -1,   172,   130,   131,   132,     1,
      -1,     3,     4,     5,     6,    15,   162,     9,    10,    11,
      12,    -1,    22,    23,    16,    17,    18,    19,    20,   175,
      22,    23,    -1,   179,     1,   181,   182,   123,   124,    -1,
     186,   123,   124,    -1,   130,   131,    -1,    -1,   130,   131,
      -1,   197,    -1,   199,   200,    22,    23,    -1,   204,    -1,
      -1,   207,    -1,   209,    -1,    -1,   152,    -1,   214,   215,
     152,    -1,   218,    -1,    -1,   221,   119,   223,   224,    -1,
     226,   227,    -1,   229,    -1,   122,   232,   124,    -1,   235,
      -1,   237,   238,    -1,   240,   153,   242,    -1,   244,    -1,
     246,    -1,   248,    -1,    -1,   251,   143,   144,   145,   167,
     256,   257,    -1,    -1,    -1,   261,    -1,   160,   264,   265,
      -1,   267,   268,    -1,   270,   125,    -1,    -1,    -1,   153,
      -1,   174,    -1,    -1,    -1,   281,    -1,    -1,   284,    -1,
     286,    -1,    -1,   289,   290,   291,     3,     4,     5,     6,
      -1,    -1,    -1,    10,    11,    12,    -1,    -1,   125,    16,
      17,    18,    19,    20,    -1,   157,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   319,    -1,   321,   168,   169,   170,   171,
      -1,   442,    -1,    -1,    -1,    -1,   447,    -1,    -1,    -1,
     451,    -1,   338,   339,    -1,   456,   457,    -1,    -1,     1,
      -1,     3,     4,     5,     6,    -1,    -1,     9,    10,    11,
      12,    -1,    -1,    -1,    16,    17,    18,    19,    20,    -1,
      22,    23,    -1,    -1,     1,   371,     3,     4,     5,     6,
     376,   377,    -1,    10,    11,    12,    11,    12,    -1,    16,
      17,    18,    19,    20,    -1,    22,    23,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    -1,    -1,   403,    10,    11,
      12,    -1,    37,    38,    16,    17,    18,    19,    20,   415,
       1,    -1,   418,     4,   420,   421,   422,   423,    -1,    10,
      11,    12,   543,    -1,    -1,   546,   547,   433,   549,   550,
     551,    22,    23,     3,     4,     5,     6,    -1,    -1,    -1,
      10,    11,    12,   160,    79,    80,    -1,    82,    -1,    84,
      -1,   168,   169,   170,   171,   172,    -1,    -1,    -1,    -1,
      -1,   467,    -1,   469,    -1,    -1,   472,    -1,   474,    -1,
     476,   477,   478,    -1,    -1,   481,    -1,    -1,    -1,    -1,
      -1,   487,   488,    -1,    -1,   491,    -1,   493,   609,   495,
     496,    -1,    -1,    -1,   500,   157,    -1,    -1,   504,    -1,
     162,   507,    -1,    -1,   510,   511,   512,   513,   514,   515,
      -1,    -1,   518,    -1,   520,   521,    -1,    -1,    -1,    -1,
     157,    -1,   528,   529,   530,   531,   532,   162,    -1,    -1,
      -1,   166,   167,   168,    -1,    -1,    -1,   172,   173,    -1,
      -1,   176,    -1,    -1,    -1,   157,    -1,    -1,    -1,   184,
      -1,    -1,   122,   188,    -1,   125,   168,   169,   170,   171,
       1,    -1,    -1,   198,   134,    -1,   136,    -1,    -1,    -1,
     576,   206,    -1,    -1,    -1,    16,    17,    18,    19,    20,
      -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   226,    -1,   228,    -1,   230,   231,     1,   233,     3,
       4,     5,     6,    -1,    -1,     9,    10,    11,    12,    -1,
      14,    -1,    16,    17,    18,    19,    20,    -1,    22,    23,
       3,     4,     5,     6,    -1,    -1,   261,    10,    11,    12,
      -1,    -1,    -1,    16,    17,    18,    19,    20,     7,    -1,
       3,     4,     5,     6,    13,   280,     9,    10,    11,    12,
      -1,    -1,    -1,    22,   289,   290,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    45,    46,    47,    48,
      49,    50,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,    -1,   114,   115,   116,   117,   118,
      -1,    -1,    -1,   157,     3,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    12,    -1,    -1,    -1,     1,   403,     3,
       4,     5,     6,    -1,   157,     9,    10,    11,    12,    -1,
      -1,    -1,    16,    17,    18,    19,    20,   156,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   164,   165,    -1,    -1,    -1,
       1,    -1,     3,     4,     5,     6,    -1,    -1,     7,    10,
      11,    12,    -1,    -1,    13,    16,    17,    18,    19,    20,
      -1,    22,    23,    -1,    -1,    -1,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    45,    46,    47,    48,
      49,    50,   487,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,    -1,   114,   115,   116,   117,   118,
      -1,    -1,    -1,   157,   125,     1,    -1,     3,     4,     5,
       6,    -1,    -1,     9,    10,    11,    12,    -1,    -1,    -1,
      16,    17,    18,    19,    20,     3,     4,     5,     6,    -1,
      -1,    -1,    10,    11,    12,    -1,   157,    -1,    -1,     1,
      -1,     3,     4,     5,     6,   164,   165,     9,    10,    11,
      12,    -1,    -1,    -1,    16,    17,    18,    19,    20,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    12,    -1,
      -1,    -1,    16,    17,    18,    19,    20,     3,     4,     5,
       6,    -1,    -1,     9,    10,    11,    12,    -1,    -1,    -1,
      16,    17,    18,    19,    20,     1,    -1,     3,     4,     5,
       6,    -1,    -1,    -1,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    22,    23,     3,     4,
       5,     6,    -1,    -1,    -1,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
      -1,    -1,    -1,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,   157,    -1,   141,   142,   143,   144,   145,   146,     1,
      -1,     3,     4,     5,     6,    -1,    -1,    -1,    10,    11,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    23,    -1,    -1,    -1,   157,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   157,   158,    -1,    -1,    -1,    -1,   125,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   157,    -1,    -1,   119,    -1,   121,   122,    -1,    -1,
     125,    -1,   127,    -1,   129,    -1,    -1,   153,    -1,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   123,   124,    -1,    -1,
      -1,    -1,    -1,   130,   131,   132,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   125
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    13,    22,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    45,    46,    47,    48,    49,    50,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   114,
     115,   116,   117,   118,   156,   164,   165,   177,   178,   180,
     181,   182,   183,   184,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   226,     3,     4,     5,     6,    10,    11,
      12,    16,    17,    18,    19,    20,   160,   172,   201,   210,
     213,   221,   223,   224,     1,    22,    23,   166,   179,     1,
     154,   197,   166,   179,   166,   179,   179,   213,   213,   125,
     179,   209,   179,   209,   197,   197,   197,     1,     4,    10,
      11,    12,   204,   222,     9,   157,   206,   208,   210,   211,
     212,   224,   206,   206,   179,   208,   210,   179,   201,   202,
     203,   210,   162,   179,   162,   179,   205,   206,   208,    14,
     179,   199,   200,   158,   179,   200,   179,   208,   206,   197,
     197,   179,     1,   179,   204,   204,   204,   208,   179,   205,
     179,   209,   179,   209,   213,   210,   155,   179,   195,   179,
     200,   195,   179,   195,   158,   179,   210,   197,   210,   197,
     210,   208,   157,   210,   179,   210,   179,   210,   197,   179,
     197,   179,   205,   179,   205,   179,   205,   179,   205,   208,
     179,   195,   197,   197,   179,   179,   205,   159,   179,   179,
     179,   197,   179,   155,   196,   153,   153,   197,   197,   197,
     213,   179,   209,   209,   179,   179,   209,   179,   179,   209,
     197,   196,     1,   179,   198,   213,   113,   179,   179,   197,
     197,   166,    21,   119,   121,   122,   125,   127,   129,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   224,   228,   179,   204,
     179,   204,     0,   180,    22,   213,   160,   168,   169,   170,
     171,   179,   179,   179,   179,   179,   213,   213,   213,   213,
       1,   198,     1,   198,   198,   179,   209,   209,   209,   209,
     209,   209,   179,   209,    21,   125,   179,   179,   179,   209,
     179,    14,   205,   200,   205,   179,   209,   179,   179,   179,
      15,     1,   209,   179,   185,   179,   213,   213,   179,   179,
     179,   205,   179,   179,   179,   179,   209,   179,   209,   179,
     209,   209,   179,   209,   179,   179,   179,   179,   179,   179,
     179,   179,   153,   217,   218,   224,   179,   198,   198,   179,
     179,   179,   209,   179,   179,   153,   179,   179,   213,   179,
     213,   213,   213,   213,   209,   179,   179,   179,   179,   209,
     179,   209,   179,   208,   141,   142,   143,   144,   145,   146,
     224,   224,   125,   123,   124,   130,   131,   152,   229,   230,
     122,   125,   134,   136,   224,   224,   125,   125,   125,   179,
     179,     1,   173,   213,   213,   213,   213,   207,   209,   208,
     179,   179,   207,     1,   206,     1,   207,   208,   213,   153,
     167,   219,   220,   224,   208,     9,   211,   217,   208,   224,
     203,   205,    15,   214,   205,   214,   208,   119,   174,   201,
     215,   216,   224,   179,   153,   225,   226,   227,   179,   179,
     214,   158,   197,   197,   157,   157,   179,   209,   207,     1,
     206,   213,   179,   179,   179,   179,   179,   179,   205,   213,
     224,   224,    24,   179,   120,   120,   120,   120,   120,   120,
     120,   125,   229,   152,   229,   151,   125,   152,   229,   125,
     125,   125,   128,   229,   229,   123,   124,   131,   132,   224,
     230,   179,   208,   179,   179,   179,   179,   179,   179,   179,
     220,   179,   179,   179,   215,   179,   214,   179,   179,   215,
     158,   208,   161,   179,   179,   126,   126,   179,   179,   179,
     179,   179,   179,   179,   218,   179,   179,   179,   179,   179,
     179,   179,   179,   125,   123,   131,   229,   151,   229,   152,
     229,   128,   151,   229,   229,   132,   229,   125,   179,     1,
     120,   175,     1,   215,   226,   226,   122,   124,   143,   144,
     145,   120,   120,   128,   229,   128,   128,   151,   128,   128,
     128,   128,   124,   208,   125,   128,   128,   124
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   176,   177,   177,   177,   178,   178,   179,   179,   179,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   182,   182,
     182,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   185,   184,   184,   184,   184,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   192,   192,   192,   193,
     193,   194,   195,   196,   196,   197,   197,   198,   198,   199,
     199,   200,   200,   201,   201,   202,   202,   203,   204,   204,
     205,   205,   206,   206,   206,   207,   207,   208,   208,   208,
     209,   209,   210,   210,   210,   210,   210,   211,   212,   213,
     213,   213,   213,   213,   213,   213,   214,   214,   215,   215,
     215,   215,   215,   216,   216,   216,   216,   217,   217,   218,
     218,   219,   219,   220,   220,   220,   221,   221,   222,   222,
     222,   222,   223,   223,   223,   224,   224,   224,   224,   224,
     225,   225,   225,   226,   227,   227,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   229,   229,
     229,   229,   230
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     3,     5,     3,     2,     2,
       3,     2,     3,     2,     4,     2,     3,     3,     2,     4,
       2,     4,     2,     4,     2,     4,     2,     1,     2,     3,
       3,     5,     3,     5,     3,     5,     3,     5,     3,     2,
       3,     2,     4,     5,     0,     5,     3,     3,     2,     5,
       5,     5,     5,     5,     3,     2,     3,     2,     3,     2,
       3,     2,     3,     2,     2,     2,     4,     5,     5,     5,
       2,     6,     3,     2,     5,     2,     5,     2,     3,     2,
       3,     2,     3,     5,     3,     2,     5,     5,     4,     3,
       2,     3,     2,     3,     2,     3,     3,     2,     3,     2,
       2,     2,     3,     3,     3,     2,     3,     3,     3,     3,
       2,     3,     2,     3,     5,     3,     4,     3,     3,     2,
       4,     4,     2,     3,     3,     2,     5,     5,     5,     5,
       3,     4,     5,     4,     5,     4,     5,     5,     2,     3,
       4,     3,     3,     5,     3,     5,     3,     2,     3,     4,
       2,     2,     1,     1,     0,     1,     1,     1,     1,     2,
       1,     1,     0,     1,     2,     3,     1,     3,     1,     1,
       1,     1,     3,     1,     3,     2,     0,     1,     3,     1,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     1,     2,     0,     3,     3,
       3,     3,     1,     1,     1,     4,     2,     3,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     2,     2,     1,     1,     2,     1,     3,     3,
       3,     3,     3,     5,     7,     5,     3,     3,     3,     3,
       3,     3,     5,     5,     5,     5,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     3,     4,     3,
       4,     2,     3,     3,     3,     3,     5,     5,     6,     5,
       6,     4,     5,     5,     5,     5,     3,     5,     1,     1,
       1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
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
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
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

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
        case 2:
#line 199 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = 0; }
#line 2409 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 3:
#line 200 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = 0; }
#line 2415 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 4:
#line 201 "mon_parse.y" /* yacc.c:1652  */
    { new_cmd = 1; asm_mode = 0;  (yyval.i) = 0; }
#line 2421 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 9:
#line 210 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_END_CMD; }
#line 2427 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 22:
#line 225 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_BAD_CMD; }
#line 2433 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 23:
#line 229 "mon_parse.y" /* yacc.c:1652  */
    { mon_bank(e_default_space, NULL); }
#line 2439 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 24:
#line 231 "mon_parse.y" /* yacc.c:1652  */
    { mon_bank((yyvsp[-1].i), NULL); }
#line 2445 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 25:
#line 233 "mon_parse.y" /* yacc.c:1652  */
    { mon_bank(e_default_space, (yyvsp[-1].str)); }
#line 2451 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 26:
#line 235 "mon_parse.y" /* yacc.c:1652  */
    { mon_bank((yyvsp[-3].i), (yyvsp[-1].str)); }
#line 2457 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 27:
#line 237 "mon_parse.y" /* yacc.c:1652  */
    { mon_jump((yyvsp[-1].a)); }
#line 2463 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 28:
#line 239 "mon_parse.y" /* yacc.c:1652  */
    { mon_go(); }
#line 2469 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 29:
#line 241 "mon_parse.y" /* yacc.c:1652  */
    { mon_display_io_regs(0); }
#line 2475 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 30:
#line 243 "mon_parse.y" /* yacc.c:1652  */
    { mon_display_io_regs((yyvsp[-1].a)); }
#line 2481 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 31:
#line 245 "mon_parse.y" /* yacc.c:1652  */
    { monitor_cpu_type_set(""); }
#line 2487 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 32:
#line 247 "mon_parse.y" /* yacc.c:1652  */
    { monitor_cpu_type_set((yyvsp[-1].str)); }
#line 2493 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 33:
#line 249 "mon_parse.y" /* yacc.c:1652  */
    { mon_cpuhistory(-1); }
#line 2499 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 34:
#line 251 "mon_parse.y" /* yacc.c:1652  */
    { mon_cpuhistory((yyvsp[-1].i)); }
#line 2505 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 35:
#line 253 "mon_parse.y" /* yacc.c:1652  */
    { mon_instruction_return(); }
#line 2511 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 36:
#line 255 "mon_parse.y" /* yacc.c:1652  */
    { machine_write_snapshot((yyvsp[-1].str),0,0,0); /* FIXME */ }
#line 2517 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 37:
#line 257 "mon_parse.y" /* yacc.c:1652  */
    { machine_read_snapshot((yyvsp[-1].str), 0); }
#line 2523 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 38:
#line 259 "mon_parse.y" /* yacc.c:1652  */
    { mon_instructions_step(-1); }
#line 2529 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 39:
#line 261 "mon_parse.y" /* yacc.c:1652  */
    { mon_instructions_step((yyvsp[-1].i)); }
#line 2535 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 40:
#line 263 "mon_parse.y" /* yacc.c:1652  */
    { mon_instructions_next(-1); }
#line 2541 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 41:
#line 265 "mon_parse.y" /* yacc.c:1652  */
    { mon_instructions_next((yyvsp[-1].i)); }
#line 2547 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 42:
#line 267 "mon_parse.y" /* yacc.c:1652  */
    { mon_stack_up(-1); }
#line 2553 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 43:
#line 269 "mon_parse.y" /* yacc.c:1652  */
    { mon_stack_up((yyvsp[-1].i)); }
#line 2559 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 44:
#line 271 "mon_parse.y" /* yacc.c:1652  */
    { mon_stack_down(-1); }
#line 2565 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 45:
#line 273 "mon_parse.y" /* yacc.c:1652  */
    { mon_stack_down((yyvsp[-1].i)); }
#line 2571 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 46:
#line 275 "mon_parse.y" /* yacc.c:1652  */
    { mon_display_screen(); }
#line 2577 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 48:
#line 280 "mon_parse.y" /* yacc.c:1652  */
    { (monitor_cpu_for_memspace[default_memspace]->mon_register_print)(default_memspace); }
#line 2583 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 49:
#line 282 "mon_parse.y" /* yacc.c:1652  */
    { (monitor_cpu_for_memspace[(yyvsp[-1].i)]->mon_register_print)((yyvsp[-1].i)); }
#line 2589 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 51:
#line 287 "mon_parse.y" /* yacc.c:1652  */
    {
                        /* What about the memspace? */
                        mon_playback_init((yyvsp[-1].str));
                    }
#line 2598 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 52:
#line 292 "mon_parse.y" /* yacc.c:1652  */
    {
                        /* What about the memspace? */
                        mon_playback_init((yyvsp[-1].str));
                    }
#line 2607 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 53:
#line 297 "mon_parse.y" /* yacc.c:1652  */
    { mon_save_symbols((yyvsp[-3].i), (yyvsp[-1].str)); }
#line 2613 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 54:
#line 299 "mon_parse.y" /* yacc.c:1652  */
    { mon_save_symbols(e_default_space, (yyvsp[-1].str)); }
#line 2619 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 55:
#line 301 "mon_parse.y" /* yacc.c:1652  */
    { mon_add_name_to_symbol_table((yyvsp[-3].a), (yyvsp[-1].str)); }
#line 2625 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 56:
#line 303 "mon_parse.y" /* yacc.c:1652  */
    { mon_remove_name_from_symbol_table(e_default_space, (yyvsp[-1].str)); }
#line 2631 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 57:
#line 305 "mon_parse.y" /* yacc.c:1652  */
    { mon_remove_name_from_symbol_table((yyvsp[-3].i), (yyvsp[-1].str)); }
#line 2637 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 58:
#line 307 "mon_parse.y" /* yacc.c:1652  */
    { mon_print_symbol_table((yyvsp[-1].i)); }
#line 2643 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 59:
#line 309 "mon_parse.y" /* yacc.c:1652  */
    { mon_print_symbol_table(e_default_space); }
#line 2649 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 60:
#line 311 "mon_parse.y" /* yacc.c:1652  */
    { mon_clear_symbol_table((yyvsp[-1].i)); }
#line 2655 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 61:
#line 313 "mon_parse.y" /* yacc.c:1652  */
    { mon_clear_symbol_table(e_default_space); }
#line 2661 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 62:
#line 315 "mon_parse.y" /* yacc.c:1652  */
    {
                        mon_add_name_to_symbol_table((yyvsp[-1].a), mon_prepend_dot_to_name((yyvsp[-3].str)));
                    }
#line 2669 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 63:
#line 319 "mon_parse.y" /* yacc.c:1652  */
    {
                        mon_add_name_to_symbol_table((yyvsp[-2].a), mon_prepend_dot_to_name((yyvsp[-4].str)));
                    }
#line 2677 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 64:
#line 325 "mon_parse.y" /* yacc.c:1652  */
    { mon_start_assemble_mode((yyvsp[0].a), NULL); }
#line 2683 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 65:
#line 326 "mon_parse.y" /* yacc.c:1652  */
    { }
#line 2689 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 66:
#line 328 "mon_parse.y" /* yacc.c:1652  */
    { mon_start_assemble_mode((yyvsp[-1].a), NULL); }
#line 2695 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 67:
#line 330 "mon_parse.y" /* yacc.c:1652  */
    { mon_disassemble_lines((yyvsp[-1].range)[0], (yyvsp[-1].range)[1]); }
#line 2701 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 68:
#line 332 "mon_parse.y" /* yacc.c:1652  */
    { mon_disassemble_lines(BAD_ADDR, BAD_ADDR); }
#line 2707 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 69:
#line 336 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_move((yyvsp[-3].range)[0], (yyvsp[-3].range)[1], (yyvsp[-1].a)); }
#line 2713 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 70:
#line 338 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_compare((yyvsp[-3].range)[0], (yyvsp[-3].range)[1], (yyvsp[-1].a)); }
#line 2719 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 71:
#line 340 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_fill((yyvsp[-3].range)[0], (yyvsp[-3].range)[1],(unsigned char *)(yyvsp[-1].str)); }
#line 2725 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 72:
#line 342 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_hunt((yyvsp[-3].range)[0], (yyvsp[-3].range)[1],(unsigned char *)(yyvsp[-1].str)); }
#line 2731 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 73:
#line 344 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display((yyvsp[-3].rt), (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], DF_PETSCII); }
#line 2737 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 74:
#line 346 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display(default_radix, (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], DF_PETSCII); }
#line 2743 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 75:
#line 348 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display(default_radix, BAD_ADDR, BAD_ADDR, DF_PETSCII); }
#line 2749 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 76:
#line 350 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display_data((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], 8, 8); }
#line 2755 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 77:
#line 352 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display_data(BAD_ADDR, BAD_ADDR, 8, 8); }
#line 2761 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 78:
#line 354 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display_data((yyvsp[-1].range)[0], (yyvsp[-1].range)[1], 24, 21); }
#line 2767 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 79:
#line 356 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display_data(BAD_ADDR, BAD_ADDR, 24, 21); }
#line 2773 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 80:
#line 358 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display(0, (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], DF_PETSCII); }
#line 2779 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 81:
#line 360 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display(0, BAD_ADDR, BAD_ADDR, DF_PETSCII); }
#line 2785 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 82:
#line 362 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display(0, (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], DF_SCREEN_CODE); }
#line 2791 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 83:
#line 364 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_display(0, BAD_ADDR, BAD_ADDR, DF_SCREEN_CODE); }
#line 2797 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 84:
#line 366 "mon_parse.y" /* yacc.c:1652  */
    { mon_memmap_zap(); }
#line 2803 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 85:
#line 368 "mon_parse.y" /* yacc.c:1652  */
    { mon_memmap_show(-1,BAD_ADDR,BAD_ADDR); }
#line 2809 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 86:
#line 370 "mon_parse.y" /* yacc.c:1652  */
    { mon_memmap_show((yyvsp[-1].i),BAD_ADDR,BAD_ADDR); }
#line 2815 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 87:
#line 372 "mon_parse.y" /* yacc.c:1652  */
    { mon_memmap_show((yyvsp[-2].i),(yyvsp[-1].range)[0],(yyvsp[-1].range)[1]); }
#line 2821 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 88:
#line 374 "mon_parse.y" /* yacc.c:1652  */
    { mon_memmap_save((yyvsp[-3].str),(yyvsp[-1].i)); }
#line 2827 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 89:
#line 378 "mon_parse.y" /* yacc.c:1652  */
    {
                      if ((yyvsp[-3].i)) {
                          temp = mon_breakpoint_add_checkpoint(0, (yyvsp[-2].range)[0], (yyvsp[-2].range)[1], TRUE, (yyvsp[-3].i), FALSE);
                      } else {
                          temp = mon_breakpoint_add_checkpoint(0, (yyvsp[-2].range)[0], (yyvsp[-2].range)[1], TRUE, e_exec, FALSE);
                      }
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                  }
#line 2840 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 90:
#line 387 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_print_checkpoints(); }
#line 2846 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 91:
#line 389 "mon_parse.y" /* yacc.c:1652  */
    {
                      if(mon_interfaces[1]->mem_bank_seen_by_cpu == NULL) {
                          mon_out("bbreak is not supported on this machine");
                      } else {
                        int newbank;
                        newbank = mon_interfaces[1]->mem_bank_from_name((yyvsp[-4].str));
                        if (newbank < 0) {
                        mon_out("Unknown bank name `%s'\n", (yyvsp[-4].str));
                        } else {
                          if ((yyvsp[-3].i)) {
                              temp = mon_breakpoint_add_checkpoint(newbank, (yyvsp[-2].range)[0], (yyvsp[-2].range)[1], TRUE, (yyvsp[-3].i), FALSE);
                          } else {
                              temp = mon_breakpoint_add_checkpoint(newbank, (yyvsp[-2].range)[0], (yyvsp[-2].range)[1], TRUE, e_exec, FALSE);
                          }
                          mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                        }
                      }
                }
#line 2869 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 92:
#line 408 "mon_parse.y" /* yacc.c:1652  */
    {
                      mon_breakpoint_add_checkpoint(0, (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], TRUE, e_exec, TRUE);
                  }
#line 2877 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 93:
#line 412 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_print_checkpoints(); }
#line 2883 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 94:
#line 415 "mon_parse.y" /* yacc.c:1652  */
    {
                      if ((yyvsp[-3].i)) {
                          temp = mon_breakpoint_add_checkpoint(0, (yyvsp[-2].range)[0], (yyvsp[-2].range)[1], TRUE, (yyvsp[-3].i), FALSE);
                      } else {
                          temp = mon_breakpoint_add_checkpoint(0, (yyvsp[-2].range)[0], (yyvsp[-2].range)[1], TRUE, e_load | e_store, FALSE);
                      }
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                  }
#line 2896 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 95:
#line 424 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_print_checkpoints(); }
#line 2902 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 96:
#line 427 "mon_parse.y" /* yacc.c:1652  */
    {
                      if ((yyvsp[-3].i)) {
                          temp = mon_breakpoint_add_checkpoint(0, (yyvsp[-2].range)[0], (yyvsp[-2].range)[1], FALSE, (yyvsp[-3].i), FALSE);
                      } else {
                          temp = mon_breakpoint_add_checkpoint(0, (yyvsp[-2].range)[0], (yyvsp[-2].range)[1], FALSE, e_exec | e_load | e_store, FALSE);
                      }
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[-1].cond_node));
                  }
#line 2915 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 97:
#line 436 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_print_checkpoints(); }
#line 2921 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 98:
#line 441 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_switch_checkpoint(e_ON, (yyvsp[-1].i)); }
#line 2927 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 99:
#line 443 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_switch_checkpoint(e_ON, -1); }
#line 2933 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 100:
#line 445 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_switch_checkpoint(e_OFF, (yyvsp[-1].i)); }
#line 2939 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 101:
#line 447 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_switch_checkpoint(e_OFF, -1); }
#line 2945 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 102:
#line 449 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_set_ignore_count((yyvsp[-1].i), -1); }
#line 2951 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 103:
#line 451 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_set_ignore_count((yyvsp[-3].i), (yyvsp[-1].i)); }
#line 2957 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 104:
#line 453 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_delete_checkpoint((yyvsp[-1].i)); }
#line 2963 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 105:
#line 455 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_delete_checkpoint(-1); }
#line 2969 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 106:
#line 457 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_set_checkpoint_condition((yyvsp[-3].i), (yyvsp[-1].cond_node)); }
#line 2975 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 107:
#line 459 "mon_parse.y" /* yacc.c:1652  */
    { mon_breakpoint_set_checkpoint_command((yyvsp[-3].i), (yyvsp[-1].str)); }
#line 2981 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 108:
#line 461 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_STRING; }
#line 2987 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 109:
#line 465 "mon_parse.y" /* yacc.c:1652  */
    { sidefx = (((yyvsp[-1].action) == e_TOGGLE) ? (sidefx ^ 1) : (yyvsp[-1].action)); }
#line 2993 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 110:
#line 467 "mon_parse.y" /* yacc.c:1652  */
    {
                         mon_out("I/O side effects are %s\n",
                                   sidefx ? "enabled" : "disabled");
                     }
#line 3002 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 111:
#line 472 "mon_parse.y" /* yacc.c:1652  */
    { 
                         break_on_dummy_access = (((yyvsp[-1].action) == e_TOGGLE) ? (break_on_dummy_access ^ 1) : (yyvsp[-1].action)); 
                         /* FIXME: some day we might want to toggle the break-on-dummy-access 
                                   per MEMSPACE, for now its a global option */                         
                         mon_breakpoint_set_dummy_state(e_default_space, break_on_dummy_access);
                     }
#line 3013 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 112:
#line 479 "mon_parse.y" /* yacc.c:1652  */
    {
                         mon_out("Checkpoints will %strigger on dummy accesses.\n",
                                   break_on_dummy_access ? "" : "not ");
                         /* FIXME: some day we might want to toggle the break-on-dummy-access 
                                   per MEMSPACE, for now its a global option */                         
                         mon_breakpoint_set_dummy_state(e_default_space, break_on_dummy_access);
                     }
#line 3025 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 113:
#line 487 "mon_parse.y" /* yacc.c:1652  */
    { 
                        int logenabled;
                        resources_get_int("MonitorLogEnabled", &logenabled);
                        logenabled = (((yyvsp[-1].action) == e_TOGGLE) ? (logenabled ^ 1) : (yyvsp[-1].action));
                        resources_set_int("MonitorLogEnabled", logenabled);
                     }
#line 3036 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 114:
#line 494 "mon_parse.y" /* yacc.c:1652  */
    {
                         int logenabled;
                         const char *logfilename;
                         resources_get_int("MonitorLogEnabled", &logenabled);
                         resources_get_string("MonitorLogFileName", &logfilename);
                         if (logenabled) {
                            mon_out("Logging to '%s' is enabled.\n", logfilename);
                         } else {
                            mon_out("Logging is disabled.\n");
                         }
                     }
#line 3052 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 115:
#line 506 "mon_parse.y" /* yacc.c:1652  */
    { 
                        resources_set_string("MonitorLogFileName", (yyvsp[-1].str));
                     }
#line 3060 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 116:
#line 510 "mon_parse.y" /* yacc.c:1652  */
    { default_radix = (yyvsp[-1].rt); }
#line 3066 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 117:
#line 512 "mon_parse.y" /* yacc.c:1652  */
    {
                         const char *p;

                         if (default_radix == e_hexadecimal)
                             p = "Hexadecimal";
                         else if (default_radix == e_decimal)
                             p = "Decimal";
                         else if (default_radix == e_octal)
                             p = "Octal";
                         else if (default_radix == e_binary)
                             p = "Binary";
                         else
                             p = "Unknown";

                         mon_out("Default radix is %s\n", p);
                     }
#line 3087 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 118:
#line 530 "mon_parse.y" /* yacc.c:1652  */
    { monitor_change_device((yyvsp[-1].i)); }
#line 3093 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 119:
#line 532 "mon_parse.y" /* yacc.c:1652  */
    { mon_export(); }
#line 3099 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 120:
#line 534 "mon_parse.y" /* yacc.c:1652  */
    { mon_quit(); YYACCEPT; }
#line 3105 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 121:
#line 536 "mon_parse.y" /* yacc.c:1652  */
    { mon_exit(); YYACCEPT; }
#line 3111 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 122:
#line 538 "mon_parse.y" /* yacc.c:1652  */
    { mon_maincpu_toggle_trace((yyvsp[-1].action)); }
#line 3117 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 123:
#line 542 "mon_parse.y" /* yacc.c:1652  */
    { mon_drive_execute_disk_cmd((yyvsp[-1].str)); }
#line 3123 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 124:
#line 544 "mon_parse.y" /* yacc.c:1652  */
    { mon_out("\t%d\n",(yyvsp[-1].i)); }
#line 3129 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 125:
#line 546 "mon_parse.y" /* yacc.c:1652  */
    { mon_command_print_help(NULL); }
#line 3135 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 126:
#line 548 "mon_parse.y" /* yacc.c:1652  */
    { mon_command_print_help((yyvsp[-1].str)); }
#line 3141 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 127:
#line 550 "mon_parse.y" /* yacc.c:1652  */
    { mon_print_convert((yyvsp[-1].i)); }
#line 3147 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 128:
#line 552 "mon_parse.y" /* yacc.c:1652  */
    { mon_change_dir((yyvsp[-1].str)); }
#line 3153 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 129:
#line 554 "mon_parse.y" /* yacc.c:1652  */
    { mon_keyboard_feed((yyvsp[-1].str)); }
#line 3159 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 130:
#line 556 "mon_parse.y" /* yacc.c:1652  */
    { mon_backtrace(); }
#line 3165 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 131:
#line 558 "mon_parse.y" /* yacc.c:1652  */
    { mon_show_dir((yyvsp[-1].str)); }
#line 3171 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 132:
#line 560 "mon_parse.y" /* yacc.c:1652  */
    { mon_show_pwd(); }
#line 3177 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 133:
#line 562 "mon_parse.y" /* yacc.c:1652  */
    { mon_screenshot_save((yyvsp[-1].str),-1); }
#line 3183 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 134:
#line 564 "mon_parse.y" /* yacc.c:1652  */
    { mon_screenshot_save((yyvsp[-3].str),(yyvsp[-1].i)); }
#line 3189 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 135:
#line 566 "mon_parse.y" /* yacc.c:1652  */
    { mon_resource_get((yyvsp[-1].str)); }
#line 3195 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 136:
#line 568 "mon_parse.y" /* yacc.c:1652  */
    { mon_resource_set((yyvsp[-2].str),(yyvsp[-1].str)); }
#line 3201 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 137:
#line 570 "mon_parse.y" /* yacc.c:1652  */
    { resources_load((yyvsp[-1].str)); }
#line 3207 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 138:
#line 572 "mon_parse.y" /* yacc.c:1652  */
    { resources_save((yyvsp[-1].str)); }
#line 3213 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 139:
#line 574 "mon_parse.y" /* yacc.c:1652  */
    { mon_reset_machine(-1); }
#line 3219 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 140:
#line 576 "mon_parse.y" /* yacc.c:1652  */
    { mon_reset_machine((yyvsp[-1].i)); }
#line 3225 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 141:
#line 578 "mon_parse.y" /* yacc.c:1652  */
    { mon_tape_ctrl((yyvsp[-1].i)); }
#line 3231 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 142:
#line 580 "mon_parse.y" /* yacc.c:1652  */
    { mon_cart_freeze(); }
#line 3237 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 143:
#line 582 "mon_parse.y" /* yacc.c:1652  */
    { }
#line 3243 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 144:
#line 584 "mon_parse.y" /* yacc.c:1652  */
    { mon_stopwatch_reset(); }
#line 3249 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 145:
#line 586 "mon_parse.y" /* yacc.c:1652  */
    { mon_stopwatch_show("Stopwatch: ", "\n"); }
#line 3255 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 146:
#line 590 "mon_parse.y" /* yacc.c:1652  */
    { mon_file_load((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].a), false, false); }
#line 3261 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 147:
#line 592 "mon_parse.y" /* yacc.c:1652  */
    { mon_file_load((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].a), true, false); }
#line 3267 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 148:
#line 594 "mon_parse.y" /* yacc.c:1652  */
    { mon_file_load((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].a), false, true); }
#line 3273 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 149:
#line 596 "mon_parse.y" /* yacc.c:1652  */
    { mon_file_save((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], FALSE); }
#line 3279 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 150:
#line 598 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_DEVICE_NUM; }
#line 3285 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 151:
#line 600 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_ADDRESS; }
#line 3291 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 152:
#line 602 "mon_parse.y" /* yacc.c:1652  */
    { mon_file_save((yyvsp[-3].str), (yyvsp[-2].i), (yyvsp[-1].range)[0], (yyvsp[-1].range)[1], TRUE); }
#line 3297 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 153:
#line 604 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_ADDRESS; }
#line 3303 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 154:
#line 606 "mon_parse.y" /* yacc.c:1652  */
    { mon_file_verify((yyvsp[-3].str),(yyvsp[-2].i),(yyvsp[-1].a)); }
#line 3309 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 155:
#line 608 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_ADDRESS; }
#line 3315 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 156:
#line 610 "mon_parse.y" /* yacc.c:1652  */
    { mon_drive_block_cmd(0,(yyvsp[-3].i),(yyvsp[-2].i),(yyvsp[-1].a)); }
#line 3321 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 157:
#line 612 "mon_parse.y" /* yacc.c:1652  */
    { mon_drive_block_cmd(1,(yyvsp[-3].i),(yyvsp[-2].i),(yyvsp[-1].a)); }
#line 3327 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 158:
#line 614 "mon_parse.y" /* yacc.c:1652  */
    { mon_drive_list(-1); }
#line 3333 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 159:
#line 616 "mon_parse.y" /* yacc.c:1652  */
    { mon_drive_list((yyvsp[-1].i)); }
#line 3339 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 160:
#line 618 "mon_parse.y" /* yacc.c:1652  */
    { mon_attach((yyvsp[-2].str),(yyvsp[-1].i)); }
#line 3345 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 161:
#line 620 "mon_parse.y" /* yacc.c:1652  */
    { mon_detach((yyvsp[-1].i)); }
#line 3351 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 162:
#line 622 "mon_parse.y" /* yacc.c:1652  */
    { mon_autostart((yyvsp[-1].str),0,1); }
#line 3357 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 163:
#line 624 "mon_parse.y" /* yacc.c:1652  */
    { mon_autostart((yyvsp[-3].str),(yyvsp[-1].i),1); }
#line 3363 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 164:
#line 626 "mon_parse.y" /* yacc.c:1652  */
    { mon_autostart((yyvsp[-1].str),0,0); }
#line 3369 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 165:
#line 628 "mon_parse.y" /* yacc.c:1652  */
    { mon_autostart((yyvsp[-3].str),(yyvsp[-1].i),0); }
#line 3375 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 166:
#line 632 "mon_parse.y" /* yacc.c:1652  */
    { mon_record_commands((yyvsp[-1].str)); }
#line 3381 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 167:
#line 634 "mon_parse.y" /* yacc.c:1652  */
    { mon_end_recording(); }
#line 3387 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 168:
#line 636 "mon_parse.y" /* yacc.c:1652  */
    { mon_playback_init((yyvsp[-1].str)); }
#line 3393 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 169:
#line 640 "mon_parse.y" /* yacc.c:1652  */
    { mon_memory_fill((yyvsp[-2].a), BAD_ADDR, (unsigned char *)(yyvsp[-1].str)); }
#line 3399 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 170:
#line 642 "mon_parse.y" /* yacc.c:1652  */
    { printf("Not yet.\n"); }
#line 3405 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 171:
#line 646 "mon_parse.y" /* yacc.c:1652  */
    { yydebug = 1; }
#line 3411 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 172:
#line 649 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.str) = (yyvsp[0].str); }
#line 3417 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 173:
#line 652 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.str) = (yyvsp[0].str); }
#line 3423 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 174:
#line 653 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.str) = NULL; }
#line 3429 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 176:
#line 657 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_FILENAME; }
#line 3435 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 178:
#line 661 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_DEVICE_NUM; }
#line 3441 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 179:
#line 664 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[-1].i) | (yyvsp[0].i); }
#line 3447 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 180:
#line 665 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3453 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 181:
#line 668 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3459 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 182:
#line 669 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = 0; }
#line 3465 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 183:
#line 672 "mon_parse.y" /* yacc.c:1652  */
    {
                                    if (!mon_register_valid(default_memspace, (yyvsp[0].reg))) {
                                        return ERR_INVALID_REGISTER;
                                    }
                                    (yyval.i) = new_reg(default_memspace, (yyvsp[0].reg));
                                }
#line 3476 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 184:
#line 678 "mon_parse.y" /* yacc.c:1652  */
    {
                                    if (!mon_register_valid((yyvsp[-1].i), (yyvsp[0].reg))) {
                                        return ERR_INVALID_REGISTER;
                                    }
                                    (yyval.i) = new_reg((yyvsp[-1].i), (yyvsp[0].reg));
                                }
#line 3487 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 187:
#line 691 "mon_parse.y" /* yacc.c:1652  */
    { (monitor_cpu_for_memspace[reg_memspace((yyvsp[-2].i))]->mon_register_set_val)(reg_memspace((yyvsp[-2].i)), reg_regid((yyvsp[-2].i)), (uint16_t) (yyvsp[0].i)); }
#line 3493 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 188:
#line 694 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3499 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 189:
#line 695 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_EXPECT_CHECKNUM; }
#line 3505 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 191:
#line 699 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.range)[0] = (yyvsp[0].a); (yyval.range)[1] = BAD_ADDR; }
#line 3511 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 192:
#line 702 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.range)[0] = (yyvsp[-2].a); (yyval.range)[1] = (yyvsp[0].a); }
#line 3517 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 193:
#line 704 "mon_parse.y" /* yacc.c:1652  */
    { if (resolve_range(e_default_space, (yyval.range), (yyvsp[0].str))) return ERR_ADDR_TOO_BIG; }
#line 3523 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 194:
#line 706 "mon_parse.y" /* yacc.c:1652  */
    { if (resolve_range((yyvsp[-2].i), (yyval.range), (yyvsp[0].str))) return ERR_ADDR_TOO_BIG; }
#line 3529 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 195:
#line 709 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.a) = (yyvsp[0].a); }
#line 3535 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 196:
#line 710 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.a) = BAD_ADDR; }
#line 3541 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 197:
#line 714 "mon_parse.y" /* yacc.c:1652  */
    {
             (yyval.a) = new_addr(e_default_space,(yyvsp[0].i));
             if (opt_asm) new_cmd = asm_mode = 1;
         }
#line 3550 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 198:
#line 719 "mon_parse.y" /* yacc.c:1652  */
    {
             (yyval.a) = new_addr((yyvsp[-2].i), (yyvsp[0].i));
             if (opt_asm) new_cmd = asm_mode = 1;
         }
#line 3559 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 199:
#line 724 "mon_parse.y" /* yacc.c:1652  */
    {
             temp = mon_symbol_table_lookup_addr(e_default_space, (yyvsp[0].str));
             if (temp >= 0)
                 (yyval.a) = new_addr(e_default_space, temp);
             else
                 return ERR_UNDEFINED_LABEL;
         }
#line 3571 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 202:
#line 737 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = e_comp_space; }
#line 3577 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 203:
#line 738 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = e_disk8_space; }
#line 3583 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 204:
#line 739 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = e_disk9_space; }
#line 3589 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 205:
#line 740 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = e_disk10_space; }
#line 3595 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 206:
#line 741 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = e_disk11_space; }
#line 3601 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 207:
#line 744 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); if (!CHECK_ADDR((yyvsp[0].i))) return ERR_ADDR_TOO_BIG; }
#line 3607 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 208:
#line 746 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3613 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 209:
#line 748 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[-2].i) + (yyvsp[0].i); }
#line 3619 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 210:
#line 749 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[-2].i) - (yyvsp[0].i); }
#line 3625 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 211:
#line 750 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[-2].i) * (yyvsp[0].i); }
#line 3631 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 212:
#line 751 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = ((yyvsp[0].i)) ? ((yyvsp[-2].i) / (yyvsp[0].i)) : 1; }
#line 3637 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 213:
#line 752 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[-1].i); }
#line 3643 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 214:
#line 753 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_MISSING_CLOSE_PAREN; }
#line 3649 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 215:
#line 754 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3655 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 216:
#line 757 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.cond_node) = (yyvsp[0].cond_node); }
#line 3661 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 217:
#line 758 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.cond_node) = 0; }
#line 3667 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 218:
#line 761 "mon_parse.y" /* yacc.c:1652  */
    {
               (yyval.cond_node) = new_cond; (yyval.cond_node)->is_parenthized = FALSE;
               (yyval.cond_node)->child1 = (yyvsp[-2].cond_node); (yyval.cond_node)->child2 = (yyvsp[0].cond_node); (yyval.cond_node)->operation = (yyvsp[-1].cond_op);
           }
#line 3676 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 219:
#line 766 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_INCOMPLETE_COND_OP; }
#line 3682 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 220:
#line 768 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.cond_node) = (yyvsp[-1].cond_node); (yyval.cond_node)->is_parenthized = TRUE; }
#line 3688 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 221:
#line 770 "mon_parse.y" /* yacc.c:1652  */
    { return ERR_MISSING_CLOSE_PAREN; }
#line 3694 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 222:
#line 772 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.cond_node) = (yyvsp[0].cond_node); }
#line 3700 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 223:
#line 775 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.cond_node) = new_cond;
                            (yyval.cond_node)->operation = e_INV;
                            (yyval.cond_node)->is_parenthized = FALSE;
                            (yyval.cond_node)->reg_num = (yyvsp[0].i); (yyval.cond_node)->is_reg = TRUE; (yyval.cond_node)->banknum=-1;
                            (yyval.cond_node)->child1 = NULL; (yyval.cond_node)->child2 = NULL;
                          }
#line 3711 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 224:
#line 781 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.cond_node) = new_cond;
                            (yyval.cond_node)->operation = e_INV;
                            (yyval.cond_node)->is_parenthized = FALSE;
                            (yyval.cond_node)->value = (yyvsp[0].i); (yyval.cond_node)->is_reg = FALSE; (yyval.cond_node)->banknum=-1;
                            (yyval.cond_node)->child1 = NULL; (yyval.cond_node)->child2 = NULL;
                          }
#line 3722 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 225:
#line 787 "mon_parse.y" /* yacc.c:1652  */
    {(yyval.cond_node)=new_cond;
                            (yyval.cond_node)->operation=e_INV;
                            (yyval.cond_node)->is_parenthized = FALSE;
                            (yyval.cond_node)->banknum=mon_banknum_from_bank(e_default_space,(yyvsp[-2].str)); (yyval.cond_node)->value = (yyvsp[0].a); (yyval.cond_node)->is_reg = FALSE;
                            (yyval.cond_node)->child1 = NULL; (yyval.cond_node)->child2 = NULL;  
                        }
#line 3733 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 226:
#line 793 "mon_parse.y" /* yacc.c:1652  */
    {(yyval.cond_node)=new_cond;
                          (yyval.cond_node)->operation=e_INV;
                          (yyval.cond_node)->is_parenthized = FALSE;
                          (yyval.cond_node)->banknum=0; (yyval.cond_node)->value = (yyvsp[0].a); (yyval.cond_node)->is_reg = FALSE;
                          (yyval.cond_node)->child1 = NULL; (yyval.cond_node)->child2 = NULL;  
                      }
#line 3744 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 229:
#line 805 "mon_parse.y" /* yacc.c:1652  */
    { mon_add_number_to_buffer((yyvsp[0].i)); }
#line 3750 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 230:
#line 806 "mon_parse.y" /* yacc.c:1652  */
    { mon_add_string_to_buffer((yyvsp[0].str)); }
#line 3756 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 233:
#line 813 "mon_parse.y" /* yacc.c:1652  */
    { mon_add_number_to_buffer((yyvsp[0].i)); }
#line 3762 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 234:
#line 814 "mon_parse.y" /* yacc.c:1652  */
    { mon_add_number_masked_to_buffer((yyvsp[0].i), 0x00); }
#line 3768 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 235:
#line 815 "mon_parse.y" /* yacc.c:1652  */
    { mon_add_string_to_buffer((yyvsp[0].str)); }
#line 3774 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 236:
#line 818 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3780 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 237:
#line 819 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (monitor_cpu_for_memspace[reg_memspace((yyvsp[0].i))]->mon_register_get_val)(reg_memspace((yyvsp[0].i)), reg_regid((yyvsp[0].i))); }
#line 3786 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 238:
#line 822 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3792 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 239:
#line 823 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = strtol((yyvsp[0].str), NULL, 10); }
#line 3798 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 240:
#line 824 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = strtol((yyvsp[0].str), NULL, 10); }
#line 3804 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 241:
#line 825 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = strtol((yyvsp[0].str), NULL, 10); }
#line 3810 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 242:
#line 828 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = resolve_datatype(B_NUMBER,(yyvsp[0].str)); }
#line 3816 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 243:
#line 829 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = resolve_datatype(O_NUMBER,(yyvsp[0].str)); }
#line 3822 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 244:
#line 830 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = resolve_datatype(D_NUMBER,(yyvsp[0].str)); }
#line 3828 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 245:
#line 833 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3834 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 246:
#line 834 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3840 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 247:
#line 835 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3846 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 248:
#line 836 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3852 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 249:
#line 837 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 3858 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 253:
#line 845 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = 0;
                                                if ((yyvsp[-1].str)) {
                                                    (monitor_cpu_for_memspace[default_memspace]->mon_assemble_instr)((yyvsp[-1].str), (yyvsp[0].mode));
                                                } else {
                                                    new_cmd = 1;
                                                    asm_mode = 0;
                                                }
                                                opt_asm = 0;
                                              }
#line 3872 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 255:
#line 856 "mon_parse.y" /* yacc.c:1652  */
    { asm_mode = 0; }
#line 3878 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 256:
#line 859 "mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[0].i) > 0xff) {
                          (yyval.mode).addr_mode = ASM_ADDR_MODE_IMMEDIATE_16;
                          (yyval.mode).param = (yyvsp[0].i);
                        } else {
                          (yyval.mode).addr_mode = ASM_ADDR_MODE_IMMEDIATE;
                          (yyval.mode).param = (yyvsp[0].i);
                        } }
#line 3890 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 257:
#line 866 "mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[0].i) >= 0x10000) {
               (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_LONG;
               (yyval.mode).param = (yyvsp[0].i);
             } else if ((yyvsp[0].i) < 0x100) {
               (yyval.mode).addr_mode = ASM_ADDR_MODE_ZERO_PAGE;
               (yyval.mode).param = (yyvsp[0].i);
             } else {
               (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE;
               (yyval.mode).param = (yyvsp[0].i);
             }
           }
#line 3906 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 258:
#line 877 "mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[-2].i) >= 0x10000) {
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_LONG_X;
                            (yyval.mode).param = (yyvsp[-2].i);
                          } else if ((yyvsp[-2].i) < 0x100) { 
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_ZERO_PAGE_X;
                            (yyval.mode).param = (yyvsp[-2].i);
                          } else {
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_X;
                            (yyval.mode).param = (yyvsp[-2].i);
                          }
                        }
#line 3922 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 259:
#line 888 "mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[-2].i) < 0x100) {
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_ZERO_PAGE_Y;
                            (yyval.mode).param = (yyvsp[-2].i);
                          } else {
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_Y;
                            (yyval.mode).param = (yyvsp[-2].i);
                          }
                        }
#line 3935 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 260:
#line 896 "mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[-2].i) < 0x100) {
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_STACK_RELATIVE;
                            (yyval.mode).param = (yyvsp[-2].i);
                          } else { /* 6809 */
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
                            if ((yyvsp[-2].i) >= -16 && (yyvsp[-2].i) < 16) {
                                (yyval.mode).addr_submode = (yyvsp[0].i) | ((yyvsp[-2].i) & 0x1F);
                            } else if ((yyvsp[-2].i) >= -128 && (yyvsp[-2].i) < 128) {
                                (yyval.mode).addr_submode = 0x80 | (yyvsp[0].i) | ASM_ADDR_MODE_INDEXED_OFF8;
                                (yyval.mode).param = (yyvsp[-2].i);
                            } else if ((yyvsp[-2].i) >= -32768 && (yyvsp[-2].i) < 32768) {
                                (yyval.mode).addr_submode = 0x80 | (yyvsp[0].i) | ASM_ADDR_MODE_INDEXED_OFF16;
                                (yyval.mode).param = (yyvsp[-2].i);
                            } else {
                                (yyval.mode).addr_mode = ASM_ADDR_MODE_ILLEGAL;
                                mon_out("offset too large even for 16 bits (signed)\n");
                            }
                          }
                        }
#line 3959 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 261:
#line 915 "mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[-2].i) < 0x100) {
                            (yyval.mode).addr_mode = ASM_ADDR_MODE_DOUBLE;
                            (yyval.mode).param = (yyvsp[0].i);
                            (yyval.mode).addr_submode = (yyvsp[-2].i);
                          }
                        }
#line 3970 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 262:
#line 921 "mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[-1].i) < 0x100) {
                               (yyval.mode).addr_mode = ASM_ADDR_MODE_INDIRECT;
                               (yyval.mode).param = (yyvsp[-1].i);
                             } else {
                               (yyval.mode).addr_mode = ASM_ADDR_MODE_ABS_INDIRECT;
                               (yyval.mode).param = (yyvsp[-1].i);
                             }
                           }
#line 3983 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 263:
#line 929 "mon_parse.y" /* yacc.c:1652  */
    { if ((yyvsp[-3].i) < 0x100) {
                                           (yyval.mode).addr_mode = ASM_ADDR_MODE_INDIRECT_X;
                                           (yyval.mode).param = (yyvsp[-3].i);
                                         } else {
                                           (yyval.mode).addr_mode = ASM_ADDR_MODE_ABS_INDIRECT_X;
                                           (yyval.mode).param = (yyvsp[-3].i);
                                         }
                                       }
#line 3996 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 264:
#line 938 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_STACK_RELATIVE_Y; (yyval.mode).param = (yyvsp[-5].i); }
#line 4002 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 265:
#line 940 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_INDIRECT_Y; (yyval.mode).param = (yyvsp[-3].i); }
#line 4008 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 266:
#line 941 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IND_BC; }
#line 4014 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 267:
#line 942 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IND_DE; }
#line 4020 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 268:
#line 943 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IND_HL; }
#line 4026 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 269:
#line 944 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IND_IX; }
#line 4032 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 270:
#line 945 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IND_IY; }
#line 4038 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 271:
#line 946 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IND_SP; }
#line 4044 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 272:
#line 948 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_A; (yyval.mode).param = (yyvsp[-3].i); }
#line 4050 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 273:
#line 950 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_HL; (yyval.mode).param = (yyvsp[-3].i); }
#line 4056 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 274:
#line 952 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_IX; (yyval.mode).param = (yyvsp[-3].i); }
#line 4062 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 275:
#line 954 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_ABSOLUTE_IY; (yyval.mode).param = (yyvsp[-3].i); }
#line 4068 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 276:
#line 955 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_IMPLIED; }
#line 4074 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 277:
#line 956 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_ACCUMULATOR; }
#line 4080 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 278:
#line 957 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_B; }
#line 4086 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 279:
#line 958 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_C; }
#line 4092 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 280:
#line 959 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_D; }
#line 4098 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 281:
#line 960 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_E; }
#line 4104 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 282:
#line 961 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_H; }
#line 4110 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 283:
#line 962 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IXH; }
#line 4116 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 284:
#line 963 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IYH; }
#line 4122 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 285:
#line 964 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_L; }
#line 4128 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 286:
#line 965 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IXL; }
#line 4134 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 287:
#line 966 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IYL; }
#line 4140 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 288:
#line 967 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_AF; }
#line 4146 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 289:
#line 968 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_BC; }
#line 4152 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 290:
#line 969 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_DE; }
#line 4158 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 291:
#line 970 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_HL; }
#line 4164 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 292:
#line 971 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IX; }
#line 4170 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 293:
#line 972 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_IY; }
#line 4176 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 294:
#line 973 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_REG_SP; }
#line 4182 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 295:
#line 975 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.mode).addr_mode = ASM_ADDR_MODE_DIRECT; (yyval.mode).param = (yyvsp[0].i); }
#line 4188 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 296:
#line 976 "mon_parse.y" /* yacc.c:1652  */
    {    /* Clash with addr,x addr,y addr,s modes! */
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        if ((yyvsp[-2].i) >= -16 && (yyvsp[-2].i) < 16) {
            (yyval.mode).addr_submode = (3 << 5) | ((yyvsp[-2].i) & 0x1F);
        } else if ((yyvsp[-2].i) >= -128 && (yyvsp[-2].i) < 128) {
            (yyval.mode).addr_submode = 0x80 | (3 << 5) | ASM_ADDR_MODE_INDEXED_OFF8;
            (yyval.mode).param = (yyvsp[-2].i);
        } else if ((yyvsp[-2].i) >= -32768 && (yyvsp[-2].i) < 32768) {
            (yyval.mode).addr_submode = 0x80 | (3 << 5) | ASM_ADDR_MODE_INDEXED_OFF16;
            (yyval.mode).param = (yyvsp[-2].i);
        } else {
            (yyval.mode).addr_mode = ASM_ADDR_MODE_ILLEGAL;
            mon_out("offset too large even for 16 bits (signed)\n");
        }
    }
#line 4208 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 297:
#line 991 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_INC1;
        }
#line 4217 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 298:
#line 995 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-2].i) | ASM_ADDR_MODE_INDEXED_INC2;
        }
#line 4226 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 299:
#line 999 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[0].i) | ASM_ADDR_MODE_INDEXED_DEC1;
        }
#line 4235 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 300:
#line 1003 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[0].i) | ASM_ADDR_MODE_INDEXED_DEC2;
        }
#line 4244 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 301:
#line 1007 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[0].i) | ASM_ADDR_MODE_INDEXED_OFF0;
        }
#line 4253 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 302:
#line 1011 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_OFFB;
        }
#line 4262 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 303:
#line 1015 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_OFFA;
        }
#line 4271 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 304:
#line 1019 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_OFFD;
        }
#line 4280 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 305:
#line 1023 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).param = (yyvsp[-2].i);
        if ((yyvsp[-2].i) >= -128 && (yyvsp[-2].i) < 128) {
            (yyval.mode).addr_submode = ASM_ADDR_MODE_INDEXED_OFFPC8;
        } else if ((yyvsp[-2].i) >= -32768 && (yyvsp[-2].i) < 32768) {
            (yyval.mode).addr_submode = ASM_ADDR_MODE_INDEXED_OFFPC16;
        } else {
            (yyval.mode).addr_mode = ASM_ADDR_MODE_ILLEGAL;
            mon_out("offset too large even for 16 bits (signed)\n");
        }
    }
#line 4297 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 306:
#line 1035 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        if ((yyvsp[-3].i) >= -16 && (yyvsp[-3].i) < 16) {
            (yyval.mode).addr_submode = (yyvsp[-3].i) & 0x1F;
        } else if ((yyvsp[-4].i) >= -128 && (yyvsp[-4].i) < 128) {
            (yyval.mode).addr_submode = ASM_ADDR_MODE_INDEXED_OFF8;
            (yyval.mode).param = (yyvsp[-3].i);
        } else if ((yyvsp[-3].i) >= -32768 && (yyvsp[-3].i) < 32768) {
            (yyval.mode).addr_submode = ASM_ADDR_MODE_INDEXED_OFF16;
            (yyval.mode).param = (yyvsp[-3].i);
        } else {
            (yyval.mode).addr_mode = ASM_ADDR_MODE_ILLEGAL;
            mon_out("offset too large even for 16 bits (signed)\n");
        }
    }
#line 4317 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 307:
#line 1050 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-2].i) | ASM_ADDR_MODE_INDEXED_INC1;
        }
#line 4326 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 308:
#line 1054 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-3].i) | ASM_ADDR_MODE_INDEXED_INC2;
        }
#line 4335 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 309:
#line 1058 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_DEC1;
        }
#line 4344 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 310:
#line 1062 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_DEC2;
        }
#line 4353 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 311:
#line 1066 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-1].i) | ASM_ADDR_MODE_INDEXED_OFF0;
        }
#line 4362 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 312:
#line 1070 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-2].i) | ASM_ADDR_MODE_INDEXED_OFFB;
        }
#line 4371 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 313:
#line 1074 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-2].i) | ASM_ADDR_MODE_INDEXED_OFFA;
        }
#line 4380 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 314:
#line 1078 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | (yyvsp[-2].i) | ASM_ADDR_MODE_INDEXED_OFFD;
        }
#line 4389 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 315:
#line 1082 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).param = (yyvsp[-3].i);
        if ((yyvsp[-3].i) >= -128 && (yyvsp[-3].i) < 128) {
            (yyval.mode).addr_submode = ASM_ADDR_MODE_INDEXED_OFFPC8_IND;
        } else if ((yyvsp[-3].i) >= -32768 && (yyvsp[-3].i) < 32768) {
            (yyval.mode).addr_submode = ASM_ADDR_MODE_INDEXED_OFFPC16_IND;
        } else {
            (yyval.mode).addr_mode = ASM_ADDR_MODE_ILLEGAL;
            mon_out("offset too large even for 16 bits (signed)\n");
        }
    }
#line 4406 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 316:
#line 1094 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDEXED;
        (yyval.mode).addr_submode = 0x80 | ASM_ADDR_MODE_EXTENDED_INDIRECT;
        (yyval.mode).param = (yyvsp[-1].i);
        }
#line 4416 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 317:
#line 1099 "mon_parse.y" /* yacc.c:1652  */
    {
        (yyval.mode).addr_mode = ASM_ADDR_MODE_INDIRECT_LONG_Y;
        (yyval.mode).param = (yyvsp[-3].i);
        }
#line 4425 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 318:
#line 1107 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (0 << 5); printf("reg_x\n"); }
#line 4431 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 319:
#line 1108 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (1 << 5); printf("reg_y\n"); }
#line 4437 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 320:
#line 1109 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (yyvsp[0].i); }
#line 4443 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 321:
#line 1110 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (3 << 5); printf("reg_s\n"); }
#line 4449 "mon_parse.c" /* yacc.c:1652  */
    break;

  case 322:
#line 1114 "mon_parse.y" /* yacc.c:1652  */
    { (yyval.i) = (2 << 5); printf("reg_u\n"); }
#line 4455 "mon_parse.c" /* yacc.c:1652  */
    break;


#line 4459 "mon_parse.c" /* yacc.c:1652  */
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
#line 1118 "mon_parse.y" /* yacc.c:1918  */


int parse_and_execute_line(char *input)
{
   char *temp_buf;
   int i, rc;

   temp_buf = lib_malloc(strlen(input) + 3);
   strcpy(temp_buf,input);
   i = (int)strlen(input);
   temp_buf[i++] = '\n';
   temp_buf[i++] = '\0';
   temp_buf[i++] = '\0';

   make_buffer(temp_buf);
   mon_clear_buffer();
   if ( (rc =yyparse()) != 0) {
       mon_out("ERROR -- ");
       switch(rc) {
         case ERR_BAD_CMD:
           mon_out("Bad command:\n");
           break;
         case ERR_RANGE_BAD_START:
           mon_out("Bad first address in range:\n");
           break;
         case ERR_RANGE_BAD_END:
           mon_out("Bad second address in range:\n");
           break;
         case ERR_EXPECT_CHECKNUM:
           mon_out("Checkpoint number expected:\n");
           break;
         case ERR_EXPECT_END_CMD:
           mon_out("Unexpected token:\n");
           break;
         case ERR_MISSING_CLOSE_PAREN:
           mon_out("')' expected:\n");
           break;
         case ERR_INCOMPLETE_COND_OP:
           mon_out("Conditional operation missing an operand:\n");
           break;
         case ERR_EXPECT_FILENAME:
           mon_out("Expecting a filename:\n");
           break;
         case ERR_ADDR_TOO_BIG:
           mon_out("Address too large:\n");
           break;
         case ERR_IMM_TOO_BIG:
           mon_out("Immediate argument too large:\n");
           break;
         case ERR_EXPECT_STRING:
           mon_out("Expecting a string.\n");
           break;
         case ERR_UNDEFINED_LABEL:
           mon_out("Found an undefined label.\n");
           break;
         case ERR_EXPECT_DEVICE_NUM:
           mon_out("Expecting a device number.\n");
           break;
         case ERR_EXPECT_ADDRESS:
           mon_out("Expecting an address.\n");
           break;
         case ERR_INVALID_REGISTER:
           mon_out("Invalid register.\n");
           break;
         case ERR_ILLEGAL_INPUT:
         default:
           mon_out("Wrong syntax:\n");
       }
       mon_out("  %s\n", input);
       for (i = 0; i < last_len; i++)
           mon_out(" ");
       mon_out("  ^\n");
       asm_mode = 0;
       new_cmd = 1;
   }
   lib_free(temp_buf);
   free_buffer();

   return rc;
}

static int yyerror(char *s)
{
#if 0
   fprintf(stderr, "ERR:%s\n", s);
#endif
   return 0;
}

static int resolve_datatype(unsigned guess_type, const char *num)
{
   /* FIXME: Handle cases when default type is non-numerical */
   if (default_radix == e_hexadecimal) {
       return strtol(num, NULL, 16);
   }

   if ((guess_type == D_NUMBER) || (default_radix == e_decimal)) {
       return strtol(num, NULL, 10);
   }

   if ((guess_type == O_NUMBER) || (default_radix == e_octal)) {
       return strtol(num, NULL, 8);
   }

   return strtol(num, NULL, 2);
}

/*
 * Resolve a character sequence containing 8 hex digits like "08001000".
 * This could be a lazy version of "0800 1000". If the default radix is not
 * hexadecimal, we handle it like a ordinary number, in the latter case there
 * is only one number in the range.
 */
static int resolve_range(enum t_memspace memspace, MON_ADDR range[2],
                         const char *num)
{
    char start[5];
    char end[5];
    long sa;

    range[1] = BAD_ADDR;

    switch (default_radix)
    {
    case e_hexadecimal:
        /* checked twice, but as the code must have exactly 8 digits: */
        if (strlen(num) == 8) {
            memcpy(start, num, 4);
            start[4] = '\0';
            memcpy(end, num + 4, 4);
            end[4] = '\0';
            sa = strtol(start, NULL, 16);
            range[1] = new_addr(memspace, strtol(end, NULL, 16));
        }
        else
            sa = strtol(num, NULL, 16);
        break;

    case e_decimal:
       sa = strtol(num, NULL, 10);
       break;

    case e_octal:
       sa = strtol(num, NULL, 8);
       break;

    default:
       sa = strtol(num, NULL, 2);
    }

    if (!CHECK_ADDR(sa))
        return ERR_ADDR_TOO_BIG;

    range[0] = new_addr(memspace, sa);
    return 0;
}
