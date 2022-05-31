/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common.hpp
 * @brief Implementation of common functions
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-10-29
 */

#ifndef HOLO_3D_COMMON_COMMON_HPP_
#define HOLO_3D_COMMON_COMMON_HPP_

#include <holo/3d/common/common.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
struct BBox<PointT, 3>
{
    void operator()(PointCloudT<PointT> const& cloud, PointT& min_pt, PointT& max_pt)
    {
        static_assert(PointT::SIZE_VALUE >= 3, "PointT SIZE_VALUE must be greater than 3");

        using ScalarType = typename PointT::ScalarType;

        min_pt[0] = std::numeric_limits<ScalarType>::max();
        min_pt[1] = std::numeric_limits<ScalarType>::max();
        min_pt[2] = std::numeric_limits<ScalarType>::max();

        max_pt[0] = std::numeric_limits<ScalarType>::min();
        max_pt[1] = std::numeric_limits<ScalarType>::min();
        max_pt[2] = std::numeric_limits<ScalarType>::min();

        for (size_t i = 0; i < cloud.size(); ++i)
        {
            PointT const& pt = cloud[i];
            ScalarType    x  = pt.GetX();
            ScalarType    y  = pt.GetY();
            ScalarType    z  = pt.GetZ();

            if (x < min_pt[0])
            {
                min_pt[0] = x;
            }

            if (y < min_pt[1])
            {
                min_pt[1] = y;
            }

            if (z < min_pt[2])
            {
                min_pt[2] = z;
            }

            if (x > max_pt[0])
            {
                max_pt[0] = x;
            }

            if (y > max_pt[1])
            {
                max_pt[1] = y;
            }

            if (z > max_pt[2])
            {
                max_pt[2] = z;
            }
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
struct BBox<PointT, 2>
{
    void operator()(PointCloudT<PointT> const& cloud, PointT& min_pt, PointT& max_pt)
    {
        static_assert(PointT::SIZE_VALUE >= 2, "PointT SIZE_VALUE must be greater than 2");

        using ScalarType = typename PointT::ScalarType;

        min_pt[0] = std::numeric_limits<ScalarType>::max();
        min_pt[1] = std::numeric_limits<ScalarType>::max();

        max_pt[0] = std::numeric_limits<ScalarType>::min();
        max_pt[1] = std::numeric_limits<ScalarType>::min();

        for (size_t i = 0; i < cloud.size(); ++i)
        {
            PointT const& pt = cloud[i];
            ScalarType    x  = pt[0];
            ScalarType    y  = pt[1];

            if (x < min_pt[0])
            {
                min_pt[0] = x;
            }

            if (y < min_pt[1])
            {
                min_pt[1] = y;
            }

            if (x > max_pt[0])
            {
                max_pt[0] = x;
            }

            if (y > max_pt[1])
            {
                max_pt[1] = y;
            }
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT, typename T>
void CompensatePointCloud(geometry::Pose3T<T> const& pose, PointCloudT<PointT>& cloud)
{
    size_t num = cloud.size();

    if (num <= 1 || pose == Pose3T<T>::Identity())
    {
        return;
    }

    using Pose3Type  = geometry::Pose3T<T>;
    using Point3Type = geometry::Point3T<T>;

    // slerp for quaternion
    float64_t t0 = cloud.at(0).GetTimestamp().ToSec();
    float64_t t1 = cloud.at(num - 1).GetTimestamp().ToSec();

    // compensate each point using linear intepolation
    for (size_t i = 0; i < num; ++i)
    {
        PointT&   pt    = cloud[i];
        float64_t t     = pt.GetTimestamp().ToSec();
        T         ratio = (t - t0) / (t1 - t0);
        assert(ratio >= 0 && ratio <= 1);

        Pose3Type  pose_t = Pose3Type::Interpolate(Pose3Type::Identity(), pose, ratio);
        Point3Type pt_t   = pose_t.TransformFrom(Point3Type(pt[0], pt[1], pt[2]));

        pt.Set(pt_t[0], pt_t[1], pt_t[2]);
        pt.SetTimestamp(common::Timestamp(t0));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT, typename T = float64_t>
size_t ComputeMeanAndCovarianceMatrix(PointCloudT<PointT> const& cloud, numerics::Matrix3T<T>& covariance_matrix,
                                      numerics::Vector3T<T>& mean)
{
    size_t num_points = cloud.size();

    if (num_points <= 0U)
    {
        covariance_matrix.SetIdentity();
        mean.SetZero();
        return 0;
    }

    numerics::MatrixT<T, 9, 1> accu;
    accu.SetZero();

    for (size_t i = 0U; i < num_points; ++i)
    {
        PointT const& pt = cloud[i];
        accu(0) += pt[0] * pt[0];
        accu(1) += pt[0] * pt[1];
        accu(2) += pt[0] * pt[2];
        accu(3) += pt[1] * pt[1];
        accu(4) += pt[1] * pt[2];
        accu(5) += pt[2] * pt[2];
        accu(6) += pt[0];
        accu(7) += pt[1];
        accu(8) += pt[2];
    }

    accu /= static_cast<T>(num_points);

    mean(0) = accu(6);
    mean(1) = accu(7);
    mean(2) = accu(8);

    covariance_matrix(0) = accu(0) - accu(6) * accu(6);
    covariance_matrix(1) = accu(1) - accu(6) * accu(7);
    covariance_matrix(2) = accu(2) - accu(6) * accu(8);
    covariance_matrix(4) = accu(3) - accu(7) * accu(7);
    covariance_matrix(5) = accu(4) - accu(7) * accu(8);
    covariance_matrix(8) = accu(5) - accu(8) * accu(8);
    covariance_matrix(3) = covariance_matrix(1);
    covariance_matrix(6) = covariance_matrix(2);
    covariance_matrix(7) = covariance_matrix(5);

    return num_points;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT, typename T = float64_t>
size_t ComputeMeanAndCovarianceMatrix(PointCloudT<PointT> const& cloud, std::vector<size_t> const& indices,
                                      numerics::Matrix3T<T>& covariance_matrix, numerics::Vector3T<T>& mean)
{
    size_t num_points = indices.size();

    if (num_points <= 0U)
    {
        covariance_matrix.SetIdentity();
        mean.SetZero();
        return 0;
    }

    numerics::MatrixT<T, 9, 1> accu;
    accu.SetZero();

    for (auto const& i : indices)
    {
        PointT const& pt = cloud[i];
        accu(0) += pt[0] * pt[0];
        accu(1) += pt[0] * pt[1];
        accu(2) += pt[0] * pt[2];
        accu(3) += pt[1] * pt[1];
        accu(4) += pt[1] * pt[2];
        accu(5) += pt[2] * pt[2];
        accu(6) += pt[0];
        accu(7) += pt[1];
        accu(8) += pt[2];
    }

    accu /= static_cast<T>(num_points);

    mean(0) = accu(6);
    mean(1) = accu(7);
    mean(2) = accu(8);

    covariance_matrix(0) = accu(0) - accu(6) * accu(6);
    covariance_matrix(1) = accu(1) - accu(6) * accu(7);
    covariance_matrix(2) = accu(2) - accu(6) * accu(8);
    covariance_matrix(4) = accu(3) - accu(7) * accu(7);
    covariance_matrix(5) = accu(4) - accu(7) * accu(8);
    covariance_matrix(8) = accu(5) - accu(8) * accu(8);
    covariance_matrix(3) = covariance_matrix(1);
    covariance_matrix(6) = covariance_matrix(2);
    covariance_matrix(7) = covariance_matrix(5);

    return num_points;
}

}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_COMMON_COMMON_HPP_
