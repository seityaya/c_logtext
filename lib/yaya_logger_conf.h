//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#ifndef YAYA_LOGGER_CONF_H_
#define YAYA_LOGGER_CONF_H_

// clang-format off

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // OPTION

/*Включить логгер*/
#ifndef LOGGER_LOGS          /*Работает*/
#define LOGGER_LOGS          LOGGER_ON
#endif

/*Метод  выделения памяти*/
#ifndef LOGGER_STATIC        /*В разработке*/
#define LOGGER_STATIC        LOGGER_OFF
#endif

/*Включить стили*/
#ifndef LOGGER_OUT           /*Работает*/
#define LOGGER_OUT           LOGGER_ON //or (DLS_STDOUT | DLS_STDERR | DLS_STDBUF | DLS_STDFILE | DLS_STDCSV)
#endif

/*Включить стили*/
#ifndef LOGGER_STYLE         /*В разработке*/
#define LOGGER_STYLE         LOGGER_ON
#endif

/*Включить вложенный вывод*/
#ifndef LOGGER_RECURSION     /*Работает*/
#define LOGGER_RECURSION     LOGGER_ON
#endif

/*Включить заголовок как отдельный формат*/
#ifndef LOGGER_FORMAT_HEAD   /*Работает*/
#define LOGGER_FORMAT_HEAD   LOGGER_ON
#endif

/*Включить динамический вычисляемый формат*/
#ifndef LOGGER_FORMAT_ATOM   /*Работает*/
#define LOGGER_FORMAT_ATOM   LOGGER_ON
#endif

/*Включить вывод перед очисткой как отдельный формат*/
#ifndef LOGGER_FORMAT_FREE   /*Работает*/
#define LOGGER_FORMAT_FREE   LOGGER_ON
#endif

/*Включить ошибку логера как отдельный формат*/
#ifndef LOGGER_FORMAT_ERROR  /*Работает*/
#define LOGGER_FORMAT_ERROR  LOGGER_ON
#endif

/*Строка скрыватель*/
#ifndef LOGGER_HIDDEN_STR    /*Работает*/
#define LOGGER_HIDDEN_STR    "..."
#endif

/*Размер буфера для вывода*/
#ifndef LOGGER_OUT_BUFF_SIZE
#define LOGGER_OUT_BUFF_SIZE 1000
#endif

/*Размер буфера для нужд логера*/
#ifndef LOGGER_TMP_BUFF_SIZE
#define LOGGER_TMP_BUFF_SIZE 500
#endif

#if LOGGER_STATIC
/*Максимальное количество токенов в строке*/
#define LOGGER_NUM_TOKEN 20
#endif

// // END // OPTION
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // HEADER

#include "yaya_logger_public.h"

// // END // HEADER
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // DEFAULT

static void* logger_main_def = NULL;

#define L_NUL      LOGGER_FLAG_T_NUL          /*<<< BEG <<<*/
#define L_VOID     LOGGER_FLAG_T_GENERATE( 0) /*<<< VOID      FORMAT TYPE*/
#define L_HEAD     LOGGER_FLAG_T_GENERATE( 1) /*<<< HEAD      FORMAT TYPE*/
#define L_ATOM     LOGGER_FLAG_T_GENERATE( 2) /*<<< ATOM      FORMAT TYPE*/
#define L_FREE     LOGGER_FLAG_T_GENERATE( 3) /*<<< FREE      FORMAT TYPE*/
#define L_GNERR    LOGGER_FLAG_T_GENERATE( 4) /*<<< GENERIC   ERROR  TYPE*/
#define L_BEGF     LOGGER_FLAG_T_GENERATE( 5) /*<<< RECURSION FORMAT TYPE*/
#define L_ENDF     LOGGER_FLAG_T_GENERATE( 6) /*<<< RECURSION FORMAT TYPE*/
#define L_INFO     LOGGER_FLAG_T_GENERATE( 7)
#define L_ERROR    LOGGER_FLAG_T_GENERATE( 8)
#define L_WARNING  LOGGER_FLAG_T_GENERATE( 9)
#define L_TODO     LOGGER_FLAG_T_GENERATE(10)
#define L_FIXME    LOGGER_FLAG_T_GENERATE(11)
#define L_DEBUG    LOGGER_FLAG_T_GENERATE(12)
#define L_RELEASE  LOGGER_FLAG_T_GENERATE(13)
#define L_TRACE    LOGGER_FLAG_T_GENERATE(14)
#define L_WARN     LOGGER_FLAG_T_GENERATE(15)
#define L_FATAL    LOGGER_FLAG_T_GENERATE(16)
#define L_FUNC     LOGGER_FLAG_T_GENERATE(17)
#define L_LOGGER   LOGGER_FLAG_T_GENERATE(18)
#define L_TEST     LOGGER_FLAG_T_GENERATE(19)
#define L_MESG     LOGGER_FLAG_T_GENERATE(20)
#define L_ALL      LOGGER_FLAG_T_ALL          /*<<< END <<<*/

static logger_filter logger_type_l1_def[] = { LOGGER_FILTER_GENERATE(L_NUL),
                                              LOGGER_FILTER_GENERATE(L_VOID),
                                              LOGGER_FILTER_GENERATE(L_HEAD),
                                              LOGGER_FILTER_GENERATE(L_ATOM),
                                              LOGGER_FILTER_GENERATE(L_FREE),
                                              LOGGER_FILTER_GENERATE(L_GNERR),
                                              LOGGER_FILTER_GENERATE(L_BEGF),
                                              LOGGER_FILTER_GENERATE(L_ENDF),
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
                                              LOGGER_FILTER_GENERATE(L_FUNC),
                                              LOGGER_FILTER_GENERATE(L_LOGGER),
                                              LOGGER_FILTER_GENERATE(L_TEST),
                                              LOGGER_FILTER_GENERATE(L_MESG),
                                              LOGGER_FILTER_GENERATE(L_ALL)
                                            };


#define LL_NUL   LOGGER_FLAG_N_NUL         /*<<< BEG <<<*/
#define LL_VOID  LOGGER_FLAG_N_GENERATE(0) /*<<< VOID   FORMAT NAME*/
#define LL_DEFI  LOGGER_FLAG_N_GENERATE(1)
#define LL_INIT  LOGGER_FLAG_N_GENERATE(2)
#define LL_MAIN  LOGGER_FLAG_N_GENERATE(3)
#define LL_DRVR  LOGGER_FLAG_N_GENERATE(4)
#define LL_ALL   LOGGER_FLAG_N_ALL         /*<<< END <<<*/

static logger_filter logger_name_l2_def[] = { LOGGER_FILTER_GENERATE(LL_NUL),
                                              LOGGER_FILTER_GENERATE(LL_VOID),
                                              LOGGER_FILTER_GENERATE(LL_DEFI),
                                              LOGGER_FILTER_GENERATE(LL_INIT),
                                              LOGGER_FILTER_GENERATE(LL_MAIN),
                                              LOGGER_FILTER_GENERATE(LL_DRVR),
                                              LOGGER_FILTER_GENERATE(LL_ALL)
                                            };


static logger_setting logger_setting_def[] = {
    {
        .logs_format = "LOGS ## $line%03. -- | $type%.08 $name%.08 $mesg",
        #if LOGGER_FORMAT_HEAD
        .head_format = "HEAD ## $line%3. $mesg",
        #endif
        #if LOGGER_FORMAT_ATOM
        .atom_format = "ATOM ## $mesg",
        #endif
        #if LOGGER_FORMAT_FREE
        .free_format = "FREE ## $stats",
        #endif
        #if LOGGER_FORMAT_ERROR
        .gerr_format = "ERROR Generic  $generic  $line $file $func",
        #endif
        .type_l1 = L_ALL,
        .name_l2 = LL_ALL,
        .stream  = LS_STDOUT,
        .out_file = "/tmp/log.txt",
    }
};


static logger_define logger_define_def[] = { { .prog = "yaya_logger",
                                               .proj = "yaya_library_collection_for_C",
                                               .version = "v0.1",
                                             }
                                           };


static logger_style logger_style_def[] = { {L_HEAD,  {0, 0, 0}, {0, 0, 0}, LSM_NONE},
                                           {L_ATOM,  {0, 0, 0}, {0, 0, 0}, LSM_NONE},
                                           {L_GNERR, {0, 0, 0}, {0, 0, 0}, LSM_NONE}
                                         };


// // END // DEFAULT
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // BEG // FORMAT
/*
 * %[скрыватель][флаги][ширина_целое][.ширина_дробное][скрыватель][тип_основание]
 * [флаги] -> [знак][заполнение][прижать][приставка]
 *
 * скрыватель: (работает только для строк)
 *        : -> скрывает текст с начала или с конца если текст не помещается по ширине; если стоят оба отдаёт предпочтение первому
 *        x -> ничего не делает
 * знак: (работает только для чисел)
 *        + -> всегда указывать знак (плюс или минус) для выводимого десятичного числового значения
 *        - -> оставлять место под знак минус
 *        x -> место не будет выделено, знак минус будет сдвигать число
 * заполнение: (работает только для чисел и если установлено основание)
 *        0 -> заполнять пустое место перед числом нулями
 *        _ -> не запонять пустое место, вставляя на пустое место пробелы
 *        x -> тоже что и [_]
 * прижать: (работает только для чисел и если установлено основание)
 *        l -> к левому краю
 *        r -> к правому краю
 *        x -> тоже что и [l]
 * приставка: (работает только для чисел)
 *        p -> 2 => bxN; 8 => oxN; 16 => hxN;
 *        P -> 2 => BxN; 8 => OxN; 16 => HxN;
 *        s -> 2 => Nxb; 8 => Nxo; 16 => Nxh;
 *        S -> 2 => NxB; 8 => NxO; 16 => NxH;
 *        x -> не использовать приставку
 *
 * ширина_целое:
 *        N -> Десятичное число, указывает минимальную ширину поля строки или для основания числа(не включая флаги для чисел).
 *             Если представление величины больше, чем ширина поля, то запись выходит за пределы поля, если нет соответствующих модификаторов
 *        x -> Выводятся без выравнивания
 *
 * ширина_дробное: (работает только для десятичных чисел с плавающей запятой)
 *        N -> Устанавливает количество знаков после десятично точки
 *        x -> выводятся все знаки
 *
 * основание:
 *        b, B - выводить как двоичное целое
 *        o, O - выводить как восьмеричное целое
 *        d, D - выводить как десятичное целое
 *        h, H - выводить как шестнадцатеричное целое
 *        e, E - N.Me+1, N.ME+1;  N.Me+0, N.ME+0;  N.Me-1, N.ME-1;
 *        f, F - N.M
 */

/*
NUM
   %5   =  |_ _ _ x x|  = |x x x x x~x|
   %05  =  |0 0 0 x x|  = |x x x x x~x| -> от правого края + заполнение нулями
   %5.  =  |_ _ _ x x|  = |x x x x x~x| -> от правого края
   %.5  =  |x x _ _ _|  = |x x x x x~x| -> от левого края

STR
  5.   =  |_ _ s t r|. = |s t r i n~g| -> от правого края + выход за пределы  T1
   .5  = .|s t r _ _|  = |s t r i n~g| -> от левого края  + выход за пределы  T2

   .5: = .|s t r _ _|  = |s t r i :|   -> от правого края + показать начало
  :.5  = .|s t r _ _|  = |: r i n g|   -> от правого края + показать конец
 :5.   =  |_ _ s t r|. = |: r i n g|   -> от левого края  + показать начало
  5.:  =  |_ _ s t r|. = |s t r i :|   -> от левого края  + показать конец
 :5.:  =  |_ _ s t r|. = |: r i n g|   -> второе двоеточие игнорируется

не поддерживается
  5.2  =  |_ . s t r|. = |s t r i n~g| -> размер + выход за пределы +
смещение от левого края 5.5  =  |_ s t r _|  = |s t r i n~g| -> по центру + выход за пределы
*/
// // END // FORMAT
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////

// clang-format on

#endif // YAYA_LOGGER_CONF_H_
