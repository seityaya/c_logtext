#include "yaya_logger.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void my_very_beautiful_long_functions(void) {
    log(L_BEGF, LL_DRVR, "Старт функции");
    log(L_INFO, LL_DRVR, "Это очень длинная функция");

    log(L_ENDF, LL_DRVR, "Стоп функции");
}

#define T_BEG() clock_gettime(CLOCK_REALTIME, &beg)
#define T_END() clock_gettime(CLOCK_REALTIME, &end)
#define T_PRT(T) \
    printf("%s" T ": ", buff); \
    printf("%5ld ns\n", ((end.tv_sec - end.tv_sec) + (end.tv_nsec - beg.tv_nsec)));

int main(int argc, char *argv[]) {
    struct timespec beg, end;

    T_BEG();
    char buff[] = "@";
    T_END();
    T_PRT("void");

    T_BEG();
    log_init(logger_type_def, logger_name_def, logger_setting_def, logger_define_def, logger_style_def);
    T_END();
    T_PRT("init");


    T_BEG();
    log_head(NULL);
    T_END();
    T_PRT("head");

    T_BEG();
    log(L_TEST, LL_MAIN, "Старт программы");
    T_END();
    T_PRT("logs");

    //    my_very_beautiful_long_functions();
    //    log(L_INFO, LL_MAIN, "Я сейчас в функции меин");
    //    log(L_INFO, LL_MAIN, "Объявление х");
    //    int x = 0;
    //    int y = 1;

    //    if (x != y) {
    //        log(L_ERROR, LL_MAIN, "x != y; x == %d; y == %d", x, y);
    //    } else {
    //        log(L_TEST, LL_MAIN, "x == y; x == %d; y == %d", x, y);
    //    }
    //    log(L_ENDF, LL_MAIN, "Конец программы");
    return 0;
}
