#include "yaya_logger.h"
#include "yaya_logger_private.h"

static logger_error ___count_num(___logger_filters *filter) {
    filter->num = 0;
    for (uintmax_t i = 0; i < sizeof(uintmax_t) * __CHAR_BIT__; i++)
    {
        if(((i == 0) ? (0) : (filter->ptr[i].flag & (1ULL << (i)))) && !(filter->ptr[i].flag == LOGGER_FLAG_ALL(uintmax_t))) {
            return LE_ERR;
        }

        if (filter->ptr[i].flag == LOGGER_FLAG_ALL(uintmax_t)) {
            filter->num = i;
            break;
        }
    }
    return LE_OK;
}

static logger_error ___free_tokens(___logger_tokens* tokens){
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


logger_error yaya_log_init(void**          lvgv,
                           logger_filter*  type_one,
                           logger_filter*  type_two,
                           logger_setting* setting,
                           logger_define*  define,
                           logger_style*   style)
{
    logger_error status = LE_ERR;
    logger **lvg = (logger**)(lvgv);

    if(lvg == NULL){
        return LE_ERR;
    }

    /*Выделение памяти для главной структуры*/
    *lvg = calloc(1, sizeof(logger));
    if((*lvg) == NULL){
        return LE_ALLOC;
    }

    /*Cвязывание указателей*/
    (*lvg)->type.ptr = (type_one  != NULL) ? type_one  : logger_type_l1_def;
    (*lvg)->name.ptr = (type_two  != NULL) ? type_two  : logger_name_l2_def;
    (*lvg)->psett    = (setting   != NULL) ? setting   : logger_setting_def;
    (*lvg)->pdefn    = (define    != NULL) ? define    : logger_define_def;
    (*lvg)->pstyl    = (style     != NULL) ? style     : logger_style_def;

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

logger_error yaya_log_func(uintmax_t count, const char* file, uintmax_t line, const char* func, const char* debug, void *lvgv, ___l1_type type_one, ___l2_type type_two, const char* mesg, ...)
{
    logger *lvg = (logger*)(lvgv);

    if(lvg == NULL){
        return LE_ERR;
    }

    lvg->absnum++;

    if (((uintmax_t)(lvg->psett->type_l1) & (uintmax_t)(type_one)) && ((uintmax_t)(lvg->psett->name_l2) & (uintmax_t)(type_two)))
    {
        char* new_format             = NULL;
        char* new_mesg               = NULL;
        ___logger_tokens* new_tokens = NULL;

        va_list va_mesgptr;
        va_start(va_mesgptr, mesg);

#if (LOGGER_STATIC == LOGGER_OFF)

        _Bool flag_free = 0;
        if(type_one == L_ATOM)
        {
            if((mesg == NULL) || (mesg[0] != ___logger_token_list[LEF_TOK].name[0]))
            {
                new_mesg   = (char*)(mesg);
                new_format = (lvg->psett->atom_format);
                new_tokens = lvg->atom;
            }
            else
            {
                new_mesg   = va_arg(va_mesgptr, char *);
                new_format = (char*)(mesg);
                logger_error status = ___logger_pars(lvg, new_format, &new_tokens);
                flag_free = 1;
                if(status != LE_OK){
                    goto end;
                }
            }
        }
        else
#endif
            if(type_one == L_HEAD)
            {
                new_mesg   = (char*)(mesg);
                new_format = (lvg->psett->head_format);
                new_tokens = lvg->head;
            }
            else if(type_one == L_GNERR)
            {
                new_mesg   = (char*)(mesg);
                new_format = (lvg->psett->gerr_format);
                new_tokens = lvg->gerr;
            }
            else
            {
                new_mesg   = (char*)(mesg);
                new_format = (lvg->psett->logs_format);
                new_tokens = lvg->logs;
            }

        lvg->curnum++;

        for (uintmax_t i = 0; i < new_tokens->num_token; i++) {
            memset(lvg->tmp_buff, 0, lvg->tmp_buff_size);
            ___logger_token_list[new_tokens->mas_opt[i].id].func(lvg, new_format, &new_tokens->mas_opt[i],
                                                                 count, file, line, func, debug,
                                                                 type_one, type_two,
                                                                 new_mesg, va_mesgptr);
        }

#if (LOGGER_STYLE == LOGGER_ON)
        ___logger_styles(lvg);
#endif

#if (LOGGER_OUT == LOGGER_ON)
        ___logger_out(lvg);
#endif

#if (LOGGER_STATIC == LOGGER_OFF)
end:
        if(flag_free == 1)
        {
            ___free_tokens(new_tokens);
        }
#endif
        va_end(va_mesgptr);
    }

    return LE_OK;
}

logger_error yaya_log_free(void* lvgv)
{
    logger *lvg = (logger*)(lvgv);

    if(lvg == NULL){
        return LE_ERR;
    }

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
