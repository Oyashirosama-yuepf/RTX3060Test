/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velocity_factor_inl.h
 * @brief this file define velocity factor used to constraint a pose and velocity
 * @author Yetong. Zhang, zhangyetong@holomatic.com
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-06-02"
 */

#ifndef HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_VELOCITY_FACTOR_INL_H_
#define HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_VELOCITY_FACTOR_INL_H_

#include <gtsam/base/Vector.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief vehicle velocity factor
 * @details error = V_b - T_wb.TransformTo(V_w)
 */
class VelocityFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Vector3>
{
public:
    /**
     * @brief define smart pointer
     */
    using Ptr      = boost::shared_ptr<VelocityFactor>;
    using ConstPtr = boost::shared_ptr<const VelocityFactor>;
    using Base     = gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Vector3>;

    /**
     * @brief default constructor
     * @note for holo::OptionalT, do not use it directly
     */
    VelocityFactor();

    /**
     * @brief constructor
     * @param pose_key associated pose variable key
     * @param velocity_key associated velocity variable key
     * @param measurement Velocity measurement in body frame
     * @param model noise model for velocity snesor, in X-Y-Z
     */
    VelocityFactor(const gtsam::Key& pose_key, const gtsam::Key& velocity_key, const gtsam::Vector3& measurement,
                   const gtsam::SharedNoiseModel& model);

    /**
     * @brief Get the Velocity Measurement
     *
     * @return velocity in body frame
     */
    const gtsam::Vector3& GetVelocityMeasurement() const;

    /**
     * @brief override function to evaluate factor error with jacobian
     *
     * @param T_wb pose of body frame in vio map frame
     * @param V_w velocity of body frame in vio map frame
     * @param H1 jacobian d(error) / d(T_wb)
     * @param H2 jacobian d(error) / d(V_w)
     * @return error of this factor
     */
    virtual gtsam::Vector evaluateError(const gtsam::Pose3& wTb, const gtsam::Vector3& Vw,
                                        boost::optional<gtsam::Matrix&> H1 = boost::none,
                                        boost::optional<gtsam::Matrix&> H2 = boost::none) const override;

private:
    /// @brief measurement velocity in body frame
    gtsam::Vector3 measurement_;
};  // class Velocity3Factor

/**
 * @}
 *
 */
}  // namespace internal
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_FACTORS_INTERNAL_VELOCITY_FACTOR_INL_H_
