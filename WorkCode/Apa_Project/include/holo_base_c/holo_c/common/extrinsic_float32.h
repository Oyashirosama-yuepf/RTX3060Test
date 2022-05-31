/*!
 * @file extrinsic_float32.h
 * @brief This header file defines extrinsic struct
 * @author duyanwei@holomatic.com
 * @date 2019-08-26
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_COMMON_EXTRINSIC_FLOAT32_H_
#define HOLO_C_COMMON_EXTRINSIC_FLOAT32_H_

#include <assert.h>
#include <holo_c/common/coordinate.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/pose3_float32.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define extrinsic struct
 *
 */
struct Extrinsicf
{
    Coordinate_t parent_coordinate;
    Coordinate_t child_coordinate;
    struct Pose3f     pose;
};

#ifdef MATRIX_ALIGN
#define   EXTRINSICF_F32_SIZE     104UL
#else
#define   EXTRINSICF_F32_SIZE     80UL
#endif
// check the size of Extrinsicf with static assert
HOLO_STATIC_ASSERT(sizeof(struct Extrinsicf) == EXTRINSICF_F32_SIZE);

/**
 * @brief initialize extrinsic from default value
 *
 * @param extrinsic extrinsic object
 */
retcode_t extrinsicf_init(struct Extrinsicf* extrinsic);

/**
 * @brief get parent coordinate from Extrinsicf
 *
 * @param extrinsic a Extrindsicf
 * @return parent coordinate
 */
Coordinate_t extrinsicf_get_parent_coordinate(const struct Extrinsicf* extrinsic);

/**
 * @brief get child coordinate from Extrinsicf
 *
 * @param extrinsic a Extrindsicf
 * @return child coordinate
 */
Coordinate_t extrinsicf_get_child_coordinate(const struct Extrinsicf* extrinsic);

/**
 * @brief get pose from Extrinsicf
 *
 * @param extrinsic a Extrinsicf
 * @return const struct Pose3f*
 */
const struct Pose3f* extrinsicf_get_pose(const struct Extrinsicf* extrinsic);

/**
 * @brief set parent coordinate to Extrinsicf
 *
 * @param extrinsic
 * @param parent_coordinate the parent coordinate
 * @return retcode_t
 */
retcode_t extrinsicf_set_parent_coordinate(struct Extrinsicf* extrinsic, Coordinate_t parent_coordinate);

/**
 * @brief set child coordinate to Extrinsicf
 *
 * @param extrinsic a Extrindsicf
 * @param child_coordinate the child coordinate
 * @return retcode_t
 */
retcode_t extrinsicf_set_child_coordinate(struct Extrinsicf* extrinsic, Coordinate_t child_coordinate);

/**
 * @brief set pose to Extrinsicf
 *
 * @param extrinsic a Extrinsicf
 * @param pose a Pose3f
 * @return retcode_t
 */
retcode_t extrinsicf_set_pose(struct Extrinsicf* extrinsic, const struct Pose3f* pose);

/**
 * @brief get serialized buffer size for a extrinsic float32_t
 *
 * @param self a extrinsic float32_t to be serialized
 * @return buffer size
 */
uint32_t extrinsicf_get_serialized_size(const struct Extrinsicf* self);

/**
 * @brief serialize a extrinsic float32_t to buffer
 *
 * @param self a extrinsic float32_t to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes serialized info buffer.
 */
retcode_t extrinsicf_serialize(const struct Extrinsicf* self, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief deserialize a extrinsic float32_t to buffer
 *
 * @param self a extrinsic float32_t to be serialized
 * @param buffer the buffer
 * @param buffer_size the size of buffer
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW buffer_size is smaller than needed
 * @return a positive integer number of bytes deserialized info buffer.
 */
retcode_t extrinsicf_deserialize(struct Extrinsicf* self, const uint8_t* buffer, uint32_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_COMMON_EXTRINSIC_FLOAT32_H_
