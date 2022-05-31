## -------------------------generated code------------------------------------
if(${OPENDDS_VERSION} VERSION_GREATER_EQUAL "3.14")
    set(IDL_OPTIONS --idl-version 4)
endif()

opendds_wrapper_compile_idl_files(
    DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}
    OPTIONS
    ${IDL_OPTIONS}
    INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}
    INSTALL)
