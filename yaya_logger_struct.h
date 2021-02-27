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
    LSM_BOLD,
} ___logger_style_mode;

#define LFS_LEF 1
#define LFS_RIG 2
#define LFS_NUL 3

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


typedef struct ___logger_style {
  const uintmax_t token;
  const uintmax_t font[3];
  const uintmax_t back[3];
  const uintmax_t mode;
} ___logger_style;


typedef struct ___logger_filter {
  const uintmax_t id;
  const uintmax_t flag;
  const char *name;
} ___logger_filter;


typedef struct ___logger_seting {
  const char *head_format;
  const char *logs_format;
  const char *atom_format;

  const uintmax_t type;
  const intmax_t  name;
  const uintmax_t stream;
  const uintmax_t style;
} ___logger_setting;


typedef struct ___logger_define {
  uintmax_t seed; // - начальные настройки ГСПЧ
  char *prog;     // - название программы
  char *proj;     // - название проекта
  char *version;  // - версия программы
  char *compiler; // - версия компилятора
} ___logger_define;

typedef struct ___logger_filter_ {
  ___logger_filter *ptr; // - указатель на список типов
  uintmax_t num;      // - количество типов
} ___logger_filter_;

typedef struct ___logger {
    ___logger_filter_ type; // - список типов
    ___logger_filter_ name; // - список имен

    uintmax_t logs_num_token;       // - количество токенов в форматной строке заголовка
    ___logger_token_mas *logs_mas_opt; // - указатель на структуру со смещениями токенов логгера

    ___logger_setting *psett; // - указатель на настройки логгера
    ___logger_style *pstyl;   // - указатель на стили
    ___logger_define *pdefn;  // - указатель на переменные среды

    char *tmp_buff; // - указатель на времменый буфер
    char *out_buff; // - указатель на буфер вывода
    uintmax_t out_offset; // - указатель на конец строки
    char *data_build;     // - дата сборки
    char *time_build;     // - время сборки
    char *projpath;       // - папка проекта
    char *compilerversion;
    uintmax_t curnum; // - номер текущего вывода
    uintmax_t absnum; // - номер вывода без учета фильтрации
    uintmax_t tiksec; // - время от старта программы, в секундах
} ___logger;

typedef struct ___logger_token {      /*список токенов*/
        const uintmax_t id;        /*идентификатор*/
        const char *name;          /*текстовое представление ключей*/
        void (*func)(LOGGER_FUNC_PARAM); /*функция токена*/
} ___logger_token;



// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // LOGGER FUNC

void ___logger_pars  (___logger *lvg, const char *format, ___logger_token_mas **mas_opt, uintmax_t *num_token);
void ___logger_format(___logger *lvg, const char *format, ___logger_token_mas *mas_opt,
                      uintmax_t *num_token, uintmax_t count, char *file,
                      uintmax_t line, const char *func, ___l1_type type,
                      ___l2_type name, const char *mesg, va_list mes_list);

void ___logger_format_str(___logger *lvg, ___logger_token_mas *mas_opt, const char *buff_orig);
void ___logger_format_num(___logger *lvg, ___logger_token_mas *mas_opt, uintmax_t buff_orig);
void ___logger_styles(___logger *lvg);
void ___logger_out(___logger *lvg);

// // END // LOGGER FUNC
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /*YAYA_LOGGER_STRUCT_H_*/
