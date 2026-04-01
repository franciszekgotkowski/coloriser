cmake_minimum_required(VERSION 4.1)
project(coloriser)

add_executable(coloriser)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CONFIGURATION_TYPES
        Debug
        Release
)
set(CMAKE_BUILD_TYPE Debug)

target_compile_options(coloriser PRIVATE
        -fno-exceptions
        -fno-rtti
        -Wextra
        -Wall
        -Werror
)

target_compile_options(coloriser PRIVATE
        $<$<CONFIG:Debug>:-g -O0 -pg>
        $<$<CONFIG:Release>:-O3 -Wno-unused-but-set-variable -Wno-unused-variable>
)

target_sources(coloriser PRIVATE
        src/main.cpp
        src/Pane.cpp
        src/Window.cpp
)

target_include_directories(coloriser
        SYSTEM PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/headers
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries( coloriser PRIVATE
        raylib
)

add_subdirectory(libs/raylib)