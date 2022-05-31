/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_slot_projection_factor.cpp
 * @brief this file defines parking_slot_projection_factor for semantic slam
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @author Changxi Cheng (chengchangxi@holomatic.com)
 * @date 2021-05-21
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_PROJECTION_FACTOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_PROJECTION_FACTOR_H_

#include <holo/localization/vision/vslam/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
namespace semantic
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief vslam parking slot projection factor
 */
class ParkingSlotProjectionFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Point3>
{
public:
    /**
     * @brief smart pointer
     */
    typedef boost::shared_ptr<ParkingSlotProjectionFactor>        Ptr;
    typedef boost::shared_ptr<const ParkingSlotProjectionFactor>  ConstPtr;
    typedef gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Point3> Base;

    /**
     * @brief Construct a new ParkingSlotFactor object
     *
     * @param pose_key key of estimated pose, T_wb1
     * @param vertex_key key of estimated vertex in world coordinate, P_w
     * @param measurement measurement (vertex) in body coordinate, P_b1
     * @param model noise model
     */
    ParkingSlotProjectionFactor(const gtsam::Key& pose_key, const gtsam::Key& vertex_key,
                                const gtsam::Point3& measurement, const gtsam::SharedNoiseModel& model);

    /**
     * @brief deconstructor
     */
    virtual ~ParkingSlotProjectionFactor()
    {
    }

    /**
     * @brief error function
     *
     * @param T_wb body pose in world frame
     * @param P_w the parking-spot vertex in world frame
     * @param H1 the optional Jacobian matrix for pose from body into world
     * @param H2 the optional Jacobian matrix for parking-spot vertex in the world
     * @return gtsam::Vector
     */
    virtual gtsam::Vector evaluateError(const gtsam::Pose3& T_wb, const gtsam::Point3& P_w,
                                        boost::optional<gtsam::Matrix&> H1 = boost::none,
                                        boost::optional<gtsam::Matrix&> H2 = boost::none) const override;

private:
    /// @brief measurement parking-spot vertex in body frame
    gtsam::Point3 measurement_;
};  // class ParkingSlotVertexFactor

typedef ParkingSlotProjectionFactor::Ptr ParkingSlotProjectionFactorPtr;
}  // namespace semantic
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_PROJECTION_FACTOR_H_