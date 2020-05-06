/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
#line 135 "mon_parse.y" /* yacc.c:1921  */

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

#line 405 "mon_parse.h" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MON_PARSE_H_INCLUDED  */
