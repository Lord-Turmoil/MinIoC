# Copyright (C) 2018 - 2023 Tony's Studio. All rights reserved.
# CMakeLists for MinIoc.

# Add all source files
file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS src/*.cpp)

# Add source to this project's executable.
add_library(mioc STATIC ${SRC_LIST} "src/ServiceContainer.cpp")

target_include_directories(mioc PUBLIC include)
