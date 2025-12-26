cmake_minimum_required(VERSION 3.16)
project(thread_bot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(thread_bot src/main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(thread_bot Threads::Threads)