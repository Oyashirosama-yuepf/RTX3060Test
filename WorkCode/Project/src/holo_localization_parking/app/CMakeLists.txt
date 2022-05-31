find_package(Boost COMPONENTS system program_options REQUIRED)
set(lib_support holo_localization_parking Boost::system Boost::program_options)
if(holo_localization_deep_FOUND)
    list(APPEND lib_support
        holo_localization::holo_localization_deep
        ${TORCH_LIBRARIES})
endif()
# visual_mapping
HOLO_COMPILE_APP(visual_mapping
    SOURCES
    visual_mapping/visual_mapping.cpp
    LIBRARIES
    ${lib_support}
    INSTALL_DIR
    bin/holo_localization_parking
    )
# avp_mapping
if(HOLO_BUILD_AVP_MAPPING)
    HOLO_COMPILE_APP(avp_mapping
        SOURCES
        avp_mapping/avp_mapping.cpp
        LIBRARIES
        ${lib_support}
        INSTALL_DIR
        bin/holo_localization_parking
        )
endif(HOLO_BUILD_AVP_MAPPING)