cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)
cmake_policy(SET CMP0048 NEW)

project(holo_utils)

## --------------------------- CONFIGURATIONS ----------------------------------------
#Set project version
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 8)
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
if(NOT HOLO_LOG_TYPE)
    set(HOLO_LOG_TYPE "HOLO_LOG")
endif()

# Set C/CXX compiler flags.
# Required CXX_FLAGS are "-std=c++11 -Wall -Wextra -Werror". Required C_FLAGS are "-Wall -Wextra -Werror".
#
# DO NOT EDIT CXX_FLAGS AND C FLAGS!!!
# If additional flags are needed, explain the rationality.
#
#
# Set C/CXX compiler flags.
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations"
    )
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_C_STANDARD 99)

# export target configuration
set(EXPORT_NAMESPACE ${PROJECT_NAME})


## !!!!!! END CONFIGURATIONS. EDIT BELOW THIS LINE SHOULD BE CAREFUL !!!!!!!!!!!!



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
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake/Modules")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
    include(HoloProjectConfiguration)
endif()

## -------------------------dependency------------------------------------
set(HOLO_LOG_TYPE_HOLO_LOG_DEFINITION 0)
set(HOLO_LOG_TYPE_LOG4CPLUS_DEFINITION 0)
set(HOLO_LOG_TYPE_GLOG_DEFINITION 1)
if(HOLO_LOG_TYPE STREQUAL "HOLO_LOG" OR HOLO_LOG_TYPE STREQUAL "LOG4CPLUS")
    find_package(LOG4CPLUS 2.0.7 REQUIRED)
    set(LOG_SRC
        src/log/log4cplus/hololog.cpp
        src/log/log4cplus/appender/console_appender.cpp
        src/log/log4cplus/layout/pattern_layout.cpp
        src/log/log4cplus/default_initializer.cpp
        )
    set(LOG_LIBRARIES PRIVATE LOG4CPLUS::log4cplus)
    set(HOLO_LOG_TYPE_DEFINITION ${HOLO_LOG_TYPE_LOG4CPLUS_DEFINITION})
elseif(HOLO_LOG_TYPE STREQUAL "GLOG")
    find_package(GLOG 0.4.0 REQUIRED)
    set(LOG_SRC
        src/log/glog/hololog.cpp
        src/log/glog/default_initializer.cpp
        )
    set(LOG_LIBRARIES PUBLIC GLOG::glog)
    set(HOLO_LOG_TYPE_DEFINITION ${HOLO_LOG_TYPE_GLOG_DEFINITION})
else()
    MESSAGE(FATAL_ERROR "Unknown log type ${HOLO_LOG_TYPE}")
endif()

#find_package(LOG4CPLUS 2.0.7 REQUIRED)
find_package(YAML-CPP REQUIRED)
find_package(Threads REQUIRED)

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

## -------------------------holo_utils----------------------------------

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "Platform: Linux ")
    set(RT_LIBRARY rt)
    set(IO_MULTIPLEXER_SRC
        src/network/epoller.cpp
        src/network/selector.cpp
        src/network/poller.cpp
        )
else()
    MESSAGE(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
    set(SOCKET_LIBRARY socket)
    set(IO_MULTIPLEXER_SRC
        src/network/selector.cpp
        src/network/poller.cpp
        )
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

HOLO_COMPILE_LIB(${PROJECT_NAME}
    SOURCES
    src/serialization/utility.cpp
    src/utils/configuration.cpp
    src/os/filesystem.cpp
    ${LOG_SRC}
    src/log/config/configure.cpp
    src/log/config/console_configure.cpp
    src/log/config/single_file_configure.cpp
    src/log/config/rolling_file_configure.cpp
    src/log/config/daily_rolling_file_configure.cpp
    src/log/config/time_based_rolling_file_configure.cpp
    src/log/config/socket_configure.cpp
    src/pcapng/pcapng_file.cpp
    src/pcapng/block/section_header_block.cpp
    src/pcapng/block/interface_description_block.cpp
    src/pcapng/block/enhanced_packet_block.cpp
    src/os/signal_handler.cpp
    src/os/utils.cpp
    src/os/shared_memory_block.cpp
    src/network/socket.cpp
    ${IO_MULTIPLEXER_SRC}
    src/network/listener.cpp
    src/network/connection_monitor.cpp
    src/network/utils.cpp
    src/bag/agent/session.cpp
    src/bag/agent/port.cpp
    src/bag/protocol/protocol.cpp
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    YAML-CPP::yaml-cpp
    Threads::Threads
    PRIVATE ${RT_LIBRARY}
    ${LOG_LIBRARIES}
    ${SOCKET_LIBRARY}
    DEFINITIONS
    HOLO_LOG_TYPE=${HOLO_LOG_TYPE_DEFINITION}
    HOLO_LOG_TYPE_HOLO_LOG=${HOLO_LOG_TYPE_HOLO_LOG_DEFINITION}
    HOLO_LOG_TYPE_LOG4CPLUS=${HOLO_LOG_TYPE_LOG4CPLUS_DEFINITION}
    HOLO_LOG_TYPE_GLOG=${HOLO_LOG_TYPE_GLOG_DEFINITION}
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::)


set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )

if(HOLO_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif(HOLO_BUILD_TEST)
add_subdirectory(unittest)

include(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY SameMajorVersion
    )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake @ONLY)

INSTALL(FILES ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    DESTINATION lib/cmake/${PROJECT_NAME} COMPONENT development)
INSTALL(DIRECTORY include/holo DESTINATION include/${PROJECT_NAME} COMPONENT development)
#INSTALL(FILES "CHANGELOG.md" DESTINATION share/doc/${PROJECT_NAME})
if(NOT HOLO_LOG_TYPE STREQUAL "GLOG")
    INSTALL(FILES include/holo/log/log4cplus/glog/logging.h DESTINATION 3rdparty/include/glog)
endif()

add_custom_target(uninstall
    COMMAND cat install_manifest.txt | xargs rm
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Uninstall")

cmake_policy(POP)
