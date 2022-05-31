/*!
 * @file imu_preintegration.h
 * @brief this header file defines several class related with imu preintegration
 * @author lichao@holomatic.com
 * @date Oct 07, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_LOCALIZATION_IMU_PREINTEGRATION
#define HOLO_LOCALIZATION_IMU_PREINTEGRATION

#include <cmath>
#include <memory>

#include <holo/common/imu.h>
#include <holo/common/imu_bias.h>
#include <holo/geometry/pose3.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>
#include <holo/utils/yaml.h>

#include <holo/localization/common/navstate.h>
#include <holo/localization/common/types.h>

namespace holo
{
namespace localization
{
/**
 * @brief class to hold the fixed parameters which will be used in imu
 * preintegration.
 */
class ImuPreintegrationParameters
{
public:
    /**
     * @brief constructor
     *
     * @param _acc_noise_sigma accelerometer sigma value
     * @param _gyro_noise_sigma gyro sigma value
     * @param _extrinsic_body_imu extrinsic between body and imu
     */
    ImuPreintegrationParameters(const Scalar _acc_noise_sigma = 1e-5, const Scalar _gyro_noise_sigma = 1e-5,
                                const Pose3Type& _extrinsic_body_imu = Pose3Type())
      : ImuPreintegrationParameters(Vector3Type::Constant(_acc_noise_sigma), Vector3Type::Constant(_gyro_noise_sigma),
                                    _extrinsic_body_imu)
    {
    }

    /**
     * @brief constructor
     *
     * @param acc_noise_sigmas accelerometer sigmas in three axix
     * @param gyro_noise_sigmas gyro sigmas in three axis
     * @param extrinsic_body_imu extrinsic between body and imu
     */
    ImuPreintegrationParameters(const Vector3Type& acc_noise_sigmas, const Vector3Type& gyro_noise_sigmas,
                                const Pose3Type& extrinsic_body_imu = Pose3Type())
      : acc_noise_sigmas_(acc_noise_sigmas)
      , gyro_noise_sigmas_(gyro_noise_sigmas)
      , extrinsic_body_imu_(extrinsic_body_imu)
      , integration_uncertainty_(1e-8)
      , frequency_(100.0)
      , gravity_(9.81)
    {
    }

    /**
     * @brief Get the Acc Noise Sigmas object
     *
     * @return Vector3Type
     */
    Vector3Type GetAccNoiseSigmas() const
    {
        return acc_noise_sigmas_;
    }

    /**
     * @brief Set the Acc Noise Sigmas object
     *
     * @param acc_noise_sigmas
     */
    void SetAccNoiseSigmas(const Vector3Type& acc_noise_sigmas)
    {
        acc_noise_sigmas_ = acc_noise_sigmas;
    }

    /**
     * @brief Get the Gyro Noise Sigmas object
     *
     * @return Vector3Type
     */
    Vector3Type GetGyroNoiseSigmas() const
    {
        return gyro_noise_sigmas_;
    }

    /**
     * @brief Set the Gyro Noise Sigma object
     *
     * @param gyro_noise_sigmas
     */
    void SetGyroNoiseSigmas(const Vector3Type& gyro_noise_sigmas)
    {
        gyro_noise_sigmas_ = gyro_noise_sigmas;
    }

    /**
     * @brief Get the Extrinsic Body Imu object
     *
     * @return const Pose3Type&
     */
    const Pose3Type& GetExtrinsicBodyImu() const
    {
        return extrinsic_body_imu_;
    }

    /**
     * @brief Set the Extrinsic Body Imu object
     *
     * @param extrinsic_body_imu
     */
    void SetExtrinsicBodyImu(const Pose3Type& extrinsic_body_imu)
    {
        extrinsic_body_imu_ = extrinsic_body_imu;
    }

    /**
     * @brief Get the Integration Uncertainty object
     *
     * @return Scalar
     */
    Scalar GetIntegrationUncertainty() const
    {
        return integration_uncertainty_;
    }

    /**
     * @brief Set the Integration Uncertainty object
     *
     * @param integration_uncertainty
     */
    void SetIntegrationUncertainty(const Scalar integration_uncertainty)
    {
        integration_uncertainty_ = integration_uncertainty;
    }

    /**
     * @brief Get the Frequency object
     *
     * @return Scalar
     */
    Scalar GetFrequency() const
    {
        return frequency_;
    }

    /**
     * @brief Set the Frequency object
     *
     * @param frequency
     */
    void SetFrequency(const Scalar frequency)
    {
        frequency_ = frequency;
    }

    /**
     * @brief Get the Gravity object
     *
     * @return const Scalar
     */
    Scalar GetGravity() const
    {
        return gravity_;
    }

    /**
     * @brief Set the Gravity object
     *
     * @param gravity
     */
    void SetGravity(const Scalar gravity)
    {
        gravity_ = gravity;
    }

    /**
     * @brief load from yaml
     */
    static ImuPreintegrationParameters LoadFromYaml(const holo::yaml::Node& node)
    {
        Vector3Type acc_noise_sigmas;
        {
            acc_noise_sigmas[0u] = node["imu_acc_noise_sigmas"][0u].as<Scalar>(1e-5);
            acc_noise_sigmas[1u] = node["imu_acc_noise_sigmas"][1u].as<Scalar>(1e-5);
            acc_noise_sigmas[2u] = node["imu_acc_noise_sigmas"][2u].as<Scalar>(1e-5);
        }
        Vector3Type gyro_noise_sigmas;
        {
            gyro_noise_sigmas[0u] = node["imu_gyro_noise_sigmas"][0u].as<Scalar>(1e-5);
            gyro_noise_sigmas[1u] = node["imu_gyro_noise_sigmas"][1u].as<Scalar>(1e-5);
            gyro_noise_sigmas[2u] = node["imu_gyro_noise_sigmas"][2u].as<Scalar>(1e-5);
        }
        const Scalar yaw_body_imu = node["yaw_body_imu"].as<Scalar>(0.0);

        /// print the paramters
        // LOG(INFO) << "IMU accelerometer noise sigmas = " << acc_noise_sigmas.Transpose();
        // LOG(INFO) << "IMU gyroscope noise sigmas = " << gyro_noise_sigmas.Transpose();
        // LOG(INFO) << "the yaw angle of imu in body frame = " << yaw_body_imu;
        return ImuPreintegrationParameters(acc_noise_sigmas, gyro_noise_sigmas,
                                           Pose3Type(Rot3Type::Rz(holo::geometry::Radian(yaw_body_imu)), Point3Type()));
    }

private:
    /**
     * @brief noise sigmas for acc (ax, ay, az)
     */
    Vector3Type acc_noise_sigmas_;

    /**
     * @brief noise sigmas for gyro (wx, wy, wz)
     */
    Vector3Type gyro_noise_sigmas_;

    /**
     * @brief extrinsic between body and imu coordinate, transform imu to body
     */
    Pose3Type extrinsic_body_imu_;

    /**
     * @brief uncertainty of integration, 1e-8 by default
     */
    Scalar integration_uncertainty_;

    /**
     * @brief frequency of imu in hz
     */
    Scalar frequency_;

    /**
     * @brief gravity magnitude (unit: m/s^2)
     *
     */
    Scalar gravity_;

};  // struct ImuPreintegrationParameters

/**
 * \brief Imu Preintegration Measurement template class
 *
 * It accumulated (integrates) the Imu measurements (rotation rates and
 * accelerations) and the corresponding covariance matrix.
 * The measurements are then used to build the Preintegrated Imu factor.
 * Integration is done incrementally (ideally, one integrates the measurement)
 * at time of factor construction.
 */
class ImuPreintegrationMeasurement
{
public:
    using Parameters = ImuPreintegrationParameters;
    using Ptr        = std::shared_ptr<ImuPreintegrationMeasurement>;
    using ConstPtr   = std::shared_ptr<const ImuPreintegrationMeasurement>;

    /// @brief constructor
    /// @param[in] params the configuration of imu preintegration
    /// @param[in] imu_bias acceleration and gyro bias used for preintegration
    ImuPreintegrationMeasurement(const Parameters& params = Parameters(), const ImuBiasType& imu_bias = ImuBiasType());

    /// @brief constructor
    /// @param[in] params the configuration of imu preintegration
    /// @param[in] imus a bunch of imu measurements
    /// @param[in] imu_bias acceleration and gyro bias used for preintegration
    ImuPreintegrationMeasurement(const Parameters& params, const std::vector<ImuType>& imus,
                                 const ImuBiasType& imu_bias);

    /// @brief destructor
    ~ImuPreintegrationMeasurement() noexcept;

    // movable
    ImuPreintegrationMeasurement(ImuPreintegrationMeasurement&& measurement);
    ImuPreintegrationMeasurement& operator=(ImuPreintegrationMeasurement&& measurement);

    // copyable
    ImuPreintegrationMeasurement(const ImuPreintegrationMeasurement& measurement);
    ImuPreintegrationMeasurement& operator=(const ImuPreintegrationMeasurement& measurement);

    /// @brief get time interval
    /// @return time interval
    Scalar GetDeltaTime() const;

    /// @brief get preintegrated navigation state, as a 9D vector on tangent
    /// space at front frame. Order is: theta, position, velocity
    /// @return preintegrated navigation state
    Vector9Type GetPreintegratedNavstate() const;

    /**
     * @brief Get the Preintegrated Jacobian Bias Acc object
     *
     * @return Matrix93Type jacobian matrix(9x3) of imu preintegrated measurement w.r.t. acelerometer bias.
     */
    Matrix93Type GetPreintegratedJacobianBiasAcc() const;

    /**
     * @brief Get the Preintegrated Jacobian Bias Gyro object
     *
     * @return Matrix93Type jacobian matrix(9x3) of imu preintegrated measurement w.r.t. gyroscope bias.
     */
    Matrix93Type GetPreintegratedJacobianBiasGyro() const;

    /**
     * @brief Get the Preintegrated Measurement Covariance object
     *
     * @return Matrix99Type covariance matrix of imu preintegrated measurement.
     */
    Matrix99Type GetPreintegratedMeasurementCovariance() const;

    /**
     * @brief Get the Start Time object
     *
     * @return const Timestamp&
     */
    const Timestamp& GetStartTime() const;

    /**
     * @brief Get the End Time object
     *
     * @return const Timestamp&
     */
    const Timestamp& GetEndTime() const;

    /**
     * @brief Get the Parameters object
     *
     * @return const Parameters&
     */
    const Parameters& GetParameters() const;

    /**
     * @brief Get the Imu Bias object
     *
     * @return const ImuBiasType&
     */
    const ImuBiasType& GetImuBias() const;

    /// @brief predict state at current frame
    /// @param[in] navstate previous navstate used for preintegration
    /// @param[in] imu_bias acceleration and gyro bias used for preintegration
    /// @return current navstate which predicted
    /// @TODO(lichao@holomatic.com)
    /// 1. define a pure virtual interface which named Measurement in
    /// Navstate, then use it to update Navstate.
    /// 2. move this Predict function to Navstate.
    NavstateType Predict(const NavstateType& navstate, const ImuBiasType& imu_bias) const;

    /// @brief compute error w.r.t. preintegrated measurements and jacobian wrt pose_i
    /// @param[in] previous previous navstate used for prediction
    /// @param[in] next next navstate used for error computation
    /// @param[in] imu_bias acceleration and gyro bias used for preintegration
    /// @param[out] jacobian_pose_i jacobian wrt pose_i
    /// @return residual error w.r.t. preintegrated measurements
    Vector9Type ComputeErrorAndJacobians(const NavstateType& previous, const NavstateType& next,
                                         const ImuBiasType& imu_bias, Matrix96Type& jacobian_pose_i) const;

    /// @brief add a single Imu measurement to the preintegration.
    /// @param[in] acc measured acceleration (in body frame)
    /// @param[in] gyro measured angular velocity
    /// @param[in] dt time interval between this and the last imu measurement
    void IntegrateMeasurement(const Vector3Type& acc, const Vector3Type& gyro, const Scalar dt);

private:
    /// PIMPL (Pointer to Implementation).
    /// More detailed information. please refer to
    /// https://en.cppreference.com/w/cpp/language/pimpl
    class Implement;
    std::unique_ptr<Implement> impl_;

    Timestamp start_time_;  ///< start time of imu preintegration measurement
    Timestamp end_time_;    ///< end time of imu preintegration measurement

    Parameters  params_;    ///< the parameters of imu preintegration measurement
    ImuBiasType imu_bias_;  ///< the imu bias of imu preintegration measurement

};  // class ImuPreintegrationMeasurement

/******************************************************************************
 * This class has the functional interfaces for imu preintegration. It can take
 * a set of Imu measurements for preintegration work and outputs specific
 * preintegration measurement or a predicted navstate from a initial navstate.
 *****************************************************************************/
class ImuPreintegration
{
public:
    using Ptr      = std::shared_ptr<ImuPreintegration>;
    using ConstPtr = std::shared_ptr<const ImuPreintegration>;

    using Parameters     = ImuPreintegrationParameters;
    using Measurement    = ImuPreintegrationMeasurement;
    using MeasurementPtr = typename Measurement::Ptr;

    /* constructor */
    ImuPreintegration(const Parameters& params);

    /* destructor */
    virtual ~ImuPreintegration() noexcept;

    /**
     * @brief imu preintegration by preintgrated a set of imus with imu bias
     *
     * @param imus imu measurements
     * @param imu_bias imu bias used in preintegration
     *
     * @return imu preintegration ptr
     */
    MeasurementPtr Preintegrate(const std::vector<ImuType>& imus, const ImuBiasType& imu_bias) const;

    /**
     * @brief Predict navstate by integrating imu measurements to initial navstate
     *
     * @param input initial navstate
     * @param imus imu measurements
     * @param imu_bias imu bias used in preintegration
     * @param output predicted navstate
     */
    void Predict(const NavstateType& input, const std::vector<ImuType>& imus, const ImuBiasType& imu_bias,
                 NavstateType& output) const;

    /**
     * @brief Predict navstate integrate imu preintegration measurements with initial navstate.
     *
     * @param input initial navstate
     * @param measurement imu preintegration measurement
     * @param output predicted navstate
     */
    void Predict(const NavstateType& input, const Measurement& measurement, const ImuBiasType& imu_bias,
                 NavstateType& output) const;

    /**
     * @brief get configuration of imu preintegration
     *
     * @return the configuration of imu preintegration
     */
    const Parameters& GetParameters() const
    {
        return params_;
    }

private:
    /**
     * @brief parameters
     */
    const Parameters params_;

};  // class ImuPreintegration

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_IMU_PREINTEGRATION
