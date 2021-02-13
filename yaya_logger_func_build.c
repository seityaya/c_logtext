#include "yaya_logger.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void logger_build(logger *lvg,
                  const char *format,
                  logger_token_mas *mas_opt,
                  uintmax_t *num_token,
                  uintmax_t *count,
                  char *file,
                  uintmax_t *line,
                  const char *func,
                  uintmax_t type,
                  uintmax_t name,
                  const char *mes,
                  va_list mes_list) {
    for (uintmax_t i = 0; i < *num_token; i++) {
       memset(lvg->tmp_buff, 0, LOGGER_TMP_BUFF_SIZE);
       logger_token_list[mas_opt[i].id].func(lvg, format, &mas_opt[i], num_token, count, file, line, func, type, name, mes, mes_list);
    }

#if LOGGER_STYLE
    /*Стили*/
    style_build(lvg);
#endif

    /*Вывод*/
    logger_out(lvg);
}

