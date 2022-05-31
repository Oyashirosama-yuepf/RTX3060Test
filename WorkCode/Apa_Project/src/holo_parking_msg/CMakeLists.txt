cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)

project(holo_parking_msg)

## --------------------------- CONFIGURATIONS ----------------------------------------
# Set project version
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
option(HOLO_BUILD_SHARED   "Build shared library"     ON)
option(HOLO_BUILD_COVERAGE "Generate coverage report" OFF)

# DO NOT EDIT CXX_FLAGS AND C FLAGS!!!
# Set C/CXX compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_C_STANDARD 99)

set(EXPORT_NAMESPACE                "${PROJECT_NAME}")
################################################################################
#                               CMAKE_SETUP                                    #
################################################################################

# Set CMake variable to build shared library or static library.
if (HOLO_BUILD_SHARED)
    set(BUILD_SHARED_LIBS ON)
else ()
    set(BUILD_SHARED_LIBS OFF)
endif ()

if(HOLO_BUILD_TEST)
    enable_testing()
endif()

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

include(HoloMacros)
## -------------------------- DEPENDENCIES --------------------------------------
find_package(holo_base REQUIRED)
find_package(holo_parking_base REQUIRED)

set(HOLO_PARKING_MSG_COMPONENTS opendds ros dds_micro)

foreach(comp ${HOLO_PARKING_MSG_COMPONENTS})
    add_subdirectory(${comp}_msg)
    if(TARGET ${PROJECT_NAME}_${comp})
        LIST(APPEND HOLO_PARKING_MSG_ENABLED_COMPONENTS ${comp})
    endif()
endforeach()

HOLO_COMPILE_LIB(holo_parking_msg
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    INSTALL_DIR lib
    INSTALL_EXPORT_DIR share/${PROJECT_NAME}/cmake
    NAMESPACE ${EXPORT_NAMESPACE}::
    )
 
include(CMakePackageConfigHelpers)

CONFIGURE_PACKAGE_CONFIG_FILE(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
    "${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake"
    INSTALL_DESTINATION "share/${PROJECT_NAME}/cmake"
    )

WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY SameMajorVersion
)

INSTALL(FILES 
    ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake 
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    DESTINATION share/${PROJECT_NAME}/cmake)
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include/${PROJECT_NAME})

cmake_policy(POP)
