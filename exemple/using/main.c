#include "logger.h"
#include <stdio.h>

void foo(){
    loggerf(L_BEGF, FOO, "im a sub");

    loggerf(L_DEBUG, FOO, "im a debug");

    loggerf(L_TODO, FOO, "im a void");

    loggerf(L_ENDF, FOO, "return");
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    loggerf_init(&logger_main_def, logger_type_def, my_logger_name, my_logger_setting);

    loggerf(L_BEGF,  "Start");

    loggerf(L_DEBUG, "Foo fnk");
    foo();

    loggerf(L_ENDF, "end");

    return 0;
}
