#ifndef LOGGER_MACRO_H
#define LOGGER_MACRO_H

#define LOGGER_BIT_GET(x, n) ((x) & (1 << (n)))
#define LOGGER_TRUE          (1 == 1)
#define LOGGER_FALSE         (!LOGGER_TRUE)

#define LOGGER_FLAG(x,  sign)       (sign)(1 << ((uintmax_t)(x)))
#define LOGGER_FLAG_ALL(sign)       (sign)(0b1111111111111111111111111111111111111111111111111111111111111111)
#define LOGGER_FLAG_NUL(sign)       (sign)(0)

#define LOGGER_NEW_COUNTER(COUNTER_NAME) enum {COUNTER_NAME = __COUNTER__};

#define LOGGER_FLAG_T_GENERATE(num)  LOGGER_FLAG(num, ___l1_type)
#define LOGGER_FLAG_T_GENERATE(num)  LOGGER_FLAG(num, ___l1_type)
#define LOGGER_FLAG_T_ALL            LOGGER_FLAG_ALL (___l1_type)
#define LOGGER_FLAG_T_NUL            LOGGER_FLAG_NUL (___l1_type)

#define LOGGER_FLAG_N_GENERATE(num)  LOGGER_FLAG(num, ___l2_type)
#define LOGGER_FLAG_N_GENERATE(num)  LOGGER_FLAG(num, ___l2_type)
#define LOGGER_FLAG_N_ALL            LOGGER_FLAG_ALL (___l2_type)
#define LOGGER_FLAG_N_NUL            LOGGER_FLAG_NUL (___l2_type)


#define LOGGER_FILTER_GENERATE(COUNTER_NAME, type, NAME)  {__COUNTER__ - COUNTER_NAME, type##_##NAME, #type "_" #NAME }


#define LOGGER_FUNC_PARAM \
    logger *lvg, \
    const char *format, \
    logger_token_mas *mas_opt, \
    uintmax_t *num_token, \
    uintmax_t count, \
    char *file, \
    uintmax_t line, \
    const char *func, \
    ___l1_type type, \
    ___l2_type name, \
    const char *mes, \
    va_list mes_list

#define LOGGER_FUNC_UNUSED \
    (void*)lvg, \
    (void*)format, \
    (void*)mas_opt, \
    (void*)num_token, \
    (void*)count, \
    (void*)file, \
    (void*)line, \
    (void*)func, \
    (void*)type, \
    (void*)name, \
    (void*)mes, \
    (void*)mes_list


#define LOGGER_FUNC_GENERATE(TOKEN)  void logger_func_##TOKEN(LOGGER_FUNC_PARAM)


#endif // LOGGER_MACRO_H
