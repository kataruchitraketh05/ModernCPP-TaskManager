#cmake
cmake_minimum_required(VERSION 3.5)
project(smart_pointers_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(unique_pointers unique_ptrs.cpp)
add_executable(circular_reference_problem circular_reference_problem.cpp)

