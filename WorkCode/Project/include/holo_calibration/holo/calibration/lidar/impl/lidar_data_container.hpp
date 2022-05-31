/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lidar_data_container.hpp
 * @brief Implementation of lidar data container
 * @author luopei(luopei@holomatic.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-09
 */

#ifndef HOLO_CALIBRATION_LIDAR_LIDAR_DATA_CONTAINER_HPP_
#define HOLO_CALIBRATION_LIDAR_LIDAR_DATA_CONTAINER_HPP_

#include <Eigen/Dense>

#include <holo/calibration/lidar/lidar_data_container.h>

namespace holo
{
namespace calibration
{
namespace lidar
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
LidarDataContainerT<PointT>::LidarDataContainerT(Parameters const& params) : params_(params)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
LidarDataContainerT<PointT>::~LidarDataContainerT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void LidarDataContainerT<PointT>::SetData(std::vector<PointCloudPtr> const& clouds, PoseSplinePtr const& pose_spline)
{
    setSourceData(clouds);
    setTargetData(pose_spline);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
uint16_t LidarDataContainerT<PointT>::GetDataSize() const
{
    return cloud_wrappers_.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
typename LidarDataContainerT<PointT>::Wrapper const& LidarDataContainerT<PointT>::GetSource(uint16_t const index) const
{
    if (index >= GetDataSize())
    {
        std::string msg = "index out of bounds!";
        LOG(ERROR) << msg;
        throw std::out_of_range(msg);
    }

    return cloud_wrappers_[index];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
typename LidarDataContainerT<PointT>::Wrapper& LidarDataContainerT<PointT>::GetSource(uint16_t const index)
{
    if (index >= GetDataSize())
    {
        std::string msg = "index out of bounds!";
        LOG(ERROR) << msg;
        throw std::out_of_range(msg);
    }

    return cloud_wrappers_[index];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
Pose3Type const& LidarDataContainerT<PointT>::GetTarget(uint16_t const index) const
{
    if (index >= GetDataSize())
    {
        std::string msg = "index out of bounds!";
        LOG(ERROR) << msg;
        throw std::out_of_range(msg);
    }

    return poses_[index];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
Pose3Type& LidarDataContainerT<PointT>::GetTarget(uint16_t const index)
{
    if (index >= GetDataSize())
    {
        std::string msg = "index out of bounds!";
        LOG(ERROR) << msg;
        throw std::out_of_range(msg);
    }

    return poses_[index];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void LidarDataContainerT<PointT>::UpdateStatus()
{
    uint8_t num = GetDataSize();

    for (uint8_t i = 0u; i < num; ++i)
    {
        Wrapper& wrapper = cloud_wrappers_[i];
        compensatePointCloud(wrapper);
    }

    updatePointCloudWrapperInfo();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void LidarDataContainerT<PointT>::setSourceData(std::vector<PointCloudPtr> const& clouds)
{
    cloud_wrappers_.clear();
    cloud_wrappers_.reserve(clouds.size());

    PointCheckerPtr zero_checker(new pointcloud::ZeroPointCheckerT<PointT>());
    PointCheckerPtr nan_checker(new pointcloud::NaNPointCheckerT<PointT>());

    for (auto const& cloud : clouds)
    {
        PointFilter point_filter(cloud);
        point_filter.AddChecker(zero_checker);
        point_filter.AddChecker(nan_checker);
        PointCloudPtr output = point_filter.Compute();
        cloud_wrappers_.push_back(Wrapper(output));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void LidarDataContainerT<PointT>::setTargetData(PoseSplinePtr const& pose_spline)
{
    pose_spline_ = pose_spline;

    uint32_t num_poses = cloud_wrappers_.size();
    poses_.resize(num_poses);

    for (uint32_t i = 0u; i < num_poses; ++i)
    {
        Timestamp t = cloud_wrappers_[i].cloud->front().GetTimestamp();
        assert(t >= pose_spline->GetStartTime() && t <= pose_spline->GetEndTime());

        if (t < pose_spline->GetStartTime() || t > pose_spline->GetEndTime())
        {
            std::string msg = " timestamp out of range!";
            LOG(ERROR) << msg;
            throw std::out_of_range(msg);
        }

        poses_[i] = pose_spline_->GetPose(t, true);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void LidarDataContainerT<PointT>::compensatePointCloud(Wrapper& wrapper)
{
    if (wrapper.cloud->empty())
    {
        return;
    }

    PointCloudPtr  cloud = wrapper.cloud;
    PointNCloudPtr feature_cloud(new PointNCloud);
    pointcloud::CopyPointCloud(*cloud, *feature_cloud);

    uint32_t num_points = cloud->size();

    Timestamp t0 = cloud->front().GetTimestamp();
    Timestamp t1 = cloud->back().GetTimestamp();

    if (t0 >= t1)
    {
        LOG(WARNING) << "all points have same timestamp!";
        wrapper.feature_cloud = feature_cloud;  /// do not compensate feature cloud
        return;
    }

    Pose3Type extrinsic_pose = Base::GetExtrinsic();

    Pose3Type pose0 = pose_spline_->GetPose(t0) * extrinsic_pose;
    Pose3Type pose1 = pose_spline_->GetPose(t1) * extrinsic_pose;
    Pose3Type pose  = pose0.Inverse() * pose1;

    // compensate each point using linear interpolation
    for (uint32_t i = 0U; i < num_points; ++i)
    {
        PointT& pt    = cloud->at(i);
        Scalar  t     = pt.GetTimestamp().ToSec();
        Scalar  ratio = (t - t0.ToSec()) / (t1.ToSec() - t0.ToSec());
        assert(ratio >= 0 && ratio <= 1);

        if (ratio < 0 || ratio > 1)
        {
            std::string msg = " ratio out of range!";
            LOG(ERROR) << msg;
            throw std::out_of_range(msg);
        }

        Pose3Type  pose_t = Pose3Type::Interpolate(Pose3Type::Identity(), pose, ratio);
        Point3Type pt_t   = pose_t.TransformFrom(Point3Type(pt[0], pt[1], pt[2]));

        feature_cloud->at(i).Set(pt_t[0], pt_t[1], pt_t[2]);
    }

    wrapper.feature_cloud = feature_cloud;  /// update feature cloud
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void LidarDataContainerT<PointT>::updatePointCloudWrapperInfo()
{
    Pose3Type extrinsic_pose = Base::GetExtrinsic();
    uint8_t   num_data       = GetDataSize();
    size_t    k              = params_.knn_num;
    Scalar    voxel_size     = params_.voxel_size;

    VoxelFilter filter(voxel_size, voxel_size, voxel_size);

    for (uint8_t i = 0u; i < num_data; ++i)
    {
        Wrapper& wrapper = GetSource(i);

        PointNCloudPtr feature_cloud = wrapper.feature_cloud;

        filter.SetInputPointCloud(feature_cloud);
        feature_cloud = filter.Compute();
        KdTreePtr tree(new KdTree);
        tree->SetInputPointCloud(feature_cloud);

        std::vector<size_t> nn_indices(k);
        std::vector<Scalar> nn_dists(k);

        for (uint32_t j = 0U; j < feature_cloud->size(); ++j)
        {
            PointNT& pt = feature_cloud->at(j);

            if (tree->KnnSearch(pt, k, nn_indices, nn_dists) < 3)
            {
                continue;
            }

            Matrix3Type cov;
            Vector3Type mean;
            pointcloud::ComputeMeanAndCovarianceMatrix(*feature_cloud, nn_indices, cov, mean);

            Eigen::Matrix3d cov_eigen;
            memcpy(cov_eigen.data(), cov.GetData(), sizeof(Scalar) * 9U);

            // This method is usually significantly faster than the QR iterative algorithm
            // Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> es;
            // es.computeDirect(cov_eigen);
            // es.compute(cov_eigen);
            // Eigen::Vector3d n = es.eigenvectors().col(0);
            Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solver;
            solver.compute(cov_eigen, Eigen::ComputeEigenvectors);
            Eigen::Vector3d n = solver.eigenvectors().col(0);
            Eigen::Vector3d v(0.0 - pt[0], 0.0 - pt[1], 0.0 - pt[2]);

            if (v.dot(n) < 0)
            {
                n *= -1;
            }

            pt.SetNormal(n(0), n(1), n(2));
        }

        wrapper.feature_cloud = feature_cloud;
        wrapper.tree          = tree;
    }
}

}  // namespace lidar
}  // namespace calibration
}  // namespace holo

#endif
