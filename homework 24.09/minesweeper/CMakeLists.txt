cmake_minimum_required(VERSION 4.3)
project(minesweeper)

set(CMAKE_CXX_STANDARD 20)

add_executable(minesweeper main.cpp
        board.h
        board.cpp
        game.h
        game.cpp)
