#include <assert.h>
#include <chrono>
#include <iostream>
#include <stdexcept>

#include <holo/bag/agent/port.h>
#include <holo/bag/agent/session.h>
#include <holo/core/exception.h>
#include <holo/network/utils.h>

namespace holo
{
namespace bag
{
namespace agent
{
#define PRINT_DEBUG_INFO 0

static constexpr holo::int32_t  DEFAULT_RECONNECT_INTERVAL{3};
static constexpr holo::uint32_t DEFAULT_CONNECT_TIMEOUT{10};
static constexpr holo::uint32_t DEFAULT_SEND_TIMEOUT{30};

static constexpr holo::uint32_t DEFAULT_RECV_BUFFER_SIZE{81920};
static constexpr holo::uint32_t DEFAULT_RECV_BUFFER_MAX_SIZE{8192000};

static constexpr holo::uint32_t DEFAULT_QUEUE_CAPACITY{4096U};
static constexpr holo::uint32_t DEFAULT_PORT_QUEUE_CAPACITY{1024U};

Session::Session(std::string const& ip, holo::int32_t const port) noexcept
  : domain_{AF_INET}
  , type_{SOCK_STREAM}
  , port_{port}
  , ip_{ip}
  , monitor_{nullptr}
  , socket_{}
  , recv_buffer_(DEFAULT_RECV_BUFFER_SIZE)
  , send_timeout_{DEFAULT_SEND_TIMEOUT}
  , protocol_analysis_{}
  , ports_{}
  , node_info_{}
  , session_state_{}
  , msg_queue_{nullptr}
  , task_handler_{}
  , peer_active_time_{0}
{
}

Session::~Session() noexcept
{
    Destroy();
}

void Session::Init()
{
    msg_queue_ = std::make_shared<QueueType>(DEFAULT_QUEUE_CAPACITY);

    node_info_.mac_address = holo::network::Utils::GetFirstIpv4MacAddress();
    node_info_.hostname    = holo::network::Utils::GetHostname();
    node_info_.host_id     = holo::network::Utils::GetHostId();

    protocol_analysis_.SetHelloMsgHandler(std::bind(&Session::onHelloMsg, this, std::placeholders::_1));
    protocol_analysis_.SetEchoRequestHandler(std::bind(&Session::onEchoRequest, this, std::placeholders::_1));
    protocol_analysis_.SetEchoResponseHandler(std::bind(&Session::onEchoResponse, this, std::placeholders::_1));
    protocol_analysis_.SetNodeFeatureRequestHandler(
        std::bind(&Session::onNodeFeatureRequest, this, std::placeholders::_1));
    protocol_analysis_.SetNodeFeatureResponseHandler(
        std::bind(&Session::onNodeFeatureResponse, this, std::placeholders::_1));
    protocol_analysis_.SetPortFeatureRequestHandler(
        std::bind(&Session::onPortFeatureRequest, this, std::placeholders::_1));
    protocol_analysis_.SetPortFeatureResponseHandler(
        std::bind(&Session::onPortFeatureResponse, this, std::placeholders::_1));
    protocol_analysis_.SetPortConfigurationRequestHandler(
        std::bind(&Session::onPortConfigurationRequest, this, std::placeholders::_1));
    protocol_analysis_.SetPortConfigurationSetHandler(
        std::bind(&Session::onPortConfigurationSet, this, std::placeholders::_1));
    protocol_analysis_.SetPortConfigurationResponseHandler(
        std::bind(&Session::onPortConfigurationResponse, this, std::placeholders::_1));
    protocol_analysis_.SetMessageInHandler(std::bind(&Session::onMessageIn, this, std::placeholders::_1));
    protocol_analysis_.SetMessageOutHandler(std::bind(&Session::onMessageOut, this, std::placeholders::_1));
    protocol_analysis_.SetPortUpdateRequestHandler(
        std::bind(&Session::onPortUpdateRequest, this, std::placeholders::_1));
    protocol_analysis_.SetErrorMsgHandler(std::bind(&Session::onErrorMsg, this, std::placeholders::_1));

    monitor_ = std::make_shared<holo::network::ConnectionMonitor>();
    monitor_->Init();
    monitor_->SetUninitializedCallback(std::bind(&Session::onUninitialized, this, std::placeholders::_1));
    monitor_->SetConnectedCallback(std::bind(&Session::onConnected, this, std::placeholders::_1));
    monitor_->SetReadCallback(std::bind(&Session::onRead, this, std::placeholders::_1));
    monitor_->SetClosedCallback(std::bind(&Session::onClosed, this, std::placeholders::_1));
    monitor_->SetWriteCallback(std::bind(&Session::onWrite, this, std::placeholders::_1));

    updatePeerActiveTime();
}

void Session::Destroy()
{
    monitor_->Destroy();
    Disconnect();
}

void Session::Disconnect()
{
    socket_.Close();
    session_state_.Reset();

    DisableAllPort();
}

holo::bool_t Session::connect()
{
    holo::network::Socket socket;

    socket.Open(domain_, type_);
    socket.SetNonBlock(true);
    socket.SetReuseAddr();
    socket.SetKeepAlive();
    socket.SetCloseWait(holo::network::Socket::CloseWaitState::NO_WAIT);

    holo::int32_t ret = socket.Connect(ip_, port_, DEFAULT_CONNECT_TIMEOUT);
    if (0 > ret)
    {
        socket.Close();
        return false;
    }
    else
    {
        session_state_.is_net_connected.store(true);
        monitor_->AddConnection(socket);
    }

    return true;
}

void Session::ProcessEventOnce()
{
    monitor_->ProcessEventOnce();
}

holo::bool_t Session::TryConnectOnce()
{
    if (!IsNetConnected())
    {
        return connect();
    }

    return true;
}

void Session::ProcessWriteEventOnce()
{
    std::shared_ptr<DataSequenceType> msg{nullptr};
    holo::uint32_t                    milliseconds{1000U};
    if (!msg_queue_->WaitForTake(msg, milliseconds))
    {
        return;
    }

    holo::int32_t ret{-1};

    {
        std::lock_guard<std::mutex> locker{write_mutex_};
        ret = socket_.Send(reinterpret_cast<holo::uint8_t const*>(msg->data()), msg->size(), send_timeout_);
    }

    if (ret != static_cast<holo::int32_t>(msg->size()))
    {
        Disconnect();
        return;
    }
}

void Session::SetTaskHandler(TaskHandler const& task)
{
    task_handler_ = task;
}

holo::int64_t Session::now()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(ClockType::now().time_since_epoch()).count();
}

void Session::updatePeerActiveTime() noexcept
{
    peer_active_time_ = now();
}

holo::int64_t Session::GetPeerActiveTime() const noexcept
{
    return peer_active_time_;
}

void Session::SendDetectionPackage()
{
    holo::bag::protocol::HbpMsgEchoRequest msg;

    holo::int32_t size = sizeof(msg);
    msg.InitHeader(GetXidAndIncrease(), size);

    if (size != underlyingWrite(reinterpret_cast<holo::uint8_t*>(&msg), size, send_timeout_))
    {
        Disconnect();
        return;
    }
}

std::shared_ptr<Port> Session::CreatePort(std::string const& topic)
{
    std::lock_guard<std::mutex> locker{ports_mutex_};

    for (auto const& port : ports_)
    {
        if (topic == port->GetTopicName())
        {
            return port;
        }
    }

    std::cout << "create topic =" << topic << std::endl;

    holo::uint32_t index = ports_.size();
    auto           port  = std::make_shared<Port>(this->shared_from_this(), topic);
    port->setIndex(index);

    ports_.emplace_back(port);
    return port;
}

std::shared_ptr<Port> Session::GetPort(std::string const& topic)
{
    std::lock_guard<std::mutex> locker{ports_mutex_};

    for (auto const& port : ports_)
    {
        if (topic == port->GetTopicName())
        {
            return port;
        }
    }

    throw std::invalid_argument{"GetPort: no such topic"};
}

std::shared_ptr<Port> Session::GetPort(holo::uint32_t const index)
{
    std::lock_guard<std::mutex> locker{ports_mutex_};
    if (index >= ports_.size())
    {
        throw std::range_error{"GetPort: port index range error"};
    }

    return ports_[index];
}

void Session::DeletePort(std::string const& topic)
{
    std::lock_guard<std::mutex> locker{ports_mutex_};

    for (auto const& port : ports_)
    {
        if (topic == port->GetTopicName())
        {
            port->Disable();
            return;
        }
    }
}

void Session::DeletePort(holo::uint32_t const index)
{
    std::lock_guard<std::mutex> locker{ports_mutex_};
    if (index >= ports_.size())
    {
        return;
    }

    ports_[index]->Disable();
}

void Session::DisableAllPort()
{
    std::lock_guard<std::mutex> locker{ports_mutex_};

    for (auto const& port : ports_)
    {
        port->Disable();
    }
}

holo::uint32_t Session::GetPortSize()
{
    std::lock_guard<std::mutex> locker{ports_mutex_};
    return ports_.size();
}

void Session::ReportPortInfo(std::string const& topic)
{
    std::shared_ptr<Port>      port     = GetPort(topic);
    std::string                metadata = port->GetMetadata();
    holo::uint32_t             size     = sizeof(holo::bag::protocol::HbpMsgPortUpdateRequest) + metadata.length();
    std::vector<holo::uint8_t> buffer(size, '\0');
    holo::bag::protocol::HbpMsgPortUpdateRequest* msg =
        new (buffer.data()) holo::bag::protocol::HbpMsgPortUpdateRequest;

    msg->InitHeader(GetXidAndIncrease(), size);

    msg->port_index = port->GetIndex();
    strncpy(msg->topic_name, topic.c_str(), holo::bag::protocol::HbpMsgPortUpdateRequest::TOPIC_NAME_SIZE);
    msg->inbound         = static_cast<holo::uint32_t>(port->IsInbound());
    msg->metadata_length = metadata.length();
    if (msg->metadata_length > 0U)
    {
        strncpy(msg->metadata, metadata.c_str(), msg->metadata_length);
    }

    if (-1 == underlyingWrite(buffer.data(), buffer.size(), send_timeout_))
    {
        Disconnect();
        return;
    }
}

void Session::ReportPortInfo(holo::uint32_t const index)
{
    std::shared_ptr<Port>      port     = GetPort(index);
    std::string                topic    = port->GetTopicName();
    std::string                metadata = port->GetMetadata();
    holo::uint32_t             size     = sizeof(holo::bag::protocol::HbpMsgPortUpdateRequest) + metadata.length();
    std::vector<holo::uint8_t> buffer(size, '\0');
    holo::bag::protocol::HbpMsgPortUpdateRequest* msg =
        new (buffer.data()) holo::bag::protocol::HbpMsgPortUpdateRequest;

    msg->InitHeader(GetXidAndIncrease(), size);

    msg->port_index = port->GetIndex();
    strncpy(msg->topic_name, topic.c_str(), holo::bag::protocol::HbpMsgPortUpdateRequest::TOPIC_NAME_SIZE);
    msg->inbound         = static_cast<holo::uint32_t>(port->IsInbound());
    msg->metadata_length = metadata.length();
    if (msg->metadata_length > 0U)
    {
        strncpy(msg->metadata, metadata.c_str(), msg->metadata_length);
    }

    if (-1 == underlyingWrite(buffer.data(), buffer.size(), send_timeout_))
    {
        Disconnect();
        return;
    }
}

holo::bool_t Session::IsNetConnected() const noexcept
{
    return session_state_.is_net_connected.load();
}

holo::bool_t Session::IsEstablished() const noexcept
{
    return session_state_.is_session_established.load();
}

holo::bool_t Session::Write(std::shared_ptr<DataSequenceType> const& sample_record)
{
    return msg_queue_->TryPush(sample_record);
}

void Session::SetNodeName(std::string const& node_name) noexcept
{
    node_info_.node_name = node_name;
}

std::string Session::GetNodeName() const noexcept
{
    return node_info_.node_name;
}

void Session::SetBusType(std::string const& bus_type) noexcept
{
    node_info_.bus_type = bus_type;
}

std::string Session::GetBusType() const noexcept
{
    return node_info_.bus_type;
}

void Session::SetDomainId(holo::uint32_t const domain_id) noexcept
{
    node_info_.domain_id = domain_id;
}

holo::uint32_t Session::GetDomainId() const noexcept
{
    return node_info_.domain_id;
}

holo::uint32_t Session::GetErrorCode() const noexcept
{
    return session_state_.error_code;
}

void Session::onUninitialized(holo::network::Socket const socket)
{
#if PRINT_DEBUG_INFO
    std::cout << "handle connection uninitialized event" << std::endl;
#endif
    socket_ = socket;
    socket_.SetNonBlock(true);
    socket_.SetReuseAddr();
    socket_.SetKeepAlive();
    socket_.SetCloseWait(holo::network::Socket::CloseWaitState::NO_WAIT);

    (void)socket_.Connect(ip_, port_);
}

void Session::onConnected(holo::network::Socket const socket)
{
    session_state_.is_net_connected.store(true);

#if PRINT_DEBUG_INFO
    std::cout << "handle connected event" << std::endl;
#endif
    socket_ = socket;

#if PRINT_DEBUG_INFO
    std::cout << "on connected. send hello " << std::endl;
#endif

    holo::bag::protocol::HbpMsgHello msg;

    holo::int32_t size = sizeof(holo::bag::protocol::HbpMsgHello);

    msg.InitHeader(GetXidAndIncrease(), size);

    if (size != underlyingWrite(reinterpret_cast<holo::uint8_t*>(&msg), size, send_timeout_))
    {
        Disconnect();
    }
}

void Session::onRead(holo::network::Socket const socket)
{
#if PRINT_DEBUG_INFO
    std::cout << "handle read event" << std::endl;
#endif
    holo::uint8_t* recv_buffer      = &(recv_buffer_[session_state_.retained_data_size]);
    holo::uint32_t recv_buffer_size = recv_buffer_.size() - session_state_.retained_data_size;
    holo::int32_t  read_size{0};
    holo::uint32_t offset{0U};
    holo::uint32_t reserved{0U};
    holo::bool_t   is_continue_read{false};

    do
    {
        is_continue_read = false;
        read_size        = socket.Recv(recv_buffer, recv_buffer_size);

        if (read_size <= 0)
        {
            throw std::runtime_error{"read data error!"};
        }
        else if (read_size == static_cast<holo::int32_t>(recv_buffer_size))
        {
            is_continue_read = true;
            offset           = 0U;
            reserved         = 0U;

            protocol_analysis_.Analysis(offset, reserved, &(recv_buffer_[0]), recv_buffer_.size());

            if (recv_buffer_.size() == reserved)
            {
                if (DEFAULT_RECV_BUFFER_MAX_SIZE > recv_buffer_.size())
                {
                    recv_buffer_.resize(DEFAULT_RECV_BUFFER_MAX_SIZE);
                }
                else
                {
                    throw std::runtime_error{"Receive Buffer Overflow!"};
                }
            }

            if (offset > 0U && reserved > 0U)
            {
                memmove(&(recv_buffer_[0]), &(recv_buffer_[offset]), reserved);
            }

            session_state_.retained_data_size = reserved;
            recv_buffer                       = &(recv_buffer_[session_state_.retained_data_size]);
            recv_buffer_size                  = recv_buffer_.size() - session_state_.retained_data_size;
        }

    } while (is_continue_read);

    offset   = 0U;
    reserved = 0U;
    protocol_analysis_.Analysis(offset, reserved, &(recv_buffer_[0]), session_state_.retained_data_size + read_size);
    if (offset > 0U && reserved > 0U)
    {
        memmove(&(recv_buffer_[0]), &(recv_buffer_[offset]), reserved);
    }

    session_state_.retained_data_size = reserved;
}

void Session::onClosed(holo::network::Socket const socket)
{
#if PRINT_DEBUG_INFO
    std::cout << "handle closed event" << std::endl;
#endif
    session_state_.Reset();
    socket.Close();
    monitor_->DelConnection(socket);
}

void Session::onWrite(holo::network::Socket const socket)
{
    (void)socket;

#if PRINT_DEBUG_INFO
    std::cout << "handle write event " << std::endl;
#endif
}

holo::int32_t Session::underlyingWrite(holo::uint8_t const* data, holo::int32_t const data_size)
{
    std::lock_guard<std::mutex> locker{write_mutex_};
    return socket_.Send(data, data_size);
}

holo::int32_t Session::underlyingWrite(holo::uint8_t const* data, holo::int32_t const data_size,
                                       holo::int32_t const seconds)
{
    std::lock_guard<std::mutex> locker{write_mutex_};
    return socket_.Send(data, data_size, seconds);
}

holo::uint32_t Session::GetXidValue() noexcept
{
    return session_state_.xid.load();
}

holo::uint32_t Session::GetXidAndIncrease() noexcept
{
    return session_state_.xid.fetch_add(1U);
}

void Session::onHelloMsg(holo::bag::protocol::HbpMsgHello const& msg)
{
    updatePeerActiveTime();

    (void)msg;
}

void Session::onEchoRequest(holo::bag::protocol::HbpMsgEchoRequest const& msg)
{
    updatePeerActiveTime();

    holo::bag::protocol::HbpMsgEchoResponse response;

    holo::int32_t size = sizeof(holo::bag::protocol::HbpMsgEchoResponse);

    response.InitHeader(msg.header.xid, size);

    if (size != underlyingWrite(reinterpret_cast<holo::uint8_t*>(&response), size, send_timeout_))
    {
        Disconnect();
    }
}

void Session::onEchoResponse(holo::bag::protocol::HbpMsgEchoResponse const& msg)
{
    updatePeerActiveTime();

    (void)msg;
}

void Session::onNodeFeatureRequest(holo::bag::protocol::HbpMsgNodeFeatureRequest const& msg)
{
    assert(6U == node_info_.mac_address.size());

    updatePeerActiveTime();

    holo::bag::protocol::HbpMsgNodeFeatureResponse response;

    holo::int32_t size = sizeof(holo::bag::protocol::HbpMsgNodeFeatureResponse);

    response.InitHeader(msg.header.xid, size);

    response.host_id     = node_info_.host_id;
    response.pid         = node_info_.pid;
    response.tid         = node_info_.tid;
    response.domain_id   = node_info_.domain_id;
    response.total_ports = GetPortSize();
    memcpy(response.hw_address, &node_info_.mac_address[0U], 6U);
    strncpy(response.node_name, node_info_.node_name.c_str(),
            holo::bag::protocol::HbpMsgNodeFeatureResponse::NODE_NAME_SIZE);
    strncpy(response.bus_type, node_info_.bus_type.c_str(),
            holo::bag::protocol::HbpMsgNodeFeatureResponse::BUS_TYPE_SIZE);
    strncpy(response.hostname, node_info_.hostname.c_str(),
            holo::bag::protocol::HbpMsgNodeFeatureResponse::HOSTNAME_SIZE);

    if (size != underlyingWrite(reinterpret_cast<holo::uint8_t*>(&response), size, send_timeout_))
    {
        Disconnect();
        return;
    }

    session_state_.is_session_established.store(true);

#if PRINT_DEBUG_INFO
    std::cout << "session established:" << std::endl;
    std::cout << "node info: host_id=" << node_info_.host_id << std::endl;
    std::cout << "node info: pid=" << node_info_.pid << std::endl;
    std::cout << "node info: tid=" << node_info_.tid << std::endl;
    std::cout << "node info: domain_id=" << node_info_.domain_id << std::endl;
    std::cout << "node info: node_name=" << node_info_.node_name << std::endl;
    std::cout << "node info: bus_type=" << node_info_.bus_type << std::endl;
    std::cout << "node info: hostname=" << node_info_.hostname << std::endl;
    std::cout << "session established ok" << std::endl;
#endif
}

void Session::onNodeFeatureResponse(holo::bag::protocol::HbpMsgNodeFeatureResponse const& msg)
{
    updatePeerActiveTime();

    (void)msg;
}

void Session::onPortFeatureRequest(holo::bag::protocol::HbpMsgPortFeatureRequest const& msg)
{
    updatePeerActiveTime();

    if (msg.port_index < GetPortSize())
    {
        auto          port     = GetPort(msg.port_index);
        std::string   topic    = port->GetTopicName();
        std::string   metadata = port->GetMetadata();
        holo::int32_t size     = sizeof(holo::bag::protocol::HbpMsgPortFeatureResponse) + metadata.length();
        size += metadata.length();
        std::vector<holo::uint8_t>                      buffer(size, '\0');
        holo::bag::protocol::HbpMsgPortFeatureResponse* response =
            new (buffer.data()) holo::bag::protocol::HbpMsgPortFeatureResponse;

        response->InitHeader(msg.header.xid, size);

        response->port_index = msg.port_index;
        strncpy(response->topic_name, topic.c_str(), holo::bag::protocol::HbpMsgPortFeatureResponse::TOPIC_NAME_SIZE);
        response->inbound         = static_cast<holo::uint32_t>(port->IsInbound());
        response->metadata_length = metadata.length();
        if (response->metadata_length > 0U)
        {
            strncpy(response->metadata, metadata.c_str(), response->metadata_length);
        }

        if (size != underlyingWrite(buffer.data(), buffer.size(), send_timeout_))
        {
            Disconnect();
            return;
        }

#if PRINT_DEBUG_INFO
        std::cout << "port info:" << std::endl;
        std::cout << "port info: port_index=" << response->port_index << std::endl;
        std::cout << "port info: inbound=" << response->inbound << std::endl;
        std::cout << "port info: topic=" << response->topic_name << std::endl;
        std::cout << "port info: metadata_length=" << response->metadata_length << std::endl;
        if (response->metadata_length > 0U)
        {
            std::cout << "port info: metadata=" << response->metadata << std::endl;
        }
#endif
    }
    else
    {
        holo::bag::protocol::HbpMsgError error_msg;

        holo::int32_t size = sizeof(holo::bag::protocol::HbpMsgError);

        error_msg.InitHeader(msg.header.xid, size);

        error_msg.type     = msg.header.type;
        error_msg.error_no = holo::bag::protocol::HbpErrorNo::NO_SUCH_PORT;

        if (size != underlyingWrite(reinterpret_cast<holo::uint8_t*>(&error_msg), size, send_timeout_))
        {
            Disconnect();
            return;
        }
    }
}

void Session::onPortFeatureResponse(holo::bag::protocol::HbpMsgPortFeatureResponse const& msg)
{
    updatePeerActiveTime();

    (void)msg;
}

void Session::onPortConfigurationRequest(holo::bag::protocol::HbpMsgPortConfigurationRequest const& msg)
{
    updatePeerActiveTime();

    if (msg.port_index < GetPortSize())
    {
        auto port = GetPort(msg.port_index);

        holo::bag::protocol::HbpMsgPortConfigurationResponse response;

        holo::int32_t size = sizeof(holo::bag::protocol::HbpMsgPortConfigurationResponse);

        response.InitHeader(msg.header.xid, size);

        response.port_index      = msg.port_index;
        response.config_flags    = port->getConfigFlag();
        response.sample_rate     = static_cast<holo::float32_t>(port->getRecordIntervalTime());
        response.sample_interval = static_cast<holo::uint32_t>(port->getRecordIntervalCount());

        if (size != underlyingWrite(reinterpret_cast<holo::uint8_t*>(&response), size, send_timeout_))
        {
            Disconnect();
            return;
        }

#if PRINT_DEBUG_INFO
        std::cout << "port config:" << std::endl;
        std::cout << "port config: port_index=" << response.port_index << std::endl;
        std::cout << "port config: config_flags=" << response.config_flags << std::endl;
        std::cout << "port config: sample_rate=" << response.sample_rate << std::endl;
        std::cout << "port config: sample_interval=" << response.sample_interval << std::endl;
#endif
    }
    else
    {
        holo::bag::protocol::HbpMsgError error_msg;

        holo::int32_t size = sizeof(holo::bag::protocol::HbpMsgError);

        error_msg.InitHeader(msg.header.xid, size);

        error_msg.type     = msg.header.type;
        error_msg.error_no = holo::bag::protocol::HbpErrorNo::NO_SUCH_PORT;

        if (size != underlyingWrite(reinterpret_cast<holo::uint8_t*>(&error_msg), size, send_timeout_))
        {
            Disconnect();
            return;
        }
    }
}

void Session::onPortConfigurationSet(holo::bag::protocol::HbpMsgPortConfigurationSet const& msg)
{
    updatePeerActiveTime();

    if (msg.port_index < GetPortSize())
    {
        auto port = GetPort(msg.port_index);
        port->setConfigFlag(msg.config_flags);
        port->setRecordIntervalCount(msg.sample_interval);
        port->setRecordIntervalTime(static_cast<holo::int64_t>(msg.sample_rate));

        holo::bag::protocol::HbpMsgPortConfigurationResponse response;

        holo::int32_t size = sizeof(holo::bag::protocol::HbpMsgPortConfigurationResponse);

        response.InitHeader(msg.header.xid, size);

        response.port_index      = msg.port_index;
        response.config_flags    = port->getConfigFlag();
        response.sample_rate     = static_cast<holo::float32_t>(port->getRecordIntervalTime());
        response.sample_interval = static_cast<holo::uint32_t>(port->getRecordIntervalCount());

        if (size != underlyingWrite(reinterpret_cast<holo::uint8_t*>(&response), size, send_timeout_))
        {
            Disconnect();
            return;
        }

        if (holo::bag::protocol::HbpConfigFlag::DISABLE == msg.config_flags)
        {
            port->Disable();
        }
        else
        {
            port->Enable();
        }
    }
    else
    {
        holo::bag::protocol::HbpMsgError error_msg;

        holo::int32_t size = sizeof(holo::bag::protocol::HbpMsgError);

        error_msg.InitHeader(msg.header.xid, size);

        error_msg.type     = msg.header.type;
        error_msg.error_no = holo::bag::protocol::HbpErrorNo::NO_SUCH_PORT;

        if (size != underlyingWrite(reinterpret_cast<holo::uint8_t*>(&error_msg), size, send_timeout_))
        {
            Disconnect();
            return;
        }
    }
}

void Session::onPortConfigurationResponse(holo::bag::protocol::HbpMsgPortConfigurationResponse const& msg)
{
    updatePeerActiveTime();

    (void)msg;
}

void Session::onMessageIn(holo::bag::protocol::HbpMsgMessageIn const& msg)
{
    updatePeerActiveTime();

    (void)msg;
}

void Session::onMessageOut(holo::bag::protocol::HbpMsgMessageOut const& msg)
{
    updatePeerActiveTime();

    auto port = GetPort(msg.port_index);

#if PRINT_DEBUG_INFO
    std::cout << "message out,  buffer_type=" << msg.buffer_type << std::endl;
#endif

    // if (holo::bag::protocol::HbpBufferType::PAYLOAD == msg.buffer_type)
    //{
    if (port->IsEnable() && port->IsSetMessageHandler())
    {
        auto sample = std::make_shared<DataSequenceType>(msg.buffer_length);
        memcpy(sample->data(), msg.buffer, msg.buffer_length);

        if (nullptr == port->msg_queue_)
        {
            port->msg_queue_ = std::make_shared<Port::QueueType>(DEFAULT_PORT_QUEUE_CAPACITY);
        }

        if (port->msg_queue_->TryPush(sample))
        {
            if (port->obtainControl())
            {
                task_handler_([port]() {
                    std::shared_ptr<DataSequenceType> msg{nullptr};

                    do
                    {
                        msg = nullptr;
                        if (!port->msg_queue_->TryTake(msg))
                        {
                            port->releaseControl();
                            return;
                        }

                        if (port->IsEnable())
                        {
                            port->handleMessage(msg);
                        }
                    } while (true);
                });
            }

            return;
        }
        else
        {
            throw std::runtime_error{"onMessageOut: msg queue no space"};
        }
    }
    // else
    //{
    //    return;
    //}
    //}
    // else
    //{
    //}
}

void Session::onPortUpdateRequest(holo::bag::protocol::HbpMsgPortUpdateRequest const& msg)
{
    updatePeerActiveTime();

    (void)msg;
}

void Session::onErrorMsg(holo::bag::protocol::HbpMsgError const& msg)
{
    updatePeerActiveTime();

    session_state_.error_code = msg.error_no;

    switch (msg.error_no)
    {
        case holo::bag::protocol::HbpErrorNo::VERSION_MISMATCH:
        {
#if PRINT_DEBUG_INFO
            std::cout << " ErrorMsg: msg version mismatch" << std::endl;
#endif
            Disconnect();
        }
        break;

        case holo::bag::protocol::HbpErrorNo::LENGTH_TOO_SMALL:
        {
#if PRINT_DEBUG_INFO
            std::cout << " ErrorMsg: msg length too small" << std::endl;
#endif
            Disconnect();
        }
        break;

        case holo::bag::protocol::HbpErrorNo::NO_SUCH_PORT:
        {
#if PRINT_DEBUG_INFO
            std::cout << " ErrorMsg: no such port" << std::endl;
#endif
        }
        break;

        default:
        {
#if PRINT_DEBUG_INFO
            std::cout << " ErrorMsg: error_no=" << msg.error_no << std::endl;
#endif
        }
        break;
    }
}

}  // namespace agent
}  // namespace bag
}  // namespace holo
