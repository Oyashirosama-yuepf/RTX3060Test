/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_source_checker_chassis_state.cpp
 * @brief This file defines the test of source checker for ChassisState type.
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Apr 20, 2020
 */

#include <gtest/gtest.h>
#include <holo/localization/tools/source_checker.h>
#include <holo/log/hololog.h>

using ChassisState              = holo::localization::ChassisState;
using SourceCheckerChassisState = holo::localization::SourceCheckerT<ChassisState>;
using SourceState               = holo::localization::SourceState;
using CoordinateType            = holo::localization::CoordinateType;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorTest, ChassisStateCase)
{
    SourceCheckerChassisState::Parameters params;
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

    SourceCheckerChassisState::Ptr source_checker_ptr = std::make_shared<SourceCheckerChassisState>(params);
    ASSERT_TRUE(SourceState::UNSURE == source_checker_ptr->GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LoadYamlTest, ChassisStateYamlCase)
{
    holo::yaml::Node yaml_node;

    yaml_node["enable_checker"] = static_cast<bool>(true);

    try
    {
        SourceCheckerChassisState::Parameters::LoadYaml(yaml_node);
    }
    catch (const std::exception& e)
    {
        LOG(WARNING) << e.what();
    }

    yaml_node["frequency"]                                   = static_cast<float>(10.0f);
    yaml_node["status_counter_threshold"]                    = static_cast<int>(5);
    yaml_node["max_timestamp_gap_tolerance"]                 = static_cast<float>(1.0f);
    yaml_node["min_period_multiple_in_normal_consistency"]   = static_cast<float>(0.5f);
    yaml_node["max_period_multiple_in_normal_consistency"]   = static_cast<float>(1.5f);
    yaml_node["min_period_multiple_in_low_obstruction"]      = static_cast<float>(0.3f);
    yaml_node["source_actual_frequency_statistics_interval"] = static_cast<float>(1.0f);
    yaml_node["enable_log"]                                  = static_cast<bool>(false);
    yaml_node["coordinate"]                                  = static_cast<std::string>("0x11010277");

    SourceCheckerChassisState source_checker(SourceCheckerChassisState::Parameters::LoadYaml(yaml_node));

    /* If the yaml file is not loaded or not completely loaded, the State of source checker is GOOD */
    ASSERT_TRUE(SourceState::UNSURE == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, DisableChassisStateCheckerCase)
{
    SourceCheckerChassisState::Parameters params;
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

    SourceCheckerChassisState source_checker(params);
    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* Create a ChassisState */
    ChassisState chassis_state;
    ASSERT_TRUE(SourceState::GOOD == source_checker.CheckSourceState(chassis_state));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, IncompleteParameterSettingCase)
{
    SourceCheckerChassisState::Parameters params;
    params.coord          = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.enable_log     = false;
    params.enable_checker = true;

    SourceCheckerChassisState source_checker(params);

    /* If the parameter setting is incomplete, the checker will be closed. The return state is always GOOD */
    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, NormalCase)
{
    SourceCheckerChassisState::Parameters params;
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
    SourceCheckerChassisState source_checker(params);

    /* Create a ChassisState */
    ChassisState    chassis_state;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        chassis_state.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(chassis_state);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, TimestampInconsistencyMediumCase)
{
    SourceCheckerChassisState::Parameters params;
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

    std::string               source_name = "chassis0";
    SourceCheckerChassisState source_checker(params, source_name);

    /* Create a ChassisState */
    ChassisState    chassis_state;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        chassis_state.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(chassis_state);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    for (; measurement_i < 10u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency - 0.07f);
        sensor_timestamp += sensor_duration;
        sensor_timestamp -= holo::common::Duration(0, 7e7);
        chassis_state.SetTimestamp(sensor_timestamp);
        ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(chassis_state));
    }

    holo::os::Sleep(1.0f / params.frequency + 0.07f);
    sensor_timestamp += sensor_duration;
    sensor_timestamp += holo::common::Duration(0, 7e7);
    chassis_state.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(chassis_state));

    holo::os::Sleep(1.0f / params.frequency + 0.07f);
    sensor_timestamp += sensor_duration;
    sensor_timestamp += holo::common::Duration(0, 7e7);
    chassis_state.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(chassis_state));

    for (; measurement_i < 18u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        chassis_state.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(chassis_state);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, TimestampInconsistencyMaxFatalCase)
{
    SourceCheckerChassisState::Parameters params;
    params.coord                                       = CoordinateType::BODY;
    params.frequency                                   = 10.0f;
    params.status_counter_threshold                    = 5;
    params.max_timestamp_gap_tolerance                 = 1.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    std::string               source_name = "chassis1";
    SourceCheckerChassisState source_checker(params, source_name);

    /* Create a ChassisState */
    ChassisState    chassis_state;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(0.1f);
        sensor_timestamp += sensor_duration;
        chassis_state.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(chassis_state);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* a bad ChassisState comes in */
    holo::os::Sleep(0.1f + 1.2f);
    sensor_timestamp += sensor_duration;
    sensor_timestamp += holo::common::Duration(1, 2e8);
    chassis_state.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(chassis_state));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, TimestampInconsistencyNegativeFatalCase)
{
    SourceCheckerChassisState::Parameters params;
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

    std::string               source_name = "chassis2";
    SourceCheckerChassisState source_checker(params, source_name);

    /* Create a ChassisState */
    ChassisState    chassis_state;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        chassis_state.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(chassis_state);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* a bad ChassisState comes in */
    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    sensor_timestamp -= holo::common::Duration(0, 2e8);
    chassis_state.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(chassis_state));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, SystemObstructionStateMiddleCase)
{
    SourceCheckerChassisState::Parameters params;

    params.coord                                       = CoordinateType(0x11010277);
    params.frequency                                   = 10.0f;
    params.status_counter_threshold                    = 5;
    params.max_timestamp_gap_tolerance                 = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = true;  // print log file
    params.enable_checker                              = true;

    std::string               source_name = "chassis3";
    SourceCheckerChassisState source_checker(params, source_name);

    /* Create a ChassisState */
    ChassisState    chassis_state;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        chassis_state.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(chassis_state);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad ChassisState comes in */
    holo::os::Sleep(1.0f / params.frequency + 0.2f);
    sensor_timestamp += sensor_duration;
    chassis_state.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(chassis_state));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, SystemObstructionStateHighCase)
{
    SourceCheckerChassisState::Parameters params;

    params.coord                                       = CoordinateType(0x11010277);
    params.frequency                                   = 10.0f;
    params.status_counter_threshold                    = 5;
    params.max_timestamp_gap_tolerance                 = 1.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = true;  // print log file
    params.enable_checker                              = true;

    /* Although enable_ Log is true, but the source name is set to empty, so the log file is not printed */
    SourceCheckerChassisState source_checker(params, "");

    /* Create a ChassisState */
    ChassisState    chassis_state;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        chassis_state.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(chassis_state);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad ChassisState comes in */
    holo::os::Sleep(1.0f / params.frequency + 1.2f);
    sensor_timestamp += sensor_duration;
    chassis_state.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(chassis_state));

    for (; measurement_i < 10u; measurement_i++)
    {
        sensor_timestamp += sensor_duration;
        chassis_state.SetTimestamp(sensor_timestamp);
        ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(chassis_state));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetMemberFunctionTest, getSourceInsistencyLevelCase)
{
    SourceCheckerChassisState::Parameters params;
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
    SourceCheckerChassisState source_checker(params);

    ASSERT_TRUE(SourceCheckerChassisState::InconsistencyLevel::NORMAL == source_checker.GetSourceInconsistencyLevel());
    /* Create a ChassisState */
    ChassisState    chassis_state;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    chassis_state.SetTimestamp(sensor_timestamp);
    source_checker.CheckSourceState(chassis_state);
    ASSERT_TRUE(SourceCheckerChassisState::InconsistencyLevel::NORMAL == source_checker.GetSourceInconsistencyLevel());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetMemberFunctionTest, getSourceObstructionLevelCase)
{
    SourceCheckerChassisState::Parameters params;
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
    SourceCheckerChassisState source_checker(params);

    ASSERT_TRUE(SourceCheckerChassisState::ObstructionLevel::LOW == source_checker.GetSourceObstructionLevel());
    /* Create a ChassisState */
    ChassisState    chassis_state;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    chassis_state.SetTimestamp(sensor_timestamp);
    source_checker.CheckSourceState(chassis_state);
    ASSERT_TRUE(SourceCheckerChassisState::ObstructionLevel::LOW == source_checker.GetSourceObstructionLevel());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetMemberFunctionTest, getSourceActualFrequencyCase)
{
    SourceCheckerChassisState::Parameters params;
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
    SourceCheckerChassisState source_checker(params);

    /* Create a ChassisState */
    ChassisState    chassis_state;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 10u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        chassis_state.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(chassis_state);
        LOG(INFO) << "Source actual frequency: " << source_checker.GetSourceActualFrequency() << "Hz";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
