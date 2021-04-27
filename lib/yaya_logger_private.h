#ifndef YAYA_LOGGER_PRIVATE_H
#define YAYA_LOGGER_PRIVATE_H

#include <stdarg.h>
#include <stdlib.h>

#include "yaya_logger_public.h"

#define LOGGER_BIT_GET(x, n)        ((uintmax_t)(x) & (UINTMAX_C(1) << (uintmax_t)(n)))

#define LOGGER_TOKEN_GENERATE_FUNC(TOKEN)  logger_error ___logger_func_##TOKEN(LOGGER_FUNC_PARAM)
#define LOGGER_TOKEN_GENERATE_ST(TOKEN)    { LEF_##TOKEN, #TOKEN, ___logger_func_##TOKEN }

#define LFS_LEF 1
#define LFS_RIG 2
#define LFS_NUL 3

#define LOGGER_FUNC_PARAM \
    logger *lvg, \
    const char *format, \
    ___logger_token_mas *mas_opt, \
    uintmax_t count, \
    const char *file, \
    uintmax_t line, \
    const char *func, \
    const char* debug, \
    ___l1_type type, \
    ___l2_type name, \
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
    (void*)debug, \
    (void*)type, \
    (void*)name, \
    (void*)mes, \
    (void*)mes_list


typedef struct ___logger_token_specifiers { /*хранение спецификаторов*/
    uintmax_t beg; /*начало спецификатора*/
    uintmax_t end; /*конец спецификатора*/
    uintmax_t lef; /*смещение слева*/
    uintmax_t rig; /*смещение справа*/
    uintmax_t lfs; /*сторона скрытия*/
} ___logger_token_specifiers;


typedef struct ___logger_token_mas {    /*хранение токенов*/
    uintmax_t id;     /*тип токена*/
    uintmax_t beg;    /*начало токена*/
    uintmax_t end;    /*конец токена*/
    uintmax_t beglog; /*начало токена вывода*/
    uintmax_t endlog; /*конец токена вывода*/
    ___logger_token_specifiers *spe;
} ___logger_token_mas;


typedef struct ___logger_tokens{
    uintmax_t            num_token;
    ___logger_token_mas *mas_opt;
    uintmax_t            curnum;
}___logger_tokens;


typedef struct ___logger_filters {
    uintmax_t num;      // - количество типов
    logger_filter *ptr; // - указатель на список типов
} ___logger_filters;


typedef struct logger {
    logger_setting *psett;
    logger_style   *pstyl;
    logger_define  *pdefn;

    ___logger_filters type;
    ___logger_filters name;

    ___logger_tokens *logs;
    ___logger_tokens *head;
    ___logger_tokens *atom;
    ___logger_tokens *gerr;

    uintmax_t tmp_buff_size;
    char      *tmp_buff;  // - указатель на времменый буфер
    uintmax_t out_buff_size;
    char      *out_buff;  // - указатель на буфер вывода
    intmax_t  out_offset; // - указатель на конец строки

    uintmax_t curnum; // - номер текущего вывода
    uintmax_t absnum; // - номер вывода без учета фильтрации
} logger;

typedef struct ___logger_token_func {      /*список токенов*/
        const uintmax_t id;        /*идентификатор*/
        const char *name;          /*текстовое представление ключей*/
        logger_error (*func)(LOGGER_FUNC_PARAM); /*функция токена*/
} ___logger_token_func;

logger_error ___logger_pars (logger *lvg, const char *format, ___logger_tokens** tokens);
logger_error ___format_build_str(logger *lvg, ___logger_token_mas *mas_opt, const char *buff_orig);
logger_error ___format_build_num(logger *lvg, ___logger_token_mas *mas_opt, uintmax_t buff_orig);

logger_error ___logger_styles(logger *lvg);
logger_error ___logger_out(logger *lvg);

logger_error ___count_num(___logger_filters *filter) ;
logger_error ___free_tokens(___logger_tokens* tokens);


LOGGER_TOKEN_GENERATE_FUNC(STR);
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

LOGGER_TOKEN_GENERATE_FUNC(alignl);
LOGGER_TOKEN_GENERATE_FUNC(aliggt);

LOGGER_TOKEN_GENERATE_FUNC(debug);

static ___logger_token_func ___logger_token_list[LEF_END + 1] = {
    {LEF_TOK, "$", NULL},
    {LEF_SPE, "%", NULL},
    {LEF_SEP, ".", NULL},
    {LEF_HID, ":", NULL},
    {LEF_CAT, "_", NULL},
    LOGGER_TOKEN_GENERATE_ST(STR),

    {LEF_BEG, NULL, NULL},

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

    LOGGER_TOKEN_GENERATE_ST(alignl),
    LOGGER_TOKEN_GENERATE_ST(aliggt),

    LOGGER_TOKEN_GENERATE_ST(debug),

    {LEF_END, NULL, NULL}
};


#endif // YAYA_LOGGER_PRIVATE_H
