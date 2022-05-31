/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file traffic_light.h
 * @brief This header file defines TrafficLight class
 * @author Zhou Huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-20
 */
#ifndef HOLO_COMMON_TRAFFIC_LIGHT_H_
#define HOLO_COMMON_TRAFFIC_LIGHT_H_

#include <holo/common/details/traffic_light.h>

namespace holo
{
namespace common
{
template <size_t LANE_SIZE, size_t SIGNAL_SIZE>
using TrafficLightT = details::TrafficLightT<LANE_SIZE, SIGNAL_SIZE>;

template <size_t LANE_SIZE, size_t SIGNAL_SIZE, size_t TRAFFIC_LIGHT_SIZE>
using TrafficLightsT = details::TrafficLightsT<LANE_SIZE, SIGNAL_SIZE, TRAFFIC_LIGHT_SIZE>;

}  // namespace common
}  // namespace holo
#endif