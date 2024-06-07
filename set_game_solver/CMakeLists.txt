cmake_minimum_required(VERSION 3.21)

# Set required C++ version.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Note: The compiler to use is generally configured outside of CMake config files.
#  See: https://stackoverflow.com/questions/45933732/how-to-specify-a-compiler-in-cmake

project(SetGameSolver
        VERSION 0.1.0
        DESCRIPTION "A simple program to generate set hands and find all sets in them."
        LANGUAGES CXX)

set(library_src cards.cpp game.cpp output.cpp)
add_library(setGameSolver ${library_src})

add_executable(findSets find_sets.cpp)
target_link_libraries(findSets setGameSolver)
