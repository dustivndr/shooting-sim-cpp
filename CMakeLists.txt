cmake_minimum_required(VERSION 3.16)
project(shooting-sim-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 REQUIRED
    COMPONENTS system window graphics)

add_executable(shooting-sim-cpp
    src/main.cpp
)

target_link_libraries(shooting-sim-cpp
    sfml-graphics
    sfml-window
    sfml-system
)

file(COPY ${CMAKE_SOURCE_DIR}/assets
     DESTINATION ${CMAKE_BINARY_DIR})
