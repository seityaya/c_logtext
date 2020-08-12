#include "yaya_logger.h"
#include "yaya_logger_func.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern logger_variables *lvg;

void format_build_num(logger_token_mas *mas_opt, uintmax_t *buff_orig) {
    mas_opt->beglog = lvg->out_offset;
    if (mas_opt->spe != NULL) {
        if (mas_opt->spe->lfs == LFS_NUL) {
            lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%0*" PRIuMAX "", (int) mas_opt->spe->lef, (uintmax_t) *buff_orig);
        } else if (mas_opt->spe->lfs == LFS_LEF) {
            lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%*" PRIuMAX "", (int) mas_opt->spe->lef, (uintmax_t) *buff_orig);
        } else if (mas_opt->spe->lfs == LFS_RIG) {
            lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%-*" PRIuMAX "", (int) mas_opt->spe->rig, (uintmax_t) *buff_orig);
        }
    } else {
        lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%" PRIuMAX "", (uintmax_t) *buff_orig);
    }
    mas_opt->endlog = lvg->out_offset;
}
