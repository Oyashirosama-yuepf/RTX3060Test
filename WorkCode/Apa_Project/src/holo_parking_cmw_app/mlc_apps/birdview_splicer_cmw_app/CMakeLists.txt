cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)

project(holo_localization_birdview_splicer_cmw_app)


## --------------------------- CONFIGURATIONS ----------------------------------------
#Set project version
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR})
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_SOVERSION}.${${PROJECT_NAME}_VERSION_PATCH})

if(HOLO_BUILD_VERSION)
    set(${PROJECT_NAME}_VERSION_TWEAK)
    set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION}.${HOLO_BUILD_VERSION})
endif(HOLO_BUILD_VERSION)

set(PROJECT_VERSION ${${PROJECT_NAME}_VERSION})

# default options
option(HOLO_BUILD_TEST     "Build unit test"          OFF)
option(HOLO_BUILD_COVERAGE "Generate coverage report" OFF)
option(HOLO_BUILD_SDK "" OFF)

# dependency configuration
set(HOLO_CMW_VERSION 0.1.0)
set(HOLO_BASE_MSG_VERSION 0.1.0)
set(HOLO_SENSORS_BASE_VERSION 0.1.0)
set(HOLO_LOCALIZATION_BASE_VERSION 0.1.0)
set(CUDA_VERSION 10.0)
set(CUDNN_VERSION 7)
set(TensorRT_VERSION 5.0)

# Set C/CXX compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_C_STANDARD 99)

## -------------------------- CMAKE_SETUP ---------------------------------------

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


## -------------------------- DEPENDENCIES --------------------------------------
find_package(holo_base_msg ${HOLO_BASE_MSG_VERSION} REQUIRED)
find_package(holo_parking_msg ${HOLO_PARKING_MSG_VERSION} REQUIRED)
find_package(cmw_wrapper REQUIRED)
find_package(holo_sensors_base ${HOLO_SENSORS_BASE_VERSION} REQUIRED)
find_package(holo_localization_base ${HOLO_LOCALIZATION_BASE_VERSION} REQUIRED)
find_package(FFMPEG REQUIRED COMPONENTS avcodec)
find_package(FFMPEG REQUIRED COMPONENTS avformat)
find_package(FFMPEG REQUIRED COMPONENTS swscale)
find_package(JPEG REQUIRED COMPONENTS JPEG)
find_package(TI_PSDK)

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
            "${PROJECT_BINARY_DIR}/src/*"
            "${PROJECT_SOURCE_DIR}/test/*"
            )
    else()
        MESSAGE(FATAL_ERROR "Unable to generate coverage report! CMAKE_BUILD_TYPE is not DEBUG!")
    endif()
endif()

## -------------------------generated code------------------------------------

## ------------------------- library ------------------------------------
if(TI_PSDK_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")
    set(BUILD_SHARED_LIBS ON)
    add_definitions(-DUSE_TDA4)
    add_definitions("-Drestrict=__restrict__")
    set(TDA4_SRC
        ${BIRDVIEW_SRC}
        ${PROJECT_SOURCE_DIR}/src/localization/birdview/tda4_nv12torgb/test_tda4.cpp
        ${PROJECT_SOURCE_DIR}/src/localization/birdview/tda4_nv12torgb/TadlInference.cpp
        ${PROJECT_SOURCE_DIR}/src/localization/birdview/tda4_nv12torgb/app_scaler_module.cpp
        ${PROJECT_SOURCE_DIR}/src/localization/birdview/tda4_nv12torgb/app_pre_proc_module.cpp
        )
    set(TDA4_LIB
        tda3_yuv2rgb
        )
    HOLO_COMPILE_LIB(${TDA4_LIB}
        SOURCES
        ${TDA4_SRC}
        INCLUDES
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        LIBRARIES
        TI_PSDK::tiovx
        TI_PSDK::psdk
        TI_PSDK::vision_apps
        INSTALL_DIR lib
        NAMESPACE tda4::
        )
endif(TI_PSDK_FOUND)

add_cmw_wrapper_executable(
        birdview_splicer_cmw
        SOURCES
        ${PROJECT_SOURCE_DIR}/src/localization/birdview/birdview_mask.cpp
        ${PROJECT_SOURCE_DIR}/src/localization/birdview/birdview_show.cpp
        ${PROJECT_SOURCE_DIR}/src/localization/birdview/birdview_image_undistortion.cpp
        ${PROJECT_SOURCE_DIR}/src/localization/birdview/birdview_splicer_cmw.cpp
        ${PROJECT_SOURCE_DIR}/src/localization/birdview/image_type_converter.cpp
        INCLUDES 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        LIBRARIES
        holo_localization::holo_localization_base
        holo_sensors_base::holo_sensors_base_image_ipc
        holo_sensors_base::holo_sensors_base_camera
        ${TDA4_LIB}
        INSTALL_DIR 
        bin
        OPENDDS ROS DDS_MICRO)

add_cmw_wrapper_executable(
        undistort_ocam_image
        SOURCES
        ${PROJECT_SOURCE_DIR}/src/localization/birdview/birdview_image_undistortion.cpp
        ${PROJECT_SOURCE_DIR}/src/localization/birdview/undistort_ocam_image.cpp
        INCLUDES 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        LIBRARIES
        holo_localization::holo_localization_base
        INSTALL_DIR 
        bin
        OPENDDS ROS DDS_MICRO)

#--------------------------- test ---------------------------------------
if(HOLO_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif(HOLO_BUILD_TEST)

#--------------------------- uninstall command --------------------
if(HOLO_BUILD_SDK)
    INSTALL(DIRECTORY app_config/vslam/sdk/ DESTINATION ${HOLO_CONFIG_ROOT}/holo_localization_parking/app_config/vslam)
else()
    INSTALL(DIRECTORY app_config/ DESTINATION ${HOLO_CONFIG_ROOT}/holo_localization_parking/app_config)
endif(HOLO_BUILD_SDK)

add_custom_target(uninstall_birdview_splicer
    COMMAND cat install_manifest.txt | xargs rm
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Uninstall")

cmake_policy(POP)
