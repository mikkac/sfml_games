cmake_minimum_required(VERSION 3.10)
project(Timber)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -Wextra -pedantic")
include(ClangTools.cmake)

find_package(SFML 2.5 COMPONENTS graphics system audio window REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/inc)
set(game_lib "game_lib")

set(GAME_SRC
    ${PROJECT_SOURCE_DIR}/src/game.cpp
    ${PROJECT_SOURCE_DIR}/src/drawing.cpp
    ${PROJECT_SOURCE_DIR}/src/random.cpp
    ${PROJECT_SOURCE_DIR}/src/utils.cpp
)
 

add_library(${game_lib} ${GAME_SRC})
target_include_directories(${game_lib} PUBLIC inc)


add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${game_lib})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-audio sfml-window)


#Clang-tidy and clang-format
set(SRC
    ${PROJECT_SOURCE_DIR}/src/drawing.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/game.cpp
    ${PROJECT_SOURCE_DIR}/src/random.cpp
)
set(HDR
    ${PROJECT_SOURCE_DIR}/src/drawing.h
    ${PROJECT_SOURCE_DIR}/src/game.h
    ${PROJECT_SOURCE_DIR}/src/random.h
    ${PROJECT_SOURCE_DIR}/src/utils.h
) 
add_clang_tool_targets(${PROJECT_NAME} ${SRC} ${HDR})

