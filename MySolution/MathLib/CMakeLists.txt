add_library(MathLib STATIC)

target_sources(MathLib
    PRIVATE
        src/Calculator.cpp
)

target_include_directories(MathLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)