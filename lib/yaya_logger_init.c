#include "yaya_logger.h"
#include "yaya_logger_private.h"

#include <stdlib.h>

logger_error ___count_num(___logger_filters *filter) {
    filter->num = 0;
    for (uintmax_t i = 0; i < sizeof(uintmax_t) * __CHAR_BIT__; i++)
    {
        if(((i == 0) ? (0) : (filter->ptr[i].flag & (1ULL << (i)))) && !(filter->ptr[i].flag == LOGGER_FLAG_ALL(uintmax_t)))
        {
            return LE_ERR;
        }

        if (filter->ptr[i].flag == LOGGER_FLAG_ALL(uintmax_t)) {
            filter->num = i;
            break;
        }
    }
    return LE_OK;
}

logger_error yaya_log_init(void**          lvgv,
                           logger_filter*  type,
                           logger_filter*  name,
                           logger_setting* setting,
                           logger_define*  define,
                           logger_style*   style)
{
    logger **lvg = (logger**)(lvgv);
    logger_error status;

    /*Выделение памяти для главной структуры*/
    *lvg = calloc(1, sizeof(logger));
    if((*lvg) == NULL){
        return LE_ALLOC;
    }

    /*Cвязывание указателей*/
    (*lvg)->type.ptr = (type    != NULL) ? type    : logger_type_def;
    (*lvg)->name.ptr = (name    != NULL) ? name    : logger_name_def;
    (*lvg)->psett    = (setting != NULL) ? setting : logger_setting_def;
    (*lvg)->pdefn    = (define  != NULL) ? define  : logger_define_def;
    (*lvg)->pstyl    = (style   != NULL) ? style   : logger_style_def;

    /*Подсчет количества флагов*/
    status = ___count_num(&(*lvg)->type);
    if(status != LE_OK){
        return status;
    }

    status = ___count_num(&(*lvg)->name);
    if(status != LE_OK){
        return status;
    }

    /*Инициализация переменных*/

    (*lvg)->tmp_buff_size = LOGGER_TMP_BUFF_SIZE;
    (*lvg)->tmp_buff = calloc((*lvg)->tmp_buff_size, sizeof(char));
    if((*lvg)->tmp_buff == NULL){
        return LE_ALLOC;
    }

    (*lvg)->out_buff_size = LOGGER_OUT_BUFF_SIZE;
    (*lvg)->out_buff = calloc((*lvg)->tmp_buff_size, sizeof(char));
    if((*lvg)->out_buff == NULL){
        return LE_ALLOC;
    }

    (*lvg)->out_offset = 0;
    (*lvg)->absnum = 0;
    (*lvg)->curnum = 0;

    /*Парсинг форматированной строки*/
    status = ___logger_pars((*lvg), (*lvg)->psett->logs_format, &(*lvg)->logs);
    if(status != LE_OK){
        return status;
    }

    status = ___logger_pars((*lvg), (*lvg)->psett->atom_format, &(*lvg)->atom);
    if(status != LE_OK){
        return status;
    }

    status = ___logger_pars((*lvg), (*lvg)->psett->head_format, &(*lvg)->head);
    if(status != LE_OK){
        return status;
    }

    status = ___logger_pars((*lvg), (*lvg)->psett->gerr_format, &(*lvg)->gerr);
    if(status != LE_OK){
        return status;
    }

    return LE_OK;
}

logger_error ___free_tokens(___logger_tokens* tokens){
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

    return LE_OK;
}

logger_error yaya_log_free(void* lvgv)
{
    logger *lvg = (logger*)(lvgv);

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

    return LE_OK;
}

