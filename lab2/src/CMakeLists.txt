cmake_minimum_required(VERSION 3.26)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(GameOfLife
        src/main.cpp
        src/Cell.cpp
        src/ArgumentParser.cpp
        src/Universe.cpp
        src/LifeGame.cpp)