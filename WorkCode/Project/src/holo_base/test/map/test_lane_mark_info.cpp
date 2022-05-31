#include <iostream>
#include <gtest/gtest.h>
#include <holo/map/lane_mark_info.h>

TEST(TestLaneInfo, Test_MapMsgBase_Valid)
{
    ::holo::map::LaneMarkInfo lane_mark;
    ASSERT_TRUE(lane_mark.IsValid());

    auto indicator_size = lane_mark.GetValidIndicatorSize();
    lane_mark.SetValidIndicatorSize(100);
    ASSERT_FALSE(lane_mark.IsValid());
    lane_mark.SetValidIndicatorSize(indicator_size);
    ASSERT_TRUE(lane_mark.IsValid());

    auto uint32_size = lane_mark.GetValidUint32Size();
    lane_mark.SetValidUint32Size(100);
    ASSERT_FALSE(lane_mark.IsValid());
    lane_mark.SetValidUint32Size(uint32_size);
    ASSERT_TRUE(lane_mark.IsValid());

    auto float32_size = lane_mark.GetValidFloat32Size();
    lane_mark.SetValidFloat32Size(100);
    ASSERT_FALSE(lane_mark.IsValid());
    lane_mark.SetValidFloat32Size(float32_size);
    ASSERT_TRUE(lane_mark.IsValid());
}

TEST(TestLaneInfo, Test_Destructor)
{
    ::holo::map::LaneMarkInfo *lane_mark = new ::holo::map::LaneMarkInfo();
    delete lane_mark;
}

TEST(TestLaneMarkInfo, Test_Convert_Uint)
{
    ::holo::map::LaneMarkInfo lane_mark;
    // now we have not any uint32 member variables.
    ASSERT_TRUE(true);
}

TEST(TestLaneMarkInfo, Test_Convert_Float)
{
    ::holo::map::LaneMarkInfo            lane_mark;
    ::std::vector<::holo::float32_t> float32_values;
    // set mark width
    float32_values.push_back(3.75);

    ::std::vector<::holo::float32_t> float32_values_rvalue = float32_values;
    lane_mark.SetValuesFloat32(float32_values);

    auto& float32_values_getter = lane_mark.GetValuesFloat32();
    for (::std::size_t i = 0; i < float32_values.size(); i++)
    {
        ASSERT_NEAR(float32_values.at(i), float32_values_getter.at(i), 0.01);
    }

    lane_mark.SetValuesFloat32(::std::move(float32_values_rvalue));
    auto& float32_values_rvalue_getter = lane_mark.GetValuesFloat32();
    for (::std::size_t i = 0; i < float32_values.size(); i++)
    {
        ASSERT_NEAR(float32_values.at(i), float32_values_rvalue_getter.at(i), 0.01);
    }
}

TEST(TestLaneMarkInfo, Test_Convert_Indicators_By_value)
{
    ::holo::map::LaneMarkInfo lane_mark;
    // now we have not any indicator
    ASSERT_TRUE(true);
}

TEST(TestLaneMarkInfo, Test_Convert_Indicators)
{
    ::holo::map::LaneMarkInfo lane_mark;
    // now we have not any indicator
    ASSERT_TRUE(true);
}

void CreateLaneMarkInfo(::holo::map::LaneMarkInfo& _lane_mark)
{
    _lane_mark.SetMarkType(::holo::map::CommonMarkType::MARK_TYPE_DOUBLE_SOLID);
    _lane_mark.SetMarkColor(::holo::map::CommonMarkColor::MARK_COLOR_YELLOW);
    _lane_mark.SetMarkMaterial(::holo::map::CommonMarkMaterial::MARK_MATERIAL_PAINTED);
    _lane_mark.SetRhombusDecelerationMarking(
        ::holo::map::CommonRhombusDecelerationMarking::RHOMBUS_DECELERATION_MARKING_LEFT);
    _lane_mark.SetMarkWidth(3.75);
    ::std::vector<::holo::geometry::Point3d> points = {::holo::geometry::Point3d(100.1, 40.2, 10.0), ::holo::geometry::Point3d(100.111, 42.2, 12.0)};
    _lane_mark.SetRefPoints(::std::move(points));
}

void CompareTwoLaneMarkInfoAreSame(const ::holo::map::LaneMarkInfo& _left_lane_mark,
                                   const ::holo::map::LaneMarkInfo& _right_lane_mark)
{
    ASSERT_EQ(_left_lane_mark.GetMarkType(), _right_lane_mark.GetMarkType());
    ASSERT_EQ(_left_lane_mark.GetMarkColor(), _right_lane_mark.GetMarkColor());
    ASSERT_EQ(_left_lane_mark.GetMarkMaterial(), _right_lane_mark.GetMarkMaterial());
    ASSERT_EQ(_left_lane_mark.GetRhombusDecelerationMarking(), _right_lane_mark.GetRhombusDecelerationMarking());
    ASSERT_EQ(_left_lane_mark.GetMarkWidth(), _right_lane_mark.GetMarkWidth());
    ASSERT_EQ(_left_lane_mark.GetRefPoints().size(), _right_lane_mark.GetRefPoints().size());
    const auto point_size = _left_lane_mark.GetRefPoints().size();
    for (::std::size_t i = 0; i < point_size; i++)
    {
        const auto& lp = _left_lane_mark.GetRefPoints().at(i);
        const auto& rp = _right_lane_mark.GetRefPoints().at(i);

        ASSERT_NEAR(lp.GetX(), rp.GetX(), 0.0001);
        ASSERT_NEAR(lp.GetY(), rp.GetY(), 0.0001);
        ASSERT_NEAR(lp.GetZ(), rp.GetZ(), 0.0001);
    }
}

TEST(TestLaneMarkInfo, Test_Constructor)
{
    ::holo::map::LaneMarkInfo lane_mark;
    ASSERT_EQ(lane_mark.GetMarkType(), ::holo::map::CommonMarkType::MARK_TYPE_NOT_INVESTIGATED);
    ASSERT_EQ(lane_mark.GetMarkColor(), ::holo::map::CommonMarkColor::MARK_COLOR_NOT_APPLICABLE);
    ASSERT_EQ(lane_mark.GetMarkMaterial(), ::holo::map::CommonMarkMaterial::MARK_MATERIAL_NOT_APPLICABLE);
    ASSERT_EQ(lane_mark.GetRhombusDecelerationMarking(),
              ::holo::map::CommonRhombusDecelerationMarking::RHOMBUS_DECELERATION_MARKING_NOT_APPLICABLE);
    ASSERT_TRUE(lane_mark.GetRefPoints().empty());
    ASSERT_NEAR(lane_mark.GetMarkWidth(), 0.0, 0.00001);
}
TEST(TestLaneMarkInfo, Test_CopyConstructor)
{
    ::holo::map::LaneMarkInfo lane_mark;
    CreateLaneMarkInfo(lane_mark);
    ::holo::map::LaneMarkInfo lane_other(lane_mark);
    CompareTwoLaneMarkInfoAreSame(lane_mark, lane_other);
    ASSERT_FALSE(&lane_mark.GetRefPoints().at(0) == &lane_other.GetRefPoints().at(0));
}
TEST(TestLaneMarkInfo, Test_MoveCopyConstructor)
{
    ::holo::map::LaneMarkInfo lane_mark;
    CreateLaneMarkInfo(lane_mark);
    ::holo::map::LaneMarkInfo lane_copy(lane_mark);
    auto                      address = &lane_mark.GetRefPoints().at(0);
    ::holo::map::LaneMarkInfo lane_move(::std::move(lane_mark));

    CompareTwoLaneMarkInfoAreSame(lane_copy, lane_move);
    ASSERT_EQ(address, &lane_move.GetRefPoints().at(0));
}
TEST(TestLaneMarkInfo, Test_AssignmentOperator)
{
    ::holo::map::LaneMarkInfo lane_mark;
    CreateLaneMarkInfo(lane_mark);
    ::holo::map::LaneMarkInfo lane_other;
    lane_other = lane_mark;
    CompareTwoLaneMarkInfoAreSame(lane_mark, lane_other);
    ASSERT_FALSE(&lane_mark.GetRefPoints().at(0) == &lane_other.GetRefPoints().at(0));
}
TEST(TestLaneMarkInfo, Test_MoveAssignmentOperator)
{
    ::holo::map::LaneMarkInfo lane_mark;
    CreateLaneMarkInfo(lane_mark);
    ::holo::map::LaneMarkInfo lane_copy;
    lane_copy                         = lane_mark;
    auto                      address = &lane_mark.GetRefPoints().at(0);
    ::holo::map::LaneMarkInfo lane_move;
    lane_move = ::std::move(lane_mark);
    CompareTwoLaneMarkInfoAreSame(lane_copy, lane_move);
    ASSERT_EQ(address, &lane_move.GetRefPoints().at(0));
}
TEST(TestLaneMarkInfo, Test_MarkType)
{
    ::holo::map::LaneMarkInfo lane_mark;
    lane_mark.SetMarkType(::holo::map::CommonMarkType::MARK_TYPE_DOUBLE_SOLID);
    ASSERT_EQ(lane_mark.GetMarkType(), ::holo::map::CommonMarkType::MARK_TYPE_DOUBLE_SOLID);
}
TEST(TestLaneMarkInfo, Test_MarkColor)
{
    ::holo::map::LaneMarkInfo lane_mark;
    lane_mark.SetMarkColor(::holo::map::CommonMarkColor::MARK_COLOR_YELLOW);
    ASSERT_EQ(lane_mark.GetMarkColor(), ::holo::map::CommonMarkColor::MARK_COLOR_YELLOW);
}
TEST(TestLaneMarkInfo, Test_MarkMaterial)
{
    ::holo::map::LaneMarkInfo lane_mark;
    lane_mark.SetMarkMaterial(::holo::map::CommonMarkMaterial::MARK_MATERIAL_PAINTED);
    ASSERT_EQ(lane_mark.GetMarkMaterial(), ::holo::map::CommonMarkMaterial::MARK_MATERIAL_PAINTED);
}
TEST(TestLaneMarkInfo, Test_RhombusDecelerationMarking)
{
    ::holo::map::LaneMarkInfo lane_mark;
    lane_mark.SetRhombusDecelerationMarking(
        ::holo::map::CommonRhombusDecelerationMarking::RHOMBUS_DECELERATION_MARKING_LEFT);
    ASSERT_EQ(lane_mark.GetRhombusDecelerationMarking(),
              ::holo::map::CommonRhombusDecelerationMarking::RHOMBUS_DECELERATION_MARKING_LEFT);
}
TEST(TestLaneMarkInfo, Test_MarkWidth)
{
    ::holo::map::LaneMarkInfo lane_mark;
    lane_mark.SetMarkWidth(13.14);
    ASSERT_NEAR(lane_mark.GetMarkWidth(), 13.14, 0.0001);
}
TEST(TestLaneMarkInfo, Test_RefPoints)
{
    ::holo::map::LaneMarkInfo      lane_mark;
    ::std::vector<::holo::geometry::Point3d> points = {::holo::geometry::Point3d(100.1, 40.2, 10.0), ::holo::geometry::Point3d(100.111, 42.2, 12.0)};
    ::std::vector<::holo::geometry::Point3d> points_backup = points;
    lane_mark.SetRefPoints(::std::move(points));
    const auto point_size = lane_mark.GetRefPoints().size();
    for (::std::size_t i = 0; i < point_size; i++)
    {
        const auto& lp = points_backup.at(i);
        const auto& rp = lane_mark.GetRefPoints().at(i);

        ASSERT_NEAR(lp.GetX(), rp.GetX(), 0.0001);
        ASSERT_NEAR(lp.GetY(), rp.GetY(), 0.0001);
        ASSERT_NEAR(lp.GetZ(), rp.GetZ(), 0.0001);
    }
}
TEST(TestLaneMarkInfo, Test_ToString)
{
    // TODO zhaofx 2019-08-23: ToString google test.
}

TEST(TestLaneMarkInfo, GetSerializedSize)
{
    ::holo::map::LaneMarkInfo      lane_mark;
    ASSERT_EQ(28, lane_mark.GetSerializedSize<4U>());
    ASSERT_EQ(32, lane_mark.GetSerializedSize<8U>());
}

TEST(TestLaneMarkInfo, SerializeAndDeserialize)
{
    ::holo::map::LaneMarkInfo lane_mark_input, lane_mark_output;

    lane_mark_input.SetMarkType(::holo::map::CommonMarkType::MARK_TYPE_DOUBLE_SOLID);
    lane_mark_input.SetMarkColor(::holo::map::CommonMarkColor::MARK_COLOR_YELLOW);
    lane_mark_input.SetMarkMaterial(::holo::map::CommonMarkMaterial::MARK_MATERIAL_PAINTED);
    lane_mark_input.SetRhombusDecelerationMarking(
        ::holo::map::CommonRhombusDecelerationMarking::RHOMBUS_DECELERATION_MARKING_LEFT);
    lane_mark_input.SetMarkWidth(3.75);
    ::std::vector<::holo::geometry::Point3d> points = {::holo::geometry::Point3d(100.1, 40.2, 10.0), ::holo::geometry::Point3d(100.111, 42.2, 12.0)};
    lane_mark_input.SetRefPoints(::std::move(points));

    uint8_t buffer[128];
    holo::serialization::Serializer<>          serializer(buffer, 128);
    serializer << lane_mark_input;
    ASSERT_EQ(lane_mark_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> lane_mark_output;

    ASSERT_EQ(lane_mark_input.GetMarkType(), lane_mark_output.GetMarkType());
    ASSERT_EQ(lane_mark_input.GetMarkColor(), lane_mark_output.GetMarkColor());
    ASSERT_EQ(lane_mark_input.GetMarkMaterial(), lane_mark_output.GetMarkMaterial());
    ASSERT_EQ(lane_mark_input.GetRhombusDecelerationMarking(), lane_mark_output.GetRhombusDecelerationMarking());
    ASSERT_EQ(lane_mark_input.GetRefPoints().empty(), lane_mark_output.GetRefPoints().empty());
    ASSERT_EQ(lane_mark_input.GetMarkWidth(), lane_mark_output.GetMarkWidth());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
