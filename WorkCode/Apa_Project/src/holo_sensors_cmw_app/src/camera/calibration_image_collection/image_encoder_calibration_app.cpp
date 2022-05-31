/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_encoder_calibration_app.cpp
 * @brief main function for get camera calibration data
 * @author chuan.yong @ yongchuan@holomatic.com
 * @date 2022-1-4
 */

#include <fstream>
#include <iostream>

#include <camera/calibration_image_collection/image_encoder_calibration_app.h>
#include <holo/log/hololog.h>
#include <holo/os/time.h>
#include <holo/utils/holo_root.h>

#include <cmw_wrapper/utils/cxxopts.hpp>

using namespace holo::log;

namespace cmw_wrapper
{
template <typename Tenc>
bool CameraCalibrationEncoder<Tenc>::getParameters(std::string const& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);

        /// Step 1: Get all parameters about camera
        const std::string            camera_name = node["name"].as<std::string>();
        const std::string            topic       = node["topic"].as<std::string>();
        const holo::common::SensorId sensor_id   = node["sensor_id"].as<uint32_t>();
        const uint32_t               cols        = node["cols"].as<uint32_t>();
        const uint32_t               rows        = node["rows"].as<uint32_t>();
        const uint32_t               fps         = node["fps"].as<uint32_t>();

        std::shared_ptr<ImageIpc> img_ipc_ptr;
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
        img_ipc_ptr = std::make_shared<ImageIpc>(sensor_id, rows, cols, Image::Encoding::NV12);
#else
        img_ipc_ptr = std::make_shared<ImageIpc>(sensor_id, rows, cols);
#endif
        std::shared_ptr<Tenc> image_encoder_ptr;
        image_encoder_ptr = std::make_shared<Tenc>(cols, rows, fps);

        camera_.name              = camera_name;
        camera_.topic             = topic;
        camera_.image_ipc_ptr     = img_ipc_ptr;
        camera_.image_encoder_ptr = image_encoder_ptr;
    }
    catch (std::exception& e)
    {
        LOG(FATAL) << "Init Config Failure: " << config_file << "\n" << e.what();
        return false;
    }
    LOG(INFO) << "camera_name : " << camera_.name;
    LOG(INFO) << "camera image topic : " << camera_.topic;

    return true;
}

template <typename Tenc>
CameraCalibrationEncoder<Tenc>::~CameraCalibrationEncoder()
{
}

template <typename Tenc>
void CameraCalibrationEncoder<Tenc>::setUp(const std::string& config_file)
{
    if (!getParameters(config_file))
    {
        std::string error = "CameraCalibrationEncoder --- could not get the "
                            "parameters from config file !";
        LOG(ERROR) << error;
        throw holo::exception::OutOfRangeException(error);
    }

    // subcribe images
    std::string               camera_name       = camera_.name;
    std::string               topic             = camera_.topic;
    std::shared_ptr<ImageIpc> ipc_ptr           = camera_.image_ipc_ptr;
    std::shared_ptr<Tenc>     image_encoder_ptr = camera_.image_encoder_ptr;

    camera_img_sub_ = cmw_.AddReader<holo::uint64_t>(topic + std::string("_info"));
    camera_img_sub_.SetOnDataAvailableCallback(std::bind(&CameraCalibrationEncoder<Tenc>::inputImageCallback, this,
                                                         camera_name, ipc_ptr, image_encoder_ptr,
                                                         std::placeholders::_1));
    std::function<void(const ImagePacket&)> h1 =
        std::bind(&CameraCalibrationEncoder<Tenc>::imageEncoderHandler, this, std::placeholders::_1);
    image_encoder_ptr->SetSender(h1);

    pub_encoded_ = cmw_.AddWriter<uint8_t*>(camera_.topic + std::string("_calibration_encoder"));
    /* loop */
    cmw_wrapper::BusType::AsyncSpin(1);
    while (cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

template <typename Tenc>
void CameraCalibrationEncoder<Tenc>::inputImageCallback(std::string const&               camera_name,
                                                        std::shared_ptr<ImageIpc> const& ipc,
                                                        std::shared_ptr<Tenc> encode, uint64_t msg)
{
    (void)msg;
    if (!ipc)
    {
        LOG(INFO) << "CameraCalibrationEncoder<Tenc>::inputImageCallback ----"
                  << " Don't have " << camera_name << " image_ipc";
        return;
    }

    Image img;
    if (!ipc->GetImageData(img))
    {
        LOG(WARNING) << "CameraCalibrationEncoder --- failed to get image from ipc!!!";
        std::cout << "CameraCalibrationEncoder --- failed to get image from ipc!!!" << std::endl;
        return;
    }

    (void)encode->Encode(img);
}

template <typename Tenc>
void CameraCalibrationEncoder<Tenc>::imageEncoderHandler(const ImagePacket& encoded_image)
{
    holo::serialization::Serializer<false, 4> serializer(output_.get(), IMAGE_ENCODE_SIZE_MAX);
    if (encoded_image.Serialize(serializer))
    {
        pub_encoded_.Write(serializer.GetData(), serializer.GetSize());
        LOG(INFO) << "encoded = " << serializer.GetSize();
    }
}

template <typename Tenc>
CameraCalibrationEncoder<Tenc>::CameraCalibrationEncoder(holo::int32_t argc, char** argv,
                                                         const std::string& config_file, const uint32_t id,
                                                         const std::string& ns)
  : output_{new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>()}, cmw_(id, ns)
{
    (void)argc;
    (void)argv;
    setUp(config_file);
}

template class CameraCalibrationEncoder<H264Encoder>;
template class CameraCalibrationEncoder<Nv12ToH264Encoder>;

}  // namespace cmw_wrapper

void signalHandler(int sig)
{
    HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
    raise(sig);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t main(holo::int32_t argc, char** argv)
{
    // set options
    cxxopts::Options options("CameraCalibrationEncoder", "CameraCalibrationEncoder node");
    // clang-format off
    options.add_options()
    ("h,help", "help message")
    ("c,config_file", "Configuration file path", cxxopts::value<std::string>()->default_value(""))
    ("v,verbose", "if also outputs glog to console")
    ("d,domain_id", "cmw domain id", cxxopts::value<holo::uint32_t>())
    ("n,namespace", "cmw namespace",cxxopts::value<std::string>()->default_value("CameraCalibrationEncoder"))
    ("l,log_to_console", "if also outputs glog to console", cxxopts::value<uint8_t>(), "0")
    ("m,min_log_level", "minimum log level, ALL/TRACE/0, DEBUG/1, INFO/2, WARNING/3, ERROR/4, FATAL/5, OFF/6",cxxopts::value<holo::uint8_t>()->default_value("1"))
    ("t,threads", "threads number used to process callback",cxxopts::value<holo::uint16_t>()->default_value("5"));

    options.parse(argc, argv);

    if (options.count("help"))
    {
        LOG(INFO) << options.help();
        return 0;
    }

    // set google logging
    std::string log_file_name =
        holo::GetLogFileAbsolutePath("holo_calibration_cmw_app/CameraCalibrationDataCollectionCmw.log");
    uint32_t log_level = options["min_log_level"].as<holo::uint8_t>() * 10000U;
    (void)log_level;
    holo::log::SingleFileConfigure log_file("log_file", log_file_name);
    log_file.SetOpenMode(std::ios_base::out);
    holo::log::HoloLogger::Add(log_file);
    log_file.SetLevel(LogLevel::INFO);

    signal(SIGSEGV, signalHandler);
    signal(SIGINT, signalHandler);

    // initialize cmw wrapper and set signal handlers to process 'Ctrl+C'
    cmw_wrapper::BusType::Initialize(argc, argv, options["namespace"].as<std::string>());
    signal(SIGINT, cmw_wrapper::BusType::SignalHandler);

    // set camera calibration data acquisition app
    std::string      config_file = options["config_file"].as<std::string>();
    holo::yaml::Node node        = holo::yaml::LoadFile(config_file);
    std::string      encode_type = node["encode_type"].as<std::string>();
    LOG(INFO) << "encode_type = " << encode_type;

#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
    if (encode_type == "h264")
    {
        cmw_wrapper::CameraCalibrationEncoder<holo::sensors::camera::Nv12ToH264Encoder> app(
            argc, argv, options["config_file"].as<std::string>(), options["domain_id"].as<holo::uint32_t>(),
            options["namespace"].as<std::string>());
    }
#else
    if (encode_type == "h264")
    {
        cmw_wrapper::CameraCalibrationEncoder<holo::sensors::camera::H264Encoder> app(
            argc, argv, options["config_file"].as<std::string>(), options["domain_id"].as<holo::uint32_t>(),
            options["namespace"].as<std::string>());
    }
#endif
    else
    {
        std::string info("unknown encode mode");
        LOG(ERROR) << info;
        throw std::invalid_argument(info);
    }

    holo::log::HoloLogger::Shutdown();

    return 0;
}
