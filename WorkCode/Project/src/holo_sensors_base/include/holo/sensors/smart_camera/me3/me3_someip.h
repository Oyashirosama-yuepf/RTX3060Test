/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_someip.h
 * @brief A class to receive and construct hirain mobileye outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/03
 */

#ifndef HOLO_SENSORS_MOBILEYE_MOBILEYE_SOMEIP_H_
#define HOLO_SENSORS_MOBILEYE_MOBILEYE_SOMEIP_H_

#include <holo/core/types.h>
#include <holo/sensors/format/someip.h>
#include <holo/sensors/smart_camera/me3/me3_base.h>
#include <holo_c/sensors/mobileye/structure/mobileye_lane.h>
#include <holo_c/sensors/mobileye/structure/mobileye_object.h>

namespace holo
{
namespace sensors
{
namespace mobileye
{
using SomeipPacketType = holo::sensors::format::SomeipPacket<1024>;

template <>
class MobileyeDriverT<SomeipPacketType> : public SmartCameraDriverT<SomeipPacketType>, public MobileyeDriverBase
{
public:
    MobileyeDriverT(const Extrinsicf& extrinsic) : SmartCameraDriverT<SomeipPacketType>(), MobileyeDriverBase(extrinsic)
    {
    }

    void ParseData(const SomeipPacketType& data);

private:
    bool_t ParseObstacles(const uint8_t* data, uint32_t size);
    void   Convert(const MobileyeObjectRawData& input, std::shared_ptr<ObstacleType>& output) const;
    void   Convert(const MobileyeObjectListRawData& input, ObstaclePtrListType& output) const;
    bool_t ParseLaneboundaries(const uint8_t* data, uint32_t size);
    void   Convert(const MobileyeLaneRawData& input, LineType& output);
    void   Convert(const MobileyeLanesRawData& input, RoadFrameType& output);
};

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo

#endif
