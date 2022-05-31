# Compile unit test [DEPRECATED!!!!]
macro(CompileTest program lib_support)
    get_filename_component(filename ${program} NAME)
    get_filename_component(path ${program} DIRECTORY)
    add_executable(${filename} ${program}.cpp)
    target_link_libraries(${filename} PRIVATE ${lib_support})
    set_property(TARGET ${filename} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${path})
    add_test(
        NAME ${filename}
        COMMAND ${filename}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endmacro()

#
# Compile holo test programs
#
# Usage: HOLO_COMPILE_TEST(main [SOURCES additional_sources ...] [INCLUDES dirs
# ...] [LIBRARIES libs ...] [DEFINITIONS defs ...] )
#
# main: main function source file(with extension) SOURCES: keyword used to
# specify addtional source files INCLUDES: keyword used to specify include
# directories LIBRARIES: keyword used to specify link libraries DEFINITIONS:
# keyword used to specify compiler definitions
function(HOLO_COMPILE_TEST main)
    cmake_parse_arguments(COMPILE "" ""
                          "SOURCES;LIBRARIES;INCLUDES;DEFINITIONS" ${ARGN})

    if(NOT main)
        message(FATAL_ERROR "Main source file not given")
    endif()

    get_filename_component(target ${main} NAME_WE)
    get_filename_component(path ${main} DIRECTORY)

    if(NOT IS_ABSOLUTE path)
        set(path ${CMAKE_CURRENT_LIST_DIR}/${path})
    endif()

    file(RELATIVE_PATH relpath ${PROJECT_SOURCE_DIR} ${path})
    string(REPLACE "/" "_" target_prefix ${relpath})

    set(target_name ${PROJECT_NAME}_${target_prefix}_${target})

    add_executable(${target_name} ${main} ${COMPILE_SOURCES})
    target_link_libraries(${target_name} PRIVATE ${COMPILE_LIBRARIES})
    target_include_directories(${target_name} PRIVATE ${COMPILE_INCLUDES})
    target_compile_definitions(${target_name} PRIVATE ${COMPILE_DEFINITIONS})
    set_property(TARGET ${target_name} PROPERTY RUNTIME_OUTPUT_DIRECTORY
                                                ${relpath})
    set_property(TARGET ${target_name} PROPERTY RUNTIME_OUTPUT_NAME ${target})
    file(RELATIVE_PATH test_name ${CMAKE_BINARY_DIR}
         ${PROJECT_BINARY_DIR}/${relpath}/${target})
    add_test(
        NAME ${test_name}
        COMMAND ${relpath}/${target}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
endfunction()

# Compile holo application Usage: HOLO_COMPILE_APP(app_target [SOURCES] src1
# [src2 ...] [INSTALL_DIR dst_dir] [INCLUDES dir1 ...] [LIBRARIES lib1 ...]
# [DEFINITIONS def1 ...]
#
# "app_target" is the application target name, The target name should be unique
# in a cmake project. "SOURCES" keyword is used to specify source files of the
# target. SOURCES keyword can be omitted. "INSTALL_DIR" keyword is used to
# specify the installation directory of the target. The install directory is
# forced relative to $HOLO_ROOT. If INSTALL_DIR is not specified, this
# application will not be installed. "INCLUDES" keyword is used to specify
# include direcotries. "LIBRARIES" keyword is used to specify link libraries
# "DEFINITIONS" keyword is used to specify target definitions.
#
function(HOLO_COMPILE_APP target)
    cmake_parse_arguments(
        COMPILE "" "INSTALL_DIR;NAMESPACE"
        "SOURCES;INCLUDES;LIBRARIES;DEFINITIONS,RPATHS" ${ARGN})

    # Check if target name is specified
    if(NOT target)
        message(FATAL_ERROR "Target name not specified!")
    endif(NOT target)

    if(IS_ABSOLUTE ${COMPILE_INSTALL_DIR})
        message(FATAL_ERROR "INSTALL_DIR only accept relative path!")
    endif()

    if(NOT COMPILE_RPATHS)
        set(COMPILE_RPATHS ${HOLO_ROOT}/lib ${HOLO_ROOT}/3rdparty/lib)
    endif()

    # Check if source files are specifed
    if(NOT COMPILE_SOURCES)
        if(NOT COMPILE_UNPARSED_ARGUMENTS)
            message(FATAL_ERROR "No source file specified for target ${target}")
        endif(NOT COMPILE_UNPARSED_ARGUMENTS)
        set(_sources ${COMPILE_UNPARSED_ARGUMENTS})
    else(NOT COMPILE_SOURCES)
        set(_sources ${COMPILE_SOURCES})
    endif(NOT COMPILE_SOURCES)

    add_executable(${target} ${_sources})
    target_include_directories(${target} PRIVATE ${COMPILE_INCLUDES})
    target_link_libraries(${target} PRIVATE ${COMPILE_LIBRARIES})
    target_compile_definitions(${target} PRIVATE ${COMPILE_DEFINITIONS})

    if(COMPILE_INSTALL_DIR)
        # calculate rpath
        foreach(input_rpath ${COMPILE_RPATHS})
            if(IS_ABSOLUTE ${input_rpath})
                file(RELATIVE_PATH actual_rpath
                     ${CMAKE_INSTALL_PREFIX}/${COMPILE_INSTALL_DIR}
                     ${input_rpath})
                set_property(
                    TARGET ${target}
                    APPEND
                    PROPERTY INSTALL_RPATH "\$ORIGIN/${actual_rpath}")
            else()
                set_property(
                    TARGET ${target}
                    APPEND
                    PROPERTY INSTALL_RPATH "\$ORIGIN/${input_rpath}")
            endif()
        endforeach()
        set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                   "${COMPILE_INSTALL_DIR}")

        install(
            TARGETS ${target}
            DESTINATION ${COMPILE_INSTALL_DIR}
            COMPONENT runtime)
    endif(COMPILE_INSTALL_DIR)

endfunction(HOLO_COMPILE_APP)

# Install holo application Usage: HOLO_INSTALL_APP(app_target [DESTINATION
# dest]) "app_target" is the application target name. "DESTINATION" keyword is
# used to specify application installation directory. The installation directory
# is relative to $HOLO_ROOT. If DESTINATION is not specified, application will
# install to default directory $HOLO_ROOT/bin
#
function(HOLO_INSTALL_APP target)
    cmake_parse_arguments(HOLO_INSTALL "" "DESTINATION" "RPATHS" ${ARGN})

    if(IS_ABSOLUTE ${HOLO_INSTALL_DESTINATION})
        message(FATAL_ERROR "DESTINATION only accept relative path!")
    endif()

    if(NOT HOLO_INSTALL_DESTINATION)
        set(HOLO_INSTALL_DESTINATION bin)
    endif()

    if(NOT HOLO_INSTALL_RPATHS)
        set(HOLO_INSTALL_RPATHS ${HOLO_ROOT}/lib ${HOLO_ROOT}/3rdparty/lib)
    endif()

    foreach(input_rpath ${HOLO_INSTALL_RPATHS})
        if(IS_ABSOLUTE ${input_rpath})
            file(RELATIVE_PATH actual_rpath
                 ${CMAKE_INSTALL_PREFIX}/${HOLO_INSTALL_DESTINATION}
                 ${input_rpath})
            set_property(
                TARGET ${target}
                APPEND
                PROPERTY INSTALL_RPATH "\$ORIGIN/${actual_rpath}")
        else()
            set_property(
                TARGET ${target}
                APPEND
                PROPERTY INSTALL_RPATH "\$ORIGIN/${input_rpath}")
        endif()
    endforeach()
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                               ${HOLO_INSTALL_DESTINATION})
    install(TARGETS ${target} DESTINATION ${HOLO_INSTALL_DESTINATION})
endfunction(HOLO_INSTALL_APP)

# Compile holo library Usage: HOLO_COMPILE_LIB(lib_target [SOURCES] src1 [src2
# ...] [INSTALL_DIR dst_dir] [INCLUDES dir1 ...] [LIBRARIES lib1 ...]
# [DEFINITIONS def1 ...]) [NAMESPACE namespace])
#
# "lib_target" is the library target name, The target name should be unique in a
# cmake project. "SOURCES" keyword is used to specify source files of the
# target. SOURCES keyword can be omitted. "INSTALL_DIR" keyword is used to
# specify the installation directory of the target. The install directory is
# forced relative to $HOLO_ROOT. If INSTALL_DIR is not specified, this library
# will not be installed. "INCLUDES" keyword is used to specify include
# direcotries. "LIBRARIES" keyword is used to specify link libraries
# "DEFINITIONS" keyword is used to specify target definitions. "NAMESPACE"
# namespace for exported target "RPATHS" keyword is used to specify rpaths for
# installed target. Is not specified, ${HOLO_ROOT}/lib and
# ${HOLO_ROOT}/3rdparty/lib will be used.
#
function(HOLO_COMPILE_LIB target)
    cmake_parse_arguments(
        COMPILE "" "INSTALL_DIR;INSTALL_EXPORT_DIR;NAMESPACE;EXPORT_COMPONENT"
        "SOURCES;INCLUDES;LIBRARIES;DEFINITIONS;RPATHS" ${ARGN})

    # Check if target name is specified
    if(NOT target)
        message(FATAL_ERROR "Target name not specified!")
    endif(NOT target)

    if(IS_ABSOLUTE ${COMPILE_INSTALL_DIR})
        message(FATAL_ERROR "INSTALL_DIR only accept relative path!")
    endif()

    if(NOT COMPILE_RPATHS)
        set(COMPILE_RPATHS ${HOLO_ROOT}/lib ${HOLO_ROOT}/3rdparty/lib)
    endif()

    # Check if source files are specifed
    if(NOT COMPILE_SOURCES)
        if(NOT COMPILE_UNPARSED_ARGUMENTS)
            set(LIBRARY_TYPE "INTERFACE")
        endif(NOT COMPILE_UNPARSED_ARGUMENTS)
        set(_sources ${COMPILE_UNPARSED_ARGUMENTS})
    else(NOT COMPILE_SOURCES)
        set(_sources ${COMPILE_SOURCES})
    endif(NOT COMPILE_SOURCES)

    if(LIBRARY_TYPE STREQUAL "INTERFACE")
        set(DEPENDENCY_TYPE "INTERFACE")
    else()
        set(DEPENDENCY_TYPE "PUBLIC")
    endif()

    add_library(${target} ${_sources} ${LIBRARY_TYPE})
    target_include_directories(${target} ${DEPENDENCY_TYPE} ${COMPILE_INCLUDES})
    target_link_libraries(${target} ${DEPENDENCY_TYPE} ${COMPILE_LIBRARIES})
    target_compile_definitions(${target} ${DEPENDENCY_TYPE}
                                         ${COMPILE_DEFINITIONS})

    if(COMPILE_INSTALL_DIR)
        # calculate rpath
        if(NOT LIBRARY_TYPE STREQUAL "INTERFACE")
            foreach(input_rpath ${COMPILE_RPATHS})
                if(IS_ABSOLUTE ${input_rpath})
                    file(RELATIVE_PATH actual_rpath
                         ${CMAKE_INSTALL_PREFIX}/${COMPILE_INSTALL_DIR}
                         ${input_rpath})
                    set_property(
                        TARGET ${target}
                        APPEND
                        PROPERTY INSTALL_RPATH "\$ORIGIN/${actual_rpath}")
                else()
                    set_property(
                        TARGET ${target}
                        APPEND
                        PROPERTY INSTALL_RPATH "\$ORIGIN/${input_rpath}")
                endif()
            endforeach()
            set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                                                       ${COMPILE_INSTALL_DIR})
        endif()

        if(COMPILE_EXPORT_COMPONENT)
            set(EXP_COMP ${COMPILE_EXPORT_COMPONENT}-)
        endif()

        if(NOT COMPILE_INSTALL_EXPORT_DIR)
            set(COMPILE_INSTALL_EXPORT_DIR
                ${COMPILE_INSTALL_DIR}/cmake/${PROJECT_NAME})
        endif()

        install(
            TARGETS ${target}
            EXPORT ${CMAKE_PROJECT_NAME}-${EXP_COMP}targets
            DESTINATION ${COMPILE_INSTALL_DIR}
            COMPONENT runtime)
        install(
            EXPORT ${CMAKE_PROJECT_NAME}-${EXP_COMP}targets
            NAMESPACE "${COMPILE_NAMESPACE}"
            DESTINATION ${COMPILE_INSTALL_EXPORT_DIR}
            COMPONENT development)
    endif(COMPILE_INSTALL_DIR)

endfunction(HOLO_COMPILE_LIB)

# Install holo library Usage: HOLO_INSTALL_LIB(lib_target [DESTINATION dest]
# [NAMESPACE namespace]) "lib_target" is the library target name. "DESTINATION"
# keyword is used to specify library installation directory. The installation
# directory is relative to $HOLO_ROOT. If DESTINATION is not specified, library
# will install to default directory $HOLO_ROOT/lib "NAMESPACE" keyword is used
# to specify lib export target namespace "RPATHS" keyword is used to specify
# rpaths for installed target. Is not specified, ${HOLO_ROOT}/lib and
# ${HOLO_ROOT}/3rdparty/lib will be used.
#
function(HOLO_INSTALL_LIB target)
    cmake_parse_arguments(
        COMPILE "" "DESTINATION;EXPORT_DESTINATION;NAMESPACE;EXPORT_COMPONENT"
        "RPATHS" ${ARGN})

    if(IS_ABSOLUTE ${COMPILE_DESTINATION})
        message(FATAL_ERROR "DESTINATION only accept relative path!")
    endif()

    if(NOT COMPILE_DESTINATION)
        set(COMPILE_DESTINATION lib)
    endif()

    if(NOT COMPILE_RPATHS)
        set(COMPILE_RPATHS ${HOLO_ROOT}/lib ${HOLO_ROOT}/3rdparty/lib)
    endif()

    if(COMPILE_DESTINATION)
        # calculate rpath
        if(NOT LIBRARY_TYPE STREQUAL "INTERFACE")
            foreach(input_rpath ${COMPILE_RPATHS})
                if(IS_ABSOLUTE ${input_rpath})
                    file(RELATIVE_PATH actual_rpath
                         ${CMAKE_INSTALL_PREFIX}/${COMPILE_DESTINATION}
                         ${input_rpath})
                    set_property(
                        TARGET ${target}
                        APPEND
                        PROPERTY INSTALL_RPATH "\$ORIGIN/${actual_rpath}")
                else()
                    set_property(
                        TARGET ${target}
                        APPEND
                        PROPERTY INSTALL_RPATH "\$ORIGIN/${input_rpath}")
                endif()
            endforeach()
            set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                                                       ${COMPILE_DESTINATION})
        endif()

        if(COMPILE_EXPORT_COMPONENT)
            set(EXP_COMP ${COMPILE_EXPORT_COMPONENT}-)
        endif()

        if(NOT COMPILE_EXPORT_DESTINATION)
            set(COMPILE_EXPORT_DESTINATION
                ${COMPILE_DESTINATION}/cmake/${PROJECT_NAME})
        endif()

        install(
            TARGETS ${target}
            EXPORT ${CMAKE_PROJECT_NAME}-${EXP_COMP}targets
            DESTINATION ${COMPILE_DESTINATION}
            COMPONENT runtime)
        install(
            EXPORT ${CMAKE_PROJECT_NAME}-${EXP_COMP}targets
            NAMESPACE "${COMPILE_NAMESPACE}"
            DESTINATION ${COMPILE_EXPORT_DESTINATION}
            COMPONENT development)
    endif(COMPILE_DESTINATION)

endfunction(HOLO_INSTALL_LIB)

# Generate coverage report Usage: GENERATE_COVERAGE_REPORT([EXCULDE_PATTERNS
# patterns ...])
#
# EXCLUDE_PATTERNS keyword is used to list file patterns that should be ignored
# in coverage report.
function(GENERATE_COVERAGE_REPORT)
    find_program(LCOV_BIN lcov)
    find_program(GENHTML_BIN genhtml)
    if(LCOV_BIN AND GENHTML_BIN)
        cmake_parse_arguments(COV "" "TARGET" "EXCLUDE_PATTERNS" ${ARGN})
        if(NOT COV_TARGET)
            set(COV_TARGET ${PROJECT_NAME})
        endif()
        set(COV_COMMANDS
            COMMAND ${LCOV_BIN} --rc lcov_branch_coverage=1 --no-external -c -b
            ${PROJECT_SOURCE_DIR} -d ${PROJECT_BINARY_DIR} -o
            ${PROJECT_NAME}.info)
        foreach(pattern ${COV_EXCLUDE_PATTERNS})
            list(
                APPEND
                COV_COMMANDS
                COMMAND
                ${LCOV_BIN}
                --rc
                lcov_branch_coverage=1
                -r
                ${PROJECT_NAME}.info
                \"${pattern}\"
                -o
                ${PROJECT_NAME}.info)
        endforeach()
        list(
            APPEND
            COV_COMMANDS
            COMMAND
            ${GENHTML_BIN}
            --rc
            lcov_branch_coverage=1
            ${PROJECT_NAME}.info
            -o
            ${PROJECT_NAME})
        list(APPEND COV_COMMANDS COMMAND rm ${PROJECT_NAME}.info)

        add_custom_target(
            _${COV_TARGET}_coverage_dir
            COMMAND ${CMAKE_COMMAND} -E make_directory coverage
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

        add_custom_target(
            ${COV_TARGET}_coverage
            ${COV_COMMANDS}
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/coverage
            DEPENDS _${COV_TARGET}_coverage_dir)
        if(TARGET coverage)
            add_dependencies(coverage ${COV_TARGET}_coverage)
        else()
            add_custom_target(coverage DEPENDS ${COV_TARGET}_coverage)
        endif()
        install(
            DIRECTORY ${PROJECT_BINARY_DIR}/coverage/
            DESTINATION share/coverage/${CMAKE_PROJECT_NAME}
            OPTIONAL
            COMPONENT development)
    else()
        message(
            FATAL_ERROR
                "LCOV not found! lcov is used for generating test coverage report. \
                             Please run 'apt-get install lcov' to install lcov")
    endif()
endfunction()

# Get gcc compiler predefined macros. This funciton is for internal use.
function(_GetCompilerPredefinedMacros OUTVAR)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory
                            ${PROJECT_BINARY_DIR}/cmake)
    execute_process(COMMAND ${CMAKE_COMMAND} -E touch
                            ${PROJECT_BINARY_DIR}/cmake/empty.h)
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -Wp,-dM -E
                ${PROJECT_BINARY_DIR}/cmake/empty.h
        OUTPUT_VARIABLE DUMP_COMPILER_MACROS)
    execute_process(COMMAND ${CMAKE_COMMAND} -E remove
                            ${PROJECT_BINARY_DIR}/cmake/empty.h)

    string(REPLACE "\n" ";" DUMP_COMPILER_MACROS "${DUMP_COMPILER_MACROS}")
    string(REPLACE "#define " "" DUMP_COMPILER_MACROS "${DUMP_COMPILER_MACROS}")
    foreach(line ${DUMP_COMPILER_MACROS})
        string(REPLACE " " ";" LINE "${line}")
        list(LENGTH LINE ELEMENT_NUMBER)
        if(ELEMENT_NUMBER GREATER 1)
            list(GET LINE 0 MACRO_NAME)
            list(SUBLIST LINE 1 -1 MACRO_VALUE)
            string(REPLACE ";" " " MACRO_VALUE "${MACRO_VALUE}")
            string(CONCAT MACRO_LINE "${MACRO_NAME}" "=" "${MACRO_VALUE}")
        else()
            set(MACRO_LINE ${LINE})
        endif()
        list(APPEND DOXYGEN_PREDEFINES ${MACRO_LINE})
    endforeach()

    string(REPLACE ";" " \\\n" DOXYGEN_PREDEFINES "${DOXYGEN_PREDEFINES}")
    set(${OUTVAR}
        "${DOXYGEN_PREDEFINES}"
        PARENT_SCOPE)

endfunction()

# Get doxygen template file path
set(_doxygen_template ${CMAKE_CURRENT_LIST_DIR}/template.doxyfile.in)

# Generate doxygen
#
# Usage: GENERAGE_DOXYGEN([OPTIMIZE_OUTPUT_FOR_C] [INPUT input_dirs...])
#
# OPTIMIZE_OUTPUT_FOR_C: This option is used to whether optimize doxygen output
# for C project. By default doxygen will generate C++ format output. INPUT: This
# argument is used to specify input source directories. By default, "include src
# doc" will be used as input source directories.
function(GENERATE_DOXYGEN)
    find_package(Doxygen)
    if(${DOXYGEN_FOUND})
        cmake_parse_arguments(DOX "OPTIMIZE_OUTPUT_FOR_C" "" "INPUT" ${ARGN})

        # DOXYGEN_PREDEFINES is used by doxygen template configuration file
        _getcompilerpredefinedmacros(DOXYGEN_PREDEFINES)

        # default output language optimizations. OPTIMIZE_OUTPUT_FOR_C is used
        # by doxygen template configuration file.
        if(DOX_OPTIMIZE_OUTPUT_FOR_C)
            set(OPTIMIZE_OUTPUT_FOR_C "YES")
        else()
            set(OPTIMIZE_OUTPUT_FOR_C "NO")
        endif()

        string(REPLACE ";" " " DOXYGEN_INPUT "${DOX_INPUT}")
        configure_file(${_doxygen_template}
                       ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.doxyfile @ONLY)

        add_custom_target(
            ${PROJECT_NAME}_doc
            COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/doc
            COMMAND ${DOXYGEN_EXECUTABLE}
                    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.doxyfile
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen")

        if(TARGET doc)
            add_dependencies(doc ${PROJECT_NAME}_doc)
        else()
            add_custom_target(doc DEPENDS ${PROJECT_NAME}_doc)
        endif()

        install(
            DIRECTORY ${PROJECT_BINARY_DIR}/doc/
            DESTINATION share/doc/${CMAKE_PROJECT_NAME}
            OPTIONAL
            COMPONENT development)
    else()
        message(WARNING "Doxygen is needed to build the documentation.")
    endif()
endfunction()
