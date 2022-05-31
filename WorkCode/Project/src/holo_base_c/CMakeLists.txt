cmake_minimum_required(VERSION "2.8")
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)

project(holo_base_c)

#Set project version
set(${PROJECT_NAME}_VERSION_MAJOR   "0")
set(${PROJECT_NAME}_VERSION_MINOR   "4")
set(${PROJECT_NAME}_VERSION_PATCH   "0")
set(${PROJECT_NAME}_SOVERSION       "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}")
set(${PROJECT_NAME}_VERSION         "${${PROJECT_NAME}_SOVERSION}.${${PROJECT_NAME}_VERSION_PATCH}")

# default options
if (CMAKE_SYSTEM_PROCESSOR STREQUAL TriCore)
    option(HOLO_BUILD_TEST   "Build unit test"      OFF)
    option(HOLO_BUILD_SHARED "Build shared library" OFF)
else ()
    option(HOLO_BUILD_TEST   "Build unit test"      ON)
    option(HOLO_BUILD_SHARED "Build shared library" ON)
endif ()
option(HOLO_MATRIX_ALIGN   "Whether matrix should be aligned" OFF)
option(HOLO_BUILD_COVERAGE "Generate coverage report"         OFF)

# Set CMake variable to build shared library or static library.
if (HOLO_BUILD_SHARED)
    set(BUILD_SHARED_LIBS       ON)
else ()
    set(BUILD_SHARED_LIBS       OFF)
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wno-unused-function")

# Set CMake variable for additional .cmake file search path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
include(HoloProjectConfiguration)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake/Modules")

# Some compiler/linker(eg. qcc5.4) won't follow rpath property to link secondary libraries.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-rpath-link=${HOLO_3RDPARTY_ROOT}/lib")

include(HoloMacros)

## ------------------------- DOXYGEN-------------------------------------
GENERATE_DOXYGEN(OPTIMIZE_OUTPUT_FOR_C INPUT include src doc)

## ------------------------- COVERAGE -----------------------------------
if(HOLO_BUILD_COVERAGE)
    if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
        set(HOLO_BUILD_TEST ON)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -DNDEBUG --coverage")
        GENERATE_COVERAGE_REPORT(EXCLUDE_PATTERNS 
            "${PROJECT_SOURCE_DIR}/3rdparty/*"
            "${PROJECT_SOURCE_DIR}/test/*"
            "${PROJECT_SOURCE_DIR}/src/generated/*")
    else()
        MESSAGE(FATAL_ERROR "Unable to generate coverage report! CMAKE_BUILD_TYPE is not DEBUG!")
    endif()
endif()

## -------------------------holo_base_c------------------------------------
add_library(${PROJECT_NAME}
    src/common/chassis_state.c
    src/common/control_command.c
    src/common/coordinate.c
    src/common/dequeue.c
    src/common/extrinsic_float32.c
    src/common/gnss_position.c
    src/common/gnss_pvt.c
    src/common/imu_float32.c
    src/common/imu_bias_float32.c
    src/common/light_signal_request.c
    src/common/odometry_float32.c
    src/common/path_float32.c
    src/common/queue.c
    src/common/someip.c
    src/common/timestamp.c
    src/common/uss_info.c
    src/filters/kalman_filter_float32.c
    src/generated/cubic_spline.c
    src/geometry/angle_float32.c
    src/geometry/box2_float32.c
    src/geometry/box3_float32.c
    src/geometry/convex_polygon2_float32.c
    src/geometry/geographical_transformation.c
    src/geometry/point2_float32.c
    src/geometry/point2_float64.c
    src/geometry/point3_float32.c
    src/geometry/point3_float64.c
    src/geometry/pose2_float32.c
    src/geometry/pose3_float32.c
    src/geometry/quaternion_float32.c
    src/geometry/rot2_float32.c
    src/geometry/rot3_float32.c
    src/numerics/cubic_polynomial.c
    src/numerics/cubic_spline.c
    src/numerics/matrix_float32.c
    src/numerics/vector_float32.c
    src/utils/serialization.c
    src/utils/geographical_transformation.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE m)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)
if (HOLO_MATRIX_ALIGN)
    target_compile_definitions(${PROJECT_NAME} PUBLIC MATRIX_ALIGN)
endif()

#if(CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64)
#    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -fpack-struct=4)
#endif()

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION 
        ${${PROJECT_NAME}_VERSION}
    SOVERSION 
        ${${PROJECT_NAME}_SOVERSION}
    INSTALL_RPATH 
        "\$ORIGIN/../3rdparty/lib"
)

if (HOLO_BUILD_TEST)
    set(UNITY_VERSION 2.4.3)
    add_library(unity 3rdparty/Unity-${UNITY_VERSION}/src/unity.c)
    include_directories(3rdparty/Unity-${UNITY_VERSION}/src)
    target_compile_definitions(unity PUBLIC UNITY_INCLUDE_DOUBLE)
    enable_testing()
    add_subdirectory(test)
endif (HOLO_BUILD_TEST)

include(CMakePackageConfigHelpers)

WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION 
        ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY 
        SameMajorVersion
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in 
    ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake 
    @ONLY
)

install(
    FILES 
        ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake 
    DESTINATION 
        "lib/cmake/${PROJECT_NAME}"
    COMPONENT
        development
)

install(
    TARGETS 
        ${PROJECT_NAME}
    EXPORT 
        ${PROJECT_NAME}-targets
    DESTINATION 
        "lib"
    COMPONENT
        runtime
)

install(
    EXPORT 
        ${PROJECT_NAME}-targets
    NAMESPACE 
        "${PROJECT_NAME}::"
    DESTINATION 
        "lib/cmake/${PROJECT_NAME}"
    COMPONENT
        development
)

install(
    DIRECTORY 
        include/holo_c
    DESTINATION 
        include/${PROJECT_NAME}
    COMPONENT
        development
)

install(
    DIRECTORY 
        ${PROJECT_BINARY_DIR}/include/holo_c
    DESTINATION 
        include/${PROJECT_NAME} OPTIONAL
    COMPONENT
        development
)

add_custom_target(uninstall 
    COMMAND 
        cat install_manifest.txt | xargs rm 
    WORKING_DIRECTORY 
        ${PROJECT_BINARY_DIR}
    COMMENT 
        "Uninstall"
)

cmake_policy(POP)
