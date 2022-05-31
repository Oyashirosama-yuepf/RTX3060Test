/*!
 * @brief This file implements extrinsic float32_t.
 * @author lichao@holomatic.com
 * @date Sep 09, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <holo_c/common/extrinsic_float32.h>
#include <holo_c/utils/serialization.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t extrinsicf_init(struct Extrinsicf* extrinsic)
{
    assert(extrinsic != NULL);

    extrinsic->parent_coordinate = coordinate_default_create();
    extrinsic->child_coordinate = coordinate_default_create();
    pose3f_init(&extrinsic->pose);

    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Coordinate_t extrinsicf_get_parent_coordinate(const struct Extrinsicf* extrinsic)
{
    assert(extrinsic != NULL);
    return extrinsic->parent_coordinate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Coordinate_t extrinsicf_get_child_coordinate(const struct Extrinsicf* extrinsic)
{
    assert(extrinsic != NULL);
    return extrinsic->child_coordinate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const struct Pose3f* extrinsicf_get_pose(const struct Extrinsicf* extrinsic)
{
    assert(extrinsic != NULL);
    return &extrinsic->pose;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t extrinsicf_set_parent_coordinate(struct Extrinsicf* extrinsic, Coordinate_t parent_coordinate)
{
    assert(extrinsic != NULL);
    extrinsic->parent_coordinate = parent_coordinate;
    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t extrinsicf_set_child_coordinate(struct Extrinsicf* extrinsic, Coordinate_t child_coordinate)
{
    assert(extrinsic != NULL);
    extrinsic->child_coordinate = child_coordinate;
    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t extrinsicf_set_pose(struct Extrinsicf* extrinsic, const struct Pose3f* pose)
{
    assert(extrinsic != NULL);
    pose3f_init_from_pose3f(&extrinsic->pose, pose);
    return RC_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t extrinsicf_get_serialized_size(const struct Extrinsicf* self)
{
    (void)self;
    uint32_t size = 0;

    size += sizeof(Coordinate_t);
    size += sizeof(Coordinate_t);
    size += pose3f_get_serialized_size(&self->pose);

    return serialization_aligned_size(size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t extrinsicf_serialize(const struct Extrinsicf* self, uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t serialized_size = 0;
    uint32_t expected_size = extrinsicf_get_serialized_size(self);

    if(buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_uint32(&self->parent_coordinate, 
                                            buffer, 
                                            buffer_size);
        serialized_size += serialize_uint32(&self->child_coordinate, 
                                            buffer + serialized_size, 
                                            buffer_size - serialized_size);
        serialized_size += pose3f_serialize(&self->pose, 
                                            buffer + serialized_size, 
                                            buffer_size - serialized_size);

        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
retcode_t extrinsicf_deserialize(struct Extrinsicf* self, const uint8_t* buffer, uint32_t buffer_size)
{
    assert(self != NULL);
    assert(buffer != NULL);

    retcode_t rc = RC_SUCCESS;
    uint32_t deserialized_size = 0;
    uint32_t expected_size = extrinsicf_get_serialized_size(self);

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_uint32(&self->parent_coordinate, 
                                                buffer, 
                                                buffer_size);
        deserialized_size += deserialize_uint32(&self->child_coordinate, 
                                                buffer + deserialized_size, 
                                                buffer_size - deserialized_size);
        deserialized_size += pose3f_deserialize(&self->pose, 
                                                buffer + deserialized_size, 
                                                buffer_size - deserialized_size);

        assert(expected_size == deserialized_size);
        rc = (retcode_t)deserialized_size;
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
