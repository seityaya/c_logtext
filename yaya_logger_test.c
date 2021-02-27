#include "yaya_logger.h"

void loggerf_test_param(){
    ___logger *logger_instance = NULL;

    printf("/* I */\n");
    loggerf_init();
    loggerf_init(&logger_instance);
    loggerf_init(&logger_instance, ___logger_type_def);
    loggerf_init(&logger_instance, ___logger_type_def, ___logger_name_def);
    loggerf_init(&logger_instance, ___logger_type_def, ___logger_name_def, ___logger_setting_def);
    loggerf_init(&logger_instance, ___logger_type_def, ___logger_name_def, ___logger_setting_def, ___logger_define_def);
    loggerf_init(&logger_instance, ___logger_type_def, ___logger_name_def, ___logger_setting_def, ___logger_define_def, ___logger_style_def);

    printf("/* H */\n");
    loggerf(L_HEAD);
    loggerf(logger_instance, L_HEAD);
    loggerf(logger_instance, L_HEAD, "HEAD == $line%3. $mess");
    loggerf(logger_instance, L_HEAD, "HEAD == $line%3. $mess", "str %s", "par");
    loggerf(L_HEAD, "HEAD == $line%3. $mess ", "HEAD str %s  ", "par");
    loggerf(L_HEAD, "HEAD");



    printf("/* E */\n");
    loggerf(1);

    printf("/* 0 */\n");
    loggerf();

//    printf("/* 1 */\n");
    loggerf(logger_instance);
    loggerf(L_ALL);
    loggerf(LL_ALL);
    loggerf("str");

//    printf("/* 2 */\n");
    loggerf(logger_instance, L_ALL);
    loggerf(logger_instance, LL_ALL);
    loggerf(logger_instance, "srt");
    loggerf(L_ALL, LL_ALL);
    loggerf(L_ALL, "str");
    loggerf(LL_ALL, "str");
    loggerf( "str %s", "par");

//    printf("/* 3 */\n");
    loggerf(logger_instance, L_ALL, LL_ALL);
    loggerf(logger_instance, L_ALL, "srt");
    loggerf(logger_instance, LL_ALL, "srt");
    loggerf(logger_instance, "srt %s", "par");
    loggerf(L_ALL, LL_ALL, "str");
    loggerf(L_ALL, "str %s", "par");
    loggerf(LL_ALL, "str %s", "par");
    loggerf("str %s %s", "par", "par");

//    printf("/* 4 */\n");
    loggerf(logger_instance, L_ALL, LL_ALL, "srt");
    loggerf(logger_instance, L_ALL, "srt %s", "par");
    loggerf(logger_instance, LL_ALL, "srt %s", "par");
    loggerf(logger_instance, "srt %s %s", "par", "par");
    loggerf(L_ALL, LL_ALL, "srt %s", "par");
    loggerf(L_ALL, "str %s %s", "par", "par");
    loggerf(LL_ALL, "str %s %s", "par", "par");
    loggerf("str %s %s %s", "par", "par", "par");

//    printf("/* 5 */\n");
    loggerf(logger_instance, L_ALL, LL_ALL, "srt %s", "par");
    loggerf(logger_instance, L_ALL, "srt %s", "par", "par");
    loggerf(logger_instance, LL_ALL, "srt %s", "par", "par");
    loggerf(logger_instance, "srt %s %s %s", "par", "par", "par");

    loggerf(L_ALL, LL_ALL, "srt %s %s", "par", "par");
    loggerf(L_ALL, "str %s %s %s", "par", "par", "par");
    loggerf(LL_ALL, "str %s %s %s", "par", "par", "par");
    loggerf("str %s %s %s %s", "par", "par", "par", "par");

//    printf("/* 6 */\n");
    loggerf(logger_instance, L_ALL, LL_ALL, "srt %s %s", "par", "par");
    loggerf(logger_instance, L_ALL, "srt %s %s %s", "par", "par", "par");
    loggerf(logger_instance, LL_ALL, "srt %s %s %s", "par", "par", "par");
    loggerf(logger_instance, "srt %s %s %s %s", "par", "par", "par", "par");

    loggerf(L_ALL, LL_ALL, "srt %s %s %s", "par", "par", "par");
    loggerf(L_ALL, "str %s %s %s %s", "par", "par", "par", "par");
    loggerf(LL_ALL, "str %s %s %s %s", "par", "par", "par", "par");
    loggerf("str %s %s %s %s %s", "par", "par", "par", "par", "par");
}

void loggerf_test_format(){

    loggerf_init();

    loggerf(L_ATOM, "## $line%03.  >> $str");
    loggerf(L_ATOM, "## $line%03.  >> $file");
    loggerf(L_ATOM, "## $line%03.  >> $line");
    loggerf(L_ATOM, "## $line%03.  >> $func");
    loggerf(L_ATOM, "## $line%03.  >> $type");
    loggerf(L_ATOM, "## $line%03.  >> $name");
    loggerf(L_ATOM, "## $line%03.  >> $mesg");              /*<<<*/

    loggerf(L_ATOM, "## $line%03.  >> $count");
    loggerf(L_ATOM, "## $line%03.  >> $curnum");
    loggerf(L_ATOM, "## $line%03.  >> $absnum");

    loggerf(L_ATOM, "## $line%03.  >> $data_build");
    loggerf(L_ATOM, "## $line%03.  >> $time_build");
    loggerf(L_ATOM, "## $line%03.  >> $data_curent");
    loggerf(L_ATOM, "## $line%03.  >> $time_curent");

    loggerf(L_ATOM, "## $line%03.  >> $prog");
    loggerf(L_ATOM, "## $line%03.  >> $prog_v");
    loggerf(L_ATOM, "## $line%03.  >> $prog_p");
    loggerf(L_ATOM, "## $line%03.  >> $proj");
    loggerf(L_ATOM, "## $line%03.  >> $compiler");
    loggerf(L_ATOM, "## $line%03.  >> $compiler_v");

    loggerf(L_ATOM, "## $line%03.  >> $tik_core");
    loggerf(L_ATOM, "## $line%03.  >> $tik_sec");
    loggerf(L_ATOM, "## $line%03.  >> $tic_rtos");
    loggerf(L_ATOM, "## $line%03.  >> $tik_unix");

    loggerf(L_ATOM, "## $line%03.  >> $type_filter");
    loggerf(L_ATOM, "## $line%03.  >> $name_filter");
    loggerf(L_ATOM, "## $line%03.  >> $type_mask");
    loggerf(L_ATOM, "## $line%03.  >> $name_mask");
    loggerf(L_ATOM, "## $line%03.  >> $type_list");
    loggerf(L_ATOM, "## $line%03.  >> $name_list");

    loggerf(L_ATOM, "## $line%03.  >> $seed");

    loggerf(L_ATOM, "## $line%03.  >> $alignl");
    loggerf(L_ATOM, "## $line%03.  >> $aliggt");

    loggerf(L_ATOM, "## $line%03.  >> $debug");

}
