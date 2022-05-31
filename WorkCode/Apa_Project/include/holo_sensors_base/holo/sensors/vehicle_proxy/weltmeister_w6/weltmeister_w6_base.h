/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file weltmeister_w6_base.h
 * @brief This header file defines .
 * @author feiminghua(feiminghua@holomaitc.com)
 * @date 2022/02/14
 */
#ifndef HOLO_SENSOR_VEHICLE_PROXY_WELTMEISTER_W6_BASE_H
#define HOLO_SENSOR_VEHICLE_PROXY_WELTMEISTER_W6_BASE_H

#include <holo/sensors/vehicle_proxy/vehicle_proxy.h>

namespace holo
{
namespace sensors
{
namespace weltmeister_w6
{
/* driver template */
template <typename InType, typename OutType = InType>
class Weltmeister_W6_T
{
public:
    Weltmeister_W6_T() = 0;
};

}  // namespace weltmeister_w6
}  // namespace sensors
}  // namespace holo

#endif//HOLO_SENSOR_VEHICLE_PROXY_WELTMEISTER_W6_BASE_H
