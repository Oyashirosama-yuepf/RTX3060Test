cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(SET CMP0028 NEW)

project(holobag_gui)

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

option(HOLO_BUILD_ON_QNX "Build project on QNX" OFF)
if(${CMAKE_SYSTEM_NAME} STREQUAL "QNX")
set(HOLO_BUILD_ON_QNX ON)
endif()

# dependency configuration
set(DEPEND_HOLO_BASE_VERSION 0.1.0)
set(DEPEND_HOLO_BAG_VERSION 0.1.0)
set(DEPEND_HOLO_CMW_VERSION 0.1.0)
set(DEPEND_HOLO_MSG_VERSION 0.1.0)
set(DEPEND_GLOG_VERSION 0.4.0)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)

# Set C/CXX compiler flags.
# Required CXX_FLAGS are "-std=c++11 -Wall -Wextra -Werror". Required C_FLAGS are "-Wall -Wextra -Werror".
#
# DO NOT EDIT CXX_FLAGS AND C FLAGS!!!
# If additional flags are needed, explain the rationality.
#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")


set(EXPORT_NAMESPACE ${PROJECT_NAME})

# Set CMake variable for additional .cmake file search path.
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/HoloProjectConfiguration.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake/Modules")

# Find the QtWidgets library
find_package(holo_base ${DEPEND_HOLO_BASE_VERSION} REQUIRED)
find_package(holo_bag ${DEPEND_HOLO_BAG_VERSION} REQUIRED)
find_package(holo_cmw ${DEPEND_HOLO_CMW_VERSION} REQUIRED)
find_package(holo_msg ${DEPEND_HOLO_MSG_VERSION} REQUIRED)
find_package(GLOG ${DEPEND_GLOG_VERSION} REQUIRED)
find_package(Qt5 REQUIRED Widgets )
if(CMAKE_CROSSCOMPILING)
    set_property(TARGET Qt5::moc PROPERTY IMPORTED_LOCATION "/usr/bin/moc")
    set_property(TARGET Qt5::rcc PROPERTY IMPORTED_LOCATION "/usr/bin/rcc")
endif()

############## Targets ###########################
HOLO_COMPILE_CMW_APP(holobag_gui
                     SOURCES    ${PROJECT_SOURCE_DIR}/include/widget.h
                                ${PROJECT_SOURCE_DIR}/include/ui_widget.h
                                ${PROJECT_SOURCE_DIR}/include/control_play.h
                                ${PROJECT_SOURCE_DIR}/include/signal_and_slot.h
                                ${PROJECT_SOURCE_DIR}/include/custom_slider.h
                                ${PROJECT_SOURCE_DIR}/include/utils.h
                                ${PROJECT_SOURCE_DIR}/include/holo_replay.h
                                ${PROJECT_SOURCE_DIR}/src/widget.cpp
                                ${PROJECT_SOURCE_DIR}/src/main.cpp
                                ${PROJECT_SOURCE_DIR}/src/ui_widget.cpp   
                                ${PROJECT_SOURCE_DIR}/src/control_play.cpp 
                                ${PROJECT_SOURCE_DIR}/src/signal_and_slot.cpp 
                                ${PROJECT_SOURCE_DIR}/src/custom_slider.cpp 
                                ${PROJECT_SOURCE_DIR}/src/utils.cpp
                                ${PROJECT_SOURCE_DIR}/src/holo_replay.cpp    
                     INCLUDES   ${PROJECT_SOURCE_DIR}/include
                                ${PROJECT_BINARY_DIR}/include
                                ${PROJECT_SOURCE_DIR}/../cmw_app/include
                     LIBRARIES  holo_bag::holo_bag_interface 
                                holo_msg::holo_msg_opendds
                                holo_bag::holo_bag_storage
                                Qt5::Widgets 
                                )
                
############## Install/Uninstall #################
INSTALL(TARGETS ${${PROJECT_NAME}_APP_TARGETS} DESTINATION bin)

INSTALL(DIRECTORY Resource/ DESTINATION ${HOLO_CONFIG_ROOT}/holo_bag/Resource)

cmake_policy(POP)

