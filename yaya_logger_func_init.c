#include "yaya_logger.h"

void filter_num(logger_filter_ *filter) {
    filter->num = 0;
    for (uintmax_t i = 0; i < sizeof(uintmax_t) * 8; i++) {
        if (filter->ptr[i].flag == LOGGER_FLAG_ALL) {
            filter->num = filter->ptr[i].id;
            break;
        }
    }
}

void yaya_log_init(logger *lvg, logger_filter *type, logger_filter *name, logger_setting *setting, logger_define *define, logger_style *style) {

    lvg->auto_init_flag = LOGGER_TRUE;

    {
        /*Cвязывание указателей*/
        lvg->type.ptr = (type != NULL) ? type : logger_type_def ;
        lvg->name.ptr = (name != NULL) ? name : logger_name_def;

        lvg->psett = (setting != NULL) ? setting : &logger_setting_def;
        lvg->pdefn = (define != NULL) ? define : &logger_define_def;
        lvg->pstyl = (style != NULL) ? style : logger_style_def;
    }

    {
        /*Инициализация переменных*/
        lvg->tmp_buff = calloc(LOGGER_TMP_BUFF_SIZE, sizeof(char));
        lvg->out_buff = calloc(LOGGER_OUT_BUFF_SIZE, sizeof(char));
        lvg->out_offset = 0;

        lvg->data_build = __DATE__;
        lvg->time_build = __TIME__;
        lvg->projpath = "/../../";
        lvg->absnum = 0;
        lvg->curnum = 0;
        lvg->compilerversion = __VERSION__;
    }

    {
        /*Подсчет количества флагов*/
        filter_num(&lvg->type);
        filter_num(&lvg->name);
    }

    {
        /*Парсинг форматированной строки*/
        mas_opt(lvg, lvg->psett->logs_format, &lvg->logs_mas_opt, &lvg->logs_num_token);
    }
}
