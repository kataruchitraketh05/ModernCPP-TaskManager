#cmake
cmake_minimum_required(VERSION 3.5)
project(smart_pointers_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(bank_account bank_account_class.cpp)