#ifndef YAYA_LOGGER_H_
#define YAYA_LOGGER_H_

#include "yaya_defines.h"
#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // FORMAT

typedef struct
{                      /*список ключей*/
    const intmax_t id; /*идентификатор*/
    const char *name;  /*текстовое представление ключей*/
} logger_format;

typedef struct
{ /**/
    uintmax_t beg;
    uintmax_t end;
    uintmax_t id;
} logger_format_mas;

typedef enum {
    LEF_SEPARATOR,
    LEF_STRING,
    LEF_TOKEN,
    LEF_PROG,
    LEF_PROJPATH,
    LEF_PROJ,
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
    LEF_TYPE_FILTER,
    LEF_NAME_FILTER,
    LEF_TYPE_NUM,
    LEF_NAME_NUM,
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
    LEF_END
} logger_forma_id;

static logger_format logger_format_list[LEF_END] = {{LEF_SEPARATOR, "$"},          // - токен
                                                    {LEF_STRING, "_string"},       // - строка,
                                                    {LEF_TOKEN, "_token"},         // - токен
                                                    {LEF_PROG, "prog"},            // - название програмы
                                                    {LEF_PROJPATH, "projpath"},    // - расположение проекта
                                                    {LEF_PROJ, "proj"},            // - название проекта
                                                    {LEF_VERSION, "version"},      // - версия верси программы
                                                    {LEF_DATA_BUILD, "databuild"}, // - дата компиляции
                                                    {LEF_TIME_BUILD, "timebuild"}, // - время компиляции
                                                    {LEF_SEED, "seed"},            // - сид запуска ГПСЧ
                                                    {LEF_COMPILER, "compiler"},    // - версия компилятора
                                                    {LEF_CURNUM, "curnum"},        // - номер выведеного сообщения
                                                    {LEF_ABSNUM, "absnum"}, // - номер сообщения без учета фильтрации
                                                    {LEF_COUNT, "count"},   // - номер сообщения, на основе __COUNTER__
                                                    {LEF_TIK, "tik"},       // - счетчик тактов процесора
                                                    {LEF_TIKSEC, "tiksec"}, // - счетчик секунд от старта
                                                    {LEF_TIK_RTOS, "tikrtos"},    // - счетчик rtos
                                                    {LEF_TIK_UNIX, "tikunix"},    // - счетчик времени
                                                    {LEF_TYPE_FILTER, "typenum"}, // - вывод настроек фильтрации типа
                                                    {LEF_NAME_FILTER, "namenum"}, // - вывод настроек фильтрации имени
                                                    {LEF_TYPE_NUM, "typenum"},    // - имя типа сообщения, номерами
                                                    {LEF_NAME_NUM, "namenum"},    // - имя названия сообщения, номерами
                                                    {LEF_TYPE, "type"},           // - имя типа сообщения
                                                    {LEF_NAME, "name"},           // - имя названия сообщения
                                                    {LEF_DATA, "data"},           // - дата сообщения
                                                    {LEF_TIME, "time"},           // - время сообщения
                                                    {LEF_FULLPATH, "fullpath"}, // - полный путь к файлу, из которого сообщение
                                                    {LEF_SHORPATH, "shorpath"}, // - короткий путь к файлу, из которого сообщение
                                                    {LEF_FILENAME, "filename"}, // - файл
                                                    {LEF_LINE, "line"},         // - номер строки
                                                    {LEF_FUNC, "func"},         // - имя функции
                                                    {LEF_MESAGE, "mesage"},     // - тело сообщения
                                                    {LEF_NEWLINE, "nl"},        // - перевод строки
                                                    {LEF_ALIGNL, "alignl"},     // - выравнивание при переносе
                                                    {LEF_ALIGGT, "aliggt"}};    // - выравнивание принудительное

// // END // FORMAT
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // FORMAT STYLE
typedef enum { LSM_NONE, LSM_STRAIGHT, LSM_ITALIC, LSM_LIGHT, LSM_BOLD } logger_style_mode;

typedef struct logger_style
{
    const uintmax_t format;
    const uintmax_t font[3];
    const uintmax_t back[3];
    const uintmax_t mode;
} logger_style;

static logger_style logger_style_def[] = {{LEF_SEPARATOR, {0, 0, 0}, {0, 0, 0}, LSM_NONE},
                                          {LEF_PROG, {0, 0, 0}, {0, 0, 0}, LSM_NONE},
                                          {LEF_PROJ, {0, 0, 0}, {0, 0, 0}, LSM_NONE}};

// // END // FORMAT STYLE
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // FLAG LIST

typedef struct
{
    const uintmax_t id;
    const uintmax_t flag;
    const char *name;
} logger_list;

typedef enum {
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

// // END // FLAG LIST
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // NAME LIST
typedef enum { LL_NUL = FLAG_NUL, LL_MAIN = FLAG(0), LL_INIT = FLAG(1), LL_my_F = FLAG(2), LL_ALL = FLAG_ALL } logger_flag_neme;

static logger_list logger_name_def[] = {LOGGER_LIST_GENERETE(0, LL_NUL),
                                        LOGGER_LIST_GENERETE(1, LL_MAIN),
                                        LOGGER_LIST_GENERETE(2, LL_INIT),
                                        LOGGER_LIST_GENERETE(3, LL_my_F),
                                        LOGGER_LIST_GENERETE(4, LL_ALL)};
// // END // NAME LIST
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // SETTING

typedef enum { L_STDOUT, L_STDERR, L_STDFILE, L_STDLOG, L_STDNET, L_STDBUF } logger_streams;

typedef struct logger_seting
{
    const char *format_head;
    const char *format_logs;
    const uintmax_t type;
    const uintmax_t name;
    const uintmax_t stream;
    const uintmax_t style;
} logger_setting;

static logger_setting logger_setting_def[1] = {{"HELLO my header: $prog $version$databuild #$timebuild $$ $seed $name-$type \"bay\" "
                                                "$projpath$line$func",
                                                "## $prog | $type | $name | $func | $line | $mesage",
                                                L_ALL,
                                                LL_ALL,
                                                L_STDOUT,
                                                FALSE}};

// // END // SETTING
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // DEFINE

typedef struct logger_define
{
    const intmax_t seed;
    const char *prog;
    const char *proj;
    const char *version;
    const char *compiler;
} logger_define;

static logger_define logger_define_def[] = {{0, "yaya_logger", "yaya_library_collection_for_C", "v0.1", "gcc 7 64-bit"}};

// // END // DEFINE
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // VARIABLES

typedef struct logger_variables
{
    //FLAG
    uintmax_t log_init_flag;
    uintmax_t log_head_flag;

    //PTR
    logger_list *ptype;
    uintmax_t type_num;
    logger_list *pname;
    uintmax_t name_num;
    logger_setting *psett;
    logger_style *pstyl;
    logger_define *pdefn;
    struct logger_variables *pglob;

    uintmax_t type_num_token;
    uintmax_t name_num_token;

    logger_format_mas *logger_token_mas_opt;

    // PARAM
    char *vfile;
    uintmax_t vcount;
    uintmax_t vline;
    char *vfunc;
    uintmax_t vtype;
    uintmax_t vname;
    char *vmesg;
    va_list vprm;

    char *data_assembly;
    char *time_assembly;
    char *projpath;
    intmax_t curnum;
    intmax_t absnum;
} logger_variables;

static logger_variables logger_variables_global[1] = {{FALSE, FALSE}};

// // END // VARIABLES
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

#define log_____() /*            */ yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, 0, 0, 0, 0)           // 0
#define log_A___(A) /*           */ yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, A, 0, 0, 0)           // 1
#define log_AB__(A, B) /*        */ yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, A, B, 0, 0)           // 2
#define log_A_C_(A, C) /*        */ yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, A, 0, C, 0)           // 2
#define log_ABC_(A, B, ...) /*   */ yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, A, B, __VA_ARGS__, 0) // 3
#define log_A_CD(A, C, ...) /*   */ yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, A, 0, C, __VA_ARGS__) // 3
#define log_ABCD(A, B, C, ...) /**/ yaya_log_func(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, A, B, C, __VA_ARGS__) // 4

// // END // MACROS OPERATOR OVERLOADING
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // MACRO BINDING

#define log_init(A, B, C, D, E) yaya_log_init(A, B, C, D, E)
#define log_head(MESG, ...) yaya_log_head(__COUNTER__, __FILE__, __LINE__, __FUNCTION__, MESG, ##__VA_ARGS__)

// // END // MACRO BINDING
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // DECLARATION

void yaya_log_init(logger_list *type, logger_list *name, logger_setting *setting, logger_define *define, logger_style *style);
void yaya_log_head(uintmax_t count, char *file, uintmax_t line, const char *func, const char *mes, ...);
void yaya_log_func(uintmax_t count, char *file, uintmax_t line, const char *func, uintmax_t type, uintmax_t name, const char *mes, ...);

// // END // DECLARATION
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /*YAYA_LOGGER_H_*/
