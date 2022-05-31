# - Try to find qpOASES lib
#
# Once done this will define
#
#  qpOASES_FOUND - system has qpOASES lib with correct version
#  qpOASES_INCLUDE_DIRS - the qpOASES include directory
#  qpOASES_LIBRARIES - the qpOASES library

include(FindPackageHandleStandardArgs)

find_path(QPOASES_INCLUDE_DIR
          NAMES qpOASES.hpp
         )
find_library(QPOASES_LIBRARY
             NAMES qpOASES
            )

if(QPOASES_INCLUDE_DIR)
    file(READ ${QPOASES_INCLUDE_DIR}/qpOASES.hpp QPOASES_VERSION_STRING)
    string(REGEX MATCH "[ ]*[\\]version *([0-9]+).([0-9]+)" _ ${QPOASES_VERSION_STRING})
    set(QPOASES_VERSION_MAJOR ${CMAKE_MATCH_1})
    set(QPOASES_VERSION_MINOR ${CMAKE_MATCH_2})
    set(QPOASES_VERSION ${QPOASES_VERSION_MAJOR}.${QPOASES_VERSION_MINOR})

    set(QPOASES_VERSION_EXACT FALSE)
    set(QPOASES_VERSION_COMPATIBLE FALSE)

    #if(QPOASES_FIND_VERSION VERSION_EQUAL QPOASES_VERSION)
    #    set(QPOASES_VERSION_EXACT TRUE)
    #    set(QPOASES_VERSION_COMPATIBLE TRUE)
    #endif()

    #if(QPOASES_FIND_VERSION_MAJOR EQUAL QPOASES_VERSION_MAJOR
    #    AND QPOASES_FIND_VERSION VERSION_LESS QPOASES_VERSION)
    #    set(QPOASES_VERSION_COMPATIBLE TRUE)
    #endif()

    # Unable to get patch version from header file. Assume version equals exactly if major and minor versions are equal.
    if (QPOASES_FIND_VERSION_MAJOR EQUAL QPOASES_VERSION_MAJOR)
        if (QPOASES_FIND_VERSION_MINOR EQUAL QPOASES_VERSION_MINOR)
            set(QPOASES_VERSION_EXACT TRUE)
            set(QPOASES_VERSION_COMPATIBLE TRUE)
        endif ()
    endif ()

endif(QPOASES_INCLUDE_DIR)

mark_as_advanced(QPOASES_INCLUDE_DIR QPOASES_LIBRARY)

set(QPOASES_INCLUDE_DIRS ${QPOASES_INCLUDE_DIR})
set(QPOASES_LIBRARIES ${QPOASES_LIBRARY})

find_package_handle_standard_args(QPOASES
    REQUIRED_VARS QPOASES_LIBRARIES QPOASES_INCLUDE_DIRS
    VERSION_VAR QPOASES_VERSION)

if (QPOASES_FOUND)
    if (NOT TARGET QPOASES::qpOASES)
        add_library(QPOASES::qpOASES UNKNOWN IMPORTED)
        set_target_properties(QPOASES::qpOASES PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${QPOASES_INCLUDE_DIR}
                IMPORTED_LOCATION ${QPOASES_LIBRARY})
    endif ()
endif ()

