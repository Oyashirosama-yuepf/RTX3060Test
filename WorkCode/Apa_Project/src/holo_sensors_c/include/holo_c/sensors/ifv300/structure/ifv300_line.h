/*!
 * @file ifv300_line.h
 * @brief This header file defines ifv300 line raw data structure and functions
 * @author liuya@holomatic.com
 * @date 2020-04-15
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_IFV300_STRUCTURE_IFV300_LINE_H_
#define HOLO_C_SENSORS_IFV300_STRUCTURE_IFV300_LINE_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/types.h>
#include <holo_c/utils/serialization.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 *
 */

#define IFV_LINE_NUM 4

struct IfvLineInfoHead
{
    uint16_t lane_change;
    uint16_t left_left_type;
    uint16_t left_type;
    uint16_t right_right_type;
    uint16_t right_type;
    uint16_t left_left_lkaconf;
    uint16_t left_lkaconf;
    uint16_t right_right_lkaconf;
    uint16_t right_lkaconf;
    uint16_t reserved;
};
HOLO_STATIC_ASSERT(sizeof(struct IfvLineInfoHead) == 20);

struct IfvLineInfoCurve
{
    uint16_t mark_color;
    uint16_t a0;
    uint16_t a1;
    uint16_t a2;
    uint16_t a3;
    uint16_t range;
};
HOLO_STATIC_ASSERT(sizeof(struct IfvLineInfoCurve) == 12);

/**
 * @brief Ifv300 Line raw data struct
 *
 */
struct IfvLinesRawData
{
    struct Timestamp        timestamp;
    struct IfvLineInfoHead  line_head;
    struct IfvLineInfoCurve left_left;
    struct IfvLineInfoCurve left;
    struct IfvLineInfoCurve right;
    struct IfvLineInfoCurve right_right;
};
HOLO_STATIC_ASSERT(sizeof(struct IfvLinesRawData) == 76);

/**
 * @{
 * Begin setter API group.
 */

/**
 * @brief set ifv lines raw data timestamp
 *
 * @param line_raw_data ifv lines raw data poiter
 * @param timestamp system timestamp
 */
static inline void ifv_lines_raw_data_set_timestamp(struct IfvLinesRawData* lines_raw_data,
                                                    const struct Timestamp* timestamp)
{
    lines_raw_data->timestamp = *timestamp;
}

/**
 * @brief Set ifv line info head raw data lane change
 *
 * @param raw_data ifv line info head pointer
 * @param value raw_value
 */
static inline void ifv_line_info_head_raw_data_set_lane_change(struct IfvLineInfoHead* raw_data, uint16_t value)
{
    raw_data->lane_change = value;
}

/**
 * @brief Set ifv line info head raw data left left line type
 *
 * @param raw_data ifv line info head pointer
 * @param value raw_value
 */
static inline void ifv_line_info_head_raw_data_set_left_left_type(struct IfvLineInfoHead* raw_data, uint16_t value)
{
    raw_data->left_left_type = value;
}

/**
 * @brief Set ifv line info head raw data left line type
 *
 * @param raw_data ifv line info head pointer
 * @param value raw_value
 */
static inline void ifv_line_info_head_raw_data_set_left_type(struct IfvLineInfoHead* raw_data, uint16_t value)
{
    raw_data->left_type = value;
}

/**
 * @brief Set ifv line info head raw data right right line type
 *
 * @param raw_data ifv line info head pointer
 * @param value raw_value
 */
static inline void ifv_line_info_head_raw_data_set_right_right_type(struct IfvLineInfoHead* raw_data, uint16_t value)
{
    raw_data->right_right_type = value;
}

/**
 * @brief Set ifv line info head raw data right line type
 *
 * @param raw_data ifv line info head pointer
 * @param value raw_value
 */
static inline void ifv_line_info_head_raw_data_set_right_type(struct IfvLineInfoHead* raw_data, uint16_t value)
{
    raw_data->right_type = value;
}

/**
 * @brief Set ifv line info head raw data left left lkaconf
 *
 * @param raw_data ifv line info head pointer
 * @param value raw_value
 */
static inline void ifv_line_info_head_raw_data_set_left_left_lkaconf(struct IfvLineInfoHead* raw_data, uint16_t value)
{
    raw_data->left_left_lkaconf = value;
}

/**
 * @brief Set ifv line info head raw data left lkaconf
 *
 * @param raw_data ifv line info head pointer
 * @param value raw_value
 */
static inline void ifv_line_info_head_raw_data_set_left_lkaconf(struct IfvLineInfoHead* raw_data, uint16_t value)
{
    raw_data->left_lkaconf = value;
}

/**
 * @brief Set ifv line info head raw data right right line lkaconf
 *
 * @param raw_data ifv line info head pointer
 * @param value raw_value
 */
static inline void ifv_line_info_head_raw_data_set_right_right_lkaconf(struct IfvLineInfoHead* raw_data, uint16_t value)
{
    raw_data->right_right_lkaconf = value;
}

/**
 * @brief Set ifv line info head raw data right line lkaconf
 *
 * @param raw_data ifv line info head pointer
 * @param value raw_value
 */
static inline void ifv_line_info_head_raw_data_set_right_lkaconf(struct IfvLineInfoHead* raw_data, uint16_t value)
{
    raw_data->right_lkaconf = value;
}

/**
 * @brief Set ifv line info curve raw data mark color
 * @param raw_data ifv line info curve pointer
 * @param value raw_value
 */
static inline void ifv_line_info_curve_raw_data_set_mark_color(struct IfvLineInfoCurve* raw_data, uint16_t value)
{
    raw_data->mark_color = value;
}

/**
 * @brief Set ifv line info curve raw data a0
 * @param raw_data ifv line info curve pointer
 * @param value raw_value
 */
static inline void ifv_line_info_curve_raw_data_set_a0(struct IfvLineInfoCurve* raw_data, uint16_t value)
{
    raw_data->a0 = value;
}

/**
 * @brief Set ifv line info curve raw data a1
 * @param raw_data ifv line info curve pointer
 * @param value raw_value
 */
static inline void ifv_line_info_curve_raw_data_set_a1(struct IfvLineInfoCurve* raw_data, uint16_t value)
{
    raw_data->a1 = value;
}

/**
 * @brief Set ifv line info curve raw data a2
 * @param raw_data ifv line info curve pointer
 * @param value raw_value
 */
static inline void ifv_line_info_curve_raw_data_set_a2(struct IfvLineInfoCurve* raw_data, uint16_t value)
{
    raw_data->a2 = value;
}

/**
 * @brief Set ifv line info curve raw data a3
 * @param raw_data ifv line info curve pointer
 * @param value raw_value
 */
static inline void ifv_line_info_curve_raw_data_set_a3(struct IfvLineInfoCurve* raw_data, uint16_t value)
{
    raw_data->a3 = value;
}

/**
 * @brief Set ifv line info curve raw data range
 * @param raw_data ifv line info curve pointer
 * @param value raw_value
 */
static inline void ifv_line_info_curve_raw_data_set_range(struct IfvLineInfoCurve* raw_data, uint16_t value)
{
    raw_data->range = value;
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
 * @brief Get ifv lines raw data timestamp
 *
 * @param lines_raw_data ifv lines raw data pointer
 * @return const struct Timestamp* timestamp pointer
 */
static inline const struct Timestamp* ifv_lines_raw_data_get_timestamp(struct IfvLinesRawData* lines_raw_data)
{
    return &lines_raw_data->timestamp;
}

/**
 * @brief Get ifv line info head raw data lane change
 *
 * @param raw_data ifv line info head pointer
 * @return uint16_t lane change raw value
 */
static inline uint16_t ifv_line_info_head_raw_data_get_lane_change(struct IfvLineInfoHead* raw_data)
{
    return raw_data->lane_change;
}

/**
 * @brief Get ifv line info head raw data left left type
 *
 * @param raw_data ifv line info head pointer
 * @return uint16_t left left type raw value
 */
static inline uint16_t ifv_line_info_head_raw_data_get_left_left_type(struct IfvLineInfoHead* raw_data)
{
    return raw_data->left_left_type;
}

/**
 * @brief Get ifv line info head raw data left type
 *
 * @param raw_data ifv line info head pointer
 * @return uint16_t left type raw value
 */
static inline uint16_t ifv_line_info_head_raw_data_get_left_type(struct IfvLineInfoHead* raw_data)
{
    return raw_data->left_type;
}

/**
 * @brief Get ifv line info head raw data right right type
 *
 * @param raw_data ifv line info head pointer
 * @return uint16_t right right type raw value
 */
static inline uint16_t ifv_line_info_head_raw_data_get_right_right_type(struct IfvLineInfoHead* raw_data)
{
    return raw_data->right_right_type;
}

/**
 * @brief Get ifv line info head raw data right type
 *
 * @param raw_data ifv line info head pointer
 * @return uint16_t right type raw value
 */
static inline uint16_t ifv_line_info_head_raw_data_get_right_type(struct IfvLineInfoHead* raw_data)
{
    return raw_data->right_type;
}

/**
 * @brief Get ifv line info head raw data left left lkaconf
 *
 * @param raw_data ifv line info head pointer
 * @return uint16_t left left type raw value
 */
static inline uint16_t ifv_line_info_head_raw_data_get_left_left_lkaconf(struct IfvLineInfoHead* raw_data)
{
    return raw_data->left_left_lkaconf;
}

/**
 * @brief Get ifv line info head raw data left lkaconf
 *
 * @param raw_data ifv line info head pointer
 * @return uint16_t left type raw value
 */
static inline uint16_t ifv_line_info_head_raw_data_get_left_lkaconf(struct IfvLineInfoHead* raw_data)
{
    return raw_data->left_lkaconf;
}

/**
 * @brief Get ifv line info head raw data right right lkaconf
 *
 * @param raw_data ifv line info head pointer
 * @return uint16_t right right type raw value
 */
static inline uint16_t ifv_line_info_head_raw_data_get_right_right_lkaconf(struct IfvLineInfoHead* raw_data)
{
    return raw_data->right_right_lkaconf;
}

/**
 * @brief Get ifv line info head raw data right lkaconf
 *
 * @param raw_data ifv line info head pointer
 * @return uint16_t right type raw value
 */
static inline uint16_t ifv_line_info_head_raw_data_get_right_lkaconf(struct IfvLineInfoHead* raw_data)
{
    return raw_data->right_lkaconf;
}

/**
 * @brief Get if line info curve mark color
 *
 * @param raw_data ifv line info curve pointer
 * @return uint16_t mark color raw value
 */
static inline uint16_t ifv_line_info_curve_raw_data_get_mark_color(struct IfvLineInfoCurve* raw_data)
{
    return raw_data->mark_color;
}

/**
 * @brief Get if line info curve a0
 *
 * @param raw_data ifv line info curve pointer
 * @return uint16_t a0 raw value
 */
static inline uint16_t ifv_line_info_curve_raw_data_get_a0(struct IfvLineInfoCurve* raw_data)
{
    return raw_data->a0;
}

/**
 * @brief Get if line info curve a1
 *
 * @param raw_data ifv line info curve pointer
 * @return uint16_t a1 raw value
 */
static inline uint16_t ifv_line_info_curve_raw_data_get_a1(struct IfvLineInfoCurve* raw_data)
{
    return raw_data->a1;
}

/**
 * @brief Get if line info curve a2
 *
 * @param raw_data ifv line info curve pointer
 * @return uint16_t a2 raw value
 */
static inline uint16_t ifv_line_info_curve_raw_data_get_a2(struct IfvLineInfoCurve* raw_data)
{
    return raw_data->a2;
}

/**
 * @brief Get if line info curve a3
 *
 * @param raw_data ifv line info curve pointer
 * @return uint16_t a3 raw value
 */
static inline uint16_t ifv_line_info_curve_raw_data_get_a3(struct IfvLineInfoCurve* raw_data)
{
    return raw_data->a3;
}

/**
 * @brief Get if line info curve range
 *
 * @param raw_data ifv line info curve pointer
 * @return uint16_t range raw value
 */
static inline uint16_t ifv_line_info_curve_raw_data_get_range(struct IfvLineInfoCurve* raw_data)
{
    return raw_data->range;
}

/**
 * @}
 * End getter API group.
 */

/**
 * @brief Construct ifv lines info head
 *
 * @param raw_data ifv lines raw data pointer
 * @param msg can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t ifv_lines_raw_data_construct_info_head(struct IfvLineInfoHead* raw_data, const uint8_t* msg);

/**
 * @brief Construct ifv lines info curve
 *
 * @param raw_data ifv lines raw data pointer
 * @param msg can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t ifv_lines_raw_data_construct_info_curve(struct IfvLineInfoCurve* raw_data, const uint8_t* msg);

/**
 * @brief Get ifv lines raw data serialized size
 *
 * @param raw_data ifv lines raw data pointer
 * @return uint32_t serialized size
 */
uint32_t ifv_lines_raw_data_get_serialized_size(const struct IfvLinesRawData* raw_data);

/**
 * @brief Serialize ifv lines raw data to buffer
 *
 * @param raw_data ifv lines raw data pointer
 * @param buffer buffer to store serialized content
 * @param buffer_size buffer size
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return retcode_t Positive interger Number of bytes serialized into buffer
 */
retcode_t ifv_lines_raw_data_serialize(const struct IfvLinesRawData* raw_data, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize ifv lines raw data from buffer
 *
 * @param raw_data ifv lines raw data pointer
 * @param buffer the buffer to deserialize from
 * @param buffer_size size of buffer
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed
 * @return retcode_t Positive integer Number of bytes deserialized from buffer
 */
retcode_t ifv_lines_raw_data_deserialize(struct IfvLinesRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif
