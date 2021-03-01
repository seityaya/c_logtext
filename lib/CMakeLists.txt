cmake_minimum_required(VERSION 3.5)

set(VERSION 0.1)
set(CMAKE_C_STANDARD 11)
set(PROJECT_NAME yaya_logger)

project(${PROJECT_NAME})

set(SRC_LIST
    yaya_logger_func.c
    yaya_logger_init.c
    yaya_logger_style.c
    yaya_logger_out.c
    yaya_logger_format.c
    yaya_logger_pars.c
    )

set(INC_LIST
    yaya_logger.h
    yaya_logger_conf.h
    yaya_logger_macro.h
    yaya_logger_struct.h
    yaya_logger_format.h
    )

add_library(${PROJECT_NAME} STATIC ${SRC_LIST} ${INC_LIST})
#add_executable(${PROJECT_NAME} ${SRC_LIST} ${INC_LIST})

add_definitions(-std=gnu11)
