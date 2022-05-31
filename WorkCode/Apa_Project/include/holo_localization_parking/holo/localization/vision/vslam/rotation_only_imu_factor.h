/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rotation_only_imu_factor.h
 * @brief This header file defines rotation only imu factor
 * @author Lifeng(lifeng@holomaitc.com)
 * @date "Jan-02-2022"
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_ROTATION_ONLY_IMU_FACTOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_ROTATION_ONLY_IMU_FACTOR_H_

#include <holo/localization/vision/vslam/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * @addtogroup vslam
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief this class measures the error between two directions
 */
class RotationOnlyImuFactor : public gtsam::NoiseModelFactor3<gtsam::Pose3, gtsam::Pose3, gtsam::Vector3>
{
public:
    /**
     * @brief define smart pointer
     */
    typedef boost::shared_ptr<RotationOnlyImuFactor>                             Ptr;
    typedef boost::shared_ptr<const RotationOnlyImuFactor>                       ConstPtr;
    typedef gtsam::NoiseModelFactor3<gtsam::Pose3, gtsam::Pose3, gtsam::Vector3> Base;

    /**
     * Constructor
     * @param pose_i Previous pose key
     * @param pose_j Current pose key
     * @param bias   Previous bias key
     * @param preintegratedMeasurements preintergration measurement
     */
    RotationOnlyImuFactor(gtsam::Key pose_i, gtsam::Key pose_j, gtsam::Key bias,
                          const PreintegratedAhrsMeasurements& preintegratedMeasurements);

    /**
     * @brief destructor
     */
    virtual ~RotationOnlyImuFactor()
    {
    }

    /**
     * @brief get preintegrated measurement
     */
    const PreintegratedAhrsMeasurements& preintegratedMeasurements() const
    {
        return pim_;
    }

    /**
     * @brief evaluate error
     *
     * @param pose_i previous pose
     * @param pose_j current pose
     * @param H_1 jacobian of error to pose_i (3x6)
     * @param H_2 jacobian of error to pose_j (3x6)
     * @param H_3 jacobian of error to bias (3x3)
     * @return gtsam::Vector contain the evaluated error(3x1)
     */
    virtual gtsam::Vector evaluateError(const gtsam::Pose3& pose_i, const gtsam::Pose3& pose_j,
                                        const gtsam::Vector3&                 bias,
                                        const boost::optional<gtsam::Matrix&> H1 = boost::none,
                                        const boost::optional<gtsam::Matrix&> H2 = boost::none,
                                        const boost::optional<gtsam::Matrix&> H3 = boost::none) const override;

private:
    /**
     * @brief preintegrated measurement
     */
    PreintegratedAhrsMeasurements pim_;
};
// class RotationOnlyImuFactor
typedef RotationOnlyImuFactor::Ptr RotationOnlyImuFactorPtr;

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_VISION_VSLAM_ROTATION_ONLY_IMU_FACTOR_H_