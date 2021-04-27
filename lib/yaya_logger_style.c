#include "yaya_logger.h"
#include "yaya_logger_private.h"

#if (LOGGER_STYLE != 0)

logger_error ___logger_styles(logger *lvg)
{
    if (lvg->psett->style)
    {

    }

    return LE_OK;
}

#endif
