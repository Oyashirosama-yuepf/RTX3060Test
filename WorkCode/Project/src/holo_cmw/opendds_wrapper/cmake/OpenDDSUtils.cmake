function(opendds_wrapper_compile_idl_files)
    cmake_parse_arguments(
        ARG "INSTALL" "TARGET" "FILES;DIRECTORIES;OPTIONS;DEPENDENCIES;INCLUDES"
        ${ARGN})
    set(OPENDDS_IDL_FILE_LIST)

    if(NOT ARG_TARGET)
        set(ARG_TARGET ${PROJECT_NAME}_opendds_gen)
    endif()

    list(APPEND OPENDDS_IDL_FILE_LIST ${ARG_FILES})
    foreach(dir ${ARG_DIRECTORIES})
        file(GLOB_RECURSE IDL_FILES "${dir}/*.idl")
        list(APPEND OPENDDS_IDL_FILE_LIST ${IDL_FILES})
    endforeach()
    list(REMOVE_DUPLICATES OPENDDS_IDL_FILE_LIST)

    set(INCLUDE_DIRS)
    set(DEPEND_LIBS)
    list(APPEND INCLUDE_DIRS ${ARG_INCLUDES})
    foreach(dep ${ARG_DEPENDENCIES})
        find_package(${dep} REQUIRED)
        list(APPEND DEPEND_LIBS ${dep}::${dep}_opendds)
        list(APPEND INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/share/${dep})
    endforeach()
    if(INCLUDE_DIRS)
        list(REMOVE_DUPLICATES INCLUDE_DIRS)
    endif()

    foreach(_idl_file ${OPENDDS_IDL_FILE_LIST})
        file(RELATIVE_PATH _idl_file_rpath "${CMAKE_CURRENT_LIST_DIR}"
             "${_idl_file}")
        get_filename_component(_idl_file_rdir "${_idl_file_rpath}" DIRECTORY)
        opendds_compile_idl_file(
            ${_idl_file}
            OUTPUT_DIR
            "${PROJECT_BINARY_DIR}/include/${_idl_file_rdir}"
            INCLUDE_DIRS
            ${INCLUDE_DIRS}
            OPTIONS
            ${ARG_OPTIONS})
        list(APPEND OPENDDS_GENERATED_HEADER_FILES
             ${OPENDDS_IDL_GENERATED_HEADER_FILES})
        list(APPEND OPENDDS_GENERATED_SOURCE_FILES
             ${OPENDDS_IDL_GENERATED_SOURCE_FILES})
    endforeach()

    add_library(${ARG_TARGET} OBJECT ${OPENDDS_GENERATED_SOURCE_FILES}
                                     ${OPENDDS_GENERATED_HEADER_FILES})
    target_link_libraries(${ARG_TARGET} PUBLIC OPENDDS::opendds ${DEPEND_LIBS})
    target_include_directories(${ARG_TARGET}
                               PUBLIC ${PROJECT_BINARY_DIR}/include)
    target_compile_options(${ARG_TARGET} PUBLIC "-fPIC")

    if(ARG_INSTALL)
        install(
            DIRECTORY ${PROJECT_BINARY_DIR}/include/
            DESTINATION include/${PROJECT_NAME}
            FILES_MATCHING
            PATTERN "*.h"
            PATTERN "*.inl")
        install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}
                DESTINATION share/${PROJECT_NAME})
    endif()
endfunction()
