#ifndef HOLO_BAG_PROTOCOL_PROTOCOL_H
#define HOLO_BAG_PROTOCOL_PROTOCOL_H

#include <functional>
#include <memory>

#include <holo/core/types.h>

namespace holo
{
namespace bag
{
namespace protocol
{
#define HOLO_BAG_PROTOCOL_VERSION (0x01)

struct HbpCommand
{
    static constexpr holo::uint16_t HELLO                       = 0x01;
    static constexpr holo::uint16_t ECHO_REQUEST                = 0x02;
    static constexpr holo::uint16_t ECHO_RESPONSE               = 0x03;
    static constexpr holo::uint16_t NODE_FEATURE_REQUEST        = 0x10;
    static constexpr holo::uint16_t NODE_FEATURE_RESPONSE       = 0x11;
    static constexpr holo::uint16_t PORT_FEATURE_REQUEST        = 0x12;
    static constexpr holo::uint16_t PORT_FEATURE_RESPONSE       = 0x13;
    static constexpr holo::uint16_t PORT_CONFIGURATION_REQUEST  = 0x14;
    static constexpr holo::uint16_t PORT_CONFIGURATION_SET      = 0x15;
    static constexpr holo::uint16_t PORT_CONFIGURATION_RESPONSE = 0x16;
    static constexpr holo::uint16_t MESSAGE_OUT                 = 0x17;
    static constexpr holo::uint16_t PORT_UPDATE_REQUEST         = 0x40;
    static constexpr holo::uint16_t MESSAGE_IN                  = 0x41;
    static constexpr holo::uint16_t ERROR                       = 0x42;
};

struct HbpErrorNo
{
    static constexpr holo::uint32_t VERSION_MISMATCH = 0x01;
    static constexpr holo::uint32_t LENGTH_TOO_SMALL = 0x02;
    static constexpr holo::uint32_t NO_SUCH_PORT     = 0x03;
};

struct HbpConfigFlag
{
    static constexpr holo::uint32_t DISABLE = 0x00;
    static constexpr holo::uint32_t RECORD  = 0x01;
    static constexpr holo::uint32_t REPLAY  = 0x02;
};

struct HbpBufferType
{
    static constexpr holo::uint32_t PAYLOAD = 0U;
    static constexpr holo::uint32_t NOTIFY  = 1U;
};

struct HbpHeader
{
    holo::uint16_t version;
    holo::uint16_t type;
    holo::uint32_t length;
    holo::uint32_t xid;

    HbpHeader() noexcept : version{HOLO_BAG_PROTOCOL_VERSION}, type{0U}, length{0U}, xid{0U}
    {
    }

    HbpHeader(holo::uint16_t const t) noexcept : version{HOLO_BAG_PROTOCOL_VERSION}, type{t}, length{0U}, xid{0U}
    {
    }
};

struct HbpMsgHello
{
    HbpHeader header;

    HbpMsgHello() noexcept : header{HbpCommand::HELLO}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::HELLO;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgEchoRequest
{
    HbpHeader header;

    HbpMsgEchoRequest() noexcept : header{HbpCommand::ECHO_REQUEST}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::ECHO_REQUEST;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgEchoResponse
{
    HbpHeader header;

    HbpMsgEchoResponse() noexcept : header{HbpCommand::ECHO_RESPONSE}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::ECHO_RESPONSE;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgNodeFeatureRequest
{
    HbpHeader header;

    HbpMsgNodeFeatureRequest() noexcept : header{HbpCommand::NODE_FEATURE_REQUEST}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::NODE_FEATURE_REQUEST;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgNodeFeatureResponse
{
    static constexpr holo::uint32_t BUS_TYPE_SIZE = 16U;
    static constexpr holo::uint32_t HOSTNAME_SIZE = 64U;

    HbpHeader      header;
    holo::uint32_t host_id;
    holo::uint32_t pid;
    holo::uint32_t tid;
    holo::char_t   bus_type[BUS_TYPE_SIZE];
    holo::uint32_t domain_id;
    holo::uint32_t total_ports;
    holo::uint8_t  hw_address[6U];
    holo::uint8_t  reserved[2U];
    holo::char_t   hostname[HOSTNAME_SIZE];

    HbpMsgNodeFeatureResponse() noexcept : header{HbpCommand::NODE_FEATURE_RESPONSE}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::NODE_FEATURE_RESPONSE;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgPortFeatureRequest
{
    HbpHeader      header;
    holo::uint32_t port_index;

    HbpMsgPortFeatureRequest() noexcept : header{HbpCommand::PORT_FEATURE_REQUEST}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::PORT_FEATURE_REQUEST;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgPortFeatureResponse
{
    static constexpr holo::uint32_t TOPIC_NAME_SIZE = 128U;

    HbpHeader      header;
    holo::uint32_t port_index;
    holo::char_t   topic_name[TOPIC_NAME_SIZE];
    holo::uint32_t inbound;
    holo::uint32_t metadata_length;
    holo::char_t   metadata[0U];

    HbpMsgPortFeatureResponse() noexcept : header{HbpCommand::PORT_FEATURE_RESPONSE}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::PORT_FEATURE_RESPONSE;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgPortConfigurationRequest
{
    HbpHeader      header;
    holo::uint32_t port_index;

    HbpMsgPortConfigurationRequest() noexcept : header{HbpCommand::PORT_CONFIGURATION_REQUEST}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::PORT_CONFIGURATION_REQUEST;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgPortConfigurationSet
{
    HbpHeader       header;
    holo::uint32_t  port_index;
    holo::uint32_t  config_flags;
    holo::float32_t sample_rate;
    holo::uint32_t  sample_interval;

    HbpMsgPortConfigurationSet() noexcept : header{HbpCommand::PORT_CONFIGURATION_SET}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::PORT_CONFIGURATION_SET;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgPortConfigurationResponse
{
    HbpHeader       header;
    holo::uint32_t  port_index;
    holo::uint32_t  config_flags;
    holo::float32_t sample_rate;
    holo::uint32_t  sample_interval;

    HbpMsgPortConfigurationResponse() noexcept : header{HbpCommand::PORT_CONFIGURATION_RESPONSE}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::PORT_CONFIGURATION_RESPONSE;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgMessageIn
{
    HbpHeader      header;
    holo::uint32_t port_index;
    holo::uint32_t buffer_type;
    holo::uint32_t buffer_length;
    holo::uint8_t  buffer[0U];

    HbpMsgMessageIn() noexcept : header{HbpCommand::MESSAGE_IN}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::MESSAGE_IN;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgMessageOut
{
    HbpHeader      header;
    holo::uint32_t port_index;
    holo::uint32_t buffer_type;
    holo::uint32_t buffer_length;
    holo::uint8_t  buffer[0U];

    HbpMsgMessageOut() noexcept : header{HbpCommand::MESSAGE_OUT}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::MESSAGE_OUT;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgPortUpdateRequest
{
    static constexpr holo::uint32_t TOPIC_NAME_SIZE = 128U;

    HbpHeader      header;
    holo::uint32_t port_index;
    holo::char_t   topic_name[TOPIC_NAME_SIZE];
    holo::uint32_t inbound;
    holo::uint32_t metadata_length;
    holo::char_t   metadata[0U];

    HbpMsgPortUpdateRequest() noexcept : header{HbpCommand::PORT_UPDATE_REQUEST}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::PORT_UPDATE_REQUEST;
        header.length  = length;
        header.xid     = xid;
    }
};

struct HbpMsgError
{
    HbpHeader      header;
    holo::uint16_t type;
    holo::uint16_t reserved;
    holo::uint32_t error_no;

    HbpMsgError() noexcept : header{HbpCommand::ERROR}
    {
    }

    void InitHeader(holo::uint32_t const xid, holo::uint32_t const length)
    {
        header.version = HOLO_BAG_PROTOCOL_VERSION;
        header.type    = HbpCommand::ERROR;
        header.length  = length;
        header.xid     = xid;
    }
};

class HbpProtocol
{
public:
    static constexpr holo::uint16_t VERSION       = HOLO_BAG_PROTOCOL_VERSION;
    static constexpr holo::uint32_t HEADER_LENGTH = sizeof(HbpHeader);

    using HelloMsgHandler                  = std::function<void(HbpMsgHello const&)>;
    using EchoRequestHandler               = std::function<void(HbpMsgEchoRequest const&)>;
    using EchoResponseHandler              = std::function<void(HbpMsgEchoResponse const&)>;
    using NodeFeatureRequestHandler        = std::function<void(HbpMsgNodeFeatureRequest const&)>;
    using NodeFeatureResponseHandler       = std::function<void(HbpMsgNodeFeatureResponse const&)>;
    using PortFeatureRequestHandler        = std::function<void(HbpMsgPortFeatureRequest const&)>;
    using PortFeatureResponseHandler       = std::function<void(HbpMsgPortFeatureResponse const&)>;
    using PortConfigurationRequestHandler  = std::function<void(HbpMsgPortConfigurationRequest const&)>;
    using PortConfigurationSetHandler      = std::function<void(HbpMsgPortConfigurationSet const&)>;
    using PortConfigurationResponseHandler = std::function<void(HbpMsgPortConfigurationResponse const&)>;
    using MessageInHandler                 = std::function<void(HbpMsgMessageIn const&)>;
    using MessageOutHandler                = std::function<void(HbpMsgMessageOut const&)>;
    using PortUpdateRequestHandler         = std::function<void(HbpMsgPortUpdateRequest const&)>;
    using ErrorMsgHandler                  = std::function<void(HbpMsgError const&)>;

    HbpProtocol() noexcept;

    void Analysis(holo::uint32_t& offset, holo::uint32_t& reserved, holo::uint8_t const* data,
                  holo::uint32_t const data_size);

    void SetHelloMsgHandler(HelloMsgHandler const& handler);
    void SetEchoRequestHandler(EchoRequestHandler const& handler);
    void SetEchoResponseHandler(EchoResponseHandler const& handler);
    void SetNodeFeatureRequestHandler(NodeFeatureRequestHandler const& handler);
    void SetNodeFeatureResponseHandler(NodeFeatureResponseHandler const& handler);
    void SetPortFeatureRequestHandler(PortFeatureRequestHandler const& handler);
    void SetPortFeatureResponseHandler(PortFeatureResponseHandler const& handler);
    void SetPortConfigurationRequestHandler(PortConfigurationRequestHandler const& handler);
    void SetPortConfigurationSetHandler(PortConfigurationSetHandler const& handler);
    void SetPortConfigurationResponseHandler(PortConfigurationResponseHandler const& handler);
    void SetMessageInHandler(MessageInHandler const& handler);
    void SetMessageOutHandler(MessageOutHandler const& handler);
    void SetPortUpdateRequestHandler(PortUpdateRequestHandler const& handler);
    void SetErrorMsgHandler(ErrorMsgHandler const& handler);

private:
    void handleError(HbpHeader const* header, holo::uint32_t const error_no);

    void handleMessage(HbpHeader const* header);

private:
    HelloMsgHandler                  hello_msg_handler_;
    EchoRequestHandler               echo_request_handler_;
    EchoResponseHandler              echo_response_handler_;
    NodeFeatureRequestHandler        node_feature_request_handler_;
    NodeFeatureResponseHandler       node_feature_response_handler_;
    PortFeatureRequestHandler        port_feature_request_handler_;
    PortFeatureResponseHandler       port_feature_response_handler_;
    PortConfigurationRequestHandler  port_configuration_request_handler_;
    PortConfigurationSetHandler      port_configuration_set_handler_;
    PortConfigurationResponseHandler port_configuration_response_handler_;
    MessageInHandler                 message_in_handler_;
    MessageOutHandler                message_out_handler_;
    PortUpdateRequestHandler         port_update_request_handler_;
    ErrorMsgHandler                  error_msg_handler_;
};

}  // namespace protocol
}  // namespace bag
}  // namespace holo

#endif
