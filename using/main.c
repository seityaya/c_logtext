//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#include "logger.h"

void foo(){
    loggerf(L_BEGF, FOO, "im a foo");

    loggerf(L_DEBUG, FOO, "im a debug");

    loggerf(L_TODO, FOO, "im a todo");

    loggerf(L_ENDF, FOO, "return to foo");
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    loggerf_init(&logger_main_def, logger_type_l1_def, my_logger_name, my_logger_setting);
    loggerf(L_BEGF,  "Start");
    loggerf(L_DEBUG, "Foo fnk start");

    foo();

    loggerf(L_ENDF, "end");
    loggerf_free(logger_main_def);


    loggerf_init();
    loggerf(L_HEAD);
    loggerf(L_BEGF);
    loggerf("Hello World!");
    loggerf(L_ENDF,  "Void");
    loggerf_free();

    return 0;
}
