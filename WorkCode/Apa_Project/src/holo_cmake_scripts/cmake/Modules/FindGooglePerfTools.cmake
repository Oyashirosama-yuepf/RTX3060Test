# - Try to find GooglePerfTools
# Once done this will define

#  GooglePerfTools_FOUND - System has GooglePerfTools
#  GooglePerfTools_INCLUDE_DIRS - The GooglePerfTools include directories
#  GooglePerfTools_VERSION - GooglePerfTools version
#
#  GooglePerfTools_<C>_FOUND - System has GooglePerfTools component <C>
#  GooglePerfTools_<C>_LIBRARIES - The libraries needed to use GooglePerfTools component <C>
#  GooglePerfTools_LIBRARIES
#
# Avaliable components:
#  profiler
#  tcmalloc
#  tcmalloc_and_profiler
#  tcmalloc_debug
#  tcmalloc_minimal
#  tcmalloc_minimal_debug

find_path(GooglePerfTools_INCLUDE_DIR gperftools/tcmalloc.h)
if (GooglePerfTools_FIND_COMPONENTS)
    foreach (comp ${GooglePerfTools_FIND_COMPONENTS})
        find_library(GooglePerfTools_${comp}_LIBRARY NAMES ${comp} lib${comp})
        if (GooglePerfTools_${comp}_LIBRARY)           
            set(GooglePerfTools_${comp}_FOUND 1)
            mark_as_advanced(GooglePerfTools_${comp}_LIBRARY)
            set(GooglePerfTools_${comp}_LIBRARIES ${GooglePerfTools_${comp}_LIBRARY})
            list(APPEND GooglePerfTools_LIBRARIES ${GooglePerfTools_${comp}_LIBRARY})
        endif ()
    endforeach ()
endif ()

if (EXISTS ${GooglePerfTools_INCLUDE_DIR}/gperftools/tcmalloc.h)
    # Read and parse version header file for version number
    file(READ ${GooglePerfTools_INCLUDE_DIR}/gperftools/tcmalloc.h _GooglePerfTools_HEADER_CONTENTS)
    STRING(REGEX MATCH "#define TC_VERSION_STRING \"gperftools ([0-9]+).([0-9]+)[.]?([0-9]?)\"" _ ${_GooglePerfTools_HEADER_CONTENTS})
    set(GooglePerfTools_VERSION_MAJOR ${CMAKE_MATCH_1})
    set(GooglePerfTools_VERSION_MINOR ${CMAKE_MATCH_2})
    set(GooglePerfTools_VERSION_PATCH ${CMAKE_MATCH_3})
    set(GooglePerfTools_VERSION ${GooglePerfTools_VERSION_MAJOR}.${GooglePerfTools_VERSION_MINOR}.${GooglePerfTools_VERSION_PATCH})
else ()
    set(GooglePerfTools_VERSION 0.0.0)
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GooglePerfTools
        REQUIRED_VARS GooglePerfTools_INCLUDE_DIR
        VERSION_VAR GooglePerfTools_VERSION
        HANDLE_COMPONENTS
        )

mark_as_advanced(GooglePerfTools_INCLUDE_DIR)

set(GooglePerfTools_INCLUDE_DIRS ${GooglePerfTools_INCLUDE_DIR})

if(GooglePerfTools_FOUND)
    if(NOT TARGET gperf::gperf)
        add_library(gperf::gperf INTERFACE IMPORTED)
        if(GooglePerfTools_INCLUDE_DIR)
            set_target_properties(gperf::gperf PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${GooglePerfTools_INCLUDE_DIR})
        endif(GooglePerfTools_INCLUDE_DIR)
        set(GooglePerfTools_LIBRARIES gperf::gperf)
    endif(NOT TARGET gperf::gperf)

    foreach(comp ${GooglePerfTools_FIND_COMPONENTS})
        if(NOT TARGET gperf::${comp})
            if(GooglePerfTools_${comp}_FOUND)
                add_library(gperf::${comp} UNKNOWN IMPORTED)
                if(GooglePerfTools_INCLUDE_DIR)
                    set_target_properties(gperf::${comp} PROPERTIES
                        INTERFACE_INCLUDE_DIRECTORIES ${GooglePerfTools_INCLUDE_DIR})
                endif()
                if(EXISTS "${GooglePerfTools_${comp}_LIBRARY}")
                    set_target_properties(gperf::${comp} PROPERTIES
                        IMPORTED_LOCATION "${GooglePerfTools_${comp}_LIBRARY}")
                endif()
            endif()
        endif()
    endforeach()
endif()
