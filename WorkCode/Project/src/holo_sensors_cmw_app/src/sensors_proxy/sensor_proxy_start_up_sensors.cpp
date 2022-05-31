/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sensors_proxy_app.cpp
 * @brief A driver for several sensors startup
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2022/01/21
 */

#include <csignal>
#include <sensors_proxy/sensors_proxy_app.h>

namespace holo_cmw
{
void SensorsProxy::StartUpAllSensors()
{
    for (uint32_t i=0; i<sensors_num_; i++)
    {
        switch (sensors_[i].type)
        {
            case SensorType::NOVATEL:
            {
                auto novatel = std::make_shared<NovatelDriverAppType>(bus_);
                novatel->Setup(config_file_[i], false);
                std::function<void(uint32_t, uint32_t)> novatel_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                    i, std::placeholders::_1, std::placeholders::_2);
                novatel->InstallCallback(novatel_handler);
                novatel_vec_.push_back(novatel);
                break;
            }
            case SensorType::LIVOX:
            {
                StartUpLivox(i);
                break;
            }
            case SensorType::PANDAR40:
            {
                StartUpPandar40(i);
                break;
            }
            case SensorType::PANDAR128:
            {
                StartUpPandar128(i);
                break;
            }
            case SensorType::RSRUBY:
            {
                StartUpRsruby(i);
                break;
            }
            case SensorType::HAP:
            {
                StartUpHap(i);
                break;
            }
            case SensorType::RSBPERAL:
            {
                StartUpRsbpearl(i);
                break;
            }
            case SensorType::OUTSTER:
            {
                StartUpOuster(i);
                break;
            }
            case SensorType::STARNETO:
            {
                StartUpStarneto(i);
                break;
            }
            case SensorType::GENERAL_CAMERA:
            {
                LOG(INFO) << "SensorType::CAMERA, i = " << i;
                StartUpCamera(i);
                break;
            }
            case SensorType::SMART_CAMERA:
            {
                LOG(INFO) << "SensorType::SMART_CAMERA, i = " << i;
                StartUpSmartCamera(i);
                break;
            }
            case SensorType::RADAR:
            {
                LOG(INFO) << "SensorType::RADAR, i = " << i;
                StartUpRadar(i);
                break;
            }
            case SensorType::UNKNOWN:
            {
                LOG(ERROR) << "check yaml please, not supported sensor type :" << static_cast<uint32_t>(sensors_[i].type);
                break;
            }

            default:
                break;
        }
    }

    LOG(INFO) << "End of StartUpAllSensors() ";
}

void SensorsProxy::StartUpLivox(uint32_t sensor_id)
{
    auto livox = std::make_shared<LivoxDriverAppType>(bus_);
    livox->Setup(config_file_[sensor_id], false);
    std::function<void(uint32_t, uint32_t)> livox_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
        sensor_id, std::placeholders::_1, std::placeholders::_2);
    livox->InstallLiveCallback(livox_handler);
    livox_vec_.push_back(livox);
}

void SensorsProxy::StartUpPandar40(uint32_t sensor_id)
{
    auto p40 = std::make_shared<P40DriverAppType>(bus_);
    p40->Setup(config_file_[sensor_id], false);
    std::function<void(uint32_t, uint32_t)> p40_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
        sensor_id, std::placeholders::_1, std::placeholders::_2);
    p40->InstallLiveCallback(p40_handler);
    p40_vec_.push_back(p40);
}

void SensorsProxy::StartUpPandar128(uint32_t sensor_id)
{
    auto p128 = std::make_shared<P128DriverAppType>(bus_);
    p128->Setup(config_file_[sensor_id], false);
    std::function<void(uint32_t, uint32_t)> p128_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
        sensor_id, std::placeholders::_1, std::placeholders::_2);
    p128->InstallLiveCallback(p128_handler);
    p128_vec_.push_back(p128);
}

void SensorsProxy::StartUpRsbpearl(uint32_t sensor_id)
{
    auto rsbp = std::make_shared<RsbpearlDriverAppType>(bus_);
    rsbp->Setup(config_file_[sensor_id], false);
    std::function<void(uint32_t, uint32_t)> rsbp_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
        sensor_id, std::placeholders::_1, std::placeholders::_2);
    rsbp->InstallLiveCallback(rsbp_handler);
    rsbp_vec_.push_back(rsbp);
}

void SensorsProxy::StartUpRsruby(uint32_t sensor_id)
{
    auto rsruby = std::make_shared<RsrubyDriverAppType>(bus_);
    rsruby->Setup(config_file_[sensor_id], false);
    std::function<void(uint32_t, uint32_t)> rsruby_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
        sensor_id, std::placeholders::_1, std::placeholders::_2);
    rsruby->InstallLiveCallback(rsruby_handler);
    rsruby_vec_.push_back(rsruby);
}

void SensorsProxy::StartUpHap(uint32_t sensor_id)
{
    auto hap = std::make_shared<HapDriverAppType>(bus_);
    hap->Setup(config_file_[sensor_id], false);
    std::function<void(uint32_t, uint32_t)> hap_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
        sensor_id, std::placeholders::_1, std::placeholders::_2);
    hap->InstallLiveCallback(hap_handler);
    hap_vec_.push_back(hap);
}

void SensorsProxy::StartUpOuster(uint32_t sensor_id)
{
    auto ouster = std::make_shared<OusterDriverAppType>(bus_);
    ouster->Setup(config_file_[sensor_id], false);
    std::function<void(uint32_t, uint32_t)> ouster_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
        sensor_id, std::placeholders::_1, std::placeholders::_2);
    ouster->InstallLiveCallback(ouster_handler);
    ouster_vec_.push_back(ouster);
}

void SensorsProxy::StartUpStarneto(uint32_t sensor_id)
{
    auto starneto = std::make_shared<StarnetoAppType>(bus_);
    starneto->Setup(config_file_[sensor_id], false);
    std::function<void(uint32_t, uint32_t)> starneto_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
        sensor_id, std::placeholders::_1, std::placeholders::_2);
    starneto->InstallLiveCallback(starneto_handler);
    starneto_vec_.push_back(starneto);
}



void SensorsProxy::StartUpSmartCamera(uint32_t sensor_id)
{
    holo::yaml::Node node        = holo::yaml::LoadFile(config_file_[sensor_id]);
    std::string      type        = node["type"].as<std::string>();
    std::string      interface   = node["interface"]["type"].as<std::string>();
    std::string      format      = node["format"].as<std::string>();
    LOG(INFO) << "type      = " << type;
    LOG(INFO) << "interface = " << interface;
    LOG(INFO) << "format    = " << format;
    std::string tif = type + ":" + interface + ":" + format;

    if (tif == "me3:udp:holocan")
    {
        auto sm = std::make_shared<SmartCameraMobileEyeHoloCanAppType>(bus_);
        sm->Setup(config_file_[sensor_id], false);
        std::function<void(uint32_t, uint32_t)> sm_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            sensor_id, std::placeholders::_1, std::placeholders::_2);
        sm->InstallLiveCallback(sm_handler);
        smt_camera_mobile_eye_vec_.push_back(sm);
    }
    else if (tif == "ifv300:udp:holocan")
    {
        auto sm = std::make_shared<SmartCameraIfv300HoloCanAppType>(bus_);
        sm->Setup(config_file_[sensor_id], false);
        std::function<void(uint32_t, uint32_t)> sm_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            sensor_id, std::placeholders::_1, std::placeholders::_2);
        sm->InstallLiveCallback(sm_handler);
        smt_camera_ifv300_vec_.push_back(sm);
    }
    else if (tif == "mpc2:udp:holocan")
    {
        auto sm = std::make_shared<SmartCameraBoschMpcHoloCanAppType>(bus_);
        sm->Setup(config_file_[sensor_id], false);
        std::function<void(uint32_t, uint32_t)> sm_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            sensor_id, std::placeholders::_1, std::placeholders::_2);
        sm->InstallLiveCallback(sm_handler);
        smt_camera_bosch_mpc_vec_.push_back(sm);
    }
    else if (tif == "matrix2:udp:holocan")
    {
        auto sm = std::make_shared<SmartCameraHorizonMatrixHoloCanAppType>(bus_);
        sm->Setup(config_file_[sensor_id], false);
        std::function<void(uint32_t, uint32_t)> sm_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            sensor_id, std::placeholders::_1, std::placeholders::_2);
        sm->InstallLiveCallback(sm_handler);
        smt_camera_horizon_matrix_vec_.push_back(sm);
    }
    else if ("me8:udp:holocan")
    {
        // auto sm = std::make_shared<SmartCameraMe8HoloCanAppType>(bus_);
        // sm->Setup(config_file_[sensor_id], false);
        // std::function<void(uint32_t, uint32_t)> sm_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
        //     sensor_id, std::placeholders::_1, std::placeholders::_2);
        // sm->InstallLiveCallback(sm_handler);
        // smt_camera_me8_vec_.push_back(sm);
    }
#if defined(ENABLE_MDC300_CAN_INTERFACE)
    else if (tif == "me3:mdc:holocan")
    {
        auto sm = std::make_shared<SmartCameraMobileEyeMdcCanAppType>(bus_);
        sm->Setup(config_file_[sensor_id], false);
        std::function<void(uint32_t, uint32_t)> sm_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            sensor_id, std::placeholders::_1, std::placeholders::_2);
        sm->InstallLiveCallback(sm_handler);
        smt_camera_mobile_eye_mdc_can_vec_.push_back(sm);
    }
    else if (tif == "ifv300:mdc:holocan")
    {
        auto sm = std::make_shared<SmartCameraIfv300MdcCanAppType>(bus_);
        sm->Setup(config_file_[sensor_id], false);
        std::function<void(uint32_t, uint32_t)> sm_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            sensor_id, std::placeholders::_1, std::placeholders::_2);
        sm->InstallLiveCallback(sm_handler);
        smt_camera_ifv300_mdc_can_vec_.push_back(sm);
    }
    else if (tif == "mpc2:mdc:holocan")
    {
        auto sm = std::make_shared<SmartCameraBoschMpcMdcCanAppType>(bus_);
        sm->Setup(config_file_[sensor_id], false);
        std::function<void(uint32_t, uint32_t)> sm_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            sensor_id, std::placeholders::_1, std::placeholders::_2);
        sm->InstallLiveCallback(sm_handler);
        smt_camera_bosch_mpc_mdc_can_vec_.push_back(sm);
    }
    else if (tif == "matrix2:mdc:holocan")
    {
        auto sm = std::make_shared<SmartCameraHorizonMatrixMdcCanAppType>(bus_);
        sm->Setup(config_file_[sensor_id], false);
        std::function<void(uint32_t, uint32_t)> sm_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            sensor_id, std::placeholders::_1, std::placeholders::_2);
        sm->InstallLiveCallback(sm_handler);
        smt_camera_horizon_mdc_can_vec_.push_back(sm);
    }
#endif
    else
    {
        LOG(ERROR) << "unsupported type-interface-format configuration: " << tif;
    }
}

void SensorsProxy::StartUpCamera(uint32_t sensor_id)
{
    holo::yaml::Node node        = holo::yaml::LoadFile(config_file_[sensor_id]);
    std::string      model       = node["model"].as<std::string>();
    std::string      encode_type = node["encode_type"].as<std::string>();
    LOG(INFO) << "model       = " << model;
    LOG(INFO) << "encode_type = " << encode_type;

    if (encode_type == "h264")
    {
        if (model == "CAMERA_LEOPARD_M021")
        {
            auto camera = std::make_shared<ImageCaptureH264LeopardM021AppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h264_leopard_m021_vec_.push_back(camera);
        }
        else if (model == "CAMERA_LEOPARD_AP020")
        {
            auto camera = std::make_shared<ImageCaptureH264LeopardAp020AppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h264_leopard_ap020_vec_.push_back(camera);
        }
        else if (model == "CAMERA_LEOPARD_AR0231")
        {
            auto camera = std::make_shared<ImageCaptureH264LeopardAr0231AppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h264_leopard_ar0231_vec_.push_back(camera);
        }
        else if (model == "CAMERA_LEOPARD_OV490")
        {
            auto camera = std::make_shared<ImageCaptureH264LeopardOv490AppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h264_leopard_ov490_vec_.push_back(camera);
        }
        else if (model == "CAMERA_ENTRON_F001R")
        {
            auto camera = std::make_shared<ImageCaptureH264EntronF001rAppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h264_entron_f001r_vec_.push_back(camera);
        }
        else if (model == "CAMERA_ENTRON_S001R")
        {
            auto camera = std::make_shared<ImageCaptureH264EntronS001rAppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h264_entron_s001r_vec_.push_back(camera);
        }
        else if (model == "CAMERA_V4L2_GENERAL")
        {
            auto camera = std::make_shared<ImageCaptureH264V4l2GeneralAppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h264_v4l2_general_vec_.push_back(camera);
        }
        else if (model == "CAMERA_VIRTUAL")
        {
            // auto camera = std::make_shared<ImageCaptureH264VirtualAppType>(bus_);
            // camera->Setup(config_file_[sensor_id], std::string(""), false);
            // std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            //     sensor_id, std::placeholders::_1, std::placeholders::_2);
            // camera->InstallLiveCallback(camera_handler);
            // camera_h264_virtual_vec_.push_back(camera);
        }
        else
        {
            LOG(ERROR) << "unknown camera model";
        }
    }
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
    else if (encode_type == "h265")
    {
        if ((model == "CAMERA_MDC610_HONGJING_NV12") || (model == "CAMERA_MDC610"))
        {
            auto camera = std::make_shared<ImageCaptureH265Mdc610HongjingAppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h265_hongjing_vec_.push_back(camera);
        }
        else if (model == "CAMERA_MDC610_H265")
        {
            auto camera = std::make_shared<ImageCaptureH265Mdc610AppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h265_mdc610_vec_.push_back(camera);
        }
    }
#endif
    else
    {
        if (model == "CAMERA_LEOPARD_M021")
        {
            auto camera = std::make_shared<ImageCaptureH265LeopardM021AppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h265_leopard_m021_vec_.push_back(camera);
        }
        else if (model == "CAMERA_LEOPARD_AP020")
        {
            auto camera = std::make_shared<ImageCaptureH265LeopardAp020AppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h265_leopard_ap020_vec_.push_back(camera);
        }
        else if (model == "CAMERA_LEOPARD_AR0231")
        {
            auto camera = std::make_shared<ImageCaptureH265LeopardAr0231AppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h265_leopard_ar0231_vec_.push_back(camera);
        }
        else if (model == "CAMERA_LEOPARD_OV490")
        {
            auto camera = std::make_shared<ImageCaptureH265LeopardOv490AppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h265_leopard_ov490_vec_.push_back(camera);
        }
        else if (model == "CAMERA_ENTRON_F001R")
        {
            auto camera = std::make_shared<ImageCaptureH265EntronF001rAppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h265_entron_f001r_vec_.push_back(camera);
        }
        else if (model == "CAMERA_ENTRON_S001R")
        {
            auto camera = std::make_shared<ImageCaptureH265EntronS001rAppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h265_entron_s001r_vec_.push_back(camera);
        }
        else if (model == "CAMERA_V4L2_GENERAL")
        {
            auto camera = std::make_shared<ImageCaptureH265V4l2GeneralAppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_h265_v4l2_general_vec_.push_back(camera);
        }
        else if (model == "CAMERA_VIRTUAL")
        {
            // auto camera = std::make_shared<ImageCaptureH265VirtualAppType>(bus_);
            // camera->Setup(config_file_[sensor_id], std::string(""), false);
            // std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            //     sensor_id, std::placeholders::_1, std::placeholders::_2);
            // camera->InstallLiveCallback(camera_handler);
            // camera_h265_virtual_vec_.push_back(camera);
        }
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
        else if ((model == "CAMERA_MDC610_HONGJING_NV12") || (model == "CAMERA_MDC610"))
        {
            // auto camera = std::make_shared<ImageCaptureNullMdc610HongjingAppType>(bus_);
            // camera->Setup(config_file_[sensor_id], std::string(""), false);
            // std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            //     sensor_id, std::placeholders::_1, std::placeholders::_2);
            // camera->InstallLiveCallback(camera_handler);
            // camera_null_mdc610_hj_vec_.push_back(camera);
        }
        else if (model == "CAMERA_MDC610_H265")
        {
            auto camera = std::make_shared<ImageCaptureNullMdc610AppType>(bus_);
            camera->Setup(config_file_[sensor_id], std::string(""), false);
            std::function<void(uint32_t, uint32_t)> camera_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
                sensor_id, std::placeholders::_1, std::placeholders::_2);
            camera->InstallLiveCallback(camera_handler);
            camera_null_mdc610_vec_.push_back(camera);
        }
#endif
        else
        {
            LOG(ERROR) << "unknown camera model";
        }
    }
}

void SensorsProxy::StartUpRadar(uint32_t sensor_id)
{
    holo::yaml::Node node        = holo::yaml::LoadFile(config_file_[sensor_id]);
    std::string      interface   = node["interface"]["type"].as<std::string>("udp");
    std::string      format      = node["format"].as<std::string>("holocan");
    LOG(INFO) << "interface = " << interface;
    LOG(INFO) << "format    = " << format;
    std::string desc             = interface + ":" + format;

    if (desc == "udp:holocan")
    {
        auto radar = std::make_shared<RadarHoloCanAppType>(bus_);
        radar->Setup(config_file_[sensor_id], false);
        std::function<void(uint32_t, uint32_t)> radar_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            sensor_id, std::placeholders::_1, std::placeholders::_2);
        radar->InstallLiveCallback(radar_handler);
        radar_holo_can_vec_.push_back(radar);
    }
#if defined(ENABLE_MDC300_CAN_INTERFACE)
    else if (desc == "mdc:holocan")
    {
        auto radar = std::make_shared<RadarMdcCanAppType>(bus_);
        radar->Setup(config_file_[sensor_id], false);
        std::function<void(uint32_t, uint32_t)> radar_handler = std::bind(&holo_cmw::SensorsProxy::SetHz, this,
            sensor_id, std::placeholders::_1, std::placeholders::_2);
        radar->InstallLiveCallback(radar_handler);
        radar_mdc_can_vec_.push_back(radar);
    }
#endif
    else
    {
        LOG(ERROR) << "unsupported radar format configuration: " << format;
    }
}

}
