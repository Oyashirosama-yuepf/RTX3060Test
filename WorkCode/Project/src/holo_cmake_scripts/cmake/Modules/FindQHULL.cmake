###############################################################################
# Find QHULL
#
# This sets the following variables:
# QHULL_FOUND - True if QHULL was found.
# QHULL_INCLUDE_DIRS - Directories containing the QHULL include files.
# QHULL_LIBRARIES - Libraries needed to use QHULL.
# QHULL_<C>_FOUND
# QHULL_<C>_LIBRARIES
# 
# qhullcpp
# qhull
# qhull_r
# qhull_p
# qhullstatic
# qhullstatic_r

find_path(QHULL_INCLUDE_DIR
    NAMES libqhull/libqhull.h)

if(QHULL_FIND_COMPONENTS)
    foreach(comp ${QHULL_FIND_COMPONENTS})
        find_library(QHULL_${comp}_LIBRARY NAMES ${comp})
        if(QHULL_${comp}_LIBRARY)
            set(QHULL_${comp}_FOUND 1)
            mark_as_advanced(QHULL_${comp}_LIBRARY)
            set(QHULL_${comp}_LIBRARIES ${QHULL_${comp}_LIBRARY})
            list(APPEND QHULL_LIBRARIES ${QHULL_${comp}_LIBRARY})
        endif()
    endforeach(comp)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Qhull REQUIRED_VARS QHULL_INCLUDE_DIR HANDLE_COMPONENTS)

mark_as_advanced(QHULL_INCLUDE_DIR)

set(QHULL_INCLUDE_DIRS ${QHULL_INCLUDE_DIR})

if(QHULL_FOUND)
    foreach(comp ${QHULL_FIND_COMPONENTS})
        if(QHULL_${comp}_FOUND)
            if(NOT TARGET QHULL::${comp})
                add_library(QHULL::${comp} UNKNOWN IMPORTED)
                set_target_properties(QHULL::${comp} PROPERTIES
                    INTERFACE_INCLUDE_DIRECTORIES ${QHULL_INCLUDE_DIR}
                    IMPORTED_LOCATION ${QHULL_${comp}_LIBRARY})
            endif()
        endif()
    endforeach()
endif(QHULL_FOUND)

