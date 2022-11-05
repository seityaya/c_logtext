//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#include "yaya_logger.h"
#include "yaya_logger_private.h"

#if LOGGER_OUT
logger_error logger_out(___logger *lvg)
{
    lvg->out_buff[lvg->out_offset + 0] = '\n';
    lvg->out_buff[lvg->out_offset + 1] = '\0';
    lvg->out_offset += 1;

    switch (lvg->psett->stream) {
        case LS_STDOUT: {
            fputs(lvg->out_buff, stdout);
            fflush(stdout);
            break;
        }
        case LS_STDERR: {
            fputs(lvg->out_buff, stderr);
            fflush(stderr);
            break;
        }
        case LS_STDBUF: {
            // TODO(yaya): circular buffer
            return LE_OK;
        }
        case LS_STDFILE: {
            fwrite(lvg->out_buff, sizeof(char), lvg->out_offset, lvg->stream);
            fflush(lvg->stream);
            break;
        }
        case LS_STDCSV: {
            lvg->tmp_buff[0] = '\0';
            size_t len = 0;
            for(uintmax_t i = 0; i < lvg->logs_f->num_token; i++){

                if(lvg->logs_f->mas_opt[i].type == LTT_STR){
                    lvg->tmp_buff[len + 0] = '"';
                    lvg->tmp_buff[len + 1] = '\0';
                    len += 1;
                }

                strncat(lvg->tmp_buff,  &lvg->out_buff[lvg->logs_f->mas_opt[i].beglog], lvg->logs_f->mas_opt[i].endlog - lvg->logs_f->mas_opt[i].beglog);
                len += lvg->logs_f->mas_opt[i].endlog - lvg->logs_f->mas_opt[i].beglog;

                if(lvg->logs_f->mas_opt[i].type == LTT_STR){
                    lvg->tmp_buff[len + 0] = '"';
                    lvg->tmp_buff[len + 1] = '\0';
                    len += 1;
                }

                lvg->tmp_buff[len + 0] = ',';
                lvg->tmp_buff[len + 1] = '\0';
                len += 1;
            }
            lvg->tmp_buff[len + 0] = '\n';
            lvg->tmp_buff[len + 1] = '\0';
            len +=1;

            fwrite(lvg->tmp_buff, sizeof(char), len, lvg->stream);
            fflush(lvg->stream);
            break;
        }
    }

    lvg->out_buff[0] = '\0';
    lvg->out_offset  = 0;

    return LE_OK;
}
#endif

bool yaya_log_flush(void **logger_ptr){
    if(logger_ptr == NULL){
        return true;
    }

    ___logger **lvg = (___logger**)(logger_ptr);

    if(*lvg == NULL){
        return true;
    }

    switch ((*lvg)->psett->stream) {
        case LS_STDOUT:
        case LS_STDERR:
        case LS_STDFILE:
        case LS_STDCSV: {
            fflush((*lvg)->stream);
            return true;
        }
        case LS_STDBUF: {
            // TODO(yaya): circular buffer
            if((*lvg)->out_offset > 0){
                strncpy((*lvg)->psett->out_buff, (*lvg)->out_buff, (*lvg)->psett->size_buff - 1);
                (*lvg)->psett->out_buff[(*lvg)->psett->size_buff - 1] = '\0';
                *(*lvg)->psett->out_size = strlen((*lvg)->psett->out_buff);
                if(((*lvg)->out_offset - (*lvg)->psett->size_buff >= 0)){
                    strncpy((*lvg)->tmp_buff, (*lvg)->out_buff + (*lvg)->psett->size_buff - 1, LOGGER_TMP_BUFF_SIZE);
                    strncpy((*lvg)->out_buff, (*lvg)->tmp_buff, LOGGER_OUT_BUFF_SIZE);
                    (*lvg)->out_offset -= (*lvg)->psett->size_buff - 1;
                }else{
                    (*lvg)->out_offset = 0;
                    return true;
                }
                return false;
            }
            return true;
        }

    }
}

