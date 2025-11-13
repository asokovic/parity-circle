cmake_minimum_required(VERSION 3.16)
project(parity_circle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(parity-circle
    src/main.cpp
    src/env.cpp
    src/api.cpp
    src/graph.cpp
    src/hamiltonian.cpp
)

target_link_libraries(parity-circle
    PRIVATE cpr::cpr
    PRIVATE nlohmann_json::nlohmann_json
)
