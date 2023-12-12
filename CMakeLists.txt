cmake_minimum_required(VERSION 3.26)
project(KingDonkey)

set(CMAKE_CXX_STANDARD 17)

include_directories(./sdl/include)
link_directories(./sdl/lib)

add_executable(KingDonkey src/main.cpp)

find_package(SDL2)

target_link_libraries(KingDonkey SDL2::SDL2)
