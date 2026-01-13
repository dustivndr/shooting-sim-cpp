cmake_minimum_required(VERSION 3.20)
project(shooting-sim-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows SFML path
if (WIN32)
    set(SFML_DIR "C:/SFML/lib/cmake/SFML")
elseif (UNIX)
    set(SFML_DIR "/usr/local/lib64/cmake/SFML")
endif()

set(SFML_STATIC_LIBRARIES ON)

find_package(SFML 3 CONFIG REQUIRED COMPONENTS Graphics Window System)

file(GLOB_RECURSE GAME_SOURCES
    src/*.cpp
)

add_executable(shooting-sim-cpp
    ${GAME_SOURCES}
)

target_link_libraries(shooting-sim-cpp PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# Assets
add_custom_command(TARGET shooting-sim-cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:shooting-sim-cpp>/assets
)
