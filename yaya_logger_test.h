#ifndef YAYA_LOGGER_TEST_H_
#define YAYA_LOGGER_TEST_H_

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NUL 0 // NULL

//ОТЛАДКА - ТРИ ТИПА СООБЩЕНИЙ
#define DEBEG_LEVEL 0

#if DEBEG_LEVEL == 0
#define DEBEG_LEVEL_0
#define print_t0(m, ...) printf(m, ##__VA_ARGS__)
#else
#define print_t0(m, ...)
#endif

#if DEBEG_LEVEL == 1
//выводит две строки
//t - пример для сравнения,
//f- результат работы функции
#define print_t1(m, ...) printf(m, ##__VA_ARGS__)
#else
#define print_t1(m, ...)
#endif

#if DEBEG_LEVEL == 2
//выводит посрочно каждый параметр
#define print_t2(m, ...) printf(m, ##__VA_ARGS__)
#else
#define print_t2(m, ...)
#endif

static void logger_test(uintmax_t line, uintmax_t coun, uintmax_t L_1, uintmax_t L_2, char *mesg, ...) {
    print_t0("%ld : %ld - log_", coun, line);
    print_t1("%ld : %ld\nf log_", coun, line);
    print_t2("%ld : %ld\n", coun, line);

    if (L_1 == NUL) {
        print_t0("_");
        print_t1("_");
        print_t2("A: L_1 == NUL\n");
    } else {
        print_t0("A");
        print_t1("A");
        print_t2("A: L_2 == %ld\n", L_1);
    }
    if (L_2 == NUL) {
        print_t0("_");
        print_t1("_");
        print_t2("B: L_2 == NUL\n");
    } else {
        print_t0("B");
        print_t1("B");
        print_t2("B: L_2 == %ld\n", L_2);
    }
    if (mesg == NUL) {
        print_t0("_");
        print_t1("_");
        print_t2("C: MES == NUL\n");
    } else {
        print_t0("C");
        print_t1("C");
        print_t2("C: MES == %s\n", mesg);
    }

    if (mesg != NUL) {
        va_list list;
        va_list list_copy;

        va_copy(list_copy, list);

        va_start(list_copy, mesg);
        uintmax_t flag = va_arg(list_copy, uintmax_t);
        va_end(list_copy);

        if (flag == NUL) {
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

        if (flag == NUL) {
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

static void logger_test_set() {
#ifndef DEBEG_LEVEL_0
    uintmax_t L_1 = 1;
    uintmax_t L_2 = 2;

    logger_test(__LINE__, __COUNTER__, NUL, NUL, NUL, NUL); //0
    print_t1("t log_____ \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, NUL, NUL, NUL); //1
    print_t1("t log_A___ \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, L_2, NUL, NUL); //2
    print_t1("t log_AB__ \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, NUL, "H", NUL); //3
    print_t1("t log_A_C_ \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, NUL, "%d", 3); //4
    print_t1("t log_A_CD \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, NUL, "%s", "h"); //5
    print_t1("t log_A_CD \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, NUL, "h%s", "w"); //6
    print_t1("t log_A_CD \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, NUL, "%s%s", "h", "w"); //7
    print_t1("t log_A_CD \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, L_2, "H", NUL); //8
    print_t1("t log_ABC_ \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, L_2, "H%s", "W"); //9
    print_t1("t log_ABCD \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, L_2, "H%d", 4); //10
    print_t1("t log_ABCD \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, L_2, "H %c %s %d", 'W', "!", 666); //10
    print_t1("t log_ABCD \n\n");

    //функция с намереной ошибкой
    logger_test(__LINE__, __COUNTER__, NUL, NUL, NUL, 1); //11
    print_t1("t log____E \n\n");
#endif
}
#endif //YAYA_LOGGER_TEST_H_
