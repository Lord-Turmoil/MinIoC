cmake_minimum_required(VERSION 3.26)
project(MIoC)

set(CMAKE_CXX_STANDARD 11)

# Add all source files
file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS src/*.cpp)

# Add final target.
add_executable(${CMAKE_PROJECT_NAME} ${SRC_LIST})

# Set include directories.
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC mioc/include)
