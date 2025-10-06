#```cmake
cmake_minimum_required(VERSION 3.5)
project(cpp14_app)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main_app main.cpp)
add_executable(task_manager_app taskManager.cpp)
