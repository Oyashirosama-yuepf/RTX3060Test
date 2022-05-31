/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file unit3_factor.cpp
 * @brief source file of Unit3Factor class
 * @author Yanwei Du(duyanwei@holomaitc.com)
 * @date "Dec-11-2019"
 */

#include <holo/localization/vision/vslam/unit3_factor.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Unit3Factor::Unit3Factor(const gtsam::Point3& feature, const gtsam::SharedNoiseModel& model, const gtsam::Key& pose_key,
                         const gtsam::Key& landmark_key, const boost::optional<gtsam::Pose3>& optional_T_bc)
  : Base(model, pose_key, landmark_key), feature_(feature), optional_T_bc_(optional_T_bc)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector Unit3Factor::evaluateError(const gtsam::Pose3& T_wb, const gtsam::Point3& landmark,
                                         const boost::optional<gtsam::Matrix&> H_pose,
                                         const boost::optional<gtsam::Matrix&> H_landmark) const
{
    // construct camera pose
    gtsam::Pose3  T_wc(T_wb);
    gtsam::Matrix H0;  // 6x6
    if (optional_T_bc_)
    {
        T_wc = T_wb.compose(*optional_T_bc_, H0);
    }

    // transform landmark to camera frame
    gtsam::Matrix       H1;            // 3 x 6
    gtsam::Matrix       H_landmark_0;  // 3 x 3
    const gtsam::Point3 ptc = T_wc.transform_to(landmark, H1, H_landmark_0);

    // construct Unit3 from landmark
    gtsam::Matrix      H2;  // 2 x 3
    const gtsam::Unit3 q = gtsam::Unit3::FromPoint3(ptc, H2);

    // construct Unit3 from feature point
    const gtsam::Unit3 p(feature_);

    // compute error
    gtsam::Matrix        H3;  // 2 x 2
    const gtsam::Vector2 error = p.errorVector(q, boost::none, H3);

    if (H_pose)
    {
        *H_pose = H3 * H2 * H1 * H0;
    }

    if (H_landmark)
    {
        *H_landmark = H3 * H2 * H_landmark_0;
    }

    return error;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo