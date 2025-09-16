#cmake
cmake_minimum_required(VERSION 3.5)
project(task_manager_app)
# Add this line to find the correct thread library
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(simple_task_manager simple_task_manager.cpp)
add_executable(task_manager_thread_mutex task_manager_thread_with_mutex.cpp)
add_executable(task_manager_thread_pro_con task_manager_thread_producer_consumer_model.cpp)
add_executable(task_manager_simple_thread_pool_1 task_manager_with_simple_thread_pool_1.cpp)
add_executable(task_manager_simple_thread_pool_2 task_manager_with_simple_thread_pool_2.cpp)
# Now, link your executable to the thread library
# Needed to link thread libraries
target_link_libraries(task_manager_thread_mutex PRIVATE Threads::Threads)
target_link_libraries(task_manager_thread_pro_con PRIVATE Threads::Threads)
target_link_libraries(task_manager_simple_thread_pool_1 PRIVATE Threads::Threads)
target_link_libraries(task_manager_simple_thread_pool_2 PRIVATE Threads::Threads)