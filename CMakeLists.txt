cmake_minimum_required(VERSION 3.10)

project(breaker)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(breaker
    ${SRC_DIR}/main.c
    ${SRC_DIR}/window.c
    ${SRC_DIR}/utils.c
    ${SRC_DIR}/ui.c
    ${SRC_DIR}/input.c
    ${SRC_DIR}/game.c
)

target_link_libraries(breaker ${SDL2_LIBRARIES})