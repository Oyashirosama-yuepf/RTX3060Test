cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)

project(holo_localization_parking)

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

# default options
option(HOLO_BUILD_APP "" ON)
option(HOLO_BUILD_TEST "" OFF)
option(HOLO_CPU_PROFILE "Use Google CPU Profiler" OFF)
option(HOLO_BUILD_SHARED "" ON)
option(HOLO_VISUALIZE_WITH_PCL "Visualization tools for offline mapping" OFF)
option(HOLO_BUILD_SDK "" OFF)
option(HOLO_LOOP_WITH_NETVLAD "Use netvlad to find loops" OFF)
option(HOLO_BUILD_AVP_MAPPING "Enable avp mapping" OFF)
option(HOLO_LOCALIZATION_BUILD_WITH_TIDL "Build with TIDL" OFF)

# dependency configuration
set(HOLO_LOCALIZATION_BASE_VERSION 0.1.0)
set(HOLO_IO_VERSION 0.1.0)
set(HOLO_3D_VERSION 0.1.0)
set(HOLO_PARKING_BASE_VERSION 0.1.0)
set(PCL_VERSION 1.8.1)
set(BOOST_VERSION)
set(HOLO_LOCALIZATION_DEEP_VERSION 0.1.0)
set(CUDA_VERSION 10.0)
set(CUDNN_VERSION 7)
set(TensorRT_VERSION 5.0)
set(HOLO_PANGOLIN_VERSION 0.5)

# Set C/CXX compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wno-error=deprecated-declarations")
set(CMAKE_C_STANDARD 99)

# export target configuration
set(EXPORT_NAMESPACE holo_localization)


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

set(HOLO_LOCALIZATION_PARKING_CONFIG_PREFIX ${HOLO_CONFIG_ROOT}/${PROJECT_NAME})
set(HOLO_LOCALIZATION_PARKING_LOG_PREFIX ${HOLO_LOG_ROOT}/${PROJECT_NAME})

## ------------------------- DEPENDENCIES --------------------------------
find_package(holo_localization_base ${HOLO_LOCALIZATION_BASE_VERSION} REQUIRED)
find_package(Boost ${BOOST_VERSION} REQUIRED)
find_package(holo_3d ${HOLO_3D_VERSION})
find_package(holo_io ${HOLO_IO_VERSION})
find_package(holo_parking_base ${HOLO_PARKING_BASE_VERSION} REQUIRED)
find_package(Pangolin ${HOLO_PANGOLIN_VERSION})

include(HoloMacros)

GENERATE_DOXYGEN(INPUT include src doc)

if(HOLO_BUILD_COVERAGE)
    if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
        set(HOLO_BUILD_TEST ON)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -DNDEBUG --coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DNDEBUG --coverage")
        GENERATE_COVERAGE_REPORT(EXCLUDE_PATTERNS
            <file patterns that should not appear in coverage report>
            # eg
            # "${PROJECT_BINARY_DIR}/src/*"
            "${PROJECT_SOURCE_DIR}/test/*"
            )
    else()
        MESSAGE(FATAL_ERROR "Unable to generate coverage report! CMAKE_BUILD_TYPE is not DEBUG!")
    endif()
endif()

if(HOLO_VISUALIZE_WITH_PCL)
    message(STATUS "Enable visualization with pcl!!!") 
    find_package(PCL ${PCL_VERSION})
    add_definitions(-DHOLO_VISUALIZE_WITH_PCL)
else()
    message(STATUS "Disable visualization with pcl!!!") 
endif(HOLO_VISUALIZE_WITH_PCL)

if(PCL_FOUND)
    include_directories(SYSTEM ${PCL_INCLUDE_DIRS})
    list(APPEND OPTIONAL_LIBRARIES ${PCL_LIBRARIES})
endif()

if(Pangolin_FOUND)
    message(STATUS "Enable visualization with pangolin!!!") 
    include_directories(SYSTEM ${Pangolin_INCLUDE_DIRS})
    list(APPEND OPTIONAL_LIBRARIES ${Pangolin_LIBRARIES})
    add_definitions(-DHOLO_VISUALIZE_WITH_PANGOLIN)
else()
    message(STATUS "Disable visualization with pangolin!!!") 
endif()


if(HOLO_LOOP_WITH_NETVLAD)
    message(STATUS "Enable find loop with netvlad!!!")
    find_package(holo_localization_deep ${HOLO_LOCALIZATION_DEEP_VERSION})
    find_package(CUDA ${CUDA_VERSION})
    find_package(CUDNN ${CUDNN_VERSION})
    find_package(TensorRT ${TensorRT_VERSION})
    add_definitions(-DHOLO_LOOP_WITH_NETVLAD)
else()
    message(STATUS "Disable find loop with netvlad!!!")
endif(HOLO_LOOP_WITH_NETVLAD)

if(HOLO_BUILD_AVP_MAPPING)
    message(STATUS "Enable AVP mapping model")
    set(AVP_SOURCES src/vision/vslam/mapping/avp_mapping.cpp)
    find_package(TI_PSDK QUIET)
    find_package(holo_localization_deep ${HOLO_LOCALIZATION_DEEP_VERSION})
    if(${TI_PSDK_FOUND} AND ${holo_localization_deep_FOUND})
        add_definitions("-DUSE_NV12")
        message(STATUS "Build AVP mapping with tda4.")
    elseif(NOT ${TI_PSDK_FOUND} AND ${holo_localization_deep_FOUND})
        find_package(CUDA ${CUDA_VERSION})
        find_package(CUDNN ${CUDNN_VERSION})
        find_package(TensorRT ${TensorRT_VERSION})
        message(STATUS "Build AVP mapping with cuda.")
    endif()
endif()

if(holo_localization_deep_FOUND)
    message("Found holo localization deep sucess!!!")
    list(APPEND OPTIONAL_LIBRARIES
    holo_localization::holo_localization_deep)
    if(CUDNN_FOUND AND TensorRT_FOUND AND CUDA_FOUND)
    message("Found cuda tensorRT cudnn success!!!")
    list(APPEND OPTIONAL_LIBRARIES
    ${CUDA_LIBRARIES}
    CUDNN::cudnn
    TensorRT::TensorRT)
    endif()
endif()

if(HOLO_LOCALIZATION_BUILD_WITH_TIDL)
    set(TI_PSDK_VERSION 07.01.00.11)
    message(STATUS "Enable do desc matching with tidl")
    set(TIDL_SOURCES src/vision/tidl/app_nms.cpp
                     src/vision/tidl/tivx_hirain_threshold_host.c
                     src/vision/tidl/tivx_img_proc_node_api.c
                     src/vision/tidl/vx_kernels_img_proc_host.c) 
    find_package(TI_PSDK ${TI_PSDK_VERSION})
    if(${TI_PSDK_FOUND}) 
    message(STATUS "TI_PSDK is found.")
    elseif()
    message(STATUS "TI_PSDK is not found !!!")
    endif()
    list(APPEND OPTIONAL_LIBRARIES
    TI_PSDK::tiovx
    TI_PSDK::psdk
    TI_PSDK::vision_apps
    )
    add_definitions("-Drestrict=__restrict__")
    add_definitions(-DHOLO_LOCALIZATION_BUILD_WITH_TIDL)
endif()


## --------------------------- SOURCES ----------------------------------------
message("INCLUDES" ${INCLUDES})
## --------------------------General--------------------------------------
HOLO_COMPILE_LIB(${PROJECT_NAME}
    SOURCES
    src/vision/3rdparty/BowVector.cpp
    src/vision/3rdparty/DescManip.cpp
    src/vision/3rdparty/ScoringObject.cpp
    src/vision/3rdparty/Vocabulary.cpp
    src/vision/geometry/fundamental_matrix_algorithm.cpp
    src/vision/geometry/fundamental_matrix_solver.cpp
    src/vision/geometry/ransac_fundamental_matrix_problem.cpp
    src/vision/vslam/common_types.cpp
    src/vision/vslam/descriptor_matcher.cpp
    src/vision/vslam/essential_matrix_factor.cpp
    src/vision/vslam/failure_detection.cpp
    src/vision/vslam/feature_associator.cpp
    src/vision/vslam/feature_track.cpp
    src/vision/vslam/intrinsic.cpp
    src/vision/vslam/graph_builder.cpp
    src/vision/vslam/initializer.cpp
    src/vision/vslam/json_saver.cpp
    src/vision/vslam/landmark.cpp
    src/vision/vslam/localization/localization.cpp
    src/vision/vslam/localization/relocalization.cpp
    src/vision/vslam/mapping/global_optimizer.cpp
    src/vision/vslam/measurements_manager_vslam.cpp
    src/vision/vslam/mapping/common_types.cpp
    src/vision/vslam/mapping/loop_detector.cpp
    src/vision/vslam/mapping/map_database_manager.cpp
    src/vision/vslam/mapping/mapping.cpp
    src/vision/vslam/mapping/sub_mapping.cpp
    src/vision/vslam/mapping/visualizer.cpp
    src/vision/vslam/pose_only_unit3_factor.cpp
    src/vision/vslam/raw_measurement_preprocessor.cpp
    src/vision/vslam/rotation_only_imu_factor.cpp
    src/vision/vslam/semantic/common_types.cpp
    src/vision/vslam/semantic/data_association.cpp
    src/vision/vslam/semantic/hungarian_optimizer.cpp
    src/vision/vslam/semantic/psf_measurement_manager.cpp
    src/vision/vslam/semantic/parking_slot_fusion.cpp
    src/vision/vslam/semantic/parking_slot_parallel_factor.cpp
    src/vision/vslam/semantic/parking_slot_point_plane_factor.cpp
    src/vision/vslam/semantic/parking_slot_projection_factor.cpp
    src/vision/vslam/semantic/parking_slot_vertex_factor.cpp
    src/vision/vslam/semantic/visualizer.cpp
    src/vision/vslam/sliding_window_estimator.cpp
    src/vision/vslam/sliding_window_state.cpp
    src/vision/vslam/track_state_transition.cpp
    src/vision/vslam/tracker.cpp
    src/vision/vslam/triangulator.cpp
    src/vision/vslam/tools/source_checker.cpp
    src/vision/vslam/unit3_factor.cpp
    src/vision/vslam/velocity_factor.cpp
    src/vision/vslam/visualizer.cpp
    src/vision/vslam/vslam_base.cpp
    src/vision/vslam/wheel_integration.cpp
    ${AVP_SOURCES}
    ${TIDL_SOURCES}
    INCLUDES
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    LIBRARIES
    holo_io::holo_io_odometry
    holo_localization::holo_localization_base
    holo_3d::holo_3d
    holo_parking_base::holo_parking_base_vision
    ${OPTIONAL_LIBRARIES}
    Boost::boost
    INSTALL_DIR lib
    NAMESPACE ${EXPORT_NAMESPACE}::
    )

set(${PROJECT_NAME}_TARGETS ${${PROJECT_NAME}_TARGETS} ${PROJECT_NAME})

if(HOLO_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif(HOLO_BUILD_TEST)

if(HOLO_BUILD_APP)
    add_subdirectory(app)
endif(HOLO_BUILD_APP)

include(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake @ONLY)

INSTALL(FILES ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    DESTINATION lib/cmake/${PROJECT_NAME})
INSTALL(FILES ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake DESTINATION lib/cmake/${PROJECT_NAME})
INSTALL(DIRECTORY include/holo DESTINATION include/${PROJECT_NAME})

if(HOLO_BUILD_SDK)
    INSTALL(DIRECTORY config/app/sdk/ DESTINATION ${HOLO_LOCALIZATION_PARKING_CONFIG_PREFIX}/lib_config/app)
else()
    INSTALL(DIRECTORY config/ DESTINATION ${HOLO_LOCALIZATION_PARKING_CONFIG_PREFIX}/lib_config)
endif(HOLO_BUILD_SDK)

add_custom_target(uninstall 
    COMMAND cat install_manifest.txt | xargs rm
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Uninstall")

cmake_policy(POP)
