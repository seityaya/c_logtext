#include "yaya_logger.h"
#include "yaya_logger_test.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void yaya_log_init(logger_list *type, logger_list *name, logger_setting *setting, logger_define *define, logger_style *style) {
    logger_variables *lvg;
    lvg = logger_variables_global;
    lvg->log_init = TRUE;
    lvg->type = type;
    lvg->name = name;
    lvg->sett = setting;
    lvg->defn = define;
    lvg->styl = style;

    //calculating the number of types in a list
    for (uintmax_t i = 0; i < sizeof(uintmax_t) * 8; i++) {
        if (lvg->type[i].flag == FLAG_ALL) {
            lvg->type_num = lvg->type[i].n;
            break;
        }
    }

    //calculating the number of names in a list
    for (uintmax_t i = 0; i < sizeof(uintmax_t) * 8; i++) {
        if (lvg->name[i].flag == FLAG_ALL) {
            lvg->name_num = lvg->name[i].n;
            break;
        }
    }

    PRINTX(lvg->defn->prog, s);
    PRINTX(lvg->sett->format_head, s);
    PRINTX(lvg->sett->format_logs, s);
    PRINTX(lvg->type_num, ld);
    PRINTX(lvg->name_num, ld);
}

void yaya_log_func(
    char *data, char *time, char *file, uintmax_t line, uintmax_t count, const char *func, uintmax_t type, uintmax_t name, const char *mes, ...) {
    logger_variables *lvg;
    lvg = logger_variables_global;
    if (lvg->log_init == FALSE) {
        lvg->log_init = TRUE;
        lvg->type = logger_type_def;
        lvg->name = logger_name_def;
        lvg->sett = logger_setting_def;
        lvg->defn = logger_define_def;
        lvg->styl = logger_style_def;
        printf("LOGER INIT WORK\n");
    }
    if (lvg->log_head == FALSE || lvg->sett->log_head == TRUE) {
        lvg->log_head = TRUE;
        lvg->sett->log_head = FALSE;
        yaya_log_head();
    }

    printf("LOGER WORK\n");
}

void yaya_log_head(void) {
    printf("LOGER HEADER WORK\n");
}

int main(int argc, char *argv[]) {
    logger_define_def->prog = "my_prog";
    log_init(logger_type_def, logger_name_def, logger_setting_def, logger_define_def, logger_style_def);

    log(L_BEGF);
    //log_test_fnc();
    //log_test_mac();

    log(L_ENDF);
    return 0;
}
