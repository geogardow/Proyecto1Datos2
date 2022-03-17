cmake_minimum_required(VERSION 3.21)
project(Proyecto1Datos2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Proyecto1Datos2
        main.cpp
        memory.cpp
        memory.h)
