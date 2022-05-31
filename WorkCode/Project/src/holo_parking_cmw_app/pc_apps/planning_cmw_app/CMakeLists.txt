cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)

project(holo_planning_parking_cmw_app)

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

# dependency configuration
set(DEPEND_HOLO_PLANNING_BASE_VERSION 0.1.0)
set(DEPEND_HOLO_PLANNING_PARKING_VERSION 0.1.0)
set(DEPEND_HOLO_BASE_MSG_VERSION 0.1.0)
set(DEPEND_HOLO_PARKING_MSG_VERSION 0.1.0)

# Set C/CXX compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_CXX_STANDARD 11)
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
find_package(holo_planning_base ${DEPEND_HOLO_PLANNING_BASE_VERSION} REQUIRED)
find_package(holo_planning_parking ${DEPEND_HOLO_PLANNING_PARKING_VERSION} REQUIRED)
find_package(holo_base_msg ${DEPEND_HOLO_BASE_MSG_VERSION} REQUIRED)
find_package(holo_parking_msg ${DEPEND_HOLO_PARKING_MSG_VERSION} REQUIRED)
find_package(cmw_wrapper)

## -------------------------holomacros------------------------------------
include(HoloMacros)

## -------------------------generated code------------------------------------
add_cmw_wrapper_executable(
    planning_hpp_app
    SOURCES
    ${PROJECT_SOURCE_DIR}/src/planning_hpp_app.cpp
    INCLUDES
    ${PROJECT_SOURCE_DIR}/include
    LIBRARIES
    holo_planning_parking::holo_planning_parking
    holo_base_msg::holo_base_msg
    holo_parking_msg::holo_parking_msg
    INSTALL_DIR
    bin
    ROS OPENDDS DDS_MICRO)

add_cmw_wrapper_executable(
    longitudinal_start_and_stop_app
    SOURCES
    ${PROJECT_SOURCE_DIR}/src/longitudinal_start_and_stop_app.cpp
    INCLUDES
    ${PROJECT_SOURCE_DIR}/include
    LIBRARIES
    holo_planning_parking::holo_planning_parking
    holo_base_msg::holo_base_msg
    INSTALL_DIR
    bin
    ROS OPENDDS DDS_MICRO)

#--------------------------- uninstall command --------------------
INSTALL(DIRECTORY config/ DESTINATION ${HOLO_CONFIG_ROOT}/${PROJECT_NAME}/app_config)

add_custom_target(uninstall_planning 
    COMMAND cat install_manifest.txt | xargs rm 
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Uninstall")

cmake_policy(POP)