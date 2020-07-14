#include "yaya_logger.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void my_very_beautiful_long_functions(void) {
    log(L_BEGF, LL_DRVR, "Старт функции");

    log(L_ENDF, LL_DRVR, "Стоп функции");
}

int main(int argc, char *argv[]) {
    clock_t start;
    clock_t end;
    long double seconds;

    start = clock();
    log_init(logger_type_def, logger_name_def, logger_setting_def, logger_define_def, logger_style_def);
    end = clock();
    seconds = (long double) (end - start) / CLOCKS_PER_SEC;
    printf("init: %Lf seconds\n", seconds);

    start = clock();
    log(L_BEGF, LL_MAIN, "Старт программы");
    end = clock();
    seconds = (long double) (end - start) / CLOCKS_PER_SEC;
    printf("logs: %Lf seconds\n", seconds);

    my_very_beautiful_long_functions();
    log(L_INFO, LL_MAIN, "Я сейчас в функции меин");
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
