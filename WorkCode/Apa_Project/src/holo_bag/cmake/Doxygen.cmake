find_package(Doxygen)
if(${DOXYGEN_FOUND})
    configure_file(${PROJECT_SOURCE_DIR}/cmake/holo_bag.doxyfile.in ${PROJECT_BINARY_DIR}/holo_bag.doxyfile @ONLY)
    add_custom_target(doc
                      COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/holo_bag.doxyfile
                      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
                      COMMENT "Generating API documentation with Doxygen"
                      VERBATIM)

#    install(DIRECTORY ${PROJECT_BINARY_DIR}/doc DESTINATION share)
else()
    message(WARNING "Doxygen is needed to build the documentation.")
endif()
