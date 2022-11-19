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
#include <malloc.h>

#include "yaya_logger.h"

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // OPTION

/*Включить отладку формата*/
#ifndef LOGGER_DEBUG_FORMAT  /*Работает*/
#define LOGGER_DEBUG_FORMAT  LOGGER_OFF
#endif

// // END // OPTION
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    const char* generic, \
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
    (void*)generic, \
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

    ___logger_tokens *logs_f;
#if LOGGER_FORMAT_HEAD
    ___logger_tokens *head_f;
#endif
#if LOGGER_FORMAT_ATOM
    ___logger_tokens *atom_f;
#endif
#if LOGGER_FORMAT_FREE
    ___logger_tokens *free_f;
#endif
#if LOGGER_FORMAT_ERROR
    ___logger_tokens *gerr;
#endif

    uintmax_t tmp_buff_size;
    char     *tmp_buff;     // - указатель на временный буфер
    char     *out_buff;     // - указатель на буфер вывода
    intmax_t  out_offset;   // - указатель на конец строки
    uintmax_t out_buff_size;// - размер буфера

    uintmax_t curnum; // - номер текущего вывода
    uintmax_t absnum; // - номер вывода без учета фильтрации
     intmax_t recnum; // - номер рекурсивного вызова

    intmax_t memory_total;
    intmax_t memory_usage;
    intmax_t memory_count_new;
    intmax_t memory_count_del;
    intmax_t memory_count_res;

    FILE     *stream;
} ___logger;

typedef struct ___logger_token_func {      /*список токенов*/
    const uintmax_t id;       /*идентификатор*/
    const char *name;         /*текстовое представление ключей*/
    logger_error (*func)(LOGGER_FUNC_PARAM);/*функция токена*/
} ___logger_token_func;


void logger_memory_new(___logger *lvg, void **ptr, void *old_ptr, size_t new_size);
void logger_memory_del(___logger *lvg, void *ptr);

logger_error logger_pars  (___logger *lvg, const char *format, ___logger_tokens** tokens);
logger_error logger_out   (___logger *lvg);

#if LOGGER_STYLE
logger_error logger_styles(___logger *lvg);
#endif

size_t       format_build_cpy(char *restrict dest, const char *restrict src, size_t full_size_dst);
logger_error format_build_str(___logger *lvg, ___logger_token_mas *mas_opt, const char *buff_orig);
logger_error format_build_num(___logger* lvg, ___logger_token_mas* mas_opt, uintmax_t buff_orig);

#define LIST_OF_TOKEN \
    X(count)           /* ARG1 номер сообщения\ на основе __COUNTER__ */\
    X(file)            /* ARG2 имя файла */\
    X(line)            /* ARG3 номер строчки */\
    X(func)            /* ARG4 имя функции */\
    X(generic)         /* ARG5 отладочная информация макроса _Generic*/\
    X(type)            /* ARG6 тип сообщения */\
    X(name)            /* ARG7 имя сообщения*/\
    X(mesg)            /* ARG8 тело сообщения */\
    \
    X(curnum)          /* номер выведенного сообщения */\
    X(absnum)          /* номер сообщения без учета фильтрации */\
    X(recnum)          /* номер в рекурсивном вызове +N 0 -N*/\
    X(rectab)          /* отступ в рекурсивном вызове*/\
    \
    X(data_build)      /* дата компиляции */\
    X(time_build)      /* время компиляции */\
    X(data_curent)     /* дата сообщения */\
    X(time_curent)     /* время сообщения */\
    \
    X(type_filter)     /* вывод настроек фильтрации типа */\
    X(name_filter)     /* вывод настроек фильтрации имени */\
    X(type_mask)       /* вывод настроек фильтрации типа как бинарную маску */\
    X(name_mask)       /* вывод настроек фильтрации имени как бинарную маску */\
    X(type_list)       /* имена всех типов сообщений */\
    X(name_list)       /* имена всех названий сообщений */\
    \
    X(proj)            /* название проекта */\
    X(prog)            /* название программы */\
    X(version)         /* версия программы */\
    \
    X(comp_v)          /* версия компилятора */\
    X(lang_v)          /* версия языка */\
    \
    X(stats)           /* отладочная информация выделения памяти*/\
    \
    X(alignl)          /* TODO выравнивание при переносе */\
    X(aliggt)          /* TODO выравнивание принудительное */\


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
