#include "yaya_logger.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern logger_variables *lvg;

void yaya_log_init(logger_list *type, logger_list *name, logger_setting *setting, logger_define *define, logger_style *style) {
    lvg->init_flag = LOGGER_TRUE;

    { /*Cвязывание указателей*/
        //lvg->pglob = logger_variables_global;
        lvg->ptype = type;
        lvg->psett = setting;
        lvg->pdefn = define;
        lvg->pname = name;
        lvg->pstyl = style;
    }

    {
        /*Инициализация переменных*/
        lvg->tmp_buff = calloc(LOGGER_TMP_BUFF_SIZE, sizeof(char));
        lvg->out_buff = calloc(LOGGER_OUT_BUFF_SIZE, sizeof(char));
        lvg->out_offset = 0;
        lvg->data_build = __DATE__;
        lvg->time_build = __TIME__;
        lvg->projpath = "/../../";
        lvg->absnum = 0;
        lvg->curnum = 0;
        lvg->compilerversion = __VERSION__;
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

    { /*Парсинг форматированной строки*/
#if LOGGER_HEAD
       mas_opt(lvg->psett->head_format, &lvg->head_mas_opt, &lvg->head_num_token);
#endif
       mas_opt(lvg->psett->logs_format, &lvg->logs_mas_opt, &lvg->logs_num_token);
    }
}
