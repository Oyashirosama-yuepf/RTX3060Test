# - Try to find pangolin lib
#
# Once done this will define
#
#  PANGOLIN_FOUND - system has pangolin lib with correct version
#  PANGOLIN_INCLUDE_DIRS - the pangolin include directory
#  PANGOLIN_LIBRARIES - the pangolin library

find_path(PANGOLIN_INCLUDE_DIR "pangolin/pangolin.h")
find_library(PANGOLIN_LIBRARY pangolin)

if (PANGOLIN_INCLUDE_DIR)
    file(READ ${PANGOLIN_INCLUDE_DIR}/pangolin/config.h PANGOLIN_VERSION_STRING)
    string(REGEX MATCH "#define PANGOLIN_VERSION_STRING *\"([0-9])+.([0-9]+)\"" _ ${PANGOLIN_VERSION_STRING})
    set(PANGOLIN_VERSION ${CMAKE_MATCH_1}.${CMAKE_MATCH_2})
endif ()

include(FindPackageHandleStandardArgs)

find_package(FFMPEG QUIET COMPONENTS avcodec avdevice avformat avutil swscale)

find_package_handle_standard_args(PANGOLIN REQUIRED_VARS PANGOLIN_LIBRARY PANGOLIN_INCLUDE_DIR FFMPEG_FOUND VERSION_VAR PANGOLIN_VERSION)

mark_as_advanced(PANGOLIN_LIBRARY PANGOLIN_INCLUDE_DIR)

set(PANGOLIN_INCLUDE_DIRS ${PANGOLIN_INCLUDE_DIR})
set(PANGOLIN_LIBRARIES ${PANGOLIN_LIBRARY})

if(PANGOLIN_FOUND)
    if(NOT TARGET PANGOLIN::pangolin)
        add_library(PANGOLIN::pangolin UNKNOWN IMPORTED)
        set_target_properties(PANGOLIN::pangolin PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${PANTGOLIN_INCLUDE_DIR}"
            IMPORTED_LOCATION "${PANGOLIN_LIBRARY}"
            INTERFACE_LINK_LIBRARIES "GL;GLU;GLEW;EGL;FFMPEG::avcodec;FFMPEG::avdevice;FFMPEG::avformat;FFMPEG::avutil;FFMPEG::swscale;OpenNI;OpenNI2;png;z;jpeg;tiff;lz4"
        )
    endif()
endif()

