#include "yaya_logger.h"

void ___count_num(___logger_filters *filter) {
    filter->num = 0;
    for (uintmax_t i = 0; i < sizeof(uintmax_t) * __CHAR_BIT__; i++)
    {
        if(((i == 0) ? (0) : (filter->ptr[i].flag & (1ULL << (i)))) && !(filter->ptr[i].flag == LOGGER_FLAG_ALL(uintmax_t)))
        {
            exit(1);
        }

        if (filter->ptr[i].flag == LOGGER_FLAG_ALL(uintmax_t)) {
            filter->num = i;
            break;
        }
    }
}

void yaya_log_init(logger**        lvg,
                   logger_filter*  type,
                   logger_filter*  name,
                   logger_setting* setting,
                   logger_define*  define,
                   logger_style*   style)
{
    /*Выделение памяти для главной структуры*/
    *lvg = calloc(1, sizeof(logger));

    /*Cвязывание указателей*/
    (*lvg)->type.ptr = (type    != NULL) ? type    : logger_type_def;
    (*lvg)->name.ptr = (name    != NULL) ? name    : logger_name_def;
    (*lvg)->psett    = (setting != NULL) ? setting : logger_setting_def;
    (*lvg)->pdefn    = (define  != NULL) ? define  : logger_define_def;
    (*lvg)->pstyl    = (style   != NULL) ? style   : logger_style_def;

    /*Подсчет количества флагов*/
    ___count_num(&(*lvg)->type);
    ___count_num(&(*lvg)->name);

    /*Инициализация переменных*/

    (*lvg)->tmp_buff_size = LOGGER_TMP_BUFF_SIZE;
    (*lvg)->tmp_buff = calloc((*lvg)->tmp_buff_size, sizeof(char));

    (*lvg)->out_buff_size = LOGGER_OUT_BUFF_SIZE;
    (*lvg)->out_buff = calloc((*lvg)->tmp_buff_size, sizeof(char));
    (*lvg)->out_offset = 0;
    (*lvg)->absnum = 0;
    (*lvg)->curnum = 0;

    /*Парсинг форматированной строки*/
    ___logger_pars((*lvg), (*lvg)->psett->logs_format, &(*lvg)->logs);
    ___logger_pars((*lvg), (*lvg)->psett->atom_format, &(*lvg)->atom);
    ___logger_pars((*lvg), (*lvg)->psett->head_format, &(*lvg)->head);
    ___logger_pars((*lvg), (*lvg)->psett->gerr_format, &(*lvg)->gerr);
}

void ___free_tokens(___logger_tokens* tokens){
    for(uintmax_t i = 0; i < tokens->num_token; i++)
    {
        if(tokens->mas_opt[i].spe != NULL)
        {
            free(tokens->mas_opt[i].spe);
            tokens->mas_opt[i].spe = NULL;
        }
    }
    free(tokens->mas_opt);
    tokens->mas_opt = NULL;

    free(tokens);
    tokens = NULL;
}

void yaya_log_free(logger* lvg)
{
    ___free_tokens(lvg->logs);
    ___free_tokens(lvg->head);
    ___free_tokens(lvg->atom);
    ___free_tokens(lvg->gerr);

    free(lvg->out_buff);
    lvg->out_buff = NULL;

    free(lvg->tmp_buff);
    lvg->tmp_buff = NULL;

    free(lvg);
    lvg = NULL;
}

