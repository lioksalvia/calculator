project(calculator VERSION 1.0 LANGUAGES CXX)

set(HEADERS
        include/api.hpp
        include/calculator.hpp
        include/calculator_error.hpp
        include/export.hpp
)

set(DETAIL_HEADERS
        include/detail/vector.hpp
        include/detail/vector.tpp
)

set(SOURCES
        src/calculator.cpp
        src/calculator_error.cpp
        src/vector.cpp
)

add_library(calculator SHARED ${SOURCES})

target_compile_definitions(calculator PRIVATE CALCULATOR_EXPORTS)

target_include_directories(calculator
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/detail
)