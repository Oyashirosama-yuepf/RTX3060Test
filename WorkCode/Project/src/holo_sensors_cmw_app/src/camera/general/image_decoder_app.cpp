/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image decoder app.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-12.
 */

#include <camera/general/image_decoder_app.h>
#include <holo/log/hololog.h>
#include <csignal>

namespace holo_cmw
{
template <typename Tdec>
bool_t ImageDecoderAppT<Tdec>::GetOutputVideoSize(const std::string& output_video_size, uint32_t& output_video_cols, uint32_t& output_video_rows)
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

template <typename Tdec>
void ImageDecoderAppT<Tdec>::Setup(const std::string& config_file, const std::string& save_image,
                                   const std::string& save_encoded_data, const std::string& output_video_size)
{
    GetParameters(config_file);
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

    /* data & decoder */
    std::memset(decode_buffer_.get(), 0, IMAGE_ENCODE_SIZE_MAX);
    compress_data_.data = decode_buffer_.get();
    image_decoder_      = std::make_shared<Tdec>(sensor_id_, cols_, rows_, fps_, show_image_);
    if (use_ipc_)
    {
        ipc_ = std::make_shared<ImageIpc>(sensor_id_, rows_, cols_, Tdec::GetOutputType());
    }

    image_decoder_->SetOutputVideoSize(output_video_cols, output_video_rows);

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

    std::function<void(const holo::Image&)> h0 =
            std::bind(&ImageDecoderAppT<Tdec>::ImageDataHandler, this, std::placeholders::_1, save_type);
    image_decoder_->SetImageCallback(h0);
    /* cmw */
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    pub_info_ = bus0_.AddWriter<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>(topic_name_ + std::string("_info"));
#else
    pub_info_    = bus0_.AddWriter<uint64_t>(topic_name_ + std::string("_info"));
#endif

    save_encoded_data_type_ = SaveType::DONT_SAVE;

    if (std::string("all") == save_encoded_data)
    {
        save_encoded_data_type_ = SaveType::SAVE_ALL;
    }
    else if (std::string("new") == save_encoded_data)
    {
        save_encoded_data_type_ = SaveType::SAVE_NEW;
    }
    else if (std::string("file") == save_encoded_data)
    {
        save_encoded_data_type_ = SaveType::SAVE_FILE;
    }
    else
    {
        save_encoded_data_type_ = SaveType::DONT_SAVE;
    }

    std::function<void(const uint8_t*, size_t)> h2 =
        std::bind(&ImageDecoderAppT<Tdec>::ImageDecoderHandler, this, std::placeholders::_1, std::placeholders::_2);
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    sub_encoded_ = bus0_.AddReader<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>>(topic_name_ +
                                                                                              std::string("_encoder"));
#else
    sub_encoded_ = bus0_.AddReader<uint8_t*>(topic_name_ + std::string("_encoder"));
#endif
    sub_encoded_.SetOnDataAvailableCallback(h2);
    LOG(INFO) << "image decoder initialized ok";

    /* loop */
#if defined(CMW_WRAPPER_ENABLE_DDS_MICRO)
    bus0_.GetParticipant()->enable();
#endif
    cmw_wrapper::BusType::AsyncSpin(1);
    while (cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(0.1f);
    }
}

template <typename Tdec>
void ImageDecoderAppT<Tdec>::GetParameters(const std::string& config_file)
{
    LOG(INFO) << "load parameters from " << config_file;
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        topic_name_           = node["topic_name"].as<std::string>();
        sensor_id_            = node["sensor_id"].as<uint32_t>();
        cols_                 = node["cols"].as<uint32_t>();
        rows_                 = node["rows"].as<uint32_t>();
        fps_                  = node["fps"].as<uint32_t>();
        show_image_           = node["show_image"].as<bool>();
        use_ipc_              = node["use_ipc"].as<holo::bool_t>("true");
    }
    catch (std::exception& e)
    {
        std::string error = "failed to read yaml config";
        LOG(ERROR) << error << ": " << e.what();
        throw std::runtime_error(error);
    }
}

template <typename Tdec>
void ImageDecoderAppT<Tdec>::ImageDecoderHandler(const uint8_t* data, size_t size)
{
    LOG(INFO) << "image decoder reveive data size: " << size;
    std::shared_ptr<uint8_t> encoded_data(new uint8_t[size](), std::default_delete<uint8_t[]>());
    if (nullptr == encoded_data)
    {
        LOG(ERROR) << "malloc encode_data space failed !";
        return;
    }
    memcpy(encoded_data.get(), data, size);

    {
        std::lock_guard<std::mutex> lg(encoded_data_mutex_);
        encoded_data_cache_.push(std::make_pair(encoded_data, size));
    }
}

template <typename Tdec>
void ImageDecoderAppT<Tdec>::DecodeThread()
{
    std::shared_ptr<uint8_t> encoded_data(new uint8_t[MAX_ENCODED_DATA_SIZE](), std::default_delete<uint8_t[]>());

    while (runing_)
    {
        holo::os::Sleep(0.001);
        {
            std::lock_guard<std::mutex> lg(encoded_data_mutex_);
            if (encoded_data_cache_.empty())
            {
                continue;
            }

            holo::serialization::Deserializer<false, 4> deserializer(
                const_cast<uint8_t*>(encoded_data_cache_.front().first.get()), encoded_data_cache_.front().second);
            bool deserialize_result = compress_data_.Deserialize(deserializer);
            encoded_data_cache_.pop();
            if (!deserialize_result)
            {
                LOG(ERROR) << "deserialization failed";
                continue;
            }
        }

        if (SaveType::DONT_SAVE != save_encoded_data_type_)
        {
            std::string name = std::to_string(static_cast<uint32_t>(sensor_id_));
            if (SaveType::SAVE_FILE == save_encoded_data_type_)
            {
                do
                {
                    if (ImageType::H264 == compress_data_.image_type)
                    {
                        name += ".h264";
                    }
                    else if (ImageType::H265 == compress_data_.image_type)
                    {
                        name += ".h265";
                    }
                    else
                    {
                        break;
                    }

                    if ((uint8_t)holo::sensors::camera::FrameType::I == compress_data_.frame_type)
                    {
                        found_first_key_frame_ = true;
                    }
                    if (found_first_key_frame_)
                    {
                        FILE* encoded_data_file = fopen(name.c_str(), "a+");
                        fseek(encoded_data_file, 0, SEEK_END);
                        fwrite(compress_data_.data, 1, compress_data_.size, encoded_data_file);
                        fclose(encoded_data_file);
                    }
                } while (0);
            }
            else
            {
                if (SaveType::SAVE_ALL == save_encoded_data_type_)
                {
                    name += "." + std::to_string(compress_data_.trigger_stamp.ToSec());
                }
                name += ".encoded_data";
                FILE* encoded_data_file = fopen(name.c_str(), "wb");
                fwrite(&compress_data_, 1, sizeof(compress_data_), encoded_data_file);
                fclose(encoded_data_file);
            }
        }

        if (!start_compare_timestamp_)
        {
            start_compare_timestamp_ = true;
            time_fps_                = holo::common::details::Duration(static_cast<int64_t>(FRAME_TIME_SLOT / fps_));
        }
        else
        {
            if (compress_data_.trigger_stamp - last_compress_data_.trigger_stamp > time_fps_)
            {
                LOG(ERROR) << "compress_data_.trigger_stamp - last_compress_data_.trigger_stamp: "
                           << (compress_data_.trigger_stamp - last_compress_data_.trigger_stamp).ToString();
            }
        }
        last_compress_data_ = compress_data_;

        image_decoder_->Decode(compress_data_);
    }
}

template <typename Tdec>
void ImageDecoderAppT<Tdec>::SaveImageThread(std::shared_ptr<uint8_t> data, uint64_t size, int code, SaveType save_type)
{
    holo::sensors::camera::ImageWrapper         wrapper;
    holo::serialization::Deserializer<false, 4> deserializer(data.get(), size);
    if (!wrapper.Deserialize(deserializer))
    {
        LOG(ERROR) << "deserialization failed";
        return;
    }

    cv::Mat image;
    cv::cvtColor(holo::sensors::camera::Image2Mat(wrapper.GetImage()), image, code);
    std::string name = std::to_string(static_cast<uint32_t>(sensor_id_));
    if (SaveType::SAVE_ALL == save_type)
    {
        name += "." + std::to_string(wrapper.GetImage().GetTimestamp().ToNsec());
    }
    name += ".jpg";
    cv::imwrite(name.c_str(), image);
}

template <typename Tdec>
void ImageDecoderAppT<Tdec>::ImageDataHandler(const holo::Image& img, SaveType save_type)
{
    if (use_ipc_)
    {
        ipc_->SetImageData(img);
        uint64_t info = (static_cast<uint64_t>(sensor_id_) << 32) + (counter_++);
        pub_info_.Write(info);
    }

    if (SaveType::DONT_SAVE == save_type)
    {
        return;
    }

    holo::sensors::camera::ImageWrapper image(img);
    const uint32_t                      size = image.GetSerializedSize();
    std::shared_ptr<uint8_t>            data(new uint8_t[size](), std::default_delete<uint8_t[]>());
    if (nullptr == data)
    {
        LOG(ERROR) << "memory alloc failed";
        return;
    }
    holo::serialization::Serializer<false, 4> serializer(data.get(), size);
    if (!image.Serialize(serializer))
    {
        LOG(ERROR) << "serialization failed";
        return;
    }

    save_image_thread_pool_->AddTask(&ImageDecoderAppT<Tdec>::SaveImageThread, this, data, image.GetSerializedSize(), CV_RGB2BGR, save_type);
}

template <>
void ImageDecoderAppT<H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>>::ImageDataHandler(
    const holo::Image& img, SaveType save_type)
{
    if (use_ipc_)
    {
        ipc_->SetImageData(img);
        uint64_t info = (static_cast<uint64_t>(sensor_id_) << 32) + (counter_++);
        pub_info_.Write(info);
    }

    if (SaveType::DONT_SAVE == save_type)
    {
        return;
    }

    holo::sensors::camera::ImageWrapper image(img);
    const uint32_t                      size = image.GetSerializedSize();
    std::shared_ptr<uint8_t>            data(new uint8_t[size](), std::default_delete<uint8_t[]>());
    if (nullptr == data)
    {
        LOG(ERROR) << "memory alloc failed";
        return;
    }
    holo::serialization::Serializer<false, 4> serializer(data.get(), size);
    if (!image.Serialize(serializer))
    {
        LOG(ERROR) << "serialization failed";
        return;
    }

    save_image_thread_pool_->AddTask(
        &ImageDecoderAppT<H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>>::SaveImageThread, this, data,
        image.GetSerializedSize(), CV_YUV2BGR_NV12, save_type);
}

template <>
void ImageDecoderAppT<H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>>::ImageDataHandler(
    const holo::Image& img, SaveType save_type)
{
    if (use_ipc_)
    {
        ipc_->SetImageData(img);
        uint64_t info = (static_cast<uint64_t>(sensor_id_) << 32) + (counter_++);
        pub_info_.Write(info);
    }

    if (SaveType::DONT_SAVE == save_type)
    {
        return;
    }

    holo::sensors::camera::ImageWrapper image(img);
    const uint32_t                      size = image.GetSerializedSize();
    std::shared_ptr<uint8_t>            data(new uint8_t[size](), std::default_delete<uint8_t[]>());
    if (nullptr == data)
    {
        LOG(ERROR) << "memory alloc failed";
        return;
    }
    holo::serialization::Serializer<false, 4> serializer(data.get(), size);
    if (!image.Serialize(serializer))
    {
        LOG(ERROR) << "serialization failed";
        return;
    }

    save_image_thread_pool_->AddTask(
        &ImageDecoderAppT<H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>>::SaveImageThread, this, data,
        image.GetSerializedSize(), CV_YUV2BGR_NV12, save_type);
}

template class ImageDecoderAppT<H26xDecoder<ImageType::H264, holo::Image::Encoding::RGB>>;
template class ImageDecoderAppT<H26xDecoder<ImageType::H265, holo::Image::Encoding::RGB>>;
template class ImageDecoderAppT<H26xDecoder<ImageType::H264, holo::Image::Encoding::BGR>>;
template class ImageDecoderAppT<H26xDecoder<ImageType::H265, holo::Image::Encoding::BGR>>;
template class ImageDecoderAppT<H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>>;
template class ImageDecoderAppT<H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>>;

}  // namespace holo_cmw

static void signalSegHandler(int sig)
{
    cmw_wrapper::BusType::SignalHandler(sig);
    holo::log::HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
}

int main(int argc, char** argv)
{
    cxxopts::Options options("ImageDecoder", "ImageDecoder node");
    // clang-format off
    options.add_options()
        ("h,help", "help message")
        ("c,config_file", "Configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "Node name for this app", cxxopts::value<std::string>()->default_value("ImageDecoder"))
        ("s,save_image", "Save image mode: new, all", cxxopts::value<std::string>()->default_value(""))
        ("e,save_encoded_data", "Save encoded data mode: new, all, file", cxxopts::value<std::string>()->default_value(""))
        ("m,min_log_level", "minimum log level, ALL/TRACE/0, D/1, I/2, W/3, E/4, F/5, OFF/6", cxxopts::value<holo::uint8_t>()->default_value("0"))
        ("t,threads_num", "number of threads", cxxopts::value<uint32_t>()->default_value("6"))
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

    uint32_t    domain_id   = options["domain_id"].as<uint32_t>();
    uint32_t    threads_num = options["threads_num"].as<uint32_t>();
    std::string node_name   = options["node_name"].as<std::string>();
    holo::CreateHoloLogSubdirectory("holo_sensors");
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/image_decoder_" + node_name + ".log");
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
    std::string      encode_type = node["encode_type"].as<std::string>();
    std::string      decode_type = node["decode_type"].as<std::string>("rgb");
    LOG(INFO) << "encode_type = " << encode_type;
    LOG(INFO) << "decode_type = " << decode_type;

    using holo::sensors::camera::ImageType;
    try
    {
        if (encode_type == "h264" && decode_type == "rgb")
        {
            using Tdec = holo::sensors::camera::H26xDecoder<ImageType::H264, holo::Image::Encoding::RGB>;
            holo_cmw::ImageDecoderAppT<Tdec> driver(domain_id, "", threads_num);
            driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["save_encoded_data"].as<std::string>(), options["output_video_size"].as<std::string>());
        }
        else if (encode_type == "h265" && decode_type == "rgb")
        {
            using Tdec = holo::sensors::camera::H26xDecoder<ImageType::H265, holo::Image::Encoding::RGB>;
            holo_cmw::ImageDecoderAppT<Tdec> driver(domain_id, "", threads_num);
            driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["save_encoded_data"].as<std::string>(), options["output_video_size"].as<std::string>());
        }
        else if (encode_type == "h264" && decode_type == "bgr")
        {
            using Tdec = holo::sensors::camera::H26xDecoder<ImageType::H264, holo::Image::Encoding::BGR>;
            holo_cmw::ImageDecoderAppT<Tdec> driver(domain_id, "", threads_num);
            driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["save_encoded_data"].as<std::string>(), options["output_video_size"].as<std::string>());
        }
        else if (encode_type == "h265" && decode_type == "bgr")
        {
            using Tdec = holo::sensors::camera::H26xDecoder<ImageType::H265, holo::Image::Encoding::BGR>;
            holo_cmw::ImageDecoderAppT<Tdec> driver(domain_id, "", threads_num);
            driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["save_encoded_data"].as<std::string>(), options["output_video_size"].as<std::string>());
        }
        else if (encode_type == "h264" && decode_type == "nv12")
        {
            using Tdec = holo::sensors::camera::H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>;
            holo_cmw::ImageDecoderAppT<Tdec> driver(domain_id, "", threads_num);
            driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["save_encoded_data"].as<std::string>(), options["output_video_size"].as<std::string>());
        }
        else if (encode_type == "h265" && decode_type == "nv12")
        {
            using Tdec = holo::sensors::camera::H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>;
            holo_cmw::ImageDecoderAppT<Tdec> driver(domain_id, "", threads_num);
            driver.Setup(options["config_file"].as<std::string>(), options["save_image"].as<std::string>(), options["save_encoded_data"].as<std::string>(), options["output_video_size"].as<std::string>());
        }
        else
        {
            std::string info("unknown encode type");
            LOG(ERROR) << info << ": " << encode_type;
            throw std::invalid_argument(info);
        }
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "image decoder application failed, exit";
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}