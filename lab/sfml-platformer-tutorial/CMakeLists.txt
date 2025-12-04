cmake_minimum_required(VERSION 3.20)
project(sfml_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML paths
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML")
set(SFML_INCLUDE_DIR "${SFML_DIR}/include")
set(SFML_LIB_DIR "${SFML_DIR}/lib")

# Include directories
include_directories(${SFML_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

# This is just for IntelliSense - we're not actually building with CMake
