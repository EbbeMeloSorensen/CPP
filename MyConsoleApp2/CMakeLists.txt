cmake_minimum_required(VERSION 3.16)

project(HelloWorld LANGUAGES CXX)

add_executable(HelloWorld
    src/main.cpp
)

target_compile_features(HelloWorld PRIVATE cxx_std_17)