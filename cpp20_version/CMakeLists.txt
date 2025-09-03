#```cmake
cmake_minimum_required(VERSION 3.5)
project(cpp20_app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(app main.cpp)
