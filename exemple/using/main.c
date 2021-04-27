#include "logger.h"
#include <stdio.h>

void foo(){
    loggerf(L_BEGF, FOO, "im a foo");

    loggerf(L_DEBUG, FOO, "im a debug");

    loggerf(L_TODO, FOO, "im a todo");

    loggerf(L_ENDF, FOO, "return to foo");
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    loggerf_init(&logger_main_def, logger_type_def, my_logger_name, my_logger_setting);

    loggerf(L_BEGF,  "Start");

    loggerf(L_DEBUG, "Foo fnk start");

    foo();

    loggerf(L_ENDF, "end");

    return 0;
}
