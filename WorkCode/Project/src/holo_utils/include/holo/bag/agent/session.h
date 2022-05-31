#ifndef HOLO_BAG_AGENT_SESSION_H
#define HOLO_BAG_AGENT_SESSION_H

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

#include <holo/core/types.h>
#include <holo/thread/lockfree_queue.h>

#include <holo/network/connection_monitor.h>
#include "../protocol/protocol.h"
#include "common.h"

namespace holo
{
namespace bag
{
namespace agent
{
class Port;
class Session : public std::enable_shared_from_this<Session>
{
public:
    using Task        = std::function<void()>;
    using TaskHandler = std::function<void(Task const& task)>;

    Session(std::string const& ip, holo::int32_t const port) noexcept;
    virtual ~Session() noexcept;

    void Init();
    void Destroy();

    void SetTaskHandler(TaskHandler const& task);
    void ProcessEventOnce();

    void ProcessWriteEventOnce();

    holo::bool_t TryConnectOnce();
    void         Disconnect();

    holo::bool_t IsNetConnected() const noexcept;
    holo::bool_t IsEstablished() const noexcept;

    holo::int64_t GetPeerActiveTime() const noexcept;
    void          SendDetectionPackage();

    std::shared_ptr<Port> CreatePort(std::string const& topic);
    std::shared_ptr<Port> GetPort(std::string const& topic);
    std::shared_ptr<Port> GetPort(holo::uint32_t const index);
    void                  DeletePort(std::string const& topic);
    void                  DeletePort(holo::uint32_t const index);
    void                  DisableAllPort();
    holo::uint32_t        GetPortSize();

    void ReportPortInfo(std::string const& topic);
    void ReportPortInfo(holo::uint32_t const index);

    holo::bool_t Write(std::shared_ptr<DataSequenceType> const& sample_record);

    void           SetNodeName(std::string const& node_name) noexcept;
    std::string    GetNodeName() const noexcept;
    void           SetBusType(std::string const& bus_type) noexcept;
    std::string    GetBusType() const noexcept;
    void           SetDomainId(holo::uint32_t const domain_id) noexcept;
    holo::uint32_t GetDomainId() const noexcept;
    holo::uint32_t GetErrorCode() const noexcept;
    holo::uint32_t GetXidValue() noexcept;
    holo::uint32_t GetXidAndIncrease() noexcept;

private:
    void onUninitialized(holo::network::Socket const socket);
    void onConnected(holo::network::Socket const socket);
    void onRead(holo::network::Socket const socket);
    void onClosed(holo::network::Socket const socket);
    void onWrite(holo::network::Socket const socket);

    void onHelloMsg(holo::bag::protocol::HbpMsgHello const& msg);
    void onEchoRequest(holo::bag::protocol::HbpMsgEchoRequest const& msg);
    void onEchoResponse(holo::bag::protocol::HbpMsgEchoResponse const& msg);
    void onNodeFeatureRequest(holo::bag::protocol::HbpMsgNodeFeatureRequest const& msg);
    void onNodeFeatureResponse(holo::bag::protocol::HbpMsgNodeFeatureResponse const& msg);
    void onPortFeatureRequest(holo::bag::protocol::HbpMsgPortFeatureRequest const& msg);
    void onPortFeatureResponse(holo::bag::protocol::HbpMsgPortFeatureResponse const& msg);
    void onPortConfigurationRequest(holo::bag::protocol::HbpMsgPortConfigurationRequest const& msg);
    void onPortConfigurationSet(holo::bag::protocol::HbpMsgPortConfigurationSet const& msg);
    void onPortConfigurationResponse(holo::bag::protocol::HbpMsgPortConfigurationResponse const& msg);
    void onMessageIn(holo::bag::protocol::HbpMsgMessageIn const& msg);
    void onMessageOut(holo::bag::protocol::HbpMsgMessageOut const& msg);
    void onPortUpdateRequest(holo::bag::protocol::HbpMsgPortUpdateRequest const& msg);
    void onErrorMsg(holo::bag::protocol::HbpMsgError const& msg);

    holo::bool_t connect();

    holo::int32_t underlyingWrite(holo::uint8_t const* data, holo::int32_t const data_size);
    holo::int32_t underlyingWrite(holo::uint8_t const* data, holo::int32_t const data_size,
                                  holo::int32_t const seconds);

    holo::int64_t now();
    void          updatePeerActiveTime() noexcept;

private:
    struct NodeInfo
    {
        NodeInfo() : host_id{0U}, pid{0U}, tid{0U}, domain_id{0U}, node_name{}, bus_type{}, hostname{}, mac_address{}
        {
        }

        holo::uint32_t             host_id;
        holo::uint32_t             pid;
        holo::uint32_t             tid;
        holo::uint32_t             domain_id;
        std::string                node_name;
        std::string                bus_type;
        std::string                hostname;
        std::vector<holo::uint8_t> mac_address;
    };

    struct SessionState
    {
        SessionState()
          : error_code{0U}, xid{0U}, is_net_connected{false}, is_session_established{false}, retained_data_size{0U}
        {
        }

        void Reset()
        {
            is_net_connected.store(false);
            is_session_established.store(false);

            error_code         = 0U;
            xid                = 0U;
            retained_data_size = 0U;
        }

        holo::uint32_t              error_code;
        std::atomic<holo::uint32_t> xid;
        std::atomic<holo::bool_t>   is_net_connected;
        std::atomic<holo::bool_t>   is_session_established;
        holo::uint32_t              retained_data_size;
    };

private:
    using QueueType = holo::thread::LockfreeQueue<std::shared_ptr<DataSequenceType>>;

    holo::int32_t                                     domain_;
    holo::int32_t                                     type_;
    holo::int32_t                                     port_;
    std::string                                       ip_;
    std::shared_ptr<holo::network::ConnectionMonitor> monitor_;
    holo::network::Socket                             socket_;
    std::vector<holo::uint8_t>                        recv_buffer_;
    holo::uint32_t                                    send_timeout_;
    mutable std::mutex                                write_mutex_;
    holo::bag::protocol::HbpProtocol                  protocol_analysis_;
    std::vector<std::shared_ptr<Port>>                ports_;
    mutable std::mutex                                ports_mutex_;
    NodeInfo                                          node_info_;
    SessionState                                      session_state_;
    std::shared_ptr<QueueType>                        msg_queue_;
    TaskHandler                                       task_handler_;
    holo::int64_t                                     peer_active_time_;
};

}  // namespace agent
}  // namespace bag
}  // namespace holo
#endif
