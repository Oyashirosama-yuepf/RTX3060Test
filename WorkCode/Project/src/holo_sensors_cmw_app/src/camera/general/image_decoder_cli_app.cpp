/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image decoder app.
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-12-24.
 */

#include <camera/general/image_decoder_cli_app.h>
#include <holo/log/hololog.h>
#include <csignal>
#include <iostream>

namespace holo_cmw
{
ImageDecoderCliApp::ImageDecoderCliApp(const struct ImageDecoderCliAppParam& param)
    : bus_{param.domain_id, param.node_name}
    , sensor_id_(param.sensor_id)
    , counter_(0)
    , output_video_cols_(0)
    , output_video_rows_(0)
    , fps_(param.fps)
    , threads_num_(param.threads_num)
    , show_image_(param.show_image)
    , topic_name_(param.topic_name)
    , save_image_data_type_(param.save_image_data_type)
    , output_image_type_(param.output_image_type)
    , save_encoded_data_type_(param.save_encoded_data_type)
    , save_data_path_(param.save_data_path)
    , decode_buffer_{new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>()}
    , sutup_decoder_(false)
    , found_first_key_frame_(false)
    , use_ipc_(param.use_ipc)
    , start_compare_timestamp_(false)
    , runing_(true)
{
    bool_t result = GetOutputVideoSize(param.output_video_size, output_video_cols_, output_video_rows_);

    if (result)
    {
        LOG(INFO) << "Set Output Video Size Success. Output Video Size: " << output_video_cols_ << "x" << output_video_rows_;
    }
    else
    {
        output_video_cols_ = 0;
        output_video_rows_ = 0;
        LOG(INFO) << "Set Output Video Size Faile. Output Video Size: " << output_video_cols_ << "x" << output_video_rows_;
    }

    decode_thread_ = std::make_shared<std::thread>(std::bind(&ImageDecoderCliApp::DecodeThread, this));

    std::memset(decode_buffer_.get(), 0, IMAGE_ENCODE_SIZE_MAX);
    compress_data_.data = decode_buffer_.get();

/* cmw */
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    pub_info_ = bus_.AddWriter<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>(topic_name_ + std::string("_info"));
#else
    pub_info_ = bus_.AddWriter<uint64_t>(topic_name_ + std::string("_info"));
#endif

std::function<void(const uint8_t*, size_t)> sub_encoded_data_callback =
        std::bind(&ImageDecoderCliApp::ImageDecoderHandler, this, std::placeholders::_1, std::placeholders::_2);
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    sub_encoded_ = bus_.AddReader<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>>(topic_name_ +
                                                                                              std::string("_encoder"));
#else
    sub_encoded_ = bus_.AddReader<uint8_t*>(topic_name_ + std::string("_encoder"));
#endif
    sub_encoded_.SetOnDataAvailableCallback(sub_encoded_data_callback);
    LOG(INFO) << "image decoder initialized ok";

/* loop */
#if defined(CMW_WRAPPER_ENABLE_DDS_MICRO)
    bus_.GetParticipant()->enable();
#endif
    cmw_wrapper::BusType::AsyncSpin(1);
    while (cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(0.1f);
    }
}

ImageDecoderCliApp::~ImageDecoderCliApp()
{
    runing_ = false;
    if (decode_thread_ && (decode_thread_->joinable()))
    {
        decode_thread_->join();
    }

    if (save_image_thread_pool_)
    {
        save_image_thread_pool_->Destroy();
    }
}

bool_t ImageDecoderCliApp::GetOutputVideoSize(const std::string& output_video_size, uint32_t& output_video_cols, uint32_t& output_video_rows)
{
    if (std::string("") == output_video_size)
    {
        output_video_cols_ = 0;
        output_video_rows_ = 0;

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

void ImageDecoderCliApp::ImageDecoderHandler(const uint8_t* data, size_t size)
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

void ImageDecoderCliApp::SetupDecoder()
{
    cols_                     = compress_data_.cols;
    rows_                     = compress_data_.rows;
    if ((output_video_cols_ == 0) && (output_video_rows_ == 0))
    {
        output_video_cols_ = cols_;
        output_video_rows_ = rows_;
    }
    compress_data_image_type_ = compress_data_.image_type;

    if ((ImageType::H265 == compress_data_image_type_) && (holo::Image::Encoding::RGB == output_image_type_))
    {
        LOG(INFO) << "show_image_" << show_image_;
        image_decoder_ = std::make_shared<holo::sensors::camera::H26xDecoder<ImageType::H265, holo::Image::Encoding::RGB>>
                     (sensor_id_, cols_, rows_, fps_, show_image_);
        if (use_ipc_)
        {
            ipc_ = std::make_shared<holo::sensors::camera::ImageIpc>(sensor_id_, rows_, cols_, holo::Image::Encoding::RGB);
        }
        image_decoder_->SetOutputVideoSize(output_video_cols_, output_video_rows_);
    }
    else if ((ImageType::H264 == compress_data_image_type_) && (holo::Image::Encoding::RGB == output_image_type_))
    {
        image_decoder_ = std::make_shared<holo::sensors::camera::H26xDecoder<ImageType::H264, holo::Image::Encoding::RGB>>
                     (sensor_id_, cols_, rows_, fps_, show_image_);
        if (use_ipc_)
        {
            ipc_ = std::make_shared<holo::sensors::camera::ImageIpc>(sensor_id_, rows_, cols_, holo::Image::Encoding::RGB);
        }
        image_decoder_->SetOutputVideoSize(output_video_cols_, output_video_rows_);
    }
    else if ((ImageType::H265 == compress_data_image_type_) && (holo::Image::Encoding::BGR == output_image_type_))
    {
        image_decoder_ = std::make_shared<holo::sensors::camera::H26xDecoder<ImageType::H265, holo::Image::Encoding::BGR>>
                     (sensor_id_, cols_, rows_, fps_, show_image_);
        ipc_           = std::make_shared<holo::sensors::camera::ImageIpc>(sensor_id_, rows_, cols_, holo::Image::Encoding::BGR);
        image_decoder_->SetOutputVideoSize(output_video_cols_, output_video_rows_);
    }
    else if ((ImageType::H264 == compress_data_image_type_) && (holo::Image::Encoding::BGR == output_image_type_))
    {
        image_decoder_ = std::make_shared<holo::sensors::camera::H26xDecoder<ImageType::H264, holo::Image::Encoding::BGR>>
                     (sensor_id_, cols_, rows_, fps_, show_image_);
        if (use_ipc_)
        {
            ipc_ = std::make_shared<holo::sensors::camera::ImageIpc>(sensor_id_, rows_, cols_, holo::Image::Encoding::BGR);
        }
        image_decoder_->SetOutputVideoSize(output_video_cols_, output_video_rows_);
    }
    else if ((ImageType::H265 == compress_data_image_type_) && (holo::Image::Encoding::NV12 == output_image_type_))
    {
        LOG(INFO) << "show_image_" << show_image_;
        image_decoder_ = std::make_shared<holo::sensors::camera::H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>>
                     (sensor_id_, cols_, rows_, fps_, show_image_);
        if (use_ipc_)
        {
            ipc_ = std::make_shared<holo::sensors::camera::ImageIpc>(sensor_id_, rows_, cols_, holo::Image::Encoding::NV12);
        }
        image_decoder_->SetOutputVideoSize(output_video_cols_, output_video_rows_);
    }
    else
    {
        image_decoder_ = std::make_shared<holo::sensors::camera::H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>>
                     (sensor_id_, cols_, rows_, fps_, show_image_);
        if (use_ipc_)
        {
            ipc_ = std::make_shared<holo::sensors::camera::ImageIpc>(sensor_id_, rows_, cols_, holo::Image::Encoding::NV12);
        }
        image_decoder_->SetOutputVideoSize(output_video_cols_, output_video_rows_);
    }

    std::function<void(const holo::Image&)> image_callback = std::bind(&ImageDecoderCliApp::ImageDataHandler, this, std::placeholders::_1);
    image_decoder_->SetImageCallback(image_callback);

    if (save_image_data_type_ != holo_cmw::SaveType::DONT_SAVE)
    {
        save_image_thread_pool_ = std::make_shared<holo::thread::ThreadPool>(threads_num_);
    }

    sutup_decoder_ = true;
}

void ImageDecoderCliApp::SaveEncodedDataFile(std::string name, std::string mode)
{
    FILE* encoded_data_file = fopen(name.c_str(), mode.c_str());
    fseek(encoded_data_file, 0, SEEK_END);
    fwrite(compress_data_.data, 1, compress_data_.size, encoded_data_file);
    fclose(encoded_data_file);
}

void ImageDecoderCliApp::DecodeThread()
{
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

        if (!sutup_decoder_)
        {
            SetupDecoder();
        }

        if (holo_cmw::SaveType::DONT_SAVE != save_encoded_data_type_)
        {
            std::string name = save_data_path_ + std::to_string(static_cast<uint32_t>(sensor_id_));

            if ((uint8_t)holo::sensors::camera::FrameType::I == compress_data_.frame_type)
            {
                found_first_key_frame_ = true;
            }
            if (found_first_key_frame_)
            {
                do
                {
                    if (holo_cmw::SaveType::SAVE_FILE == save_encoded_data_type_)
                    {
                        if (ImageType::H264 == compress_data_image_type_)
                        {
                            name += ".h264";
                        }
                        else if (ImageType::H265 == compress_data_image_type_)
                        {
                            name += ".h265";
                        }
                        else
                        {
                            break;
                        }
                        SaveEncodedDataFile(name, std::string("a+"));
                    }
                    else if(holo_cmw::SaveType::SAVE_NEW == save_encoded_data_type_)
                    {
                        if (ImageType::H264 == compress_data_image_type_)
                        {
                            name += ".h264";
                        }
                        else if (ImageType::H265 == compress_data_image_type_)
                        {
                            name += ".h265";
                        }
                        else
                        {
                            break;
                        }
                        SaveEncodedDataFile(name, std::string("wb"));
                    }
                    else
                    {
                        name += std::to_string(compress_data_.trigger_stamp.ToNsec());

                        if (ImageType::H264 == compress_data_image_type_)
                        {
                            name += ".h264";
                        }
                        else if (ImageType::H265 == compress_data_image_type_)
                        {
                            name += ".h265";
                        }
                        else
                        {
                            break;
                        }
                        SaveEncodedDataFile(name, std::string("wb"));
                    }
                }
                while(0);
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

void ImageDecoderCliApp::SaveImageThread(std::shared_ptr<uint8_t> data, uint64_t size, int code)
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
    std::string name = save_data_path_ + std::to_string(static_cast<uint32_t>(sensor_id_));
    if (save_image_data_type_ != holo_cmw::SaveType::SAVE_NEW)
    {
        name += "." + std::to_string(wrapper.GetImage().GetTimestamp().ToNsec());
    }
    name += ".jpg";
    cv::imwrite(name.c_str(), image);
}

void ImageDecoderCliApp::ImageDataHandler(const holo::Image& img)
{
    if (use_ipc_)
    {
        ipc_->SetImageData(img);
        uint64_t info = (static_cast<uint64_t>(sensor_id_) << 32) + (counter_++);
        pub_info_.Write(info);
    }

    if (holo_cmw::SaveType::DONT_SAVE == save_image_data_type_)
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

    if (holo::Image::Encoding::RGB == output_image_type_)
    {
        save_image_thread_pool_->AddTask(&ImageDecoderCliApp::SaveImageThread, this, data, image.GetSerializedSize(), CV_RGB2BGR);
    }
    else if (holo::Image::Encoding::NV12 == output_image_type_)
    {
        save_image_thread_pool_->AddTask(&ImageDecoderCliApp::SaveImageThread, this, data, image.GetSerializedSize(), CV_YUV2BGR_NV12);
    }
}
}  // namespace holo_cmw

static void signalSegHandler(int sig)
{
    cmw_wrapper::BusType::SignalHandler(sig);
    holo::log::HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
}

int main(int argc, char** argv)
{
    cxxopts::Options options("ImageDecoderCmw", "ImageDecoderCmw node");
    // clang-format off
    options.add_options()
        ("h,help", "help message")
        ("v,verbose", "if also outputs glog to console")
        ("ipc", "use ipc")
        ("n,node_name", "Node name for this app", cxxopts::value<std::string>()->default_value("ImageDecoderCmw"))
        ("m,min_log_level", "minimum log level, ALL/TRACE/0, D/1, I/2, W/3, E/4, F/5, OFF/6", cxxopts::value<holo::uint8_t>()->default_value("0"))
        ("t,threads_num", "number of threads", cxxopts::value<uint32_t>()->default_value("6"))
        ("d,domain_id", "domain id", cxxopts::value<int>()->default_value("0"))
        ("s,save_image", "Save image mode: new, all", cxxopts::value<std::string>()->default_value(""))
        ("e,save_encoded_data", "Save encoded data mode: new, all, file", cxxopts::value<std::string>()->default_value(""))
        ("o,save_file_path", "Save File Path", cxxopts::value<std::string>()->default_value("./"))
        ("sensor_id", "Sensor Id", cxxopts::value<uint32_t>())
        ("show_image", "Show Image")
        ("topic", "Topic Name", cxxopts::value<std::string>())
        ("output_image_type", "Output Image Type: nv12, rgb, bgr", cxxopts::value<std::string>()->default_value("nv12"))
        ("fps", "fps", cxxopts::value<uint32_t>()->default_value("20"))
        ("output_video_size", "IPC And SaveImage Video Size: ${cols}x${rows}", cxxopts::value<std::string>()->default_value(""))
        ;
    // clang-format on
    options.parse(argc, argv);

    if (options.count("help"))
    {
        std::cout << options.help() << std::endl;
        return 0;
    }
    if (!options.count("sensor_id"))
    {
        std::cout << "please enter the correct sensor_id" << std::endl;
        return -1;
    }
    if (!options.count("topic"))
    {
        std::cout << "please enter the correct topic" << std::endl;
        return -1;
    }

    struct holo_cmw::ImageDecoderCliAppParam param;

    param.node_name         = options["node_name"].as<std::string>();
    param.threads_num       = options["threads_num"].as<uint32_t>();
    param.domain_id         = options["domain_id"].as<int>();
    param.save_data_path    = options["save_file_path"].as<std::string>();
    param.sensor_id         = options["sensor_id"].as<uint32_t>();
    param.show_image        = options["show_image"].as<bool>();
    param.topic_name        = options["topic"].as<std::string>();
    param.fps               = options["fps"].as<uint32_t>();
    param.output_video_size = options["output_video_size"].as<std::string>();

    if (std::string("") == options["save_image"].as<std::string>())
    {
        param.save_image_data_type = holo_cmw::SaveType::DONT_SAVE;
    }
    else if (std::string("all") == options["save_image"].as<std::string>())
    {
        param.save_image_data_type = holo_cmw::SaveType::SAVE_ALL;
    }
    else
    {
        param.save_image_data_type = holo_cmw::SaveType::SAVE_NEW;
    }

    if (std::string("file") == options["save_encoded_data"].as<std::string>())
    {
        param.save_encoded_data_type = holo_cmw::SaveType::SAVE_FILE;
    }
    else if (std::string("all") == options["save_encoded_data"].as<std::string>())
    {
        param.save_encoded_data_type = holo_cmw::SaveType::SAVE_ALL;
    }
    else if (std::string("new") == options["save_encoded_data"].as<std::string>())
    {
        param.save_encoded_data_type = holo_cmw::SaveType::SAVE_NEW;
    }
    else
    {
        param.save_encoded_data_type = holo_cmw::SaveType::DONT_SAVE;
    }

    if (std::string("rgb") == options["output_image_type"].as<std::string>())
    {
        param.output_image_type = holo::Image::Encoding::RGB;
    }
    else if (std::string("bgr") == options["output_image_type"].as<std::string>())
    {
        param.output_image_type = holo::Image::Encoding::BGR;
    }
    else if (std::string("nv12") == options["output_image_type"].as<std::string>())
    {
        param.output_image_type = holo::Image::Encoding::NV12;
    }
    else
    {
        LOG(ERROR) << "invalid image type";
    }

    if (options.count("ipc"))
    {
        param.use_ipc = true;
    }
    else
    {
        param.use_ipc = false;
    }

    cmw_wrapper::BusType::Initialize(argc, argv, param.node_name);

    holo::CreateHoloLogSubdirectory("holo_sensors");
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/image_decoder_" + param.node_name + ".log");
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
    Adsfi::AdsfiLogger::GetInstance().InitLogging(std::string("image_capture_") + param.node_name, std::string("desc"), 4, 6,
                                                  std::string("./log/holo_sensors/"));
    Adsfi::AdsfiLogger::GetInstance().CreateLogger(std::string("image_capture_") + param.node_name, std::string("desc"), 4);
#else
    Adsfi::AdsfiLogger::GetInstance().InitLogging(
        std::string("image_capture_") + param.node_name, std::string("desc"), static_cast<Adsfi::HafLogLevelType>(4),
        static_cast<Adsfi::HafLogModeType>(6), std::string("./log/holo_sensors/"));
    Adsfi::AdsfiLogger::GetInstance().CreateLogger(std::string("image_capture_") + param.node_name, std::string("desc"),
                                                   static_cast<Adsfi::HafLogLevelType>(4));
#endif
#endif

    using holo::sensors::camera::ImageType;
    try
    {
        holo_cmw::ImageDecoderCliApp image_decoder_cmw_app(param);
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "image decoder application failed, exit";
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}