/**
 * @file light_signal_request.h
 * @brief This header file define light signal request.
 * @author lijiawen@holomatic.com
 * @date 2019-11-28
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_COMMON_LIGHT_SIGNAL_REQUEST_H_
#define HOLO_C_COMMON_LIGHT_SIGNAL_REQUEST_H_

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief this struct is used to describe the light signal's request
 */
struct LightSignalRequest
{
    struct Timestamp stamp;  ///< timestamp

    struct
    {
        uint16_t : 1;                    ///< Rear fog light: 1=on, 0=off
        uint16_t : 1;                    ///< Front fog light: 1=on, 0=off
        uint16_t brake_light : 1;        ///< Break light signal: 1=on, 0=off
        uint16_t : 1;                    ///< High beam light: 1=on, 0=off
        uint16_t : 1;                    ///< Low beam light: 1=on, 0=off
        uint16_t hazard_flasher : 1;     ///< hazard flasher signal: 1=on, 0=off
        uint16_t right_turn_signal : 1;  ///< Right turn signal: 1=on, 0=off
        uint16_t left_turn_signal : 1;   ///< Left turn signal: 1=on, 0=off
        uint16_t : 8;
    } light_command;

    uint8_t reserved[6];  ///< reserved for data alignment.
};
HOLO_STATIC_ASSERT(sizeof(struct LightSignalRequest) == 16UL);

/**
 * @brief initialize LightSignalRequest from default values
 *
 * @param request The pointer to a LightSignalRequest.
 */
void light_signal_request_init_default(struct LightSignalRequest* request);

/**
 * @brief get the timestamp from LightSignalRequest
 *
 * @param request The pointer to a LightSignalRequest.
 *
 * @return the timestamp of the light_signal_request
 */
const struct Timestamp* light_signal_request_get_timestamp(const struct LightSignalRequest* request);

/**
 * @brief set the timestamp of LightSignalRequest
 *
 * @param request The pointer to a LightSignalRequest.
 * @param stamp The input timestamp.
 */
void light_signal_request_set_timestamp(struct LightSignalRequest* request, const struct Timestamp* stamp);

/**
 * @brief Get light system control request.
 *
 * @param request The pointer to a LightSignalRequest.
 *
 * @return the light_command
 */
uint16_t light_signal_request_get_light_command(const struct LightSignalRequest* request);

/**
 * @brief Set light system control request.
 *
 * @param request The pointer to a LightSignalRequest.
 * @param value The input light_command.
 */
void light_signal_request_set_light_command(struct LightSignalRequest* request, uint16_t value);

/**
 * @brief get the left_turn_signal of LightSignalRequest
 *
 * @param request The pointer to a LightSignalRequest.
 *
 * @return left_turn_signal
 */
bool_t light_signal_request_get_left_turn_signal(const struct LightSignalRequest* request);

/**
 * @brief set the left_turn_signal of LightSignalRequest
 *
 * @param request The pointer to a LightSignalRequest.
 * @param left_turn_signal The left_turn_signal to be set in.
 */
void light_signal_request_set_left_turn_signal(struct LightSignalRequest* request, bool_t value);

/**
 * @brief get the right_turn_signal of LightSignalRequest
 *
 * @param request The pointer to a LightSignalRequest.
 *
 * @return right_turn_signal
 */
bool_t light_signal_request_get_right_turn_signal(const struct LightSignalRequest* request);

/**
 * @brief set the right_turn_signal of LightSignalRequest
 *
 * @param request The pointer to a LightSignalRequest.
 * @param right_turn_signal The right_turn_signal to be set in.
 */
void light_signal_request_set_right_turn_signal(struct LightSignalRequest* request, bool_t value);

/**
 * @brief set the hazard_flasher of LightSignalRequest
 *
 * @param request The pointer to a LightSignalRequest.
 *
 * @return hazard_flasher
 */
bool_t light_signal_request_get_hazard_flasher(const struct LightSignalRequest* request);

/**
 * @brief set the hazard_flasher of LightSignalRequest
 *
 * @param request The pointer to a LightSignalRequest.
 * @param hazard_flasher The hazard_flasher to be set in.
 */
void light_signal_request_set_hazard_flasher(struct LightSignalRequest* request, bool_t value);

/**
 * @brief set the brake_light of LightSignalRequest
 *
 * @param request The pointer to a LightSignalRequest.
 *
 * @return brake_light
 */
bool_t light_signal_request_get_brake_light(const struct LightSignalRequest* request);

/**
 * @brief set the brake_light of LightSignalRequest
 *
 * @param request The pointer to a LightSignalRequest.
 * @param brake_light The brake_light to be set in.
 */
void light_signal_request_set_brake_light(struct LightSignalRequest* request, bool_t value);

/**
 * @{
 * Begin serialization/deserialization API group
 */

/**
 * @brief Get serialized buffer size for LightSignalRequest. 
 *
 * @param request The LightSignalRequest object.
 *
 * @return Serialized size
 */
uint32_t light_signal_request_get_serialized_size(const struct LightSignalRequest* request);

/**
 * @brief Serialize LightSignalRequest. 
 *
 * @param request The LightSignalRequest object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive integer Number of bytes serialized into buffer
 */
retcode_t light_signal_request_serialize(const struct LightSignalRequest* request, 
                                         uint8_t* buffer,
                                         uint32_t buffer_size);

/**
 * @brief Deserialize LightSignalRequest object. 
 *
 * @param request The LightSignalRequest object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive integer Number of bytes deserialized from buffer
 */
retcode_t light_signal_request_deserialize(struct LightSignalRequest* request, 
                                           const uint8_t* buffer,
                                           uint32_t buffer_size);

/**
 * @}
 * End serialization/deserialization API group.
 */

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_COMMON_LIGHT_SIGNAL_REQUEST_H_ */
