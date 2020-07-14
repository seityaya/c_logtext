#include "yaya_logger.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

logger_variables *lvg = logger_variables_global;

void yaya_log_init(logger_list *type, logger_list *name, logger_setting *setting, logger_define *define, logger_style *style) {
    lvg->init_flag = LOGGER_TRUE;

    { /*Cвязывание указателей*/
        lvg->pglob = logger_variables_global;
        lvg->ptype = type;
        lvg->psett = setting;
        lvg->pdefn = define;
        lvg->pname = name;
        lvg->pstyl = style;
    }

    {
        /*Инициализация переменных*/
        lvg->out_buff = calloc(2000, sizeof(char));
        lvg->out_ofset = 0;
        lvg->data_build = __DATE__;
        lvg->time_build = __TIME__;
        lvg->projpath = "/../../";
        lvg->absnum = 0;
        lvg->curnum = 0;
    }

    { /*Подсчет количества флагов типа*/
        for (uintmax_t i = 0; i < sizeof(uintmax_t) * 8; i++) {
            if (lvg->ptype[i].flag == LOGGER_FLAG_ALL) {
                lvg->type_num = lvg->ptype[i].id;
                break;
            }
        }
    }

    { /*Подсчет количества флагов имени*/
        for (uintmax_t i = 0; i < sizeof(uintmax_t) * 8; i++) {
            if (lvg->pname[i].flag == LOGGER_FLAG_ALL) {
                lvg->name_num = lvg->pname[i].id;
                break;
            }
        }
    }

    { /*Парсинг форматированой строки*/
#if LOGGER_HEAD == LOGGER_TRUE
        lvg->head_mas_opt = mas_opt(lvg->psett->head_format, lvg->head_mas_opt, &lvg->head_num_token);
#endif
        lvg->logs_mas_opt = mas_opt(lvg->psett->logs_format, lvg->logs_mas_opt, &lvg->logs_num_token);
    }
}

#if LOGGER_HEAD == LOGGER_TRUE
void yaya_log_head(uintmax_t count, char *file, uintmax_t line, const char *func, const char *mesg, ...) {
    lvg->head_flag = LOGGER_TRUE;
}
#endif

void yaya_log_func(uintmax_t count, char *file, uintmax_t line, const char *func, uintmax_t type, uintmax_t name, const char *mesg, ...) {
#if LOGGER_AUTO_INIT == LOGGER_TRUE
    /*Инициализация*/
    if (lvg->init_flag == FALSE) {
        log_init(logger_type_def, logger_name_def, logger_setting_def, logger_define_def, logger_style_def);
    }
#endif

#if LOGGER_AUTO_HEAD == LOGGER_TRUE && LOGGER_HEAD == LOGGER_TRUE
    /*Заголовок*/
    if (lvg->head_flag == FALSE && &lvg->psett->head_format[0] != NULL) {
        log_head("\0");
    }
#endif

    lvg->absnum++;
    /*Логгер*/
    if ((lvg->psett->type & type) || (lvg->psett->name & name)) {
        lvg->curnum++;
        /*Формат*/
        va_list mesgptr;
        va_start(mesgptr, mesg);
        logger_build(lvg->psett->logs_format, lvg->logs_mas_opt, &lvg->logs_num_token, &count, file, &line, func, type, name, mesg, mesgptr);
        va_end(mesgptr);
    }
}

void logger_build(const char *format,
                  logger_format_mas *mas_opt,
                  uintmax_t *num_token,
                  uintmax_t *count,
                  char *file,
                  uintmax_t *line,
                  const char *func,
                  uintmax_t type,
                  uintmax_t name,
                  const char *mesg,
                  ...) {
    for (uintmax_t i = 0; i < *num_token; i++) {
        char buff[1000] = {0};
        {
            switch (mas_opt[i].id) {
            case LEF_STR: {
                strncpy(buff, &format[mas_opt[i].beg], mas_opt[i].end - mas_opt[i].beg + 1);
                format_build_str(&mas_opt[i], buff);
                break;
            }
            case LEF_LINE: {
                format_build_num(&mas_opt[i], line);
                break;
            }
            case LEF_FILENAME: {
                format_build_str(&mas_opt[i], file);
                break;
            }
            case LEF_FUNC: {
                format_build_str(&mas_opt[i], func);
                break;
            }
            case LEF_COUNT: {
                format_build_num(&mas_opt[i], count);
                break;
            }
            case LEF_MESAGE: {
                va_list list;
                va_start(list, mesg);
                vsprintf(buff, mesg, list);
                va_end(list);
                format_build_str(&mas_opt[i], buff);
                break;
            }
            case LEF_TYPE: {
                for (uintmax_t j = 0; j < lvg->type_num - 1; j++) {
                    if (type == L_ALL) {
                        format_build_str(&mas_opt[i], &logger_type_def[lvg->type_num].name[2]);
                    } else if (type == L_NUL) {
                        format_build_str(&mas_opt[i], &logger_type_def[0].name[2]);
                    } else {
                        if (LOGGER_BIT_GET(type, j)) {
                            format_build_str(&mas_opt[i], &logger_type_def[j + 1].name[2]);
                        }
                    }
                }
                break;
            }
            case LEF_NAME: {
                for (uintmax_t j = 0; j < lvg->name_num - 1; j++) {
                    if (name == LL_ALL) {
                        format_build_str(&mas_opt[i], &logger_name_def[lvg->name_num].name[3]);
                    } else if (name == LL_NUL) {
                        format_build_str(&mas_opt[i], &logger_name_def[0].name[3]);
                    } else {
                        if (LOGGER_BIT_GET(name, j)) {
                            format_build_str(&mas_opt[i], &logger_name_def[j + 1].name[3]);
                        }
                    }
                }
                break;
            }
            case LEF_CURNUM: {
                format_build_num(&mas_opt[i], &lvg->pglob->curnum);
                break;
            }
            case LEF_ABSNUM: {
                format_build_num(&mas_opt[i], &lvg->pglob->absnum);
                break;
            }

                //            case LEF_PROG: {
                //                format_build_str(&mas_opt[i], lvg->pdefn->prog);
                //                break;
                //            }
                //            case LEF_PROJPATH: {
                //                format_build_str(&mas_opt[i], lvg->pglob->projpath);
                //                break;
                //            }
                //            case LEF_PROJ: {
                //                format_build_str(&mas_opt[i], lvg->pglob->proj);
                //                break;
                //            }
                //            case LEF_VERSION: {
                //                format_build_str(&mas_opt[i], lvg->pdefn->version);
                //                break;
                //            }
                //            case LEF_DATA_BUILD: {
                //                format_build_str(&mas_opt[i], lvg->pglob->data_build);
                //                break;
                //            }
                //            case LEF_TIME_BUILD: {
                //                format_build_str(&mas_opt[i], lvg->pglob->time_build);
                //                break;
                //            }
                //            case LEF_SEED: {
                //                format_build_num(&mas_opt[i], &lvg->pdefn->seed);
                //                break;
                //            }
                //            case LEF_COMPILER: {
                //                format_build_str(&mas_opt[i], lvg->pglob->compiler);
                //                break;
                //            }
                //            case LEF_TIKSEC: {
                //                break;
                //            }
                //            case LEF_DATA: {
                //                sprintf(buff, "%d", 0);
                //                strcat(lvg->out_buff, buff);
                //                break;
                //            }
                //            case LEF_TIME: {
                //                sprintf(buff, "%d", 0);
                //                strcat(lvg->out_buff, buff);
                //                break;
                //            }
                //            case LEF_FULLPATH: {
                //                break;
                //            }
                //            case LEF_SHORPATH: {
                //                break;
                //            }
                //            case LEF_ALIGNL: {
                //                break;
                //            }
                //            case LEF_ALIGGT: {
                //                break;
                //            }
                //            case LEF_NAME_ALL: {
                //            { /*вывод настроек фильтрации*/
                //                for (uintmax_t i = 0; i < lvg->type_num - 1; i++) {
                //                    if (lvg->psett->type == L_ALL) {
                //                        printf("%s ", lvg->ptype[lvg->type_num].name);
                //                        break;
                //                    } else if (lvg->psett->type == L_NUL) {
                //                        printf("%s ", lvg->ptype[0].name);
                //                        break;
                //                    } else {
                //                        if (BIT_GET(lvg->psett->type, i)) {
                //                            printf("%s ", lvg->ptype[i + 1].name);
                //                        }
                //                    }
                //                }
                //            }
                //            }
            default: {
                printf("WORNING: NOT FIND TOKEN = %s \n", logger_format_list[i].name);
                break;
            }
            }
        }
    }

#if LOGGER_STYLE == LOGGER_TRUE
    /*Стили*/
    style_build();
#endif
    /*Вывод*/
    logger_out();
}

logger_format_mas *mas_opt(const char *format, logger_format_mas *mas_opt, uintmax_t *num_token) {
    { /*Подсчет колличества токенов и спецификаторов, выделение памяти и определение их диапазона и типа*/
        uintmax_t j = 0;
        for (uintmax_t i = 0; i < strlen(format); i++) {
            mas_opt = realloc(mas_opt, sizeof(logger_format_mas) * (j + 1));
            if (format[i] == logger_format_list[LEF_TOK].name[0] && isalpha(format[i + 1])) {
                mas_opt[j].id = LEF_TOK;
                mas_opt[j].beg = i;
                do {
                    mas_opt[j].end = i;
                    i++;
                } while (isalpha(format[i]));
                if (format[i] == logger_format_list[LEF_SPE].name[0]
                    && (isdigit(format[i + 1]) || format[i + 1] == logger_format_list[LEF_HID].name[0]
                        || format[i + 1] == logger_format_list[LEF_SEP].name[0])) {
                    mas_opt[j].spe = calloc(1, sizeof(logger_format_specifiers));
                    mas_opt[j].spe->beg = i;
                    do {
                        mas_opt[j].spe->end = i;
                        i++;
                    } while (isdigit(format[i]) || format[i] == logger_format_list[LEF_HID].name[0]
                             || format[i] == logger_format_list[LEF_SEP].name[0]);
                }
                i--;
            } else {
                mas_opt[j].beg = i;
                mas_opt[j].id = LEF_STR;
                do {
                    mas_opt[j].end = i;
                    i++;
                } while (!(format[i] == logger_format_list[LEF_TOK].name[0] && isalpha(format[i + 1])) && (format[i] != '\0'));
                i--;
            }
            j++;
        }
        *num_token = j;
    }

    { /*Определение типа токенов*/
        for (uintmax_t i = 0; i < *num_token; i++) {
            char buff[50] = {0};
            if (mas_opt[i].id == LEF_TOK) {
                strncpy(buff, &format[mas_opt[i].beg + 1], mas_opt[i].end - mas_opt[i].beg);
                for (uintmax_t j = 0; j < LEF_END; j++) {
                    if (strstr(buff, logger_format_list[j].name) != NULL) {
                        mas_opt[i].type = logger_format_list[j].type;
                        mas_opt[i].id = j;
                        break;
                    }
                }
            }
        }
    }

    { /*Парсинг спецификаторов*/
        for (uintmax_t i = 0; i < *num_token; i++) {
            if (mas_opt[i].spe != NULL) {
                char buff[10] = {0};
                strncpy(buff, &format[mas_opt[i].spe->beg], mas_opt[i].spe->end - mas_opt[i].spe->beg + 1);
                int l = 0;
                int k = 0;
                int beg = 0;
                int end = 0;
                if (mas_opt[i].type == F_STR) {
                    l = 0;
                    if (format[mas_opt[i].spe->beg + 1] == logger_format_list[LEF_HID].name[0]) {
                        l++;
                        mas_opt[i].spe->fes = FES_LEFHIDE;
                    }
                    if (format[mas_opt[i].spe->end] == logger_format_list[LEF_HID].name[0] && mas_opt[i].spe->fes != FES_LEFHIDE) {
                        mas_opt[i].spe->fes = FES_RIGHIDE;
                    }

                    k = 0;
                    beg = mas_opt[i].spe->beg + 1 + l;
                    end = mas_opt[i].spe->end + 1;
                    while (isdigit(format[beg + k]) || format[beg + k] == logger_format_list[LEF_SEP].name[0]) {
                        k++;
                    }
                    end = beg + k;
                    memset(buff, 0, 10);
                    strncpy(buff, &format[beg], end - beg);
                    char buff1[10] = {0};
                    char buff2[10] = {0};
                    if (format[beg] == logger_format_list[LEF_SEP].name[0]) {
                        sscanf(buff, ".%ld", &mas_opt[i].spe->rig);
                    } else {
                        sscanf(buff, "%ld.%ld", &mas_opt[i].spe->lef, &mas_opt[i].spe->rig);
                    }

                } else if (mas_opt[i].type == F_NUM) {
                    beg = mas_opt[i].spe->beg + 1;
                    end = mas_opt[i].spe->end + 1;
                    k = 0;
                    while (isdigit(format[beg + k]) || format[beg + k] == logger_format_list[LEF_SEP].name[0]) {
                        k++;
                    }
                    end = beg + k;
                    memset(buff, 0, 10);
                    strncpy(buff, &format[beg], end - beg);
                    char buff1[10] = {0};
                    char buff2[10] = {0};
                    if (format[beg] == '0') {
                        mas_opt[i].spe->fes = FES_NUL;
                    }
                    if (format[beg] == logger_format_list[LEF_SEP].name[0]) {
                        if (mas_opt[i].spe->fes != FES_NUL) {
                            mas_opt[i].spe->fes = FES_RIG;
                        }
                        sscanf(buff, ".%ld", &mas_opt[i].spe->rig);
                    } else {
                        if (mas_opt[i].spe->fes != FES_NUL) {
                            mas_opt[i].spe->fes = FES_LEF;
                        }
                        sscanf(buff, "%ld.", &mas_opt[i].spe->lef);
                    }
                } else {
                    printf("ERROR \n");
                }
            }
        }
    }

    { /*Тестовый вывод*/
        printf("FORMAT = %s\n", format);
        for (uintmax_t i = 0; i < *num_token; i++) {
            int k1 = 0;
            int f1 = 80;
            char buffopt[300] = {0};
            strncpy(buffopt, &format[mas_opt[i].beg], mas_opt[i].end - mas_opt[i].beg + 1);
            char buffmod[300] = {0};
            if (mas_opt[i].spe != NULL) {
                strncpy(buffmod, &format[mas_opt[i].spe->beg], mas_opt[i].spe->end - mas_opt[i].spe->beg + 1);
            }
            printf("%3ld | %10s = %02ld | %3ld <%3ld> %3ld | -%s- %n",
                   i,
                   logger_format_list[mas_opt[i].id].name,
                   mas_opt[i].id,
                   mas_opt[i].beg,
                   mas_opt[i].end - mas_opt[i].beg + 1,
                   mas_opt[i].end,
                   buffopt,
                   &k1);
            printf("%*s %ld [(%2ld) (%2ld)] -%s-    \n",
                   f1 - k1,
                   "",
                   mas_opt[i].spe != NULL ? mas_opt[i].spe->fes : 0,
                   mas_opt[i].spe != NULL ? mas_opt[i].spe->lef : 0,
                   mas_opt[i].spe != NULL ? mas_opt[i].spe->rig : 0,
                   buffmod);
        }
        printf("\n");
    }

    return mas_opt;
}

void format_build_str(logger_format_mas *mas_opt, const char *buff) {
    char buff_temp[100] = {0};

    if (mas_opt->spe != NULL) {
        uintmax_t max = mas_opt->spe->lef > mas_opt->spe->rig ? mas_opt->spe->lef : mas_opt->spe->rig;
        uintmax_t len = strlen(buff);
        if (len <= mas_opt->spe->lef || len <= mas_opt->spe->rig) {
            goto jmp_else_null;
        }
        if (mas_opt->spe->fes == FES_LEFHIDE) {
            strncpy(buff_temp, &buff[len - max], max);
            strncpy(buff_temp, HIDEN_STR, strlen(HIDEN_STR));
            lvg->out_ofset += sprintf(&lvg->out_buff[lvg->out_ofset], "%s", buff_temp);
        } else if (mas_opt->spe->fes == FES_RIGHIDE) {
            strncpy(buff_temp, &buff[0], max);
            strncpy(&buff_temp[max - strlen(HIDEN_STR)], HIDEN_STR, strlen(HIDEN_STR));
            lvg->out_ofset += sprintf(&lvg->out_buff[lvg->out_ofset], "%s", buff_temp);
        } else {
        jmp_else_null:
            if (mas_opt->spe->lef != 0) {
                lvg->out_ofset += sprintf(&lvg->out_buff[lvg->out_ofset], "%*s", (int) max, buff);
            } else if (mas_opt->spe->rig != 0) {
                lvg->out_ofset += sprintf(&lvg->out_buff[lvg->out_ofset], "%-*s", (int) max, buff);
            } else {
                goto jmp_else_main;
            }
        }
    } else {
    jmp_else_main:
        lvg->out_ofset += sprintf(&lvg->out_buff[lvg->out_ofset], "%s", buff);
    }
}

void format_build_num(logger_format_mas *mas_opt, uintmax_t *buff) {
    if (mas_opt->spe != NULL) {
        if (mas_opt->spe->fes == FES_NUL) {
            lvg->out_ofset += sprintf(&lvg->out_buff[lvg->out_ofset], "%0*ld", (int) mas_opt->spe->lef, (uintmax_t) *buff);
        } else if (mas_opt->spe->fes == FES_LEF) {
            lvg->out_ofset += sprintf(&lvg->out_buff[lvg->out_ofset], "%*ld", (int) mas_opt->spe->lef, (uintmax_t) *buff);
        } else if (mas_opt->spe->fes == FES_RIG) {
            lvg->out_ofset += sprintf(&lvg->out_buff[lvg->out_ofset], "%-*ld", (int) mas_opt->spe->rig, (uintmax_t) *buff);
        }
    } else {
        lvg->out_ofset += sprintf(&lvg->out_buff[lvg->out_ofset], "%ld", (uintmax_t) *buff);
    }
}

#if LOGGER_STYLE == LOGGER_TRUE
void style_build() {
    if (lvg->psett->style == LOGGER_TRUE) {
    }
}
#endif

void logger_out() {
    switch (lvg->psett->stream) {
    case LS_STDOUT: {
        printf("%s \n", lvg->out_buff);
        break;
    }
    case LS_STDERR: {
        break;
    }
    case LS_STDFILE: {
        break;
    }
    case LS_STDBUF: {
        break;
    }
    }
    lvg->out_buff[0] = '\0';
    lvg->out_ofset = 0;
}
