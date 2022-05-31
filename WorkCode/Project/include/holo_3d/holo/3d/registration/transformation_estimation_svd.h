/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file transformation_estimation_svd.h
 * @brief This header file defines transformation estimation svd class
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-01-29
 */

#ifndef HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_SVD_H_
#define HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_SVD_H_

#include <holo/3d/registration/transformation_estimation.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief Transformation estimation svd class
 *
 * @tparam PointSourceT
 * @tparam PointTargetT
 * @tparam Scalar
 */
template <typename PointSourceT, typename PointTargetT, typename Scalar = float64_t>
class TransformationEstimationSVDT : public TransformationEstimationBaseT<PointSourceT, PointTargetT, Scalar>
{
public:
    using Ptr      = std::shared_ptr<TransformationEstimationSVDT<PointSourceT, PointTargetT, Scalar>>;
    using ConstPtr = std::shared_ptr<const TransformationEstimationSVDT<PointSourceT, PointTargetT, Scalar>>;

    using Base = TransformationEstimationBaseT<PointSourceT, PointTargetT, Scalar>;
    using typename Base::CorrespondenceVector;
    using typename Base::Matrix4Type;
    using typename Base::Point3Type;
    using typename Base::PointCloudSource;
    using typename Base::PointCloudTarget;
    using typename Base::Pose3Type;
    using typename Base::Vector3Type;

    /**
     * @brief Construct a new Transformation Estimation SVD object
     *
     * @param with_scaling compute scale or not
     */
    TransformationEstimationSVDT(bool_t with_scaling = false);

    /**
     * @brief Destroy the Transformation Estimation SVD object
     *
     */
    virtual ~TransformationEstimationSVDT();

    /**
     * @brief transformation computation svd method with correspondences
     *
     * @param[in] cloud_src source point cloud
     * @param[in] cloud_tgt target point cloud
     * @param[in] corr_vector correspondence vector
     * @param[out] tTs transformation from source to target
     */
    void ComputeTransformation(PointCloudSource const& cloud_src, PointCloudTarget const& cloud_tgt,
                               CorrespondenceVector const& corr_vector, Pose3Type& tTs) const override;

private:
    bool_t with_scaling_;  ///< true if scale needs to be computed in transformation
};
}  // namespace pointcloud
}  // namespace holo

#include "impl/transformation_estimation_svd.hpp"

#endif  // HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_SVD_H_
