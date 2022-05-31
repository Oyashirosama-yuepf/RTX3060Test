# - Try to find umb lib
#
# Once done this will define
#
#  UMB_FOUND - system has umb lib with correct version
#  UMB_INCLUDE_DIRS - the umb include directory
#  UMB_LIBRARIES - the umb library

find_path(UMB_INCLUDE_DIR "umb.h")
find_library(UMB_LIBRARY libumb.so)

if(NOT UMB_LIBRARY AND UMB_STATIC_LIBRARY)
    set(UMB_LIBRARY ${UMB_STATIC_LIBRARY})
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(UMB REQUIRED_VARS UMB_LIBRARY UMB_INCLUDE_DIR)

mark_as_advanced(UMB_LIBRARY UMB_STATIC_LIBRARY UMB_INCLUDE_DIR)

set(UMB_INCLUDE_DIRS ${UMB_INCLUDE_DIR})
set(UMB_LIBRARIES ${UMB_LIBRARY})

if(UMB_FOUND)
    if(NOT TARGET UMB::umb)
        add_library(UMB::umb UNKNOWN IMPORTED)
        set_target_properties(UMB::umb PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${UMB_INCLUDE_DIR}
            IMPORTED_LOCATION ${UMB_LIBRARY})
    endif()
endif()
