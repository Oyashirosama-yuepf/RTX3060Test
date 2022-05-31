/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file prior_rpy_factor.cpp
 * @brief source file of prior rpy factor
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-02-08"
 */

#include <gtsam/inference/Symbol.h>

#include <holo/localization/backend/factors/prior_rpy_factor.h>
#include <holo/localization/sam/factors/internal/prior_rpy_factor_inl.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PriorRPYFactor::PriorRPYFactor(Vector3Type const& sigmas, uint32_t const pose_index, Vector3Type const& measurement,
                               bool_t const fix_roll, bool_t const fix_pitch, bool_t const fix_yaw,
                               Scalar const delta) noexcept
  : sigmas_(sigmas)
  , pose_index_(pose_index)
  , measurement_(measurement)
  , fix_roll_(fix_roll)
  , fix_pitch_(fix_pitch)
  , fix_yaw_(fix_yaw)
  , delta_(delta)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PriorRPYFactor::~PriorRPYFactor() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* PriorRPYFactor::GetFactor()
{
    gtsam::Vector3 const          sigmas(sigmas_(0u), sigmas_(1u), sigmas_(2u));
    gtsam::SharedNoiseModel const noise_model = gtsam::noiseModel::Diagonal::Sigmas(sigmas);
    gtsam::Key const              pose_key    = gtsam::symbol_shorthand::X(pose_index_);
    gtsam::Vector3 const          measurement(measurement_(0u), measurement_(1u), measurement_(2u));
    return static_cast<void*>(new holo::localization::internal::PriorRPYFactor(
        noise_model, pose_key, measurement, fix_roll_, fix_pitch_, fix_yaw_, delta_));
}
}  // namespace localization
}  // namespace holo
