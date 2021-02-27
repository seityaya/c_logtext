#include "yaya_logger.h"

#if LOGGER_HEAD
uintmax_t yaya_log_head(uintmax_t count, char *file, uintmax_t line, const char *func, logger *lvg, const char *mesg, ...) {
    ___logger_pars(lvg, lvg->psett->head_format, &lvg->temp_mas_opt, &lvg->temp_num_token);

    lvg->auto_head_flag = LOGGER_TRUE;
    va_list mesgptr;
    va_start(mesgptr, mesg);

    for (uintmax_t i = 0; i < lvg->temp_num_token; i++) {
        memset(lvg->tmp_buff, 0, LOGGER_TMP_BUFF_SIZE);
        logger_token_list[lvg->temp_mas_opt[i].id].func(lvg, lvg->psett->head_format, &lvg->temp_mas_opt[i], &lvg->temp_num_token, count, file, line, func, L_HEAD, LL_HEAD, mesg, mesgptr);
    }

    va_end(mesgptr);

#if LOGGER_STYLE
        /*Стили*/
        ___logger_style(lvg);
#endif

        /*Вывод*/
        ___logger_out(lvg);

    free(lvg->temp_mas_opt);
    return LOGGER_TRUE;
}
#endif
