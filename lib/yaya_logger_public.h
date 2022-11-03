//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#ifndef YAYA_LOGGER_PUBLIC_H_
#define YAYA_LOGGER_PUBLIC_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#include "yaya_logger_conf.h"

#define LOGGER_TRUE                        (1 == 1)
#define LOGGER_FALSE                       (!LOGGER_TRUE)

#define LOGGER_ON                          LOGGER_TRUE
#define LOGGER_OFF                         LOGGER_FALSE

#define LOGGER_FLAG(x,  sign)              (sign)(UINTMAX_C(1) << ((uintmax_t)(x)))
#define LOGGER_FLAG_ALL(sign)              (sign)(UINTMAX_C(0) - UINTMAX_C(1))
#define LOGGER_FLAG_NUL(sign)              (sign)(UINTMAX_C(0))

#define LOGGER_FLAG_T_GENERATE(num)        LOGGER_FLAG(num, logger_l1_type)
#define LOGGER_FLAG_T_ALL                  LOGGER_FLAG_ALL (logger_l1_type)
#define LOGGER_FLAG_T_NUL                  LOGGER_FLAG_NUL (logger_l1_type)

#define LOGGER_FLAG_N_GENERATE(num)        LOGGER_FLAG(num, logger_l2_type)
#define LOGGER_FLAG_N_ALL                  LOGGER_FLAG_ALL (logger_l2_type)
#define LOGGER_FLAG_N_NUL                  LOGGER_FLAG_NUL (logger_l2_type)

#define LOGGER_FILTER_GENERATE(NAME)       {NAME, #NAME }

#define LOGGER_TOKEN_GENERATE_ENUM(TOKEN)  LEF_##TOKEN


typedef intmax_t  logger_l1_type;
typedef uintmax_t logger_l2_type;


typedef enum{
    LE_OK,
    LE_ERR,
    LE_ALLOC
} logger_error;


typedef enum {
    LS_STDOUT,
    LS_STDERR,
    LS_STDBUF,
    LS_STDFILE,
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
    union{
        const logger_l1_type type_l1;
        const logger_l2_type name_l2;
    };
    const uintmax_t font[3];
    const uintmax_t back[3];
    const uintmax_t mode;
} logger_style;


typedef struct logger_filter {
    const uintmax_t flag;
    const char      *name;
} logger_filter;

typedef struct logger_setting {
    char *logs_format;
#if LOGGER_HEAD
    char *head_format;
#endif
#if LOGGER_ATOM
    char *atom_format;
#endif
#if LOGGER_ERROR
    char *gerr_format;
#endif
    logger_l1_type type_l1;
    logger_l2_type name_l2;

    logger_streams stream;
    char          *out_file;
    char          *out_buff;
    size_t        *out_size;
    size_t         size_buff;
} logger_setting;

#endif /*YAYA_LOGGER_PUBLIC_H_*/
