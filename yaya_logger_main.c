#include "yaya_logger.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>





#include <time.h>
struct timespec beg, end;
#define T_BEG() clock_gettime(CLOCK_REALTIME, &beg)
#define T_END() clock_gettime(CLOCK_REALTIME, &end)
#define T_PRT(T) \
    printf("@" T ": "); \
    printf("%5ld ns\n", ((end.tv_sec - end.tv_sec) + (end.tv_nsec - beg.tv_nsec)));




void my_very_beautiful_long_functions(void) {
    log(L_BEGF, LL_DRVR, "Старт функции");
    log(L_INFO, LL_DRVR, "Это очень длинная функция");

    log(L_ENDF, LL_DRVR, "Стоп функции");
}


int main(int argc, char *argv[]) {

    log(L_TEST, LL_MAIN, "Старт программы %s", "!");

    log(L_INFO, LL_MAIN, "Я сейчас в функции меин");

    my_very_beautiful_long_functions();

    log(L_INFO, LL_MAIN, "Объявление х");
    int x = 0;
    int y = 1;

    if (x != y) {
        log(L_ERROR, LL_MAIN, "x != y; x == %d; y == %d", x, y);
    } else {
        log(L_TEST, LL_MAIN, "x == y; x == %d; y == %d", x, y);
    }
    log(L_ENDF, LL_MAIN, "Конец программы");
    return 0;
}
