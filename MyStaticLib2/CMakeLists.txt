cmake_minimum_required(VERSION 3.16)

project(MyStaticLib VERSION 1.0 LANGUAGES CXX)

# Create static library
add_library(MyStaticLib STATIC
    src/math_utils.cpp
)

target_include_directories(MyStaticLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(MyStaticLib PUBLIC cxx_std_17)

# ✅ Test executable
add_executable(TestApp
    test/main.cpp
)

target_link_libraries(TestApp PRIVATE MyStaticLib)