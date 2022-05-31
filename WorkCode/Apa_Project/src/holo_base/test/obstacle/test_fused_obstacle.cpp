/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_fused_obstacle.cpp
 * @brief This file implements test for FusedObstacleT.
 * @author Zhou Huishuang(zhouhuishuang@holomaitc.com)
 * @date 2021-10-25
 */

#include <gtest/gtest.h>
#include <holo/obstacle/fused_obstacle.h>

using namespace holo;
using holo::common::Classification;
using holo::numerics::Vector3f;

using FusedObstacleType = holo::gh02::obstacle::FusedObstacleT<holo::float32_t, 10U>;

TEST(FusedObstacleT, DefaultConstructor)
{
    FusedObstacleType obs;
    ASSERT_EQ(obs.GetHistoryInfo().size(), 0);
    ASSERT_EQ(obs.GetObstacleId(), 0);
    ASSERT_EQ(obs.GetConfidence(), 0);
    ASSERT_EQ(obs.GetClassificationConfidence(), 0);
    ASSERT_EQ(obs.GetAbsoluteVelocity(), FusedObstacleType::Point3Type());
    ASSERT_EQ(obs.GetRelativeVelocity(), FusedObstacleType::Point3Type());
    ASSERT_EQ(obs.GetAbsoluteAccelaration(), FusedObstacleType::Point3Type());
    ASSERT_EQ(obs.GetHeadingAngle(), 0.0);
    ASSERT_EQ(obs.GetHeadingAngularVelocity(), 0.0);
    ASSERT_EQ(obs.GetBbox3dWidth(), 0.0);
    ASSERT_EQ(obs.GetBbox3dHeight(), 0.0);
    ASSERT_EQ(obs.GetBbox3dDepth(), 0.0);
    ASSERT_EQ(obs.GetHeadingAngleStd(), 0.0);
    ASSERT_EQ(obs.GetTrackingPeriod(), 0.0);
    ASSERT_EQ(obs.IsMovable(), false);
    ASSERT_EQ(obs.IsHeadingToEgoCar(), false);
    ASSERT_EQ(obs.IsEverHeadingToEgoCar(), false);
    ASSERT_EQ(obs.GetLampStatus(), FusedObstacleType::LampStatus::NONE);

    ASSERT_EQ(obs.GetTrackingStatus(), FusedObstacleType::TrackingStatus::INVALID);
    ASSERT_EQ(obs.GetCutInStatus(), FusedObstacleType::CutInStatus::UNKNOWN);
    ASSERT_EQ(obs.GetMovingStatus(), FusedObstacleType::MovingStatus::STATIC);
    ASSERT_EQ(obs.GetPredictPath().size(), 0);
    ASSERT_EQ(obs.Getpolygon().size(), 0);

    for (size_t i = 0; i < 3U; i++)
    {
        for (size_t j = 0; j < 3U; j++)
        {
            ASSERT_EQ(obs.GetPositionCov()[i][j], 0);
            ASSERT_EQ(obs.GetvelocityCov()[i][j], 0);
            ASSERT_EQ(obs.GetAccelarationCov()[i][j], 0);
            ASSERT_EQ(obs.GetSizeCov()[i][j], 0);
        }
    }
}

TEST(FusedObstacleT, SetAndGetHistoryInfo)
{
    FusedObstacleType obs;

    FusedObstacleType::HistoryInfo hi1, hi2;
    hi1.obstacle_id                         = 5;
    hi1.sensor_id                           = 0x01020304U;
    hi1.raw_sensor_capture_timestamp        = Timestamp(1, 2);
    hi1.sensor_perception_capture_timestamp = Timestamp(3, 4);
    hi1.sensor_perception_output_timestamp  = Timestamp(5, 6);
    hi1.fusion_capture_timestamp            = Timestamp(7, 8);
    hi1.fusion_output_timestamp             = Timestamp(9, 10);

    hi2.obstacle_id                         = 10;
    hi2.sensor_id                           = 0x01020305U;
    hi2.raw_sensor_capture_timestamp        = Timestamp(10, 20);
    hi2.sensor_perception_capture_timestamp = Timestamp(30, 40);
    hi2.sensor_perception_output_timestamp  = Timestamp(50, 60);
    hi2.fusion_capture_timestamp            = Timestamp(70, 80);
    hi2.fusion_output_timestamp             = Timestamp(90, 100);

    holo::container::Vector<FusedObstacleType::HistoryInfo, 32U> history_infos;
    history_infos.push_back(hi1);
    history_infos.push_back(hi2);

    obs.SetHistoryInfo(history_infos);
    ASSERT_EQ(obs.GetHistoryInfo().size(), 2);
    ASSERT_EQ(obs.GetHistoryInfo()[0].obstacle_id, hi1.obstacle_id);
    ASSERT_EQ(obs.GetHistoryInfo()[0].sensor_id, hi1.sensor_id);
    ASSERT_EQ(obs.GetHistoryInfo()[0].raw_sensor_capture_timestamp, hi1.raw_sensor_capture_timestamp);
    ASSERT_EQ(obs.GetHistoryInfo()[0].sensor_perception_capture_timestamp, hi1.sensor_perception_capture_timestamp);
    ASSERT_EQ(obs.GetHistoryInfo()[0].sensor_perception_output_timestamp, hi1.sensor_perception_output_timestamp);
    ASSERT_EQ(obs.GetHistoryInfo()[0].fusion_capture_timestamp, hi1.fusion_capture_timestamp);
    ASSERT_EQ(obs.GetHistoryInfo()[0].fusion_output_timestamp, hi1.fusion_output_timestamp);

    ASSERT_EQ(obs.GetHistoryInfo()[1].obstacle_id, hi2.obstacle_id);
    ASSERT_EQ(obs.GetHistoryInfo()[1].sensor_id, hi2.sensor_id);
    ASSERT_EQ(obs.GetHistoryInfo()[1].raw_sensor_capture_timestamp, hi2.raw_sensor_capture_timestamp);
    ASSERT_EQ(obs.GetHistoryInfo()[1].sensor_perception_capture_timestamp, hi2.sensor_perception_capture_timestamp);
    ASSERT_EQ(obs.GetHistoryInfo()[1].sensor_perception_output_timestamp, hi2.sensor_perception_output_timestamp);
    ASSERT_EQ(obs.GetHistoryInfo()[1].fusion_capture_timestamp, hi2.fusion_capture_timestamp);
    ASSERT_EQ(obs.GetHistoryInfo()[1].fusion_output_timestamp, hi2.fusion_output_timestamp);
}

TEST(FusedObstacleT, SetAndGetObstacleId)
{
    FusedObstacleType obs;
    obs.SetObstacleId(2);
    ASSERT_EQ(obs.GetObstacleId(), 2);
}

TEST(FusedObstacleT, SetAndGetClassification)
{
    FusedObstacleType obs;
    obs.SetClassification(Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::ANIMAL_DOG));
    ASSERT_EQ(obs.GetClassification(),
              Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::ANIMAL_DOG));
}

TEST(FusedObstacleT, SetAndGetPosition)
{
    FusedObstacleType obs;
    obs.SetPosition(FusedObstacleType::Point3Type(1.0, 2.0, 3.0));
    ASSERT_EQ(obs.GetPosition(), FusedObstacleType::Point3Type(1.0, 2.0, 3.0));
}

TEST(FusedObstacleT, SetAndGetExistConfidence)
{
    FusedObstacleType obs;
    obs.SetExistConfidence(5);
    ASSERT_EQ(obs.GetExistConfidence(), 5);
}

TEST(FusedObstacleT, SetAndGetConfidence)
{
    FusedObstacleType obs;
    obs.SetConfidence(2);
    ASSERT_EQ(obs.GetConfidence(), 2);
}

TEST(FusedObstacleT, SetAndGetClassificationConfidence)
{
    FusedObstacleType obs;
    obs.SetClassificationConfidence(3);
    ASSERT_EQ(obs.GetClassificationConfidence(), 3);
}

TEST(FusedObstacleT, SetAndGetAbsoluteVelocity)
{
    FusedObstacleType obs;
    obs.SetAbsoluteVelocity(FusedObstacleType::Point3Type(1.0, 2.0, 3.0));
    ASSERT_EQ(obs.GetAbsoluteVelocity(), FusedObstacleType::Point3Type(1.0, 2.0, 3.0));
}

TEST(FusedObstacleT, SetAndGetAbsoluteVelocityWithTemplateType)
{
    FusedObstacleType obs;
    obs.SetAbsoluteVelocity(1.0, 2.0, 3.0);
    ASSERT_EQ(obs.GetAbsoluteVelocity<holo::numerics::Vector3f>(), holo::numerics::Vector3f(1.0, 2.0, 3.0));
}

TEST(FusedObstacleT, SetAndGetRelativeVelocity)
{
    FusedObstacleType obs;
    obs.SetRelativeVelocity(FusedObstacleType::Point3Type(1.1, 2.1, 3.1));
    ASSERT_EQ(obs.GetRelativeVelocity(), FusedObstacleType::Point3Type(1.1, 2.1, 3.1));
}

TEST(FusedObstacleT, SetAndGetRelativeVelocityWithTemplateType)
{
    FusedObstacleType obs;
    obs.SetRelativeVelocity(1.0, 2.0, 3.0);
    ASSERT_EQ(obs.GetRelativeVelocity<holo::numerics::Vector3f>(), holo::numerics::Vector3f(1.0, 2.0, 3.0));
}

TEST(FusedObstacleT, SetAndGetAbsoluteAccelaration)
{
    FusedObstacleType obs;
    obs.SetAbsoluteAccelaration(FusedObstacleType::Point3Type(1.2, 2.2, 3.2));
    ASSERT_EQ(obs.GetAbsoluteAccelaration(), FusedObstacleType::Point3Type(1.2, 2.2, 3.2));
}

TEST(FusedObstacleT, SetAndGetAbsoluteAccelarationWithTemplateType)
{
    FusedObstacleType obs;
    obs.SetAbsoluteAccelaration(1.0, 2.0, 3.0);
    ASSERT_EQ(obs.GetAbsoluteAccelaration<holo::numerics::Vector3f>(), holo::numerics::Vector3f(1.0, 2.0, 3.0));
}

TEST(FusedObstacleT, SetAndGetHeadingAngle)
{
    FusedObstacleType obs;
    obs.SetHeadingAngle(2.0);
    ASSERT_EQ(obs.GetHeadingAngle(), 2.0);
}

TEST(FusedObstacleT, SetAndGetHeadingAngularVelocity)
{
    FusedObstacleType obs;
    obs.SetHeadingAngularVelocity(3.0);
    ASSERT_EQ(obs.GetHeadingAngularVelocity(), 3.0);
}

TEST(FusedObstacleT, SetAndGetBbox3dWidth)
{
    FusedObstacleType obs;
    obs.SetBbox3dWidth(4.0);
    ASSERT_EQ(obs.GetBbox3dWidth(), 4.0);
}

TEST(FusedObstacleT, SetAndGetBbox3dHeight)
{
    FusedObstacleType obs;
    obs.SetBbox3dHeight(5.0);
    ASSERT_EQ(obs.GetBbox3dHeight(), 5.0);
}

TEST(FusedObstacleT, SetAndGetBbox3dDepth)
{
    FusedObstacleType obs;
    obs.SetBbox3dDepth(6.0);
    ASSERT_EQ(obs.GetBbox3dDepth(), 6.0);
}

TEST(FusedObstacleT, SetAndGetPositionCov)
{
    FusedObstacleType                         obs;
    std::array<std::array<float32_t, 3U>, 3U> myarray;
    myarray[0] = std::array<float32_t, 3U>{0.0f, 1.0f, 2.0f};
    myarray[1] = std::array<float32_t, 3U>{3.0f, 4.0f, 5.0f};
    myarray[2] = std::array<float32_t, 3U>{6.0f, 7.0f, 8.0f};

    obs.SetPositionCov(myarray);

    ASSERT_EQ(obs.GetPositionCov()[0][0], 0.0f);
    ASSERT_EQ(obs.GetPositionCov()[0][1], 1.0f);
    ASSERT_EQ(obs.GetPositionCov()[0][2], 2.0f);
    ASSERT_EQ(obs.GetPositionCov()[1][0], 3.0f);
    ASSERT_EQ(obs.GetPositionCov()[1][1], 4.0f);
    ASSERT_EQ(obs.GetPositionCov()[1][2], 5.0f);
    ASSERT_EQ(obs.GetPositionCov()[2][0], 6.0f);
    ASSERT_EQ(obs.GetPositionCov()[2][1], 7.0f);
    ASSERT_EQ(obs.GetPositionCov()[2][2], 8.0f);
}

TEST(FusedObstacleT, SetAndGetvelocityCov)
{
    FusedObstacleType                         obs;
    std::array<std::array<float32_t, 3U>, 3U> myarray;
    myarray[0] = std::array<float32_t, 3U>{0.1f, 1.1f, 2.1f};
    myarray[1] = std::array<float32_t, 3U>{3.1f, 4.1f, 5.1f};
    myarray[2] = std::array<float32_t, 3U>{6.1f, 7.1f, 8.1f};

    obs.SetvelocityCov(myarray);

    ASSERT_EQ(obs.GetvelocityCov()[0][0], 0.1f);
    ASSERT_EQ(obs.GetvelocityCov()[0][1], 1.1f);
    ASSERT_EQ(obs.GetvelocityCov()[0][2], 2.1f);
    ASSERT_EQ(obs.GetvelocityCov()[1][0], 3.1f);
    ASSERT_EQ(obs.GetvelocityCov()[1][1], 4.1f);
    ASSERT_EQ(obs.GetvelocityCov()[1][2], 5.1f);
    ASSERT_EQ(obs.GetvelocityCov()[2][0], 6.1f);
    ASSERT_EQ(obs.GetvelocityCov()[2][1], 7.1f);
    ASSERT_EQ(obs.GetvelocityCov()[2][2], 8.1f);
}

TEST(FusedObstacleT, SetAndGetAccelarationCov)
{
}

TEST(FusedObstacleT, SetAndGetSizeCov)
{
    FusedObstacleType                         obs;
    std::array<std::array<float32_t, 3U>, 3U> myarray;
    myarray[0] = std::array<float32_t, 3U>{0.1f, 1.1f, 2.1f};
    myarray[1] = std::array<float32_t, 3U>{3.1f, 4.1f, 5.1f};
    myarray[2] = std::array<float32_t, 3U>{6.1f, 7.1f, 8.1f};

    obs.SetSizeCov(myarray);

    ASSERT_EQ(obs.GetSizeCov()[0][0], 0.1f);
    ASSERT_EQ(obs.GetSizeCov()[0][1], 1.1f);
    ASSERT_EQ(obs.GetSizeCov()[0][2], 2.1f);
    ASSERT_EQ(obs.GetSizeCov()[1][0], 3.1f);
    ASSERT_EQ(obs.GetSizeCov()[1][1], 4.1f);
    ASSERT_EQ(obs.GetSizeCov()[1][2], 5.1f);
    ASSERT_EQ(obs.GetSizeCov()[2][0], 6.1f);
    ASSERT_EQ(obs.GetSizeCov()[2][1], 7.1f);
    ASSERT_EQ(obs.GetSizeCov()[2][2], 8.1f);
}

TEST(FusedObstacleT, SetAndGetHeadingAngleStd)
{
    FusedObstacleType obs;
    obs.SetHeadingAngleStd(4.0);
    ASSERT_EQ(obs.GetHeadingAngleStd(), 4.0);
}

TEST(FusedObstacleT, SetAndGetTrackingPeriod)
{
    FusedObstacleType obs;
    obs.SetTrackingPeriod(5.0);
    ASSERT_EQ(obs.GetTrackingPeriod(), 5.0);
}

TEST(FusedObstacleT, IsMovable)
{
    FusedObstacleType obs;
    obs.SetMovableStatus(true);
    ASSERT_EQ(obs.IsMovable(), true);
}

TEST(FusedObstacleT, IsHeadingToEgoCar)
{
    FusedObstacleType obs;
    obs.SetHeadingToEgoCarStatus(true);
    ASSERT_EQ(obs.IsHeadingToEgoCar(), true);
}

TEST(FusedObstacleT, IsEverHeadingToEgoCar)
{
    FusedObstacleType obs;
    obs.SetEverHeadingToEgoCarStatus(true);
    ASSERT_EQ(obs.IsEverHeadingToEgoCar(), true);
}

TEST(FusedObstacleT, SetAndGetLampStatus)
{
    FusedObstacleType obs;
    obs.SetLampStatus(FusedObstacleType::LampStatus::BRAKE);
    ASSERT_EQ(obs.GetLampStatus(), FusedObstacleType::LampStatus::BRAKE);
}

TEST(FusedObstacleT, SetAndGetTrackingStatus)
{
    FusedObstacleType obs;
    obs.SetTrackingStatus(FusedObstacleType::TrackingStatus::NEW);
    ASSERT_EQ(obs.GetTrackingStatus(), FusedObstacleType::TrackingStatus::NEW);
}

TEST(FusedObstacleT, SetAndGetCutInStatus)
{
    FusedObstacleType obs;
    obs.SetCutInStatus(FusedObstacleType::CutInStatus::CUT_IN);
    ASSERT_EQ(obs.GetCutInStatus(), FusedObstacleType::CutInStatus::CUT_IN);
}

TEST(FusedObstacleT, SetAndGetMovingStatus)
{
    FusedObstacleType obs;
    obs.SetMovingStatus(FusedObstacleType::MovingStatus::MOVING);
    ASSERT_EQ(obs.GetMovingStatus(), FusedObstacleType::MovingStatus::MOVING);
}

TEST(FusedObstacleT, SetAndGetPredictPath)
{
    FusedObstacleType::PredictPath::PathPoint points1, points2;
    points1.timestamp     = Timestamp(1, 2);
    points1.position      = FusedObstacleType::Point2Type(10.0, 20.0);
    points1.heading_angle = 5.0;
    points1.velocity      = FusedObstacleType::Point2Type(1.1, 2.2);

    points2.timestamp     = Timestamp(10, 20);
    points2.position      = FusedObstacleType::Point2Type(11.0, 21.0);
    points2.heading_angle = 3.5;
    points2.velocity      = FusedObstacleType::Point2Type(1.3, 2.3);

    holo::container::Vector<FusedObstacleType::PredictPath::PathPoint, 10U> path_point;
    path_point.push_back(points1);
    path_point.push_back(points2);

    FusedObstacleType::PredictPath pre_path1;
    pre_path1.SetConfidence(10);
    pre_path1.SetPathPoints(path_point);

    FusedObstacleType::PredictPath pre_path2;
    pre_path2.SetConfidence(20);
    pre_path2.SetPathPoints(path_point);

    FusedObstacleType                                            obs;
    holo::container::Vector<FusedObstacleType::PredictPath, 10U> pre_paths;
    pre_paths.push_back(pre_path1);
    pre_paths.push_back(pre_path2);
    obs.SetPredictPath(pre_paths);

    ASSERT_EQ(obs.GetPredictPath().size(), 2);

    ASSERT_EQ(obs.GetPredictPath()[0].GetConfidence(), 10);
    ASSERT_EQ(obs.GetPredictPath()[0].GetPathPoints().size(), 2);
    ASSERT_EQ(obs.GetPredictPath()[0].GetPathPoints()[0].timestamp, Timestamp(1, 2));
    ASSERT_EQ(obs.GetPredictPath()[0].GetPathPoints()[0].position, FusedObstacleType::Point2Type(10.0, 20.0));
    ASSERT_EQ(obs.GetPredictPath()[0].GetPathPoints()[0].heading_angle, 5.0);
    ASSERT_EQ(obs.GetPredictPath()[0].GetPathPoints()[0].velocity, FusedObstacleType::Point2Type(1.1, 2.2));

    ASSERT_EQ(obs.GetPredictPath()[0].GetPathPoints()[1].timestamp, Timestamp(10, 20));
    ASSERT_EQ(obs.GetPredictPath()[0].GetPathPoints()[1].position, FusedObstacleType::Point2Type(11.0, 21.0));
    ASSERT_EQ(obs.GetPredictPath()[0].GetPathPoints()[1].heading_angle, 3.5);
    ASSERT_EQ(obs.GetPredictPath()[0].GetPathPoints()[1].velocity, FusedObstacleType::Point2Type(1.3, 2.3));

    ASSERT_EQ(obs.GetPredictPath()[1].GetConfidence(), 20);
    ASSERT_EQ(obs.GetPredictPath()[1].GetPathPoints().size(), 2);
    ASSERT_EQ(obs.GetPredictPath()[1].GetPathPoints()[0].timestamp, Timestamp(1, 2));
    ASSERT_EQ(obs.GetPredictPath()[1].GetPathPoints()[0].position, FusedObstacleType::Point2Type(10.0, 20.0));
    ASSERT_EQ(obs.GetPredictPath()[1].GetPathPoints()[0].heading_angle, 5.0);
    ASSERT_EQ(obs.GetPredictPath()[1].GetPathPoints()[0].velocity, FusedObstacleType::Point2Type(1.1, 2.2));

    ASSERT_EQ(obs.GetPredictPath()[1].GetPathPoints()[1].timestamp, Timestamp(10, 20));
    ASSERT_EQ(obs.GetPredictPath()[1].GetPathPoints()[1].position, FusedObstacleType::Point2Type(11.0, 21.0));
    ASSERT_EQ(obs.GetPredictPath()[1].GetPathPoints()[1].heading_angle, 3.5);
    ASSERT_EQ(obs.GetPredictPath()[1].GetPathPoints()[1].velocity, FusedObstacleType::Point2Type(1.3, 2.3));
}

TEST(FusedObstacleT, SetAndGetpolygon)
{
    FusedObstacleType                                           obs;
    holo::container::Vector<FusedObstacleType::Point3Type, 10U> ve;
    ve.push_back(FusedObstacleType::Point3Type(1.0, 2.0, 3.0));
    ve.push_back(FusedObstacleType::Point3Type(4.0, 5.0, 6.0));

    obs.Setpolygon(ve);
    ASSERT_EQ(obs.Getpolygon().size(), 2);
    ASSERT_EQ(obs.Getpolygon()[0], FusedObstacleType::Point3Type(1.0, 2.0, 3.0));
    ASSERT_EQ(obs.Getpolygon()[1], FusedObstacleType::Point3Type(4.0, 5.0, 6.0));
}

///////////////////////////////////////////////////////////////////////////////
TEST(FusedObstacleT, SerializeAndDeserialize)
{
    FusedObstacleType obstacle_general_input, obstacle_general_output;

    FusedObstacleType::HistoryInfo hi1, hi2;
    hi1.obstacle_id                         = 5;
    hi1.sensor_id                           = 0x01020304U;
    hi1.raw_sensor_capture_timestamp        = Timestamp(1, 2);
    hi1.sensor_perception_capture_timestamp = Timestamp(3, 4);
    hi1.sensor_perception_output_timestamp  = Timestamp(5, 6);
    hi1.fusion_capture_timestamp            = Timestamp(7, 8);
    hi1.fusion_output_timestamp             = Timestamp(9, 10);

    hi2.obstacle_id                         = 10;
    hi2.sensor_id                           = 0x01020305U;
    hi2.raw_sensor_capture_timestamp        = Timestamp(10, 20);
    hi2.sensor_perception_capture_timestamp = Timestamp(30, 40);
    hi2.sensor_perception_output_timestamp  = Timestamp(50, 60);
    hi2.fusion_capture_timestamp            = Timestamp(70, 80);
    hi2.fusion_output_timestamp             = Timestamp(90, 100);

    holo::container::Vector<FusedObstacleType::HistoryInfo, 32U> history_infos;
    history_infos.push_back(hi1);
    history_infos.push_back(hi2);

    obstacle_general_input.SetHistoryInfo(history_infos);
    obstacle_general_input.SetObstacleId(5);
    obstacle_general_input.SetClassification(
        Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::ANIMAL_DOG));
    obstacle_general_input.SetExistConfidence(90.0f);
    obstacle_general_input.SetPosition(holo::geometry::Point3T<float32_t>(4.5f, 6.7f, 8.9f));

    obstacle_general_input.SetConfidence(2);
    obstacle_general_input.SetClassificationConfidence(3);
    obstacle_general_input.SetAbsoluteVelocity(FusedObstacleType::Point3Type(1.0, 2.0, 3.0));
    obstacle_general_input.SetRelativeVelocity(FusedObstacleType::Point3Type(1.1, 2.1, 3.1));
    obstacle_general_input.SetAbsoluteAccelaration(FusedObstacleType::Point3Type(1.2, 2.2, 3.2));
    obstacle_general_input.SetHeadingAngle(2.0);
    obstacle_general_input.SetHeadingAngularVelocity(3.0);
    obstacle_general_input.SetBbox3dWidth(4.0);
    obstacle_general_input.SetBbox3dHeight(5.0);
    obstacle_general_input.SetBbox3dDepth(6.0);

    std::array<std::array<float32_t, 3U>, 3U> myarray;
    myarray[0] = std::array<float32_t, 3U>{0.1f, 1.1f, 2.1f};
    myarray[1] = std::array<float32_t, 3U>{3.1f, 4.1f, 5.1f};
    myarray[2] = std::array<float32_t, 3U>{6.1f, 7.1f, 8.1f};

    obstacle_general_input.SetPositionCov(myarray);
    obstacle_general_input.SetvelocityCov(myarray);
    obstacle_general_input.SetAccelarationCov(myarray);
    obstacle_general_input.SetSizeCov(myarray);

    obstacle_general_input.SetHeadingAngleStd(4.0);
    obstacle_general_input.SetTrackingPeriod(5.0);
    obstacle_general_input.SetMovableStatus(true);
    obstacle_general_input.SetHeadingToEgoCarStatus(true);
    obstacle_general_input.SetEverHeadingToEgoCarStatus(true);
    obstacle_general_input.SetLampStatus(FusedObstacleType::LampStatus::BRAKE);
    obstacle_general_input.SetTrackingStatus(FusedObstacleType::TrackingStatus::NEW);
    obstacle_general_input.SetCutInStatus(FusedObstacleType::CutInStatus::CUT_IN);
    obstacle_general_input.SetMovingStatus(FusedObstacleType::MovingStatus::MOVING);

    FusedObstacleType::PredictPath::PathPoint points1, points2;
    points1.timestamp     = Timestamp(1, 2);
    points1.position      = FusedObstacleType::Point2Type(10.0, 20.0);
    points1.heading_angle = 5.0;
    points1.velocity      = FusedObstacleType::Point2Type(1.1, 2.2);

    points2.timestamp     = Timestamp(10, 20);
    points2.position      = FusedObstacleType::Point2Type(11.0, 21.0);
    points2.heading_angle = 3.5;
    points2.velocity      = FusedObstacleType::Point2Type(1.3, 2.3);

    holo::container::Vector<FusedObstacleType::PredictPath::PathPoint, 10U> path_point;
    path_point.push_back(points1);
    path_point.push_back(points2);

    FusedObstacleType::PredictPath pre_path1;
    pre_path1.SetConfidence(10);
    pre_path1.SetPathPoints(path_point);

    FusedObstacleType::PredictPath pre_path2;
    pre_path2.SetConfidence(20);
    pre_path2.SetPathPoints(path_point);

    FusedObstacleType                                            obs;
    holo::container::Vector<FusedObstacleType::PredictPath, 10U> pre_paths;
    pre_paths.push_back(pre_path1);
    pre_paths.push_back(pre_path2);
    obstacle_general_input.SetPredictPath(pre_paths);

    holo::container::Vector<FusedObstacleType::Point3Type, 10U> ve;
    ve.push_back(FusedObstacleType::Point3Type(1.0, 2.0, 3.0));
    ve.push_back(FusedObstacleType::Point3Type(4.0, 5.0, 6.0));

    obstacle_general_input.Setpolygon(ve);

    uint8_t                           buffer[8192];
    holo::serialization::Serializer<> serializer(buffer, 8192);
    serializer << obstacle_general_input;
    ASSERT_EQ(obstacle_general_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> obstacle_general_output;

    ASSERT_EQ(obstacle_general_input.GetObstacleId(), obstacle_general_output.GetObstacleId());
    ASSERT_EQ(obstacle_general_input.GetClassification(), obstacle_general_output.GetClassification());
    ASSERT_EQ(obstacle_general_input.GetExistConfidence(), obstacle_general_output.GetExistConfidence());
    ASSERT_EQ(obstacle_general_input.GetPosition(), obstacle_general_output.GetPosition());

    ASSERT_EQ(obstacle_general_output.GetHistoryInfo().size(), 2);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[0].obstacle_id, hi1.obstacle_id);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[0].sensor_id, hi1.sensor_id);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[0].raw_sensor_capture_timestamp,
              hi1.raw_sensor_capture_timestamp);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[0].sensor_perception_capture_timestamp,
              hi1.sensor_perception_capture_timestamp);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[0].sensor_perception_output_timestamp,
              hi1.sensor_perception_output_timestamp);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[0].fusion_capture_timestamp, hi1.fusion_capture_timestamp);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[0].fusion_output_timestamp, hi1.fusion_output_timestamp);

    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[1].obstacle_id, hi2.obstacle_id);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[1].sensor_id, hi2.sensor_id);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[1].raw_sensor_capture_timestamp,
              hi2.raw_sensor_capture_timestamp);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[1].sensor_perception_capture_timestamp,
              hi2.sensor_perception_capture_timestamp);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[1].sensor_perception_output_timestamp,
              hi2.sensor_perception_output_timestamp);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[1].fusion_capture_timestamp, hi2.fusion_capture_timestamp);
    ASSERT_EQ(obstacle_general_output.GetHistoryInfo()[1].fusion_output_timestamp, hi2.fusion_output_timestamp);

    ASSERT_EQ(obstacle_general_output.GetObstacleId(), 5);
    ASSERT_EQ(obstacle_general_output.GetConfidence(), 2);
    ASSERT_EQ(obstacle_general_output.GetClassificationConfidence(), 3);
    ASSERT_EQ(obstacle_general_output.GetAbsoluteVelocity(), FusedObstacleType::Point3Type(1.0, 2.0, 3.0));
    ASSERT_EQ(obstacle_general_output.GetRelativeVelocity(), FusedObstacleType::Point3Type(1.1, 2.1, 3.1));
    ASSERT_EQ(obstacle_general_output.GetAbsoluteAccelaration(), FusedObstacleType::Point3Type(1.2, 2.2, 3.2));
    ASSERT_EQ(obstacle_general_output.GetHeadingAngle(), 2.0);
    ASSERT_EQ(obstacle_general_output.GetHeadingAngularVelocity(), 3.0);
    ASSERT_EQ(obstacle_general_output.GetBbox3dWidth(), 4.0);
    ASSERT_EQ(obstacle_general_output.GetBbox3dHeight(), 5.0);
    ASSERT_EQ(obstacle_general_output.GetBbox3dDepth(), 6.0);

    ASSERT_EQ(obstacle_general_output.GetPositionCov()[0][0], 0.1f);
    ASSERT_EQ(obstacle_general_output.GetPositionCov()[0][1], 1.1f);
    ASSERT_EQ(obstacle_general_output.GetPositionCov()[0][2], 2.1f);
    ASSERT_EQ(obstacle_general_output.GetPositionCov()[1][0], 3.1f);
    ASSERT_EQ(obstacle_general_output.GetPositionCov()[1][1], 4.1f);
    ASSERT_EQ(obstacle_general_output.GetPositionCov()[1][2], 5.1f);
    ASSERT_EQ(obstacle_general_output.GetPositionCov()[2][0], 6.1f);
    ASSERT_EQ(obstacle_general_output.GetPositionCov()[2][1], 7.1f);
    ASSERT_EQ(obstacle_general_output.GetPositionCov()[2][2], 8.1f);

    ASSERT_EQ(obstacle_general_output.GetvelocityCov()[0][0], 0.1f);
    ASSERT_EQ(obstacle_general_output.GetvelocityCov()[0][1], 1.1f);
    ASSERT_EQ(obstacle_general_output.GetvelocityCov()[0][2], 2.1f);
    ASSERT_EQ(obstacle_general_output.GetvelocityCov()[1][0], 3.1f);
    ASSERT_EQ(obstacle_general_output.GetvelocityCov()[1][1], 4.1f);
    ASSERT_EQ(obstacle_general_output.GetvelocityCov()[1][2], 5.1f);
    ASSERT_EQ(obstacle_general_output.GetvelocityCov()[2][0], 6.1f);
    ASSERT_EQ(obstacle_general_output.GetvelocityCov()[2][1], 7.1f);
    ASSERT_EQ(obstacle_general_output.GetvelocityCov()[2][2], 8.1f);

    ASSERT_EQ(obstacle_general_output.GetAccelarationCov()[0][0], 0.1f);
    ASSERT_EQ(obstacle_general_output.GetAccelarationCov()[0][1], 1.1f);
    ASSERT_EQ(obstacle_general_output.GetAccelarationCov()[0][2], 2.1f);
    ASSERT_EQ(obstacle_general_output.GetAccelarationCov()[1][0], 3.1f);
    ASSERT_EQ(obstacle_general_output.GetAccelarationCov()[1][1], 4.1f);
    ASSERT_EQ(obstacle_general_output.GetAccelarationCov()[1][2], 5.1f);
    ASSERT_EQ(obstacle_general_output.GetAccelarationCov()[2][0], 6.1f);
    ASSERT_EQ(obstacle_general_output.GetAccelarationCov()[2][1], 7.1f);
    ASSERT_EQ(obstacle_general_output.GetAccelarationCov()[2][2], 8.1f);

    ASSERT_EQ(obstacle_general_output.GetSizeCov()[0][0], 0.1f);
    ASSERT_EQ(obstacle_general_output.GetSizeCov()[0][1], 1.1f);
    ASSERT_EQ(obstacle_general_output.GetSizeCov()[0][2], 2.1f);
    ASSERT_EQ(obstacle_general_output.GetSizeCov()[1][0], 3.1f);
    ASSERT_EQ(obstacle_general_output.GetSizeCov()[1][1], 4.1f);
    ASSERT_EQ(obstacle_general_output.GetSizeCov()[1][2], 5.1f);
    ASSERT_EQ(obstacle_general_output.GetSizeCov()[2][0], 6.1f);
    ASSERT_EQ(obstacle_general_output.GetSizeCov()[2][1], 7.1f);
    ASSERT_EQ(obstacle_general_output.GetSizeCov()[2][2], 8.1f);

    ASSERT_EQ(obstacle_general_output.GetHeadingAngleStd(), 4.0);
    ASSERT_EQ(obstacle_general_output.GetTrackingPeriod(), 5.0);
    ASSERT_EQ(obstacle_general_output.IsMovable(), true);
    ASSERT_EQ(obstacle_general_output.IsHeadingToEgoCar(), true);
    ASSERT_EQ(obstacle_general_output.IsEverHeadingToEgoCar(), true);
    ASSERT_EQ(obstacle_general_output.GetLampStatus(), FusedObstacleType::LampStatus::BRAKE);
    ASSERT_EQ(obstacle_general_output.GetTrackingStatus(), FusedObstacleType::TrackingStatus::NEW);
    ASSERT_EQ(obstacle_general_output.GetCutInStatus(), FusedObstacleType::CutInStatus::CUT_IN);
    ASSERT_EQ(obstacle_general_output.GetMovingStatus(), FusedObstacleType::MovingStatus::MOVING);

    ASSERT_EQ(obstacle_general_output.GetPredictPath().size(), 2);
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[0].GetConfidence(), 10);
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[0].GetPathPoints().size(), 2);
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[0].GetPathPoints()[0].timestamp, Timestamp(1, 2));
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[0].GetPathPoints()[0].position,
              FusedObstacleType::Point2Type(10.0, 20.0));
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[0].GetPathPoints()[0].heading_angle, 5.0);
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[0].GetPathPoints()[0].velocity,
              FusedObstacleType::Point2Type(1.1, 2.2));

    ASSERT_EQ(obstacle_general_output.GetPredictPath()[0].GetPathPoints()[1].timestamp, Timestamp(10, 20));
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[0].GetPathPoints()[1].position,
              FusedObstacleType::Point2Type(11.0, 21.0));
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[0].GetPathPoints()[1].heading_angle, 3.5);
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[0].GetPathPoints()[1].velocity,
              FusedObstacleType::Point2Type(1.3, 2.3));

    ASSERT_EQ(obstacle_general_output.GetPredictPath()[1].GetConfidence(), 20);
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[1].GetPathPoints().size(), 2);
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[1].GetPathPoints()[0].timestamp, Timestamp(1, 2));
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[1].GetPathPoints()[0].position,
              FusedObstacleType::Point2Type(10.0, 20.0));
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[1].GetPathPoints()[0].heading_angle, 5.0);
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[1].GetPathPoints()[0].velocity,
              FusedObstacleType::Point2Type(1.1, 2.2));

    ASSERT_EQ(obstacle_general_output.GetPredictPath()[1].GetPathPoints()[1].timestamp, Timestamp(10, 20));
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[1].GetPathPoints()[1].position,
              FusedObstacleType::Point2Type(11.0, 21.0));
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[1].GetPathPoints()[1].heading_angle, 3.5);
    ASSERT_EQ(obstacle_general_output.GetPredictPath()[1].GetPathPoints()[1].velocity,
              FusedObstacleType::Point2Type(1.3, 2.3));

    ASSERT_EQ(obstacle_general_output.Getpolygon().size(), 2);
    ASSERT_EQ(obstacle_general_output.Getpolygon()[0], FusedObstacleType::Point3Type(1.0, 2.0, 3.0));
    ASSERT_EQ(obstacle_general_output.Getpolygon()[1], FusedObstacleType::Point3Type(4.0, 5.0, 6.0));
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
