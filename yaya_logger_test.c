#include "yaya_logger.h"

uintmax_t yaya_log_test(){
    logger logger_instance;

    printf("/* I */\n");
    logger_init();
    logger_init(&logger_instance);
    logger_init(&logger_instance, logger_type_def);
    logger_init(&logger_instance, logger_type_def, logger_name_def);
    logger_init(&logger_instance, logger_type_def, logger_name_def, logger_setting_def);
    logger_init(&logger_instance, logger_type_def, logger_name_def, logger_setting_def, logger_define_def);
    logger_init(&logger_instance, logger_type_def, logger_name_def, logger_setting_def, logger_define_def, logger_style_def);

    printf("/* H */\n");
    logger_head();
    logger_head(&logger_instance);
    logger_head(&logger_instance, "str");
    logger_head(&logger_instance, "str %s", "par");

//    logger_head("str");
//    logger_head("str %s", "par");

    printf("/* E */\n");
    loggerf(1);

    printf("/* 0 */\n");
    loggerf();

    printf("/* 1 */\n");
    loggerf(&logger_instance);
    loggerf(L_ALL);
    loggerf(LL_ALL);
    loggerf("str");

    printf("/* 2 */\n");
    loggerf(&logger_instance, L_ALL);
    loggerf(&logger_instance, LL_ALL);
    loggerf(&logger_instance, "srt");
    loggerf(L_ALL, LL_ALL);
    loggerf(L_ALL, "str");
    loggerf(LL_ALL, "str");
    loggerf( "str %s", "par");

    printf("/* 3 */\n");
    loggerf(&logger_instance, L_ALL, LL_ALL);
    loggerf(&logger_instance, L_ALL, "srt");
    loggerf(&logger_instance, LL_ALL, "srt");
    loggerf(&logger_instance, "srt %s", "par");
    loggerf(L_ALL, LL_ALL, "str");
    loggerf(L_ALL, "str %s", "par");
    loggerf(LL_ALL, "str %s", "par");
    loggerf("str %s %s", "par", "par");

    printf("/* 4 */\n");
    loggerf(&logger_instance, L_ALL, LL_ALL, "srt");
    loggerf(&logger_instance, L_ALL, "srt %s", "par");
    loggerf(&logger_instance, LL_ALL, "srt %s", "par");
    loggerf(&logger_instance, "srt %s %s", "par", "par");
    loggerf(L_ALL, LL_ALL, "srt %s", "par");
    loggerf(L_ALL, "str %s %s", "par", "par");
    loggerf(LL_ALL, "str %s %s", "par", "par");
    loggerf("str %s %s %s", "par", "par", "par");

    printf("/* 5 */\n");
    loggerf(&logger_instance, L_ALL, LL_ALL, "srt %s", "par");
    loggerf(&logger_instance, L_ALL, "srt %s", "par", "par");
    loggerf(&logger_instance, LL_ALL, "srt %s", "par", "par");
    loggerf(&logger_instance, "srt %s %s %s", "par", "par", "par");

    loggerf(L_ALL, LL_ALL, "srt %s %s", "par", "par");
    loggerf(L_ALL, "str %s %s %s", "par", "par", "par");
    loggerf(LL_ALL, "str %s %s %s", "par", "par", "par");
    loggerf("str %s %s %s %s", "par", "par", "par", "par");

    printf("/* 6 */\n");
    loggerf(&logger_instance, L_ALL, LL_ALL, "srt %s %s", "par", "par");
    loggerf(&logger_instance, L_ALL, "srt %s %s %s", "par", "par", "par");
    loggerf(&logger_instance, LL_ALL, "srt %s %s %s", "par", "par", "par");
    loggerf(&logger_instance, "srt %s %s %s %s", "par", "par", "par", "par");

    loggerf(L_ALL, LL_ALL, "srt %s %s %s", "par", "par", "par");
    loggerf(L_ALL, "str %s %s %s %s", "par", "par", "par", "par");
    loggerf(LL_ALL, "str %s %s %s %s", "par", "par", "par", "par");
    loggerf("str %s %s %s %s %s", "par", "par", "par", "par", "par");

    return LOGGER_TRUE;
}
