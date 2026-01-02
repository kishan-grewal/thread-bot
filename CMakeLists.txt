cmake_minimum_required(VERSION 3.16)
project(thread_bot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(thread_bot
    src/main.cpp
    src/robot.cpp
    src/world.cpp
    src/worker.cpp
    src/reporter_worker.cpp
    src/world_worker.cpp
    # pulls in matching hpps, + types.hpp + shared_context.hpp
)

find_package(Threads REQUIRED)
target_link_libraries(thread_bot Threads::Threads)