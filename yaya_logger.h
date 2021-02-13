#ifndef YAYA_LOGGER_H_
#define YAYA_LOGGER_H_

#include "yaya_logger_func_build_fnc.h"
#include "yaya_logger_struct.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // DEFINE OPTION
#define LOGGER_LOGS LOGGER_TRUE  /*Включить логгер*/
#define LOGGER_HEAD LOGGER_TRUE  /*Включить заголовки*/
#define LOGGER_STYLE LOGGER_TRUE /*Включить стили*/
#define LOGGER_OUT LOGGER_TRUE   /*Включить вывод*/

#define LOGGER_AUTO_INIT LOGGER_TRUE /*Автоматическая Инициализация*/
#define LOGGER_AUTO_HEAD LOGGER_FALSE /*Автоматический вывод заголовка*/

#define HIDDEN_STR "..."

//#define LOGS_FORMAT  "LOGS ## $absnum%3. | $curnum%3. | $type%.7 | $name%.7 | $count%3. | $line%3. | $func%:15. | $message"
#define LOGS_FORMAT  "LOGS ## $line%3. -- $file%:15."

//#define HEAD_FORMAT "HEAD ## $message"
#define HEAD_FORMAT "HEAD ## $line%3."

#define TYPE_FILTER L_ALL
#define NAME_FILTER LL_ALL

#define LOGGER_OUT_BUFF_SIZE 1000
#define LOGGER_TMP_BUFF_SIZE 300
#define LOGGER_NUM_TOKEN_OR_AUTO 0 /*if 0, auto allocation*/

static logger logger_defines = {0};
#define LOGGER_LVG &logger_defines
// // END // DEFINE OPTION
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // MACRO FUNCTION

#define LOGGER_FLAG(x)       (uintmax_t)(1 << ((uintmax_t)(x)))
#define LOGGER_FLAG_ALL      (uintmax_t)(0b1111111111111111111111111111111111111111111111111111111111111111)
#define LOGGER_FLAG_NUL      (uintmax_t)(0)

#define LOGGER_BIT_GET(x, n) ((x) & (1 << (n)))
#define LOGGER_TRUE          (1 == 1)
#define LOGGER_FALSE         (!LOGGER_TRUE)

// // END // MACRO FUNCTION
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // FORMAT TOKEN

#define LFS_LEF 1
#define LFS_RIG 2
#define LFS_NUL 3

//typedef struct logger_token_specifiers { /*хранение спецификаторов*/
//  uintmax_t beg; /*начало спецификатора*/
//  uintmax_t end; /*конец спецификатора*/
//  uintmax_t lef; /*смещение слева*/
//  uintmax_t rig; /*смещение справа*/
//  uintmax_t lfs; /*сторона скрытия*/
//} logger_token_specifiers;

//typedef struct logger_token_mas {    /*хранение токенов*/
//  uintmax_t id;     /*тип токена*/
//  uintmax_t beg;    /*начало токена*/
//  uintmax_t end;    /*конец токена*/
//  uintmax_t beglog; /*начало токена вывода*/
//  uintmax_t endlog; /*конец токена вывода*/
//  logger_token_specifiers *spe;
//} logger_token_mas;

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct logger_token {      /*список токенов*/
        const uintmax_t id; /*идентификатор*/
        const char *name; /*текстовое представление ключей*/
        void (*func)(LOGGER_FUNC_PARAM); /*функция токена*/
} logger_token;

#define LOGGER_TOKEN_GENERATE_ENUM(TOKEN) LEF_##TOKEN

typedef enum {
    // SYS
    LOGGER_TOKEN_GENERATE_ENUM(TOK),
    LOGGER_TOKEN_GENERATE_ENUM(SPE),
    LOGGER_TOKEN_GENERATE_ENUM(SEP),
    LOGGER_TOKEN_GENERATE_ENUM(HID),
    LOGGER_TOKEN_GENERATE_ENUM(STR),

    // WORK
    //LOGGER_TOKEN_GENERATE_ENUM(line),
    //LOGGER_TOKEN_GENERATE_ENUM(),
    LEF_line,
    LEF_file,
    LEF_func,
    LEF_COUNT,
    LEF_TYPE,
    LEF_NAME,
    LEF_MESSAGE,
    LEF_CURNUM,
    LEF_ABSNUM,
    LEF_PROG,
    LEF_PROJ,
    LEF_PROJ_VERSION,
    LEF_COMPILERVERSION,

    // NOT WORK
    LEF_PROJ_PATH,
    LEF_VERSION,
    LEF_DATA_BUILD,
    LEF_TIME_BUILD,
    LEF_SEED,
    LEF_TIK,
    LEF_TIKSEC,
    LEF_TIK_RTOS,
    LEF_TIK_UNIX,
    LEF_TYPE_FILTER,
    LEF_NAME_FILTER,
    LEF_TYPE_NUM,
    LEF_NAME_NUM,
    LEF_TYPE_LIST,
    LEF_NAME_LIST,
    LEF_DATA,
    LEF_TIME,
    LEF_FULLPATH,
    LEF_SHORPATH,
    LEF_ALIGNL,
    LEF_ALIGGT,
    LEF_NUM_TOKEN_HEAD,
    LEF_NUM_TOKEN_LOGS,
    LEF_void,
    LEF_END
} logger_token_id;


#define LOGGER_TOKEN_GENERATE_ST(TOKEN)  { LEF_##TOKEN, #TOKEN, logger_func_##TOKEN }

static logger_token logger_token_list[LEF_END] = {
    {LEF_TOK, "$", NULL}, // - токен формата токена
    {LEF_SPE, "%", NULL}, // - токен формата вывода
    {LEF_SEP, ".", NULL}, // - токен формата вывода, разделитель
    {LEF_HID, ":", NULL}, // - токен формата вывода, скрыватель
    {LEF_STR, " ", logger_func_str}, // - токен формата текста

    LOGGER_TOKEN_GENERATE_ST(line), // - номер строки
    LOGGER_TOKEN_GENERATE_ST(file), // - файл
    LOGGER_TOKEN_GENERATE_ST(func), // - имя функции
    LOGGER_TOKEN_GENERATE_ST(void), // -
    LOGGER_TOKEN_GENERATE_ST(void), // -
    LOGGER_TOKEN_GENERATE_ST(void), // -
    LOGGER_TOKEN_GENERATE_ST(void), // -
    LOGGER_TOKEN_GENERATE_ST(void), // -
    LOGGER_TOKEN_GENERATE_ST(void), // -

    //    {LEF_COUNT, "count"}, // - номер сообщения, на основе __COUNTER__
    //    {LEF_TYPE, "type"},       // - имя типа сообщения
    //    {LEF_NAME, "name"},       // - имя названия сообщения
    //    {LEF_MESSAGE, "message"}, // - тело сообщения
    //    {LEF_CURNUM, "curnum"}, // - номер выведенного сообщения
    //    {LEF_ABSNUM, "absnum"}, // - номер сообщения без учета фильтрации
    //    {LEF_PROG, "prog"},            // - название программы
    //    {LEF_PROJ, "proj"},            // - название проекта
    //    {LEF_PROJ_VERSION, "version"}, // - версия программы

    //    {LEF_DATA, "data"},         // - дата сообщения
    //    {LEF_TIME, "time"},         // - время сообщения
    //    {LEF_PROJ_PATH, "path"},    // - расположение проекта
    //    {LEF_FULLPATH, "fullpath"}, // - полный путь к файлу, из которого сообщение
    //    {LEF_SHORPATH,
    //     "shorpath"}, // - короткий путь к файлу, из которого сообщение
    //    {LEF_VERSION, "version"},      // - версия программы
    //    {LEF_DATA_BUILD, "databuild"}, // - дата компиляции
    //    {LEF_TIME_BUILD, "timebuild"}, // - время компиляции
    //    {LEF_SEED, "seed"},            // - сид запуска ГПСЧ
    //    {LEF_TIK, "tik"}, // - счетчик тактов процессора
    //    {LEF_TIKSEC, "tiksec"}, // - счетчик секунд от старта
    //    {LEF_TIK_RTOS, "tikrtos"}, // - счетчик rtos
    //    {LEF_TIK_UNIX, "tikunix"}, // - счетчик времени
    //    {LEF_TYPE_FILTER, "typefilter"}, // - вывод настроек фильтрации типа
    //    {LEF_NAME_FILTER, "namefilter"}, // - вывод настроек фильтрации имени
    //    {LEF_TYPE_NUM, "typenum"}, // - имя типа сообщения, номером
    //    {LEF_NAME_NUM, "namenum"}, // - имя названия сообщения, номером
    //    {LEF_TYPE_LIST, "typelist"}, // - имена всех типов сообщений + номер флага
    //    {LEF_NAME_LIST, "namelist"}, // - имена всех названий сообщений

    //    {LEF_ALIGNL, "alignl"}, // - выравнивание при переносе
    //    {LEF_ALIGGT, "aliggt"}, // - выравнивание принудительное
    //    {LEF_NUM_TOKEN_HEAD, "headtoken"}, // - количество токенов в заголовке
    //    {LEF_NUM_TOKEN_LOGS, "logstoken"} // - количество токенов в логгере
};

/*
STR
  5.   =  |_ _ s t r|. = |s t r i n~g| -> от правого края + выход за пределы
   .5  = .|s t r _ _|  = |s t r i n~g| -> от левого края  + выход за пределы

   .5: = .|s t r _ _|  = |s t r i :|   -> от правого края + показать начало
  :.5  =  |s t r _ _|  = |: r i n g|   -> от правого края + показать конец
 :5.   =  |_ _ s t r|  = |: r i n g|   -> от левого края  + показать начало
  5.:  =  |_ _ s t r|  = |s t r i :|   -> от левого края  + показать конец
 :5.:  =  |_ _ s t r|  = |: r i n g|   -> от левого края  + показать центр

второе двоеточие игнорируется

не поддерживается
  5.2  =  |_ . s t r|. = |s t r i n~g| -> размер          + выход за пределы +
смещение от левого края 5.5  =  |_ s t r _|  = |s t r i n~g| -> по центру +
выход за пределы

NUM
   05  =  0 0 0 x x
   5.  =  _ _ _ x x
   .5  =  x x _ _ _
*/

// // END // FORMAT
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // FORMAT STYLE

typedef enum {
    LSM_NONE,
    LSM_STRAIGHT,
    LSM_ITALIC,
    LSM_LIGHT,
    LSM_BOLD,
} logger_style_mode;

//typedef struct logger_style {
//  const uintmax_t token;
//  const uintmax_t font[3];
//  const uintmax_t back[3];
//  const uintmax_t mode;
//} logger_style;

static logger_style logger_style_def[] = { {LEF_TOK, {0, 0, 0}, {0, 0, 0}, LSM_NONE},
                                           {LEF_PROG, {0, 0, 0}, {0, 0, 0}, LSM_NONE},
                                           {LEF_PROJ, {0, 0, 0}, {0, 0, 0}, LSM_NONE}
                                         };

// // END // FORMAT STYLE
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // TYPE LIST

//typedef struct logger_filter {
//  const uintmax_t id;
//  const uintmax_t flag;
//  const char *name;
//} logger_filter;

//typedef  enum __attribute__ ((aligned(4))) {
#define    L_NUL  LOGGER_FLAG_NUL
#define    L_VOID  LOGGER_FLAG(0)
#define    L_INFO   LOGGER_FLAG(1)
#define    L_ERROR  LOGGER_FLAG(2)
#define    L_WARNING  LOGGER_FLAG(3)
#define    L_TODO  LOGGER_FLAG(4)
#define    L_FIXME  LOGGER_FLAG(5)
#define    L_DEBUG  LOGGER_FLAG(6)
#define    L_RELEASE  LOGGER_FLAG(7)
#define    L_TRACE  LOGGER_FLAG(8)
#define    L_WARN  LOGGER_FLAG(9)
#define    L_FATAL  LOGGER_FLAG(10)
#define    L_BEGF  LOGGER_FLAG(11)
#define    L_ENDF  LOGGER_FLAG(12)
#define    L_FUNC  LOGGER_FLAG(13)
#define    L_LOGGER  LOGGER_FLAG(14)
#define    L_HEAD  LOGGER_FLAG(15)
#define    L_TEST  LOGGER_FLAG(16)
#define    L_ALL  LOGGER_FLAG_ALL
//} logger_filter_one;

#define LOGGER_LIST_GENERATE(N, NAME)  { N, NAME, #NAME }

static logger_filter logger_type_def[] = { LOGGER_LIST_GENERATE(0, L_NUL),
                                           LOGGER_LIST_GENERATE(1, L_VOID),
                                           LOGGER_LIST_GENERATE(2, L_INFO),
                                           LOGGER_LIST_GENERATE(3, L_ERROR),
                                           LOGGER_LIST_GENERATE(4, L_WARNING),
                                           LOGGER_LIST_GENERATE(5, L_TODO),
                                           LOGGER_LIST_GENERATE(6, L_FIXME),
                                           LOGGER_LIST_GENERATE(7, L_DEBUG),
                                           LOGGER_LIST_GENERATE(8, L_RELEASE),
                                           LOGGER_LIST_GENERATE(9, L_TRACE),
                                           LOGGER_LIST_GENERATE(10, L_WARN),
                                           LOGGER_LIST_GENERATE(11, L_FATAL),
                                           LOGGER_LIST_GENERATE(12, L_BEGF),
                                           LOGGER_LIST_GENERATE(13, L_ENDF),
                                           LOGGER_LIST_GENERATE(14, L_FUNC),
                                           LOGGER_LIST_GENERATE(15, L_LOGGER),
                                           LOGGER_LIST_GENERATE(16, L_HEAD),
                                           LOGGER_LIST_GENERATE(17, L_TEST),
                                           LOGGER_LIST_GENERATE(18, L_ALL)
                                         };

// // END // TYPE LIST
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // NAME LIST

//typedef enum {
#define    LL_NUL  LOGGER_FLAG_NUL
#define    LL_VOID  LOGGER_FLAG(0)
#define    LL_MAIN  LOGGER_FLAG(1)
#define    LL_INIT  LOGGER_FLAG(2)
#define    LL_DRVR  LOGGER_FLAG(3)
#define    LL_ALL  LOGGER_FLAG_ALL
//} logger_filter_two;

static logger_filter logger_name_def[] = { LOGGER_LIST_GENERATE(0, LL_NUL),
                                           LOGGER_LIST_GENERATE(1, LL_VOID),
                                           LOGGER_LIST_GENERATE(2, LL_MAIN),
                                           LOGGER_LIST_GENERATE(3, LL_INIT),
                                           LOGGER_LIST_GENERATE(4, LL_DRVR),
                                           LOGGER_LIST_GENERATE(5, LL_ALL)
                                         };

// // END // NAME LIST
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // SETTING

typedef enum {
    LS_STDOUT,
    LS_STDERR,
    LS_STDFILE,
    LS_STDLOG,
    LS_STDNET,
    LS_STDBUF,
    LS_STDCSV
} logger_streams;

//typedef struct logger_seting {
//  const char *head_format;
//  const char *logs_format;
//  const uintmax_t type;
//  const uintmax_t name;
//  const uintmax_t stream;
//  const uintmax_t style;
//} logger_setting;

static logger_setting logger_setting_def = {HEAD_FORMAT,
                                            LOGS_FORMAT,
                                            TYPE_FILTER,
                                            NAME_FILTER,
                                            LS_STDOUT,
                                            LOGGER_FALSE};

// // END // SETTING
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // DEFINE

//typedef struct logger_define {
//  uintmax_t seed; // - начальные настройки ГСПЧ
//  char *prog;     // - название программы
//  char *proj;     // - название проекта
//  char *version;  // - версия программы
//  char *compiler; // - версия компилятора
//} logger_define;

static logger_define logger_define_def = {.seed = 0,
                                          .prog = "yaya_logger",
                                          .proj = "yaya_library_collection_for_C",
                                          .version = "v0.1",
                                          .compiler = "gcc 7 x64"};

// // END // DEFINE
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // VARIABLES

//typedef struct logger_filter_ {
//  logger_filter *ptr; // - указатель на список типов
//  uintmax_t num;      // - количество типов
//} logger_filter_;

//typedef struct logger {
//    uintmax_t auto_head_flag; // - флаг заголовка
//    uintmax_t auto_init_flag; // - флаг инициализации

//    logger_filter_ type; // - список типов
//    logger_filter_ name; // - список имен

//    uintmax_t error; //ошибки логгера



//    uintmax_t temp_num_token;       // - количество токенов в форматной строке логгера
//    logger_token_mas *temp_mas_opt; // - указатель на структуру со смещениями токенов заголовка

//    uintmax_t logs_num_token;       // - количество токенов в форматной строке заголовка
//    logger_token_mas *logs_mas_opt; // - указатель на структуру со смещениями токенов логгера

//    logger_setting *psett; // - указатель на настройки логгера
//    logger_style *pstyl;   // - указатель на стили
//    logger_define *pdefn;  // - указатель на переменные среды

//    char *tmp_buff; // - указатель на времменый буфер
//    char *out_buff; // - указатель на буфер вывода
//    uintmax_t out_offset; // - указатель на конец строки
//    char *data_build;     // - дата сборки
//    char *time_build;     // - время сборки
//    char *projpath;       // - папка проекта
//    char *compilerversion;
//    uintmax_t curnum; // - номер текущего вывода
//    uintmax_t absnum; // - номер вывода без учета фильтрации
//    uintmax_t tiksec; // - время от старта программы, в секундах
//} logger;

// // END // VARIABLES
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // MACROS OPERATOR OVERLOADING

#if LOGGER_LOGS

#define loggerf(...)    \
    XXX_x(            , \
    ##__VA_ARGS__     , \
    XXX_Z(__VA_ARGS__), \
    XXX_Y(__VA_ARGS__), \
    XXX_X(__VA_ARGS__), \
    XXX_W(__VA_ARGS__), \
    XXX_V(__VA_ARGS__), \
    XXX_U(__VA_ARGS__), \
    XXX_T(__VA_ARGS__), \
    XXX_S(__VA_ARGS__), \
    XXX_R(__VA_ARGS__), \
    XXX_Q(__VA_ARGS__), \
    XXX_P(__VA_ARGS__), \
    XXX_O(__VA_ARGS__), \
    XXX_N(__VA_ARGS__), \
    XXX_M(__VA_ARGS__), \
    XXX_L(__VA_ARGS__), \
    XXX_K(__VA_ARGS__), \
    XXX_J(__VA_ARGS__), \
    XXX_I(__VA_ARGS__), \
    XXX_H(__VA_ARGS__), \
    XXX_G(__VA_ARGS__), \
    XXX_F(__VA_ARGS__), \
    XXX_E(__VA_ARGS__), \
    XXX_D(__VA_ARGS__), \
    XXX_C(__VA_ARGS__), \
    XXX_B(__VA_ARGS__), \
    XXX_A(__VA_ARGS__), \
    XXX_0(__VA_ARGS__))

#define XXX_x(x, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, FUNC, ...) FUNC


#define XXX_0()                log_0()
#define XXX_A(A)               log_1(A)
#define XXX_B(A, B)            log_2(A, B)
#define XXX_C(A, B, C)         log_3(A, B, C)
#define XXX_D(A, B, C, D)      log_4(A, B, C, D)
#define XXX_E(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_F(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_G(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_H(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_I(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_J(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_K(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_L(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_M(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_O(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_P(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_Q(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_R(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_S(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_T(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_U(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_V(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_W(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_X(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_Y(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)
#define XXX_Z(A, B, C, D, ...) log_5(A, B, C, D, __VA_ARGS__)

/*
A - logger [logger*]
B - L1     [int]
C - L2     [int]
D - str    [char*]
E - va     [...]

A     -> logger*
A     -> int(L1)
A     -> int(L2)            ???
A     -> char*

AB    -> logger*, int(L1)
AC    -> logger*, int(L2)   ???
AD    -> logger*, char*
BC    -> int(L1), int(L2)
BD    -> int(L1), char*
CD    -> int(L2), char*     ???
DE    -> char*  , va

ABC   -> logger*, int(L1), int(L2)
ABD   -> logger*, int(L1), char*
BCD   -> int(L1), int(L2), char*
BDE   -> int(L1), char*  , va

ABCD  -> int*   , int(L1), int(L2), char*
ABDE  -> int*   , int(L1), char*  , va
BCDE  -> int(L1), int(L2), char*  , va

ABCDE -> int*   , int(L1), int(L2), char*  , va
*/

#define log_0()      log______()

#define log_1(a)                       \
    _Generic((a),                      \
    logger*                    : log_A____(a), \
    logger_filter_one          : log__B___(a), \
    /*log___C__(a),*/     \
    char*                      : log____D_(a))


#define log_2(a, b)                                                            \
   _Generic((a),                                                               \
   logger*                    : _Generic((b),                                  \
                                 int                       : log_AB___(a, b),  \
                                 char*                     : log_A__D_(a, b)), \
    \
   int                        : _Generic((b),                                  \
                                 int                       : log__BC__(a, b),  \
                                 char*                     : log__B_D_(a, b)), \
    \
   char*                                                   : log____DE(a, b))



//#define log_3      (a, b, c)        _Generic((a), int*  : log_3_ABC__(a, b, c), int   : log_3__BCD_(a, b, c))
//#define log_3_ABC__(a, b, c)        _Generic((b), int   : log_3__BCD_(a, b, c))

//#define log_3_LA_AB_BC(L, A, BC) _Generic((BC), int : log_AB__(L, A, BC), char* : log_A_C_(L, A, BC))

////#define log_4(L, A, B, C) log_LABC_(L, A, B, C) || log_LA_CD(L, A, C, ...)
//#define log_4(L, A, BC, ...) _Generic((A), int : log_3_BC_CD(L, A, BC, __VA_ARGS__))
//#define log_4_BC_CD(L, A, BC, ...) _Generic((BC), int : log_3_B_C(L, A, BC, __VA_ARGS__), char * : log_3_C_D(L, A, BC, __VA_ARGS__))
//#define log_4_B_C(L, A, BC, ...) log_ABC_(L, A, BC, __VA_ARGS__)
//#define log_4_C_D(L, A, BC, ...) log_A_CD(L, A, BC, __VA_ARGS__)

////#define log_5(A, B, C, ...) log_LABCD(A, B, C, ##__VA_ARGS__)
//#define log_5(L, A, B, C, ...)   _Generic((A), int : log_4_B(L, A, B, C, __VA_ARGS__))
//#define log_5_B(L, A, B, C, ...) _Generic((B), int : log_4_C(L, A, B, C, __VA_ARGS__), char * : log_4_D(L, A, B, C, __VA_ARGS__))
//#define log_5_C(L, A, B, C, ...) log_ABCD(L, A, B, C, __VA_ARGS__)
//#define log_5_D(L, A, B, C, ...) log_A_CD(L, A, B, C, __VA_ARGS__)




#define LP_OR_DEF(A) _Generic((A), logger*               : (A), default : (LOGGER_LVG) )
#define L1_OR_DEF(A) _Generic((A), logger_filter_one     : (A), default : (L_VOID)     )
#define L2_OR_DEF(A) _Generic((A), logger_filter_two     : (A), default : (LL_VOID)    )
#define CP_OR_DEF(A) _Generic((A), char*                 : (A), default : (NULL)       )

#define LOGGER_MV __COUNTER__, __FILE__, __LINE__, __FUNCTION__

#define log______()                    yaya_log_func(LOGGER_MV, LOGGER_LVG  , L_VOID      , LL_VOID     , NULL        , NULL       )

#define log_A____(A)                   yaya_log_func(LOGGER_MV, LP_OR_DEF(A), L_VOID      , LL_VOID     , NULL        , NULL       )
#define log__B___(B)                   yaya_log_func(LOGGER_MV, LOGGER_LVG  , L1_OR_DEF(B), LL_VOID     , NULL        , NULL       )
#define log___C__(C)                   yaya_log_func(LOGGER_MV, LOGGER_LVG  , LL_VOID     , L2_OR_DEF(C), NULL        , NULL       )
#define log____D_(D)                   yaya_log_func(LOGGER_MV, LOGGER_LVG  , L_VOID      , LL_VOID     , CP_OR_DEF(D), NULL       )

#define log_AB___(A, B)                yaya_log_func(LOGGER_MV, LP_OR_DEF(A), L1_OR_DEF(B), LL_VOID     , NULL        , NULL       )
#define log_A_C__(A, C)                yaya_log_func(LOGGER_MV, LOGGER_LVG  , L_VOID      , L2_OR_DEF(C), NULL        , NULL       )
#define log_A__D_(A, D)                yaya_log_func(LOGGER_MV, LOGGER_LVG  , L_VOID      , LL_VOID     , CP_OR_DEF(D), NULL       )
#define log__BC__(B, C)                yaya_log_func(LOGGER_MV, LOGGER_LVG  , L1_OR_DEF(B), L2_OR_DEF(C), NULL        , NULL       )
#define log__B_D_(B, D)                yaya_log_func(LOGGER_MV, LOGGER_LVG  , L1_OR_DEF(B), LL_VOID     , CP_OR_DEF(D), NULL       )
#define log____DE(D, E)                yaya_log_func(LOGGER_MV, LOGGER_LVG  , L_VOID      , LL_VOID     , CP_OR_DEF(D), E          )





//#define log_ABC__(A, B, C)             yaya_log_func(A         , LOGGER_MV, IN_OR_DEF(B), IN_OR_DEF(C), NULL        , NULL       )
//#define log_AB_D_(A, B, D)             yaya_log_func(LOGGER_LVG, LOGGER_MV, IN_OR_DEF(B), L_VOID      , CP_OR_NUL(D), D          )
//#define log__BCD_(B, C, D)             yaya_log_func(LOGGER_LVG, LOGGER_MV, IN_OR_DEF(B), CP_OR_NUL(C), CP_OR_NUL(D), NULL       )
//#define log__B_DE(C, D, ...)           yaya_log_func(LOGGER_LVG, LOGGER_MV, IN_OR_DEF(B), L_VOID      , CP_OR_NUL(D), __VA_ARGS__)

//#define log_AB____(A, B)               yaya_log_func(L         , LOGGER_MV, A     , L_VOID,      NULL            , NULL       )
//#define log_AB__(A, B, C)              yaya_log_func(L         , LOGGER_MV, A     , INT_OR_1(B), NULL            , NULL       )

//#define log_A_C_(A, B, C)              yaya_log_func(L         , LOGGER_MV, A     , L_VOID     , CHARP_OR_NULL(C), NULL       )
//#define log_ABC_(A, B, C, ...)         yaya_log_func(L         , LOGGER_MV, A     , INT_OR_1(B), __VA_ARGS__     , NULL       )
//#define log_A_CD(A, B, C, ...)         yaya_log_func(L         , LOGGER_MV, A     , L_VOID     , CHARP_OR_NULL(C), __VA_ARGS__)

//#define log_ABCD(A, B, C, D, ...)      yaya_log_func(L         , LOGGER_MV, A     , INT_OR_1(B), CHARP_OR_NULL(C), __VA_ARGS__)


//LOGGER_LVG

// // END // MACROS OPERATOR OVERLOADING
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // MACRO BINDING


#define logger_init(L, A, B, C, D, E)   yaya_log_init(L, A, B, C, D, E)
#define logger_head(L, MESG, ...)       yaya_log_head(L, __COUNTER__, __FILE__, __LINE__, __FUNCTION__, MESG, ##__VA_ARGS__)
#define logeer_atom(L, TOKEN, ...)      yaya_log_atom(L, __COUNTER__, __FILE__, __LINE__, __FUNCTION__, TOKEN, ##__VA_ARGS__)

// // END // MACRO BINDING
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
#else
#define log_init(...)
#define log_head(...)
#define log_void(...)
#define log(...)
#endif

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // DECLARATION

void yaya_log_init(logger *lvg,
                   logger_filter *type,
                   logger_filter *name,
                   logger_setting *setting,
                   logger_define *define,
                   logger_style *style);

void yaya_log_head(logger *lvg,
                   uintmax_t count,
                   char *file,
                   uintmax_t line,
                   const char *func,
                   const char *mes,
                   ...);

uintmax_t yaya_log_func(uintmax_t count,
                        char *file,
                        uintmax_t line,
                        const char *func,
                        logger *lvg,
                        logger_filter_one type_one,
                        logger_filter_two type_two,
                        const char *mes,
                        ...);


uintmax_t // колличество токкенов
mas_opt(logger *lvg, const char *format, //форматная строка
        logger_token_mas **mas_opt, //хранилище распарсеной информации
        uintmax_t *num_token); // колличество токкенов



void logger_build(logger *lvg, const char *format, logger_token_mas *mas_opt,
                  uintmax_t *num_token, uintmax_t *count, char *file,
                  uintmax_t *line, const char *func, uintmax_t type,
                  uintmax_t name, const char *mesg, va_list mes_list);
void format_build_str(logger *lvg, logger_token_mas *mas_opt, const char *buff_orig);
void format_build_num(logger *lvg, logger_token_mas *mas_opt, uintmax_t *buff_orig);
void style_build(logger *lvg);
void logger_out(logger *lvg);

// // END // DECLARATION
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /*YAYA_LOGGER_H_*/
