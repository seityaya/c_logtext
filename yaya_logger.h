#ifndef YAYA_LOGGER_H_
#define YAYA_LOGGER_H_

#include "yaya_defines.h"
#include "yaya_logger_test.h"
#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOGGER_NULL 0

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // FORMAT

typedef struct {
    const intmax_t n;
    const char *name;
} logger_format;

typedef enum
{
    LEF_SEPARATOR,
    LEF_PROG,
    LEF_PROJ,
    LEF_PROJPATH,
    LEF_VERSION,
    LEF_DATA_BUILD,
    LEF_TIME_BUILD,
    LEF_SEED,
    LEF_COMPILER,
    LEF_CURNUM,
    LEF_ABSNUM,
    LEF_COUNT,
    LEF_TIK,
    LEF_TIKSEC,
    LEF_TIK_RTOS,
    LEF_TIK_UNIX,
    LEF_TYPE,
    LEF_NAME,
    LEF_DATA,
    LEF_TIME,
    LEF_FULLPATH,
    LEF_SHORPATH,
    LEF_FILENAME,
    LEF_LINE,
    LEF_FUNC,
    LEF_MESAGE,
    LEF_NEWLINE,
    LEF_ALIGNL,
    LEF_ALIGGT,
    LEF_END,
    LEF_ENDEND
} logger_enum_format;

static logger_format logger_format_list[LEF_ENDEND] = {{LEF_SEPARATOR, "$"},           // - метка
                                                       {LEF_PROG, "prog"},             // - название програмы
                                                       {LEF_PROJ, "proj"},             // - название проекта
                                                       {LEF_PROJPATH, "projpath"},     // - расположение проекта
                                                       {LEF_VERSION, "version"},       // - версия верси программы
                                                       {LEF_DATA_BUILD, "data_build"}, // - дата компиляции
                                                       {LEF_TIME_BUILD, "time_build"}, // - время компиляции
                                                       {LEF_SEED, "seed"},             // - сид запуска ГПСЧ
                                                       {LEF_COMPILER, "compiler"},     // - версия компилятора
                                                       {LEF_CURNUM, "curnum"},         // - номер выведеного сообщения
                                                       {LEF_ABSNUM, "absnum"}, // - номер сообщения без учета фильтрации
                                                       {LEF_COUNT, "count"},   // - номер сообщения, на основе __COUNTER__
                                                       {LEF_TIK, "tik"},       // - счетчик тактов процесора
                                                       {LEF_TIKSEC, "tiksec"},    // - счетчик секунд от старта
                                                       {LEF_TIK_RTOS, "tikrtos"}, // - счетчик rtos
                                                       {LEF_TIK_UNIX, "tikunix"}, // - счетчик времени
                                                       {LEF_TYPE, "type"},        // - тип сообщения
                                                       {LEF_NAME, "name"},        // - имя сообщения
                                                       {LEF_DATA, "data"},        // - дата сообщения
                                                       {LEF_TIME, "time"},        // - время сообщения
                                                       {LEF_FULLPATH, "fullpath"}, // - полный путь к файлу, из которого сообщение
                                                       {LEF_SHORPATH, "shorpath"}, // - короткий путь к файлу, из которого сообщение
                                                       {LEF_FILENAME, "filename"}, // - файл
                                                       {LEF_LINE, "line"},         // - номер строки
                                                       {LEF_FUNC, "func"},         // - имя функции
                                                       {LEF_MESAGE, "mesage"},     // - тело сообщения
                                                       {LEF_NEWLINE, "nl"},        // - перевод строки
                                                       {LEF_ALIGNL, "alignl"},     // - выравнивание при переносе
                                                       {LEF_ALIGGT, "aliggt"},     // - выравнивание принудительное
                                                       {LEF_END, " "}};
// // END // FORMAT
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // FLAG LIST

typedef struct {
    const uintmax_t n;
    const uintmax_t flag;
    const char *name;
} logger_list;

typedef enum
{
    L_NUL = FLAG_NUL,
    L_VOID = FLAG(0),
    L_INFO = FLAG(1),
    L_ERROR = FLAG(2),
    L_WARNING = FLAG(3),
    L_TODO = FLAG(4),
    L_FIXMI = FLAG(5),
    L_DEBUG = FLAG(6),
    L_RELISE = FLAG(7),
    L_TRASE = FLAG(8),
    L_WARN = FLAG(9),
    L_FATAL = FLAG(10),
    L_BEGF = FLAG(11),
    L_ENDF = FLAG(12),
    L_FUNC = FLAG(13),
    L_LOGGER = FLAG(14),
    L_HEAD = FLAG(15),
    L_TEST = FLAG(16),
    L_ALL = FLAG_ALL
} logger_flag_type;

#define LOGGER_LIST_GENERETE(N, NAME) \
    { N, NAME, #NAME }

static logger_list logger_type_def[] = {LOGGER_LIST_GENERETE(0, L_NUL),
                                        LOGGER_LIST_GENERETE(1, L_VOID),
                                        LOGGER_LIST_GENERETE(2, L_INFO),
                                        LOGGER_LIST_GENERETE(3, L_ERROR),
                                        LOGGER_LIST_GENERETE(4, L_WARNING),
                                        LOGGER_LIST_GENERETE(5, L_TODO),
                                        LOGGER_LIST_GENERETE(6, L_FIXMI),
                                        LOGGER_LIST_GENERETE(7, L_DEBUG),
                                        LOGGER_LIST_GENERETE(8, L_RELISE),
                                        LOGGER_LIST_GENERETE(9, L_TRASE),
                                        LOGGER_LIST_GENERETE(10, L_WARN),
                                        LOGGER_LIST_GENERETE(11, L_FATAL),
                                        LOGGER_LIST_GENERETE(12, L_BEGF),
                                        LOGGER_LIST_GENERETE(13, L_ENDF),
                                        LOGGER_LIST_GENERETE(14, L_FUNC),
                                        LOGGER_LIST_GENERETE(15, L_LOGGER),
                                        LOGGER_LIST_GENERETE(16, L_HEAD),
                                        LOGGER_LIST_GENERETE(17, L_TEST),
                                        LOGGER_LIST_GENERETE(18, L_ALL)};

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    LL_NUL = FLAG_NUL,
    LL_MAIN = FLAG(0),
    LL_INIT = FLAG(1),
    LL_ALL = FLAG_ALL
} logger_flag_neme;

static logger_list logger_name_def[] = {LOGGER_LIST_GENERETE(0, LL_NUL),
                                        LOGGER_LIST_GENERETE(1, LL_MAIN),
                                        LOGGER_LIST_GENERETE(2, LL_INIT),
                                        LOGGER_LIST_GENERETE(3, LL_ALL)};
// // END // FLAG LIST
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // SETTING

typedef enum
{
    L_STDOUT,
    L_STDERR,
    L_STDFILE,
    L_STDLOG,
    L_STDNET,
    L_STDBUFF
} logger_streams;

typedef struct logger_seting {
    char *format_head;
    char *format_logs;
    uintmax_t type;
    uintmax_t title;
    uintmax_t stream;
    uintmax_t style;
    uintmax_t log_head;
} logger_setting;

static logger_setting logger_setting_def[1] = {{"$prog $version $data_assembly $time_assembly $seed",
                                                "$actnum $absnum $type $name $data $time $path $line $func $mesage",
                                                L_INFO,
                                                L_ALL,
                                                L_STDOUT,
                                                TRUE,
                                                TRUE}};

// // END // SETTING
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // STYLE

typedef struct logger_style {
    intmax_t t;
} logger_style;

static logger_style logger_style_def[1];

// // END // STYLE
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // DEFINE

typedef struct logger_define {
    intmax_t seed;
    char *prog;
    char *proj;
    char *version;
    char *type;
    char *compiler;
} logger_define;

static logger_define logger_define_def[1];

// // END // DEFINE
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // VARIABLES

typedef struct logger_variables {
    uintmax_t log_init;
    uintmax_t log_head;

    logger_list *type;
    uintmax_t type_num;

    logger_list *name;
    uintmax_t name_num;

    logger_setting *sett;
    logger_style *styl;
    logger_define *defn;

    intmax_t format_head_list[LEF_END];
    intmax_t format_logs_list[LEF_END];

    char *data_assembly;
    char *time_assembly;
    char *projpath;
    intmax_t curnum;
    intmax_t absnum;
} logger_variables;

static logger_variables logger_variables_global[1] = {{FALSE, FALSE, NULL, 0, NULL, 0, NULL, NULL, NULL, {0}, {0}, NULL, NULL, NULL, FALSE, FALSE}};

// // END // VARIABLES
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // DECLARATION

void yaya_log_init(logger_list *type, logger_list *name, logger_setting *setting, logger_define *define, logger_style *style);
void yaya_log_head(void);
void yaya_log_func(
    char *data, char *time, char *file, uintmax_t line, uintmax_t count, const char *func, uintmax_t type, uintmax_t name, const char *mes, ...);

// // END // DECLARATION
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // MACROS OPERATOR OVERLOADING

#define log(...) \
    XXX_x(, \
          ##__VA_ARGS__, \
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

#define XXX_0() log_0()
#define XXX_A(A) log_1(A)
#define XXX_B(A, B) log_2(A, B)
#define XXX_C(A, B, C) log_3(A, B, C)
#define XXX_D(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_E(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_F(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_G(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_H(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_I(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_J(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_K(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_L(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_M(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_O(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_P(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_Q(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_R(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_S(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_T(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_U(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_V(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_W(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_X(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_Y(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_Z(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)

#define log_0() log_____()
#define log_1(A) log_A___(A)

//#define log_2(A, B) log_AB__(A, B)
#define log_2(A, BC) _Generic((A), int : log_2_BC(A, BC))
#define log_2_BC(A, BC) _Generic((BC), int : log_AB__(A, BC), char * : log_A_C_(A, BC))

//#define log_3(A, B, C) log_ABC_(A, B, C)
#define log_3(A, BC, ...) _Generic((A), int : log_3_BC_CD(A, BC, __VA_ARGS__))
#define log_3_BC_CD(A, BC, ...) _Generic((BC), int : log_3_B_C(A, BC, __VA_ARGS__), char * : log_3_C_D(A, BC, __VA_ARGS__))
#define log_3_B_C(A, BC, ...) log_ABC_(A, BC, __VA_ARGS__)
#define log_3_C_D(A, BC, ...) log_A_CD(A, BC, __VA_ARGS__)

//#define log_4(A, B, C, ...) log_ABCD(A, B, C, ##__VA_ARGS__)
#define log_4(A, B, C, ...) _Generic((A), int : log_4_B(A, B, C, __VA_ARGS__))
#define log_4_B(A, B, C, ...) _Generic((B), int : log_4_C(A, B, C, __VA_ARGS__), char * : log_4_D(A, B, C, __VA_ARGS__))
#define log_4_C(A, B, C, ...) log_ABCD(A, B, C, __VA_ARGS__)
#define log_4_D(A, B, C, ...) log_A_CD(A, B, C, __VA_ARGS__)

#define log_____() /*              */ _logger_cal_str  0, 0, 0, 0)           _logger_cal_stp //0
#define log_A___(A) /*             */ _logger_cal_str  A, 0, 0, 0)           _logger_cal_stp //1
#define log_AB__(A, B) /*          */ _logger_cal_str  A, B, 0, 0)           _logger_cal_stp //2
#define log_A_C_(A, C) /*          */ _logger_cal_str  A, 0, C, 0)           _logger_cal_stp //2
#define log_ABC_(A, B, ...) /*     */ _logger_cal_str  A, B, __VA_ARGS__, 0) _logger_cal_stp //3
#define log_A_CD(A, C, ...) /*     */ _logger_cal_str  A, 0, C, __VA_ARGS__) _logger_cal_stp //3
#define log_ABCD(A, B, C, ...) /*  */ _logger_cal_str  A, B, C, __VA_ARGS__) _logger_cal_stp //4

// // END // MACROS OPERATOR OVERLOADING
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // MACRO BINDING

#define _logger_cal_str yaya_log_func(NULL, NULL, __FILE__, __LINE__, __COUNTER__, __FUNCTION__,
//yaya_log_func_test_mini(__LINE__, __COUNTER__,
#define _logger_cal_stp

#define log_init(A, B, C, D, E) yaya_log_init(A, B, C, D, E)
#define log_test_fnc() yaya_log_test_func_set()
#define log_test_mac() yaya_log_test_macros_set()

// // END // MACRO BINDING
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /*YAYA_LOGGER_H_*/
