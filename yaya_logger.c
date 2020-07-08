#include "yaya_logger.h"
#include "yaya_logger_func.h"
#include "yaya_logger_test.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* 
 * Инициализация
 * Разбор форматной строки заголовка/логера
 * Запись в массив смещений в logger_variables_global
 * Инициализация logger_variables_global оставшихся перменных
 * Инициализация структуры logger_define
 * 
 * Заголовок
 * Вовод информации согласно форматной строке
 * 
 * Логер
 * Вовод информации согласно форматной строке
 * 
 * Дальнейшие улучшения
 * Вывод в другие потоки
 * Цветной вывод
 */

void yaya_log_init(logger_list *type, logger_list *name, logger_setting *setting, logger_define *define, logger_style *style) {
    //printf("LOGER INIT WORK\n");
    logger_variables *lvg;
    lvg = logger_variables_global;
    lvg->log_init_flag = TRUE;
    lvg->ptype = type;
    lvg->pname = name;
    lvg->psett = setting;
    lvg->pdefn = define;
    lvg->pstyl = style;

    //calculating the number of types in a list
    for (uintmax_t i = 0; i < sizeof(uintmax_t) * 8; i++) {
        if (lvg->ptype[i].flag == FLAG_ALL) {
            lvg->type_num = lvg->ptype[i].n;
            break;
        }
    }

    //calculating the number of names in a list
    for (uintmax_t i = 0; i < sizeof(uintmax_t) * 8; i++) {
        if (lvg->pname[i].flag == FLAG_ALL) {
            lvg->name_num = lvg->pname[i].n;
            break;
        }
    }

    //PRINTX(lvg->defn->prog, s);
    //PRINTX(lvg->sett->format_head, s);
    //PRINTX(lvg->sett->format_logs, s);
    //PRINTX(lvg->type_num, ld);
    //PRINTX(lvg->name_num, ld);
}

void yaya_log_head(void) {
    logger_variables *lvg;
    lvg = logger_variables_global;
    lvg->log_head_flag = TRUE;
}

void yaya_log_func(uintmax_t count, char *file, uintmax_t line, const char *func, uintmax_t type, uintmax_t name, const char *mes, ...) {
    logger_variables *lvg;
    lvg = logger_variables_global;
    /* Инициализация */
    if (lvg->log_init_flag == FALSE) {
        log_init(logger_type_def, logger_name_def, logger_setting_def, logger_define_def, logger_style_def);
    }
    /* Заголовок */
    if (lvg->log_head_flag == FALSE && lvg->psett->log_head == TRUE) {
        yaya_log_head();
    }
    /* Логгер */
    if ((lvg->psett->type & type) || (lvg->psett->name & name)) {
        for (uintmax_t i = 0; i < lvg->type_num - 1; i++) {
            if (lvg->psett->type == L_ALL) {
                printf("%s ", lvg->ptype[lvg->type_num].name);
                break;
            } else if (lvg->psett->type == L_NUL) {
                printf("%s ", lvg->ptype[0].name);
                break;
            } else {
                if (BIT_GET(lvg->psett->type, i)) {
                    printf("%s ", lvg->ptype[i + 1].name);
                }
            }
        }

        for (uintmax_t i = 0; i < lvg->name_num - 1; i++) {
            if (lvg->psett->name == L_ALL) {
                printf("%s ", lvg->pname[lvg->name_num].name);
                break;
            } else if (lvg->psett->name == L_NUL) {
                printf("%s ", lvg->pname[0].name);
                break;
            } else {
                if (BIT_GET(lvg->psett->name, i)) {
                    printf("%s ", lvg->pname[i + 1].name);
                }
            }
        }

        for (uintmax_t i = 0; i < lvg->type_num; i++) {
            if (BIT_GET(type, i)) {
                printf("%s ", logger_type_def[i + 1].name);
            }
        }
        for (uintmax_t i = 0; i < lvg->name_num; i++) {
            if (BIT_GET(name, i)) {
                printf("%s ", logger_name_def[i + 1].name);
            }
        }
        va_list list;
        va_start(list, mes);
        vprintf(mes, list);
        va_end(list);
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    log(L_BEGF, LL_MAIN, "Старт программы");

    printf("%s   ", &logger_setting_def->format_head[0]);
    printf("%c   ", logger_format_list[LEF_SEPARATOR].name[0]);
    printf("\n");

    for (uintmax_t i = 0; i < strlen(logger_setting_def->format_head); i++) {
        if (logger_setting_def->format_head[i] == logger_format_list[LEF_SEPARATOR].name[0]) {
            printf("%d \n", i);
        }
    }

    log(L_ENDF, LL_MAIN, "Стоп программы");
    return 0;
}
