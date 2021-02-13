#include "yaya_logger.h"

#if LOGGER_HEAD
void yaya_log_head(logger *lvg, uintmax_t count, char *file, uintmax_t line, const char *func, const char *mes, ...) {
    mas_opt(lvg, lvg->psett->head_format, &lvg->temp_mas_opt, &lvg->temp_num_token);

    lvg->auto_head_flag = LOGGER_TRUE;
    va_list mesptr;
    va_start(mesptr, mes);
    logger_build(lvg, lvg->psett->head_format, lvg->temp_mas_opt, &lvg->temp_num_token, &count, file, &line, func, 0, 0, mes, mesptr);
    va_end(mesptr);

    free(lvg->temp_mas_opt);
}
#endif
