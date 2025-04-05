cmake_minimum_required(VERSION 3.30)
project(Classes)

set(CMAKE_CXX_STANDARD 20)

add_executable(Classes main.cpp
        Crawler.h
        Crawler.cpp
        Board.cpp
        Board.h
        Cell.cpp
        Cell.h)
