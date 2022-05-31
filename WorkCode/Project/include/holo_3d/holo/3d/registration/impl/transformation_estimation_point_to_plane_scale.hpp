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
#include <holo/3d/registration/transformation_estimation_point_to_plane_scale.h>
#include <holo/numerics/eigen_solver.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
TransformationEstimationPointToPlaneScaleT<PointSourceT, PointTargetT,
                                           Scalar>::TransformationEstimationPointToPlaneScaleT()
{
    static_assert(traits::HasNormal<PointTargetT>::value, "PointTargetT does not have field nx, ny and nz!");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
TransformationEstimationPointToPlaneScaleT<PointSourceT, PointTargetT,
                                           Scalar>::~TransformationEstimationPointToPlaneScaleT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
void TransformationEstimationPointToPlaneScaleT<PointSourceT, PointTargetT, Scalar>::ComputeTransformation(
    PointCloudSource const& cloud_src, PointCloudTarget const& cloud_tgt, CorrespondenceVector const& corr_vector,
    Pose3Type& tTs) const
{
    if (corr_vector.empty())
    {
        tTs = Pose3Type::Identity();
        return;
    }

    using EigenVector3 = Eigen::Matrix<Scalar, 3, 1>;
    using EigenVector6 = Eigen::Matrix<Scalar, 6, 1>;
    using EigenMatrix3 = Eigen::Matrix<Scalar, 3, 3>;
    using EigenMatrix4 = Eigen::Matrix<Scalar, 4, 4>;
    using EigenMatrix6 = Eigen::Matrix<Scalar, 6, 6>;
    using Vec3X        = std::vector<EigenVector3, Eigen::aligned_allocator<EigenVector3>>;

    // The algorithm is described in Low: Linear Least-Squares Optimization for Point-to-Plane ICP Surface
    // Registration (2004) in the discussion: "To improve the numerical stability of the computation, it is
    // important to use a unit of distance that is comparable in magnitude with the rotation angles. The simplest
    // way is to rescale and move the two input surfaces so that they are bounded within a unit sphere or cube
    // centered at the origin."
    // - Gelfand et al.: Geometrically Stable Sampling for the ICP Algorithm (2003), in sec 3.1: "As is common with
    // PCA methods, we will shift the center of mass of the points	to the origin." ... "Therefore, after shifting
    // the center of mass, we will scale the point set so that the average distance of points	from the origin
    // is 1."

    EigenVector3 center_src, center_tgt;
    center_src.setZero();
    center_tgt.setZero();

    uint32_t num_corrs = corr_vector.size();

    // compute centroid
    for (auto const& corr : corr_vector)
    {
        center_src += cloud_src[corr.first].template As<EigenVector3>();
        center_tgt += cloud_tgt[corr.second].template As<EigenVector3>();
    }

    center_src /= num_corrs;
    center_tgt /= num_corrs;

    Vec3X xyz_src(num_corrs);  ///< source demean xyz vector
    Vec3X xyz_tgt(num_corrs);  ///< taregt demean xyz vector
    Vec3X nor_tgt(num_corrs);  ///< target normal vector

    Scalar accum = 0.0;

    // substract the centroid and calculate the scaling factor
    for (uint32_t i = 0u; i < num_corrs; ++i)
    {
        xyz_src[i] = cloud_src[corr_vector[i].first].template As<EigenVector3>() - center_src;
        xyz_tgt[i] = cloud_tgt[corr_vector[i].second].template As<EigenVector3>() - center_tgt;
        nor_tgt[i] = cloud_tgt[corr_vector[i].second].template GetNormal<EigenVector3>();

        accum += xyz_src[i].norm() + xyz_tgt[i].norm();
    }

    // inverse scale (do a multiplication instead of division)
    const Scalar factor         = 2.0 * static_cast<Scalar>(num_corrs) / accum;
    const Scalar factor_squared = factor * factor;

    EigenMatrix6 ATA;
    EigenVector6 ATb;
    ATA.setZero();
    ATb.setZero();

    // A = [a_i1, a_i2, a_i3, n_ix, n_iy, n_iz]  eq(10)
    //   = [C^t, N^t]
    // b = [n_ix*d_ix+n_iy*d_iy+n_iz*d_iz-n_ix*s_ix-n_iy*s_iy-n_iz*s_iz]
    //   = [(d_i-s_i).dot(n_i)] eq(8)
    // so ATA become
    // [CC^t CN^t]
    // [NC^t NN^t]

    EigenMatrix3 C_tl    = EigenMatrix3::Zero();
    EigenMatrix3 C_tr_bl = EigenMatrix3::Zero();
    EigenMatrix3 C_br    = EigenMatrix3::Zero();

    EigenVector3 b_t = EigenVector3::Zero();
    EigenVector3 b_b = EigenVector3::Zero();

    EigenVector3 cross;
    Scalar       dot;

    for (size_t i = 0u; i < num_corrs; ++i)
    {
        cross = xyz_src[i].cross(nor_tgt[i]);

        C_tl += cross * cross.transpose();
        C_tr_bl += cross * nor_tgt[i].transpose();
        C_br += nor_tgt[i] * nor_tgt[i].transpose();

        dot = (xyz_tgt[i] - xyz_src[i]).dot(nor_tgt[i]);

        b_t += cross * dot;
        b_b += nor_tgt[i] * dot;
    }

    // Scale with the factor and copy the 3x3 submatrixes into ATA and b
    C_tl *= factor_squared;
    C_tr_bl *= factor;

    ATA << C_tl, C_tr_bl, C_tr_bl.transpose(), C_br;

    ATb << b_t(0) * factor_squared, b_t(1) * factor_squared, b_t(2) * factor_squared, b_b(0) * factor, b_b(1) * factor,
        b_b(2) * factor;

    // Solve ATA * x = ATb
    // x = [alpha; beta; gamma; trans_x; trans_y; trans_z]
    EigenVector6 x = ATA.ldlt().solve(ATb);

    // The calculated transformation in the scaled coordinate system
    const Scalar sa = std::sin(x(0)), ca = std::cos(x(0)), sb = std::sin(x(1)), cb = std::cos(x(1)),
                 sg = std::sin(x(2)), cg = std::cos(x(2)), tx = x(3), ty = x(4), tz = x(5);

    // rpy to rotation matrix
    EigenMatrix4 TT;
    TT << cg * cb, -sg * ca + cg * sb * sa, sg * sa + cg * sb * ca, tx, sg * cb, cg * ca + sg * sb * sa,
        -cg * sa + sg * sb * ca, ty, -sb, cb * sa, cb * ca, tz, 0.0, 0.0, 0.0, 1.0;

    // Transformation matrix into the local coordinate systems of model/data
    // let d_i,s_i be origin point, d_si, s_si is scaled demean source point
    // d_si = T_t * d_i; s_si = T_s * s_i
    // d_si = TT * s_si; so we get d_i = T_t^{-1} * TT * T_s * s_i
    EigenMatrix4 T_s, T_t;

    T_s << factor, 0.0, 0.0, -center_src.x() * factor, 0.0, factor, 0.0, -center_src.y() * factor, 0.0, 0.0, factor,
        -center_src.z() * factor, 0.0, 0.0, 0.0, 1.0;

    T_t << factor, 0.0, 0.0, -center_tgt.x() * factor, 0.0, factor, 0.0, -center_tgt.y() * factor, 0.0, 0.0, factor,
        -center_tgt.z() * factor, 0.0, 0.0, 0.0, 1.0;

    EigenMatrix4 T_delta = T_t.inverse() * TT * T_s;

    Matrix4Type holo_mat;
    std::memcpy(holo_mat.GetData(), T_delta.data(), sizeof(Scalar) * 16u);

    tTs = Pose3Type(holo_mat);
}

}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_REGISTRATION_TRANSFORMATION_ESTIMATION_POINT_TO_PLANE_HPP_
