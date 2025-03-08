project(calculator VERSION 1.0 LANGUAGES CXX)

set(HEADERS
    include/calculator/api.hpp
    include/calculator/calculator.hpp
)

set(SOURCES
    src/calculator.cpp
)

add_library(calculator SHARED ${SOURCES})

target_compile_definitions(calculator PRIVATE CALCULATOR_EXPORTS)

target_include_directories(calculator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)