#ifndef YAYA_LOGGER_FORMAT_H_
#define YAYA_LOGGER_FORMAT_H_

#include <string.h>

#include "yaya_logger_macro.h"
#include "yaya_logger_struct.h"

LOGGER_TOKEN_GENERATE_FUNC(str);
LOGGER_TOKEN_GENERATE_FUNC(file);
LOGGER_TOKEN_GENERATE_FUNC(line);
LOGGER_TOKEN_GENERATE_FUNC(func);
LOGGER_TOKEN_GENERATE_FUNC(type);
LOGGER_TOKEN_GENERATE_FUNC(name);
LOGGER_TOKEN_GENERATE_FUNC(mesg);

LOGGER_TOKEN_GENERATE_FUNC(count);      /*<<<*/
LOGGER_TOKEN_GENERATE_FUNC(curnum);
LOGGER_TOKEN_GENERATE_FUNC(absnum);

LOGGER_TOKEN_GENERATE_FUNC(short_path);
LOGGER_TOKEN_GENERATE_FUNC(full_path);

LOGGER_TOKEN_GENERATE_FUNC(data_build);
LOGGER_TOKEN_GENERATE_FUNC(time_build);
LOGGER_TOKEN_GENERATE_FUNC(data_curent);
LOGGER_TOKEN_GENERATE_FUNC(time_curent);

LOGGER_TOKEN_GENERATE_FUNC(prog);
LOGGER_TOKEN_GENERATE_FUNC(prog_v);
LOGGER_TOKEN_GENERATE_FUNC(prog_p);
LOGGER_TOKEN_GENERATE_FUNC(proj);
LOGGER_TOKEN_GENERATE_FUNC(compiler);
LOGGER_TOKEN_GENERATE_FUNC(compiler_v);

LOGGER_TOKEN_GENERATE_FUNC(tik_core);
LOGGER_TOKEN_GENERATE_FUNC(tik_sec);
LOGGER_TOKEN_GENERATE_FUNC(tic_rtos);
LOGGER_TOKEN_GENERATE_FUNC(tik_unix);

LOGGER_TOKEN_GENERATE_FUNC(type_filter);
LOGGER_TOKEN_GENERATE_FUNC(name_filter);
LOGGER_TOKEN_GENERATE_FUNC(type_mask);
LOGGER_TOKEN_GENERATE_FUNC(name_mask);
LOGGER_TOKEN_GENERATE_FUNC(type_list);
LOGGER_TOKEN_GENERATE_FUNC(name_list);

LOGGER_TOKEN_GENERATE_FUNC(seed);

LOGGER_TOKEN_GENERATE_FUNC(alignl);
LOGGER_TOKEN_GENERATE_FUNC(aliggt);

LOGGER_TOKEN_GENERATE_FUNC(debug);

typedef enum {
    LOGGER_TOKEN_GENERATE_ENUM(TOK),          /* токен формата токена */
    LOGGER_TOKEN_GENERATE_ENUM(SPE),          /* токен формата вывода, модификатор*/
    LOGGER_TOKEN_GENERATE_ENUM(SEP),          /* токен формата вывода, разделитель */
    LOGGER_TOKEN_GENERATE_ENUM(HID),          /* токен формата вывода, скрыватель */
    LOGGER_TOKEN_GENERATE_ENUM(CAT),          /* токен формата соеденения */

    LOGGER_TOKEN_GENERATE_ENUM(BEG),          /* открывающий токен */

    LOGGER_TOKEN_GENERATE_ENUM(str),          /* токен формата текста */
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

    LOGGER_TOKEN_GENERATE_ENUM(seed),         /* сид запуска ГПСЧ */

    LOGGER_TOKEN_GENERATE_ENUM(alignl),       /* выравнивание при переносе */
    LOGGER_TOKEN_GENERATE_ENUM(aliggt),       /* выравнивание принудительное */

    LOGGER_TOKEN_GENERATE_ENUM(debug),       /* выравнивание принудительное */

    LOGGER_TOKEN_GENERATE_ENUM(END)          /* замыкающий токен */
} ___logger_token_id;

static ___logger_token ___logger_token_list[LEF_END] = {
    {LEF_TOK, "$", NULL},
    {LEF_SPE, "%", NULL},
    {LEF_SEP, ".", NULL},
    {LEF_HID, ":", NULL},
    {LEF_CAT, "_", NULL},

    {LEF_BEG, NULL, NULL},

    LOGGER_TOKEN_GENERATE_ST(str),
    LOGGER_TOKEN_GENERATE_ST(file),
    LOGGER_TOKEN_GENERATE_ST(line),
    LOGGER_TOKEN_GENERATE_ST(func),
    LOGGER_TOKEN_GENERATE_ST(type),
    LOGGER_TOKEN_GENERATE_ST(name),
    LOGGER_TOKEN_GENERATE_ST(mesg),

    LOGGER_TOKEN_GENERATE_ST(count),
    LOGGER_TOKEN_GENERATE_ST(curnum),
    LOGGER_TOKEN_GENERATE_ST(absnum),

    LOGGER_TOKEN_GENERATE_ST(short_path),
    LOGGER_TOKEN_GENERATE_ST(full_path),

    LOGGER_TOKEN_GENERATE_ST(data_build),
    LOGGER_TOKEN_GENERATE_ST(time_build),
    LOGGER_TOKEN_GENERATE_ST(data_curent),
    LOGGER_TOKEN_GENERATE_ST(time_curent),

    LOGGER_TOKEN_GENERATE_ST(prog),
    LOGGER_TOKEN_GENERATE_ST(prog_v),
    LOGGER_TOKEN_GENERATE_ST(prog_p),
    LOGGER_TOKEN_GENERATE_ST(proj),
    LOGGER_TOKEN_GENERATE_ST(compiler),
    LOGGER_TOKEN_GENERATE_ST(compiler_v),

    LOGGER_TOKEN_GENERATE_ST(tik_core),
    LOGGER_TOKEN_GENERATE_ST(tik_sec),
    LOGGER_TOKEN_GENERATE_ST(tic_rtos),
    LOGGER_TOKEN_GENERATE_ST(tik_unix),

    LOGGER_TOKEN_GENERATE_ST(type_filter),
    LOGGER_TOKEN_GENERATE_ST(name_filter),
    LOGGER_TOKEN_GENERATE_ST(type_mask),
    LOGGER_TOKEN_GENERATE_ST(name_mask),
    LOGGER_TOKEN_GENERATE_ST(type_list),
    LOGGER_TOKEN_GENERATE_ST(name_list),

    LOGGER_TOKEN_GENERATE_ST(seed),

    LOGGER_TOKEN_GENERATE_ST(alignl),
    LOGGER_TOKEN_GENERATE_ST(aliggt),

    LOGGER_TOKEN_GENERATE_ST(debug),

    {LEF_END, NULL, NULL}
};

#endif /*YAYA_LOGGER_FORMAT_H_*/
