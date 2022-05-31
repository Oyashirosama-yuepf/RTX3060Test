/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2019-10-18
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_VEHICLE_CONFIG_H_
#define _HOLO_PLANNING_VEHICLE_CONFIG_H_

#include <holo/core/types.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace planning
{
namespace config
{

struct VehicleConfig
{
    float32_t width;
    float32_t length;
    float32_t wheel_base;
    float32_t max_brake;
    float32_t max_acc;
    float32_t imu_to_front_edge;
    float32_t imu_to_back_edge;
};

bool_t ParseVehicleConfig(const yaml::Node& node, VehicleConfig& cfg);

}  // namespace config
}  // namespace planning
}  // namespace holo

#endif