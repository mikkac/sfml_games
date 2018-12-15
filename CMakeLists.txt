cmake_minimum_required(VERSION 3.10)
project(bob_was_alone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -Wextra -pedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(ClangTools.cmake)

find_package(SFML 2.5 COMPONENTS graphics system audio window REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/inc)
set(game_lib "game_lib")

set(GAME_SRC
   ${PROJECT_SOURCE_DIR}/src/random.cpp
)
 
add_library(${game_lib} ${GAME_SRC})
target_include_directories(${game_lib} PUBLIC inc)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${game_lib})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-audio sfml-window)

#Clang-tidy and clang-format
set(SRC
    ${PROJECT_SOURCE_DIR}/src/random.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)
set(HDR
    ${PROJECT_SOURCE_DIR}/inc/random.h
) 
add_clang_tool_targets(${PROJECT_NAME} ${SRC} ${HDR})

