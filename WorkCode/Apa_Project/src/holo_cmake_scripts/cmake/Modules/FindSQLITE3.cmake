# - find Sqlite 3
# SQLITE3_INCLUDE_DIR - Where to find Sqlite 3 header files (directory)
# SQLITE3_LIBRARIES - Sqlite 3 libraries
# SQLITE3_LIBRARY_RELEASE - Where the release library is
# SQLITE3_LIBRARY_DEBUG - Where the debug library is
# SQLITE3_FOUND - Set to TRUE if we found everything (library, includes and executable)

find_path(SQLITE3_INCLUDE_DIR "sqlite3.h" PATH_SUFFIXES sqlite)
find_library(SQLITE3_LIBRARY sqlite3)

if (SQLITE3_INCLUDE_DIR)
    file(READ ${SQLITE3_INCLUDE_DIR}/sqlite3.h SQLITE3_VERSION_STRING)
    string(REGEX MATCH "#define SQLITE_VERSION *\"([0-9]+).([0-9]+).([0-9]+)\"" _ ${SQLITE3_VERSION_STRING})
    set(SQLITE3_VERSION_MAJOR ${CMAKE_MATCH_1})
    set(SQLITE3_VERSION_MINOR ${CMAKE_MATCH_2})
    set(SQLITE3_VERSION_PATCH ${CMAKE_MATCH_3})
    set(SQLITE3_VERSION ${SQLITE3_VERSION_MAJOR}.${SQLITE3_VERSION_MINOR}.${SQLITE3_VERSION_PATCH})
endif (SQLITE3_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SQLITE3 REQUIRED_VARS SQLITE3_LIBRARY SQLITE3_INCLUDE_DIR VERSION_VAR SQLITE3_VERSION)

mark_as_advanced(SQLITE3_LIBRARY SQLITE3_INCLUDE_DIR)

set(SQLITE3_INCLUDE_DIRS ${SQLITE3_INCLUDE_DIR})
set(SQLITE3_LIBRARIES ${SQLITE3_LIBRARY})

IF( SQLITE3_FOUND )
    IF( NOT SQLITE3_FIND_QUIETLY )
        MESSAGE( STATUS "Found Sqlite3 header file in ${SQLITE3_INCLUDE_DIR}")
        MESSAGE( STATUS "Found Sqlite3 libraries: ${SQLITE3_LIBRARIES}")
    ENDIF( NOT SQLITE3_FIND_QUIETLY )
    if (NOT TARGET SQLITE3::sqlite3)
        add_library(SQLITE3::sqlite3 UNKNOWN IMPORTED)
        set_target_properties(SQLITE3::sqlite3 PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${SQLITE3_INCLUDE_DIR}"
            IMPORTED_LOCATION "${SQLITE3_LIBRARY}"
        )
    endif ()
ELSE(SQLITE3_FOUND)
    IF( SQLITE3_FIND_REQUIRED)
        MESSAGE( FATAL_ERROR "Could not find Sqlite3" )
    ELSE( SQLITE3_FIND_REQUIRED)
        MESSAGE( STATUS "Optional package Sqlite3 was not found" )
    ENDIF( SQLITE3_FIND_REQUIRED)
ENDIF(SQLITE3_FOUND)
