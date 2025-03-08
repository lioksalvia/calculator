project(calculator.demo VERSION 1.0 LANGUAGES CXX)

set(SOURCES
    src/main.cpp
)

add_executable(calculator.demo ${SOURCES})

target_link_libraries(calculator.demo PRIVATE calculator)

target_include_directories(calculator.demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../calculator/include)