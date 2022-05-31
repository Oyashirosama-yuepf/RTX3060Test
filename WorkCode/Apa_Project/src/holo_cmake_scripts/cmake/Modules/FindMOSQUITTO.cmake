# * Try to find mosquitto lib
#
# Once done this will define
#
# MOSQUITTO_FOUND - system has mosquitto lib with correct version
# MOSQUITTO_INCLUDE_DIRS - the mosquitto include directory MOSQUITTO_LIBRARIES -
# the mosquitto library

find_path(MOSQUITTO_INCLUDE_DIR "mosquitto.h")
find_library(MOSQUITTO_LIBRARY libmosquitto.so)
find_library(MOSQUITTOPP_LIBRARY libmosquittopp.so)

if(MOSQUITTO_INCLUDE_DIR)
    file(READ ${MOSQUITTO_INCLUDE_DIR}/mosquitto.h MOSQUITTO_VERSION_STRING)
    string(REGEX MATCH "#define LIBMOSQUITTO_MAJOR *([0-9]+)" _
                 ${MOSQUITTO_VERSION_STRING})
    set(MOSQUITTO_VERSION_MAJOR ${CMAKE_MATCH_1})
    string(REGEX MATCH "#define LIBMOSQUITTO_MINOR *([0-9]+)" _
                 ${MOSQUITTO_VERSION_STRING})
    set(MOSQUITTO_VERSION_MINOR ${CMAKE_MATCH_1})
    string(REGEX MATCH "#define LIBMOSQUITTO_REVISION *([0-9]+)" _
                 ${MOSQUITTO_VERSION_STRING})
    set(MOSQUITTO_VERSION_PATCH ${CMAKE_MATCH_1})
    set(MOSQUITTO_VERSION
        ${MOSQUITTO_VERSION_MAJOR}.${MOSQUITTO_VERSION_MINOR}.${MOSQUITTO_VERSION_PATCH}
    )
endif(MOSQUITTO_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    MOSQUITTO
    REQUIRED_VARS MOSQUITTO_LIBRARY MOSQUITTOPP_LIBRARY MOSQUITTO_INCLUDE_DIR
    VERSION_VAR MOSQUITTO_VERSION)

mark_as_advanced(MOSQUITTO_LIBRARY MOSQUITTOPP_LIBRARY MOSQUITTO_INCLUDE_DIR)

set(MOSQUITTO_INCLUDE_DIRS ${MOSQUITTO_INCLUDE_DIR})
set(MOSQUITTO_LIBRARIES ${MOSQUITTO_LIBRARY} ${MOSQUITTOPP_LIBRARY})

if(MOSQUITTO_FOUND)
    if(NOT TARGET MOSQUITTO::mosquitto)
        add_library(MOSQUITTO::mosquitto UNKNOWN IMPORTED)
        set_target_properties(
            MOSQUITTO::mosquitto PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                            ${MOSQUITTO_INCLUDE_DIR})
        set_target_properties(MOSQUITTO::mosquitto
                              PROPERTIES IMPORTED_LOCATION ${MOSQUITTO_LIBRARY})
    endif()
    if(NOT TARGET MOSQUITTO::mosquittopp)
        add_library(MOSQUITTO::mosquittopp UNKNOWN IMPORTED)
        set_target_properties(
            MOSQUITTO::mosquittopp PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                              ${MOSQUITTO_INCLUDE_DIR})
        set_target_properties(
            MOSQUITTO::mosquittopp PROPERTIES IMPORTED_LOCATION
                                              ${MOSQUITTOPP_LIBRARY})
    endif()
endif()
