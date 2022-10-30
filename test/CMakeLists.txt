#Author                 : Seityagiya Terlekchi
#Contacts               : seityaya@ukr.net
#Creation Date          : 2020.02
#License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
#SPDX-License-Identifier: LGPL-2.1-or-later
#Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME logger_test)
project(${PROJECT_NAME})

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME}
    main.c
    test.c
    test.h
    )

add_subdirectory(${CMAKE_SOURCE_DIR}/../lib/ yaya_logger)
target_include_directories(${PROJECT_NAME} PUBLIC ../lib/)
target_link_libraries(${PROJECT_NAME} yaya_logger)
