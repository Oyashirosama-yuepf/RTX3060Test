# - Try to find Huawei ADSF package
#
# Once done this will define
#
#  ADSF_FOUND - system has adsf lib with correct version
#  ADSF_INCLUDE_DIRS - the adsf include directory
#  ADSF_LIBRARIES - the adsf library
#  ADSF_${comp}_FOUND - adsf component found
#  ADSF_${comp}_LIBRARY - the adsf component library
#
# The following targets will be defined
#
#  ADSF::${component}
#  ADSF::ADSF
#
#

if (HOLO_BUILD_PLATFORM STREQUAL "MDC610-1.0.012-B0120000.B011")
    if (NOT ADSF_FIND_COMPONENTS)
        set(ADSF_FIND_COMPONENTS adb)
    endif()

    find_path(ADSFI_INCLUDE_DIR "adsf/adsfi_base.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/include)
    MESSAGE(STATUS ADSFI_INCLUDE_DIR=${ADSFI_INCLUDE_DIR})
    find_path(ARXML_INCLUDE_DIR "impl_type_boolean.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/arxml_include)
    MESSAGE(STATUS ARXML_INCLUDE_DIR=${ARXML_INCLUDE_DIR})
    find_path(AscendDVPP_INCLUDE_DIR "HiDvpp.h" PATHS ${CMAKE_SYSROOT}/usr/include/dvpp)
    MESSAGE(STATUS AscendDVPP_INCLUDE_DIR=${AscendDVPP_INCLUDE_DIR})
    find_path(AscendHAL_INCLUDE_DIR "ascend_hal.h" PATHS ${CMAKE_SYSROOT}/usr/include/driver)
    MESSAGE(STATUS AscendHAL_INCLUDE_DIR=${AscendHAL_INCLUDE_DIR})
    set(ADSF_REQUIRED_VARS ADSFI_INCLUDE_DIR ARXML_INCLUDE_DIR AscendDVPP_INCLUDE_DIR AscendHAL_INCLUDE_DIR)
elseif (HOLO_BUILD_PLATFORM MATCHES "MDC610-1.0.017")
    if (NOT ADSF_FIND_COMPONENTS)
        set(ADSF_FIND_COMPONENTS adb adsf mdc_aiv)
    endif()

    find_path(ADSFI_INCLUDE_DIR "adsf/adsfi_base.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/adsf/include)
    MESSAGE(STATUS ADSFI_INCLUDE_DIR=${ADSFI_INCLUDE_DIR})
    find_path(ARXML_INCLUDE_DIR "impl_type_boolean.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/arxml_include)
    MESSAGE(STATUS ARXML_INCLUDE_DIR=${ARXML_INCLUDE_DIR})
    find_path(AscendDVPP_INCLUDE_DIR "HiDvpp.h" PATHS ${CMAKE_SYSROOT}/usr/include/dvpp)
    MESSAGE(STATUS AscendDVPP_INCLUDE_DIR=${AscendDVPP_INCLUDE_DIR})
    find_path(AscendHAL_INCLUDE_DIR "ascend_hal.h" PATHS ${CMAKE_SYSROOT}/usr/include/driver)
    MESSAGE(STATUS AscendHAL_INCLUDE_DIR=${AscendHAL_INCLUDE_DIR})
    find_path(HAFVENC_INCLUDE_DIR "video/haf_venc.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/adb/include)
    MESSAGE(STATUS HAFVENC_INCLUDE_DIR=${HAFVENC_INCLUDE_DIR})
    find_path(LOGGER_INCLUDE_DIR "core/logger.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/adb/include)
    MESSAGE(STATUS LOGGER_INCLUDE_DIR=${LOGGER_INCLUDE_DIR})
    set(ADSF_REQUIRED_VARS ADSFI_INCLUDE_DIR ARXML_INCLUDE_DIR AscendDVPP_INCLUDE_DIR AscendHAL_INCLUDE_DIR HAFVENC_INCLUDE_DIR LOGGER_INCLUDE_DIR)
elseif (HOLO_BUILD_PLATFORM MATCHES "MDC610-1.0.019")
    if (NOT ADSF_FIND_COMPONENTS)
        set(ADSF_FIND_COMPONENTS adb adsf mdc_aiv)
    endif()

    find_path(ADSFI_INCLUDE_DIR "adsf/adsfi_base.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/adsf/include)
    MESSAGE(STATUS ADSFI_INCLUDE_DIR=${ADSFI_INCLUDE_DIR})
    find_path(ARXML_INCLUDE_DIR "impl_type_boolean.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/arxml_include)
    MESSAGE(STATUS ARXML_INCLUDE_DIR=${ARXML_INCLUDE_DIR})
    find_path(AscendDVPP_INCLUDE_DIR "HiDvpp.h" PATHS ${CMAKE_SYSROOT}/usr/include/dvpp)
    MESSAGE(STATUS AscendDVPP_INCLUDE_DIR=${AscendDVPP_INCLUDE_DIR})
    find_path(AclDVPP_INCLUDE_DIR "hi_dvpp.h" PATHS ${CMAKE_SYSROOT}/usr/local/Ascend/acllib/include/acl/dvpp/)
    MESSAGE(STATUS AclDVPP_INCLUDE_DIR=${AclDVPP_INCLUDE_DIR})
    find_path(AscendHAL_INCLUDE_DIR "ascend_hal.h" PATHS ${CMAKE_SYSROOT}/usr/include/driver)
    MESSAGE(STATUS AscendHAL_INCLUDE_DIR=${AscendHAL_INCLUDE_DIR})
    find_path(HAFVENC_INCLUDE_DIR "video/haf_venc.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/adb/include)
    MESSAGE(STATUS HAFVENC_INCLUDE_DIR=${HAFVENC_INCLUDE_DIR})
    find_path(LOGGER_INCLUDE_DIR "core/logger.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/adb/include)
    MESSAGE(STATUS LOGGER_INCLUDE_DIR=${LOGGER_INCLUDE_DIR})
    set(ADSF_REQUIRED_VARS ADSFI_INCLUDE_DIR ARXML_INCLUDE_DIR AscendDVPP_INCLUDE_DIR AclDVPP_INCLUDE_DIR AscendHAL_INCLUDE_DIR HAFVENC_INCLUDE_DIR LOGGER_INCLUDE_DIR)
elseif (HOLO_BUILD_PLATFORM MATCHES "MDC610-1.1.001")
    if (NOT ADSF_FIND_COMPONENTS)
        set(ADSF_FIND_COMPONENTS adb adsf mdc_aiv)
    endif()

    find_path(ADSFI_INCLUDE_DIR "adsf/adsfi_base.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/adsf/include)
    MESSAGE(STATUS ADSFI_INCLUDE_DIR=${ADSFI_INCLUDE_DIR})
    find_path(ARXML_INCLUDE_DIR "impl_type_boolean.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/arxml_include)
    MESSAGE(STATUS ARXML_INCLUDE_DIR=${ARXML_INCLUDE_DIR})
    find_path(AscendDVPP_INCLUDE_DIR "HiDvpp.h" PATHS ${CMAKE_SYSROOT}/usr/include/dvpp)
    MESSAGE(STATUS AscendDVPP_INCLUDE_DIR=${AscendDVPP_INCLUDE_DIR})
    find_path(AclDVPP_INCLUDE_DIR "hi_dvpp.h" PATHS ${CMAKE_SYSROOT}/usr/local/Ascend/acllib/include/acl/dvpp)
    MESSAGE(STATUS AclDVPP_INCLUDE_DIR=${AclDVPP_INCLUDE_DIR})
    find_path(AscendHAL_INCLUDE_DIR "ascend_hal.h" PATHS ${CMAKE_SYSROOT}/usr/include/driver)
    MESSAGE(STATUS AscendHAL_INCLUDE_DIR=${AscendHAL_INCLUDE_DIR})
    find_path(HAFVENC_INCLUDE_DIR "video/haf_venc.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/adb/include)
    MESSAGE(STATUS HAFVENC_INCLUDE_DIR=${HAFVENC_INCLUDE_DIR})
    find_path(LOGGER_INCLUDE_DIR "core/logger.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/adb/include)
    MESSAGE(STATUS LOGGER_INCLUDE_DIR=${LOGGER_INCLUDE_DIR})
    set(ADSF_REQUIRED_VARS ADSFI_INCLUDE_DIR ARXML_INCLUDE_DIR AscendDVPP_INCLUDE_DIR AclDVPP_INCLUDE_DIR AscendHAL_INCLUDE_DIR HAFVENC_INCLUDE_DIR LOGGER_INCLUDE_DIR)
elseif (HOLO_BUILD_PLATFORM MATCHES "MDC610-1.1801.001")
    if (NOT ADSF_FIND_COMPONENTS)
        set(ADSF_FIND_COMPONENTS adb adsf mdc_aiv)
    endif()

    find_path(ADSFI_INCLUDE_DIR "adsf/adsfi_base.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/adsf/include)
    MESSAGE(STATUS ADSFI_INCLUDE_DIR=${ADSFI_INCLUDE_DIR})
    find_path(ARXML_INCLUDE_DIR "impl_type_boolean.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/arxml_include)
    MESSAGE(STATUS ARXML_INCLUDE_DIR=${ARXML_INCLUDE_DIR})
    find_path(AscendDVPP_INCLUDE_DIR "HiDvpp.h" PATHS ${CMAKE_SYSROOT}/usr/include/dvpp)
    MESSAGE(STATUS AscendDVPP_INCLUDE_DIR=${AscendDVPP_INCLUDE_DIR})
    find_path(AclDVPP_INCLUDE_DIR "hi_dvpp.h" PATHS ${CMAKE_SYSROOT}/usr/local/Ascend/runtime/include/acl/dvpp)
    MESSAGE(STATUS AclDVPP_INCLUDE_DIR=${AclDVPP_INCLUDE_DIR})
    find_path(AscendHAL_INCLUDE_DIR "ascend_hal.h" PATHS ${CMAKE_SYSROOT}/usr/include/driver)
    MESSAGE(STATUS AscendHAL_INCLUDE_DIR=${AscendHAL_INCLUDE_DIR})
    find_path(HAFVENC_INCLUDE_DIR "video/haf_venc.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/adb/include)
    MESSAGE(STATUS HAFVENC_INCLUDE_DIR=${HAFVENC_INCLUDE_DIR})
    find_path(LOGGER_INCLUDE_DIR "core/logger.h" PATHS ${CMAKE_SYSROOT}/usr/include/adsfi/adb/include)
    MESSAGE(STATUS LOGGER_INCLUDE_DIR=${LOGGER_INCLUDE_DIR})
    set(ADSF_REQUIRED_VARS ADSFI_INCLUDE_DIR ARXML_INCLUDE_DIR AscendDVPP_INCLUDE_DIR AclDVPP_INCLUDE_DIR AscendHAL_INCLUDE_DIR HAFVENC_INCLUDE_DIR LOGGER_INCLUDE_DIR)
endif()

foreach(lib ${ADSF_FIND_COMPONENTS})
    find_library(ADSF_${lib}_LIBRARY ${lib} PATHS ${CMAKE_SYSROOT}/usr/adsfi ${CMAKE_SYSROOT}/usr/lib/mdc_vector)
    list(APPEND ADSF_REQUIRED_VARS ADSF_${lib}_LIBRARY)
    message("ADSF_${lib}_LIBRARY = ${ADSF_${lib}_LIBRARY}")
    if(ADSF_${lib}_LIBRARY)
        set(ADSF_${lib}_FOUND 1)
        mark_as_advanced(ADSF_${lib}_LIBRARY)
        list(APPEND ADSF_LIBRARIES ${ADSF_${lib}_LIBRARY})
    endif()
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    ADSF
    REQUIRED_VARS
    ${ADSF_REQUIRED_VARS}
    HANDLE_COMPONENTS
    )

if(ADSF_FOUND)
    set(ADSF_INCLUDE_DIRS ${ADSFI_INCLUDE_DIR} ${ARXML_INCLUDE_DIR} ${AscendDVPP_INCLUDE_DIR} ${AscendHAL_INCLUDE_DIR}
                          ${HAFVENC_INCLUDE_DIR} ${LOGGER_INCLUDE_DIR} ${AclDVPP_INCLUDE_DIR})
    foreach(comp ${ADSF_FIND_COMPONENTS})
        if(NOT TARGET ADSF::${comp})
            add_library(ADSF::${comp} UNKNOWN IMPORTED)
            set_target_properties(ADSF::${comp} PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${ADSF_INCLUDE_DIRS}"
                IMPORTED_LOCATION ${ADSF_${comp}_LIBRARY}
                )
            list(APPEND acl_interface_libs ADSF::${comp})
        endif()
    endforeach()
    if (NOT TARGET ADSF::ADSF)
        add_library(ADSF::ADSF INTERFACE IMPORTED)
        set_target_properties(ADSF::ADSF PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${ADSF_INCLUDE_DIRS}"
            INTERFACE_LINK_LIBRARIES "${acl_interface_libs}"
            )
    endif()
endif()
