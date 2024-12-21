# Extract version
function(mioc_extract_version)
    file(READ "${CMAKE_CURRENT_LIST_DIR}/include/mioc/detail/Macros.h" file_contents)

    string(REGEX MATCH "MIOC_VERSION_MAJOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract major version number")
    endif()
    set(MAJOR_VERSION ${CMAKE_MATCH_1})

    string(REGEX MATCH "MIOC_VERSION_MINOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract minor version number")
    endif()
    set(MINOR_VERSION ${CMAKE_MATCH_1})
    
    string(REGEX MATCH "MIOC_VERSION_PATCH ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract patch version number")
    endif()
    set(PATCH_VERSION ${CMAKE_MATCH_1})

    set(MIOC_VERSION_MAJOR ${MAJOR_VERSION} PARENT_SCOPE)
    set(MIOC_VERSION_MINOR ${MINOR_VERSION} PARENT_SCOPE)
    set(MIOC_VERSION_PATCH ${PATCH_VERSION} PARENT_SCOPE)
    set(MIOC_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}" PARENT_SCOPE)
endfunction()
