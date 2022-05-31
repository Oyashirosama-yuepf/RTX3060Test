/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300_holocan.h
 * @brief A class to receive and construct ifv300 outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/04
 */

#ifndef _HOLO_SENSORS_IFV300_IFV300_HOLOCAN_H
#define _HOLO_SENSORS_IFV300_IFV300_HOLOCAN_H

#include <holo/core/types.h>
#include <holo/sensors/format/holocan.h>
#include <holo/sensors/smart_camera/ifv300/ifv300_base.h>

namespace holo
{
namespace sensors
{
namespace ifv300
{
using holo::sensors::format::HoloCanPacket;

/* driver based on holo can */
template <>
class Ifv300DriverT<HoloCanPacket> : public SmartCameraDriverT<HoloCanPacket>, public Ifv300DriverBase
{
public:
    Ifv300DriverT(const Extrinsicf& extrinsic)
      : SmartCameraDriverT<HoloCanPacket>(), Ifv300DriverBase(extrinsic), lane_boundary_header_{}
    {
    }

    void ParseData(const HoloCanPacket& msg);

private:
    struct LaneboundaryHeader
    {
        uint8_t left_left_type;       //! lane boundary type
        uint8_t left_type;            //! lane boundary type
        uint8_t right_type;           //! lane boundary type
        uint8_t right_right_type;     //! lane boundary type
        uint8_t left_left_lkaconf;    //! lane boundary quality
        uint8_t left_lkaconf;         //! lane boundary quality
        uint8_t right_lkaconf;        //! lane boundary quality
        uint8_t right_right_lkaconf;  //! lane boundary quality
        bool_t  valid;                //! valid indicator
    };

private:
    bool_t ConstructObjectPartA(const HoloCanPacket& msg, std::array<ObjectType, IFV300_OBJECTS_NUM>& object_list);
    bool_t ConstructObjectPartB(const HoloCanPacket& msg, std::array<ObjectType, IFV300_OBJECTS_NUM>& object_list);
    bool_t ConstructObjectPartC(const HoloCanPacket& msg, std::array<ObjectType, IFV300_OBJECTS_NUM>& object_list);
    void   ConvertToObstacle(const ObjectType& input, std::shared_ptr<ObstacleType>& output);
    void   ConvertToObstaclePtrListWithTransform(const std::array<ObjectType, IFV300_OBJECTS_NUM>& input,
                                                 ObstaclePtrListType&                              output) const;
    void   ConstructLaneboundaryHeader(const HoloCanPacket& msg, LaneboundaryHeader& header);
    void   ConstructLaneboundaryBody(const HoloCanPacket& msg, LineType& laneboundary);
    void   ConvertToRoadFrameWithTransform(const std::array<LineType, IFV300_LINES_NUM>& input, RoadFrameType& output);

private:
    LaneboundaryHeader lane_boundary_header_;
};

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo

#endif
