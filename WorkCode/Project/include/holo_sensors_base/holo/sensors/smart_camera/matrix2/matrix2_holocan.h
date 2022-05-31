/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file horizon_matrix2_holocan.h
 * @brief A class to receive and construct horizon matrix2 outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/09
 */

#ifndef _HOLO_SENSORS_HORIZON_MATRIX2_HORIZON_MATRIX2_HOLOCAN_H
#define _HOLO_SENSORS_HORIZON_MATRIX2_HORIZON_MATRIX2_HOLOCAN_H

#include <holo/core/types.h>
#include <holo/sensors/format/holocan.h>
#include <holo/sensors/smart_camera/matrix2/matrix2_base.h>

namespace holo
{
namespace sensors
{
namespace horizon_matrix2
{
using holo::sensors::format::HoloCanPacket;

/* driver based on holo can */
template <>
class HorizonMatrix2DriverT<HoloCanPacket> : public SmartCameraDriverT<HoloCanPacket>, public HorizonMatrix2DriverBase
{
public:
    HorizonMatrix2DriverT(const Extrinsicf& extrinsic)
      : SmartCameraDriverT<HoloCanPacket>(), HorizonMatrix2DriverBase(extrinsic)
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

private:
    void ConstructObjectPartA(const HoloCanPacket& msg, ObjectType& object);
    void ConstructObjectPartB(const HoloCanPacket& msg, ObjectType& object);
    void ConstructObjectPartC(const HoloCanPacket& msg, ObjectType& object);
    void ConstructObjectPartD(const HoloCanPacket& msg, ObjectType& object);
    void ConstructObjectPartE(const HoloCanPacket& msg, ObjectType& object);
    void ConvertToObstacle(const ObjectType& input, std::shared_ptr<ObstacleType>& output);
    void ConvertToObstaclePtrListWithTransform(const ObjectListType& input, ObstaclePtrListType& output) const;
    void ConstructLaneboundaryPartA(const HoloCanPacket& msg, LineType& laneboundary);
    void ConstructLaneboundaryPartB(const HoloCanPacket& msg, LineType& laneboundary);
    void ConvertToRoadFrameWithTransform(const LineListType& input, RoadFrameType& output);
};

}  // namespace horizon_matrix2
}  // namespace sensors
}  // namespace holo

#endif
