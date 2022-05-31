#include <iostream>
#include <gtest/gtest.h>
#include <holo/map/lane_info.h>

TEST(TestLaneInfo, Test_MapMsgBase_Valid)
{
    ::holo::map::LaneInfo lane;
    ASSERT_TRUE(lane.IsValid());

    auto indicator_size = lane.GetValidIndicatorSize();
    lane.SetValidIndicatorSize(100);
    ASSERT_FALSE(lane.IsValid());
    lane.SetValidIndicatorSize(indicator_size);
    ASSERT_TRUE(lane.IsValid());

    auto uint32_size = lane.GetValidUint32Size();
    lane.SetValidUint32Size(100);
    ASSERT_FALSE(lane.IsValid());
    lane.SetValidUint32Size(uint32_size);
    ASSERT_TRUE(lane.IsValid());

    auto float32_size = lane.GetValidFloat32Size();
    lane.SetValidFloat32Size(100);
    ASSERT_FALSE(lane.IsValid());
    lane.SetValidFloat32Size(float32_size);
    ASSERT_TRUE(lane.IsValid());
}

TEST(TestLaneInfo, Destructor)
{
    ::holo::map::LaneInfo *lane = new ::holo::map::LaneInfo();
    delete lane;
}

TEST(TestLaneInfo, Test_Convert_Uint)
{
    ::holo::map::LaneInfo lane;
    // now we have not any uint32 member variables.
    ASSERT_TRUE(true);
}

TEST(TestLaneInfo, Test_Convert_Float)
{
    ::holo::map::LaneInfo            lane;
    ::std::vector<::holo::float32_t> float32_values;
    // set width
    float32_values.push_back(3.75);
    // set length
    float32_values.push_back(100.33);
    // set max speed limit
    float32_values.push_back(33.33);
    // set min speed limit
    float32_values.push_back(20.22);

    ::std::vector<::holo::float32_t> float32_values_rvalue = float32_values;
    lane.SetValuesFloat32(float32_values);

    auto& float32_values_getter = lane.GetValuesFloat32();
    for (::std::size_t i = 0; i < float32_values.size(); i++)
    {
        ASSERT_NEAR(float32_values.at(i), float32_values_getter.at(i), 0.01);
    }

    lane.SetValuesFloat32(::std::move(float32_values_rvalue));
    auto& float32_values_rvalue_getter = lane.GetValuesFloat32();
    for (::std::size_t i = 0; i < float32_values.size(); i++)
    {
        ASSERT_NEAR(float32_values.at(i), float32_values_rvalue_getter.at(i), 0.01);
    }
}

TEST(TestLaneInfo, Test_Convert_Indicators_By_value)
{
    ::holo::map::LaneInfo lane;
    // now we have not any indicator
    ASSERT_TRUE(true);
}

TEST(TestLaneInfo, Test_Convert_Indicators)
{
    ::holo::map::LaneInfo lane;
    // now we have not any indicator
    ASSERT_TRUE(true);
}

void CreateALaneInfo(::holo::map::LaneInfo& lane)
{
    lane.SetId(1000);
    lane.SetSeq(2);
    lane.SetType(::holo::map::CommonLaneType::LANE_TYPE_SLOW);
    lane.SetMaxSpeedLimit(33.33f);
    lane.SetMinSpeedLimit(16.66f);
    lane.SetWidth(3.75f);
    lane.SetLength(100.1314f);
    lane.SetSuccLaneIds(::std::vector<::holo::map::KeyValue>({10000, 20000, 30000}));
    lane.SetPreLaneIds(::std::vector<::holo::map::KeyValue>({40000, 50000, 60000}));
    ::std::vector<::holo::geometry::Point3d> points = {::holo::geometry::Point3d(100.1, 40.2, 10.0), ::holo::geometry::Point3d(100.111, 42.2, 12.0)};
    lane.SetRefPoints(points);
}

void CompareTwoLaneInfoAreSame(const ::holo::map::LaneInfo& left, const ::holo::map::LaneInfo& right)
{
    ASSERT_EQ(left.GetId(), right.GetId());
    ASSERT_EQ(left.GetSeq(), right.GetSeq());
    ASSERT_EQ(left.GetType(), right.GetType());
    ASSERT_NEAR(left.GetMaxSpeedLimit(), right.GetMaxSpeedLimit(), 0.0001);
    ASSERT_NEAR(left.GetMinSpeedLimit(), right.GetMinSpeedLimit(), 0.0001);
    ASSERT_NEAR(left.GetWidth(), right.GetWidth(), 0.0001);
    ASSERT_NEAR(left.GetLength(), right.GetLength(), 0.0001);
    // ASSERT_EQ(left.GetLeftMark(), right.GetLeftMark());
    // ASSERT_EQ(left.GetRightMark(), right.GetRightMark());
    ASSERT_EQ(left.GetSuccLaneIds(), right.GetSuccLaneIds());
    ASSERT_EQ(left.GetPreLaneIds(), right.GetPreLaneIds());
    ASSERT_EQ(left.GetRefPoints().size(), right.GetRefPoints().size());
    ::std::size_t point_size = left.GetRefPoints().size();
    for (::std::size_t i = 0; i < point_size; i++)
    {
        const auto& lp = left.GetRefPoints().at(i);
        const auto& rp = right.GetRefPoints().at(i);
        ASSERT_NEAR(lp.GetX(), rp.GetX(), 0.0001);
        ASSERT_NEAR(lp.GetY(), rp.GetY(), 0.0001);
        ASSERT_NEAR(lp.GetZ(), rp.GetZ(), 0.0001);
    }
}

TEST(TestLaneInfo, Test_Constructor)
{
    ::holo::map::LaneInfo lane;
    ASSERT_EQ(lane.GetId(), ::std::numeric_limits<::holo::map::KeyValue>::max());
    ASSERT_EQ(lane.GetSeq(), ::std::numeric_limits<::holo::map::SeqValue>::max());
    ASSERT_EQ(lane.GetType(), ::holo::map::CommonLaneType::LANE_TYPE_UNDEFINED);
    ASSERT_NEAR(lane.GetMaxSpeedLimit(), 0, 0.0001);
    ASSERT_NEAR(lane.GetMinSpeedLimit(), 0, 0.0001);
    ASSERT_NEAR(lane.GetWidth(), 0.0, 0.0001);
    ASSERT_NEAR(lane.GetLength(), 0.0, 0.0001);
    ASSERT_TRUE(lane.GetSuccLaneIds().empty());
    ASSERT_TRUE(lane.GetPreLaneIds().empty());
    ASSERT_TRUE(lane.GetRefPoints().empty());
}
TEST(TestLaneInfo, Test_CopyConstructor)
{
    ::holo::map::LaneInfo lane;
    CreateALaneInfo(lane);
    ::holo::map::LaneInfo other(lane);
    CompareTwoLaneInfoAreSame(lane, other);
}
TEST(TestLaneInfo, Test_MoveCopyConstructor)
{
    ::holo::map::LaneInfo lane;
    CreateALaneInfo(lane);
    ::holo::map::LaneInfo copy(lane);
    auto                  address_ref       = &lane.GetRefPoints().at(0);
    auto                  address_succ_lane = &lane.GetSuccLaneIds().at(0);
    auto                  address_pre_lane  = &lane.GetPreLaneIds().at(0);
    ::holo::map::LaneInfo move(::std::move(lane));
    CompareTwoLaneInfoAreSame(move, copy);
    ASSERT_EQ(address_ref, &move.GetRefPoints().at(0));
    ASSERT_EQ(address_succ_lane, &move.GetSuccLaneIds().at(0));
    ASSERT_EQ(address_pre_lane, &move.GetPreLaneIds().at(0));
    ASSERT_TRUE(lane.GetRefPoints().empty());
    ASSERT_TRUE(lane.GetSuccLaneIds().empty());
    ASSERT_TRUE(lane.GetPreLaneIds().empty());
}
TEST(TestLaneInfo, Test_AssignmentOperator)
{
    ::holo::map::LaneInfo lane;
    CreateALaneInfo(lane);
    ::holo::map::LaneInfo other;
    other = lane;
    CompareTwoLaneInfoAreSame(lane, other);
}
TEST(TestLaneInfo, Test_MoveAssignmentOperator)
{
    ::holo::map::LaneInfo lane;
    CreateALaneInfo(lane);
    ::holo::map::LaneInfo copy(lane);
    auto                  address_ref       = &lane.GetRefPoints().at(0);
    auto                  address_succ_lane = &lane.GetSuccLaneIds().at(0);
    auto                  address_pre_lane  = &lane.GetPreLaneIds().at(0);
    ::holo::map::LaneInfo move;
    move = ::std::move(lane);
    CompareTwoLaneInfoAreSame(move, copy);
    ASSERT_EQ(address_ref, &move.GetRefPoints().at(0));
    ASSERT_EQ(address_succ_lane, &move.GetSuccLaneIds().at(0));
    ASSERT_EQ(address_pre_lane, &move.GetPreLaneIds().at(0));
    ASSERT_TRUE(lane.GetRefPoints().empty());
    ASSERT_TRUE(lane.GetSuccLaneIds().empty());
    ASSERT_TRUE(lane.GetPreLaneIds().empty());
}
TEST(TestLaneInfo, Test_ID)
{
    ::holo::map::LaneInfo lane;
    lane.SetId(1000);
    ASSERT_EQ(lane.GetId(), 1000);

    ::holo::map::KeyValue id = ::std::numeric_limits<::holo::map::KeyValue>::max();
    lane.SetId(id);
    ASSERT_EQ(lane.GetId(), ::std::numeric_limits<::holo::map::KeyValue>::max());

    id = ::std::numeric_limits<::holo::map::KeyValue>::min();
    lane.SetId(id);
    ASSERT_EQ(lane.GetId(), ::std::numeric_limits<::holo::map::KeyValue>::min());

    id = 0;
    lane.SetId(id);
    ASSERT_EQ(lane.GetId(), 0);

    // dont crash
    id = -1000;
    lane.SetId(id);
    ASSERT_TRUE(lane.GetId() > 0);
}
TEST(TestLaneInfo, Test_Seq)
{
    ::holo::map::LaneInfo lane;
    lane.SetSeq(100);
    ASSERT_EQ(lane.GetSeq(), 100);

    ::holo::map::SeqValue seq = ::std::numeric_limits<::holo::map::SeqValue>::max();
    lane.SetSeq(seq);
    ASSERT_EQ(lane.GetSeq(), ::std::numeric_limits<::holo::map::SeqValue>::max());

    seq = ::std::numeric_limits<::holo::map::SeqValue>::min();
    lane.SetSeq(seq);
    ASSERT_EQ(lane.GetSeq(), ::std::numeric_limits<::holo::map::SeqValue>::min());

    seq = 0;
    lane.SetSeq(seq);
    ASSERT_EQ(lane.GetSeq(), 0);

    // dont crash
    seq = -1;
    lane.SetSeq(seq);
    ASSERT_TRUE(lane.GetSeq());
}
TEST(TestLaneInfo, Test_Width)
{
    ::holo::map::LaneInfo lane;
    lane.SetWidth(100.00f);
    ASSERT_NEAR(lane.GetWidth(), 100.00f, 0.00001);

    ::holo::float32_t width = ::std::numeric_limits<::holo::float32_t>::max();
    lane.SetWidth(width);
    ASSERT_NEAR(lane.GetWidth(), ::std::numeric_limits<::holo::float32_t>::max(), 0.0001);

    width = ::std::numeric_limits<::holo::float32_t>::min();
    lane.SetWidth(width);
    ASSERT_NEAR(lane.GetWidth(), ::std::numeric_limits<::holo::float32_t>::min(), 0.0001);

    width = 0.0f;
    lane.SetWidth(width);
    ASSERT_NEAR(lane.GetWidth(), 0.0f, 0.0001);

    width = -1.0f;
    lane.SetWidth(width);
    ASSERT_NEAR(lane.GetWidth(), -1.0f, 0.0001);
}
TEST(TestLaneInfo, Test_Length)
{
    ::holo::map::LaneInfo lane;
    lane.SetLength(100.00f);
    ASSERT_NEAR(lane.GetLength(), 100.00f, 0.00001);

    ::holo::float32_t length = ::std::numeric_limits<::holo::float32_t>::max();
    lane.SetLength(length);
    ASSERT_NEAR(lane.GetLength(), ::std::numeric_limits<::holo::float32_t>::max(), 0.0001);

    length = ::std::numeric_limits<::holo::float32_t>::min();
    lane.SetLength(length);
    ASSERT_NEAR(lane.GetLength(), ::std::numeric_limits<::holo::float32_t>::min(), 0.0001);

    length = 0.0f;
    lane.SetLength(length);
    ASSERT_NEAR(lane.GetLength(), 0.0f, 0.0001);

    length = -1.0f;
    lane.SetLength(length);
    ASSERT_NEAR(lane.GetLength(), -1.0f, 0.0001);
}
TEST(TestLaneInfo, Test_MaxSpeedLimit)
{
    ::holo::map::LaneInfo lane;
    lane.SetMaxSpeedLimit(16.66f);
    ASSERT_NEAR(lane.GetMaxSpeedLimit(), 16.66f, 0.0001);

    ::holo::float32_t speed = ::std::numeric_limits<::holo::float32_t>::max();
    lane.SetMaxSpeedLimit(speed);
    ASSERT_NEAR(lane.GetMaxSpeedLimit(), ::std::numeric_limits<::holo::float32_t>::max(), 0.0001);

    speed = ::std::numeric_limits<::holo::float32_t>::min();
    lane.SetMaxSpeedLimit(speed);
    ASSERT_NEAR(lane.GetMaxSpeedLimit(), ::std::numeric_limits<::holo::float32_t>::min(), 0.0001);

    speed = 0;
    lane.SetMaxSpeedLimit(speed);
    ASSERT_NEAR(lane.GetMaxSpeedLimit(), 0.0, 0.0001);

    speed = -1.0;
    lane.SetMaxSpeedLimit(speed);
    ASSERT_NEAR(lane.GetMaxSpeedLimit(), -1.0, 0.0001);
}
TEST(TestLaneInfo, Test_MinSpeedLimit)
{
    ::holo::map::LaneInfo lane;
    lane.SetMinSpeedLimit(100.00f);
    ASSERT_NEAR(lane.GetMinSpeedLimit(), 100.00f, 0.0001);

    ::holo::float32_t speed = ::std::numeric_limits<::holo::float32_t>::max();
    lane.SetMinSpeedLimit(speed);
    ASSERT_NEAR(lane.GetMinSpeedLimit(), ::std::numeric_limits<::holo::float32_t>::max(), 0.0001);

    speed = ::std::numeric_limits<::holo::float32_t>::min();
    lane.SetMinSpeedLimit(speed);
    ASSERT_NEAR(lane.GetMinSpeedLimit(), ::std::numeric_limits<::holo::float32_t>::min(), 0.0001);

    speed = 0.0f;
    lane.SetMinSpeedLimit(speed);
    ASSERT_NEAR(lane.GetMinSpeedLimit(), 0, 0.0001);

    // dont crash
    speed = -1.0f;
    lane.SetMinSpeedLimit(speed);
    ASSERT_NEAR(lane.GetMinSpeedLimit(), -1.0f, 0.0001);
}
TEST(TestLaneInfo, Test_Type)
{
    ::holo::map::LaneInfo lane;
    lane.SetType(::holo::map::CommonLaneType::LANE_TYPE_SLOW);
    ASSERT_EQ(lane.GetType(), ::holo::map::CommonLaneType::LANE_TYPE_SLOW);
}
TEST(TestLaneInfo, Test_LeftMark)
{
    ::holo::map::LaneInfo     lane;
    ::holo::map::LaneMarkInfo lane_mark;

    lane_mark.SetMarkWidth(100.00f);
    lane.SetLeftMark(lane_mark);
    ASSERT_NEAR(lane_mark.GetMarkWidth(), lane.GetLeftMark().GetMarkWidth(), 0.0001);

    ::std::vector<::holo::geometry::Point3d> points = {::holo::geometry::Point3d(100.1, 40.2, 10.0), ::holo::geometry::Point3d(100.111, 42.2, 12.0)};
    lane_mark.SetRefPoints(::std::move(points));

    auto address = &lane_mark.GetRefPoints().at(0);
    lane.SetLeftMark(::std::move(lane_mark));
    ASSERT_EQ(&lane.GetLeftMark().GetRefPoints().at(0), address);
}
TEST(TestLaneInfo, Test_RightMark)
{
    ::holo::map::LaneInfo     lane;
    ::holo::map::LaneMarkInfo lane_mark;

    lane_mark.SetMarkWidth(100.00f);
    lane.SetRightMark(lane_mark);
    ASSERT_NEAR(lane_mark.GetMarkWidth(), lane.GetRightMark().GetMarkWidth(), 0.0001);

    ::std::vector<::holo::geometry::Point3d> points = {::holo::geometry::Point3d(100.1, 40.2, 10.0), ::holo::geometry::Point3d(100.111, 42.2, 12.0)};
    lane_mark.SetRefPoints(::std::move(points));

    auto address = &lane_mark.GetRefPoints().at(0);
    lane.SetRightMark(::std::move(lane_mark));
    ASSERT_EQ(&lane.GetRightMark().GetRefPoints().at(0), address);
}
TEST(TestLaneInfo, Test_SuccLaneIds)
{
    ::holo::map::LaneInfo                lane;
    ::std::vector<::holo::map::KeyValue> lane_seq_list = {100000, 2222222, 333333};
    lane.SetSuccLaneIds(lane_seq_list);
    ASSERT_EQ(lane.GetSuccLaneIds(), lane_seq_list);

    auto address = &lane_seq_list.at(0);
    lane.SetSuccLaneIds(::std::move(lane_seq_list));
    ASSERT_EQ(address, &lane.GetSuccLaneIds().at(0));
}
TEST(TestLaneInfo, Test_PreLaneIds)
{
    ::holo::map::LaneInfo                lane;
    ::std::vector<::holo::map::KeyValue> lane_seq_list = {100000, 2222222, 333333};
    lane.SetPreLaneIds(lane_seq_list);
    ASSERT_EQ(lane.GetPreLaneIds(), lane_seq_list);

    auto address = &lane_seq_list.at(0);
    lane.SetPreLaneIds(::std::move(lane_seq_list));
    ASSERT_EQ(address, &lane.GetPreLaneIds().at(0));
}
TEST(TestLaneInfo, Test_RefPoints)
{
    ::holo::map::LaneInfo          lane;
    ::std::vector<::holo::geometry::Point3d> points = {::holo::geometry::Point3d(100.1, 40.2, 10.0), ::holo::geometry::Point3d(100.111, 42.2, 12.0)};
    lane.SetRefPoints(points);
    ASSERT_EQ(points, lane.GetRefPoints());
    auto address = &points.at(0);
    ASSERT_TRUE(address != &lane.GetRefPoints().at(0));

    lane.SetRefPoints(::std::move(points));
    ASSERT_TRUE(address == &lane.GetRefPoints().at(0));
}
TEST(TestLaneInfo, Test_ToString)
{
    // TODO zhaofx 2019-08-24: For function ToString.
}

TEST(TestLaneInfo, GetSerializedSize)
{
    ::holo::map::LaneInfo          lane;
    ASSERT_EQ(112, lane.GetSerializedSize<4U>());
    ASSERT_EQ(144, lane.GetSerializedSize<8U>());
}

TEST(TestLaneInfo, SerializeAndDeserialize)
{
    ::holo::map::LaneInfo lane_input, lane_output;

    lane_input.SetId(1000);
    lane_input.SetSeq(2);
    lane_input.SetType(::holo::map::CommonLaneType::LANE_TYPE_SLOW);
    lane_input.SetMaxSpeedLimit(33.33f);
    lane_input.SetMinSpeedLimit(16.66f);
    lane_input.SetWidth(3.75f);
    lane_input.SetLength(100.1314f);
    lane_input.SetSuccLaneIds(::std::vector<::holo::map::KeyValue>({10000, 20000, 30000}));
    lane_input.SetPreLaneIds(::std::vector<::holo::map::KeyValue>({40000, 50000, 60000}));
    ::std::vector<::holo::geometry::Point3d> points = 
           {::holo::geometry::Point3d(100.1, 40.2, 10.0), ::holo::geometry::Point3d(100.111, 42.2, 12.0)};
    lane_input.SetRefPoints(points);

    uint8_t buffer[256];
    holo::serialization::Serializer<>          serializer(buffer, 256);
    serializer << lane_input;
    ASSERT_EQ(lane_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> lane_output;

    ASSERT_EQ(lane_input.GetId(), lane_output.GetId());
    ASSERT_EQ(lane_input.GetSeq(), lane_output.GetSeq());
    ASSERT_EQ(lane_input.GetType(), lane_output.GetType());
    ASSERT_EQ(lane_input.GetMaxSpeedLimit(), lane_output.GetMaxSpeedLimit());
    ASSERT_EQ(lane_input.GetMinSpeedLimit(), lane_output.GetMinSpeedLimit());
    ASSERT_EQ(lane_input.GetWidth(), lane_output.GetWidth());
    ASSERT_EQ(lane_input.GetLength(),lane_output.GetLength());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
