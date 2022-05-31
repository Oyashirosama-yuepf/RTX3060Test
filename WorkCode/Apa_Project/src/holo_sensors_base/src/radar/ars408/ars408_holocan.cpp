/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ars408_holocan.hpp
 * @brief A class to receive and construct conti radar outputs in someip format
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/03
 */

#include <holo/log/hololog.h>
#include <holo/core/types.h>
#include <holo/sensors/format/holocan.h>
#include <holo/sensors/radar/ars408/ars408_holocan.h>
#include <holo_c/sensors/dbc/conti_radar_dbc.h>

namespace holo
{
namespace sensors
{
namespace conti_radar
{
void ContiRadarDriverT<HoloCanPacket>::ParseData(const HoloCanPacket& msg)
{
    switch (msg.GetId())
    {
        case ID_Object_0_Status:
            /* judge if old data in buffer */
            if (0 != objnum_in_list_)
            {
                CanbusCycleEndHandler(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
            }
            /* start of cycle, clear valid flag */
            object_list_.clear();
            /* parsing message */
            ConstructObjectPart0(msg, object_list_info_);
            if (0 == object_list_info_.objects_num)
            {
                CanbusCycleEndHandler(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
            }
            break;
        case ID_Object_1_General:
            ConstructObjectPart1(msg, object_list_info_, object_list_);
            break;
        case ID_Object_2_Quality:
            ConstructObjectPart2(msg, object_list_);
            break;
        case ID_Object_3_Extended:
            objnum_in_list_ += ConstructObjectPart3(msg, object_list_);
            if (object_list_.size() == objnum_in_list_)
            {
                CanbusCycleEndHandler(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
            }
            break;
        default:
            break;
    }
}

void ContiRadarDriverT<HoloCanPacket>::CanbusCycleEndHandler(const holo::common::Timestamp& timestamp)
{
    if (obstacles_callback_)
    {
        ObstaclePtrListType obstacles;
        obstacles.SetTimestamp(timestamp);
        obstacles.SetCoordinate(extrinsic_.GetParentCoordinate());
        obstacles.SetSensorId(this->GetSensorId());
        Convert(object_list_info_, object_list_, obstacles);
        obstacles_callback_(obstacles);
    }
    object_list_.clear();
    object_list_info_.valid = false;
    objnum_in_list_         = 0;
}

bool_t ContiRadarDriverT<HoloCanPacket>::ConstructObjectPart0(const HoloCanPacket& msg, ObjectListInfo& list_info)
{
    uint32_t u32val;
    u32val                 = GET_Object_0_Status_Object_NofObjects(msg.GetData());
    list_info.objects_num  = CALC_Object_0_Status_Object_NofObjects(u32val, 1);
    u32val                 = GET_Object_0_Status_Object_MeasCounter(msg.GetData());
    list_info.measure_cntr = CALC_Object_0_Status_Object_MeasCounter(u32val, 1);
    list_info.valid        = true;

    return true;
}

bool_t ContiRadarDriverT<HoloCanPacket>::ConstructObjectPart1(const HoloCanPacket& msg, ObjectListInfo& list_info,
                                                              std::map<uint8_t, ObjectType>& object_list)
{
    uint32_t   u32val;
    uint8_t    u8val;
    float32_t  f32val;
    ObjectType object;
    /* fetch id and check */
    u32val = GET_Object_1_General_Object_ID(msg.GetData());
    u8val  = CALC_Object_1_General_Object_ID(u32val, 1);
    if (object_list.count(u8val))
    {
        /* seems bad error happens */
        LOG(ERROR) << "object list clear due to duplicated object id: " << uint32_t(u8val);
        /* clear outdated object list */
        object_list.clear();
        /* clear outdated object list info */
        list_info.valid = false;
    }
    object.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
    if (list_info.valid)
    {
        object.SetMeasCounter(list_info.measure_cntr);
    }
    else
    {
        object.SetMeasCounter(0);  //! using fake value here
    }
    object.SetId(u8val);
    u32val = GET_Object_1_General_Object_DistLong(msg.GetData());
    f32val = CALC_Object_1_General_Object_DistLong(u32val, 1.0f);
    object.SetDistLong(f32val);
    u32val = GET_Object_1_General_Object_DistLat(msg.GetData());
    f32val = CALC_Object_1_General_Object_DistLat(u32val, 1.0f);
    object.SetDistLat(f32val);
    u32val = GET_Object_1_General_Object_VrelLong(msg.GetData());
    f32val = CALC_Object_1_General_Object_VrelLong(u32val, 1.0f);
    object.SetVrelLong(f32val);
    u32val = GET_Object_1_General_Object_VrelLat(msg.GetData());
    f32val = CALC_Object_1_General_Object_VrelLat(u32val, 1.0f);
    object.SetVrelLat(f32val);
    u32val = GET_Object_1_General_Object_RCS(msg.GetData());
    f32val = CALC_Object_1_General_Object_RCS(u32val, 1.0f);
    object.SetRcs(f32val);
    u32val = GET_Object_1_General_Object_DynProp(msg.GetData());
    f32val = CALC_Object_1_General_Object_DynProp(u32val, 1.0f);
    object.SetDynprop(f32val);
    /* set part indicator */
    object.SetPart1Valid(true);
    object_list.insert(std::make_pair(u8val, object));

    return true;
}

bool_t ContiRadarDriverT<HoloCanPacket>::ConstructObjectPart2(const HoloCanPacket&           msg,
                                                              std::map<uint8_t, ObjectType>& object_list)
{
    uint8_t u8val;
    /* fetch id and check */
    u8val = GET_Object_2_Quality_Object_ID(msg.GetData());
    u8val = CALC_Object_2_Quality_Object_ID(u8val, 1);
    if (!object_list.count(u8val))
    {
        LOG(ERROR) << "object broken: " << uint32_t(u8val) << ", found in p2";
        return false;
    }
    ObjectType& object = object_list[u8val];
    u8val              = GET_Object_2_Quality_Object_VrelLong_rms(msg.GetData());
    u8val              = CALC_Object_2_Quality_Object_VrelLong_rms(u8val, 1);
    object.SetVrelLongRms(u8val);
    u8val = GET_Object_2_Quality_Object_VrelLat_rms(msg.GetData());
    u8val = CALC_Object_2_Quality_Object_VrelLat_rms(u8val, 1);
    object.SetVrelLatRms(u8val);
    u8val = GET_Object_2_Quality_Object_ProbOfexist(msg.GetData());
    u8val = CALC_Object_2_Quality_Object_ProbOfexist(u8val, 1);
    object.SetProbOfExist(u8val);
    u8val = GET_Object_2_Quality_Object_Orientation_rms(msg.GetData());
    u8val = CALC_Object_2_Quality_Object_Orientation_rms(u8val, 1);
    object.SetAngleRms(u8val);
    u8val = GET_Object_2_Quality_Object_MeasState(msg.GetData());
    u8val = CALC_Object_2_Quality_Object_MeasState(u8val, 1);
    object.SetMeasState(u8val);
    u8val = GET_Object_2_Quality_Object_DistLong_rms(msg.GetData());
    u8val = CALC_Object_2_Quality_Object_DistLong_rms(u8val, 1);
    object.SetDistLongRms(u8val);
    u8val = GET_Object_2_Quality_Object_DistLat_rms(msg.GetData());
    u8val = CALC_Object_2_Quality_Object_DistLat_rms(u8val, 1);
    object.SetDistLatRms(u8val);
    u8val = GET_Object_2_Quality_Object_ArelLong_rms(msg.GetData());
    u8val = CALC_Object_2_Quality_Object_ArelLong_rms(u8val, 1);
    object.SetArelLongRms(u8val);
    u8val = GET_Object_2_Quality_Object_ArelLat_rms(msg.GetData());
    u8val = CALC_Object_2_Quality_Object_ArelLat_rms(u8val, 1);
    object.SetArelLatRms(u8val);
    /* set part indicator */
    object.SetPart2Valid(true);

    return true;
}

bool_t ContiRadarDriverT<HoloCanPacket>::ConstructObjectPart3(const HoloCanPacket&           msg,
                                                              std::map<uint8_t, ObjectType>& object_list)
{
    uint32_t  u32val;
    uint8_t   u8val;
    float32_t f32val;
    /* fetch id and check */
    u32val = GET_Object_3_Extended_Object_ID(msg.GetData());
    u8val  = CALC_Object_3_Extended_Object_ID(u32val, 1);
    if (!object_list.count(u8val))
    {
        LOG(ERROR) << "object broken: " << uint32_t(u8val) << ", found in p3";
        return false;
    }
    ObjectType& object = object_list[u8val];
    u32val             = GET_Object_3_Extended_Object_Length(msg.GetData());
    f32val             = CALC_Object_3_Extended_Object_Length(u32val, 1.0f);
    object.SetLength(f32val);
    u32val = GET_Object_3_Extended_Object_Width(msg.GetData());
    f32val = CALC_Object_3_Extended_Object_Width(u32val, 1.0f);
    object.SetWidth(f32val);
    u32val = GET_Object_3_Extended_Object_OrientationAngle(msg.GetData());
    f32val = CALC_Object_3_Extended_Object_OrientationAngle(u32val, 1.0f);
    object.SetAngle(f32val);
    u32val = GET_Object_3_Extended_Object_ArelLong(msg.GetData());
    f32val = CALC_Object_3_Extended_Object_ArelLong(u32val, 1.0f);
    object.SetArelLong(f32val);
    u32val = GET_Object_3_Extended_Object_ArelLat(msg.GetData());
    f32val = CALC_Object_3_Extended_Object_ArelLat(u32val, 1.0f);
    object.SetArelLat(f32val);
    u8val = GET_Object_3_Extended_Object_Class(msg.GetData());
    u8val = CALC_Object_3_Extended_Object_Class(u8val, 1.0f);
    object.SetClassification(u8val);
    /* set part indicator */
    object.SetPart3Valid(true);

    return true;
}

void ContiRadarDriverT<HoloCanPacket>::Convert(const ObjectListInfo&                list_info,
                                               const std::map<uint8_t, ObjectType>& list,
                                               ObstaclePtrListType&                 output) const
{
    uint32_t objnum = 0;
    auto     out    = output.GetObstacleList().begin();
    for (auto in = list.cbegin(); in != list.cend() && out != output.GetObstacleList().end(); in++)
    {
        if (!in->second.IsValid())
        {
            continue;
        }
        *out = std::make_shared<ObstacleType>();
        (*out)->SetSensorId(this->GetSensorId());
        in->second.ConvertToHoloObstacleWithTransform(extrinsic_, **out++);
        objnum++;
    }
    output.SetSize(objnum);
    /* log bad objects number */
    if (!list_info.valid)
    {
        LOG(ERROR) << "lost object list info in this cycle";
    }
    else
    {
        if (objnum != list_info.objects_num)
        {
            LOG(ERROR) << "lost " << list_info.objects_num - objnum << " of " << uint32_t(list_info.objects_num)
                       << " objects";
        }
    }
}

template class ContiRadarDriverT<HoloCanPacket>;

}  // namespace conti_radar
}  // namespace sensors
}  // namespace holo
