/*!
 * \brief wheel integration class header file in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \author Mingyu. Xu, xumingyu@holomatic.com
 * \date Dec-23-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/wheel_integration.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WheelIntegrationBase::Parameters WheelIntegrationBase::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    const Scalar frequency = node["frequency"].as<Scalar>(10.0);

    const Scalar chassis_frequency = node["chassis_frequency"].as<Scalar>(100.0);

    const float32_t wheel_base = node["wheel_base"].as<float32_t>();

    const float32_t track_gauge = node["track_gauge"].as<float32_t>();

    const float32_t wheel_diameter = node["wheel_diameter"].as<float32_t>();

    const float32_t wheel_pulse_per_cycle = node["wheel_pulse_per_cycle"].as<float32_t>();

    const uint32_t max_wheel_pulse_num = node["max_wheel_pulse_num"].as<uint32_t>(4096u);

    const auto steering_ratio_table = LoadSteeringRatioTable(node);

    return Parameters(frequency, chassis_frequency, wheel_base, track_gauge, wheel_diameter, wheel_pulse_per_cycle,
                      max_wheel_pulse_num, steering_ratio_table);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WheelIntegrationBase::SteeringRatioTable
WheelIntegrationBase::Parameters::LoadSteeringRatioTable(const holo::yaml::Node& node)
{
    std::string steering_ratio_table_file = node["steering_ratio_table_file"].as<std::string>();

    // if the given path is relative path, add ${HOLO_ROOT} before it
    steering_ratio_table_file =
        holo::GetFileAbsolutePath(steering_ratio_table_file, holo::GetHoloConfigRootDirectory());

    if (!boost::filesystem::exists(steering_ratio_table_file))
    {
        LOG(ERROR) << "WheelIntegrationBase ---  file: " << steering_ratio_table_file << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    LOG(INFO) << "WheelIntegrationBase --- trying to load steering ration table from " << steering_ratio_table_file
              << "\n";
    std::ifstream      ifs(steering_ratio_table_file, std::fstream::in);
    SteeringRatioTable table;

    while (ifs.good())
    {
        Scalar angle = 0.0, ratio = 0.0;
        ifs >> angle >> ratio;

        if (ifs.fail())
        {
            break;
        }
        table.push_back(SteeringRatio(angle * M_PI / 180.0, ratio));
    }

    return table;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WheelIntegrationBase::Parameters WheelIntegrationBase::Parameters::Example()
{
    return Parameters(20.0, 100.0, 2.7, 1.6, 0.65, 86, 4096);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WheelIntegrationBase::WheelIntegrationBase(const Parameters& parameters) : parameters_(parameters)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Pose2 WheelIntegrationBase::predict(const Pose3& start_pose, const WheelIntegrationMeasurement& wim) const
{
    return Pose2(start_pose.GetRotation().YPR()[0] + wim.delta_yaw, start_pose.GetX() + wim.delta_x,
                 start_pose.GetY() + wim.delta_y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scalar WheelIntegrationBase::getSteeringAngleRatio(const SteeringRatioTable& steering_ratio_table, Scalar angle)
{
    if (angle < steering_ratio_table.front().steering_angle)
    {
        return steering_ratio_table.front().ratio;
    }

    if (angle > steering_ratio_table.back().steering_angle)
    {
        return steering_ratio_table.back().ratio;
    }

    auto iter_right = std::lower_bound(steering_ratio_table.begin(), steering_ratio_table.end(), angle,
                                       [](const SteeringRatio& x, Scalar t) { return x.steering_angle < t; });
    auto iter_left  = iter_right - 1;

    Scalar angle_a = iter_left->steering_angle;
    Scalar angle_b = iter_right->steering_angle;
    Scalar ratio_a = iter_left->ratio;
    Scalar ratio_b = iter_right->ratio;

    Scalar k = (ratio_b - ratio_a) / (angle_b - angle_a);
    Scalar b = ratio_a - k * angle_a;

    return k * angle + b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AckermannWheelIntegration::AckermannWheelIntegration(const WheelIntegrationBase::Parameters& parameters)
  : WheelIntegrationBase(parameters)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WheelIntegrationMeasurement
AckermannWheelIntegration::integrateMeasurement(const std::vector<ChassisState>& new_measurement) const
{
    WheelIntegrationMeasurement wim;
    if (new_measurement.empty())
    {
        LOG(ERROR) << "wheel integration --- input chassis data empty\n";
        return wim;
    }

    wim.start = new_measurement.front().GetTimestamp();
    wim.end   = new_measurement.back().GetTimestamp();

    Timestamp      last_chassis_timestamp      = wim.start;
    holo::uint32_t last_rear_left_wheel_pulse  = new_measurement.front().GetRearLeftWheelPulse();
    holo::uint32_t last_rear_right_wheel_pulse = new_measurement.front().GetRearRightWheelPulse();

    for (const auto& chassis_state : new_measurement)
    {
        float32_t const delta_time = chassis_state.GetTimestamp().ToSec() - last_chassis_timestamp.ToSec();
        if (delta_time < (1 / parameters_.chassis_frequency - 0.0001))
        {
            continue;
        }

        /// calculate shifting length using wheel pulse
        int32_t delta_rear_left_wheel_pulse  = chassis_state.GetRearLeftWheelPulse() - last_rear_left_wheel_pulse;
        int32_t delta_rear_right_wheel_pulse = chassis_state.GetRearRightWheelPulse() - last_rear_right_wheel_pulse;
        if (delta_rear_left_wheel_pulse < 0)
        {
            delta_rear_left_wheel_pulse += parameters_.max_wheel_pulse_num;
        }
        if (delta_rear_right_wheel_pulse < 0)
        {
            delta_rear_right_wheel_pulse += parameters_.max_wheel_pulse_num;
        }

        float64_t rear_left_wheel_length =
            delta_rear_left_wheel_pulse / parameters_.wheel_pulse_per_cycle * M_PI * parameters_.wheel_diameter;
        float64_t rear_right_wheel_length =
            delta_rear_right_wheel_pulse / parameters_.wheel_pulse_per_cycle * M_PI * parameters_.wheel_diameter;
        float64_t rear_wheel_length = 0.5f * (rear_left_wheel_length + rear_right_wheel_length);

        if ((uint8_t)chassis_state.GetGearPosition() == 2)
        {
            rear_wheel_length = -rear_wheel_length;
        }

        /// calculate increment angle
        Scalar    ratio = getSteeringAngleRatio(parameters_.steering_ratio_table, chassis_state.GetFrontWheelAngle());
        float64_t instant_radius  = parameters_.wheel_base / tan(chassis_state.GetFrontWheelAngle() / ratio);
        float64_t increment_angle = rear_wheel_length / instant_radius;

        /// calculate delta translation
        wim.delta_x += cos(wim.delta_yaw + 0.5f * increment_angle) * rear_wheel_length;
        wim.delta_y += sin(wim.delta_yaw + 0.5f * increment_angle) * rear_wheel_length;
        wim.delta_yaw += increment_angle;

        last_rear_left_wheel_pulse  = chassis_state.GetRearLeftWheelPulse();
        last_rear_right_wheel_pulse = chassis_state.GetRearRightWheelPulse();
        last_chassis_timestamp      = chassis_state.GetTimestamp();
    }

    return wim;
}
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
