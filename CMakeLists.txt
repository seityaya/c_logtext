cmake_minimum_required(VERSION 3.5)

set(VERSION 0.1)
set(CMAKE_C_STANDARD 11)
set(PROJECT_NAME yaya_logger)

set(MAIN_LIST
    yaya_logger_main.c
    )

set(SRC_LIST

    yaya_logger_func_logs.c
    yaya_logger_func_init.c
    yaya_logger_func_info.c
    yaya_logger_func_head.c
    yaya_logger_func_style.c
    yaya_logger_func_out.c
    yaya_logger_func_build.c
    yaya_logger_func_build_num.c
    yaya_logger_func_build_str.c
    yaya_logger_func_build_fnc.c
    yaya_logger_func_mas_opt.c
    )

set(INC_LIST
    yaya_logger.h
    yaya_logger_main.h
    yaya_logger_conf.h
    yaya_logger_struct.h
    yaya_logger_func_build_fnc.h
    )

#add_library(${PROJECT_NAME} STATIC ${SRC_LIST} ${INC_LIST})
add_executable(${PROJECT_NAME} ${MAIN_LIST} ${SRC_LIST} ${INC_LIST})

add_definitions(-DYAYA_LOGGER)
add_definitions(-std=gnu11)
