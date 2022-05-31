/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ars408_someip.cpp
 * @brief A class to receive and construct conti radar outputs in someip format
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/03
 */

#include <holo/log/hololog.h>
#include <holo/core/types.h>
#include <holo/sensors/format/someip.h>
#include <holo/sensors/radar/ars408/ars408_someip.h>
#include <holo_c/sensors/dbc/conti_radar_dbc.h>
#include <holo_c/sensors/conti_radar/structure/conti_radar_object.h>

namespace holo
{
namespace sensors
{
namespace conti_radar
{
void ContiRadarDriverT<SomeipPacketType>::ParseData(const SomeipPacketType& data)
{
    /* check data */
    if (data.GetPayloadLength() < sizeof(SomeIpPayloadHeader))
    {
        LOG(ERROR) << "payload size too small:" << data.GetPayloadLength();
        return;
    }
    /* parse data */
    const SomeIpPayloadHeader* header = reinterpret_cast<const SomeIpPayloadHeader*>(data.GetPayload());
    if (header->h0 != '#')
    {
        LOG(ERROR) << "payload header mismatch:" << static_cast<uint32_t>(header->h0);
        return;
    }
    /* check header.rc */
    if (header->rc != parsing_buffer_.rc)
    {
        parsing_buffer_.Reset();
        parsing_buffer_.rc = header->rc;
    }
    uint32_t psize   = data.GetPayloadLength() - sizeof(SomeIpPayloadHeader);
    uint32_t poffset = (header->pi - 1) * PACKET_PAYLOAD_CAPACITY;
    (void)std::memcpy(parsing_buffer_.payload + poffset, data.GetPayload() + sizeof(SomeIpPayloadHeader), psize);
    parsing_buffer_.payload_size += psize;
    parsing_buffer_.payload_pnum++;
    if (header->pn != parsing_buffer_.payload_pnum)
    {
        return;
    }
    if (obstacles_callback_)
    {
        ParseObstacles(parsing_buffer_.payload, parsing_buffer_.payload_size);
    }
}

bool_t ContiRadarDriverT<SomeipPacketType>::ParseObstacles(const uint8_t* data, uint32_t size)
{
    struct ContiRadarObjectListRawData raw_objects;
    retcode_t                          retcode = conti_radar_object_list_raw_data_deserialize(&raw_objects, data, size);
    if (!(retcode > 0))
    {
        LOG(ERROR) << "failed to deserialize payload to objects: " << retcode;
        return false;
    }
    ObstaclePtrListType obstacles;
    obstacles.SetTimestamp(
        holo::common::Timestamp(raw_objects.objects[0].timestamp.sec, raw_objects.objects[0].timestamp.nsec));
    obstacles.SetCoordinate(extrinsic_.GetParentCoordinate());
    obstacles.SetSensorId(this->GetSensorId());
    Convert(raw_objects, obstacles);
    obstacles_callback_(obstacles);
    return true;
}

void ContiRadarDriverT<SomeipPacketType>::Convert(const ContiRadarObjectListRawData& input,
                                                  ObstaclePtrListType&               output) const
{
    uint32_t objnum = 0;
    auto     out    = output.GetObstacleList().begin();
    for (uint32_t i = 0; i < input.num && out != output.GetObstacleList().end(); i++)
    {
        if (0 == input.objects[i].prob_of_exist)
        {
            continue;
        }
        *out = std::make_shared<ObstacleType>();
        (*out)->SetSensorId(this->GetSensorId());
        Convert(input.objects[i], *out++);
        objnum++;
    }
    output.SetSize(objnum);
}

void ContiRadarDriverT<SomeipPacketType>::Convert(const ContiRadarObjectRawData& input,
                                                  std::shared_ptr<ObstacleType>& output) const
{
    uint8_t    u8val;
    float32_t  f32val;
    ObjectType object;
    /* part 1 */
    object.SetTimestamp(holo::common::Timestamp(input.timestamp.sec, input.timestamp.nsec));
    object.SetMeasCounter(0);
    u8val = CALC_Object_1_General_Object_ID(input.id, 1);
    object.SetId(u8val);
    f32val = CALC_Object_1_General_Object_DistLong(input.dist_lon, 1.0f);
    object.SetDistLong(f32val);
    f32val = CALC_Object_1_General_Object_DistLat(input.dist_lat, 1.0f);
    object.SetDistLat(f32val);
    f32val = CALC_Object_1_General_Object_VrelLong(input.vrel_lon, 1.0f);
    object.SetVrelLong(f32val);
    f32val = CALC_Object_1_General_Object_VrelLat(input.vrel_lat, 1.0f);
    object.SetVrelLat(f32val);
    f32val = CALC_Object_1_General_Object_RCS(input.rcs, 1.0f);
    object.SetRcs(f32val);
    f32val = CALC_Object_1_General_Object_DynProp(input.dyn_prop, 1.0f);
    object.SetDynprop(f32val);
    object.SetPart1Valid(true);
    /* part 2 */
    u8val = CALC_Object_2_Quality_Object_VrelLong_rms(input.vrel_lon_rms, 1);
    object.SetVrelLongRms(u8val);
    u8val = CALC_Object_2_Quality_Object_VrelLat_rms(input.vrel_lat_rms, 1);
    object.SetVrelLatRms(u8val);
    u8val = CALC_Object_2_Quality_Object_ProbOfexist(input.prob_of_exist, 1);
    object.SetProbOfExist(u8val);
    u8val = CALC_Object_2_Quality_Object_Orientation_rms(input.orientation_angle_rms, 1);
    object.SetAngleRms(u8val);
    u8val = CALC_Object_2_Quality_Object_MeasState(input.meas_state, 1);
    object.SetMeasState(u8val);
    u8val = CALC_Object_2_Quality_Object_DistLong_rms(input.dist_lon_rms, 1);
    object.SetDistLongRms(u8val);
    u8val = CALC_Object_2_Quality_Object_DistLat_rms(input.dist_lat_rms, 1);
    object.SetDistLatRms(u8val);
    u8val = CALC_Object_2_Quality_Object_ArelLong_rms(input.arel_lon_rms, 1);
    object.SetArelLongRms(u8val);
    u8val = CALC_Object_2_Quality_Object_ArelLat_rms(input.arel_lat_rms, 1);
    object.SetArelLatRms(u8val);
    object.SetPart2Valid(true);
    /* part 3 */
    f32val = CALC_Object_3_Extended_Object_Length(input.length, 1.0f);
    object.SetLength(f32val);
    f32val = CALC_Object_3_Extended_Object_Width(input.width, 1.0f);
    object.SetWidth(f32val);
    f32val = CALC_Object_3_Extended_Object_OrientationAngle(input.orientation_angle, 1.0f);
    object.SetAngle(f32val);
    f32val = CALC_Object_3_Extended_Object_ArelLong(input.arel_lon, 1.0f);
    object.SetArelLong(f32val);
    f32val = CALC_Object_3_Extended_Object_ArelLat(input.arel_lat, 1.0f);
    object.SetArelLat(f32val);
    u8val = CALC_Object_3_Extended_Object_Class(input.classification, 1.0f);
    object.SetClassification(u8val);
    object.SetPart3Valid(true);
    /* convert */
    object.ConvertToHoloObstacleWithTransform(extrinsic_, *output);
}

template class ContiRadarDriverT<SomeipPacketType>;

}  // namespace conti_radar
}  // namespace sensors
}  // namespace holo
