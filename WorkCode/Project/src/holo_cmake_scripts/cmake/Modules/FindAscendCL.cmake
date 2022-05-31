# - Try to find Huawei AscendCL package
#
# Once done this will define
#
#  AscendCL_FOUND - system has acl lib with correct version
#  AscendCL_INCLUDE_DIRS - the acl include directory
#  AscendCL_LIBRARIES - the acl library
#  AscendCL_${comp}_FOUND - acl component found
#  AscendCL_${comp}_LIBRARY - the acl component library
#
# The following targets will be defined
#
#  AscendCL::${component}
#  AscendCL::AscendCL
#
#

if (NOT AscendCL_FIND_COMPONENTS)
    set(AscendCL_FIND_COMPONENTS acl_cblas acl_dvpp acl_retr ascendcl)
endif()

find_path(AscendCL_INCLUDE_DIR "acl/acl.h")
set(AscendCL_REQUIRED_VARS AscendCL_INCLUDE_DIR)

foreach(lib ${AscendCL_FIND_COMPONENTS})
    find_library(AscendCL_${lib}_LIBRARY ${lib} PATH_SUFFIXES lib64/stub)
    list(APPEND AscendCL_REQUIRED_VARS AscendCL_${lib}_LIBRARY)
    message("AscendCL_${lib}_LIBRARY = ${AscendCL_${lib}_LIBRARY}")
    if(AscendCL_${lib}_LIBRARY)
        set(AscendCL_${lib}_FOUND 1)
        mark_as_advanced(AscendCL_${lib}_LIBRARY)
        list(APPEND AscendCL_LIBRARIES ${AscendCL_${lib}_LIBRARY})
    endif()
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    AscendCL
    REQUIRED_VARS
    ${AscendCL_REQUIRED_VARS}
    HANDLE_COMPONENTS
    )

if(AscendCL_FOUND)
    set(AscendCL_INCLUDE_DIRS ${AscendCL_INCLUDE_DIR})
    foreach(comp ${AscendCL_FIND_COMPONENTS})
        if(NOT TARGET AscendCL::${comp})
            add_library(AscendCL::${comp} UNKNOWN IMPORTED)
            set_target_properties(AscendCL::${comp} PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${AscendCL_INCLUDE_DIRS}"
                IMPORTED_LOCATION ${AscendCL_${comp}_LIBRARY}
                )
            list(APPEND acl_interface_libs AscendCL::${comp})
        endif()
    endforeach()
    if (NOT TARGET AscendCL::AscendCL)
        add_library(AscendCL::AscendCL INTERFACE IMPORTED)
        set_target_properties(AscendCL::AscendCL PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${AscendCL_INCLUDE_DIRS}"
            INTERFACE_LINK_LIBRARIES "${acl_interface_libs}"
            )
    endif()
endif()
