cmake_minimum_required(VERSION 3.16)
project(MyStaticLib VERSION 1.0 LANGUAGES CXX)

include(FetchContent)

# -------------------------------------------------
# Library
# -------------------------------------------------
add_library(MyStaticLib STATIC
    src/math_utils.cpp
)

target_include_directories(MyStaticLib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(MyStaticLib PUBLIC cxx_std_17)

# -------------------------------------------------
# GoogleTest (download automatically)
# -------------------------------------------------
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# -------------------------------------------------
# Test executable
# -------------------------------------------------
add_executable(MyStaticLibTests
    tests/math_tests.cpp
)

target_link_libraries(MyStaticLibTests
    PRIVATE
        MyStaticLib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MyStaticLibTests)