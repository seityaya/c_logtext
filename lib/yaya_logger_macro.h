#ifndef YAYA_LOGGER_MACRO_H
#define YAYA_LOGGER_MACRO_H

#include <stdarg.h>

#define LOGGER_BIT_GET(x, n)        ((x) & (1 << (n)))
#define LOGGER_TRUE                 (1 == 1)
#define LOGGER_FALSE                (!LOGGER_TRUE)

#define LOGGER_FLAG(x,  sign)       (sign)(1 << ((uintmax_t)(x)))
#define LOGGER_FLAG_ALL(sign)       (sign)((uintmax_t)(0) - 1)
#define LOGGER_FLAG_NUL(sign)       (sign)(0)

#define LOGGER_FLAG_T_GENERATE(num)  LOGGER_FLAG(num, ___l1_type)
#define LOGGER_FLAG_T_ALL            LOGGER_FLAG_ALL (___l1_type)
#define LOGGER_FLAG_T_NUL            LOGGER_FLAG_NUL (___l1_type)

#define LOGGER_FLAG_N_GENERATE(num)  LOGGER_FLAG(num, ___l2_type)
#define LOGGER_FLAG_N_ALL            LOGGER_FLAG_ALL (___l2_type)
#define LOGGER_FLAG_N_NUL            LOGGER_FLAG_NUL (___l2_type)

#define LOGGER_FILTER_GENERATE(NAME)  {NAME, #NAME }

#define LOGGER_TOKEN_GENERATE_FUNC(TOKEN)  void ___logger_func_##TOKEN(LOGGER_FUNC_PARAM)
#define LOGGER_TOKEN_GENERATE_ENUM(TOKEN)  LEF_##TOKEN
#define LOGGER_TOKEN_GENERATE_ST(TOKEN)    { LEF_##TOKEN, #TOKEN, ___logger_func_##TOKEN }


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

#endif /*YAYA_LOGGER_MACRO_H*/
