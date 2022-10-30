//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#include "yaya_logger.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    loggerf_init();
    loggerf(L_BEGF,  "Start");
    loggerf(L_DEBUG, "Hello World!");
    loggerf(L_ENDF, "End");
    loggerf_free();

    return 0;
}
