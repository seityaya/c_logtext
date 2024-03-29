//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#ifndef LOGGER_CONF_H
#define LOGGER_CONF_H

#include "yaya_logger.h"

#define    NUL      LOGGER_FLAG_N_NUL            /*<<<*/
#define    VOID     LOGGER_FLAG_N_GENERATE(0)    /*<<<*/
#define    MAIN_FN  LOGGER_FLAG_N_GENERATE(1)
#define    BUTYFUL  LOGGER_FLAG_N_GENERATE(2)
#define    LONG_FN  LOGGER_FLAG_N_GENERATE(3)
#define    DRIVER   LOGGER_FLAG_N_GENERATE(4)
#define    FOO      LOGGER_FLAG_N_GENERATE(5)
#define    ALL      LOGGER_FLAG_N_ALL            /*<<<*/

static logger_filter my_logger_name[] = { LOGGER_FILTER_GENERATE(NUL),      /*<<<*/
                                          LOGGER_FILTER_GENERATE(VOID),     /*<<<*/
                                          LOGGER_FILTER_GENERATE(MAIN_FN),
                                          LOGGER_FILTER_GENERATE(BUTYFUL),
                                          LOGGER_FILTER_GENERATE(LONG_FN),
                                          LOGGER_FILTER_GENERATE(DRIVER),
                                          LOGGER_FILTER_GENERATE(FOO),
                                          LOGGER_FILTER_GENERATE(ALL)       /*<<<*/
                                        };



logger_setting my_logger_setting[] = { { .head_format = "HEAD ## $line%3. >> $mesg",
                                         .logs_format = "$data_curent $time_curent $func%.5 $line%.3 $type%.8 $name%.5 $recnum%2. >> $rectab $mesg",
                                         .atom_format = "$line",
                                         .free_format = "FREE ## $stats",
                                         .gerr_format = ">>ERROR<<",
                                         .type_l1 = L_ALL,
                                         .name_l2 = ALL,
                                         .stream = LS_STDOUT,
                                     } };

#endif /* LOGGER_CONF_H */
