#include "yaya_logger.h"
#include "yaya_logger_private.h"

#include <string.h>

logger_error yaya_log_func(uintmax_t count, const char* file, uintmax_t line, const char* func, const char* debug, void *lvgv, ___l1_type type_one, ___l2_type type_two, const char* mesg, ...)
{
    logger *lvg = (logger*)(lvgv);
    lvg->absnum++;

    if (((uintmax_t)(lvg->psett->type) & (uintmax_t)(type_one)) && ((uintmax_t)(lvg->psett->name) & (uintmax_t)(type_two)))
    {
        char* new_format             = NULL;
        char* new_mesg               = NULL;
        ___logger_tokens* new_tokens = NULL;
        _Bool flag_free = 0;

        va_list va_mesgptr;
        va_start(va_mesgptr, mesg);

        if(type_one == L_HEAD || type_one == L_ATOM || type_one == L_GNERR)
        {
            if(type_one == L_ATOM){
                if(mesg == NULL)
                {
                    new_mesg   = (char*)(mesg);
                    new_format = (char*)(lvg->psett->atom_format);
                    new_tokens = lvg->atom;
                }
                else if(mesg[0] != ___logger_token_list[LEF_TOK].name[0] )
                {
                    new_mesg   = (char*)(mesg);
                    new_format = (char*)(lvg->psett->atom_format);
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

            if(type_one == L_HEAD){
                new_mesg   = (char*)(mesg);
                new_format = (char*)(lvg->psett->head_format);
                new_tokens = lvg->head;
            }

            if(type_one == L_GNERR){
                new_mesg   = (char*)(mesg);
                new_format = (char*)(lvg->psett->gerr_format);
                new_tokens = lvg->gerr;
            }
        }
        else
        {
            new_mesg   = (char*)(mesg);
            new_format = (char*)(lvg->psett->logs_format);
            new_tokens   = lvg->logs;
        }

        lvg->curnum++;

        for (uintmax_t i = 0; i < new_tokens->num_token; i++) {
            memset(lvg->tmp_buff, 0, lvg->tmp_buff_size);
            ___logger_token_list[new_tokens->mas_opt[i].id].func(lvg, new_format, &new_tokens->mas_opt[i],
                                                                 count, file, line, func, debug,
                                                                 type_one, type_two,
                                                                 new_mesg, va_mesgptr);
        }
#if (LOGGER_STYLE != 0)
        ___logger_styles(lvg);
#endif

#if (LOGGER_OUT != 0)
        ___logger_out(lvg);
#endif

end:
        if(flag_free == 1)
        {
            ___free_tokens(new_tokens);
        }

        va_end(va_mesgptr);

        return LE_OK;
    }
    return LE_OK;
}

