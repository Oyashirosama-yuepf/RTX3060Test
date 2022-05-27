cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)

project(holo_localization_deep_cmw_app)

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

# dependency configuration
set(HOLO_CMW_VERSION 0.1.0)
set(HOLO_BASE_MSG_VERSION 0.1.0)
set(HOLO_LOCALIZATION_DEEP_VERSION 0.1.0)

# Set C/CXX compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-error=deprecated-declarations")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-error=deprecated-declarations")
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
find_package(cmw_wrapper REQUIRED)
find_package(holo_base_msg ${HOLO_BASE_MSG_VERSION} REQUIRED)
find_package(holo_parking_base REQUIRED)
find_package(holo_parking_msg REQUIRED)
find_package(TI_PSDK QUIET)
if(${TI_PSDK_FOUND})
    # list(APPEND OPTIONAL_LIBRARIES 
    # TI_PSDK::psdk
    # )
    add_definitions("-DUSE_NV12")
    message(STATUS "Build FeatureDetectorCmw with tda4.")
else()
    list(APPEND OPTIONAL_LIBRARIES 
    CUDNN::cudnn
    TensorRT::TensorRT
    torch)
    message(STATUS "Build FeatureDetectorCmw with cuda.")
endif()

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
add_cmw_wrapper_executable(
    feature_detector_cmw
    SOURCES
    ${PROJECT_SOURCE_DIR}/src/localization/deep/feature_detector_cmw.cpp
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_localization::holo_localization_deep
    holo_parking_base::holo_parking_base_vision
    holo_parking_msg::holo_parking_msg
    ${OPTIONAL_LIBRARIES}
    INSTALL_DIR 
    bin
    OPENDDS ROS DDS_MICRO)

#--------------------------- Install/Uninstall command --------------------
INSTALL(DIRECTORY app_config/ DESTINATION ${HOLO_CONFIG_ROOT}/holo_localization_deep/app_config)

add_custom_target(uninstall_feature_detector
	COMMAND cat install_manifest.txt | xargs rm
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	COMMENT "Uninstall")

cmake_policy(POP)
