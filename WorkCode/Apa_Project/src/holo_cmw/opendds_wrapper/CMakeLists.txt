cmake_minimum_required(VERSION 2.8)

project(opendds_wrapper)

OPTION(OPENDDS_WRAPPER_BUILD_TOOLS "Build opendds tools" ON)

set(${PROJECT_NAME}_VERSION_MAJOR   ${${CMAKE_PROJECT_NAME}_VERSION_MAJOR})
set(${PROJECT_NAME}_VERSION_MINOR   ${${CMAKE_PROJECT_NAME}_VERSION_MINOR})
set(${PROJECT_NAME}_VERSION_PATCH   ${${CMAKE_PROJECT_NAME}_VERSION_PATCH})
set(${PROJECT_NAME}_SOVERSION       ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR})
set(${PROJECT_NAME}_VERSION         ${${PROJECT_NAME}_SOVERSION}.${${PROJECT_NAME}_VERSION_PATCH})

if (HOLO_BUILD_VERSION)
    set(${PROJECT_NAME}_VERSION     ${${PROJECT_NAME}_VERSION}.${HOLO_BUILD_VERSION})
    set(${PROJECT_NAME}_VERSION_TWEAK)
endif (HOLO_BUILD_VERSION)

if(NOT DEPEND_OPENDDS_VERSION)
    set(DEPEND_OPENDDS_VERSION 3.16)
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
include(HoloProjectConfiguration)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HOLO_ROOT}/cmake/Modules")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

## -------------------------holomacros------------------------------------
include(HoloMacros)
include(OpenDDSUtils)

## ------------------------- DOXYGEN-------------------------------------
GENERATE_DOXYGEN(INPUT include src)

find_package(OPENDDS ${DEPEND_OPENDDS_VERSION} REQUIRED)

if(OPENDDS_FOUND)
    find_package(holo_utils REQUIRED)

    add_subdirectory(message)
    set_source_files_properties(${OPENDDS_IDL_GENERATED_HEADER_FILES} ${OPENDDS_IDL_GENERATED_SOURCE_FILES} PROPERTIES GENERATED TRUE)

    add_library(${PROJECT_NAME} src/opendds/bus.cpp src/opendds/waitset.cpp $<TARGET_OBJECTS:${PROJECT_NAME}_opendds_gen>)
    
    target_include_directories(${PROJECT_NAME} PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
    target_link_libraries(${PROJECT_NAME} PUBLIC OPENDDS::opendds holo_utils::holo_utils)

    set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${${PROJECT_NAME}_VERSION}
        SOVERSION ${${PROJECT_NAME}_SOVERSION}
        INSTALL_RPATH "\$ORIGIN;\$ORIGIN/../3rdparty/lib"
    )

    add_subdirectory(example)

    configure_file(cmake/${PROJECT_NAME}-config.cmake.in ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake @ONLY)
    
    INSTALL(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets DESTINATION lib)
    INSTALL(EXPORT ${PROJECT_NAME}-targets NAMESPACE "holo_cmw::" DESTINATION share/${PROJECT_NAME}/cmake)
    INSTALL(FILES ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake DESTINATION share/${PROJECT_NAME}/cmake)
    INSTALL(FILES cmake/OpenDDSUtils.cmake DESTINATION share/${PROJECT_NAME}/cmake)
    INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include/${PROJECT_NAME})
    INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/config/ DESTINATION config)
    INSTALL(FILES ${PROJECT_SOURCE_DIR}/config/setenv.bash DESTINATION ${CMAKE_INSTALL_PREFIX})

    if(OPENDDS_WRAPPER_BUILD_TOOLS)
        add_subdirectory(tools/monitor)
    endif()
endif()
