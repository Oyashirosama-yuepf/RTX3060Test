/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_source_checker_road_frame.cpp
 * @brief This file defines the test of source checker for RoadFrame type.
 * @author Wenzhi Liu (liuwenzhi@holomatic.com)
 * @date 2020-08-26
 */

#include <gtest/gtest.h>
#include <holo/localization/tools/source_checker.h>
#include <holo/localization/tools/source_checker_helper.h>

using RoadFrame              = holo::localization::RoadFrame;
using SourceCheckerRoadFrame = holo::localization::SourceCheckerT<RoadFrame>;
using SourceState            = holo::localization::SourceState;
using CoordinateType         = holo::localization::CoordinateType;
using UniqueParamters        = holo::localization::internal::RoadFrameCheckerUniqueParameters;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorTest, RoadFrameCase)
{
    SourceCheckerRoadFrame::Parameters params;
    params.coord                                       = CoordinateType(0x11010277);
    params.frequency                                   = 10.0f;
    params.status_counter_threshold                    = 5;
    params.max_timestamp_gap_tolerance                 = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    SourceCheckerRoadFrame::Ptr source_checker_ptr = std::make_shared<SourceCheckerRoadFrame>(params);
    ASSERT_TRUE(SourceState::UNSURE == source_checker_ptr->GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(LoadYamlTest, RoadFrameYamlCase)
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

    SourceCheckerRoadFrame source_checker(SourceCheckerRoadFrame::Parameters::LoadYaml(yaml_node));

    /* If the yaml file is not loaded or not completely loaded, the State of source checker is GOOD */
    ASSERT_TRUE(SourceState::UNSURE == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, DisableRoadFrameCheckerCase)
{
    SourceCheckerRoadFrame::Parameters params;
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

    SourceCheckerRoadFrame source_checker(params);
    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, IncompleteParameterSettingCase)
{
    SourceCheckerRoadFrame::Parameters params;
    params.coord          = CoordinateType(0x11010277);  // VEHICLE_GNSS_NOVATEL_REAR_MIDDLE_CENTER
    params.enable_log     = false;
    params.enable_checker = true;

    SourceCheckerRoadFrame source_checker(params);

    /* If the parameter setting is incomplete, the checker will be closed. The return state is always GOOD */
    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, NormalCase)
{
    SourceCheckerRoadFrame::Parameters params;
    params.coord                                       = CoordinateType(0x11010277);
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
    SourceCheckerRoadFrame source_checker(params);

    /* Create a Road frame */
    RoadFrame       road_frame;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        road_frame.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(road_frame);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, TimestampInconsistencyMediumCase)
{
    SourceCheckerRoadFrame::Parameters params;
    params.coord                                       = CoordinateType(0x11010277);
    params.frequency                                   = 10.0f;
    params.status_counter_threshold                    = 5;
    params.max_timestamp_gap_tolerance                 = 5.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    std::string            source_name = "roadframe0";
    SourceCheckerRoadFrame source_checker(params, source_name);

    /* Create a RoadFrame */
    RoadFrame       road_frame;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        road_frame.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(road_frame);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad RoadFrame comes in */
    holo::os::Sleep(1.0f / params.frequency + 0.07f);
    sensor_timestamp += sensor_duration;
    sensor_timestamp += holo::common::Duration(0, 7e7);
    road_frame.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(road_frame));

    holo::os::Sleep(1.0f / params.frequency - 0.07f);
    sensor_timestamp += sensor_duration;
    sensor_timestamp -= holo::common::Duration(0, 7e7);
    road_frame.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(road_frame));

    for (; measurement_i < 13u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        road_frame.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(road_frame);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, TimestampInconsistencyMaxFatalCase)
{
    SourceCheckerRoadFrame::Parameters params;
    params.coord                                       = CoordinateType(0x11010277);
    params.frequency                                   = 10.0f;
    params.status_counter_threshold                    = 5;
    params.max_timestamp_gap_tolerance                 = 1.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    std::string            source_name = "roadframe1";
    SourceCheckerRoadFrame source_checker(params, source_name);

    /* Create a RoadFrame */
    RoadFrame       road_frame;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(0.1f);
        sensor_timestamp += sensor_duration;
        road_frame.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(road_frame);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* a bad RoadFrame comes in */
    holo::os::Sleep(0.1f + 1.2f);
    sensor_timestamp += sensor_duration;
    sensor_timestamp += holo::common::Duration(1, 2e8);
    road_frame.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(road_frame));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, TimestampInconsistencyNegativeFatalCase)
{
    SourceCheckerRoadFrame::Parameters params;
    params.coord                                       = CoordinateType(0x11010277);
    params.frequency                                   = 10.0f;
    params.status_counter_threshold                    = 5;
    params.max_timestamp_gap_tolerance                 = 1.0f;
    params.min_period_multiple_in_normal_consistency   = 0.5f;
    params.max_period_multiple_in_normal_consistency   = 1.5f;
    params.min_period_multiple_in_low_obstruction      = 0.3f;
    params.source_actual_frequency_statistics_interval = 1.0f;
    params.enable_log                                  = false;
    params.enable_checker                              = true;

    std::string            source_name = "roadframe2";
    SourceCheckerRoadFrame source_checker(params, source_name);

    /* Create a RoadFrame */
    RoadFrame       road_frame;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        road_frame.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(road_frame);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* a bad RoadFrame comes in */
    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    sensor_timestamp -= holo::common::Duration(0, 2e8);
    road_frame.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(road_frame));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, SystemObstructionStateMiddleCase)
{
    SourceCheckerRoadFrame::Parameters params;

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

    std::string            source_name = "roadframe3";
    SourceCheckerRoadFrame source_checker(params, source_name);

    /* Create a RoadFrame */
    RoadFrame       road_frame;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        road_frame.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(road_frame);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad RoadFrame comes in */
    holo::os::Sleep(1.0f / params.frequency + 0.2f);
    sensor_timestamp += sensor_duration;
    road_frame.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::UNSURE == source_checker.CheckSourceState(road_frame));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, SystemObstructionStateHighCase)
{
    SourceCheckerRoadFrame::Parameters params;

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
    SourceCheckerRoadFrame source_checker(params, "");

    /* Create a RoadFrame */
    RoadFrame       road_frame;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        road_frame.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(road_frame);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad RoadFrame comes in */
    holo::os::Sleep(1.0f / params.frequency + 1.2f);
    sensor_timestamp += sensor_duration;
    road_frame.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(road_frame));

    for (; measurement_i < 10u; measurement_i++)
    {
        sensor_timestamp += sensor_duration;
        road_frame.SetTimestamp(sensor_timestamp);
        ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(road_frame));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, UniqueFunctionConfidenceNotEnoughCase)
{
    using LaneBoundaryType = holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float32_t, 3UL>>;
    SourceCheckerRoadFrame::Parameters params;
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
    unique_params.detected_lane_confidence_threshold = 50;
    unique_params.detected_lane_too_narrow_threshold = 2.8;
    unique_params.detected_lane_too_wide_threshold   = 5.2;

    std::string source_name = "roadframe4";
    auto        function =
        std::bind(holo::localization::internal::CheckRoadFrameUniqueState, unique_params, std::placeholders::_1);

    SourceCheckerRoadFrame source_checker(params, source_name, function);

    /* Create a RoadFrame */
    RoadFrame       road_frame;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    LaneBoundaryType& left_lane  = road_frame[1u];
    LaneBoundaryType& right_lane = road_frame[2u];

    left_lane.SetConfidence(30);
    left_lane.SetCoordinateRange(0, 1);
    right_lane.SetConfidence(80);
    right_lane.SetCoordinateRange(0, 1);

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        road_frame.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(road_frame);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    /* A bad RoadFrame comes in */
    right_lane.SetConfidence(30);
    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    road_frame.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(road_frame));
    ASSERT_TRUE(SourceState::BAD == source_checker.GetSourceState());

    right_lane.SetConfidence(80);
    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    road_frame.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::GOOD == source_checker.CheckSourceState(road_frame));
    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CheckSourceStateTest, UniqueFunctionAbnormalRoadWidthCase)
{
    using LaneBoundaryType = holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float32_t, 3UL>>;
    SourceCheckerRoadFrame::Parameters params;
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
    unique_params.detected_lane_confidence_threshold = 50;
    unique_params.detected_lane_too_narrow_threshold = 2.8;
    unique_params.detected_lane_too_wide_threshold   = 5.2;

    std::string source_name = "roadframe5";
    auto        function =
        std::bind(holo::localization::internal::CheckRoadFrameUniqueState, unique_params, std::placeholders::_1);
    SourceCheckerRoadFrame source_checker(params, source_name, function);

    /* Create a RoadFrame */
    RoadFrame road_frame;

    uint8_t           measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);
    LaneBoundaryType& left_lane  = road_frame[1u];
    LaneBoundaryType& right_lane = road_frame[2u];

    holo::numerics::Polynomial<holo::float32_t, 3UL> curve;
    curve.SetCoefficient<0>(2);
    LaneBoundaryType lane_1(curve);
    lane_1.SetConfidence(80);
    lane_1.SetCoordinateRange(0, 1);
    left_lane  = lane_1;
    right_lane = lane_1;

    for (; measurement_i < 5u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        road_frame.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(road_frame);
    }

    ASSERT_TRUE(SourceState::GOOD == source_checker.GetSourceState());

    curve.SetCoefficient<0>(1);
    LaneBoundaryType lane_2(curve);
    lane_2.SetConfidence(80);
    lane_2.SetCoordinateRange(0, 1);
    left_lane  = lane_2;
    right_lane = lane_2;

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    road_frame.SetTimestamp(sensor_timestamp);
    ASSERT_TRUE(SourceState::BAD == source_checker.CheckSourceState(road_frame));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetMemberFunctionTest, getSourceInsistencyLevelCase)
{
    SourceCheckerRoadFrame::Parameters params;
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
    SourceCheckerRoadFrame source_checker(params);

    ASSERT_TRUE(SourceCheckerRoadFrame::InconsistencyLevel::NORMAL == source_checker.GetSourceInconsistencyLevel());
    /* Create a RoadFrame */
    RoadFrame       road_frame;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    road_frame.SetTimestamp(sensor_timestamp);
    source_checker.CheckSourceState(road_frame);
    ASSERT_TRUE(SourceCheckerRoadFrame::InconsistencyLevel::NORMAL == source_checker.GetSourceInconsistencyLevel());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetMemberFunctionTest, getSourceObstructionLevelCase)
{
    SourceCheckerRoadFrame::Parameters params;
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
    SourceCheckerRoadFrame source_checker(params);

    ASSERT_TRUE(SourceCheckerRoadFrame::ObstructionLevel::LOW == source_checker.GetSourceObstructionLevel());
    /* Create a RoadFrame */
    RoadFrame       road_frame;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    holo::os::Sleep(1.0f / params.frequency);
    sensor_timestamp += sensor_duration;
    road_frame.SetTimestamp(sensor_timestamp);
    source_checker.CheckSourceState(road_frame);
    ASSERT_TRUE(SourceCheckerRoadFrame::ObstructionLevel::LOW == source_checker.GetSourceObstructionLevel());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetMemberFunctionTest, getSourceActualFrequencyCase)
{
    SourceCheckerRoadFrame::Parameters params;
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
    SourceCheckerRoadFrame source_checker(params);

    /* Create a RoadFrame */
    RoadFrame       road_frame;
    uint8_t         measurement_i = 0;
    holo::common::Timestamp sensor_timestamp(0, 0);
    holo::common::Duration  sensor_duration(0, 1e8);

    for (; measurement_i < 10u; measurement_i++)
    {
        holo::os::Sleep(1.0f / params.frequency);
        sensor_timestamp += sensor_duration;
        road_frame.SetTimestamp(sensor_timestamp);
        source_checker.CheckSourceState(road_frame);
        LOG(INFO) << "Source actual frequency: " << source_checker.GetSourceActualFrequency() << "Hz";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
