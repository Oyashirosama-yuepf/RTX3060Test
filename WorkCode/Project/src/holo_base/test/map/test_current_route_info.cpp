#include <gtest/gtest.h>
#include <holo/map/current_route_info.h>
#include <iostream>

TEST(TestCurrentRouteInfo, Test_Initialization)
{
    ::holo::map::CurrentRouteInfo current_route;
    ASSERT_TRUE(current_route.GetLinks().empty());
    ASSERT_TRUE(current_route.GetRearLinks().empty());
    ASSERT_TRUE(current_route.GetObjects().empty());
}

TEST(TestCurrentRouteInfo, Test_CopyConstructor)
{
    ::holo::map::CurrentRouteInfo        current_route;
    ::std::vector<::holo::map::LinkInfo> link_list;
    ::holo::map::LinkInfo                link;
    link.SetID(100);
    link.SetWidth(100.00f);
    link.SetLength(200.00f);
    link.SetLaneCount(4);
    ::holo::map::LaneInfo lane;
    lane.SetId(1001);
    lane.SetSeq(0);
    lane.SetMaxSpeedLimit(120);
    lane.SetMinSpeedLimit(60);
    lane.SetWidth(3.75f);
    lane.SetLength(200.00f);
    lane.SetType(::holo::map::CommonLaneType::LANE_TYPE_UNDEFINED);
    ::std::vector<::holo::map::LaneInfo> lane_list;
    lane_list.push_back(lane);
    link.SetLaneInfos(::std::move(lane_list));
    link_list.emplace_back(::std::move(link));
    current_route.SetLinks(link_list);
    // SetRearLinks is same to SetLinks

    ::holo::map::CurrentRouteInfo other(current_route);
    ASSERT_EQ(current_route.GetLinks().at(0).GetID(), other.GetLinks().at(0).GetID());
    ASSERT_NEAR(current_route.GetLinks().at(0).GetWidth(), other.GetLinks().at(0).GetWidth(), 0.0001);
    ASSERT_NEAR(current_route.GetLinks().at(0).GetLength(), other.GetLinks().at(0).GetLength(), 0.0001);
    ASSERT_EQ(current_route.GetLinks().at(0).GetLaneCount(), other.GetLinks().at(0).GetLaneCount());
    const auto& current_lane = current_route.GetLinks().at(0).GetLaneInfos().at(0);
    const auto& other_lane   = current_route.GetLinks().at(0).GetLaneInfos().at(0);

    ASSERT_EQ(current_lane.GetId(), other_lane.GetId());
    ASSERT_EQ(current_lane.GetSeq(), other_lane.GetSeq());
    ASSERT_EQ(current_lane.GetMaxSpeedLimit(), other_lane.GetMaxSpeedLimit());
    ASSERT_EQ(current_lane.GetMinSpeedLimit(), other_lane.GetMinSpeedLimit());
    ASSERT_NEAR(current_lane.GetWidth(), other_lane.GetWidth(), 0.0001);
    ASSERT_NEAR(current_lane.GetLength(), other_lane.GetLength(), 0.0001);
    ASSERT_EQ(current_lane.GetType(), other_lane.GetType());
}
TEST(TestCurrentRouteInfo, Test_MoveCopyConstructor)
{
    ::holo::map::CurrentRouteInfo        current_route;
    ::std::vector<::holo::map::LinkInfo> link_list;
    ::holo::map::LinkInfo                link;
    link.SetID(100);
    link.SetWidth(100.00f);
    link.SetLength(200.00f);
    link.SetLaneCount(4);
    link_list.emplace_back(::std::move(link));
    auto address_link0 = &link_list.at(0);
    current_route.SetLinks(::std::move(link_list));
    ::holo::map::CurrentRouteInfo other(::std::move(current_route));
    ASSERT_EQ(address_link0, &other.GetLinks().at(0));
    ASSERT_EQ(other.GetLinks().at(0).GetID(), 100);
    ASSERT_NEAR(other.GetLinks().at(0).GetWidth(), 100.00f, 0.0001);
    ASSERT_NEAR(other.GetLinks().at(0).GetLength(), 200.00f, 0.0001);
    ASSERT_EQ(other.GetLinks().at(0).GetLaneCount(), 4);
}
TEST(TestCurrentRouteInfo, Test_AssignmentOperator)
{
    ::holo::map::CurrentRouteInfo        current_route;
    ::std::vector<::holo::map::LinkInfo> link_list;
    ::holo::map::LinkInfo                link;
    link.SetID(100);
    link.SetWidth(100.00f);
    link.SetLength(200.00f);
    link.SetLaneCount(4);
    ::holo::map::LaneInfo lane;
    lane.SetId(1001);
    lane.SetSeq(0);
    lane.SetMaxSpeedLimit(120);
    lane.SetMinSpeedLimit(60);
    lane.SetWidth(3.75f);
    lane.SetLength(200.00f);
    lane.SetType(::holo::map::CommonLaneType::LANE_TYPE_UNDEFINED);
    ::std::vector<::holo::map::LaneInfo> lane_list;
    lane_list.push_back(lane);
    link.SetLaneInfos(::std::move(lane_list));
    link_list.emplace_back(::std::move(link));
    current_route.SetLinks(link_list);

    // assignment operator
    ::holo::map::CurrentRouteInfo other;
    other = current_route;

    ASSERT_EQ(current_route.GetLinks().at(0).GetID(), other.GetLinks().at(0).GetID());
    ASSERT_NEAR(current_route.GetLinks().at(0).GetWidth(), other.GetLinks().at(0).GetWidth(), 0.0001);
    ASSERT_NEAR(current_route.GetLinks().at(0).GetLength(), other.GetLinks().at(0).GetLength(), 0.0001);
    ASSERT_EQ(current_route.GetLinks().at(0).GetLaneCount(), other.GetLinks().at(0).GetLaneCount());
    const auto& current_lane = current_route.GetLinks().at(0).GetLaneInfos().at(0);
    const auto& other_lane   = current_route.GetLinks().at(0).GetLaneInfos().at(0);

    ASSERT_EQ(current_lane.GetId(), other_lane.GetId());
    ASSERT_EQ(current_lane.GetSeq(), other_lane.GetSeq());
    ASSERT_EQ(current_lane.GetMaxSpeedLimit(), other_lane.GetMaxSpeedLimit());
    ASSERT_EQ(current_lane.GetMinSpeedLimit(), other_lane.GetMinSpeedLimit());
    ASSERT_NEAR(current_lane.GetWidth(), other_lane.GetWidth(), 0.0001);
    ASSERT_NEAR(current_lane.GetLength(), other_lane.GetLength(), 0.0001);
    ASSERT_EQ(current_lane.GetType(), other_lane.GetType());
}
TEST(TestCurrentRouteInfo, Test_MoveAssignmentOperator)
{
    ::holo::map::CurrentRouteInfo        current_route;
    ::std::vector<::holo::map::LinkInfo> link_list;
    ::holo::map::LinkInfo                link;
    link.SetID(100);
    link.SetWidth(100.00f);
    link.SetLength(200.00f);
    link.SetLaneCount(4);
    link_list.emplace_back(::std::move(link));
    auto address_link0 = &link_list.at(0);
    current_route.SetLinks(::std::move(link_list));

    // move assignment operator
    ::holo::map::CurrentRouteInfo other;
    other = ::std::move(current_route);

    ASSERT_EQ(address_link0, &other.GetLinks().at(0));
    ASSERT_EQ(other.GetLinks().at(0).GetID(), 100);
    ASSERT_NEAR(other.GetLinks().at(0).GetWidth(), 100.00f, 0.0001);
    ASSERT_NEAR(other.GetLinks().at(0).GetLength(), 200.00f, 0.0001);
    ASSERT_EQ(other.GetLinks().at(0).GetLaneCount(), 4);
}
TEST(TestCurrentRouteInfo, Test_ToString)
{
    // TODO zhaofx 2019-08-24: For function ToString.
}
TEST(TestCurrentRouteInfo, TestSerialize)
{
    ::holo::map::CurrentRouteInfo          route_info;
    ::holo::map::LinkInfo                  link_info;
    ::holo::map::LaneInfo                  lane_info;
    ::holo::map::CommonObject              object;
    std::vector<::holo::map::LinkInfo>     links;
    std::vector<::holo::map::LaneInfo>     lanes;
    std::vector<::holo::map::CommonObject> objects;
    uint8_t                                status = 5;

    lane_info.SetId(123);
    link_info.SetID(456);
    lanes.push_back(lane_info);
    link_info.SetLaneInfos(lanes);
    links.push_back(link_info);
    object.SetObjectId(789);
    objects.push_back(object);

    uint8_t buffer[10240U];
    ::holo::serialization::Serializer<true, 4>        serializer(buffer, 10240);

    route_info.SetLinks(links);
    route_info.SetRearLinks(links);
    route_info.SetObjects(objects);
    route_info.SetStatus(status);

    route_info.Serialize(serializer);

    ::holo::map::CurrentRouteInfo result_route_info;
    ::holo::uint32_t              size = serializer.GetSize();

    ::holo::serialization::Deserializer<true, 4> deserializer(buffer, serializer.GetSize());

    result_route_info.Deserialize(deserializer);

    ASSERT_EQ(result_route_info.GetObjects().front().GetObjectId(), 789);
    ASSERT_EQ(result_route_info.GetLinks().front().GetID(), 456);
    ASSERT_EQ(result_route_info.GetLinks().front().GetLaneInfos().front().GetId(), 123);
    ASSERT_EQ(result_route_info.GetStatus(), 5);
}

TEST(TestCurrentRouteInfo, GetSerializedSize)
{
    ::holo::map::CurrentRouteInfo route_info;
    ASSERT_EQ(16, route_info.GetSerializedSize<4U>());
    ASSERT_EQ(32, route_info.GetSerializedSize<8U>());
}

TEST(TestCurrentRouteInfo, SerializeAndDeserialize)
{
    ::holo::map::CurrentRouteInfo          route_info_input, route_info_output;
    ::holo::map::LinkInfo                  link_info;
    ::holo::map::LaneInfo                  lane_info;
    ::holo::map::CommonObject              object;
    std::vector<::holo::map::LinkInfo>     links;
    std::vector<::holo::map::LaneInfo>     lanes;
    std::vector<::holo::map::CommonObject> objects;
    uint8_t                                status = 5;

    lane_info.SetId(123);
    link_info.SetID(456);
    lanes.push_back(lane_info);
    link_info.SetLaneInfos(lanes);
    links.push_back(link_info);
    object.SetObjectId(789);
    objects.push_back(object);

    route_info_input.SetLinks(links);
    route_info_input.SetRearLinks(links);
    route_info_input.SetObjects(objects);
    route_info_input.SetStatus(status);

    uint8_t buffer[1280U];
    holo::serialization::Serializer<>          serializer(buffer, 1280);
    serializer << route_info_input;
    ASSERT_EQ(route_info_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> route_info_output;

    ASSERT_EQ(route_info_input.GetObjects().front().GetObjectId(),
              route_info_output.GetObjects().front().GetObjectId());
    ASSERT_EQ(route_info_input.GetLinks().front().GetID(), route_info_output.GetLinks().front().GetID());
    ASSERT_EQ(route_info_input.GetLinks().front().GetLaneInfos().front().GetId(),
              route_info_output.GetLinks().front().GetLaneInfos().front().GetId());
    ASSERT_EQ(route_info_input.GetStatus(), route_info_output.GetStatus());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
