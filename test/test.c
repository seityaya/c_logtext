//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#include <stdio.h>
#include <inttypes.h>

#include "test.h"

#define IF_TYPE_TEST(test) ((TYPE_TEST) & (test))

void test_printf(){
    printf("^^ BEG %s \n", __func__);

    for(intmax_t i = 0;  i < NUM_RUN_CYCLES; i++){
        printf("## %03d  >> %s %" PRIiMAX " \n" , __LINE__, __func__, i);
    }

    printf("^^ END %s \n\n\n\n", __func__);
}

void loggerf_test_free_token(){
    printf("^^ BEG %s \n", __func__);

    void *logger_instance = NULL;
    loggerf_init(&logger_instance);

    for(intmax_t i = 0;  i < NUM_RUN_CYCLES; i++){
        loggerf(logger_instance, L_ATOM, "$## $line%03.  >> $func $mesg" , "%" PRIuMAX "", i);
    }

    loggerf_free(logger_instance);

    printf("^^ END %s \n\n\n\n", __func__);
}

void loggerf_test_free(){
    printf("^^ BEG %s \n", __func__);

    void *logger_instance = NULL;

    logger_setting my_logger_setting[] = { { .head_format = "HEAD ## $line%3. >> $mesg",
                                             .logs_format = "$## $line%03.  >> $func $mesg",
                                             .atom_format = "$## line",
                                             .gerr_format = ">>ERROR<<",
                                             .type_l1 = L_ALL,
                                             .name_l2 = LL_ALL,
                                             .stream = LS_STDOUT,
                                           } };

    for(intmax_t i = 0;  i < NUM_RUN_CYCLES; i++){
        loggerf_init(&logger_instance, NULL, NULL, my_logger_setting);
        loggerf(logger_instance, L_VOID, "%" PRIuMAX "", i);
        loggerf_free(logger_instance);
    }

    printf("^^ END %s \n\n\n\n", __func__);
}

void loggerf_test_param(){
    printf("^^ BEG %s \n", __func__);

    void *logger_instance = NULL;

    printf("/* I */\n");
    loggerf_init();
    loggerf_init(&logger_instance);
    loggerf_init(&logger_instance, logger_type_l1_def);
    loggerf_init(&logger_instance, logger_type_l1_def, logger_name_l2_def);
    loggerf_init(&logger_instance, logger_type_l1_def, logger_name_l2_def, logger_setting_def);
    loggerf_init(&logger_instance, logger_type_l1_def, logger_name_l2_def, logger_setting_def, logger_define_def);
    loggerf_init(&logger_instance, logger_type_l1_def, logger_name_l2_def, logger_setting_def, logger_define_def, logger_style_def);

    printf("/* H */\n");
    loggerf(L_HEAD);
    loggerf(logger_instance, L_HEAD);
    loggerf(logger_instance, L_HEAD, "HEAD == $line%3. $mesg");
    loggerf(logger_instance, L_HEAD, "HEAD == $line%3. $mesg", "str %s", "par");
    loggerf(L_HEAD, "HEAD == $line%3. $mesg ", "HEAD str %s  ", "par");
    loggerf(L_HEAD, "HEAD");

    printf("/* A */\n");
    loggerf(L_ATOM);

    printf("/* E */\n");
    loggerf(L_GNERR);
    loggerf(1);

    printf("/* 0 */\n");
    loggerf();

    printf("/* 1 */\n");
    loggerf(logger_instance);
    loggerf(L_ALL);
    loggerf(LL_ALL);
    loggerf("str");

    printf("/* 2 */\n");
    loggerf(logger_instance, L_ALL);
    loggerf(logger_instance, LL_ALL);
    loggerf(logger_instance, "srt");
    loggerf(L_ALL, LL_ALL);
    loggerf(L_ALL, "str");
    loggerf(LL_ALL, "str");
    loggerf( "str %s", "par");

    printf("/* 3 */\n");
    loggerf(logger_instance, L_ALL, LL_ALL);
    loggerf(logger_instance, L_ALL, "srt");
    loggerf(logger_instance, LL_ALL, "srt");
    loggerf(logger_instance, "srt %s", "par");
    loggerf(L_ALL, LL_ALL, "str");
    loggerf(L_ALL, "str %s", "par");
    loggerf(LL_ALL, "str %s", "par");
    loggerf("str %s %s", "par", "par");

    printf("/* 4 */\n");
    loggerf(logger_instance, L_ALL, LL_ALL, "srt");
    loggerf(logger_instance, L_ALL, "srt %s", "par");
    loggerf(logger_instance, LL_ALL, "srt %s", "par");
    loggerf(logger_instance, "srt %s %s", "par", "par");
    loggerf(L_ALL, LL_ALL, "srt %s", "par");
    loggerf(L_ALL, "str %s %s", "par", "par");
    loggerf(LL_ALL, "str %s %s", "par", "par");
    loggerf("str %s %s %s", "par", "par", "par");

    printf("/* 5 */\n");
    loggerf(logger_instance, L_ALL, LL_ALL, "srt %s", "par");
    loggerf(logger_instance, L_ALL, "srt %s", "par", "par");
    loggerf(logger_instance, LL_ALL, "srt %s", "par", "par");
    loggerf(logger_instance, "srt %s %s %s", "par", "par", "par");

    loggerf(L_ALL, LL_ALL, "srt %s %s", "par", "par");
    loggerf(L_ALL, "str %s %s %s", "par", "par", "par");
    loggerf(LL_ALL, "str %s %s %s", "par", "par", "par");
    loggerf("str %s %s %s %s", "par", "par", "par", "par");

    printf("/* 6 */\n");
    loggerf(logger_instance, L_ALL, LL_ALL, "srt %s %s", "par", "par");
    loggerf(logger_instance, L_ALL, "srt %s %s %s", "par", "par", "par");
    loggerf(logger_instance, LL_ALL, "srt %s %s %s", "par", "par", "par");
    loggerf(logger_instance, "srt %s %s %s %s", "par", "par", "par", "par");

    loggerf(L_ALL, LL_ALL, "srt %s %s %s", "par", "par", "par");
    loggerf(L_ALL, "str %s %s %s %s", "par", "par", "par", "par");
    loggerf(LL_ALL, "str %s %s %s %s", "par", "par", "par", "par");
    loggerf("str %s %s %s %s %s", "par", "par", "par", "par", "par");

    loggerf_free();
    loggerf_free(logger_instance);

    printf("^^ END %s \n\n\n\n", __func__);
}

void loggerf_test_token(){
    printf("^^ BEG %s \n", __func__);

    loggerf_init();

    loggerf(L_ATOM, "$str", "str"); /*<<<*/
    loggerf(L_ATOM, "$STR", "STR"); /*<<<*/
    loggerf(L_ATOM, "$## $line%03.  >> $str");
    loggerf(L_ATOM, "$## $line%03.  >> $file");
    loggerf(L_ATOM, "$## $line%03.  >> $line");
    loggerf(L_ATOM, "$## $line%03.  >> $func");
    loggerf(L_ATOM, "$## $line%03.  >> $type");
    loggerf(L_ATOM, "$## $line%03.  >> $name");
    loggerf(L_ATOM, "$## $line%03.  >> $mesg", "mesg"); /*<<<*/
    loggerf(L_ATOM, "$## $line%03.  >> $mesg", "$mesg", "$mesg"); /*<<<*/

    loggerf(L_ATOM, "$## $line%03.  >> $count");
    loggerf(L_ATOM, "$## $line%03.  >> $curnum");
    loggerf(L_ATOM, "$## $line%03.  >> $absnum");

    loggerf(L_ATOM, "$## $line%03.  >> $data_build");
    loggerf(L_ATOM, "$## $line%03.  >> $time_build");
    loggerf(L_ATOM, "$## $line%03.  >> $data_curent");
    loggerf(L_ATOM, "$## $line%03.  >> $time_curent");

    loggerf(L_ATOM, "$## $line%03.  >> $prog");
    loggerf(L_ATOM, "$## $line%03.  >> $prog_v");
    loggerf(L_ATOM, "$## $line%03.  >> $prog_p");
    loggerf(L_ATOM, "$## $line%03.  >> $proj");
    loggerf(L_ATOM, "$## $line%03.  >> $compiler");
    loggerf(L_ATOM, "$## $line%03.  >> $compiler_v");

    loggerf(L_ATOM, "$## $line%03.  >> $tik_core");
    loggerf(L_ATOM, "$## $line%03.  >> $tik_sec");
    loggerf(L_ATOM, "$## $line%03.  >> $tic_rtos");
    loggerf(L_ATOM, "$## $line%03.  >> $tik_unix");

    loggerf(L_ATOM, "$## $line%03.  >> $type_filter");
    loggerf(L_ATOM, "$## $line%03.  >> $name_filter");
    loggerf(L_ATOM, "$## $line%03.  >> $type_mask");
    loggerf(L_ATOM, "$## $line%03.  >> $name_mask");
    loggerf(L_ATOM, "$## $line%03.  >> $type_list");
    loggerf(L_ATOM, "$## $line%03.  >> $name_list");

    loggerf(L_ATOM, "$## $line%03.  >> $alignl");
    loggerf(L_ATOM, "$## $line%03.  >> $aliggt");

    loggerf(L_ATOM, "$## $line%03.  >> $debug");

    loggerf_free();

    printf("^^ END %s \n\n\n\n", __func__);
}

void loggerf_test_format(){
    printf("^^ BEG %s \n", __func__);

    loggerf_init();

    loggerf(L_ATOM, "$** $line%03.  >> $num         |$line|");

    loggerf(L_ATOM);

    loggerf(L_ATOM, "$** $line%03.  >> $num%5       |$line%5|");
    loggerf(L_ATOM, "$** $line%03.  >> $num%.5      |$line%.5|");
    loggerf(L_ATOM, "$** $line%03.  >> $num%5.      |$line%5.|");
    loggerf(L_ATOM, "$** $line%03.  >> $num%05.     |$line%05.|");
    loggerf(L_ATOM, "$** $line%03.  >> $num%5.0     |$line%5.0|");

    loggerf(L_ATOM);

    loggerf(L_ATOM, "$** $line%03.  >> $num%2       |$line%2|");
    loggerf(L_ATOM, "$** $line%03.  >> $num%.2      |$line%.2|");
    loggerf(L_ATOM, "$** $line%03.  >> $num%2.      |$line%2.|");
    loggerf(L_ATOM, "$** $line%03.  >> $num%02.     |$line%02.|");
    loggerf(L_ATOM, "$** $line%03.  >> $num%2.0     |$line%2.0|");

    loggerf(L_ATOM);
    loggerf(L_ATOM, "$mesg", "======================================================");

    loggerf(L_ATOM, "$** $line%03.  >> $str         |$mesg|", "str");

    loggerf(L_ATOM);

    loggerf(L_ATOM, "$** $line%03.  >> $str%9       |$mesg%9|"    , "string");
    loggerf(L_ATOM, "$** $line%03.  >> $str%.9      |$mesg%.9|"   , "string");
    loggerf(L_ATOM, "$** $line%03.  >> $str%9.      |$mesg%9.|"   , "string");
    loggerf(L_ATOM, "$** $line%03.  >> $str%09.     |$mesg%09.|"  , "string");
    loggerf(L_ATOM, "$** $line%03.  >> $str%9.0     |$mesg%9.0|"  , "string");

    loggerf(L_ATOM);

    loggerf(L_ATOM, "$** $line%03.  >> $str%5       |$mesg%5|"    , "string");
    loggerf(L_ATOM, "$** $line%03.  >> $str%.5      |$mesg%.5|"   , "string");
    loggerf(L_ATOM, "$** $line%03.  >> $str%5.      |$mesg%5.|"   , "string");
    loggerf(L_ATOM, "$** $line%03.  >> $str%05.     |$mesg%05.|"  , "string");
    loggerf(L_ATOM, "$** $line%03.  >> $str%5.0     |$mesg%5.0|"  , "string");

    loggerf(L_ATOM);

    loggerf(L_ATOM, "$** $line%03.  >> $str%:5       |$mesg%5|"    , "string");
    loggerf(L_ATOM, "$** $line%03.  >> $str%:.5      |$mesg%.5|"   , "string");
    loggerf(L_ATOM, "$** $line%03.  >> $str%:5.      |$mesg%5.|"   , "string");
    loggerf(L_ATOM, "$** $line%03.  >> $str%:05.     |$mesg%05.|"  , "string");
    loggerf(L_ATOM, "$** $line%03.  >> $str%:5.0     |$mesg%5.0|"  , "string");

    loggerf_free();

    printf("^^ END %s \n\n\n\n", __func__);
}

void loggerf_test_output(){
    void *logger_instance = NULL;

    logger_setting setting = logger_setting_def[0];
    setting.logs_format = "LOGS ## $data_curent $time_curent >> $line%03. -- | $type%.08 $name%.08 $mesg";


    setting.stream = LS_STDOUT;
    loggerf_init(&logger_instance, NULL, NULL, &setting);
    loggerf(logger_instance, "LS_STDOUT 1");
    loggerf(logger_instance, "LS_STDOUT 2");
    loggerf(logger_instance, "LS_STDOUT 3");
    loggerf_free(logger_instance);


    setting.stream = LS_STDERR;
    loggerf_init(&logger_instance, NULL, NULL, &setting);
    loggerf(logger_instance, "LS_STDERR 1");
    loggerf(logger_instance, "LS_STDERR 2");
    loggerf(logger_instance, "LS_STDERR 3");
    loggerf_free(logger_instance);


#define BUFF_SIZE 2
    char buff[BUFF_SIZE] = {0};
    size_t size = 0;

    setting.stream = LS_STDBUF;
    setting.out_buff = buff;
    setting.out_size = &size;
    setting.size_buff = BUFF_SIZE;

    loggerf_init(&logger_instance, NULL, NULL, &setting);
    loggerf(logger_instance, "LS_STDBUF 1");
    loggerf(logger_instance, "LS_STDBUF 2");
    loggerf(logger_instance, "LS_STDBUF 3");
    while(!loggerf_flush(logger_instance)){
        fwrite(buff, sizeof(char), size, stdout);
    }
    loggerf_free(logger_instance);


    printf("%s\n", "/tmp/logger_test.txt");
    setting.stream = LS_STDFILE;
    setting.out_file = "/tmp/logger_test.txt";
    loggerf_init(&logger_instance, NULL, NULL, &setting);
    loggerf(logger_instance, "LS_STDFILE 1");
    loggerf(logger_instance, "LS_STDFILE 2");
    loggerf(logger_instance, "LS_STDFILE 3");
    loggerf_free(logger_instance);


    printf("%s\n", "/tmp/logger_test.csv");
    setting.stream = LS_STDCSV;
    setting.out_file = "/tmp/logger_test.csv";
    loggerf_init(&logger_instance, NULL, NULL, &setting);
    loggerf(logger_instance, "LS_STDCSV 1");
    loggerf(logger_instance, "LS_STDCSV 2");
    loggerf(logger_instance, "LS_STDCSV 3");
    loggerf_free(logger_instance);
}
