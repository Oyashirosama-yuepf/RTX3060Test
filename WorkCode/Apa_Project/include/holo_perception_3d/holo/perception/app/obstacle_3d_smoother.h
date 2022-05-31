/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_3d_smoother.h
 * @brief This header file defines Obstacle3DSmoother class.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2022-04-15"
 */

#ifndef HOLO_PERCEPTION_APP_OBSTACLE_3D_SMOOTHER_H_
#define HOLO_PERCEPTION_APP_OBSTACLE_3D_SMOOTHER_H_

#include <deque>
#include <list>
#include <memory>
#include <unordered_map>

#include <holo/common/odometry.h>
#include <holo/geometry/pose3.h>
#include <holo/log/hololog.h>
#include <holo/perception/common/box_object.h>

namespace holo
{
namespace perception
{
class Obstacle3DSmoother
{
public:
    using Scalar                   = holo::float32_t;
    using CameraDetectedObject     = BoxObjectT<Scalar, 128U>;
    using CameraDetectedObjectPtr  = std::shared_ptr<CameraDetectedObject>;
    using CameraDetectedObjectList = std::list<CameraDetectedObjectPtr>;

    using OdometryType    = holo::common::Odometryf;
    using OdometryMessage = std::shared_ptr<OdometryType>;
    using OdometryCache   = std::deque<OdometryMessage>;

    using Point3Type = holo::geometry::Point3T<Scalar>;
    using Point2Type = holo::geometry::Point2T<Scalar>;
    using Rot3Type   = holo::geometry::Rot3T<Scalar>;
    using Pose3Type  = holo::geometry::Pose3T<Scalar>;
    using Timestamp  = holo::common::Timestamp;
    using IdType     = holo::uint32_t;

    /**
     * @brief Construct a new Obstacle 3 D Smoother object
     *
     * @param window_size the number of frames inside a window
     */
    explicit Obstacle3DSmoother(uint32_t window_size);

    /**
     * @brief Destroy the Obstacle 3 D Smoother object
     *
     */
    ~Obstacle3DSmoother() = default;

    /**
     * @brief smooth single obstacle
     *
     * @param det_obj   input detected object
     * @param dr_odom   input DR odometry
     * @return true the obstacle is not filtered
     * @return false the  obstacle is filtered
     */
    bool DoWorkSingleObs(CameraDetectedObjectPtr& det_obj, OdometryType const& dr_odom);

    /**
     * @brief smooth a list of obstacles
     *
     * @param det_obj_list  input detected object
     * @param dr_odom   input DR odometry
     */
    void DoWork(CameraDetectedObjectList& det_obj_list, OdometryType const& dr_odom);

private:
    uint32_t                                                                      window_size_;
    std::unordered_map<std::string, std::deque<std::pair<Point3Type, Timestamp>>> map_obs_id_to_kp3d_queue_;
};

}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_APP_OBSTACLE_3D_SMOOTHER_H_
