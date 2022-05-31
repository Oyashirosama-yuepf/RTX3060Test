/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_imu_extrinsic_factor.cpp
 * @brief this file is the implementation of camera imu extrinsic factor
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2020-04-21"
 */

#include <gtsam/inference/Symbol.h>

#include <holo/localization/backend/factors/camera_imu_extrinsic_factor.h>
#include <holo/localization/sam/factors/internal/camera_imu_extrinsic_factor_inl.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraImuExtrinsicFactor::CameraImuExtrinsicFactor(Vector2Type const& sigmas, uint64_t const wTi_index,
                                                   uint64_t const ptw_index, uint64_t const rpy_index,
                                                   uint64_t const itc_index, Matrix3Type const& K,
                                                   Point2Type const& measurement, bool_t const fix_wTi,
                                                   bool_t const fix_ptw, bool_t const fix_roll, bool_t const fix_pitch,
                                                   bool_t const fix_yaw, bool_t const fix_itc)
  : sigmas_(sigmas)
  , wTi_index_(wTi_index)
  , ptw_index_(ptw_index)
  , rpy_index_(rpy_index)
  , itc_index_(itc_index)
  , K_(K)
  , measurement_(measurement)
  , fix_wTi_(fix_wTi)
  , fix_ptw_(fix_ptw)
  , fix_roll_(fix_roll)
  , fix_pitch_(fix_pitch)
  , fix_yaw_(fix_yaw)
  , fix_itc_(fix_itc)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraImuExtrinsicFactor::~CameraImuExtrinsicFactor()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* CameraImuExtrinsicFactor::GetFactor() const
{
    gtsam::Vector2                   sigmas_value(sigmas_(0u), sigmas_(1u));
    gtsam::SharedNoiseModel const    noise_model = gtsam::noiseModel::Diagonal::Sigmas(sigmas_value);
    gtsam::Key const                 wTi_key     = gtsam::symbol_shorthand::X(wTi_index_);
    gtsam::Key const                 ptw_key     = gtsam::symbol_shorthand::L(ptw_index_);
    gtsam::Key const                 rpy_key     = gtsam::symbol_shorthand::T(rpy_index_);
    gtsam::Key const                 itc_key     = gtsam::symbol_shorthand::T(itc_index_);
    gtsam::Cal3_S2::shared_ptr const K =
        boost::make_shared<gtsam::Cal3_S2>(K_(0u, 0u), K_(1u, 1u), K_(0u, 1u), K_(0u, 2u), K_(1u, 2u));
    gtsam::Point2 const measurement(measurement_.GetX(), measurement_.GetY());
    return static_cast<void*>(new holo::localization::internal::CameraImuExtrinsicFactor(
        noise_model, wTi_key, ptw_key, rpy_key, itc_key, K, measurement, fix_wTi_, fix_ptw_, fix_roll_, fix_pitch_,
        fix_yaw_, fix_itc_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CameraImuExtrinsicFactor::TestDefaultConstructorOfInternalFactor()
{
    holo::localization::internal::CameraImuExtrinsicFactor();
}
}  // namespace localization
}  // namespace holo
