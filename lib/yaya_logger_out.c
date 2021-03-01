#include "yaya_logger.h"

void ___logger_out(___logger *lvg)
{
    switch (lvg->psett->stream) {
        case LS_STDOUT: {
            printf("%s\n", lvg->out_buff);
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
    lvg->out_offset  = 0;
}
