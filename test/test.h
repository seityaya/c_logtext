//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#ifndef LOGGER_TEST_H
#define LOGGER_TEST_H

#include "yaya_logger.h"

#define NUM_RUN_CYCLES 1000000

#define    PRINTF      1
#define    FREE_TOKEN  2
#define    FREE_LOGGER 4
#define    PARAM       8
#define    TOKEN       16
#define    FORMAT      32

#define TYPE_TEST      PRINTF | FREE_TOKEN | FREE_LOGGER | PARAM | TOKEN | FORMAT

void test_printf();

void loggerf_test_free_token();

void loggerf_test_free();

void loggerf_test_param();

void loggerf_test_token();

void loggerf_test_format();

#endif /* LOGGER_TEST_H */
