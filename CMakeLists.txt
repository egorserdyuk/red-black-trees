cmake_minimum_required(VERSION 3.13)
project(red-black-trees)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(red-black-trees main.cpp)

target_link_libraries(red-black-trees ${CMAKE_EXE_LINKER_FLAGS})