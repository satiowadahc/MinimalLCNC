cmake_minimum_required(VERSION 3.19)
project(MinimalLCNC)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(MinimalLCNC main.cpp)
target_link_libraries(MinimalLCNC ${CURSES_LIBRARIES})