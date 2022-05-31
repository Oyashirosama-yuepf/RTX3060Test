# - Try to find x264 lib
#
# Once done this will define
#
#  X264_FOUND - system has x264 lib with correct version
#  X264_INCLUDE_DIRS - the x264 include directory
#  X264_LIBRARIES - the x264 library

if (NOT TARGET X264::x264)

    find_path(X264_INCLUDE_DIR "x264.h")
    find_library(X264_LIBRARY libx264.so)
    
    if (X264_INCLUDE_DIR)
        file(READ ${X264_INCLUDE_DIR}/x264.h X264_VERSION_STRING)
        set(X264_VERSION_MAJOR 0)
        string(REGEX MATCH "#define X264_BUILD *([0-9]+)" _ ${X264_VERSION_STRING})
        set(X264_VERSION_MINOR ${CMAKE_MATCH_1})
    endif ()
    
    include(FindPackageHandleStandardArgs)
    
    find_package_handle_standard_args(X264 REQUIRED_VARS X264_LIBRARY X264_INCLUDE_DIR VERSION_VAR X264_VERSION)
    
    mark_as_advanced(X264_LIBRARY X264_INCLUDE_DIR)
    
    set(X264_INCLUDE_DIRS ${X264_INCLUDE_DIR})
    set(X264_LIBRARIES ${X264_LIBRARY})
    
    if (X264_FOUND)
        if (NOT TARGET X264::x264)
            add_library(X264::x264 UNKNOWN IMPORTED)
            set_target_properties(X264::x264 PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${X264_INCLUDE_DIR}"
                IMPORTED_LOCATION "${X264_LIBRARY}"
                )
        endif()
    endif ()
endif ()
