/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file weltmeister_w6_someip.h
 * @brief This header file defines
 * @author feiminghua
 * @date 2022-02-17
 */
#ifndef HOLO_SENSOR_VEHICLE_PROXY_VEHICLE_W6_SOMEIP_H
#define HOLO_SENSOR_VEHICLE_PROXY_VEHICLE_W6_SOMEIP_H

#include <holo/core/types.h>
#include <iostream>
#include <holo/sensors/format/someip.h>
#include <holo/sensors/vehicle_proxy/weltmeister_w6/weltmeister_w6_base.h>
#include <holo_c/common/chassis_state.h>
#include <holo_c/sensors/vehicle_body_state/vehicle_body_state.h>

//fmh mod the class name Weltmeister_W6_T
namespace holo
{
namespace sensors
{
namespace weltmeister_w6
{
using SomeipPacketType = holo::sensors::format::SomeipPacket<512>;
//class template special
template <>
class Weltmeister_W6_T<SomeipPacketType, SomeipPacketType> : public VehicleProxyBase<SomeipPacketType, SomeipPacketType>
{
public:
    Weltmeister_W6_T() : VehicleProxyBase<SomeipPacketType, SomeipPacketType>()
    {
    }

    void ParseData(const SomeipPacketType& data)
    {
        uint32_t length = data.GetPayloadLength();

        if (data.GetMethodId() == ID_CHASSIS_STATE)
        {
            ::ChassisState             struct_cs;
            holo::common::ChassisState chassis_state;
            chassis_state_init_default(&struct_cs);
            chassis_state_deserialize(&struct_cs, data.GetPayload() + 4, length - 4);
            holo::common::Timestamp stamp(struct_cs.stamp.sec, struct_cs.stamp.nsec);
            chassis_state.SetTimestamp(stamp);
            chassis_state.SetVehicleSpeed(chassis_state_get_vehicle_speed(&struct_cs));
            chassis_state.SetFrontLeftWheelSpeed(chassis_state_get_front_left_wheel_speed(&struct_cs));
            chassis_state.SetFrontRightWheelSpeed(chassis_state_get_front_right_wheel_speed(&struct_cs));
            chassis_state.SetRearLeftWheelSpeed(chassis_state_get_rear_left_wheel_speed(&struct_cs));
            chassis_state.SetRearRightWheelSpeed(chassis_state_get_rear_right_wheel_speed(&struct_cs));
            chassis_state.SetLongitudinalAcceleration(chassis_state_get_longitudinal_acceleration(&struct_cs));
            chassis_state.SetLateralAcceleration(chassis_state_get_lateral_acceleration(&struct_cs));
            chassis_state.SetYawRate(chassis_state_get_yaw_rate(&struct_cs));
            chassis_state.SetFrontWheelAngle(chassis_state_get_front_wheel_angle(&struct_cs));
            chassis_state.SetEnergySourceLevel(chassis_state_get_energy_source_level(&struct_cs));

            /* callback */
            if (chassis_state_callback_)
            {
                chassis_state_callback_(chassis_state);
            }
        }
        else if (data.GetMethodId() == ID_VEHICLE_BODY_STATE)
        {
            ::VehicleBodyState             struct_vbs;
            holo::common::VehicleBodyState vehicle_body_state;
            vehicle_body_state_init_default(&struct_vbs);
            vehicle_body_state_deserialize(&struct_vbs, data.GetPayload() + 4, length - 4);
            holo::common::Timestamp stamp(struct_vbs.stamp.sec, struct_vbs.stamp.nsec);
            vehicle_body_state.SetTimestamp(stamp);
            vehicle_body_state.SetFrontLeftTirePressure(vehicle_body_state_get_front_left_tire_pressure(&struct_vbs));
            vehicle_body_state.SetFrontRightTirePressure(vehicle_body_state_get_front_right_tire_pressure(&struct_vbs));
            vehicle_body_state.SetRearLeftTirePressure(vehicle_body_state_get_rear_left_tire_pressure(&struct_vbs));
            vehicle_body_state.SetRearRightTirePressure(vehicle_body_state_get_rear_right_tire_pressure(&struct_vbs));
            vehicle_body_state.SetStateValue(vehicle_body_state_get_state_flags(&struct_vbs));

            /* callback */
            if (vehicle_body_state_callback_)
            {
                vehicle_body_state_callback_(vehicle_body_state);
            }

            WeatherValue weather_value;
            weather_value.timestamp.SetSec(struct_vbs.stamp.sec);
            weather_value.timestamp.SetNsec(struct_vbs.stamp.nsec);
            weather_value.rainfall    = (float32_t)struct_vbs.rain_fall;
            weather_value.temperature = (float32_t)struct_vbs.temperature;

            if (weather_value_callback_)
            {
                weather_value_callback_(weather_value);
            }
        }
        else
        {
            /* blank */
        }
    }

private:
    enum : uint32_t
    {
        ID_CHASSIS_STATE      = 11,
        ID_VEHICLE_BODY_STATE = 12
    };
};//class Weltmeister_W6_T

}  // namespace weltmeister_w6
}  // namespace sensors
}  // namespace holo

#endif//HOLO_SENSOR_VEHICLE_PROXY_VEHICLE_W6_SOMEIP_H
