/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point2point_icp.hpp
 * @brief This header file defines implementation of gicp
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-05-26
 */

#ifndef HOLO_3D_REGISTRATION_GICP_HPP_
#define HOLO_3D_REGISTRAITON_GICP_HPP_

#include <holo/3d/registration/transformation_estimation_svd.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
GICPT<PointSourceT, PointTargetT, Scalar>::GICPT() : Base()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
GICPT<PointSourceT, PointTargetT, Scalar>::~GICPT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t GICPT<PointSourceT, PointTargetT, Scalar>::preCompute()
{
    if (!Base::preCompute())
    {
        LOG(ERROR) << "base pre compute failed!";
        return false;
    }

    // init the source tree if it's not set
    if (!tree_source_.get())
    {
        tree_source_.reset(new KdTreeSource);
        tree_source_->SetInputPointCloud(source_);
    }
    else if (tree_source_->GetInputPointCloud() != source_)
    {
        tree_source_->SetInputPointCloud(source_);
    }

    if (source_->size() < knn_ || target_->size() < knn_)
    {
        LOG(ERROR) << "point cloud size is less than k: " << knn_;
        return false;
    }

    if (covariances_source_.size() != source_->size())
    {
        computeCovariance(source_, *tree_source_, covariances_source_);
    }

    if (covariances_target_.size() != target_->size())
    {
        computeCovariance(target_, *tree_target_, covariances_target_);
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
bool_t GICPT<PointSourceT, PointTargetT, Scalar>::Compute(const Pose3Type& guess)
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

    std::vector<size_t> nn_indices(1u);
    std::vector<Scalar> nn_dists_square(1u);

    PointCloudSourcePtr src_transformed(new PointCloudSource(source_->size()));
    TransformPointCloud(*source_, guess, *src_transformed);

    Matrix6Type H;
    Vector6Type b;

    // repeat until convergence
    do
    {
        previous_transformation_ = final_transformation_;

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

        H.SetZero();
        b.SetZero();
        size_t num_corrs = correspondences_.size();
        mahalanobis_.resize(num_corrs);

        Matrix3Type R = previous_transformation_.GetRotation().ToMatrix();

        for (size_t i = 0; i < num_corrs; ++i)
        {
            auto const& corr = correspondences_[i];

            Vector3Type const  transed_mean_A = src_transformed->at(corr.first).template As<Vector3Type>();
            Matrix3Type const& cov_A          = covariances_source_[corr.first];
            Vector3Type const  mean_B         = target_->at(corr.second).template As<Vector3Type>();
            Matrix3Type const& cov_B          = covariances_target_[corr.second];

            // eq(2) in  https://www.robots.ox.ac.uk/~avsegal/resources/papers/Generalized_ICP.pdf
            Matrix3Type RCR = cov_B + R * cov_A * R.Transpose();
            mahalanobis_[i] = RCR.Inverse();

            Vector3Type const error = mean_B - transed_mean_A;

            Matrix36Type J;
            J.SetBlock(0, 0, transed_mean_A.ToSkewSymmetric());
            J.SetBlock(0, 3, -Matrix3Type::Identity());

            H += J.Transpose() * mahalanobis_[i] * J;
            b += J.Transpose() * mahalanobis_[i] * error;
        }

        EigenMatrix6 H_e;
        memcpy(H_e.data(), H.GetData(), sizeof(Scalar) * 36u);
        EigenVector6 b_e;
        memcpy(b_e.data(), b.GetData(), sizeof(Scalar) * 6u);

        EigenVector6 x = H_e.ldlt().solve(-b_e);
        Vector6Type  delta;
        memcpy(delta.GetData(), x.data(), sizeof(Scalar) * 6u);
        transformation_ = Pose3Type::Expmap(delta);

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
Scalar GICPT<PointSourceT, PointTargetT, Scalar>::computeCorrespondences(PointCloudSource const& cloud_src,
                                                                         PointCloudTarget const& cloud_tgt,
                                                                         Scalar                  max_dist_square)
{
    (void)cloud_tgt;

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
                correspondences_.emplace_back(std::make_pair(idx, nn_indices[0]));
                error2 += nn_dists_square[0];
            }
        }
    }

    return error2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointSourceT, typename PointTargetT, typename Scalar>
template <typename PointT>
bool_t GICPT<PointSourceT, PointTargetT, Scalar>::computeCovariance(std::shared_ptr<PointCloudT<PointT> > const& cloud,
                                                                    KdTreeT<PointT, Scalar>&                     kdtree,
                                                                    std::vector<Matrix3Type>& covariances)
{
    covariances.resize(cloud->size());

    std::vector<size_t> nn_indices(knn_);
    std::vector<Scalar> nn_dists_square(knn_);

    for (size_t i = 0; i < cloud->size(); ++i)
    {
        kdtree.KnnSearch(cloud->at(i), knn_, nn_indices, nn_dists_square);

        // compute covariance
        Vector3Type mean;
        Matrix3Type covariance;

        ComputeMeanAndCovarianceMatrix(*cloud, nn_indices, covariance, mean);

        using EigenMatrix3 = Eigen::Matrix<Scalar, 3, 3>;
        using EigenVector3 = Eigen::Matrix<Scalar, 3, 1>;

        EigenMatrix3 cov_e;
        memcpy(cov_e.data(), covariance.GetData(), sizeof(Scalar) * 9u);

        Eigen::JacobiSVD<EigenMatrix3> svd(cov_e, Eigen::ComputeFullU | Eigen::ComputeFullV);

        // use plane regularization method
        EigenVector3 values = EigenVector3(1, 1, 1e-3);

        cov_e = svd.matrixU() * values.asDiagonal() * svd.matrixV().transpose();

        memcpy(covariances[i].GetData(), cov_e.data(), sizeof(Scalar) * 9u);
    }

    return true;
}

}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_REGISTRAITON_GICP_HPP_
