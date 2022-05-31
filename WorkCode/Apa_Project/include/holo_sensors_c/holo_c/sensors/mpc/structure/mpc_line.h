/*!
 * @file mpc_line.h
 * @brief This header file defines bosch mpc line raw data structure and functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_MPC_STRUCTURE_MPC_LINE_H_
#define HOLO_C_SENSORS_MPC_STRUCTURE_MPC_LINE_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/types.h>
#include <holo_c/sensors/dbc/mpc_recv_dbc.h>
#include <holo_c/utils/serialization.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 *
 */

#define MPC_LINE_NUM 4

/**
 * @brief Mpc Line raw data struct
 *
 */
struct MpcLineRawData
{
    struct Timestamp timestamp;

    uint16_t confidence;
    uint16_t id;
    uint16_t type;
    uint16_t width;
    uint16_t color;

    uint16_t dx_begin;
    uint16_t dx_end;
    uint16_t dy;

    uint16_t angle_diff;
    uint16_t horizon_curve;
};
HOLO_STATIC_ASSERT(sizeof(struct MpcLineRawData) == 28);

struct MpcLinesRawData
{
    struct MpcLineRawData left_left_line;
    struct MpcLineRawData left_line;
    struct MpcLineRawData right_line;
    struct MpcLineRawData right_right_line;
};
HOLO_STATIC_ASSERT(sizeof(struct MpcLinesRawData) == 112);

/**
 * @{
 * Begin setter API group.
 */

/**
 * @brief set mpc line raw data timestamp
 *
 * @param line_raw_data mpc line raw data poiter
 * @param timestamp system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mpc_line_raw_data_set_timestamp(struct MpcLineRawData*  line_raw_data,
                                                   const struct Timestamp* timestamp)
{
    line_raw_data->timestamp = *timestamp;
}

/**
 * @brief set mpc line raw data confidence
 *
 * @param line_raw_data mpc line raw data pointer
 * @param confidence data confidence
 * @return retcode_t RC_SUCCESS
 */
static inline void mpc_line_raw_data_set_confidence(struct MpcLineRawData* line_raw_data, uint16_t confidence)
{
    line_raw_data->confidence = confidence;
}

/**
 * @brief set mpc line raw data line id
 *
 * @param line_raw_data mpc line raw data pointer
 * @param id line id
 * @return retcode_t RC_SUCCESS
 */
static inline void mpc_line_raw_data_set_id(struct MpcLineRawData* line_raw_data, uint16_t id)
{
    line_raw_data->id = id;
}

/**
 * @brief set mpc line raw data line type
 *
 * @param line_raw_data mpc line raw data pointer
 * @param type line type
 * @return retcode_t RC_SUCCESS
 */
static inline void mpc_line_raw_data_set_type(struct MpcLineRawData* line_raw_data, uint16_t type)
{
    line_raw_data->type = type;
}

/**
 * @brief set mpc line raw data line width
 *
 * @param line_raw_data mpc line raw data pointer
 * @param width line width
 * @return retcode_t RC_SUCCESS
 */
static inline void mpc_line_raw_data_set_width(struct MpcLineRawData* line_raw_data, uint16_t width)
{
    line_raw_data->width = width;
}

/**
 * @brief set mpc line raw data line color
 *
 * @param line_raw_data mpc line raw data pointer
 * @param color line color
 * @return retcode_t RC_SUCCESS
 */
static inline void mpc_line_raw_data_set_color(struct MpcLineRawData* line_raw_data, uint16_t color)
{
    line_raw_data->color = color;
}

/**
 * @brief set mpc line raw data dx begin
 *
 * @param line_raw_data mpc line raw data pointer
 * @param dx_begin line dx begin
 * @return retcode_t RC_SUCCESS
 */
static inline void mpc_line_raw_data_set_dx_begin(struct MpcLineRawData* line_raw_data, uint16_t dx_begin)
{
    line_raw_data->dx_begin = dx_begin;
}

/**
 * @brief set mpc line raw data line dx end
 *
 * @param line_raw_data mpc line raw data pointer
 * @param dx_end line dx_end
 * @return retcode_t RC_SUCCESS
 */
static inline void mpc_line_raw_data_set_dx_end(struct MpcLineRawData* line_raw_data, uint16_t dx_end)
{
    line_raw_data->dx_end = dx_end;
}

/**
 * @brief set mpc line raw data line dy
 *
 * @param line_raw_data mpc line raw data pointer
 * @param dy line dy
 * @return retcode_t RC_SUCCESS
 */
static inline void mpc_line_raw_data_set_dy(struct MpcLineRawData* line_raw_data, uint16_t dy)
{
    line_raw_data->dy = dy;
}

/**
 * @brief set mpc line raw data line angle diff
 *
 * @param line_raw_data mpc line raw data pointer
 * @param angle_diff line angle diff
 * @return retcode_t RC_SUCCESS
 */
static inline void mpc_line_raw_data_set_angle_diff(struct MpcLineRawData* line_raw_data, uint16_t angle_diff)
{
    line_raw_data->angle_diff = angle_diff;
}

/**
 * @brief set mpc line raw data line horizon curve
 *
 * @param line_raw_data mpc line raw data pointer
 * @param horizon_curve line horizen cure
 * @return retcode_t RC_SUCCESS
 */
static inline void mpc_line_raw_data_set_horizon_curve(struct MpcLineRawData* line_raw_data, uint16_t horizon_curve)
{
    line_raw_data->horizon_curve = horizon_curve;
}

/**
 * @}
 * End setter API group.
 */

/**
 * @{
 * Begin getter API group.
 */

/**
 * @brief get mpc line raw data timestamp
 *
 * @param line_raw_data mpc line raw data pointer
 * @param timestamp timestamp pointer
 * @return retcode_t RC_SUCCE
 */
static inline const struct Timestamp* mpc_line_raw_data_get_timestamp(struct MpcLineRawData* line_raw_data)
{
    return &line_raw_data->timestamp;
}

/**
 * @brief get mpc line raw data confidence
 *
 * @param line_raw_data mpc line raw data pointer
 * @return uint16_t confidence
 */
static inline uint16_t mpc_line_raw_data_get_confidence(struct MpcLineRawData* line_raw_data)
{
    return line_raw_data->confidence;
}

/**
 * @brief get mpc line raw data line id
 *
 * @param line_raw_data mpc line raw data pointer
 * @return uint16_t line id
 */
static inline uint16_t mpc_line_raw_data_get_id(struct MpcLineRawData* line_raw_data)
{
    return line_raw_data->id;
}

/**
 * @brief get mpc line raw data line type
 *
 * @param line_raw_data mpc line raw data pointer
 * @return uint16_t line type
 */
static inline uint16_t mpc_line_raw_data_get_type(struct MpcLineRawData* line_raw_data)
{
    return line_raw_data->type;
}

/**
 * @brief get mpc line raw data line width
 *
 * @param line_raw_data mpc line raw data pointer
 * @return uint16_t line width
 */
static inline uint16_t mpc_line_raw_data_get_width(struct MpcLineRawData* line_raw_data)
{
    return line_raw_data->width;
}

/**
 * @brief get mpc line raw data line color
 *
 * @param line_raw_data mpc line raw data pointer
 * @return uint16_t line color
 */
static inline uint16_t mpc_line_raw_data_get_color(struct MpcLineRawData* line_raw_data)
{
    return line_raw_data->type;
}

/**
 * @brief get mpc line raw data line dx begin
 *
 * @param line_raw_data mpc line raw data pointer
 * @return uint16_t line dx begin
 */
static inline uint16_t mpc_line_raw_data_get_dx_begin(struct MpcLineRawData* line_raw_data)
{
    return line_raw_data->dx_begin;
}

/**
 * @brief get mpc line raw data line dx end
 *
 * @param line_raw_data mpc line raw data pointer
 * @return uint16_t line dx end
 */
static inline uint16_t mpc_line_raw_data_get_dx_end(struct MpcLineRawData* line_raw_data)
{
    return line_raw_data->dx_end;
}

/**
 * @brief get mpc line raw data line dy
 *
 * @param line_raw_data mpc line raw data pointer
 * @return uint16_t line dy
 */
static inline uint16_t mpc_line_raw_data_get_dy(struct MpcLineRawData* line_raw_data)
{
    return line_raw_data->dy;
}

/**
 * @brief get mpc line raw data line angle diff
 *
 * @param line_raw_data mpc line raw data pointer
 * @return uint16_t line angle diff
 */
static inline uint16_t mpc_line_raw_data_get_angle_diff(struct MpcLineRawData* line_raw_data)
{
    return line_raw_data->angle_diff;
}

/**
 * @brief get mpc line raw data line horizon curve
 *
 * @param line_raw_data mpc line raw data pointer
 * @return uint16_t line horizon curve
 */
static inline uint16_t mpc_line_raw_data_get_horizon_curve(struct MpcLineRawData* line_raw_data)
{
    return line_raw_data->horizon_curve;
}

/**
 * @}
 * End getter API group.
 */

/**
 * @brief construct mpc line raw data partA
 *
 * @param line_raw_data mpc line raw data pointer
 * @param msg mpc can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mpc_line_raw_data_construct_partA(struct MpcLineRawData* line_raw_data, const uint8_t* msg);

/**
 * @brief construct mpc line raw data partB
 *
 * @param line_raw_data mpc line raw data pointer
 * @param msg can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mpc_line_raw_data_construct_partB(struct MpcLineRawData* line_raw_data, const uint8_t* msg);

/**
 * @brief Get 4byte aligned mpc lines raw data serialized size.
 *
 * @param raw_data The mpc lines raw data.
 *
 * @return uint32_t Serialized size.
 *
 * @see mpc_lines_raw_data_get_serialized_size_8byte_aligned.
 */
uint32_t mpc_lines_raw_data_get_serialized_size_4byte_aligned(const struct MpcLinesRawData* raw_data);

/**
 * @brief Get 8byte aligned mpc lines raw data serialized size.
 *
 * @param raw_data The mpc lines raw data.
 *
 * @return uint32_t Serialized size.
 *
 * @see mpc_lines_raw_data_get_serialized_size_4byte_aligned.
 */
uint32_t mpc_lines_raw_data_get_serialized_size_8byte_aligned(const struct MpcLinesRawData* raw_data);

/**
 * @brief Default interface get mpc lines raw data serialized size.
 *
 * @param raw_data The mpc lines raw data.
 *
 * @return uint32_t serialied size.
 */
uint32_t mpc_lines_raw_data_get_serialized_size(const struct MpcLinesRawData* raw_data);

/**
 * @brief Serialize Mpc lines raw data 4byte aligned.
 *
 * @param position The Mpc lines raw data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see mpc_lines_raw_data_serialize_8byte_aligned.
 */
retcode_t mpc_lines_raw_data_serialize_4byte_aligned(const struct MpcLinesRawData* raw_data, uint8_t* buffer,
                                                     uint32_t buffer_size);

/**
 * @brief Serialize Mpc lines raw data 8byte aligned.
 *
 * @param position The Mpc lines raw data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see mpc_lines_raw_data_serialize_4byte_aligned.
 */
retcode_t mpc_lines_raw_data_serialize_8byte_aligned(const struct MpcLinesRawData* raw_data, uint8_t* buffer,
                                                     uint32_t buffer_size);

/**
 * @brief Default serialize Mpc lines raw data.
 *
 * @param position The Mpc lines raw data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 */
retcode_t mpc_lines_raw_data_serialize(const struct MpcLinesRawData* raw_data, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize Mpc lines raw data 4byte aligned.
 *
 * @param position The Mpc lines raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see mpc_lines_raw_data_deserialize_8byte_aligned.
 */
retcode_t mpc_lines_raw_data_deserialize_4byte_aligned(struct MpcLinesRawData* raw_data, const uint8_t* buffer,
                                                       uint32_t buffer_size);

/**
 * @brief Deserialize Mpc lines raw data 8byte aligned.
 *
 * @param position The Mpc lines raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see mpc_lines_raw_data_deserialize_4byte_aligned.
 */
retcode_t mpc_lines_raw_data_deserialize_8byte_aligned(struct MpcLinesRawData* raw_data, const uint8_t* buffer,
                                                       uint32_t buffer_size);

/**
 * @brief Default deserialize Mpc lines raw data.
 *
 * @param position The Mpc lines raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 */
retcode_t mpc_lines_raw_data_deserialize(struct MpcLinesRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif
