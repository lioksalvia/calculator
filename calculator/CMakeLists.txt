project(calculator VERSION 1.0 LANGUAGES CXX)

set(HEADERS
    include/detail/number_t.hpp
    include/detail/value_t.hpp
    include/detail/vector.hpp
    include/detail/vector.tpp
    include/calculator.hpp
    include/calculator_api.hpp
    include/calculator_error.hpp
    include/export.hpp
)

set(SOURCES
    src/calculator.cpp
    src/calculator_error.cpp
    src/value_t.cpp
    src/vector.cpp
)

add_library(calculator SHARED ${SOURCES})
target_include_directories(calculator
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/detail
)

target_compile_definitions(calculator PRIVATE CALCULATOR_EXPORTS)