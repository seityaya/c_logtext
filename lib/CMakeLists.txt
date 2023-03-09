#Author                 : Seityagiya Terlekchi
#Contacts               : seityaya@ukr.net
#Creation Date          : 2020.02
#License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
#SPDX-License-Identifier: LGPL-2.1-or-later
#Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_STANDARD 11)
add_definitions(-std=c11)

set(VERSION 0.1)
set(PROJECT_NAME yaya_logger)

project(${PROJECT_NAME})

add_definitions(-DYAYA_MEMORY_STATS_USE=1)

set(SRC_LIST
    yaya_logger.c
    yaya_logger_format.c
    yaya_logger_func.c
    yaya_logger_out.c
    yaya_logger_pars.c
    yaya_logger_style.c
    yaya_logger_static.c
    )

set(INC_LIST
    yaya_logger.h
    yaya_logger_conf.h
    yaya_logger_private.h
    yaya_logger_public.h
    )

add_library(${PROJECT_NAME} SHARED ${SRC_LIST} ${INC_LIST})
#add_executable(${PROJECT_NAME} ${SRC_LIST} ${INC_LIST})

add_subdirectory(${CMAKE_SOURCE_DIR}/../../yaya_memory/lib/ yaya_memory)
target_include_directories(${PROJECT_NAME} PUBLIC ../../yaya_memory/lib/)
target_link_libraries(${PROJECT_NAME} yaya_memory)
