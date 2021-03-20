#ifndef YAYA_LOGGER_STRUCT_H_
#define YAYA_LOGGER_STRUCT_H_

#include <stdint.h>
#include "yaya_logger_macro.h"

typedef intmax_t  ___l1_type;
typedef uintmax_t ___l2_type;


typedef enum {
    LS_STDOUT,
    LS_STDERR,
    LS_STDFILE,
    LS_STDLOG,
    LS_STDNET,
    LS_STDBUF,
    LS_STDCSV
} ___logger_streams;


typedef enum {
    LSM_NONE,
    LSM_STRAIGHT,
    LSM_ITALIC,
    LSM_LIGHT,
    LSM_BOLD
} ___logger_style_mode;


#define LFS_LEF 1
#define LFS_RIG 2
#define LFS_NUL 3


typedef struct logger_define {
        uintmax_t seed; // - начальные настройки ГСПЧ
        char *prog;     // - название программы
        char *proj;     // - название проекта
        char *version;  // - версия программы
        char *compiler; // - версия компилятора
        char *data_build;     // - дата сборки
        char *time_build;     // - время сборки
        char *projpath;       // - папка проекта
        char *compilerversion;
        uintmax_t tiksec; // - время от старта программы, в секундах
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
        uintmax_t  stream;
        uintmax_t  style;
} logger_setting;


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
        void (*func)(LOGGER_FUNC_PARAM); /*функция токена*/
} ___logger_token_func;


void ___logger_pars (logger *lvg, const char *format, ___logger_tokens** tokens);
void ___logger_format_str(logger *lvg, ___logger_token_mas *mas_opt, const char *buff_orig);
void ___logger_format_num(logger *lvg, ___logger_token_mas *mas_opt, uintmax_t buff_orig);

void ___logger_styles(logger *lvg);
void ___logger_out(logger *lvg);

void ___count_num(___logger_filters *filter) ;
void ___free_tokens(___logger_tokens* tokens);

#endif /*YAYA_LOGGER_STRUCT_H_*/
