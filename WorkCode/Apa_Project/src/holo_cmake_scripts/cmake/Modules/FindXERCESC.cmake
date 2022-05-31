# - Try to find xerces-c lib
#
# Once done this will define
#
#  XERCESC_FOUND - system has x264 lib with correct version
#  XERCESC_INCLUDE_DIRS - the x264 include directory
#  XERCESC_LIBRARIES - the x264 library

if (NOT TARGET XERCESC::xerces-c)

    find_path(XERCESC_INCLUDE_DIR "xercesc/util/XercesVersion.hpp")
    find_library(XERCESC_LIBRARY libxerces-c.so)
    
    if (XERCESC_INCLUDE_DIR)
        file(READ ${XERCESC_INCLUDE_DIR}/xercesc/util/XercesVersion.hpp XERCESC_VERSION_STRING)
        string(REGEX MATCH "#define XERCES_VERSION_MAJOR *([0-9]+)" _ ${XERCESC_VERSION_STRING})
        set(XERCESC_VERSION_MAJOR ${CMAKE_MATCH_1})
        string(REGEX MATCH "#define XERCES_VERSION_MINOR *([0-9]+)" _ ${XERCESC_VERSION_STRING})
        set(XERCESC_VERSION_MINOR ${CMAKE_MATCH_1})
        string(REGEX MATCH "#define XERCES_VERSION_REVISION *([0-9]+)" _ ${XERCESC_VERSION_STRING})
        set(XERCESC_VERSION_PATCH ${CMAKE_MATCH_1})
        set(XERCESC_VERSION ${XERCESC_VERSION_MAJOR}.${XERCES_VERSION_MINOR}.${XERCESC_VERSION_PATCH})
    endif ()
    
    include(FindPackageHandleStandardArgs)
    
    find_package_handle_standard_args(XERCESC 
        REQUIRED_VARS 
            XERCESC_LIBRARY 
            XERCESC_INCLUDE_DIR 
        VERSION_VAR 
            XERCESC_VERSION
        )
    
    mark_as_advanced(XERCESC_LIBRARY XERCESC_INCLUDE_DIR)
    
    set(XERCESC_INCLUDE_DIRS ${XERCESC_INCLUDE_DIR})
    set(XERCESC_LIBRARIES ${XERCESC_LIBRARY})
    
    if (XERCESC_FOUND)
        if (NOT TARGET XERCESC::xerces-c)
            add_library(XERCESC::xerces-c UNKNOWN IMPORTED)
            set_target_properties(XERCESC::xerces-c PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES 
                    "${XERCESC_INCLUDE_DIR}"
                IMPORTED_LOCATION 
                    "${XERCESC_LIBRARY}"
                )
        endif()
    endif ()
endif ()
