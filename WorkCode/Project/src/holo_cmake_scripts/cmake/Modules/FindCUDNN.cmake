# - Try to find cudnn lib
#
# Once done this will define
#
#  CUDNN_FOUND - system has cudnn lib with correct version
#  CUDNN_INCLUDE_DIRS - the cudnn include directory
#  CUDNN_LIBRARIES - the cudnn library

find_path(CUDNN_INCLUDE_DIR "cudnn.h")
find_library(CUDNN_LIBRARY libcudnn.so PATH_SUFFIXES lib64)
find_library(CUDNN_STATIC_LIBRARY libcudnn_static.a PATH_SUFFIXES lib64)

if(CUDNN_INCLUDE_DIR)
    file(READ ${CUDNN_INCLUDE_DIR}/cudnn.h CUDNN_VERSION_STRING)
    string(REGEX MATCH "define CUDNN_MAJOR +([0-9]+)" _ ${CUDNN_VERSION_STRING})
    set(CUDNN_VERSION_MAJOR ${CMAKE_MATCH_1})
    string(REGEX MATCH "define CUDNN_MINOR +([0-9]+)" _ ${CUDNN_VERSION_STRING})
    set(CUDNN_VERSION_MINOR ${CMAKE_MATCH_1})
    string(REGEX MATCH "define CUDNN_PATCHLEVEL +([0-9]+)" _ ${CUDNN_VERSION_STRING})
    set(CUDNN_VERSION_PATCH ${CMAKE_MATCH_1})
    set(CUDNN_VERSION ${CUDNN_VERSION_MAJOR}.${CUDNN_VERSION_MINOR}.${CUDNN_VERSION_PATCH})
endif(CUDNN_INCLUDE_DIR)

if(NOT CUDNN_LIBRARY AND CUDNN_STATIC_LIBRARY)
    set(CUDNN_LIBRARY ${CUDNN_STATIC_LIBRARY})
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(CUDNN REQUIRED_VARS CUDNN_LIBRARY CUDNN_INCLUDE_DIR VERSION_VAR CUDNN_VERSION)

mark_as_advanced(CUDNN_LIBRARY CUDNN_STATIC_LIBRARY CUDNN_INCLUDE_DIR)

set(CUDNN_INCLUDE_DIRS ${CUDNN_INCLUDE_DIR})
set(CUDNN_LIBRARIES ${CUDNN_LIBRARY})

set(CUDNN_INCLUDE_PATH ${CUDNN_INCLUDE_DIR})
set(CUDNN_LIBRARY_PATH ${CUDNN_LIBRARY})

if(CUDNN_FOUND)
    if(NOT TARGET CUDNN::cudnn)
        add_library(CUDNN::cudnn UNKNOWN IMPORTED)
        set_target_properties(CUDNN::cudnn PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${CUDNN_INCLUDE_DIR}
            IMPORTED_LOCATION ${CUDNN_LIBRARY})
    endif()
endif()
