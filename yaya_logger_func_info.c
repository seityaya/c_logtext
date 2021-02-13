#include "yaya_logger.h"

uintmax_t yaya_log_info(logger *lvg, uintmax_t count, char *file, uintmax_t line, const char *func, const char *mesg, ...) {
     if(mas_opt(lvg, mesg, &lvg->temp_mas_opt, &lvg->temp_num_token) == 0){
       return 0;
     }

     va_list mesgptr;
     va_start(mesgptr, mesg);
     logger_build(lvg, lvg->psett->logs_format, lvg->logs_mas_opt, &lvg->logs_num_token, &count, file, &line, func, L_NUL, LL_NUL, mesg, mesgptr);
     va_end(mesgptr);

     free(lvg->temp_mas_opt);
     return 1;
}
