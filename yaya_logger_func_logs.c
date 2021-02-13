#include "yaya_logger.h"

uintmax_t yaya_log_func(uintmax_t count, char *file, uintmax_t line, const char *func, logger *lvg, uintmax_t type_one, uintmax_t type_two, const char *mesg, ...) {
#if LOGGER_AUTO_INIT
    /*Инициализация*/
    if (lvg->auto_init_flag == LOGGER_FALSE) {
        yaya_log_init(lvg, NULL, NULL, NULL, NULL, NULL);
    }
#endif

#if LOGGER_AUTO_HEAD && LOGGER_HEAD
    /*Заголовок*/
    if (lvg->auto_head_flag == LOGGER_FALSE && &lvg->psett->head_format[0] != NULL) {
        log_head(NULL);
    }
#endif

    lvg->absnum++;
    /*Логгер*/
    if ((lvg->psett->type & type_one) && (lvg->psett->name & type_two) && !(lvg->error)) {
        lvg->curnum++;
        /*Формат*/
        va_list mesgptr;
        va_start(mesgptr, mesg);
        logger_build(lvg, lvg->psett->logs_format, lvg->logs_mas_opt, &lvg->logs_num_token, &count, file, &line, func, type_one, type_two, mesg, mesgptr);
        va_end(mesgptr);
        return LOGGER_TRUE;
    } else {
        return LOGGER_FALSE;
    }
}
