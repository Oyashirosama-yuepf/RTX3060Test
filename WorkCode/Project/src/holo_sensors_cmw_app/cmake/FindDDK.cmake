# - Try to find Huawei DDK package
#
# Once done this will define
#
#  DDK_FOUND - system has flann lib with correct version
#  DDK_INCLUDE_DIRS - the flann include directory
#  DDK_LIBRARIES - the flann library

find_path(DDK_AIENGINE_INCLUDE_DIR "hiaiengine/ai_types.h" PATHS ${DDK_TOOLKIT_ROOT}/include/inc PATH_SUFFIXES inc)
find_path(DDK_LIBC_SECURE_INCLUDE_DIR "securec.h" PATHS ${DDK_TOOLKIT_ROOT}/include/libc_sec/include PATH_SUFFIXES libc_sec/include)
find_path(DDK_THIRD_PARTY_CEREAL_INCLUDE_DIR "cereal/cereal.hpp" PATHS ${DDK_TOOLKIT_ROOT}/include PATH_SUFFIXES third_party/cereal/include)
find_path(DDK_THIRD_PARTY_GFLAGS_INCLUDE_DIR "gflags/gflags.h" PATHS ${DDK_TOOLKIT_ROOT}/include PATH_SUFFIXES third_party/gflags/include)
find_path(DDK_THIRD_PARTY_PROTOBUF_INCLUDE_DIR "google/protobuf/map.h" PATHS ${DDK_TOOLKIT_ROOT}/include PATH_SUFFIXES third_party/protobuf/include)
find_path(DDK_THIRD_PARTY_OPENCV2_INCLUDE_DIR "opencv2/cvconfig.h" PATHS ${DDK_TOOLKIT_ROOT}/include PATH_SUFFIXES third_party/opencv/include)
# find_path(DDK_THIRD_PARTY_OPENCV_INCLUDE_DIR "opencv/cv.h" PATHS ${DDK_TOOLKIT_ROOT}/include PATH_SUFFIXES third_party/opencv/include)

set(DDK_INCLUDE_DIRS 
    ${DDK_AIENGINE_INCLUDE_DIR} 
    ${DDK_LIBC_SECURE_INCLUDE_DIR}
    ${DDK_THIRD_PARTY_CEREAL_INCLUDE_DIR}
    ${DDK_THIRD_PARTY_GFLAGS_INCLUDE_DIR}
    ${DDK_THIRD_PARTY_PROTOBUF_INCLUDE_DIR}
    ${DDK_THIRD_PARTY_OPENCV2_INCLUDE_DIR})

set(DDK_LIBARIES_DIRS
    ${DDK_TOOLKIT_ROOT}/lib/aarch64-linux-gnu/lib)

foreach(lib ${DDK_FIND_COMPONENTS})
    find_library(DDK_${lib}_LIBRARY ${lib} HINTS ${DDK_TOOLKIT_ROOT}/lib/aarch64-linux-gnu/lib)
    message(DDK_${lib}_LIBRARY = ${DDK_${lib}_LIBRARY})
    message(HINTS = ${DDK_TOOLKIT_ROOT}/lib/aarch64-linux-gnu/lib)
    if(DDK_${lib}_LIBRARY)
        set(DDK_${lib}_FOUND 1)
        mark_as_advanced(DDK_${lib}_LIBRARY)
        set(DDK_${lib}_LIBRARIES ${DDK_${lib}_LIBRARY})
        list(APPEND DDK_LIBRARIES ${DDK_${lib}_LIBRARIES})
        MESSAGE(STATUS "DDK_${lib}_PATH = ${DDK_${lib}_LIBRARY}")
    endif()
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    DDK 
    REQUIRED_VARS
    DDK_AIENGINE_INCLUDE_DIR 
    DDK_LIBC_SECURE_INCLUDE_DIR
    DDK_THIRD_PARTY_CEREAL_INCLUDE_DIR
    DDK_THIRD_PARTY_GFLAGS_INCLUDE_DIR
    DDK_THIRD_PARTY_PROTOBUF_INCLUDE_DIR
    DDK_THIRD_PARTY_OPENCV2_INCLUDE_DIR
    HANDLE_COMPONENTS
    )

mark_as_advanced(
    DDK_AIENGINE_INCLUDE_DIR 
    DDK_LIBC_SECURE_INCLUDE_DIR
    DDK_THIRD_PARTY_CEREAL_INCLUDE_DIR
    DDK_THIRD_PARTY_GFLAGS_INCLUDE_DIR
    DDK_THIRD_PARTY_PROTOBUF_INCLUDE_DIR
    DDK_THIRD_PARTY_OPENCV2_INCLUDE_DIR
    )

