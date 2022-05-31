/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file types.h
 * @brief This header file defines common types for lidar calibration
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-09
 */

#ifndef HOLO_CALIBRATION_LIDAR_TYPES_H_
#define HOLO_CALIBRATION_LIDAR_TYPES_H_

#include <holo/log/hololog.h>
#include <holo/3d/common/common.h>
#include <holo/3d/common/kdtree.h>
#include <holo/3d/common/point_types.h>
#include <holo/3d/filter/point_filter.h>
#include <holo/3d/filter/voxel_grid_filter.h>
#include <holo/calibration/common/data_container_base.h>
#include <holo/common/odometry.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/spline.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace calibration
{
namespace lidar
{
using Scalar         = float64_t;
using PointScalar    = float32_t;
using Timestamp      = common::Timestamp;
using OdometryType   = common::OdometryT<Scalar>;
using Rot3Type       = geometry::Rot3T<Scalar>;
using Pose3Type      = geometry::Pose3T<Scalar>;
using Point3Type     = geometry::Point3T<Scalar>;
using Vector3Type    = numerics::Vector3T<Scalar>;
using Vector6Type    = numerics::Vector6T<Scalar>;
using Matrix6Type    = numerics::Matrix6T<Scalar>;
using Matrix3Type    = numerics::Matrix3T<Scalar>;
using Matrix4Type    = numerics::Matrix4T<Scalar>;
using PointT         = pointcloud::PointXYZIRSt<PointScalar>;
using PointNT        = pointcloud::PointXYZNormalt<PointScalar>;
using PointCloud     = pointcloud::PointCloudT<PointT>;
using PointNCloud    = pointcloud::PointCloudT<PointNT>;
using PointCloudPtr  = std::shared_ptr<PointCloud>;
using PointNCloudPtr = std::shared_ptr<PointNCloud>;
using KdTree         = pointcloud::KdTreeT<PointNT, Scalar>;
using KdTreePtr      = std::shared_ptr<KdTree>;

/**
 * @brief Point cloud wrapper
 *
 * @tparam PointT
 */
template <typename PointT>
struct PointCloudWrapper
{
    PointCloudWrapper(PointCloudPtr _cloud) : cloud(_cloud), feature_cloud(new PointNCloud), tree(nullptr)
    {
    }

    PointCloudPtr  cloud;          ///< original point cloud
    PointNCloudPtr feature_cloud;  ///< compenstated feature point cloud
    KdTreePtr      tree;           ///< feature cloud kdtree
};

}  // namespace lidar
}  // namespace calibration
}  // namespace holo

#endif
