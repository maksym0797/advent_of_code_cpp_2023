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
        day_three/day_three.h
        day_four/day_four.cpp
        day_four/day_four.h
        day_five/day_five.cpp
        day_five/day_five.h
        day_six/day_six.cpp
        day_six/day_six.h
        day_seven/day_seven.cpp
        day_seven/day_seven.h
)
