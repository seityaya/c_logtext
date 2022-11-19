//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#include "yaya_logger.h"
#include "yaya_logger_private.h"

logger_error logger_out(___logger *lvg)
{
#if (((LOGGER_OUT) == LOGGER_OFF))
    (void)(lvg);
    lvg->out_buff[0] = '\0';
    lvg->out_offset  = 0;    // TODO(yaya): Баг с контролем выхода за границу
#else
    lvg->out_buff[lvg->out_offset + 0] = '\n';
    lvg->out_buff[lvg->out_offset + 1] = '\0';
    lvg->out_offset += 1;

    switch (lvg->psett->stream) {
#if (((LOGGER_OUT) & DLS_STDOUT) || (LOGGER_OUT == LOGGER_ON))
        case LS_STDOUT: {
            fputs(lvg->out_buff, stdout);
            fflush(stdout);
            break;
        }
#endif
#if (((LOGGER_OUT) & DLS_STDERR) || (LOGGER_OUT == LOGGER_ON))
        case LS_STDERR: {
            fputs(lvg->out_buff, stderr);
            fflush(stderr);
            break;
        }
#endif
#if (((LOGGER_OUT) & DLS_STDBUF) || (LOGGER_OUT == LOGGER_ON))
        case LS_STDBUF: {
            // TODO(yaya): circular buffer
            return LE_OK;
        }
#endif
#if (((LOGGER_OUT) & DLS_STDFILE) || (LOGGER_OUT == LOGGER_ON))
        case LS_STDFILE: {
            fwrite(lvg->out_buff, sizeof(char), lvg->out_offset, lvg->stream);
            fflush(lvg->stream);
            break;
        }
#endif
#if (((LOGGER_OUT) & DLS_STDCSV) || (LOGGER_OUT == LOGGER_ON))
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
#endif
    }

    lvg->out_buff[0] = '\0';
    lvg->out_offset  = 0;
#endif
    return LE_OK;
}

bool yaya_log_flush(void **logger_ptr){
#if (((LOGGER_OUT) == LOGGER_OFF))
    (void)(logger_ptr);
#else
    if(logger_ptr == NULL){
        return false;
    }
    ___logger *lvg = (___logger*)(*logger_ptr);
    if(lvg == NULL){
        return false;
    }

    switch (lvg->psett->stream) {
#if (((LOGGER_OUT) & DLS_STDOUT) || (LOGGER_OUT == LOGGER_ON))
        case LS_STDOUT:
#endif
#if (((LOGGER_OUT) & DLS_STDERR) || (LOGGER_OUT == LOGGER_ON))
        case LS_STDERR:
#endif
#if (((LOGGER_OUT) & DLS_STDFILE) || (LOGGER_OUT == LOGGER_ON))
        case LS_STDFILE:
#endif
#if (((LOGGER_OUT) & DLS_STDCSV) || (LOGGER_OUT == LOGGER_ON))
        case LS_STDCSV:
#endif
#if (((LOGGER_OUT) & (DLS_STDOUT | DLS_STDERR | DLS_STDFILE | DLS_STDCSV)) || (LOGGER_OUT == LOGGER_ON))
        {
            fflush(lvg->stream);
            return false;
        }
#endif
#if (((LOGGER_OUT) & DLS_STDBUF) || (LOGGER_OUT == LOGGER_ON))
        case LS_STDBUF: {
            // TODO(yaya): circular buffer
            if(lvg->out_offset > 0){
                strncpy(lvg->psett->out_buff, lvg->out_buff, lvg->psett->size_buff - 1);
                lvg->psett->out_buff[lvg->psett->size_buff - 1] = '\0';
                *lvg->psett->out_size = strlen(lvg->psett->out_buff);
                if((lvg->out_offset - lvg->psett->size_buff >= 0)){
                    strncpy(lvg->tmp_buff, lvg->out_buff + lvg->psett->size_buff - 1, LOGGER_TMP_BUFF_SIZE);
                    strncpy(lvg->out_buff, lvg->tmp_buff, LOGGER_OUT_BUFF_SIZE);
                    lvg->out_offset -= lvg->psett->size_buff - 1;
                }else{
                    lvg->out_offset = 0;
                    return false;
                }
                return true;
            }
            return false;
        }
#endif
    }
    return false;
#endif
}

