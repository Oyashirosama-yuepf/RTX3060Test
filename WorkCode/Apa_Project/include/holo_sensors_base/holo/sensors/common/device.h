/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file device.h
 * @brief define the sensor base class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-07-24
 */

#ifndef _HOLO_SENSORS_COMMON_DEVICE_H
#define _HOLO_SENSORS_COMMON_DEVICE_H

#include <holo/common/sensor_id.h>
#include <holo/core/types.h>

namespace holo
{
namespace sensors
{
namespace common
{
class Device
{
public:
    using SensorId = holo::common::SensorId;

    Device() noexcept              = default;
    Device(const Device&) noexcept = default;
    Device& operator=(const Device& other) noexcept = default;
    Device(SensorId sensor_id) noexcept : sensor_id_(sensor_id)
    {
    }

    virtual ~Device() = default;

    void SetSensorId(const SensorId& sensor_id) noexcept
    {
        sensor_id_ = sensor_id;
    }
    void SetSensorId(uint32_t sensor_id) noexcept
    {
        sensor_id_ = sensor_id;
    }
    const SensorId& GetSensorId() const noexcept
    {
        return sensor_id_;
    }

private:
    SensorId sensor_id_;
};

}  // namespace common
}  // namespace sensors
}  // namespace holo

#endif
