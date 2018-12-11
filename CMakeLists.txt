cmake_minimum_required(VERSION 3.10)
project(mad_dead)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -Wextra -pedantic")
include(ClangTools.cmake)

find_package(SFML 2.5 COMPONENTS graphics system audio window REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/inc)
set(game_lib "game_lib")

set(GAME_SRC
    ${PROJECT_SOURCE_DIR}/src/bullet.cpp
    ${PROJECT_SOURCE_DIR}/src/game.cpp
    ${PROJECT_SOURCE_DIR}/src/hud.cpp
    ${PROJECT_SOURCE_DIR}/src/pickup.cpp
    ${PROJECT_SOURCE_DIR}/src/player.cpp
    ${PROJECT_SOURCE_DIR}/src/random.cpp
    ${PROJECT_SOURCE_DIR}/src/rectangle.cpp
    ${PROJECT_SOURCE_DIR}/src/screen.cpp
    ${PROJECT_SOURCE_DIR}/src/text_wrapper.cpp
    ${PROJECT_SOURCE_DIR}/src/texture_holder.cpp
    ${PROJECT_SOURCE_DIR}/src/utils.cpp
    ${PROJECT_SOURCE_DIR}/src/zombie.cpp
    ${PROJECT_SOURCE_DIR}/src/zombie_arena.cpp
)
 
add_library(${game_lib} ${GAME_SRC})
target_include_directories(${game_lib} PUBLIC inc)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${game_lib})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-audio sfml-window)

#Clang-tidy and clang-format
set(SRC
    ${PROJECT_SOURCE_DIR}/src/bullet.cpp
    ${PROJECT_SOURCE_DIR}/src/game.cpp
    ${PROJECT_SOURCE_DIR}/src/hud.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/pickup.cpp
    ${PROJECT_SOURCE_DIR}/src/player.cpp
    ${PROJECT_SOURCE_DIR}/src/random.cpp
    ${PROJECT_SOURCE_DIR}/src/rectangle.cpp
    ${PROJECT_SOURCE_DIR}/src/screen.cpp
    ${PROJECT_SOURCE_DIR}/src/text_wrapper.cpp
    ${PROJECT_SOURCE_DIR}/src/texture_holder.cpp
    ${PROJECT_SOURCE_DIR}/src/utils.cpp
    ${PROJECT_SOURCE_DIR}/src/zombie.cpp
    ${PROJECT_SOURCE_DIR}/src/zombie_arena.cpp
)
set(HDR
    ${PROJECT_SOURCE_DIR}/inc/bullet.h
    ${PROJECT_SOURCE_DIR}/inc/game.h
    ${PROJECT_SOURCE_DIR}/inc/hud.h
    ${PROJECT_SOURCE_DIR}/inc/pickup.h
    ${PROJECT_SOURCE_DIR}/inc/player.h
    ${PROJECT_SOURCE_DIR}/inc/random.h
    ${PROJECT_SOURCE_DIR}/inc/rectangle.h
    ${PROJECT_SOURCE_DIR}/inc/screen.h
    ${PROJECT_SOURCE_DIR}/inc/text_wrapper.h
    ${PROJECT_SOURCE_DIR}/inc/texture_holder.h
    ${PROJECT_SOURCE_DIR}/inc/utils.h
    ${PROJECT_SOURCE_DIR}/inc/zombie.h
    ${PROJECT_SOURCE_DIR}/inc/zombie_arena.h
) 
add_clang_tool_targets(${PROJECT_NAME} ${SRC} ${HDR})

