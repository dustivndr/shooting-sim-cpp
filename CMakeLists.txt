cmake_minimum_required(VERSION 3.16)
project(shooting-sim-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows SFML path
if (WIN32)
    set(SFML_DIR "C:/SFML/lib/cmake/SFML")
endif()

find_package(SFML 3 CONFIG REQUIRED COMPONENTS Graphics Window System)

add_executable(shooting-sim-cpp
    src/main.cpp
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

# Windows DLLs
if (WIN32)
    add_custom_command(TARGET shooting-sim-cpp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:shooting-sim-cpp>
            $<TARGET_FILE_DIR:shooting-sim-cpp>
        COMMAND_EXPAND_LISTS
    )
endif()
