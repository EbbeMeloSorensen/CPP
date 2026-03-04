cmake_minimum_required(VERSION 3.16)

project(MyConsoleApp1 LANGUAGES CXX)

add_executable(MyConsoleApp1
    src/main.cpp
)

target_compile_features(MyConsoleApp1 PRIVATE cxx_std_17)