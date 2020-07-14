#ifndef YAYA_LOGGER_TEST_H_
#define YAYA_LOGGER_TEST_H_

#include "yaya_logger.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOGGER_NULL 0

//ОТЛАДКА - ТРИ ТИПА СООБЩЕНИЙ
// 0 - вывод через макрос
// 1 - отладка коротким способом
// 2 - отладка длинным способом
#define DEBUG_LEVEL 1

#if DEBUG_LEVEL == 0
#define DEBUG_LEVEL_0
#define print_t0(m, ...) printf(m, ##__VA_ARGS__)
#else
#define print_t0(m, ...)
#endif

#if DEBUG_LEVEL == 1
//выводит две строки
//t - пример для сравнения,
//f - результат работы функции
#define print_t1(m, ...) printf(m, ##__VA_ARGS__)
#else
#define print_t1(m, ...)
#endif

#if DEBUG_LEVEL == 2
//выводит посрочно каждый параметр
#define print_t2(m, ...) printf(m, ##__VA_ARGS__)
#else
#define print_t2(m, ...)
#endif

#define log_exsempl_maxi(type, name, mes, ...) \
    yaya_log_func_maxi(__DATE__, __TIME__, __FILE__, __LINE__, __COUNTER__, __FUNCTION__, type, name, *mes, ##__VA_ARGS__)
#define log_exsempl_mini(type, name, mes, ...) yaya_log_func_test_mini(uintmax_t line, uintmax_t coun, uintmax_t L_1, uintmax_t L_2, mesg, ...);

void yaya_log_func_test_maxi(
    char *data, char *time, char *file, uintmax_t line, uintmax_t count, const char *func, uintmax_t type, uintmax_t name, const char *mes, ...);
void yaya_log_func_test_mini(uintmax_t line, uintmax_t coun, uintmax_t L_1, uintmax_t L_2, char *mesg, ...);
void yaya_log_func_test_set(void);
void yaya_log_macr_test_set(void);

#endif /*YAYA_LOGGER_TEST_H_*/
