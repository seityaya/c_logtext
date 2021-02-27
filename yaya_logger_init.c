#include "yaya_logger.h"

void count_num(___logger_filter_ *filter) {
    filter->num = 0;
    for (uintmax_t i = 0; i < sizeof(uintmax_t) * __CHAR_BIT__; i++) {
        if (filter->ptr[i].flag == LOGGER_FLAG_ALL(uintmax_t)) {
            filter->num = filter->ptr[i].id;
            break;
        }
    }
}

uintmax_t yaya_log_init(___logger **lvg,
                        ___logger_filter *type,
                        ___logger_filter *name,
                        ___logger_setting *setting,
                        ___logger_define *define,
                        ___logger_style *style)
{
    /*Выделение памяти для главной структуры*/
    *lvg = calloc(1, sizeof(___logger));

    /*Cвязывание указателей*/
    (*lvg)->type.ptr = (type != NULL) ? type : ___logger_type_def ;
    (*lvg)->name.ptr = (name != NULL) ? name : ___logger_name_def;
    (*lvg)->psett = (setting != NULL) ? setting : ___logger_setting_def;
    (*lvg)->pdefn = (define != NULL) ? define : ___logger_define_def;
    (*lvg)->pstyl = (style != NULL) ? style : ___logger_style_def;

    /*Инициализация переменных*/
    (*lvg)->tmp_buff = calloc(LOGGER_TMP_BUFF_SIZE, sizeof(char));
    (*lvg)->out_buff = calloc(LOGGER_OUT_BUFF_SIZE, sizeof(char));
    (*lvg)->out_offset = 0;
    (*lvg)->data_build = __DATE__;
    (*lvg)->time_build = __TIME__;
    (*lvg)->projpath = "/../../";
    (*lvg)->absnum = 0;
    (*lvg)->curnum = 0;
    (*lvg)->compilerversion = __VERSION__;

    /*Подсчет количества флагов*/
    count_num(&(*lvg)->type);
    count_num(&(*lvg)->name);

    /*Парсинг форматированной строки*/
    ___logger_pars((*lvg), (*lvg)->psett->logs_format, &(*lvg)->logs_mas_opt, &(*lvg)->logs_num_token);

    return LOGGER_TRUE;
}
