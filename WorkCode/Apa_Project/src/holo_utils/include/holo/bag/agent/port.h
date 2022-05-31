#ifndef HOLO_BAG_AGENT_PORT_H
#define HOLO_BAG_AGENT_PORT_H

#include <holo/core/types.h>
#include <holo/thread/lockfree_queue.h>

#include <atomic>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "../protocol/protocol.h"
#include "common.h"

namespace holo
{
namespace bag
{
namespace agent
{
class Session;
class Port : public std::enable_shared_from_this<Port>
{
public:
    friend class Session;
    using MessageHandler = std::function<void(holo::uint8_t const*, holo::uint32_t const)>;

    Port(std::weak_ptr<Session> const& session, std::string const& topic_name) noexcept;

    void ReportInfo();
    void Write(holo::uint8_t const* data, holo::uint32_t const data_size,
               holo::uint32_t const data_type = holo::bag::protocol::HbpBufferType::PAYLOAD);
    void SetMessageHandler(MessageHandler const& handler);

    void           Enable() noexcept;
    void           Disable() noexcept;
    holo::bool_t   IsEnable() const noexcept;
    holo::bool_t   IsSetMessageHandler() const noexcept;
    holo::uint32_t GetIndex() const noexcept;
    void           SetInbound(holo::bool_t const is_inbound) noexcept;
    holo::bool_t   IsInbound() const noexcept;
    void           SetNodeName(std::string const& node_name);
    std::string    GetNodeName() const noexcept;
    std::string    GetTopicName() const noexcept;
    void           SetMetadata(std::string const& metadata);
    std::string    GetMetadata() const noexcept;

private:
    void handleMessage(std::shared_ptr<DataSequenceType> const& msg);

    void           setConfigFlag(holo::uint32_t const flag) noexcept;
    holo::uint32_t getConfigFlag() noexcept;

    void          setRecordIntervalCount(holo::int32_t const interval) noexcept;
    holo::int32_t getRecordIntervalCount() const noexcept;
    holo::bool_t  isSetRecordIntervalCount() const noexcept;
    holo::bool_t  checkRecordIntervalCount() noexcept;

    void          setRecordIntervalTime(holo::int64_t const& interval) noexcept;
    holo::int64_t getRecordIntervalTime() const noexcept;
    holo::bool_t  isSetRecordIntervalTime() const noexcept;
    holo::bool_t  checkRecordIntervalTime(holo::int64_t const& current) noexcept;

    holo::bool_t obtainControl() noexcept;
    void         releaseControl() noexcept;

    void setIndex(holo::uint32_t const index) noexcept;

private:
    struct RecordConfiguration
    {
        RecordConfiguration() noexcept : record_interval_count{0}, record_interval_time{}
        {
        }

        holo::int32_t record_interval_count;
        holo::int64_t record_interval_time;
    };

    struct RecordStatus
    {
        RecordStatus() noexcept : current_interval_count{0}, last_record_time{0}
        {
        }

        holo::int32_t current_interval_count;
        holo::int64_t last_record_time;
    };

    struct ReplayConfiguration
    {
        ReplayConfiguration() noexcept : message_handler{nullptr}
        {
        }

        MessageHandler message_handler;
    };

    struct ReplayStatus
    {
        ReplayStatus() noexcept : control{false}
        {
        }

        std::atomic<holo::bool_t> control;
    };

private:
    using QueueType = holo::thread::LockfreeQueue<std::shared_ptr<DataSequenceType>>;

    std::weak_ptr<Session>     session_;
    holo::bool_t               enable_;
    holo::bool_t               inbound_;
    holo::uint32_t             index_;
    std::string                node_name_;
    std::string                topic_name_;
    std::string                metadata_;
    RecordConfiguration        record_config_;
    RecordStatus               record_status_;
    ReplayConfiguration        replay_config_;
    ReplayStatus               replay_status_;
    holo::uint32_t             config_flag_; /*0, disable; 1, record enable; 2, replay enable*/
    std::shared_ptr<QueueType> msg_queue_;
};

}  // namespace agent
}  // namespace bag
}  // namespace holo
#endif
