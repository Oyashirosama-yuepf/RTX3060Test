cmake_minimum_required(VERSION 2.8)

find_package(ros_wrapper QUIET)

if(ros_wrapper_FOUND)
    ## ------------------------- COVERAGE -----------------------------------
    if(HOLO_BUILD_COVERAGE)
        if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
            set(HOLO_BUILD_TEST ON)
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -DNDEBUG --coverage")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DNDEBUG --coverage")
            GENERATE_COVERAGE_REPORT(TARGET ros_coverage EXCLUDE_PATTERNS
                "${PROJECT_BINARY_DIR}/src/*"
                "${PROJECT_SOURCE_DIR}/test/*"
                "${PROJECT_SOURCE_DIR}/example/*"
                "${PROJECT_SOURCE_DIR}/tools/*"
                )
        else()
            MESSAGE(FATAL_ERROR "Unable to generate coverage report! CMAKE_BUILD_TYPE is not DEBUG!")
        endif()
    endif()

    add_subdirectory(message)
    
    HOLO_COMPILE_LIB(${PROJECT_NAME}_ros
    SOURCES
    src/vision/point_feature_list_traits.cpp
    INCLUDES
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/devel/include>
    $<INSTALL_INTERFACE:include/holo_base_msg>
    LIBRARIES
    holo_cmw::ros_wrapper
    holo_parking_base::holo_parking_base_vision
    INSTALL_DIR lib
    INSTALL_EXPORT_DIR share/${PROJECT_NAME}/cmake
    NAMESPACE ${EXPORT_NAMESPACE}::
    EXPORT_COMPONENT ros
    )

    set_target_properties(${PROJECT_NAME}_ros PROPERTIES
        VERSION ${${PROJECT_NAME}_VERSION}
        SOVERSION ${${PROJECT_NAME}_SOVERSION}
    )

    add_dependencies(${PROJECT_NAME}_ros ${PROJECT_NAME}_generate_messages_cpp)

    if(HOLO_BUILD_TEST)
        add_subdirectory(test)
    endif()
    
    add_subdirectory(example)
    
    INSTALL(DIRECTORY include/${PROJECT_NAME} DESTINATION include/${PROJECT_NAME})
endif()
