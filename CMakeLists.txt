# ====================================================================
# Top-level CMakeLists.txt file for Mini IoC
# ====================================================================

cmake_minimum_required(VERSION 3.16)

include(cmake/utils.cmake)

# --------------------------------------------------------------------
# Project configuration
# --------------------------------------------------------------------

mioc_extract_version()

project(mioc
    VERSION ${MIOC_VERSION}
    DESCRIPTION "A mini IoC implementation with C++"
    LANGUAGES CXX)

option(MIOC_BUILD_TEST "Build unit tests" OFF)

# --------------------------------------------------------------------
# Project options
# --------------------------------------------------------------------

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

if(NOT DEFINED MIOC_MASTER_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(MIOC_MASTER_PROJECT ON)
        message(STATUS "${PROJECT_NAME} is build as the master project")
    else()
        set(MIOC_MASTER_PROJECT OFF)
        message(STATUS "${PROJECT_NAME} is build as a sub-project")
    endif()
endif()

# --------------------------------------------------------------------
# Global compiler settings
# --------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)

# --------------------------------------------------------------------
# Targets
# --------------------------------------------------------------------

set(TARGET_NAME ${PROJECT_NAME})

add_library(${TARGET_NAME} INTERFACE)
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

if (MIOC_MASTER_PROJECT)
    set(MIOC_LIB ${TARGET_NAME})
else()
    set(MIOC_LIB ${TARGET_NAME} PARENT_SCOPE)
endif()

if(MIOC_BUILD_TEST OR MIOC_MASTER_PROJECT)
    enable_testing()
    add_subdirectory(tests)
else()
    message(STATUS "Skipping ${PROJECT_NAME} unit tests")
endif()
