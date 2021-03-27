#include <stdio.h>
#include "test.h"

#define IF_TYPE_TEST(test) ((TYPE_TEST) & (test))

void loggerf_test_free_token(){
#if IF_TYPE_TEST(FREE_TOKEN)

    printf("^^ BEG %s \n", __func__);

    logger *logger_instance = NULL;
    loggerf_init(&logger_instance);

    int i = 0;
    for(i = 0;  i < NUM_RUN_CYCLES; i++){
        loggerf(logger_instance, L_ATOM, "$## $line%03.  >> $str");
    }

    loggerf_free(logger_instance);

    printf("^^ END %s \n", __func__);

#endif
}

void loggerf_test_free(){
#if IF_TYPE_TEST(FREE_LOGGER)

    printf("^^ BEG %s \n", __func__);

    logger *logger_instance = NULL;

    int i = 0;
    for(i = 0;  i < NUM_RUN_CYCLES; i++){
        loggerf_init(&logger_instance);
        loggerf(logger_instance);
        loggerf_free(logger_instance);
    }

    printf("^^ END %s \n", __func__);

#endif
}

void loggerf_test_param(){
#if IF_TYPE_TEST(PARAM)

    logger *logger_instance = NULL;

    printf("/* I */\n");
    loggerf_init();
    loggerf_init(&logger_instance);
    loggerf_init(&logger_instance, logger_type_def);
    loggerf_init(&logger_instance, logger_type_def, logger_name_def);
    loggerf_init(&logger_instance, logger_type_def, logger_name_def, logger_setting_def);
    loggerf_init(&logger_instance, logger_type_def, logger_name_def, logger_setting_def, logger_define_def);
    loggerf_init(&logger_instance, logger_type_def, logger_name_def, logger_setting_def, logger_define_def, logger_style_def);

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

#endif
}

void loggerf_test_token(){
#if IF_TYPE_TEST(TOKEN)

    loggerf_init();

    loggerf(L_ATOM, "$## $line%03.  >> $str");
    loggerf(L_ATOM, "$## $line%03.  >> $file");
    loggerf(L_ATOM, "$## $line%03.  >> $line");
    loggerf(L_ATOM, "$## $line%03.  >> $func");
    loggerf(L_ATOM, "$## $line%03.  >> $type");
    loggerf(L_ATOM, "$## $line%03.  >> $name");
    loggerf(L_ATOM, "$## $line%03.  >> $mesg");              /*<<<*/

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

    loggerf(L_ATOM, "$## $line%03.  >> $seed");

    loggerf(L_ATOM, "$## $line%03.  >> $alignl");
    loggerf(L_ATOM, "$## $line%03.  >> $aliggt");

    loggerf(L_ATOM, "$## $line%03.  >> $debug");

    loggerf(L_ATOM);
    loggerf(L_ATOM);
    loggerf(L_ATOM);

    loggerf_free();

#endif
}

void loggerf_test_format(){
#if IF_TYPE_TEST(FORMAT)

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

#endif
}
