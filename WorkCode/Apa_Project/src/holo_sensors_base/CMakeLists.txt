cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0074 NEW)

project(holo_sensors_base)


## --------------------------- CONFIGURATIONS ----------------------------------------
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
option(HOLO_BUILD_TEST           "Build unit test"            OFF)
option(HOLO_CPU_PROFILE          "Use Google CPU Profiler"    OFF)
option(HOLO_BUILD_SHARED         "Build shared library"       ON)
option(HOLO_BUILD_COVERAGE       "Generate coverage report"   OFF)
option(HOLO_BUILD_ON_TDA4        "Build project on TDA4"      OFF)
option(HOLO_BUILD_ON_MDC300      "Build project on MDC300"    OFF)
option(HOLO_BUILD_ON_MDC610      "Build project on MDC610"    OFF)
option(HOLO_BUILD_WITH_CUDA      "Build with cuda features"   OFF)
option(HOLO_BUILD_VEHICLE_AIONLX "Build aionlx vehicle proxy" OFF)

MESSAGE(STATUS CMAKE_EXPORT_NO_PACKAGE_REGISTRY = ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY})
MESSAGE(STATUS HOLO_BUILD_PLATFORM = ${HOLO_BUILD_PLATFORM})
MESSAGE(STATUS HOLO_BUILD_PRODUCT = ${HOLO_BUILD_PRODUCT})

if (HOLO_BUILD_PLATFORM MATCHES "tda4")
    set(HOLO_BUILD_ON_TDA4 ON)
    MESSAGE(STATUS "HOLO_BUILD_ON_TDA4 = ${HOLO_BUILD_ON_TDA4} (OVERRIDE)")
endif()

if (HOLO_BUILD_PLATFORM MATCHES "MDC610")
    set(HOLO_BUILD_ON_MDC610 ON)
    MESSAGE(STATUS "HOLO_BUILD_ON_MDC610 = ${HOLO_BUILD_ON_MDC610} (OVERRIDE)")
    if (HOLO_BUILD_PLATFORM MATCHES "MDC610-1.0.012")
        add_compile_definitions(MDC610_VERSION_NUM=20210430)
        MESSAGE(STATUS "MDC610_VERSION_NUM = 20210430")
    elseif(HOLO_BUILD_PLATFORM MATCHES "MDC610-1.0.017")
        add_compile_definitions(MDC610_VERSION_NUM=20210830)
        MESSAGE(STATUS "MDC610_VERSION_NUM = 20210830")
    elseif(HOLO_BUILD_PLATFORM MATCHES "MDC610-1.0.019")
        add_compile_definitions(MDC610_VERSION_NUM=20211130)
        MESSAGE(STATUS "MDC610_VERSION_NUM = 20211130")
    elseif(HOLO_BUILD_PLATFORM MATCHES "MDC610-1.1.001")
        add_compile_definitions(MDC610_VERSION_NUM=20211231)
        MESSAGE(STATUS "MDC610_VERSION_NUM = 20211231")
    elseif(HOLO_BUILD_PLATFORM MATCHES "MDC610-1.1801.001")
        add_compile_definitions(MDC610_VERSION_NUM=20220228)
        MESSAGE(STATUS "MDC610_VERSION_NUM = 20220228")
    endif()
endif()

MESSAGE(STATUS CMAKE_EXPORT_NO_PACKAGE_REGISTRY = ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY})
MESSAGE(STATUS HOLO_BUILD_PRODUCT = ${HOLO_BUILD_PRODUCT})
MESSAGE(STATUS HOLO_BUILD_TEST = ${HOLO_BUILD_TEST})
MESSAGE(STATUS HOLO_CPU_PROFILE = ${HOLO_CPU_PROFILE})
MESSAGE(STATUS HOLO_BUILD_SHARED = ${HOLO_BUILD_SHARED})
MESSAGE(STATUS HOLO_BUILD_COVERAGE = ${HOLO_BUILD_COVERAGE})
MESSAGE(STATUS HOLO_BUILD_ON_TDA4 = ${HOLO_BUILD_ON_TDA4})
MESSAGE(STATUS HOLO_BUILD_ON_MDC610 = ${HOLO_BUILD_ON_MDC610})
MESSAGE(STATUS HOLO_BUILD_WITH_CUDA = ${HOLO_BUILD_WITH_CUDA})
MESSAGE(STATUS HOLO_BUILD_VEHICLE_AIONLX = ${HOLO_BUILD_VEHICLE_AIONLX})

set(SYSTEM_LIBRARY_RT "")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(SYSTEM_LIBRARY_RT "rt")
endif()

set(SYSTEM_LIBRARY_SOCKET "")
if(${CMAKE_SYSTEM_NAME} STREQUAL "QNX")
    set(HOLO_BUILD_ON_QNX ON)
    set(SYSTEM_LIBRARY_SOCKET socket)
    MESSAGE(STATUS "QNX System detected, set HOLO_BUILD_ON_QNX to ${HOLO_BUILD_ON_QNX}")
endif()

# dependency configuration
set(DEPEND_HOLO_BASE_VERSION 0.7.0)
set(DEPEND_HOLO_SENSORS_C_VERSION 0.1.0)
set(DEPEND_FFMPEG_VERSION 3.4.6)
set(DEPEND_FFMPEG_COMPONENTS avcodec avdevice avfilter avformat avutil swresample swscale)
set(DEPEND_X264_VERSION 0.157)
set(DEPEND_NANOPB_VERSION 0.3.9)
set(DEPEND_LZ4_VERSION 1.9.1)

# Set C/CXX compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-error=deprecated-declarations -fstack-protector-strong")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-error=deprecated-declarations -fstack-protector-strong")
set(CMAKE_C_STANDARD 99)
if(HOLO_BUILD_ON_MDC610)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
    set(CMAKE_CXX_STANDARD 14)
elseif(HOLO_BUILD_ON_TDA4)
    set(TDA4_CMAKE_C_CXX_FLAGS "-fms-extensions -Wno-write-strings -Wno-format-security -fno-short-enums -mcpu=cortex-a72 -Wno-format-truncation -MMD")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TDA4_CMAKE_C_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${TDA4_CMAKE_C_CXX_FLAGS}")
endif()

MESSAGE(STATUS CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS})
MESSAGE(STATUS CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD})
MESSAGE(STATUS CMAKE_C_FLAGS = ${CMAKE_C_FLAGS})
MESSAGE(STATUS CMAKE_C_STANDARD = ${CMAKE_C_STANDARD})

# export target configuration
set(EXPORT_NAMESPACE ${PROJECT_NAME})

## -------------------------- CMAKE_SETUP ---------------------------------------

# Set CMake variable to build shared library or static library.
if(HOLO_BUILD_SHARED)
    set(BUILD_SHARED_LIBS ON)
else()
    set(BUILD_SHARED_LIBS OFF)
endif()

# Set CMake variable for additional .cmake file search path.
if(NOT HOLO_ROOT AND NOT DEFINED ENV{HOLO_ROOT})
    MESSAGE(FATAL_ERROR "Unable to set HOLO_ROOT. Please set HOLO_ROOT environment variable or pass HOLO_ROOT as cmake parameter")
else()
    if(NOT HOLO_ROOT)
        set(HOLO_ROOT $ENV{HOLO_ROOT})
    endif()
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake/Modules")
    include(HoloProjectConfiguration)
endif()

## -------------------------- DEPENDENCIES --------------------------------------
find_package(holo_base ${DEPEND_HOLO_BASE_VERSION} REQUIRED)
find_package(holo_sensors_c ${DEPEND_HOLO_SENSORS_C_VERSION} REQUIRED)
find_package(nanopb ${DEPEND_NANOPB_VERSION} REQUIRED)
find_package(FFMPEG ${DEPEND_FFMPEG_VERSION} REQUIRED COMPONENTS ${DEPEND_FFMPEG_COMPONENTS})
find_package(X264 ${DEPEND_X264_VERSION} REQUIRED)
find_package(LZ4 ${DEPEND_LZ4_VERSION} REQUIRED)
find_package(LIBYUV REQUIRED)
find_package(holo_metadata_cpp REQUIRED)

if (HOLO_BUILD_ON_TDA4)
    find_package(TI_PSDK REQUIRED)
    if (HOLO_BUILD_WITH_CUDA)
        SET(HOLO_BUILD_WITH_CUDA OFF)
        MESSAGE("disable CUDA for platform TDA4")
    endif()
endif()
if (HOLO_BUILD_ON_MDC610)
    if (HOLO_BUILD_WITH_CUDA)
        SET(HOLO_BUILD_WITH_CUDA OFF)
        MESSAGE("disable CUDA for platform MDC610")
    endif()
endif()

if (HOLO_BUILD_ON_MDC610)
    add_compile_definitions(MDC_PRODUCTION_MDC610)
    add_compile_definitions(MDC_PRODUCTION_CORE)
    find_package(AscendCL REQUIRED)
    MESSAGE(STATUS AscendCL_INCLUDE_DIRS = ${AscendCL_INCLUDE_DIRS})
    MESSAGE(STATUS AscendCL_LIBRARIES = ${AscendCL_LIBRARIES})
    find_package(ADSF REQUIRED)
    MESSAGE(STATUS ADSF_INCLUDE_DIRS = ${ADSF_INCLUDE_DIRS})
    MESSAGE(STATUS ADSF_LIBRARIES = ${ADSF_LIBRARIES})
    find_package(ara-core REQUIRED)
    set(MDC610_SDK_LIBRARIES_DIR ${ara-core_CMAKE_DIR}/../../)
    MESSAGE(STATUS MDC610_SDK_LIBRARIES_DIR = ${MDC610_SDK_LIBRARIES_DIR})
    find_package(ara-com REQUIRED)
    set(ara-exec_DIR ${MDC610_SDK_LIBRARIES_DIR}/cmake/exec/)
    find_package(ara-exec REQUIRED)
    find_package(rtf-crc REQUIRED)
    find_package(rtf-e2e REQUIRED)
    find_package(rtf-e2exf REQUIRED)
    set(MDC610_SDK_INCLUDE_DIRS)
    LIST(APPEND MDC610_SDK_INCLUDE_DIRS ${ara-core_INCLUDE_DIRS})
    LIST(APPEND MDC610_SDK_INCLUDE_DIRS ${ara-com_INCLUDE_DIRS})
    LIST(APPEND MDC610_SDK_INCLUDE_DIRS ${ara-exec_INCLUDE_DIRS})
    LIST(APPEND MDC610_SDK_INCLUDE_DIRS ${rtf-crc_INCLUDE_DIRS})
    LIST(APPEND MDC610_SDK_INCLUDE_DIRS ${rtf-e2e_INCLUDE_DIRS})
    LIST(APPEND MDC610_SDK_INCLUDE_DIRS ${rtf-e2exf_INCLUDE_DIRS})
    MESSAGE(STATUS MDC610_SDK_INCLUDE_DIRS = ${MDC610_SDK_INCLUDE_DIRS})
    set(MDC610_SDK_LIBRARIES)
    LIST(APPEND MDC610_SDK_LIBRARIES ${ara-core_LIBRARIES})
    LIST(APPEND MDC610_SDK_LIBRARIES ${ara-com_LIBRARIES})
    LIST(APPEND MDC610_SDK_LIBRARIES ${ara-exec_LIBRARIES})
    LIST(APPEND MDC610_SDK_LIBRARIES ${rtf-crc_LIBRARIES})
    LIST(APPEND MDC610_SDK_LIBRARIES ${rtf-e2e_LIBRARIES})
    LIST(APPEND MDC610_SDK_LIBRARIES ${rtf-e2exf_LIBRARIES})
    MESSAGE(STATUS MDC610_SDK_LIBRARIES = ${MDC610_SDK_LIBRARIES})
endif()

if (HOLO_BUILD_WITH_CUDA)
    find_package(CUDA REQUIRED)
    MESSAGE(STATUS CUDA_VERSION=${CUDA_VERSION})
    MESSAGE(STATUS CUDA_TOOLKIT_ROOT_DIR=${CUDA_TOOLKIT_ROOT_DIR})
    MESSAGE(STATUS CUDA_SDK_ROOT_DIR=${CUDA_SDK_ROOT_DIR})
    MESSAGE(STATUS CUDA_INCLUDE_DIRS=${CUDA_INCLUDE_DIRS})
endif(HOLO_BUILD_WITH_CUDA)

## -------------------------holomacros------------------------------------
include(HoloMacros)

## ------------------------- DOXYGEN-------------------------------------
GENERATE_DOXYGEN(INPUT include src doc)

## ------------------------- COVERAGE -----------------------------------
if(HOLO_BUILD_COVERAGE)
    if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
        set(HOLO_BUILD_TEST ON)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -DNDEBUG --coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DNDEBUG --coverage")
        GENERATE_COVERAGE_REPORT(EXCLUDE_PATTERNS
            "${PROJECT_BINARY_DIR}/src/*"
            "${PROJECT_SOURCE_DIR}/test/*")
    else()
        MESSAGE(FATAL_ERROR "Unable to generate coverage report! CMAKE_BUILD_TYPE is not DEBUG!")
    endif()
endif()

## -------------------------generated code------------------------------------

## ------------------------- library -----------------------------------------
# --------------------------holo_sensors_utils--------------------------------
set (SOURCE_CPP_UTILS
    src/utils/sensors_utils.cpp
    src/utils/livox_crc.cpp
    src/format/holosync.cpp
    src/format/packed_data.cpp
    )
if (HOLO_BUILD_ON_MDC610)
    set (SOURCE_CPP_UTILS
        ${SOURCE_CPP_UTILS}
        src/utils/mdc610_utils.cpp
        )
endif()
set (LIBRARIES_UTILS
    holo_base::holo_base_common
    holo_base::holo_base_os
    )
if (HOLO_BUILD_ON_MDC610)
    set (LIBRARIES_UTILS
        ${LIBRARIES_UTILS}
        AscendCL::AscendCL
        ADSF::ADSF
        rm
        )
endif(HOLO_BUILD_ON_MDC610)
HOLO_COMPILE_LIB(${PROJECT_NAME}_utils
    SOURCES
    ${SOURCE_CPP_UTILS}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    ${LIBRARIES_UTILS}
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_utils)
set_target_properties(${PROJECT_NAME}_utils PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )

# --------------------------lidar_utils--------------------------------
set (SOURCE_LIDAR_UTILS_CPP
    src/utils/lidar_utils.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_lidar_utils
    SOURCES
    ${SOURCE_LIDAR_UTILS_CPP}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    LZ4::LZ4
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_lidar_utils)
set_target_properties(${PROJECT_NAME}_lidar_utils PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
## ---------------------holo_sensors_base_image_process----------------------------
HOLO_COMPILE_LIB(${PROJECT_NAME}_image_process
    SOURCES
    src/image/convert/image_color_convert_libyuv.cpp
    src/image/convert/image_color_convert_opencv.cpp
    src/image/resize/image_resize.cpp
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_os
    LIBYUV::LIBYUV
    ${PROJECT_NAME}_utils
    ${SYSTEM_LIBRARY_RT}
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_image_process)
set_target_properties(${PROJECT_NAME}_image_process PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
# ------------------------------interface-------------------------------------
set(SENSOR_INTERFACE_SOURCES)
set(SENSOR_INTERFACE_INCLUDES)
set(SENSOR_INTERFACE_LIBRARIES)
## socket
LIST (APPEND SENSOR_INTERFACE_SOURCES
    src/interface/holo_socket/tcp_client.cpp
    src/interface/holo_socket/udp_client.cpp
    src/interface/holo_socket/udp_server.cpp
    src/interface/holo_socket/socket_can.cpp
    src/interface/socket_can_interface.cpp
    )
LIST(APPEND SENSOR_INTERFACE_LIBRARIES
    ${PROJECT_NAME}_utils
    ${SYSTEM_LIBRARY_SOCKET}
    )
## others
if (HOLO_BUILD_ON_MDC300)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}:${MDC_SDK_LIBRARY_DIRS}")
    MESSAGE(STATUS CMAKE_EXE_LINKER_FLAGS=${CMAKE_EXE_LINKER_FLAGS})
    LINK_DIRECTORIES(${MDC_SDK_LIBRARY_DIRS})
    add_compile_definitions(ENABLE_MDC300_CAN_INTERFACE)
    LIST (APPEND SENSOR_INTERFACE_SOURCES
        src/interface/mdc300/generated/canrxserviceinterface_common.cpp
        src/interface/mdc300/generated/cantxserviceinterface_common.cpp
        src/interface/mdc300_can_interface.cpp
        )
    LIST (APPEND SENSOR_INTERFACE_INCLUDES
        ${MDC_SDK_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/holo/sensors/interface/mdc300/generated/includes>
        )
    LIST(APPEND SENSOR_INTERFACE_LIBRARIES
        ${PROJECT_NAME}_utils
        ${SDK_LIB}
        )
elseif (HOLO_BUILD_ON_MDC610)
    add_compile_definitions(HOLO_PLATFORM_MDC610)
    LINK_DIRECTORIES(${MDC610_SDK_LIBRARIES_DIR}/mdc/base-plat/)
    # ---- mdc610 camera interface ----
    add_compile_definitions(ENABLE_MDC610_CAMERA_INTERFACE)
    LIST (APPEND SENSOR_INTERFACE_SOURCES
        src/interface/mdc610/generated/src/ara/camera_a_cm_receive/camera_a_cm_receive_loggingBehavior.cpp
        src/interface/mdc610/generated/src/mdc/cam/camera/cameradecodedmbufserviceinterface_common.cpp
        src/interface/mdc610/generated/src/mdc/cam/camera/cameraencodedmbufserviceinterface_common.cpp
        src/interface/mdc610_camera_interface.cpp
        )
    LIST (APPEND SENSOR_INTERFACE_INCLUDES
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/holo/sensors/interface/mdc610/generated/includes>
        )
    LIST(APPEND SENSOR_INTERFACE_LIBRARIES
        ascend_hal
        ADSF::ADSF
        ${MDC610_SDK_LIBRARIES}
        )
    # ---- mdc610 lidar interface ----
    add_compile_definitions(ENABLE_MDC610_LIDAR_INTERFACE)
    LIST (APPEND SENSOR_INTERFACE_SOURCES
        src/interface/mdc610_lidar_interface.cpp
    )
    LIST (APPEND SENSOR_INTERFACE_INCLUDES
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/holo/sensors/interface/mdc610/generated/includes>
    )
    LIST(APPEND SENSOR_INTERFACE_LIBRARIES
        ascend_hal
        ADSF::ADSF
        ${MDC610_SDK_LIBRARIES}
    )
    # ---- mdc610 cm files ----
    INSTALL(DIRECTORY 3rdparty/mdc610/ DESTINATION etc)
endif()
if (SENSOR_INTERFACE_SOURCES)
    HOLO_COMPILE_LIB(${PROJECT_NAME}_interface
        SOURCES
        ${SENSOR_INTERFACE_SOURCES}
        INCLUDES
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        ${SENSOR_INTERFACE_INCLUDES}
        LIBRARIES
        ${PROJECT_NAME}_utils
        ${SENSOR_INTERFACE_LIBRARIES}
        INSTALL_DIR lib
        NAMESPACE ${EXPORT_NAMESPACE}::
        )
    set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_interface)
    set_target_properties(${PROJECT_NAME}_interface PROPERTIES
        VERSION ${${PROJECT_NAME}_VERSION}
        SOVERSION ${${PROJECT_NAME}_SOVERSION}
        )
endif()

# -------------------------holo_sensors_aceinna-------------------------------
set (SOURCE_CPP_ACEINNA
    src/imu/aceinna/aceinna_holocan.cpp
    src/imu/aceinna/aceinna_someip.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_aceinna
    SOURCES
    ${SOURCE_CPP_ACEINNA}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_sensors_c::holo_sensors_c
    ${PROJECT_NAME}_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_aceinna)
set_target_properties(${PROJECT_NAME}_aceinna PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
# -------------------------holo_sensors_asensing-------------------------------
set (SOURCE_CPP_ASENSING
    src/asensing/asensing_holocan.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_asensing
    SOURCES
    ${SOURCE_CPP_ASENSING}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_sensors_c::holo_sensors_c
    ${PROJECT_NAME}_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_asensing)
set_target_properties(${PROJECT_NAME}_asensing PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
## ---------------------holo_sensors_base_image_ipc----------------------------
HOLO_COMPILE_LIB(${PROJECT_NAME}_image_ipc
    SOURCES
    src/camera/image_ipc.cpp
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_os
    ${PROJECT_NAME}_utils
    ${SYSTEM_LIBRARY_RT}
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_image_ipc)
set_target_properties(${PROJECT_NAME}_image_ipc PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
## -------------------------holo_sensors_camera--------------------------------
set(CAMERA_SOURCES_LIST)
set(CAMERA_SUPPORT_LIBRARIES)
set(CAMERA_SUPPORT_DEFINITIONS)
set(CAMERA_SOURCES_LIST
    src/camera/capture/image_capture.cpp
    src/camera/capture/image_capture_raw.cpp
    src/camera/capture/image_capture_rgb.cpp
    src/camera/capture/image_converter.cpp
    src/camera/capture/image_timestamper.cpp
    src/camera/encoder/image_encoder_base.cpp
    src/camera/encoder/image_encoder_h26x.cpp
    src/camera/decoder/image_decoder_h26x.cpp
    src/camera/decoder/image_decoder_base.cpp
    src/camera/bayer_convert.cpp
    src/camera/utils/image_convert.cpp
    src/camera/utils/h26x_utils.cpp
    )
SET(CAMERA_SUPPORT_LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_os
    ${PROJECT_NAME}_utils
    ${PROJECT_NAME}_image_ipc
    FFMPEG::avcodec
    FFMPEG::avformat
    FFMPEG::swscale
    LIBYUV::LIBYUV
    )
if (HOLO_BUILD_ON_TDA4)
    set(CAMERA_SOURCES_LIST
        ${CAMERA_SOURCES_LIST}
        src/camera/decoder/image_decoder_tda4.cpp
        src/camera/encoder/image_encoder_tda4.cpp
        src/camera/encoder/image_sync_encoder_tda4.cpp
        src/camera/decoder/image_sync_decoder_tda4.cpp
        src/camera/encoder/image_resize_encoder_tda4.cpp
        src/camera/decoder/image_resize_decoder_tda4.cpp
        src/camera/encoder/tda4_encode_vx_context.cpp
        src/camera/decoder/tda4_decode_vx_context.cpp
        src/camera/encoder/image_foresight_encode.cpp
        src/camera/decoder/image_foresight_decode.cpp
        src/camera/encoder/image_panoramic_encode.cpp
        src/camera/decoder/image_panoramic_decode.cpp
        )
    MESSAGE(CAMERA_SOURCES_LIST=${CAMERA_SOURCES_LIST})
    set(CAMERA_SUPPORT_LIBRARIES
        ${CAMERA_SUPPORT_LIBRARIES}
        TI_PSDK::psdk
        LIBYUV::LIBYUV
        )
    MESSAGE(CAMERA_SUPPORT_LIBRARIES=${CAMERA_SUPPORT_LIBRARIES})
    set(CAMERA_SUPPORT_DEFINITIONS
        ${CAMERA_SUPPORT_DEFINITIONS}
        HOLO_PLATFORM_TDA4
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
        )
    MESSAGE(CAMERA_SUPPORT_DEFINITIONS=${CAMERA_SUPPORT_DEFINITIONS})
endif(HOLO_BUILD_ON_TDA4)
if (HOLO_BUILD_ON_MDC610)
    set(CAMERA_SOURCES_LIST
        ${CAMERA_SOURCES_LIST}
        src/camera/encoder/image_encoder_mdc610.cpp
        src/camera/decoder/image_decoder_mdc610.cpp
        )
    MESSAGE(CAMERA_SOURCES_LIST=${CAMERA_SOURCES_LIST})
    set(CAMERA_SUPPORT_LIBRARIES
        ${CAMERA_SUPPORT_LIBRARIES}
        AscendCL::AscendCL
        ADSF::ADSF
        )
    MESSAGE(CAMERA_SUPPORT_LIBRARIES=${CAMERA_SUPPORT_LIBRARIES})
endif()
if(HOLO_BUILD_WITH_CUDA)
    cuda_include_directories(
        ${PROJECT_SOURCE_DIR}/include()
        )
    cuda_compile(${PROJECT_NAME}_camera_gpu SHARED
        src/camera/image_gpu.cu
        )
    LIST(APPEND CAMERA_SOURCES_LIST ${${PROJECT_NAME}_camera_gpu})
    LIST(APPEND CAMERA_SUPPORT_LIBRARIES ${CUDA_LIBRARIES})

    SET(TEGRA_MEDIA_PATH "")
    SET(TEGRA_INCLUDE "")

    if(EXISTS ${CMAKE_SYSROOT}/usr/src/tegra_multimedia_api)
        SET(TEGRA_MEDIA_PATH ${CMAKE_SYSROOT}/usr/src/tegra_multimedia_api)
    elseif(EXISTS ${CMAKE_SYSROOT}/home/nvidia/tegra_multimedia_api)
        SET(TEGRA_MEDIA_PATH ${CMAKE_SYSROOT}/home/nvidia/tegra_multimedia_api)
    elseif(EXISTS ${CMAKE_SYSROOT}/usr/src/jetson_multimedia_api)
        SET(TEGRA_MEDIA_PATH ${CMAKE_SYSROOT}/usr/src/jetson_multimedia_api)
    elseif(EXISTS ${CMAKE_SYSROOT}/home/nvidia/jetson_multimedia_api)
        SET(TEGRA_MEDIA_PATH ${CMAKE_SYSROOT}/home/nvidia/jetson_multimedia_api)
    endif()
    MESSAGE(TEGRA_MEDIA_PATH=${TEGRA_MEDIA_PATH})

    SET(TEGRA_SRC_FILES "")
    if(NOT (TEGRA_MEDIA_PATH STREQUAL ""))
        LIST(APPEND CAMERA_SOURCES_LIST src/camera/encoder/image_encoder_xavier.cpp)
        LIST(APPEND TEGRA_INCLUDE ${TEGRA_MEDIA_PATH}/include)
        LIST(APPEND TEGRA_INCLUDE ${TEGRA_MEDIA_PATH}/samples/common/classes)
        LIST(APPEND TEGRA_INCLUDE ${TEGRA_MEDIA_PATH}/samples/common/algorithm/cuda)
        LIST(APPEND TEGRA_INCLUDE ${TEGRA_MEDIA_PATH}/samples/common/algorithm/trt)
        LIST(APPEND TEGRA_INCLUDE ${CMAKE_SYSROOT}/usr/include/libdrm)
        MESSAGE(TEGRA_INCLUDE = ${TEGRA_INCLUDE})
        FILE(GLOB_RECURSE TEGRA_CU_FILES ${TEGRA_MEDIA_PATH}/samples/common/algorithm/cuda/*.cu)
        cuda_compile(holo_sensors_camera_tegra_gpu
            ${TEGRA_CU_FILES}
            SHARED
            )
        LIST(APPEND CAMERA_SOURCES_LIST ${holo_sensors_camera_tegra_gpu})
        LIST(APPEND TEGRA_SRC_FILES
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvBuffer.cpp
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvElement.cpp
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvLogging.cpp
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvUtils.cpp
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvVideoEncoder.cpp
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvDrmRenderer.cpp
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvEglRenderer.cpp
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvElementProfiler.cpp
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvV4l2Element.cpp
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvVideoConverter.cpp
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvVideoDecoder.cpp
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvVideoEncoder.cpp
            ${TEGRA_MEDIA_PATH}/samples/common/classes/NvV4l2ElementPlane.cpp)
        LIST(APPEND TEGRA_SRC_FILES ${TEGRA_MEDIA_PATH}/samples/common/algorithm/cuda/NvCudaProc.cpp)
        # LIST(APPEND TEGRA_SRC_FILES ${TEGRA_MEDIA_PATH}/samples/common/algorithm/trt/trt_inference.cpp)
        SET_PROPERTY(SOURCE ${TEGRA_SRC_FILES} PROPERTY COMPILE_FLAGS "-Wno-error=unused-parameter -Wno-error=missing-field-initializers")
        LIST(APPEND CAMERA_SUPPORT_LIBRARIES -ldrm -lv4l2 -lEGL -lGLESv2 -lX11 nvbuf_utils -lnvinfer -lnvparsers -lnvosd  -lcuda -lcudart)

        add_compile_definitions(HOLO_CAMERA_USE_TEGRA_MMA)
    endif()
    message(CAMERA_SUPPORT_LIBRARIES=${CAMERA_SUPPORT_LIBRARIES})
    message(CMAKE_SYSROOT=${CMAKE_SYSROOT})
    message(CMAKE_CURRENT_LIST_DIR=${CMAKE_CURRENT_LIST_DIR})
    HOLO_COMPILE_LIB(${PROJECT_NAME}_camera
        SOURCES
        ${CAMERA_SOURCES_LIST}
        ${TEGRA_SRC_FILES}
        INCLUDES
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        ${TEGRA_INCLUDE}
        ${CUDA_INCLUDE_DIRS}
        LIBRARIES
        ${CAMERA_SUPPORT_LIBRARIES}
        DEFINITIONS
        HOLO_CAMERA_USE_CUDA
        ${CAMERA_SUPPORT_DEFINITIONS}
        INSTALL_DIR lib
        NAMESPACE ${EXPORT_NAMESPACE}::
        )
    target_link_directories(
        ${PROJECT_NAME}_camera
        PUBLIC
        "${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/tegra"
        "${CUDA_TOOLKIT_ROOT_DIR}/targets/aarch64-linux/lib"
        )
    set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_camera)
    set_target_properties(${PROJECT_NAME}_camera PROPERTIES
        VERSION ${${PROJECT_NAME}_VERSION}
        SOVERSION ${${PROJECT_NAME}_SOVERSION}
        )
else()
    HOLO_COMPILE_LIB(${PROJECT_NAME}_camera
        SOURCES
        ${CAMERA_SOURCES_LIST}
        INCLUDES
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        LIBRARIES
        ${CAMERA_SUPPORT_LIBRARIES}
        DEFINITIONS
        ${CAMERA_SUPPORT_DEFINITIONS}
        INSTALL_DIR lib
        NAMESPACE ${EXPORT_NAMESPACE}::
        )
    set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_camera)
    set_target_properties(${PROJECT_NAME}_camera PROPERTIES
        VERSION ${${PROJECT_NAME}_VERSION}
        SOVERSION ${${PROJECT_NAME}_SOVERSION}
        )
endif(HOLO_BUILD_WITH_CUDA)
#-------------------------holo_sensors_radar_ars408---------------------------
set (SOURCE_CPP_ARS408
    src/radar/ars408/structure/ars408_obstacle.cpp
    src/radar/ars408/ars408_holocan.cpp
    src/radar/ars408/ars408_someip.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_ars408
    SOURCES
    ${SOURCE_CPP_ARS408}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_base::holo_base_obstacle
    holo_sensors_c::holo_sensors_c
    ${PROJECT_NAME}_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_ars408)
set_target_properties(${PROJECT_NAME}_ars408 PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
## -------------------------holo_sensors_mpc2--------------------------
set (SOURCE_CPP_MPC2
    src/smart_camera/mpc2/structure/mpc2_laneboundary.cpp
    src/smart_camera/mpc2/structure/mpc2_obstacle.cpp
    src/smart_camera/mpc2/holocan/mpc2_holocan.cpp
    src/smart_camera/mpc2/holocan/mpc2_holocan_laneboundary.cpp
    src/smart_camera/mpc2/holocan/mpc2_holocan_obstacle.cpp
    src/smart_camera/mpc2/holocan/mpc2_holocan_spd_limit_sign.cpp
    src/smart_camera/mpc2/someip/mpc2_someip.cpp
    src/smart_camera/mpc2/someip/mpc2_someip_laneboundary.cpp
    src/smart_camera/mpc2/someip/mpc2_someip_obstacle.cpp
    src/smart_camera/mpc2/mpc2.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_mpc2
    SOURCES
    ${SOURCE_CPP_MPC2}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_base::holo_base_numerics
    holo_base::holo_base_obstacle
    holo_sensors_c::holo_sensors_c
    ${PROJECT_NAME}_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_mpc2)
set_target_properties(${PROJECT_NAME}_mpc2 PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
## -------------------------holo_sensors_matrix2-----------------------
set (SOURCE_CPP_MATRIX2
    src/smart_camera/matrix2/structure/matrix2_laneboundary.cpp
    src/smart_camera/matrix2/structure/matrix2_obstacle.cpp
    src/smart_camera/matrix2/holocan/matrix2_holocan.cpp
    src/smart_camera/matrix2/holocan/matrix2_holocan_laneboundary.cpp
    src/smart_camera/matrix2/holocan/matrix2_holocan_obstacle.cpp
    src/smart_camera/matrix2/matrix2.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_matrix2
    SOURCES
    ${SOURCE_CPP_MATRIX2}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_base::holo_base_numerics
    holo_base::holo_base_obstacle
    holo_sensors_c::holo_sensors_c
    ${PROJECT_NAME}_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_matrix2)
set_target_properties(${PROJECT_NAME}_matrix2 PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
## -------------------------holo_sensors_ifv300--------------------------------
set (SOURCE_CPP_IFV300
    src/smart_camera/ifv300/structure/ifv300_laneboundary.cpp
    src/smart_camera/ifv300/structure/ifv300_obstacle.cpp
    src/smart_camera/ifv300/holocan/ifv300_holocan.cpp
    src/smart_camera/ifv300/holocan/ifv300_holocan_laneboundary.cpp
    src/smart_camera/ifv300/holocan/ifv300_holocan_obstacle.cpp
    src/smart_camera/ifv300/someip/ifv300_someip.cpp
    src/smart_camera/ifv300/someip/ifv300_someip_laneboundary.cpp
    src/smart_camera/ifv300/someip/ifv300_someip_obstacle.cpp
    src/smart_camera/ifv300/ifv300.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_ifv300
    SOURCES
    ${SOURCE_CPP_IFV300}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_base::holo_base_numerics
    holo_base::holo_base_obstacle
    holo_sensors_c::holo_sensors_c
    ${PROJECT_NAME}_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_ifv300)
set_target_properties(${PROJECT_NAME}_ifv300 PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
## -------------------------holo_sensors_me8--------------------------------
set (SOURCE_CPP_ME8
    src/smart_camera/me8/structure/me8_laneboundary.cpp
    src/smart_camera/me8/structure/me8_obstacle.cpp
    src/smart_camera/me8/holocan/me8_holocan.cpp
    src/smart_camera/me8/holocan/me8_holocan_laneboundary.cpp
    src/smart_camera/me8/holocan/me8_holocan_obstacle.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_me8
    SOURCES
    ${SOURCE_CPP_ME8}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_base::holo_base_numerics
    holo_base::holo_base_obstacle
    holo_sensors_c::holo_sensors_c
    ${PROJECT_NAME}_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_me8)
set_target_properties(${PROJECT_NAME}_me8 PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
## -------------------------holo_sensors_mobileye------------------------------
set (SOURCE_CPP_ME3
    src/smart_camera/me3/structure/me3_laneboundary.cpp
    src/smart_camera/me3/structure/me3_obstacle.cpp
    src/smart_camera/me3/holocan/me3_holocan.cpp
    src/smart_camera/me3/holocan/me3_holocan_laneboundary.cpp
    src/smart_camera/me3/holocan/me3_holocan_obstacle.cpp
    src/smart_camera/me3/someip/me3_someip.cpp
    src/smart_camera/me3/someip/me3_someip_laneboundary.cpp
    src/smart_camera/me3/someip/me3_someip_obstacle.cpp
    src/smart_camera/me3/me3.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_me3
    SOURCES
    ${SOURCE_CPP_ME3}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_base::holo_base_numerics
    holo_base::holo_base_obstacle
    holo_sensors_c::holo_sensors_c
    ${PROJECT_NAME}_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_me3)
set_target_properties(${PROJECT_NAME}_me3 PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
## -------------------------holo_sensors_novatel------------------------------
set (SOURCE_CPP_NOVATEL
    src/novatel/novatel.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_novatel
    SOURCES
    ${SOURCE_CPP_NOVATEL}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_base::holo_base_os
    ${PROJECT_NAME}_utils
    holo_sensors_c::holo_sensors_c
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_novatel)
set_target_properties(${PROJECT_NAME}_novatel PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
## -------------------------holo_sensors_starneto------------------------------
set (SOURCE_CPP_STARNETO
    src/gnss/starneto/starneto.cpp
)
HOLO_COMPILE_LIB(${PROJECT_NAME}_starneto
    SOURCES
    ${SOURCE_CPP_STARNETO}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_base::holo_base_os
    ${PROJECT_NAME}_utils
    holo_sensors_c::holo_sensors_c
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_starneto)
set_target_properties(${PROJECT_NAME}_starneto PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
## ---------------------holo_sensors_base_pointcloud_ipc----------------------------
HOLO_COMPILE_LIB(${PROJECT_NAME}_pointcloud_ipc
    SOURCES
    src/lidar/pointcloud_ipc.cpp
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_os
    ${PROJECT_NAME}_utils
    ${SYSTEM_LIBRARY_RT}
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_pointcloud_ipc)
set_target_properties(${PROJECT_NAME}_pointcloud_ipc PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )

# --------------------------lidar_scan--------------------------------
set (SOURCE_LIDAR_SCAN_CPP
    src/lidar/livox/livox_converter.cpp
    src/lidar/pandar/pandar_converter.cpp
    src/lidar/pandar128/pandar128_converter.cpp
	src/lidar/mdc610/mdc610_lidar_converter.cpp
    src/lidar/rsm1/rsm1_converter.cpp
    src/lidar/rsbpearl/rsbpearl_converter.cpp
    src/lidar/rsruby/rsruby_converter.cpp
    src/lidar/velodyne/velodyne_converter.cpp
    src/format/lidar_scan.cpp
    src/lidar/ouster/ouster_converter.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_lidar_scan
    SOURCES
    ${SOURCE_LIDAR_SCAN_CPP}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    ${PROJECT_NAME}_lidar_utils
    ${PROJECT_NAME}_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_lidar_scan)
set_target_properties(${PROJECT_NAME}_lidar_scan PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
#-------------------------holo_sensors_livox-----------------------------------
set (SOURCE_CPP_LIVOX
    src/lidar/livox/livox_driver.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_livox
    SOURCES
    ${SOURCE_CPP_LIVOX}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    ${PROJECT_NAME}_utils
    ${PROJECT_NAME}_lidar_utils
    ${PROJECT_NAME}_lidar_scan
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_livox)
set_target_properties(${PROJECT_NAME}_livox PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
#-------------------------holo_sensors_livox_hap-----------------------------------
set (SOURCE_CPP_LIVOX_HAP
    src/lidar/livox/livox_hap_driver.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_livox_hap
    SOURCES
    ${SOURCE_CPP_LIVOX_HAP}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    ${PROJECT_NAME}_utils
    ${PROJECT_NAME}_lidar_utils
    ${PROJECT_NAME}_lidar_scan
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_livox_hap)
set_target_properties(${PROJECT_NAME}_livox_hap PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
#-------------------------holo_sensors_pandar----------------------------------
set (SOURCE_CPP_PANDAR
    src/lidar/pandar/pandar_driver.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_pandar
    SOURCES
    ${SOURCE_CPP_PANDAR}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    ${PROJECT_NAME}_utils
    ${PROJECT_NAME}_lidar_utils
    ${PROJECT_NAME}_lidar_scan
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_pandar)
set_target_properties(${PROJECT_NAME}_pandar PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
#-------------------------holo_sensors_pandar128----------------------------------
set (SOURCE_CPP_PANDAR
    src/lidar/pandar128/pandar128_driver.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_pandar128
    SOURCES
    ${SOURCE_CPP_PANDAR}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    ${PROJECT_NAME}_utils
    ${PROJECT_NAME}_lidar_utils
    ${PROJECT_NAME}_lidar_scan
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_pandar128)
set_target_properties(${PROJECT_NAME}_pandar128 PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
#-------------------------holo_sensors_ouster----------------------------------
set (SOURCE_CPP_OUSTER
    src/lidar/ouster/ouster_driver.cpp
)
HOLO_COMPILE_LIB(${PROJECT_NAME}_ouster
    SOURCES
    ${SOURCE_CPP_OUSTER}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    ${PROJECT_NAME}_utils
    ${PROJECT_NAME}_lidar_utils
    ${PROJECT_NAME}_lidar_scan
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_ouster)
set_target_properties(${PROJECT_NAME}_ouster PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)
#-------------------------holo_sensors_rsm1----------------------------------
set (SOURCE_CPP_RSM1
    src/lidar/rsm1/rsm1_driver.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_rsm1
    SOURCES
    ${SOURCE_CPP_RSM1}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    ${PROJECT_NAME}_utils
    ${PROJECT_NAME}_lidar_utils
    ${PROJECT_NAME}_lidar_scan
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_rsm1)
set_target_properties(${PROJECT_NAME}_rsm1 PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
#-------------------------holo_sensors_rsruby----------------------------------
set (SOURCE_CPP_RSRUBY
    src/lidar/rsruby/rsruby_driver.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_rsruby
    SOURCES
    ${SOURCE_CPP_RSRUBY}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    ${PROJECT_NAME}_utils
    ${PROJECT_NAME}_lidar_utils
    ${PROJECT_NAME}_lidar_scan
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_rsruby)
set_target_properties(${PROJECT_NAME}_rsruby PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
#-------------------------holo_sensors_rsbpearl----------------------------------
set (SOURCE_CPP_RSBPEARL
    src/lidar/rsbpearl/rsbpearl_driver.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_rsbpearl
    SOURCES
    ${SOURCE_CPP_RSBPEARL}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    ${PROJECT_NAME}_utils
    ${PROJECT_NAME}_lidar_utils
    ${PROJECT_NAME}_lidar_scan
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_rsbpearl)
set_target_properties(${PROJECT_NAME}_rsbpearl PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
## -------------------------holo_sensors_ublox-------------------------------
set (SOURCE_CPP_UBLOX
    src/gnss/ublox/ublox.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_ublox
    SOURCES
    ${SOURCE_CPP_UBLOX}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    ${PROJECT_NAME}_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_ublox)
set_target_properties(${PROJECT_NAME}_ublox PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )
#-------------------------holo_sensors_velodyne---------------------------
set (SOURCE_CPP_VELODYNE
    src/lidar/velodyne/velodyne_driver.cpp
    )
HOLO_COMPILE_LIB(${PROJECT_NAME}_velodyne
    SOURCES
    ${SOURCE_CPP_VELODYNE}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_sensors_c::holo_sensors_c
    ${PROJECT_NAME}_utils
    ${PROJECT_NAME}_lidar_utils
    ${PROJECT_NAME}_lidar_scan
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_velodyne)
set_target_properties(${PROJECT_NAME}_velodyne PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )

#-------------------------holo_sensors_metadata---------------------------
HOLO_COMPILE_APP(
    ${PROJECT_NAME}_metadata_generator
    SOURCES
    src/metadata/generator.cpp
    INCLUDES
    include
    LIBRARIES
    holo_metadata_cpp::holo_metadata_cpp
    holo_base::holo_base_common
    ${PROJECT_NAME}_interface
    INSTALL_DIR
    share/${PROJECT_NAME}_metadata)

#if(NOT CMAKE_CROSSCOMPILING)
#    # if native build, execute generator after build
#    add_custom_command(
#        TARGET ${PROJECT_NAME}_metadata_generator
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E make_directory metadata
#        COMMAND ./${PROJECT_NAME}_metadata_generator
#        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/share/${PROJECT_NAME}_metadata
#        COMMENT "Generating holo_base_metadata")
#else()
#    # if cross compile, execute generator after build if target platform is x86_64
#    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
#        add_custom_command(
#            TARGET ${PROJECT_NAME}_metadata_generator
#            POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E make_directory metadata
#            COMMAND ./${PROJECT_NAME}_metadata_generator
#            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/share/${PROJECT_NAME}_metadata
#            COMMENT "Generating holo_base_metadata")
#    endif()
#endif()

## -------------------------holo_sensors end------------------------------------

if(HOLO_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

include(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY SameMajorVersion
    )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake @ONLY)

FILE(GLOB FIND_LIBRARY_CMAKE_SCRIPTS "cmake/Find*.cmake")
MESSAGE(STATUS FIND_LIBRARY_CMAKE_SCRIPTS=${FIND_LIBRARY_CMAKE_SCRIPTS})
INSTALL(FILES ${FIND_LIBRARY_CMAKE_SCRIPTS} DESTINATION cmake/Modules)

INSTALL(FILES ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    DESTINATION lib/cmake/${PROJECT_NAME} COMPONENT development)

INSTALL(DIRECTORY include/holo DESTINATION include/${PROJECT_NAME} COMPONENT development)
INSTALL(DIRECTORY ${PROJECT_BINARY_DIR}/include/holo DESTINATION include/${PROJECT_NAME} OPTIONAL COMPONENT development)
install(DIRECTORY ${PROJECT_BINARY_DIR}/share/ DESTINATION share)

add_custom_target(uninstall
    COMMAND cat install_manifest.txt | xargs rm
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Uninstall")

cmake_policy(POP)
