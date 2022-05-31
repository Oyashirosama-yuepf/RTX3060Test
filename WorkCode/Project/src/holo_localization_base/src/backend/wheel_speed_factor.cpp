/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file wheel_speed_factor.cpp
 * @brief this file deines wheel speed factor class
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-08-04
 */

#include <holo/localization/backend/wheel_speed_factor.h>
#include <holo/localization/sam/factors/internal/wheel_speed_factor_inl.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WheelSpeedFactor::WheelSpeedFactor(uint64_t const pose1_index, uint64_t const pose2_index, Pose3Type const& iEb,
                                   WheelPreintegrationMeasurement const& pwm)
  : pose1_index_(pose1_index), pose2_index_(pose2_index), iEb_(iEb), pwm_(pwm)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* WheelSpeedFactor::GetFactor() const
{
    gtsam::Key const pose1_key = gtsam::symbol_shorthand::X(pose1_index_);
    gtsam::Key const pose2_key = gtsam::symbol_shorthand::X(pose2_index_);

    // convert holo pose to gtsam pose
    Matrix4Type const             mat        = iEb_.ToMatrix();
    uint32_t const                array_size = mat.GetCols() * mat.GetRows();
    Eigen::Matrix<Scalar, 4u, 4u> result;
    memcpy(result.data(), mat.GetData(), sizeof(Scalar) * array_size);
    gtsam::Pose3 const iEb = gtsam::Pose3(result);

    // convert holo matrix3 to gtsam matrix3
    Matrix3Type const             covariance     = pwm_.GetPreintegratedMeasurementCovariance();
    uint32_t const                array_size_cov = covariance.GetCols() * covariance.GetRows();
    Eigen::Matrix<Scalar, 3u, 3u> res_cov;
    memcpy(res_cov.data(), covariance.GetData(), sizeof(Scalar) * array_size_cov);
    gtsam::Matrix3 const pwm_cov = gtsam::Matrix3(res_cov);

    Vector3Type const    preintegrated_wheel_dist = pwm_.GetPreintegrated();
    gtsam::Vector3 const pwm_dist(preintegrated_wheel_dist(0u), preintegrated_wheel_dist(1u),
                                  preintegrated_wheel_dist(2u));
    return static_cast<void*>(
        new holo::localization::internal::WheelSpeedFactor(pose1_key, pose2_key, iEb, pwm_cov, pwm_dist));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WheelSpeedFactor::TestDefaultConstructorOfInternalFactor()
{
    holo::localization::internal::WheelSpeedFactor();
}

}  // namespace localization
}  // namespace holo
