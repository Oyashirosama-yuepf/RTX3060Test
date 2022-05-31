/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_someip.hpp
 * @brief A class to receive and construct mobileye outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/05/26
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/me3/me3_someip.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace mobileye
{
/* static const value */
static const uint32_t MESSAGE_TYPE_OBJECTS        = 0x21;
static const uint32_t MESSAGE_TYPE_LANEBOUNDARIES = 0x20;

bool_t MobileyeDriverT<SomeipPacketType>::ParseObstacles(const uint8_t* data, uint32_t size)
{
    struct MobileyeObjectListRawData raw_objects;
    retcode_t                        retcode = mobileye_object_list_raw_data_deserialize(&raw_objects, data, size);
    if (!(retcode > 0))
    {
        LOG(ERROR) << "faile to deserialize payload to objects: " << retcode;
        return false;
    }
    ObstaclePtrListType obstacles;
    obstacles.SetTimestamp(
        holo::common::Timestamp(raw_objects.object[0].timestamp.sec, raw_objects.object[0].timestamp.nsec));
    obstacles.SetCoordinate(extrinsic_.GetParentCoordinate());
    obstacles.SetSensorId(this->GetSensorId());
    Convert(raw_objects, obstacles);
    obstacles_callback_(obstacles);
    return true;
}

bool_t MobileyeDriverT<SomeipPacketType>::ParseLaneboundaries(const uint8_t* data, uint32_t size)
{
    struct MobileyeLanesRawData raw_lines;
    retcode_t                   retcode = mobileye_lanes_raw_data_deserialize(&raw_lines, data, size);
    if (!(retcode > 0))
    {
        LOG(ERROR) << "faile to deserialize payload to lines: " << retcode;
        return false;
    }
    RoadFrameType road_frame;
    /* header */
    holo::common::Timestamp stamp(raw_lines.line0.timestamp.sec, raw_lines.line0.timestamp.nsec);
    road_frame.SetTimestamp(stamp);
    Convert(raw_lines, road_frame);
    roadframe_callback_(road_frame);
    return true;
}

void MobileyeDriverT<SomeipPacketType>::ParseData(const SomeipPacketType& data)
{
    /* parsing */
    if (data.GetMethodId() == MESSAGE_TYPE_OBJECTS)
    {
        if (obstacles_callback_)
        {
            ParseObstacles(data.GetPayload(), data.GetPayloadLength());
        }
    }
    else if (data.GetMethodId() == MESSAGE_TYPE_LANEBOUNDARIES)
    {
        if (roadframe_callback_)
        {
            ParseLaneboundaries(data.GetPayload(), data.GetPayloadLength());
        }
    }
    else
    {
        LOG(ERROR) << "unknown someip packet method id: " << data.GetMethodId();
    }
}

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo
