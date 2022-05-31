# - Try to find flann lib
#
# Once done this will define
#
#  FLANN_FOUND - system has flann lib with correct version
#  FLANN_INCLUDE_DIRS - the flann include directory
#  FLANN_LIBRARIES - the flann library

find_path(FLANN_INCLUDE_DIR "flann/flann.h")
find_library(FLANN_LIBRARY flann_cpp)

if(FLANN_INCLUDE_DIR)
    file(READ ${FLANN_INCLUDE_DIR}/flann/config.h FLANN_VERSION_STRING)
    string(REGEX MATCH "#define FLANN_VERSION_ *\".*([0-9]+).([0-9]+).([0-9]+)\"" _ ${FLANN_VERSION_STRING})
    set(FLANN_VERSION_MAJOR ${CMAKE_MATCH_1})
    set(FLANN_VERSION_MINOR ${CMAKE_MATCH_2})
    set(FLANN_VERSION_PATCH ${CMAKE_MATCH_3})
    set(FLANN_VERSION ${FLANN_VERSION_MAJOR}.${FLANN_VERSION_MINOR}.${FLANN_VERSION_PATCH})
endif(FLANN_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(FLANN REQUIRED_VARS FLANN_LIBRARY FLANN_INCLUDE_DIR VERSION_VAR FLANN_VERSION)

mark_as_advanced(FLANN_LIBRARY FLANN_INCLUDE_DIR)

set(FLANN_INCLUDE_DIRS ${FLANN_INCLUDE_DIR})
set(FLANN_LIBRARIES ${FLANN_LIBRARY})

if(FLANN_FOUND)
    if(NOT TARGET FLANN::flann)
        add_library(FLANN::flann UNKNOWN IMPORTED)
        if(FLANN_INCLUDE_DIR)
            set_target_properties(FLANN::flann PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${FLANN_INCLUDE_DIR})
        endif()
        if(FLANN_LIBRARY)
            set_target_properties(FLANN::flann PROPERTIES
                IMPORTED_LOCATION ${FLANN_LIBRARY})
        endif()
    endif()
endif()

