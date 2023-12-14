cmake_minimum_required(VERSION 3.26)
project(BcpProjectTemplate)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_DIR ./sdl)
find_package(SDL2)

include_directories(sdl/include)
link_directories(sdl/lib)

add_executable(BcpProjectTemplate src/main.cpp)

target_link_libraries(BcpProjectTemplate SDL2::SDL2)

add_custom_command(TARGET BcpProjectTemplate POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/static ${CMAKE_CURRENT_BINARY_DIR}/static
)