cmake_minimum_required(VERSION 3.10)
project(2dGame)

find_package(SDL2 REQUIRED)

add_executable(2d_shooter main.cpp)

target_link_libraries(2d_shooter SDL2::SDL2)



