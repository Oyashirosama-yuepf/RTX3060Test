cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0074 NEW)

project(holo_bag)


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
option(HOLO_BUILD_TEST "Build unit test"                OFF)
option(HOLO_CPU_PROFILE "Use Google CPU Profiler"       ON )
option(HOLO_BUILD_SHARED "Build shared library"         ON )
option(HOLO_BUILD_WITH_CUDA "Build with cuda features"  OFF)
option(HOLO_BUILD_COVERAGE "Generate coverage report"   OFF)
option(HOLO_BUILD_ON_QNX "Build project on QNX"         OFF)

set(QNX_SYS_LIB "")
if(${CMAKE_SYSTEM_NAME} STREQUAL "QNX")
set(HOLO_BUILD_ON_QNX ON)
set(QNX_SYS_LIB "socket")
endif()

# dependency configuration
set(DEPEND_HOLO_BASE_VERSION 0.2.0)
set(DEPEND_YAML_CPP_VERSION 0.6.2)
set(DEPEND_SQLITE3_VERSION 3.29.0)

# Set C/CXX compiler flags.
# Required CXX_FLAGS are "-std=c++11 -Wall -Wextra -Werror". Required C_FLAGS are "-Wall -Wextra -Werror".
#
# DO NOT EDIT CXX_FLAGS AND C FLAGS!!!
# If additional flags are needed, explain the rationality.
#
#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -fstack-protector-strong -Wno-error=deprecated-declarations -Wno-error=strict-aliasing")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DEIGEN_MPL2_ONLY -Wall -Wextra -Werror -fstack-protector-strong -Wno-error=deprecated-declarations")

# export target configuration
set(EXPORT_NAMESPACE ${PROJECT_NAME})


## !!!!!! END CONFIGURATIONS. EDIT BELOW THIS LINE SHOULD BE CAREFUL !!!!!!!!!!!!

## -------------------------- CMAKE_SETUP ---------------------------------------
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
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake/Modules")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
    include(HoloProjectConfiguration)
endif()

## -------------------------- DEPENDENCIES --------------------------------------
find_package(holo_base ${DEPEND_HOLO_BASE_VERSION} REQUIRED)
find_package(YAML-CPP ${DEPEND_YAML_CPP_VERSION} REQUIRED)
find_package(SQLITE3 ${DEPEND_SQLITE3_VERSION} REQUIRED)
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

## -------------------------holo_bag_base------------------------------------

HOLO_COMPILE_LIB(
    ${PROJECT_NAME}_base
    SOURCES
    src/holo/base/base_io_interface.cpp
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    holo_base::holo_base_core
    holo_base::holo_base_os
    holo_base::holo_base_utils
    holo_base::holo_base_prediction
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_base)
set(${PROJECT_NAME}_COMPONETS ${${PROJECT_NAME}_COMPONENTS} base)

set_target_properties(${PROJECT_NAME}_base PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )

## -------------------------holo_bag_storage------------------------------------

HOLO_COMPILE_LIB(
    ${PROJECT_NAME}_storage
    SOURCES
    src/holo/storage/sqlite_statement_wrapper.cpp
    src/holo/storage/sqlite_storage.cpp
    src/holo/storage/sqlite_wrapper.cpp
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    ${PROJECT_NAME}_base
    holo_base::holo_base_utils
    SQLITE3::sqlite3
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_storage)
set(${PROJECT_NAME}_COMPONETS ${${PROJECT_NAME}_COMPONENTS} storage)

set_target_properties(${PROJECT_NAME}_storage PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )

## -------------------------holo_bag_interface------------------------------------

HOLO_COMPILE_LIB(
    ${PROJECT_NAME}_interface
    SOURCES
    src/holo/interface/sequential_reader.cpp
    src/holo/interface/sequential_writer.cpp
    src/holo/interface/filter.cpp
    src/holo/interface/info.cpp
    src/holo/interface/reader.cpp
    src/holo/interface/writer.cpp
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    ${PROJECT_NAME}_storage
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)
set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_interface)
set(${PROJECT_NAME}_COMPONETS ${${PROJECT_NAME}_COMPONENTS} interface)

set_target_properties(${PROJECT_NAME}_interface PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )

## -------------------------holo_bag end------------------------------------
if(HOLO_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif(HOLO_BUILD_TEST)

include(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in ${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake @ONLY)

INSTALL(FILES ${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake
              ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
        DESTINATION lib/cmake/${PROJECT_NAME} COMPONENT development)

INSTALL(DIRECTORY include/ DESTINATION include/${PROJECT_NAME} COMPONENT development)
INSTALL(DIRECTORY script/ DESTINATION ${HOLO_CONFIG_ROOT}/${PROJECT_NAME}/script)

add_custom_target(uninstall
    COMMAND cat install_manifest.txt | xargs rm
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Uninstall")

cmake_policy(POP)