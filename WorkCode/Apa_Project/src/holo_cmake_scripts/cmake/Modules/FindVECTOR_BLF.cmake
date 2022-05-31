# - Try to find vector_blf lib
#
# Once done this will define
#
#  VECTOR_BLF_FOUND - system has vector_blf lib with correct version
#  VECTOR_BLF_INCLUDE_DIRS - the vector_blf include directory
#  VECTOR_BLF_LIBRARIES - the vector_blf library

find_path(VECTOR_BLF_INCLUDE_DIR "Vector/BLF.h")
find_library(VECTOR_BLF_LIBRARY Vector_BLF)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(VECTOR_BLF REQUIRED_VARS VECTOR_BLF_LIBRARY VECTOR_BLF_INCLUDE_DIR)

mark_as_advanced(VECTOR_BLF_LIBRARY VECTOR_BLF_INCLUDE_DIR)

set(VECTOR_BLF_INCLUDE_DIRS ${VECTOR_BLF_INCLUDE_DIR})
set(VECTOR_BLF_LIBRARIES ${VECTOR_BLF_LIBRARY})

if(VECTOR_BLF_FOUND)
    if(NOT TARGET VECTOR_BLF::vector_blf)
        add_library(VECTOR_BLF::vector_blf UNKNOWN IMPORTED)
        if(VECTOR_BLF_INCLUDE_DIR)
            set_target_properties(VECTOR_BLF::vector_blf PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${VECTOR_BLF_INCLUDE_DIR})
        endif()
        if(VECTOR_BLF_LIBRARY)
            set_target_properties(VECTOR_BLF::vector_blf PROPERTIES
                IMPORTED_LOCATION ${VECTOR_BLF_LIBRARY})
        endif()
    endif()
endif()

