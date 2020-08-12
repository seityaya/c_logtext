#include "yaya_logger.h"
#include "yaya_logger_func.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern logger_variables *lvg;

void yaya_log_func(uintmax_t count, char *file, uintmax_t line, const char *func, uintmax_t type, uintmax_t name, const char *mesg, ...) {
#if LOGGER_AUTO_INIT
    /*Инициализация*/
    if (lvg->init_flag == LOGGER_FALSE) {
        log_init(logger_type_def, logger_name_def, logger_setting_def, logger_define_def, logger_style_def);
    }
#endif

#if LOGGER_AUTO_HEAD && LOGGER_HEAD
    /*Заголовок*/
    if (lvg->head_flag == LOGGER_FALSE && &lvg->psett->head_format[0] != NULL) {
        log_head(NULL);
    }
#endif

    lvg->absnum++;
    /*Логгер*/
    if ((lvg->psett->type & type) && (lvg->psett->name & name) && !(lvg->error)) {
        lvg->curnum++;
        /*Формат*/
        va_list mesgptr;
        va_start(mesgptr, mesg);
        logger_build(lvg->psett->logs_format, lvg->logs_mas_opt, &lvg->logs_num_token, &count, file, &line, func, type, name, mesg, mesgptr);
        va_end(mesgptr);

#if LOGGER_STYLE
        /*Стили*/
        style_build();
#endif

        /*Вывод*/
        logger_out();
    }
}
