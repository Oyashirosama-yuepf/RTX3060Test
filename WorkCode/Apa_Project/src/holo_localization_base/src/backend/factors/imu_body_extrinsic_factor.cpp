/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_body_extinsic_factor.cpp
 * @brief this file define imu body extrinsic factor class
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-08-13
 */

#include <holo/localization/backend/factors/imu_body_extrinsic_factor.h>
#include <holo/localization/sam/factors/internal/imu_body_extrinsic_factor_inl.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImuBodyExtrinsicFactor::ImuBodyExtrinsicFactor(uint64_t const pose1_index, uint64_t const pose2_index,
                                               uint64_t const iRb_index, Point3Type const& itb,
                                               WheelPreintegrationMeasurement const& pwm)
  : pose1_index_(pose1_index), pose2_index_(pose2_index), iRb_index_(iRb_index), itb_(itb), pwm_(pwm)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* ImuBodyExtrinsicFactor::GetFactor() const
{
    gtsam::Key const pose1_key = gtsam::symbol_shorthand::X(pose1_index_);
    gtsam::Key const pose2_key = gtsam::symbol_shorthand::X(pose2_index_);
    gtsam::Key const iRb_key   = gtsam::symbol_shorthand::E(iRb_index_);

    // convert holo pose to gtsam pose
    Matrix4Type const             mat        = pwm_.GetEibHat().ToMatrix();
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

    // convert holo matrix3 to gtsam matrix3
    Matrix3Type const             jacobian_iRb        = pwm_.GetPreintegratedHRib();
    uint32_t const                array_size_jacobian = jacobian_iRb.GetCols() * jacobian_iRb.GetRows();
    Eigen::Matrix<Scalar, 3u, 3u> res_jacobian;
    memcpy(res_jacobian.data(), jacobian_iRb.GetData(), sizeof(Scalar) * array_size_jacobian);
    gtsam::Matrix3 const pwm_jacobian = gtsam::Matrix3(res_jacobian);

    Vector3Type const    preintegrated_wheel_dist = pwm_.GetPreintegrated();
    gtsam::Vector3 const pwm_dist(preintegrated_wheel_dist(0u), preintegrated_wheel_dist(1u),
                                  preintegrated_wheel_dist(2u));
    return static_cast<void*>(new holo::localization::internal::ImuBodyExtrinsicFactor(
        pose1_key, pose2_key, iRb_key, iEb.translation(), pwm_cov, pwm_jacobian, iEb.rotation(), pwm_dist));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImuBodyExtrinsicFactor::TestDefaultConstructorOfInternalFactor()
{
    holo::localization::internal::ImuBodyExtrinsicFactor();
}

}  // namespace localization
}  // namespace holo
