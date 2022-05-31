#include <assert.h>
#include <holo/bag/protocol/protocol.h>
#include <stdexcept>

namespace holo
{
namespace bag
{
namespace protocol
{
HbpProtocol::HbpProtocol() noexcept
  : echo_request_handler_{nullptr}
  , echo_response_handler_{nullptr}
  , node_feature_request_handler_{nullptr}
  , node_feature_response_handler_{nullptr}
  , port_feature_request_handler_{nullptr}
  , port_feature_response_handler_{nullptr}
  , port_configuration_request_handler_{nullptr}
  , port_configuration_set_handler_{nullptr}
  , port_configuration_response_handler_{nullptr}
  , message_in_handler_{nullptr}
  , message_out_handler_{nullptr}
  , port_update_request_handler_{nullptr}
  , error_msg_handler_{nullptr}
{
}

void HbpProtocol::Analysis(holo::uint32_t& offset, holo::uint32_t& reserved, holo::uint8_t const* data,
                           holo::uint32_t const data_size)
{
    offset   = 0U;
    reserved = data_size;

    while (reserved >= HEADER_LENGTH)
    {
        HbpHeader const* header = reinterpret_cast<HbpHeader const*>(data);

        if (header->length < HEADER_LENGTH)
        {
            handleError(header, HbpErrorNo::LENGTH_TOO_SMALL);
            offset += HEADER_LENGTH;
            reserved -= HEADER_LENGTH;
            data += HEADER_LENGTH;
            break;
        }

        if (header->length > reserved)
        {
            break;
        }

        if (VERSION != header->version)
        {
            handleError(header, HbpErrorNo::VERSION_MISMATCH);
            offset += header->length;
            reserved -= header->length;
            data += header->length;
            continue;
        }

        handleMessage(header);

        offset += header->length;
        reserved -= header->length;
        data += header->length;
    }
}

void HbpProtocol::handleError(HbpHeader const* header, holo::uint32_t const error_no)
{
    HbpMsgError error_info;

    error_info.header.length = sizeof(HbpMsgError);
    error_info.header.xid    = header->xid;

    error_info.type     = header->type;
    error_info.error_no = error_no;

    assert(nullptr != error_msg_handler_);
    error_msg_handler_(error_info);
}

void HbpProtocol::handleMessage(HbpHeader const* header)
{
    switch (header->type)
    {
        case HbpCommand::HELLO:
        {
            assert(nullptr != hello_msg_handler_);

            HbpMsgHello const* message = reinterpret_cast<HbpMsgHello const*>(header);
            hello_msg_handler_(*message);
        }
        break;

        case HbpCommand::ECHO_REQUEST:
        {
            assert(nullptr != echo_request_handler_);

            HbpMsgEchoRequest const* message = reinterpret_cast<HbpMsgEchoRequest const*>(header);
            echo_request_handler_(*message);
        }
        break;

        case HbpCommand::ECHO_RESPONSE:
        {
            assert(nullptr != echo_response_handler_);

            HbpMsgEchoResponse const* message = reinterpret_cast<HbpMsgEchoResponse const*>(header);
            echo_response_handler_(*message);
        }
        break;

        case HbpCommand::NODE_FEATURE_REQUEST:
        {
            assert(nullptr != node_feature_request_handler_);

            HbpMsgNodeFeatureRequest const* message = reinterpret_cast<HbpMsgNodeFeatureRequest const*>(header);
            node_feature_request_handler_(*message);
        }
        break;

        case HbpCommand::NODE_FEATURE_RESPONSE:
        {
            assert(nullptr != node_feature_response_handler_);

            HbpMsgNodeFeatureResponse const* message = reinterpret_cast<HbpMsgNodeFeatureResponse const*>(header);
            node_feature_response_handler_(*message);
        }
        break;

        case HbpCommand::PORT_FEATURE_REQUEST:
        {
            assert(nullptr != port_feature_request_handler_);

            HbpMsgPortFeatureRequest const* message = reinterpret_cast<HbpMsgPortFeatureRequest const*>(header);
            port_feature_request_handler_(*message);
        }
        break;

        case HbpCommand::PORT_FEATURE_RESPONSE:
        {
            assert(nullptr != port_feature_response_handler_);

            HbpMsgPortFeatureResponse const* message = reinterpret_cast<HbpMsgPortFeatureResponse const*>(header);
            port_feature_response_handler_(*message);
        }
        break;

        case HbpCommand::PORT_CONFIGURATION_REQUEST:
        {
            assert(nullptr != port_configuration_request_handler_);

            HbpMsgPortConfigurationRequest const* message =
                reinterpret_cast<HbpMsgPortConfigurationRequest const*>(header);
            port_configuration_request_handler_(*message);
        }
        break;

        case HbpCommand::PORT_CONFIGURATION_SET:
        {
            assert(nullptr != port_configuration_set_handler_);

            HbpMsgPortConfigurationSet const* message = reinterpret_cast<HbpMsgPortConfigurationSet const*>(header);
            port_configuration_set_handler_(*message);
        }
        break;

        case HbpCommand::PORT_CONFIGURATION_RESPONSE:
        {
            assert(nullptr != port_configuration_response_handler_);

            HbpMsgPortConfigurationResponse const* message =
                reinterpret_cast<HbpMsgPortConfigurationResponse const*>(header);
            port_configuration_response_handler_(*message);
        }
        break;

        case HbpCommand::MESSAGE_OUT:
        {
            assert(nullptr != message_out_handler_);

            HbpMsgMessageOut const* message = reinterpret_cast<HbpMsgMessageOut const*>(header);
            message_out_handler_(*message);
        }
        break;

        case HbpCommand::PORT_UPDATE_REQUEST:
        {
            assert(nullptr != port_update_request_handler_);

            HbpMsgPortUpdateRequest const* message = reinterpret_cast<HbpMsgPortUpdateRequest const*>(header);
            port_update_request_handler_(*message);
        }
        break;

        case HbpCommand::MESSAGE_IN:
        {
            assert(nullptr != message_in_handler_);

            HbpMsgMessageIn const* message = reinterpret_cast<HbpMsgMessageIn const*>(header);
            message_in_handler_(*message);
        }
        break;

        case HbpCommand::ERROR:
        {
            assert(nullptr != error_msg_handler_);

            HbpMsgError const* message = reinterpret_cast<HbpMsgError const*>(header);
            error_msg_handler_(*message);
        }
        break;

        default:
        {
            throw std::runtime_error{"Unknow Message"};
        }
        break;
    }
}

void HbpProtocol::SetHelloMsgHandler(HelloMsgHandler const& handler)
{
    hello_msg_handler_ = handler;
}

void HbpProtocol::SetEchoRequestHandler(EchoRequestHandler const& handler)
{
    echo_request_handler_ = handler;
}

void HbpProtocol::SetEchoResponseHandler(EchoResponseHandler const& handler)
{
    echo_response_handler_ = handler;
}

void HbpProtocol::SetNodeFeatureRequestHandler(NodeFeatureRequestHandler const& handler)
{
    node_feature_request_handler_ = handler;
}

void HbpProtocol::SetNodeFeatureResponseHandler(NodeFeatureResponseHandler const& handler)
{
    node_feature_response_handler_ = handler;
}

void HbpProtocol::SetPortFeatureRequestHandler(PortFeatureRequestHandler const& handler)
{
    port_feature_request_handler_ = handler;
}

void HbpProtocol::SetPortFeatureResponseHandler(PortFeatureResponseHandler const& handler)
{
    port_feature_response_handler_ = handler;
}

void HbpProtocol::SetPortConfigurationRequestHandler(PortConfigurationRequestHandler const& handler)
{
    port_configuration_request_handler_ = handler;
}

void HbpProtocol::SetPortConfigurationSetHandler(PortConfigurationSetHandler const& handler)
{
    port_configuration_set_handler_ = handler;
}

void HbpProtocol::SetPortConfigurationResponseHandler(PortConfigurationResponseHandler const& handler)
{
    port_configuration_response_handler_ = handler;
}

void HbpProtocol::SetMessageInHandler(MessageInHandler const& handler)
{
    message_in_handler_ = handler;
}

void HbpProtocol::SetMessageOutHandler(MessageOutHandler const& handler)
{
    message_out_handler_ = handler;
}

void HbpProtocol::SetPortUpdateRequestHandler(PortUpdateRequestHandler const& handler)
{
    port_update_request_handler_ = handler;
}

void HbpProtocol::SetErrorMsgHandler(ErrorMsgHandler const& handler)
{
    error_msg_handler_ = handler;
}

}  // namespace protocol
}  // namespace bag
}  // namespace holo
