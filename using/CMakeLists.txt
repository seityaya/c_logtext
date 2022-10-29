cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME logger_using)
project(${PROJECT_NAME})

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME}
    logger.h
    main.c
    )

target_include_directories(${PROJECT_NAME} PUBLIC ../lib/)
add_subdirectory(${CMAKE_SOURCE_DIR}/../lib/ yaya_logger)
target_link_libraries(${PROJECT_NAME} yaya_logger)
