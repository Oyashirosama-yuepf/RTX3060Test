/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_proxy.h
 * @brief This header file defines .
 * @author guoguangchao(guoguangchao@holomaitc.com)
 * @date 2020/09/14
 */

#ifndef HOLO_SENSOR_VEHICLE_INFO_VEHICLE_INFO_H
#define HOLO_SENSOR_VEHICLE_INFO_VEHICLE_INFO_H

#include <holo/common/chassis_state.h>
#include <holo/common/control_command.h>
#include <holo/common/vehicle_body_state.h>
#include <holo/core/types.h>
#include <holo/sensors/common/device.h>
#include <holo/sensors/common/interface.h>
#include <functional>
#if defined (ENABLE_VEHICLE_PROXY_AIONLX)
#include <holo/common/apa_control_command.h>
#endif

namespace holo
{
namespace sensors
{
using holo::common::ChassisState;
using holo::common::ControlCommand;
#if defined (ENABLE_VEHICLE_PROXY_AIONLX)
using holo::common::ApaControlCommand;
#endif
using holo::common::Timestamp;
using holo::common::VehicleBodyState;

struct WeatherValue
{
    holo::common::Timestamp timestamp;
    float32_t               rainfall;
    float32_t               temperature;
};

template <typename In, typename Out = In>
class VehicleProxyBase
{
public:
    using ChassisStateCallback     = std::function<void(const ChassisState&)>;
    using VehicleBodyStateCallback = std::function<void(const VehicleBodyState&)>;
    using WeatherValueCallback     = std::function<void(const WeatherValue&)>;
    using InType                   = In;
    using OutType                  = Out;

    VehicleProxyBase()
      : chassis_state_callback_(nullptr), vehicle_body_state_callback_(nullptr), weather_value_callback_(nullptr)
    {
    }

    void InstallCallback(const ChassisStateCallback& callback) noexcept
    {
        chassis_state_callback_ = callback;
    }
    void InstallCallback(const VehicleBodyStateCallback& callback) noexcept
    {
        vehicle_body_state_callback_ = callback;
    }
    void InstallCallback(const WeatherValueCallback& callback) noexcept
    {
        weather_value_callback_ = callback;
    }

    virtual void   ParseData(const InType&) = 0;
    virtual bool_t VehicleControlEnabled() const noexcept
    {
        return false;
    }
    virtual void VehicleControlLogic(const ChassisState&, const ControlCommand&, OutType&)
    {
    }
    #if defined (ENABLE_VEHICLE_PROXY_AIONLX)
    virtual void VehicleControlLogic(const ChassisState&, const ApaControlCommand&, OutType&)
    {
    }
    #endif

public:
    /* callbacks */
    ChassisStateCallback     chassis_state_callback_;
    VehicleBodyStateCallback vehicle_body_state_callback_;
    WeatherValueCallback     weather_value_callback_;
};

}  // namespace sensors
}  // namespace holo

#endif
