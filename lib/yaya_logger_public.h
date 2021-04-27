#ifndef YAYA_LOGGER_STRUCT_H_
#define YAYA_LOGGER_STRUCT_H_

#include <stdint.h>

#define LOGGER_TRUE                        (1 == 1)
#define LOGGER_FALSE                       (!LOGGER_TRUE)

#define LOGGER_FLAG(x,  sign)              (sign)(UINTMAX_C(1) << ((uintmax_t)(x)))
#define LOGGER_FLAG_ALL(sign)              (sign)(UINTMAX_C(0) - UINTMAX_C(1))
#define LOGGER_FLAG_NUL(sign)              (sign)(UINTMAX_C(0))

#define LOGGER_FLAG_T_GENERATE(num)        LOGGER_FLAG(num, ___l1_type)
#define LOGGER_FLAG_T_ALL                  LOGGER_FLAG_ALL (___l1_type)
#define LOGGER_FLAG_T_NUL                  LOGGER_FLAG_NUL (___l1_type)

#define LOGGER_FLAG_N_GENERATE(num)        LOGGER_FLAG(num, ___l2_type)
#define LOGGER_FLAG_N_ALL                  LOGGER_FLAG_ALL (___l2_type)
#define LOGGER_FLAG_N_NUL                  LOGGER_FLAG_NUL (___l2_type)

#define LOGGER_FILTER_GENERATE(NAME)       {NAME, #NAME }

#define LOGGER_TOKEN_GENERATE_ENUM(TOKEN)  LEF_##TOKEN


typedef enum {
    LOGGER_TOKEN_GENERATE_ENUM(TOK),          /* токен формата токена */
    LOGGER_TOKEN_GENERATE_ENUM(SPE),          /* токен формата вывода, модификатор*/
    LOGGER_TOKEN_GENERATE_ENUM(SEP),          /* токен формата вывода, разделитель */
    LOGGER_TOKEN_GENERATE_ENUM(HID),          /* токен формата вывода, скрыватель */
    LOGGER_TOKEN_GENERATE_ENUM(CAT),          /* токен формата соеденения */
    LOGGER_TOKEN_GENERATE_ENUM(STR),          /* токен формата текста */

    LOGGER_TOKEN_GENERATE_ENUM(BEG),          /* открывающий токен */

    LOGGER_TOKEN_GENERATE_ENUM(file),         /* имя файла */
    LOGGER_TOKEN_GENERATE_ENUM(line),         /* номер строчки*/
    LOGGER_TOKEN_GENERATE_ENUM(func),         /* имя функции */
    LOGGER_TOKEN_GENERATE_ENUM(type),         /* тип сообщения */
    LOGGER_TOKEN_GENERATE_ENUM(name),         /* имя сообщения*/
    LOGGER_TOKEN_GENERATE_ENUM(mesg),         /* тело сообщения */

    LOGGER_TOKEN_GENERATE_ENUM(count),        /* номер сообщения, на основе __COUNTER__ */
    LOGGER_TOKEN_GENERATE_ENUM(curnum),       /* номер выведенного сообщения */
    LOGGER_TOKEN_GENERATE_ENUM(absnum),       /* номер сообщения без учета фильтрации */

    LOGGER_TOKEN_GENERATE_ENUM(short_path),   /* короткий путь */
    LOGGER_TOKEN_GENERATE_ENUM(full_path),    /* полный путь */

    LOGGER_TOKEN_GENERATE_ENUM(data_build),   /* дата компиляции */
    LOGGER_TOKEN_GENERATE_ENUM(time_build),   /* время компиляции */
    LOGGER_TOKEN_GENERATE_ENUM(data_curent),  /* дата сообщения */
    LOGGER_TOKEN_GENERATE_ENUM(time_curent),  /* время сообщения */

    LOGGER_TOKEN_GENERATE_ENUM(prog),         /* название программы */
    LOGGER_TOKEN_GENERATE_ENUM(prog_v),       /* версия программы */
    LOGGER_TOKEN_GENERATE_ENUM(prog_p),       /* расположение программы */
    LOGGER_TOKEN_GENERATE_ENUM(proj),         /* название проекта */
    LOGGER_TOKEN_GENERATE_ENUM(compiler),     /* название компилятора */
    LOGGER_TOKEN_GENERATE_ENUM(compiler_v),   /* версия компилятора */

    LOGGER_TOKEN_GENERATE_ENUM(tik_core),     /* счетчик тактов процессора */
    LOGGER_TOKEN_GENERATE_ENUM(tik_sec),      /* счетчик секунд от старта */
    LOGGER_TOKEN_GENERATE_ENUM(tic_rtos),     /* счетчик rtos */
    LOGGER_TOKEN_GENERATE_ENUM(tik_unix),     /* счетчик времени в формате UNIX*/

    LOGGER_TOKEN_GENERATE_ENUM(type_filter),  /* вывод настроек фильтрации типа */
    LOGGER_TOKEN_GENERATE_ENUM(name_filter),  /* вывод настроек фильтрации имени */
    LOGGER_TOKEN_GENERATE_ENUM(type_mask),    /* вывод настроек фильтрации типа как бинарную маску */
    LOGGER_TOKEN_GENERATE_ENUM(name_mask),    /* вывод настроек фильтрации имени как бинарную маску */
    LOGGER_TOKEN_GENERATE_ENUM(type_list),    /* имена всех типов сообщений */
    LOGGER_TOKEN_GENERATE_ENUM(name_list),    /* имена всех названий сообщений */

    LOGGER_TOKEN_GENERATE_ENUM(alignl),       /* выравнивание при переносе */
    LOGGER_TOKEN_GENERATE_ENUM(aliggt),       /* выравнивание принудительное */

    LOGGER_TOKEN_GENERATE_ENUM(debug),        /* отладочная информация */

    LOGGER_TOKEN_GENERATE_ENUM(END)           /* замыкающий токен */
} ___logger_token_id;


typedef intmax_t  ___l1_type;
typedef uintmax_t ___l2_type;


typedef enum{
    LE_OK,
    LE_ERR,
    LE_ALLOC
} logger_error;


typedef enum {
    LS_STDOUT,
    LS_STDERR,
    LS_STDFILE,
    LS_STDLOG,
    LS_STDNET,
    LS_STDBUF,
    LS_STDCSV
} logger_streams;


typedef enum {
    LSM_NONE,
    LSM_STRAIGHT,
    LSM_ITALIC,
    LSM_LIGHT,
    LSM_BOLD
} logger_style_mode;


typedef struct logger_define {
    char *prog;               // - название программы
    char *proj;               // - название проекта
    char *version;            // - версия программы
    char *compiler;           // - версия компилятора
    char *data_build;         // - дата сборки
    char *time_build;         // - время сборки
    char *projpath;           // - папка проекта
    char *compilerversion;
} logger_define;


typedef struct logger_style {
    const uintmax_t token;
    const uintmax_t font[3];
    const uintmax_t back[3];
    const uintmax_t mode;
} logger_style;


typedef struct logger_filter {
    const uintmax_t flag;
    const char      *name;
} logger_filter;


typedef struct logger_setting {
    char *head_format;
    char *logs_format;
    char *atom_format;
    char *gerr_format;

    ___l1_type type;
    ___l2_type name;
    uintmax_t  style;
    uintmax_t  stream;
    char      *out_buff;
} logger_setting;

#endif /*YAYA_LOGGER_STRUCT_H_*/
