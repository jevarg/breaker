cmake_minimum_required(VERSION 3.10)

project(breaker)
find_library(SDL2_LIBRARY NAME SDL2 REQUIRED)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(breaker
    ${SRC_DIR}/main.c
    ${SRC_DIR}/window.c
    ${SRC_DIR}/utils.c
    ${SRC_DIR}/ui.c
    ${SRC_DIR}/input.c
    ${SRC_DIR}/game.c
    ${SRC_DIR}/bar.c
    # ${SRC_DIR}/ball.c
    # ${SRC_DIR}/brick.c
)

include_directories(breaker ${SDL2_INCLUDE_DIR})
target_link_libraries(breaker ${SDL2_LIBRARY})