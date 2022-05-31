cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)
cmake_policy(SET CMP0048 NEW)

project(holo_sensors_c)

## --------------------------- CONFIGURATIONS ----------------------------------------
#Set project version
set(${PROJECT_NAME}_VERSION_MAJOR   0)
set(${PROJECT_NAME}_VERSION_MINOR   3)
set(${PROJECT_NAME}_VERSION_PATCH   0)
set(${PROJECT_NAME}_SOVERSION       ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR})
set(${PROJECT_NAME}_VERSION         ${${PROJECT_NAME}_SOVERSION}.${${PROJECT_NAME}_VERSION_PATCH})

if(HOLO_BUILD_VERSION)
    set(${PROJECT_NAME}_VERSION_TWEAK)
    set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION}.${HOLO_BUILD_VERSION})
endif(HOLO_BUILD_VERSION)

set(PROJECT_VERSION ${${PROJECT_NAME}_VERSION})

# default options
if (CMAKE_SYSTEM_PROCESSOR STREQUAL TriCore)
    option(HOLO_BUILD_TEST   "Build unit test"      OFF)
    option(HOLO_BUILD_SHARED "Build shared library" OFF)
else ()
    option(HOLO_BUILD_TEST   "Build unit test"      ON)
    option(HOLO_BUILD_SHARED "Build shared library" ON)
endif ()
option(HOLO_MATRIX_ALIGN   "Whether matrix should be aligned" OFF)
option(HOLO_BUILD_COVERAGE "Generate coverage report"         OFF)

# dependency configuration
set(DEPEND_HOLO_BASE_C_VERSION 0.1.0)

# Set C/CXX compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_C_STANDARD 99)

# export target configuration
set(EXPORT_NAMESPACE ${PROJECT_NAME})

## -------------------------- CMAKE_SETUP ---------------------------------------

# Set CMake variable to build shared library or static library.
if(HOLO_BUILD_SHARED)
    set(BUILD_SHARED_LIBS ON)
else()
    set(BUILD_SHARED_LIBS OFF)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wno-unused-function")

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
find_package(holo_base_c ${DEPEND_HOLO_BASE_C_VERSION} REQUIRED)

## -------------------------holomacros------------------------------------
include(HoloMacros)

## ------------------------- DOXYGEN-------------------------------------
GENERATE_DOXYGEN(OPTIMIZE_OUTPUT_FOR_C INPUT src doc
    include/sensors/aceinna
    include/sensors/can
    include/sensors/conti_radar
    include/sensors/ifv300
    include/sensors/mobileye
    include/sensors/mpc
    include/sensors/tc297_cpu
    include/sensors/ublox
    include/sensors/uss
    include/sensors/vehicle_body_state
    )

## ------------------------- COVERAGE -----------------------------------
if(HOLO_BUILD_COVERAGE)
    if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
        set(HOLO_BUILD_TEST ON)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -DNDEBUG --coverage")
        GENERATE_COVERAGE_REPORT(EXCLUDE_PATTERNS
            "${PROJECT_SOURCE_DIR}/3rdparty/*"
            "${PROJECT_SOURCE_DIR}/test/*"
            "${PROJECT_BINARY_DIR}/src/*")
    else()
        MESSAGE(FATAL_ERROR "Unable to generate coverage report! CMAKE_BUILD_TYPE is not DEBUG!")
    endif()
endif()

## -------------------------generated code------------------------------------

## ------------------------- library ------------------------------------
HOLO_COMPILE_LIB(${PROJECT_NAME}
    SOURCES
    src/sensors/aceinna/aceinna_imu_driver.c
    src/sensors/can/vehicle_can_driver.c
    src/sensors/conti_radar/conti_radar_driver.c
    src/sensors/conti_radar/structure/conti_radar_object.c
    src/sensors/mpc/mpc_driver.c
    src/sensors/mpc/structure/mpc_object.c
    src/sensors/mpc/structure/mpc_line.c
    src/sensors/ublox/ublox_cfg.c
    src/sensors/ublox/ublox_driver.c
    src/sensors/ublox/ubx_msg.c
    src/sensors/ublox/ubx_parse.c
    src/sensors/uss/bosch_uss_driver.c
    src/sensors/tc297_cpu/cpu_state.c
    src/sensors/vehicle_body_state/vehicle_body_state.c
    src/sensors/ifv300/ifv300_driver.c
    src/sensors/ifv300/structure/ifv300_object.c
    src/sensors/ifv300/structure/ifv300_line.c
    src/sensors/mobileye/mobileye_driver.c
    src/sensors/mobileye/structure/mobileye_lane.c
    src/sensors/mobileye/structure/mobileye_object.c
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base_c::holo_base_c
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)
if (HOLO_MATRIX_ALIGN)
    target_compile_definitions(${PROJECT_NAME} PUBLIC MATRIX_ALIGN)
endif()

#if(CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64)
#    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -fpack-struct=4)
#endif()

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

#--------------------------- test ---------------------------------------
if(HOLO_BUILD_TEST)
    set(UNITY_VERSION 2.4.3)
    add_library(unity 3rdparty/Unity-${UNITY_VERSION}/src/unity.c)
    include_directories(3rdparty/Unity-${UNITY_VERSION}/src)
    target_compile_definitions(unity PUBLIC UNITY_INCLUDE_DOUBLE)
    enable_testing()
    add_subdirectory(test)
endif(HOLO_BUILD_TEST)

#--------------------------- config version -----------------------------
include(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in
    ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake
    @ONLY
)

INSTALL(FILES ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake 
    DESTINATION lib/cmake/${PROJECT_NAME}
)

INSTALL(DIRECTORY include/holo_c DESTINATION include/${PROJECT_NAME})
INSTALL(DIRECTORY ${PROJECT_BINARY_DIR}/include/holo_c DESTINATION include/${PROJECT_NAME} OPTIONAL)

#--------------------------- uninstall command --------------------
add_custom_target(uninstall 
    COMMAND cat install_manifest.txt | xargs rm 
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Uninstall"
)

cmake_policy(POP)

