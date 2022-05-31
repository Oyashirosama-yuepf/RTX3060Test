# - Try to find adolc lib
#
# Once done this will define
#
#  ADOLC_FOUND - system has adolc lib with correct version
#  ADOLC_INCLUDE_DIRS - the adolc include directory
#  ADOLC_LIBRARIES - the adolc library

find_path(ADOLC_INCLUDE_DIR "adolc/adolc.h")
find_library(ADOLC_LIBRARY adolc)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(ADOLC REQUIRED_VARS ADOLC_LIBRARY ADOLC_INCLUDE_DIR)

mark_as_advanced(ADOLC_LIBRARY ADOLC_INCLUDE_DIR)

set(ADOLC_INCLUDE_DIRS ${ADOLC_INCLUDE_DIR})
set(ADOLC_LIBRARIES ${ADOLC_LIBRARY})

if(ADOLC_FOUND)
    if(NOT TARGET ADOLC::adolc)
        add_library(ADOLC::adolc UNKNOWN IMPORTED)
        if(ADOLC_INCLUDE_DIR)
            set_target_properties(ADOLC::adolc PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${ADOLC_INCLUDE_DIR})
        endif()
        if(ADOLC_LIBRARY)
            set_target_properties(ADOLC::adolc PROPERTIES
                IMPORTED_LOCATION ${ADOLC_LIBRARY})
        endif()
    endif()
endif()

