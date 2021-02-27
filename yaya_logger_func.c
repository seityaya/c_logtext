#include "yaya_logger.h"

uintmax_t yaya_log_func(uintmax_t count, char *file, uintmax_t line, const char *func, const char* debug, logger *lvg, ___l1_type type_one, ___l2_type type_two, const char *mesg, ...) {
#if LOGGER_AUTO_INIT
    /*Инициализация*/
    if (lvg->auto_init_flag == LOGGER_FALSE) {
        yaya_log_init(lvg, NULL, NULL, NULL, NULL, NULL);
    }
#endif

#if LOGGER_AUTO_HEAD && LOGGER_HEAD
    /*Заголовок*/
    if (lvg->auto_head_flag == LOGGER_FALSE && &lvg->psett->head_format[0] != NULL) {
        logger_head(lvg, NULL);
    }
#endif

    lvg->absnum++;
    /*Логгер*/
    if ((lvg->psett->type & type_one) && (lvg->psett->name & type_two) && !(lvg->error)) {
        lvg->curnum++;
        /*Формат*/
        va_list mesgptr;
        va_start(mesgptr, mesg);
        printf("%s   ", debug);
        for (uintmax_t i = 0; i < lvg->logs_num_token; i++) {
            memset(lvg->tmp_buff, 0, LOGGER_TMP_BUFF_SIZE);
            logger_token_list[lvg->logs_mas_opt[i].id].func(lvg, lvg->psett->logs_format, &lvg->logs_mas_opt[i], &lvg->logs_num_token, count, file, line, func, type_one, type_two, mesg, mesgptr);
        }

        va_end(mesgptr);
#if LOGGER_STYLE
        /*Стили*/
        ___logger_style(lvg);
#endif

        /*Вывод*/
        ___logger_out(lvg);

        return LOGGER_TRUE;
    } else {
        return LOGGER_FALSE;
    }
}

uintmax_t yaya_log_defl(uintmax_t count, char *file, uintmax_t line, const char *func, const char* debug,  logger *lvg){
    printf("%s   ERROR: %s %ju %s |  \n", debug, file, line, func);
    return LOGGER_TRUE;
}
