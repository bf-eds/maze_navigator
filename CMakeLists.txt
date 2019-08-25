cmake_minimum_required(VERSION 3.14)

project(maze)
set(CMAKE_CXX_STANDARD 17)

add_library(maze SHARED maze.cpp maze_navigator.h)
target_include_directories(maze PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
add_executable(maze_demo maze_demo.cpp)

include(GenerateExportHeader)
generate_export_header(maze)
target_link_libraries(maze_demo maze)
