/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_to_plane_icp.hpp
 * @brief This header file defines implementation of point to plane icp
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-01-31
 */

#ifndef HOLO_3D_REGISTRATION_POINT_TO_PLANE_ICP_HPP_
#define HOLO_3D_REGISTRAITON_POINT_TO_PLANE_ICP_HPP_

#include <holo/3d/registration/transformation_estimation_point_to_plane.h>
#include <holo/3d/registration/transformation_estimation_point_to_plane_scale.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
PointToPlaneICPT<PointSourceT, PointTargetT, Scalar>::PointToPlaneICPT(bool_t scale_cloud) : Base()
{
    static_assert(traits::HasNormal<PointSourceT>::value, "PointSourceT does not have field nx, ny and nz!");
    static_assert(traits::HasNormal<PointTargetT>::value, "PointTargetT does not have field nx, ny and nz!");

    if (!scale_cloud)
    {
        transformation_estimation_.reset(
            new TransformationEstimationPointToPlaneT<PointSourceT, PointTargetT, Scalar>());
    }
    else
    {
        transformation_estimation_.reset(
            new TransformationEstimationPointToPlaneScaleT<PointSourceT, PointTargetT, Scalar>());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
PointToPlaneICPT<PointSourceT, PointTargetT, Scalar>::~PointToPlaneICPT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
void PointToPlaneICPT<PointSourceT, PointTargetT, Scalar>::SetMaxAngle(Scalar max_angle)
{
    max_angle_ = max_angle;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
Scalar PointToPlaneICPT<PointSourceT, PointTargetT, Scalar>::GetMaxAngle() const noexcept
{
    return max_angle_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t PointToPlaneICPT<PointSourceT, PointTargetT, Scalar>::Compute(const Pose3Type& guess)
{
    if (!preCompute())
    {
        LOG(ERROR) << "Precompute failed!";
        return false;
    }

    // initialize final transformation to the guessed one
    final_transformation_ = guess;
    transformation_       = Pose3Type::Identity();
    uint32_t iteration    = 0;
    Scalar   max_dist_sqr = max_correspondence_distance_ * max_correspondence_distance_;
    Scalar   current_mse  = 0.0;
    Scalar   previous_mse = std::numeric_limits<Scalar>::max();
    Scalar   delta_mse    = std::numeric_limits<Scalar>::max();

    PointCloudSourcePtr src_transformed(new PointCloudSource(source_->size()));
    TransformPointCloud(*source_, guess, *src_transformed);

    // repeat until convergence
    do
    {
        previous_transformation_ = transformation_;

        // compute correspondences
        Scalar error2 = computeCorrespondences(*src_transformed, *target_, max_dist_sqr);

        uint32_t num_valid_corrs = correspondences_.size();

        if (num_valid_corrs < min_number_correspondences_)
        {
            converged_ = false;
            LOG(ERROR) << "not enough correspondences!";
            break;
        }

        previous_mse = current_mse;
        current_mse  = error2 / static_cast<Scalar>(num_valid_corrs);
        delta_mse    = std::fabs(previous_mse - current_mse);

        // check euclidean epsilon
        if (delta_mse < euclidean_fitness_epsilon_)
        {
            converged_ = true;
            LOG_IF(INFO, verbose_) << "converged after: " << iteration
                                   << " iterations. Reason: fitness epsilon: " << current_mse
                                   << " corr: " << num_valid_corrs;
            break;
        }

        // compute transformation
        transformation_estimation_->ComputeTransformation(*src_transformed, *target_, correspondences_,
                                                          transformation_);

        // transform the data
        TransformPointCloud(*src_transformed, transformation_, *src_transformed);

        // update the final transformation
        final_transformation_ = transformation_ * final_transformation_;

        ++iteration;

        // check rotation and translation epsilon
        Matrix4Type diff             = transformation_.ToMatrix();
        Scalar      rotation_epsilon = diff.GetBlock(0, 0, 3, 3).CwiseAbs().MaxCoeff();
        Scalar      translation_sqr  = diff.GetBlock(0, 3, 3, 1).GetSquaredNorm();

        if (rotation_epsilon < rotation_epsilon_ && translation_sqr < translation_epsilon_)
        {
            converged_ = true;
            LOG_IF(INFO, verbose_) << "converged after: " << iteration
                                   << " iterations. Reason: fitness epsilon: " << current_mse
                                   << " corr: " << num_valid_corrs;
            break;
        }

    } while (iteration < max_iterations_ && !converged_);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
Scalar PointToPlaneICPT<PointSourceT, PointTargetT, Scalar>::computeCorrespondences(PointCloudSource const& cloud_src,
                                                                                    PointCloudTarget const& cloud_tgt,
                                                                                    Scalar max_dist_square)
{
    Scalar dot_min = std::cos(geometry::Radian(max_angle_));

    Scalar error2 = 0.0;
    // clear correspondences
    correspondences_.clear();
    correspondences_.reserve(indices_source_.size());

    std::vector<size_t> nn_indices(1u);
    std::vector<Scalar> nn_dists_square(1u);

    // compute correspondences
    for (auto const& idx : indices_source_)
    {
        PointSourceT const& pt_src = cloud_src[idx];

        if (tree_target_->KnnSearch(pt_src, 1, nn_indices, nn_dists_square) > 0)
        {
            if (nn_dists_square[0] < max_dist_square)
            {
                PointTargetT const& pt_tgt = cloud_tgt[nn_indices[0]];

                if (pt_tgt.GetNormal().Dot(pt_src.GetNormal()) > dot_min)
                {
                    correspondences_.emplace_back(std::make_pair(idx, nn_indices[0]));
                    error2 += nn_dists_square[0];
                }
            }
        }
    }

    return error2;
}

}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_REGISTRAITON_POINT_TO_PLANE_ICP_HPP_
