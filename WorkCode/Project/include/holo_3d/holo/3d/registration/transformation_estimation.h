/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file transformation_estimation.h
 * @brief This header file defines transformation estimation base class
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-01-29
 */

#ifndef HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_H_
#define HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_H_

#include <holo/3d/common/point_traits.h>
#include <holo/3d/common/point_types.h>
#include <holo/3d/common/point_cloud.h>
#include <holo/geometry/pose3.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief Transformation estimation base class
 *
 * @tparam PointSourceT
 * @tparam PointTargetT
 * @tparam Scalar
 */
template <typename PointSourceT, typename PointTargetT, typename Scalar = float64_t>
class TransformationEstimationBaseT
{
public:
    using Ptr      = std::shared_ptr<TransformationEstimationBaseT<PointSourceT, PointTargetT, Scalar> >;
    using ConstPtr = std::shared_ptr<const TransformationEstimationBaseT<PointSourceT, PointTargetT, Scalar> >;

    using PointCloudSource = PointCloudT<PointSourceT>;
    using PointCloudTarget = PointCloudT<PointTargetT>;
    using Pose3Type        = holo::geometry::Pose3T<Scalar>;
    using Point3Type       = holo::geometry::Point3T<Scalar>;
    using Rot3Type         = holo::geometry::Rot3T<Scalar>;
    using Vector3Type      = holo::numerics::Vector3T<Scalar>;
    using Vector6Type      = holo::numerics::Vector6T<Scalar>;
    using Matrix4Type      = holo::numerics::Matrix4T<Scalar>;
    using Matrix6Type      = holo::numerics::Matrix6T<Scalar>;
    using MatrixXType      = numerics::MatrixT<Scalar, -1, -1>;
    using VectorXType      = numerics::VectorT<Scalar, -1>;

    using Correspondence       = std::pair<int32_t, int32_t>;
    using CorrespondenceVector = std::vector<Correspondence>;

    /**
     * @brief Construct a new Transformation Estimation object
     *
     */
    TransformationEstimationBaseT()
    {
        static_assert(std::is_floating_point<typename PointSourceT::ScalarType>::value,
                      "PointSourceT::Scalar is not a floating-point type!");
        static_assert(std::is_floating_point<typename PointTargetT::ScalarType>::value,
                      "PointTargetT::Scalar is not a floating-point type!");
    }

    /**
     * @brief Destroy the Transformation Estimation object
     *
     */
    virtual ~TransformationEstimationBaseT()
    {
    }

    /**
     * @brief Abstract transformation computation method with correspondences
     *
     * @param[in] cloud_src source point cloud
     * @param[in] cloud_tgt target point cloud
     * @param[in] corr_vector correspondence vector
     * @param[out] tTs transformation from source to target
     */
    virtual void ComputeTransformation(PointCloudSource const& cloud_src, PointCloudTarget const& cloud_tgt,
                                       CorrespondenceVector const& corr_vector, Pose3Type& tTs) const = 0;
};
}  // namespace pointcloud
}  // namespace holo

#endif
