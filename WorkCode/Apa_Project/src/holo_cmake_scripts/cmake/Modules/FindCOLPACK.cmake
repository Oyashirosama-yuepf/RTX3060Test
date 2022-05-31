# - Try to find ColPack lib
#
# Once done this will define
#
#  COLPACK_FOUND - system has ColPack lib with correct version
#  COLPACK_INCLUDE_DIRS - the ColPack include directory
#  COLPACK_LIBRARIES - the ColPack library

find_path(COLPACK_INCLUDE_DIR "ColPack/ColPackHeaders.h")
find_library(COLPACK_LIBRARY ColPack)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(COLPACK REQUIRED_VARS COLPACK_LIBRARY COLPACK_INCLUDE_DIR)

mark_as_advanced(COLPACK_LIBRARY COLPACK_INCLUDE_DIR)

set(COLPACK_INCLUDE_DIRS ${COLPACK_INCLUDE_DIR})
set(COLPACK_LIBRARIES ${COLPACK_LIBRARY})

if(COLPACK_FOUND)
    if(NOT TARGET COLPACK::ColPack)
        add_library(COLPACK::ColPack UNKNOWN IMPORTED)
        if(COLPACK_INCLUDE_DIR)
            set_target_properties(COLPACK::ColPack PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${COLPACK_INCLUDE_DIR})
        endif()
        if(COLPACK_LIBRARY)
            set_target_properties(COLPACK::ColPack PROPERTIES
                IMPORTED_LOCATION ${COLPACK_LIBRARY})
        endif()
    endif()
endif()

