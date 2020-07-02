#include "yaya_logger.h"
#include "yaya_logger_test.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    logger_test_set();

    //yaya_log_exsempl(L_DEBUG | L_RELISE, L_BEGF | L_ENDF, "TEST %c %s %d", '!', "HELLO", 666);

#ifdef DEBEG_LEVEL_0
    log(); //0

    log(L_TEST); //1

    log(L_TEST, L_TEST); //2
    log(L_TEST, "test"); //2

    log(L_TEST, L_TEST, "test"); //3
    //log(L_TEST, "%s", "test");   //3
    //log(L_TEST, "%c %s", 't', "test"); //3 + 1

    //log(L_TEST, L_TEST, "H%s", "W"); //4
    //log(L_TEST, L_TEST, "H %c %s", 'W', "!");  //4 + 1

    //log(L_TEST, L_TEST, NULL, "W"); //4 + E
    //log(L_TEST, L_TEST, NULL, "W", 1); //4 + 1 + E

    //log(NULL, NULL, NULL, "W", 1); //4N + 1 + E
#endif
    return 0;
}
