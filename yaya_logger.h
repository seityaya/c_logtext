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

/*
$prog - название програмы
$proj - название проекта
$projpath - расположение проекта
$version - версия
$data_assembly - дата компиляции
$time_assembly - время компиляции
$seed - сид запуска ГПСЧ
$compiler - версия компилятора
*
$curnum - номер выведеного сообщения
$absnum - номер сообщения без учета фильтрации
$count - номер сообщения, на основе __COUNTER__
$tik - счетчик тактов процесора
$tik_rtos - счетчик rtos
$tik_unix - счетчик секунд
$type - тип сообщения
$name - имя сообщения
$data - дата сообщения
$time - время сообщения
$fullpath - полный путь к файлу, из которого сообщение
$path - короткий путь к файлу, из которого сообщение
$line - номер строки
$func - имя функции
$mesage - тело сообщения
*
\n - перевод строки
$align - выравнивание при переносе
$alig1 - выравнивание принудительное, выравнивание идет по двум меткам
$$ - вывод знака $
*/

#define NUL 0 // NULL

typedef struct {
    const intmax_t id;
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
    L_MAIN = FLAG(13),
    L_FUNC = FLAG(14),
    L_LOGGER = FLAG(15),
    L_HEAD = FLAG(16),
    L_TEST = FLAG(17),
    L_ALL = FLAG_ALL
} logger_enum;

#define LOGGER_TYPE_NUM 19

#define LOGER_LIST(NAME) \
    { NAME, #NAME }

static logger_list logger_type_standart[LOGGER_TYPE_NUM] = {{L_NUL, "NUL"},
                                                            {L_VOID, "VOID"},
                                                            {L_INFO, "INFO"},
                                                            {L_ERROR, "ERROR"},
                                                            {L_WARNING, "WARNING"},
                                                            {L_TODO, "TODO"},
                                                            {L_FIXMI, "FIXMI"},
                                                            {L_DEBUG, "DEBUG"},
                                                            {L_RELISE, "RELISE"},
                                                            {L_TRASE, "TRASE"},
                                                            {L_WARN, "WARN"},
                                                            {L_FATAL, "FATAL"},
                                                            {L_BEGF, "BEGF"},
                                                            {L_ENDF, "ENDF"},
                                                            {L_MAIN, "MAIN"},
                                                            {L_FUNC, "FUNC"},
                                                            {L_LOGGER, "LOGGER"},
                                                            LOGER_LIST(L_TEST),
                                                            {L_ALL, "ALL"}};
typedef enum
{
    L_STDOUT,
    L_STDERR,
    L_STDFILE,
    L_STDLOG,
    L_STDNET
} logger_streams;

typedef struct logger_seting {
    char *format_head;
    char *format_logs;
    intmax_t stream;
    intmax_t type;
    intmax_t title;
} logger_setting;

static logger_setting logger_setting_standart = {"$prog $version $data_assembly $time_assembly $seed",
                                                 "$actnum $absnum $type $name $data $time $path $line $func $mesage",
                                                 L_STDOUT,
                                                 L_INFO,
                                                 L_ALL};

typedef struct logger_style {
    intmax_t t;
} logger_style;

struct logger_define {
    uint32_t seed;
    char *prog;
    char *proj;
    char *version;
    char *data_assembly;
    char *time_assembly;
    char *projpath;
    uint32_t curnum;
    uint32_t absnum;
    char *type;
    char *name;
    char *data;
    char *time;
    char *fullpath;
    char *path;
    char *line;
    char *func;
    char *mesage;
};

void yaya_log_init(logger_list *type, logger_list *name, logger_setting *setting, logger_style *style) {}

void yaya_log_func(char *data,
                   char *time,
                   char *file,
                   uintmax_t line,
                   uintmax_t count,
                   const char *func,
                   uintmax_t type,
                   uintmax_t name,
                   char *mes,
                   ...) {
    printf("Data   : %s\nTime   : %s\nCount  : %ld\nLine   : %ld\nFile   : %s\nFunc   : %s\n",
           data,
           time,
           count,
           line,
           file,
           func);

    char temp[1000];

    printf("Type N : %ld\n", type);
    temp[0] = '\0';
    for (uintmax_t i = 0; i < LOGGER_TYPE_NUM - 1; i++) {
        if (BIT_GET(type, i)) {
            strcat(temp, logger_type_standart[i + 1].name);
            strcat(temp, " ");
        }
    }
    printf("Type L : %s\n", temp);

    temp[0] = '\0';
    printf("Name N : %ld\n", name);
    for (uintmax_t i = 0; i < LOGGER_TYPE_NUM - 1; i++) {
        if (BIT_GET(name, i)) {
            strcat(temp, logger_type_standart[i + 1].name);
            strcat(temp, " ");
        }
    }
    printf("Name L : %s\n", temp);
    printf("Messg  : %s\n", mes);
    printf("Args   : ");
    va_list list;
    va_start(list, mes);
    vprintf(mes, list);
    va_end(list);
    printf("\n\n");
}

#define yaya_log_exsempl(type, name, mes, ...) \
    yaya_log_func(__DATE__, __TIME__, __FILE__, __LINE__, __COUNTER__, __FUNCTION__, type, name, mes, ##__VA_ARGS__)

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define P(x) printf("# -> %s \n", #x)

#define log_____() logger_test(__LINE__, __COUNTER__, NUL, NUL, NUL, NUL)   //0
#define log_A___(A) logger_test(__LINE__, __COUNTER__, A, NUL, NUL, NUL)    //1
#define log_AB__(A, B) logger_test(__LINE__, __COUNTER__, A, B, NUL, NUL)   //2
#define log_A_C_(A, C) logger_test(__LINE__, __COUNTER__, A, NUL, C, NUL)   //2
#define log_ABC_(A, B, C) logger_test(__LINE__, __COUNTER__, A, B, C, NUL)  //3
#define log_A_CD(A, C, D) logger_test(__LINE__, __COUNTER__, A, NUL, C, D)  //3
#define log_ABCD(A, B, C, D) logger_test(__LINE__, __COUNTER__, A, B, C, D) //4

#define log_0() log_____()
#define log_1(A) log_A___(A)
//#define log_2(A, B) log_AB__(A, B)
//#define log_2(A, B) _Generic((A, B), (int, int) : log_AB__(A, B), (int, char *) : log_A_C_(A, B))
#define log_2_BC(A, BC) _Generic((BC), char * : log_A_C_(A, BC), int : log_AB__(A, BC))
#define log_2(A, BC) _Generic((A), default : log_2_BC(A, BC))
#define log_3(A, B, C) log_ABC_(A, B, C)
#define log_4(A, B, C, ...) log_ABCD(A, B, C, ##__VA_ARGS__)

#define XXX_0() log_0()
#define XXX_1(A) log_1(A)
#define XXX_2(A, B) log_2(A, B)
#define XXX_3(A, B, C) log_3(A, B, C)
#define XXX_4(A, B, C, D) log_4(A, B, C, D)

#define XXX_X(x, A, B, C, D, FUNC, ...) FUNC

#define log(...) \
    XXX_X(, \
          ##__VA_ARGS__, \
          XXX_4(__VA_ARGS__), \
          XXX_3(__VA_ARGS__), \
          XXX_2(__VA_ARGS__), \
          XXX_1(__VA_ARGS__), \
          XXX_0(__VA_ARGS__))

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define VA_NARGS_IMPL(_1, _2, N, ...) N
//#define VA_NARGS(...) VA_NARGS_IMPL(__VA_ARGS__, _2_arg, _3_arg)

//#define LOG_IMPL2(suffix, ...) log_##suffix(__VA_ARGS__)
//#define LOG_IMPL(suffix, ...) LOG_IMPL2(suffix, __VA_ARGS__)
//#define log(...) LOG_IMPL(VA_NARGS(__VA_ARGS__), __VA_ARGS__)

//#define VA_NUM_ARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N
//#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1)

#endif /*YAYA_LOGGER_H_*/
