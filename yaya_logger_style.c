#include "yaya_logger.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if LOGGER_STYLE
void ___logger_style(logger *lvg)
{
    if (lvg->psett->style) {
    }
}
#endif
