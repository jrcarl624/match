cmake_minimum_required(VERSION 3.27)
project(Match)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp") # Shouldnt be doing this but kys

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_executable(Match ${SOURCES} ${HEADERS} "src/fish.cpp")


