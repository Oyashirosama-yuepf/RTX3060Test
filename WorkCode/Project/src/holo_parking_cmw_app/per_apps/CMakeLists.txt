cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)

project(holo_perception_parking_cmw_app)


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

# dependency configuration
set(DEPEND_HOLO_BASE_VERSION 0.1.0)
set(DEPEND_HOLO_PERCEPTION_BASE_VERSION 0.1.0)
set(DEPEND_HOLO_PERCEPTION_PARKING_VERSION 0.1.0)
set(DEPEND_HOLO_SENSORS_VERSION 0.1.0)
set(DEPEND_HOLO_CMW_VERSION 0.1.0)
set(DEPEND_GLOG_VERSION 0.4.0)

option(HOLO_PERCEPTION_BUILD_WITH_CUDA "Build on CUDA" ON)
option(HOLO_PERCEPTION_BUILD_WITH_TIDL "Build on TIDL" OFF)

# Set C/CXX compiler flags.
# Required CXX_FLAGS are "-std=c++11 -Wall -Wextra -Werror". Required C_FLAGS are "-Wall -Wextra -Werror".
#
# DO NOT EDIT CXX_FLAGS AND C FLAGS!!!
# If additional flags are needed, explain the rationality.
#
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")
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

set(EXPORT_NAMESPACE ${PROJECT_NAME})

############## Dependencies ######################
find_package(holo_base ${DEPEND_HOLO_BASE_VERSION} REQUIRED)
find_package(cmw_wrapper REQUIRED)
find_package(holo_sensors_base ${DEPEND_HOLO_SENSORS_VERSION} REQUIRED)
find_package(holo_perception_parking ${DEPEND_HOLO_PERCEPTION_PARKING_VERSION} REQUIRED)
find_package(holo_sensors_base ${DEPEND_HOLO_SENSORS_VERSION} REQUIRED)
# find_package(holo_cmw ${DEPEND_HOLO_CMW_VERSION} REQUIRED)
find_package(GLOG ${DEPEND_GLOG_VERSION} REQUIRED)
find_package(holo_parking_base REQUIRED)
find_package(holo_base_msg REQUIRED)
message("############################################")
message(${holo_base_msg_FOUND})
find_package(OpenCV 3.3.1 QUIET COMPONENTS
    calib3d
    core
    features2d
    flann
    highgui
    imgcodecs
    imgproc
    xfeatures2d
    cv_bridge
    )
find_package(FFMPEG REQUIRED COMPONENTS avcodec)
find_package(FFMPEG REQUIRED COMPONENTS avformat)
find_package(JPEG REQUIRED COMPONENTS JPEG)

set(DEPEND_BOOST_VERSION 1.65.1)
set(DEPEND_BOOST_COMPONENTS thread)
find_package(Protobuf ${DEPEND_PROTOBUF_VERSION} REQUIRED)
find_package(Boost ${DEPEND_BOOST_VERSION} REQUIRED COMPONENTS ${DEPEND_BOOST_COMPONENTS})
###################
find_package(Threads)


############## Dependent libs ######################
set(COMMON_LIBRARIES
    holo_base::holo_base_os
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_base::holo_base_numerics
    holo_base::holo_base_obstacle
    holo_base::holo_base_freespace
    holo_base::holo_base_vision
    holo_base_msg::holo_base_msg
    holo_perception_base::holo_perception_base
    holo_perception_parking::holo_perception_parking
    holo_sensors_base::holo_sensors_base_image_ipc
    ${OpenCV_LIBS}
    FFMPEG::avcodec 
    FFMPEG::avformat 
    JPEG::JPEG
    protobuf::libprotobuf
    Boost::thread
    
)

# ---------------------------------------------------------------
## HACK. If TI_PSDK is found, disable CUDA on all platform.
find_package(TI_PSDK)
if(${TI_PSDK_FOUND}) 
    MESSAGE(STATUS "TI_PSDK is found.")
    set(HOLO_PERCEPTION_BUILD_WITH_TIDL ON)
    add_library(TI_SELF_KERNEL INTERFACE IMPORTED)
    set_target_properties(
        TI_SELF_KERNEL
        PROPERTIES INTERFACE_LINK_LIBRARIES "${HOLO_ROOT}/lib/libvx_kernels_private_proc.a")
endif()

if(HOLO_PERCEPTION_BUILD_WITH_TIDL)
    set(HOLO_PERCEPTION_BUILD_WITH_CUDA OFF)
    set(HOLO_BUILD_TEST OFF)

    add_definitions(-DTIDL_INFERENCE)
endif()

if(HOLO_PERCEPTION_BUILD_WITH_CUDA)
    set(HOLO_PERCEPTION_BUILD_WITH_TIDL OFF)
    set(HOLO_BUILD_TEST OFF) 

    set(DEPEND_CUDA_VERSION 10.0)
    set(DEPEND_TensorRT_VERSION 5.0)
    set(DEPEND_CUDNN_VERSION 7)
    set(CUDA_LINK_LIBRARIES_KEYWORD PRIVATE)
    find_package(CUDA ${DEPEND_CUDA_VERSION} REQUIRED)
    find_package(CUDNN ${DEPEND_CUDNN_VERSION} REQUIRED)
    find_package(TensorRT ${DEPEND_TensorRT_VERSION} REQUIRED)
    message(STATUS "TensorRT_FOUND: " ${TensorRT_FOUND})

    add_definitions(-DHOLO_PERCEPTION_PARKING_ENGINE_TENSOR_RT)
    add_definitions(-DHOLO_PERCEPTION_PARKING_WITH_CUDA)
endif()


if(HOLO_PERCEPTION_BUILD_WITH_CUDA)
    message(STATUS "SET COMMON_LIBRARIES with CUDA : " ${HOLO_PERCEPTION_BUILD_WITH_CUDA})
    set(COMMON_LIBRARIES ${COMMON_LIBRARIES} holo_perception_parking::holo_perception_parking_backend_cuda )
endif()

if(HOLO_PERCEPTION_BUILD_WITH_TIDL)
    message(STATUS "SET COMMON_LIBRARIES with TIDL : " ${HOLO_PERCEPTION_BUILD_WITH_TIDL})
    set(COMMON_LIBRARIES ${COMMON_LIBRARIES} holo_perception_parking::holo_perception_parking_backend holo_perception_parking::holo_perception_parking_backend_tidl
                                             holo_perception_parking::tidl_inference)
endif()


## -------------------------holomacros------------------------------------
include(HoloMacros)


add_definitions(-DBUILD_ROS_CMW)
if(HOLO_PERCEPTION_BUILD_WITH_CUDA)
    # ROS 
    add_cmw_wrapper_executable(camera_obstacle_detection_parking_app_cmw
        SOURCES ${PROJECT_SOURCE_DIR}/src/perception/obstacle_detection/camera_obstacle_detection_parking_app.cpp
        INSTALL_DIR bin
        INCLUDES   ${PROJECT_SOURCE_DIR}/include 
        LIBRARIES  ${COMMON_LIBRARIES} 
        ROS)

    add_cmw_wrapper_executable(vision_freespace_app
        SOURCES ${PROJECT_SOURCE_DIR}/src/perception/vision_freespace/vision_freespace_app.cpp
        INSTALL_DIR bin
        INCLUDES   ${PROJECT_SOURCE_DIR}/include 
        LIBRARIES  ${COMMON_LIBRARIES} 
        ROS)
    # OpenDDS
    add_cmw_wrapper_executable(camera_obstacle_detection_parking_app_cmw
        SOURCES ${PROJECT_SOURCE_DIR}/src/perception/obstacle_detection/camera_obstacle_detection_parking_app.cpp
        INSTALL_DIR bin
        INCLUDES   ${PROJECT_SOURCE_DIR}/include 
        LIBRARIES  ${COMMON_LIBRARIES} 
        OPENDDS)

    add_cmw_wrapper_executable(vision_freespace_app
        SOURCES ${PROJECT_SOURCE_DIR}/src/perception/vision_freespace/vision_freespace_app.cpp
        INSTALL_DIR bin
        INCLUDES   ${PROJECT_SOURCE_DIR}/include 
        LIBRARIES  ${COMMON_LIBRARIES} 
        OPENDDS)
endif()

if(HOLO_PERCEPTION_BUILD_WITH_TIDL)
    ######temp to do find_package#######
    ###### ROS #######
    add_cmw_wrapper_executable(camera_obstacle_detection_parking_app_cmw
                SOURCES ${PROJECT_SOURCE_DIR}/src/perception/obstacle_detection/camera_obstacle_detection_parking_app.cpp
                INSTALL_DIR bin
                INCLUDES ${PROJECT_SOURCE_DIR}/include 
                LIBRARIES ${COMMON_LIBRARIES} 
                ROS)
    add_cmw_wrapper_executable(vision_freespace_app
                SOURCES ${PROJECT_SOURCE_DIR}/src/perception/vision_freespace/vision_freespace_app.cpp
                INSTALL_DIR bin
                INCLUDES ${PROJECT_SOURCE_DIR}/include
                LIBRARIES ${COMMON_LIBRARIES} 
                ROS)
    add_cmw_wrapper_executable(vision_parkingslot_app
                SOURCES ${PROJECT_SOURCE_DIR}/src/perception/vision_parkingslot/vision_parkingslot_app.cpp
                INSTALL_DIR bin
                INCLUDES ${PROJECT_SOURCE_DIR}/include
                LIBRARIES ${COMMON_LIBRARIES} 
                ROS)
    ###### DDS #######
    add_cmw_wrapper_executable(camera_obstacle_detection_parking_dds_app_cmw
                SOURCES ${PROJECT_SOURCE_DIR}/src/perception/obstacle_detection/camera_obstacle_detection_parking_app.cpp
                INSTALL_DIR bin
                INCLUDES ${PROJECT_SOURCE_DIR}/include 
                LIBRARIES ${COMMON_LIBRARIES} 
                OPENDDS DDS_MICRO)
    add_cmw_wrapper_executable(vision_freespace_dds_app
                SOURCES ${PROJECT_SOURCE_DIR}/src/perception/vision_freespace/vision_freespace_app.cpp
                INSTALL_DIR bin
                INCLUDES ${PROJECT_SOURCE_DIR}/include
                LIBRARIES ${COMMON_LIBRARIES} 
                OPENDDS DDS_MICRO)
    add_cmw_wrapper_executable(vision_parkingslot_dds_app
                SOURCES ${PROJECT_SOURCE_DIR}/src/perception/vision_parkingslot/vision_parkingslot_app.cpp
                INSTALL_DIR bin
                INCLUDES ${PROJECT_SOURCE_DIR}/include
                LIBRARIES ${COMMON_LIBRARIES} 
                OPENDDS)
endif(HOLO_PERCEPTION_BUILD_WITH_TIDL)  

############## Install/Uninstall #################
INSTALL(TARGETS ${${PROJECT_NAME}_APP_TARGETS} DESTINATION bin)
INSTALL(DIRECTORY app_config/ DESTINATION ${HOLO_CONFIG_ROOT}/holo_perception_parking/app_config)

add_custom_target(per_uninstall
	COMMAND cat install_manifest.txt | xargs rm
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	COMMENT "Uninstall")

cmake_policy(POP)
