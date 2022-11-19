//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#include "yaya_logger.h"
#include "yaya_logger_private.h"

static logger_error count_num(___logger_filters *filter) {
    if(filter == NULL){
        return LE_ERR;
    }

    filter->num = 0;

    if(filter->ptr[0].flag != LOGGER_FLAG_NUL(uintmax_t))
    {
        return LE_ERR;
    }

    for (uintmax_t i = 1; i < sizeof(uintmax_t) * __CHAR_BIT__; i++)
    {
        if((filter->ptr[i].flag & (1ULL << (i)))
           &&
           (filter->ptr[i].flag != LOGGER_FLAG_ALL(uintmax_t))) {
            return LE_ERR;
        }

        if (filter->ptr[i].flag == LOGGER_FLAG_ALL(uintmax_t)) {
            filter->num = i;
            break;
        }
    }
    return LE_OK;
}

static logger_error free_tokens(___logger *lvg, ___logger_tokens* tokens){
    if(tokens == NULL){
        return LE_ERR;
    }

    for(uintmax_t i = 0; i < tokens->num_token; i++)
    {
        if(tokens->mas_opt[i].spe != NULL)
        {
            logger_memory_del(lvg, tokens->mas_opt[i].spe);
            tokens->mas_opt[i].spe = NULL;
        }
    }
    logger_memory_del(lvg, tokens->mas_opt);
    tokens->mas_opt = NULL;

    logger_memory_del(lvg, tokens);
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
    ___logger **lvg = (___logger**)(logger_ptr);

    if(lvg == NULL){
        return LE_ERR;
    }

    /*Выделение памяти для главной структуры*/
    logger_memory_new(*lvg, (void*)(&(*lvg)), NULL, sizeof(___logger));
    if((*lvg) == NULL){
        return LE_ALLOC;
    }

    /*Связывание указателей*/
    (*lvg)->type.ptr = (level_one != NULL) ? level_one  : logger_type_l1_def;
    (*lvg)->name.ptr = (level_two != NULL) ? level_two  : logger_name_l2_def;
    (*lvg)->psett    = (setting   != NULL) ? setting    : logger_setting_def;
    (*lvg)->pdefn    = (define    != NULL) ? define     : logger_define_def;
    (*lvg)->pstyl    = (style     != NULL) ? style      : logger_style_def;

    (*lvg)->out_offset = 0;
    (*lvg)->absnum     = 0;
    (*lvg)->curnum     = 0;
    (*lvg)->recnum     = 0;

    /*Подсчет количества флагов*/
    status = count_num(&(*lvg)->type);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }

    status = count_num(&(*lvg)->name);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }

    /*Инициализация переменных*/
    (*lvg)->tmp_buff_size = LOGGER_TMP_BUFF_SIZE;
    logger_memory_new(*lvg, (void*)(&((*lvg)->tmp_buff)), NULL, sizeof(char) * (*lvg)->tmp_buff_size);
    if((*lvg)->tmp_buff == NULL){
        yaya_log_free(logger_ptr);
        return LE_ALLOC;
    }

    (*lvg)->out_buff_size = LOGGER_OUT_BUFF_SIZE;
    logger_memory_new(*lvg, (void*)(&((*lvg)->out_buff)), NULL, sizeof(char) * (*lvg)->out_buff_size);
    if((*lvg)->out_buff == NULL){
        yaya_log_free(logger_ptr);
        return LE_ALLOC;
    }

    /*Парсинг форматированной строки*/
    status = logger_pars((*lvg), (*lvg)->psett->logs_format, &(*lvg)->logs_f);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }

#if LOGGER_FORMAT_HEAD
    status = logger_pars((*lvg), (*lvg)->psett->head_format, &(*lvg)->head_f);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }
#endif
#if LOGGER_FORMAT_ATOM
    status = logger_pars((*lvg), (*lvg)->psett->atom_format, &(*lvg)->atom_f);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }
#endif
#if LOGGER_FORMAT_FREE
    status = logger_pars((*lvg), (*lvg)->psett->free_format, &(*lvg)->free_f);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }
#endif
#if LOGGER_FORMAT_ERROR
    status = logger_pars((*lvg), (*lvg)->psett->gerr_format, &(*lvg)->gerr);
    if(status != LE_OK){
        yaya_log_free(logger_ptr);
        return status;
    }
#endif

    /*Создание потока вывода*/
#if (((LOGGER_OUT) != LOGGER_OFF))
    switch ((*lvg)->psett->stream) {
#if (((LOGGER_OUT) & DLS_STDOUT) || (LOGGER_OUT == LOGGER_ON))
        case LS_STDOUT: {
            (*lvg)->stream = stdout;
            break;
        }
#endif
#if (((LOGGER_OUT) & DLS_STDERR) || (LOGGER_OUT == LOGGER_ON))
        case LS_STDERR: {
            (*lvg)->stream = stderr;
            break;
        }
#endif
#if (((LOGGER_OUT) & DLS_STDBUF) || (LOGGER_OUT == LOGGER_ON))
        case LS_STDBUF: {
            (*lvg)->stream = NULL;
            if((*lvg)->psett->size_buff < 2){
                yaya_log_free(logger_ptr);
                return LE_ERR;
            }
            break;
        }
#endif
#if (((LOGGER_OUT) & DLS_STDFILE) || (LOGGER_OUT == LOGGER_ON))
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
#endif
#if (((LOGGER_OUT) & DLS_STDCSV) || (LOGGER_OUT == LOGGER_ON))
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
#endif
    }
#endif
    return LE_OK;
}

logger_error yaya_log_func(uintmax_t count,
                           const char* file,
                           uintmax_t line,
                           const char* func,
                           const char* generic,
                           void *logger_ptr,
                           logger_l1_type level_one,
                           logger_l2_type level_two,
                           const char* mesg,
                           ...)
{
    ___logger *lvg = (___logger*)(logger_ptr);

    if(lvg == NULL){
        return LE_ERR;
    }

    lvg->absnum++;

    if (((uintmax_t)(lvg->psett->type_l1) & (uintmax_t)(level_one))
        &&
        ((uintmax_t)(lvg->psett->name_l2) & (uintmax_t)(level_two)))
    {
        char* new_format             = NULL;
        char* new_mesg               = NULL;
        ___logger_tokens* new_tokens = NULL;

        va_list va_mesgptr;
        va_start(va_mesgptr, mesg);

#if LOGGER_FORMAT_ATOM || LOGGER_FORMAT_FREE
        bool flag_free = false;
#endif

#if LOGGER_FORMAT_ATOM
        if(level_one == L_ATOM)
        {
            if((mesg == NULL) || (mesg[0] != ___logger_token_list[LEF_TOK].name[0]))
            {
                new_mesg   = (char*)(mesg);
                new_format = (lvg->psett->atom_format);
                new_tokens = lvg->atom_f;
            }
            else
            {
                new_mesg   = va_arg(va_mesgptr, char *);
                new_format = (char*)(mesg);
                logger_error status = logger_pars(lvg, new_format, &new_tokens);
                flag_free = true;
                if(status != LE_OK){
                    goto end;
                }
            }
        }
        else
#endif
#if LOGGER_FORMAT_HEAD
            if(level_one == L_HEAD)
            {
                new_mesg   = (char*)(mesg);
                new_format = (lvg->psett->head_format);
                new_tokens = lvg->head_f;
            }
            else
#endif
#if LOGGER_FORMAT_FREE
                if(level_one == L_FREE)
                {
                    new_mesg   = (char*)(mesg);
                    new_format = (lvg->psett->free_format);
                    new_tokens = lvg->free_f;
                }
                else
#endif
#if LOGGER_FORMAT_ERROR
                    if(level_one == L_GNERR)
                    {
                        new_mesg   = (char*)(mesg);
                        new_format = (lvg->psett->gerr_format);
                        new_tokens = lvg->gerr;
                    }
                    else
#endif
                    {
                        new_mesg   = (char*)(mesg);
                        new_format = (lvg->psett->logs_format);
                        new_tokens = lvg->logs_f;
                    }

        lvg->curnum++;

#if LOGGER_RECURSION
#define POSITIV(a) (a) > 0 ? (a) : (-(a))
#define NEGITIV(a) (a) < 0 ? (a) : (-(a))
        if(level_one == L_BEGF){
            lvg->recnum = POSITIV(lvg->recnum);
            lvg->recnum++;
        }

        if(level_one == L_ENDF){
            lvg->recnum = NEGITIV(lvg->recnum);
        }
#undef POSITIV
#undef NEGITIV
#endif
        for (uintmax_t i = 0; i < new_tokens->num_token; i++) {
            memset(lvg->tmp_buff, 0, lvg->tmp_buff_size); // TODO(yaya): del
            ___logger_token_list[new_tokens->mas_opt[i].id].func(lvg, new_format, &new_tokens->mas_opt[i],
                                                                 count, file, line, func, generic,
                                                                 level_one, level_two,
                                                                 new_mesg, va_mesgptr);
        }
#if LOGGER_RECURSION
        if(level_one == L_ENDF){
            lvg->recnum++;
        }
#endif

#if LOGGER_STYLE
        logger_styles(lvg);
#endif

        logger_out(lvg);

#if LOGGER_FORMAT_ATOM || LOGGER_FORMAT_FREE
end:
        if(flag_free)
        {
            free_tokens(lvg, new_tokens);
        }
#endif
        va_end(va_mesgptr);
    }

    return LE_OK;
}

logger_error yaya_log_free(void** logger_ptr)
{
    ___logger **lvg = (___logger**)(logger_ptr);

    if(lvg == NULL){
        return LE_ERR;
    }

    if(*lvg == NULL){
        return LE_ERR;
    }

#if (((LOGGER_OUT) & (DLS_STDFILE | DLS_STDCSV)) || (LOGGER_OUT == LOGGER_ON))
    if(((*lvg)->psett->stream == LS_STDFILE) || ((*lvg)->psett->stream == LS_STDCSV)){
        fclose((*lvg)->stream);
    }
#endif

    free_tokens(*lvg, (*lvg)->logs_f);
#if LOGGER_FORMAT_HEAD
    free_tokens(*lvg, (*lvg)->head_f);
#endif
#if LOGGER_FORMAT_ATOM
    free_tokens(*lvg, (*lvg)->atom_f);
#endif
#if LOGGER_FORMAT_FREE
    free_tokens(*lvg, (*lvg)->free_f);
#endif
#if LOGGER_FORMAT_ERROR
    free_tokens(*lvg, (*lvg)->gerr);
#endif

    logger_memory_del(*lvg, (*lvg)->out_buff);
    (*lvg)->out_buff = NULL;

    logger_memory_del(*lvg, (*lvg)->tmp_buff);
    (*lvg)->tmp_buff = NULL;

    logger_memory_del(*lvg, *lvg);
    *lvg = NULL;

    logger_ptr = NULL;

    return LE_OK;
}
