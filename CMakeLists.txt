cmake_minimum_required(VERSION 3.26)
project(BcpProjectTemplate)

set(CMAKE_CXX_STANDARD 17)

include_directories(./sdl/include)
link_directories(./sdl/lib)

add_executable(BcpProjectTemplate src/main.cpp)

find_package(SDL2)

target_link_libraries(BcpProjectTemplate SDL2::SDL2)
