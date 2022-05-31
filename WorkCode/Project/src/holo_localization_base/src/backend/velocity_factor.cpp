/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velocity_factor.cpp
 * @brief source file for velocity factor class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-06-02"
 */

#include <holo/localization/backend/velocity_factor.h>
#include <holo/localization/sam/factors/internal/velocity_factor_inl.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VelocityFactor::VelocityFactor(const uint64_t pose_index, const uint64_t velocity_index, const Vector3Type& velocity,
                               const Vector3Type& sigmas)
  : pose_index_(pose_index), velocity_index_(velocity_index), velocity_(velocity), sigmas_(sigmas)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* VelocityFactor::GetFactor()
{
    const gtsam::Key              pose_key     = gtsam::symbol_shorthand::X(pose_index_);
    const gtsam::Key              velocity_key = gtsam::symbol_shorthand::V(velocity_index_);
    const gtsam::Vector3          velocity_measurement(velocity_(0u), velocity_(1u), velocity_(2u));
    const gtsam::Vector3          sigmas_value(sigmas_(0u), sigmas_(1u), sigmas_(2u));
    const gtsam::SharedNoiseModel noise_model = gtsam::noiseModel::Diagonal::Sigmas(sigmas_value);
    return static_cast<void*>(
        new holo::localization::internal::VelocityFactor(pose_key, velocity_key, velocity_measurement, noise_model));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VelocityFactor::TestDefaultConstructorOfInternalFactor()
{
    holo::localization::internal::VelocityFactor();
}
}  // namespace localization
}  // namespace holo
