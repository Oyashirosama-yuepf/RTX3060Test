/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image capture APP.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-12.
 */

#include <camera/general/image_capture_app.h>
#include <holo/log/hololog.h>
#include <csignal>

namespace holo_cmw
{
void ImageCaptureAppBase::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        topic_name_           = node["topic_name"].as<std::string>();
        sensor_id_            = node["sensor_id"].as<uint32_t>();
        cols_                 = node["cols"].as<uint32_t>();
        rows_                 = node["rows"].as<uint32_t>();
        fps_                  = node["fps"].as<uint32_t>();
        trigger_mode_         = node["trigger_mode"].as<bool>();
        show_image_           = node["show_image"].as<bool>();
        use_ipc_              = node["use_ipc"].as<bool>("true");
    }
    catch (std::exception& e)
    {
        std::string info = "failed to load parameters";
        LOG(ERROR) << info << ":" << e.what();
        throw std::runtime_error(info);
    }
}

bool_t ImageCaptureAppBase::GetOutputVideoSize(const std::string& output_video_size, uint32_t& output_video_cols, uint32_t& output_video_rows)
{
    if (std::string("") == output_video_size)
    {
        output_video_cols = cols_;
        output_video_rows = rows_;

        return true;
    }

    try
    {
         std::string sub_str;

        for(size_t i = 0; i < output_video_size.length(); ++i)
        {
            if('x' == output_video_size[i])
            {
                if(!sub_str.empty())
                {
                    output_video_cols = std::stoi(sub_str);
                    sub_str.clear();
                }
            }
            else
            {
                sub_str.push_back(output_video_size[i]);
            }
        }
    
        if(!sub_str.empty())
        {
            output_video_rows = std::stoi(sub_str);
        }
    }
    catch(...)
    {
        return false;
    }

    return true;
}

template <typename T>
void ImageCaptureSyncBaseT<T>::TimeSyncHandler(std::shared_ptr<ImageTimestamperT<T>> driver, const T& data)
{
    driver->SetSyncInfo(data);
}

template class ImageCaptureSyncBaseT<HoloSyncPacket>;
template class ImageCaptureSyncBaseT<HoloSyncDiffPacket>;

template <typename Tcam>
void ImageCaptureRawApp<Tcam>::Setup(const std::string& config_file, const std::string& save_image, const std::string& output_video_size, bool_t blocking_mode)
{
    (void)save_image;
    (void)output_video_size;
    /* load params */
    ImageCaptureAppBase::GetParameters(config_file);
    /* cmw */
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    pub_raw_ = bus0_->AddWriter<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>>(topic_name_ +
                                                                                          std::string("_raw_image"));
#else
    pub_raw_     = bus0_->AddWriter<uint8_t*>(topic_name_ + std::string("_raw_image"));
#endif
    driver_ =
        std::make_shared<ImageCaptureRaw<ImageType::RAW_YUYV>>(SensorId(sensor_id_), cols_, rows_, fps_, trigger_mode_);
    std::function<void(const ImagePacket&)> h0 =
        std::bind(&ImageCaptureRawApp<Tcam>::ImageRawHandler, this, std::placeholders::_1);
    driver_->SetRawCallback(h0);

    holo::yaml::Node node1 = holo::yaml::LoadFile(config_file);
    data_interface_        = std::make_shared<V4l2Interface<Tcam>>(node1);
    std::function<void(const StreamBuffer&)> h1 =
        std::bind(&ImageCaptureRaw<ImageType::RAW_YUYV>::ParseData, driver_.get(), std::placeholders::_1);
    data_interface_->InstallCallback(h1);

    holo::os::Sleep(0.5f);

#if defined(APP_MAIN_FUNCTION)
    holo::yaml::Node node2 = holo::yaml::LoadFile(config_file)["sync"];
    sync_interface_        = std::make_shared<UdpInterface<HoloSyncPacket>>(node2);
    std::function<void(const HoloSyncPacket&)> h2 =
        std::bind(&ImageCaptureSyncBaseT<HoloSyncPacket>::TimeSyncHandler, this, driver_, std::placeholders::_1);
    sync_interface_->InstallCallback(h2);

    /* loop */
    cmw_wrapper::BusType::AsyncSpin(1);
#endif
    thread_ = std::make_shared<std::thread>(&ImageCaptureRawApp<Tcam>::BackgroundImageCapBase, this);
    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

template <typename Tcam>
void ImageCaptureRawApp<Tcam>::SetTimeSyncData(const HoloSyncPacket& data)
{
    driver_->SetSyncInfo(data);
}

template <typename Tcam>
void ImageCaptureRawApp<Tcam>::ImageRawHandler(const ImagePacket& raw_image)
{
    holo::serialization::Serializer<false, 4> serializer(output_.get(), IMAGE_RAW_SIZE_MAX);
    if (raw_image.Serialize(serializer))
    {
        frames_++;
        pub_raw_.Write(serializer.GetData(), serializer.GetSize());
    }
}

template <typename Tcvt, typename Tenc>
void ImageCaptureMdc610App<Tcvt, Tenc>::Setup(const std::string& config_file, const std::string& save_image, const std::string& output_video_size, bool_t blocking_mode)
{
    /* load params */
    ImageCaptureAppBase::GetParameters(config_file);
    /* cmw */
    // pub_counter_ = bus0_.AddWriter<uint32_t>(topic_name_ + std::string("_counter"));

    uint32_t output_video_cols = cols_;
    uint32_t output_video_rows = rows_;
    bool_t result = GetOutputVideoSize(output_video_size, output_video_cols, output_video_rows);

    if (result)
    {
        LOG(INFO) << "Set Output Video Size Success. Output Video Size: " << output_video_cols << "x" << output_video_rows;
    }
    else
    {
        output_video_cols = cols_;
        output_video_rows = rows_;
        LOG(INFO) << "Set Output Video Size Faile. Output Video Size: " << output_video_cols << "x" << output_video_rows;
    }
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    pub_info_ = bus0_->AddWriter<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>(topic_name_ + std::string("_info"));
    pub_encoded_ = bus0_->AddWriter<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>>(topic_name_ +
                                                                                              std::string("_encoder"));
#else
    pub_info_    = bus0_->AddWriter<uint64_t>(topic_name_ + std::string("_info"));
    pub_encoded_ = bus0_->AddWriter<uint8_t*>(topic_name_ + std::string("_encoder"));
#endif

    /* nv12 driver */
    nv12_driver_ =
        std::make_shared<ImageCaptureBasic<Tcvt, Tenc>>(SensorId(sensor_id_), cols_, rows_, fps_, show_image_);
    if (use_ipc_)
    {
        ipc_ = std::make_shared<ImageIpc>(SensorId(sensor_id_), rows_, cols_, holo::Image::Encoding::NV12);
    }
    nv12_driver_->SetOutputVideoSize(output_video_cols, output_video_rows);

    SaveType save_type;

    if (std::string("all") == save_image)
    {
        save_type = SaveType::SAVE_ALL;
    }
    else if (std::string("new") == save_image)
    {
        save_type = SaveType::SAVE_NEW;
    }
    else
    {
        save_type = SaveType::DONT_SAVE;
    }

    std::function<void(const holo::Image&)> h =
            std::bind(&ImageCaptureMdc610App<Tcvt, Tenc>::ImageNV12DataHandler, this, std::placeholders::_1, save_type);
    nv12_driver_->SetImageCallback(h);

    /* h265 driver */
    h265_driver_ = std::make_shared<ImageCaptureEncoded<>>(sensor_id_, cols_, rows_, fps_,
                                                           holo::sensors::camera::ImageType::H265, show_image_);
    std::function<void(const ImagePacket&)> h2 =
        std::bind(&ImageCaptureMdc610App<Tcvt, Tenc>::ImageH265EncoderHandler, this, std::placeholders::_1);
    h265_driver_->SetSender(h2);
    /* loop */
#if defined(APP_MAIN_FUNCTION)
    cmw_wrapper::BusType::AsyncSpin(1);
#endif
    thread_ = std::make_shared<std::thread>(&ImageCaptureMdc610App<Tcvt, Tenc>::Background, this, config_file);
    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

template <typename Tcvt, typename Tenc>
void ImageCaptureMdc610App<Tcvt, Tenc>::Background(const std::string& config_file)
{
    /* fetch image data */
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
    Mdc610CameraInterfaceParam nv12_param;
    std::string                encode_type;
    holo::yaml::Node           node;
    try
    {
        node                               = holo::yaml::LoadFile(config_file);
        nv12_param.instance                = node["device_name"].as<int32_t>();
        nv12_param.use_datalayer_timestamp = node["use_datalayer_timestamp"].as<holo::bool_t>("true");
        encode_type                        = node["encode_type"].as<std::string>("");

        if (nv12_param.instance >= MIN_H265_CHANNEL_ID && nv12_param.instance <= MAX_H265_CHANNEL_ID)
        {
            nv12_param.instance -= 50u;
        }
        if (nv12_param.instance < MIN_NV12_CHANNEL_ID || nv12_param.instance > MAX_NV12_CHANNEL_ID)
        {
            LOG(ERROR) << "device_name's value is between 21 and 34";
            return;
        }
        LOG(INFO) << "nv12 instance                = " << nv12_param.instance;
        LOG(INFO) << "nv12 use_datalayer_timestamp = " << nv12_param.use_datalayer_timestamp;
        LOG(INFO) << "encode_type                  = " << encode_type;
    }
    catch (std::exception& e)
    {
        std::string info = "failed to load camera instance";
        LOG(ERROR) << info << ":" << e.what();
        throw std::runtime_error(info);
    }

    std::function<void(const StreamBuffer&, const Timestamp&, const Timestamp&)> h3 =
        std::bind(&ImageCaptureBasic<Tcvt, Tenc>::ParseData, nv12_driver_.get(), std::placeholders::_1,
                  std::placeholders::_2, std::placeholders::_3);
    std::shared_ptr<Mdc610CameraInterface<holo_cmw::decodedProxy>> nv12_interface =
        std::make_shared<Mdc610CameraInterface<holo_cmw::decodedProxy>>(nv12_param);
    nv12_interface->InstallCallback(h3);

    std::shared_ptr<Mdc610CameraInterface<holo_cmw::encodedProxy>> h265_interface = nullptr;
    if (encode_type == "h265")
    {
        Mdc610CameraInterfaceParam h265_param;
        h265_param.instance                = nv12_param.instance + 50u;
        h265_param.use_datalayer_timestamp = nv12_param.use_datalayer_timestamp;
        LOG(INFO) << "h265 instance                = " << h265_param.instance;
        LOG(INFO) << "h265 use_datalayer_timestamp = " << h265_param.use_datalayer_timestamp;
        std::function<void(const StreamBuffer&, const Timestamp&, const Timestamp&, const uint8_t&)> h4 =
            std::bind(&ImageCaptureEncoded<>::ParseData, h265_driver_.get(), std::placeholders::_1,
                      std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        h265_interface = std::make_shared<Mdc610CameraInterface<holo_cmw::encodedProxy>>(h265_param);
        h265_interface->InstallCallback(h4);
    }
#endif
    BackgroundImageCapBase();
}

template <typename Tcvt, typename Tenc>
void ImageCaptureMdc610App<Tcvt, Tenc>::ImageH265EncoderHandler(const ImagePacket& encoded_image)
{
    holo::serialization::Serializer<false, 4> serializer(output_.get(), IMAGE_ENCODE_SIZE_MAX);
    if (encoded_image.Serialize(serializer))
    {
        pub_encoded_.Write(serializer.GetData(), serializer.GetSize());
        LOG(INFO) << "sensor id = " << sensor_id_ << ", encoded = " << serializer.GetSize();
    }
}

template <typename Tcvt, typename Tenc>
void ImageCaptureMdc610App<Tcvt, Tenc>::ImageNV12DataHandler(const holo::Image& img, SaveType save_type)
{
    if (use_ipc_)
    {
        ipc_->SetImageData(img);
        uint64_t info = (static_cast<uint64_t>(sensor_id_) << 32) + counter_++;
        pub_info_.Write(info);
        LOG(INFO) << "sensor id = " << sensor_id_ << ", counter = " << counter_++;
    }

    if (SaveType::DONT_SAVE == save_type)
    {
        return;    
    }

    cv::Mat image;
    if (img.GetEncoding() == holo::Image::Encoding::NV12)
    {
        cv::cvtColor(holo::sensors::camera::Image2Mat(img), image, CV_YUV2BGR_NV12);
    }
    else if (img.GetEncoding() == holo::Image::Encoding::RGB)
    {
        cv::cvtColor(holo::sensors::camera::Image2Mat(img), image, CV_RGB2BGR);
    }
    else if (img.GetEncoding() == holo::Image::Encoding::BGR)
    {
        image = holo::sensors::camera::Image2Mat(img);
    }
    else
    {
        return;
    }
    std::string name = std::to_string(static_cast<uint32_t>(sensor_id_));
    if (SaveType::SAVE_ALL == save_type)
    {
        name += "." + std::to_string(img.GetTimestamp().ToSec());
    }
    name += ".jpg";
    cv::imwrite(name.c_str(), image);
}

template <typename Tcam, typename Tcvt, typename Tenc, typename Tsync>
void ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync>::Setup(const std::string& config_file, const std::string& save_image, const std::string& output_video_size, bool_t blocking_mode)
{
    /* load params */
    ImageCaptureAppBase::GetParameters(config_file);

    uint32_t output_video_cols = cols_;
    uint32_t output_video_rows = rows_;
    bool_t result = GetOutputVideoSize(output_video_size, output_video_cols, output_video_rows);

    if (result)
    {
        LOG(INFO) << "Set Output Video Size Success. Output Video Size: " << output_video_cols << "x" << output_video_rows;
    }
    else
    {
        output_video_cols = cols_;
        output_video_rows = rows_;
        LOG(INFO) << "Set Output Video Size Faile. Output Video Size: " << output_video_cols << "x" << output_video_rows;
    }

    /* cmw */
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    pub_info_ = bus0_->AddWriter<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>(topic_name_ + std::string("_info"));
    pub_encoded_ = bus0_->AddWriter<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>>(topic_name_ +
                                                                                              std::string("_encoder"));
#elif defined(CMW_WRAPPER_ENABLE_ROS)
    pub_info_    = bus0_->AddWriter<uint64_t>(topic_name_ + std::string("_info"));
    pub_encoded_ = bus0_->AddWriter<ImagePacket, ros_wrapper::DefaultConversionTraits<ImagePacket>>(
        topic_name_ + std::string("_encoder"));
#else
    pub_info_    = bus0_->AddWriter<uint64_t>(topic_name_ + std::string("_info"));
    pub_encoded_ = bus0_->AddWriter<uint8_t*>(topic_name_ + std::string("_encoder"));
#endif
    /* driver */
    driver_ = std::make_shared<ImageCaptureRgbT<Tcvt, Tenc, Tsync>>(SensorId(sensor_id_), cols_, rows_, fps_,
                                                                    trigger_mode_, show_image_);
    if (use_ipc_)
    {
        ipc_ = std::make_shared<ImageIpc>(SensorId(sensor_id_), rows_, cols_, holo::Image::Encoding::RGB);
    }
    driver_->SetOutputVideoSize(output_video_cols, output_video_rows);

    SaveType save_type;
    if (std::string("all") == save_image)
    {
        save_type = SaveType::SAVE_ALL;
    }
    else if (std::string("new") == save_image)
    {
        save_type = SaveType::SAVE_NEW;
    }
    else
    {
        save_type = SaveType::DONT_SAVE;
    }

    std::function<void(const holo::Image&)> h =
            std::bind(&ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync>::ImageDataHandler, this, std::placeholders::_1, save_type);
    driver_->SetImageCallback(h);

    std::function<void(const ImagePacket&)> h1 =
        std::bind(&ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync>::ImageEncoderHandler, this, std::placeholders::_1);
    driver_->SetSender(h1);

    holo::yaml::Node node1                                        = holo::yaml::LoadFile(config_file);
    data_interface_                                               = std::make_shared<V4l2Interface<Tcam>>(node1);
    std::function<void(const StreamBuffer&, const Timestamp&)> h5 = std::bind(
        &ImageCaptureRgbT<Tcvt, Tenc, Tsync>::ParseData, driver_.get(), std::placeholders::_1, std::placeholders::_2);
    data_interface_->InstallCallback(h5);

    holo::os::Sleep(0.5f);

#if defined(APP_MAIN_FUNCTION)
    holo::yaml::Node node2 = holo::yaml::LoadFile(config_file)["sync"];
    sync_interface_        = std::make_shared<UdpInterface<Tsync>>(node2);
    std::function<void(const Tsync&)> h2 =
        std::bind(&ImageCaptureSyncBaseT<Tsync>::TimeSyncHandler, this, driver_, std::placeholders::_1);
    sync_interface_->InstallCallback(h2);

    /* loop */
    cmw_wrapper::BusType::AsyncSpin(1);
#endif
    thread_ = std::make_shared<std::thread>(&ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync>::BackgroundImageCapBase, this);
    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

template <typename Tcam, typename Tcvt, typename Tenc, typename Tsync>
void ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync>::SetTimeSyncData(const Tsync& data)
{
    driver_->SetSyncInfo(data);
}

template <typename Tcam, typename Tcvt, typename Tenc, typename Tsync>
void ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync>::ImageDataHandler(const holo::Image& img, SaveType save_type)
{
    if (use_ipc_)
    {
        ipc_->SetImageData(img);
        uint64_t info = (static_cast<uint64_t>(sensor_id_) << 32) + counter_++;
        pub_info_.Write(info);
        LOG(INFO) << "sensor id = " << sensor_id_ << ", counter = " << counter_++;
    }

    if (SaveType::DONT_SAVE == save_type)
    {
        return;    
    }

    cv::Mat image;
    cv::cvtColor(holo::sensors::camera::Image2Mat(img), image, CV_RGB2BGR);
    std::string name = std::to_string(static_cast<uint32_t>(sensor_id_));
    if (SaveType::SAVE_ALL == save_type)
    {
        name += "." + std::to_string(img.GetTimestamp().ToSec());
    }
    name += ".jpg";
    cv::imwrite(name.c_str(), image);
}

template <typename Tcam, typename Tcvt, typename Tenc, typename Tsync>
void ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync>::ImageEncoderHandler(const ImagePacket& encoded_image)
{
#if defined(CMW_WRAPPER_ENABLE_ROS)
    if (encoded_image.size > 0)
    {
        pub_encoded_.Write(encoded_image);
        LOG(INFO) << "sensor id = " << sensor_id_ << ", encoded = " << encoded_image.size + 40u;
    }
#else
    holo::serialization::Serializer<false, 4> serializer(output_.get(), IMAGE_ENCODE_SIZE_MAX);
    if (encoded_image.Serialize(serializer))
    {
        pub_encoded_.Write(serializer.GetData(), serializer.GetSize());
        LOG(INFO) << "sensor id = " << sensor_id_ << ", encoded = " << serializer.GetSize();
    }
#endif
}

template <typename Tdec>
void ImageCaptureEncodedApp<Tdec>::Setup(const std::string& config_file, const std::string& save_image, const std::string& output_video_size, bool_t blocking_mode)
{
    /* load params */
    ImageCaptureAppBase::GetParameters(config_file);

    uint32_t output_video_cols = cols_;
    uint32_t output_video_rows = rows_;
    bool_t result = GetOutputVideoSize(output_video_size, output_video_cols, output_video_rows);

    if (result)
    {
        LOG(INFO) << "Set Output Video Size Success. Output Video Size: " << output_video_cols << "x" << output_video_rows;
    }
    else
    {
        output_video_cols = cols_;
        output_video_rows = rows_;
        LOG(INFO) << "Set Output Video Size Faile. Output Video Size: " << output_video_cols << "x" << output_video_rows;
    }

    /* cmw */
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    pub_info_ = bus0_->AddWriter<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>(topic_name_ + std::string("_info"));
    pub_encoded_ = bus0_->AddWriter<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>>(topic_name_ +
                                                                                              std::string("_encoder"));
#else
    pub_info_    = bus0_->AddWriter<uint64_t>(topic_name_ + std::string("_info"));
    pub_encoded_ = bus0_->AddWriter<uint8_t*>(topic_name_ + std::string("_encoder"));
#endif
    driver_ = std::make_shared<ImageCaptureEncoded<Tdec>>(SensorId(sensor_id_), cols_, rows_, fps_,
                                                          holo::sensors::camera::ImageType::H265, show_image_);
    if (use_ipc_)
    {
        ipc_ = std::make_shared<ImageIpc>(SensorId(sensor_id_), rows_, cols_, Tdec::GetOutputType());
    }
    driver_->SetOutputVideoSize(output_video_cols, output_video_rows);
    SaveType save_type;
    if (std::string("all") == save_image)
    {
        save_type = SaveType::SAVE_ALL;
    }
    else if (std::string("new") == save_image)
    {
        save_type = SaveType::SAVE_NEW;
    }
    else
    {
        save_type = SaveType::DONT_SAVE;
    }

    std::function<void(const holo::Image&)> h = std::bind(&ImageCaptureEncodedApp<Tdec>::ImageDataHandler, this,
                                                              std::placeholders::_1, save_type);
    driver_->SetImageCallback(h);

    std::function<void(const ImagePacket&)> h1 =
        std::bind(&ImageCaptureEncodedApp::ImageEncoderHandler, this, std::placeholders::_1);
    driver_->SetSender(h1);

    /* fetch image data */
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
    Mdc610CameraInterfaceParam param;
    std::string                encode_type;
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        param.instance        = node["device_name"].as<int32_t>();
        encode_type           = node["encode_type"].as<std::string>();
        if (param.instance >= MIN_NV12_CHANNEL_ID && param.instance <= MAX_NV12_CHANNEL_ID)
        {
            param.instance += 50u;
        }
        if (param.instance < MIN_H265_CHANNEL_ID || param.instance > MAX_H265_CHANNEL_ID)
        {
            std::string error = "device_name value is between 71 and 84";
            LOG(INFO) << error << ": " << strerror(errno);
            throw std::runtime_error(error);
        }
        LOG(INFO) << "camera instance = " << param.instance;
    }
    catch (std::exception& e)
    {
        std::string info = "failed to load camera instance";
        LOG(ERROR) << info << ":" << e.what();
        throw std::runtime_error(info);
    }
    std::function<void(const ImagePacket& packet)> h2 =
        std::bind(&ImageCaptureEncoded<Tdec>::Decode, driver_.get(), std::placeholders::_1);
    interface_ = std::make_shared<Mdc610CameraInterface<holo_cmw::encodedProxy>>(param);
    interface_->InstallCallback(h2);
    // Forward data encoded data from sensor
    if (encode_type == "h265" || encode_type == "h264")
    {
        std::function<void(const StreamBuffer&, const Timestamp&, const Timestamp&, const uint8_t&)> h3 =
            std::bind(&ImageCaptureEncoded<Tdec>::ParseData, driver_.get(), std::placeholders::_1,
                      std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        interface_->InstallCallback(h3);
    }
#endif
    /* loop */
#if defined(APP_MAIN_FUNCTION)
    cmw_wrapper::BusType::AsyncSpin(1);
#endif
    thread_ = std::make_shared<std::thread>(&ImageCaptureEncodedApp<Tdec>::BackgroundImageCapBase, this);
    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

template <typename Tdec>
void ImageCaptureEncodedApp<Tdec>::ImageEncoderHandler(const ImagePacket& encoded_image)
{
    holo::serialization::Serializer<false, 4> serializer(output_.get(), IMAGE_ENCODE_SIZE_MAX);
    if (encoded_image.Serialize(serializer))
    {
        frames_++;
        pub_encoded_.Write(serializer.GetData(), serializer.GetSize());
        LOG(INFO) << "sensor id = " << sensor_id_ << ", encoded = " << serializer.GetSize();
    }
}

template <typename Tdec>
void ImageCaptureEncodedApp<Tdec>::ImageDataHandler(const holo::Image& img, SaveType save_type)
{
    if (use_ipc_)
    {
        ipc_->SetImageData(img);
        uint64_t info = (static_cast<uint64_t>(sensor_id_) << 32) + counter_++;
        pub_info_.Write(info);
        LOG(INFO) << "sensor id = " << sensor_id_ << ", counter = " << counter_++;
    }

    if (SaveType::DONT_SAVE == save_type)
    {
        return;    
    }

    cv::Mat image;
    if (img.GetEncoding() == holo::Image::Encoding::NV12)
    {
        cv::cvtColor(holo::sensors::camera::Image2Mat(img), image, CV_YUV2BGR_NV12);
    }
    else if (img.GetEncoding() == holo::Image::Encoding::RGB)
    {
        cv::cvtColor(holo::sensors::camera::Image2Mat(img), image, CV_RGB2BGR);
    }
    else if (img.GetEncoding() == holo::Image::Encoding::BGR)
    {
        image = holo::sensors::camera::Image2Mat(img);
    }
    else
    {
        return;
    }
    std::string name = std::to_string(static_cast<uint32_t>(sensor_id_));
    if (SaveType::SAVE_ALL == save_type)
    {
        name += "." + std::to_string(img.GetTimestamp().ToSec());
    }
    name += ".jpg";
    cv::imwrite(name.c_str(), image);
}

template class ImageCaptureEncodedApp<holo::sensors::camera::H264ToRGBDecoder>;
template class ImageCaptureEncodedApp<holo::sensors::camera::H265ToRGBDecoder>;

template class ImageCaptureEncodedApp<holo::sensors::camera::H264ToBGRDecoder>;
template class ImageCaptureEncodedApp<holo::sensors::camera::H265ToBGRDecoder>;

template class ImageCaptureEncodedApp<holo::sensors::camera::H264ToNv12Decoder>;
template class ImageCaptureEncodedApp<holo::sensors::camera::H265ToNv12Decoder>;

template <typename Tcvt, typename Tenc> 
void ImageCaptureVirtAppT<Tcvt, Tenc>::Setup(const std::string& config_file, const std::string& save_image, const std::string& output_video_size, bool_t blocking_mode)
{
    (void)blocking_mode;
    (void)save_image;
    (void)output_video_size;
    /* load params */
    ImageCaptureAppBase::GetParameters(config_file);
    /* cmw */
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    pub_info_ = bus0_->AddWriter<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>(topic_name_ + std::string("_info"));
    pub_encoded_ = bus0_->AddWriter<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>>(topic_name_ +
                                                                                              std::string("_encoder"));
#else
    pub_info_    = bus0_->AddWriter<uint64_t>(topic_name_ + std::string("_info"));
    pub_encoded_ = bus0_->AddWriter<uint8_t*>(topic_name_ + std::string("_encoder"));
#endif
    /* driver */
    driver_ = std::make_shared<ImageCaptureVirtual<Tcvt, Tenc>>(SensorId(sensor_id_), cols_, rows_, fps_, show_image_);
    holo::yaml::Node node1 = holo::yaml::LoadFile(config_file);
    data_interface_        = std::make_shared<VirtCamInterface>(node1);
    std::function<void(const StreamBuffer&, const Timestamp&, const Timestamp&)> h5 =
        std::bind(&ImageCaptureVirtual<Tcvt, Tenc>::ParseData, driver_.get(), std::placeholders::_1,
                  std::placeholders::_2, std::placeholders::_3);
    data_interface_->InstallCallback(h5);
    holo::os::Sleep(0.5f);
#if defined(APP_MAIN_FUNCTION)
    cmw_wrapper::BusType::AsyncSpin(1);
#endif
    /* loop */
    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}
template <typename Tcvt, typename Tenc>
void ImageCaptureVirtAppT<Tcvt, Tenc>::ImageCounterHandler(uint32_t counter)
{
    // pub_counter_.Write(counter);
    uint64_t info = (static_cast<uint64_t>(sensor_id_) << 32) + counter;
    pub_info_.Write(info);
    LOG(INFO) << "sensor id = " << sensor_id_ << ", counter = " << counter;
}

template class ImageCaptureRgbAppT<CameraM021, Bayer8Converter, H264Encoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbAppT<CameraAP020, YuyvConverter, H264Encoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbAppT<CameraAR0231, YuyvConverter, H264Encoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbAppT<CameraOV490, YuyvConverter, H264Encoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbAppT<CameraV4l2General, YuyvConverter, H264Encoder, HoloSyncDiffPacket>;
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
template class ImageCaptureMdc610App<RawToNv12Converter, DummyEncoder>;
#endif
template class ImageCaptureRgbAppT<CameraM021, Bayer8Converter, DummyEncoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbAppT<CameraAP020, YuyvConverter, DummyEncoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbAppT<CameraAR0231, YuyvConverter, DummyEncoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbAppT<CameraOV490, YuyvConverter, DummyEncoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbAppT<CameraV4l2General, YuyvConverter, DummyEncoder, HoloSyncDiffPacket>;

}  // namespace holo_cmw

#if defined(APP_MAIN_FUNCTION)
static void signalSegHandler(int sig)
{
    cmw_wrapper::BusType::SignalHandler(sig);
    holo::log::HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
}

int main(int argc, char** argv)
{
    cxxopts::Options options("ImageCapture", "ImageCapture node");
    // clang-format off
    options.add_options()
        ("h,help", "help message")
        ("c,config_file", "Configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "Node name for this app", cxxopts::value<std::string>()->default_value("ImageCapture"))
        ("s,save_image", "Save image mode: new, all", cxxopts::value<std::string>()->default_value(""))
        ("m,min_log_level", "minimum log level, ALL/TRACE/0, D/1, I/2, W/3, E/4, F/5, OFF/6", cxxopts::value<holo::uint8_t>()->default_value("0"))
        ("d,domain_id", "domain id", cxxopts::value<uint32_t>()->default_value("0"))
        ("output_video_size", "IPC And SaveImage Video Size: ${cols}x${rows}", cxxopts::value<std::string>()->default_value(""))
        ;
    // clang-format on
    options.parse(argc, argv);

    if (options.count("help"))
    {
        LOG(INFO) << options.help();
        return 0;
    }

    uint32_t    domain_id = options["domain_id"].as<uint32_t>();
    std::string node_name = options["node_name"].as<std::string>();
    holo::CreateHoloLogSubdirectory("holo_sensors");
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/image_capture_" + node_name + ".log");
    uint32_t    log_level     = options["min_log_level"].as<holo::uint8_t>();
    log_level                 = std::min<uint32_t>(log_level, 6);
    log_level                 = ((log_level * 10000 + 9999) / 10000) * 10000;

    holo::log::RollingFileConfigure log_file("log_file", log_file_name);
    holo::log::HoloLogger::Add(log_file);
    holo::log::HoloLogger::SetLogLevel(static_cast<holo::log::LogLevel>(log_level));
    holo::log::HoloLogger::SetLogLevel(holo::log::ConsoleConfigure::DEFAULT_CONSOLE_CONFIG_NAME,
                                       options.count("verbose") ? (static_cast<holo::log::LogLevel>(log_level)) :
                                                                  (holo::log::LogLevel::OFF));

    signal(SIGSEGV, signalSegHandler);
    signal(SIGINT, cmw_wrapper::BusType::SignalHandler);

#if defined(HOLO_PLATFORM_MDC610)
#if (MDC610_VERSION_NUM == 20210430)
    Adsfi::AdsfiLogger::GetInstance().InitLogging(std::string("image_capture_") + node_name, std::string("desc"), 4, 6,
                                                  std::string("./log/holo_sensors/"));
    Adsfi::AdsfiLogger::GetInstance().CreateLogger(std::string("image_capture_") + node_name, std::string("desc"), 4);
#else
    Adsfi::AdsfiLogger::GetInstance().InitLogging(
        std::string("image_capture_") + node_name, std::string("desc"), static_cast<Adsfi::HafLogLevelType>(4),
        static_cast<Adsfi::HafLogModeType>(6), std::string("./log/holo_sensors/"));
    Adsfi::AdsfiLogger::GetInstance().CreateLogger(std::string("image_capture_") + node_name, std::string("desc"),
                                                   static_cast<Adsfi::HafLogLevelType>(4));
#endif
#endif

    cmw_wrapper::BusType::Initialize(argc, argv, node_name);

    std::string      config_file = options["config_file"].as<std::string>();
    holo::yaml::Node node        = holo::yaml::LoadFile(config_file);
    std::string      model       = node["model"].as<std::string>();
    std::string      encode_type = node["encode_type"].as<std::string>();
    LOG(INFO) << "model       = " << model;
    LOG(INFO) << "encode_type = " << encode_type;

    /*
     * model                    Tcam                Tcvt        raw
     * CAMERA_LEOPARD_M021      CameraM021          bayer8      no
     * CAMERA_LEOPARD_AP020     CameraAP020         yuyv        yes
     * CAMERA_LEOPARD_AR0231    CameraAR0231        yuyv        yes
     * CAMERA_LEOPARD_OV490     CameraOV490         yuyv        yes
     * CAMERA_ENTRON_F001R      CameraV4l2General   yuyv        yes
     * CAMERA_ENTRON_S001R      CameraV4l2General   yuyv        yes
     */
    try
    {
        if (encode_type == "raw")
        {
            if (model == "CAMERA_LEOPARD_M021")
            {
                std::string info("cannot pub raw data of leopard m021");
                LOG(ERROR) << info;
                throw std::invalid_argument(info);
            }
            else if (model == "CAMERA_LEOPARD_AP020")
            {
                using Tcam = holo_cmw::CameraAP020;
                holo_cmw::ImageCaptureRawApp<Tcam> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_LEOPARD_AR0231")
            {
                using Tcam = holo_cmw::CameraAR0231;
                holo_cmw::ImageCaptureRawApp<Tcam> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_LEOPARD_OV490")
            {
                using Tcam = holo_cmw::CameraOV490;
                holo_cmw::ImageCaptureRawApp<Tcam> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_ENTRON_F001R")
            {
                using Tcam = holo_cmw::CameraV4l2General;
                holo_cmw::ImageCaptureRawApp<Tcam> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_ENTRON_S001R")
            {
                using Tcam = holo_cmw::CameraV4l2General;
                holo_cmw::ImageCaptureRawApp<Tcam> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else
            {
                std::string info("unknown camera model");
                LOG(ERROR) << info;
                throw std::invalid_argument(info);
            }
        }
        else if (encode_type == "h264")
        {
            using Tenc  = holo::sensors::camera::H264Encoder;
            using Tsync = holo::sensors::camera::HoloSyncDiffPacket;
            if (model == "CAMERA_LEOPARD_M021")
            {
                using Tcam = holo_cmw::CameraM021;
                using Tcvt = holo::sensors::camera::Bayer8Converter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_LEOPARD_AP020")
            {
                using Tcam = holo_cmw::CameraAP020;
                using Tcvt = holo::sensors::camera::YuyvConverter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_LEOPARD_AR0231")
            {
                using Tcam = holo_cmw::CameraAR0231;
                using Tcvt = holo::sensors::camera::YuyvConverter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_LEOPARD_OV490")
            {
                using Tcam = holo_cmw::CameraOV490;
                using Tcvt = holo::sensors::camera::YuyvConverter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_ENTRON_F001R")
            {
                using Tcam = holo_cmw::CameraV4l2General;
                using Tcvt = holo::sensors::camera::YuyvConverter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_ENTRON_S001R")
            {
                using Tcam = holo_cmw::CameraV4l2General;
                using Tcvt = holo::sensors::camera::YuyvConverter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_V4L2_GENERAL")
            {
                using Tcam = holo_cmw::CameraV4l2General;
                using Tcvt = holo::sensors::camera::YuyvConverter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_VIRTUAL")
            {
                using Tenc = holo::sensors::camera::DummyEncoder;
                using Tcvt = holo::sensors::camera::RawToNv12Converter;
                holo_cmw::ImageCaptureVirtAppT<Tcvt, Tenc> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else
            {
                std::string info("unknown camera model");
                LOG(ERROR) << info;
                throw std::invalid_argument(info);
            }
        }
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
        else if (encode_type == "h265")
        {
            if ((model == "CAMERA_MDC610_HONGJING_NV12") || (model == "CAMERA_MDC610"))
            {
                using Tenc = holo::sensors::camera::DummyEncoder;
                using Tcvt = holo::sensors::camera::RawToNv12Converter;
                holo_cmw::ImageCaptureMdc610App<Tcvt, Tenc> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_MDC610_UYVY")
            {
                using Tenc = holo::sensors::camera::DummyEncoder;
                using Tcvt = holo::sensors::camera::UyvyToNv12Converter;
                holo_cmw::ImageCaptureMdc610App<Tcvt, Tenc> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_MDC610_H265")
            {
                using Tdec = holo::sensors::camera::H265ToNv12Decoder;
                holo_cmw::ImageCaptureEncodedApp<Tdec> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
        }
#endif
        else
        {
            using Tenc  = holo::sensors::camera::DummyEncoder;
            using Tsync = holo::sensors::camera::HoloSyncDiffPacket;
            if (model == "CAMERA_LEOPARD_M021")
            {
                using Tcam = holo_cmw::CameraM021;
                using Tcvt = holo::sensors::camera::Bayer8Converter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_LEOPARD_AP020")
            {
                using Tcam = holo_cmw::CameraAP020;
                using Tcvt = holo::sensors::camera::YuyvConverter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_LEOPARD_AR0231")
            {
                using Tcam = holo_cmw::CameraAR0231;
                using Tcvt = holo::sensors::camera::YuyvConverter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_LEOPARD_OV490")
            {
                using Tcam = holo_cmw::CameraOV490;
                using Tcvt = holo::sensors::camera::YuyvConverter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_ENTRON_F001R")
            {
                using Tcam = holo_cmw::CameraV4l2General;
                using Tcvt = holo::sensors::camera::YuyvConverter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_ENTRON_S001R")
            {
                using Tcam = holo_cmw::CameraV4l2General;
                using Tcvt = holo::sensors::camera::YuyvConverter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_V4L2_GENERAL")
            {
                using Tcam = holo_cmw::CameraV4l2General;
                using Tcvt = holo::sensors::camera::YuyvConverter;
                holo_cmw::ImageCaptureRgbAppT<Tcam, Tcvt, Tenc, Tsync> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_VIRTUAL")
            {
                using Tcvt = holo::sensors::camera::RawToNv12Converter;
                holo_cmw::ImageCaptureVirtAppT<Tcvt, Tenc> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
            else if ((model == "CAMERA_MDC610_HONGJING_NV12") || (model == "CAMERA_MDC610"))
            {
                using Tcvt = holo::sensors::camera::RawToNv12Converter;
                holo_cmw::ImageCaptureMdc610App<Tcvt, Tenc> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_MDC610_UYVY")
            {
                using Tcvt = holo::sensors::camera::UyvyToNv12Converter;
                holo_cmw::ImageCaptureMdc610App<Tcvt, Tenc> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
            else if (model == "CAMERA_MDC610_H265")
            {
                using Tdec = holo::sensors::camera::H265ToNv12Decoder;
                holo_cmw::ImageCaptureEncodedApp<Tdec> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["output_video_size"].as<std::string>());
            }
#endif
            else
            {
                std::string info("unknown camera model");
                LOG(ERROR) << info;
                throw std::invalid_argument(info);
            }
        }
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "image capture application failed, exit";
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}
#endif
