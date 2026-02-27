cmake_minimum_required(VERSION 3.16)

project(2dGame)
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(2d_shooter src/main.cpp)

target_link_libraries(2d_shooter 
    PRIVATE 
    SDL3::SDL3
    SDL3_image::SDL3_image

    

)
