
find_program(LCOV_BIN lcov)
find_program(GENHTML_BIN genhtml)

if(LCOV_BIN AND GENHTML_BIN)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory coverage WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
    add_custom_target(coverage
        COMMAND ${LCOV_BIN} --rc lcov_branch_coverage=1 --no-external -c
                -b ${PROJECT_SOURCE_DIR} -d ${PROJECT_BINARY_DIR} -o ${PROJECT_NAME}.info
        COMMAND ${LCOV_BIN} --rc lcov_branch_coverage=1 -r ${PROJECT_NAME}.info
                "*/${PROJECT_NAME}/3rdparty/*" -o ${PROJECT_NAME}.info
        COMMAND ${LCOV_BIN} --rc lcov_branch_coverage=1 -r ${PROJECT_NAME}.info
                "*/${PROJECT_NAME}/test/*" -o ${PROJECT_NAME}.info
        COMMAND ${GENHTML_BIN} --rc lcov_branch_coverage=1 ${PROJECT_NAME}.info -o ${PROJECT_NAME}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/coverage
        )
else()
    MESSAGE(FATAL_ERROR "LCOV not found! lcov is used for generating test coverage report. \
                         Please run 'apt-get install lcov' to install lcov")
endif()
