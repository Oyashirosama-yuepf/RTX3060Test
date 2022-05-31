# - Try to find desay_pps lib
#
# Once done this will define
#
#  DesayPPS_FOUND - system has desay_pps lib with correct version
#  DesayPPS_INCLUDE_DIRS - the desay_pps include directory
#  DesayPPS_LIBRARIES - the desay_pps library

find_path(DesayPPS_INCLUDE_DIR "ppscontrol.h")
find_library(DesayPPS_LIBRARY pps_com)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(DesayPPS REQUIRED_VARS DesayPPS_LIBRARY DesayPPS_INCLUDE_DIR)

mark_as_advanced(DesayPPS_LIBRARY DesayPPS_INCLUDE_DIR)

set(DesayPPS_INCLUDE_DIRS ${DesayPPS_INCLUDE_DIR})
set(DesayPPS_LIBRARIES ${DesayPPS_LIBRARY})

if(DesayPPS_FOUND)
    if(NOT TARGET DesayPPS::pps)
        add_library(DesayPPS::pps UNKNOWN IMPORTED)
        if(DesayPPS_INCLUDE_DIR)
            set_target_properties(DesayPPS::pps PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${DesayPPS_INCLUDE_DIR})
        endif()
        if(DesayPPS_LIBRARY)
            set_target_properties(DesayPPS::pps PROPERTIES
                IMPORTED_LOCATION ${DesayPPS_LIBRARY})
        endif()
    endif()
endif()

