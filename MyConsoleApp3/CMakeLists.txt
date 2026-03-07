cmake_minimum_required(VERSION 3.16)

project(MyConsoleApp3 LANGUAGES CXX)

add_executable(MyConsoleApp3
    src/main.cpp
)

target_compile_features(MyConsoleApp3 PRIVATE cxx_std_17)