#ifndef YAYA_LOGGER_FUNC_BUILD_FNC_H_
#define YAYA_LOGGER_FUNC_BUILD_FNC_H_

#include "yaya_logger_macro.h"
#include "yaya_logger_struct.h"

LOGGER_FUNC_GENERATE(void);
LOGGER_FUNC_GENERATE(str);
LOGGER_FUNC_GENERATE(line);
LOGGER_FUNC_GENERATE(file);
LOGGER_FUNC_GENERATE(func);
LOGGER_FUNC_GENERATE(type);
LOGGER_FUNC_GENERATE(mess);
LOGGER_FUNC_GENERATE(name);

typedef enum {
    // SYS
    LOGGER_TOKEN_GENERATE_ENUM(TOK),
    LOGGER_TOKEN_GENERATE_ENUM(SPE),
    LOGGER_TOKEN_GENERATE_ENUM(SEP),
    LOGGER_TOKEN_GENERATE_ENUM(HID),
    LOGGER_TOKEN_GENERATE_ENUM(str),

    // WORK
    //LOGGER_TOKEN_GENERATE_ENUM(line),
    //LOGGER_TOKEN_GENERATE_ENUM(),
    LEF_line,
    LEF_file,
    LEF_func,
    LEF_type,
    LEF_mess,
    LEF_name,
    LEF_COUNT,
    LEF_CURNUM,
    LEF_ABSNUM,
    LEF_PROG,
    LEF_PROJ,
    LEF_PROJ_VERSION,
    LEF_COMPILERVERSION,

    // NOT WORK
    LEF_PROJ_PATH,
    LEF_VERSION,
    LEF_DATA_BUILD,
    LEF_TIME_BUILD,
    LEF_SEED,
    LEF_TIK,
    LEF_TIKSEC,
    LEF_TIK_RTOS,
    LEF_TIK_UNIX,
    LEF_TYPE_FILTER,
    LEF_NAME_FILTER,
    LEF_TYPE_NUM,
    LEF_NAME_NUM,
    LEF_TYPE_LIST,
    LEF_NAME_LIST,
    LEF_DATA,
    LEF_TIME,
    LEF_FULLPATH,
    LEF_SHORPATH,
    LEF_ALIGNL,
    LEF_ALIGGT,
    LEF_NUM_TOKEN_HEAD,
    LEF_NUM_TOKEN_LOGS,
    LEF_void,
    LEF_END
} logger_token_id;

#define LOGGER_TOKEN_GENERATE_ST(TOKEN)  { LEF_##TOKEN, #TOKEN, logger_func_##TOKEN }

static logger_token logger_token_list[LEF_END] = {
    {LEF_TOK, "$", NULL}, // - токен формата токена
    {LEF_SPE, "%", NULL}, // - токен формата вывода
    {LEF_SEP, ".", NULL}, // - токен формата вывода, разделитель
    {LEF_HID, ":", NULL}, // - токен формата вывода, скрыватель

    LOGGER_TOKEN_GENERATE_ST(str),  // - токен формата текста
    LOGGER_TOKEN_GENERATE_ST(line), // - номер строки
    LOGGER_TOKEN_GENERATE_ST(file), // - файл
    LOGGER_TOKEN_GENERATE_ST(func), // - имя функции
    LOGGER_TOKEN_GENERATE_ST(type), // -
    LOGGER_TOKEN_GENERATE_ST(mess), // -
    LOGGER_TOKEN_GENERATE_ST(name), // -
    LOGGER_TOKEN_GENERATE_ST(void), // -
    LOGGER_TOKEN_GENERATE_ST(void), // -
    LOGGER_TOKEN_GENERATE_ST(void), // -

    //    {LEF_COUNT, "count"}, // - номер сообщения, на основе __COUNTER__
    //    {LEF_TYPE, "type"},       // - имя типа сообщения
    //    {LEF_NAME, "name"},       // - имя названия сообщения
    //    {LEF_MESSAGE, "message"}, // - тело сообщения
    //    {LEF_CURNUM, "curnum"}, // - номер выведенного сообщения
    //    {LEF_ABSNUM, "absnum"}, // - номер сообщения без учета фильтрации
    //    {LEF_PROG, "prog"},            // - название программы
    //    {LEF_PROJ, "proj"},            // - название проекта
    //    {LEF_PROJ_VERSION, "version"}, // - версия программы
    //    {LEF_DATA, "data"},         // - дата сообщения
    //    {LEF_TIME, "time"},         // - время сообщения
    //    {LEF_PROJ_PATH, "path"},    // - расположение проекта
    //    {LEF_FULLPATH, "fullpath"}, // - полный путь к файлу, из которого сообщение
    //    {LEF_SHORPATH, "shorpath"}, // - короткий путь к файлу, из которого сообщение
    //    {LEF_VERSION, "version"},      // - версия программы
    //    {LEF_DATA_BUILD, "databuild"}, // - дата компиляции
    //    {LEF_TIME_BUILD, "timebuild"}, // - время компиляции
    //    {LEF_SEED, "seed"},            // - сид запуска ГПСЧ
    //    {LEF_TIK, "tik"}, // - счетчик тактов процессора
    //    {LEF_TIKSEC, "tiksec"}, // - счетчик секунд от старта
    //    {LEF_TIK_RTOS, "tikrtos"}, // - счетчик rtos
    //    {LEF_TIK_UNIX, "tikunix"}, // - счетчик времени
    //    {LEF_TYPE_FILTER, "typefilter"}, // - вывод настроек фильтрации типа
    //    {LEF_NAME_FILTER, "namefilter"}, // - вывод настроек фильтрации имени
    //    {LEF_TYPE_NUM, "typenum"}, // - имя типа сообщения, номером
    //    {LEF_NAME_NUM, "namenum"}, // - имя названия сообщения, номером
    //    {LEF_TYPE_LIST, "typelist"}, // - имена всех типов сообщений + номер флага
    //    {LEF_NAME_LIST, "namelist"}, // - имена всех названий сообщений

    //    {LEF_ALIGNL, "alignl"}, // - выравнивание при переносе
    //    {LEF_ALIGGT, "aliggt"}, // - выравнивание принудительное
    //    {LEF_NUM_TOKEN_HEAD, "headtoken"}, // - количество токенов в заголовке
    //    {LEF_NUM_TOKEN_LOGS, "logstoken"} // - количество токенов в логгере
    // дата = день, месяц, год, день недели, и т.д
    // время = часы, минуты, секунды, милисекунды, и т.д
};




#endif /*YAYA_LOGGER_FUNC_BUILD_FNC_H_*/
