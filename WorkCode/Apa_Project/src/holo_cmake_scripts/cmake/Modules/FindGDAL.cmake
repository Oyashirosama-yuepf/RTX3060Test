# GDAL_INCLUDE_DIR - Where to find GDAL header files (directory)
# GDAL_LIBRARIES - GDAL libraries
# GDAL_FOUND - Set to TRUE if we found everything (library, includes and executable)
# GDAL_VERSION (GDAL_VERSION_MAJOR, GDAL_VERSION_MINOR, GDAL_VERSION_PATCH)

find_path(GDAL_INCLUDE_DIR
    gdal/gdal.h
    PATH_SUFFIXES include
)

find_library(GDAL_LIBRARY
    gdal
    PATH_SUFFIXES lib
)

if(EXISTS "${GDAL_INCLUDE_DIR}/gdal/gdal_version.h")
    file(STRINGS "${GDAL_INCLUDE_DIR}/gdal/gdal_version.h" GDAL_VERSIONS_TMP REGEX "^#[ ]*define GDAL_VERSION_[A-Z]+[ ]+[0-9]+$")
    string(REGEX REPLACE ".*#[ ]*define GDAL_VERSION_MAJOR[ ]+([0-9]+).*" "\\1" GDAL_VERSION_MAJOR ${GDAL_VERSIONS_TMP})
    string(REGEX REPLACE ".*#[ ]*define GDAL_VERSION_MINOR[ ]+([0-9]+).*" "\\1" GDAL_VERSION_MINOR ${GDAL_VERSIONS_TMP})
    string(REGEX REPLACE ".*#[ ]*define GDAL_VERSION_REV[ ]+([0-9]+).*" "\\1" GDAL_VERSION_REV ${GDAL_VERSIONS_TMP})
    string(REGEX REPLACE ".*#[ ]*define GDAL_VERSION_BUILD[ ]+([0-9]+).*" "\\1" GDAL_VERSION_BUILD ${GDAL_VERSIONS_TMP})
    set(GDAL_VERSION_STRING "${GDAL_VERSION_MAJOR}.${GDAL_VERSION_MINOR}.${GDAL_VERSION_REV}")
endif()

# handle the QUIETLY and REQUIRED arguments and set GDAL_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GDAL
                                  REQUIRED_VARS GDAL_LIBRARY GDAL_INCLUDE_DIR
                                  VERSION_VAR GDAL_VERSION_STRING)

mark_as_advanced(GDAL_INCLUDE_DIR GDAL_LIBRARY)

if(GDAL_FOUND)
    if (NOT TARGET GDAL::gdal)
        add_library(GDAL::gdal UNKNOWN IMPORTED)
        set_target_properties(GDAL::gdal PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${GDAL_INCLUDE_DIR}
            IMPORTED_LOCATION ${GDAL_LIBRARY}
        )
    endif ()
endif()
