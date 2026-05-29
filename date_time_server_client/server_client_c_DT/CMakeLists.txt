cmake_minimum_required(VERSION 3.10)
project(ClientServerApp C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(test)
