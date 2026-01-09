cmake_minimum_required(VERSION 3.16)
project(shooting-sim-cpp)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(shooting-sim-cpp src/main.cpp)
target_link_libraries(shooting-sim-cpp sfml-graphics sfml-window sfml-system)
