/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_general_obstacle_id_tracker.h
 * @brief This header file defines .
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-08-17"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_GENERAL_OBSTACLE_ID_TRACKER_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_GENERAL_OBSTACLE_ID_TRACKER_H_

#include <holo/perception/utils/obstacle_id_tracking_pipeline.h>

#include <holo/perception/utils/impl/obstacle_id_tracking_pipeline.hpp>

/**
 * @addtogroup fusion
 *
 * @{
 */

/**
 * @brief This class is for obstacle's sensor id and obstacle id association.
 * ParkingGeneralObstacleIdTracker drived from GeneralObstacleIdTracker
 *
 * @details Eventually this class is deriverd from TrackingPipeline, with
 * <SensorMeasurementKey, _Track, SensorMeasurementKeyHash>.
 */

namespace holo
{
namespace perception
{
class ParkingVisionObstacleIdTracker : public VisionObstacleIdTracker
{
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif
