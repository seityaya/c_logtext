#include "yaya_logger.h"
#include "yaya_logger_func.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern logger_variables *lvg;

void logger_out() {
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
    lvg->out_offset = 0;
}
