cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME logger_test)
project(${PROJECT_NAME})

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME}
    main.c
    test.c
    test.h
    )

add_subdirectory(${CMAKE_SOURCE_DIR}/../../lib/ yaya_logger)

target_include_directories(${PROJECT_NAME} PUBLIC ../../lib/)
target_link_libraries(${PROJECT_NAME} yaya_logger)
