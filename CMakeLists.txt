cmake_minimum_required(VERSION 3.20)

project(Cybershoot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS
    system
    window
    graphics
    audio
    network
    REQUIRED
)

file(GLOB_RECURSE GAME_SOURCES
    src/*.cpp
)

add_executable(Cybershoot
    ${GAME_SOURCES}
)

target_link_libraries(Cybershoot
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
)

add_custom_command(TARGET Cybershoot POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Cybershoot>/assets
)
