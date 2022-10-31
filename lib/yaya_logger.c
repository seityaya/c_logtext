//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

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


logger_error yaya_log_init(void**          logger_ptr,
                           logger_filter*  level_one,
                           logger_filter*  level_two,
                           logger_setting* setting,
                           logger_define*  define,
                           logger_style*   style)
{
    logger_error status = LE_ERR;
    logger **lvg = (logger**)(logger_ptr);

    if(lvg == NULL){
        return LE_ERR;
    }

    /*Выделение памяти для главной структуры*/
    *lvg = calloc(1, sizeof(logger));
    if((*lvg) == NULL){
        return LE_ALLOC;
    }

    /*Cвязывание указателей*/
    (*lvg)->type.ptr = (level_one != NULL) ? level_one  : logger_type_l1_def;
    (*lvg)->name.ptr = (level_two != NULL) ? level_two  : logger_name_l2_def;
    (*lvg)->psett    = (setting   != NULL) ? setting   : logger_setting_def;
    (*lvg)->pdefn    = (define    != NULL) ? define    : logger_define_def;
    (*lvg)->pstyl    = (style     != NULL) ? style     : logger_style_def;

    (*lvg)->out_offset = 0;
    (*lvg)->absnum     = 0;
    (*lvg)->curnum     = 0;

    /*Подсчет количества флагов*/
    status = ___count_num(&(*lvg)->type);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }

    status = ___count_num(&(*lvg)->name);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }

    /*Инициализация переменных*/
    (*lvg)->tmp_buff_size = LOGGER_TMP_BUFF_SIZE;
    (*lvg)->tmp_buff = calloc((*lvg)->tmp_buff_size, sizeof(char));
    if((*lvg)->tmp_buff == NULL){
        yaya_log_free(logger_ptr);
        return LE_ALLOC;
    }

    (*lvg)->out_buff_size = LOGGER_OUT_BUFF_SIZE;
    (*lvg)->out_buff = calloc((*lvg)->tmp_buff_size, sizeof(char));
    if((*lvg)->out_buff == NULL){
        yaya_log_free(logger_ptr);
        return LE_ALLOC;
    }

    /*Парсинг форматированной строки*/
    status = ___logger_pars((*lvg), (*lvg)->psett->logs_format, &(*lvg)->logs);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }

#if (LOGGER_STATIC == LOGGER_OFF)
    status = ___logger_pars((*lvg), (*lvg)->psett->atom_format, &(*lvg)->atom);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }
#endif

    status = ___logger_pars((*lvg), (*lvg)->psett->head_format, &(*lvg)->head);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }

    status = ___logger_pars((*lvg), (*lvg)->psett->gerr_format, &(*lvg)->gerr);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }

    /*Создание потока вывода*/
    switch ((*lvg)->psett->stream) {
        case LS_STDOUT: {
            (*lvg)->stream = stdout;
            break;
        }
        case LS_STDERR: {
            (*lvg)->stream = stderr;
            break;
        }
        case LS_STDBUF: {
            (*lvg)->stream = NULL;
            if((*lvg)->psett->size_buff < 2){
                yaya_log_free(logger_ptr);
                return LE_ERR;
            }
            break;
        }
        case LS_STDFILE: {
            FILE *file_out = fopen((*lvg)->psett->out_file, "a+");
            if(file_out != NULL){
                (*lvg)->stream = file_out;
            }else{
                yaya_log_free(logger_ptr);
                return LE_ERR;
            }
            break;
        }
        case LS_STDCSV: {
            FILE *file_out = fopen((*lvg)->psett->out_file, "a+");
            if(file_out != NULL){
                (*lvg)->stream = file_out;
            }else{
                yaya_log_free(logger_ptr);
                return LE_ERR;
            }
            break;
        }
    }

    return LE_OK;
}

logger_error yaya_log_func(uintmax_t count,
                           const char* file,
                           uintmax_t line,
                           const char* func,
                           const char* debug,
                           void *logger_ptr,
                           ___l1_type level_one,
                           ___l2_type level_two,
                           const char* mesg,
                           ...)
{
    logger *lvg = (logger*)(logger_ptr);

    if(lvg == NULL){
        return LE_ERR;
    }

    lvg->absnum++;

    if (((uintmax_t)(lvg->psett->type_l1) & (uintmax_t)(level_one)) && ((uintmax_t)(lvg->psett->name_l2) & (uintmax_t)(level_two)))
    {
        char* new_format             = NULL;
        char* new_mesg               = NULL;
        ___logger_tokens* new_tokens = NULL;

        va_list va_mesgptr;
        va_start(va_mesgptr, mesg);

#if (LOGGER_STATIC == LOGGER_OFF)
        _Bool flag_free = 0;
        if(level_one == L_ATOM)
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
            if(level_one == L_HEAD)
            {
                new_mesg   = (char*)(mesg);
                new_format = (lvg->psett->head_format);
                new_tokens = lvg->head;
            }
            else if(level_one == L_GNERR)
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
                                                                 level_one, level_two,
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

logger_error yaya_log_free(void** logger_ptr)
{
    if(logger_ptr == NULL){
        return LE_ERR;
    }

    logger **lvg = (logger**)(logger_ptr);

    if(*lvg == NULL){
        return LE_ERR;
    }

    if(((*lvg)->psett->stream == LS_STDFILE) || ((*lvg)->psett->stream == LS_STDCSV)){
        fclose((*lvg)->stream);
    }

    ___free_tokens((*lvg)->logs);
    ___free_tokens((*lvg)->head);
    ___free_tokens((*lvg)->atom);
    ___free_tokens((*lvg)->gerr);

    free((*lvg)->out_buff);
    (*lvg)->out_buff = NULL;

    free((*lvg)->tmp_buff);
    (*lvg)->tmp_buff = NULL;

    free((*lvg));
    *lvg = NULL;

    logger_ptr = NULL;

    return LE_OK;
}
