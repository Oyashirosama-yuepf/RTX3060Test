# - Try to find polyclipping lib
#
# Once done this will define
#
#  POLYCLIPPING_FOUND - system has polyclipping lib with correct version
#  POLYCLIPPING_INCLUDE_DIRS - the polyclipping include directory
#  POLYCLIPPING_LIBRARIES - the polyclipping library

find_path(POLYCLIPPING_INCLUDE_DIR "polyclipping/clipper.hpp")
find_library(POLYCLIPPING_LIBRARY polyclipping)

if(POLYCLIPPING_INCLUDE_DIR)
    file(READ ${POLYCLIPPING_INCLUDE_DIR}/polyclipping/clipper.hpp POLYCLIPPING_VERSION_STRING)
    string(REGEX MATCH "#define CLIPPER_VERSION *\".*([0-9]+).([0-9]+).([0-9]+)\"" _ ${POLYCLIPPING_VERSION_STRING})
    set(POLYCLIPPING_VERSION_MAJOR ${CMAKE_MATCH_1})
    set(POLYCLIPPING_VERSION_MINOR ${CMAKE_MATCH_2})
    set(POLYCLIPPING_VERSION_PATCH ${CMAKE_MATCH_3})
    set(POLYCLIPPING_VERSION ${POLYCLIPPING_VERSION_MAJOR}.${POLYCLIPPING_VERSION_MINOR}.${POLYCLIPPING_VERSION_PATCH})
endif(POLYCLIPPING_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(POLYCLIPPING REQUIRED_VARS POLYCLIPPING_LIBRARY POLYCLIPPING_INCLUDE_DIR VERSION_VAR POLYCLIPPING_VERSION)

mark_as_advanced(POLYCLIPPING_LIBRARY POLYCLIPPING_INCLUDE_DIR)

set(POLYCLIPPING_INCLUDE_DIRS ${POLYCLIPPING_INCLUDE_DIR})
set(POLYCLIPPING_LIBRARIES ${POLYCLIPPING_LIBRARY})

if (POLYCLIPPING_FOUND)
    if (NOT TARGET POLYCLIPPING::polyclipping)
        add_library(POLYCLIPPING::polyclipping UNKNOWN IMPORTED)
        set_target_properties(POLYCLIPPING::polyclipping PROPERTIES
            IMPORTED_LOCATION "${POLYCLIPPING_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${POLYCLIPPING_INCLUDE_DIR}")
    endif ()
endif ()

