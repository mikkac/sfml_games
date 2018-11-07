cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
project(Timber)

find_package(SFML 2.5 COMPONENTS graphics system audio window REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/inc)
set(game_lib "game_lib")
set(LIB_SRC
    ./src/game.cpp
    ./src/drawing.cpp
) 
set(LIB_INC
    ./inc/game.h
    ./inc/drawing.h
) 
add_library(${game_lib} ${LIB_SRC} ${LIB_INC})
target_include_directories(${game_lib} PUBLIC inc)


add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${game_lib})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-audio sfml-window)

