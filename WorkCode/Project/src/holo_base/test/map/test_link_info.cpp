#include <iostream>
#include <gtest/gtest.h>
#include <holo/map/link_info.h>

TEST(TestLaneInfo, Test_MapMsgBase_Valid)
{
    ::holo::map::LinkInfo link;
    ASSERT_TRUE(link.IsValid());

    auto indicator_size = link.GetValidIndicatorSize();
    link.SetValidIndicatorSize(100);
    ASSERT_FALSE(link.IsValid());
    link.SetValidIndicatorSize(indicator_size);
    ASSERT_TRUE(link.IsValid());

    auto uint32_size = link.GetValidUint32Size();
    link.SetValidUint32Size(100);
    ASSERT_FALSE(link.IsValid());
    link.SetValidUint32Size(uint32_size);
    ASSERT_TRUE(link.IsValid());

    auto float32_size = link.GetValidFloat32Size();
    link.SetValidFloat32Size(100);
    ASSERT_FALSE(link.IsValid());
    link.SetValidFloat32Size(float32_size);
    ASSERT_TRUE(link.IsValid());
}

TEST(TestLaneMarkInfo, Test_Destructor)
{
    ::holo::map::LinkInfo *link = new ::holo::map::LinkInfo();
    delete link;
}

TEST(TestLaneMarkInfo, Test_Convert_Uint)
{
    ::holo::map::LinkInfo link;
    // now we have not any uint32 member variables.
    ASSERT_TRUE(true);
}

TEST(TestLaneMarkInfo, Test_Convert_Float)
{
    ::holo::map::LinkInfo            link;
    ::std::vector<::holo::float32_t> float32_values;
    // set mark width
    float32_values.push_back(3.75);
    // set length
    float32_values.push_back(100.33);
    // set max speed limit
    float32_values.push_back(33.33);
    // set min speed limit
    float32_values.push_back(20.22);

    ::std::vector<::holo::float32_t> float32_values_rvalue = float32_values;
    link.SetValuesFloat32(float32_values);

    auto& float32_values_getter = link.GetValuesFloat32();
    for (::std::size_t i = 0; i < float32_values.size(); i++)
    {
        ASSERT_NEAR(float32_values.at(i), float32_values_getter.at(i), 0.01);
    }

    link.SetValuesFloat32(::std::move(float32_values_rvalue));
    auto& float32_values_rvalue_getter = link.GetValuesFloat32();
    for (::std::size_t i = 0; i < float32_values.size(); i++)
    {
        ASSERT_NEAR(float32_values.at(i), float32_values_rvalue_getter.at(i), 0.01);
    }
}

TEST(TestLinkInfo, Test_Convert_Indicators_By_value)
{
    ::holo::map::LinkInfo link;
    ::holo::uint32_t value = 0;
    link.SetIndicatorsByValue(value);
    ASSERT_FALSE(link.IsOnRoute());
    ASSERT_FALSE(link.IsOnBifurcation());

    // value -> "111"
    value = 3;
    link.SetIndicatorsByValue(value);
    ASSERT_TRUE(link.IsOnRoute());
    ASSERT_TRUE(link.IsOnBifurcation());

    ASSERT_EQ(value, link.GetIndicatorsByValue());
}

TEST(TestLinkInfo, Test_Convert_Indicators)
{
    ::holo::map::LinkInfo link;
    const ::std::bitset<::holo::map::MapMsgBase::kHoloMapBitset_32> bit("01");
    link.SetIndicators(bit);

    ASSERT_TRUE(link.IsOnRoute());
    ASSERT_FALSE(link.IsOnBifurcation());

}

TEST(TestLinkInfo, Test_Constructor)
{
    ::holo::map::LinkInfo link;
    ASSERT_EQ(link.GetID(), 0);
    ASSERT_EQ(link.GetLaneCount(), 0);
    ASSERT_TRUE(link.GetRefPoints().empty());
    ASSERT_NEAR(link.GetMaxSpeedLimit(), 0.0, 0.0001);
    ASSERT_NEAR(link.GetMinSpeedLimit(), 0.0, 0.0001);
    ASSERT_NEAR(link.GetLength(), 0.0, 0.0001);
    ASSERT_NEAR(link.GetWidth(), 0.0, 0.0001);
    ASSERT_TRUE(link.GetLaneInfos().empty());
}
TEST(TestLinkInfo, Test_CopyConstructor)
{
    ::holo::map::LinkInfo link;
    link.SetID(10000);
    ::std::vector<::holo::map::LaneInfo> lane_list;
    lane_list.push_back(::holo::map::LaneInfo());
    lane_list.push_back(::holo::map::LaneInfo());
    link.SetLaneCount(lane_list.size());
    link.SetLaneInfos(::std::move(lane_list));
    link.SetWidth(100.0f);
    link.SetLength(2000.0f);
    link.SetMaxSpeedLimit(33.33f);
    link.SetMinSpeedLimit(0.0f);

    ::holo::map::LinkInfo other(link);
    ASSERT_EQ(link.GetID(), other.GetID());
    ASSERT_EQ(link.GetLaneCount(), other.GetLaneCount());
    ASSERT_EQ(link.GetRefPoints(), other.GetRefPoints());
    ASSERT_NEAR(link.GetLength(), other.GetLength(), 0.0001);
    ASSERT_NEAR(link.GetWidth(), other.GetWidth(), 0.0001);
    ASSERT_NEAR(link.GetMaxSpeedLimit(), other.GetMaxSpeedLimit(), 0.0001);
    ASSERT_NEAR(link.GetMinSpeedLimit(), other.GetMinSpeedLimit(), 0.0001);
    ASSERT_EQ(link.GetLaneInfos().size(), other.GetLaneInfos().size());
    ASSERT_EQ(link.GetLaneInfos().size(), link.GetLaneCount());
    ASSERT_EQ(other.GetLaneInfos().size(), other.GetLaneCount());
}
TEST(TestLinkInfo, Test_MoveCopyConstructor)
{
    ::holo::map::LinkInfo link;
    link.SetID(10000);

    ::std::vector<::holo::map::LaneInfo> lane_list;
    lane_list.push_back(::holo::map::LaneInfo());
    lane_list.push_back(::holo::map::LaneInfo());
    link.SetLaneCount(lane_list.size());
    link.SetLaneInfos(::std::move(lane_list));
    link.SetWidth(100.0f);
    link.SetLength(2000.0f);
    link.SetMaxSpeedLimit(20.0f);
    link.SetMinSpeedLimit(10.0f);
    ::std::vector<::holo::geometry::Point3d> points = {::holo::geometry::Point3d(43.00f, 120.22f, 20.0),
                                             ::holo::geometry::Point3d(43.55f, 120.13f, 21.0)};
    link.SetRefPoints(::std::move(points));
    auto address_ref = &link.GetRefPoints().at(0);

    ::holo::map::LinkInfo other(link);
    ::holo::map::LinkInfo move(::std::move(link));
    ASSERT_EQ(move.GetID(), other.GetID());
    ASSERT_EQ(move.GetLaneCount(), other.GetLaneCount());
    ASSERT_EQ(move.GetRefPoints(), other.GetRefPoints());
    ASSERT_NEAR(move.GetLength(), other.GetLength(), 0.0001);
    ASSERT_NEAR(move.GetWidth(), other.GetWidth(), 0.0001);
    ASSERT_NEAR(move.GetMaxSpeedLimit(), other.GetMaxSpeedLimit(), 0.0001);
    ASSERT_NEAR(move.GetMinSpeedLimit(), other.GetMinSpeedLimit(), 0.0001);
    ASSERT_EQ(move.GetLaneInfos().size(), other.GetLaneInfos().size());
    ASSERT_EQ(move.GetLaneInfos().size(), move.GetLaneCount());
    ASSERT_EQ(other.GetLaneInfos().size(), other.GetLaneCount());
    ASSERT_EQ(&move.GetRefPoints().at(0), address_ref);
}
TEST(TestLinkInfo, Test_AssignmentOperator)
{
    ::holo::map::LinkInfo link;
    link.SetID(10000);
    ::std::vector<::holo::map::LaneInfo> lane_list;
    lane_list.push_back(::holo::map::LaneInfo());
    lane_list.push_back(::holo::map::LaneInfo());
    link.SetLaneCount(lane_list.size());
    link.SetLaneInfos(::std::move(lane_list));
    link.SetWidth(100.0f);
    link.SetLength(2000.0f);
    link.SetMaxSpeedLimit(20.0f);
    link.SetMinSpeedLimit(20.0f);

    ::holo::map::LinkInfo other;
    other = link;
    ASSERT_EQ(link.GetID(), other.GetID());
    ASSERT_EQ(link.GetLaneCount(), other.GetLaneCount());
    ASSERT_EQ(link.GetRefPoints(), other.GetRefPoints());
    ASSERT_NEAR(link.GetLength(), other.GetLength(), 0.0001);
    ASSERT_NEAR(link.GetWidth(), other.GetWidth(), 0.0001);
    ASSERT_EQ(link.GetLaneInfos().size(), other.GetLaneInfos().size());
    ASSERT_EQ(link.GetLaneInfos().size(), link.GetLaneCount());
    ASSERT_EQ(other.GetLaneInfos().size(), other.GetLaneCount());
    ASSERT_NEAR(link.GetMaxSpeedLimit(), other.GetMaxSpeedLimit(), 0.0001);
    ASSERT_NEAR(link.GetMinSpeedLimit(), other.GetMinSpeedLimit(), 0.0001);
}
TEST(TestLinkInfo, Test_MoveAssignmentOperator)
{
    ::holo::map::LinkInfo link;
    link.SetID(10000);
    ::std::vector<::holo::map::LaneInfo> lane_list;
    lane_list.push_back(::holo::map::LaneInfo());
    lane_list.push_back(::holo::map::LaneInfo());
    link.SetLaneCount(lane_list.size());
    link.SetLaneInfos(::std::move(lane_list));
    link.SetWidth(100.0f);
    link.SetLength(2000.0f);
    link.SetMaxSpeedLimit(20.0f);
    link.SetMinSpeedLimit(20.0f);
    ::std::vector<::holo::geometry::Point3d> points = {::holo::geometry::Point3d(43.00f, 120.22f, 20.0),
                                             ::holo::geometry::Point3d(43.55f, 120.13f, 21.0)};
    link.SetRefPoints(::std::move(points));
    auto address_ref = &link.GetRefPoints().at(0);

    ::holo::map::LinkInfo other;
    other = link;
    ::holo::map::LinkInfo move;
    move = ::std::move(link);
    ASSERT_EQ(move.GetID(), other.GetID());
    ASSERT_EQ(move.GetLaneCount(), other.GetLaneCount());
    ASSERT_EQ(move.GetRefPoints(), other.GetRefPoints());
    ASSERT_NEAR(move.GetLength(), other.GetLength(), 0.0001);
    ASSERT_NEAR(move.GetWidth(), other.GetWidth(), 0.0001);
    ASSERT_EQ(move.GetLaneInfos().size(), other.GetLaneInfos().size());
    ASSERT_EQ(move.GetLaneInfos().size(), move.GetLaneCount());
    ASSERT_EQ(other.GetLaneInfos().size(), other.GetLaneCount());
    ASSERT_EQ(&move.GetRefPoints().at(0), address_ref);
    ASSERT_NEAR(move.GetMaxSpeedLimit(), other.GetMaxSpeedLimit(), 0.0001);
    ASSERT_NEAR(move.GetMinSpeedLimit(), other.GetMinSpeedLimit(), 0.0001);
}
TEST(TestLinkInfo, Test_ID)
{
    ::holo::map::KeyValue id(0);
    ::holo::map::LinkInfo link;
    link.SetID(id);
    ASSERT_EQ(link.GetID(), id);
    id = 1000000;
    link.SetID(id);
    ASSERT_EQ(link.GetID(), id);

    id = ::std::numeric_limits<::holo::map::KeyValue>::max();
    link.SetID(id);
    ASSERT_EQ(link.GetID(), id);

    id = ::std::numeric_limits<::holo::map::KeyValue>::min();
    link.SetID(id);
    ASSERT_EQ(link.GetID(), id);

    // No crash
    id = -100;
    link.SetID(id);
    ASSERT_TRUE(link.GetID() > 0);
}
TEST(TestLinkInfo, Test_MaxLimitSpeed)
{
    ::holo::float32_t     speed(0.0f);
    ::holo::map::LinkInfo link;
    link.SetMaxSpeedLimit(speed);
    ASSERT_NEAR(link.GetMaxSpeedLimit(), speed, 0.0001);

    speed = 3.44f;
    link.SetMaxSpeedLimit(speed);
    ASSERT_NEAR(link.GetMaxSpeedLimit(), speed, 0.0001);

    speed = ::std::numeric_limits<::holo::float32_t>::max();
    link.SetMaxSpeedLimit(speed);
    ASSERT_NEAR(link.GetMaxSpeedLimit(), speed, 0.0001);

    speed = ::std::numeric_limits<::holo::float32_t>::min();
    link.SetMaxSpeedLimit(speed);
    ASSERT_NEAR(link.GetMaxSpeedLimit(), speed, 0.0001);

    // No crash
    speed = -1000.00f;
    link.SetMaxSpeedLimit(speed);
    ASSERT_NEAR(link.GetMaxSpeedLimit(), speed, 0.0001);
}

TEST(TestLinkInfo, Test_MinLimitSpeed)
{
    ::holo::float32_t     speed(0.0f);
    ::holo::map::LinkInfo link;
    link.SetMinSpeedLimit(speed);
    ASSERT_NEAR(link.GetMinSpeedLimit(), speed, 0.0001);

    speed = 3.44f;
    link.SetMinSpeedLimit(speed);
    ASSERT_NEAR(link.GetMinSpeedLimit(), speed, 0.0001);

    speed = ::std::numeric_limits<::holo::float32_t>::max();
    link.SetMinSpeedLimit(speed);
    ASSERT_NEAR(link.GetMinSpeedLimit(), speed, 0.0001);

    speed = ::std::numeric_limits<::holo::float32_t>::min();
    link.SetMinSpeedLimit(speed);
    ASSERT_NEAR(link.GetMinSpeedLimit(), speed, 0.0001);

    // No crash
    speed = -1000.00f;
    link.SetMinSpeedLimit(speed);
    ASSERT_NEAR(link.GetMinSpeedLimit(), speed, 0.0001);
}
TEST(TestLinkInfo, Test_Width)
{
    ::holo::float32_t     width(0.0f);
    ::holo::map::LinkInfo link;
    link.SetWidth(width);
    ASSERT_NEAR(link.GetWidth(), width, 0.0001);

    width = 3.44f;
    link.SetWidth(width);
    ASSERT_NEAR(link.GetWidth(), width, 0.0001);

    width = ::std::numeric_limits<::holo::float32_t>::max();
    link.SetWidth(width);
    ASSERT_NEAR(link.GetWidth(), width, 0.0001);

    width = ::std::numeric_limits<::holo::float32_t>::min();
    link.SetWidth(width);
    ASSERT_NEAR(link.GetWidth(), width, 0.0001);

    // No crash
    width = -1000.00f;
    link.SetWidth(width);
    ASSERT_NEAR(link.GetWidth(), width, 0.0001);
}
TEST(TestLinkInfo, Test_Length)
{
    ::holo::float32_t     length(0.0f);
    ::holo::map::LinkInfo link;
    link.SetLength(length);
    ASSERT_NEAR(link.GetLength(), length, 0.0001);

    length = 100.00f;
    link.SetLength(length);
    ASSERT_NEAR(link.GetLength(), length, 0.0001);

    length = ::std::numeric_limits<::holo::float32_t>::max();
    link.SetLength(length);
    ASSERT_NEAR(link.GetLength(), length, 0.0001);

    length = ::std::numeric_limits<::holo::float32_t>::min();
    link.SetLength(length);
    ASSERT_NEAR(link.GetLength(), length, 0.0001);

    // No crash
    length = -1000.00f;
    link.SetLength(length);
    ASSERT_NEAR(link.GetLength(), length, 0.0001);
}
TEST(TestLinkInfo, Test_LaneCount)
{
    ::holo::uint8_t       value(0);
    ::holo::map::LinkInfo link;
    link.SetLaneCount(value);
    ASSERT_EQ(link.GetLaneCount(), value);

    value = ::std::numeric_limits<::holo::uint8_t>::max();
    link.SetLaneCount(value);
    ASSERT_EQ(link.GetLaneCount(), value);

    value = ::std::numeric_limits<::holo::uint8_t>::min();
    link.SetLaneCount(value);
    ASSERT_EQ(link.GetLaneCount(), value);

    // No crash
    value = -100;
    link.SetLaneCount(value);
    ASSERT_TRUE(link.GetLaneCount() > 0);
}
TEST(TestLinkInfo, Test_RefPoints)
{
    ::holo::map::LinkInfo          link;
    ::std::vector<::holo::geometry::Point3d> points = {::holo::geometry::Point3d(100.1, 40.2, 10.0), ::holo::geometry::Point3d(100.111, 42.2, 12.0)};
    link.SetRefPoints(points);
    ASSERT_EQ(points, link.GetRefPoints());
    auto address = &points.at(0);
    ASSERT_TRUE(address != &link.GetRefPoints().at(0));

    link.SetRefPoints(::std::move(points));
    ASSERT_TRUE(address == &link.GetRefPoints().at(0));
}

TEST(TestLinkInfo, Test_ToString)
{
}

TEST(TestLinkInfo, GetSerializedSize)
{
    ::holo::map::LinkInfo          link;
    ASSERT_EQ(52, link.GetSerializedSize<4U>());
    ASSERT_EQ(72, link.GetSerializedSize<8U>());
}

TEST(TestLinkInfo, SerializeAndDeserialize)
{
   ::holo::map::LinkInfo link_input, link_output;
    link_input.SetID(10000);
    ::std::vector<::holo::map::LaneInfo> lane_list;
    lane_list.push_back(::holo::map::LaneInfo());
    lane_list.push_back(::holo::map::LaneInfo());
    link_input.SetLaneCount(lane_list.size());
    link_input.SetLaneInfos(::std::move(lane_list));
    link_input.SetWidth(100.0f);
    link_input.SetLength(2000.0f);
    link_input.SetMaxSpeedLimit(20.0f);
    link_input.SetMinSpeedLimit(20.0f);
    ::std::vector<::holo::geometry::Point3d> points = {::holo::geometry::Point3d(43.00f, 120.22f, 20.0),
                                             ::holo::geometry::Point3d(43.55f, 120.13f, 21.0)};
    link_input.SetRefPoints(::std::move(points));

    uint8_t buffer[1280U];
    holo::serialization::Serializer<>          serializer(buffer, 1280);
    serializer << link_input;
    ASSERT_EQ(link_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> link_output;

    ASSERT_EQ(link_input.GetID(), link_output.GetID());
    ASSERT_EQ(link_input.GetLaneCount(), link_output.GetLaneCount());
    ASSERT_EQ(link_input.GetRefPoints(), link_output.GetRefPoints());
    ASSERT_EQ(link_input.GetLength(), link_output.GetLength());
    ASSERT_EQ(link_input.GetWidth(), link_output.GetWidth());
    ASSERT_EQ(link_input.GetLaneInfos().size(), link_output.GetLaneInfos().size());
    ASSERT_EQ(link_input.GetLaneInfos().size(), link_output.GetLaneCount());
    ASSERT_EQ(link_input.GetLaneInfos().size(), link_output.GetLaneCount());
    ASSERT_EQ(link_input.GetMaxSpeedLimit(), link_output.GetMaxSpeedLimit());
    ASSERT_EQ(link_input.GetMinSpeedLimit(), link_output.GetMinSpeedLimit());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
