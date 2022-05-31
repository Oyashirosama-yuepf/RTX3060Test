/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file failure_detector.h
 * @brief This header file defines failure detector class.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-03-02"
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_FAILURE_DETECTOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_FAILURE_DETECTOR_H_

#include <holo/localization/common/localization_base.h>
#include <holo/localization/tightly_coupled_fusion/common_types.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup
 * @{
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief failure detector class to check whether the estimated result is valid
 */
class FailureDetector
{
public:
    /**
     * @brief failure detector parameters
     */
    struct Parameters
    {
        Scalar x_translation_threshold;  /// translation threshold along x axis[m] in 1 second

        Scalar y_translation_threshold;  /// translation threshold along y axis[m] in 1 second

        Scalar yaw_threshold;  /// yaw threshold[rad] in 1 second

        Scalar vehicle_speed_threshold;  /// vehicle speed threshold[m/s]

        Scalar gyro_bias_norm_threshold;  /// gyro bias norm threshold[rad/s]

        Scalar acc_bias_norm_threshold;  /// acc bias norm threshold[m/s^2]

        Vector3Type translation_standard_deviation_threshold;  ///< translation standard deviation threshold[m]

        Vector3Type rotation_standard_threshold;  ///< rotation standard deviation threshold[rad]

        /**
         * @brief Construct a new Parameters object
         *
         * @param[in] _x_translation_threshold translation threshold along x axis[m] in 1 second
         * @param[in] _y_translation_threshold translation threshold along y axis[m] in 1 second
         * @param[in] _yaw_threshold yaw threshold[rad] in 1 second
         * @param[in] _vehicle_speed_threshold vehicle speed threshold[m/s]
         * @param[in] _gyro_bias_norm_threshold gyro bias norm threshold[rad/s]
         * @param[in] _acc_bias_norm_threshold acc bias norm threshold[m/s^2]
         * @param[in] _translation_standard_deviation_threshold translation standard deviation threshold[m]
         * @param[in] _rotation_standard_threshold rotation standard deviation threshold[rad]
         */
        Parameters(const Scalar _x_translation_threshold = 33.0, const Scalar _y_translation_threshold = 4.4,
                   const Scalar _yaw_threshold = 5.5, const Scalar _vehicle_speed_threshold = 33.0,
                   const Scalar _gyro_bias_norm_threshold = 1.0, const Scalar _acc_bias_norm_threshold = 2.5,
                   const Vector3Type _translation_standard_deviation_threshold = Vector3Type(1.0, 1.0, 1.0),
                   const Vector3Type _rotation_standard_threshold              = Vector3Type(1.0, 1.0, 1.0))
          : x_translation_threshold(_x_translation_threshold)
          , y_translation_threshold(_y_translation_threshold)
          , yaw_threshold(_yaw_threshold)
          , vehicle_speed_threshold(_vehicle_speed_threshold)
          , gyro_bias_norm_threshold(_gyro_bias_norm_threshold)
          , acc_bias_norm_threshold(_acc_bias_norm_threshold)
          , translation_standard_deviation_threshold(_translation_standard_deviation_threshold)
          , rotation_standard_threshold(_rotation_standard_threshold)
        {
        }

        /**
         * @brief static method to load parameters from yaml
         *
         * @param node yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        /**
         * @brief static method to generate example parameters for unit test
         *
         * @return the generated parameters for unit test
         */
        static Parameters GenerateExample();

        /**
         * @brief output stream for failure detector parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "Failure Detector Parameters: "
               << "\n x_translation_threshold[m] = " << parameters.x_translation_threshold
               << "\n y_translation_threshold[m] = " << parameters.y_translation_threshold
               << "\n yaw_threshold[rad] = " << parameters.yaw_threshold
               << "\n vehicle_speed_threshold[m/s] = " << parameters.vehicle_speed_threshold
               << "\n gyro_bias_norm_threshold[rad/s] = " << parameters.gyro_bias_norm_threshold
               << "\n acc_bias_norm_threshold[m/s^2] = " << parameters.acc_bias_norm_threshold
               << "\n translation_standard_deviation_threshold[m] = "
               << parameters.translation_standard_deviation_threshold
               << "\n rotation_standard_threshold[rad] = " << parameters.rotation_standard_threshold << std::endl;
            return os;
        }
    };  // Parameters

    /**
     * @brief Define failure status
     *
     */
    enum class Status : uint32_t
    {
        ALLGOOD                                = 0u,  // failure not detected
        TIMESTAMP_FAILURE                      = 1u,  // for timestamp
        X_TRANSLATION_FAILURE                  = 2u,  // for x_translation_threshold
        Y_TRANSLATION_FAILURE                  = 3u,  // for y_translation_threshold
        YAW_FAILURE                            = 4u,  // for yaw_threshold
        VEHICLE_FAILURE                        = 5u,  // for vehicle_speed_threshold
        GYRO_BIAS_FAILURE                      = 6u,  // for gyro_bias_threshold
        ACC_BIAS_FAILURE                       = 7u,  // for acc_bias_threshold
        TRANSLATION_STANDARD_DEVIATION_FAILURE = 8u,  // for translation_standard_deviation_threshold
        ROTATION_STANDARD_DEVIATION_FAILURE    = 9u,  // for rotation_standard_deviation_threshold
    };

    /**
     * @brief constructor
     *
     * @param[in] parameters
     */
    FailureDetector(const Parameters& parameters) : parameters_(parameters)
    {
    }

    /**
     * @brief judge whether failure case is detected and which estimated navstate is a failure case
     *
     * @param[in] last_stamped_advanced_navstate last stamped advanced navstate
     * @param[in] newest_stamped_advanced_navstate newest stamped advanced navstate
     * @return Status the detected failure status
     *
     */
    Status Run(const StampedAdvancedNavstate& last_stamped_advanced_navstate,
               const StampedAdvancedNavstate& newest_stamped_advanced_navstate) const;

private:
    /// @brief parameters
    const Parameters parameters_;

};  // FailureDetector

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_FAILURE_DETECTOR_H_
