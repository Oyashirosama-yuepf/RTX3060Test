/**
 * @file holo_record.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief the implementation of the holo record cmw app
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#include <dirent.h>
#include <holo/log/hololog.h>
#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_record.h>
#include <utils.h>
#if defined(HOLO_TIME_WITH_MDC_TIME)
#include <holo/sensors/utils/mdc610_utils.h>
#endif

#include <csignal>
#include <fstream>
#include <regex>

namespace holo_cmw
{
HoloRecord::HoloRecord(int argc, char** argv, const std::string& name, holo::uint64_t domain_id, bool encode,
                       holo::uint16_t extract_frame, const std::string& encode_type, const std::string& image_type)
  : active_record_(false), encode_(encode), spliting_(false), bag_base_counter_(0)
{
    BusType::Initialize(argc, argv, name);
    signal(SIGINT, BusType::SignalHandler);
    bus_ptr_  = std::make_shared<BusType>(domain_id, "");
    if (encode_)
    {
        if (extract_frame > 0)
        {
            extract_frame_frequency_ = extract_frame;
        }
        encode_thread_pool_ = std::shared_ptr<HoloThreadPool>(new HoloThreadPool(5));
        encode_thread_pool_->EnQueue(std::bind(&HoloRecord::encodeImage, this));
        setTencType(encode_type, image_type);
    }
    if (nullptr == encode_thread_pool_)
    {
        encode_thread_pool_ = std::shared_ptr<HoloThreadPool>(new HoloThreadPool(5));
        LOG(INFO) << "Initialize thread resources.";
    }
}

HoloRecord::~HoloRecord()
{
    BusType::SignalHandler(SIGINT);
    active_record_ = false;
    encode_ = false;

    record_ptr_.reset();
    encode_thread_pool_.reset();
    std::cout << "Finish Record!" << std::endl;
}

bool HoloRecord::SetUp(const ::holo::uint64_t split_size, const ::holo::uint64_t split_time, const std::string& file_name, bool is_split)
{
    bag_base_name_ = file_name;
    if (!loadConfigFile("", split_size, split_time))
    {
        LOG(ERROR) << "Could not load config file ";
        return false;
    }
    if (!initWriter(bag_base_name_, is_split))
    {
        LOG(ERROR) << "Could not create file.";
        return false;
    }
    if (!storeRunningParams("holo_sensors/extrinsics") || !storeRunningParams("holo_sensors/intrinsics"))
    {
        LOG(ERROR) << "Could not store the params file.";
    }
    if (!storeDataVersion() || !storeHardwareVersion() || !storeSoftwareVersion())
    {
        LOG(ERROR) << "Could not store the Data | Software | Hardware Version.";
    }
    if (!createTopics())
    {
        LOG(ERROR) << "Could not create topics.";
        return false;
    }
    return true;
}

bool HoloRecord::splitBag()
{
    spliting_ = true;
    if (SetUp(log(options_.max_bagfile_size)/log(2) - 29, options_.max_bagfile_duration, bag_base_name_, !bag_base_name_.empty()))
    {
        spliting_ = false;
        return true;
    }
    return false;
}

bool HoloRecord::createSplitBag()
{
    if (record_ptr_feature_ != nullptr)
    {
        LOG(INFO) << "Feature holobag already create.";
        return false;
    }
    // init record_ptr_feature_
    record_ptr_feature_ = std::make_shared<holo::bag::Writer>();

    options_.uri            = "";
    options_.max_cache_size = 1536;

    if (bag_base_name_.empty())
    {
#if defined(HOLO_TIME_WITH_MDC_TIME)
        holo::common::Timestamp current_time(0, 0);
        if (!holo::mdc610::GetManagmentLevelTime(current_time))
        {
            LOG(ERROR) << "GetLocalTime failed";
            return false;
        }
        int64_t timestamp = current_time.ToNsec();
        options_.uri += getTime(timestamp);
#else
        options_.uri += getTime();
#endif
    }
    else
    {
        options_.uri += bag_base_name_ + "_" + std::to_string(++bag_base_counter_);
    }
    record_ptr_feature_->Open(options_);

    for (auto topic : topic_map_)
    {
        record_ptr_feature_->CreateTopic(topic.second);
    }
    return true;
}

void HoloRecord::Record()
{
    if (!initSubscriber())
    {
        LOG(ERROR) << "Could not init subscriber ";
        return;
    }
    showSubInfo();
    active_record_ = true;
    BusType::AsyncSpin(1);
    while (BusType::IsRunning())
    {
        auto split_control = record_ptr_->ShouldSplitBagFile();
        if (split_control.first)
        {
            splitBag();
            split_control.second = false;
        }
        if (split_control.second)
        {
            createSplitBag();
        }
        sleep(1);
        initSubscriber();
    }
}

void HoloRecord::showSubInfo()
{
    std::cout << "Subscribing: " << std::endl;
    std::cout << "Topics size = " << topic_map_.size() << std::endl;
    for (auto topic: topic_map_)
    {
        std::cout << "Topic name: " << topic.first << std::endl;
    }
    std::cout << "Begin to record!" << std::endl;
}

bool HoloRecord::loadConfigFile(const std::string& config_file, const ::holo::uint64_t split_size, const ::holo::uint64_t split_time)
{
    options_.uri                  = "";
    options_.max_cache_size       = 1536;
    options_.max_bagfile_duration = split_time;
    if(split_size == 0)
    {
        options_.max_bagfile_size = 0;
    }
    else
    {
        options_.max_bagfile_size = pow(2, 29 + split_size);
    }

    if(isUmbMessage())
    {
        if (topic_map_.size() > 0)
        {
            return true;
        }

        std::string file_path;
        std::string topic_type_file;

        if (config_file.empty())
        {
            file_path = holo::GetHoloConfigRootDirectory() + "/umb_topic.cfg";
        }
        else
        {
            file_path = config_file;
        }

        std::ifstream ifs(file_path);
        if (!ifs.is_open())
        {
            LOG(ERROR) << "Failed to open topic config file: " << file_path;
            return false;
        }

        std::string              topic_name;
        uint32_t                 topic_id;
        holo::bag::TopicMetadata record_topic;
        record_topic.type = "cmw_wrapper::BuiltinBuffer";
        while (ifs >> topic_name >> topic_id)
        {
            record_topic.name                 = topic_name;
            record_topic.serialization_format = std::to_string(4);
            record_topic.type_version         = topic_id;
            topic_map_.insert({record_topic.name, record_topic});
        }

        for (auto topic : topic_map_)
        {
            if (topic.second.type == "cmw_wrapper::BuiltinBuffer")
            {
                auto reader = bus_ptr_->AddReader<holo::uint8_t*>(topic.first);
                auto f =
                    std::bind(&HoloRecord::onMessage, this, std::placeholders::_1, std::placeholders::_2, topic.second);
                reader.SetOnDataAvailableCallback(f);
            }
            else
            {
                LOG(ERROR) << "Could not tell the topic with name " << topic.first;
            }
        }
    }
    return true;
}

bool HoloRecord::initWriter(const std::string& file_name, bool is_split)
{
    auto temp_record_ptr = record_ptr_;

    if(record_ptr_feature_ != nullptr)
    {
        record_ptr_         = record_ptr_feature_;
        record_ptr_feature_ = nullptr;
        spliting_           = false;
        encode_thread_pool_->EnQueue(std::bind(&HoloRecord::recodeReset, this, temp_record_ptr));
        LOG(INFO) << "Finish init writer split bag.";
        return true;
    }

    record_ptr_ = std::make_shared<holo::bag::Writer>();
    if (record_ptr_)
    {
        if (!is_split)
        {
#if defined(HOLO_TIME_WITH_MDC_TIME)
        holo::common::Timestamp current_time(0, 0);
        if (!holo::mdc610::GetManagmentLevelTime(current_time))
        {
            LOG(ERROR) << "GetLocalTime failed";
            return false;
        }
        int64_t timestamp = current_time.ToNsec();
        options_.uri += getTime(timestamp);
#else
        options_.uri += getTime();
#endif
        }
        else
        {
            options_.uri += file_name + "_" + std::to_string(++bag_base_counter_);
        }
        record_ptr_->Open(options_);
        createTopics();
        if (spliting_)
        {
            spliting_ = false;
            temp_record_ptr.reset();
        }
        return true;
    }
    throw std::runtime_error("record_ptr_ is no initialized, please check it!");
}

bool HoloRecord::createTopics()
{
    if (record_ptr_)
    {
        for (auto topic : topic_map_)
        {
            record_ptr_->CreateTopic(topic.second);
        }
        return true;
    }
    return false;
}

bool HoloRecord::storeRunningParams(const std::string& path)
{
    if (record_ptr_)
    {
        std::vector<std::shared_ptr<holo::bag::ParamMetadata>> params;
        collectRunningParams(path, params);
        record_ptr_->WriteAllParams(params);
        return true;
    }
    throw std::runtime_error("record_ptr_ is no initialized, please check it!");
}

bool HoloRecord::collectRunningParams(const std::string&                                      path,
                                      std::vector<std::shared_ptr<holo::bag::ParamMetadata>>& params)
{
    std::string yaml_file_path;
    if (path.empty())
    {
        yaml_file_path = holo::GetHoloConfigRootDirectory();
    }
    else
    {
        if (holo::IsAbsolutePath(path))
        {
            yaml_file_path = path;
        }
        else
        {
            yaml_file_path = holo::GetHoloConfigRootDirectory() + "/" + path;
        }
    }
    try
    {
        DIR* dir;
        dir = opendir(yaml_file_path.c_str());
        if (dir == NULL)
        {
            LOG(ERROR) << "the yaml file path is not a directory or not exist: " << yaml_file_path;
            return false;
        }
        struct dirent* ptr       = NULL;
        char           dot[3]    = ".";
        char           dotdot[6] = "..";
        while ((ptr = readdir(dir)) != NULL)  // read dirs in loop
        {
            if ((strcmp(ptr->d_name, dot) == 0) || (strcmp(ptr->d_name, dotdot) == 0))
            {
                continue;
            }
            if (ptr->d_type == DT_DIR)
            {
                collectRunningParams(path + "/" + std::string(ptr->d_name), params);
            }
            else
            {
                std::string file_name(ptr->d_name);
                std::string file_path = yaml_file_path + "/" + file_name;
                LOG(INFO) << " File path = " << file_path;
                std::ifstream     in(file_path);
                std::stringstream buffer;
                buffer << in.rdbuf();
                std::string data(buffer.str());
                auto        param = std::make_shared<holo::bag::ParamMetadata>();
                param->path       = path;
                param->name       = file_name;
                param->file       = data;
                params.push_back(param);
            }
        }
        closedir(dir);
    }
    catch (std::exception& e)
    {
        return false;
    }
    return true;
}

bool HoloRecord::storeDataVersion()
{
    if (record_ptr_)
    {
        std::vector<std::shared_ptr<holo::bag::SysVersionMetadata>> version;
        auto bag_version      = std::make_shared<holo::bag::SysVersionMetadata>();
        bag_version->category = "holobag";
        bag_version->type     = "sys";
        bag_version->version  = "cmw_version";
        version.push_back(bag_version);
        auto map_version      = std::make_shared<holo::bag::SysVersionMetadata>();
        map_version->category = "map";
        map_version->type     = "data";
        map_version->version  = "V7";
        version.push_back(map_version);
        record_ptr_->WriteVersion(version);
        return true;
    }
    throw std::runtime_error("record_ptr_ is no initialized, please check it!");
}

bool HoloRecord::storeSoftwareVersion()
{
    if (record_ptr_)
    {
        std::vector<std::shared_ptr<holo::bag::SysVersionMetadata>> version;
        bool                                                        iscollect = collectLibraryVersion(version);
        LOG(INFO) << "collect lib " << iscollect;
        record_ptr_->WriteVersion(version);
        return true;
    }
    throw std::runtime_error("record_ptr_ is no initialized, please check it!");
}

bool HoloRecord::storeHardwareVersion()
{
    if (record_ptr_)
    {
        std::vector<std::shared_ptr<holo::bag::SysVersionMetadata>> version;
        auto cpu_version      = std::make_shared<holo::bag::SysVersionMetadata>();
        cpu_version->category = "cpu";
        cpu_version->type     = "hardware";
        std::string cpu_info  = GetStrFromTerminal("cat /proc/cpuinfo | grep name | cut -f2 -d: | uniq -c");
        if (cpu_info.empty())
        {
            cpu_info = GetStrFromTerminal("cat /proc/device-tree/model");
        }
        cpu_version->version = cpu_info;
        version.push_back(cpu_version);
        record_ptr_->WriteVersion(version);
        return true;
    }
    throw std::runtime_error("record_ptr_ is no initialized, please check it!");
}

bool HoloRecord::collectLibraryVersion(std::vector<std::shared_ptr<holo::bag::SysVersionMetadata>>& sys_version)
{
    std::string lib_path = holo::GetHoloRootDirectory() + "/lib";
    try
    {
        DIR* dir;
        dir = opendir(lib_path.c_str());
        if (dir == NULL)
        {
            LOG(ERROR) << "the lib file path is not a directory or not exist: " << lib_path;
            return false;
        }
        struct dirent* ptr       = NULL;
        char           dot[3]    = ".";
        char           dotdot[6] = "..";
        while ((ptr = readdir(dir)) != NULL)  // read dirs in loop
        {
            if ((strcmp(ptr->d_name, dot) == 0) || (strcmp(ptr->d_name, dotdot) == 0) || ptr->d_type == DT_DIR)
            {
                continue;
            }
            else
            {
                LOG(INFO) << ptr->d_name;
                std::regex  reg("\\.so\\.");
                std::cmatch m;
                auto        ret = std::regex_search(ptr->d_name, m, reg);
                if (ret)
                {
                    auto lib_version      = std::make_shared<holo::bag::SysVersionMetadata>();
                    lib_version->category = m.prefix();
                    lib_version->type     = "software";
                    lib_version->version  = m.suffix();
                    sys_version.push_back(lib_version);
                }
            }
        }
        closedir(dir);
    }
    catch (std::exception& e)
    {
        return false;
    }
    return true;
}

bool HoloRecord::initSubscriber()
{
    if (!isUmbMessage())
    {
        auto topics = bus_ptr_->GetTopicList();
        holo::bag::TopicMetadata  record_topic;
        for (auto topic : topics)
        {
            if (topic_map_.find(topic.topic_name) != topic_map_.end())
            {
                continue;
            }
            record_topic.type                 = "cmw_wrapper::BuiltinBuffer";
            record_topic.name                 = topic.topic_name;
            record_topic.serialization_format = std::to_string(4);
            record_topic.type_version         = "";
            if (topic.type_name == "opendds_wrapper::BuiltinBuffer" || topic.type_name == "ros_wrapper::BuiltinBuffer")
            {
                auto reader = bus_ptr_->AddReader<holo::uint8_t*>(topic.topic_name);
                auto f =
                    std::bind(&HoloRecord::onMessage, this, std::placeholders::_1, std::placeholders::_2, record_topic);
                reader.SetOnDataAvailableCallback(f);
                topic_map_.insert({topic.topic_name, record_topic});
                record_ptr_->CreateTopic(record_topic);
            }
            else
            {
                LOG(ERROR) << "Could not tell the topic with name " << topic.topic_name;
            }
        }
    }
    return true;
}  // namespace holo_cmw

void HoloRecord::onMessage(holo::uint8_t const* buffer, size_t size, const holo::bag::TopicMetadata& tmd)
{
    if (!active_record_ || spliting_)
    {
        return;
    }
    auto ser_msg = std::make_shared<holo::bag::SerializedBagMessage>();
    if (!createSerializedBagMessage(tmd.name, ser_msg))
    {
        LOG(ERROR) << "Create Serialized Bag Message Failed!!!";
        return;
    }
    try
    {
        ser_msg->serialized_data.resize(size);
        memcpy(ser_msg->serialized_data.data(), buffer, size);
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "Memcpy " << tmd.name << " Error,Continue.";
        return;
    }
    record_ptr_->Write(ser_msg);

    if (encode_ && ((tmd.name.find("camera") != std::string::npos) && (tmd.name.find("info") != std::string::npos)))
    {
        std::pair<::holo::uint32_t, ::holo::uint32_t> info_mesage = analyInfo(buffer, size);
        if (isUmbMessage())
        {
            if (charToIntLittle(buffer, 0) % extract_frame_frequency_ != 0)
            {
                return;
            }
        }
        else
        {
            if (info_mesage.second % extract_frame_frequency_ != 0)
            {
                return;
            }
        }
        LOG(WARNING) << "topic name is : " << tmd.name << " and sensors id is : " << info_mesage.first;
        if (initEncodeMap(tmd.name, info_mesage.first))
        {
            encode_topic_queue_.push(tmd.name);
        }
    }
}

bool HoloRecord::createSerializedBagMessage(const std::string& topic_name, SerializedDataPtr msg)
{
    int64_t timestamp = 0;
#if defined(HOLO_TIME_WITH_MDC_TIME)
    holo::common::Timestamp current_time(0, 0);
    if (!holo::mdc610::GetManagmentLevelTime(current_time))
    {
        LOG(ERROR) << "GetLocalTime failed";
        return false;
    }
    timestamp = current_time.ToNsec();
#else
    uint32_t sec;
    uint32_t nsec;
    if (!holo::os::GetSystemTime(sec, nsec))
    {
        LOG(ERROR) << "GetLocalTime failed";
        return false;
    }
    timestamp = holo::common::Timestamp(sec, nsec).ToNsec();
#endif
    msg->time_stamp   = timestamp;
    msg->topic_name   = topic_name;
    return true;
}

void HoloRecord::imageEncoderHandler(const holo::sensors::camera::ImagePacket& encoded_data, std::string topic_name)
{
    if (!active_record_ || spliting_)
    {
        return;
    }
    auto ser_msg = std::make_shared<holo::bag::SerializedBagMessage>();
    if (!createSerializedBagMessage(topic_name, ser_msg))
    {
        LOG(ERROR) << "Create Serialized Bag Message Failed!!!";
        return;
    }
    LOG(ERROR) << "Get Image data for encode.";
    ser_msg->serialized_data.resize(1048576);
    holo::serialization::Serializer<false, 4> obuffer(ser_msg->serialized_data.data(), 1048576);
    try
    {
        encoded_data.Serialize(obuffer);
        ser_msg->serialized_data.resize(obuffer.GetSize());
    }
    catch(const std::exception& e)
    {
        LOG(ERROR) << "Encode Image Failed!";
        return;
    }
    record_ptr_->Write(ser_msg);
}

bool HoloRecord::initEncodeMap(std::string topic_name, ::holo::uint32_t sensor_id_data)
{
    if(!encode_)
    {
        return false;
    }

    if(encode_map_.find(topic_name) != encode_map_.end())
    {
        return true;
    }

    SensorID sensor_id(sensor_id_data);

    try
    {
        LOG(WARNING) << "Enter init ipc ptr. And ipc id is " << sensor_id_data;
        std::shared_ptr<IpcType>  ipc_ptr  = std::make_shared<IpcType>(sensor_id);
        LOG(WARNING) << "Finish init ipc ptr. And ipc GetCols : " << ipc_ptr->GetCols() << " GetRows() is : " << ipc_ptr->GetRows();
        std::shared_ptr<TencBase> tenc_ptr = getTencObject(tenc_type_, ipc_ptr->GetCols(), ipc_ptr->GetRows(), 10);
        LOG(WARNING) << "Finish init TencBase.";
        tenc_ptr -> SetSender(std::bind(&HoloRecord::imageEncoderHandler, this, std::placeholders::_1, createEncodeTopicByInfo(topic_name)));
        encode_map_.insert(std::pair<std::string, std::pair<std::shared_ptr<IpcType>, std::shared_ptr<TencBase>>>(
            topic_name, std::pair<std::shared_ptr<IpcType>, std::shared_ptr<TencBase>>(ipc_ptr, tenc_ptr)));
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "Holo Record could not construction image encode map " << e.what();
    }
    return true;

}

void HoloRecord::encodeImage()
{
    while(encode_)
    {
        while(encode_)
        {
            if(encode_topic_queue_.empty())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            else
            {
                break;
            }
        }
        
        try
        {
            if(encode_topic_queue_.empty())
            {
                std::cout << "Finish encoder thread" << std::endl;
                LOG(ERROR) << "Finish encoder thread.";
                return;
            }
            auto image_map_data = encode_map_.find(encode_topic_queue_.front());
            holo::Image rgb_image;
            LOG(ERROR) << "Get msg from shm.";
            if (image_map_data->second.first->GetImageData(rgb_image))
            {
                LOG(ERROR) << "Send msg to Encode.";
                image_map_data->second.second->Encode(rgb_image);
            }
        }
        catch (std::exception& e)
        {
            LOG(ERROR) << " Encode Image Failed! Continue!";
        }
        encode_topic_queue_.pop();
    }
    std::cout << "Finish encoder thread" << std::endl;
    LOG(ERROR) << "Finish encoder thread.";
    return;
}

std::pair<::holo::uint32_t, ::holo::uint32_t> HoloRecord::analyInfo(holo::uint8_t const* buffer, size_t size)
{
    ::holo::uint64_t value = uint8_t_to_uint64_t(buffer, size);
    ::holo::uint32_t senosr_id_data = value >> 32;
    ::holo::uint32_t count = value;
    return std::make_pair(senosr_id_data, count);
}

void HoloRecord::setTencType(const std::string encode_type, const std::string image_type)
{
    if (encode_type == "RGB" && image_type == "H264")
    {
        tenc_type_ = TencType::RgbToH264;
        return;
    }
    if (encode_type == "RGB" && image_type == "H265")
    {
        tenc_type_ = TencType::RgbToH265;
        return;
    }
    if (encode_type == "NV12" && image_type == "H264")
    {
        tenc_type_ = TencType::Nv12ToH264;
        return;
    }
    if (encode_type == "NV12" && image_type == "H265")
    {
        tenc_type_ = TencType::Nv12ToH265;
        return;
    }
    throw std::runtime_error("Error parameter. encode_type must be RGB/NV12. image_type must be H264/H265");
}

std::shared_ptr<HoloRecord::TencBase> HoloRecord::getTencObject(HoloRecord::TencType tenc_type, ::holo::uint32_t cols,
                                                                ::holo::uint32_t rows, ::holo::uint32_t fps)
{
    LOG(WARNING) << "holobag record. And image tenc_type is " << tenc_type;
    if (tenc_type_ == TencType::RgbToH264)
    {
        using Tenc = holo::sensors::camera::ImageEncoder<holo::Image::Encoding::RGB, holo::sensors::camera::ImageType::H264>;
        return std::make_shared<Tenc>(cols, rows, fps);
    }
    if (tenc_type_ == TencType::RgbToH265)
    {
        using Tenc = holo::sensors::camera::ImageEncoder<holo::Image::Encoding::RGB, holo::sensors::camera::ImageType::H265>;
        return std::make_shared<Tenc>(cols, rows, fps);
    }
    if (tenc_type_ == TencType::Nv12ToH264)
    {
        using Tenc = holo::sensors::camera::ImageEncoder<holo::Image::Encoding::NV12, holo::sensors::camera::ImageType::H264>;
        return std::make_shared<Tenc>(cols, rows, fps);
    }
    if (tenc_type_ == TencType::Nv12ToH265)
    {
        using Tenc = holo::sensors::camera::ImageEncoder<holo::Image::Encoding::NV12, holo::sensors::camera::ImageType::H265>;
        return std::make_shared<Tenc>(cols, rows, fps);
    }
    using Tenc = holo::sensors::camera::ImageEncoder<holo::Image::Encoding::RGB, holo::sensors::camera::ImageType::H264>;
    return std::make_shared<Tenc>(cols, rows, fps);
}

bool HoloRecord::isUmbMessage()
{
#ifdef _MESSAGE_TYPE_ROS_AND_OPENDDS_
    return false;
#endif
    return true;
}

std::string HoloRecord::createEncodeTopicByInfo(std::string info_topic_name)
{
    std::string::size_type    pos         = info_topic_name.find("info");
    std::string               encode_name = info_topic_name.replace(pos, 4, "encoder");
    holo::bag::TopicMetadata  record_topic;

    record_topic.type = "cmw_wrapper::BuiltinBuffer";
    record_topic.name                 = encode_name;
    record_topic.serialization_format = std::to_string(4);
    record_topic.type_version = "image encode";
    topic_map_.insert({record_topic.name, record_topic});
    createTopics();
    return encode_name;
}

void HoloRecord::recodeReset(std::shared_ptr<holo::bag::Writer>& sub_record)
{
    sub_record.reset();
    LOG(INFO) << "Sub thread finish data reset.";
}

}  // namespace holo_cmw
