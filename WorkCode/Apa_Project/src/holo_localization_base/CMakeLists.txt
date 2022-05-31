cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)

project(holo_localization_base)

## --------------------------- CONFIGURATIONS ----------------------------------------
# Set project version
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 7)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR})
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_SOVERSION}.${${PROJECT_NAME}_VERSION_PATCH})

if(HOLO_BUILD_VERSION)
    set(${PROJECT_NAME}_VERSION_TWEAK)
    set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION}.${HOLO_BUILD_VERSION})
endif(HOLO_BUILD_VERSION)

# default options
option(HOLO_BUILD_TEST     "Build unit test"          OFF)
option(HOLO_BUILD_SHARED   "Build shared library"     ON)
option(HOLO_BUILD_COVERAGE "Generate coverage report" OFF)
option(HOLO_BUILD_DEPRECATED_TYPE "Build deprecated types" OFF)

# dependency configuration
set(HOLO_BASE_VERSION 0.9.0)
set(GTSAM_VERSION 4.0.0)
set(GTSAM_COMPONENTS gtsam gtsam_unstable)
set(OPENCV_VERSION 3.3.1)

# Set C/CXX compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_C_STANDARD 99)

# export target configuration
set(EXPORT_NAMESPACE holo_localization)

## -------------------------- CMAKE_SETUP ---------------------------------------

# Set CMake variable to build shared library or static library.
if(HOLO_BUILD_SHARED)
    set(BUILD_SHARED_LIBS ON)
else()
    set(BUILD_SHARED_LIBS OFF)
endif()

# Set CMake variable for additional .cmake file search path.
if(NOT HOLO_ROOT AND NOT DEFINED ENV{HOLO_ROOT})
    MESSAGE(FATAL_ERROR "Unable to set HOLO_ROOT. Please set HOLO_ROOT environment variable or HOLO_ROOT cmake commandline argument")
else()
    if(NOT HOLO_ROOT)
        set(HOLO_ROOT $ENV{HOLO_ROOT})
    endif()
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake/Modules")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
    include(HoloProjectConfiguration)
endif()

## ------------------------- DEPENDENCIES --------------------------------
find_package(holo_base ${HOLO_BASE_VERSION} REQUIRED)
find_package(GTSAM ${GTSAM_VERSION} REQUIRED COMPONENTS ${GTSAM_COMPONENTS})
find_package(OPENCV ${OPENCV_VERSION} REQUIRED)

## -------------------------holomacros------------------------------------
include(HoloMacros)

## ------------------------- DOXYGEN-------------------------------------
GENERATE_DOXYGEN(INPUT include src)

## ------------------------- COVERAGE -----------------------------------
if(HOLO_BUILD_COVERAGE)
    if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
        set(HOLO_BUILD_TEST ON)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -DNDEBUG --coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DNDEBUG --coverage")
        GENERATE_COVERAGE_REPORT(EXCLUDE_PATTERNS
            "${PROJECT_SOURCE_DIR}/test/*"
            )
    else()
        MESSAGE(FATAL_ERROR "Unable to generate coverage report! CMAKE_BUILD_TYPE is not DEBUG!")
    endif()
endif()

## -------------------------generated code------------------------------------

## ------------------------- holo_localization_base_sam library ------------------------------------
HOLO_COMPILE_LIB(${PROJECT_NAME}_sam
    SOURCES
    src/sam/factors/internal/camera_imu_extrinsic_factor_inl.cpp
    src/sam/factors/internal/gnss_position_velocity_factor_inl.cpp
    src/sam/factors/internal/imu_body_extrinsic_factor_inl.cpp
    src/sam/factors/internal/lane_factor_inl.cpp
    src/sam/factors/internal/line_projection_factor_inl.cpp
    src/sam/factors/internal/point2line_factor_inl.cpp
    src/sam/factors/internal/point2plane_factor_inl.cpp
    src/sam/factors/internal/point2point_factor_inl.cpp
    src/sam/factors/internal/pose_only_unit3_factor_inl.cpp
    src/sam/factors/internal/prior_rpy_factor_inl.cpp
    src/sam/factors/internal/projection_line_factor_inl.cpp
    src/sam/factors/internal/velocity_factor_inl.cpp
    src/sam/factors/internal/wheel_speed_factor_inl.cpp
    src/sam/vision/line/line_triangulation.cpp
    src/sam/vision/line/orthonormal_line.cpp
    src/sam/vision/line/plucker_line.cpp
    INCLUDES
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    LIBRARIES
    GTSAM::gtsam
    GTSAM::gtsam_unstable
    OPENCV::opencv
    holo_base::holo_base_numerics
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_sam)

set_target_properties(${PROJECT_NAME}_sam PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## ------------------------- holo_localization_base library ------------------------------------
set(DEPRECATED_SRC)
if(HOLO_BUILD_DEPRECATED_TYPE)
set(DEPRECATED_SRC
    src/backend/factors/camera_imu_extrinsic_factor.cpp
    src/backend/factors/gnss_position_velocity_factor.cpp
    src/backend/factors/imu_body_extrinsic_factor.cpp
    src/backend/factors/lane_factor.cpp
    src/backend/factors/prior_rpy_factor.cpp
    src/backend/factors/projection_line_factor.cpp
    src/backend/smoother.cpp
    src/backend/velocity_factor.cpp
    src/backend/wheel_speed_factor.cpp
    )
endif(HOLO_BUILD_DEPRECATED_TYPE)

HOLO_COMPILE_LIB(${PROJECT_NAME}
    SOURCES
    ${DEPRECATED_SRC}
    src/common/imu_preintegration.cpp
    src/common/localization_base.cpp
    src/common/measurements_manager_base.cpp
    src/common/navstate.cpp
    src/tools/pose_spline.cpp
    src/tools/source_checker.cpp
    src/tools/source_checker_helper.cpp
    src/tools/spline_fitting.cpp
    src/vision/common/image_undistorter.cpp
    src/vision/common/mask.cpp
    src/vision/common/mat.cpp
    src/vision/feature/fast.cpp
    src/vision/feature/feature2d.cpp
    src/vision/feature/gridding_feature_extractor.cpp
    INCLUDES
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    LIBRARIES
    OPENCV::opencv
    holo_base::holo_base_common
    holo_base::holo_base_filters
    holo_base::holo_base_geometry
    holo_base::holo_base_map
    holo_base::holo_base_numerics
    holo_base::holo_base_os
    ${PROJECT_NAME}_sam
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

#--------------------------- test ---------------------------------------
if(HOLO_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif(HOLO_BUILD_TEST)
add_subdirectory(unittest)

#--------------------------- config version -----------------------------
include(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake @ONLY)

INSTALL(FILES ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake 
    DESTINATION lib/cmake/${PROJECT_NAME})

# install include directories
INSTALL(DIRECTORY include/holo DESTINATION include/${PROJECT_NAME})

#--------------------------- uninstall command --------------------
add_custom_target(uninstall 
    COMMAND cat install_manifest.txt | xargs rm 
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Uninstall"
)

cmake_policy(POP)
