project(demo VERSION 1.0 LANGUAGES CXX)

set(SOURCES
    src/main.cpp
)

add_executable(demo ${SOURCES})

target_link_libraries(demo PRIVATE calculator)