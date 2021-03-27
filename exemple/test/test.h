#ifndef LOGGER_TEST_H
#define LOGGER_TEST_H

#include "yaya_logger.h"

#define    FREE_TOKEN  1
#define    FREE_LOGGER 2
#define    PARAM       4
#define    TOKEN       8
#define    FORMAT      16

#define TYPE_TEST      TOKEN | FORMAT

#define NUM_RUN_CYCLES 10000000

void loggerf_test_free_token();

void loggerf_test_free();

void loggerf_test_param();

void loggerf_test_token();

void loggerf_test_format();

#endif /* LOGGER_TEST_H */
