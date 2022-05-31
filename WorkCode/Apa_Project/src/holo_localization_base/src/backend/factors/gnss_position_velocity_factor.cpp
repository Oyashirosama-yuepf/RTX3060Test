/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_position_velocity_factor.cpp
 * @brief Source file for GNSS position and velocity factor class
 * @author Lei Gehang (leigehang@holomaitc.com)
 * @date Aug 24, 2020
 */

#include <holo/localization/backend/factors/gnss_position_velocity_factor.h>

#include <holo/localization/sam/factors/internal/gnss_position_velocity_factor_inl.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <int32_t ROW, int32_t COL>
Eigen::Matrix<Scalar, ROW, COL> convertMatrix(holo::numerics::MatrixT<Scalar, ROW, COL> const& in)
{
    Eigen::Matrix<Scalar, ROW, COL> out;
    for (int32_t i = 0; i < ROW; i++)
    {
        for (int32_t j = 0; j < COL; j++)
        {
            out(i, j) = in(i, j);
        }
    }
    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::PreintegratedImuMeasurements convert(ImuPreintegrationMeasurement const& pim_holo)
{
    // get parameters
    ImuPreintegrationParameters const& params = pim_holo.GetParameters();

    // get imu bias
    ImuBiasType const& imu_bias = pim_holo.GetImuBias();

    // PreintegrationBase params
    boost::shared_ptr<gtsam::PreintegratedImuMeasurements::Params> preint_param =
        gtsam::PreintegratedImuMeasurements::Params::MakeSharedU(params.GetGravity());
    preint_param->setBodyPSensor(gtsam::Pose3(convertMatrix<4u, 4u>(params.GetExtrinsicBodyImu().ToMatrix())));
    preint_param->accelerometerCovariance =
        convertMatrix<3u, 3u>(params.GetAccNoiseSigmas().CwiseSquare().AsDiagonal());
    preint_param->gyroscopeCovariance = convertMatrix<3u, 3u>(params.GetGyroNoiseSigmas().CwiseSquare().AsDiagonal());
    preint_param->integrationCovariance =
        convertMatrix<3u, 3u>((Scalar)params.GetIntegrationUncertainty() * Matrix3Type::Identity());

    // get imu bias
    gtsam::imuBias::ConstantBias const imubias(convertMatrix<3u, 1u>(imu_bias.GetLinearAccelerationBias<Vector3Type>()),
                                               convertMatrix<3u, 1u>(imu_bias.GetAngularVelocityBias<Vector3Type>()));

    return gtsam::PreintegratedImuMeasurements(
        gtsam::PreintegrationType(preint_param, pim_holo.GetDeltaTime(),
                                  convertMatrix<9u, 1u>(pim_holo.GetPreintegratedNavstate()),
                                  convertMatrix<9u, 3u>(pim_holo.GetPreintegratedJacobianBiasAcc()),
                                  convertMatrix<9u, 3u>(pim_holo.GetPreintegratedJacobianBiasGyro()), imubias),
        convertMatrix<9u, 9u>(pim_holo.GetPreintegratedMeasurementCovariance()));
}

}  // namespace internal

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GnssPositionVelocityFactor::GnssPositionVelocityFactor(uint64_t const pose_index, uint64_t const velocity_index,
                                                       Vector6Type const& gnss_measurement, Vector6Type const& sigmas,
                                                       OptionalPimType const& pim, Rot3Type const& wRb)
  : pose_index_(pose_index)
  , velocity_index_(velocity_index)
  , gnss_measurement_(gnss_measurement)
  , sigmas_(sigmas)
  , pim_(pim)
  , wRb_(wRb)
{
    if (pose_index_ != velocity_index_)
    {
        std::stringstream ss;
        ss << "GnssPositionVelocityFactor --- pose_index must be equal to the velocity_index\n"
           << "current index is: pose_index = " << pose_index_ << ", velocity_index = " << velocity_index_;
        std::cout << ss.str() << std::endl;
        throw std::runtime_error(ss.str());
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* GnssPositionVelocityFactor::GetFactor()
{
    gtsam::Key const pose_key     = gtsam::symbol_shorthand::X(pose_index_);
    gtsam::Key const velocity_key = gtsam::symbol_shorthand::V(velocity_index_);

    gtsam::Point3 const  gnss_position(gnss_measurement_.At(0u), gnss_measurement_.At(1u), gnss_measurement_.At(2u));
    gtsam::Vector3 const gnss_velocity(gnss_measurement_.At(3u), gnss_measurement_.At(4u), gnss_measurement_.At(5u));

    gtsam::Vector6 const sigmas = (gtsam::Vector6() << sigmas_.At(0u), sigmas_.At(1u), sigmas_.At(2u), sigmas_.At(3u),
                                   sigmas_.At(4u), sigmas_.At(5u))
                                      .finished();

    if (!pim_)
    {
        return static_cast<void*>(
            new internal::GnssPositionVelocityFactor(pose_key, velocity_key, gnss_position, gnss_velocity, sigmas));
    }

    // construct pim
    internal::GnssPositionVelocityFactor::PimType pim = internal::convert(*pim_);

    gtsam::Matrix3 wRb;
    wRb << wRb_.R00(), wRb_.R01(), wRb_.R02(), wRb_.R10(), wRb_.R11(), wRb_.R12(), wRb_.R20(), wRb_.R21(), wRb_.R22();

    return static_cast<void*>(new internal::GnssPositionVelocityFactor(pose_key, velocity_key, gnss_position,
                                                                       gnss_velocity, sigmas, pim, wRb));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}  // namespace localization
}  // namespace holo
