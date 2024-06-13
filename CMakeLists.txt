cmake_minimum_required(VERSION 3.28)
project(LFyAProject)

set(CMAKE_CXX_STANDARD 26)

add_executable(LFyAProject main.cpp
        Estado.cpp
        Estado.h
        Automata.cpp
        Automata.h
        Conversion.cpp
        Conversion.h
)
