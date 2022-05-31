/*
 * Copyright (C) HoloMatic Technology (Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file   fisheye_intrinsic_factor_inl.h
 * @brief  Define the fish-eye intrinsic factor
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date   2021-08-19
 */

#ifndef HOLO_CALIBRATION_DEV_FACTORS_INTERNAL_FISHEYE_INTRINSIC_FACTOR_INL_H_
#define HOLO_CALIBRATION_DEV_FACTORS_INTERNAL_FISHEYE_INTRINSIC_FACTOR_INL_H_

#include <holo/calibration/camera/field/types.h>
#include <holo/common/details/intrinsic.h>
#include <holo/localization/sam/sam.h>

namespace holo
{
namespace calibration
{
namespace internal
{
/**
 * @addtogroup internal
 * @{
 *
 */
class FisheyeIntrinsicFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Vector8>
{
public:
    using Base = gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Vector8>;

    /**
     * @brief Constructor
     * @param[in] measure_2d 2D measurement in image frame [unit: pixel].
     * @param[in] point3d_world 3D point in the world frame [unit: m].
     * @param[in] model GTSAM's noise model.
     * @param[in] pose_key Index of camera pose.
     * @param[in] intrinsic_key Index of camera intrinsic.
     */
    FisheyeIntrinsicFactor(gtsam::Point2 const& measure_2d, gtsam::Point3 const& point3d_world,
                           gtsam::SharedNoiseModel const& model, gtsam::Key pose_key, gtsam::Key intrinsic_key)
      : Base(model, pose_key, intrinsic_key), measured_2d_(measure_2d), point3d_world_(point3d_world)
    {
    }

    ///@brief Destructor
    virtual ~FisheyeIntrinsicFactor()
    {
    }

    /**
     * @brief Evaluate error z - h(x) and optionally derivatives.
     * @param[in] pose Extrinsic of camera to be estimated.
     * @param[in] intrinsic Intrinsic of camera to be estimated. intrinsic: fx fy cx cy d1 d2 d3 d4
     * @param[in][out] H1 Jacobian of error w.r.t cTw
     * @param[in][out] H2 Jacobian of error w.r.t intrinsic
     * @return projection error(2 dimension)
     */
    virtual gtsam::Vector evaluateError(gtsam::Pose3 const& cTw, gtsam::Vector8 const& intrinsic,
                                        boost::optional<gtsam::Matrix&> H1 = boost::none,
                                        boost::optional<gtsam::Matrix&> H2 = boost::none) const override;

protected:
    ///@brief 2D point in image
    gtsam::Point2 measured_2d_;

    ///@brief 3D points in the world coordinate system
    gtsam::Point3 point3d_world_;
};
/**
 * @}
 */
}  // namespace internal
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_FACTORS_INTERNAL_FISHEYE_INTRINSIC_FACTOR_INL_H_
