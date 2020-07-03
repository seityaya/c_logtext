#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//ОТЛАДКА - ТРИ ТИПА СООБЩЕНИЙ
// 0 - вывод через макрос
// 1 - отладка коротким способом
// 2 - отладка длинным способом
#define DEBUG_LEVEL 0

#if DEBUG_LEVEL == 0
#define DEBUG_LEVEL_0
#define print_t0(m, ...) printf(m, ##__VA_ARGS__)
#else
#define print_t0(m, ...)
#endif

#if DEBUG_LEVEL == 1
//выводит две строки
//t - пример для сравнения,
//f- результат работы функции
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

#define LOGGER_NULL 0 // NULL

static void logger_test(uintmax_t line, uintmax_t coun, uintmax_t L_1, uintmax_t L_2, char *mesg, ...) {
    print_t0("%03ld : %03ld - log_", coun, line);
    print_t1("%03ld : %03ld\nf log_", coun, line);
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

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define log_____() /*              */ logger_test(__LINE__, __COUNTER__, LOGGER_NULL, LOGGER_NULL, LOGGER_NULL, LOGGER_NULL) //0
#define log_A___(A) /*             */ logger_test(__LINE__, __COUNTER__, A, LOGGER_NULL, LOGGER_NULL, LOGGER_NULL)           //1
#define log_AB__(A, B) /*          */ logger_test(__LINE__, __COUNTER__, A, B, LOGGER_NULL, LOGGER_NULL)                     //2
#define log_A_C_(A, C) /*          */ logger_test(__LINE__, __COUNTER__, A, LOGGER_NULL, C, LOGGER_NULL)                     //2
#define log_ABC_(A, B, ...) /*     */ logger_test(__LINE__, __COUNTER__, A, B, __VA_ARGS__, LOGGER_NULL)                     //3
#define log_A_CD(A, C, ...) /*     */ logger_test(__LINE__, __COUNTER__, A, LOGGER_NULL, C, __VA_ARGS__)                     //3
#define log_ABCD(A, B, C, ...) /*  */ logger_test(__LINE__, __COUNTER__, A, B, C, __VA_ARGS__)                               //4

#define log_0() log_____()
#define log_1(A) log_A___(A)

//#define log_2(A, B) log_AB__(A, B)
#define log_2(A, BC) _Generic((A), int : log_2_BC(A, BC))
#define log_2_BC(A, BC) _Generic((BC), int : log_AB__(A, BC), char * : log_A_C_(A, BC))

//#define log_3(A, B, C) log_ABC_(A, B, C)
#define log_3(A, BC, ...) _Generic((A), int : log_3_BC_CD(A, BC, __VA_ARGS__))
#define log_3_BC_CD(A, BC, ...) _Generic((BC), int : log_3_B_C(A, BC, __VA_ARGS__), char * : log_3_C_D(A, BC, __VA_ARGS__))
#define log_3_B_C(A, BC, ...) log_ABC_(A, BC, __VA_ARGS__)
#define log_3_C_D(A, BC, ...) log_A_CD(A, BC, __VA_ARGS__)

//#define log_4(A, B, C, ...) log_ABCD(A, B, C, ##__VA_ARGS__)
#define log_4(A, B, C, ...) _Generic((A), int : log_4_B(A, B, C, __VA_ARGS__))
#define log_4_B(A, B, C, ...) _Generic((B), int : log_4_C(A, B, C, __VA_ARGS__), char * : log_4_D(A, B, C, __VA_ARGS__))
#define log_4_C(A, B, C, ...) log_ABCD(A, B, C, __VA_ARGS__)
#define log_4_D(A, B, C, ...) log_A_CD(A, B, C, __VA_ARGS__)

#define XXX_0() log_0()
#define XXX_A(A) log_1(A)
#define XXX_B(A, B) log_2(A, B)
#define XXX_C(A, B, C) log_3(A, B, C)
#define XXX_D(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_E(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_F(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_G(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_H(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_I(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_J(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_K(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_L(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_M(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_O(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_P(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_Q(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_R(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_S(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_T(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_U(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_V(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_W(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_X(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_Y(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)
#define XXX_Z(A, B, C, ...) log_4(A, B, C, __VA_ARGS__)

#define XXX_x(x, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, FUNC, ...) FUNC

#define log(...) \
    XXX_x(, \
          ##__VA_ARGS__, \
          XXX_Z(__VA_ARGS__), \
          XXX_Y(__VA_ARGS__), \
          XXX_X(__VA_ARGS__), \
          XXX_W(__VA_ARGS__), \
          XXX_V(__VA_ARGS__), \
          XXX_U(__VA_ARGS__), \
          XXX_T(__VA_ARGS__), \
          XXX_S(__VA_ARGS__), \
          XXX_R(__VA_ARGS__), \
          XXX_Q(__VA_ARGS__), \
          XXX_P(__VA_ARGS__), \
          XXX_O(__VA_ARGS__), \
          XXX_N(__VA_ARGS__), \
          XXX_M(__VA_ARGS__), \
          XXX_L(__VA_ARGS__), \
          XXX_K(__VA_ARGS__), \
          XXX_J(__VA_ARGS__), \
          XXX_I(__VA_ARGS__), \
          XXX_H(__VA_ARGS__), \
          XXX_G(__VA_ARGS__), \
          XXX_F(__VA_ARGS__), \
          XXX_E(__VA_ARGS__), \
          XXX_D(__VA_ARGS__), \
          XXX_C(__VA_ARGS__), \
          XXX_B(__VA_ARGS__), \
          XXX_A(__VA_ARGS__), \
          XXX_0(__VA_ARGS__))

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
#ifndef DEBUG_LEVEL_0
    uintmax_t L_1 = 1;
    uintmax_t L_2 = 2;

    logger_test(__LINE__, __COUNTER__, LOGGER_NULL, LOGGER_NULL, LOGGER_NULL, LOGGER_NULL); //0
    print_t1("t log_____ \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, LOGGER_NULL, LOGGER_NULL, LOGGER_NULL); //1
    print_t1("t log_A___ \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, L_2, LOGGER_NULL, LOGGER_NULL); //2
    print_t1("t log_AB__ \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, LOGGER_NULL, "H", LOGGER_NULL); //3
    print_t1("t log_A_C_ \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, LOGGER_NULL, "%d", 3); //4
    print_t1("t log_A_CD \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, LOGGER_NULL, "%s", "h"); //5
    print_t1("t log_A_CD \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, LOGGER_NULL, "h%s", "w"); //6
    print_t1("t log_A_CD \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, LOGGER_NULL, "%s%s", "h", "w"); //7
    print_t1("t log_A_CD \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, L_2, "H", LOGGER_NULL); //8
    print_t1("t log_ABC_ \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, L_2, "H%s", "W"); //9
    print_t1("t log_ABCD \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, L_2, "H%d", 4); //10
    print_t1("t log_ABCD \n\n");

    logger_test(__LINE__, __COUNTER__, L_1, L_2, "H %c %s %d", 'W', "!", 666); //10
    print_t1("t log_ABCD \n\n");

    //функция с намереной ошибкой
    logger_test(__LINE__, __COUNTER__, LOGGER_NULL, LOGGER_NULL, LOGGER_NULL, 1); //11
    print_t1("t log____E \n\n");
#endif

#define L_TEST 1

#ifdef DEBUG_LEVEL_0
    log(); //0

    log(L_TEST); //1

    log(L_TEST, L_TEST); //2
    log(L_TEST, "test"); //2

    log(L_TEST, L_TEST, "test"); //3
    log(L_TEST, "%s", "test");   //3

    log(L_TEST, "%c %s", 't', "test"); //3 + 1

    log(L_TEST, L_TEST, "H%s", "W");                  //4
    log(L_TEST, L_TEST, "H %c %s", 'W', "!");         //4 + 1
    log(L_TEST, L_TEST, "H %c %s %d", 'W', "!", 666); //4 + 2

    log(L_TEST, L_TEST, NULL, "W");    //4 + E
    log(L_TEST, L_TEST, NULL, "W", 1); //4 + 1 + E

    log(LOGGER_NULL, LOGGER_NULL, NULL, "W", 1); //4N + 1 + E
#endif

    return 0;
}
