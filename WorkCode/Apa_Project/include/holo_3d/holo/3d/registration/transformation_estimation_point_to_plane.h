/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file transformation_estimation_point_to_plane.h
 * @brief This header file defines transformation estimation point to plane class
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-01-29
 */

#ifndef HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_POINT_TO_PLANE_H_
#define HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_POINT_TO_PLANE_H_

#include <holo/3d/registration/transformation_estimation.h>

namespace holo
{
namespace pointcloud
{
template <typename PointSourceT, typename PointTargetT, typename Scalar = float64_t>
class TransformationEstimationPointToPlaneT : public TransformationEstimationBaseT<PointSourceT, PointTargetT, Scalar>
{
public:
    using Ptr      = std::shared_ptr<TransformationEstimationPointToPlaneT<PointSourceT, PointTargetT, Scalar>>;
    using ConstPtr = std::shared_ptr<const TransformationEstimationPointToPlaneT<PointSourceT, PointTargetT, Scalar>>;

    using Base = TransformationEstimationBaseT<PointSourceT, PointTargetT, Scalar>;
    using typename Base::CorrespondenceVector;
    using typename Base::Matrix4Type;
    using typename Base::Matrix6Type;
    using typename Base::MatrixXType;
    using typename Base::Point3Type;
    using typename Base::PointCloudSource;
    using typename Base::PointCloudTarget;
    using typename Base::Pose3Type;
    using typename Base::Rot3Type;
    using typename Base::Vector3Type;
    using typename Base::Vector6Type;
    using typename Base::VectorXType;

    /**
     * @brief Construct a new Transformation Estimation Point2Plane object
     *
     */
    TransformationEstimationPointToPlaneT();

    /**
     * @brief Destroy the Transformation Estimation Point2Plane object
     *
     */
    virtual ~TransformationEstimationPointToPlaneT();

    /**
     * @brief transformation computation point2plane method with correspondences
     *
     * @param[in] cloud_src source point cloud
     * @param[in] cloud_tgt target point cloud
     * @param[in] corr_vector correspondence vector
     * @param[out] tTs pose transformation
     */
    void ComputeTransformation(PointCloudSource const& cloud_src, PointCloudTarget const& cloud_tgt,
                               CorrespondenceVector const& corr_vector, Pose3Type& tTs) const override;
};
}  // namespace pointcloud
}  // namespace holo

#endif
