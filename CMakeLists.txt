cmake_minimum_required(VERSION 3.10)
project(Timber)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -Wextra -pedantic")
include(ClangTools.cmake)

find_package(SFML 2.5 COMPONENTS graphics system audio window REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/inc)
set(game_lib "game_lib")
set(LIB_SRC
    ${PROJECT_SOURCE_DIR}/src/game.cpp
    ${PROJECT_SOURCE_DIR}/src/drawing.cpp
) 
set(LIB_INC
    ${PROJECT_SOURCE_DIR}/inc/game.h
    ${PROJECT_SOURCE_DIR}/inc/drawing.h
) 
add_library(${game_lib} ${LIB_SRC} ${LIB_INC})
target_include_directories(${game_lib} PUBLIC inc)


add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${game_lib})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-audio sfml-window)

add_clang_tool_targets(${PROJECT_NAME} ${LIB_SRC} ${LIB_HDR})

