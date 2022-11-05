//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#include "yaya_logger.h"
#include "yaya_logger_private.h"

logger_error format_build_num(___logger* lvg, ___logger_token_mas* mas_opt, uintmax_t buff_orig)
{
    mas_opt->type = LTT_NUM;
    mas_opt->beglog = lvg->out_offset;

    if (mas_opt->spe != NULL){
        if (mas_opt->spe->lfs == LFS_NUL){
            lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%0*" PRIiMAX "", (int)mas_opt->spe->lef, buff_orig);
        }else if (mas_opt->spe->lfs == LFS_LEF){
            lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%*" PRIiMAX "", (int)mas_opt->spe->lef, buff_orig);
        }else if (mas_opt->spe->lfs == LFS_RIG){
            lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%-*" PRIiMAX "", (int)mas_opt->spe->rig, buff_orig);
        }
    }else{
        lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%" PRIiMAX "", buff_orig);
    }

    mas_opt->endlog = lvg->out_offset;

    return LE_OK;
}

logger_error format_build_str(___logger *lvg, ___logger_token_mas *mas_opt, const char *buff_orig)
{
    mas_opt->type = LTT_STR;
    static char buff[LOGGER_TMP_BUFF_SIZE] = {0}; //FIXME

    mas_opt->beglog = lvg->out_offset;

    if (mas_opt->spe != NULL){
        uintmax_t max = mas_opt->spe->lef > mas_opt->spe->rig ? mas_opt->spe->lef : mas_opt->spe->rig;
        uintmax_t len = strlen(buff_orig);
        if (len <= mas_opt->spe->lef || len <= mas_opt->spe->rig){
            goto jmp_else_null;
        }
        if (mas_opt->spe->lfs == LFS_LEF){
            strncpy(buff, &buff_orig[len - max], max);
            strncpy(buff, LOGGER_HIDDEN_STR, strlen(LOGGER_HIDDEN_STR));
            lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%s", buff);
        }else if (mas_opt->spe->lfs == LFS_RIG){
            strncpy(buff, &buff_orig[0], max);
            strncpy(&buff[max - strlen(LOGGER_HIDDEN_STR)], LOGGER_HIDDEN_STR, strlen(LOGGER_HIDDEN_STR));
            lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%s", buff);
        }else{
        jmp_else_null:
            if (mas_opt->spe->lef != 0){
                lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%*s", (int)max, buff_orig);
            }else if (mas_opt->spe->rig != 0){
                lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%-*s", (int)max, buff_orig);
            }else{
                goto jmp_else_main;
            }
        }
    }else{
    jmp_else_main:
        lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%s", buff_orig);
    }

    mas_opt->endlog = lvg->out_offset;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(STR){
    LOGGER_FUNC_UNUSED;
    strncpy(lvg->tmp_buff, &format[mas_opt->beg], mas_opt->end - mas_opt->beg + 1);
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}
