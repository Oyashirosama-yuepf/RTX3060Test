/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bosch_mpc_someip.hpp
 * @brief A class to receive and construct bosch mpc outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/08/24
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_someip.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
static const uint32_t MESSAGE_TYPE_OBJECTS        = 0x21;
static const uint32_t MESSAGE_TYPE_LANEBOUNDARIES = 0x20;

bool_t BoschMpcDriverT<SomeipPacketType>::ParseObstacles(const uint8_t* data, uint32_t size)
{
    struct MpcObjectListRawData raw_objects;
    retcode_t                   retcode = mpc_object_list_raw_data_deserialize(&raw_objects, data, size);
    if (!(retcode > 0))
    {
        LOG(ERROR) << "failed to deserialize payload to objects: " << retcode;
        return false;
    }
    ObstaclePtrListType obstacles;
    obstacles.SetTimestamp(
        holo::common::Timestamp(raw_objects.object[0].timestamp.sec, raw_objects.object[0].timestamp.nsec));
    obstacles.SetCoordinate(extrinsic_.GetParentCoordinate());
    obstacles.SetSensorId(this->GetSensorId());
    ConvertToObstaclePtrListWithTransform(raw_objects, obstacles);
    obstacles_callback_(obstacles);
    return true;
}

bool_t BoschMpcDriverT<SomeipPacketType>::ParseLaneboundaries(const uint8_t* data, uint32_t size)
{
    struct MpcLinesRawData raw_lines;
    retcode_t              retcode = mpc_lines_raw_data_deserialize(&raw_lines, data, size);
    if (!(retcode > 0))
    {
        LOG(ERROR) << "failed to deserialize payload to lines: " << retcode;
        return false;
    }
    RoadFrameType road_frame;
    /* header */
    holo::common::Timestamp stamp(raw_lines.left_line.timestamp.sec, raw_lines.left_line.timestamp.nsec);
    road_frame.SetTimestamp(stamp);
    ConvertToRoadFrameWithTransform(raw_lines, road_frame);
    roadframe_callback_(road_frame);
    return true;
}

void BoschMpcDriverT<SomeipPacketType>::ParseData(const SomeipPacketType& data)
{
    /* parsing */
    if (data.GetMethodId() == MESSAGE_TYPE_OBJECTS)
    {
        if (obstacles_callback_)
        {
            ParseObstacles(data.GetPayload() + 4, data.GetPayloadLength() - 4);
        }
    }
    else if (data.GetMethodId() == MESSAGE_TYPE_LANEBOUNDARIES)
    {
        if (roadframe_callback_)
        {
            ParseLaneboundaries(data.GetPayload() + 4, data.GetPayloadLength() - 4);
        }
    }
    else
    {
        LOG(ERROR) << "unknown someip packet method id: " << data.GetMethodId();
    }
}

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo
