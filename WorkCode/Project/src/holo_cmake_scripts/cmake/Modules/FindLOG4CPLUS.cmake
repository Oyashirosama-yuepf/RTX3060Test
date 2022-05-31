# - Try to find log4cplus lib
#
# Once done this will define
#
#  LOG4CPLUS_FOUND - system has log4cplus lib with correct version
#  LOG4CPLUS_INCLUDE_DIRS - the log4cplus include directory
#  LOG4CPLUS_LIBRARIES - the log4cplus library
#
#  LOG4CPLUS::log4cplus - log4cplus cmake target

find_path(LOG4CPLUS_INCLUDE_DIR "log4cplus/log4cplus.h")
find_library(LOG4CPLUS_LIBRARY liblog4cplus.so)

if(LOG4CPLUS_INCLUDE_DIR)
    file(READ ${LOG4CPLUS_INCLUDE_DIR}/log4cplus/version.h LOG4CPLUS_VERSION_STRING)
    string(REGEX MATCH "#define LOG4CPLUS_VERSION LOG4CPLUS_MAKE_VERSION.([0-9]+), ([0-9]+), ([0-9]+)" _ ${LOG4CPLUS_VERSION_STRING})
    set(LOG4CPLUS_VERSION_MAJOR ${CMAKE_MATCH_1})
    set(LOG4CPLUS_VERSION_MINOR ${CMAKE_MATCH_2})
    set(LOG4CPLUS_VERSION_PATCH ${CMAKE_MATCH_3})
    set(LOG4CPLUS_VERSION ${LOG4CPLUS_VERSION_MAJOR}.${LOG4CPLUS_VERSION_MINOR}.${LOG4CPLUS_VERSION_PATCH})
endif(LOG4CPLUS_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(LOG4CPLUS REQUIRED_VARS LOG4CPLUS_LIBRARY LOG4CPLUS_INCLUDE_DIR VERSION_VAR LOG4CPLUS_VERSION)

mark_as_advanced(LOG4CPLUS_LIBRARY LOG4CPLUS_INCLUDE_DIR)

set(LOG4CPLUS_INCLUDE_DIRS ${LOG4CPLUS_INCLUDE_DIR})
set(LOG4CPLUS_LIBRARIES ${LOG4CPLUS_LIBRARY})

if(LOG4CPLUS_FOUND)
    if(NOT TARGET LOG4CPLUS::log4cplus)
        add_library(LOG4CPLUS::log4cplus UNKNOWN IMPORTED)
        if(LOG4CPLUS_INCLUDE_DIR)
            set_target_properties(LOG4CPLUS::log4cplus PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${LOG4CPLUS_INCLUDE_DIR})
        endif()
        if(LOG4CPLUS_LIBRARY)
            set_target_properties(LOG4CPLUS::log4cplus PROPERTIES
                IMPORTED_LOCATION ${LOG4CPLUS_LIBRARY})
        endif()
    endif()
endif()

