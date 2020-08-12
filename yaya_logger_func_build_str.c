#include "yaya_logger.h"
#include "yaya_logger_func.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern logger_variables *lvg;

void format_build_str(logger_token_mas *mas_opt, const char *buff_orig) {
    char buff[LOGGER_TMP_BUFF_SIZE] = {0};
    mas_opt->beglog = lvg->out_offset;
    if (mas_opt->spe != NULL) {
        uintmax_t max = mas_opt->spe->lef > mas_opt->spe->rig ? mas_opt->spe->lef : mas_opt->spe->rig;
        uintmax_t len = strlen(buff_orig);
        if (len <= mas_opt->spe->lef || len <= mas_opt->spe->rig) {
            goto jmp_else_null;
        }
        if (mas_opt->spe->lfs == LFS_LEF) {
            strncpy(buff, &buff_orig[len - max], max);
            strncpy(buff, HIDDEN_STR, strlen(HIDDEN_STR));
            lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%s", buff);
        } else if (mas_opt->spe->lfs == LFS_RIG) {
            strncpy(buff, &buff_orig[0], max);
            strncpy(&buff[max - strlen(HIDDEN_STR)], HIDDEN_STR, strlen(HIDDEN_STR));
            lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%s", buff);
        } else {
        jmp_else_null:
            if (mas_opt->spe->lef != 0) {
                lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%*s", (int) max, buff_orig);
            } else if (mas_opt->spe->rig != 0) {
                lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%-*s", (int) max, buff_orig);
            } else {
                goto jmp_else_main;
            }
        }
    } else {
    jmp_else_main:
        lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%s", buff_orig);
    }
    mas_opt->endlog = lvg->out_offset;
}
