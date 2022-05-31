cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0074 NEW)

project(holo_sensors_cmw_app)

## --------------------------- CONFIGURATIONS --------------------------------
#Set project version
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 9)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR})
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_SOVERSION}.${${PROJECT_NAME}_VERSION_PATCH})

if(HOLO_BUILD_VERSION)
    set(${PROJECT_NAME}_VERSION_TWEAK)
    set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION}.${HOLO_BUILD_VERSION})
endif(HOLO_BUILD_VERSION)

set(PROJECT_VERSION ${${PROJECT_NAME}_VERSION})

# default options
option(HOLO_BUILD_TEST           "Build unit test"               OFF)
option(HOLO_CPU_PROFILE          "Use Google CPU Profiler"       OFF)
option(HOLO_BUILD_COVERAGE       "Generate coverage report"      OFF)
option(HOLO_BUILD_WITH_CUDA      "Build with cuda features"      OFF)

option(HOLO_BUILD_ON_ACU         "Build project on ACU"          OFF)
option(HOLO_BUILD_ON_MDC300      "Build project on MDC300"       OFF)
option(HOLO_BUILD_ON_MDC610      "Build project on MDC610"       OFF)
option(HOLO_BUILD_ON_TDA4        "Build project on TDA4"         OFF)
option(HOLO_BUILD_ON_QNX         "Build project on QNX"          OFF)

option(HOLO_BUILD_VEHICLE_AIONLX "Build aionlx vehicle proxy"    OFF)

option(HOLO_BUILD_OPENDDS_APP    "Build with opendds enabled"    ON)
option(HOLO_BUILD_ROS_APP        "Build with ros enabled"        ON)
option(HOLO_BUILD_UMB_APP        "Build with umb enabled"        ON)
option(HOLO_BUILD_DDS_MICRO_APP  "Build with dds micro enabled"  ON)
option(HOLO_BUILD_MDC_CM_APP     "Build with MDC_CM enabled"     ON)

MESSAGE(STATUS CMAKE_EXPORT_NO_PACKAGE_REGISTRY = ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY})
MESSAGE(STATUS HOLO_BUILD_PLATFORM = ${HOLO_BUILD_PLATFORM})
MESSAGE(STATUS HOLO_BUILD_PRODUCT = ${HOLO_BUILD_PRODUCT})

if (HOLO_BUILD_PLATFORM MATCHES "MDC610")
    set(HOLO_BUILD_ON_MDC610 ON)
    MESSAGE(STATUS "HOLO_BUILD_ON_MDC610 = ${HOLO_BUILD_ON_MDC610} (OVERRIDE)")
endif()

if (HOLO_BUILD_PLATFORM MATCHES "tda4")
    set(HOLO_BUILD_ON_TDA4 ON)
    MESSAGE(STATUS "HOLO_BUILD_ON_TDA4 = ${HOLO_BUILD_ON_TDA4} (OVERRIDE)")
endif()

if (HOLO_BUILD_PLATFORM MATCHES "qnx")
    set(HOLO_BUILD_ON_QNX ON)
    MESSAGE(STATUS "HOLO_BUILD_ON_QNX = ${HOLO_BUILD_ON_QNX} (OVERRIDE)")
endif()

if (HOLO_BUILD_PLATFORM MATCHES "mdc300")
    set(HOLO_BUILD_ON_MDC300 ON)
    MESSAGE(STATUS "HOLO_BUILD_ON_MDC300 = ${HOLO_BUILD_ON_MDC300} (OVERRIDE)")
endif()

MESSAGE(STATUS CMAKE_EXPORT_NO_PACKAGE_REGISTRY = ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY})
MESSAGE(STATUS HOLO_BUILD_PRODUCT = ${HOLO_BUILD_PRODUCT})
MESSAGE(STATUS HOLO_BUILD_TEST = ${HOLO_BUILD_TEST})
MESSAGE(STATUS HOLO_CPU_PROFILE = ${HOLO_CPU_PROFILE})
MESSAGE(STATUS HOLO_BUILD_COVERAGE = ${HOLO_BUILD_COVERAGE})
MESSAGE(STATUS HOLO_BUILD_WITH_CUDA = ${HOLO_BUILD_WITH_CUDA})
MESSAGE(STATUS HOLO_BUILD_ON_ACU = ${HOLO_BUILD_ON_ACU})
MESSAGE(STATUS HOLO_BUILD_ON_MDC300 = ${HOLO_BUILD_ON_MDC300})
MESSAGE(STATUS HOLO_BUILD_ON_MDC610 = ${HOLO_BUILD_ON_MDC610})
MESSAGE(STATUS HOLO_BUILD_ON_TDA4 = ${HOLO_BUILD_ON_TDA4})
MESSAGE(STATUS HOLO_BUILD_ON_QNX = ${HOLO_BUILD_ON_QNX})
MESSAGE(STATUS HOLO_BUILD_VEHICLE_AIONLX = ${HOLO_BUILD_VEHICLE_AIONLX})
MESSAGE(STATUS HOLO_BUILD_OPENDDS_APP = ${HOLO_BUILD_OPENDDS_APP})
MESSAGE(STATUS HOLO_BUILD_ROS_APP = ${HOLO_BUILD_ROS_APP})
MESSAGE(STATUS HOLO_BUILD_UMB_APP = ${HOLO_BUILD_UMB_APP})
MESSAGE(STATUS HOLO_BUILD_DDS_MICRO_APP = ${HOLO_BUILD_DDS_MICRO_APP})
MESSAGE(STATUS HOLO_BUILD_MDC_CM_APP = ${HOLO_BUILD_MDC_CM_APP})

if(${CMAKE_SYSTEM_NAME} STREQUAL "QNX")
    set(HOLO_BUILD_ON_QNX ON)
    MESSAGE(STATUS "QNX System detected, set HOLO_BUILD_ON_QNX to ${HOLO_BUILD_ON_QNX}")
endif()

if(HOLO_BUILD_ON_QNX)
    add_compile_definitions(DISABLE_V4L2_INTERFACE)
    MESSAGE(STATUS "QNX System detected, disable v4l2 interface")
endif()


if(HOLO_BUILD_ON_ACU)
    add_compile_definitions(NOVATEL_ON_ACU)
endif(HOLO_BUILD_ON_ACU)

# dependency configuration
set(DEPEND_HOLO_BASE_VERSION 0.0.0)
set(DEPEND_HOLO_SENSORS_BASE_VERSION 0.0.0)
set(DEPEND_HOLO_BASE_MSG_VERSION 0.0.0)
set(DEPEND_CMW_WRAPPER_VERSION 0.0.0)
set(DEPEND_GH02_MSG_VERSION 0.0.0)

# Set C/CXX compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-error=deprecated-declarations -fstack-protector-strong")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-error=deprecated-declarations -fstack-protector-strong")
set(CMAKE_C_STANDARD 99)
if(HOLO_BUILD_ON_MDC300 OR HOLO_BUILD_ON_MDC610)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
elseif(HOLO_BUILD_ON_TDA4)
set(TDA4_CMAKE_C_CXX_FLAGS "-fms-extensions -Wno-write-strings -Wno-format-security -fno-short-enums -mcpu=cortex-a72 -Wno-format-truncation -MMD")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TDA4_CMAKE_C_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${TDA4_CMAKE_C_CXX_FLAGS}")
endif()

MESSAGE(STATUS CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS})
MESSAGE(STATUS CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD})
MESSAGE(STATUS CMAKE_C_FLAGS = ${CMAKE_C_FLAGS})
MESSAGE(STATUS CMAKE_C_STANDARD = ${CMAKE_C_STANDARD})

## -------------------------- CMAKE_SETUP ------------------------------------

# Set CMake variable for additional .cmake file search path.
if(NOT HOLO_ROOT AND NOT DEFINED ENV{HOLO_ROOT})
    MESSAGE(FATAL_ERROR "Unable to set HOLO_ROOT. Please set HOLO_ROOT environment variable or HOLO_ROOT cmake commandline argument")
else()
    if(NOT HOLO_ROOT)
        set(HOLO_ROOT $ENV{HOLO_ROOT})
    endif()
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake/Modules")
    include(HoloProjectConfiguration)
endif()

set(TARGET_APP_TYPES)
foreach(APP_TYPE OPENDDS ROS UMB DDS_MICRO)
    if(HOLO_BUILD_${APP_TYPE}_APP)
        LIST(APPEND TARGET_APP_TYPES ${APP_TYPE})
    endif()
endforeach()
set(MDC_CM_APP_TYPES)
if(HOLO_BUILD_MDC_CM_APP)
    LIST(APPEND MDC_CM_APP_TYPES MDC_CM)
endif()
MESSAGE(STATUS "GENERATE APP TYPES = ${TARGET_APP_TYPES} ${MDC_CM_APP_TYPES}")

## -------------------------- DEPENDENCIES -----------------------------------
find_package(holo_base ${DEPEND_HOLO_BASE_VERSION} REQUIRED)
find_package(holo_sensors_base ${DEPEND_HOLO_SENSORS_BASE_VERSION} REQUIRED)
find_package(holo_base_msg ${DEPEND_HOLO_BASE_MSG_VERSION} REQUIRED)
find_package(cmw_wrapper ${DEPEND_CMW_WRAPPER_VERSION} QUIET)
find_package(gh02_msg ${DEPEND_GH02_MSG_VERSION} QUIET)

if (HOLO_BUILD_ON_MDC300)
    find_package(MDC_SDK REQUIRED)
    MESSAGE(STATUS MDC_SDK_INCLUDE_DIRS=${MDC_SDK_INCLUDE_DIRS})
    MESSAGE(STATUS MDC_SDK_LIBRARY_DIRS=${MDC_SDK_LIBRARY_DIRS})
    MESSAGE(STATUS SDK_LIB=${SDK_LIB})
endif()

if (HOLO_BUILD_ON_TDA4)
    find_package(TI_PSDK REQUIRED)
    if (HOLO_BUILD_WITH_CUDA)
        SET(HOLO_BUILD_WITH_CUDA OFF)
        MESSAGE("disable CUDA for the target platform is TDA4")
    endif(HOLO_BUILD_WITH_CUDA)
endif(HOLO_BUILD_ON_TDA4)

if(HOLO_BUILD_WITH_CUDA)
    add_compile_definitions(HOLO_CAMERA_USE_CUDA)
    SET(TEGRA_MEDIA_PATH "")
    if(EXISTS ${CMAKE_SYSROOT}/usr/src/tegra_multimedia_api)
        SET(TEGRA_MEDIA_PATH ${CMAKE_SYSROOT}/usr/src/tegra_multimedia_api)
    elseif(EXISTS ${CMAKE_SYSROOT}/home/nvidia/tegra_multimedia_api)
        SET(TEGRA_MEDIA_PATH ${CMAKE_SYSROOT}/home/nvidia/tegra_multimedia_api)
    elseif(EXISTS ${CMAKE_SYSROOT}/home/nvidia/jetson_multimedia_api)
        SET(TEGRA_MEDIA_PATH ${CMAKE_SYSROOT}/home/nvidia/jetson_multimedia_api)
    elseif(EXISTS ${CMAKE_SYSROOT}/usr/src/jetson_multimedia_api)
        SET(TEGRA_MEDIA_PATH ${CMAKE_SYSROOT}/usr/src/jetson_multimedia_api)
    endif()
    MESSAGE(TEGRA_MEDIA_PATH=${TEGRA_MEDIA_PATH})
    if(NOT (TEGRA_MEDIA_PATH STREQUAL ""))
        add_compile_definitions(HOLO_CAMERA_USE_TEGRA_MMA)
    endif()
endif(HOLO_BUILD_WITH_CUDA)

## -------------------------holomacros----------------------------------------
include(HoloMacros)

## ------------------------- DOXYGEN------------------------------------------
GENERATE_DOXYGEN(INPUT include src doc)

## ------------------------- COVERAGE ----------------------------------------
if(HOLO_BUILD_COVERAGE)
    if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
        set(HOLO_BUILD_TEST ON)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -DNDEBUG --coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DNDEBUG --coverage")
        GENERATE_COVERAGE_REPORT(EXCLUDE_PATTERNS
            "${PROJECT_BINARY_DIR}/src/*"
            "${PROJECT_SOURCE_DIR}/test/*"
        )
    else()
        MESSAGE(FATAL_ERROR "Unable to generate coverage report! CMAKE_BUILD_TYPE is not DEBUG!")
    endif()
endif()

## -------------------------generated code------------------------------------

## ----------------------------libraries--------------------------------------

## ------------------------- general application -----------------------------
set(HOLO_CMW_MSG_MDC_CM)
set(HOLO_CMW_MSG_LIBRARIES)
MESSAGE(STATUS "holo_base_msg_FOUND = ${holo_base_msg_FOUND}")
MESSAGE(STATUS "gh02_msg_FOUND = ${gh02_msg_FOUND}")

if(TARGET_APP_TYPES AND holo_base_msg_FOUND)
    LIST(APPEND HOLO_CMW_MSG_LIBRARIES holo_base_msg::holo_base_msg)
endif()
if(MDC_CM_APP_TYPES AND gh02_msg_FOUND)
    LIST(APPEND HOLO_CMW_MSG_LIBRARIES gh02_msg::gh02_msg_mdc_cm)
endif()
MESSAGE(STATUS "HOLO_CMW_MSG_LIBRARIES = ${HOLO_CMW_MSG_LIBRARIES}")

## ------------------------- holo_cmw v2 application -------------------------
add_cmw_wrapper_executable(conti_radar_cmw
    SOURCES     src/conti_radar/conti_radar_app.cpp
    INCLUDES    include
    LIBRARIES   ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_ars408
                holo_sensors_base::holo_sensors_base_interface
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
if(NOT HOLO_BUILD_ON_QNX)
add_cmw_wrapper_executable(image_capture_cmw
    SOURCES     src/camera/general/image_capture_app.cpp
    INCLUDES    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    LIBRARIES   holo_sensors_base::holo_sensors_base_camera
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_utils
                holo_sensors_base::holo_sensors_base_interface
                holo_sensors_base::holo_sensors_base_image_process
                holo_base::holo_base_os
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
    ${MDC_CM_APP_TYPES}
)
endif()
add_cmw_wrapper_executable(image_encoder_calibration_cmw
    SOURCES     src/camera/calibration_image_collection/image_encoder_calibration_app.cpp
    INCLUDES    include
    LIBRARIES   holo_sensors_base::holo_sensors_base_camera
                holo_sensors_base::holo_sensors_base_utils
                holo_sensors_base::holo_sensors_base_interface
                holo_sensors_base::holo_sensors_base_image_process
                ${HOLO_CMW_MSG_LIBRARIES}
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(image_decoder_cmw
    SOURCES     src/camera/general/image_decoder_app.cpp
    INCLUDES    include
    LIBRARIES   holo_sensors_base::holo_sensors_base_camera
                holo_sensors_base::holo_sensors_base_utils
                holo_sensors_base::holo_sensors_base_interface
                holo_sensors_base::holo_sensors_base_image_process
                ${HOLO_CMW_MSG_LIBRARIES}
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
    ${MDC_CM_APP_TYPES}
)
add_cmw_wrapper_executable(image_decoder_cmw_cli
    SOURCES     src/camera/general/image_decoder_cli_app.cpp
    INCLUDES    include
    LIBRARIES   holo_sensors_base::holo_sensors_base_camera
                holo_sensors_base::holo_sensors_base_utils
                holo_sensors_base::holo_sensors_base_interface
                holo_sensors_base::holo_sensors_base_image_process
                ${HOLO_CMW_MSG_LIBRARIES}
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
    ${MDC_CM_APP_TYPES}
)
add_cmw_wrapper_executable(imu_cmw
    SOURCES     src/imu/imu_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_aceinna
                holo_sensors_base::holo_sensors_base_interface
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(asensing_cmw
    SOURCES     src/asensing/asensing_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_asensing
                holo_sensors_base::holo_sensors_base_interface
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(novatel_cmw
    SOURCES     src/novatel/novatel_app.cpp
                src/utils/utils.cpp
    INCLUDES    include
    LIBRARIES   ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_novatel
                holo_sensors_base::holo_sensors_base_interface
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
    ${MDC_CM_APP_TYPES}
)
add_cmw_wrapper_executable(starneto_cmw
    SOURCES     src/gnss/starneto/starneto_app.cpp
    INCLUDES    include
    LIBRARIES   ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_starneto
                holo_sensors_base::holo_sensors_base_interface
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(smart_camera_cmw
    SOURCES     src/smart_camera/smart_camera_app.cpp
    INCLUDES    include
    LIBRARIES   ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_ifv300
                holo_sensors_base::holo_sensors_base_matrix2
                holo_sensors_base::holo_sensors_base_me3
                holo_sensors_base::holo_sensors_base_mpc2
                holo_sensors_base::holo_sensors_base_interface
                holo_sensors_base::holo_sensors_base_me8
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(ublox_cmw
    SOURCES     src/gnss/ublox/ublox_app.cpp
    INCLUDES    include
    LIBRARIES   ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_ublox
                holo_sensors_base::holo_sensors_base_interface
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(velodyne_cmw
    SOURCES     src/lidar/velodyne/velodyne_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_velodyne
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_interface
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(velodyne_converter_app
    SOURCES     src/lidar/velodyne/velodyne_converter_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_velodyne
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(pandar_cmw
    SOURCES     src/lidar/pandar/pandar_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pandar
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_interface
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(pandar_converter_cmw
    SOURCES     src/lidar/pandar/pandar_converter_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pandar
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(pandar128_cmw
    SOURCES     src/lidar/pandar128/pandar128_app.cpp
                src/utils/utils.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pandar128
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_interface
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(pandar128_converter_cmw
    SOURCES     src/lidar/pandar128/pandar128_converter_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pandar128
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(livox_cmw
    SOURCES     src/lidar/livox/livox_app.cpp
                src/utils/utils.cpp    
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_livox
                holo_sensors_base::holo_sensors_base_interface
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(livox_converter_cmw
    SOURCES     src/lidar/livox/livox_converter_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_livox
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(livox_hap_cmw
    SOURCES     src/lidar/livox/livox_hap_app.cpp
                src/utils/utils.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_livox_hap
                holo_sensors_base::holo_sensors_base_interface
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(rsm1_cmw
    SOURCES     src/lidar/rsm1/rsm1_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_rsm1
                holo_sensors_base::holo_sensors_base_interface
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
    ${MDC_CM_APP_TYPES}
)
add_cmw_wrapper_executable(rsm1_converter_cmw
    SOURCES     src/lidar/rsm1/rsm1_converter_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_rsm1
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(rsbpearl_cmw
    SOURCES     src/lidar/rsbpearl/rsbpearl_app.cpp
                src/utils/utils.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_rsbpearl
                holo_sensors_base::holo_sensors_base_interface
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(rsbpearl_converter_cmw
    SOURCES     src/lidar/rsbpearl/rsbpearl_converter_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_rsbpearl
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(rsruby_cmw
    SOURCES     src/lidar/rsruby/rsruby_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_rsruby
                holo_sensors_base::holo_sensors_base_interface
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
add_cmw_wrapper_executable(rsruby_converter_cmw
    SOURCES     src/lidar/rsruby/rsruby_converter_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_rsruby
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)

add_cmw_wrapper_executable(lidar_converter_cmw
    SOURCES     src/lidar/lidar_converter_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_lidar_scan
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
    ${MDC_CM_APP_TYPES}
)

if (HOLO_BUILD_ON_MDC610)
add_cmw_wrapper_executable(mdc610_lidar_cmw
    SOURCES     src/lidar/mdc610/mdc610_lidar_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_utils
                holo_sensors_base::holo_sensors_base_lidar_scan
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_interface
                LZ4::LZ4
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
    ${MDC_CM_APP_TYPES}
)

add_cmw_wrapper_executable(mdc610_lidar_converter
    SOURCES     src/lidar/mdc610/mdc610_lidar_converter_app.cpp
    INCLUDES    include
                include/holo/sensors/lidar/libply
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_lidar_scan
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
                holo_sensors_base::holo_sensors_base_utils
                LZ4::LZ4
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
    ${MDC_CM_APP_TYPES}
)
endif()

add_cmw_wrapper_executable(ouster_cmw
    SOURCES     src/lidar/ouster/ouster_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_sensors_base::holo_sensors_base_ouster
                holo_sensors_base::holo_sensors_base_interface
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ROS
)

add_cmw_wrapper_executable(ouster_converter_cmw
    SOURCES     src/lidar/ouster/ouster_converter_app.cpp
    INCLUDES    include
    LIBRARIES   holo_base::holo_base_os
                ${HOLO_CMW_MSG_LIBRARIES}
                holo_base_msg::holo_base_msg
                holo_sensors_base::holo_sensors_base_ouster
                holo_sensors_base::holo_sensors_base_pointcloud_ipc
    DEFINITIONS APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ROS
)

if (HOLO_BUILD_ON_TDA4)
add_cmw_wrapper_executable(tda4_image_capture_front
    SOURCES     src/camera/tda4/image_capture/app_capture_module.c
                src/camera/tda4/image_capture/app_img_mosaic_module.c
                src/camera/tda4/image_capture/app_sensor_module.c
                src/camera/tda4/image_capture/main.c
                src/camera/tda4/image_capture/main_hlos_arm.cpp
    INCLUDES    ${CMAKE_SOURCE_DIR}
                include
                include/camera/tda4/image_capture
                ${TI_PSDK_imaging_INCLUDE_DIRS}
                ${TI_PSDK_ivision_INCLUDE_DIRS}
                ${TI_PSDK_tiadalg_INCLUDE_DIRS}
                ${TI_PSDK_tidl_INCLUDE_DIRS}
                ${TI_PSDK_tiovx_INCLUDE_DIRS}
                ${TI_PSDK_vision_apps_INCLUDE_DIRS}
    LIBRARIES   TI_PSDK::psdk
                holo_sensors_base::holo_sensors_base_image_ipc
                holo_sensors_base::holo_sensors_base_camera
                holo_sensors_base::holo_sensors_base_image_process
    DEFINITIONS CUSTOM_KERNEL_PATH
                BUILD_TUTORIAL
                BUILD_CONFORMANCE_TEST
                LINUX
                J7
                A72=\"A72\"
                TARGET_NUM_CORES=1
                TARGET_ARCH=64
                ARCH_64
                ARM
                TARGET_BUILD=1
                NUM_CAPT_CHANNELS=1
                NUM_ENCODE_CHANNEL=1
                APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)

add_cmw_wrapper_executable(tda4_image_capture_360deg
    SOURCES     src/camera/tda4/image_capture/app_capture_module.c
                src/camera/tda4/image_capture/app_img_mosaic_module.c
                src/camera/tda4/image_capture/app_sensor_module.c
                src/camera/tda4/image_capture/main.c
                src/camera/tda4/image_capture/main_hlos_arm.cpp
    INCLUDES    ${CMAKE_SOURCE_DIR}
                include
                include/camera/tda4/image_capture
                ${TI_PSDK_imaging_INCLUDE_DIRS}
                ${TI_PSDK_ivision_INCLUDE_DIRS}
                ${TI_PSDK_tiadalg_INCLUDE_DIRS}
                ${TI_PSDK_tidl_INCLUDE_DIRS}
                ${TI_PSDK_tiovx_INCLUDE_DIRS}
                ${TI_PSDK_vision_apps_INCLUDE_DIRS}
    LIBRARIES   TI_PSDK::psdk
                holo_sensors_base::holo_sensors_base_image_ipc
                holo_sensors_base::holo_sensors_base_camera
                holo_sensors_base::holo_sensors_base_image_process
    DEFINITIONS CUSTOM_KERNEL_PATH
                BUILD_TUTORIAL
                BUILD_CONFORMANCE_TEST
                LINUX
                J7
                A72=\"A72\"
                TARGET_NUM_CORES=1
                TARGET_ARCH=64
                ARCH_64
                ARM
                TARGET_BUILD=1
                NUM_CAPT_CHANNELS=4
                NUM_ENCODE_CHANNEL=4
                APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)

add_cmw_wrapper_executable(tda4_image_capture_encoder_front
    SOURCES     src/camera/tda4/image_capture_encoder/app_capture_module.c
                src/camera/tda4/image_capture_encoder/app_encode_module.c
                src/camera/tda4/image_capture_encoder/app_img_convert.c
                src/camera/tda4/image_capture_encoder/app_img_mosaic_module.c
                src/camera/tda4/image_capture_encoder/app_sensor_module.c
                src/camera/tda4/image_capture_encoder/app_stream.c
                src/camera/tda4/image_capture_encoder/main_hlos_arm.cpp
    INCLUDES    ${CMAKE_SOURCE_DIR}
                include
                include/camera/tda4/image_capture_encoder
                ${TI_PSDK_imaging_INCLUDE_DIRS}
                ${TI_PSDK_ivision_INCLUDE_DIRS}
                ${TI_PSDK_tiadalg_INCLUDE_DIRS}
                ${TI_PSDK_tidl_INCLUDE_DIRS}
                ${TI_PSDK_tiovx_INCLUDE_DIRS}
                ${TI_PSDK_vision_apps_INCLUDE_DIRS}
    LIBRARIES   
                TI_PSDK::psdk
                holo_sensors_base::holo_sensors_base_image_ipc
                holo_sensors_base::holo_sensors_base_camera
                holo_sensors_base::holo_sensors_base_image_process
    DEFINITIONS 
                CUSTOM_KERNEL_PATH
                BUILD_TUTORIAL
                BUILD_CONFORMANCE_TEST
                LINUX
                J7
                A72=\"A72\"
                TARGET_NUM_CORES=1
                TARGET_ARCH=64
                ARCH_64
                ARM
                TARGET_BUILD=1
                NUM_CAPT_CHANNELS=1
                NUM_ENCODE_CHANNEL=1
                APP_MAIN_FUNCTION
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)

add_cmw_wrapper_executable(tda4_image_capture_encoder_360deg
    SOURCES     src/camera/tda4/image_capture_encoder/app_capture_module.c
                src/camera/tda4/image_capture_encoder/app_encode_module.c
                src/camera/tda4/image_capture_encoder/app_img_convert.c
                src/camera/tda4/image_capture_encoder/app_img_mosaic_module.c
                src/camera/tda4/image_capture_encoder/app_sensor_module.c
                src/camera/tda4/image_capture_encoder/app_stream.c
                src/camera/tda4/image_capture_encoder/main_hlos_arm.cpp
    INCLUDES    ${CMAKE_SOURCE_DIR}
                include
                include/camera/tda4/image_capture_encoder
                ${TI_PSDK_imaging_INCLUDE_DIRS}
                ${TI_PSDK_ivision_INCLUDE_DIRS}
                ${TI_PSDK_tiadalg_INCLUDE_DIRS}
                ${TI_PSDK_tidl_INCLUDE_DIRS}
                ${TI_PSDK_tiovx_INCLUDE_DIRS}
                ${TI_PSDK_vision_apps_INCLUDE_DIRS}
    LIBRARIES   
                TI_PSDK::psdk
                holo_sensors_base::holo_sensors_base_image_ipc
                holo_sensors_base::holo_sensors_base_camera
                holo_sensors_base::holo_sensors_base_image_process
    DEFINITIONS 
                CUSTOM_KERNEL_PATH
                BUILD_TUTORIAL
                BUILD_CONFORMANCE_TEST
                LINUX
                J7
                A72=\"A72\"
                TARGET_NUM_CORES=1
                TARGET_ARCH=64
                ARCH_64
                ARM
                TARGET_BUILD=1
                NUM_CAPT_CHANNELS=4
                NUM_ENCODE_CHANNEL=4
                APP_MAIN_FUNCTION                
    INSTALL_DIR bin
    ${TARGET_APP_TYPES}
)
endif()

# add_cmw_wrapper_executable(sensors_proxy_app
#     SOURCES     src/utils/utils.cpp
#                 src/novatel/novatel_app.cpp
#                 src/lidar/livox/livox_app.cpp
#                 src/lidar/livox/livox_hap_app.cpp
#                 src/lidar/pandar/pandar_app.cpp
#                 src/lidar/pandar128/pandar128_app.cpp
#                 src/lidar/rsruby/rsruby_app.cpp
#                 src/lidar/rsbpearl/rsbpearl_app.cpp
#                 src/camera/general/image_capture_app.cpp
#                 src/sensors_proxy/sensors_proxy_app.cpp
#                 src/sensors_proxy/sensor_proxy_start_up_sensors.cpp
#                 src/smart_camera/smart_camera_app.cpp
#                 src/conti_radar/conti_radar_app.cpp
#                 src/gnss/starneto/starneto_app.cpp
#                 src/lidar/ouster/ouster_app.cpp
#     INCLUDES    include
#                 $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
#                 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
#     LIBRARIES   holo_base::holo_base_os
#                 holo_base_msg::holo_base_msg
#                 holo_sensors_base::holo_sensors_base_novatel
#                 holo_sensors_base::holo_sensors_base_livox
#                 holo_sensors_base::holo_sensors_base_livox_hap
#                 holo_sensors_base::holo_sensors_base_pointcloud_ipc
#                 holo_sensors_base::holo_sensors_base_interface
#                 holo_sensors_base::holo_sensors_base_pandar
#                 holo_sensors_base::holo_sensors_base_pandar128
#                 holo_sensors_base::holo_sensors_base_rsbpearl
#                 holo_sensors_base::holo_sensors_base_rsruby
#                 holo_sensors_base::holo_sensors_base_image_ipc
#                 holo_sensors_base::holo_sensors_base_camera
#                 holo_sensors_base::holo_sensors_base_ouster
#                 holo_sensors_base::holo_sensors_base_starneto
#                 ${HOLO_CMW_MSG_LIBRARIES}
#                 holo_sensors_base::holo_sensors_base_utils
#                 holo_sensors_base::holo_sensors_base_ifv300
#                 holo_sensors_base::holo_sensors_base_matrix2
#                 holo_sensors_base::holo_sensors_base_me3
#                 holo_sensors_base::holo_sensors_base_mpc2
#                 holo_sensors_base::holo_sensors_base_ars408
#                 ${SYSTEM_LIBRARY_SOCKET}
#                 ${PLATFORM_DEPENDENT_LIBS}
#     INSTALL_DIR bin
#     ${TARGET_APP_TYPES}
#     ${MDC_CM_APP_TYPES}
# )

#--------------------------- test --------------------------------------------
if(HOLO_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif(HOLO_BUILD_TEST)

#--------------------------- uninstall command -------------------------------
add_custom_target(uninstall 
    COMMAND cat install_manifest.txt | xargs rm 
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Uninstall")

cmake_policy(POP)
