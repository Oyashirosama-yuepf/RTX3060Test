/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common.h
 * @brief This header file defines common functions of point cloud
 * @author luopei(luopei@holomaitc.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-10-29
 */

#ifndef HOLO_3D_COMMON_COMMON_H_
#define HOLO_3D_COMMON_COMMON_H_

#include <holo/3d/common/details/common.h>
#include <holo/3d/common/point_cloud.h>
#include <holo/3d/common/point_types.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief Copy point
 *
 * @tparam PointInT
 * @tparam PointOutT
 * @param[in] pt_in input point
 * @param[out] pt_out output point
 */
template <typename PointInT, typename PointOutT>
void CopyPoint(PointInT const& pt_in, PointOutT& pt_out)
{
    internal::CopyPointFunctor<PointInT, PointOutT> copy;
    copy(pt_in, pt_out);
}

/**
 * @brief Copy point cloud
 *
 * @tparam PointInT
 * @tparam PointOutT
 * @param[in] pcd1 input point cloud
 * @param[out] pcd2 output point cloud
 */
template <typename PointInT, typename PointOutT>
void CopyPointCloud(PointCloudT<PointInT> const& pcd1, PointCloudT<PointOutT>& pcd2)
{
    using PoseType = typename PointCloudT<PointOutT>::PoseType;
    PoseType pose  = (PoseType)pcd1.GetPose();

    pcd2.SetTimestamp(pcd1.GetTimestamp());
    pcd2.SetCoordinate(pcd1.GetCoordinate());
    pcd2.SetDense(pcd1.IsDense());
    pcd2.SetPose(pose);

    pcd2.resize(pcd1.size());

    for (size_t i = 0U; i < pcd1.size(); ++i)
    {
        CopyPoint(pcd1[i], pcd2[i]);
    }
}

/**
 * @brief Copy point cloud with indices
 *
 * @tparam PointInT
 * @tparam PointOutT
 * @param[in] pcd1 input point cloud
 * @param[in] indices indices of input point cloud
 * @param[out] pcd2 output point cloud
 */
template <typename PointInT, typename PointOutT>
void CopyPointCloud(PointCloudT<PointInT> const& pcd1, std::vector<size_t> const& indices, PointCloudT<PointOutT>& pcd2)
{
    using PoseType = typename PointCloudT<PointOutT>::PoseType;
    PoseType pose  = (PoseType)pcd1.GetPose();
    pcd2.SetTimestamp(pcd1.GetTimestamp());
    pcd2.SetCoordinate(pcd1.GetCoordinate());
    pcd2.SetDense(pcd1.IsDense());
    pcd2.SetPose(pose);

    pcd2.resize(indices.size());

    for (size_t i = 0U; i < indices.size(); ++i)
    {
        CopyPoint(pcd1[indices[i]], pcd2[i]);
    }
}

/**
 * @brief Calculate the boundingbox points of a point cloud
 *
 * @tparam PointT
 * @tparam Dim
 * @tparam Condition
 */
template <typename PointT, int32_t Dim = 3>
struct BBox
{
    void operator()(PointCloudT<PointT> const& cloud, PointT& min_pt, PointT& max_pt);
};

/**
 * @brief Transform point cloud
 *
 * @tparam PointT
 * @tparam T
 * @param[in] input point cloud
 * @param[in] pose transformation
 * @param[out] output point cloud
 */
template <typename PointT, typename T>
void TransformPointCloud(PointCloudT<PointT> const& input, geometry::Pose3T<T> const& pose, PointCloudT<PointT>& output)
{
    internal::TransformFunctor<PointT> functor;

    functor.template operator()<T>(input, pose, output);
}

/**
 * @brief Transform point cloud with indices
 *
 * @tparam PointT
 * @tparam T
 * @param[in] input point cloud
 * @param[in] pose transformation
 * @param[out] output point cloud
 */
template <typename PointT, typename T>
void TransformPointCloud(PointCloudT<PointT> const& input, std::vector<size_t> const& indices,
                         geometry::Pose3T<T> const& pose, PointCloudT<PointT>& output)
{
    internal::TransformFunctor<PointT> functor;

    functor.template operator()<T>(input, indices, pose, output);
}

/**
 * @brief compensate point cloud
 *
 * @tparam PointT
 * @tparam T
 * @param[in] pose transformation
 * @param[in,out] cloud point cloud
 */
template <typename PointT, typename T = float64_t>
void CompensatePointCloud(geometry::Pose3T<T> const& pose, PointCloudT<PointT>& cloud);

/**
 * @brief Compute the normalized 3x3 covariance matrix and the centroid of a given point cloud
 *
 * @tparam PointT
 * @tparam T
 * @param[in] cloud the input point cloud
 * @param[out] covariance_matrix the resultant 3x3 covariance matrix
 * @param[out] mean the centroid of the set of points in the cloud
 * @return size_t number of valid points used to determine the covariance matrix
 */
template <typename PointT, typename T = float64_t>
size_t ComputeMeanAndCovarianceMatrix(PointCloudT<PointT> const& cloud, numerics::Matrix3T<T>& covariance_matrix,
                                      numerics::Vector3T<T>& mean);

/**
 * @brief Compute the normalized 3x3 covariance matrix and the centroid of a given point cloud
 *
 * @tparam PointT
 * @tparam T
 * @param[in] cloud the point cloud
 * @param[in] indices subset of points given by their indices
 * @param[out] covariance_matrix the resultant 3x3 covariance matrix
 * @param[out] mean the centroid of the set of points in the cloud
 * @return size_t number of valid points used to determine the covariance matrix
 */
template <typename PointT, typename T = float64_t>
size_t ComputeMeanAndCovarianceMatrix(PointCloudT<PointT> const& cloud, std::vector<size_t> const& indices,
                                      numerics::Matrix3T<T>& covariance_matrix, numerics::Vector3T<T>& mean);

}  // namespace pointcloud
}  // namespace holo
#endif  // HOLO_3D_COMMON_COMMON_H_
