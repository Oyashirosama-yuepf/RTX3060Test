/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file transformation_estimation_svd.hpp
 * @brief This header file defines implementation of transformation estimation svd
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-01-29
 */

#ifndef HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_SVD_HPP_
#define HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_SVD_HPP_

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <holo/3d/common/point_traits.h>
#include <holo/3d/registration/transformation_estimation_svd.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
TransformationEstimationSVDT<PointSourceT, PointTargetT, Scalar>::TransformationEstimationSVDT(bool_t with_scaling)
  : with_scaling_(with_scaling)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
TransformationEstimationSVDT<PointSourceT, PointTargetT, Scalar>::~TransformationEstimationSVDT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
void TransformationEstimationSVDT<PointSourceT, PointTargetT, Scalar>::ComputeTransformation(
    PointCloudSource const& cloud_src, PointCloudTarget const& cloud_tgt, CorrespondenceVector const& corr_vector,
    Pose3Type& tTs) const
{
    if (corr_vector.empty())
    {
        tTs = Pose3Type::Identity();
        return;
    }

    uint32_t num_corrs = corr_vector.size();

    using EigenMatrixX = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    using EigenMatrix4 = Eigen::Matrix<Scalar, 4u, 4u>;
    using EigenVector3 = Eigen::Matrix<Scalar, 3u, 1u>;

    EigenMatrixX src_mat(3u, num_corrs);
    EigenMatrixX tgt_mat(3u, num_corrs);

    for (uint32_t i = 0u; i < num_corrs; ++i)
    {
        src_mat.block(0u, i, 3u, 1u) = cloud_src(corr_vector[i].first).template As<EigenVector3>();
        tgt_mat.block(0u, i, 3u, 1u) = cloud_tgt(corr_vector[i].second).template As<EigenVector3>();
    }

    // @TODO implement holo matrix umeyama
    // the algorithm is described in umeyama:Least-Squares Estimation of Transformation Parameters Between 2 Point
    // Patterns(1991)
    EigenMatrix4 transformation = Eigen::umeyama(src_mat, tgt_mat, with_scaling_);

    Matrix4Type mat4_holo;
    std::memcpy(mat4_holo.GetData(), transformation.data(), sizeof(Scalar) * 16u);
    tTs = Pose3Type(mat4_holo);

    return;
}

}  // namespace pointcloud
}  // namespace holo

#endif
