cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(leetcode-solutions LANGUAGES C CXX)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(CMAKE_CXX_STANDARD 11)

option(SANITIZER "Enable address sanitizer" OFF)
if(SANITIZER)
add_definitions(-fsanitize=address)
endif(SANITIZER)

add_subdirectory(solutions)