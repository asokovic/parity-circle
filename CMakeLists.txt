cmake_minimum_required(VERSION 3.16)
project(parity_circle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(parity-circle
    src/main.cpp
    src/env.cpp
)