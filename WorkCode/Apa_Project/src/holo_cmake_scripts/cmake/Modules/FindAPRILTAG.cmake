# * Try to find apriltag lib
#
# Once done this will define
#
# APRILTAG_FOUND - system has apriltag lib with correct version
# APRILTAG_INCLUDE_DIRS - the apriltag include directory APRILTAG_LIBRARIES -
# the apriltag library

find_path(APRILTAG_INCLUDE_DIR "apriltag/apriltag.h")
find_library(APRILTAG_LIBRARY apriltag)

set(APRILTAG_REQUIRED_VARS APRILTAG_INCLUDE_DIR APRILTAG_LIBRARY)

if(APRILTAG_FIND_VERSION_MAJOR EQUAL 2)
    find_path(APRILTAG_CPP_INCLUDE_DIR "apriltag_cpp/apriltags2_adapter.h")
    find_library(APRILTAG_CPP_LIBRARY apriltag_cpp)
    set(APRILTAG_REQUIRED_VARS ${APRILTAG_REQUIRED_VARS} APRILTAG_CPP_INCLUDE_DIR APRILTAG_CPP_LIBRARY)
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    APRILTAG REQUIRED_VARS ${APRILTAG_REQUIRED_VARS})
mark_as_advanced(${APRILTAG_REQUIRED_VARS})

if(APRILTAG_FOUND)
    if(NOT TARGET APRILTAG::apriltag)
        add_library(APRILTAG::apriltag UNKNOWN IMPORTED)
        set_target_properties(
            APRILTAG::apriltag
            PROPERTIES IMPORTED_LOCATION "${APRILTAG_LIBRARY}"
                       INTERFACE_INCLUDE_DIRECTORIES
                       "${APRILTAG_INCLUDE_DIR}/apriltag")
    endif()
    if((NOT TARGET APRILTAG::apriltag_cpp) AND (APRILTAG_FIND_VERSION_MAJOR EQUAL 2))
        add_library(APRILTAG::apriltag_cpp UNKNOWN IMPORTED)
        set_target_properties(
            APRILTAG::apriltag_cpp
            PROPERTIES IMPORTED_LOCATION "${APRILTAG_CPP_LIBRARY}"
                       INTERFACE_INCLUDE_DIRECTORIES
                       "${APRILTAG_CPP_INCLUDE_DIR}/apriltag_cpp"
                       INTERFACE_LINK_LIBRARIES "APRILTAG::apriltag")
    endif()
endif()
