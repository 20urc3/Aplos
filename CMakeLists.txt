cmake_minimum_required(VERSION 3.27)
project(Aplos)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Aplos
        include/CLI11.hpp
        src/Aplos.cpp
)
