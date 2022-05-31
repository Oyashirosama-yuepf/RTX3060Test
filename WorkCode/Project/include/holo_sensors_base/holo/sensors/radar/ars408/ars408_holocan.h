/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file conti_radar_holocan.h
 * @brief A class to receive and construct conti radar outputs in holocan format
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/12
 */

#ifndef HOLO_SENSORS_CONTI_RADAR_CONTI_RADAR_HOLOCAN_H_
#define HOLO_SENSORS_CONTI_RADAR_CONTI_RADAR_HOLOCAN_H_

#include <holo/core/types.h>
#include <holo/sensors/format/holocan.h>
#include <holo/sensors/radar/ars408/ars408_base.h>

namespace holo
{
namespace sensors
{
namespace conti_radar
{
using holo::sensors::format::HoloCanPacket;

template <>
class ContiRadarDriverT<HoloCanPacket> : public ContiRadarDriverBase<HoloCanPacket>
{
public:
    ContiRadarDriverT(const Extrinsicf& extrinsic)
      : ContiRadarDriverBase<HoloCanPacket>(extrinsic), object_list_info_{}, objnum_in_list_(0)
    {
    }

    void ParseData(const HoloCanPacket& data);

private:
    struct ObjectListInfo
    {
        uint16_t measure_cntr;
        uint8_t  objects_num;
        bool_t   valid;
    };

private:
    void   Convert(const ObjectListInfo& list_info, const std::map<uint8_t, ObjectType>& list,
                   ObstaclePtrListType& output) const;
    void   CanbusCycleEndHandler(const holo::common::Timestamp& timestamp);
    bool_t ConstructObjectPart0(const HoloCanPacket& msg, ObjectListInfo& object_list_info);
    bool_t ConstructObjectPart1(const HoloCanPacket& msg, ObjectListInfo& object_list_info,
                                std::map<uint8_t, ObjectType>& object_list);
    bool_t ConstructObjectPart2(const HoloCanPacket& msg, std::map<uint8_t, ObjectType>& object_list);
    bool_t ConstructObjectPart3(const HoloCanPacket& msg, std::map<uint8_t, ObjectType>& object_list);

private:
    ObjectListInfo                object_list_info_;
    std::map<uint8_t, ObjectType> object_list_;
    uint32_t                      objnum_in_list_;
};

}  // namespace conti_radar
}  // namespace sensors
}  // namespace holo

#endif
