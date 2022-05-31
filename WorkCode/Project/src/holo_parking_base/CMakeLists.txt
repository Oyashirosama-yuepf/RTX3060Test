cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)
cmake_policy(SET CMP0048 NEW)

project(holo_parking_base)


## --------------------------- CONFIGURATIONS ----------------------------------------
#Set project version
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 4)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR})
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_SOVERSION}.${${PROJECT_NAME}_VERSION_PATCH})

if(HOLO_BUILD_VERSION)
    set(${PROJECT_NAME}_VERSION_TWEAK)
    set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION}.${HOLO_BUILD_VERSION})
endif(HOLO_BUILD_VERSION)

set(PROJECT_VERSION ${${PROJECT_NAME}_VERSION})

# default options
option(HOLO_BUILD_TEST     "Build unit test"          ON)
option(HOLO_CPU_PROFILE    "Use Google CPU Profiler"  ON)
option(HOLO_BUILD_SHARED   "Build shared library"     ON)
option(HOLO_BUILD_COVERAGE "Generate coverage report" OFF)
option(HOLO_CONFIG_USE_FIXED_SIZE_CONTAINER "Use fixed size container" OFF)

# dependency configuration
set(DEPEND_HOLO_BASE_C_VERSION 0.1.0)
set(DEPEND_HOLO_BASE_VERSION 0.1.0)
set(DEPEND_EIGEN3_VERSION 3.3.7)
set(DEPEND_YAML_CPP_VERSION 0.6.2)
set(DEPEND_GLOG_VERSION 0.4.0)
set(DEPEND_OPENCV_VERSION 3.3.1)

# Set C/CXX compiler flags.
# Required CXX_FLAGS are "-std=c++11 -Wall -Wextra -Werror". Required C_FLAGS are "-Wall -Wextra -Werror".
#
# DO NOT EDIT CXX_FLAGS AND C FLAGS!!!
# If additional flags are needed, explain the rationality.
#
#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -fstack-protector-strong -Wno-error=deprecated-declarations -Wno-error=strict-aliasing")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DEIGEN_MPL2_ONLY -Wall -Wextra -Werror -fstack-protector-strong -Wno-error=deprecated-declarations")

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

## -------------------------- DEPENDENCIES --------------------------------------
find_package(holo_base_c ${DEPEND_HOLO_BASE_C_VERSION})
find_package(holo_base ${DEPEND_HOLO_BASE_VERSION})
find_package(holo_utils)
find_package(holo_metadata_cpp REQUIRED)

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

## -------------------------holo_parking_base_vision------------------------------------
set (SOURCE_CPP_VISION
    src/vision/point_feature.cpp
    src/vision/point_feature_list.cpp
    src/vision/point_feature_list_ipc.cpp
    src/vision/point_feature_list_smb.cpp
)

HOLO_COMPILE_LIB(${PROJECT_NAME}_vision
    SOURCES
    ${SOURCE_CPP_VISION}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base_c::holo_base_c
    holo_base::holo_base_common
    holo_base::holo_base_numerics
    holo_utils::holo_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_vision)

set_target_properties(${PROJECT_NAME}_vision PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_parking_base_localization------------------------------------
set (SOURCE_CPP_LOCALIZATION
    src/localization/vehicle_pose_2d.cpp
)

HOLO_COMPILE_LIB(${PROJECT_NAME}_localization
    SOURCES
    ${SOURCE_CPP_LOCALIZATION}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base_c::holo_base_c
    holo_base::holo_base_common
    holo_base::holo_base_numerics
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_localization)

set_target_properties(${PROJECT_NAME}_localization PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_parking_base_planning------------------------------------
set (SOURCE_CPP_PLANNING
    src/planning/path_attribute.cpp
)

HOLO_COMPILE_LIB(${PROJECT_NAME}_planning
    SOURCES
    ${SOURCE_CPP_PLANNING}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_planning)

set_target_properties(${PROJECT_NAME}_planning PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_parking_base_map------------------------------------
set (SOURCE_CPP_MAP
    src/map/navigation_road_builder.cpp
    src/map/parking_map_io.cpp
    src/map/parking_map_common_types.cpp
    src/map/map_path_process.cpp
)

HOLO_COMPILE_LIB(${PROJECT_NAME}_map
    SOURCES
    ${SOURCE_CPP_MAP}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_map)

set_target_properties(${PROJECT_NAME}_map PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)
## -------------------------holo_parking_base_control------------------------------------
set (SOURCE_CPP_CONTROL
    src/control/apa_control_command.cpp
)

HOLO_COMPILE_LIB(${PROJECT_NAME}_control
    SOURCES
    ${SOURCE_CPP_CONTROL}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_control)

set_target_properties(${PROJECT_NAME}_control PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_parking_base_sensors------------------------------------
set (SOURCE_CPP_CONTROL
    src/sensors/car_body_state.cpp
)

HOLO_COMPILE_LIB(${PROJECT_NAME}_sensors
    SOURCES
    ${SOURCE_CPP_CONTROL}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_sensors)

set_target_properties(${PROJECT_NAME}_sensors PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_parking_base_parking_manager------------------------------------
set (SOURCE_CPP_SYSTEM
    src/parking_manager/state_machine_from_gac_apa.cpp
)

HOLO_COMPILE_LIB(${PROJECT_NAME}_parking_manager
    SOURCES
    ${SOURCE_CPP_SYSTEM}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_parking_manager)

set_target_properties(${PROJECT_NAME}_parking_manager PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_parking_base_system------------------------------------
set (SOURCE_CPP_SYSTEM
    src/system/remote_control_signal.cpp
    src/system/tbox_command.cpp
    src/system/fapa_command.cpp
    src/system/hmi_command.cpp
    src/system/hmi_parking_state.cpp
    src/system/hpa_event_request.cpp
    src/system/hpa_event_response.cpp
    src/system/hpa_info.cpp
    src/system/hpa_control_output_command.cpp
    src/system/top_machine2hpa_machine.cpp
    src/system/cloud_path_info.cpp
)

HOLO_COMPILE_LIB(${PROJECT_NAME}_system
    SOURCES
    ${SOURCE_CPP_SYSTEM}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_system)

set_target_properties(${PROJECT_NAME}_system PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_parking_base_surrounding------------------------------------
set (SOURCE_CPP_SURROUNDING
    src/surrounding/luminous_intensity.cpp
    src/surrounding/obstacle_distance.cpp
    src/surrounding/slope.cpp
)

HOLO_COMPILE_LIB(${PROJECT_NAME}_surrounding
    SOURCES
    ${SOURCE_CPP_SURROUNDING}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base::holo_base_common
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_surrounding)

set_target_properties(${PROJECT_NAME}_surrounding PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_parking_base_metadata------------------------------------

# ------------------------- library ------------------------------------

HOLO_COMPILE_LIB(${PROJECT_NAME}_metadata
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    ${PROJECT_NAME}_vision
    holo_metadata_cpp::holo_metadata_cpp
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_metadata)

# -------------------------generated code------------------------------------
holo_compile_app(
    ${PROJECT_NAME}_metadata_generator
    SOURCES
    src/metadata/generator.cpp
    INCLUDES
    include
    LIBRARIES
    ${PROJECT_NAME}_metadata
    INSTALL_DIR
    share/${PROJECT_NAME}_metadata)

## -------------------------holo_parking_base end------------------------------------

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

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake @ONLY)

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
