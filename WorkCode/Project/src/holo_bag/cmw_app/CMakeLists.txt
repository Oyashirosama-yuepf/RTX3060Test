cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0074 NEW)

project(holo_bag_cmw_app)


## --------------------------- CONFIGURATIONS ----------------------------------------
#Set project version
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 2)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR})
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_SOVERSION}.${${PROJECT_NAME}_VERSION_PATCH})

if(HOLO_BUILD_VERSION)
    set(${PROJECT_NAME}_VERSION_TWEAK)
    set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION}.${HOLO_BUILD_VERSION})
endif(HOLO_BUILD_VERSION)

set(PROJECT_VERSION ${${PROJECT_NAME}_VERSION})

# default options
option(HOLO_CAMERA_USE_IN_TDA4 "Build project on TDA4" OFF)
option(HOLO_BUILD_ON_QNX "Build project on QNX" OFF)
if(${CMAKE_SYSTEM_NAME} STREQUAL "QNX")
set(HOLO_BUILD_ON_QNX ON)
endif()

option(HOLO_BUILD_WITH_CUDA     "Build with cuda features" OFF)
option(HOLO_TIME_WITH_MDC_TIME  "Build use mdc time"       OFF)

if (HOLO_BUILD_PLATFORM MATCHES "MDC610")
    add_compile_definitions(HOLO_PLATFORM_MDC610)
    set(HOLO_BUILD_ON_MDC610 ON)
    MESSAGE(STATUS "HOLO_BUILD_ON_MDC610 = ${HOLO_BUILD_ON_MDC610} (OVERRIDE)")
    if (HOLO_BUILD_PLATFORM MATCHES "MDC610-1.0.012")
        add_compile_definitions(MDC610_VERSION_V430)
        MESSAGE(STATUS "Add compile definition MDC610_VERSION_V430")
    elseif(HOLO_BUILD_PLATFORM MATCHES "MDC610-1.0.017")
        add_compile_definitions(MDC610_VERSION_V830)
        MESSAGE(STATUS "Add compile definition MDC610_VERSION_V830")
    endif()
endif()

if(HOLO_CAMERA_USE_IN_TDA4)
    add_compile_definitions(HOLO_CAMERA_USE_IN_TDA4)
endif()

if(HOLO_BUILD_WITH_CUDA)
    add_compile_definitions(HOLO_CAMERA_USE_CUDA)
    SET(TEGRA_MEDIA_PATH "")
    if(EXISTS ${CMAKE_SYSROOT}/usr/src/tegra_multimedia_api)
        SET(TEGRA_MEDIA_PATH ${CMAKE_SYSROOT}/usr/src/tegra_multimedia_api)
    elseif(EXISTS ${CMAKE_SYSROOT}/home/nvidia/Desktop/tegra_multimedia_api)
        SET(TEGRA_MEDIA_PATH ${CMAKE_SYSROOT}/home/nvidia/Desktop/tegra_multimedia_api)
    elseif(EXISTS ${CMAKE_SYSROOT}/home/nvidia/tegra_multimedia_api)
        SET(TEGRA_MEDIA_PATH ${CMAKE_SYSROOT}/home/nvidia/tegra_multimedia_api)
    endif()
    MESSAGE(TEGRA_MEDIA_PATH=${TEGRA_MEDIA_PATH})
    if(NOT (TEGRA_MEDIA_PATH STREQUAL ""))
        add_compile_definitions(HOLO_CAMERA_USE_TEGRA_MMA)
    endif()
endif(HOLO_BUILD_WITH_CUDA)

if(HOLO_TIME_WITH_MDC_TIME)
    add_compile_definitions(HOLO_TIME_WITH_MDC_TIME)
endif()

set(QNX_SYS_LIB "")
if(${CMAKE_SYSTEM_NAME} STREQUAL "QNX")
set(HOLO_BUILD_ON_QNX ON)
set(QNX_SYS_LIB "socket")
endif()

# dependency configuration
set(DEPEND_HOLO_BAG_VERSION 0.1.0)
set(DEPEND_HOLO_SENSORS_BASE_VERSION 0.1.0)
set(DEPEND_CMW_WRAPPER_VERSION 0.1.0)

# Set C/CXX compiler flags.
# Required CXX_FLAGS are "-std=c++11 -Wall -Wextra -Werror". Required C_FLAGS are "-Wall -Wextra -Werror".
#
# DO NOT EDIT CXX_FLAGS AND C FLAGS!!!
# If additional flags are needed, explain the rationality.
#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -fstack-protector-strong -Wno-error=deprecated-declarations -Wno-error=strict-aliasing")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DEIGEN_MPL2_ONLY -Wall -Wextra -Werror -fstack-protector-strong -Wno-error=deprecated-declarations")

# export target configuration
set(EXPORT_NAMESPACE ${PROJECT_NAME})

# Set CMake variable for additional .cmake file search path.
if(NOT HOLO_ROOT AND NOT DEFINED ENV{HOLO_ROOT})
    MESSAGE(FATAL_ERROR "Unable to set HOLO_ROOT. Please set HOLO_ROOT environment variable or pass HOLO_ROOT as cmake parameter")
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
find_package(holo_bag ${DEPEND_HOLO_BAG_VERSION} REQUIRED)
find_package(holo_sensors_base ${DEPEND_HOLO_SENSORS_BASE_VERSION} REQUIRED)
find_package(cmw_wrapper ${DEPEND_CMW_WRAPPER_VERSION} REQUIRED)

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
        include(Coverage)
    else()
        MESSAGE(FATAL_ERROR "Unable to generate coverage report! CMAKE_BUILD_TYPE is not DEBUG!")
    endif()
endif()

set(MDC_610_SDK)
if (HOLO_BUILD_PLATFORM MATCHES "MDC610")
    LIST(APPEND MDC_610_SDK ${MDC610_SDK_LIBRARIES})
    MESSAGE(STATUS "Add MDC610_SDK_LIBRARIES")
endif()

## -------------------------holo_bag_cmw------------------------------------
add_cmw_wrapper_executable(holobag
                           SOURCES    ${PROJECT_SOURCE_DIR}/src/holo_filter.cpp
                                      ${PROJECT_SOURCE_DIR}/src/holo_info.cpp
                                      ${PROJECT_SOURCE_DIR}/src/holo_replay.cpp
                                      ${PROJECT_SOURCE_DIR}/src/holo_record.cpp
                                      ${PROJECT_SOURCE_DIR}/src/holo_export.cpp
                                      ${PROJECT_SOURCE_DIR}/src/holobag.cpp
                                      ${PROJECT_SOURCE_DIR}/src/utils.cpp
                           INCLUDES   ${PROJECT_SOURCE_DIR}/include
                           LIBRARIES  holo_bag::holo_bag_interface
                                      holo_sensors_base::holo_sensors_base_camera
                                      holo_sensors_base::holo_sensors_base_image_process
                                      ${MDC_610_SDK} -lpthread
                           INSTALL_DIR bin
                           UMB
                           ROS
                           OPENDDS)

## -------------------------holo_bag end------------------------------------

INSTALL(TARGETS ${${PROJECT_NAME}_APP_TARGETS} DESTINATION bin)

add_custom_target(uninstall
	COMMAND cat install_manifest.txt | xargs rm
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	COMMENT "Uninstall")

cmake_policy(POP)
