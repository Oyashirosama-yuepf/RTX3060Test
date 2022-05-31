cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)
cmake_policy(SET CMP0048 NEW)

project(holo_base)


## --------------------------- CONFIGURATIONS ----------------------------------------
#Set project version
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 13)
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
option(HOLO_CPU_PROFILE    "Use Google CPU Profiler"  ON)
option(HOLO_BUILD_SHARED   "Build shared library"     ON)
option(HOLO_BUILD_COVERAGE "Generate coverage report" OFF)
option(HOLO_CONFIG_USE_FIXED_SIZE_CONTAINER "Use fixed size container" OFF)

# dependency configuration
set(DEPEND_HOLO_BASE_C_VERSION 0.4.0)
set(DEPEND_EIGEN3_VERSION 3.3.7)
set(DEPEND_YAML_CPP_VERSION 0.6.2)
set(DEPEND_OPENCV_VERSION 3.3.1)
set(DEPEND_HOLO_UTILS_VERSION 0.4.0)
set(DEPEND_HOLO_METADATA_CPP_VERSION 0.1.1)

# Set C/CXX compiler flags.
# Required CXX_FLAGS are "-std=c++11 -Wall -Wextra -Werror". Required C_FLAGS are "-Wall -Wextra -Werror".
#
# DO NOT EDIT CXX_FLAGS AND C FLAGS!!!
# If additional flags are needed, explain the rationality.
#
#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fstack-protector-strong -Wno-error=deprecated-declarations -Wno-error=strict-aliasing")
set(CMAKE_CXX_STANDARD 14)

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
find_package(Eigen3 ${DEPEND_EIGEN3_VERSION} REQUIRED)
find_package(YAML-CPP ${DEPEND_YAML_CPP_VERSION} REQUIRED)
find_package(OPENCV ${DEPEND_OPENCV_VERSION} REQUIRED)
find_package(HOLO_UTILS ${DEPEND_HOLO_UTILS_VERSION} REQUIRED)
find_package(holo_metadata_cpp ${DEPEND_HOLO_METADATA_CPP_VERSION} REQUIRED)

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

## -------------------------generated code------------------------------------
include(ProjectConfig)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.in ${PROJECT_BINARY_DIR}/include/holo/core/config.h)

include(NumericsInstantiate)

## -------------------------holo_base_core------------------------------------
set (SOURCE_CPP_CORE
    src/core/epsilon.cpp
)
HOLO_COMPILE_LIB(${PROJECT_NAME}_core
    SOURCES
    ${SOURCE_CPP_CORE}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_base_c::holo_base_c
    holo_utils::holo_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_core)

set_target_properties(${PROJECT_NAME}_core PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_base_comomn------------------------------------
set (SOURCE_CPP_COMMON
    src/common/camera_base.cpp
    src/common/camera_fisheye.cpp
    src/common/classification.cpp
    src/common/details/intrinsic.cpp
    src/common/gnss_position.cpp
    src/common/image.cpp
    src/common/intrinsic.cpp
    #src/common/lane.cpp
    #src/common/lane_boundary.cpp
    src/common/path.cpp
    src/common/segmentation_2d.cpp
    #src/common/road_frame.cpp
    #src/common/holo_global_new_delete.cpp
    src/common/vehicle_specification.cpp
)
HOLO_COMPILE_LIB(${PROJECT_NAME}_common
    SOURCES
    ${SOURCE_CPP_COMMON}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_base_utils
    holo_utils::holo_utils
    holo_base_c::holo_base_c
    holo_base_core
    holo_base_numerics
    holo_base_geometry
    OPENCV::opencv
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_common)

set_target_properties(${PROJECT_NAME}_common PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_base_os------------------------------------
set (SOURCE_CPP_OS
    src/os/time.cpp
    src/os/timer.cpp
    src/os/tictoc_timer.cpp
)
HOLO_COMPILE_LIB(${PROJECT_NAME}_os
    SOURCES
    ${SOURCE_CPP_OS}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_base_c::holo_base_c
    holo_utils::holo_utils
    ${PROJECT_NAME}_common
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_os)

set_target_properties(${PROJECT_NAME}_os PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_base_filters------------------------------------
set (SOURCE_CPP_FILTERS
    src/filters/kalman_filter.cpp
)
HOLO_COMPILE_LIB(${PROJECT_NAME}_filters
    SOURCES
    ${SOURCE_CPP_FILTERS}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_base_c::holo_base_c
    holo_utils::holo_utils
    ${PROJECT_NAME}_numerics
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_filters)

set_target_properties(${PROJECT_NAME}_filters PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_base_freespace------------------------------------
set (SOURCE_CPP_FILTERS
    src/freespace/local_map_free_space.cpp
)
HOLO_COMPILE_LIB(${PROJECT_NAME}_freespace
    SOURCES
    ${SOURCE_CPP_FILTERS}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_base_c::holo_base_c
    holo_base_numerics
    holo_utils::holo_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_freespace)

set_target_properties(${PROJECT_NAME}_freespace PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_base_geometry----------------------------------
set (SOURCE_CPP_GEOMETRY
    src/geometry/geographical_transformation.cpp
    src/geometry/point3_spline.cpp
)

HOLO_COMPILE_LIB(${PROJECT_NAME}_geometry
    SOURCES
    ${SOURCE_CPP_GEOMETRY}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_base_numerics
    holo_utils::holo_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_geometry)

set_target_properties(${PROJECT_NAME}_geometry PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_base_numerics------------------------------------
set (SOURCE_CPP_NUMERICS
    src/numerics/eigen_solver.cpp
    src/numerics/spline.cpp
    src/numerics/utility.cpp
    ${NUMERICS_ADDITIONAL_SOURCES}
)
HOLO_COMPILE_LIB(${PROJECT_NAME}_numerics
    SOURCES
    ${SOURCE_CPP_NUMERICS}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_base_core
    holo_base_utils
    holo_utils::holo_utils
    Eigen3::Eigen
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_numerics)

set_target_properties(${PROJECT_NAME}_numerics PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)
## -------------------------holo_base_map------------------------------------
set (CPP_SOURCE_MAP 
    src/map/current_route_line.cpp
)
HOLO_COMPILE_LIB(${PROJECT_NAME}_map
    SOURCES
    ${CPP_SOURCE_MAP}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_base_c::holo_base_c
    holo_utils::holo_utils
    ${PROJECT_NAME}_common
    ${PROJECT_NAME}_geometry
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_map)

set_target_properties(${PROJECT_NAME}_map PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)


## -------------------------holo_base_utils----------------------------------
set (SOURCE_CPP_UTILS
    src/utils/holo_root.cpp
    src/utils/geographical_transformation.cpp
)

HOLO_COMPILE_LIB(${PROJECT_NAME}_utils
    SOURCES
    ${SOURCE_CPP_UTILS}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_utils::holo_utils
    YAML-CPP::yaml-cpp
    holo_base_c::holo_base_c
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_utils)

set_target_properties(${PROJECT_NAME}_utils PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_base_probability-------------------------------
set (SOURCE_CPP_PROBABILITY
    src/probability/ransac/ransac.cpp
    src/probability/ransac/ransac_line2_fitting_problem.cpp
    src/probability/ransac/ransac_plane3_fitting_problem.cpp
    src/probability/ransac/ransac_problem.cpp
    src/probability/ransac/ransac_problem_data_container_adapter.cpp
)
HOLO_COMPILE_LIB(${PROJECT_NAME}_probability
    SOURCES
    ${SOURCE_CPP_PROBABILITY}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_utils::holo_utils
    holo_base_geometry
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_probability)

set_target_properties(${PROJECT_NAME}_probability PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_base_obstacle------------------------------------
HOLO_COMPILE_LIB(${PROJECT_NAME}_obstacle
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_base_c::holo_base_c
    holo_base_geometry
    holo_base_common
    holo_base_numerics
    holo_base_vision
    holo_base_utils
    holo_utils::holo_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_obstacle)

## -------------------------holo_base_vision------------------------------------
set (SOURCE_CPP_VISION
    src/vision/keypoint2.cpp
)

HOLO_COMPILE_LIB(${PROJECT_NAME}_vision
    SOURCES
    ${SOURCE_CPP_VISION}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base_c::holo_base_c
    holo_base_common
    holo_base_numerics
    holo_utils::holo_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_vision)

set_target_properties(${PROJECT_NAME}_vision PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_base_prediction------------------------------------
set (SOURCE_CPP_PREDICTION
    src/prediction/intentions.cpp
)
HOLO_COMPILE_LIB(${PROJECT_NAME}_prediction
    SOURCES
    ${SOURCE_CPP_PREDICTION}
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_base_c::holo_base_c
    holo_utils::holo_utils
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
)

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME}_prediction)

set_target_properties(${PROJECT_NAME}_prediction PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
)

## -------------------------holo_base_metadata------------------------------------

# ------------------------- library ------------------------------------

HOLO_COMPILE_LIB(${PROJECT_NAME}_metadata
    INCLUDES
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    LIBRARIES
    holo_base_common
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

#if(NOT CMAKE_CROSSCOMPILING)
#    add_custom_command(
#        TARGET ${PROJECT_NAME}_metadata_generator
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E make_directory metadata
#        COMMAND ./${PROJECT_NAME}_metadata_generator
#        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/share/${PROJECT_NAME}_metadata
#        COMMENT "Generating holo_base_metadata")
#else()
#    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
#        add_custom_command(
#            TARGET ${PROJECT_NAME}_metadata_generator
#            POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E make_directory metadata
#            COMMAND ./${PROJECT_NAME}_metadata_generator
#            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/share/${PROJECT_NAME}_metadata
#            COMMENT "Generating holo_base_metadata")
#    endif()
#endif()


## -------------------------holo_base end------------------------------------

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
INSTALL(DIRECTORY ${PROJECT_BINARY_DIR}/include/holo DESTINATION include/${PROJECT_NAME} OPTIONAL COMPONENT development)
INSTALL(FILES "CHANGELOG.md" DESTINATION share/doc/${PROJECT_NAME})
install(DIRECTORY ${PROJECT_BINARY_DIR}/share/ DESTINATION share)

add_custom_target(uninstall 
    COMMAND cat install_manifest.txt | xargs rm 
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Uninstall")

cmake_policy(POP)
