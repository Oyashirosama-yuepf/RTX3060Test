# - Try to find rply lib 
# 
# Once done this will define 
# 
#  RPLY_FOUND - system has rply lib with correct version 
#  RPLY_INCLUDE_DIRS - the rply include directory 
#  RPLY_LIBRARIES - the rply library 

find_path(RPLY_INCLUDE_DIR "rply/rply.h") 
find_library(RPLY_LIBRARY rply) 

if(RPLY_INCLUDE_DIR)
    file(READ ${RPLY_INCLUDE_DIR}/rply/rply.h RPLY_VERSION_STRING)
    string(REGEX MATCH "#define RPLY_VERSION *\".*([0-9]+).([0-9]+).([0-9]+)\"" _ ${RPLY_VERSION_STRING})
    set(RPLY_VERSION_MAJOR ${CMAKE_MATCH_1})
    set(RPLY_VERSION_MINOR ${CMAKE_MATCH_2})
    set(RPLY_VERSION_PATCH ${CMAKE_MATCH_3})
    set(RPLY_VERSION ${RPLY_VERSION_MAJOR}.${RPLY_VERSION_MINOR}.${RPLY_VERSION_PATCH})
endif(RPLY_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(RPLY REQUIRED_VARS RPLY_LIBRARY RPLY_INCLUDE_DIR VERSION_VAR RPLY_VERSION)

mark_as_advanced(RPLY_LIBRARY RPLY_INCLUDE_DIR)

set(RPLY_INCLUDE_DIRS ${RPLY_INCLUDE_DIR})
set(RPLY_LIBRARIES ${RPLY_LIBRARY})

if(RPLY_FOUND)
    if(NOT TARGET RPLY::rply)
        add_library(RPLY::rply UNKNOWN IMPORTED)
        set_target_properties(RPLY::rply PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${RPLY_INCLUDE_DIR}
            IMPORTED_LOCATION ${RPLY_LIBRARY})
    endif()
endif()

