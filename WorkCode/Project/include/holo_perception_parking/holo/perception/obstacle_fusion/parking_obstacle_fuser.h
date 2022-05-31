/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_obstacle_fuser.h
 * @brief using uss to correct vision measuremnent.
 * @author wenxunzhe@holomatic.com
 * @date Apirl-28-2022
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_FUSER_H__
#define HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_FUSER_H__

#include <glog/logging.h>
#include <holo/common/odometry.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/obstacle_fusion/parking_kd_tree.h>
#include <holo/perception/utils/sensor_obstacle_track.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <map>
namespace holo
{
namespace perception
{
class ParkingObstacleFuser
{
public:
    using Scalar    = float32_t;
    using Timestamp = holo::common::Timestamp;
    using Vector3f  = holo::numerics::Vector3f;
    using Zone      = holo::geometry::Box3f;

    using ObstacleVisionPtrList = holo::obstacle::ObstacleVisionPtrList;
    using VisionObsType         = holo::obstacle::ObstacleVisionT<Scalar>;
    using VisionObsPtr          = std::shared_ptr<VisionObsType>;
    using VisionMessage         = std::shared_ptr<ObstacleVisionPtrList>;
    using VisionMessageMap      = std::unordered_map<uint32_t, VisionMessage>;
    using VisionMeasurementMap  = std::unordered_map<SensorMeasurementKey, VisionObsPtr, SensorMeasurementKeyHash>;
    using OdometryType          = holo::common::Odometryf;
    using OdometryMessage       = std::shared_ptr<OdometryType>;
    using OdometryCache         = std::deque<OdometryMessage>;

    using UssKdTreePtr = std::shared_ptr<KdTree>;
    using UssVector    = std::vector<holo::geometry::Point2f>;

    ParkingObstacleFuser();

    void DoWork(VisionMeasurementMap& vision_measurement_map, OdometryCache const& odo_cache,
                UssKdTreePtr const& uss_kd_tree, UssVector const& uss_vector);

    void Proximity(UssVector points, int index, UssKdTreePtr tree, float distanceTol, std::vector<int>& cluster,
                   std::vector<bool>& visited, Zone const& clustering_zone);

    std::vector<std::vector<int>> Clustering(UssVector const& points, UssKdTreePtr tree, float distanceTol,
                                             Zone const& clustering_zone);

private:
    bool_t checkInUssPerceptionZone(VisionObsPtr const& obs);

    void measurementUpdate(std::vector<std::vector<int>> cluster, UssVector const& uss_vector,
                           VisionObsPtr& vision_measurement);

    void vehicleMeasurementUpdate(VisionObsPtr& vision_measurement, Scalar const& k, Scalar const& b);

    void nonVehicleMeasurementUpdate(std::vector<std::vector<int>> cluster, UssVector const& uss_vector,
                                     VisionObsPtr& vision_measurement);

    void fittingLineLMS(UssVector const& uss_vector, std::vector<int> associated_uss, Scalar& k, Scalar& b);
};

}  // namespace perception
}  // namespace holo
#endif
