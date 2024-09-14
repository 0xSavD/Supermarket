cmake_minimum_required(VERSION 3.27)
project(SupermarketExercise)


set(CMAKE_CXX_STANDARD 17)

add_executable(SupermarketExercise main.cpp
        src/pos.cpp
        inc/pos.h)
target_include_directories(SupermarketExercise PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
