cmake_minimum_required(VERSION 2.8) # Set the minimum version of CMake required

project(pipeline) # Name your project as "pipeline"

# Set C++ standard/compiler options directly, optional but recommended for portability
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++20")


# Glob all files matching the given wildcard expressions into a variable
file(GLOB SOURCES "*.cpp")

# Add an executable to the project using the specified source files
add_executable(pipeline ${SOURCES})

