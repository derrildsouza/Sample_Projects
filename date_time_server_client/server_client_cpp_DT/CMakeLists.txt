cmake_minimum_required(VERSION 3.10)
project(ClientServerAppCPP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(test)
