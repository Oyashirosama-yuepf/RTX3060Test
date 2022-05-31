/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file logger.h
 * @brief the header of the logger
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2020-04-29
 */

#ifndef HOLO_C_CONTROL_LOG_LOGGER_H_
#define HOLO_C_CONTROL_LOG_LOGGER_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOGGER_MAX_BUFFER 1024

extern struct Logger* global_logger_pointer;

/**
 * @brief the logger of holo_control_c
 */
struct Logger
{
    struct Timestamp stamp;  ///< timestamp

    uint32_t index;                      ///< index of buffer's feasible part
    char     buffer[LOGGER_MAX_BUFFER];  ///< buffer of data
};

/**
 * @brief Initialize the logger
 *
 * @param logger Pointer to Logger structure
 */
void logger_init_default(struct Logger* logger);

/**
 * @brief get the timestamp from Logger
 *
 * @param logger Pointer to Logger structure
 *
 * @return Timestamp
 */
const struct Timestamp* logger_get_timestamp(const struct Logger* logger);

/**
 * @brief set the timestamp from Logger
 *
 * @param logger Pointer to Logger structure
 * @param stamp input timestamp
 */
void logger_set_timestamp(struct Logger* logger, const struct Timestamp* stamp);

/**
 * @brief print log into logger's buffer
 *
 * @param logger Pointer to Logger structure
 * @param log Pointer to log data
 *
 * @return false if logger's buffer overflow, true otherwise
 */
bool_t logger_print_log(struct Logger* logger, const char* str, ...);

/**
 * @brief Get serialized buffer size for logger. Alignment is base on project configuration.
 * @detail Alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param logger The logger object.
 *
 * @return Serialized size
 */
uint32_t logger_get_serialized_size(const struct Logger* logger);

/**
 * @brief Serialize logger. Alignment is base on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param logger The logger object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW if buffer_size is smaller than needed.
 * @return Positive integer Number of bytes serialized into buffer
 */
retcode_t logger_serialize(const struct Logger* logger, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize logger object. Alignment is base on project configuration.
 * @detail The buffer alignment is define by HOLO_CONFIG_SERIALIZATION_ALIGNMENT macro.
 *
 * @param logger The logger object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed.
 * @return Positive integer Number of bytes deserialized from buffer
 */
retcode_t logger_deserialize(struct Logger* logger, const uint8_t* buffer, uint32_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_LOG_LOGGER_H_ */
