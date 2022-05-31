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
#include <glog/logging.h>
#include <holo_msg_type_string.h>
#include <include/holo_replay.h>
#include <include/utils.h>

#define VERSION_NOT_MATCH 0
#define VERSION_NOT_MENTIONED 1
#define VERSION_MATCH 2

namespace holo_cmw
{
HoloReplay::HoloReplay(int argc, char** argv, const std::string& name)
  : cmw_(argc, argv, name)
  , cmw_encoder_(argc, argv, "1")
  , active_replay_(true)
  , paused_(false)
  , version_check_(VERSION_NOT_MENTIONED)
  , paused_time_(0)
  , deserializer_(std::make_shared<holo_cmw::HoloMsgSerialization>())
{
}

HoloReplay::~HoloReplay()
{
    active_replay_ = false;
}

bool HoloReplay::SetUp(const std::string& config_file, const std::string& file_name)
{
    if (!loadConfigFile(config_file))
    {
        LOG(ERROR) << "Could not load config file " << config_file;
        return false;
    }

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

    return true;
}

void HoloReplay::SetUserOptions(holo::float64_t skip_time, holo::float64_t duration, holo::float32_t rate)
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
        if (duration + skip_time > bag_duration_)
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

    set_cmw_spin();
    waitForFilledQueue(options_);
    playMessagesFromQueue(options_);
    std::cout << "\n Done for replay" << std::endl;

    set_stop_flag();          // set a flag to stop playing
    end_callback_(2);
}

bool HoloReplay::loadConfigFile(const std::string& config_file)
{
    std::string file_path;
    std::string topic_type_file;
    if (config_file.empty())
    {
        file_path = holo::GetHoloConfigRootDirectory() + "/holo_bag/app_config/holo_replay_app.yaml";
    }
    else
    {
        file_path = config_file;
    }
    try
    {
        holo::yaml::Node node                       = holo::yaml::LoadFile(file_path);
        options_.read_ahead_queue_size_             = node["read_ahead_queue_size"].as<holo::uint32_t>();
        options_.read_ahead_lower_bound_percentage_ = node["read_ahead_lower_bound_percentage"].as<holo::float64_t>();
        holo::uint32_t wait_time                    = node["queue_read_wait_period"].as<holo::uint32_t>();
        options_.queue_read_wait_period_            = std::chrono::milliseconds(wait_time);
        options_.rate_                              = node["rate"].as<holo::float32_t>();
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "Holo Record could not load config file: " << e.what();
        return false;
    }
    return true;
}

bool HoloReplay::initPublisher()
{
    holo::bool_t intialized = true;
    for (auto& it : replay_map_)
    {
        // Common
        if (it.second.tmd_.type == "ChassisStateTopicType" ||
            it.second.tmd_.type == "holo_cmw::dds::common::ChassisState")
        {
            holo_cmw::CMW::ChassisStatePublisher* publisher = new holo_cmw::CMW::ChassisStatePublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::ChassisStateTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "ControlCommandTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::common::ControlCommand")
        {
            holo_cmw::CMW::ControlCommandPublisher* publisher = new holo_cmw::CMW::ControlCommandPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::ControlCommandTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "ControlLoggerTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::common::ControlLogger")
        {
            holo_cmw::CMW::ControlLoggerPublisher* publisher = new holo_cmw::CMW::ControlLoggerPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::ControlLoggerTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "CpuStatesTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::common::CpuStates")
        {
            holo_cmw::CMW::CpuStatesPublisher* publisher = new holo_cmw::CMW::CpuStatesPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::CpuStatesTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "DataBufferTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::common::DataBuffer")
        {
            holo_cmw::CMW::DataBufferPublisher* publisher = new holo_cmw::CMW::DataBufferPublisher();

            auto st = it.first.find("encoder");
            if (st == std::string::npos)
            {
                *publisher = cmw_.AddPublisher<holo_cmw::CMW::DataBufferTopicType>(it.first);
            }
            else
            {
                *publisher = cmw_encoder_.AddPublisher<holo_cmw::CMW::DataBufferTopicType>(it.first);
            }
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "GnssPositionTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::common::GnssPosition")
        {
            holo_cmw::CMW::GnssPositionPublisher* publisher = new holo_cmw::CMW::GnssPositionPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::GnssPositionTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "GnssPvtTopicType" || it.second.tmd_.type == "holo_cmw::dds::common::GnssPvt")
        {
            holo_cmw::CMW::GnssPvtPublisher* publisher = new holo_cmw::CMW::GnssPvtPublisher();
            *publisher                                 = cmw_.AddPublisher<holo_cmw::CMW::GnssPvtTopicType>(it.first);
            it.second.publisher_                       = publisher;
        }
        else if (it.second.tmd_.type == "ImudTopicType" || it.second.tmd_.type == "holo_cmw::dds::common::Imud")
        {
            holo_cmw::CMW::ImudPublisher* publisher = new holo_cmw::CMW::ImudPublisher();
            *publisher                              = cmw_.AddPublisher<holo_cmw::CMW::ImudTopicType>(it.first);
            it.second.publisher_                    = publisher;
        }
        else if (it.second.tmd_.type == "LaneSceneTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::common::LaneScene")
        {
            holo_cmw::CMW::LaneScenePublisher* publisher = new holo_cmw::CMW::LaneScenePublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::LaneSceneTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "OdmStatesTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::common::OdmStates")
        {
            holo_cmw::CMW::OdmStatesPublisher* publisher = new holo_cmw::CMW::OdmStatesPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::OdmStatesTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "OdometrydTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::common::Odometryd")
        {
            holo_cmw::CMW::OdometrydPublisher* publisher = new holo_cmw::CMW::OdometrydPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::OdometrydTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "PathdTopicType" || it.second.tmd_.type == "holo_cmw::dds::common::Pathd")
        {
            holo_cmw::CMW::PathdPublisher* publisher = new holo_cmw::CMW::PathdPublisher();
            *publisher                               = cmw_.AddPublisher<holo_cmw::CMW::PathdTopicType>(it.first);
            it.second.publisher_                     = publisher;
        }
        else if (it.second.tmd_.type == "RoadFrameTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::common::RoadFrame")
        {
            holo_cmw::CMW::RoadFramePublisher* publisher = new holo_cmw::CMW::RoadFramePublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::RoadFrameTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "RoadFrame2TopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::common::RoadFrame2")
        {
            holo_cmw::CMW::RoadFrame2Publisher* publisher = new holo_cmw::CMW::RoadFrame2Publisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::RoadFrame2TopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "StringDataTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::example::StringData")
        {
            holo_cmw::CMW::StringDataPublisher* publisher = new holo_cmw::CMW::StringDataPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::StringDataTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "UInt32TopicType" || it.second.tmd_.type == "holo_cmw::dds::common::UInt32")
        {
            holo_cmw::CMW::UInt32Publisher* publisher = new holo_cmw::CMW::UInt32Publisher();
            *publisher                                = cmw_.AddPublisher<holo_cmw::CMW::UInt32TopicType>(it.first);
            it.second.publisher_                      = publisher;
        }
        else if (it.second.tmd_.type == "VehicleBodyStateTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::common::VehicleBodyState")
        {
            holo_cmw::CMW::VehicleBodyStatePublisher* publisher = new holo_cmw::CMW::VehicleBodyStatePublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::VehicleBodyStateTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "WeatherTopicType" || it.second.tmd_.type == "holo_cmw::dds::common::Weather")
        {
            holo_cmw::CMW::WeatherPublisher* publisher = new holo_cmw::CMW::WeatherPublisher();
            *publisher                                 = cmw_.AddPublisher<holo_cmw::CMW::WeatherTopicType>(it.first);
            it.second.publisher_                       = publisher;
        }
        else if (it.second.tmd_.type == "WeatherValueTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::sensors::WeatherValue")
        {
            holo_cmw::CMW::WeatherValuePublisher* publisher = new holo_cmw::CMW::WeatherValuePublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::WeatherValueTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        // map
        else if (it.second.tmd_.type == "AdviceTopicType" || it.second.tmd_.type == "holo_cmw::dds::map::Advice")
        {
            holo_cmw::CMW::AdvicePublisher* publisher = new holo_cmw::CMW::AdvicePublisher();
            *publisher                                = cmw_.AddPublisher<holo_cmw::CMW::AdviceTopicType>(it.first);
            it.second.publisher_                      = publisher;
        }
        else if (it.second.tmd_.type == "RoadRefPointTypeIntervalsTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::map::RoadRefPointTypeIntervals")
        {
            holo_cmw::CMW::RoadRefPointTypeIntervalsPublisher* publisher =
                new holo_cmw::CMW::RoadRefPointTypeIntervalsPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::RoadRefPointTypeIntervalsTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        // Obstacle
        else if (it.second.tmd_.type == "ObstacleGeneralListTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::obstacle::ObstacleGeneralList")
        {
            holo_cmw::CMW::ObstacleGeneralListPublisher* publisher = new holo_cmw::CMW::ObstacleGeneralListPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::ObstacleGeneralListTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "ObstacleRadarListTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::obstacle::ObstacleRadarList")
        {
            holo_cmw::CMW::ObstacleRadarListPublisher* publisher = new holo_cmw::CMW::ObstacleRadarListPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::ObstacleRadarListTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else if (it.second.tmd_.type == "ObstacleVisionListTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::obstacle::ObstacleVisionList")
        {
            holo_cmw::CMW::ObstacleVisionListPublisher* publisher = new holo_cmw::CMW::ObstacleVisionListPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::ObstacleVisionListTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        // planning
        else if (it.second.tmd_.type == "PlanningStateTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::planning::PlanningState")
        {
            holo_cmw::CMW::PlanningStatePublisher* publisher = new holo_cmw::CMW::PlanningStatePublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::PlanningStateTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        // prediction
        else if (it.second.tmd_.type == "IntentionsTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::prediction::Intentions")
        {
            holo_cmw::CMW::IntentionsPublisher* publisher = new holo_cmw::CMW::IntentionsPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::IntentionsTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        // vision
        else if (it.second.tmd_.type == "ImageObjectsKeyPoint2fTopicType" ||
                 it.second.tmd_.type == "holo_cmw::dds::vision::ImageObjectsKeyPoint2f")
        {
            holo_cmw::CMW::ImageObjectsKeyPoint2fPublisher* publisher =
                new holo_cmw::CMW::ImageObjectsKeyPoint2fPublisher();
            *publisher           = cmw_.AddPublisher<holo_cmw::CMW::ImageObjectsKeyPoint2fTopicType>(it.first);
            it.second.publisher_ = publisher;
        }
        else
        {
            intialized = false;
            LOG(ERROR) << "Could not tell the topic type which is " << it.second.tmd_.type
                       << ", this publisher will not be initialized!";
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
        std::string  type_version;
        holo::bool_t matched = true;
        if (!holo_cmw::HoloMsgTypeString::GetMsgTypeString(topic.topic_metadata.type, type_version))
        {
            LOG(ERROR) << "Could not get type version with the name " << topic.topic_metadata.type;
            matched = false;
        }
        if (type_version != topic.topic_metadata.type_version)
        {
            LOG(ERROR) << "the topic type " << topic.topic_metadata.type
                       << " version is not matched with current system: \n"
                       << "bag type version: " << topic.topic_metadata.type_version
                       << "     ,length = " << topic.topic_metadata.type_version.size() << " \n"
                       << "sys type version: " << type_version << "     ,length = " << type_version.size();
            matched = false;
        }
        ReplayMetadata rmd(topic.topic_metadata, nullptr, matched);
        replay_map_.insert(std::make_pair(topic.topic_metadata.name, rmd));
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
    while (is_on_playing())
    {
        int i = keyboard_hit();
        if (i != 0)  // so we got some user input
        {
            char ch = fgetc(stdin);
            // printf("user hit %c. \n", ch);
            if (ch == 'q')
            {
                set_stop_flag();  // printf("\n--user press 'q'");
            }
            else if (ch == 32)    // space key to toggle playing
                paused_ = !paused_;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    close_keyboard();
}

void HoloReplay::loadStorageContent(const PlayOptions& options)
{
    holo::int64_t                time_first_message;
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

    while (is_on_playing() && replay_ptr_->HasNext())
    {
        if (message_queue_.size_approx() < queue_lower_boundary)
        {
            enqueueUpToBoundary(time_first_message, queue_upper_boundary);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}

void HoloReplay::enqueueUpToBoundary(holo::int64_t& time_first_message, uint64_t boundary)
{
    holo::bag::ReplayableMessage message;
    for (size_t i = message_queue_.size_approx(); i < boundary; i++)
    {
        if (!replay_ptr_->HasNext())
        {
            break;
        }
        message.message_ = replay_ptr_->ReadNext();
        if (message.message_->time_stamp <= time_first_message)
        {
            continue;
        }
        message.time_since_start_ = message.message_->time_stamp - time_first_message;
        message_queue_.enqueue(message);
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
    holo::bag::ReplayableMessage message;

    float rate = 1.0;
    // Use rate if in valid range
    if (options.rate_ > 0.0)
    {
        rate = options.rate_;
    }
    while (is_on_playing())
    {
        if (paused_)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            paused_time_ += 10;
            continue;
        }
        if (!message_queue_.try_dequeue(message))
        {
            break;
        }
        holo::float64_t current_stamp = message.message_->time_stamp / 1000000000.0;
        holo::float64_t delt;
        delt = current_stamp - bag_start_time_;
        showMsg(current_stamp,delt);
        publishMsg(message.message_);
        std::this_thread::sleep_until(start_time_ +
                                      std::chrono::duration_cast<std::chrono::nanoseconds>(
                                          1.0 / rate * std::chrono::nanoseconds(message.time_since_start_) +
                                          std::chrono::milliseconds(paused_time_)));

        if ((delt > bag_duration_ + options_.skip_time_))
        {
            set_stop_flag();
            end_callback_(delt);
        }
        time_callback_(delt);
        rate = options.rate_;
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
    if (it->second.publisher_ == nullptr)
    {
        LOG(WARNING) << "Publisher is not initialized: " << msg->topic_name;
        return;
    }
    if (!it->second.version_matched_)
    {
        LOG(INFO) << "Jump the unmatched message: " << it->second.tmd_.name;
        return;
    }
    LOG(INFO) << "Start pub " << msg->topic_name;

    auto&                               buffer = msg->serialized_data;
    holo::utils::Deserializer<false, 4> ibuffer(buffer);
    // Common
    if (it->second.tmd_.type == "ChassisStateTopicType" ||
        it->second.tmd_.type == "holo_cmw::dds::common::ChassisState")
    {
        holo_cmw::CMW::ChassisStateTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }
        holo_cmw::CMW::ChassisStatePublisher* publisher =
            (holo_cmw::CMW::ChassisStatePublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "ControlCommandTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::common::ControlCommand")
    {
        holo_cmw::CMW::ControlCommandTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::ControlCommandPublisher* publisher =
            (holo_cmw::CMW::ControlCommandPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "ControlLoggerTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::common::ControlLogger")
    {
        holo_cmw::CMW::ControlLoggerTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::ControlLoggerPublisher* publisher =
            (holo_cmw::CMW::ControlLoggerPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "CpuStatesTopicType" || it->second.tmd_.type == "holo_cmw::dds::common::CpuStates")
    {
        holo_cmw::CMW::CpuStatesTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::CpuStatesPublisher* publisher = (holo_cmw::CMW::CpuStatesPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "DataBufferTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::common::DataBuffer")
    {
        holo_cmw::CMW::DataBufferTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::DataBufferPublisher* publisher = (holo_cmw::CMW::DataBufferPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "GnssPositionTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::common::GnssPosition")
    {
        holo_cmw::CMW::GnssPositionTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::GnssPositionPublisher* publisher =
            (holo_cmw::CMW::GnssPositionPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "GnssPvtTopicType" || it->second.tmd_.type == "holo_cmw::dds::common::GnssPvt")
    {
        holo_cmw::CMW::GnssPvtTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::GnssPvtPublisher* publisher = (holo_cmw::CMW::GnssPvtPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "ImudTopicType" || it->second.tmd_.type == "holo_cmw::dds::common::Imud")
    {
        holo_cmw::CMW::ImudTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::ImudPublisher* publisher = (holo_cmw::CMW::ImudPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "LaneSceneTopicType" || it->second.tmd_.type == "holo_cmw::dds::common::LaneScene")
    {
        holo_cmw::CMW::LaneSceneTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::LaneScenePublisher* publisher = (holo_cmw::CMW::LaneScenePublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "OdmStatesTopicType" || it->second.tmd_.type == "holo_cmw::dds::common::OdmStates")
    {
        holo_cmw::CMW::OdmStatesTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::OdmStatesPublisher* publisher = (holo_cmw::CMW::OdmStatesPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "OdometrydTopicType" || it->second.tmd_.type == "holo_cmw::dds::common::Odometryd")
    {
        holo_cmw::CMW::OdometrydTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::OdometrydPublisher* publisher = (holo_cmw::CMW::OdometrydPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "PathdTopicType" || it->second.tmd_.type == "holo_cmw::dds::common::Pathd")
    {
        holo_cmw::CMW::PathdTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::PathdPublisher* publisher = (holo_cmw::CMW::PathdPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "RoadFrame2TopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::common::RoadFrame2")
    {
        holo_cmw::CMW::RoadFrame2TopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::RoadFrame2Publisher* publisher = (holo_cmw::CMW::RoadFrame2Publisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "StringDataTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::example::StringData")
    {
        holo_cmw::CMW::StringDataTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::StringDataPublisher* publisher = (holo_cmw::CMW::StringDataPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub StringData msg!";
    }
    else if (it->second.tmd_.type == "UInt32TopicType" || it->second.tmd_.type == "holo_cmw::dds::common::UInt32")
    {
        holo_cmw::CMW::UInt32TopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::UInt32Publisher* publisher = (holo_cmw::CMW::UInt32Publisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "VehicleBodyStateTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::common::VehicleBodyState")
    {
        holo_cmw::CMW::VehicleBodyStateTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::VehicleBodyStatePublisher* publisher =
            (holo_cmw::CMW::VehicleBodyStatePublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "WeatherTopicType" || it->second.tmd_.type == "holo_cmw::dds::common::Weather")
    {
        holo_cmw::CMW::WeatherTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::WeatherPublisher* publisher = (holo_cmw::CMW::WeatherPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    // map
    else if (it->second.tmd_.type == "AdviceTopicType" || it->second.tmd_.type == "holo_cmw::dds::map::Advice")
    {
        holo_cmw::CMW::AdviceTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::AdvicePublisher* publisher = (holo_cmw::CMW::AdvicePublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "RoadRefPointTypeIntervalsTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::map::RoadRefPointTypeIntervals")
    {
        holo_cmw::CMW::RoadRefPointTypeIntervalsTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::RoadRefPointTypeIntervalsPublisher* publisher =
            (holo_cmw::CMW::RoadRefPointTypeIntervalsPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub RoadRefPointTypeIntervals msg!";
    }
    // Obstacle
    else if (it->second.tmd_.type == "ObstacleGeneralListTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::obstacle::ObstacleGeneralList")
    {
        holo_cmw::CMW::ObstacleGeneralListTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::ObstacleGeneralListPublisher* publisher =
            (holo_cmw::CMW::ObstacleGeneralListPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "ObstacleRadarListTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::obstacle::ObstacleRadarList")
    {
        holo_cmw::CMW::ObstacleRadarListTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::ObstacleRadarListPublisher* publisher =
            (holo_cmw::CMW::ObstacleRadarListPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else if (it->second.tmd_.type == "ObstacleVisionListTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::obstacle::ObstacleVisionList")
    {
        holo_cmw::CMW::ObstacleVisionListTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::ObstacleVisionListPublisher* publisher =
            (holo_cmw::CMW::ObstacleVisionListPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    // planning
    else if (it->second.tmd_.type == "PlanningStateTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::planning::PlanningState")
    {
        holo_cmw::CMW::PlanningStateTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::PlanningStatePublisher* publisher =
            (holo_cmw::CMW::PlanningStatePublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    // prediction
    else if (it->second.tmd_.type == "IntentionsTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::prediction::Intentions")
    {
        holo_cmw::CMW::IntentionsTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::IntentionsPublisher* publisher = (holo_cmw::CMW::IntentionsPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    // sensors
    else if (it->second.tmd_.type == "WeatherValueTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::sensors::WeatherValue")
    {
        holo_cmw::CMW::WeatherValueTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::WeatherValuePublisher* publisher =
            (holo_cmw::CMW::WeatherValuePublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    // vision
    else if (it->second.tmd_.type == "ImageObjectsKeyPoint2fTopicType" ||
             it->second.tmd_.type == "holo_cmw::dds::vision::ImageObjectsKeyPoint2f")
    {
        holo_cmw::CMW::ImageObjectsKeyPoint2fTopicType output;
        try
        {
            deserializer_->Deserialize(ibuffer, output);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "Deserialize " << it->second.tmd_.name << " Failed,Continue.";
            return;
        }

        holo_cmw::CMW::ImageObjectsKeyPoint2fPublisher* publisher =
            (holo_cmw::CMW::ImageObjectsKeyPoint2fPublisher*)(it->second.publisher_);
        publisher->Write(output);
        LOG(INFO) << "Pub a " << it->second.tmd_.type << " msg!";
    }
    else
    {
        LOG(WARNING) << "Could not tell the topic type which is " << it->second.tmd_.type;
        return;
    }
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
    delt -= options_.skip_time_;
    result.append(std::to_string(delt));
    result.append(" / ");
    result.append(std::to_string(bag_duration_));
    printf("%s\r", result.c_str());
    fflush(stdout);
}

holo::float64_t HoloReplay::GetBagDuration()
{
    return bag_duration_;
}

holo::float64_t HoloReplay::GetBagStartTime()
{
    return bag_start_time_;
}

holo::bool_t HoloReplay::GetPause()
{
    return paused_;
}

holo::float32_t HoloReplay::GetRate()
{
    return options_.rate_;
}

holo::float64_t HoloReplay::GetSkipTime()
{
    return options_.skip_time_;
}
    
void HoloReplay::SetPause(holo::bool_t pause)
{
    paused_ = pause;
}
    
void HoloReplay::SetRate(holo::float32_t rate)
{
    options_.rate_ = rate;
}

void HoloReplay::SetSkipTime(holo::float64_t skip_time)
{
    options_.skip_time_ = skip_time;
}

void HoloReplay::SetStopFlag()
{
    set_stop_flag();
    end_callback_(0);
}

void HoloReplay::QueuePop()
{
    while (message_queue_.pop())
    {
    }
}

void HoloReplay::SetStartFlag()
{
    set_play_flag();
}

}  // namespace holo_cmw