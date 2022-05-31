# - Try to find blas lib
#
# Once done this will define
#
#  BLAS_FOUND - system has blas lib with correct version
#  BLAS_INCLUDE_DIRS - the blas include directory
#  BLAS_LIBRARIES - the blas library

find_path(BLAS_INCLUDE_DIR "coin")
find_library(BLAS_LIBRARY coinblas)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(BLAS REQUIRED_VARS BLAS_LIBRARY BLAS_INCLUDE_DIR)

mark_as_advanced(BLAS_LIBRARY BLAS_INCLUDE_DIR)

set(BLAS_INCLUDE_DIRS ${BLAS_INCLUDE_DIR})
set(BLAS_LIBRARIES ${BLAS_LIBRARY})

if(BLAS_FOUND)
    if(NOT TARGET BLAS::blas)
        add_library(BLAS::blas UNKNOWN IMPORTED)
        if(BLAS_INCLUDE_DIR)
            set_target_properties(BLAS::blas PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${BLAS_INCLUDE_DIR})
        endif()
        if(BLAS_LIBRARY)
            set_target_properties(BLAS::blas PROPERTIES
                IMPORTED_LOCATION ${BLAS_LIBRARY})
        endif()
    endif()
endif()

