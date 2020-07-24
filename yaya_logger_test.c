#include "yaya_logger_test.h"
#include "yaya_logger.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOGGER_TYPE_NUM 19
extern logger_list logger_type_def[];

void yaya_log_func_test_maxi(
    char *data, char *time, char *file, uintmax_t line, uintmax_t count, const char *func, uintmax_t type, uintmax_t name, const char *mes, ...) {
    printf("Data   : %s\nTime   : %s\nCount  : %"PRIXMAX"\nLine   : %"PRIXMAX"\nFile   : %s\nFunc   : %s\n", data, time, count, line, file, func);
    char temp[1000];
    printf("Type N : %"PRIXMAX"\n", type);
    temp[0] = '\0';
    for (uintmax_t i = 0; i < LOGGER_TYPE_NUM - 1; i++) {
        if (LOGGER_BIT_GET(type, i)) {
            strcat(temp, logger_type_def[i + 1].name);
            strcat(temp, " ");
        }
    }
    printf("Type L : %s\n", temp);

    temp[0] = '\0';
    printf("Name N : %"PRIXMAX"\n", name);
    for (uintmax_t i = 0; i < LOGGER_TYPE_NUM - 1; i++) {
        if (LOGGER_BIT_GET(name, i)) {
            strcat(temp, logger_type_def[i + 1].name);
            strcat(temp, " ");
        }
    }
    printf("Name L : %s\n", temp);
    printf("Messg  : %s\n", mes);
    printf("Args   : ");
    va_list list;
    va_start(list, mes);
    vprintf(mes, list);
    va_end(list);
    printf("\n\n");
}

void yaya_log_func_test_mini(uintmax_t line, uintmax_t coun, uintmax_t L_1, uintmax_t L_2, char *mesg, ...) {
    print_t0("%03"PRIXMAX" : %03"PRIXMAX" - log_", coun, line);
    print_t1("%03"PRIXMAX" : %03"PRIXMAX"\nf log_", coun, line);
    print_t2("%03ld : %03ld\n", coun, line);

    if (L_1 == LOGGER_NULL) {
        print_t0("_");
        print_t1("_");
        print_t2("A: L_1 == NUL\n");
    } else {
        print_t0("A");
        print_t1("A");
        print_t2("A: L_2 == %ld\n", L_1);
    }
    if (L_2 == LOGGER_NULL) {
        print_t0("_");
        print_t1("_");
        print_t2("B: L_2 == NUL\n");
    } else {
        print_t0("B");
        print_t1("B");
        print_t2("B: L_2 == %ld\n", L_2);
    }
    if (mesg == LOGGER_NULL) {
        print_t0("_");
        print_t1("_");
        print_t2("C: MES == NUL\n");
    } else {
        print_t0("C");
        print_t1("C");
        print_t2("C: MES == %s\n", mesg);
    }

    if (mesg != LOGGER_NULL) {
        va_list list;
        va_list list_copy;

        va_copy(list_copy, list);

        va_start(list_copy, mesg);
        uintmax_t flag = va_arg(list_copy, uintmax_t);
        va_end(list_copy);

        if (flag == LOGGER_NULL) {
            print_t0("_");
            print_t1("_");
            print_t2("D: ARG == NUL\n");
        } else {
            print_t0("D ==> ");
            print_t1("D ==> ");
            print_t2("D: ARG ==> ");

            va_start(list, mesg);
            vprintf(mesg, list);
            va_end(list);
        }
    } else {
        va_list list;
        va_start(list, mesg);
        uintmax_t flag = va_arg(list, uintmax_t);
        va_end(list);

        if (flag == LOGGER_NULL) {
            print_t0("_");
            print_t1("_");
            print_t2("D: ARG == NUL\n");
        } else {
            print_t0("E");
            print_t1("E");
            print_t2("D: ERROR!!\n");
        }
    }
    print_t0("\n");
    print_t1("\n");
    print_t2("\n\n");
}

void yaya_log_test_func_set(void) {
    uintmax_t L_1 = 1;
    uintmax_t L_2 = 2;

    yaya_log_func_test_mini(__LINE__, __COUNTER__, LOGGER_NULL, LOGGER_NULL, LOGGER_NULL,
                            LOGGER_NULL); // 0
    print_t1("t log_____ \n\n");

    yaya_log_func_test_mini(__LINE__, __COUNTER__, L_1, LOGGER_NULL, LOGGER_NULL, LOGGER_NULL); // 1
    print_t1("t log_A___ \n\n");

    yaya_log_func_test_mini(__LINE__, __COUNTER__, L_1, L_2, LOGGER_NULL, LOGGER_NULL); // 2
    print_t1("t log_AB__ \n\n");

    yaya_log_func_test_mini(__LINE__, __COUNTER__, L_1, LOGGER_NULL, "H", LOGGER_NULL); // 3
    print_t1("t log_A_C_ \n\n");

    yaya_log_func_test_mini(__LINE__, __COUNTER__, L_1, LOGGER_NULL, "%d", 3); // 4
    print_t1("t log_A_CD \n\n");

    yaya_log_func_test_mini(__LINE__, __COUNTER__, L_1, LOGGER_NULL, "%s", "h"); // 5
    print_t1("t log_A_CD \n\n");

    yaya_log_func_test_mini(__LINE__, __COUNTER__, L_1, LOGGER_NULL, "h%s", "w"); // 6
    print_t1("t log_A_CD \n\n");

    yaya_log_func_test_mini(__LINE__, __COUNTER__, L_1, LOGGER_NULL, "%s%s", "h", "w"); // 7
    print_t1("t log_A_CD \n\n");

    yaya_log_func_test_mini(__LINE__, __COUNTER__, L_1, L_2, "H", LOGGER_NULL); // 8
    print_t1("t log_ABC_ \n\n");

    yaya_log_func_test_mini(__LINE__, __COUNTER__, L_1, L_2, "H%s", "W"); // 9
    print_t1("t log_ABCD \n\n");

    yaya_log_func_test_mini(__LINE__, __COUNTER__, L_1, L_2, "H%d", 4); // 10
    print_t1("t log_ABCD \n\n");

    yaya_log_func_test_mini(__LINE__, __COUNTER__, L_1, L_2, "H %c %s %d", 'W', "!", 666); // 10
    print_t1("t log_ABCD \n\n");

    //функция с намереной ошибкой
    yaya_log_func_test_mini(__LINE__, __COUNTER__, LOGGER_NULL, LOGGER_NULL, LOGGER_NULL, 1); // 11
    print_t1("t log____E \n\n");
}

void yaya_log_macr_test_set(void) {
    log(); // 0

    log(0); // 1

    log(0, 0);      // 2
    log(0, "test"); // 2

    log(0, 0, "test");    // 3
    log(0, "%s", "test"); // 3

    log(0, "%c %s", 't', "test"); // 3 + 1

    log(0, 0, "H%s", "W");                  // 4
    log(0, 0, "H %c %s", 'W', "!");         // 4 + 1
    log(0, 0, "H %c %s %d", 'W', "!", 666); // 4 + 2

    log(0, 0, NULL, "W");    // 4 + E
    log(0, 0, NULL, "W", 1); // 4 + 1 + E

    log(0, 0, NULL, "W", 1); // 4N + 1 + E
}
