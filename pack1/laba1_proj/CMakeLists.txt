cmake_minimum_required(VERSION 3.10)
project(laba1_proj C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    main.c
    src/funcs.c
)

add_executable(laba1 ${SOURCES})
