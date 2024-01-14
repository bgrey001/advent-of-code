cmake_minimum_required(VERSION 3.26)
project(advent_of_code)

set(CMAKE_CXX_STANDARD 14)

include_directories(day1)

add_executable(advent_of_code
        day1/task1.h
        main.cpp
        day2/task2.h
        day3/task3.h)
