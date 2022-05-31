################################################################################
#   HOLO_COMPILE_CMW_APP(target                                                #
#       [ROS|RTIDDS|OPENDDS]                                                   #
#       [SOURCES] src1 [...]                                                   #
#       [INCLUDES dir1 ...]                                                    #
#       [LIBRARIES lib1 ...]                                                   #
#       [DEFINITIONS def1 ...]                                                 #
#   )                                                                          #
################################################################################
function (HOLO_COMPILE_CMW_APP target)
    cmake_parse_arguments(CMW_APP "ROS;RTIDDS;OPENDDS" "INSTALL_DIR" "SOURCES;INCLUDES;LIBRARIES;DEFINITIONS" ${ARGN})
    
    if (NOT target)
        MESSAGE(FATAL_ERROR "Target name not specified!")
    endif (NOT target)

    if (NOT CMW_APP_SOURCES)
        set(CMW_APP_SOURCES ${CMW_APP_UNPARSED_ARGUMENTS})
    endif (NOT CMW_APP_SOURCES)

    if (NOT CMW_APP_INSTALL_DIR)
        set(CMW_APP_INSTALL_DIR bin)
    endif (NOT CMW_APP_INSTALL_DIR)

    HOLO_COMPILE_CMW_TARGET(${target} 
        TYPE            
            "CMW_APP"
        ROS             
            ${CMW_APP_ROS}
        RTIDDS          
            ${CMW_APP_RTIDDS}
        OPENDDS         
            ${CMW_APP_OPENDDS}
        SOURCES         
            ${CMW_APP_SOURCES}
        INCLUDES        
            ${CMW_APP_INCLUDES}
        LIBRARIES       
            ${CMW_APP_LIBRARIES}
        DEFINITIONS     
            ${CMW_APP_DEFINITIONS}
        INSTALL_DIR     
            ${CMW_APP_INSTALL_DIR}
        )
endfunction (HOLO_COMPILE_CMW_APP)

################################################################################
#   HOLO_COMPILE_CMW_LIB(target                                                #
#       [ROS|RTIDDS|OPENDDS]                                                   #
#       [SOURCES] src1 [src2 ...]                                              #
#       [INCLUDES dir1 ...]                                                    #
#       [LIBRARIES lib1 ...]                                                   #
#       [DEFINITIONS def1 ...]                                                 #
#   )                                                                          #
################################################################################
function (HOLO_COMPILE_CMW_LIB target)
    cmake_parse_arguments(CMW_LIB "ROS;OPENDDS;RTIDDS" "INSTALL_DIR" "SOURCES;INCLUDES;LIBRARIES;DEFINITIONS" ${ARGN})
    
    if (NOT target)
        MESSAGE(FATAL_ERROR "Target name not specified!")
    endif (NOT target)

    if (NOT CMW_LIB_SOURCES)
        set(CMW_LIB_SOURCES ${CMW_LIB_UNPARSED_ARGUMENTS})
    endif (NOT CMW_LIB_SOURCES)

    if (NOT CMW_LIB_INSTALL_DIR)
        set(CMW_LIB_INSTALL_DIR lib)
    endif (NOT CMW_LIB_INSTALL_DIR)

    HOLO_COMPILE_CMW_TARGET(${target} 
    TYPE            "CMW_LIB"
    ROS             ${CMW_APP_ROS}
    RTIDDS          ${CMW_APP_RTIDDS}
    OPENDDS         ${CMW_APP_OPENDDS}
    SOURCES         ${CMW_LIB_SOURCES}
    INCLUDES        ${CMW_LIB_INCLUDES}
    LIBRARIES       ${CMW_LIB_LIBRARIES}
    DEFINITIONS     ${CMW_LIB_DEFINITIONS}
    INSTALL_DIR     ${CMW_LIB_INSTALL_DIR})
endfunction (HOLO_COMPILE_CMW_LIB)

################################################################################
#   HOLO_COMPILE_CMW_BRIDGE_APP(target                                         #
#       [ROS|RTIDDS|OPENDDS]                                                   #
#       [SOURCES] src1 [...]                                                   #
#       [INCLUDES dir1 ...]                                                    #
#       [LIBRARIES lib1 ...]                                                   #
#       [DEFINITIONS def1 ...]                                                 #
#   )                                                                          #
################################################################################
function (HOLO_COMPILE_CMW_BRIDGE_APP target)
    cmake_parse_arguments(CMW_BRIDGE_APP "" "INSTALL_DIR" "SOURCES;INCLUDES;LIBRARIES;DEFINITIONS" ${ARGN})
    
    if (NOT target)
        message(FATAL_ERROR "Target name not specified!")
    endif (NOT target)

    if (NOT CMW_BRIDGE_APP_SOURCES)
        set(CMW_BRIDGE_APP_SOURCES ${CMW_BRIDGE_APP_UNPARSED_ARGUMENTS})
    endif (NOT CMW_BRIDGE_APP_SOURCES)

    if (NOT CMW_BRIDGE_APP_INSTALL_DIR)
        set(CMW_BRIDGE_APP_INSTALL_DIR bin)
    endif (NOT CMW_BRIDGE_APP_INSTALL_DIR)

    _compile_cmw_bridge_target(${target} 
    TYPE        "CMW_BRIDGE_APP"
    SOURCES     ${CMW_BRIDGE_APP_SOURCES}
    INCLUDES    ${CMW_BRIDGE_APP_INCLUDES}
    LIBRARIES   ${CMW_BRIDGE_APP_LIBRARIES}
    DEFINITIONS ${CMW_BRIDGE_APP_DEFINITIONS}
    INSTALL_DIR ${CMW_BRIDGE_APP_INSTALL_DIR})
endfunction (HOLO_COMPILE_CMW_BRIDGE_APP)

################################################################################
#   HOLO_COMPILE_CMW_BRIDGE_LIB(target                                         #
#       [ROS|RTIDDS|OPENDDS]                                                   #
#       [SOURCES] src1 [...]                                                   #
#       [INCLUDES dir1 ...]                                                    #
#       [LIBRARIES lib1 ...]                                                   #
#       [DEFINITIONS def1 ...]                                                 #
#   )                                                                          #
################################################################################
function (HOLO_COMPILE_CMW_BRIDGE_LIB target)
    cmake_parse_arguments(CMW_BRIDGE_LIB "" "INSTALL_DIR" "SOURCES;INCLUDES;LIBRARIES;DEFINITIONS" ${ARGN})
    
    if (NOT target)
        message(FATAL_ERROR "Target name not specified!")
    endif (NOT target)

    if (NOT CMW_BRIDGE_LIB_SOURCES)
        set(CMW_BRIDGE_LIB_SOURCES ${CMW_BRIDGE_LIB_UNPARSED_ARGUMENTS})
    endif (NOT CMW_BRIDGE_LIB_SOURCES)

    if (NOT CMW_BRIDGE_LIB_INSTALL_DIR)
        set(CMW_BRIDGE_LIB_INSTALL_DIR lib)
    endif (NOT CMW_BRIDGE_LIB_INSTALL_DIR)

    _compile_cmw_bridge_target(${target} 
    TYPE        "CMW_BRIDGE_LIB"
    SOURCES     ${CMW_BRIDGE_LIB_SOURCES}
    INCLUDES    ${CMW_BRIDGE_LIB_INCLUDES}
    LIBRARIES   ${CMW_BRIDGE_LIB_LIBRARIES}
    DEFINITIONS ${CMW_BRIDGE_LIB_DEFINITIONS}
    INSTALL_DIR ${CMW_BRIDGE_LIB_INSTALL_DIR})
endfunction (HOLO_COMPILE_CMW_BRIDGE_LIB)


################################################################################


function (HOLO_COMPILE_CMW_TARGET target)
    cmake_parse_arguments(CMW_TARGET 
        "" 
        "TYPE;ROS;RTIDDS;OPENDDS;INSTALL_DIR;" 
        "SOURCES;INCLUDES;LIBRARIES;DEFINITIONS" 
        ${ARGN}
        )

    if (NOT CMW_TARGET_TYPE)
        message(FATAL_ERROR "Target Type Not Specified for ${target}!")
    endif (NOT CMW_TARGET_TYPE)
    
    if (NOT CMW_TARGET_SOURCES)
        message(FATAL_ERROR "No source file specified for target ${target}")
    endif (NOT CMW_TARGET_SOURCES)

    if (CMW_TARGET_ROS AND NOT ROS_FOUND)
        message(FATAL_ERROR "Unable to create ros target : ${target}, because ROS NOT FOUND!")
    endif ()

    if (CMW_TARGET_ROS AND NOT HOLO_CMW_BUILD_ROS_CMW)
        message(FATAL_ERROR "Unable to create ros target : ${target}, because holo_cmw unsupport ros!")
    endif ()

    if (CMW_TARGET_RTIDDS AND NOT RTIDDS_FOUND)
        message(FATAL_ERROR "Unable to create rtidds target : ${target}, because RTIDDS NOT FOUND!")
    endif ()

    if (CMW_TARGET_RTIDDS AND NOT HOLO_CMW_BUILD_RTIDDS_CMW)
        message(FATAL_ERROR "Unable to create rtidds target : ${target}, because holo_cmw unsupport rtidds!")
    endif ()

    if (CMW_TARGET_OPENDDS AND NOT OPENDDS_FOUND)
        message(FATAL_ERROR "Unable to create opendds target : ${target}, because OPENDDS NOT FOUND!")
    endif ()

    if (CMW_TARGET_OPENDDS AND NOT HOLO_CMW_BUILD_OPENDDS_CMW)
        message(FATAL_ERROR "Unable to create opendds target : ${target}, because holo_cmw unsupport opendds!")
    endif ()

    if (ROS_FOUND AND HOLO_CMW_BUILD_ROS_CMW)
        if (CMW_TARGET_TYPE STREQUAL "CMW_LIB")
            add_library(${target}_ros ${CMW_TARGET_SOURCES})
            set_property(TARGET ${target}_ros PROPERTY OUTPUT_NAME ${target})
            set_property(TARGET ${target}_ros PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ros/lib)
        else ()
            add_executable(${target}_ros ${CMW_TARGET_SOURCES})
            set_property(TARGET ${target}_ros PROPERTY OUTPUT_NAME ${target})
            set_property(TARGET ${target}_ros PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/ros/bin)
        endif ()

        target_link_libraries(${target}_ros ${CMW_TARGET_LIBRARIES} ${ROS_LIBRARIES} holo_cmw::holo_ros_cmw)
        target_include_directories(${target}_ros PRIVATE ${CMW_TARGET_INCLUDES} ${ROS_INCLUDE_DIRS})
        target_compile_definitions(${target}_ros PRIVATE ${CMW_TARGET_DEFINITIONS} ${ROS_DEFINITIONS} "-DHOLO_CMW_USE_ROS_CMW")

        set(target_rpath)
        foreach (path ${HOLO_ROOT}/lib ${HOLO_3RDPARTY_ROOT}/lib)
            file(RELATIVE_PATH rpath ${HOLO_ROOT}/${CMW_TARGET_INSTALL_DIR}/ros ${path})
            list(APPEND target_rpath "\$ORIGIN/${rpath}")
        endforeach ()
        set_target_properties(${target}_ros PROPERTIES INSTALL_RPATH "${target_rpath}")

        install(TARGETS ${target}_ros DESTINATION ${CMW_TARGET_INSTALL_DIR}/ros)
    endif ()

    if (RTIDDS_FOUND AND HOLO_CMW_BUILD_RTIDDS_CMW)
        if (CMW_TARGET_TYPE STREQUAL "CMW_LIB")
            add_library(${target}_rtidds ${CMW_TARGET_SOURCES})
            set_property(TARGET ${target}_rtidds PROPERTY OUTPUT_NAME ${target})
            set_property(TARGET ${target}_rtidds PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/rtidds/lib)
        else ()
            add_executable(${target}_rtidds ${CMW_TARGET_SOURCES})
            set_property(TARGET ${target}_rtidds PROPERTY OUTPUT_NAME ${target})
            set_property(TARGET ${target}_rtidds PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/rtidds/bin)
        endif ()

        target_link_libraries(${target}_rtidds ${CMW_TARGET_LIBRARIES} ${RTIDDS_CXX11_LIBRARIES} ${RTIDDS_EXTRA_LIBRARIES} holo_cmw::holo_rtidds_cxx11_cmw)
        target_include_directories(${target}_rtidds PRIVATE ${CMW_TARGET_INCLUDES} ${RTIDDS_CXX11_INCLUDE_DIRS})
        target_compile_definitions(${target}_rtidds PRIVATE ${CMW_TARGET_DEFINITIONS} ${RTIDDS_CXX11_DEFINITIONS} "-DHOLO_CMW_USE_RTIDDS_CXX11_CMW")

        set(target_rpath)
        foreach (path ${HOLO_ROOT}/lib ${HOLO_3RDPARTY_ROOT}/lib)
            file(RELATIVE_PATH rpath ${HOLO_ROOT}/${CMW_TARGET_INSTALL_DIR}/rtidds ${path})
            list(APPEND target_rpath "\$ORIGIN/${rpath}")
        endforeach ()
        set_target_properties(${target}_rtidds PROPERTIES INSTALL_RPATH "${target_rpath}")

        install(TARGETS ${target}_rtidds DESTINATION ${CMW_TARGET_INSTALL_DIR}/rtidds)
    endif ()

    if (OPENDDS_FOUND AND HOLO_CMW_BUILD_OPENDDS_CMW)
        if (CMW_TARGET_TYPE STREQUAL "CMW_LIB")
            add_library(${target}_opendds ${CMW_TARGET_SOURCES})
            set_target_properties(${target}_opendds PROPERTIES
                OUTPUT_NAME 
                    "${target}"
                RUNTIME_OUTPUT_DIRECTORY 
                    "${PROJECT_BINARY_DIR}/opendds/lib"
            )
        else ()
            add_executable(${target}_opendds ${CMW_TARGET_SOURCES})
            set_target_properties(${target}_opendds PROPERTIES 
                OUTPUT_NAME 
                    "${target}"
                RUNTIME_OUTPUT_DIRECTORY 
                    "${PROJECT_BINARY_DIR}/opendds/bin"
            )
        endif ()

        target_link_libraries(${target}_opendds 
            ${CMW_TARGET_LIBRARIES} 
            holo_cmw::holo_opendds_cmw
        )

        target_include_directories(${target}_opendds PRIVATE 
            ${CMW_TARGET_INCLUDES} 
            ${OPENDDS_INCLUDE_DIRS}
        )

        target_compile_definitions(${target}_opendds PRIVATE 
            ${CMW_TARGET_DEFINITIONS} 
            ${OPENDDS_DEFINITIONS} 
            "-DHOLO_CMW_USE_OPENDDS_CMW"
        )

        set(target_rpath)
        foreach (path ${HOLO_ROOT}/lib ${HOLO_3RDPARTY_ROOT}/lib)
            file(RELATIVE_PATH 
                rpath 
                ${HOLO_ROOT}/${CMW_TARGET_INSTALL_DIR}/opendds 
                ${path}
            )

            list(APPEND target_rpath "\$ORIGIN/${rpath}")
        endforeach ()
        set_target_properties(${target}_opendds PROPERTIES 
            INSTALL_RPATH 
                "${target_rpath}"
        )

        install(
            TARGETS 
                ${target}_opendds 
            DESTINATION 
                ${CMW_TARGET_INSTALL_DIR}/opendds
        )

        if (CMAKE_SYSTEM_NAME STREQUAL "QNX")
            target_link_libraries(${target}_opendds socket)
            target_compile_options(${target}_opendds PRIVATE -pthread)
        else ()
            target_link_libraries(${target}_opendds PRIVATE pthread)
        endif ()

    endif ()
endfunction (HOLO_COMPILE_CMW_TARGET)

function (_compile_cmw_bridge_target target)
    cmake_parse_arguments(CMW_BRIDGE "" "TYPE;INSTALL_DIR" "SOURCES;INCLUDES;LIBRARIES;DEFINITIONS" ${ARGN})

    if (NOT CMW_BRIDGE_SOURCES)
        message(FATAL_ERROR "Unable to create cmw bridge : ${target}, because no source files specified!")
    endif (NOT CMW_BRIDGE_SOURCES)

    if (NOT ROS_FOUND)
        message(FATAL_ERROR "Unable to create cmw bridge : ${target}, because ROS NOT FOUND!")
    endif (NOT ROS_FOUND)

    if (NOT HOLO_CMW_BUILD_ROS_CMW)
        message(FATAL_ERROR "Unable to create cmw bridge : ${target}, because holo_cmw unsupport ros!")
    endif (NOT HOLO_CMW_BUILD_ROS_CMW)

    if (NOT OPENDDS_FOUND)
        message(FATAL_ERROR "Unable to create cmw bridge : ${target}, because OPENDDS NOT FOUND!")
    endif (NOT OPENDDS_FOUND)

    if (NOT HOLO_CMW_BUILD_OPENDDS_CMW)
        message(FATAL_ERROR "Unable to create cmw bridge : ${target}, because holo_cmw build unsupport opendds!")
    endif (NOT HOLO_CMW_BUILD_OPENDDS_CMW)

    list(APPEND CMW_BRIDGE_INCLUDES ${ROS_INCLUDE_DIRS})
    list(APPEND CMW_BRIDGE_INCLUDES ${OPENDDS_INCLUDE_DIRS})

    list(APPEND CMW_BRIDGE_LIBRARIES holo_cmw::holo_ros_cmw holo_cmw::holo_opendds_cmw)
    list(APPEND CMW_BRIDGE_LIBRARIES ${ROS_LIBRARIES} ${OPENDDS_LIBRARIES})

    list(APPEND CMW_BRIDGE_DEFINITIONS ${ROS_DEFINITIONS})
    list(APPEND CMW_BRIDGE_DEFINITIONS -DHOLO_CMW_USE_ROS_CMW)
    list(APPEND CMW_BRIDGE_DEFINITIONS -DHOLO_CMW_USE_OPENDDS_CMW)

    set(bridge_name ${target}_bridge)

    if (CMW_BRIDGE_TYPE STREQUAL "CMW_BRIDGE_LIB")
        add_library(${bridge_name} ${CMW_BRIDGE_SOURCES})
        set_property(TARGET ${bridge_name} PROPERTY OUTPUT_NAME ${bridge_name})
        set_property(TARGET ${bridge_name} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bridge/lib)
    else () # CMW_BRIDGE_APP
        add_executable(${bridge_name} ${CMW_BRIDGE_SOURCES})
        set_property(TARGET ${bridge_name} PROPERTY OUTPUT_NAME ${bridge_name})
        set_property(TARGET ${bridge_name} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bridge/bin)
    endif (CMW_BRIDGE_TYPE STREQUAL "CMW_BRIDGE_LIB")

    target_link_libraries(${bridge_name} ${CMW_BRIDGE_LIBRARIES})
    target_include_directories(${bridge_name} PRIVATE ${CMW_BRIDGE_INCLUDES})
    target_compile_definitions(${bridge_name} PRIVATE ${CMW_BRIDGE_DEFINITIONS})

    set(target_rpath)
    foreach (path ${HOLO_ROOT}/lib ${HOLO_3RDPARTY_ROOT}/lib)
        file(RELATIVE_PATH rpath ${HOLO_ROOT}/${CMW_BRIDGE_INSTALL_DIR}/bridge ${path})
        list(APPEND target_rpath "\$ORIGIN/${rpath}")
    endforeach (path)
    set_target_properties(${bridge_name} PROPERTIES INSTALL_RPATH "${target_rpath}")

    install(TARGETS ${bridge_name} DESTINATION ${CMW_BRIDGE_INSTALL_DIR}/bridge)
endfunction (_compile_cmw_bridge_target)

