/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file me8_holocan.h
 * @brief A class to receive and construct me8 outputs
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/12/09
 */

#ifndef _HOLO_SENSORS_ME8_ME8_HOLOCAN_H
#define _HOLO_SENSORS_ME8_ME8_HOLOCAN_H

#include <holo/core/types.h>
#include <holo/sensors/format/holocan.h>
#include <holo/sensors/smart_camera/me8/structure/me8_laneboundary.h>
#include <holo/sensors/smart_camera/me8/structure/me8_obstacle.h>
#include <holo/sensors/smart_camera/smart_camera.h>
#include <holo_c/sensors/dbc/me8_opFailsafes.h>
#include <holo_c/sensors/dbc/me8_opHazards.h>
#include <holo_c/sensors/dbc/me8_opLanesAdjacent.h>
#include <holo_c/sensors/dbc/me8_opLanesHost.h>
#include <holo_c/sensors/dbc/me8_opObjects.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace me8
{
using holo::common::Extrinsicf;
using holo::sensors::common::Device;
using holo::sensors::format::HoloCanPacket;

static const uint32_t ME8_HOST_LINES_NUM     = 2u;
static const uint32_t ME8_ADJACENT_LINES_NUM = 4u;
static const uint32_t ME8_OBJECTS_NUM        = 12u;

class Me8Driver : public SmartCameraDriverT<HoloCanPacket>, public Device
{
public:
    /* obstacle alias */
    using ObjectType     = holo::sensors::me8::Me8Obstacle;
    using ObjectListType = std::array<ObjectType, ME8_OBJECTS_NUM>;
    /* roadframe alias */
    using LineTypeHost         = holo::sensors::me8::Me8LaneBoundaryHost;
    using LineListTypeHost     = std::array<LineTypeHost, ME8_HOST_LINES_NUM>;
    using LineTypeAdjacent     = holo::sensors::me8::Me8LaneBoundaryAdjacent;
    using LineListTypeAdjacent = std::array<LineTypeAdjacent, ME8_ADJACENT_LINES_NUM>;

    Me8Driver(const Extrinsicf& extrinsic) : SmartCameraDriverT<HoloCanPacket>(), Device(extrinsic.GetSensorId()), extrinsic_(extrinsic)
    {
    }

    void ParseData(const HoloCanPacket& msg);

private:
    // todo: ConstructObjHeader() if not useful, del it
    void ConstructObjHeader(const HoloCanPacket& msg);
    void ConstructObject(const HoloCanPacket& msg, ObjectListType& object_list);
    void ConvertToObstacle(const ObjectType& input, std::shared_ptr<ObstacleType>& output);
    void ConvertToObstaclePtrListWithTransform(ObjectListType& input, ObstaclePtrListType& output) const;

    void ConstructLaneboundaryHostPartA(const HoloCanPacket& msg, LineTypeHost& host_lane_boundary);
    void ConstructLaneboundaryHostPartB(const HoloCanPacket& msg, LineTypeHost& host_lane_boundary);
    void ConstructLaneboundaryAdjacentPartA(const HoloCanPacket& msg, LineTypeAdjacent& adjacent_lane_boundary);
    void ConstructLaneboundaryAdjacentPartB(const HoloCanPacket& msg, LineTypeAdjacent& adjacent_lane_boundary);
    void ConvertToRoadFrameWithTransform(RoadFrameType& output);

private:
    Extrinsicf           extrinsic_;
    ObjectListType       object_list_;
    LineListTypeHost     host_lane_boundary_list_;
    LineListTypeAdjacent adjacent_lane_boundary_list_;
};
}  // namespace me8
}  // namespace sensors
}  // namespace holo

#endif
