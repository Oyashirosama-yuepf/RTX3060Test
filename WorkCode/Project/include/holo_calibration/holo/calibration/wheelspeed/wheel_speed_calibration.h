/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file wheel_speed_calibration.h
 * @brief This header file is used to define the calibration class.
 * @author Lei Gehang (leigehang@holomatic.com)
 * @author jiaxing.zhao (zhaojiaxing@holomatic.com)
 * @date 2020-9-03
 */

#ifndef HOLO_CALIBRATION_WHEELSPEED_WHEEL_SPEED_CALIBRATION_H_
#define HOLO_CALIBRATION_WHEELSPEED_WHEEL_SPEED_CALIBRATION_H_

#include <holo/log/hololog.h>
#include <holo/calibration/wheelspeed/types.h>
#include <holo/common/optional.h>

namespace holo
{
namespace calibration
{
namespace wheelspeed
{
/**
 * @addtogroup wheelspeed
 * @{
 *
 */

/**
 * @brief This class defines the calibration relative functions of the integrated navigation module
 * @details The calibration of the integrated navigation includes the calibration of the wheel speed correction
 * parameters, the calibration of the Gnss validity checker parameters. It will be expanded in the future.
 */
class WheelSpeedCalibration
{
public:
    /**
     * @brief The parameters of this class
     *
     */
    struct Parameters
    {
        /**
         * @brief Unit: m/s (equal to 100km/h)
         */
        Scalar upper_limit_wheel_speed = Scalar(27.77);

        /**
         * @brief  Unit: m/s (equal to 40km/h)
         */
        Scalar lower_limit_wheel_speed = Scalar(11.11);

        /**
         * @brief The allowed maximum of front_wheel_angle, it is to exclude the large turn.(It
         *        is equal to the 10 degree of steer_angle. The formula: front_wheel_angle =
         *        Radian(steering_angle) / 13.6)
         * @note 13.6 is the experience value given by PC
         *       Unit: radian
         */
        Scalar maximum_front_wheel_angle = Scalar(0.0128);

        /**
         * @brief The allowed maximum time difference between the wheel speed and corresponding GPS data
         */
        Scalar maximum_time_difference = Scalar(0.04);

        /**
         * @brief The mimimum accumulated counter of each sample segment. It can be adjusted based on the
         *        accuracy of calibration result.
         */
        uint16_t minimum_counter = 10u;

        /**
         * @brief The number of the sample segment Parameters
         */
        uint16_t sample_segment_number = 8u;
    };  // Parameters

    /**
     * @brief Construct a default calibration object
     */
    WheelSpeedCalibration() = default;

    /**
     * @brief Construct a new WheelSpeedCalibration object
     *
     * @param[in] param The WheelSpeedCalibration parameters
     */
    WheelSpeedCalibration(Parameters const& param) : parameters_(param)
    {
    }

    /**
     * @brief Destroy the WheelSpeedCalibration object
     */
    ~WheelSpeedCalibration() noexcept
    {
    }

    /**
     * @brief Run the wheel speed calibration process
     *
     * @param[in] state The old calibration state
     * @param[in] chassis_state The input chassis state data
     * @param[in] gps_data The corresponding GPS data
     * @param[in] nav_state The corresponding navigation state
     * @return std::pair<The updated CalibrationState, OptionalT<WheelSpeedCorrectionCoefficient>> If the computed
     *         coefficients are invalid or the current data can't be used to compute the coefficient, it will the
     *         OptionalT::none
     */
    std::pair<State, OptionalT<WheelSpeedCorrectionCoefficient>> Run(State const&                   old_state,
                                                                     ChassisState const&            chassis_state,
                                                                     GnssPvtType const&             gps_data,
                                                                     StampedAdvancedNavstate const& nav_state) const;

private:
    /**
     * @brief Insert the wheel speed calibration data to the state variable
     *
     * @param[in] old_state The old calibration state
     * @param[in] chassis_state The wheel speed data wanted to be saved
     * @param[in] gps_data The corresponding Gps data
     * @param[in] current_nav_state The corresponding navigation state
     * @return The updated calibration state (only the WheelSpeedCalibrationState will be updated)
     */
    State insertWheelSpeedData(State const& old_state, ChassisState const& chassis_state, GnssPvtType const& gps_data,
                               StampedAdvancedNavstate const& nav_state) const;

    /**
     * @brief Judge if the wheel speed calibration meets the requirements.
     * @details Current calibration requirements are:
     * (1) The number of the speed segment is equal to the the setted parameter named as sample_segment_number;
     * (2) The accumulated counter of each sample segment is more than the setted parameter named as minimum_counter.
     *
     * @param[in] state Current calibration state
     * @return It return true if it meets the requirements, otherwise, return false
     */
    bool_t isWheelSpeedDataEnough(State const& state) const;

    /**
     * @brief Compute the wheel speed calibration coefficients based on input calibration state
     *
     * @param[in] state The current calibration state
     * @return OptionalT<Wheel speed correction coefficient struct> If the computed coefficients are invalid, it will
     *         return OptionalT::none
     */
    OptionalT<WheelSpeedCorrectionCoefficient> computeWheelSpeedCoefficients(State const& state) const;

    /**
     * @brief Realize first order linear fitting
     * @details Fitting the first order linear function, for example y = a * x + b (a, b are coeffcients, x is input
     * variable, y is output result) or z = a * x + b * y + c (a, b, c are coefficients, x, y are input variables, z is
     * output result).
     * The following is a case: for the linear equation with two unknowns (y = a * x + b). We should input the sets of
     * (x1, x2, x3, x4...) and (y1, y2, y3, y4...). Then we can fit and get the coefficients of the equations.
     *
     * @param[in] input_calibration_data The input data
     * @param[in] ground_truth The fitting truth value
     * @return The coefficients of the first order linear fitting. It is a matrix of many rows and one column, in which
     * the rows of the matrix are the coefficients a, b or c of the equation in turn.
     */
    Vector2Type firstOrderLinearFitting(MatrixXType const& input_calibration_data,
                                        VectorXType const& ground_truth) const;

    /**
     * @brief the parameters of this class
     */
    const Parameters parameters_;
};

/**
 * @}
 *
 */
}  // namespace wheelspeed
}  // namespace calibration
}  // namespace holo
#endif  // HOLO_CALIBRATION_WHEELSPEED_WHEEL_SPEED_CALIBRATION_H_
