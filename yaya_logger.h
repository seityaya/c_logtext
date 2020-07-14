#ifndef YAYA_LOGGER_H_
#define YAYA_LOGGER_H_

#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // DEFINE OPTION
#define LOGGER_LOGS LOGGER_TRUE   /*Включить логгер*/
#define LOGGER_HEAD LOGGER_FALSE  /*Включить заголовки*/
#define LOGGER_STYLE LOGGER_FALSE /*Включить стили*/

#define LOGGER_AUTO_INIT LOGGER_FALSE /*Автоматическая Инициализация*/
#define LOGGER_AUTO_HEAD LOGGER_FALSE /*Автоматический вывод заголовка*/

#define HIDEN_STR "..."

#define LOGS_FORMAT "## $absnum%3. | $curnum%3. | $type%.10 | $name%.10 | $count%3. | $file%:.25 | $line%3. | $func%:15. | $mesage"
#define HEAD_FORMAT "HELLO"
#define TYPE_FILTER L_ALL ^ L_BEGF ^ L_ENDF
#define NAME_FILTER LL_ALL ^ LL_DRVR

// // END // DEFINE OPTION
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // MACRO FUNCTION

#define LOGGER_FLAG(x) (1 << (x))
#define LOGGER_FLAG_ALL (2147483647)
#define LOGGER_FLAG_NUL (0)
#define LOGGER_BIT_GET(x, n) ((x) & (1 << (n)))
#define LOGGER_TRUE (1 == 1)
#define LOGGER_FALSE (!LOGGER_TRUE)

// // END // MACRO FUNCTION
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // FORMAT

#define FES_LEF 1
#define FES_RIG 2
#define FES_LEFHIDE 3
#define FES_RIGHIDE 4
#define FES_NUL 5

typedef struct
{                     /*хранение спецификаторов*/
    uintmax_t beg;    /*начало токена*/
    uintmax_t end;    /*конец токена*/
    uintmax_t lef;    /*смещение с лева*/
    uintmax_t rig;    /*смещение с права*/
    uintmax_t fes;    /*сторона скрытия*/
} logger_format_specifiers;

typedef struct
{                      /*хранение токенов*/
    uintmax_t type;    /*тип параметра*/
    uintmax_t id;      /*тип токена*/
    uintmax_t beg;     /*начало токена*/
    uintmax_t end;     /*конец токена*/
    logger_format_specifiers *spe;
} logger_format_mas;

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{                         /*список токенов*/
    const uintmax_t type; /*тип параметра*/
    const uintmax_t id;   /*идентификатор*/
    const char *name;     /*текстовое представление ключей*/
} logger_format;

typedef enum
{
    //SYS
    LEF_TOK,
    LEF_SPE,
    LEF_SEP,
    LEF_HID,
    LEF_STR,

    //WORK
    LEF_LINE,
    LEF_FILENAME,
    LEF_FUNC,
    LEF_COUNT,
    LEF_TYPE,
    LEF_NAME,
    LEF_MESAGE,
    LEF_CURNUM,
    LEF_ABSNUM,

    //NOT WORK
    LEF_PROG,
    LEF_PROJPATH,
    LEF_PROJ,
    LEF_VERSION,
    LEF_DATA_BUILD,
    LEF_TIME_BUILD,
    LEF_SEED,
    LEF_COMPILER,
    LEF_TIK,
    LEF_TIKSEC,
    LEF_TIK_RTOS,
    LEF_TIK_UNIX,
    LEF_TYPE_FILTER,
    LEF_NAME_FILTER,
    LEF_TYPE_NUM,
    LEF_NAME_NUM,
    LEF_TYPE_ALL,
    LEF_NAME_ALL,
    LEF_DATA,
    LEF_TIME,
    LEF_FULLPATH,
    LEF_SHORPATH,
    LEF_ALIGNL,
    LEF_ALIGGT,
    LEF_NUM_TOKEN_HEAD,
    LEF_NUM_TOKEN_LOGS,
    LEF_END
} logger_forma_id;

#define F_STR 1
#define F_NUM 2
#define F_SYS 3

/*
STR
  5.   =  |_ _ s t r|. = |s t r i n~g| -> от правого края + выход за пределы
   .5  = .|s t r _ _|  = |s t r i n~g| -> от левого края  + выход за пределы
                                    
   .5: = .|s t r _ _|  = |s t r i :|   -> от правого края + показать начало
  :.5  =  |s t r _ _|  = |: r i n g|   -> от правого края + показать конец
 :5.   =  |_ _ s t r|  = |: r i n g|   -> от левого края  + показать начало
  5.:  =  |_ _ s t r|  = |s t r i :|   -> от левого края  + показать конец
 :5.:  =  |_ _ s t r|  = |: r i n g|   -> от левого края  + показать конец - второе двоеточие игнорируется
                                                                          
not work, 
  5.2  =  |_ . s t r|. = |s t r i n~g| -> размер          + выход за пределы + смещение от левого края 
  5.5  =  |_ s t r _|  = |s t r i n~g| -> по центру       + выход за пределы
                                             
NUM
   05  =  0 0 0 x x
   5.  =  _ _ _ x x
   .5  =  x x _ _ _
*/

static logger_format logger_format_list[LEF_END] = {
    {F_SYS, LEF_TOK, "$"}, // - токен формата строки
    {F_SYS, LEF_SPE, "%"}, // - токен формата вывода
    {F_SYS, LEF_SEP, "."}, // - токен формата вывода, разделитель
    {F_SYS, LEF_HID, ":"}, // - токен формата вывода, скрывать
    {F_SYS, LEF_STR, "&"}, // - строка, служебное обозначение

    {F_NUM, LEF_LINE, "line"},     // - номер строки
    {F_STR, LEF_FILENAME, "file"}, // - файл
    {F_STR, LEF_FUNC, "func"},     // - имя функции
    {F_NUM, LEF_COUNT, "count"},   // - номер сообщения, на основе __COUNTER__
    {F_STR, LEF_TYPE, "type"},     // - имя типа сообщения
    {F_STR, LEF_NAME, "name"},     // - имя названия сообщения
    {F_STR, LEF_MESAGE, "mesage"}, // - тело сообщения
    {F_NUM, LEF_CURNUM, "curnum"}, // - номер выведеного сообщения
    {F_NUM, LEF_ABSNUM, "absnum"}, // - номер сообщения без учета фильтрации

    //    {F_STR, LEF_PROG, "prog"},                // - название програмы
    //    {F_STR, LEF_PROJ, "proj"},                // - название проекта
    //    {F_STR, LEF_PROJPATH, "path"},            // - расположение проекта
    //    {F_STR, LEF_FULLPATH, "fullpath"},        // - полный путь к файлу, из которого сообщение
    //    {F_STR, LEF_SHORPATH, "shorpath"},        // - короткий путь к файлу, из которого сообщение
    //    {F_STR, LEF_VERSION, "version"},          // - версия верси программы
    //    {F_STR, LEF_DATA_BUILD, "databuild"},     // - дата компиляции
    //    {F_STR, LEF_TIME_BUILD, "timebuild"},     // - время компиляции
    //    {F_NUM, LEF_SEED, "seed"},                // - сид запуска ГПСЧ
    //    {F_STR, LEF_COMPILER, "compiler"},        // - версия компилятора
    //    {F_NUM, LEF_TIK, "tik"},                  // - счетчик тактов процесора
    //    {F_NUM, LEF_TIKSEC, "tiksec"},            // - счетчик секунд от старта
    //    {F_NUM, LEF_TIK_RTOS, "tikrtos"},         // - счетчик rtos
    //    {F_NUM, LEF_TIK_UNIX, "tikunix"},         // - счетчик времени
    //    {F_STR, LEF_TYPE_FILTER, "typefilter"},   // - вывод настроек фильтрации типа
    //    {F_STR, LEF_NAME_FILTER, "namefilter"},   // - вывод настроек фильтрации имени
    //    {F_NUM, LEF_TYPE_NUM, "typenum"},         // - имя типа сообщения, номером
    //    {F_NUM, LEF_NAME_NUM, "namenum"},         // - имя названия сообщения, номером
    //    {F_STR, LEF_TYPE_ALL, "typeall"},         // - имена всех типов сообщений
    //    {F_STR, LEF_NAME_ALL, "nameall"},         // - имена всех названий сообщений
    //    {F_STR, LEF_DATA, "data"},                // - дата сообщения
    //    {F_STR, LEF_TIME, "time"},                // - время сообщения
    //    {F_STR, LEF_ALIGNL, "alignl"},            // - выравнивание при переносе
    //    {F_STR, LEF_ALIGGT, "aliggt"},            // - выравнивание принудительное
    //    {F_NUM, LEF_NUM_TOKEN_HEAD, "headtoken"}, // - колличесво токенов в заголовке
    //    {F_NUM, LEF_NUM_TOKEN_LOGS, "logstoken"}  // - колличесво токенов в логгере
};

// // END // FORMAT
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // FORMAT STYLE
typedef enum
{
    LSM_NONE,
    LSM_STRAIGHT,
    LSM_ITALIC,
    LSM_LIGHT,
    LSM_BOLD
} logger_style_mode;

typedef struct logger_style
{
    const uintmax_t format;
    const uintmax_t font[3];
    const uintmax_t back[3];
    const uintmax_t mode;
} logger_style;

static logger_style logger_style_def[] = {{LEF_TOK, {0, 0, 0}, {0, 0, 0}, LSM_NONE},
                                          {LEF_PROG, {0, 0, 0}, {0, 0, 0}, LSM_NONE},
                                          {LEF_PROJ, {0, 0, 0}, {0, 0, 0}, LSM_NONE}};

// // END // FORMAT STYLE
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // LOGGER_FLAG LIST

typedef struct
{
    const uintmax_t id;
    const uintmax_t flag;
    const char *name;
} logger_list;

typedef enum
{
    L_NUL = LOGGER_FLAG_NUL,
    L_VOID = LOGGER_FLAG(0),
    L_INFO = LOGGER_FLAG(1),
    L_ERROR = LOGGER_FLAG(2),
    L_WARNING = LOGGER_FLAG(3),
    L_TODO = LOGGER_FLAG(4),
    L_FIXMI = LOGGER_FLAG(5),
    L_DEBUG = LOGGER_FLAG(6),
    L_RELISE = LOGGER_FLAG(7),
    L_TRASE = LOGGER_FLAG(8),
    L_WARN = LOGGER_FLAG(9),
    L_FATAL = LOGGER_FLAG(10),
    L_BEGF = LOGGER_FLAG(11),
    L_ENDF = LOGGER_FLAG(12),
    L_FUNC = LOGGER_FLAG(13),
    L_LOGGER = LOGGER_FLAG(14),
    L_HEAD = LOGGER_FLAG(15),
    L_TEST = LOGGER_FLAG(16),
    L_ALL = LOGGER_FLAG_ALL
} logger_LOGGER_FLAG_type;

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
// // END // LOGGER_FLAG LIST
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // NAME LIST

typedef enum
{
    LL_NUL = LOGGER_FLAG_NUL,
    LL_MAIN = LOGGER_FLAG(0),
    LL_INIT = LOGGER_FLAG(1),
    LL_DRVR = LOGGER_FLAG(2),
    LL_ALL = LOGGER_FLAG_ALL
} logger_LOGGER_FLAG_neme;

static logger_list logger_name_def[] = {LOGGER_LIST_GENERETE(0, LL_NUL),
                                        LOGGER_LIST_GENERETE(1, LL_MAIN),
                                        LOGGER_LIST_GENERETE(2, LL_INIT),
                                        LOGGER_LIST_GENERETE(3, LL_DRVR),
                                        LOGGER_LIST_GENERETE(4, LL_ALL)};
// // END // NAME LIST
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // SETTING

typedef enum
{
    LS_STDOUT,
    LS_STDERR,
    LS_STDFILE,
    LS_STDLOG,
    LS_STDNET,
    LS_STDBUF,
    LS_STDCSV
} logger_streams;

typedef struct logger_seting
{
    const char *head_format;
    const char *logs_format;
    const uintmax_t type;
    const uintmax_t name;
    const uintmax_t stream;
    const uintmax_t style;
} logger_setting;

static logger_setting logger_setting_def[1] = {{HEAD_FORMAT, LOGS_FORMAT, TYPE_FILTER, NAME_FILTER, LS_STDOUT, LOGGER_FALSE}};

// // END // SETTING
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // DEFINE

typedef struct logger_define
{
    uintmax_t seed; // - начальные настройки ГСПЧ
    char *prog;     // - название программы
    char *proj;     // - название проекта
    char *version;  // - версия программы
                    //   char *compiler; // - версия компилятора
} logger_define;

static logger_define logger_define_def[] = {{0, "yaya_logger", "yaya_library_collection_for_C", "v0.1"}};

// // END // DEFINE
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // VARIABLES

typedef struct logger_variables
{
    uintmax_t head_flag; // - флаг заголовка
    uintmax_t init_flag; // - флаг инициализации

    uintmax_t head_num_token;        // - колличество токенов в форматной строке логгера
    logger_format_mas *logs_mas_opt; // - указатель на структуру со смещениями токенов логера

    uintmax_t logs_num_token;        // - колличество токенов в форматной строке заголовка
    logger_format_mas *head_mas_opt; // - указатель на структуру со смещениями токенов заголовка

    logger_list *ptype;             // - указатель на список типов
    logger_list *pname;             // - указатель на список имен
    logger_setting *psett;          // - указатель на настройки логгера
    logger_style *pstyl;            // - указатель на стили
    logger_define *pdefn;           // - указатель на переменные среды
    struct logger_variables *pglob; // указатель структуру с внутренними переменными

    uintmax_t type_num; // - колличесво типов
    uintmax_t name_num; // - колличество имен

    uintmax_t type_max_len; // - максимальная длинна типа | для выравнивания
    uintmax_t name_max_len; // - максимальная длинна имени | для выравнивания

    char *out_buff;          // - указатель на буфер вывода
    uintmax_t out_ofset;     // - указатель на конец строки
    char *data_build;        // - дата сборки
    char *time_build;        // - время сборки
    char *proj;              // - имя проекта
    char *projpath;          // - папка проекта
    char *compiler;
    uintmax_t curnum;        // - номер текущего вывода
    uintmax_t absnum;        // - номер вывода без учета фильтрации
    uintmax_t tiksec;        // - время от старта программы, в секундах
} logger_variables;

static logger_variables logger_variables_global[1] = {{LOGGER_FALSE, LOGGER_FALSE}};

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

logger_format_mas *mas_opt(const char *format, logger_format_mas *mas_opt, uintmax_t *num_token);
void logger_build(const char *format,
                  logger_format_mas *mas_opt,
                  uintmax_t *num_token,
                  uintmax_t *count,
                  char *file,
                  uintmax_t *line,
                  const char *func,
                  uintmax_t type,
                  uintmax_t name,
                  const char *mesg,
                  ...);
void format_build_str(logger_format_mas *mas_opt, const char *buff_orig);
void format_build_num(logger_format_mas *mas_opt, uintmax_t *buff_orig);
void style_build(void);
void logger_out(void);
// // END // DECLARATION
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /*YAYA_LOGGER_H_*/
