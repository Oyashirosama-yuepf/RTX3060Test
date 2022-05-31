/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_motion_state_detector.h
 * @brief This file is used to define the VehicleMotionStateDetector class which is to detect the vehicle motion state
 * such as the stationary state, the uniform speed linear motion or the variable speed linear motion and so on.
 * @note The rear wheels speed of ChassiStae must been calibrated firstly.
 * @author Lei Gehang(leigehang@holomatic.com)
 * @date Feb 19, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_VEHICLE_MOTION_STATE_DETECTOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_VEHICLE_MOTION_STATE_DETECTOR_H_

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
 * @brief This class is used to detect the vehicle motion state such as the stationary state, the uniform speed linear
 * motion or the variable speed linear motion and so on.
 *
 */
class VehicleMotionStateDetector
{
public:
    /**
     * @brief The handy types definition
     *
     */
    /// The size is hard code, it can be adjusted after testing.
    static std::size_t constexpr kSpeedBufferFixedSize = 100u;

    using Timestamp = holo::common::Timestamp;
    /// The fixed size accumulator of speed value for computing covariance and mean.
    using SpeedFixedSizeAccumulator = FixedSizeAccumulator<holo::float32_t, kSpeedBufferFixedSize>;
    using OptionalTimestamp         = holo::OptionalT<Timestamp>;

    /**
     * @brief The parameters of the vehicle motion state detector
     *
     */
    struct Parameters
    {
        /// Max delay time between two corrected vehicle velocity inputs. For detecting delay and loss. Unit: s.
        Scalar max_delay_time_for_input = Scalar(0.1);

        /**
         * @brief Stationary case: Speed mean and cov for judging whether vehicle is stationary. If the actual values
         * are both lower than them, the vehicle is stationray.
         *
         * @details
         * 1. Speed mean for judging whether vehicle is stationary. Unit: m/s.
         * 2. Speed covariance for judging whether vehicle is stationary.  Unit: m/s.
         */
        Scalar max_speed_mean_for_stationray_judgement = Scalar(0.02);
        Scalar max_speed_cov_for_stationary_judgement  = Scalar(0.01);

        /// For judging whether vehicle is at uniform speed. If the speed covariance is lower, it is at uniform speed.
        Scalar max_speed_cov_for_uniform_speed_judgement = Scalar(0.02);  ///< Unit: (m/s)^2

        /**
         * @brief Linear motion case: Differential speed mean and cov between two wheels for judging whether vehicle is
         * at linear motion. If the actual values are both lower than them, the vehicle is at linear motion.
         *
         * @details
         * 1. Differential speed mean. Unit: m/s
         * 2. Differential speed covariance. Unit: m/s
         */
        Scalar max_diff_speed_mean_for_linear_motion_judgement = Scalar(0.02);
        Scalar max_diff_speed_cov_for_linear_motion_judgement  = Scalar(0.02);

        /**
         * @brief Output stream overloading for VehicleMotionStateDetector's parameter
         *
         * @param[in] os std::ostream&
         * @param[in] parameters Parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << "VehicleMotionStateDetectorParameters: \n"
               << "max_delay_time_for_input = " << parameters.max_delay_time_for_input << "\n"
               << "max_speed_mean_for_stationray_judgement = " << parameters.max_speed_mean_for_stationray_judgement
               << "\n"
               << "max_speed_cov_for_stationary_judgement = " << parameters.max_speed_cov_for_stationary_judgement
               << "\n"
               << "max_speed_cov_for_uniform_speed_judgement = " << parameters.max_speed_cov_for_uniform_speed_judgement
               << "\n"
               << "max_diff_speed_mean_for_linear_motion_judgement = "
               << parameters.max_diff_speed_mean_for_linear_motion_judgement << "\n"
               << "max_diff_speed_cov_for_linear_motion_judgement = "
               << parameters.max_diff_speed_cov_for_linear_motion_judgement << std::endl;
            return os;
        }

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);
    };

    /**
     * @brief Construct a new Vehicle Motion State Detector object
     *
     * @param[in] parameters The input parameters of this class
     */
    VehicleMotionStateDetector(Parameters const& parameters)
      : parameters_(parameters)
      , rear_left_wheel_speed_accumulator_()
      , rear_right_wheel_speed_accumulator_()
      , rear_wheel_speed_difference_accmulator_()
      , last_input_velocity_timestamp_(optional::none)
    {
    }

    /**
     * @brief Run the detection of the vehicle motion state.
     * @details In current method, we only rely on the vehicle velocity, which includes the corrected wheel speeds of
     * the rear wheels, to determine which the motion state the vehicle is at.
     *
     * @param[in] vehicle_velocity_sequence The corrected vehicle velocity sequence
     * @return The enum class standing for the vehicle motion state.
     */
    VehicleMotionState Run(std::vector<StampedCorrectedVehicleVelocity> const& vehicle_velocity_sequence);

    /**
     * @brief Reset the detector class. It will recovery to the defalut.
     *
     */
    void Reset()
    {
        rear_left_wheel_speed_accumulator_.Reset();
        rear_right_wheel_speed_accumulator_.Reset();
        rear_wheel_speed_difference_accmulator_.Reset();
        last_input_velocity_timestamp_ = optional::none;
    }

protected:
    /**
     * @brief To judge whether the datas in the accmulator is enough for the vehicle motion state determination.
     *
     * @return It returns true if it is enough. Otherwise, it returns false.
     */
    bool_t islDataEnough() const
    {
        return (rear_right_wheel_speed_accumulator_.GetBufferSize() >= kSpeedBufferFixedSize) &&
               (rear_left_wheel_speed_accumulator_.GetBufferSize() >= kSpeedBufferFixedSize) &&
               (rear_wheel_speed_difference_accmulator_.GetBufferSize() >= kSpeedBufferFixedSize);
    }

    /**
     * @brief To judge whether the vechile is stationary.
     *
     * @return It returns true if it is stationary. Otherwise, it returns false.
     */
    bool_t isVehicleStationary() const
    {
        return (std::fabs(std::max(rear_left_wheel_speed_accumulator_.GetMean(),
                                   rear_right_wheel_speed_accumulator_.GetMean())) <
                parameters_.max_speed_mean_for_stationray_judgement) &&
               (std::max(rear_left_wheel_speed_accumulator_.GetCovariance(),
                         rear_right_wheel_speed_accumulator_.GetCovariance()) <
                parameters_.max_speed_cov_for_stationary_judgement);
    }

    /**
     * @brief To judge whether the vehicle is running at linear motion.
     * @attention If the vehicle is stationray, it is not at linear motion.
     *
     * @return It returns true if it is at linear motion. Otherwise, it returns false.
     */
    bool_t isVehicleAtLinearMotion() const
    {
        return (std::fabs(rear_wheel_speed_difference_accmulator_.GetMean()) <
                parameters_.max_diff_speed_mean_for_linear_motion_judgement) &&
               (rear_wheel_speed_difference_accmulator_.GetCovariance() <
                parameters_.max_diff_speed_cov_for_linear_motion_judgement);
    }

    /**
     * @brief To judge whether the vehicle is running at uniform speed motion. It means the speed is constant.
     * @attention If the vehicle is stationray, it is not at uniform speed motion.
     *
     * @return It returns true if it is at uniform speed motion. Otherwise, it returns false.
     */
    bool_t isVehicleAtUniformSpeedMotion() const
    {
        return (std::max(rear_left_wheel_speed_accumulator_.GetCovariance(),
                         rear_right_wheel_speed_accumulator_.GetCovariance()) <
                parameters_.max_speed_cov_for_uniform_speed_judgement);
    }

    /**
     * @brief Add the relative wheel speed values to the accumulators.
     *
     * @param[in] corrected_vehicle_velocity Current corrected vehicle velocity.
     */
    void addData(StampedCorrectedVehicleVelocity const& corrected_vehicle_velocity)
    {
        rear_left_wheel_speed_accumulator_.AddData(corrected_vehicle_velocity.GetData().rear_left_wheel_speed);
        rear_right_wheel_speed_accumulator_.AddData(corrected_vehicle_velocity.GetData().rear_right_wheel_speed);
        rear_wheel_speed_difference_accmulator_.AddData(corrected_vehicle_velocity.GetData().rear_left_wheel_speed -
                                                        corrected_vehicle_velocity.GetData().rear_right_wheel_speed);
        last_input_velocity_timestamp_ = OptionalTimestamp(corrected_vehicle_velocity.GetTimestamp());
    }

    /**
     * @brief To judge whether the input measuremens is lost for a long time, which means there is large time difference
     * between current input and last input.
     *
     * @param[in] corrected_vehicle_velocity Current corrected vehicle velocity.
     * @return It returns true if has lost. Otherwise, it returns false.
     */
    bool_t isMeasurementLost(StampedCorrectedVehicleVelocity const& corrected_vehicle_velocity) const;

private:
    Parameters const parameters_;

    /// The accumulator to compute the covariance and mean of the rear left wheel speed
    SpeedFixedSizeAccumulator rear_left_wheel_speed_accumulator_;

    /// The accumulator to compute the covariance and mean of the rear right wheel speed
    SpeedFixedSizeAccumulator rear_right_wheel_speed_accumulator_;

    /// The accumulator to compute the covariance and mean of the rear wheels speed difference
    SpeedFixedSizeAccumulator rear_wheel_speed_difference_accmulator_;

    /// To record the timestamp of the last received velocity. It's used to detect the input loss and delay
    OptionalTimestamp last_input_velocity_timestamp_;
};

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_VEHICLE_MOTION_STATE_DETECTOR_H_