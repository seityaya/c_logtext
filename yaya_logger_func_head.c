#include "yaya_logger.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern logger_variables *lvg;

#if LOGGER_HEAD

void yaya_log_head(uintmax_t count, char *file, uintmax_t line, const char *func, const char *mes, ...) {
    lvg->head_flag = LOGGER_TRUE;
    va_list mesptr;
    va_start(mesptr, mes);
    logger_build(lvg->psett->head_format, lvg->head_mas_opt, &lvg->head_num_token, &count, file, &line, func, 0, 0, mes, mesptr);
    va_end(mesptr);
}

#endif
