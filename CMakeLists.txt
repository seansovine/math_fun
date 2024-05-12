cmake_minimum_required(VERSION 3.21)

# How do we want to name our targets? ~Camel case for now.
project(MathFunPrograms
        VERSION 0.1.0
        DESCRIPTION "A collection of mathematically-oriented programs written for fun."
        LANGUAGES CXX)

add_subdirectory(set_game_solver)
