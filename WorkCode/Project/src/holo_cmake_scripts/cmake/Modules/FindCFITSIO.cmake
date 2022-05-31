# - Try to find cfitsio lib
#
# Once done this will define
#
#  CFITSIO_FOUND - system has cfitsio lib with correct version
#  CFITSIO_INCLUDE_DIRS - the cfitsio include directory
#  CFITSIO_LIBRARIES - the cfitsio library

find_path(CFITSIO_INCLUDE_DIR "fitsio.h" PATH_SUFFIXES cfitsio)
find_library(CFITSIO_LIBRARY libcfitsio.so)

if(CFITSIO_INCLUDE_DIR)
    file(READ ${CFITSIO_INCLUDE_DIR}/fitsio.h CFITSIO_VERSION_STRING)
    string(REGEX MATCH "#define CFITSIO_VERSION *([0-9]+).([0-9]+)" _ ${CFITSIO_VERSION_STRING})
    set(CFITSIO_VERSION_MAJOR ${CMAKE_MATCH_1})
    set(CFITSIO_VERSION_MINOR ${CMAKE_MATCH_2})
    set(CFITSIO_VERSION ${CFITSIO_VERSION_MAJOR}.${CFITSIO_VERSION_MINOR})
endif(CFITSIO_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(CFITSIO REQUIRED_VARS CFITSIO_LIBRARY CFITSIO_INCLUDE_DIR VERSION_VAR CFITSIO_VERSION)

mark_as_advanced(CFITSIO_LIBRARY CFITSIO_INCLUDE_DIR)

set(CFITSIO_INCLUDE_DIRS ${CFITSIO_INCLUDE_DIR})
set(CFITSIO_LIBRARIES ${CFITSIO_LIBRARY})

if(CFITSIO_FOUND)
    if(NOT TARGET CFITSIO::cfitsio)
        add_library(CFITSIO::cfitsio UNKNOWN IMPORTED)
        if(CFITSIO_INCLUDE_DIR)
            set_target_properties(CFITSIO::cfitsio PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${CFITSIO_INCLUDE_DIR})
        endif()
        if(CFITSIO_LIBRARY)
            set_target_properties(CFITSIO::cfitsio PROPERTIES
                IMPORTED_LOCATION ${CFITSIO_LIBRARY})
        endif()
    endif()
endif()

