#include "yaya_logger.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void yaya_log_init(logger_list *type, logger_list *name, logger_setting *setting, logger_define *define, logger_style *style) {
    logger_variables *lvg;
    lvg = logger_variables_global;
    lvg->log_init_flag = TRUE;

    { /*связывание указателей*/
        lvg->pglob = logger_variables_global;
        lvg->ptype = type;
        lvg->psett = setting;
        lvg->pdefn = define;
        lvg->pname = name;
        lvg->pstyl = style;
    }

    { /*Подсчет количества флагов типа*/
        for (uintmax_t i = 0; i < sizeof(uintmax_t) * 8; i++) {
            if (lvg->ptype[i].flag == FLAG_ALL) {
                lvg->type_num = lvg->ptype[i].id;
                break;
            }
        }
    }

    { /*Подсчет количества флагов имени*/
        for (uintmax_t i = 0; i < sizeof(uintmax_t) * 8; i++) {
            if (lvg->pname[i].flag == FLAG_ALL) {
                lvg->name_num = lvg->pname[i].id;
                break;
            }
        }
    }

    { /* Подсчетточного точного колличества токенов, выделение памяти и определение их диапазона */
        lvg->logger_token_mas_opt = calloc(1, sizeof(logger_format_mas));
        uintmax_t j = 0;
        for (uintmax_t i = 0; i < strlen(lvg->psett->format_logs); i++) {
            if (lvg->psett->format_logs[i] == logger_format_list[LEF_SEPARATOR].name[0]) {
                lvg->logger_token_mas_opt = realloc(lvg->logger_token_mas_opt, sizeof(logger_format_mas) * (j + 1));
                lvg->logger_token_mas_opt[j].beg = i;
                lvg->logger_token_mas_opt[j].id = LEF_TOKEN;
                do {
                    lvg->logger_token_mas_opt[j].end = i;
                    i++;
                } while (isalpha(lvg->psett->format_logs[i])
                         || ((lvg->psett->format_logs[i] == logger_format_list[LEF_SEPARATOR].name[0])
                             && (lvg->psett->format_logs[i - 1] == logger_format_list[LEF_SEPARATOR].name[0])));
                i--;
                j++;
            } else {
                lvg->logger_token_mas_opt = realloc(lvg->logger_token_mas_opt, sizeof(logger_format_mas) * (j + 1));
                lvg->logger_token_mas_opt[j].beg = i;
                lvg->logger_token_mas_opt[j].id = LEF_STRING;
                do {
                    lvg->logger_token_mas_opt[j].end = i;
                    i++;
                } while (!(lvg->psett->format_logs[i] == logger_format_list[LEF_SEPARATOR].name[0]));
                i--;
                j++;
            }
        }
        lvg->type_num_token = j;
    }

    { /*Определение типа токенов*/
        for (uintmax_t i = 0; i < lvg->type_num_token; i++) {
            char buff[50] = {0};
            if (lvg->logger_token_mas_opt[i].id == LEF_TOKEN) {
                strncpy(buff,
                        &lvg->psett->format_logs[lvg->logger_token_mas_opt[i].beg + 1],
                        lvg->logger_token_mas_opt[i].end - lvg->logger_token_mas_opt[i].beg);
                for (uintmax_t j = 0; j < LEF_END; j++) {
                    if (strstr(buff, logger_format_list[j].name) != NULL) {
                        lvg->logger_token_mas_opt[i].id = j;
                        break;
                    }
                }
            }
        }
    }
    /*Тестовый вывод*/
    /* { 
        for (uintmax_t i = 0; i < lvg->type_num_token; i++) {
            printf("%02ld | %02ld = %10s | %3ld <%02ld> %3ld\n",
                   i,
                   lvg->logger_token_mas_opt[i].id,
                   logger_format_list[lvg->logger_token_mas_opt[i].id].name,
                   lvg->logger_token_mas_opt[i].beg,
                   lvg->logger_token_mas_opt[i].end - lvg->logger_token_mas_opt[i].beg + 1,
                   lvg->logger_token_mas_opt[i].end);
        }
        printf("\n");
    } */
}

void yaya_log_head(uintmax_t count, char *file, uintmax_t line, const char *func, const char *mes, ...) {
    logger_variables *lvg;
    lvg = logger_variables_global;
    lvg->log_head_flag = TRUE;
}

void yaya_log_func(uintmax_t count, char *file, uintmax_t line, const char *func, uintmax_t type, uintmax_t name, const char *mesg, ...) {
    logger_variables *lvg;
    lvg = logger_variables_global;

    /*Инициализация*/
    if (lvg->log_init_flag == FALSE) {
        log_init(logger_type_def, logger_name_def, logger_setting_def, logger_define_def, logger_style_def);
    }

    /*Заголовок*/
    if (lvg->log_head_flag == FALSE && &lvg->psett->format_head[0] != NULL) {
        log_head("\0");
    }

    /*Логгер*/
    if ((lvg->psett->type & type) || (lvg->psett->name & name)) {
        {
            char buff_str[2000] = {0};
            for (uintmax_t i = 0; i < lvg->type_num_token; i++) {
                char buff[1000] = {0};
                switch (lvg->logger_token_mas_opt[i].id) {
                case LEF_SEPARATOR: {
                    break;
                }
                case LEF_STRING: {
                    strncpy(buff,
                            &logger_setting_def->format_logs[lvg->logger_token_mas_opt[i].beg],
                            lvg->logger_token_mas_opt[i].end - lvg->logger_token_mas_opt[i].beg + 1);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_TOKEN: {
                    break;
                }
                case LEF_PROG: {
                    sprintf(buff, "%s", (&lvg->pdefn->prog[0] == NULL) ? "\0" : lvg->pdefn->prog);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_PROJPATH: {
                    sprintf(buff, "%s", __FILE__);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_PROJ: {
                    sprintf(buff, "%s", &lvg->pdefn->proj[0] == NULL ? "\0" : lvg->pdefn->proj);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_VERSION: {
                    sprintf(buff, "%s", &lvg->pdefn->version[0] == NULL ? "\0" : lvg->pdefn->version);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_DATA_BUILD: {
                    sprintf(buff, "%s", __DATE__);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_TIME_BUILD: {
                    sprintf(buff, "%s", __TIME__);
                    strcat(buff_str, buff);
                    break;
                }

                case LEF_SEED: {
                    sprintf(buff, "%ld", lvg->pdefn->seed);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_COMPILER: {
                    sprintf(buff, "%s", __VERSION__);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_CURNUM: {
                    sprintf(buff, "%ld", logger_variables_global->curnum);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_ABSNUM: {
                    sprintf(buff, "%ld", logger_variables_global->absnum);
                    strcat(buff_str, buff);
                    break;
                }

                case LEF_COUNT: {
                    sprintf(buff, "%ld", logger_variables_global->vcount);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_TIK: {
                    break;
                }
                case LEF_TIKSEC: {
                    break;
                }
                case LEF_TIK_RTOS: {
                    break;
                }
                case LEF_TIK_UNIX: {
                    break;
                }
                case LEF_TYPE: {
                    for (uintmax_t i = 0; i < lvg->type_num - 1; i++) {
                        if (type == L_ALL) {
                            sprintf(buff, "%s", &logger_type_def[lvg->type_num].name[2]);
                        } else if (type == L_NUL) {
                            sprintf(buff, "%s", &logger_type_def[0].name[2]);
                        } else {
                            if (BIT_GET(type, i)) {
                                sprintf(buff, "%s ", &logger_type_def[i + 1].name[2]);
                            }
                        }
                    }
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_NAME: {
                    for (uintmax_t i = 0; i < lvg->name_num - 1; i++) {
                        if (type == L_ALL) {
                            sprintf(buff, "%s", &logger_name_def[lvg->name_num].name[3]);
                        } else if (name == L_NUL) {
                            sprintf(buff, "%s", &logger_name_def[0].name[3]);
                        } else {
                            if (BIT_GET(name, i)) {
                                sprintf(buff, "%s", &logger_name_def[i + 1].name[3]);
                            }
                        }
                    }
                    strcat(buff_str, buff);
                    break;
                }

                case LEF_DATA: {
                    sprintf(buff, "%d", 0);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_TIME: {
                    sprintf(buff, "%d", 0);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_FULLPATH: {
                    break;
                }
                case LEF_SHORPATH: {
                    break;
                }
                case LEF_FILENAME: {
                    sprintf(buff, "%s", file);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_LINE: {
                    sprintf(buff, "%ld", line);
                    strcat(buff_str, buff);
                    break;
                }

                case LEF_FUNC: {
                    sprintf(buff, "%s", func);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_MESAGE: {
                    va_list list;
                    va_start(list, mesg);
                    vsprintf(buff, mesg, list);
                    va_end(list);
                    strcat(buff_str, buff);
                    break;
                }
                case LEF_NEWLINE: {
                    //                sprintf(buff, "%s", "\n");
                    //                strcat(buff_str, buff);
                    break;
                }
                case LEF_ALIGNL: {
                    break;
                }
                case LEF_ALIGGT: {
                    break;
                }

                default: {
                    printf("case for token not find");
                    { /*вывод настроек фильтрации*/
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
                    }
                    break;
                }
                }
            }
            printf("%s\n", buff_str);
        }
    }
    /* Анти-логгер */
    /* else { 
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
        printf("- IGNORE!");
    } */
}
