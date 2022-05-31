/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_map_navigation_request.cpp
 * @brief Testing for RoutingSearchRequestT
 * @author zhouhuishuang(zhouhuishuang@holomaitc.com)
 * @date "2021-08-30"
 */

#include <gtest/gtest.h>
#include <holo/map/map_navigation_request.h>

using namespace holo;
using NavigationPointType      = holo::map::NavigationPoint;
using RoutingSearchRequestType = holo::map::RoutingSearchRequestT<2U>;

TEST(NavigationPoint, DefaultConstructor)
{
    NavigationPointType navigation_point;
    ASSERT_EQ(NavigationPointType::LayerId::UNKNOWN, navigation_point.GetLayerId());
    ASSERT_EQ(0U, navigation_point.GetElementId());
    ASSERT_EQ(holo::common::Coordinate(0), navigation_point.GetCoordinate());
    ASSERT_EQ(holo::geometry::Point3f(0, 0, 0), navigation_point.GetPosition());
}

TEST(NavigationPoint, Constructor)
{
    NavigationPointType navigation_point(NavigationPointType::LayerId::POI, 5U, 36984440U,
                                         holo::geometry::Point3f(1.0, 2.0, 3.0));
    ASSERT_EQ(NavigationPointType::LayerId::POI, navigation_point.GetLayerId());
    ASSERT_EQ(5U, navigation_point.GetElementId());
    ASSERT_EQ(holo::common::Coordinate(36984440U), navigation_point.GetCoordinate());
    ASSERT_EQ(holo::geometry::Point3f(1.0, 2.0, 3.0), navigation_point.GetPosition());
}

TEST(NavigationPoint, GetAndSetLayerId)
{
    NavigationPointType navigation_point;
    navigation_point.SetLayerId(NavigationPointType::LayerId::POI);
    ASSERT_EQ(NavigationPointType::LayerId::POI, navigation_point.GetLayerId());
}

TEST(NavigationPoint, GetAndSetElementId)
{
    NavigationPointType navigation_point;
    navigation_point.SetElementId(5U);
    ASSERT_EQ(5U, navigation_point.GetElementId());
}

TEST(NavigationPoint, GetAndSetCoordinate)
{
    NavigationPointType navigation_point;
    navigation_point.SetCoordinate(holo::common::Coordinate(36984440U));
    ASSERT_EQ(holo::common::Coordinate(36984440U), navigation_point.GetCoordinate());
}

TEST(NavigationPoint, GetAndSetPosition)
{
    NavigationPointType navigation_point;
    navigation_point.SetPosition(holo::geometry::Point3f(1.0, 2.0, 3.0));
    ASSERT_EQ(holo::geometry::Point3f(1.0, 2.0, 3.0), navigation_point.GetPosition());
}

TEST(NavigationPoint, GetSerializedSize)
{
    NavigationPointType navigation_point;
    ASSERT_EQ(28, navigation_point.GetSerializedSize<4U>());
    ASSERT_EQ(36, navigation_point.GetSerializedSize<8U>());
}

TEST(NavigationPoint, SerializeAndDeserialize)
{
    NavigationPointType navigation_point(NavigationPointType::LayerId::POI, 5U, 36984440U,
                                         holo::geometry::Point3f(1.0, 2.0, 3.0));

    uint8_t                           buffer[1024];
    holo::serialization::Serializer<> serializer(buffer, 1024);
    serializer << navigation_point;
    ASSERT_EQ(navigation_point.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    NavigationPointType                 navigation_point_output;
    deserializer >> navigation_point_output;

    ASSERT_EQ(navigation_point.GetLayerId(), navigation_point_output.GetLayerId());
    ASSERT_EQ(navigation_point.GetElementId(), navigation_point_output.GetElementId());
    ASSERT_EQ(navigation_point.GetCoordinate(), navigation_point_output.GetCoordinate());
    ASSERT_EQ(navigation_point.GetPosition(), navigation_point_output.GetPosition());
}

TEST(RoutingSearchRequest, DefaultConstructor)
{
    RoutingSearchRequestType request;
    ASSERT_EQ(0U, request.size());
    ASSERT_EQ(RoutingSearchRequestType::Policy::DEFAULT, request.GetPolicy());
    ASSERT_EQ(0U, request.size());
}

TEST(RoutingSearchRequest, Constructor)
{
    RoutingSearchRequestType request(5U, RoutingSearchRequestType::Policy::SHORTEST_TOLL);
    ASSERT_EQ(5U, request.GetRequestId());
    ASSERT_EQ(RoutingSearchRequestType::Policy::SHORTEST_TOLL, request.GetPolicy());
    ASSERT_EQ(0U, request.size());
}

TEST(RoutingSearchRequest, GetAndSetRequestId)
{
    RoutingSearchRequestType request;
    request.SetRequestId(5U);
    ASSERT_EQ(5U, request.GetRequestId());
}

TEST(RoutingSearchRequest, GetAndSetPolicy)
{
    RoutingSearchRequestType request;
    request.SetPolicy(RoutingSearchRequestType::Policy::SHORTEST_TOLL);
    ASSERT_EQ(RoutingSearchRequestType::Policy::SHORTEST_TOLL, request.GetPolicy());
}

TEST(RoutingSearchRequest, GetSerializedSize)
{
    RoutingSearchRequestType request;
    ASSERT_EQ(16, request.GetSerializedSize<4U>());
    ASSERT_EQ(24, request.GetSerializedSize<8U>());
}

TEST(RoutingSearchRequest, SerializeAndDeserialize)
{
    RoutingSearchRequestType request;
    NavigationPointType      navigation_point1(NavigationPointType::LayerId::POI, 5U, 36984440U,
                                          holo::geometry::Point3f(1.0, 2.0, 3.0));
    NavigationPointType      navigation_point2(NavigationPointType::LayerId::ROAD, 10U, 36984111U,
                                          holo::geometry::Point3f(7.0, 8.0, 9.0));

    request.push_back(navigation_point1);
    request.push_back(navigation_point2);
    ASSERT_EQ(2U, request.size());

    request.SetRequestId(2U);
    request.SetPolicy(RoutingSearchRequestType::Policy::SHORTEST_TOLL);

    uint8_t                           buffer[1024];
    holo::serialization::Serializer<> serializer(buffer, 1024);

    serializer << request;
    ASSERT_EQ(request.GetSerializedSize(), serializer.GetSize());

    RoutingSearchRequestType            request_output;
    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> request_output;

    ASSERT_EQ(request.GetRequestId(), request_output.GetRequestId());
    ASSERT_EQ(request.GetPolicy(), request_output.GetPolicy());
    ASSERT_EQ(request.size(), request_output.size());
    ASSERT_EQ(request[0].GetLayerId(), request_output[0].GetLayerId());
    ASSERT_EQ(request[0].GetElementId(), request_output[0].GetElementId());
    ASSERT_EQ(request[0].GetCoordinate(), request_output[0].GetCoordinate());
    ASSERT_EQ(request[0].GetPosition(), request_output[0].GetPosition());

    ASSERT_EQ(request[1].GetLayerId(), request_output[1].GetLayerId());
    ASSERT_EQ(request[1].GetElementId(), request_output[1].GetElementId());
    ASSERT_EQ(request[1].GetCoordinate(), request_output[1].GetCoordinate());
    ASSERT_EQ(request[1].GetPosition(), request_output[1].GetPosition());
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
