# - Try to find chealpix lib
#
# Once done this will define
#
#  HEALPIX_FOUND - system has chealpix lib with correct version
#  CHEALPIX_INCLUDE_DIRS - the chealpix include directory
#  CHEALPIX_LIBRARIES - the chealpix library

find_path(CHEALPIX_INCLUDE_DIR "chealpix.h" PATH_SUFFIXES chealpix)
find_library(CHEALPIX_LIBRARY libchealpix.so)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(HEALPIX REQUIRED_VARS CHEALPIX_LIBRARY CHEALPIX_INCLUDE_DIR)

mark_as_advanced(CHEALPIX_LIBRARY CHEALPIX_INCLUDE_DIR)

set(CHEALPIX_INCLUDE_DIRS ${CHEALPIX_INCLUDE_DIR})
set(CHEALPIX_LIBRARIES ${CHEALPIX_LIBRARY})

if(HEALPIX_FOUND)
    if(NOT TARGET HEALPIX::chealpix)
        add_library(HEALPIX::chealpix UNKNOWN IMPORTED)
        set_target_properties(HEALPIX::chealpix PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${CHEALPIX_INCLUDE_DIR}"
            IMPORTED_LOCATION "${CHEALPIX_LIBRARY}"
        )
    endif()
endif()

