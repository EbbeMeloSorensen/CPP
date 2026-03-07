cmake_minimum_required(VERSION 3.20)

project(MySolution LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(MyStaticLib3)
add_subdirectory(Containers)
add_subdirectory(MyConsoleApp2)
