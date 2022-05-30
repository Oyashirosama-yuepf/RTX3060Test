cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)
cmake_policy(SET CMP0048 NEW)

project(holo_parking_manager_app)

## --------------------------- CONFIGURATIONS --------------------------------
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
option(HOLO_BUILD_TEST                     "Build unit test"                          OFF)
option(HOLO_CPU_PROFILE                    "Use Google CPU Profiler"                  OFF)
option(HOLO_BUILD_COVERAGE                 "Generate coverage report"                 OFF)
                      
option(HOLO_BUILD_ON_MDC                   "Build project on MDC"                     OFF)
option(HOLO_BUILD_ON_QNX                   "Build project on QNX"                     OFF)                   

if(${CMAKE_SYSTEM_NAME} STREQUAL "QNX")
    set(HOLO_BUILD_ON_QNX ON)
endif()

# dependency configuration
set(DEPEND_holo_base_VERSION 0.0.0)
set(DEPEND_holo_base_msg_VERSION 0.0.0)
set(DEPEND_cmw_wrapper_VERSION 0.0.0)

# Set C/CXX compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_C_STANDARD 99)

## -------------------------- CMAKE_SETUP ------------------------------------

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

## -------------------------- DEPENDENCIES -----------------------------------
find_package(holo_base ${DEPEND_HOLO_BASE_VERSION} REQUIRED)
find_package(holo_base_msg ${DEPEND_holo_base_msg_VERSION})
find_package(holo_parking_base REQUIRED)
find_package(cmw_wrapper ${DEPEND_cmw_wrapper_VERSION})
find_package(holo_parking_cmw_app/system_apps/tinyfsm/include ${DEPEND_tinyfsm_version})

## -------------------------holomacros----------------------------------------
include(HoloMacros)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../tinyfsm include)
## ------------------------- DOXYGEN------------------------------------------
GENERATE_DOXYGEN(INPUT include src)

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

set(SYSTEM_LIBRARY_SOCKET "")
if(${CMAKE_SYSTEM_NAME} STREQUAL "QNX")
    set(HOLO_BUILD_ON_QNX ON)
    set(SYSTEM_LIBRARY_SOCKET socket)
    MESSAGE(STATUS "QNX System detected, set HOLO_BUILD_ON_QNX to ${HOLO_BUILD_ON_QNX}")
endif()

## ------------------------- generated code------------------------------------
## ------------------------- general application -----------------------------
## ------------------------- holo_cmw v2 application -------------------------
add_cmw_wrapper_executable(parking_manager_cmw
    SOURCES     src/parking_manager/parking_manager_app.cpp
                src/parking_manager/interface_manager/common_interface.cpp
                src/parking_manager/interface_manager/dds_interface.cpp
                src/parking_manager/utils/parking_utils.cpp
                src/parking_manager/utils/mapping_utils.cpp
                src/parking_manager/parking_state_machine/parking_state_machine.cpp
                src/parking_manager/parking_state_machine/parking_manager.cpp
                src/parking_manager/parking_state_machine/parking_fsm_state.cpp
    INCLUDES    include
                include_directories(../)
    LIBRARIES   holo_base_msg::holo_base_msg
                holo_base::holo_base_common
                holo_base::holo_base_os
                holo_parking_base::holo_parking_base_system
                ${SYSTEM_LIBRARY_SOCKET}
    INSTALL_DIR bin
    ROS OPENDDS 
)

#--------------------------- test --------------------------------------------
if(HOLO_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif(HOLO_BUILD_TEST)

#--------------------------- uninstall command -------------------------------
add_custom_target(uninstall_parking_manager
    COMMAND cat install_manifest.txt | xargs rm 
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Uninstall")

cmake_policy(POP)
