/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file projection_line_factor.cpp
 * @brief this file is the implementation of projection line factor class
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date June 20, 2020
 */

#include <gtsam/inference/Symbol.h>
#include <holo/localization/backend/factors/projection_line_factor.h>
#include <holo/localization/sam/factors/internal/projection_line_factor_inl.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ProjectionLineFactor::ProjectionLineFactor(uint64_t const index, Point3Type const& point, Pose3Type const& bTc,
                                           Matrix3Type const& K, Line2Type const& line, Scalar const sigma,
                                           Scalar const huber_loss_threshold,
                                           bool_t const enable_rotation_constraint) noexcept
  : index_(index)
  , point_(point)
  , bTc_(bTc)
  , K_(K)
  , line_(line)
  , sigma_(sigma)
  , huber_loss_threshold_(huber_loss_threshold)
  , enable_rotation_constraint_(enable_rotation_constraint)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* ProjectionLineFactor::GetFactor()
{
    gtsam::Key const    wTb_key = gtsam::symbol_shorthand::X(index_);
    gtsam::Point3 const point   = gtsam::Point3(point_.GetX(), point_.GetY(), point_.GetZ());

    // convert holo pose to gtsam pose
    Matrix4Type                   mat        = bTc_.ToMatrix();
    uint32_t const                array_size = mat.GetCols() * mat.GetRows();
    Eigen::Matrix<Scalar, 4u, 4u> result;
    memcpy(result.data(), mat.GetData(), sizeof(Scalar) * array_size);
    gtsam::Pose3 bTc = gtsam::Pose3(result);

    gtsam::Cal3_S2 const K = gtsam::Cal3_S2(K_(0u, 0u), K_(1u, 1u), K_(0u, 1u), K_(0u, 2u), K_(1u, 2u));

    Line2Type const line = line_;

    gtsam::SharedNoiseModel const noise_model =
        gtsam::noiseModel::Diagonal::Sigmas((gtsam::Vector1(1) << sigma_).finished());

    if (huber_loss_threshold_ <= 0.0)
    {
        return static_cast<void*>(new holo::localization::internal::ProjectionLineFactor(
            wTb_key, noise_model, point, bTc, K, line, enable_rotation_constraint_));
    }

    // Create huber loss
    const gtsam::noiseModel::Robust::shared_ptr huber_noise_model = gtsam::noiseModel::Robust::Create(
        gtsam::noiseModel::mEstimator::Huber::Create(huber_loss_threshold_), noise_model);

    return static_cast<void*>(new holo::localization::internal::ProjectionLineFactor(
        wTb_key, huber_noise_model, point, bTc, K, line, enable_rotation_constraint_));
}
}  // namespace localization
}  // namespace holo
