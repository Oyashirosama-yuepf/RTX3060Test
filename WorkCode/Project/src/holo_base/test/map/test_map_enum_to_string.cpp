#include <holo/map/map_enum.h>
#include <iostream>

#include <gtest/gtest.h>

using namespace std;

TEST(TestEnum, ToStringCrossingTypeNormal)
{
    ::std::stringstream ss;

    int32_t type_max = static_cast<int32_t>(::holo::map::CrossingType::ENUM_MODEL_TYPE_MAX);
    int32_t type_min = static_cast<int32_t>(::holo::map::CrossingType::DESTINATION);
    for (int32_t i = type_min; i < type_max; i++)
    {
        ss << static_cast<::holo::map::CrossingType>(i);
        if (i < type_max - 1)
        {
            ss << ",";
        }
    }
    ::std::string content = ss.str();

    ::std::string crossing_type_content =
        "DESTINATION"
        ",TOLL_ENTRANCE"
        ",TOLL_STOP"
        ",TOLL_EXIT"
        ",TOLL_ETC_ENTRANCE"
        ",TOLL_ETC_SLOW"
        ",TOLL_ETC_EXIT"
        ",TUNNEL_ENTRANCE"
        ",TUNNEL_EXIT"
        ",MOTORWAY_PASS_BY_ENTRANCE"
        ",MOTORWAY_PASS_BY_EXIT"
        ",MOTORWAY_TO_RAMP"
        ",MOTORWAY_TO_JCT"
        ",RAMP_TO_MOTORWAY"
        ",JCT_TO_MOTORWAY"
        ",JCT_SPLIT"
        ",JCT_MERGE"
        ",MOTORWAY_RIGHT_NARROWED"
        ",MOTORWAY_RIGHT_EXPANDED"
        ",MOTORWAY_MIDDLE_NARROWED"
        ",MOTORWAY_MIDDLE_EXPANDED"
        ",MOTORWAY_LEFT_NARROWED"
        ",MOTORWAY_LEFT_EXPANDED"
        ",MOTORWAY_BOTH_SIDE_NARROWED"
        ",MOTORWAY_BOTH_SIDE_EXPANDED"
        ",JCT_RIGHT_NARROWED"
        ",JCT_RIGHT_EXPANDED"
        ",JCT_MIDDLE_NARROWED"
        ",JCT_MIDDLE_EXPANDED"
        ",JCT_LEFT_NARROWED"
        ",JCT_LEFT_EXPANDED"
        ",JCT_BOTH_SIDE_NARROWED"
        ",JCT_BOTH_SIDE_EXPANDED"
        ",MOTORWAY_LANE_NUM_INCREASE"
        ",MOTORWAY_LANE_NUM_DECREASE"
        ",JCT_LANE_NUM_INCREASE"
        ",JCT_LANE_NUM_DECREASE"
        ",ACCELERATION_LANE"
        ",DECELERATION_LANE"
        ",JCT"
        ",TOLL"
        ",TUNNEL"
        ",BRIDGE"
        ",RAMP_ENTRANCE"
        ",RAMP_EXIT"
        ",MOTORWAY"
        ",NONE_MOTORWAY_AREA"
        ",RESTRICT_ROAD"
        ",MAP_ERROR"
        ",NO_MODEL";
    ASSERT_EQ(crossing_type_content, content);
}

TEST(TestEnum, ToStringCrossingTypeOverflow)
{
    ::std::stringstream ss;
    int                 type_max = static_cast<int>(::holo::map::CrossingType::ENUM_MODEL_TYPE_MAX);
    int                 type_min = static_cast<int>(::holo::map::CrossingType::DESTINATION);

    ss << static_cast<::holo::map::CrossingType>(type_max + 1);
    const ::std::string overflow = "???";
    ::std::string       content  = ss.str();

    ASSERT_EQ(overflow, content);

    ::std::stringstream ss_1;
    ss_1 << static_cast<::holo::map::CrossingType>(type_min - 1);
    content = ss_1.str();
    ASSERT_EQ(overflow, content);
}

TEST(TestEnum, ToStringCommonLinkType)
{
    std::stringstream stream;

    const holo::int32_t start = static_cast<holo::int32_t>(holo::map::CommonLinkType::LINK_TYPE_UNDEFINED);
    const holo::int32_t end = static_cast<holo::int32_t>(holo::map::CommonLinkType::LINK_TYPE_MAX);

    for (holo::int32_t i = start; i < end; ++i)
    {
        stream << static_cast<holo::map::CommonLinkType>(i) << ",";
    }

    const std::string content = stream.str();
    const std::string criterion = "LINK_TYPE_UNDEFINED"
                                  ",LINK_TYPE_MOTORWAY"
                                  ",LINK_TYPE_MOTORWAY_BRIDGE"
                                  ",LINK_TYPE_MOTORWAY_TUNNEL"
                                  ",LINK_TYPE_MOTORWAY_RAMP_ENTRANCE"
                                  ",LINK_TYPE_MOTORWAY_RAME_EXIT"
                                  ",LINK_TYPE_MOTORWAY_JCT"
                                  ",LINK_TYPE_MOTORWAY_TOLL"
                                  ",LINK_TYPE_MOTORWAY_TOLL_ENTRANCE"
                                  ",LINK_TYPE_MOTORWAY_TOOL_EXIT"
                                  ",";
    EXPECT_EQ(content, criterion);
}

TEST(TestEnum, ToStringCommonLinkTypeOverflow)
{
    const holo::int32_t start = static_cast<holo::int32_t>(holo::map::CommonLinkType::LINK_TYPE_UNDEFINED);
    const holo::int32_t end = static_cast<holo::int32_t>(holo::map::CommonLinkType::LINK_TYPE_MAX);

    {
        std::stringstream stream;
        stream.clear();
        stream << static_cast<holo::map::CommonLinkType>(start-1);
        EXPECT_EQ(stream.str(), std::string("???"));
    }
    
    {
        std::stringstream stream;
        stream.clear();
        stream << static_cast<holo::map::CommonLinkType>(end+1);
        EXPECT_EQ(stream.str(), std::string("???"));
    }
}

TEST(TestEnum, ToStringCommonLaneType)
{
    ::std::stringstream ss;

    int32_t type_max = static_cast<int32_t>(::holo::map::CommonLaneType::LANE_TYPE_MAX);
    int32_t type_min = static_cast<int32_t>(::holo::map::CommonLaneType::LANE_TYPE_UNDEFINED);
    for (int32_t i = type_min; i < type_max; i++)
    {
        ss << static_cast<::holo::map::CommonLaneType>(i);
        if (i < type_max - 1)
        {
            ss << ",";
        }
    }
    ::std::string content = ss.str();
    ::std::string common_lane_content =
        "LANE_TYPE_UNDEFINED"
        ",LANE_TYPE_REGULAR,LANE_TYPE_ACCELERATION,LANE_TYPE_DECELERATION,LANE_TYPE_HOV,LANE_TYPE_SLOW,LANE_TYPE_"
        "PASSING_OVERTAKING,LANE_TYPE_HARD_SHOULDER,LANE_TYPE_TRUCK_PARKING,LANE_TYPE_REGULATED_ACCESS,LANE_TYPE_SOFT_"
        "SHOULDER,LANE_TYPE_EMERGENCY_PARKING_STRIP,LANE_TYPE_BUS,LANE_TYPE_BICYCLE,LANE_TYPE_TURN,LANE_TYPE_"
        "REVERSIBLE,LANE_TYPE_CENTER_TUEN,LANE_TYPE_TRUCK_ESCAPE,LANE_TYPE_VARIABLE_DRIVING_LANE,LANE_TYPE_PARKING_"
        "LANE,LANE_TYPE_COMPOUND_LANE,LANE_TYPE_JUNCTION_LANE,LANE_TYPE_ROUNDABOUT_LANE,LANE_TYPE_OTHER";
    ASSERT_EQ(common_lane_content, content);
}

TEST(TestEnum, ToStringCommonLaneTypeOverflow)
{
    ::std::stringstream ss;
    int32_t             type_max = static_cast<int32_t>(::holo::map::CommonLaneType::LANE_TYPE_MAX);
    int32_t             type_min = static_cast<int32_t>(::holo::map::CommonLaneType::LANE_TYPE_UNDEFINED);

    ss << static_cast<::holo::map::CommonLaneType>(type_max + 1);
    const ::std::string overflow = "???";
    ::std::string       content  = ss.str();

    ASSERT_EQ(overflow, content);

    ::std::stringstream ss_1;
    ss_1 << static_cast<::holo::map::CommonLaneType>(type_min - 1);
    content = ss_1.str();
    ASSERT_EQ(overflow, content);
}

TEST(TestEnum, ToStringCommonLaneTransType)
{
    std::stringstream stream;

    const holo::int32_t start = static_cast<holo::int32_t>(holo::map::CommonLaneTransType::LANE_TRANS_TYPE_NO_ATTRIBUTE);
    const holo::int32_t end = static_cast<holo::int32_t>(holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MAX);

    for (holo::int32_t i = start; i < end; ++i)
    {
        stream << static_cast<holo::map::CommonLaneTransType>(i) << ",";
    }

    const std::string content = stream.str();
    const std::string criterion = "LANE_TRANS_TYPE_NO_ATTRIBUTE"
                                  ",LANE_TRANS_TYPE_MERGE_TO_LEFT_FORBIDDEN"
                                  ",LANE_TRANS_TYPE_MERGE_TO_RIGHT_FORBIDDEN"
                                  ",LANE_TRANS_TYPE_MERGE_TO_LEFT_OPTIONAL"
                                  ",LANE_TRANS_TYPE_MERGE_TO_LEFT_FORCED"
                                  ",LANE_TRANS_TYPE_MERGE_TO_RIGHT_OPTIONAL"
                                  ",LANE_TRANS_TYPE_MERGE_TO_RIGHT_FORCED"
                                  ",LANE_TRANS_TYPE_MERGED_BY_LEFT"
                                  ",LANE_TRANS_TYPE_MERGED_BY_RIGHT"
                                  ",";
    EXPECT_EQ(content, criterion);
}

TEST(TestEnum, ToStringCommonLaneTransTypeOverflow)
{
    const holo::int32_t start = static_cast<holo::int32_t>(holo::map::CommonLaneTransType::LANE_TRANS_TYPE_NO_ATTRIBUTE);
    const holo::int32_t end = static_cast<holo::int32_t>(holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MAX);

    {
        std::stringstream stream;
        stream.clear();
        stream << static_cast<holo::map::CommonLaneTransType>(start-1);
        EXPECT_EQ(stream.str(), std::string("???"));
    }

    {
        std::stringstream stream;
        stream.clear();
        stream << static_cast<holo::map::CommonLaneTransType>(end+1);
        EXPECT_EQ(stream.str(), std::string("???"));
    }
}

TEST(TestEnum, ToStringCommonMarkColor)
{
    ::std::stringstream ss;

    int32_t type_max = static_cast<int32_t>(::holo::map::CommonMarkColor::MARK_COLOR_MAX);
    int32_t type_min = static_cast<int32_t>(::holo::map::CommonMarkColor::MARK_COLOR_NOT_APPLICABLE);
    for (int32_t i = type_min; i < type_max; i++)
    {
        ss << static_cast<::holo::map::CommonMarkColor>(i);
        if (i < type_max - 1)
        {
            ss << ",";
        }
    }
    ::std::string content             = ss.str();
    ::std::string common_lane_content = "MARK_COLOR_NOT_APPLICABLE"
                                        ",MARK_COLOR_OTHERS,MARK_COLOR_WHITE,MARK_COLOR_YELLOW,MARK_COLOR_LEFT_YELLOW_"
                                        "RIGHT_WHITE,MARK_COLOR_LEFT_WHITE_RIGHT_YELLOW";
    ASSERT_EQ(common_lane_content, content);
}

TEST(TestEnum, ToStringCommonMarkColorOverflow)
{
    ::std::stringstream ss;
    int32_t             type_max = static_cast<int32_t>(::holo::map::CommonMarkColor::MARK_COLOR_MAX);
    int32_t             type_min = static_cast<int32_t>(::holo::map::CommonMarkColor::MARK_COLOR_NOT_APPLICABLE);

    ss << static_cast<::holo::map::CommonMarkColor>(type_max + 1);
    const ::std::string overflow = "???";
    ::std::string       content  = ss.str();

    ASSERT_EQ(overflow, content);

    ::std::stringstream ss_1;
    ss_1 << static_cast<::holo::map::CommonMarkColor>(type_min - 1);
    content = ss_1.str();
    ASSERT_EQ(overflow, content);
}

TEST(TestEnum, ToStringCommonMarkType)
{
    ::std::stringstream ss;

    int32_t type_max = static_cast<int32_t>(::holo::map::CommonMarkType::MARK_TYPE_MAX);
    int32_t type_min = static_cast<int32_t>(::holo::map::CommonMarkType::MARK_TYPE_NOT_INVESTIGATED);
    for (int32_t i = type_min; i < type_max; i++)
    {
        ss << static_cast<::holo::map::CommonMarkType>(i);
        if (i < type_max - 1)
        {
            ss << ",";
        }
    }
    ::std::string content             = ss.str();
    ::std::string common_lane_content = "MARK_TYPE_NOT_INVESTIGATED"
                                        ",MARK_TYPE_SINGLE_DASHED,MARK_TYPE_SHORT_THICK_DASHED,MARK_TYPE_DOUBLE_"
                                        "DASHED,MARK_TYPE_SINGLE_SOLID,MARK_TYPE_DOUBLE_SOLID,MARK_TYPE_LEFT_SOLID_"
                                        "RIGHT_DASHED,MARK_TYPE_LEFT_DASHED_RIGHT_SOLID,MARK_TYPE_VIRTUAL_MARKING";
    ASSERT_EQ(common_lane_content, content);
}

TEST(TestEnum, ToStringCommonMarkTypeOverflow)
{
    ::std::stringstream ss;
    int32_t             type_max = static_cast<int32_t>(::holo::map::CommonMarkType::MARK_TYPE_MAX);
    int32_t             type_min = static_cast<int32_t>(::holo::map::CommonMarkType::MARK_TYPE_NOT_INVESTIGATED);

    ss << static_cast<::holo::map::CommonMarkType>(type_max + 1);
    const ::std::string overflow = "???";
    ::std::string       content  = ss.str();

    ASSERT_EQ(overflow, content);

    ::std::stringstream ss_1;
    ss_1 << static_cast<::holo::map::CommonMarkType>(type_min - 1);
    content = ss_1.str();
    ASSERT_EQ(overflow, content);
}
TEST(TestEnum, ToStringCommonMarkMaterial)
{
    ::std::stringstream ss;

    int32_t type_max = static_cast<int32_t>(::holo::map::CommonMarkMaterial::MARK_MATERIAL_MAX);
    int32_t type_min = static_cast<int32_t>(::holo::map::CommonMarkMaterial::MARK_MATERIAL_NOT_APPLICABLE);
    for (int32_t i = type_min; i < type_max; i++)
    {
        ss << static_cast<::holo::map::CommonMarkMaterial>(i);
        if (i < type_max - 1)
        {
            ss << ",";
        }
    }
    ::std::string content = ss.str();
    ::std::string common_lane_content =
        "MARK_MATERIAL_NOT_APPLICABLE"
        ",MARK_MATERIAL_PAINTED,MARK_MATERIAL_RAISED_PAVEMENT_MARKER,MARK_MATERIAL_PAINTED_AND_RAISED_PAVEMENT_MARKER";
    ASSERT_EQ(common_lane_content, content);
}

TEST(TestEnum, ToStringCommonMarkMaterialOverflow)
{
    ::std::stringstream ss;

    int32_t type_max = static_cast<int32_t>(::holo::map::CommonMarkMaterial::MARK_MATERIAL_MAX);
    int32_t type_min = static_cast<int32_t>(::holo::map::CommonMarkMaterial::MARK_MATERIAL_NOT_APPLICABLE);

    ss << static_cast<::holo::map::CommonMarkMaterial>(type_max + 1);
    const ::std::string overflow = "???";
    ::std::string       content  = ss.str();

    ASSERT_EQ(overflow, content);

    ::std::stringstream ss_1;
    ss_1 << static_cast<::holo::map::CommonMarkMaterial>(type_min - 1);
    content = ss_1.str();
    ASSERT_EQ(overflow, content);
}

TEST(TestEnum, ToStringCommonRhombusDecelerationMarking)
{
    ::std::stringstream ss;

    int32_t type_max = static_cast<int32_t>(::holo::map::CommonRhombusDecelerationMarking::RHOMBUS_DECELERATION_MAX);
    int32_t type_min = static_cast<int32_t>(
        ::holo::map::CommonRhombusDecelerationMarking::RHOMBUS_DECELERATION_MARKING_NOT_APPLICABLE);
    for (int32_t i = type_min; i < type_max; i++)
    {
        ss << static_cast<::holo::map::CommonRhombusDecelerationMarking>(i);
        if (i < type_max - 1)
        {
            ss << ",";
        }
    }
    ::std::string content = ss.str();
    ::std::string common_lane_content =
        "RHOMBUS_DECELERATION_MARKING_NOT_APPLICABLE"
        ",RHOMBUS_DECELERATION_MARKING_RIGHT,RHOMBUS_DECELERATION_MARKING_LEFT,RHOMBUS_DECELERATION_MARKING_BOTH";
    ASSERT_EQ(common_lane_content, content);
}

TEST(TestEnum, ToStringCommonRhombusDecelerationMarkingOverflow)
{
    ::std::stringstream ss;

    int32_t type_max = static_cast<int32_t>(::holo::map::CommonRhombusDecelerationMarking::RHOMBUS_DECELERATION_MAX);
    int32_t type_min = static_cast<int32_t>(
        ::holo::map::CommonRhombusDecelerationMarking::RHOMBUS_DECELERATION_MARKING_NOT_APPLICABLE);

    ss << static_cast<::holo::map::CommonRhombusDecelerationMarking>(type_max + 1);
    const ::std::string overflow = "???";
    ::std::string       content  = ss.str();

    ASSERT_EQ(overflow, content);

    ::std::stringstream ss_1;
    ss_1 << static_cast<::holo::map::CommonRhombusDecelerationMarking>(type_min - 1);
    content = ss_1.str();
    ASSERT_EQ(overflow, content);
}

TEST(ObjectType, OperatorOutput)
{

    holo::map::ObjectType object = holo::map::ObjectType::TYPE_UNDEFINED;
    std::cout << object;

    holo::map::ObjectType object2 = holo::map::ObjectType::TYPE_UNKNOWN;
    std::cout << object2;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
