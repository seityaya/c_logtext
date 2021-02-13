#ifndef YAYA_LOGGER_FUNC_BUILD_FNC_H_
#define YAYA_LOGGER_FUNC_BUILD_FNC_H_

#include "yaya_logger_struct.h"

#define LOGGER_FUNC_PARAM logger *lvg, const char *format, logger_token_mas *mas_opt, uintmax_t *num_token, uintmax_t *count, char *file, uintmax_t *line, const char *func, uintmax_t type, uintmax_t name, const char *mes, va_list mes_list
#define LOGGER_FUNC_GENERATE(TOKEN)  void logger_func_##TOKEN(LOGGER_FUNC_PARAM)

LOGGER_FUNC_GENERATE(void);
LOGGER_FUNC_GENERATE(str);
LOGGER_FUNC_GENERATE(line);
LOGGER_FUNC_GENERATE(file);
LOGGER_FUNC_GENERATE(func);


#endif /*YAYA_LOGGER_FUNC_BUILD_FNC_H_*/
