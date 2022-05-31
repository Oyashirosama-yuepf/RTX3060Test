/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file imu_accumulator.h
 * @brief This file is used to define the ImuAccumulator class which is to accumulate IMU measurements one-axis by one
 * axis.
 * @author Lei Gehang(leigehang@holomatic.com)
 * @date Feb 19, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_IMU_ACCUMULATOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_IMU_ACCUMULATOR_H_

#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/localization/tightly_coupled_fusion/utils/fixed_size_accumulator.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup utils
 * @{
 *
 */

/**
 * @brief This class inherites from the ImuT to add the support for some operators and math functions.
 * @details The supported operators and math functions include +, +=, /(Scalar), -, *, and std::sqrt().
 *
 * @tparam T The precision type. float64 or float32.
 */
template <typename T>
class AdvancedImuT : public holo::common::details::ImuT<T>
{
public:
    using ImuType = holo::common::details::ImuT<T>;

    /**
     * @brief Construct a new AdvancedImu from the ImuType
     *
     * @param[in] imu The Imu type
     */
    AdvancedImuT(ImuType const& imu) : ImuType(imu)
    {
    }

    /**
     * @brief The Constructor.
     *
     * @param[in] acc_value The Scalar value to initialize the acceleration
     * @param[in] gyro_value The Scalar value to initialize the angular velocity
     */
    AdvancedImuT(Scalar acc_value = 0.0, Scalar gyro_value = 0.0) : ImuType()
    {
        this->SetLinearAcceleration(acc_value, acc_value, acc_value);
        this->SetAngularVelocity(gyro_value, gyro_value, gyro_value);
    }

    /**
     * @brief The operator+ overloading for the AdvancedImuT type.
     *
     * @param[in] lhs The left hand side element.
     * @param[in] rhs The right hand side element.
     * @return The result of the operator +.
     */
    friend AdvancedImuT operator+(AdvancedImuT const& lhs, AdvancedImuT const& rhs)
    {
        AdvancedImuT result;

        result.SetAngularVelocity(lhs.template GetAngularVelocity<Point3Type>() +
                                  rhs.template GetAngularVelocity<Point3Type>());
        result.SetLinearAcceleration(lhs.template GetLinearAcceleration<Point3Type>() +
                                     rhs.template GetLinearAcceleration<Point3Type>());

        return result;
    }

    /**
     * @brief The operator+= overloading for the AdvancedImuT type.
     *
     * @param[in] rhs THe right hand side element.
     * @return The result of the operator +=.
     */
    AdvancedImuT& operator+=(AdvancedImuT const& rhs)
    {
        this->SetAngularVelocity((*this).template GetAngularVelocity<Point3Type>() +
                                 rhs.template GetAngularVelocity<Point3Type>());
        this->SetLinearAcceleration((*this).template GetLinearAcceleration<Point3Type>() +
                                    rhs.template GetLinearAcceleration<Point3Type>());

        return *this;
    }

    /**
     * @brief The operator- overloading for the AdvancedImuT type.
     *
     * @param[in] lhs The left hand side element.
     * @param[in] rhs The right hand side element.
     * @return The result of the operator -.
     */
    friend AdvancedImuT operator-(AdvancedImuT const& lhs, AdvancedImuT const& rhs)
    {
        AdvancedImuT result;

        result.SetAngularVelocity(lhs.template GetAngularVelocity<Point3Type>() -
                                  rhs.template GetAngularVelocity<Point3Type>());
        result.SetLinearAcceleration(lhs.template GetLinearAcceleration<Point3Type>() -
                                     rhs.template GetLinearAcceleration<Point3Type>());

        return result;
    }

    /**
     * @brief The operator- overloading for the AdvancedImuT type.
     *
     * @return The result of the operator -.
     */
    AdvancedImuT operator-()
    {
        AdvancedImuT result;

        result.SetAngularVelocity((*this).template GetAngularVelocity<Point3Type>() * (-1.0));
        result.SetLinearAcceleration((*this).template GetLinearAcceleration<Point3Type>() * (-1.0));

        return result;
    }

    /**
     * @brief The operator/ overloading for the AdvancedImuT type.
     *
     * @param[in] lhs The left hand side element.
     * @param[in] scalar_value The scalar value.
     * @return The result of the operator /
     */
    friend AdvancedImuT operator/(AdvancedImuT const& lhs, Scalar scalar_value)
    {
        AdvancedImuT result;

        result.SetAngularVelocity(lhs.template GetAngularVelocity<Point3Type>() / scalar_value);
        result.SetLinearAcceleration(lhs.template GetLinearAcceleration<Point3Type>() / scalar_value);

        return result;
    }

    /**
     * @brief The operator* overloading for the AdvancedImuT type.
     *
     * @param[in] lhs The left hand side element.
     * @param[in] scalar_value The scalar value.
     * @return The result of the operator *
     */
    friend AdvancedImuT operator*(AdvancedImuT const& lhs, Scalar const scalar_value)
    {
        AdvancedImuT result;

        result.SetAngularVelocity(lhs.template GetAngularVelocity<Point3Type>() * scalar_value);
        result.SetLinearAcceleration(lhs.template GetLinearAcceleration<Point3Type>() * scalar_value);

        return result;
    }

    /**
     * @brief The operator* overloading for the AdvancedImuT type.
     *
     * @param[in] scalar_value The scalar value.
     * @param[in] rhs The right hand side element.
     * @return The result of the operator *
     */
    friend AdvancedImuT operator*(Scalar const scalar_value, AdvancedImuT const& rhs)
    {
        AdvancedImuT result;

        result.SetAngularVelocity(rhs.template GetAngularVelocity<Point3Type>() * scalar_value);
        result.SetLinearAcceleration(rhs.template GetLinearAcceleration<Point3Type>() * scalar_value);

        return result;
    }

    /**
     * @brief The operator* overloading for the AdvancedImuT type.
     *
     * @param[in] lhs The left hand side element.
     * @param[in] rhs The right hand side element.
     * @return The result of the operator *
     */
    friend AdvancedImuT operator*(AdvancedImuT const& lhs, AdvancedImuT const& rhs)
    {
        AdvancedImuT result;

        Point3Type const left_angular_velocity  = lhs.template GetAngularVelocity<Point3Type>();
        Point3Type const left_acceleration      = lhs.template GetLinearAcceleration<Point3Type>();
        Point3Type const right_angular_velocity = rhs.template GetAngularVelocity<Point3Type>();
        Point3Type const right_acceleration     = rhs.template GetLinearAcceleration<Point3Type>();

        result.SetAngularVelocity(left_angular_velocity.GetX() * right_angular_velocity.GetX(),
                                  left_angular_velocity.GetY() * right_angular_velocity.GetY(),
                                  left_angular_velocity.GetZ() * right_angular_velocity.GetZ());
        result.SetLinearAcceleration(left_acceleration.GetX() * right_acceleration.GetX(),
                                     left_acceleration.GetY() * right_acceleration.GetY(),
                                     left_acceleration.GetZ() * right_acceleration.GetZ());

        return result;
    }

    /**
     * @brief The sqrt functions overloading for the AdvancedImuT type.
     *
     * @param[in] imu The AdvancedImuT type
     * @return The sqrted AdvancedImuT
     */
    AdvancedImuT Sqrt() const
    {
        AdvancedImuT result;

        Point3Type const angular_velocity = (*this).template GetAngularVelocity<Point3Type>();
        Point3Type const acceleration     = (*this).template GetLinearAcceleration<Point3Type>();

        result.SetAngularVelocity(std::sqrt(angular_velocity.GetX()), std::sqrt(angular_velocity.GetY()),
                                  std::sqrt(angular_velocity.GetZ()));
        result.SetLinearAcceleration(std::sqrt(acceleration.GetX()), std::sqrt(acceleration.GetY()),
                                     std::sqrt(acceleration.GetZ()));

        return result;
    }
};

/**
 * @brief The parameters of the IMU bias estimator.
 *
 */
struct ImuAccumulatorParameters
{
    /// The max delay time between two IMU. For detecting delay or IMU loss.
    Scalar max_delay_time_for_imu = Scalar(0.1);  ///< Unit: s

    /**
     * @brief The max norm for the acceptable and normal IMU measurements. If the actual value is over them, we
     * think the IMU measurements is abnormal and need to be rejected.
     * @details
     *  1. Max norm for the 3-axis angular velocioty. Unit: rad/s.
     *  2. Max norm for the 3-axis acceleration. Unit: m/s^2.
     */
    Scalar max_norm_for_angular_velocity = Scalar(holo::geometry::Radian(2.0));
    Scalar max_norm_for_acceleration     = Scalar(9.81 * 1.1);

    /**
     * @brief Output stream overloading for ImuBiasEstimator's parameter
     *
     * @param[in] os std::ostream&
     * @param[in] parameters Parameters
     * @return std::ostream& contains content of the given parameters
     */
    friend std::ostream& operator<<(std::ostream& os, ImuAccumulatorParameters const& parameters)
    {
        os << "ImuAccumulator: \n"
           << "max_delay_time_for_imu = " << parameters.max_delay_time_for_imu << "\n"
           << "max_norm_for_angular_velocity = " << parameters.max_norm_for_angular_velocity << "\n"
           << "max_norm_for_acceleration = " << parameters.max_norm_for_acceleration << std::endl;
        return os;
    }

    /**
     * @brief Static method to load parameters from yaml
     *
     * @param[in] node Yaml node
     * @return the loaded parameters
     */
    static ImuAccumulatorParameters LoadFromYaml(holo::yaml::Node const& node)
    {
        ImuAccumulatorParameters params;

        try
        {
            params.max_delay_time_for_imu = node["max_delay_time_for_imu"].as<Scalar>(params.max_delay_time_for_imu);
            params.max_norm_for_angular_velocity =
                node["max_norm_for_angular_velocity"].as<Scalar>(params.max_norm_for_angular_velocity);
            params.max_norm_for_acceleration =
                node["max_norm_for_acceleration"].as<Scalar>(params.max_norm_for_acceleration);
        }
        catch (std::exception const& e)
        {
            LOG(WARNING) << "ImuAccumulator --> Can not loading parameters from yaml file. The exception "
                            "information is: "
                         << e.what();
        }

        return params;
    }
};

/**
 * @brief This class is used to accumulate IMU measurements one-axis by one-axis in a fixed window size.
 *
 * @tparam N The fixed size for IMU accmulator.
 */
template <size_t N>
class ImuAccumulator
{
public:
    /**
     * @brief The handy types definition
     *
     */
    using AdvancedImu        = AdvancedImuT<Scalar>;
    using OptionalTimestamp  = holo::OptionalT<holo::common::Timestamp>;
    using StampedVector6Type = StampedT<Vector6Type>;

    /**
     * @brief Construct a new Imu Accumulator object
     *
     * @param[in] parameters The input parameters
     */
    ImuAccumulator(ImuAccumulatorParameters const& parameters = ImuAccumulatorParameters())
      : parameters_(parameters), fixed_size_imu_accumulator_(), last_input_imu_time_(optional::none)
    {
    }

    /**
     * @brief Add IMU measurements to the accmulator.
     *
     * @param[in] imu_measurements The IMU measurements.
     */
    void Add(std::vector<ImuType> const& imu_measurements)
    {
        /// Find the first iterator, which timestamp is newer than last input imu timestamp.
        std::vector<ImuType>::const_iterator corrected_imu_start_iterator = imu_measurements.begin();
        if (imu_measurements.size() > 0 && last_input_imu_time_.IsValid())
        {
            ImuType last_input_imu_measurement;
            last_input_imu_measurement.SetTimestamp(last_input_imu_time_.GetData());

            corrected_imu_start_iterator = std::upper_bound(imu_measurements.begin(), imu_measurements.end(),
                                                            last_input_imu_measurement, StampedTimeCompareT<ImuType>());
        }

        /// Check input imu data.
        for (auto iter = corrected_imu_start_iterator; iter != imu_measurements.end(); iter++)
        {
            if (!isImuAbnormal(*iter))
            {
                if (isMeasurementLost(*iter))
                {
                    this->Reset();
                }
                fixed_size_imu_accumulator_.AddData(AdvancedImu(*iter));
                last_input_imu_time_ = OptionalTimestamp(iter->GetTimestamp());
            }
        }
    }

    /**
     * @brief Reset the IMU bias estimator to the default.
     *
     */
    void Reset()
    {
        fixed_size_imu_accumulator_.Reset();
        last_input_imu_time_ = optional::none;
    }

    /**
     * @brief Get the buffer size to display how many IMU has been added to the accumulator.
     *
     * @return The buffer size.
     */
    size_t GetBufferSize() const
    {
        return fixed_size_imu_accumulator_.GetBufferSize();
    }

    /**
     * @brief Get the mean IMU measurement.
     * @note If there is no IMU added to the accumulator, it will return the default IMU types.
     *
     * @return The mean IMU measurement. Its timestamp is the timestamp of the last added IMU.
     */
    ImuType GetMeanType() const
    {
        ImuType mean_imu;

        if (this->GetBufferSize() > 0u && last_input_imu_time_.IsValid())
        {
            AdvancedImu const advanced_imu_mean = fixed_size_imu_accumulator_.GetMean();

            mean_imu.SetTimestamp(last_input_imu_time_.GetData());
            mean_imu.SetAngularVelocity(advanced_imu_mean.GetAngularVelocity<Point3Type>());
            mean_imu.SetLinearAcceleration(advanced_imu_mean.GetLinearAcceleration<Point3Type>());
        }

        return mean_imu;
    }

    /**
     * @brief Get the mean Imu measurement.
     * @note If there is no IMU added to the accumulator, it will return the Vector6::zero with the zero timestamp.
     *
     * @return Stamped vector6 type. The 0~2 dimension is mean acceleration[x, y, z]; The 3~5 dimension is mean
     * angular velocity[x, y, z]. Its timestamp is the timestamp of the last added IMU.
     */
    StampedVector6Type GetMean() const
    {
        StampedVector6Type stamped_mean_imu;

        if (this->GetBufferSize() > 0u && last_input_imu_time_.IsValid())
        {
            AdvancedImu const advanced_imu_mean = fixed_size_imu_accumulator_.GetMean();

            stamped_mean_imu.SetTimestamp(last_input_imu_time_.GetData());
            stamped_mean_imu.GetData().SetSegment(0u, advanced_imu_mean.GetLinearAcceleration<Vector3Type>());
            stamped_mean_imu.GetData().SetSegment(3u, advanced_imu_mean.GetAngularVelocity<Vector3Type>());
        }

        return stamped_mean_imu;
    }

    /**
     * @brief Get the covariance of Imu measurement.
     * @note If there is no IMU added to the accumulator, it will return the Vector6::zero with the zero timestamp.
     *
     * @return Stamped vector6 type. The 0~2 dimension is covariance of acceleration[x, y, z]; The 3~5 dimension is
     * covariance of angular velocity[x, y, z]. Its timestamp is the timestamp of the last added IMU.
     */
    StampedVector6Type GetCovariance() const
    {
        StampedVector6Type stamped_imu_cov;

        if (this->GetBufferSize() > 0u && last_input_imu_time_.IsValid())
        {
            AdvancedImu const advanced_imu_cov = fixed_size_imu_accumulator_.GetCovariance();

            stamped_imu_cov.SetTimestamp(last_input_imu_time_.GetData());
            stamped_imu_cov.GetData().SetSegment(0u, advanced_imu_cov.GetLinearAcceleration<Vector3Type>());
            stamped_imu_cov.GetData().SetSegment(3u, advanced_imu_cov.GetAngularVelocity<Vector3Type>());
        }

        return stamped_imu_cov;
    }

    /**
     * @brief Get the stdandard deviation of Imu measurement.
     * @note If there is no IMU added to the accumulator, it will return the Vector6::zero with the zero timestamp.
     *
     * @return Stamped vector6 type. The 0~2 dimension is stdandard deviation of acceleration[x, y, z]; The 3~5
     * dimension is stdandard deviation of angular velocity[x, y, z]. Its timestamp is the timestamp of the last
     * added IMU.
     */
    StampedVector6Type GetStdandardDeviation() const
    {
        StampedVector6Type stamped_imu_stdandard_dev;

        if (this->GetBufferSize() > 0u && last_input_imu_time_.IsValid())
        {
            AdvancedImu const advanced_imu_stddev = fixed_size_imu_accumulator_.GetStdandardDeviation();

            stamped_imu_stdandard_dev.SetTimestamp(last_input_imu_time_.GetData());
            stamped_imu_stdandard_dev.GetData().SetSegment(0u,
                                                           advanced_imu_stddev.GetLinearAcceleration<Vector3Type>());
            stamped_imu_stdandard_dev.GetData().SetSegment(3u, advanced_imu_stddev.GetAngularVelocity<Vector3Type>());
        }

        return stamped_imu_stdandard_dev;
    }

protected:
    /**
     * @brief To judge whether the IMU is abnormal or inacceptable.
     *
     * @param[in] imu The IMU measurement
     * @return It returns true is the IMU is abnormal or inacceptable. Otherwise, it returns false.
     */
    bool_t isImuAbnormal(ImuType const& imu) const
    {
        /// If the angular velocity or acceleration is over the threshold, it isn't the normal imu.
        return (imu.GetAngularVelocity<Vector3Type>().GetNorm() > parameters_.max_norm_for_angular_velocity ||
                imu.GetLinearAcceleration<Vector3Type>().GetNorm() > parameters_.max_norm_for_acceleration);
    }

    /**
     * @brief To judge whether the input measuremens is lost for a long time, which means there is large time
     * difference between current input and last input.
     *
     * @param[in] imu The IMU measurement
     * @return It returns true if IMU has lost. Otherwise, it returns false.
     */
    bool_t isMeasurementLost(ImuType const& imu) const
    {
        bool is_lost = false;

        if (last_input_imu_time_.IsValid())
        {
            Scalar const time_difference = (imu.GetTimestamp() - last_input_imu_time_.GetData()).ToSec();

            if (time_difference <= Scalar(1e-9) || time_difference > parameters_.max_delay_time_for_imu)
            {
                is_lost = true;
            }
        }

        return is_lost;
    }

private:
    ImuAccumulatorParameters const parameters_;

    FixedSizeAccumulator<AdvancedImu, N> fixed_size_imu_accumulator_;  ///< The aacumulator for Imu Type
    OptionalTimestamp last_input_imu_time_;  ///< Last input IMU time. For detecting IMU loss or delay.

};  /// class ImuAccumulator

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_IMU_BIAS_ESTIMATOR_H_
