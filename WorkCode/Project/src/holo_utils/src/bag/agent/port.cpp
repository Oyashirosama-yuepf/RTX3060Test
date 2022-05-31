#include <holo/bag/agent/port.h>
#include <holo/bag/agent/session.h>
#include <holo/bag/protocol/protocol.h>
#include <cstring>

namespace holo
{
namespace bag
{
namespace agent
{
Port::Port(std::weak_ptr<Session> const& session, std::string const& topic_name) noexcept
  : session_{session}
  , enable_{false}
  , inbound_{false}
  , index_{0U}
  , node_name_{}
  , topic_name_{topic_name}
  , metadata_{}
  , record_config_{}
  , record_status_{}
  , replay_config_{}
  , replay_status_{}
  , config_flag_{0U}
  , msg_queue_{nullptr}
{
}

void Port::ReportInfo()
{
    auto session = session_.lock();
    if (nullptr == session)
    {
        return;
    }

    if (!session->IsEstablished())
    {
        return;
    }

    session->ReportPortInfo(index_);
}

void Port::Write(holo::uint8_t const* data, holo::uint32_t const data_size, holo::uint32_t const data_type)
{
    if ((holo::bag::protocol::HbpConfigFlag::RECORD != config_flag_) || !enable_)
    {
        return;
    }

    auto session = session_.lock();
    if (nullptr == session)
    {
        return;
    }

    if (!session->IsEstablished())
    {
        return;
    }

    if (isSetRecordIntervalCount())
    {
        if (!checkRecordIntervalCount())
        {
            return;
        }
    }
    else if (isSetRecordIntervalTime())
    {
        holo::int64_t now =
            std::chrono::duration_cast<std::chrono::nanoseconds>(ClockType::now().time_since_epoch()).count();

        if (!checkRecordIntervalTime(now))
        {
            return;
        }
    }
    else
    {
    }

    holo::int32_t                         header_size = sizeof(holo::bag::protocol::HbpMsgMessageIn);
    holo::int32_t                         size        = header_size + data_size;
    auto                                  sample      = std::make_shared<DataSequenceType>(size);
    holo::char_t*                         buffer      = sample->data();
    holo::bag::protocol::HbpMsgMessageIn* msg         = new (buffer) holo::bag::protocol::HbpMsgMessageIn;

    msg->InitHeader(session->GetXidAndIncrease(), size);
    msg->port_index    = index_;
    msg->buffer_type   = data_type;
    msg->buffer_length = data_size;
    std::memcpy(buffer + header_size, data, data_size);

    session->Write(sample);
}

void Port::handleMessage(std::shared_ptr<DataSequenceType> const& msg)
{
    if ((holo::bag::protocol::HbpConfigFlag::REPLAY != config_flag_) || !enable_)
    {
        return;
    }

    replay_config_.message_handler(reinterpret_cast<holo::uint8_t*>(msg->data()), msg->size());
}

void Port::SetMessageHandler(MessageHandler const& handler)
{
    replay_config_.message_handler = handler;
}

void Port::Enable() noexcept
{
    enable_ = true;
}

void Port::Disable() noexcept
{
    enable_ = false;
}

holo::bool_t Port::IsEnable() const noexcept
{
    return enable_;
}

holo::bool_t Port::IsSetMessageHandler() const noexcept
{
    return ((nullptr == replay_config_.message_handler) ? false : true);
}

holo::uint32_t Port::GetIndex() const noexcept
{
    return index_;
}

void Port::SetInbound(holo::bool_t const is_inbound) noexcept
{
    inbound_ = is_inbound;
}

holo::bool_t Port::IsInbound() const noexcept
{
    return inbound_;
}

void Port::SetNodeName(std::string const& node_name)
{
    node_name_ = node_name;
}

std::string Port::GetNodeName() const noexcept
{
    return node_name_;
}

std::string Port::GetTopicName() const noexcept
{
    return topic_name_;
}

void Port::SetMetadata(std::string const& metadata)
{
    metadata_ = metadata;
}

std::string Port::GetMetadata() const noexcept
{
    return metadata_;
}

void Port::setConfigFlag(holo::uint32_t const flag) noexcept
{
    config_flag_ = flag;
}

holo::uint32_t Port::getConfigFlag() noexcept
{
    return config_flag_;
}

void Port::setRecordIntervalCount(holo::int32_t const interval) noexcept
{
    record_config_.record_interval_count = interval;
}

holo::int32_t Port::getRecordIntervalCount() const noexcept
{
    return record_config_.record_interval_count;
}

holo::bool_t Port::isSetRecordIntervalCount() const noexcept
{
    return record_config_.record_interval_count > 0;
}

holo::bool_t Port::checkRecordIntervalCount() noexcept
{
    ++record_status_.current_interval_count;

    if (record_status_.current_interval_count > record_config_.record_interval_count)
    {
        record_status_.current_interval_count = 0;
        return true;
    }
    return false;
}

void Port::setRecordIntervalTime(holo::int64_t const& interval) noexcept
{
    record_config_.record_interval_time = interval;
}

holo::int64_t Port::getRecordIntervalTime() const noexcept
{
    return record_config_.record_interval_time;
}

holo::bool_t Port::isSetRecordIntervalTime() const noexcept
{
    return record_config_.record_interval_time > 0;
}

holo::bool_t Port::checkRecordIntervalTime(holo::int64_t const& current) noexcept
{
    if (current >= (record_status_.last_record_time + record_config_.record_interval_time))
    {
        record_status_.last_record_time = current;
        return true;
    }
    return false;
}

holo::bool_t Port::obtainControl() noexcept
{
    holo::bool_t old_control = false;
    return replay_status_.control.compare_exchange_weak(old_control, true);
}

void Port::releaseControl() noexcept
{
    replay_status_.control.store(false);
}

void Port::setIndex(holo::uint32_t const index) noexcept
{
    index_ = index;
}

}  // namespace agent
}  // namespace bag
}  // namespace holo
