/*!
 * @file test_source_checker_odometry.cpp
 * @brief Unit test for source checker odometry.
 * @author lichao@holomatic.com
 * @date Jul 02, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <gtest/gtest.h>
#include <holo/localization/tools/source_checker.h>
#include <holo/localization/tools/source_checker_helper.h>

using SourceCheckerOdometry = holo::localization::SourceCheckerOdometry;
using SourceState           = holo::localization::SourceState;
using OdometryType          = holo::localization::OdometryType;
using CoordinateType        = holo::localization::CoordinateType;
using UniqueParamters       = holo::localization::internal::OdometryCheckerUniqueParameters;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorTest, OdometryCase)
{
    SourceCheckerOdometry::Parameters params;
    params.coord                       = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.frequency                   = 10.0f;
    params.status_counter_threshold    = 5;
    params.max_timestamp_gap_tolerance = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    SourceCheckerOdometry::Ptr source_checker_ptr = std::make_shared<SourceCheckerOdometry>(params);
    ASSERT_TRUE(SourceState::UNSURE == source_checker_ptr->GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LoadYamlTest, OdometryYamlCase)
{
    holo::yaml::Node yaml_node;

    yaml_node["enable_checker"]                              = static_cast<bool>(true);
    yaml_node["frequency"]                                   = static_cast<float>(10.0f);
    yaml_node["status_counter_threshold"]                    = static_cast<int>(5);
    yaml_node["max_timestamp_gap_tolerance"]                 = static_cast<float>(1.0f);
    yaml_node["min_period_multiple_in_normal_consistency"]   = static_cast<float>(0.5f);
    yaml_node["max_period_multiple_in_normal_consistency"]   = static_cast<float>(1.5f);
    yaml_node["min_period_multiple_in_low_obstruction"]      = static_cast<float>(0.3f);
    yaml_node["source_actual_frequency_statistics_interval"] = static_cast<float>(0.3f);
    yaml_node["enable_log"]                                  = static_cast<bool>(false);
    yaml_node["coordinate"]                                  = static_cast<std::string>("0x11010277");

    SourceCheckerOdometry source_checker(SourceCheckerOdometry::Parameters::LoadYaml(yaml_node));

    /* If the yaml file is not loaded or not completely loaded, the State of source checker is GOOD */
    ASSERT_TRUE(SourceState::UNSURE == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, DisableOdometryCheckerCase)
{
    SourceCheckerOdometry::Parameters params;
    params.coord                       = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.frequency                   = 10.0f;
    params.status_counter_threshold    = 5;
    params.max_timestamp_gap_tolerance = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = false;

    SourceCheckerOdometry source_checker(params);
    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, IncompleteParameterSettingCase)
{
    SourceCheckerOdometry::Parameters params;
    params.coord          = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.enable_log     = false;
    params.enable_checker = true;

    SourceCheckerOdometry source_checker(params);

    /* If the parameter setting is incomplete, the checker will be closed. The return state is always GOOD */
    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, NormalCase)
{
    SourceCheckerOdometry::Parameters params;
    params.coord                       = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.frequency                   = 10.0f;
    params.status_counter_threshold    = 5;
    params.max_timestamp_gap_tolerance = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    /* No source_name have been set, the default source_name is unknown */
    SourceCheckerOdometry source_checker(params);

    /* Create a Odometry */
    OdometryType    odometry;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    odometry.SetStatus(OdometryType::Status::ALLGOOD);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(odometry);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad Odometry comes in */
    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    odometry.SetTimestamp(sensor_timestamp);
    odometry.SetStatus(OdometryType::Status::POSITIONINACTIVE);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(odometry));

    odometry.SetStatus(OdometryType::Status::ALLGOOD);

    for (; measurement_i < 11u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(odometry);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, StatusBadCase)
{
    SourceCheckerOdometry::Parameters params;
    params.coord                       = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.frequency                   = 10.0f;
    params.status_counter_threshold    = 5;
    params.max_timestamp_gap_tolerance = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    std::string           source_name = "odometry0";
    SourceCheckerOdometry source_checker(params, source_name);

    /* Create a Odometry */
    OdometryType    odometry;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    odometry.SetStatus(OdometryType::Status::POSITIONINACTIVE);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(odometry);
    }

    ASSERT_TRUE(SourceState::BAD == source_checker.GetSourceState());

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    odometry.SetTimestamp(sensor_timestamp);
    odometry.SetStatus(OdometryType::Status::ALLGOOD);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(odometry));

    for (; measurement_i < 15u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(odometry);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, TimestampInconsistencyMediumCase)
{
    SourceCheckerOdometry::Parameters params;

    params.coord                       = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.frequency                   = 10.0f;
    params.status_counter_threshold    = 5;
    params.max_timestamp_gap_tolerance = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    std::string           source_name = "odometry1";
    SourceCheckerOdometry source_checker(params, source_name);

    /* Create a Odometry */
    OdometryType    odometry;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    odometry.SetStatus(OdometryType::Status::ALLGOOD);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(odometry);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad Odometry comes in */
    holo::os::Sleep(1.0f / params.frequency + 0.2f);
    sensor_timestamp += sensor_duration;
    sensor_timestamp += holo::common::Duration(0, 2e8);
    odometry.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(odometry));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, TimestampInconsistencyMaxFatalCase)
{
    SourceCheckerOdometry::Parameters params;
    params.coord                       = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.frequency                   = 10.0f;
    params.status_counter_threshold    = 5;
    params.max_timestamp_gap_tolerance = 1.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    std::string           source_name = "odometry1";
    SourceCheckerOdometry source_checker(params, source_name);

    /* Create a Odometry */
    OdometryType    odometry;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    odometry.SetStatus(OdometryType::Status::ALLGOOD);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(0.1f);
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(odometry);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad Odometry comes in */
    holo::os::Sleep(0.1f + 1.2f);
    sensor_timestamp += sensor_duration;
    sensor_timestamp += holo::common::Duration(1, 2e8);
    odometry.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(odometry));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, TimestampInconsistencyNegativeFatalCase)
{
    SourceCheckerOdometry::Parameters params;
    params.coord                       = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.frequency                   = 10.0f;
    params.status_counter_threshold    = 5;
    params.max_timestamp_gap_tolerance = 1.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    std::string           source_name = "odometry2";
    SourceCheckerOdometry source_checker(params, source_name);

    /* Create a Odometry */
    OdometryType    odometry;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    odometry.SetStatus(OdometryType::Status::ALLGOOD);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(odometry);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad Odometry comes in */
    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    sensor_timestamp -= holo::common::Duration(0, 2e8);
    odometry.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(odometry));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, SystemObstructionStateMiddleCase)
{
    SourceCheckerOdometry::Parameters params;

    params.coord                       = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.frequency                   = 10.0f;
    params.status_counter_threshold    = 5;
    params.max_timestamp_gap_tolerance = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = true;  // print log file
    params.enable_checker                              = true;

    std::string           source_name = "odometry3";
    SourceCheckerOdometry source_checker(params, source_name);

    /* Create a Odometry */
    OdometryType    odometry;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    odometry.SetStatus(OdometryType::Status::ALLGOOD);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(odometry);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad Odometry comes in */
    holo::os::Sleep(1.0f / params.frequency + 0.2f);
    sensor_timestamp += sensor_duration;
    odometry.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(odometry));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, SystemObstructionStateHighCase)
{
    SourceCheckerOdometry::Parameters params;

    params.coord                       = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.frequency                   = 10.0f;
    params.status_counter_threshold    = 5;
    params.max_timestamp_gap_tolerance = 1.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = true;  // print log file
    params.enable_checker                              = true;

    /* Although enable_ Log is true, but the source name is set to empty, so the log file is not printed */
    SourceCheckerOdometry source_checker(params, "");

    /* Create a Odometry */
    OdometryType    odometry;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    odometry.SetStatus(OdometryType::Status::ALLGOOD);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(odometry);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad Odometry comes in */
    holo::os::Sleep(1.0f / params.frequency + 1.2f);
    sensor_timestamp += sensor_duration;
    odometry.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(odometry));

    for (; measurement_i < 10u; measurement_i++)
    {
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(odometry));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, UniqueFunctionSourceStatusUNKNOWNCase)
{
    SourceCheckerOdometry::Parameters params;
    params.coord                       = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.frequency                   = 10.0f;
    params.status_counter_threshold    = 5;
    params.max_timestamp_gap_tolerance = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    UniqueParamters unique_params;
    unique_params.translation_x_cov_threshold = 10.0f;
    unique_params.translation_y_cov_threshold = 10.0f;
    unique_params.translation_z_cov_threshold = 10.0f;
    unique_params.rotation_x_cov_threshold    = 10.0f;
    unique_params.rotation_y_cov_threshold    = 10.0f;
    unique_params.rotation_z_cov_threshold    = 10.0f;

    auto function =
        std::bind(holo::localization::internal::CheckOdometryUniqueState, unique_params, std::placeholders::_1);

    std::string           source_name = "odometry4";
    SourceCheckerOdometry source_checker(params, source_name, function);

    holo::numerics::Matrix6d pose_cov = holo::numerics::Matrix6d::Identity();

    /* Create a Odometry */
    OdometryType    odometry;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    odometry.SetStatus(OdometryType::Status::ALLGOOD);
    odometry.SetPoseCovariance(pose_cov);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(odometry);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    odometry.SetTimestamp(sensor_timestamp);
    odometry.SetStatus(OdometryType::Status::UNKNOWN);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(odometry));
    ASSERT_TRUE(SourceState::BAD == source_checker.GetSourceState());

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    odometry.SetTimestamp(sensor_timestamp);
    odometry.SetStatus(OdometryType::Status::ALLGOOD);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(odometry));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, UniqueFunctionCovarianceOutBoundsCase)
{
    SourceCheckerOdometry::Parameters params;
    params.coord                       = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.frequency                   = 10.0f;
    params.status_counter_threshold    = 5;
    params.max_timestamp_gap_tolerance = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = true;
    params.enable_checker                              = true;

    UniqueParamters unique_params;
    unique_params.translation_x_cov_threshold = 10.0f;
    unique_params.translation_y_cov_threshold = 10.0f;
    unique_params.translation_z_cov_threshold = 10.0f;
    unique_params.rotation_x_cov_threshold    = 10.0f;
    unique_params.rotation_y_cov_threshold    = 10.0f;
    unique_params.rotation_z_cov_threshold    = 10.0f;

    std::string source_name = "odometry5";
    auto        function =
        std::bind(holo::localization::internal::CheckOdometryUniqueState, unique_params, std::placeholders::_1);

    SourceCheckerOdometry source_checker(params, source_name, function);

    holo::numerics::Matrix6d pose_cov = holo::numerics::Matrix6d::Identity();
    /* Create a Odometry */
    OdometryType    odometry;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    odometry.SetStatus(OdometryType::Status::ALLGOOD);
    odometry.SetPoseCovariance(pose_cov);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(odometry);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    odometry.SetTimestamp(sensor_timestamp);
    pose_cov(5, 5) = 15.0f;
    odometry.SetPoseCovariance(pose_cov);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(odometry));
    ASSERT_TRUE(SourceState::BAD == source_checker.GetSourceState());

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    odometry.SetTimestamp(sensor_timestamp);
    pose_cov(5, 5) = 5.0f;
    odometry.SetPoseCovariance(pose_cov);
    ASSERT_TRUE(SourceState::GOOD == source_checker.CheckSourceState(odometry));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetMemberFunctionTest, getSourceObstructionLevelCase)
{
    SourceCheckerOdometry::Parameters params;
    params.coord                                       = CoordinateType::BODY;
    params.frequency                                   = 10.0f;
    params.status_counter_threshold                    = 5;
    params.max_timestamp_gap_tolerance                 = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    /* No source_name have been set, the default source_name is unknown */
    SourceCheckerOdometry source_checker(params);

    ASSERT_TRUE(SourceCheckerOdometry::ObstructionLevel::LOW == source_checker.GetSourceObstructionLevel());
    /* Create a Odometry */
    OdometryType    odometry;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    odometry.SetTimestamp(sensor_timestamp);
    source_checker.CheckSourceState(odometry);
    ASSERT_TRUE(SourceCheckerOdometry::ObstructionLevel::LOW == source_checker.GetSourceObstructionLevel());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetMemberFunctionTest, getSourceInsistencyLevelCase)
{
    SourceCheckerOdometry::Parameters params;
    params.coord                                       = CoordinateType::BODY;
    params.frequency                                   = 10.0f;
    params.status_counter_threshold                    = 5;
    params.max_timestamp_gap_tolerance                 = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    /* No source_name have been set, the default source_name is unknown */
    SourceCheckerOdometry source_checker(params);

    ASSERT_TRUE(SourceCheckerOdometry::InconsistencyLevel::NORMAL == source_checker.GetSourceInconsistencyLevel());
    /* Create a Odometry */
    OdometryType    odometry;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    odometry.SetTimestamp(sensor_timestamp);
    source_checker.CheckSourceState(odometry);
    ASSERT_TRUE(SourceCheckerOdometry::InconsistencyLevel::NORMAL == source_checker.GetSourceInconsistencyLevel());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetMemberFunctionTest, getSourceActualFrequencyCase)
{
    SourceCheckerOdometry::Parameters params;
    params.coord                                       = CoordinateType::BODY;
    params.frequency                                   = 10.0f;
    params.status_counter_threshold                    = 5;
    params.max_timestamp_gap_tolerance                 = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 0.3f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    /* No source_name have been set, the default source_name is unknown */
    SourceCheckerOdometry source_checker(params);

    /* Create a Odometry */
    OdometryType    odometry;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 10u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        odometry.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(odometry);
        LOG(INFO) << "Source actual frequency: " << source_checker.GetSourceActualFrequency() << "Hz";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
