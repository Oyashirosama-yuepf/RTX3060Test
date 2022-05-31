# - Try to find VPTREE lib
#
# Once done this will define
#
#  VPTREE_FOUND - system has VPTREE lib with correct version
#  VPTREE_INCLUDE_DIRS - the VPTREE include directory
#  VPTREE_LIBRARIES - the VPTREE library

include(FindPackageHandleStandardArgs)

find_path(VPTREE_INCLUDE_DIR
          NAMES vptree/vptree.h
         )
find_library(VPTREE_LIBRARY
             NAMES vptree
            )

mark_as_advanced(VPTREE_INCLUDE_DIR VPTREE_LIBRARY)

set(VPTREE_INCLUDE_DIRS ${VPTREE_INCLUDE_DIR})
set(VPTREE_LIBRARIES ${VPTREE_LIBRARY})

find_package_handle_standard_args(VPTREE
    REQUIRED_VARS VPTREE_LIBRARIES VPTREE_INCLUDE_DIRS)

if (VPTREE_FOUND)
    if (NOT TARGET VPTREE::vptree)
        add_library(VPTREE::vptree UNKNOWN IMPORTED)
        set_target_properties(VPTREE::vptree PROPERTIES
            IMPORTED_LOCATION ${VPTREE_LIBRARY}
            INTERFACE_INCLUDE_DIRECTORIES ${VPTREE_INCLUDE_DIR})
    endif ()
endif ()

