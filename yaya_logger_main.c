#include "yaya_logger_main.h"
#include "yaya_logger_struct.h"
#include "yaya_logger.h"
//#include <stdarg.h>
//#include <stdint.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>

void my_very_beautiful_long_functions(void) {
//        loggerf(L_BEGF, LL_DRVR, "Старт функции");
//        loggerf(L_INFO, LL_DRVR, "Это очень длинная функция");

//        loggerf(L_ENDF, LL_DRVR, "Стоп функции");
}

struct timespec beg, end;
#define T_BEG() clock_gettime(CLOCK_REALTIME, &beg)
#define T_END() clock_gettime(CLOCK_REALTIME, &end)
#define T_PRT(T) \
    printf("%s" T ": ", buff); \
    printf("%5ld ns\n", ((end.tv_sec - end.tv_sec) + (end.tv_nsec - beg.tv_nsec)));

//extern logger_filter *logger_type_def;
//extern logger_filter *logger_name_def;
//extern logger_setting *logger_setting_def;
//extern logger_define *logger_define_def;
//extern logger_style *logger_style_def;
//extern logger_token *logger_token_list;

int main(int argc, char *argv[]) {
    logger logger_instance;

    //yaya_log_init(&logger_instance, NULL, NULL, NULL, NULL, NULL);

    /*0*/
    //loggerf();

    /*1*/
    //loggerf(&logger_instance);
    loggerf(L_NUL);
    loggerf(L_ALL);

    //loggerf("HELLO");



    /*2*/
    //loggerf(L_BEGF, LL_DRVR);
    //loggerf(L_BEGF, "1");
    //loggerf("%s", "2");


    //loggerf(&logger_instance, L_BEGF);
    //loggerf("%s", "3");

//int a = 0;
//    printf("int = %"PRIu64"\n", sizeof(a));

//    printf("1 << = %"PRIu64"\n", sizeof(L_INFO));

//    printf("16 << = %"PRIu64"\n", sizeof(L_TEST));


















    //    T_BEG();
    //    logger logger_instance;
    //    char buff[] = "@";
    //    T_END();
    //    T_PRT("void");

    //    T_BEG();
    //    logger_init(&logger_instance, logger_type_def, logger_name_def, &logger_setting_def, &logger_define_def, logger_style_def);
    //    T_END();
    //    T_PRT("init");

    //    T_BEG();
    //    logger_head(&logger_instance, NULL);
    //    T_END();
    //    T_PRT("head");

    //    T_BEG();
    //    loggerf(L_TEST, LL_MAIN, "Старт программы");
    //    T_END();
    //    T_PRT("logs");

    //    my_very_beautiful_long_functions();

    //    T_BEG();
    //    loggerf(L_INFO, LL_MAIN, "Я сейчас в функции меин");
    //    T_END();
    //    T_PRT("logs");

    //    loggerf(L_INFO, LL_MAIN, "Объявление х");
    //    int x = 0;
    //    int y = 1;




    ////    if (x != y) {
    ////        loggerf(L_ERROR, LL_MAIN, "x != y; x == %d; y == %d", x, y);
    ////    } else {
    ////        loggerf(L_TEST, LL_MAIN, "x == y; x == %d; y == %d", x, y);
    ////    }
    ////    loggerf(L_ENDF, LL_MAIN, "Конец программы");

    ////    loggerf();
    ////    loggerf(L_INFO);
    ////    loggerf(L_INFO, LL_DRVR);

    return 0;
}
