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
   ${PROJECT_SOURCE_DIR}/src/collision_detection.cpp
   ${PROJECT_SOURCE_DIR}/src/engine.cpp
   ${PROJECT_SOURCE_DIR}/src/hud.cpp
   ${PROJECT_SOURCE_DIR}/src/level_manager.cpp
   ${PROJECT_SOURCE_DIR}/src/particle.cpp
   ${PROJECT_SOURCE_DIR}/src/particle_system.cpp
   ${PROJECT_SOURCE_DIR}/src/playable_character.cpp
   ${PROJECT_SOURCE_DIR}/src/random.cpp
   ${PROJECT_SOURCE_DIR}/src/sound_manager.cpp
   ${PROJECT_SOURCE_DIR}/src/text_wrapper.cpp
   ${PROJECT_SOURCE_DIR}/src/texture_holder.cpp
)
 
add_library(${game_lib} ${GAME_SRC})
target_include_directories(${game_lib} PUBLIC inc)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${game_lib})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-audio sfml-window)

#Clang-tidy and clang-format
set(SRC
    ${PROJECT_SOURCE_DIR}/src/collision_detection.cpp
    ${PROJECT_SOURCE_DIR}/src/engine.cpp
    ${PROJECT_SOURCE_DIR}/src/hud.cpp
    ${PROJECT_SOURCE_DIR}/src/level_manager.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/particle.cpp
    ${PROJECT_SOURCE_DIR}/src/particle_system.cpp
    ${PROJECT_SOURCE_DIR}/src/playable_character.cpp
    ${PROJECT_SOURCE_DIR}/src/random.cpp
    ${PROJECT_SOURCE_DIR}/src/sound_manager.cpp
    ${PROJECT_SOURCE_DIR}/src/text_wrapper.cpp
    ${PROJECT_SOURCE_DIR}/src/texture_holder.cpp
)
set(HDR
    ${PROJECT_SOURCE_DIR}/inc/collision_detection.h
    ${PROJECT_SOURCE_DIR}/inc/engine.h
    ${PROJECT_SOURCE_DIR}/inc/hud.h
    ${PROJECT_SOURCE_DIR}/inc/level_manager.h
    ${PROJECT_SOURCE_DIR}/inc/particle.h
    ${PROJECT_SOURCE_DIR}/inc/particle_system.h
    ${PROJECT_SOURCE_DIR}/inc/playable_character.h
    ${PROJECT_SOURCE_DIR}/inc/random.h
    ${PROJECT_SOURCE_DIR}/inc/sound_manager.cpp
    ${PROJECT_SOURCE_DIR}/inc/text_wrapper.h
    ${PROJECT_SOURCE_DIR}/inc/texture_holder.h
    ${PROJECT_SOURCE_DIR}/inc/utils.h
) 
add_clang_tool_targets(${PROJECT_NAME} ${SRC} ${HDR})

