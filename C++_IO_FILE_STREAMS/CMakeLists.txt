#cmake
cmake_minimum_required(VERSION 3.5)
project(io_file_streams_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(file_write_read file_write_read.cpp)
add_executable(binary_random_access binary_random_access.cpp)
add_executable(string_streams string_streams.cpp)
# Add the 'include' directory so the compiler can find "json.hpp"
target_include_directories(file_write_read PUBLIC ${CMAKE_SOURCE_DIR}/include)