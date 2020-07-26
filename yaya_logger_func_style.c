#include "yaya_logger.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern logger_variables *lvg;

#if LOGGER_STYLE
void style_build() {
    if (lvg->psett->style) {
    }
}
#endif
