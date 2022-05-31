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

#include <cmw_wrapper/cmw_bus.h>
#include <holo/bag/base/serialized_bag_message.h>
#include <holo/bag/base/topic_metadata.h>
#include <holo/bag/interface/reader.h>
#include <holo/bag/interface/replayable_message.h>
#include <holo/bag/interface/storage_options.h>
#include <holo/bag/thridparty/readerwriterqueue.h>
#include <holo/common/sensor_id.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/os/time.h>
#include <holo/sensors/camera/decoder/image_decoder.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/serialization/deserializer.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_thread_pool.h>
#include <play_options.h>

#include <chrono>
#include <future>
#include <map>
#include <thread>
namespace holo_cmw
{
class HoloReplay
{
    using TdecBase     = holo::sensors::camera::ImageDecoderBase;
    using SensorID     = ::holo::common::SensorId;
    using CmwBus       = cmw_wrapper::BusType;
    using BusType      = CmwBus;
    using ReplayMap    = std::map<std::string, holo::bag::TopicMetadata>;
    using MessageQueue = moodycamel::ReaderWriterQueue<holo::bag::ReplayableMessage>;
    using TimePoint    = std::chrono::time_point<std::chrono::high_resolution_clock>;
    using DecodeSpace  = std::pair<holo::sensors::camera::ImagePacket, std::shared_ptr<uint8_t>>;
    using DeCodeMap    = std::pair<::holo::uint32_t, std::pair<std::shared_ptr<TdecBase>, DecodeSpace>>;
    using Buffer       = holo::container::Vector<::holo::uint8_t, std::numeric_limits<size_t>::max()>;
    using DecodeQueue  = std::queue<Buffer>;
    using Decoder      = std::map<std::string, std::pair<DeCodeMap, DecodeQueue>>;

public:
    HoloReplay(int argc, char **argv, const std::string &name, holo::uint64_t domain_id = 0,
               holo::bool_t show_image = false, const std::string &encode_type = "RGB", const std::string &image_type = "H264");
    ~HoloReplay();
    bool SetUp(const std::string& file_name = "");
    void SetUserOptions(holo::float64_t skip_time = 0.0, holo::float64_t duration = 0.0, holo::float32_t rate = 1.0, holo::bool_t accept = false);
    void Play();
    void SetIgnoredTopics(const std::vector<std::string>& ignored_topics, std::size_t vector_size);

private:
    enum TdecType{RgbToH264 ,RgbToH265, Nv12ToH264, Nv12ToH265, BgrToH264, BgrToH265};

private:
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

    bool isIgnoredTopic(std::string topic_name);

    std::string replaceTopic(std::string topic_name, std::string find_data, std::string replace_data, bool ifUseRe);
    void sendInfoMessage(::holo::uint32_t counter, ::holo::uint32_t sensor_id, std::string topic_name);

    void initDecoderThread();
    void imageDecode(std::string topic_name);
    void setTencType(const std::string decode_type, const std::string image_type);
    std::shared_ptr<HoloReplay::TdecBase> getTdecObject(HoloReplay::TdecType tdec_type, ::holo::uint32_t sensors_id,
                                                        ::holo::uint32_t cols, ::holo::uint32_t rows, uint32_t fps);

private:
    std::shared_ptr<BusType> bus_ptr_;

    holo::bool_t  active_replay_;
    holo::bool_t  paused_;
    holo::bool_t  image_play_;
    holo::uint8_t version_check_;

    ReplayMap                                          replay_map_;
    PlayOptions                                        options_;
    MessageQueue                                       message_queue_;
    holo::bag::ReplayableMessage                       enque_temp_message_;
    holo::bag::ReplayableMessage                       deque_temp_message_;
    std::chrono::time_point<std::chrono::system_clock> start_time_;
    holo::int64_t                                      paused_time_;

    std::shared_ptr<holo::bag::Reader> replay_ptr_;
    holo::float64_t                    bag_start_time_;
    holo::float64_t                    bag_duration_;

    mutable std::future<void>    storage_loading_future_;
    std::shared_ptr<std::thread> command_thread_;

    holo::bool_t             accept_or_ignore_;
    std::vector<std::string> ignored_topics_;

    std::shared_ptr<HoloThreadPool> decode_thread_pool_;
    Decoder                         image_decoder_;
    TdecType                        tdec_type_;
};

}  // namespace holo_cmw

#endif  // _HOLO_CMW_APPS__HOLO_REPLAY_H_