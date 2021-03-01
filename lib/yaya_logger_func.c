#include "yaya_logger.h"

uintmax_t yaya_log_func(uintmax_t count, char *file, uintmax_t line, const char *func, const char* debug, ___logger *lvg, ___l1_type type_one, ___l2_type type_two, const char *mesg, ...) {

    char* new_format = malloc(300);
    new_format = NULL;
    char* new_mesg = malloc(300);
    new_mesg = NULL;
    uintmax_t temp_num_token = 0;       // - количество токенов в форматной строке логгера
    ___logger_token_mas *temp_mas_opt = NULL; // - указатель на структуру со смещениями токенов заголовка

    va_list va_mesgptr;
    va_start(va_mesgptr, mesg);

    if(type_one == L_HEAD || type_one == L_ATOM)
    {
        if(type_one == L_HEAD){
            type_one = L_HEAD;

            if(mesg == NULL) {
                new_format = (char*)lvg->psett->head_format;
            }else{
                new_format = (char*)mesg;
            }
        }else{
            type_one = L_ATOM;

            if(mesg == NULL) {
                new_format = (char*)lvg->psett->atom_format;
            }else{
                new_format = (char*)mesg;
            }
        }

        ___logger_pars(lvg, new_format, &temp_mas_opt, &temp_num_token);

        new_mesg =  va_arg(va_mesgptr, char *);
    }
    else
    {
        if (!(lvg->psett->type & type_one) && !(lvg->psett->name & type_two)) {
            goto end;
        }
        lvg->curnum++;

        new_format = (char*)lvg->psett->logs_format;
        new_mesg   = (char*)mesg;
        temp_mas_opt = lvg->logs_mas_opt;
        temp_num_token = lvg->logs_num_token;

    }

    for (uintmax_t i = 0; i < temp_num_token; i++) {
        memset(lvg->tmp_buff, 0, LOGGER_TMP_BUFF_SIZE);
        ___logger_token_list[temp_mas_opt[i].id].func(lvg, new_format, &temp_mas_opt[i],
                                                      count, file, line, func, debug,
                                                      type_one, type_two,
                                                      new_mesg, va_mesgptr);
    }

    ___logger_styles(lvg);
    ___logger_out(lvg);
    lvg->absnum++;
end:
    va_end(va_mesgptr);
    if(type_one == L_HEAD || type_one == L_ATOM)
    {
        free(temp_mas_opt);
    }
    return LOGGER_TRUE;
}

uintmax_t yaya_log_defl(uintmax_t count, char *file, uintmax_t line, const char *func, const char* debug,  ___logger *lvg){
    printf("%s   ERROR: %s %ju %s \n", debug, file, line, func);
    return LOGGER_TRUE;
}
