cmake_minimum_required(VERSION 2.8)

find_package(dds_micro_wrapper QUIET)

file(GLOB_RECURSE DDS_MICRO_SRC
    "*.cxx"
)

if(dds_micro_wrapper_FOUND)
    ## ------------------------- COVERAGE -----------------------------------
    if(HOLO_BUILD_COVERAGE)
        if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
            set(HOLO_BUILD_TEST ON)
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -DNDEBUG --coverage")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DNDEBUG --coverage")
            GENERATE_COVERAGE_REPORT(TARGET dds_micro_coverage EXCLUDE_PATTERNS
                "${PROJECT_BINARY_DIR}/*"
                "${PROJECT_SOURCE_DIR}/test/*"
                "${PROJECT_SOURCE_DIR}/example/*"
                "${PROJECT_SOURCE_DIR}/tools/*"
                )
        else()
            MESSAGE(FATAL_ERROR "Unable to generate coverage report! CMAKE_BUILD_TYPE is not DEBUG!")
        endif()
    endif()
    
    INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/holo_parking_msg/holo_base_msg DESTINATION ${HOLO_ROOT}/include/${PROJECT_NAME}/${PROJECT_NAME})
    HOLO_COMPILE_LIB(${PROJECT_NAME}_dds_micro
    SOURCES
    src/vision/point_feature_list_traits.cpp
    ${DDS_MICRO_SRC}
    INCLUDES
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    LIBRARIES
    holo_cmw::dds_micro_wrapper
    holo_parking_base::holo_parking_base_vision
    INSTALL_DIR lib
    INSTALL_EXPORT_DIR share/${PROJECT_NAME}/cmake
    NAMESPACE ${EXPORT_NAMESPACE}::
    EXPORT_COMPONENT dds_micro
    )

    set_target_properties(${PROJECT_NAME}_dds_micro PROPERTIES
        VERSION ${${PROJECT_NAME}_VERSION}
        SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )

    if(HOLO_BUILD_TEST)
        add_subdirectory(test)
    endif()
    
    INSTALL(DIRECTORY include/${PROJECT_NAME} DESTINATION include/${PROJECT_NAME})
endif()

