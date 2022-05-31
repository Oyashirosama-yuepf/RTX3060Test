/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file unit3_factor.h
 * @brief This header file defines unit3 factor
 * @author Yanwei Du(duyanwei@holomaitc.com)
 * @date "Sep-02-2019"
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_UNIT3_FACTOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_UNIT3_FACTOR_H_

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
class Unit3Factor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Point3>
{
public:
    /**
     * @brief define smart pointer
     */
    typedef boost::shared_ptr<Unit3Factor>                        Ptr;
    typedef boost::shared_ptr<const Unit3Factor>                  ConstPtr;
    typedef gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Point3> Base;

    /**
     * @brief Construct a new Unit3Factor object
     *
     * @param feature feature measurement in normalized coordinate
     * @param model noise model
     * @param pose_key key of estimated pose
     * @param landmark_key key of estimated landmark
     * @param optional_T_bc transform from body to sensor frame (default identity)
     */
    Unit3Factor(const gtsam::Point3& feature, const gtsam::SharedNoiseModel& model, const gtsam::Key& pose_key,
                const gtsam::Key& landmark_key, const boost::optional<gtsam::Pose3>& optional_T_bc = boost::none);

    /**
     * @brief evaluate error
     *
     * @param T_wb pose of body in world frame
     * @param landmark landmark in world frame
     * @param H_pose jacobian of error to pose (2x6)
     * @param H_landmark jacobian of error to landmark (2x3)
     * @return gtsam::Vector contain the evaluated error(2x1)
     */
    virtual gtsam::Vector evaluateError(const gtsam::Pose3& T_wb, const gtsam::Point3& landmark,
                                        const boost::optional<gtsam::Matrix&> H_pose     = boost::none,
                                        const boost::optional<gtsam::Matrix&> H_landmark = boost::none) const override;

    /**
     * @brief get feature point measurement
     *
     * @return feature point measurement
     */
    const gtsam::Point3& GetFeatureMeasurement() const noexcept
    {
        return feature_;
    }

private:
    gtsam::Point3 feature_;  ///< 2D feature measurement of normalized coordinate.(on normalized plane. z == 1)

    boost::optional<gtsam::Pose3> optional_T_bc_;  ///< extrinsic parameters

};  // class Unit3Factor

typedef Unit3Factor::Ptr Unit3FactorPtr;

/**
 * @}
 *
 */

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_UNIT3_FACTOR_H_