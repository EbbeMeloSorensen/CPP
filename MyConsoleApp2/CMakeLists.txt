cmake_minimum_required(VERSION 3.16)

project(MyConsoleApp2 LANGUAGES CXX)

add_executable(MyConsoleApp2
    src/main.cpp
)

target_link_libraries(MyConsoleApp2
    PRIVATE
        MyStaticLib3
) 

target_compile_features(MyConsoleApp2 PRIVATE cxx_std_17)



