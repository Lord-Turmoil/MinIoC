cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME "mioc")
set(BINARY_NAME "mioc")
set(CMAKE_CXX_STANDARD 11)

project(${PROJECT_NAME}
    VERSION 1.2.3
    DESCRIPTION "A mini IoC implementation with C++"
    LANGUAGES CXX)

set(LIBRARY_BASE_PATH "${PROJECT_SOURCE_DIR}")

include_directories("${LIBRARY_BASE_PATH}/include")
file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS "${LIBRARY_BASE_PATH}/src/*.cpp")
add_library(${BINARY_NAME} ${SRC_LIST})
target_include_directories(${BINARY_NAME} PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

install (
	TARGETS ${BINARY_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

enable_testing()
add_subdirectory(tests)