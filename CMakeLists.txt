cmake_minimum_required(VERSION 3.15)
project(CHIP8 C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Directories
set(ROOT_DIR "/home/angel_c/Projects/CHIP-8")
set(SRC_DIR "${ROOT_DIR}/src")
set(INCLUDE_DIR "${ROOT_DIR}/include")
set(BUILD_DIR "${ROOT_DIR}/build")
set(ROM "${ROOT_DIR}/assets/chip8-test-suite/bin/1-chip8-logo.ch8")

# Add include directories
include_directories(${INCLUDE_DIR})

# Find SDL3
find_package(SDL3 REQUIRED)

# Collect source files
set(SOURCES
    ${SRC_DIR}/chip8.c
    ${SRC_DIR}/display.c
    ${SRC_DIR}/input.c
    ${SRC_DIR}/main.c
    ${SRC_DIR}/timer.c
)

# Add executable
add_executable(chip8 ${SOURCES})

# Link SDL3
target_link_libraries(chip8 PRIVATE SDL3::SDL3)

# Optional: define a custom target to run your ROM
add_custom_target(run
    COMMAND chip8 ${ROM}
    DEPENDS chip8
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
