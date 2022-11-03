//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#ifndef YAYA_LOGGER_PRIVATE_H
#define YAYA_LOGGER_PRIVATE_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "yaya_logger.h"

#if LOGGER_STATIC
#define malloc XXX_malloc_XXX
#define calloc XXX_calloc_XXX
#define realloc XXX_realloc_XXX
#define free XXX_free_XXX
#endif

#define LOGGER_BIT_GET(x, n)        ((uintmax_t)(x) & (UINTMAX_C(1) << (uintmax_t)(n)))

#define LOGGER_TOKEN_GENERATE_FUNC(TOKEN)  logger_error ___logger_func_##TOKEN(LOGGER_FUNC_PARAM)
#define LOGGER_TOKEN_GENERATE_ST(TOKEN)    { LEF_##TOKEN, #TOKEN, ___logger_func_##TOKEN }

#define LFS_LEF 1
#define LFS_RIG 2
#define LFS_NUL 3

#define LTT_STR 0
#define LTT_NUM 1

#define LOGGER_FUNC_PARAM \
    ___logger *lvg, \
    const char *format, \
    ___logger_token_mas *mas_opt, \
    uintmax_t count, \
    const char *file, \
    uintmax_t line, \
    const char *func, \
    const char* debug_generic, \
    logger_l1_type type, \
    logger_l2_type name, \
    const char *mes, \
    va_list mes_list

#define LOGGER_FUNC_UNUSED \
    (void*)lvg, \
    (void*)format, \
    (void*)mas_opt, \
    (void*)count, \
    (void*)file, \
    (void*)line, \
    (void*)func, \
    (void*)debug_generic, \
    (void*)type, \
    (void*)name, \
    (void*)mes, \
    (void*)mes_list


typedef struct ___logger_token_specifiers { /*хранение спецификаторов*/
    uintmax_t beg;/*начало спецификатора*/
    uintmax_t end;/*конец спецификатора*/
    uintmax_t lef;/*смещение слева*/
    uintmax_t rig;/*смещение справа*/
    uintmax_t lfs;/*сторона скрытия*/
} ___logger_token_specifiers;


typedef struct ___logger_token_mas {    /*хранение токенов*/
    uintmax_t id;    /*вид токена*/
    uintmax_t type;  /*тип токена*/
    uintmax_t beg;   /*начало токена*/
    uintmax_t end;   /*конец токена*/
    uintmax_t beglog;/*начало токена вывода*/
    uintmax_t endlog;/*конец токена вывода*/
    ___logger_token_specifiers *spe;
} ___logger_token_mas;


typedef struct ___logger_tokens{
    uintmax_t            num_token;
    ___logger_token_mas *mas_opt;
    uintmax_t            curnum;
}___logger_tokens;


typedef struct ___logger_filters {
    uintmax_t num;     // - количество типов
    logger_filter *ptr;// - указатель на список типов
} ___logger_filters;


typedef struct ___logger {
    logger_setting *psett;
    logger_style   *pstyl;
    logger_define  *pdefn;

    ___logger_filters type;
    ___logger_filters name;

    ___logger_tokens *logs;
#if LOGGER_HEAD
    ___logger_tokens *head;
#endif
#if LOGGER_ATOM
    ___logger_tokens *atom;
#endif
#if LOGGER_ERROR
    ___logger_tokens *gerr;
#endif

    uintmax_t tmp_buff_size;
    char     *tmp_buff;     // - указатель на временный буфер
    char     *out_buff;     // - указатель на буфер вывода
    intmax_t  out_offset;   // - указатель на конец строки
    uintmax_t out_buff_size;// - размер буфера

    uintmax_t curnum;// - номер текущего вывода
    uintmax_t absnum;// - номер вывода без учета фильтрации

    FILE     *stream;
} ___logger;


typedef struct ___logger_token_func {      /*список токенов*/
    const uintmax_t id;       /*идентификатор*/
    const char *name;         /*текстовое представление ключей*/
    logger_error (*func)(LOGGER_FUNC_PARAM);/*функция токена*/
} ___logger_token_func;


logger_error logger_pars  (___logger *lvg, const char *format, ___logger_tokens** tokens);

#if LOGGER_OUT
logger_error logger_out   (___logger *lvg);
#endif

#if LOGGER_STYLE
logger_error logger_styles(___logger *lvg);
#endif

logger_error format_build_str(___logger *lvg, ___logger_token_mas *mas_opt, const char *buff_orig);
logger_error format_build_num(___logger* lvg, ___logger_token_mas* mas_opt, uintmax_t buff_orig);

#define LIST_OF_TOKEN \
    X(file)            /* имя файла */\
    X(line)            /* номер строчки */\
    X(func)            /* имя функции */\
    X(type)            /* тип сообщения */\
    X(name)            /* имя сообщения*/\
    X(mesg)            /* тело сообщения */\
    X(count)           /* номер сообщения\ на основе __COUNTER__ */\
    X(curnum)          /* номер выведенного сообщения */\
    X(absnum)          /* номер сообщения без учета фильтрации */\
    X(short_path)      /* короткий путь */\
    X(full_path)       /* полный путь */\
    X(data_build)      /* дата компиляции */\
    X(time_build)      /* время компиляции */\
    X(data_curent)     /* дата сообщения */\
    X(time_curent)     /* время сообщения */\
    X(prog)            /* название программы */\
    X(prog_v)          /* версия программы */\
    X(prog_p)          /* расположение программы */\
    X(proj)            /* название проекта */\
    X(compiler)        /* название компилятора */\
    X(compiler_v)      /* версия компилятора */\
    X(tik_core)        /* счетчик тактов процессора */\
    X(tik_sec)         /* счетчик секунд от старта */\
    X(tic_rtos)        /* счетчик rtos */\
    X(tik_unix)        /* счетчик времени в формате UNIX*/\
    X(type_filter)     /* вывод настроек фильтрации типа */\
    X(name_filter)     /* вывод настроек фильтрации имени */\
    X(type_mask)       /* вывод настроек фильтрации типа как бинарную маску */\
    X(name_mask)       /* вывод настроек фильтрации имени как бинарную маску */\
    X(type_list)       /* имена всех типов сообщений */\
    X(name_list)       /* имена всех названий сообщений */\
    X(alignl)          /* выравнивание при переносе */\
    X(aliggt)          /* выравнивание принудительное */\
    X(debug_generic)   /* отладочная информация макроса _Generic*/\
    X(debug_stats)     /* отладочная информация выделения памяти*/


LOGGER_TOKEN_GENERATE_FUNC(STR);
#define X(name) LOGGER_TOKEN_GENERATE_FUNC(name);
LIST_OF_TOKEN
#undef X


typedef enum ___logger_token_id {
    LOGGER_TOKEN_GENERATE_ENUM(TOK),          /* токен формата токена */
    LOGGER_TOKEN_GENERATE_ENUM(SPE),          /* токен формата вывода, модификатор*/
    LOGGER_TOKEN_GENERATE_ENUM(SEP),          /* токен формата вывода, разделитель */
    LOGGER_TOKEN_GENERATE_ENUM(HID),          /* токен формата вывода, скрыватель */
    LOGGER_TOKEN_GENERATE_ENUM(CAT),          /* токен формата соединения */
    LOGGER_TOKEN_GENERATE_ENUM(STR),          /* токен формата текста */
    LOGGER_TOKEN_GENERATE_ENUM(BEG),          /* открывающий токен */

#define X(name) LOGGER_TOKEN_GENERATE_ENUM(name),
    LIST_OF_TOKEN
#undef X

    LOGGER_TOKEN_GENERATE_ENUM(END)           /* замыкающий токен */
} ___logger_token_id;

static ___logger_token_func ___logger_token_list[LEF_END + 1] = {
    {LEF_TOK, "$", NULL},
    {LEF_SPE, "%", NULL},
    {LEF_SEP, ".", NULL},
    {LEF_HID, ":", NULL},
    {LEF_CAT, "_", NULL},
    LOGGER_TOKEN_GENERATE_ST(STR),

    {LEF_BEG, NULL, NULL},

    #define X(name) LOGGER_TOKEN_GENERATE_ST(name),
    LIST_OF_TOKEN
    #undef X

    {LEF_END, NULL, NULL}
};

#endif // YAYA_LOGGER_PRIVATE_H
