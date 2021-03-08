#ifndef YAYA_LOGGER_CONF_H
#define YAYA_LOGGER_CONF_H

#include "yaya_logger_macro.h"
#include "yaya_logger_struct.h"
#include "yaya_logger_format.h"

// clang-format off
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // OPTION

#ifndef LOGGER_LOGS
#define LOGGER_LOGS          1 /*Включить логгер*/
#endif

#ifndef LOGGER_STYLE
#define LOGGER_STYLE         1 /*Включить стили*/
#endif

#ifndef LOGGER_OUT
#define LOGGER_OUT           1 /*Включить вывод*/
#endif

#ifndef LOGGER_DEF
#define LOGGER_DEF           1 /*Включить обобщеный логгер*/
#endif

#ifndef LOGGER_DEBUG
#define LOGGER_DEBUG         0           /*Включить отладку, 0 - выключить*/
#endif

#ifndef LOGGER_HIDDEN_STR
#define LOGGER_HIDDEN_STR   "..."
#endif

#if !defined LOGGER_DYNAMIC \
    && \
    !defined LOGGER_STATIC

    //#error LOGGER ALLOCATION TYPE NOT DEFINED
    #define LOGGER_DYNAMIC
#else
    #ifndef LOGGER_NUM_TOKEN
    #define LOGGER_NUM_TOKEN 20
    #endif
#endif

#define LOGGER_OUT_BUFF_SIZE 1000
#define LOGGER_TMP_BUFF_SIZE 1000

// // END // OPTION
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // DEFAULT

#if LOGGER_DEF == LOGGER_TRUE
static logger* logger_main_def = NULL;
#endif


#define    L_NUL      LOGGER_FLAG_T_NUL          /*<<< BEG*/
#define    L_VOID     LOGGER_FLAG_T_GENERATE( 0) /*<<< VOID FORMAT TYPE*/
#define    L_HEAD     LOGGER_FLAG_T_GENERATE( 1) /*<<< HEAD FORMAT TYPE*/
#define    L_ATOM     LOGGER_FLAG_T_GENERATE( 2) /*<<< ATOM FORMAT TYPE*/
#define    L_GNERR    LOGGER_FLAG_T_GENERATE( 3) /*<<< GENERIC ERROR TYPE*/
#define    L_INFO     LOGGER_FLAG_T_GENERATE( 4)
#define    L_ERROR    LOGGER_FLAG_T_GENERATE( 5)
#define    L_WARNING  LOGGER_FLAG_T_GENERATE( 6)
#define    L_TODO     LOGGER_FLAG_T_GENERATE( 7)
#define    L_FIXME    LOGGER_FLAG_T_GENERATE( 8)
#define    L_DEBUG    LOGGER_FLAG_T_GENERATE( 9)
#define    L_RELEASE  LOGGER_FLAG_T_GENERATE(10)
#define    L_TRACE    LOGGER_FLAG_T_GENERATE(11)
#define    L_WARN     LOGGER_FLAG_T_GENERATE(12)
#define    L_FATAL    LOGGER_FLAG_T_GENERATE(13)
#define    L_BEGF     LOGGER_FLAG_T_GENERATE(14)
#define    L_ENDF     LOGGER_FLAG_T_GENERATE(15)
#define    L_FUNC     LOGGER_FLAG_T_GENERATE(16)
#define    L_LOGGER   LOGGER_FLAG_T_GENERATE(17)
#define    L_TEST     LOGGER_FLAG_T_GENERATE(18)
#define    L_MESG     LOGGER_FLAG_T_GENERATE(19)
#define    L_ALL      LOGGER_FLAG_T_ALL          /*<<< END*/

static logger_filter logger_type_def[] = { LOGGER_FILTER_GENERATE(L_NUL),
                                           LOGGER_FILTER_GENERATE(L_VOID),
                                           LOGGER_FILTER_GENERATE(L_HEAD),
                                           LOGGER_FILTER_GENERATE(L_ATOM),
                                           LOGGER_FILTER_GENERATE(L_GNERR),
                                           LOGGER_FILTER_GENERATE(L_INFO),
                                           LOGGER_FILTER_GENERATE(L_ERROR),
                                           LOGGER_FILTER_GENERATE(L_WARNING),
                                           LOGGER_FILTER_GENERATE(L_TODO),
                                           LOGGER_FILTER_GENERATE(L_FIXME),
                                           LOGGER_FILTER_GENERATE(L_DEBUG),
                                           LOGGER_FILTER_GENERATE(L_RELEASE),
                                           LOGGER_FILTER_GENERATE(L_TRACE),
                                           LOGGER_FILTER_GENERATE(L_WARN),
                                           LOGGER_FILTER_GENERATE(L_FATAL),
                                           LOGGER_FILTER_GENERATE(L_BEGF),
                                           LOGGER_FILTER_GENERATE(L_ENDF),
                                           LOGGER_FILTER_GENERATE(L_FUNC),
                                           LOGGER_FILTER_GENERATE(L_LOGGER),
                                           LOGGER_FILTER_GENERATE(L_TEST),
                                           LOGGER_FILTER_GENERATE(L_MESG),
                                           LOGGER_FILTER_GENERATE(L_ALL)
                                         };


#define    LL_NUL   LOGGER_FLAG_N_NUL         /*<<<*/
#define    LL_VOID  LOGGER_FLAG_N_GENERATE(0) /*<<<*/
#define    LL_DEFI  LOGGER_FLAG_N_GENERATE(1)
#define    LL_INIT  LOGGER_FLAG_N_GENERATE(2)
#define    LL_MAIN  LOGGER_FLAG_N_GENERATE(3)
#define    LL_DRVR  LOGGER_FLAG_N_GENERATE(4)
#define    LL_ALL   LOGGER_FLAG_N_ALL         /*<<<*/

static logger_filter logger_name_def[] = { LOGGER_FILTER_GENERATE(LL_NUL),
                                           LOGGER_FILTER_GENERATE(LL_VOID),
                                           LOGGER_FILTER_GENERATE(LL_DEFI),
                                           LOGGER_FILTER_GENERATE(LL_INIT),
                                           LOGGER_FILTER_GENERATE(LL_MAIN),
                                           LOGGER_FILTER_GENERATE(LL_DRVR),
                                           LOGGER_FILTER_GENERATE(LL_ALL)
                                         };


static logger_style logger_style_def[] = { {LEF_mesg, {0, 0, 0}, {0, 0, 0}, LSM_NONE},
                                           {LEF_file, {0, 0, 0}, {0, 0, 0}, LSM_NONE},
                                           {LEF_line, {0, 0, 0}, {0, 0, 0}, LSM_NONE}
                                         };


static logger_define logger_define_def[] = { {.seed = 0,
                                              .prog = "yaya_logger",
                                              .proj = "yaya_library_collection_for_C",
                                              .version = "v0.1",
                                              .compiler = "gcc 7 x64"}
                                           };


static logger_setting logger_setting_def[] = { {.head_format = "HEAD ## $line%3. $mesg",
                                                .logs_format = "LOGS ## $line%03. -- | $type%.08 $name%.08 $mesg",
                                                .atom_format = "",
                                                .gerr_format = "ERROR Generic  $debug  $line $file $func",
                                                .type = L_ALL,
                                                .name = LL_ALL,
                                                .stream = LS_STDOUT,
                                                .style = LOGGER_FALSE}
                                             };

// // END // DEFAULT
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* format:

STR
  5.   =  |_ _ s t r|. = |s t r i n~g| -> от правого края + выход за пределы
   .5  = .|s t r _ _|  = |s t r i n~g| -> от левого края  + выход за пределы

   .5: = .|s t r _ _|  = |s t r i :|   -> от правого края + показать начало
  :.5  =  |s t r _ _|  = |: r i n g|   -> от правого края + показать конец
 :5.   =  |_ _ s t r|  = |: r i n g|   -> от левого края  + показать начало
  5.:  =  |_ _ s t r|  = |s t r i :|   -> от левого края  + показать конец
 :5.:  =  |_ _ s t r|  = |: r i n g|   -> от левого края  + показать центр

второе двоеточие игнорируется

не поддерживается
  5.2  =  |_ . s t r|. = |s t r i n~g| -> размер          + выход за пределы +
смещение от левого края 5.5  =  |_ s t r _|  = |s t r i n~g| -> по центру +
выход за пределы

NUM
   05  =  |0 0 0 x x| = |x x x x x~x| -> от правого края + заполнение нулями
   5.  =  |_ _ _ x x| = |x x x x x~x| -> от правого края
   .5  =  |x x _ _ _| = |x x x x x~x| -> от левого края
*/

// clang-format on

#endif // YAYA_LOGGER_CONF_H
