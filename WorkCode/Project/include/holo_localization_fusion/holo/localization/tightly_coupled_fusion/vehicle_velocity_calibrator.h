/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_velocity_calibrator.h
 * @brief This header file is used to define the vehicle velocity calibrator class.
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date May 30, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_VEHICLE_VELOCITY_CALIBRATOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_VEHICLE_VELOCITY_CALIBRATOR_H_

#include <holo/localization/tightly_coupled_fusion/common_types.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup tightly_coupled_fusion
 * @{
 *
 */

/**
 * @brief This class is used to calibrate the vehicle velocity.
 *
 */
class VehicleVelocityCalibrator
{
public:
    /**
     * @brief Define common type
     *
     */
    using Ptr      = std::shared_ptr<VehicleVelocityCalibrator>;
    using ConstPtr = std::shared_ptr<const VehicleVelocityCalibrator>;

    /**
     * @brief The relative parameters of this class.
     *
     */
    struct Parameters
    {
        VehicleVelocityCorrectionCoefficients initial_correction_coefficients;
        VehicleVelocityCorrectionCoefficients maximum_correction_coefficients;
        VehicleVelocityCorrectionCoefficients minimum_correction_coefficients;

        /// The number of segment in which the vehicle velocity range is divided.
        uint16_t sample_segment_number = 3u;

        /// The window size to save the calibration data for each data segment
        uint16_t each_data_segment_window_size = 10u;

        /// The upper and lower limit for the calibrated vehicle velocity range.
        Scalar calibrated_velocity_upper_limit = Scalar(27.77);  ///< Unit: m/s (100 km/h)
        Scalar calibrated_velocity_lower_limit = Scalar(11.11);  ///< Unit: m/s (40 km/h)

        /// The max condition number of matrix A for the valid solution to sovle the linear least square problem: AX = b
        Scalar max_condition_number_for_least_square = Scalar(100.0);

        bool_t verbose = false;  ///< The verbose switch for detail log.

        /**
         * @brief Construct a new Parameters struct
         *
         * @param[in] _initial_correction_coefficients The initial correction coefficnets
         * @param[in] _sample_segment_number The number of segment for velocity range sample.
         * @param[in] _each_data_segment_window_size The window size to save the calibration data for each data segment
         * @param[in] _calibrated_velocity_upper_limit  The upper limit for the calibrated vehicle velocity range.
         * @param[in] _calibrated_velocity_lower_limit The lower limit for the calibrated vehicle velocity range.
         * @param[in] _max_condition_number_for_least_square The max condition number of matrix A for the valid solution
         * to sovle the linear least square problem: AX = b
         * @param[in] _verbose The verbose switch for detail log.
         */
        Parameters(VehicleVelocityCorrectionCoefficients const& _initial_correction_coefficients =
                       VehicleVelocityCorrectionCoefficients(),
                   VehicleVelocityCorrectionCoefficients const& _maximum_correction_coefficients =
                       VehicleVelocityCorrectionCoefficients(1.1, std::numeric_limits<Scalar>::max()),
                   VehicleVelocityCorrectionCoefficients const& _minimum_correctio_coefficients =
                       VehicleVelocityCorrectionCoefficients(0.8, std::numeric_limits<Scalar>::min()),
                   uint16_t const _sample_segment_number = 3u, uint16_t const _each_data_segment_window_size = 10u,
                   Scalar const _calibrated_velocity_upper_limit       = 27.77,
                   Scalar const _calibrated_velocity_lower_limit       = 11.11,
                   Scalar const _max_condition_number_for_least_square = 100.0, bool_t const _verbose = false)
          : initial_correction_coefficients(_initial_correction_coefficients)
          , maximum_correction_coefficients(_maximum_correction_coefficients)
          , minimum_correction_coefficients(_minimum_correctio_coefficients)
          , sample_segment_number(_sample_segment_number)
          , each_data_segment_window_size(_each_data_segment_window_size)
          , calibrated_velocity_upper_limit(_calibrated_velocity_upper_limit)
          , calibrated_velocity_lower_limit(_calibrated_velocity_lower_limit)
          , max_condition_number_for_least_square(_max_condition_number_for_least_square)
          , verbose(_verbose)
        {
        }

        /**
         * @brief The operator overloading for <<.
         *
         * @param[in] os The std ostream.
         * @param[in] params The parameters object.
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& params);

        /**
         * @brief Static method to load parameters from yaml node.
         *
         * @param[in] node The yaml node.
         * @return The loaded parameters.
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief static method to generate example parameters for unit test
         *
         * @return The generated parameters for unit test
         */
        static Parameters GenerateExample()
        {
            return Parameters();
        }
    };

    /**
     * @brief Construct a new Vehicle Velocity Calibrator object
     *
     * @param[in] parameters The initial parameters.
     */
    explicit VehicleVelocityCalibrator(Parameters const& parameters)
      : parameters_(parameters)
      , correction_coefficients_(parameters.initial_correction_coefficients)
      , calibration_data_()
    {
    }

    /**
     * @brief Run the vehicle velocity calibrator.
     *
     * @param[in] raw_velocity The raw velocity value to be calibrated.
     * @param[in] ground_truth The ground truth for reference.
     * @return It returns true if we can calibrate the corrections coefficients of the vehicle velocity. Otherwise, it
     * return false. The failure reason may be there is no enough data for calibration.
     */
    bool_t Run(Scalar const raw_velocity, Scalar const ground_truth);

    /**
     * @brief Get the correction coefficients from the calibrator.
     *
     * @return VehicleVelocityCorrectionCoefficients
     */
    VehicleVelocityCorrectionCoefficients const& GetCorrectionCoefficients() const
    {
        return correction_coefficients_;
    }

    /**
     * @brief Clear hitorical calibration data of this calibrator.
     *
     */
    void ClearCalibrationData()
    {
        calibration_data_.clear();
    }

protected:
    /**
     * @brief The data pair of the raw velocity and ground truth value.
     *
     */
    struct CalibrationDataPair
    {
        Scalar raw_velocity;  ///< The raw velocity value to be calibrated.
        Scalar ground_truth;  ///< The ground truth for reference.

        /**
         * @brief Construct a new Calibration Data Pair object
         *
         * @param[in] _raw_velocity The raw velocity value to be calibrated.
         * @param[in] _ground_truth The ground truth for reference.
         */
        CalibrationDataPair(Scalar const _raw_velocity, Scalar const _ground_truth)
          : raw_velocity(_raw_velocity), ground_truth(_ground_truth)
        {
        }
    };
    using CalibrationDataPairs = std::deque<CalibrationDataPair>;

    /**
     * @brief CalibrationData is a Map(Key: the index of data segementation, Value: CalibrationDataPairs)
     * @details In order to ensure the effective distribution of data and improve the calibration accuracy, we segment
     * the calibration velocity range. The range is [velocity_lower_limit, velocity_upper_limit]. And the number of
     * segments is determined by parameters. And the size of each segment is "(velocity_upper_limit -
     * velocity_lower_limit) / segment_number".
     *
     * For example, if the calibrated velocity range is [20, 100]. And the segment number is 3. So the CalibrationData
     * is divided to 3 parts:
     *
     *            | - - - - -  Index: 0 - - - - -  |  - - - - - Index: 1 - - - - - | - - - - - Index: 2 - - - - - |
     * Velocity:  20                              46.67                          73.33                           100
     */
    using CalibrationData = std::unordered_map<uint16_t, CalibrationDataPairs>;

    /**
     * @brief Insert the calibration data to the buffer.
     *
     * @param[in] raw_velocity The raw velocity to be calibrated.
     * @param[in] ground_truth The ground truth for reference.
     * @param[in, out] calibration_data The updated calibration data buffer.
     */
    void insertCalibrationData(Scalar const raw_velocity, Scalar const ground_truth,
                               CalibrationData& calibration_data) const;

    /**
     * @brief To judge whether the calibration data is enough to compute the correction coefficients.
     *
     * @param[in] calibration_data The calibration data buffer.
     * @param[in] sample_segment_number The sample segment number.
     * @param[in] min_size_of_each_data_segments The min size for each data segment to compute the result.
     * @return It returns true if the data is enough. Otherwise, it returns false.
     */
    bool_t isCalibrationDataEnough(CalibrationData const& calibration_data, uint16_t const sample_segment_number,
                                   uint16_t const min_size_of_each_data_segments) const;

    /**
     * @brief Compute the corrections coefficient based on the calibration data.
     *
     * @param[in] calibration_data Th calibration data.
     * @return It returns optional correction coefficients if successfull. Otherwise, it returns optional::none.
     */
    OptionalT<VehicleVelocityCorrectionCoefficients>
    computeCorrectionCoefficients(CalibrationData const& calibration_data) const;

private:
    Parameters const parameters_;

    /// The vehicle velocity correction coefficients. It will update when we run the calibrator and insert the new data.
    VehicleVelocityCorrectionCoefficients correction_coefficients_;

    CalibrationData calibration_data_;  ///< The data for computing the correction coefficients.
};

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  /// HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_VEHICLE_VELOCITY_CALIBRATOR_H_