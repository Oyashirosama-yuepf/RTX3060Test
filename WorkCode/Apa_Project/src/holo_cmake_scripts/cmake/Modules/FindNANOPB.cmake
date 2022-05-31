
find_path(NANOPB_INCLUDE_DIR "nanopb/pb.h")
find_library(NANOPB_LIBRARY protobuf-nanopb)

if(NANOPB_INCLUDE_DIR)
    file(READ ${NANOPB_INCLUDE_DIR}/nanopb/pb.h NANOPB_VERSION_STRING)
    string(REGEX MATCH "#define NANOPB_VERSION nanopb-*([0-9]+).([0-9]+).([0-9]+)" _ ${NANOPB_VERSION_STRING})
    set(NANOPB_VERSION_MAJOR ${CMAKE_MATCH_1})
    set(NANOPB_VERSION_MINOR ${CMAKE_MATCH_2})
    set(NANOPB_VERSION_PATCH ${CMAKE_MATCH_3})
    set(NANOPB_VERSION ${NANOPB_VERSION_MAJOR}.${NANOPB_VERSION_MINOR}.${NANOPB_VERSION_PATCH})
endif(NANOPB_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(NANOPB REQUIRED_VARS NANOPB_LIBRARY NANOPB_INCLUDE_DIR VERSION_VAR NANOPB_VERSION)

mark_as_advanced(NANOPB_LIBRARY NANOPB_INCLUDE_DIR)

set(NANOPB_INCLUDE_DIRS ${NANOPB_INCLUDE_DIR})
set(NANOPB_LIBRARIES ${NANOPB_LIBRARY})

if(NANOPB_FOUND)
    if(NOT TARGET NANOPB::nanopb)
        add_library(NANOPB::nanopb UNKNOWN IMPORTED)
        if(NANOPB_INCLUDE_DIR)
            set_target_properties(NANOPB::nanopb PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${NANOPB_INCLUDE_DIR})
        endif()
        if(NANOPB_LIBRARY)
            set_target_properties(NANOPB::nanopb PROPERTIES
                IMPORTED_LOCATION ${NANOPB_LIBRARY})
        endif()
    endif()
endif()

