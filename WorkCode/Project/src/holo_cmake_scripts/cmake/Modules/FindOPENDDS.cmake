# This Script Will Sets The Following Variables:
#   OPENDDS_FOUND - True If OPENDDS Was Found
#   ACE_ROOT                    -
#   TAO_ROOT                    -
#   DDS_ROOT                    -
#   PERL_PROGRAM                - perl
#   TAO_IDL_PROGRAM             - tao_idl
#   ACE_GPERF_PROGRAM           - ace_gperf
#   OPENDDS_IDL_PROGRAM         - opendds_idl
#   OPENDDS_IDL_TEMPLATE_FILE   - ${DDS_ROOT}/idl/IDLTemplate.txt
#   OPENDDS_HOST_DIR            -
#   OPENDDS_TARGET_DIR          -
#   OPENDDS_INCLUDE_DIR         -
#   OPENDDS_INCLUDE_DIRS        -
#   OPENDDS_DEFINITIONS         -
#   OPENDDS_LIBRARIES           -
#   OPENDDS_EXTRA_LIBRARIES     -
#   OPENDDS_VERSION             -
#   OPENDDS_VERSION_MAJOR       -
#   OPENDDS_VERSION_MINOR       -
#   OPENDDS_VERSION_MICRO       -
#
# This Script Will Provide The Following Function
#   - OPENDDS_COMPILE_IDL_FILE()

find_package(XERCESC QUIET)

include(FindPackageHandleStandardArgs)

if (CMAKE_CROSSCOMPILING AND HOLO_ROOT)
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" "${HOLO_ROOT}/../host")
endif ()

###### DIRS ######
unset(OPENDDS_REQUIRED_DIRS)

find_path(OPENDDS_HOST_DIR "bin/opendds_idl" NO_CMAKE_FIND_ROOT_PATH)
list(APPEND OPENDDS_REQUIRED_DIRS "OPENDDS_HOST_DIR")
#message("OPENDDS_HOST_DIR = ${OPENDDS_HOST_DIR}")

find_path(OPENDDS_TARGET_DIR "bin/DCPSInfoRepo")
list(APPEND OPENDDS_REQUIRED_DIRS "OPENDDS_TARGET_DIR")
#message("OPENDDS_TARGET_DIR = ${OPENDDS_TARGET_DIR}")

find_path(OPENDDS_INCLUDE_DIR "dds/DdsDcps.idl")
list(APPEND OPENDDS_REQUIRED_DIRS "OPENDDS_INCLUDE_DIR")
#message("OPENDDS_INCLUDE_DIR = ${OPENDDS_INCLUDE_DIR}")

###### PROGRAMS ######
unset(_OPENDDS_REQUIRED_BINS)
list(APPEND _OPENDDS_REQUIRED_BINS "perl")
list(APPEND _OPENDDS_REQUIRED_BINS "tao_idl")
list(APPEND _OPENDDS_REQUIRED_BINS "ace_gperf")
list(APPEND _OPENDDS_REQUIRED_BINS "opendds_idl")
unset(OPENDDS_REQUIRED_BINS)
foreach (bin_name ${_OPENDDS_REQUIRED_BINS})
    string(TOUPPER "${bin_name}_PROGRAM" bin_var)
    find_program(${bin_var} "${bin_name}")
    #message("${bin_var} = ${${bin_var}}")
    list(APPEND OPENDDS_REQUIRED_BINS ${bin_var})
endforeach ()

###### LIBRARIES ######
unset(_OPENDDS_REQUIRED_LIBS)
list(APPEND _OPENDDS_REQUIRED_LIBS "ACE")
list(APPEND _OPENDDS_REQUIRED_LIBS "ACE_XML_Utils")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_Dcps")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_FACE")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_Federator")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_InfoRepoDiscovery")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_InfoRepoLib")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_InfoRepoServ")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_Model")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_monitor")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_Multicast")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_QOS_XML_XSC_Handler")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_Rtps")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_Rtps_Udp")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_Shmem")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_Tcp")
list(APPEND _OPENDDS_REQUIRED_LIBS "OpenDDS_Udp")
list(APPEND _OPENDDS_REQUIRED_LIBS "TAO")
list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_AnyTypeCode")
list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_BiDirGIOP")
list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_CodecFactory")
#list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_Codeset")
#list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_IDL_BE")
list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_IDL_FE")
list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_ImR_Client")
list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_IORManip")
list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_IORTable")
list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_PI")
list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_PortableServer")
list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_Svc_Utils")
#list(APPEND _OPENDDS_REQUIRED_LIBS "TAO_Valuetype")
unset(OPENDDS_REQUIRED_LIBS)
foreach (lib_name ${_OPENDDS_REQUIRED_LIBS})
    string(TOUPPER "${lib_name}_LIBRARY" lib_var)
    find_library(${lib_var} "${lib_name}")
    #message("${lib_var} = ${${lib_var}}")
    list(APPEND OPENDDS_REQUIRED_LIBS ${lib_var})
endforeach ()

###### VERSION ######
find_file(OPENDDS_VERSION_FILE "dds/Version.h")
if (OPENDDS_VERSION_FILE)
    file(STRINGS ${OPENDDS_VERSION_FILE} version_strings REGEX "^#define OPENDDS_.*_VERSION")
    if(NOT version_strings)
        file(STRINGS ${OPENDDS_VERSION_FILE} version_strings REGEX "^#define DDS_.*_VERSION")
    endif()

    foreach (version_string ${version_strings}) 
        string(REGEX MATCH "DDS_MAJOR_VERSION ([0-9]+)" version ${version_string})
        if (version)
            set(OPENDDS_VERSION_MAJOR ${CMAKE_MATCH_1})
        endif (version)

        string(REGEX MATCH "DDS_MINOR_VERSION ([0-9]+)" version ${version_string})
        if (version)
            set(OPENDDS_VERSION_MINOR ${CMAKE_MATCH_1})
        endif (version)

        string(REGEX MATCH "DDS_MICRO_VERSION ([0-9]+)" version ${version_string})
        if (version)
            set(OPENDDS_VERSION_MICRO ${CMAKE_MATCH_1})
        endif (version)
    endforeach (version_string)

    set(OPENDDS_VERSION "${OPENDDS_VERSION_MAJOR}.${OPENDDS_VERSION_MINOR}.${OPENDDS_VERSION_MICRO}")
endif (OPENDDS_VERSION_FILE)

#string(REPLACE ";" "" OPENDDS_REQUIRED_DIRS ${OPENDDS_REQUIRED_DIRS})
#message("OPENDDS_REQUIRED_DIRS = ${OPENDDS_REQUIRED_DIRS}")
#string(REPLACE ";" "" OPENDDS_REQUIRED_BINS ${OPENDDS_REQUIRED_BINS})
#message("OPENDDS_REQUIRED_BINS = ${OPENDDS_REQUIRED_BINS}")
#string(REPLACE ";" "" OPENDDS_REQUIRED_LIBS ${OPENDDS_REQUIRED_LIBS})
#message("OPENDDS_REQUIRED_LIBS = ${OPENDDS_REQUIRED_LIBS}")

find_package_handle_standard_args(OPENDDS 
    REQUIRED_VARS 
        XERCESC_FOUND
        ${OPENDDS_REQUIRED_DIRS} 
        ${OPENDDS_REQUIRED_BINS} 
        ${OPENDDS_REQUIRED_LIBS} 
    VERSION_VAR 
        OPENDDS_VERSION
)

mark_as_advanced(
    ${OPENDDS_REQUIRED_DIRS} 
    ${OPENDDS_REQUIRED_BINS} 
    ${OPENDDS_REQUIRED_LIBS}
)

if (OPENDDS_FOUND)
    #set(ENV{LD_LIBRARY_PATH} $ENV{LD_LIBRARY_PATH} ${OPENDDS_HOST_DIR}/lib)
    #set(CMAKE_C_FLAGS   "-Wl,-rpath-link ${OPENDDS_HOST_DIR}/lib")
    #set(CMAKE_CXX_FLAGS "-Wl,-rpath-link ${OPENDDS_HOST_DIR}/lib")

    set(ACE_ROOT "${OPENDDS_HOST_DIR}/share/ace")
    set(TAO_ROOT "${OPENDDS_HOST_DIR}/share/tao")
    set(DDS_ROOT "${OPENDDS_HOST_DIR}/share/dds")

    message(STATUS "Found OPENDDS Host    : ${OPENDDS_HOST_DIR}")
    message(STATUS "Found OPENDDS Target  : ${OPENDDS_TARGET_DIR}")
    message(STATUS "Found OPENDDS Version : ${OPENDDS_VERSION}")

    set(OPENDDS_INCLUDE_DIRS ${OPENDDS_INCLUDE_DIR})
    set(OPENDDS_IDL_TEMPLATE_FILE "${OPENDDS_HOST_DIR}/share/dds/dds/idl/IDLTemplate.txt")

    foreach (lib_name ${_OPENDDS_REQUIRED_LIBS})
        if (lib_name STREQUAL "ACE")
            string(REPLACE "ACE" "ACE::ACE" target_name ${lib_name})
        elseif (lib_name MATCHES "ACE_")
            string(REPLACE "ACE_" "ACE::" target_name ${lib_name})
        elseif (lib_name STREQUAL "TAO")
            string(REPLACE "TAO" "TAO::TAO" target_name ${lib_name})
        elseif (lib_name MATCHES "TAO_")
            string(REPLACE "TAO_" "TAO::" target_name ${lib_name})
        elseif (lib_name MATCHES "OpenDDS_")
            string(REPLACE "OpenDDS_" "OPENDDS::" target_name ${lib_name})
        endif ()

        if (NOT TARGET ${target_name})
            string(TOUPPER "${lib_name}_LIBRARY" var_name)
            add_library(${target_name} UNKNOWN IMPORTED)
            set_target_properties(${target_name} PROPERTIES 
                IMPORTED_LOCATION 
                    "${${var_name}}"
                INTERFACE_INCLUDE_DIRECTORIES 
                    "${OPENDDS_INCLUDE_DIR}"
            )
            list(APPEND OPENDDS_LIBRARIES ${target_name})
            #message("${target_name} = ${${var_name}}")
        endif ()
    endforeach ()

    set_target_properties(ACE::XML_Utils PROPERTIES
        INTERFACE_LINK_LIBRARIES
            "XERCESC::xerces-c"
    )

    set_target_properties(OPENDDS::Dcps PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "ACE::ACE;TAO::TAO;TAO::PI;TAO::BiDirGIOP;TAO::AnyTypeCode;TAO::CodecFactory;TAO::PortableServer"
    )

    set_target_properties(OPENDDS::FACE PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Dcps"
    )

    set_target_properties(OPENDDS::Federator PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Dcps"
    )

    set_target_properties(OPENDDS::InfoRepoDiscovery PROPERTIES
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Dcps;OPENDDS::Tcp"
    )

    set_target_properties(OPENDDS::InfoRepoLib PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::InfoRepoDiscovery;TAO::Svc_Utils;TAO::ImR_Client;TAO::IORManip;TAO::IORTable"
    )

    set_target_properties(OPENDDS::InfoRepoServ PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Federator"
    )

    set_target_properties(OPENDDS::Model PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Dcps"
    )

    set_target_properties(OPENDDS::monitor PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Dcps"
    )

    set_target_properties(OPENDDS::Multicast PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Dcps"
    )

    set_target_properties(OPENDDS::QOS_XML_XSC_Handler PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Dcps;ACE::XML_Utils"
    )

    set_target_properties(OPENDDS::Rtps PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Dcps"
    )

    set_target_properties(OPENDDS::Rtps_Udp PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Rtps"
    )

    set_target_properties(OPENDDS::Shmem PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Dcps"
    )

    set_target_properties(OPENDDS::Tcp PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Dcps"
    )

    set_target_properties(OPENDDS::Udp PROPERTIES 
        INTERFACE_LINK_LIBRARIES 
            "OPENDDS::Dcps"
    )

    if (TARGET OPENDDS::Security)
        set_target_properties(OPENDDS::Security PROPERTIES 
            INTERFACE_LINK_LIBRARIES 
                "OPENDDS::Rtps;ACE::XML_Utils"
        )
    endif ()

    if (NOT TARGET OPENDDS::opendds)
        add_library(OPENDDS::opendds INTERFACE IMPORTED)
        set_target_properties(OPENDDS::opendds PROPERTIES 
            INTERFACE_LINK_LIBRARIES 
            "XERCESC::xerces-c;OPENDDS::Dcps;OPENDDS::Tcp;OPENDDS::Udp;OPENDDS::Rtps;OPENDDS::Rtps_Udp;OPENDDS::Shmem;OPENDDS::Multicast;OPENDDS::InfoRepoDiscovery"
            INTERFACE_LINK_OPTIONS -pthread
        )
    endif ()

    if (WIN32)
        set(OPENDDS_DEFINITIONS     "")
        set(OPENDDS_EXTRA_LIBRARIES netapi32 advapi32 user32 ws2_32)
    else (WIN32)
        set(OPENDDS_DEFINITIONS     "__ACE_INLINE__")
        set(OPENDDS_EXTRA_LIBRARIES dl rt m pthread)
    endif (WIN32)

endif ()

################################################################################
#   Usage:                                                                     #
#   OPENDDS_COMPILE_IDL_FILE(<idl_file>                                        #
#       INCLUDES                                                               #
#           <include_dirs>                                                     #
#       OUTPUT_DIR                                                             #
#           <output_dir>                                                       #
#       OPTIONS                                                                #
#           <options_for_tao_idl_and_opendds_idl>                              #
#       TAO_IDL_OPTIONS                                                        #
#           <tao_idl_options>                                                  #
#       OPENDDS_IDL_OPTIONS                                                    #
#           <opendds_idl_options>                                              #
#   )                                                                          #
#                                                                              #
#   Note:                                                                      #
#   Use following variables to get generated files                             #
#       - OPENDDS_IDL_GENERATED_HEADER_FILES                                   #
#       - OPENDDS_IDL_GENERATED_SOURCE_FILES                                   #
#                                                                              #
################################################################################
function (OPENDDS_COMPILE_IDL_FILE idl_file)
    cmake_parse_arguments(COMPILE "" "OUTPUT_DIR" "INCLUDE_DIRS;OPTIONS;TAO_IDL_OPTIONS;OPENDDS_IDL_OPTIONS" ${ARGN})

    if (NOT idl_file)
        message(FATAL_ERROR "IDL File Not Specified!")
    endif ()

    if (NOT COMPILE_OUTPUT_DIR)
        message(FATAL_ERROR "OUTPUT_DIR Not Specified!")
    endif ()

    get_filename_component(idl_file_dir  ${idl_file} DIRECTORY)
    get_filename_component(idl_file_name ${idl_file} NAME_WE)

    set(OPENDDS_IDL_GENERATED_HEADER_FILES)
    set(OPENDDS_IDL_GENERATED_SOURCE_FILES)

    set(ts_idl_file "${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupport.idl")

    set(IDL_COMPILER_OPTS)
    #list(APPEND IDL_COMPILER_OPTS "-v")
    list(APPEND IDL_COMPILER_OPTS "-Cw")
    list(APPEND IDL_COMPILER_OPTS "-D__ACE_INLINE__")
    list(APPEND IDL_COMPILER_OPTS "${COMPILE_OPTIONS}")
    list(APPEND IDL_COMPILER_OPTS "-I${OPENDDS_INCLUDE_DIRS}")
    foreach (dir ${COMPILE_INCLUDE_DIRS})
        list(APPEND IDL_COMPILER_OPTS "-I${dir}")
    endforeach ()

    set(dds_idl_opts ${IDL_COMPILER_OPTS})
    add_custom_command(
        OUTPUT
            ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupport.idl
            ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupportImpl.h
            ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupportImpl.cpp
        COMMAND
            ${CMAKE_COMMAND} -E make_directory ${COMPILE_OUTPUT_DIR}
        COMMAND
            DDS_ROOT=${DDS_ROOT}
            LD_LIBRARY_PATH=${OPENDDS_HOST_DIR}/lib
            ${OPENDDS_IDL_PROGRAM} ${dds_idl_opts} ${COMPILE_OPENDDS_IDL_OPTIONS} ${idl_file} -o ${COMPILE_OUTPUT_DIR}
        DEPENDS
            ${idl_file}
            ${OPENDDS_IDL_PROGRAM}
            ${OPENDDS_IDL_TEMPLATE_FILE}
        COMMENT
            "Generating ${ts_idl_file}"
    )
    list(APPEND OPENDDS_IDL_GENERATED_HEADER_FILES ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupportImpl.h)
    list(APPEND OPENDDS_IDL_GENERATED_SOURCE_FILES ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupportImpl.cpp)

    set(tao_idl_opts ${IDL_COMPILER_OPTS})
    list(APPEND tao_idl_opts "-I${idl_file_dir}")
    list(APPEND tao_idl_opts "-Wb,pre_include=ace/pre.h")
    list(APPEND tao_idl_opts "-Wb,post_include=ace/post.h")

    add_custom_command(
        OUTPUT 
            ${COMPILE_OUTPUT_DIR}/${idl_file_name}C.h
            ${COMPILE_OUTPUT_DIR}/${idl_file_name}C.cpp
            ${COMPILE_OUTPUT_DIR}/${idl_file_name}S.h
            ${COMPILE_OUTPUT_DIR}/${idl_file_name}S.cpp
        COMMAND
            ACE_ROOT=${ACE_ROOT}
            LD_LIBRARY_PATH=${OPENDDS_HOST_DIR}/lib
            ${TAO_IDL_PROGRAM} ${tao_idl_opts} ${COMPILE_TAO_IDL_OPTIONS} ${idl_file} -o ${COMPILE_OUTPUT_DIR}
        DEPENDS
            ${idl_file}
            ${ts_idl_file}
            ${TAO_IDL_PROGRAM} 
            ${ACE_GPERF_PROGRAM}
        COMMENT
            "Compiling ${idl_file}"
    )
    list(APPEND OPENDDS_IDL_GENERATED_HEADER_FILES ${COMPILE_OUTPUT_DIR}/${idl_file_name}C.h)
    list(APPEND OPENDDS_IDL_GENERATED_SOURCE_FILES ${COMPILE_OUTPUT_DIR}/${idl_file_name}C.cpp)
    list(APPEND OPENDDS_IDL_GENERATED_HEADER_FILES ${COMPILE_OUTPUT_DIR}/${idl_file_name}S.h)
    list(APPEND OPENDDS_IDL_GENERATED_SOURCE_FILES ${COMPILE_OUTPUT_DIR}/${idl_file_name}S.cpp)

    add_custom_command(
        OUTPUT 
            ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupportC.h
            ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupportC.cpp
            ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupportS.h
            ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupportS.cpp
        COMMAND
            ACE_ROOT=${ACE_ROOT}
            LD_LIBRARY_PATH=${OPENDDS_HOST_DIR}/lib
            ${TAO_IDL_PROGRAM} ${tao_idl_opts} ${COMPILE_TAO_IDL_OPTIONS} ${ts_idl_file} -o ${COMPILE_OUTPUT_DIR}
        DEPENDS
            ${ts_idl_file}
            ${TAO_IDL_PROGRAM} 
            ${ACE_GPERF_PROGRAM}
        COMMENT
            "Compiling ${ts_idl_file}"
    )
    list(APPEND OPENDDS_IDL_GENERATED_HEADER_FILES ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupportC.h)
    list(APPEND OPENDDS_IDL_GENERATED_SOURCE_FILES ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupportC.cpp)
    list(APPEND OPENDDS_IDL_GENERATED_HEADER_FILES ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupportS.h)
    list(APPEND OPENDDS_IDL_GENERATED_SOURCE_FILES ${COMPILE_OUTPUT_DIR}/${idl_file_name}TypeSupportS.cpp)

    set(OPENDDS_IDL_GENERATED_HEADER_FILES ${OPENDDS_IDL_GENERATED_HEADER_FILES} PARENT_SCOPE)
    set(OPENDDS_IDL_GENERATED_SOURCE_FILES ${OPENDDS_IDL_GENERATED_SOURCE_FILES} PARENT_SCOPE)
endfunction ()

