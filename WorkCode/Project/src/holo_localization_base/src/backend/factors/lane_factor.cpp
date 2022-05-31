/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_factor.cpp
 * @brief impletation of  lane factor class
 * @author Zhang Yelin (zhangyelin@holomatic.com)
 * @date Dec 13, 2019
 */

#include <gtsam/inference/Symbol.h>
#include <holo/localization/backend/factors/lane_factor.h>
#include <holo/localization/sam/factors/internal/lane_factor_inl.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Lane2Factor::Lane2Factor(const uint64_t& pose_key, const Point3Type& point, const Line2& line, const Scalar& sigma,
                         const LaneCorrespondenceType& lane_correspondence_type,
                         const bool_t                  disable_rotation_optimization)
  : pose_index_(pose_key)
  , point_(point)
  , line_(line)
  , sigma_(sigma)
  , lane_correspondence_type_(lane_correspondence_type)
  , disable_rotation_optimization_(disable_rotation_optimization)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* Lane2Factor::GetFactor()
{
    const gtsam::Symbol          pose_key('x', pose_index_);
    const Point3Type             point                    = point_;
    const Line2                  line                     = line_;
    const Scalar                 sigmas_value             = sigma_;
    const LaneCorrespondenceType lane_correspondence_type = lane_correspondence_type_;

    const gtsam::SharedNoiseModel noise_model =
        gtsam::noiseModel::Diagonal::Sigmas((gtsam::Vector1(1) << sigmas_value).finished());
    return static_cast<void*>(new holo::localization::internal::Lane2Factor(
        pose_key, noise_model, point, line, lane_correspondence_type, disable_rotation_optimization_));
}
}  // namespace localization
}  // namespace holo
