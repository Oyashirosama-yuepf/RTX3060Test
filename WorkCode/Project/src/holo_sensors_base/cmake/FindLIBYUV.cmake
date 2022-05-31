find_path(LIBYUV_INCLUDE_DIR
  NAMES libyuv.h
  DOC "libyuv include directory")
MESSAGE(STATUS "LIBYUV_INCLUDE_DIR = ${LIBYUV_INCLUDE_DIR}")
mark_as_advanced(LIBYUV_INCLUDE_DIR)
find_library(LIBYUV_LIBRARY
  NAMES yuv
  DOC "libyuv library")
MESSAGE(STATUS "LIBYUV_LIBRARY = ${LIBYUV_LIBRARY}")
mark_as_advanced(LIBYUV_LIBRARY)

if (LIBYUV_INCLUDE_DIR)
  file(STRINGS "${LIBYUV_INCLUDE_DIR}/libyuv.h" _libyuv_version_lines
    REGEX "#define[ \t]+LIBYUV_VERSION_(MAJOR|MINOR|RELEASE)")
  string(REGEX REPLACE ".*LIBYUV_VERSION_MAJOR *\([0-9]*\).*" "\\1" _libyuv_version_major "${_libyuv_version_lines}")
  string(REGEX REPLACE ".*LIBYUV_VERSION_MINOR *\([0-9]*\).*" "\\1" _libyuv_version_minor "${_libyuv_version_lines}")
  string(REGEX REPLACE ".*LIBYUV_VERSION_RELEASE *\([0-9]*\).*" "\\1" _libyuv_version_release "${_libyuv_version_lines}")
  if (NOT _libyuv_version_major)
    set(_libyuv_version_major 0)
  endif()
  if (NOT _libyuv_version_minor)
    set(_libyuv_version_minor 0)
  endif()
  if (NOT _libyuv_version_release)
    set(_libyuv_version_release 0)
  endif()
  set(LIBYUV_VERSION "${_libyuv_version_major}.${_libyuv_version_minor}.${_libyuv_version_release}")
  unset(_libyuv_version_major)
  unset(_libyuv_version_minor)
  unset(_libyuv_version_release)
  unset(_libyuv_version_lines)
endif ()
MESSAGE(STATUS "LIBYUV_VERSION = ${LIBYUV_VERSION}")
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBYUV
  REQUIRED_VARS LIBYUV_LIBRARY LIBYUV_INCLUDE_DIR
  VERSION_VAR LIBYUV_VERSION)

if (LIBYUV_FOUND)
  set(LIBYUV_INCLUDE_DIRS "${LIBYUV_INCLUDE_DIR}")
  set(LIBYUV_LIBRARIES "${LIBYUV_LIBRARY}")

  if (NOT TARGET LIBYUV::LIBYUV)
    add_library(LIBYUV::LIBYUV UNKNOWN IMPORTED)
    set_target_properties(LIBYUV::LIBYUV PROPERTIES
      IMPORTED_LOCATION "${LIBYUV_LIBRARY}"
      INTERFACE_INCLUDE_DIRECTORIES "${LIBYUV_INCLUDE_DIR}")
  endif ()
endif ()
