/*!
 * \brief wheel integration class header file in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \author Mingyu. Xu, xumingyu@holomatic.com
 * \date Dec-23-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_WHEEL_INTEGRATION_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_WHEEL_INTEGRATION_H_

#include <holo/localization/vision/vslam/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup localization
 * @brief wheel integration class
 *
 * @details
 */
class WheelIntegrationBase
{
public:
    struct SteeringRatio
    {
        Scalar steering_angle;

        Scalar ratio;

        SteeringRatio(const Scalar _steering_angle, const Scalar _ratio)
          : steering_angle(_steering_angle), ratio(_ratio)
        {
        }
    };

    using SteeringRatioTable = std::vector<SteeringRatio>;

    /**
     * @brief define parameters
     */
    struct Parameters
    {
        /// @brief algorithm running frequency
        Scalar frequency;

        /// @brief frequency to control chassis data
        Scalar chassis_frequency;

        /// @brief vehicle wheel base
        float32_t wheel_base;

        /// @brief vehicle track gauge
        float32_t track_gauge;

        /// @brief vehicle wheel diameter
        float32_t wheel_diameter;

        /// @brief wheel pulse per cycle
        float32_t wheel_pulse_per_cycle;

        /// @brief maximum wheel pulse number
        uint32_t max_wheel_pulse_num;

        SteeringRatioTable steering_ratio_table;

        /**
         * @brief Construct a new Parameters object
         */
        Parameters(const Scalar _frequency, const Scalar _chassis_frequency, const float32_t _wheel_base,
                   const float32_t _track_gauge, const float32_t _wheel_diameter,
                   const float32_t _wheel_pulse_per_cycle, const uint32_t _max_wheel_pulse_num,
                   const SteeringRatioTable& _steering_ratio_table = {})
          : frequency(_frequency)
          , chassis_frequency(_chassis_frequency)
          , wheel_base(_wheel_base)
          , track_gauge(_track_gauge)
          , wheel_diameter(_wheel_diameter)
          , wheel_pulse_per_cycle(_wheel_pulse_per_cycle)
          , max_wheel_pulse_num(_max_wheel_pulse_num)
          , steering_ratio_table(_steering_ratio_table)
        {
        }

        /**
         * @brief load from yaml
         *
         * @param node
         * @return Parameters
         */
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        static SteeringRatioTable LoadSteeringRatioTable(const holo::yaml::Node& node);

        /**
         * @brief static example parameters for unit test
         *
         * @return Parameters
         */
        static Parameters Example();
    };

    /**
     * @brief constructor with parameters
     */
    WheelIntegrationBase(const Parameters& parameters);

    /**
     * @brief destructor
     */
    virtual ~WheelIntegrationBase()
    {
    }

    /**
     * @brief integrate new measurement
     *
     */
    virtual WheelIntegrationMeasurement
    integrateMeasurement(const std::vector<ChassisState>& new_measurement) const = 0;

    /**
     * @brief predict new state with a given start state
     *
     */
    virtual Pose2 predict(const Pose3& start_pose, const WheelIntegrationMeasurement& wim) const;

    static Scalar getSteeringAngleRatio(const SteeringRatioTable& steering_ratio_table, Scalar angle);

protected:
    /// @brief parameteres
    const Parameters parameters_;

};  // class WheelIntegrationBase

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup localization
 * @brief derived wheel integration class
 * @details make wheel integration use ackermann model
 */
class AckermannWheelIntegration : public WheelIntegrationBase
{
public:
    AckermannWheelIntegration(const WheelIntegrationBase::Parameters& parameters);

    virtual ~AckermannWheelIntegration()
    {
    }

    /**
     * @brief integrate wheel pulse with ackermann model
     * @param new_measurement input chassis data
     * @return integrated wheel measurement
     */
    virtual WheelIntegrationMeasurement
    integrateMeasurement(const std::vector<ChassisState>& new_measurement) const override;
};  // class AckermannWheelIntegrationBase
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_WHEEL_INTEGRATION_H_
