/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_holocan.h
 * @brief A class to receive and construct mobileye outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/04
 */

#ifndef _HOLO_SENSORS_MOBILEYE_MOBILEYE_HOLOCAN_H
#define _HOLO_SENSORS_MOBILEYE_MOBILEYE_HOLOCAN_H

#include <holo/core/types.h>
#include <holo/sensors/format/holocan.h>
#include <holo/sensors/smart_camera/me3/me3_base.h>

namespace holo
{
namespace sensors
{
namespace mobileye
{
using holo::sensors::format::HoloCanPacket;

static const uint32_t MOBILEYE_OBSTACLE_NUM     = 8u;
static const uint32_t MOBILEYE_LANEBOUNDARY_NUM = 4u;

/* driver based on someip packet */
template <>
class MobileyeDriverT<HoloCanPacket> : public SmartCameraDriverT<HoloCanPacket>, public MobileyeDriverBase
{
public:
    MobileyeDriverT(const Extrinsicf& extrinsic)
      : SmartCameraDriverT<HoloCanPacket>(), MobileyeDriverBase(extrinsic), object_header_{0}
    {
    }

    void ParseData(const HoloCanPacket& msg);

private:
    enum : uint8_t
    {
        NEXT_LEFT_INDEX  = 0,
        LKA_LEFT_INDEX   = 1,
        LKA_RIGHT_INDEX  = 2,
        NEXT_RIGHT_INDEX = 3
    };
    struct ObjectHeader
    {
        uint8_t object_num;
    };

private:
    void ConstructObjectHeader(const HoloCanPacket& msg, ObjectHeader& header);
    void ConstructObjectPart0(const HoloCanPacket& msg, ObjectType& object);
    void ConstructObjectPart1(const HoloCanPacket& msg, ObjectType& object);
    void ConstructObjectPart2(const HoloCanPacket& msg, ObjectType& object);
    void ConstructObjectPart3(const HoloCanPacket& msg, ObjectType& object);
    void ConvertToObstacle(const ObjectType& input, std::shared_ptr<ObstacleType>& output);
    void ConvertToObstaclePtrListWithTransform(const ObjectHeader& header, const ObjectListType& input,
                                               ObstaclePtrListType& output) const;
    void ConstructLaneboundaryPart0(const HoloCanPacket& msg, LineType& laneboundary);
    void ConstructLaneboundaryPart1(const HoloCanPacket& msg, LineType& laneboundary);
    void ConstructLaneboundaryPart2(const HoloCanPacket& msg, LineType& laneboundary);
    void ConvertToRoadFrameWithTransform(const LineListType& input, RoadFrameType& output);

private:
    ObjectHeader object_header_;
};

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo

#endif
