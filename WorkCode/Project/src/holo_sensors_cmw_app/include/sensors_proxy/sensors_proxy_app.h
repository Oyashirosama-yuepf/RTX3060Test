/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sensors_proxy_app.h
 * @brief This header file define the app of multi sensors driver
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2022/01/15
 */
#ifndef HOLO_CMW_APPS_SENSORS_PROXY_APP_H
#define HOLO_CMW_APPS_SENSORS_PROXY_APP_H

#include <conti_radar/conti_radar_app.h>
#include <gnss/starneto/starneto_app.h>
#include <holo/sensors/interface/udp_interface.h>
#include <holo/os/timer.h>
#include <holo/sensors/format/rawbuf.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/utils/yaml.h>
#include <camera/general/image_capture_app.h>
#include <lidar/livox/livox_app.h>
#include <lidar/livox/livox_hap_app.h>
#include <lidar/ouster/ouster_app.h>
#include <lidar/pandar/pandar_app.h>
#include <lidar/pandar128/pandar128_app.h>
#include <lidar/rsbpearl/rsbpearl_app.h>
#include <lidar/rsruby/rsruby_app.h>
#include <novatel/novatel_app.h>
#include <sensors_proxy/sensors_proxy_app.h>
#include <smart_camera/smart_camera_app.h>
#include <utils/timediff_utils.h>


namespace holo_cmw
{
using holo::sensors::bosch_mpc::BoschMpcDriverT;
using holo::sensors::horizon_matrix2::HorizonMatrix2DriverT;
using holo::sensors::ifv300::Ifv300DriverT;
using holo::sensors::mobileye::MobileyeDriverT;
using holo::sensors::format::HoloCanPacket;
using holo::sensors::format::SomeipPacket;
using holo::sensors::conti_radar::ContiRadarDriverT;

using RawbufferType               = holo::sensors::format::Rawbuffer<4096>;
using LivoxDriverAppType          = holo_cmw::LivoxDriverApp<holo::sensors::format::LivoxPacket<96>>;
using NovatelDriverAppType        = holo_cmw::NovatelDriverApp;
using P40DriverAppType            = holo_cmw::PandarDriverApp<1800>;
using P40PDriverAppType           = holo_cmw::PandarDriverApp<3560>;
using P128DriverAppType           = holo_cmw::Pandar128DriverApp;
using RsbpearlDriverAppType       = holo_cmw::RsbpearlDriverApp;
using RsrubyDriverAppType         = holo_cmw::RsrubyDriverApp;
using HapDriverAppType            = holo_cmw::LivoxHapDriverApp<holo::sensors::format::LivoxHapPacket<1440>>;
using OusterDriverAppType         = holo_cmw::OusterDriverApp<640>;
using StarnetoAppType             = holo_cmw::StarnetoAppT<holo::sensors::starneto::StarnetoDriver, UdpInterface<HoloCanPacket>>;


using SmartCameraMobileEyeHoloCanAppType     = holo_cmw::SmartCameraApp<MobileyeDriverT<HoloCanPacket>, UdpInterface<HoloCanPacket>>;
using SmartCameraMobileEyeSomeIpAppType      = holo_cmw::SmartCameraApp<MobileyeDriverT<holo::sensors::mobileye::SomeipPacketType>, UdpInterface<holo::sensors::mobileye::SomeipPacketType>>;
using SmartCameraIfv300HoloCanAppType        = holo_cmw::SmartCameraApp<Ifv300DriverT<HoloCanPacket>, UdpInterface<HoloCanPacket>>;
using SmartCameraIfv300SomeIpAppType         = holo_cmw::SmartCameraApp<Ifv300DriverT<holo::sensors::ifv300::SomeipPacketType>, UdpInterface<holo::sensors::ifv300::SomeipPacketType>>;
using SmartCameraBoschMpcHoloCanAppType      = holo_cmw::SmartCameraApp<BoschMpcDriverT<HoloCanPacket>, UdpInterface<HoloCanPacket>>;
using SmartCameraBoschMpcSomeIpAppType       = holo_cmw::SmartCameraApp<BoschMpcDriverT<holo::sensors::bosch_mpc::SomeipPacketType>, UdpInterface<holo::sensors::bosch_mpc::SomeipPacketType>>;
using SmartCameraHorizonMatrixHoloCanAppType = holo_cmw::SmartCameraApp<HorizonMatrix2DriverT<HoloCanPacket>, UdpInterface<HoloCanPacket>>;
#if defined(ENABLE_MDC300_CAN_INTERFACE)
using SmartCameraMobileEyeMdcCanAppType      = SmartCameraApp<MobileyeDriverT<HoloCanPacket>, MdcCanInterface<HoloCanPacket>>;
using SmartCameraIfv300MdcCanAppType         = SmartCameraApp<Ifv300DriverT<HoloCanPacket>, MdcCanInterface<HoloCanPacket>>;
using SmartCameraBoschMpcMdcCanAppType       = SmartCameraApp<BoschMpcDriverT<HoloCanPacket>, MdcCanInterface<HoloCanPacket>>;
using SmartCameraHorizonMatrixMdcCanAppType  = SmartCameraApp<HorizonMatrix2DriverT<HoloCanPacket>, MdcCanInterface<HoloCanPacket>>;
#endif

using ImageCaptureH264LeopardM021AppType   = ImageCaptureRgbAppT<CameraM021, Bayer8Converter, H264Encoder, HoloSyncDiffPacket>;
using ImageCaptureH264LeopardAp020AppType  = ImageCaptureRgbAppT<CameraAP020, YuyvConverter, H264Encoder, HoloSyncDiffPacket>;
using ImageCaptureH264LeopardAr0231AppType = ImageCaptureRgbAppT<CameraAR0231, YuyvConverter, H264Encoder, HoloSyncDiffPacket>;
using ImageCaptureH264LeopardOv490AppType  = ImageCaptureRgbAppT<CameraOV490, YuyvConverter, H264Encoder, HoloSyncDiffPacket>;
using ImageCaptureH264EntronF001rAppType   = ImageCaptureRgbAppT<CameraV4l2General, YuyvConverter, H264Encoder, HoloSyncDiffPacket>;
using ImageCaptureH264EntronS001rAppType   = ImageCaptureRgbAppT<CameraV4l2General, YuyvConverter, H264Encoder, HoloSyncDiffPacket>;
using ImageCaptureH264V4l2GeneralAppType   = ImageCaptureRgbAppT<CameraV4l2General, YuyvConverter, H264Encoder, HoloSyncDiffPacket>;
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
using ImageCaptureH265Mdc610AppType         = ImageCaptureEncodedApp<H265ToNv12Decoder>;
using ImageCaptureNullMdc610AppType         = ImageCaptureEncodedApp<H265ToNv12Decoder>;
using ImageCaptureH265Mdc610HongjingAppType = ImageCaptureMdc610App<holo::sensors::camera::RawToNv12Converter, DummyEncoder>;
#endif
using ImageCaptureH265LeopardM021AppType   = ImageCaptureRgbAppT<CameraM021, Bayer8Converter, DummyEncoder, HoloSyncDiffPacket>;
using ImageCaptureH265LeopardAp020AppType  = ImageCaptureRgbAppT<CameraAP020, YuyvConverter, DummyEncoder, HoloSyncDiffPacket>;
using ImageCaptureH265LeopardAr0231AppType = ImageCaptureRgbAppT<CameraAR0231, YuyvConverter, DummyEncoder, HoloSyncDiffPacket>;
using ImageCaptureH265LeopardOv490AppType  = ImageCaptureRgbAppT<CameraOV490, YuyvConverter, DummyEncoder, HoloSyncDiffPacket>;
using ImageCaptureH265EntronF001rAppType   = ImageCaptureRgbAppT<CameraV4l2General, YuyvConverter, DummyEncoder, HoloSyncDiffPacket>;
using ImageCaptureH265EntronS001rAppType   = ImageCaptureRgbAppT<CameraV4l2General, YuyvConverter, DummyEncoder, HoloSyncDiffPacket>;
using ImageCaptureH265V4l2GeneralAppType   = ImageCaptureRgbAppT<CameraV4l2General, YuyvConverter, DummyEncoder, HoloSyncDiffPacket>;

using RadarHoloCanAppType                  = holo_cmw::RadarAppT<ContiRadarDriverT<HoloCanPacket>, UdpInterface<HoloCanPacket>>;
#if defined(ENABLE_MDC300_CAN_INTERFACE)
using RadarMdcCanAppType                   = holo_cmw::RadarAppT<ContiRadarDriverT<HoloCanPacket>, MdcCanInterface<HoloCanPacket>>;
#endif

enum class SensorType : uint32_t
{
    NOVATEL          = 0,
    LIVOX            = 1,
    PANDAR40         = 2,
    PANDAR128        = 3,
    RSBPERAL         = 4,
    RSRUBY           = 5,
    HAP              = 6,
    GENERAL_CAMERA   = 7,
    SMART_CAMERA     = 8,
    OUTSTER          = 9,
    STARNETO         = 10,
    RADAR            = 11,
    SENSOR_TYPE_SUM  = 12,
    UNKNOWN          = 13
};

struct SensorOutputHz
{
    uint32_t min;
    uint32_t max;
    uint32_t current;
};

struct SensorStatistics
{
    uint32_t                    id;
    std::string                 name;
    uint32_t                    cpuload;
    std::vector<SensorOutputHz> hz;
    SensorType                  type;
};

class SensorsProxy
{
public:
    SensorsProxy(const std::string& config_file, uint32_t domain_id);

    bool SetHz(uint32_t sensor_code, uint32_t msg_code, uint32_t hz);
    void Callback(const RawbufferType& data, void* args, struct sockaddr_in* dest);
    void Bg(const struct sockaddr_in& live_addr, const struct sockaddr_in& user_addr);
    void StartUpAllSensors();
    void SwitchAllSensors(bool_t on_off);
    ~SensorsProxy();

private:
    void StartUpCamera(uint32_t sensor_id);
    void StartUpSmartCamera(uint32_t sensor_id);
    void StartUpLivox(uint32_t sensor_id);
    void StartUpPandar40(uint32_t sensor_id);
    void StartUpPandar128(uint32_t sensor_id);
    void StartUpRsbpearl(uint32_t sensor_id);
    void StartUpRsruby(uint32_t sensor_id);
    void StartUpHap(uint32_t sensor_id);
    void StartUpRadar(uint32_t sensor_id);
    void StartUpOuster(uint32_t sensor_id);
    void StartUpStarneto(uint32_t sensor_id);
    int32_t ShellExec(const char * cmd, std::vector<std::string>& rstring_list, bool nonblock = false);
    void SetTimediffValue(int64_t value) noexcept;
    void SetImageTimesyncData(const HoloSyncDiffPacket& data);

private:
    struct sockaddr_in                                                   live_addr_;
    struct sockaddr_in                                                   user_addr_;
    uint32_t                                                             sensors_num_;
    std::vector<SensorStatistics>                                        sensors_;
    std::shared_ptr<UdpInterface<RawbufferType>>                         status_interface_;
    std::shared_ptr<UdpInterface<RawbufferType>>                         online_interface_;
    std::shared_ptr<std::thread>                                         thread_;
    std::vector<std::string>                                             config_file_;
    bool_t                                                               back_ground_th_running_;
    bool_t                                                               rcev_app_broadcast_;
    std::shared_ptr<cmw_wrapper::BusType>                                bus_;
    std::string                                                          start_ins_cmd_;
    std::string                                                          stop_ins_cmd_;
    std::string                                                          start_holobag_cmd_;
    std::string                                                          stop_holobag_cmd_;
    std::string                                                          mount_ext_storage_dev_cmd_;
    std::string                                                          ext_storage_dev_check_cmd_;
    std::string                                                          ext_storage_dev_name_;
    std::string                                                          mkdir_cmd_;
    bool_t                                                               sensors_switch_;
    uint32_t                                                             app_live_counter_;
    uint32_t                                                             temp_live_counter_;

    std::vector<std::shared_ptr<NovatelDriverAppType>>                   novatel_vec_;
    std::vector<std::shared_ptr<LivoxDriverAppType>>                     livox_vec_;
    std::vector<std::shared_ptr<P40DriverAppType>>                       p40_vec_;
    std::vector<std::shared_ptr<P128DriverAppType>>                      p128_vec_;
    std::vector<std::shared_ptr<RsbpearlDriverAppType>>                  rsbp_vec_;
    std::vector<std::shared_ptr<RsrubyDriverAppType>>                    rsruby_vec_;
    std::vector<std::shared_ptr<HapDriverAppType>>                       hap_vec_;
    std::vector<std::shared_ptr<OusterDriverAppType>>                    ouster_vec_;
    std::vector<std::shared_ptr<StarnetoAppType>>                        starneto_vec_;
    
    /* smart camera */
    std::vector<std::shared_ptr<SmartCameraMobileEyeHoloCanAppType>>     smt_camera_mobile_eye_vec_;
    std::vector<std::shared_ptr<SmartCameraIfv300HoloCanAppType>>        smt_camera_ifv300_vec_;
    std::vector<std::shared_ptr<SmartCameraBoschMpcHoloCanAppType>>      smt_camera_bosch_mpc_vec_;
    std::vector<std::shared_ptr<SmartCameraHorizonMatrixHoloCanAppType>> smt_camera_horizon_matrix_vec_;
    // std::vector<std::shared_ptr<SmartCameraMe8HoloCanAppType>>           smt_camera_me8_vec_;
#if defined(ENABLE_MDC300_CAN_INTERFACE)
    std::vector<std::shared_ptr<SmartCameraMobileEyeMdcCanAppType>>      smt_camera_mobile_eye_mdc_can_vec_;
    std::vector<std::shared_ptr<SmartCameraIfv300MdcCanAppType>>         smt_camera_ifv300_mdc_can_vec_;
    std::vector<std::shared_ptr<SmartCameraBoschMpcMdcCanAppType>>       smt_camera_bosch_mpc_mdc_can_vec_;
    std::vector<std::shared_ptr<SmartCameraHorizonMatrixMdcCanAppType>>  smt_camera_horizon_mdc_can_vec_;
#endif

    /* camera */
    /* h264 */
    std::vector<std::shared_ptr<ImageCaptureH264LeopardM021AppType>>     camera_h264_leopard_m021_vec_;
    std::vector<std::shared_ptr<ImageCaptureH264LeopardAp020AppType>>    camera_h264_leopard_ap020_vec_;
    std::vector<std::shared_ptr<ImageCaptureH264LeopardAr0231AppType>>   camera_h264_leopard_ar0231_vec_;
    std::vector<std::shared_ptr<ImageCaptureH264LeopardOv490AppType>>    camera_h264_leopard_ov490_vec_;
    std::vector<std::shared_ptr<ImageCaptureH264EntronF001rAppType>>     camera_h264_entron_f001r_vec_;
    std::vector<std::shared_ptr<ImageCaptureH264EntronS001rAppType>>     camera_h264_entron_s001r_vec_;
    std::vector<std::shared_ptr<ImageCaptureH264V4l2GeneralAppType>>     camera_h264_v4l2_general_vec_;
    /* h265 */
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
    std::vector<std::shared_ptr<ImageCaptureH265Mdc610AppType>>          camera_h265_mdc610_vec_;
    std::vector<std::shared_ptr<ImageCaptureH265Mdc610HongjingAppType>>  camera_h265_hongjing_vec_;
#endif
    std::vector<std::shared_ptr<ImageCaptureH265LeopardM021AppType>>     camera_h265_leopard_m021_vec_;
    std::vector<std::shared_ptr<ImageCaptureH265LeopardAp020AppType>>    camera_h265_leopard_ap020_vec_;
    std::vector<std::shared_ptr<ImageCaptureH265LeopardAr0231AppType>>   camera_h265_leopard_ar0231_vec_;
    std::vector<std::shared_ptr<ImageCaptureH265LeopardOv490AppType>>    camera_h265_leopard_ov490_vec_;
    std::vector<std::shared_ptr<ImageCaptureH265EntronF001rAppType>>     camera_h265_entron_f001r_vec_;
    std::vector<std::shared_ptr<ImageCaptureH265EntronS001rAppType>>     camera_h265_entron_s001r_vec_;
    std::vector<std::shared_ptr<ImageCaptureH265V4l2GeneralAppType>>     camera_h265_v4l2_general_vec_;
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
    std::vector<std::shared_ptr<ImageCaptureNullMdc610AppType>>          camera_null_mdc610_vec_;
#endif

    std::vector<std::shared_ptr<RadarHoloCanAppType>>                    radar_holo_can_vec_;
#if defined(ENABLE_MDC300_CAN_INTERFACE)
    std::vector<std::shared_ptr<RadarMdcCanAppType>>                     radar_mdc_can_vec_;
#endif

    std::shared_ptr<TimediffGetter>                       timediff_getter_;
    std::shared_ptr<UdpInterface<HoloSyncDiffPacket>>     sync_interface_;
};


}

#endif
