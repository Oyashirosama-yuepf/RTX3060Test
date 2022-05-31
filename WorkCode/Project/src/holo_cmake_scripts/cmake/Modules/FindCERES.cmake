# - Try to find ceres lib
#
# Once done this will define
#
#  CERES_FOUND - system has ceres lib with correct version
#  CERES_INCLUDE_DIRS - the ceres include directory
#  CERES_LIBRARIES - the ceres library

if (NOT TARGET CERES::ceres)
    find_package(Eigen3 3.3.7 QUIET)
#    find_package(SuiteSparse QUIET)
#    find_package(CXSparse QUIET)
    
    find_path(CERES_INCLUDE_DIR "ceres/ceres.h")
    find_library(CERES_LIBRARY ceres)
    
    if (CERES_INCLUDE_DIR)
        file(READ ${CERES_INCLUDE_DIR}/ceres/version.h CERES_VERSION_STRING)
        string(REGEX MATCH "#define CERES_VERSION_MAJOR *([0-9]+)" _ ${CERES_VERSION_STRING})
        set(CERES_VERSION_MAJOR ${CMAKE_MATCH_1})
        string(REGEX MATCH "#define CERES_VERSION_MINOR *([0-9]+)" _ ${CERES_VERSION_STRING})
        set(CERES_VERSION_MINOR ${CMAKE_MATCH_1})
        string(REGEX MATCH "#define CERES_VERSION_REVISION *([0-9]+)" _ ${CERES_VERSION_STRING})
        set(CERES_VERSION_PATCH ${CMAKE_MATCH_1})
        set(CERES_VERSION ${CERES_VERSION_MAJOR}.${CERES_VERSION_MINOR}.${CERES_VERSION_PATCH})
    endif ()
    
    include(FindPackageHandleStandardArgs)
    
    find_package_handle_standard_args(CERES REQUIRED_VARS CERES_LIBRARY CERES_INCLUDE_DIR Eigen3_FOUND VERSION_VAR CERES_VERSION)
    
    mark_as_advanced(CERES_LIBRARY CERES_INCLUDE_DIR)
    
    set(CERES_INCLUDE_DIRS ${CERES_INCLUDE_DIR})
    set(CERES_LIBRARIES ${CERES_LIBRARY})
    
    if (CERES_FOUND)
        if (NOT TARGET CERES::ceres)
            add_library(CERES::ceres UNKNOWN IMPORTED)
            set_target_properties(CERES::ceres PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${CERES_INCLUDE_DIR}"
                IMPORTED_LOCATION "${CERES_LIBRARY}"
                INTERFACE_LINK_LIBRARIES "Eigen3::Eigen")
        endif()
    endif ()
endif ()
