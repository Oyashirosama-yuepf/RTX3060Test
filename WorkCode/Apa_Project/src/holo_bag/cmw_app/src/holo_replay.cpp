/**
 * @file holo_replay.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief the implement of the holo_replay cmw app
 * @version 0.1
 * @date 2020-05-09
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#include <holo/log/hololog.h>
#include <holo_replay.h>
#include <utils.h>

#include <csignal>
#include <iostream>
#include <regex>

#define VERSION_NOT_MATCH 0
#define VERSION_NOT_MENTIONED 1
#define VERSION_MATCH 2

namespace holo_cmw
{
HoloReplay::HoloReplay(int argc, char** argv, const std::string& name, holo::uint64_t domain_id,
                       holo::bool_t show_image, const std::string& encode_type, const std::string& image_type)
  : active_replay_(true)
  , paused_(false)
  , image_play_(show_image)
  , version_check_(VERSION_NOT_MENTIONED)
  , paused_time_(0)
{
    BusType::Initialize(argc, argv, name);
    signal(SIGINT, BusType::SignalHandler);
    bus_ptr_ = std::make_shared<BusType>(domain_id, "");

    if(show_image)
    {
        setTencType(encode_type, image_type);
    }
#if defined(HOLO_PLATFORM_MDC610)
    std::string node_name = "holo_bag_mdc_decode";
#if defined(MDC610_VERSION_V430)
    Adsfi::AdsfiLogger::GetInstance().InitLogging(std::string("image_capture_") + node_name, std::string("desc"), 4, 6, std::string("./log/holo_sensors/"));
    Adsfi::AdsfiLogger::GetInstance().CreateLogger(std::string("image_capture_") + node_name,std::string("desc"), 4);
#else
    Adsfi::AdsfiLogger::GetInstance().InitLogging(std::string("image_capture_") + node_name, std::string("desc"), static_cast<Adsfi::HafLogLevelType>(4), static_cast<Adsfi::HafLogModeType>(6), std::string("./log/holo_sensors/"));
    Adsfi::AdsfiLogger::GetInstance().CreateLogger(std::string("image_capture_") + node_name,std::string("desc"), static_cast<Adsfi::HafLogLevelType>(4));
#endif
#endif
}

HoloReplay::~HoloReplay()
{
    image_play_ = false;
    decode_thread_pool_.reset();
    active_replay_ = false;
}

bool HoloReplay::SetUp(const std::string& file_name)
{
    if (!initReader(file_name))
    {
        LOG(ERROR) << "Could not init reader!";
        return false;
    }

    if (!initPublisher())
    {
        LOG(ERROR) << "Could not init publisher!";
        return false;
    }

    if (image_play_)
    {
        initDecoderThread();
    }

    command_thread_ = std::shared_ptr<std::thread>(new std::thread(std::bind(&HoloReplay::getCommand, this)));
    return true;
}

void HoloReplay::SetUserOptions(holo::float64_t skip_time, holo::float64_t duration, holo::float32_t rate, holo::bool_t accept)
{
    if (skip_time >= 0.0)
    {
        options_.skip_time_ = skip_time;
        if (bag_duration_ - skip_time <= 0)
        {
            throw std::runtime_error("Too large skip time, bag duration is " + std::to_string(bag_duration_));
        }
        bag_duration_ -= skip_time;
    }

    if (duration > 0.0)
    {
        if (duration > bag_duration_)
        {
            throw std::runtime_error("Wrong end time, skip time is " + std::to_string(skip_time) + " bag duratuin is " +
                                     std::to_string(bag_duration_));
        }
        bag_duration_ = duration;
    }
    else if (duration < 0)
    {
        throw std::runtime_error("Parameter error: -d " + std::to_string(duration));
    }

    if (rate > 0.0)
    {
        options_.rate_ = rate;
    }
    accept_or_ignore_ = accept;
}

void HoloReplay::Play()
{
    if (version_check_ == VERSION_NOT_MATCH)
    {
        LOG(ERROR) << " holobag version not matched, please change the version!!";
        return;
    }
    else if (version_check_ == VERSION_NOT_MENTIONED)
    {
        LOG(WARNING) << "No holobag version get,continue play may core dump or no msg out!!";
    }

    PlayOptions option      = options_;
    storage_loading_future_ = std::async(std::launch::async, [this, option]() { loadStorageContent(option); });

    // set_cmw_spin();
    waitForFilledQueue(options_);
    playMessagesFromQueue(options_);
    std::cout << "\n Done for replay" << std::endl;

    BusType::SignalHandler(SIGINT);  // set a flag to stop playing
    command_thread_->join();         // wait command thread exit
}

void HoloReplay::SetIgnoredTopics(const std::vector<std::string>& ignored_topics, std::size_t vector_size)
{
    ignored_topics_.resize(vector_size);
    ignored_topics_ = ignored_topics;
}

bool HoloReplay::initPublisher()
{
    holo::bool_t intialized = true;
    for (auto& it : replay_map_)
    {
        // Common
        if (it.second.type == "cmw_wrapper::BuiltinBuffer" || it.second.type == "umb_wrapper::BuiltinBuffer" ||
            it.second.type == "ros_wrapper::BuiltinBuffer" || it.second.type == "opendds_wrapper::BuiltinBuffer")
        {
            if((it.first.find("camera") != std::string::npos) && (it.first.find("info") != std::string::npos))
            {
                bus_ptr_->AddWriter<::holo::uint64_t>(it.first);
                continue;
            }
            bus_ptr_->AddWriter<holo::uint8_t*>(it.first);
        }
        else
        {
            intialized = false;
            LOG(ERROR) << "Could not tell the topic type which is " << it.second.name;
        }
    }
    return intialized;
}

bool HoloReplay::initReader(const std::string& file_name)
{
    replay_ptr_ = std::make_shared<holo::bag::Reader>();
    if (replay_ptr_)
    {
        if (file_name.empty())
        {
            LOG(ERROR) << "file name is empty!";
            return false;
        }
        else
        {
            holo::bag::StorageOptions option;
            option.uri = file_name;
            replay_ptr_->Open(option);
            getBagMetadataMsg();
        }
    }
    return true;
}

void HoloReplay::getBagMetadataMsg()
{
    auto metadata = replay_ptr_->GetMetadata();
    for (auto& sys_data : metadata.version_data)
    {
        if (sys_data.category == "holobag")
        {
            if (sys_data.version == "base_version")
            {
                version_check_ = VERSION_NOT_MATCH;
            }
            else if (sys_data.version == "cmw_version")
            {
                version_check_ = VERSION_MATCH;
            }
        }
    }
    for (auto& topic : metadata.topics_with_message_count)
    {
        replay_map_.insert(std::make_pair(topic.topic_metadata.name, topic.topic_metadata));
    }

    auto m_seconds = std::chrono::duration_cast<std::chrono::nanoseconds>(metadata.duration);
    bag_duration_  = m_seconds.count() / 1000000000.0;

    auto start_time = metadata.starting_time.time_since_epoch();
    auto start_ms   = std::chrono::duration_cast<std::chrono::nanoseconds>(start_time);
    bag_start_time_ = start_ms.count() / 1000000000.0;
}

void HoloReplay::getCommand()
{
    init_keyboard();
    printf("--press SPACE key to toggle playback, press 'q' or ctrl+c to exit.\n\n");
    while (BusType::IsRunning())
    {
        int i = keyboard_hit();
        if (i != 0)  // so we got some user input
        {
            char ch = fgetc(stdin);
            // printf("user hit %c. \n", ch);
            if (ch == 'q')
                BusType::SignalHandler(SIGINT);  // printf("\n--user press 'q'");
            else if (ch == 32)                   // space key to toggle playing
                paused_ = !paused_;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    close_keyboard();
}

void HoloReplay::loadStorageContent(const PlayOptions& options)
{
    holo::int64_t                time_first_message = 0;
    holo::bag::ReplayableMessage message;
    if (replay_ptr_ == nullptr)
    {
        LOG(ERROR) << "Please init replay ptr first!";
        return;
    }

    if (replay_ptr_->HasNext())
    {
        message.message_          = replay_ptr_->ReadNext();
        message.time_since_start_ = 0;
        holo::int64_t skip_nano   = (holo::int64_t)(options.skip_time_ * 1000000000);
        time_first_message        = message.message_->time_stamp + skip_nano;
    }
    auto queue_lower_boundary =
        static_cast<size_t>(options.read_ahead_queue_size_ * options_.read_ahead_lower_bound_percentage_);
    auto queue_upper_boundary = options.read_ahead_queue_size_;

    while (BusType::IsRunning())
    {
        if (message_queue_.size_approx() < queue_lower_boundary)
        {
            try
            {
                enqueueUpToBoundary(time_first_message, queue_upper_boundary);
            }
            catch(holo::bag::SqliteException const&)
            {
                break;
            }
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}

void HoloReplay::enqueueUpToBoundary(holo::int64_t& time_first_message, uint64_t boundary)
{
    // holo::bag::ReplayableMessage message;
    while (message_queue_.size_approx() < boundary)
    {
        enque_temp_message_.message_ = replay_ptr_->ReadNext();
        if (enque_temp_message_.message_->time_stamp <= time_first_message)
        {
            continue;
        }
        enque_temp_message_.time_since_start_ = enque_temp_message_.message_->time_stamp - time_first_message;
        message_queue_.enqueue(enque_temp_message_);
    }
}

void HoloReplay::waitForFilledQueue(const PlayOptions& options) const
{
    while (message_queue_.size_approx() <
               options.read_ahead_queue_size_ * options_.read_ahead_lower_bound_percentage_ &&
           !isStorageCompletelyLoaded())
    {
        std::this_thread::sleep_for(options_.queue_read_wait_period_);
    }
}

void HoloReplay::playMessagesFromQueue(const PlayOptions& options)
{
    start_time_ = std::chrono::system_clock::now();
    do
    {
        playMessagesUntilQueueEmpty(options);
        if (!isStorageCompletelyLoaded())
        {
            LOG(WARNING) << "Message queue starved. Messages will be delayed. Consider "
                            "increasing the --read-ahead-queue-size option.";
        }
    } while (!isStorageCompletelyLoaded());
}

bool HoloReplay::isStorageCompletelyLoaded() const
{
    if (storage_loading_future_.valid() &&
        storage_loading_future_.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
    {
        storage_loading_future_.get();
    }
    return !storage_loading_future_.valid();
}

void HoloReplay::playMessagesUntilQueueEmpty(const PlayOptions& options)
{
    float rate = 1.0;
    // Use rate if in valid range
    if (options.rate_ > 0.0)
    {
        rate = options.rate_;
    }
    while (BusType::IsRunning())
    {
        if (paused_)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            paused_time_ += 10;
            continue;
        }
        if (!message_queue_.try_dequeue(deque_temp_message_))
        {
            break;
        }
        std::this_thread::sleep_until(start_time_ + std::chrono::duration_cast<std::chrono::nanoseconds>(
                                      1.0 / rate * std::chrono::nanoseconds(deque_temp_message_.time_since_start_) +
                                      std::chrono::milliseconds(paused_time_)));
        publishMsg(deque_temp_message_.message_);
        holo::float64_t current_stamp = deque_temp_message_.message_->time_stamp / 1000000000.0;
        holo::float64_t delt;
        delt = current_stamp - bag_start_time_ - options_.skip_time_;
        showMsg(current_stamp, delt);
        if ((delt > bag_duration_))
        {
            BusType::SignalHandler(SIGINT);
        }
    }
}

void HoloReplay::publishMsg(const std::shared_ptr<holo::bag::SerializedBagMessage> msg)
{
    auto it = replay_map_.find(msg->topic_name);
    if (it == replay_map_.end())
    {
        LOG(WARNING) << "Unknown msg topic：" << msg->topic_name;
        return;
    }

    if (isIgnoredTopic(msg->topic_name))
    {
        LOG(INFO) << msg->topic_name << " not to play" <<std::endl;
        return;
    }

    LOG(INFO) << "Start pub " << msg->topic_name;

    auto& buffer = msg->serialized_data;

    if ((msg->topic_name.find("camera") != std::string::npos) && (msg->topic_name.find("info") != std::string::npos))
    {
        if (!image_play_)
        {
            return;
        }
        std::string sub_string = replaceTopic(msg->topic_name, "info", "", true);
        if (image_decoder_.find(sub_string) != image_decoder_.end())
        {
            return;
        }
        ::holo::uint8_t*                  info_buff = msg->serialized_data.data();
        size_t                            info_size = msg->serialized_data.size();
        ::holo::uint64_t                  info_data = uint8_t_to_uint64_t(info_buff, info_size);

        holo::sensors::camera::ImagePacket compress_data;
        std::shared_ptr<uint8_t> decode_buffer = {new uint8_t[::holo::sensors::camera::IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>()};
        std::memset(decode_buffer.get(), 0, ::holo::sensors::camera::IMAGE_ENCODE_SIZE_MAX);
        compress_data.data = decode_buffer.get();

        DecodeSpace decode_space = std::pair<holo::sensors::camera::ImagePacket, std::shared_ptr<uint8_t>>(compress_data, decode_buffer);
        DeCodeMap decode_map = std::pair<::holo::uint32_t, std::pair<std::shared_ptr<TdecBase>, DecodeSpace>>(
            info_data >> 32, std::pair<std::shared_ptr<TdecBase>, DecodeSpace>(nullptr, decode_space));
        DecodeQueue                       decode_queue;
        std::pair<DeCodeMap, DecodeQueue> decode_data = std::pair<DeCodeMap, DecodeQueue>(decode_map, decode_queue);

        image_decoder_.insert(std::pair<std::string, std::pair<DeCodeMap, DecodeQueue>>(sub_string, decode_data));
        return;
    }

    if((msg->topic_name.find("camera") != std::string::npos) && (msg->topic_name.find("encoder") != std::string::npos))
    {
        if (image_play_)
        {
            std::string sub_string = replaceTopic(msg->topic_name, "encoder", "", true);
            if(image_decoder_.find(sub_string) == image_decoder_.end())
            {
                return;
            }
            image_decoder_[sub_string].second.push(buffer);
            return;
        }
    }
    BusType::WriterType<holo::uint8_t*> writer = bus_ptr_->GetWriter<holo::uint8_t*>(msg->topic_name);
    writer.Write(buffer.data(), buffer.size());

}

void HoloReplay::showMsg(const holo::float64_t current_stamp, holo::float64_t delt)
{
    std::string result;
    if (paused_)
    {
        result.append("[PAUSED ]  Bag Time: ");
    }
    else
    {
        result.append("[RUNNING]  Bag Time: ");
    }
    result.append(std::to_string(current_stamp));
    result.append("   Duration: ");

    delt = (delt < 0) ? 0 : delt;
    result.append(std::to_string(delt));
    result.append(" / ");
    result.append(std::to_string(bag_duration_));
    printf("%s\r", result.c_str());
    fflush(stdout);
}

bool HoloReplay::isIgnoredTopic(std::string topic_name)
{
    holo::bool_t finded = std::find(ignored_topics_.begin(), ignored_topics_.end(), topic_name) != ignored_topics_.end();
    LOG(INFO) << "Finded = " << finded << " , Accept = " << accept_or_ignore_
              << " Is_Ignore_Topic = " << (finded != accept_or_ignore_);
    return finded != accept_or_ignore_;
}

std::string HoloReplay::replaceTopic(std::string topic_name, std::string find_data, std::string replace_data, bool ifUseRe)
{
    std::string sub_data = "";
    if(ifUseRe)
    {
        std::regex  reg("[^\\/:*?<>|\r\n]+$");
        std::smatch smat;
        
        if (std::regex_search(topic_name, smat, reg))
        {
            sub_data                   = smat.str();
            std::string::size_type pos = sub_data.find(find_data);
            sub_data                   = sub_data.replace(pos, find_data.length(), replace_data);
        }
        return sub_data;
    }
    std::string::size_type pos = topic_name.find(find_data);
    sub_data                   = topic_name.replace(pos, find_data.length(), replace_data);
    return sub_data;
}

void HoloReplay::imageDecode(std::string topic_name)
{
    std::string sub_string = replaceTopic(topic_name, "encoder", "", true);
    while(image_play_)
    {
        while(image_play_)
        {
            if (image_decoder_.count(sub_string) <= 0 || image_decoder_[sub_string].second.empty())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            else
            {
                break;
            }
        }

        if (image_decoder_[sub_string].second.empty())
        {
            std::cout << "Finish decode thread." << std::endl;
            return;
        }

        holo::serialization::Deserializer<false, 4> ibuffer(image_decoder_[sub_string].second.front().data(),
                                                            image_decoder_[sub_string].second.front().size());
        if (image_decoder_.count(sub_string) > 0 && image_decoder_[sub_string].first.second.second.first.Deserialize(ibuffer))
        {
            ::holo::uint32_t cols = image_decoder_[sub_string].first.second.second.first.cols;
            ::holo::uint32_t rows = image_decoder_[sub_string].first.second.second.first.rows;
            if (image_decoder_[sub_string].first.second.first == nullptr)
            {
                std::shared_ptr<TdecBase> decoser_ptr =
                    getTdecObject(tdec_type_, image_decoder_[sub_string].first.first, cols, rows, 10);
                image_decoder_[sub_string].first.second.first = decoser_ptr;
                decoser_ptr->SetImageCounterCallback(std::bind(&HoloReplay::sendInfoMessage, this,
                                                               std::placeholders::_1,
                                                               image_decoder_[sub_string].first.first, topic_name));
            }
            image_decoder_[sub_string].first.second.first->Decode(image_decoder_[sub_string].first.second.second.first);
        }
        image_decoder_[sub_string].second.pop();
    }
    std::cout << "Finish decode thread." << std::endl;
    return;
}

void HoloReplay::sendInfoMessage(::holo::uint32_t counter, ::holo::uint32_t sensor_id, std::string topic_name)
{
    std::string                           info_string = replaceTopic(topic_name, "encoder", "info", false);
    BusType::WriterType<::holo::uint64_t> writer      = bus_ptr_->GetWriter<::holo::uint64_t>(info_string);
    ::holo::uint64_t                      info_data   = (static_cast<::holo::uint64_t>(sensor_id) << 32) + counter;
    writer.Write(info_data);
}

void HoloReplay::initDecoderThread()
{
    if(replay_ptr_ == nullptr)
    {
        LOG(ERROR) << "init sub decoder thread error";
        return;
    }

    std::vector<holo::bag::TopicMetadata> topic_list = replay_ptr_->GetAllTopicsAndTypes();
    std::vector<std::string>              encoder_topic_list;
    for (size_t index = 0; index < topic_list.size(); ++index)
    {
        if ((topic_list[index].name.find("camera") != std::string::npos) &&
            (topic_list[index].name.find("encoder") != std::string::npos))
        {
            encoder_topic_list.push_back(topic_list[index].name);
            LOG(INFO) << "Topic " << topic_list[index].name << " push.";
        }
    }
    decode_thread_pool_ = std::shared_ptr<HoloThreadPool>(new HoloThreadPool(encoder_topic_list.size()));
    for (size_t index = 0; index < encoder_topic_list.size(); ++index)
    {
        auto f = std::bind(&HoloReplay::imageDecode, this, encoder_topic_list[index]);
        decode_thread_pool_->EnQueue(f);
    }
}

void HoloReplay::setTencType(const std::string decode_type, const std::string image_type)
{
    if (decode_type == "RGB" && image_type == "H264")
    {
        tdec_type_ = TdecType::RgbToH264;
        return;
    }
    if (decode_type == "RGB" && image_type == "H265")
    {
        tdec_type_ = TdecType::RgbToH265;
        return;
    }
    if (decode_type == "NV12" && image_type == "H264")
    {
        tdec_type_ = TdecType::Nv12ToH264;
        return;
    }
    if (decode_type == "NV12" && image_type == "H265")
    {
        tdec_type_ = TdecType::Nv12ToH265;
        return;
    }
    if (decode_type == "BGR" && image_type == "H264")
    {
        tdec_type_ = TdecType::BgrToH264;
        return;
    }
    if (decode_type == "BGR" && image_type == "H265")
    {
        tdec_type_ = TdecType::BgrToH265;
        return;
    }
    throw std::runtime_error("Error parameter. decode_type must be RGB/NV12/BGR. image_type must be H264/H265");
}

std::shared_ptr<HoloReplay::TdecBase> HoloReplay::getTdecObject(HoloReplay::TdecType tdec_type, ::holo::uint32_t sensors_id,
                                                                ::holo::uint32_t cols, ::holo::uint32_t rows, ::holo::uint32_t fps)
{
    LOG(INFO) << "holobag paly. And image tdec_type is " << tdec_type;
    if (tdec_type_ == TdecType::RgbToH264)
    {
        using Tdec = holo::sensors::camera::H26xDecoder<holo::sensors::camera::ImageType::H264, holo::Image::Encoding::RGB>;
        return std::make_shared<Tdec>(sensors_id, cols, rows, fps, false);
    }
    if (tdec_type_ == TdecType::RgbToH265)
    {
        using Tdec = holo::sensors::camera::H26xDecoder<holo::sensors::camera::ImageType::H265, holo::Image::Encoding::RGB>;
        return std::make_shared<Tdec>(sensors_id, cols, rows, fps, false);
    }
    if (tdec_type_ == TdecType::Nv12ToH264)
    {
        using Tdec = holo::sensors::camera::H26xDecoder<holo::sensors::camera::ImageType::H264, holo::Image::Encoding::NV12>;
        return std::make_shared<Tdec>(sensors_id, cols, rows, fps, false);
    }
    if (tdec_type_ == TdecType::Nv12ToH265)
    {
        using Tdec = holo::sensors::camera::H26xDecoder<holo::sensors::camera::ImageType::H265, holo::Image::Encoding::NV12>;
        return std::make_shared<Tdec>(sensors_id, cols, rows, fps, false);
    }
    if (tdec_type_ == TdecType::BgrToH264)
    {
        using Tdec = holo::sensors::camera::H26xDecoder<holo::sensors::camera::ImageType::H264, holo::Image::Encoding::BGR>;
        return std::make_shared<Tdec>(sensors_id, cols, rows, fps, false);
    }
    if (tdec_type_ == TdecType::BgrToH265)
    {
        using Tdec = holo::sensors::camera::H26xDecoder<holo::sensors::camera::ImageType::H265, holo::Image::Encoding::BGR>;
        return std::make_shared<Tdec>(sensors_id, cols, rows, fps, false);
    }
    using Tdec = holo::sensors::camera::H26xDecoder<holo::sensors::camera::ImageType::H264, holo::Image::Encoding::RGB>;
    return std::make_shared<Tdec>(sensors_id, cols, rows, fps, false);
}

}  // namespace holo_cmw
