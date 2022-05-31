/*!
 * @file imu_preintegration.cpp
 * @brief the implementation of imu preintegration class
 * @author lichao@holomatic.com
 * @date Oct 07, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/navigation/NavState.h>

#include <holo/localization/common/imu_preintegration.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace localization
{
using PreintegrationType           = gtsam::PreintegrationType;
using ConstantBias                 = gtsam::imuBias::ConstantBias;
using PreintegratedImuMeasurements = gtsam::PreintegratedImuMeasurements;

/******************************************************************************/
/**
 * \brief Implementation of Imu Preintegration Measurement
 */
class ImuPreintegrationMeasurement::Implement
{
public:
    /// @brief constructor
    /// @param[in] params the configuration of imu preintegration
    /// @param[in] imu_bias acceleration and gyro bias used for preintegration
    Implement(const Parameters& params, const ImuBiasType& imu_bias)
    {
        // PreintegrationBase params
        boost::shared_ptr<PreintegratedImuMeasurements::Params> preint_param =
            PreintegratedImuMeasurements::Params::MakeSharedU(params.GetGravity());
        preint_param->setBodyPSensor(
            gtsam::Pose3(ConvertMatrix<Scalar, 4, 4>(params.GetExtrinsicBodyImu().ToMatrix())));
        // ENU navigation frame, gravity vector default is -9.81 m/s^2
        // acc white noise in continuous
        preint_param->accelerometerCovariance =
            ConvertMatrix<Scalar, 3, 3>(params.GetAccNoiseSigmas().CwiseSquare().AsDiagonal());
        // gyro white noise in continuous
        preint_param->gyroscopeCovariance =
            ConvertMatrix<Scalar, 3, 3>(params.GetGyroNoiseSigmas().CwiseSquare().AsDiagonal());
        // integration uncertainty continuous
        // TODO: hard code 1e-8 (@lichao)
        preint_param->integrationCovariance =
            ConvertMatrix<Scalar, 3, 3>((Scalar)params.GetIntegrationUncertainty() * Matrix3Type::Identity());

        /* convert holo::ImuBias to gtsam::ConstantBias */
        ConstantBias imubias(
            ConvertMatrix<ImuBiasType::ScalarType, 3, 1>(imu_bias.GetLinearAccelerationBias<Vector3Type>()),
            ConvertMatrix<ImuBiasType::ScalarType, 3, 1>(imu_bias.GetAngularVelocityBias<Vector3Type>()));
        pim_ = PreintegratedImuMeasurements(preint_param, imubias);
    }

    /// @brief get time interval
    /// @return time interval
    Scalar GetDeltaTime() const
    {
        return pim_.deltaTij();
    }

    /// @brief get preintegrated navigation state, as a 9D vector on tangent
    /// space at front frame. Order is: theta, position, velocity
    /// @return preintegrated navigation state
    Vector9Type GetPreintegratedNavstate() const
    {
        return ConvertToHoloMatrix<Scalar, 9, 1>(pim_.preintegrated());
    }

    /**
     * @brief Get the Preintegrated Jacobian Bias Acc object
     *
     * @return Matrix93Type
     */
    Matrix93Type GetPreintegratedJacobianBiasAcc() const
    {
        return ConvertToHoloMatrix<Scalar, 9, 3>(pim_.preintegrated_H_biasAcc());
    }

    /**
     * @brief Get the Preintegrated Jacobian Bias Gyro object
     *
     * @return Matrix93Type
     */
    Matrix93Type GetPreintegratedJacobianBiasGyro() const
    {
        return ConvertToHoloMatrix<Scalar, 9, 3>(pim_.preintegrated_H_biasOmega());
    }

    /**
     * @brief Get the Preintegrated Measurement Covariance object
     *
     * @return Matrix99Type
     */
    Matrix99Type GetPreintegratedMeasurementCovariance() const
    {
        return ConvertToHoloMatrix<Scalar, 9, 9>(pim_.preintMeasCov());
    }

    /// @brief predict state at current frame
    /// @param[in] navstate previous navstate used for preintegration
    /// @param[in] imu_bias acceleration and gyro bias used for preintegration
    /// @return current navstate which predicted
    NavstateType Predict(const NavstateType& navstate, const ImuBiasType& imu_bias)
    {
        NavstateType       result;
        const ConstantBias imubias(
            ConvertMatrix<ImuBiasType::ScalarType, 3, 1>(imu_bias.GetLinearAccelerationBias<Vector3Type>()),
            ConvertMatrix<ImuBiasType::ScalarType, 3, 1>(imu_bias.GetAngularVelocityBias<Vector3Type>()));
        // convert holo::Navstate to gtsam::Navstate
        const gtsam::NavState previous(
            gtsam::Pose3(ConvertMatrix<NavstateType::ScalarType, 4, 4>(navstate.GetPose().ToMatrix())),
            ConvertMatrix<NavstateType::ScalarType, 3, 1>(navstate.GetVelocity()));
        const gtsam::NavState current = pim_.predict(previous, imubias);
        auto                  mat     = ConvertToHoloMatrix<float64_t, 4, 4>(current.pose().matrix());
        result.SetPose(Pose3d(mat));
        result.SetVelocity(ConvertToHoloMatrix<NavstateType::ScalarType, 3, 1>(current.velocity()));
        return result;
    }

    /// @brief compute error w.r.t. preintegrated measurements and jacobian wrt pose_i
    /// @param[in] previous previous navstate used for prediction
    /// @param[in] next next navstate used for error computation
    /// @param[in] imu_bias acceleration and gyro bias used for preintegration
    /// @param[out] jacobian_pose_i jacobian wrt pose_i
    /// @return residual error w.r.t. preintegrated measurements
    Vector9Type ComputeErrorAndJacobians(const NavstateType& previous, const NavstateType& next,
                                         const ImuBiasType& imu_bias, Matrix96Type& jacobian_pose_i) const
    {
        const ConstantBias imubias(
            ConvertMatrix<ImuBiasType::ScalarType, 3, 1>(imu_bias.GetLinearAccelerationBias<Vector3Type>()),
            ConvertMatrix<ImuBiasType::ScalarType, 3, 1>(imu_bias.GetAngularVelocityBias<Vector3Type>()));

        // convert holo::Pose to gtsam::Pose
        const gtsam::Pose3 previous_pose(ConvertMatrix<NavstateType::ScalarType, 4, 4>(previous.GetPose().ToMatrix()));
        const gtsam::Pose3 current_pose(ConvertMatrix<NavstateType::ScalarType, 4, 4>(next.GetPose().ToMatrix()));

        gtsam::Matrix96 jacobian_gtsam;
        gtsam::Vector9  error_gtsam = pim_.computeErrorAndJacobians(
            previous_pose, ConvertMatrix<NavstateType::ScalarType, 3, 1>(previous.GetVelocity()), current_pose,
            ConvertMatrix<NavstateType::ScalarType, 3, 1>(next.GetVelocity()), imubias, jacobian_gtsam);
        jacobian_pose_i = ConvertToHoloMatrix<Scalar, 9, 6>(jacobian_gtsam);
        return ConvertToHoloMatrix<Scalar, 9, 1>(error_gtsam);
    }

    /// @brief add a single Imu measurement to the preintegration.
    /// @param[in] acc measured acceleration (in body frame)
    /// @param[in] gyro measured angular velocity
    /// @param[in] dt time interval between this and the last imu measurement
    void IntegrateMeasurement(const Vector3Type& acc, const Vector3Type& gyro, const Scalar dt)
    {
        pim_.integrateMeasurement(gtsam::Vector3(acc(0), acc(1), acc(2)), gtsam::Vector3(gyro(0), gyro(1), gyro(2)),
                                  dt);
    }

private:
    template <typename InScalar, uint8_t RowValue, uint8_t ColValue>
    Eigen::Matrix<float64_t, RowValue, ColValue>
    ConvertMatrix(holo::numerics::MatrixT<InScalar, RowValue, ColValue> mat) const
    {
        const uint32_t array_size = mat.GetCols() * mat.GetRows();

        Eigen::Matrix<InScalar, RowValue, ColValue> tmp;
        (void)memcpy(tmp.data(), mat.GetData(), sizeof(InScalar) * array_size);
        Eigen::Matrix<float64_t, RowValue, ColValue> result = tmp.template cast<float64_t>();
        return result;
    }

    template <typename OutScalar, uint8_t RowValue, uint8_t ColValue>
    holo::numerics::MatrixT<OutScalar, RowValue, ColValue>
    ConvertToHoloMatrix(Eigen::Matrix<float64_t, RowValue, ColValue> mat) const
    {
        uint32_t array_size = mat.cols() * mat.rows();

        Eigen::Matrix<OutScalar, RowValue, ColValue> tmp = mat.template cast<OutScalar>();
        holo::numerics::MatrixT<OutScalar, RowValue, ColValue> result;
        (void)memcpy(result.GetData(), tmp.data(), sizeof(OutScalar) * array_size);
        return result;
    }

    /// gtsam imu preintegration measurement
    PreintegratedImuMeasurements pim_;

};  // class ImuPreintegrationMeasurement::Implement

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// the implementations of Measurement
ImuPreintegrationMeasurement::ImuPreintegrationMeasurement(const Parameters& params, const ImuBiasType& imu_bias)
  : impl_(new Implement(params, imu_bias)), start_time_(0, 0), end_time_(0, 0), params_(params), imu_bias_(imu_bias)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// the implementations of Measurement
ImuPreintegrationMeasurement::ImuPreintegrationMeasurement(const Parameters& params, const std::vector<ImuType>& imus,
                                                           const ImuBiasType& imu_bias)
  : ImuPreintegrationMeasurement(params, imu_bias)
{
    // DLOG(INFO) << "imu preintegrate";
    // DLOG(INFO) << "imu set size: " << imus.size();
    typename std::vector<ImuType>::const_iterator it     = imus.begin();
    typename std::vector<ImuType>::const_iterator itnext = it;
    itnext++;

    for (; itnext != imus.end(); it = itnext, itnext++)
    {
        /* midpoint integration */
        Duration    sample_time = itnext->GetTimestamp() - it->GetTimestamp();
        Vector3Type mid_acc =
            Scalar(0.5) * (it->GetLinearAcceleration<Vector3Type>() + itnext->GetLinearAcceleration<Vector3Type>());
        Vector3Type mid_gyr =
            Scalar(0.5) * (it->GetAngularVelocity<Vector3Type>() + itnext->GetAngularVelocity<Vector3Type>());
        // DLOG(INFO) << "front stamp: " << it->GetTimestamp() << "\t rear stamp: " << itnext->GetTimestamp()
        //            << "\n\t acc: " << mid_acc.Transpose() << "\t gyro: " << mid_gyr.Transpose()
        //            << "\t sample time: " << (sample_time).ToSec();

        impl_->IntegrateMeasurement(mid_acc, mid_gyr, (sample_time).ToSec());
    }

    (void)impl_->GetPreintegratedNavstate();
    // DLOG(INFO) << "imu preint deltaT: " << impl_->GetDeltaTime();
    // DLOG(INFO) << "imu preint measure: "
    //           << "Theta: " << measure.GetSegment(0, 3).Transpose()
    //           << "\tPosition: " << measure.GetSegment(3, 3).Transpose()
    //           << "\tVelocity: " << measure.GetSegment(6, 3).Transpose();

    /* set start and end time */
    if (!imus.empty())
    {
        start_time_ = imus.front().GetTimestamp();
        end_time_   = imus.back().GetTimestamp();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImuPreintegrationMeasurement::~ImuPreintegrationMeasurement() = default;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImuPreintegrationMeasurement::ImuPreintegrationMeasurement(ImuPreintegrationMeasurement&&) = default;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImuPreintegrationMeasurement& ImuPreintegrationMeasurement::
                              operator=(ImuPreintegrationMeasurement&& measurement) = default;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImuPreintegrationMeasurement::ImuPreintegrationMeasurement(const ImuPreintegrationMeasurement& measurement)
  : impl_(new Implement(*measurement.impl_))
  , start_time_(measurement.start_time_)
  , end_time_(measurement.end_time_)
  , params_(measurement.params_)
  , imu_bias_(measurement.imu_bias_)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImuPreintegrationMeasurement& ImuPreintegrationMeasurement::operator=(const ImuPreintegrationMeasurement& measurement)
{
    if (this != &measurement)
    {
        this->impl_.reset(new Implement(*measurement.impl_));
        this->start_time_ = measurement.start_time_;
        this->end_time_   = measurement.end_time_;
        this->params_     = measurement.params_;
        this->imu_bias_   = measurement.imu_bias_;
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scalar ImuPreintegrationMeasurement::GetDeltaTime() const
{
    return impl_->GetDeltaTime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector9Type ImuPreintegrationMeasurement::GetPreintegratedNavstate() const
{
    return impl_->GetPreintegratedNavstate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Matrix93Type ImuPreintegrationMeasurement::GetPreintegratedJacobianBiasAcc() const
{
    return impl_->GetPreintegratedJacobianBiasAcc();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Matrix93Type ImuPreintegrationMeasurement::GetPreintegratedJacobianBiasGyro() const
{
    return impl_->GetPreintegratedJacobianBiasGyro();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Matrix99Type ImuPreintegrationMeasurement::GetPreintegratedMeasurementCovariance() const
{
    return impl_->GetPreintegratedMeasurementCovariance();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Timestamp& ImuPreintegrationMeasurement::GetStartTime() const
{
    return start_time_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Timestamp& ImuPreintegrationMeasurement::GetEndTime() const
{
    return end_time_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ImuPreintegrationParameters& ImuPreintegrationMeasurement::GetParameters() const
{
    return params_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ImuBiasType& ImuPreintegrationMeasurement::GetImuBias() const
{
    return imu_bias_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NavstateType ImuPreintegrationMeasurement::Predict(const NavstateType& navstate, const ImuBiasType& imu_bias) const
{
    return impl_->Predict(navstate, imu_bias);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector9Type ImuPreintegrationMeasurement::ComputeErrorAndJacobians(const NavstateType& previous,
                                                                   const NavstateType& next,
                                                                   const ImuBiasType&  imu_bias,
                                                                   Matrix96Type&       jacobian_pose_i) const
{
    return impl_->ComputeErrorAndJacobians(previous, next, imu_bias, jacobian_pose_i);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImuPreintegrationMeasurement::IntegrateMeasurement(const Vector3Type& acc, const Vector3Type& gyro,
                                                        const Scalar dt)
{
    impl_->IntegrateMeasurement(acc, gyro, dt);

    /* accumulate end time */
    end_time_ += Duration(dt);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// the implementations of ImuPreintegration
ImuPreintegration::ImuPreintegration(const Parameters& params) : params_(params)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImuPreintegration::~ImuPreintegration()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImuPreintegration::MeasurementPtr ImuPreintegration::Preintegrate(const std::vector<ImuType>& imus,
                                                                  const ImuBiasType&          imu_bias) const
{
    // create a pim pointer and return
    return MeasurementPtr(new Measurement(params_, imus, imu_bias));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImuPreintegration::Predict(const NavstateType& input, const std::vector<ImuType>& imus,
                                const ImuBiasType& imu_bias, NavstateType& output) const
{
    MeasurementPtr pim(new Measurement(params_, imus, imu_bias));

    output = pim->Predict(input, imu_bias);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImuPreintegration::Predict(const NavstateType& input, const Measurement& measurement, const ImuBiasType& imu_bias,
                                NavstateType& output) const
{
    output = measurement.Predict(input, imu_bias);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace localization

}  // namespace holo
