# - Try to find yaml-cpp lib
#
# Once done this will define
#
#  YAML-CPP_FOUND - system has yaml-cpp lib with correct version
#  YAML-CPP_INCLUDE_DIRS - the yaml-cpp include directory
#  YAML-CPP_LIBRARIES - the yaml-cpp library

find_path(YAML-CPP_INCLUDE_DIR "yaml-cpp/yaml.h")
find_library(YAML-CPP_LIBRARY yaml-cpp)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(YAML-CPP REQUIRED_VARS YAML-CPP_LIBRARY YAML-CPP_INCLUDE_DIR)

mark_as_advanced(YAML-CPP_LIBRARY YAML-CPP_INCLUDE_DIR)

set(YAML-CPP_INCLUDE_DIRS ${YAML-CPP_INCLUDE_DIR})
set(YAML-CPP_LIBRARIES ${YAML-CPP_LIBRARY})

if(YAML-CPP_FOUND)
    if(NOT TARGET YAML-CPP::yaml-cpp)
        add_library(YAML-CPP::yaml-cpp UNKNOWN IMPORTED)
        if(YAML-CPP_INCLUDE_DIR)
            set_target_properties(YAML-CPP::yaml-cpp PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${YAML-CPP_INCLUDE_DIR})
        endif()
        if(YAML-CPP_LIBRARY)
            set_target_properties(YAML-CPP::yaml-cpp PROPERTIES
                IMPORTED_LOCATION ${YAML-CPP_LIBRARY})
        endif()
    endif()
endif()

