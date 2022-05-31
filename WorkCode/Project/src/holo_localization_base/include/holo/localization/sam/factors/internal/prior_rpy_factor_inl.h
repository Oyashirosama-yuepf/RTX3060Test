/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file prior_rpy_factor_inl.h
 * @brief header file of prior rpy factor
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-02-08"
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_PRIOR_RPY_FACTOR_INL_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_PRIOR_RPY_FACTOR_INL_H_

#include <gtsam/base/Vector.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>

namespace holo
{
namespace localization
{
namespace internal
{
/**
 * @addtogroup sam
 * @{
 *
 */

class PriorRPYFactor : public gtsam::NoiseModelFactor1<gtsam::Pose3>
{
public:
    /**
     * @brief define smart pointer
     */
    using Ptr      = boost::shared_ptr<PriorRPYFactor>;
    using ConstPtr = boost::shared_ptr<const PriorRPYFactor>;
    using Base     = gtsam::NoiseModelFactor1<gtsam::Pose3>;

    /**
     * @brief construct a new prior RPY factor object
     *
     * @param[in] model noise model for measurement
     * @param[in] pose_key key of the pose to be optimized
     * @param[in] measurement roll, pich, yaw measurement
     * @param[in] fix_roll whether fix roll during optimization
     * @param[in] fix_pitch whether fix pitch during optimization
     * @param[in] fix_yaw whether fix yaw during optimization
     * @param[in] delta small perturbution used to compute numerical derivation
     */
    PriorRPYFactor(gtsam::SharedNoiseModel const& model, gtsam::Key const& pose_key, gtsam::Vector3 const& measurement,
                   bool const fix_roll, bool const fix_pitch, bool const fix_yaw, double const delta = 1e-8);

    /**
     * @brief destructor
     */
    ~PriorRPYFactor() noexcept;

    /**
     * @brief evaluate error
     *
     * @param[in] pose pose to be optimzied
     * @param[in] H jacobian of error w.r.t pose
     * @return gtsam::Vector error
     */
    virtual gtsam::Vector evaluateError(gtsam::Pose3 const&             pose,
                                        boost::optional<gtsam::Matrix&> H = boost::none) const override;

protected:
    /**
     * @brief compute jacobian of RPY w.r.t rotation vector with numerical derivation
     *
     * @param[in] rotation_vector rotation vector
     * @param[in] delta small perturbution add to rotation vector
     * @return gtsam::Matrix33 jacobian of RPY w.r.t rotation vector
     */
    gtsam::Matrix33 computeJacobianOfRPYwrtRotationVector(gtsam::Vector3 const& rotation_vector,
                                                          double const          delta) const;

protected:
    gtsam::Vector3 measurement_;  ///< roll, pitch, yaw measurement
    bool           fix_roll_;     ///< whether fix roll during optimization
    bool           fix_pitch_;    ///< whether fix pitch during optimization
    bool           fix_yaw_;      ///< whether fix yaw during optimization
    double         delta_;        ///< perturbution used to compute numerical derivation
};

/**
 * @}
 *
 */
}  // namespace internal
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_PRIOR_RPY_FACTOR_INL_H_
