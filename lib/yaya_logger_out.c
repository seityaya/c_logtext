//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#include "yaya_logger.h"
#include "yaya_logger_private.h"

#if (LOGGER_OUT == LOGGER_ON)
logger_error ___logger_out(logger *lvg)
{
    switch (lvg->psett->stream) {
        case LS_STDOUT: {
            fputs(lvg->out_buff, stdout);
            fputc('\n', stdout);
            break;
        }
        case LS_STDERR: {
            fputs(lvg->out_buff, stderr);
            fputc('\n', stderr);
            break;
        }
        case LS_STDFILE: {
            printf("LS_STDFILE");
            break;
        }
        case LS_STDBUF: {
            printf("LS_STDBUF");
            break;
        }
    }

    lvg->out_buff[0] = '\0';
    lvg->out_offset  = 0;

    return LE_OK;
}
#endif
