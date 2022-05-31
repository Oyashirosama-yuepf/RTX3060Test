# - Try to find Ipopt lib
#
# Once done this will define
#
#  IPOPT_FOUND - system has Ipopt lib with correct version
#  IPOPT_INCLUDE_DIRS - the Ipopt include directory
#  IPOPT_LIBRARIES - the Ipopt library

find_path(IPOPT_INCLUDE_DIR "coin/IpoptConfig.h")
find_library(IPOPT_LIBRARY ipopt)

if(IPOPT_INCLUDE_DIR)
    file(READ ${IPOPT_INCLUDE_DIR}/coin/IpoptConfig.h IPOPT_VERSION_STRING)
    string(REGEX MATCH "#define IPOPT_VERSION \"([0-9]+).([0-9]+).([0-9]+)\"" _ ${IPOPT_VERSION_STRING})
    set(IPOPT_VERSION_MAJOR ${CMAKE_MATCH_1})
    set(IPOPT_VERSION_MINOR ${CMAKE_MATCH_2})
    set(IPOPT_VERSION_PATCH ${CMAKE_MATCH_3})
    set(IPOPT_VERSION ${IPOPT_VERSION_MAJOR}.${IPOPT_VERSION_MINOR}.${IPOPT_VERSION_PATCH})
endif(IPOPT_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(IPOPT REQUIRED_VARS IPOPT_LIBRARY IPOPT_INCLUDE_DIR VERSION_VAR IPOPT_VERSION)

mark_as_advanced(IPOPT_LIBRARY IPOPT_INCLUDE_DIR)

set(IPOPT_INCLUDE_DIRS ${IPOPT_INCLUDE_DIR})
set(IPOPT_LIBRARIES ${IPOPT_LIBRARY})

if(IPOPT_FOUND)
    if(NOT TARGET IPOPT::Ipopt)
        add_library(IPOPT::Ipopt UNKNOWN IMPORTED)
        if(IPOPT_INCLUDE_DIR)
            set_target_properties(IPOPT::Ipopt PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${IPOPT_INCLUDE_DIR})
        endif()
        if(IPOPT_LIBRARY)
            set_target_properties(IPOPT::Ipopt PROPERTIES
                IMPORTED_LOCATION ${IPOPT_LIBRARY})
        endif()
    endif()
endif()
