cmake_minimum_required(VERSION 3.5)
project(yaya_logger VERSION 0.1 LANGUAGES C)
set (CMAKE_C_STANDARD 11)

set(SRC_LIST
    yaya_logger_main.c
    yaya_logger.h
    yaya_logger_func.c
    yaya_logger_func_logs.c
    yaya_logger_func_init.c
    yaya_logger_func_head.c
    yaya_logger_func_style.c
    yaya_logger_func_out.c
    yaya_logger_func_build.c
    yaya_logger_func_build_num.c
    yaya_logger_func_build_str.c
    yaya_logger_func_mas_opt.c
    yaya_logger_func_mas_fnk.c
    yaya_logger_func.h
    yaya_logger_test.h
    yaya_logger_test.c)

add_executable(${PROJECT_NAME} ${SRC_LIST})

add_definitions(-DYAYA_LOGGER)
add_definitions(-std=gnu11)
