/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file someip_format.h
 * @brief the some ip packet definition
 * @author guoguangchao@holomatic.com
 * @date 2019-12-03
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_SENSORS_FORMAT_SOMEIP_H
#define HOLO_SENSORS_FORMAT_SOMEIP_H

#include <assert.h>
#include <holo/core/types.h>
#include <holo/log/hololog.h>
#include <holo/os/endian.h>
#include <holo/sensors/format/format.h>

#include <cstring>
#include <iomanip>
#include <memory>

namespace holo
{
namespace sensors
{
namespace format
{
/**
 * @brief this class describes someip packet.
 */
template <uint32_t PayloadCapacity>
class SomeipPacket : public FormatBase
{
private:
    /* someip packet layout */
    struct someip_packet_str
    {
        uint16_t service_id;
        uint16_t method_id;
        uint32_t msg_length;
        uint16_t client_id;
        uint16_t session_id;
        uint8_t  proto_ver;
        uint8_t  if_ver;
        uint8_t  msg_type;
        uint8_t  ret_code;
        uint8_t  payload[];
    };

public:
    /* message type of someip packet */
    enum Type : uint8_t
    {
        REQUEST           = 0x00,
        REQUEST_NO_RETURN = 0x01,
        NOTIFICATION      = 0x02,
        RESPONSE          = 0x80,
        ERROR             = 0x81
    };

    /* return code of someip packet */
    enum ReturnCode : uint8_t
    {
        OK                        = 0x00,
        E_NOT_OK                  = 0x01,
        E_UNKNOWN_SERVICE         = 0x02,
        E_UNKNOWN_METHOD          = 0x03,
        E_NOT_READY               = 0x04,
        E_NOT_REACHABLE           = 0x05,
        E_TIMEOUT                 = 0x06,
        E_WRONG_PROTOCOL_VERSION  = 0x07,
        E_WRONG_INTERFACE_VERSION = 0x08,
        E_MALFORMED_MESSAGE       = 0x09,
        E_WRONG_MESSAGE_TYPE      = 0x0a
        // 0x0b-0x1f Reserved for generic SOME/IP errors. These errors will be specified in future versions
        // 0x20-0x5e Reserved for specific
    };

public:
    /**
     * @brief      Constructs a new instance.
     *
     */
    SomeipPacket()
      : allocated_capacity_(PACKET_HEADER_SIZE + MESSAGE_HEADER_SIZE + PayloadCapacity)
      , allocated_(new uint8_t[allocated_capacity_](), std::default_delete<uint8_t[]>())
    {
        /* construct default object */
        (void)std::memset(allocated_.get(), 0, allocated_capacity_);
        data_             = reinterpret_cast<struct someip_packet_str*>(allocated_.get());
        data_->msg_length = holo::os::hton32(MESSAGE_HEADER_SIZE);
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  service_id The service_id
     * @param[in]  method_id  The method_id
     * @param[in]  msg_length The message length
     * @param[in]  client_id  The client_id
     * @param[in]  session_id The session_id
     * @param[in]  proto_ver  The prototype version
     * @param[in]  if_ver     The interface_version
     * @param[in]  msg_type   The message_type
     * @param[in]  ret_code   The return_code
     */
    SomeipPacket(uint16_t service_id, uint16_t method_id, uint32_t msg_length, uint16_t client_id, uint16_t session_id,
                 uint8_t proto_ver, uint8_t if_ver, uint8_t msg_type, uint8_t ret_code)
      : allocated_capacity_(PACKET_HEADER_SIZE + MESSAGE_HEADER_SIZE + PayloadCapacity)
      , allocated_(new uint8_t[allocated_capacity_](), std::default_delete<uint8_t[]>())
    {
        msg_length = std::max(msg_length, static_cast<uint32_t>(MESSAGE_HEADER_SIZE));
        msg_length = std::min(msg_length, static_cast<uint32_t>(MESSAGE_HEADER_SIZE) + PayloadCapacity);
        (void)std::memset(allocated_.get(), 0, allocated_capacity_);
        data_             = reinterpret_cast<struct someip_packet_str*>(allocated_.get());
        data_->service_id = holo::os::hton16(service_id);
        data_->method_id  = holo::os::hton16(method_id);
        data_->msg_length = holo::os::hton32(msg_length);
        data_->client_id  = holo::os::hton16(client_id);
        data_->session_id = holo::os::hton16(session_id);
        data_->proto_ver  = proto_ver;
        data_->if_ver     = if_ver;
        data_->msg_type   = msg_type;
        data_->ret_code   = ret_code;
    }
    /**
     * @brief      Sets the service identifier.
     *
     * @param[in]  service_id  The service identifier
     */
    void SetServiceId(uint16_t service_id) noexcept
    {
        data_->service_id = holo::os::hton16(service_id);
    }
    /**
     * @brief      Sets the method identifier.
     *
     * @param[in]  method_id  The method identifier
     */
    void SetMethodId(uint16_t method_id) noexcept
    {
        data_->method_id = holo::os::hton16(method_id);
    }
    /**
     * @brief      Sets the message length.
     *
     * @param[in]  msg_length  The message length in bytes
     *
     * @return     return false if msg_length larger than max_pll+8,
     *             return true if accept, ok
     */
    bool SetMsgLength(uint32_t msg_length) noexcept
    {
        if (msg_length > PayloadCapacity + MESSAGE_HEADER_SIZE)
        {
            return false;
        }
        data_->msg_length = holo::os::hton32(msg_length);
        return true;
    }
    /**
     * @brief      Sets the payload length.
     *
     * @param[in]  payload_length  The message payload length in bytes
     *
     * @return     return false if payload_length too large
     *             return true if accept, ok
     */
    bool SetPayloadLength(uint32_t payload_length) noexcept
    {
        return SetMsgLength(payload_length + MESSAGE_HEADER_SIZE);
    }
    /**
     * @brief      Sets the client identifier.
     *
     * @param[in]  client_id  The client identifier
     */
    void SetClientId(uint16_t client_id) noexcept
    {
        data_->client_id = holo::os::hton16(client_id);
    }
    /**
     * @brief      Sets the session identifier.
     *
     * @param[in]  session_id  The session identifier
     */
    void SetSessionId(uint16_t session_id) noexcept
    {
        data_->session_id = holo::os::hton16(session_id);
    }
    /**
     * @brief      Sets the prototype verison.
     *
     * @param[in]  proto_ver  The prototype version
     */
    void SetProtoVerison(uint8_t proto_ver) noexcept
    {
        data_->proto_ver = proto_ver;
    }
    /**
     * @brief      Sets if version.
     *
     * @param[in]  if_ver  If version
     */
    void SetIfVersion(uint8_t if_ver) noexcept
    {
        data_->if_ver = if_ver;
    }
    /**
     * @brief      Sets the message type.
     *
     * @param[in]  msg_type  The message type
     */
    void SetMsgType(uint8_t msg_type) noexcept
    {
        data_->msg_type = msg_type;
    }
    /**
     * @brief      Sets the return code.
     *
     * @param[in]  ret_code  The ret code
     */
    void SetReturnCode(uint8_t ret_code) noexcept
    {
        data_->ret_code = ret_code;
    }
    /**
     * @brief      Gets the message identifier.
     *
     * @return     The message identifier.
     */
    uint32_t GetMsgId() const noexcept
    {
        return uint32_t(holo::os::ntoh16(data_->service_id) << 16) + holo::os::ntoh16(data_->method_id);
    }
    /**
     * @brief      Gets the service identifier.
     *
     * @return     The service identifier.
     */
    uint16_t GetServiceId() const noexcept
    {
        return holo::os::ntoh16(data_->service_id);
    }
    /**
     * @brief      Gets the method identifier.
     *
     * @return     The method identifier.
     */
    uint16_t GetMethodId() const noexcept
    {
        return holo::os::ntoh16(data_->method_id);
    }
    /**
     * @brief      Gets the message length.
     *
     * @return     The message length.
     */
    uint32_t GetMsgLength() const noexcept
    {
        return holo::os::ntoh32(data_->msg_length);
    }
    /**
     * @brief      Gets the request identifier.
     *
     * @return     The request identifier.
     */
    uint32_t GetReqId() const noexcept
    {
        return uint32_t(holo::os::ntoh16(data_->client_id) << 16) + holo::os::ntoh16(data_->session_id);
    }
    /**
     * @brief      Gets the client identifier.
     *
     * @return     The client identifier.
     */
    uint16_t GetClientId() const noexcept
    {
        return holo::os::ntoh16(data_->client_id);
    }
    /**
     * @brief      Gets the session identifier.
     *
     * @return     The session identifier.
     */
    uint16_t GetSessionId() const noexcept
    {
        return holo::os::ntoh16(data_->session_id);
    }
    /**
     * @brief      Gets the prototype verison.
     *
     * @return     The prototype verison.
     */
    uint8_t GetProtoVerison() const noexcept
    {
        return data_->proto_ver;
    }
    /**
     * @brief      Gets Interface version.
     *
     * @return     The Interface version.
     */
    uint8_t GetIfVersion() const noexcept
    {
        return data_->if_ver;
    }
    /**
     * @brief      Gets the message type.
     *
     * @return     The message type.
     */
    uint8_t GetMsgType() const noexcept
    {
        return data_->msg_type;
    }
    /**
     * @brief      Gets the return code.
     *
     * @return     The return code.
     */
    uint8_t GetReturnCode() const noexcept
    {
        return data_->ret_code;
    }
    /**
     * @brief      Gets the payload length.
     *
     * @return     The payload length in bytes
     */
    uint32_t GetPayloadLength() const noexcept
    {
        return holo::os::ntoh32(data_->msg_length) - MESSAGE_HEADER_SIZE;
    }
    /**
     * @brief      Gets the maximum payload length this packet can hold.
     *
     * @return     The maximum payload length in bytes.
     */
    uint32_t GetPayloadCapacity() const noexcept
    {
        return PayloadCapacity;
    }
    /**
     * @brief      Sets the payload.
     *
     * @param[in]  offset  The payload offset
     * @param[in]  data    The source data address
     * @param[in]  length  The source data length
     *
     * @return     { description_of_the_return_value }
     */
    uint32_t SetPayload(uint32_t offset, const uint8_t* const data, uint32_t length) noexcept
    {
        uint32_t payload_length = holo::os::ntoh32(data_->msg_length) - MESSAGE_HEADER_SIZE;
        /* check input data */
        assert(data);
        if ((offset + length) > payload_length)
        {
            LOG(ERROR) << "unable to set payload: out of range";
            return 0;
        }
        /* copy data */
        (void)std::memcpy(data_->payload + offset, data, length);
        return length;
    }

    /**
     * @brief      Gets the payload.
     *
     * @param[in]  offset  The payload offset
     * @param      data    The target data address
     * @param[in]  length  The target data length
     *
     * @return     The payload size
     */
    uint32_t GetPayload(uint32_t offset, uint8_t* data, uint32_t length) const noexcept
    {
        uint32_t payload_length = holo::os::ntoh32(data_->msg_length) - MESSAGE_HEADER_SIZE;
        /* check input data */
        assert(data);
        if (offset >= payload_length)
        {
            LOG(ERROR) << "unable to get payload: out of range";
            return 0;
        }
        /* copy data */
        auto len = std::min<uint32_t>(length, payload_length - offset);
        (void)std::memcpy(data, data_->payload + offset, len);
        return len;
    }

    uint8_t* GetPayload() const noexcept
    {
        return data_->payload;
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return holo::os::ntoh32(data_->msg_length) + PACKET_HEADER_SIZE;
    }

    uint32_t Serialize(uint8_t* data, uint32_t length) const noexcept
    {
        const uint32_t total_length = holo::os::ntoh32(data_->msg_length) + PACKET_HEADER_SIZE;
        if (length != total_length)
        {
            return 0;
        }
        (void)std::memcpy(data, data_, total_length);
        return total_length;
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t length)
    {
        auto           ptr          = reinterpret_cast<const struct someip_packet_str*>(data);
        const uint32_t total_length = holo::os::ntoh32(ptr->msg_length) + PACKET_HEADER_SIZE;
        if (length != total_length)
        {
            LOG(ERROR) << "unable to deserialize: bad data";
            return 0;
        }
        (void)std::memcpy(data_, data, total_length);
        return total_length;
    }

    std::string ToString() const
    {
        std::stringstream ss;
        ss << "someip packet: \n"
           << "msg_id           (u32) = " << std::hex << "0x" << static_cast<uint32_t>(GetMsgId()) << "\n"
           << "service_id       (u16) = " << std::hex << "0x" << static_cast<uint32_t>(GetServiceId()) << "\n"
           << "method_id        (u16) = " << std::hex << "0x" << static_cast<uint32_t>(GetMethodId()) << "\n"
           << "msg_length       (u32) = " << std::hex << "0x" << static_cast<uint32_t>(GetMsgLength()) << "\n"
           << "req_id           (u32) = " << std::hex << "0x" << static_cast<uint32_t>(GetReqId()) << "\n"
           << "client_id        (u16) = " << std::hex << "0x" << static_cast<uint32_t>(GetClientId()) << "\n"
           << "session_id       (u16) = " << std::hex << "0x" << static_cast<uint32_t>(GetSessionId()) << "\n"
           << "proto_verison    (u08) = " << std::hex << "0x" << static_cast<uint32_t>(GetProtoVerison()) << "\n"
           << "if_version       (u08) = " << std::hex << "0x" << static_cast<uint32_t>(GetIfVersion()) << "\n"
           << "msg_type         (u08) = " << std::hex << "0x" << static_cast<uint32_t>(GetMsgType()) << "\n"
           << "return_code      (u08) = " << std::hex << "0x" << static_cast<uint32_t>(GetReturnCode()) << "\n"
           << "payload_length   (u32) = " << std::hex << "0x" << static_cast<uint32_t>(GetPayloadLength()) << "\n"
           << "payload_capacity (u32) = " << std::hex << "0x" << static_cast<uint32_t>(GetPayloadCapacity()) << "\n";
        uint32_t payload_len = GetPayloadLength();
        if (payload_len > 0)
        {
            ss << "payload :";
            for (uint32_t i = 0; i < payload_len; ++i)
            {
                uint8_t byte = 0;
                (void)GetPayload(i, &byte, 1);
                ss << " 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(byte);
            }
        }
        ss << std::endl;
        return ss.str();
    }

private:
    /* const values for someip packet access and default values */
    static constexpr uint32_t PACKET_HEADER_SIZE  = 8u;
    static constexpr uint32_t MESSAGE_HEADER_SIZE = 8u;
    /* memory aloocated for packet */
    size_t                   allocated_capacity_;
    std::shared_ptr<uint8_t> allocated_;
    /* data struct ptr for fast access */
    struct someip_packet_str* data_;
};

}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif
