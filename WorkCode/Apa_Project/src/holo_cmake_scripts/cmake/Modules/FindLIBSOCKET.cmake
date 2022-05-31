# - Try to find libsocket lib
#
# Once done this will define
#
#  LIBSOCKET_FOUND - system has libsocket lib with correct version
#  LIBSOCKET_INCLUDE_DIRS - the libsocket include directory
#  LIBSOCKET_LIBRARIES - the libsocket library
#  LIBSOCKET_C_LIBRARIES - the libsocket library
#  LIBSOCKET_CPP_LIBRARIES - the libsocket library

find_path(LIBSOCKET_INCLUDE_DIR "libsocket/socket.hpp")

if (NOT LIBSOCKET_FIND_COMPONENTS)
    set(LIBSOCKET_FIND_COMPONENTS socket++)
endif ()

set(LIBSOCKET_REQUIRED_VARS)

if (LIBSOCKET_FIND_COMPONENTS)
    foreach (comp ${LIBSOCKET_FIND_COMPONENTS})
        find_library(LIBSOCKET_${comp}_LIBRARY ${comp})
        if(LIBSOCKET_${comp}_LIBRARY)
            set(LIBSOCKET_${comp}_FOUND 1)
            mark_as_advanced(LIBSOCKET_${comp}_LIBRARY)
            set(LIBSOCKET_${comp}_LIBRARIES ${LIBSOCKET_${comp}_LIBRARY})
            list(APPEND LIBSOCKET_LIBRARIES ${LIBSOCKET_${comp}_LIBRARIES})
        endif()
    endforeach()
endif ()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(LIBSOCKET REQUIRED_VARS LIBSOCKET_INCLUDE_DIR HANDLE_COMPONENTS)

mark_as_advanced(LIBSOCKET_INCLUDE_DIR)

set(LIBSOCKET_INCLUDE_DIRS ${LIBSOCKET_INCLUDE_DIR})

if (LIBSOCKET_FOUND)
    if (LIBSOCKET_FIND_COMPONENTS)
        foreach (comp ${LIBSOCKET_FIND_COMPONENTS})
            if (LIBSOCKET_${comp}_FOUND)
                if (NOT TARGET LIBSOCKET::${comp})
                    add_library(LIBSOCKET::${comp} UNKNOWN IMPORTED)
                    set_target_properties(LIBSOCKET::${comp} PROPERTIES
                        INTERFACE_INCLUDE_DIRECTORIES ${LIBSOCKET_INCLUDE_DIR}/libsocket
                        IMPORTED_LOCATION ${LIBSOCKET_${comp}_LIBRARY})
                endif ()
            endif()
        endforeach()
    endif ()
endif()

