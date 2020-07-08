#include "yaya_logger.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    log(L_BEGF, LL_MAIN, "Старт программы");
    log(L_INFO, LL_MAIN, "Я сейчас в функции меин");
    log(L_INFO, LL_MAIN, "Объявление х");
    int x = 0;
    int y = 1;

    if (x != y) {
        log(L_ERROR, LL_MAIN, "x != y; x == %d; y == %d", x, y);
    } else {
        log(L_TEST, LL_MAIN, "x == y; x == %d; y == %d", x, y);
    }
    log(L_ENDF, LL_MAIN, "Старт программы");
    return 0;
}
