#ifndef YAYA_LOGGER_STRUCT_H_
#define YAYA_LOGGER_STRUCT_H_

#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
} logger_streams;

typedef enum {
    LSM_NONE,
    LSM_STRAIGHT,
    LSM_ITALIC,
    LSM_LIGHT,
    LSM_BOLD,
} logger_style_mode;

#define LFS_LEF 1
#define LFS_RIG 2
#define LFS_NUL 3

typedef struct logger_token_specifiers { /*хранение спецификаторов*/
  uintmax_t beg; /*начало спецификатора*/
  uintmax_t end; /*конец спецификатора*/
  uintmax_t lef; /*смещение слева*/
  uintmax_t rig; /*смещение справа*/
  uintmax_t lfs; /*сторона скрытия*/
} logger_token_specifiers;

typedef struct logger_token_mas {    /*хранение токенов*/
  uintmax_t id;     /*тип токена*/
  uintmax_t beg;    /*начало токена*/
  uintmax_t end;    /*конец токена*/
  uintmax_t beglog; /*начало токена вывода*/
  uintmax_t endlog; /*конец токена вывода*/
  logger_token_specifiers *spe;
} logger_token_mas;


typedef struct logger_style {
  const uintmax_t token;
  const uintmax_t font[3];
  const uintmax_t back[3];
  const uintmax_t mode;
} logger_style;


typedef struct logger_filter {
  const uintmax_t id;
  const uintmax_t flag;
  const char *name;
} logger_filter;


typedef struct logger_seting {
  const char *head_format;
  const char *logs_format;
  const uintmax_t type;
  const intmax_t  name;
  const uintmax_t stream;
  const uintmax_t style;
} logger_setting;


typedef struct logger_define {
  uintmax_t seed; // - начальные настройки ГСПЧ
  char *prog;     // - название программы
  char *proj;     // - название проекта
  char *version;  // - версия программы
  char *compiler; // - версия компилятора
} logger_define;

typedef struct logger_filter_ {
  logger_filter *ptr; // - указатель на список типов
  uintmax_t num;      // - количество типов
} logger_filter_;

typedef struct logger {
    uintmax_t auto_head_flag; // - флаг заголовка
    uintmax_t auto_init_flag; // - флаг инициализации

    logger_filter_ type; // - список типов
    logger_filter_ name; // - список имен

    uintmax_t error; //ошибки логгера



    uintmax_t temp_num_token;       // - количество токенов в форматной строке логгера
    logger_token_mas *temp_mas_opt; // - указатель на структуру со смещениями токенов заголовка

    uintmax_t logs_num_token;       // - количество токенов в форматной строке заголовка
    logger_token_mas *logs_mas_opt; // - указатель на структуру со смещениями токенов логгера

    logger_setting *psett; // - указатель на настройки логгера
    logger_style *pstyl;   // - указатель на стили
    logger_define *pdefn;  // - указатель на переменные среды

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
} logger;

typedef struct logger_token {      /*список токенов*/
        const uintmax_t id;        /*идентификатор*/
        const char *name;          /*текстовое представление ключей*/
        void (*func)(LOGGER_FUNC_PARAM); /*функция токена*/
} logger_token;

#define LOGGER_TOKEN_GENERATE_ENUM(TOKEN) LEF_##TOKEN

#endif /*YAYA_LOGGER_STRUCT_H_*/
