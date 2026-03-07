cmake_minimum_required(VERSION 3.16)
project(Containers VERSION 1.0 LANGUAGES CXX)

include(FetchContent)

# -------------------------------------------------
# Library
# -------------------------------------------------
add_library(Containers STATIC
    src/BinTree.cpp
    src/CyclicArray.cpp
    src/Heap.cpp
    src/MxCifQuadTree.cpp
)

target_include_directories(Containers
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(Containers PUBLIC cxx_std_17)

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
add_executable(ContainersTests
    tests/math_tests.cpp
)

target_link_libraries(ContainersTests
    PRIVATE
        Containers
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ContainersTests)