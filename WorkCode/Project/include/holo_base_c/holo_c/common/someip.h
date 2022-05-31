/**
 * @file someip.h
 * @brief This header defins someip package and declear it's operation functions.
 * @author liuya(liuya@holomatic.com)
 * @date 2019-12-06
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_COMMON_SOMEIP_H_
#define HOLO_C_COMMON_SOMEIP_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SOMEIP_PAYLOAD_MAX_LENGTH 1024

/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief This structure defines some_ip packet.
 *
 */
struct SomeipPacket
{
    uint16_t service_id;
    uint16_t method_id;
    uint32_t msg_length;
    uint16_t client_id;
    uint16_t session_id;
    uint8_t  proto_ver;  ///< protocol version
    uint8_t  if_ver;     ///< interface version
    uint8_t  msg_type;
    uint8_t  ret_code;  ///< return code
    uint8_t  payload[SOMEIP_PAYLOAD_MAX_LENGTH];
};

/**
 * @brief Init someip packet with default value;
 *
 * @param packet The someip packet.
 *
 * @return retcode_t RC_SUCCESS.
 */
retcode_t someip_packet_init_default(struct SomeipPacket* packet);

/**
 * @brief Get 4byte aligned serialized buffer size for someip packet.
 *
 * @param packet The someip packet.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes serialized info buffer.
 *
 * @see someip_packet_get_serialized_size_8byte_aligned.
 */
uint32_t someip_packet_get_serialized_size_4byte_aligned(const struct SomeipPacket* packet);

/**
 * @brief Get 8byte aligned serialized buffer size for someip packet.
 *
 * @param packet The someip packet.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes serialized info buffer.
 *
 * @see someip_packet_get_serialized_size_4byte_aligned.
 */
uint32_t someip_packet_get_serialized_size_8byte_aligned(const struct SomeipPacket* packet);

/**
 * @brief Default get serialized buffer size for someip packet.
 *
 * @param packet The someip packet.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes serialized info buffer.
 */
uint32_t someip_packet_get_serialized_size(const struct SomeipPacket* packet);

/**
 * @brief Serialize someip packet 4byte aligned.
 *
 * @param self The someip packet.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see someip_packet_serialize_8byte_aligned
 */
retcode_t someip_packet_serialize_4byte_aligned(const struct SomeipPacket* packet, uint8_t* buffer,
                                                uint32_t buffer_size);

/**
 * @brief Serialize someip packet 8byte aligned.
 *
 * @param self The someip packet.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see someip_packet_serialize_4byte_aligned
 */
retcode_t someip_packet_serialize_8byte_aligned(const struct SomeipPacket* packet, uint8_t* buffer,
                                                uint32_t buffer_size);

/**
 * @brief Default serialize someip packet.
 *
 * @param self The someip packet.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 */
retcode_t someip_packet_serialize(const struct SomeipPacket* packet, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize someip packet 4byte aligned.
 *
 * @param self The someip packet.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see someip_packet_deserialize_8byte_aligned.
 */
retcode_t someip_packet_deserialize_4byte_aligned(struct SomeipPacket* packet, const uint8_t* buffer,
                                                  uint32_t buffer_size);

/**
 * @brief Deserialize someip packet 8byte aligned.
 *
 * @param self The someip packet.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see someip_packet_deserialize_4byte_aligned.
 */
retcode_t someip_packet_deserialize_8byte_aligned(struct SomeipPacket* packet, const uint8_t* buffer,
                                                  uint32_t buffer_size);

/**
 * @brief Default deserialize someip packet.
 *
 * @param self The someip packet.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 */
retcode_t someip_packet_deserialize(struct SomeipPacket* packet, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @{
 * Begin getter API group.
 */

/**
 * @brief Get the serivce id of someip packet.
 *
 * @param packet The someip packet.
 *
 * @return uint16_t Service id.
 */
static inline uint16_t someip_packet_get_service_id(const struct SomeipPacket* packet)
{
    return packet->service_id;
}

/**
 * @brief Get the method id of someip packet.
 *
 * @param packet The someip packet.
 *
 * @return uint16_t Method id.
 */
static inline uint16_t someip_packet_get_method_id(const struct SomeipPacket* packet)
{
    return packet->method_id;
}

/**
 * @brief Get the message length of someip packet.
 *
 * @param packet The someip packet.
 *
 * @return uint32_t Message length.
 */
static inline uint32_t someip_packet_get_msg_length(const struct SomeipPacket* packet)
{
    return packet->msg_length;
}

/**
 * @brief Get the client id of someip packet.
 *
 * @param packet The someip packet.
 *
 * @return uint16_t Client id.
 */
static inline uint16_t someip_packet_get_client_id(const struct SomeipPacket* packet)
{
    return packet->client_id;
}

/**
 * @brief Get the sessoin id of someip packet.
 *
 * @param packet The someip packet.
 *
 * @return uint16_t Session id.
 */
static inline uint16_t someip_packet_get_session_id(const struct SomeipPacket* packet)
{
    return packet->session_id;
}

/**
 * @brief Get the protocal version of someip packet.
 *
 * @param packet The someip packet.
 *
 * @return uint8_t Protocol version.
 */
static inline uint8_t someip_packet_get_protocol_version(const struct SomeipPacket* packet)
{
    return packet->proto_ver;
}

/**
 * @brief Get the interface version of someip packet.
 *
 * @param packet The someip packet.
 *
 * @return uint8_t Interface version.
 */
static inline uint8_t someip_packet_get_interface_version(const struct SomeipPacket* packet)
{
    return packet->if_ver;
}

/**
 * @brief Get the message type of someip packet.
 *
 * @param packet The someip packet.
 *
 * @return uint8_t Message type.
 */
static inline uint8_t someip_packet_get_message_type(const struct SomeipPacket* packet)
{
    return packet->msg_type;
}

/**
 * @brief Get the return code of someip packet.
 *
 * @param packet The someip packet.

 * @return uint8_t Return code.
 */
static inline uint8_t someip_packet_get_return_code(const struct SomeipPacket* packet)
{
    return packet->ret_code;
}

/**
 * @brief Get the payload content of someip packet.
 *
 * @param packet The someip packet.
 * @param buffer Buffer to get payload content.
 * @param buffer_size Size of buffer to store payload.
 *
 * @return uint8_t Positive value means payload content length.
 * @return uint8_t RC_FAIL means buffer_size less than payload content length.
 */
retcode_t someip_packet_get_payload(const struct SomeipPacket* packet, uint8_t* buffer, uint8_t buffer_size);

/**
 * @}
 * End getter API group.
 */

/**
 * @{
 * Begin setter API group.
 */

/**
 * @brief Set someip packet's method id.
 *
 * @param packet The someip packet.
 * @param id Method id.
 */
static inline void someip_packet_set_method_id(struct SomeipPacket* packet, uint16_t id)
{
    packet->method_id = id;
}

/**
 * @brief Set someip packet's service id.
 *
 * @param packet The someip packet.
 * @param id Service id.
 */
static inline void someip_packet_set_service_id(struct SomeipPacket* packet, uint16_t id)
{
    packet->service_id = id;
}

/**
 * @brief Set someip packet's message length.
 *
 * @param packet The someip packet.
 * @param length Message length.
 */
static inline void someip_packet_set_message_length(struct SomeipPacket* packet, uint32_t length)
{
    packet->msg_length = length;
}

/**
 * @brief Set someip packet's client id.
 *
 * @param packet The someip packet.
 * @param id Client id.
 */
static inline void someip_packet_set_client_id(struct SomeipPacket* packet, uint16_t id)
{
    packet->client_id = id;
}

/**
 * @brief Set someip packet's session id.
 *
 * @param packet The someip packet.
 * @param id Session id.
 */
static inline void someip_packet_set_session_id(struct SomeipPacket* packet, uint16_t id)
{
    packet->session_id = id;
}

/**
 * @brief Set someip packet's protocol version.
 *
 * @param packet The someip packet.
 * @param id Protocol version.
 */
static inline void someip_packet_set_protocol_version(struct SomeipPacket* packet, uint8_t version)
{
    packet->proto_ver = version;
}

/**
 * @brief Set someip packet's interface version.
 *
 * @param packet The someip packet.
 * @param id Interface version.
 */
static inline void someip_packet_set_interface_version(struct SomeipPacket* packet, uint8_t version)
{
    packet->if_ver = version;
}

/**
 * @brief Set someip packet's message type.
 *
 * @param packet The someip packet.
 * @param type Message type.
 */
static inline void someip_packet_set_message_type(struct SomeipPacket* packet, uint8_t type)
{
    packet->msg_type = type;
}

/**
 * @brief Set someip packet's return code.
 *
 * @param packet The someip packet.
 * @param type Return code.
 */
static inline void someip_packet_set_return_code(struct SomeipPacket* packet, uint8_t code)
{
    packet->ret_code = code;
}

/**
 * @brief Set someip packet's payload content.
 *
 * @param packet The someip packet.
 * @param buffer Payload content.
 * @param len Payload content length.
 *
 * @return retcode_t RC_SUCCESS set packet payload successed.
 * @return retocde_t RC_FAIL content length larger than payload max lenght, set failed.
 */
retcode_t someip_packet_set_payload(struct SomeipPacket* packet, const uint8_t* buffer, uint32_t len);

/**
 * @}
 * End setter API group.
 */

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_COMMON_SOMEIP_H */
