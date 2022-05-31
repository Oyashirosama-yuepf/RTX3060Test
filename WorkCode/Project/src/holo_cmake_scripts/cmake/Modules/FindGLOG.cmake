# - Try to find glog lib
#
# Once done this will define
#
#  GLOG_FOUND - system has glog lib with correct version
#  GLOG_INCLUDE_DIRS - the glog include directory
#  GLOG_LIBRARIES - the glog library

if (NOT TARGET GLOG::glog)
    
    find_path(GLOG_INCLUDE_DIR "glog/logging.h")
    find_library(GLOG_LIBRARY libglog.so)
    
    include(FindPackageHandleStandardArgs)
    
    find_package_handle_standard_args(GLOG REQUIRED_VARS GLOG_LIBRARY GLOG_INCLUDE_DIR)
    
    mark_as_advanced(GLOG_LIBRARY GLOG_INCLUDE_DIR)
    
    set(GLOG_INCLUDE_DIRS ${GLOG_INCLUDE_DIR})
    set(GLOG_LIBRARIES ${GLOG_LIBRARY})
    
    if (GLOG_FOUND)
        if (NOT TARGET GLOG::glog)
            add_library(GLOG::glog UNKNOWN IMPORTED)
            set_target_properties(GLOG::glog PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${GLOG_INCLUDE_DIR}"
                IMPORTED_LOCATION "${GLOG_LIBRARY}"
            )
        endif()
    endif ()
endif ()
