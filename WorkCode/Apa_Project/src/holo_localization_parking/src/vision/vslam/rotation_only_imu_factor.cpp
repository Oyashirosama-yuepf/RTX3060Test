/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rotation_only_imu_factor.cpp
 * @brief This cpp file defines rotation only imu factor
 * @author Lifeng(lifeng@holomaitc.com)
 * @date "Jan-02-2022"
 */

#include <holo/localization/vision/vslam/rotation_only_imu_factor.h>

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
RotationOnlyImuFactor::RotationOnlyImuFactor(gtsam::Key pose_i, gtsam::Key pose_j, gtsam::Key bias,
                                             const PreintegratedAhrsMeasurements& preintegratedMeasurements)
  : Base(gtsam::noiseModel::Gaussian::Covariance(preintegratedMeasurements.preintMeasCov()), pose_i, pose_j, bias)
  , pim_(preintegratedMeasurements)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector RotationOnlyImuFactor::evaluateError(const gtsam::Pose3& pose_i, const gtsam::Pose3& pose_j,
                                                   const gtsam::Vector3& bias, const boost::optional<gtsam::Matrix&> H1,
                                                   const boost::optional<gtsam::Matrix&> H2,
                                                   const boost::optional<gtsam::Matrix&> H3) const
{
    const auto Ri = pose_i.rotation();
    const auto Rj = pose_j.rotation();
    // Do bias correction, if (H3) will contain 3*3 derivative used below
    const gtsam::Vector3 biascorrectedOmega = pim_.predict(bias, H3);

    // Coriolis term
    const gtsam::Vector3 coriolis       = pim_.integrateCoriolis(Ri);
    const gtsam::Vector3 correctedOmega = biascorrectedOmega - coriolis;

    // Prediction
    const gtsam::Rot3 correctedDeltaRij = gtsam::Rot3::Expmap(correctedOmega);

    // Get error between actual and prediction
    const gtsam::Rot3 actualRij = Ri.between(Rj);
    const gtsam::Rot3 fRrot     = correctedDeltaRij.between(actualRij);
    gtsam::Vector3    fR        = gtsam::Rot3::Logmap(fRrot);

    // Terms common to derivatives
    const gtsam::Matrix3 D_cDeltaRij_cOmega = gtsam::Rot3::ExpmapDerivative(correctedOmega);
    const gtsam::Matrix3 D_fR_fRrot         = gtsam::Rot3::LogmapDerivative(fR);

    gtsam::Matrix3 D_error_to_translation = gtsam::Matrix3::Zero();
    if (H1)
    {
        // dfR/dPose_i
        H1->resize(3, 6);
        gtsam::Matrix3 D_coriolis = -D_cDeltaRij_cOmega * gtsam::skewSymmetric(coriolis);
        (*H1).block(0, 0, 3, 3)   = D_fR_fRrot * (-actualRij.transpose() - fRrot.transpose() * D_coriolis);
        (*H1).block(0, 3, 3, 3)   = D_error_to_translation;
    }

    if (H2)
    {
        // dfR/dPosej
        H2->resize(3, 6);
        (*H2).block(0, 0, 3, 3) = D_fR_fRrot;
        (*H2).block(0, 3, 3, 3) = D_error_to_translation;
    }

    if (H3)
    {
        // dfR/dBias, note H3 contains derivative of predict
        const gtsam::Matrix3 JbiasOmega = D_cDeltaRij_cOmega * (*H3);
        H3->resize(3, 3);
        (*H3) << D_fR_fRrot * (-fRrot.transpose() * JbiasOmega);
    }

    gtsam::Vector error(3);
    error << fR;
    return error;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo