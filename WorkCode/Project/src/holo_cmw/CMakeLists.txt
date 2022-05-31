cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028    NEW)
cmake_policy(SET CMP0022    NEW)

project(holo_cmw)

################################################################################
#                           PROJECT CONFIGURATION                              #
################################################################################

set(${PROJECT_NAME}_VERSION_MAJOR   "0")
set(${PROJECT_NAME}_VERSION_MINOR   "8")
set(${PROJECT_NAME}_VERSION_PATCH   "0")
set(${PROJECT_NAME}_SOVERSION       "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}")
set(${PROJECT_NAME}_VERSION         "${${PROJECT_NAME}_SOVERSION}.${${PROJECT_NAME}_VERSION_PATCH}")

if (HOLO_BUILD_VERSION)
    set(${PROJECT_NAME}_VERSION     "${${PROJECT_NAME}_VERSION}.${HOLO_BUILD_VERSION}")
    set(${PROJECT_NAME}_VERSION_TWEAK)
endif (HOLO_BUILD_VERSION)

# default options
option(HOLO_BUILD_TEST              "" OFF)
option(HOLO_BUILD_SHARED            "" ON)
# options for holo_cmw v2
option(HOLO_CMW_BUILD_ROS_WRAPPER       "" OFF)
option(HOLO_CMW_BUILD_RTIDDS_WRAPPER    "" OFF)
option(HOLO_CMW_BUILD_MDC_CM_WRAPPER    "" OFF)
option(HOLO_CMW_BUILD_OPENDDS_WRAPPER   "" OFF)
option(HOLO_CMW_BUILD_DDS_MICRO_WRAPPER   "" OFF)
option(HOLO_CMW_BUILD_PPS_WRAPPER   "" OFF)
option(HOLO_CMW_BUILD_UMB_WRAPPER   "" OFF)

# DO NOT EDIT CXX_FLAGS AND C FLAGS!!!
set(CMAKE_C_FLAGS                   "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_C_STANDARD                "99")
set(CMAKE_CXX_FLAGS                 "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_CXX_STANDARD              "14")

# export target configuration
set(EXPORT_NAMESPACE                "${PROJECT_NAME}")

## !!!!!! END CONFIGURATIONS. EDIT BELOW THIS LINE SHOULD BE CAREFUL !!!!!!!!!!!!


################################################################################
#                               CMAKE_SETUP                                    #
################################################################################

# Set CMake variable to build shared library or static library.
if (HOLO_BUILD_SHARED)
    set(BUILD_SHARED_LIBS ON)
else ()
    set(BUILD_SHARED_LIBS OFF)
endif ()

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

if(HOLO_CMW_BUILD_OPENDDS_WRAPPER)
    add_subdirectory(opendds_wrapper)
endif()
if(HOLO_CMW_BUILD_MDC_CM_WRAPPER)
    add_subdirectory(mdc_cm_wrapper)
endif()
if(HOLO_CMW_BUILD_DDS_MICRO_WRAPPER)
    add_subdirectory(dds_micro_wrapper)
endif()
if(HOLO_CMW_BUILD_PPS_WRAPPER)
    add_subdirectory(pps_wrapper)
endif()
if(HOLO_CMW_BUILD_ROS_WRAPPER)
    add_subdirectory(ros_wrapper)
endif()
if(HOLO_CMW_BUILD_UMB_WRAPPER)
    add_subdirectory(umb_wrapper)
endif()
add_subdirectory(cmw_wrapper)

INSTALL(FILES "CHANGELOG.md" DESTINATION share/doc/${PROJECT_NAME})

add_custom_target(uninstall
    COMMAND 
        cat install_manifest.txt | xargs rm
    WORKING_DIRECTORY 
        ${PROJECT_BINARY_DIR}
    COMMENT 
        "Uninstall"
)

cmake_policy(POP)

