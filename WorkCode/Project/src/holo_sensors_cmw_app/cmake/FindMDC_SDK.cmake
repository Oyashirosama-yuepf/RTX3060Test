set(MDC_PLATFORM_SDK_ROOT ${CMAKE_SYSROOT}/../resources/package/aarch64/ubuntu-16.04/mdc_platform_sdk)
set(MDC_SDK_INCLUDE_DIRS ${MDC_PLATFORM_SDK_ROOT}/include CACHE STRING "")
set(MDC_SDK_LIBRARY_DIRS ${MDC_PLATFORM_SDK_ROOT}/lib CACHE STRING "")

set(MDC_COMMON_DEFINITIONS -DHAS_DDS_BINDING -DHAS_VSOMEIP_BINDING)
add_definitions(${MDC_COMMON_DEFINITIONS})
set(SDK_LIB ara_com ara_per ara_exec ara_log crypto ddscpp ddscore dlt gmock gmock_main iccshm JsonParser
	jsoncpp KeyValueStorage logging MdioDrvAdapter pthread pci_dev_info protobuf-c rng someip securec ssl
    vrtf_vcc vcc_ddsdriver vcc_someipdriver yaml-cpp)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    MDC_SDK 
    REQUIRED_VARS
    MDC_SDK_INCLUDE_DIRS
    HANDLE_COMPONENTS
    )

mark_as_advanced(
    MDC_SDK_INCLUDE_DIRS
    )    