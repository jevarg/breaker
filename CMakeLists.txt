cmake_minimum_required(VERSION 3.10)

project(breaker)

find_library(SDL2 SDL2 REQUIRED)
find_library(SDL2_IMAGE SDL2_image REQUIRED)
find_library(SDL2_TTF SDL2_ttf REQUIRED)
find_library(SDL2_MIXER SDL2_mixer REQUIRED)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(breaker
    ${SRC_DIR}/main.c
    ${SRC_DIR}/window.c
    ${SRC_DIR}/utils.c
    ${SRC_DIR}/ui.c
    ${SRC_DIR}/input.c
    ${SRC_DIR}/game.c
    ${SRC_DIR}/bar.c
    ${SRC_DIR}/ball.c
    ${SRC_DIR}/map.c
    ${SRC_DIR}/collisions.c
    ${SRC_DIR}/brick.c
    ${SRC_DIR}/resource_manager.c
    ${SRC_DIR}/text.c
    ${SRC_DIR}/particle.c
    ${SRC_DIR}/particle_list.c
)

target_link_libraries(breaker
    ${SDL2}
    ${SDL2_IMAGE}
    ${SDL2_TTF}
    ${SDL2_MIXER}
)