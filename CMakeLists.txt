cmake_minimum_required(VERSION 3.26)
project(advent_of_code)

set(CMAKE_CXX_STANDARD 17)

include_directories(day1)

add_executable(advent_of_code
        day1/task1.h
        main.cpp
        day2/task2.h
        day3/task3.h
        day4/task4.h
        day5/task5.cpp
        day5/task5.h
)
