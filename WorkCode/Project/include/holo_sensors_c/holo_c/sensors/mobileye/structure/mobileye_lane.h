/*!
 * @file mpc_line.h
 * @brief This header file defines bosch mpc line raw data structure and functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_MOBILEYE_STRUCTURE_MOBILEYE_LANE_H_
#define HOLO_C_SENSORS_MOBILEYE_STRUCTURE_MOBILEYE_LANE_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/types.h>
#include <holo_c/sensors/mobileye/mobileye_dbc_output.h>
#include <holo_c/utils/serialization.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 *
 */

#define MOBILEYE_LANE_NUM 4

/**
 * @brief Mobileye Lane raw data struct
 *
 */
struct MobileyeLaneRawData
{
    struct Timestamp timestamp;

    uint16_t range_start;		//! @brief lane view start
    uint16_t mark_width;		//! @brief lane mark width
    uint16_t mark_quality;		//! @brief mark quality
    uint16_t mark_type;			//! @brief mark type
    uint16_t location_type;		//! @brief lane location
    uint16_t lane_index;		//! @brief lane index
    uint16_t frame_index;		//! @brief for message sync

    uint16_t c2;				//! c2
    uint16_t range_end;			//! lane view start
    uint16_t c1;				//! c1
    uint16_t c0;				//! c1

    uint16_t mark_color;		//!< mark color
    uint16_t c3;				//!< c3
    uint16_t crossing;			//!< lane crossing indicator
    uint16_t tlc;
};
HOLO_STATIC_ASSERT(sizeof(struct MobileyeLaneRawData) == 40);

struct MobileyeLanesRawData
{
    struct MobileyeLaneRawData line0;
    struct MobileyeLaneRawData line1;
    struct MobileyeLaneRawData line2;
    struct MobileyeLaneRawData line3;
};
HOLO_STATIC_ASSERT(sizeof(struct MobileyeLanesRawData) == 160);

/**
 * @{
 * Begin setter API group.
 */

/**
 * @brief set mobileye lane raw data timestamp
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param timestamp system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_timestamp(struct MobileyeLaneRawData*  lane_raw_data,
                                                   const struct Timestamp* timestamp)
{
    lane_raw_data->timestamp = *timestamp;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_range_start(struct MobileyeLaneRawData*  lane_raw_data, uint16_t range_start)
{
    lane_raw_data->range_start = range_start;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_mark_width(struct MobileyeLaneRawData*  lane_raw_data, uint16_t mark_width)
{
    lane_raw_data->mark_width = mark_width;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_mark_quality(struct MobileyeLaneRawData*  lane_raw_data, uint16_t mark_quality)
{
    lane_raw_data->mark_quality = mark_quality;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_mark_type(struct MobileyeLaneRawData*  lane_raw_data, uint16_t mark_type)
{
    lane_raw_data->mark_type = mark_type;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_location_type(struct MobileyeLaneRawData*  lane_raw_data, uint16_t location_type)
{
    lane_raw_data->location_type = location_type;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_lane_index(struct MobileyeLaneRawData*  lane_raw_data, uint16_t lane_index)
{
    lane_raw_data->lane_index = lane_index;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_frame_index(struct MobileyeLaneRawData*  lane_raw_data, uint16_t frame_index)
{
    lane_raw_data->frame_index = frame_index;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_c2(struct MobileyeLaneRawData*  lane_raw_data, uint16_t c2)
{
    lane_raw_data->c2 = c2;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_range_end(struct MobileyeLaneRawData*  lane_raw_data, uint16_t range_end)
{
    lane_raw_data->range_end = range_end;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_c1(struct MobileyeLaneRawData*  lane_raw_data, uint16_t c1)
{
    lane_raw_data->c1 = c1;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_c0(struct MobileyeLaneRawData*  lane_raw_data, uint16_t c0)
{
    lane_raw_data->c0 = c0;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_mark_color(struct MobileyeLaneRawData*  lane_raw_data, uint16_t mark_color)
{
    lane_raw_data->mark_color = mark_color;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_c3(struct MobileyeLaneRawData*  lane_raw_data, uint16_t c3)
{
    lane_raw_data->c3 = c3;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_crossing(struct MobileyeLaneRawData*  lane_raw_data, uint16_t crossing)
{
    lane_raw_data->crossing = crossing;
}

/**
 * @brief set mobileye lane raw data range_start
 *
 * @param lane_raw_data mobileye line raw data poiter
 * @param range_start system timestamp
 * @return retcode_t RC_SUCCESS
 */
static inline void mobileye_lane_raw_data_set_tlc(struct MobileyeLaneRawData*  lane_raw_data, uint16_t tlc)
{
    lane_raw_data->tlc = tlc;
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
 * @brief get mobileye lanes raw data timestamp
 *
 * @param line_raw_data mobileye lanes raw data pointer
 * @param timestamp timestamp pointer
 * @return retcode_t RC_SUCCE
 */
static inline const struct Timestamp* mobileye_lane_raw_data_get_timestamp(struct MobileyeLaneRawData* lane_raw_data)
{
    return &lane_raw_data->timestamp;
}

/**
 * @brief get mobileye lanes raw data line range_start
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t line range_start
 */
static inline uint16_t mobileye_lane_raw_data_get_range_start(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->range_start;
}

/**
 * @brief get mobileye lanes raw data line mark_width
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t line mark_width
 */
static inline uint16_t mobileye_lane_raw_data_get_mark_width(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->mark_width;
}

/**
 * @brief get mobileye lanes raw data line mark_quality
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t line mark_quality
 */
static inline uint16_t mobileye_lane_raw_data_get_mark_quality(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->mark_quality;
}

/**
 * @brief get mobileye lanes raw data line mark_type
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t line mark_type
 */
static inline uint16_t mobileye_lane_raw_data_get_mark_type(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->mark_type;
}

/**
 * @brief get mobileye lanes raw data line location_type
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t line location_type
 */
static inline uint16_t mobileye_lane_raw_data_get_location_type(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->location_type;
}

/**
 * @brief get mobileye lanes raw data message sync index
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t for message sync index
 */
static inline uint16_t mobileye_lane_raw_data_get_lane_index(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->lane_index;
}

/**
 * @brief get mobileye lanes raw data line dx end
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t line dx end
 */
static inline uint16_t mobileye_lane_raw_data_get_frame_index(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->frame_index;
}

/**
 * @brief get mobileye lanes raw data C2_Lane_Curvature
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t C2_Lane_Curvature
 */
static inline uint16_t mobileye_lane_raw_data_get_c2(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->c2;
}

/**
 * @brief get mobileye lanes raw data lane view end
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t lane view end
 */
static inline uint16_t mobileye_lane_raw_data_get_range_end(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->range_end;
}

/**
 * @brief get mobileye lanes raw data C1_Heading_Angle
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t C1_Heading_Angle
 */
static inline uint16_t mobileye_lane_raw_data_get_c1(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->c1;
}

/**
 * @brief get mobileye lanes raw data C0_Lane_Position
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t C0_Lane_Position
 */
static inline uint16_t mobileye_lane_raw_data_get_c0(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->c0;
}

/**
 * @brief get mobileye lanes raw data line mark color
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t line mark color
 */
static inline uint16_t mobileye_lane_raw_data_get_mark_color(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->mark_color;
}

/**
 * @brief get mobileye lanes raw data C3_Lane_Curvature_Driv
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t C3_Lane_Curvature_Driv
 */
static inline uint16_t mobileye_lane_raw_data_get_c3(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->c3;
}

/**
 * @brief get mobileye lanes raw data lane crossing indicator
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t lane crossing indicator
 */
static inline uint16_t mobileye_lane_raw_data_get_crossing(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->crossing;
}

/**
 * @brief get mobileye lanes raw data tlc
 *
 * @param lane_raw_data mobileye lanes raw data pointer
 * @return uint16_t tlc
 */
static inline uint16_t mobileye_lane_raw_data_get_tlc(struct MobileyeLaneRawData* lane_raw_data)
{
    return lane_raw_data->tlc;
}

/**
 * @}
 * End getter API group.
 */

/**
 * @brief construct mobileye lanes raw data part0
 *
 * @param line_raw_data mobileye lanes raw data pointer
 * @param msg mpc can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mobileye_lane_raw_data_construct_part0(struct MobileyeLaneRawData* lane_raw_data, const uint8_t* msg);

/**
 * @brief construct mobileye lanes raw data part1
 *
 * @param line_raw_data mobileye lanes raw data pointer
 * @param msg can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mobileye_lane_raw_data_construct_part1(struct MobileyeLaneRawData* lane_raw_data, const uint8_t* msg);

/**
 * @brief construct mobileye lanes raw data part2
 *
 * @param line_raw_data mobileye lanes raw data pointer
 * @param msg can message
 * @return retcode_t RC_SUCCESS
 */
retcode_t mobileye_lane_raw_data_construct_part2(struct MobileyeLaneRawData* lane_raw_data, const uint8_t* msg);

/**
 * @brief Get 4byte aligned mobileye lanes raw data serialized size.
 *
 * @param raw_data The mobileye lanes raw data.
 *
 * @return uint32_t Serialized size.
 *
 * @see mpc_lines_raw_data_get_serialized_size_8byte_aligned.
 */
uint32_t mobileye_lanes_raw_data_get_serialized_size_4byte_aligned(const struct MobileyeLanesRawData* raw_data);

/**
 * @brief Get 8byte aligned mobileye lanes raw data serialized size.
 *
 * @param raw_data The mobileye lanes raw data.
 *
 * @return uint32_t Serialized size.
 *
 * @see mpc_lines_raw_data_get_serialized_size_4byte_aligned.
 */
uint32_t mobileye_lanes_raw_data_get_serialized_size_8byte_aligned(const struct MobileyeLanesRawData* raw_data);

/**
 * @brief Default interface get mobileye lanes raw data serialized size.
 *
 * @param raw_data The mobileye lanes raw data.
 *
 * @return uint32_t serialied size.
 */
uint32_t mobileye_lanes_raw_data_get_serialized_size(const struct MobileyeLanesRawData* raw_data);

/**
 * @brief Serialize Mobileye lanes raw data 4byte aligned.
 *
 * @param raw_data The Mobileye lanes raw data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see mpc_lines_raw_data_serialize_8byte_aligned.
 */
retcode_t mobileye_lanes_raw_data_serialize_4byte_aligned(const struct MobileyeLanesRawData* raw_data, uint8_t* buffer,
                                                     uint32_t buffer_size);


/**
 * @brief Serialize Mobileye lanes raw data 8byte aligned.
 *
 * @param raw_data The Mobileye lanes raw data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see mpc_lines_raw_data_serialize_4byte_aligned.
 */
retcode_t mobileye_lanes_raw_data_serialize_8byte_aligned(const struct MobileyeLanesRawData* raw_data, uint8_t* buffer,
                                                     uint32_t buffer_size);


/**
 * @brief Default serialize Mobileye lanes raw data.
 *
 * @param raw_data The Mobileye lanes raw data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 */
retcode_t mobileye_lanes_raw_data_serialize(const struct MobileyeLanesRawData* raw_data, uint8_t* buffer, uint32_t buffer_size);


/**
 * @brief Deserialize Mobileye lanes raw data 4byte aligned.
 *
 * @param raw_data The Mobileye lanes raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see mpc_lines_raw_data_deserialize_8byte_aligned.
 */
retcode_t mobileye_lanes_raw_data_deserialize_4byte_aligned(struct MobileyeLanesRawData* raw_data, const uint8_t* buffer,
														   uint32_t buffer_size);

/**
 * @brief Deserialize Mobileye lanes raw data 8byte aligned.
 *
 * @param raw_data The Mobileye lanes raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see mpc_lines_raw_data_deserialize_4byte_aligned.
 */
retcode_t mobileye_lanes_raw_data_deserialize_8byte_aligned(struct MobileyeLanesRawData* raw_data, const uint8_t* buffer,
														   uint32_t buffer_size);

/**
 * @brief Default deserialize Mobileye lanes raw data.
 *
 * @param raw_data The Mobileye lanes raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 */
retcode_t mobileye_lanes_raw_data_deserialize(struct MobileyeLanesRawData* raw_data, const uint8_t* buffer, uint32_t buffer_size);
/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif
