/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file transformation_estimation_point_to_plane.hpp
 * @brief This header file defines implementation of transformation estimation point to plane
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-01-29
 */

#ifndef HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_POINT_TO_PLANE_HPP_
#define HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_POINT_TO_PLANE_HPP_

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <holo/3d/common/point_traits.h>
#include <holo/3d/registration/transformation_estimation_point_to_plane.h>
#include <holo/numerics/eigen_solver.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
TransformationEstimationPointToPlaneT<PointSourceT, PointTargetT, Scalar>::TransformationEstimationPointToPlaneT()
{
    static_assert(traits::HasNormal<PointTargetT>::value, "PointTargetT does not have field nx, ny and nz!");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
TransformationEstimationPointToPlaneT<PointSourceT, PointTargetT, Scalar>::~TransformationEstimationPointToPlaneT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
void TransformationEstimationPointToPlaneT<PointSourceT, PointTargetT, Scalar>::ComputeTransformation(
    PointCloudSource const& cloud_src, PointCloudTarget const& cloud_tgt, CorrespondenceVector const& corr_vector,
    Pose3Type& tTs) const
{
    if (corr_vector.empty())
    {
        tTs = Pose3Type::Identity();
        return;
    }

    uint32_t num_corrs = corr_vector.size();

    MatrixXType ATA(6u, 6u);
    VectorXType ATb(6u);

    ATA.SetZero();
    ATb.SetZero();

    for (uint32_t i = 0u; i < num_corrs; ++i)
    {
        auto const& pt_src = cloud_src(corr_vector[i].first);
        auto const& pt_tgt = cloud_tgt(corr_vector[i].second);

        Scalar const sx = pt_src.GetX();
        Scalar const sy = pt_src.GetY();
        Scalar const sz = pt_src.GetZ();
        Scalar const dx = pt_tgt.GetX();
        Scalar const dy = pt_tgt.GetY();
        Scalar const dz = pt_tgt.GetZ();
        Scalar const nx = pt_tgt.GetNormalX();
        Scalar const ny = pt_tgt.GetNormalY();
        Scalar const nz = pt_tgt.GetNormalZ();

        Scalar a = nz * sy - ny * sz;
        Scalar b = nx * sz - nz * sx;
        Scalar c = ny * sx - nx * sy;

        //    0  1  2  3  4  5
        //    6  7  8  9 10 11
        //   12 13 14 15 16 17
        //   18 19 20 21 22 23
        //   24 25 26 27 28 29
        //   30 31 32 33 34 35

        ATA(0u) += a * a;
        ATA(1u) += a * b;
        ATA(2u) += a * c;
        ATA(3u) += a * nx;
        ATA(4u) += a * ny;
        ATA(5u) += a * nz;
        ATA(7u) += b * b;
        ATA(8u) += b * c;
        ATA(9u) += b * nx;
        ATA(10u) += b * ny;
        ATA(11u) += b * nz;
        ATA(14u) += c * c;
        ATA(15u) += c * nx;
        ATA(16u) += c * ny;
        ATA(17u) += c * nz;
        ATA(21u) += nx * nx;
        ATA(22u) += nx * ny;
        ATA(23u) += nx * nz;
        ATA(28u) += ny * ny;
        ATA(29u) += ny * nz;
        ATA(35u) += nz * nz;

        Scalar d = nx * dx + ny * dy + nz * dz - nx * sx - ny * sy - nz * sz;
        ATb(0u) += a * d;
        ATb(1u) += b * d;
        ATb(2u) += c * d;
        ATb(3u) += nx * d;
        ATb(4u) += ny * d;
        ATb(5u) += nz * d;
    }

    ATA(6u)  = ATA(1u);
    ATA(12u) = ATA(2u);
    ATA(13u) = ATA(8u);
    ATA(18u) = ATA(3u);
    ATA(19u) = ATA(9u);
    ATA(20u) = ATA(15u);
    ATA(24u) = ATA(4u);
    ATA(25u) = ATA(10u);
    ATA(26u) = ATA(16u);
    ATA(27u) = ATA(22u);
    ATA(30u) = ATA(5u);
    ATA(31u) = ATA(11u);
    ATA(32u) = ATA(17u);
    ATA(33u) = ATA(23u);
    ATA(34u) = ATA(29u);

    // solve ATA*x = ATb;
    VectorXType x = eigen_solver::SolveLinearSystem(ATA, ATb, eigen_solver::Type::LDLT);

    tTs = Pose3Type(Rot3Type::RzRyRx(x(0u), x(1u), x(2u)), Point3Type(x(3u), x(4u), x(5u)));

    return;
}

}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_POINT_TO_PLANE_HPP_
