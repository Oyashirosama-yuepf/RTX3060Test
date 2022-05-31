/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file motion_status.h
 * @brief This header file defines a class to decide objs motion status
 * @author zouyi(zouyi@holomatic.com)
 * @date "2022-04-15"
 */

#ifndef HOLO_PERCEPTION_3D_APP_MOTION_STATUS_H_
#define HOLO_PERCEPTION_3D_APP_MOTION_STATUS_H_

#include <iostream>
#include <list>
#include <memory>

#include <holo/common/camera_fisheye.h>
#include <holo/common/odometry.h>
#include <holo/geometry/pose3.h>
#include <holo/log/hololog.h>
#include <holo/obstacle/obstacle_base.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/obstacle/obstacle_vision.h>
#include <holo/perception/common/box_object.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace perception
{

class MotionStatus
{
public:
    MotionStatus()  = default;
    ~MotionStatus() = default;
    struct Config;
    using Scalar           = holo::float32_t;
    using Timestamp        = holo::common::Timestamp;
    using Object           = holo::obstacle::ObstacleVisionT<holo::float32_t>;
    using ObjectList       = holo::obstacle::ObstacleVisionPtrList;
    using Odometryd        = holo::common::Odometryd;
    using MotionStatusType = holo::obstacle::MotionStatus;

    using CameraDetectedObjectType = BoxObjectT<Scalar, 128U>;
    using CameraDetectedObjectPtr  = std::shared_ptr<CameraDetectedObjectType>;
    using CameraDetectedObjectList = std::list<CameraDetectedObjectPtr>;
    using Pose3Type                = holo::geometry::Pose3T<Scalar>;

    /**
     * @brief
     * init with config
     * @param conf
     * @return uint32_t
     */
    uint32_t Init(Config const& conf);

    /**
     * @brief
     * set odometry(body in dr) and objlist ,their timestamp should be nearly same
     * Execute one frame data ,  result is setted in the input param
     * @param odometry
     * @param object_list
     * @return uint32_t
     */
    uint32_t Execute(Odometryd const& odometry, ObjectList& object_list);

    /**
     * @brief
     * set odometry(body in dr) and objlist ,their timestamp should be nearly same
     * Execute one frame data ,  result is returned  the input param
     * motion_info2 == (4,1) means static
     * @param odometry
     * @param object_list
     * @return uint32_t
     */
    uint32_t Execute(Odometryd const& odometry, CameraDetectedObjectList& object_list);

private:
    class Imply;
    std::shared_ptr<Imply> inner_imply_;
};

/**
 * @brief
 * the config should be setted by user
 */
struct MotionStatus::Config
{
    holo::geometry::Pose3d          pose3d;      // camera in body
    holo::common::FisheyeIntrinsicf intrinsic;   // include k d
    holo::yaml::Node                parameters;  // other parameters in yaml file
};

}  // namespace perception
}  // namespace holo
#endif  // HOLO_PERCEPTION_3D_APP_MOTION_STATUS_H_
