project(tests VERSION 1.0 LANGUAGES CXX)

find_package(Boost CONFIG REQUIRED COMPONENTS unit_test_framework)

set(SOURCES
    src/calculator_tests.cpp
    src/main.cpp
)

add_executable(tests ${SOURCES})
target_include_directories(calculator
    PRIVATE ${CMAKE_SOURCE_DIR}/calculator/include/detail
)

target_link_libraries(tests PRIVATE calculator Boost::unit_test_framework)

target_compile_definitions(tests PRIVATE BOOST_TEST_DYN_LINK)

add_test(NAME calculator_tests COMMAND tests)