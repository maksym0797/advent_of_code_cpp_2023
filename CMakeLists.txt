cmake_minimum_required(VERSION 3.26)
project(advent_of_code_2023_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(advent_of_code_2023_cpp main.cpp
        day_one/day_one.cpp
        day_one/day_one.hpp
        day_two/day_two.cpp
        day_two/day_two.h
        day_one/day_one.cpp
        day_three/day_three.cpp
        day_three/day_three.h)
