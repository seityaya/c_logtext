#ifndef YAYA_LOGGER_CONF_H
#define YAYA_LOGGER_CONF_H

#include "yaya_logger_macro.h"
#include "yaya_logger_struct.h"
#include "yaya_logger_format.h"

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // OPTION

#define LOGGER_LOGS   LOGGER_TRUE        /*Включить логгер*/
#define LOGGER_STYLE  LOGGER_TRUE        /*Включить стили*/
#define LOGGER_OUT    LOGGER_TRUE        /*Включить вывод*/
#define LOGGER_DEF    LOGGER_TRUE        /*Включить структуру*/
#define LOGGER_TEST   LOGGER_FALSE        /*Включить отладку*/

#define LOGGER_HIDDEN_STR        "..."
#define LOGGER_OUT_BUFF_SIZE     1000
#define LOGGER_TMP_BUFF_SIZE     500
#define LOGGER_NUM_TOKEN_OR_AUTO 0       /*if 0, auto allocation*/

// // END // OPTION
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if LOGGER_DEF == LOGGER_TRUE
static ___logger* ___logger_main_def = NULL;
#endif


#define    L_NUL      LOGGER_FLAG_T_NUL          /*<<<*/
#define    L_VOID     LOGGER_FLAG_T_GENERATE( 0) /*<<<*/
#define    L_HEAD     LOGGER_FLAG_T_GENERATE( 1) /*<<<*/
#define    L_ATOM     LOGGER_FLAG_T_GENERATE( 2) /*<<<*/
#define    L_DEFI     LOGGER_FLAG_T_GENERATE( 3)
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
#define    L_ALL      LOGGER_FLAG_T_ALL          /*<<<*/

LOGGER_NEW_COUNTER(LT_COUNTER)
static ___logger_filter ___logger_type_def[] = { LOGGER_FILTER_GENERATE(LT_COUNTER, L, NUL),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, VOID),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, HEAD),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, ATOM),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, DEFI),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, INFO),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, ERROR),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, WARNING),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, TODO),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, FIXME),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, DEBUG),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, RELEASE),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, TRACE),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, WARN),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, FATAL),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, BEGF),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, ENDF),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, FUNC),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, LOGGER),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, TEST),
                                                 LOGGER_FILTER_GENERATE(LT_COUNTER, L, ALL)
                                               };


#define    LL_NUL   LOGGER_FLAG_N_NUL         /*<<<*/
#define    LL_VOID  LOGGER_FLAG_N_GENERATE(0) /*<<<*/
#define    LL_DEFI  LOGGER_FLAG_N_GENERATE(1)
#define    LL_MAIN  LOGGER_FLAG_N_GENERATE(2)
#define    LL_INIT  LOGGER_FLAG_N_GENERATE(3)
#define    LL_DRVR  LOGGER_FLAG_N_GENERATE(4)
#define    LL_ALL   LOGGER_FLAG_N_ALL         /*<<<*/

LOGGER_NEW_COUNTER(LN_COUNTER)
static ___logger_filter ___logger_name_def[] = { LOGGER_FILTER_GENERATE(LN_COUNTER, LL, NUL),
                                                 LOGGER_FILTER_GENERATE(LN_COUNTER, LL, VOID),
                                                 LOGGER_FILTER_GENERATE(LN_COUNTER, LL, DEFI),
                                                 LOGGER_FILTER_GENERATE(LN_COUNTER, LL, MAIN),
                                                 LOGGER_FILTER_GENERATE(LN_COUNTER, LL, INIT),
                                                 LOGGER_FILTER_GENERATE(LN_COUNTER, LL, DRVR),
                                                 LOGGER_FILTER_GENERATE(LN_COUNTER, LL, ALL)
                                               };


static ___logger_style ___logger_style_def[] = { {LEF_mesg, {0, 0, 0}, {0, 0, 0}, LSM_NONE},
                                                 {LEF_file, {0, 0, 0}, {0, 0, 0}, LSM_NONE},
                                                 {LEF_line, {0, 0, 0}, {0, 0, 0}, LSM_NONE}
                                               };


static ___logger_define ___logger_define_def[] = { {.seed = 0,
                                                    .prog = "yaya_logger",
                                                    .proj = "yaya_library_collection_for_C",
                                                    .version = "v0.1",
                                                    .compiler = "gcc 7 x64"}
                                                 };


static ___logger_setting ___logger_setting_def[] = { {.head_format = "HEAD ## $line%3. $mess",
                                                      .logs_format = "LOGS ## $line%03. -- | $type%.08 $name%.08 $mesg",
                                                      .atom_format = " ",
                                                      .type = L_ALL,
                                                      .name = LL_ALL,
                                                      .stream = LS_STDOUT,
                                                      .style = LOGGER_FALSE}
                                                   };


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

#endif // YAYA_LOGGER_CONF_H
