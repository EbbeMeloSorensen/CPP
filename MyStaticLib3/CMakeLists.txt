cmake_minimum_required(VERSION 3.16)
project(MyStaticLib3 VERSION 1.0 LANGUAGES CXX)

include(FetchContent)

# -------------------------------------------------
# Library
# -------------------------------------------------
add_library(MyStaticLib3 STATIC
    src/Heap.cpp
    src/Calculator.cpp
)

target_include_directories(MyStaticLib3
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(MyStaticLib3 PUBLIC cxx_std_17)

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
        MyStaticLib3
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MyStaticLibTests)