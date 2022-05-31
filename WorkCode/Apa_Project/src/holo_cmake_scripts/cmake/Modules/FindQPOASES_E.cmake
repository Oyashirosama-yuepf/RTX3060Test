include(FindPackageHandleStandardArgs)

find_path(QPOASES_E_INCLUDE_DIR
          NAMES qpOASES_e.h
          PATH_SUFFIXES include/qpOASES_e
         )
message(${QPOASES_E_INCLUDE_DIR})
find_library(QPOASES_E_LIBRARY
             NAMES qpOASES_e
            )

mark_as_advanced(QPOASES_E_INCLUDE_DIR QPOASES_E_LIBRARY)

set(QPOASES_E_INCLUDE_DIRS ${QPOASES_E_INCLUDE_DIR})
set(QPOASES_E_LIBRARIES ${QPOASES_E_LIBRARY})

find_package_handle_standard_args(QPOASES_E
    REQUIRED_VARS QPOASES_E_LIBRARIES QPOASES_E_INCLUDE_DIRS)

if (QPOASES_E_FOUND)
    if (NOT TARGET QPOASES_E::qpOASES)
        add_library(QPOASES::qpOASES_e UNKNOWN IMPORTED)
        set_target_properties(QPOASES::qpOASES_e PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${QPOASES_E_INCLUDE_DIR}
                IMPORTED_LOCATION ${QPOASES_E_LIBRARY})
    endif ()
endif ()
