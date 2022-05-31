/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300_someip.h
 * @brief A class to receive and construct aptive ifv300 outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/03
 */

#ifndef HOLO_SENSORS_IFV300_IFV300_SOMEIP_H_
#define HOLO_SENSORS_IFV300_IFV300_SOMEIP_H_

#include <holo/core/types.h>
#include <holo/sensors/format/someip.h>
#include <holo/sensors/smart_camera/ifv300/ifv300_base.h>
#include <holo_c/sensors/ifv300/structure/ifv300_line.h>
#include <holo_c/sensors/ifv300/structure/ifv300_object.h>

namespace holo
{
namespace sensors
{
namespace ifv300
{
using SomeipPacketType = holo::sensors::format::SomeipPacket<1024>;

template <>
class Ifv300DriverT<SomeipPacketType> : public SmartCameraDriverT<SomeipPacketType>, public Ifv300DriverBase
{
public:
    Ifv300DriverT(const Extrinsicf& extrinsic) : SmartCameraDriverT<SomeipPacketType>(), Ifv300DriverBase(extrinsic)
    {
    }

    void ParseData(const SomeipPacketType& data);

private:
    void   Convert(const IfvObjectRawData& input, std::shared_ptr<ObstacleType>& output) const;
    void   Convert(const IfvObjectListRawData& input, ObstaclePtrListType& output) const;
    void   Convert(const IfvLineInfoCurve& input, LineType& output);
    void   Convert(const IfvLinesRawData& input, RoadFrameType& output);
    bool_t ParseObstacles(const uint8_t* data, uint32_t size);
    bool_t ParseLaneboundaries(const uint8_t* data, uint32_t size);
};

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo

#endif
