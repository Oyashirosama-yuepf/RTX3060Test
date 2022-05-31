
/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_traffic_light.cpp
 * @brief unit test for alarm class
 * @author zhouhuishuang@holomatic.com
 * @date 2021-04-20
 */
#include <gtest/gtest.h>
#include <holo/common/traffic_light.h>

using TrafficLight  = holo::common::TrafficLightT<5U, 2U>;
using TrafficLights = holo::common::TrafficLightsT<5U, 2U, 5U>;

TEST(TrafficLight, DefaultConstructor)
{
    TrafficLight                                      traffic_light;
    holo::container::Vector<holo::uint64_t, 5U>       lane_id;
    holo::container::Vector<TrafficLight::Signal, 2U> signal;

    signal = traffic_light.GetSignals();
    ASSERT_EQ(false, traffic_light.IsDetected());
    ASSERT_EQ(false, traffic_light.IsTemporary());
    ASSERT_EQ(0, traffic_light.GetConfidence());
    ASSERT_EQ(-1, traffic_light.GetTimer());
    ASSERT_EQ(holo::geometry::Box3d(), traffic_light.GetBoundingBox());
    ASSERT_EQ(signal.size(), 0);
    ASSERT_EQ(lane_id, traffic_light.GetLaneIds());
}

TEST(TrafficLight, Constructor)
{
    TrafficLight                                      traffic_light(10, true, true, 10, 50);
    holo::container::Vector<holo::uint64_t, 5U>       lane_id;
    holo::container::Vector<TrafficLight::Signal, 2U> signal;

    signal = traffic_light.GetSignals();
    ASSERT_EQ(10, traffic_light.GetTrackId());
    ASSERT_EQ(true, traffic_light.IsDetected());
    ASSERT_EQ(true, traffic_light.IsTemporary());
    ASSERT_EQ(10, traffic_light.GetTimer());
    ASSERT_EQ(50, traffic_light.GetConfidence());
    ASSERT_EQ(holo::geometry::Box3d(), traffic_light.GetBoundingBox());
    ASSERT_EQ(signal.size(), 0);
    ASSERT_EQ(lane_id, traffic_light.GetLaneIds());
}

TEST(TrafficLight, SetAndGetTrackId)
{
    TrafficLight traffic_light;
    traffic_light.SetTrackId(10);
    ASSERT_EQ(10, traffic_light.GetTrackId());
}

TEST(TrafficLight, IsAndSetDetectFlag)
{
    TrafficLight traffic_light;
    ASSERT_EQ(false, traffic_light.IsDetected());
    traffic_light.SetDetectFlag(true);
    ASSERT_EQ(true, traffic_light.IsDetected());
    traffic_light.SetDetectFlag(false);
    ASSERT_EQ(false, traffic_light.IsDetected());
}

TEST(TrafficLight, IsAndSetTemporaryFlag)
{
    TrafficLight traffic_light;
    ASSERT_EQ(false, traffic_light.IsTemporary());
    traffic_light.SetTemporaryFlag(true);
    ASSERT_EQ(true, traffic_light.IsTemporary());
    traffic_light.SetTemporaryFlag(false);
    ASSERT_EQ(false, traffic_light.IsTemporary());
}

TEST(TrafficLight, SetAndGetTimer)
{
    TrafficLight traffic_light;
    traffic_light.SetTimer(-20);
    ASSERT_EQ(-20, traffic_light.GetTimer());
}

TEST(TrafficLight, SetAndGetConfidence)
{
    TrafficLight traffic_light;
    traffic_light.SetConfidence(8.9f);
    ASSERT_EQ(8.9f, traffic_light.GetConfidence());
}

TEST(TrafficLight, SetAndGetBoundingBox)
{
    holo::geometry::Point3d const center(10.0f, -11.0f, 12.0f);
    holo::geometry::Box3d const   box3(1.0f, 2.0f, 4.0f, center);

    TrafficLight traffic_light;
    traffic_light.SetBoundingBox(box3);
    ASSERT_EQ(box3, traffic_light.GetBoundingBox());
}

TEST(TrafficLight, SetAndGetLaneIds)
{
    holo::container::Vector<holo::uint64_t, 5U> lane_id;
    for (size_t i = 0; i < 3; ++i)
    {
        lane_id.push_back(100000 + i);
    }

    TrafficLight traffic_light;
    traffic_light.SetLaneIds(lane_id);
    ASSERT_EQ(lane_id, traffic_light.GetLaneIds());
}

TEST(TrafficLight, SetAndGetSignals)
{
    holo::container::Vector<TrafficLight::Signal, 2U> signals;
    TrafficLight::Signal                              signal1, signal2;
    signal1.type   = TrafficLight::Type::UNDEFINED;
    signal1.status = TrafficLight::Status::RED;

    signal2.type   = TrafficLight::Type::LEFT_FORWARD;
    signal2.status = TrafficLight::Status::GREEN;

    signals.push_back(signal1);
    signals.push_back(signal2);

    TrafficLight traffic_light;
    traffic_light.SetSignals(signals);

    for (size_t i = 0; i < 2; i++)
    {
        ASSERT_EQ(signals[i].type, traffic_light.GetSignals()[i].type);
        ASSERT_EQ(signals[i].status, traffic_light.GetSignals()[i].status);
    }
}

TEST(TrafficLight, GetSerializedSize)
{
    TrafficLight traffic_light;

    ASSERT_EQ(144, traffic_light.GetSerializedSize<4U>());
    ASSERT_EQ(152, traffic_light.GetSerializedSize<8U>());
}

TEST(TrafficLight, SerializeAndDeserialize)
{
    TrafficLight traffic_light(10, true, true, 10, 50);

    holo::geometry::Point3d const center(10.0f, -11.0f, 12.0f);
    holo::geometry::Box3d const   box3(1.0f, 2.0f, 4.0f, center);

    holo::container::Vector<holo::uint64_t, 5U> lane_id;

    for (size_t i = 0; i < 3; ++i)
    {
        lane_id.push_back(100000 + i);
    }

    holo::container::Vector<TrafficLight::Signal, 2U> signals;
    TrafficLight::Signal                              signal1, signal2;
    signal1.type   = TrafficLight::Type::UNDEFINED;
    signal1.status = TrafficLight::Status::RED;

    signal2.type   = TrafficLight::Type::LEFT_FORWARD;
    signal2.status = TrafficLight::Status::GREEN;

    signals.push_back(signal1);
    signals.push_back(signal2);

    traffic_light.SetSignals(signals);
    traffic_light.SetBoundingBox(box3);
    traffic_light.SetLaneIds(lane_id);

    uint8_t                           buffer[10240];
    holo::serialization::Serializer<> serializer(buffer, 1024);
    serializer << traffic_light;
    ASSERT_EQ(traffic_light.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    TrafficLight                        traffic_light_output;
    deserializer >> traffic_light_output;

    ASSERT_EQ(traffic_light.GetTrackId(), traffic_light_output.GetTrackId());
    ASSERT_EQ(traffic_light.IsDetected(), traffic_light_output.IsDetected());
    ASSERT_EQ(traffic_light.IsTemporary(), traffic_light_output.IsTemporary());
    ASSERT_EQ(traffic_light.GetConfidence(), traffic_light_output.GetConfidence());
    ASSERT_EQ(traffic_light.GetTimer(), traffic_light_output.GetTimer());
    ASSERT_EQ(traffic_light.GetBoundingBox(), traffic_light_output.GetBoundingBox());
    ASSERT_EQ(traffic_light.GetLaneIds(), traffic_light_output.GetLaneIds());

    for (size_t i = 0; i < 2; i++)
    {
        ASSERT_EQ(traffic_light.GetSignals()[i].type, traffic_light_output.GetSignals()[i].type);
        ASSERT_EQ(traffic_light.GetSignals()[i].status, traffic_light_output.GetSignals()[i].status);
    }
}

TEST(TrafficLights, DefaultConstructor)
{
    TrafficLights list;
    ASSERT_EQ(0U, list.size());
    ASSERT_EQ(holo::common::Timestamp(), list.GetTimestamp());
    ASSERT_EQ(holo::common::Coordinate(), list.GetCoordinate());
}

TEST(TrafficLights, Constructor)
{
    TrafficLights list(holo::common::Timestamp(10, 20), holo::common::Coordinate(100));
    ASSERT_EQ(0U, list.size());
    ASSERT_EQ(holo::common::Timestamp(10, 20), list.GetTimestamp());
    ASSERT_EQ(holo::common::Coordinate(100), list.GetCoordinate());
}

TEST(TrafficLights, GetAndSetTimestamp)
{
    TrafficLights list;
    list.SetTimestamp(holo::common::Timestamp(10, 20));
    ASSERT_EQ(holo::common::Timestamp(10, 20), list.GetTimestamp());
}

TEST(TrafficLights, GetAndSetCoordinate)
{
    TrafficLights list;
    list.SetCoordinate(holo::common::Coordinate(100));
    ASSERT_EQ(holo::common::Coordinate(100), list.GetCoordinate());
}

TEST(TrafficLights, GetSerializedSize)
{
    TrafficLights list;
    ASSERT_EQ(16, list.GetSerializedSize<4U>());
    ASSERT_EQ(20, list.GetSerializedSize<8U>());
}

TEST(TrafficLights, SerializeAndDeserialize)
{
    TrafficLight traffic_light_1(10, true, true, 10, 50);

    holo::container::Vector<holo::uint64_t, 5U> lane_id_1;
    lane_id_1.push_back(1000);
    lane_id_1.push_back(1100);
    lane_id_1.push_back(1200);

    traffic_light_1.SetBoundingBox(
        holo::geometry::Box3d(1.0f, 2.0f, 4.0f, holo::geometry::Point3d(10.0f, 11.0f, 12.0f)));
    traffic_light_1.SetLaneIds(lane_id_1);

    holo::container::Vector<TrafficLight::Signal, 2U> signals;
    TrafficLight::Signal                              signal1, signal2;
    signal1.type   = TrafficLight::Type::UNDEFINED;
    signal1.status = TrafficLight::Status::RED;

    signal2.type   = TrafficLight::Type::LEFT_FORWARD;
    signal2.status = TrafficLight::Status::GREEN;

    signals.push_back(signal1);
    signals.push_back(signal2);

    traffic_light_1.SetSignals(signals);

    TrafficLight traffic_light_2(5, true, true, 10, 50);

    holo::container::Vector<holo::uint64_t, 5U> lane_id_2;

    lane_id_2.push_back(101);
    lane_id_2.push_back(102);
    lane_id_2.push_back(103);

    traffic_light_2.SetBoundingBox(
        holo::geometry::Box3d(10.0f, 20.0f, 40.0f, holo::geometry::Point3d(10.0f, 11.0f, 12.0f)));
    traffic_light_2.SetLaneIds(lane_id_2);
    traffic_light_2.SetSignals(signals);

    TrafficLights traffic_lights, traffic_lights_output;

    traffic_lights.push_back(traffic_light_1);
    traffic_lights.push_back(traffic_light_2);

    uint8_t                           buffer[10240];
    holo::serialization::Serializer<> serializer(buffer, 1024);
    serializer << traffic_lights;
    ASSERT_EQ(traffic_lights.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> traffic_lights_output;

    for (size_t i = 0; i < 2; i++)
    {
        ASSERT_EQ(traffic_lights[i].GetTrackId(), traffic_lights_output[i].GetTrackId());
        ASSERT_EQ(traffic_lights[i].IsDetected(), traffic_lights_output[i].IsDetected());
        ASSERT_EQ(traffic_lights[i].IsTemporary(), traffic_lights_output[i].IsTemporary());
        ASSERT_EQ(traffic_lights[i].GetConfidence(), traffic_lights_output[i].GetConfidence());
        ASSERT_EQ(traffic_lights[i].GetTimer(), traffic_lights_output[i].GetTimer());
        ASSERT_EQ(traffic_lights[i].GetBoundingBox(), traffic_lights_output[i].GetBoundingBox());
        ASSERT_EQ(traffic_lights[i].GetLaneIds(), traffic_lights_output[i].GetLaneIds());

        for (size_t j = 0; j < 2; j++)
        {
            ASSERT_EQ(traffic_lights[i].GetSignals()[i].type, traffic_lights_output[i].GetSignals()[i].type);
            ASSERT_EQ(traffic_lights[i].GetSignals()[i].status, traffic_lights_output[i].GetSignals()[i].status);
        }
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
