# * Try to find ti psdk lib
#
# Once done this will define
#
# TI_PSDK_FOUND - system has psdk lib with correct version

if(NOT TI_PSDK_VERSION)
    set(TI_PSDK_VERSION "07.01.00.11")
    message(
        WARNING
            "TI_PSDK_VERSION not specified! Using default version ${TI_PSDK_VERSION}"
    )
endif()

if(TI_PSDK_PATCH_VERSION)
    set(TI_PSDK_VERSION_POSTFIX "-${TI_PSDK_PATCH_VERSION}")
endif()

string(TOUPPER ${CMAKE_SYSTEM_NAME} UPPER_SYSNAME)
string(TOLOWER ${CMAKE_SYSTEM_NAME} LOWER_SYSNAME)

if(TI_PSDK_VERSION STREQUAL "07.00.00.11")
    set(TI_PSDK_ROOT_DIR "psdk_rtos_auto_j7_07_00_00_11${TI_PSDK_VERSION_POSTFIX}")
    set(TI_PSDK_TIDL_VERSION "j7_01_02_00_09")
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(_IMAGING_LIBS
            libti_imaging_aealg.a
            libti_imaging_awbalg.a
            libti_imaging_dcc.a
            libti_imaging_ittsrvr.a
            libti_imaging_sensordrv.a
            libvx_kernels_imaging.a
            libvx_target_kernels_imaging_aewb.a)
        set(_TIOVX_LIBS
            libvx_conformance_engine.a
            libvx_kernels_host_utils.a
            libvx_kernels_target_utils.a
            libvx_platform_psdk_j7_linux.a
            libvx_tutorial.a
            libvx_conformance_tests.a
            libvx_kernels_hwa.a
            libvx_kernels_test_kernels.a
            libvx_target_kernels_source_sink.a
            libvx_utils.a
            libvx_conformance_tests_testmodule.a
            libvx_kernels_hwa_tests.a
            libvx_kernels_test_kernels_tests.a
            libvx_tiovx_tests.a
            libvx_vxu.a
            libvx_framework.a
            libvx_kernels_openvx_core.a
            libvx_kernels_tidl.a
            libvx_tiovx_tidl_tests.a)
        set(_VISION_APPS_LIBS
            libapp_tirtos_linux_mpu1_common.a
            libapp_utils_remote_service.a
            libvx_applib_sde_singlelayer.a
            libvx_kernels_img_proc.a
            # libvx_srv_render_utils_tools.a
            libapp_utils_console_io.a
            libitt_server.a
            libvx_applib_srv_bowl_lut_gen.a
            libvx_kernels_lidar.a
            libvx_target_kernels_fileio.a
            libapp_utils_draw2d.a
            libnetwork_api.a
            libvx_applib_srv_calibration.a
            libvx_kernels_park_assist.a
            libvx_target_kernels_lidar_arm.a
            libapp_utils_grpx.a
            libvx_applib_fused_ogmap.a
            libvx_applib_surround_radar_ogmap.a
            libvx_kernels_sample.a
            libvx_target_kernels_park_assist.a
            libapp_utils_ipc.a
            libvx_applib_lidar_ogmap.a
            libvx_applib_surround_sfm_ogmap.a
            libvx_kernels_srv.a
            libvx_target_kernels_sample_a72.a
            libapp_utils_iss.a
            libvx_applib_ps_mapping.a
            libvx_applib_tests.a
            libvx_kernels_srv_tests.a
            libvx_target_kernels_srv_gpu.a
            libapp_utils_mem.a
            libvx_applib_radar_gtrack.a
            libvx_app_ptk_demo_common.a
            libvx_kernels_stereo.a
            libvx_target_kernels_stereo.a
            libapp_utils_opengl.a
            libvx_applib_sde_multilayer.a
            libvx_kernels_common.a
            libvx_kernels_stereo_tests.a
            libapp_utils_perf_stats.a
            libvx_applib_sde_obstacle_detection.a
            libvx_kernels_fileio.a
            # libvx_srv_render_utils.a
        )
    elseif(CMAKE_SYSTEM_NAME STREQUAL "QNX")
        set(_IMAGING_LIBS)
        set(TIOVX_LIBS)
        set(_VISION_APPS_LIBS
            libapp_tirtos_qnx_mpu1_common.a
            libapp_utils_opengl.a
            libvx_applib_srv_calibration.a
            libvx_kernels_park_assist.a
            # libvx_srv_render_utils_tools.a
            libapp_utils_console_io.a
            libapp_utils_perf_stats.a
            libvx_applib_tests.a
            libvx_kernels_sample.a
            libvx_target_kernels_fileio.a
            libapp_utils_draw2d.a
            libapp_utils_remote_service.a
            libvx_app_ptk_demo_common.a
            libvx_kernels_srv.a
            libvx_target_kernels_lidar_arm.a
            libapp_utils_grpx.a
            libitt_server.a
            libvx_kernels_common.a
            libvx_kernels_srv_tests.a
            libvx_target_kernels_park_assist.a
            libapp_utils_ipc.a
            libnetwork_api.a
            libvx_kernels_fileio.a
            libvx_kernels_stereo.a
            libvx_target_kernels_sample_a72.a
            libapp_utils_iss.a
            libvx_applib_ps_mapping.a
            libvx_kernels_img_proc.a
            libvx_kernels_stereo_tests.a
            libvx_target_kernels_srv_gpu.a
            libapp_utils_mem.a
            libvx_applib_srv_bowl_lut_gen.a
            libvx_kernels_lidar.a
            # libvx_srv_render_utils.a
            libvx_target_kernels_stereo.a)
    endif()
elseif(TI_PSDK_VERSION STREQUAL "07.01.00.11")
    set(TI_PSDK_ROOT_DIR "ti-processor-sdk-rtos-j721e-evm-07_01_00_11${TI_PSDK_VERSION_POSTFIX}")
    set(TI_PSDK_TIDL_VERSION "j7_01_03_00_11")
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(_IMAGING_LIBS
            libti_imaging_aealg.a
            libti_imaging_awbalg.a
            libti_imaging_dcc.a
            libti_imaging_ittsrvr.a
            libti_imaging_sensordrv.a
            libvx_kernels_imaging.a
            libvx_target_kernels_imaging_aewb.a)

        set(_TIOVX_LIBS
            libvx_conformance_engine.a
            libvx_kernels_host_utils.a
            libvx_kernels_target_utils.a
            libvx_platform_psdk_j7_${LOWER_SYSNAME}.a
            libvx_tutorial.a
            libvx_conformance_tests.a
            libvx_kernels_hwa.a
            libvx_kernels_test_kernels.a
            libvx_target_kernels_source_sink.a
            libvx_utils.a
            libvx_conformance_tests_testmodule.a
            libvx_kernels_hwa_tests.a
            libvx_kernels_test_kernels_tests.a
            libvx_tiovx_tests.a
            libvx_vxu.a
            libvx_framework.a
            libvx_kernels_openvx_core.a
            libvx_kernels_tidl.a
            libvx_tiovx_tidl_tests.a)

        set(_VISION_APPS_LIBS
            libapp_tirtos_${LOWER_SYSNAME}_mpu1_common.a
            libapp_utils_perf_stats.a
            libvx_applib_sde_singlelayer.a
            libvx_kernels_fileio.a
            # libvx_srv_render_utils_tools.a
            libapp_utils_console_io.a
            libapp_utils_remote_service.a
            libvx_applib_semseg_cnn.a
            libvx_kernels_img_proc.a
            libvx_target_kernels_fileio.a
            libapp_utils_draw2d.a
            libvx_applib_common.a
            libvx_applib_srv_bowl_lut_gen.a
            libvx_kernels_lidar.a
            libvx_target_kernels_img_proc_a72.a
            libapp_utils_grpx.a
            libvx_applib_fused_ogmap.a
            libvx_applib_srv_calibration.a
            libvx_kernels_park_assist.a
            libvx_target_kernels_lidar_arm.a
            libapp_utils_ipc.a
            libvx_applib_lidar_ogmap.a
            libvx_applib_ss_sde_detection.a
            libvx_kernels_sample.a
            libvx_target_kernels_park_assist.a
            libapp_utils_iss.a
            libvx_applib_ps_mapping.a
            libvx_applib_surround_radar_ogmap.a
            libvx_kernels_srv.a
            libvx_target_kernels_sample_a72.a
            libapp_utils_itt_server.a
            libvx_applib_radar_gtrack.a
            libvx_applib_surround_sfm_ogmap.a
            libvx_kernels_srv_tests.a
            libvx_target_kernels_srv_gpu.a
            libapp_utils_mem.a
            libvx_applib_sde_ldc.a
            libvx_applib_tests.a
            libvx_kernels_stereo.a
            libvx_target_kernels_stereo.a
            libapp_utils_network_api.a
            libvx_applib_sde_multilayer.a
            libvx_app_ptk_demo_common.a
            libvx_kernels_stereo_tests.a
            libapp_utils_opengl.a
            libvx_applib_sde_obstacle_detection.a
            libvx_kernels_common.a
            # libvx_srv_render_utils.a
        )

        find_path(TI_PSDK_TARGETFS "/usr/lib/libti_rpmsg_char.so"
                  PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}/targetfs")
        find_library(TI_RPMSG_CHAR_LIBRARY ti_rpmsg_char
                     PATHS ${TI_PSDK_TARGETFS}/usr/lib)

    elseif(CMAKE_SYSTEM_NAME STREQUAL "QNX")
        set(_IMAGING_LIBS
            libti_imaging_aealg.a libti_imaging_ittsrvr.a
            libti_imaging_sensordrv.a libvx_kernels_imaging.a
            libvx_target_kernels_imaging_aewb.a)

        set(_TIOVX_LIBS
            libvx_conformance_engine.a
            libvx_kernels_host_utils.a
            libvx_kernels_target_utils.a
            libvx_platform_psdk_j7_qnx.a
            libvx_tutorial.a
            libvx_conformance_tests.a
            libvx_kernels_hwa.a
            libvx_kernels_test_kernels.a
            libvx_target_kernels_source_sink.a
            libvx_utils.a
            libvx_conformance_tests_testmodule.a
            libvx_kernels_hwa_tests.a
            libvx_kernels_test_kernels_tests.a
            libvx_tiovx_tests.a
            libvx_vxu.a
            libvx_framework.a
            libvx_kernels_openvx_core.a
            libvx_kernels_tidl.a
            libvx_tiovx_tidl_tests.a)

        set(_VISION_APPS_LIBS
            libapp_tirtos_qnx_mpu1_common.a
            libapp_utils_network_api.a
            libvx_app_ptk_demo_common.a
            libvx_kernels_srv_tests.a
            libvx_target_kernels_park_assist.a
            libapp_utils_console_io.a
            libapp_utils_opengl.a
            libvx_kernels_common.a
            libvx_kernels_stereo.a
            libvx_target_kernels_sample_a72.a
            libapp_utils_draw2d.a
            libapp_utils_perf_stats.a
            libvx_kernels_fileio.a
            libvx_kernels_stereo_tests.a
            libvx_target_kernels_srv_gpu.a
            libapp_utils_grpx.a
            libapp_utils_remote_service.a
            libvx_kernels_img_proc.a
            libvx_srv_render_utils.a
            libvx_target_kernels_stereo.a
            libapp_utils_ipc.a
            libvx_applib_ps_mapping.a
            libvx_kernels_lidar.a
            libvx_srv_render_utils_tools.a
            libapp_utils_iss.a
            libvx_applib_srv_bowl_lut_gen.a
            libvx_kernels_park_assist.a
            libvx_target_kernels_fileio.a
            libapp_utils_itt_server.a
            libvx_applib_srv_calibration.a
            libvx_kernels_sample.a
            libvx_target_kernels_img_proc_a72.a
            libapp_utils_mem.a
            libvx_applib_tests.a
            libvx_kernels_srv.a
            libvx_target_kernels_lidar_arm.a)

        set(_qnx_libs
            # psdkqa/qnx/devnp/ethremotecfg/aarch64/a.le/libti-remoteswitchcfg-client.a
            # psdkqa/qnx/devnp/remote_device/aarch64/a.le/libti-remote-device-client.a
            # psdkqa/qnx/resmgr/udma_qnx_rsmgr/usr/aarch64/a.le/libtiudma-usr.a
            psdkqa/qnx/resmgr/ipc_qnx_rsmgr/usr/aarch64/a.le/libtiipc-usr.a
            psdkqa/qnx/sharedmemallocator/usr/aarch64/a.le/libsharedmemallocator.a
            # psdkqa/pdk/packages/ti/osal/lib/qnx/j721e/qnx_a72/release/enetphy.aa72fg
            # psdkqa/pdk/packages/ti/osal/lib/qnx/j721e/qnx_a72/release/enetsoc.aa72fg
            # psdkqa/pdk/packages/ti/osal/lib/qnx/j721e/qnx_a72/release/enet.aa72fg
            # psdkqa/pdk/packages/ti/drv/udma/lib/j721e/qnx_mpu1_0/release/udma_apputils.aa72fg
            # psdkqa/pdk/packages/ti/osal/lib/qnx/j721e/qnx_a72/release/sciclient.aa72fg
            psdkqa/pdk/packages/ti/osal/lib/qnx/j721e/qnx_a72/release/ti.osal.aa72fg
            # psdkqa/pdk/packages/ti/csl/lib/j721e/qnx_a72/release/ti.csl.aa72fg
        )
        find_path(
            PSDK_QNX_ROOT
            psdkqa/qnx/resmgr/ipc_qnx_rsmgr/usr/aarch64/a.le/libtiipc-usr.a
            PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}")
        list(APPEND REQUIRED_VARS PSDK_QNX_ROOT)
        message("PSDK_QNX_ROOT=${PSDK_QNX_ROOT}")
        foreach(lib ${_qnx_libs})
            set(PSDK_QNX_LIBS ${PSDK_QNX_ROOT}/${lib} ${PSDK_QNX_LIBS})
        endforeach()
        set(PSDK_QNX_LIBS ${PSDK_QNX_LIBS} GLESv2 EGL screen)

    else()
        message(
            FATAL_ERROR "Unsupported CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME}")
    endif()
elseif(TI_PSDK_VERSION STREQUAL "07.02.00.06")
    set(TI_PSDK_ROOT_DIR "ti-processor-sdk-rtos-j721e-evm-07_02_00_06${TI_PSDK_VERSION_POSTFIX}")
    set(TI_PSDK_TIDL_VERSION "j7_01_04_00_08")
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(_IMAGING_LIBS
            libti_imaging_aealg.a
            libti_imaging_awbalg.a
            libti_imaging_dcc.a
            libti_imaging_ittsrvr.a
            libti_imaging_sensordrv.a
            libvx_kernels_imaging.a
            libvx_target_kernels_imaging_aewb.a)

        set(_TIOVX_LIBS
            libvx_conformance_engine.a
            libvx_conformance_tests.a
            libvx_conformance_tests_testmodule.a
            libvx_framework.a
            libvx_kernels_host_utils.a
            libvx_kernels_hwa.a
            libvx_kernels_hwa_tests.a
            libvx_kernels_openvx_core.a
            libvx_kernels_target_utils.a
            libvx_kernels_test_kernels.a
            libvx_kernels_test_kernels_tests.a
            libvx_kernels_tidl.a
            libvx_platform_psdk_j7_${LOWER_SYSNAME}.a
            libvx_target_kernels_source_sink.a
            libvx_tiovx_tests.a
            libvx_tiovx_tidl_tests.a
            libvx_tutorial.a
            libvx_utils.a
            libvx_vxu.a)

        set(_VISION_APPS_LIBS
            libapp_tirtos_${LOWER_SYSNAME}_mpu1_common.a
            libapp_utils_console_io.a
            libapp_utils_draw2d.a
            libapp_utils_grpx.a
            libapp_utils_ipc.a
            libapp_utils_iss.a
            libapp_utils_itt_server.a
            libapp_utils_mem.a
            libapp_utils_network_api.a
            libapp_utils_opengl.a
            libapp_utils_perf_stats.a
            libapp_utils_remote_service.a
            libvx_applib_common.a
            libvx_applib_fused_ogmap.a
            libvx_applib_lidar_ogmap.a
            libvx_applib_ps_mapping.a
            libvx_applib_radar_gtrack.a
            libvx_applib_sde_ldc.a
            libvx_applib_sde_multilayer.a
            libvx_applib_sde_obstacle_detection.a
            libvx_applib_sde_singlelayer.a
            libvx_applib_semseg_cnn.a
            libvx_applib_srv_bowl_lut_gen.a
            libvx_applib_srv_calibration.a
            libvx_applib_ss_sde_detection.a
            libvx_applib_surround_radar_ogmap.a
            libvx_applib_surround_sfm_ogmap.a
            libvx_applib_tests.a
            libvx_app_modules.a
            libvx_app_ptk_demo_common.a
            libvx_kernels_common.a
            libvx_kernels_fileio.a
            libvx_kernels_img_proc.a
            libvx_kernels_lidar.a
            libvx_kernels_park_assist.a
            libvx_kernels_sample.a
            libvx_kernels_srv.a
            libvx_kernels_srv_tests.a
            libvx_kernels_stereo.a
            libvx_kernels_stereo_tests.a
            libvx_srv_render_utils.a
            libvx_srv_render_utils_tools.a
            libvx_target_kernels_fileio.a
            libvx_target_kernels_img_proc_a72.a
            libvx_target_kernels_lidar_arm.a
            libvx_target_kernels_park_assist.a
            libvx_target_kernels_sample_a72.a
            libvx_target_kernels_srv_gpu.a
            libvx_target_kernels_stereo.a)

        find_path(TI_PSDK_TARGETFS "/usr/lib/libti_rpmsg_char.so"
                  PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}/targetfs")
        find_library(TI_RPMSG_CHAR_LIBRARY ti_rpmsg_char
                     PATHS ${TI_PSDK_TARGETFS}/usr/lib)
    else()
        message(
            FATAL_ERROR "Unsupported CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME}")
    endif()
else()
    message(FATAL_ERROR "Unsupported TI_PSDK version ${TI_PSDK_VERSION}")
endif()

find_path(TI_PSDK_imaging_INCLUDE_DIR_ROOT
          "kernels/include/TI/j7_imaging_aewb.h"
          PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}/imaging")
find_path(TI_PSDK_ivision_INCLUDE_DIR "ivision.h"
          PATH_SUFFIXES ${TI_PSDK_ROOT_DIR}/ivision)
find_path(TI_PSDK_tiadalg_INCLUDE_DIR "tiadalg_interface.h"
          PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}/tiadalg/include")
find_path(TI_PSDK_tidl_INCLUDE_DIR "ti_dl/inc/itidl_ti.h"
          PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}/tidl_${TI_PSDK_TIDL_VERSION}")
find_path(TI_PSDK_tiovx_INCLUDE_DIR "TI/tivx.h"
          PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}/tiovx/include")
find_path(TI_PSDK_tiovx_utils_INCLUDE_DIR "tivx_utils.h"
          PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}/tiovx/utils/include")
find_path(TI_PSDK_tiovx_kernels_INCLUDE_DIR "TI/tivx_kernels.h"
          PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}/tiovx/kernels/include")
find_path(TI_PSDK_tiovx_kernels_j7_INCLUDE_DIR "TI/j7.h"
          PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}/tiovx/kernels_j7/include")
find_path(TI_PSDK_vision_apps_INCLUDE_DIR_ROOT
          "kernels/common/target/vx_ptk_alg_common.h"
          PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}/vision_apps")
find_path(TI_PSDK_glm_INCLUDE_DIR_ROOT "glm/glm.hpp"
          PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}/glm")
find_path(TI_PSDK_vxlib_INCLUDE_DIR_ROOT "ti/vxlib/src/common/VXLIB_bufParams.h"
          PATH_SUFFIXES "${TI_PSDK_ROOT_DIR}/vxlib_c66x_1_1_5_0/packages")

set(REQUIRED_VARS
    TI_PSDK_imaging_INCLUDE_DIR_ROOT
    TI_PSDK_ivision_INCLUDE_DIR
    TI_PSDK_tiadalg_INCLUDE_DIR
    TI_PSDK_tidl_INCLUDE_DIR
    TI_PSDK_tiovx_INCLUDE_DIR
    TI_PSDK_tiovx_utils_INCLUDE_DIR
    TI_PSDK_tiovx_kernels_INCLUDE_DIR
    TI_PSDK_tiovx_kernels_j7_INCLUDE_DIR
    TI_PSDK_vision_apps_INCLUDE_DIR_ROOT
    TI_PSDK_glm_INCLUDE_DIR_ROOT
    TI_PSDK_vxlib_INCLUDE_DIR_ROOT)

mark_as_advanced(
    TI_PSDK_imaging_INCLUDE_DIR_ROOT
    TI_PSDK_ivision_INCLUDE_DIR
    TI_PSDK_tiadalg_INCLUDE_DIR
    TI_PSDK_tidl_INCLUDE_DIR
    TI_PSDK_tiovx_INCLUDE_DIR
    TI_PSDK_tiovx_utils_INCLUDE_DIR
    TI_PSDK_tiovx_kernels_INCLUDE_DIR
    TI_PSDK_tiovx_kernels_j7_INCLUDE_DIR
    TI_PSDK_vision_apps_INCLUDE_DIR_ROOT
    TI_PSDK_glm_INCLUDE_DIR_ROOT
    TI_PSDK_vxlib_INCLUDE_DIR_ROOT)

set(TI_PSDK_imaging_INCLUDE_DIRS
    ${TI_PSDK_imaging_INCLUDE_DIR_ROOT}
    ${TI_PSDK_imaging_INCLUDE_DIR_ROOT}/kernels/include
    ${TI_PSDK_imaging_INCLUDE_DIR_ROOT}/sensor_drv/include)
set(TI_PSDK_ivision_INCLUDE_DIRS ${TI_PSDK_ivision_INCLUDE_DIR})
set(TI_PSDK_tiadalg_INCLUDE_DIRS ${TI_PSDK_tiadalg_INCLUDE_DIR})
set(TI_PSDK_tidl_INCLUDE_DIRS ${TI_PSDK_tidl_INCLUDE_DIR}
                              ${TI_PSDK_tidl_INCLUDE_DIR}/ti_dl/inc)
set(TI_PSDK_tiovx_INCLUDE_DIRS
    ${TI_PSDK_tiovx_INCLUDE_DIR} ${TI_PSDK_tiovx_utils_INCLUDE_DIR}
    ${TI_PSDK_tiovx_kernels_INCLUDE_DIR}
    ${TI_PSDK_tiovx_kernels_j7_INCLUDE_DIR})
set(TI_PSDK_vision_apps_INCLUDE_DIRS
    ${TI_PSDK_vision_apps_INCLUDE_DIR_ROOT}/apps/basic_demos/app_tirtos/tirtos_${LOWER_SYSNAME}/mpu1
    ${TI_PSDK_vision_apps_INCLUDE_DIR_ROOT}/apps/basic_demos/app_tirtos/tirtos_${LOWER_SYSNAME}
    ${TI_PSDK_vision_apps_INCLUDE_DIR_ROOT}/apps/basic_demos/app_tirtos/common
    ${TI_PSDK_vision_apps_INCLUDE_DIR_ROOT}/kernels/img_proc/include
    ${TI_PSDK_vision_apps_INCLUDE_DIR_ROOT}/kernels/fileio/include
    ${TI_PSDK_vision_apps_INCLUDE_DIR_ROOT}/kernels/srv/include
    ${TI_PSDK_vision_apps_INCLUDE_DIR_ROOT}/applibs
    ${TI_PSDK_vision_apps_INCLUDE_DIR_ROOT}/kernels/srv/c66
    ${TI_PSDK_vision_apps_INCLUDE_DIR_ROOT}/kernels/srv/gpu/3dsrv
    ${TI_PSDK_vision_apps_INCLUDE_DIR_ROOT})
set(TI_PSDK_vxlib_INCLUDE_DIRS ${TI_PSDK_vxlib_INCLUDE_DIR_ROOT})

foreach(lib ${_IMAGING_LIBS})
    find_library(
        TI_PSDK_imaging_${lib}_LIBRARY ${lib}
        PATH_SUFFIXES
            "${TI_PSDK_ROOT_DIR}/imaging/lib/J7/A72/${UPPER_SYSNAME}/release")
    list(APPEND TI_PSDK_imaging_LIBRARIES ${TI_PSDK_imaging_${lib}_LIBRARY})
    list(APPEND REQUIRED_VARS TI_PSDK_imaging_${lib}_LIBRARY)
    mark_as_advanced(TI_PSDK_imaging_${lib}_LIBRARY)
endforeach()

foreach(lib ${_TIOVX_LIBS})
    find_library(
        TI_PSDK_tiovx_${lib}_LIBRARY ${lib}
        PATH_SUFFIXES
            "${TI_PSDK_ROOT_DIR}/tiovx/lib/J7/A72/${UPPER_SYSNAME}/release")
    list(APPEND TI_PSDK_tiovx_LIBRARIES ${TI_PSDK_tiovx_${lib}_LIBRARY})
    list(APPEND REQUIRED_VARS TI_PSDK_tiovx_${lib}_LIBRARY)
    mark_as_advanced(TI_PSDK_tiovx_${lib}_LIBRARY)
endforeach()

foreach(lib ${_VISION_APPS_LIBS})
    find_library(
        TI_PSDK_vision_apps_${lib}_LIBRARY ${lib}
        PATH_SUFFIXES
            "${TI_PSDK_ROOT_DIR}/vision_apps/lib/J7/A72/${UPPER_SYSNAME}/release"
    )
    list(APPEND TI_PSDK_vision_apps_LIBRARIES
         ${TI_PSDK_vision_apps_${lib}_LIBRARY})
    list(APPEND REQUIRED_VARS TI_PSDK_vision_apps_${lib}_LIBRARY)
    mark_as_advanced(TI_PSDK_vision_apps_${lib}_LIBRARY)
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TI_PSDK REQUIRED_VARS ${REQUIRED_VARS})

if(NOT TARGET TI_PSDK::imaging)
    add_library(TI_PSDK::imaging INTERFACE IMPORTED)
    set_target_properties(
        TI_PSDK::imaging
        PROPERTIES INTERFACE_LINK_LIBRARIES "${TI_PSDK_imaging_LIBRARIES}"
                   INTERFACE_INCLUDE_DIRECTORIES
                   "${TI_PSDK_imaging_INCLUDE_DIRS}")
endif()

if(NOT TARGET TI_PSDK::ivision)
    add_library(TI_PSDK::ivision INTERFACE IMPORTED)
    set_target_properties(
        TI_PSDK::ivision PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                    "${TI_PSDK_ivision_INCLUDE_DIRS}")
endif()

if(NOT TARGET TI_PSDK::tiadalg)
    add_library(TI_PSDK::tiadalg INTERFACE IMPORTED)
    set_target_properties(
        TI_PSDK::tiadalg PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                    "${TI_PSDK_tiadalg_INCLUDE_DIRS}")
endif()

if(NOT TARGET TI_PSDK::tidl)
    add_library(TI_PSDK::tidl INTERFACE IMPORTED)
    set_target_properties(
        TI_PSDK::tidl PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                 "${TI_PSDK_tidl_INCLUDE_DIRS}")
endif()

if(NOT TARGET TI_PSDK::tiovx)
    add_library(TI_PSDK::tiovx INTERFACE IMPORTED)
    set_target_properties(
        TI_PSDK::tiovx
        PROPERTIES INTERFACE_LINK_LIBRARIES "${TI_PSDK_tiovx_LIBRARIES}"
                   INTERFACE_INCLUDE_DIRECTORIES
                   "${TI_PSDK_tiovx_INCLUDE_DIRS}")
endif()

if(NOT TARGET TI_PSDK::vision_apps)
    set(_vision_apps_libs ${TI_PSDK_vision_apps_LIBRARIES}
                          ${TI_RPMSG_CHAR_LIBRARY} ${PSDK_QNX_LIBS})
    add_library(TI_PSDK::vision_apps INTERFACE IMPORTED)
    set_target_properties(
        TI_PSDK::vision_apps
        PROPERTIES INTERFACE_LINK_LIBRARIES "${_vision_apps_libs}"
                   INTERFACE_INCLUDE_DIRECTORIES
                   "${TI_PSDK_vision_apps_INCLUDE_DIRS}")
endif()

if(NOT TARGET TI_PSDK::vxlib)
    add_library(TI_PSDK::vxlib INTERFACE IMPORTED)
    set_target_properties(
        TI_PSDK::vxlib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                  "${TI_PSDK_vxlib_INCLUDE_DIRS}")
endif()

if(NOT TARGET TI_PSDK::psdk)
    add_library(TI_PSDK::psdk INTERFACE IMPORTED)
    set_target_properties(
        TI_PSDK::psdk
        PROPERTIES
            INTERFACE_LINK_LIBRARIES
            "-Wl,--start-group;TI_PSDK::imaging;TI_PSDK::ivision;TI_PSDK::tiadalg;TI_PSDK::tidl;TI_PSDK::tiovx;TI_PSDK::vision_apps;TI_PSDK::vxlib;-Wl,--end-group"
    )
endif()
