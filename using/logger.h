#ifndef LOGGER_CONF_H
#define LOGGER_CONF_H

#include "yaya_logger.h"

static void* my_logger_instans = NULL;

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
                                         .logs_format = "LOGS ## $line%03. -- | $type%.15 $name%.08 >> $func%10.  $mesg%.10 << $file%20.",
                                         .atom_format = "$line",
                                         .gerr_format = ">>ERROR<<",
                                         .type_l1 = L_ALL,
                                         .name_l2 = FOO,
                                         .stream = LS_STDOUT,
                                     } };

#endif /* LOGGER_CONF_H */
