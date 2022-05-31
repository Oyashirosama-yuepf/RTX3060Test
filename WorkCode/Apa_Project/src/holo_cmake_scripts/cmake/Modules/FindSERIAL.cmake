# - Try to find serial lib
#
# Once done this will define
#
#  SERIAL_FOUND - system has serial lib with correct version
#  SERIAL_INCLUDE_DIRS - the serial include directory
#  SERIAL_LIBRARIES - the serial library

find_path(SERIAL_INCLUDE_DIR "serial/serial.h")
find_library(SERIAL_LIBRARY serial)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SERIAL REQUIRED_VARS SERIAL_LIBRARY SERIAL_INCLUDE_DIR)

mark_as_advanced(SERIAL_LIBRARY SERIAL_INCLUDE_DIR)

set(SERIAL_INCLUDE_DIRS ${SERIAL_INCLUDE_DIR})
set(SERIAL_LIBRARIES ${SERIAL_LIBRARY})

if(SERIAL_FOUND)
    if(NOT TARGET SERIAL::serial)
        add_library(SERIAL::serial UNKNOWN IMPORTED)
        set_target_properties(SERIAL::serial PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${SERIAL_INCLUDE_DIR}
            IMPORTED_LOCATION ${SERIAL_LIBRARY})
    endif()
endif()

