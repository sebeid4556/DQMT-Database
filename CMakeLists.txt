cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_STANDARD 17)

project(main)

set(SDL2_INCLUDE_DIR C:/sdl2/include)

include_directories(C:/sdl2/include)
include_directories(source)
file(GLOB_RECURSE SRC_FILES
    source/*.h
    source/*.cpp
    ${SDL2_INCLUDE_DIR}/*.h
)

link_directories(C:/sdl2/lib)

add_executable(main ${SRC_FILES})

target_link_libraries(main SDL2 SDL2main SDL2_image SDL2_ttf)
