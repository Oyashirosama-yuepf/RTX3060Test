/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file essential_matrix_factor.cpp
 * @brief This implementation file defines essential matrix factor
 * @author Lifeng(lifeng@holomaitc.com)
 * @date "Jan-03-2022"
 */

#include <holo/localization/vision/vslam/essential_matrix_factor.h>

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
EssentialMatrixFactor::EssentialMatrixFactor(const gtsam::Point3& p1, const gtsam::Point3& p2,
                                             const gtsam::Key& pose1_key, const gtsam::Key& pose2_key,
                                             const gtsam::SharedNoiseModel&       model,
                                             const boost::optional<gtsam::Pose3>& optional_T_bc)
  : Base(model, pose1_key, pose2_key), p1_(p1), p2_(p2), optional_T_bc_(optional_T_bc)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector EssentialMatrixFactor::evaluateError(const gtsam::Pose3& wTb1, const gtsam::Pose3& wTb2,
                                                   const boost::optional<gtsam::Matrix&> H_pose1,
                                                   const boost::optional<gtsam::Matrix&> H_pose2) const
{
    // construct camera pose
    gtsam::Pose3  wTc1(wTb1);
    gtsam::Matrix D_camera1_to_body;  // 6x6
    if (optional_T_bc_)
    {
        wTc1 = wTb1.compose(*optional_T_bc_, D_camera1_to_body);
    }
    gtsam::Pose3  wTc2(wTb2);
    gtsam::Matrix D_camera2_to_body;  // 6x6
    if (optional_T_bc_)
    {
        wTc2 = wTb2.compose(*optional_T_bc_, D_camera2_to_body);
    }

    // compute relative Pose3 between camera1 and camera2
    gtsam::Matrix D_1T2_camera1, D_1T2_camera2;
    gtsam::Pose3  _1T2_ = wTc1.between(wTc2, D_1T2_camera1, D_1T2_camera2);

    // convert to EssentialMatrix
    gtsam::Matrix          D_E_to_1T2;
    gtsam::EssentialMatrix E = gtsam::EssentialMatrix::FromPose3(_1T2_, D_E_to_1T2);

    // // compute error
    gtsam::Matrix D_error_to_E;
    gtsam::Vector error(1);
    error << E.error(p1_, p2_, D_error_to_E);

    // compose jacobian
    if (H_pose1)
    {
        *H_pose1 = D_error_to_E * D_E_to_1T2 * D_1T2_camera1 * D_camera1_to_body;
    }
    if (H_pose2)
    {
        *H_pose2 = D_error_to_E * D_E_to_1T2 * D_1T2_camera2 * D_camera2_to_body;
    }

    return error;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EssentialMatrixFactor2::EssentialMatrixFactor2(const gtsam::EssentialMatrix& measuredE, const gtsam::Key& pose1_key,
                                               const gtsam::Key& pose2_key, const gtsam::SharedNoiseModel& model,
                                               const boost::optional<gtsam::Pose3>& optional_T_bc)
  : Base(model, pose1_key, pose2_key), measuredE_(measuredE), optional_T_bc_(optional_T_bc)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector EssentialMatrixFactor2::evaluateError(const gtsam::Pose3& wTb1, const gtsam::Pose3& wTb2,
                                                    const boost::optional<gtsam::Matrix&> H_pose1,
                                                    const boost::optional<gtsam::Matrix&> H_pose2) const
{
    // construct camera pose
    gtsam::Pose3  wTc1(wTb1);
    gtsam::Matrix D_camera1_to_body;  // 6x6
    if (optional_T_bc_)
    {
        wTc1 = wTb1.compose(*optional_T_bc_, D_camera1_to_body);
    }
    gtsam::Pose3  wTc2(wTb2);
    gtsam::Matrix D_camera2_to_body;  // 6x6
    if (optional_T_bc_)
    {
        wTc2 = wTb2.compose(*optional_T_bc_, D_camera2_to_body);
    }

    // compute relative Pose3 between camera1 and camera2
    gtsam::Matrix D_1T2_camera1, D_1T2_camera2;
    gtsam::Pose3  _1T2_ = wTc1.between(wTc2, D_1T2_camera1, D_1T2_camera2);

    // convert to EssentialMatrix
    gtsam::Matrix          D_E_to_1T2;
    gtsam::EssentialMatrix E = gtsam::EssentialMatrix::FromPose3(_1T2_, D_E_to_1T2);

    // // compute error
    gtsam::Vector error(5);
    error << measuredE_.localCoordinates(E);  // 5D error

    // compose jacobian
    if (H_pose1)
    {
        *H_pose1 = D_E_to_1T2 * D_1T2_camera1 * D_camera1_to_body;
    }
    if (H_pose2)
    {
        *H_pose2 = D_E_to_1T2 * D_1T2_camera2 * D_camera2_to_body;
    }

    return error;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo