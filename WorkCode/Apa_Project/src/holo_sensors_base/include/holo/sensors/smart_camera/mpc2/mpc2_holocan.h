/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bosch_mpc_holocan.h
 * @brief A class to receive and construct bosch mpc outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/08/24
 */

#ifndef _HOLO_SENSORS_BOSCH_MPC_BOSCH_MPC_HOLOCAN_H
#define _HOLO_SENSORS_BOSCH_MPC_BOSCH_MPC_HOLOCAN_H

#include <holo/sensors/format/holocan.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_base.h>
#include <holo/sensors/smart_camera/mpc2/structure/mpc2_spd_limit_sign.h>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
using holo::sensors::format::HoloCanPacket;

/* driver based on someip packet */
template <>
class BoschMpcDriverT<HoloCanPacket> : public SmartCameraDriverT<HoloCanPacket>, public BoschMpcDriverBase
{
public:
    BoschMpcDriverT(const Extrinsicf& extrinsic) : SmartCameraDriverT<HoloCanPacket>(), BoschMpcDriverBase(extrinsic)
    {
    }
    void ParseData(const HoloCanPacket& msg);

public:
    void ConstructObjectPartA(const HoloCanPacket& msg, ObjectType& object);
    void ConstructObjectPartB(const HoloCanPacket& msg, ObjectType& object);
    void ConstructObjectPartC(const HoloCanPacket& msg, ObjectType& object);
    void ConstructObjectPartD(const HoloCanPacket& msg, ObjectType& object);
    void ConstructObjectPartE(const HoloCanPacket& msg, ObjectType& object);
    void ConvertToObstacle(const ObjectType& input, std::shared_ptr<ObstacleType>& output);
    void ConvertToObstaclePtrListWithTransform(const std::array<ObjectType, 16>& input,
                                               ObstaclePtrListType&              output) const;
    void ConstructLaneBoundaryPartA(const HoloCanPacket& msg, LineType& lane_boundary);
    void ConstructLaneBoundaryPartB(const HoloCanPacket& msg, LineType& lane_boundary);
    void ConvertToRoadFrameWithTransform(const std::array<LineType, 4>& input, RoadFrameType& output);

    void ConstructSpdLimitSign1PartA(const HoloCanPacket& msg, SpdSignType& spd_sign);
    void ConstructSpdLimitSign2PartA(const HoloCanPacket& msg, SpdSignType& spd_sign);
    void ConstructSpdLimitSign3PartA(const HoloCanPacket& msg, SpdSignType& spd_sign);
    void ConstructSpdLimitSign4PartA(const HoloCanPacket& msg, SpdSignType& spd_sign);
    void ConstructSpdLimitSign5PartA(const HoloCanPacket& msg, SpdSignType& spd_sign);
    void ConstructSpdLimitSign7PartA(const HoloCanPacket& msg, SpdSignType& spd_sign);
    void ConstructSpdLimitSign8PartA(const HoloCanPacket& msg, SpdSignType& spd_sign);
};

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo

#endif
