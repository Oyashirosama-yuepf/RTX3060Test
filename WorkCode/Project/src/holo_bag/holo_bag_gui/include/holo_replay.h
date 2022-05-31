/**
 * @file holo_replay.h
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief the header of the holo_replay cmw app
 * @version 0.1
 * @date 2020-05-09
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_CMW_APPS__HOLO_REPLAY_H_
#define _HOLO_CMW_APPS__HOLO_REPLAY_H_

#include <holo/bag/base/serialized_bag_message.h>
#include <holo/bag/base/topic_metadata.h>
#include <holo/bag/interface/reader.h>
#include <holo/bag/interface/replayable_message.h>
#include <holo/bag/interface/storage_options.h>
#include <holo/bag/thridparty/readerwriterqueue.h>
#include <holo/core/types.h>
#include <holo/os/time.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_cmw/CMW/CMW.h>
#include <holo_cmw/message/message.h>
#include <holo_msg_serialization.h>
#include <play_options.h>
#include <holo_cmw/utils/cxxopts.hpp>

#include <chrono>
#include <future>
#include <thread>

namespace holo_cmw
{
class HoloReplay
{
    struct ReplayMetadata
    {
        holo::bag::TopicMetadata tmd_;
        void*                    publisher_;
        holo::bool_t             version_matched_;

        ReplayMetadata(holo::bag::TopicMetadata tmd, void* pub, holo::bool_t matched)
          : tmd_(tmd), publisher_(pub), version_matched_(matched)
        {
        }
    };

    using TopicList    = std::vector<holo::bag::TopicMetadata>;
    using ReplayMap    = std::map<std::string, ReplayMetadata>;
    using PublisherMap = std::map<std::string, void*>;
    using MessageQueue = moodycamel::ReaderWriterQueue<holo::bag::ReplayableMessage>;
    using TimePoint    = std::chrono::time_point<std::chrono::high_resolution_clock>;

public:
    HoloReplay(int argc, char** argv, const std::string& name);
    ~HoloReplay();
    bool SetUp(const std::string& config_file, const std::string& file_name = "");
    void SetUserOptions(holo::float64_t skip_time = 0.0, holo::float64_t duration = 0.0, holo::float32_t rate = 1.0);
    void Play();

public:
    using CallbackType = std::function<void(holo::float64_t)>;
    holo::float64_t GetBagDuration();
    holo::float64_t GetBagStartTime();
    holo::bool_t    GetPause();
    holo::float32_t GetRate();
    holo::float64_t GetSkipTime();

    void SetPause(holo::bool_t pause);
    void SetRate(holo::float32_t rate);
    void SetSkipTime(holo::float64_t skip_time);
    void SetStopFlag();
    void SetStartFlag();
    void PlayEnd();
    void QueuePop();

    void SetTimeCallback(const CallbackType& handler) noexcept
    {
        time_callback_ = handler;
    }

    void SetEndCallback(const CallbackType& handler) noexcept
    {
        end_callback_ = handler;
    }

private:
    CallbackType time_callback_;
    CallbackType end_callback_;

private:
    bool loadConfigFile(const std::string& config_file);
    bool initPublisher();
    bool initReader(const std::string& file_name);
    void getBagMetadataMsg();

    void getCommand();

    void publishMsg(const std::shared_ptr<holo::bag::SerializedBagMessage> msg);
    void showMsg(const holo::float64_t current_stamp, holo::float64_t delt);

    void loadStorageContent(const PlayOptions& options);
    void enqueueUpToBoundary(holo::int64_t& time_first_message, uint64_t boundary);
    void waitForFilledQueue(const PlayOptions& options) const;
    void playMessagesFromQueue(const PlayOptions& options);
    bool isStorageCompletelyLoaded() const;
    void playMessagesUntilQueueEmpty(const PlayOptions& options);

    CMW cmw_;
    CMW cmw_encoder_;

    holo::bool_t active_replay_;
    holo::bool_t paused_;
    holo::uint8_t version_check_;

    ReplayMap                                          replay_map_;
    TopicList                                          replay_topic_list_;
    PlayOptions                                        options_;
    MessageQueue                                       message_queue_;
    std::chrono::time_point<std::chrono::system_clock> start_time_;
    holo::int64_t                                      paused_time_;

    std::shared_ptr<holo::bag::Reader> replay_ptr_;
    holo::float64_t                    bag_start_time_;
    holo::float64_t                    bag_duration_;

    mutable std::future<void>    storage_loading_future_;
    std::shared_ptr<std::thread> play_thread_;
    std::shared_ptr<std::thread> command_thread_;

    std::shared_ptr<holo_cmw::HoloMsgSerialization> deserializer_;
};

}  // namespace holo_cmw

#endif  // _HOLO_CMW_APPS__HOLO_REPLAY_H_
