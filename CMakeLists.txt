cmake_minimum_required(VERSION 3.5)
project(yaya_logger VERSION 0.1 LANGUAGES C)
set (CMAKE_C_STANDARD 11)

include_directories(./../../yaya_library_collection_for_C/yaya_defines/)

set(SRC_LIST
    yaya_logger.c
    yaya_logger.h
    ./../yaya_defines/yaya_defines.h)

add_executable(${PROJECT_NAME} ${SRC_LIST})

add_definitions(-DYAYA_LOGGER)
