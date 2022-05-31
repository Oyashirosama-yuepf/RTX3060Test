/*!
 * @file test_source_checker.cpp
 * @brief Unit test for source checker imu.
 * @author lichao@holomatic.com
 * @date Jul 02, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <gtest/gtest.h>
#include <holo/localization/tools/source_checker.h>

using SourceCheckerImu = holo::localization::SourceCheckerImu;
using SourceState      = holo::localization::SourceState;
using ImuType          = holo::localization::ImuType;
using CoordinateType   = holo::localization::CoordinateType;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorTest, ImuCase)
{
    SourceCheckerImu::Parameters params;
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

    SourceCheckerImu::Ptr source_checker_ptr = std::make_shared<SourceCheckerImu>(params);
    ASSERT_TRUE(SourceState::UNSURE == source_checker_ptr->GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LoadYamlTest, ImuYamlCase)
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

    SourceCheckerImu source_checker(SourceCheckerImu::Parameters::LoadYaml(yaml_node));

    /* If the yaml file is not loaded or not completely loaded, the State of source checker is GOOD */
    ASSERT_TRUE(SourceState::UNSURE == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, DisableImuCheckerCase)
{
    SourceCheckerImu::Parameters params;
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

    SourceCheckerImu source_checker(params);
    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, IncompleteParameterSettingCase)
{
    SourceCheckerImu::Parameters params;
    params.coord          = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.enable_log     = false;
    params.enable_checker = true;

    SourceCheckerImu source_checker(params);

    /* If the parameter setting is incomplete, the checker will be closed. The return state is always GOOD */
    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, NormalCase)
{
    SourceCheckerImu::Parameters params;
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
    SourceCheckerImu source_checker(params);

    /* Create a Imu */
    ImuType         imu;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    imu.SetStatus(ImuType::Status::ALLGOOD);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        imu.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(imu);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad Imu comes in */
    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    imu.SetTimestamp(sensor_timestamp);
    imu.SetStatus(ImuType::Status::GYROZERROR);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(imu));

    imu.SetStatus(ImuType::Status::ALLGOOD);

    for (; measurement_i < 11u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        imu.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(imu);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, StatusBadCase)
{
    SourceCheckerImu::Parameters params;
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

    std::string      souce_name = "imu0";
    SourceCheckerImu source_checker(params, souce_name);

    /* Create a Imu */
    ImuType         imu;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    imu.SetStatus(ImuType::Status::GYROZERROR);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        imu.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(imu);
    }

    ASSERT_TRUE(SourceState::BAD == source_checker.GetSourceState());

    /* A good Imu comes in */
    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    imu.SetTimestamp(sensor_timestamp);
    imu.SetStatus(ImuType::Status::ALLGOOD);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(imu));

    for (; measurement_i < 15u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        imu.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(imu);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, TimestampInconsistencyMediumCase)
{
    SourceCheckerImu::Parameters params;
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

    std::string      souce_name = "imu1";
    SourceCheckerImu source_checker(params, souce_name);

    /* Create a Imu */
    ImuType         imu;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    imu.SetStatus(ImuType::Status::ALLGOOD);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        imu.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(imu);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad Imu comes in */
    holo::os::Sleep(1.0f / params.frequency + 0.2f);
    sensor_timestamp += sensor_duration;
    sensor_timestamp += holo::common::Duration(0, 2e8);
    imu.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(imu));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, TimestampInconsistencyMaxFatalCase)
{
    SourceCheckerImu::Parameters params;
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

    std::string      souce_name = "imu2";
    SourceCheckerImu source_checker(params, souce_name);

    /* Create a Imu */
    ImuType         imu;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    imu.SetStatus(ImuType::Status::ALLGOOD);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(0.1f);
        sensor_timestamp += sensor_duration;
        imu.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(imu);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad Imu comes in */
    holo::os::Sleep(0.1f + 1.2f);
    sensor_timestamp += sensor_duration;
    sensor_timestamp += holo::common::Duration(1, 2e8);
    imu.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(imu));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, TimestampInconsistencyNegativeFatalCase)
{
    SourceCheckerImu::Parameters params;
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

    std::string      souce_name = "imu3";
    SourceCheckerImu source_checker(params, souce_name);

    /* Create a Imu */
    ImuType         imu;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    imu.SetStatus(ImuType::Status::ALLGOOD);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        imu.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(imu);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad Imu comes in */
    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    sensor_timestamp -= holo::common::Duration(0, 2e8);
    imu.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(imu));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, SystemObstructionStateMiddleCase)
{
    SourceCheckerImu::Parameters params;

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

    std::string      source_name = "imu4";
    SourceCheckerImu source_checker(params, source_name);

    /* Create a Imu */
    ImuType         imu;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    imu.SetStatus(ImuType::Status::ALLGOOD);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        imu.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(imu);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad Imu comes in */
    holo::os::Sleep(1.0f / params.frequency + 0.2f);
    sensor_timestamp += sensor_duration;
    imu.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(imu));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, SystemObstructionStateHighCase)
{
    SourceCheckerImu::Parameters params;

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
    SourceCheckerImu source_checker(params, "");

    /* Create a Imu */
    ImuType         imu;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    imu.SetStatus(ImuType::Status::ALLGOOD);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        imu.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(imu);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad Imu comes in */
    holo::os::Sleep(1.0f / params.frequency + 1.2f);
    sensor_timestamp += sensor_duration;
    imu.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(imu));

    for (; measurement_i < 10u; measurement_i++)
    {
        sensor_timestamp += sensor_duration;
        imu.SetTimestamp(sensor_timestamp);
        ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(imu));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetMemberFunctionTest, getSourceInsistencyLevelCase)
{
    SourceCheckerImu::Parameters params;
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
    SourceCheckerImu source_checker(params);

    ASSERT_TRUE(SourceCheckerImu::InconsistencyLevel::NORMAL == source_checker.GetSourceInconsistencyLevel());
    /* Create a Imu */
    ImuType         imu;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    imu.SetTimestamp(sensor_timestamp);
    source_checker.CheckSourceState(imu);
    ASSERT_TRUE(SourceCheckerImu::InconsistencyLevel::NORMAL == source_checker.GetSourceInconsistencyLevel());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetMemberFunctionTest, getSourceObstructionLevelCase)
{
    SourceCheckerImu::Parameters params;
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
    SourceCheckerImu source_checker(params);

    ASSERT_TRUE(SourceCheckerImu::ObstructionLevel::LOW == source_checker.GetSourceObstructionLevel());
    /* Create a Imu */
    ImuType         imu;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    imu.SetTimestamp(sensor_timestamp);
    source_checker.CheckSourceState(imu);
    ASSERT_TRUE(SourceCheckerImu::ObstructionLevel::LOW == source_checker.GetSourceObstructionLevel());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetMemberFunctionTest, getSourceActualFrequencyCase)
{
    SourceCheckerImu::Parameters params;
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
    SourceCheckerImu source_checker(params);

    /* Create a Imu */
    ImuType         imu;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 10u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        imu.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(imu);
        LOG(INFO) << "Source actual frequency: " << source_checker.GetSourceActualFrequency() << "Hz";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
