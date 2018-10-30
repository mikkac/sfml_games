cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
project(Timber)

find_package(SFML 2.5 COMPONENTS graphics system audio window REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/inc)
set(SOURCES src/Timber.cpp) 

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-audio sfml-window)

