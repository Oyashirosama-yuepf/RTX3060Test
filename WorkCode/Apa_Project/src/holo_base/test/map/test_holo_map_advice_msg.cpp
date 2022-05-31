#include <holo/map/advice.h>
#include <iostream>

#include <gtest/gtest.h>

using Serializer      = holo::serialization::Serializer<false, 4>;
using Deserializer    = holo::serialization::Deserializer<false, 4>;

#define TEST_DATA_CROSSING_INFO_1 holo::map::CrossingInfo test_data_crossing_info_1;                \
    do {                                                                                            \
        test_data_crossing_info_1.crossing_type = holo::map::CrossingType::ENUM_MODEL_TYPE_MAX;     \
        test_data_crossing_info_1.distance      = 999.9;                                            \
    } while (false);

#define TEST_DATA_CROSSING_INFO_2 holo::map::CrossingInfo test_data_crossing_info_2;                \
    do {                                                                                            \
        test_data_crossing_info_2.crossing_type = holo::map::CrossingType::BRIDGE;                  \
        test_data_crossing_info_2.distance      = -999.99;                                          \
    } while (false);

#define TEST_DATA_CROSSING_INFO_3 holo::map::CrossingInfo test_data_crossing_info_3;                \
    do {                                                                                            \
        test_data_crossing_info_3.crossing_type = holo::map::CrossingType::DESTINATION;             \
        test_data_crossing_info_3.distance      = 0.0;                                              \
    } while (false);

#define TEST_DATA_CROSSING_INFO_GROUP_1 std::vector<holo::map::CrossingInfo> test_data_crossing_info_group_1;   \
    do {                                                                                                        \
        TEST_DATA_CROSSING_INFO_1;                                                                              \
        TEST_DATA_CROSSING_INFO_2;                                                                              \
        TEST_DATA_CROSSING_INFO_3;                                                                              \
        test_data_crossing_info_group_1 = {                                                                     \
            test_data_crossing_info_1,                                                                          \
            test_data_crossing_info_2,                                                                          \
            test_data_crossing_info_3                                                                           \
        };                                                                                                      \
    } while (false);

#define TEST_DATA_TARGET_LANE_ADVICE_1 holo::map::TargetLaneAdvice test_data_target_lane_advice_1;              \
    do {                                                                                                        \
        test_data_target_lane_advice_1.type_with_left    = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MAX; \
        test_data_target_lane_advice_1.type_with_right   = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MAX; \
        test_data_target_lane_advice_1.type_with_current = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MAX; \
        test_data_target_lane_advice_1.lane_type         = holo::map::CommonLaneType::LANE_TYPE_MAX;            \
        test_data_target_lane_advice_1.lane_id           = 1234567890987654321;                                 \
        test_data_target_lane_advice_1.valid             = true;                                                \
    } while (false);

#define TEST_DATA_TARGET_LANE_ADVICE_2 holo::map::TargetLaneAdvice test_data_target_lane_advice_2;                       \
    do {                                                                                                                 \
        test_data_target_lane_advice_2.type_with_left    = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_NO_ATTRIBUTE; \
        test_data_target_lane_advice_2.type_with_right   = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_NO_ATTRIBUTE; \
        test_data_target_lane_advice_2.type_with_current = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_NO_ATTRIBUTE; \
        test_data_target_lane_advice_2.lane_type         = holo::map::CommonLaneType::LANE_TYPE_UNDEFINED;               \
        test_data_target_lane_advice_2.lane_id           = 0;                                                            \
        test_data_target_lane_advice_2.valid             = true;                                                         \
    } while (false);

#define TEST_DATA_TARGET_LANE_ADVICE_3 holo::map::TargetLaneAdvice test_data_target_lane_advice_3;                         \
    do {                                                                                                                   \
        test_data_target_lane_advice_3.type_with_left    = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGED_BY_LEFT; \
        test_data_target_lane_advice_3.type_with_right   = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGED_BY_LEFT; \
        test_data_target_lane_advice_3.type_with_current = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGED_BY_LEFT; \
        test_data_target_lane_advice_3.lane_type         = holo::map::CommonLaneType::LANE_TYPE_SLOW;                      \
        test_data_target_lane_advice_3.lane_id           = 1234567890987654321;                                            \
        test_data_target_lane_advice_3.valid             = false;                                                          \
    } while (false);

#define TEST_DATA_TARGET_LANE_ADVICE_GROUP_1 holo::map::TargetLaneAdviceGroup test_data_target_lane_advice_group_1;         \
    do {                                                                                                                    \
        TEST_DATA_TARGET_LANE_ADVICE_1                                                                                      \
        TEST_DATA_TARGET_LANE_ADVICE_2                                                                                      \
        TEST_DATA_TARGET_LANE_ADVICE_3                                                                                      \
        test_data_target_lane_advice_group_1.left_lane_advice       = test_data_target_lane_advice_1;                       \
        test_data_target_lane_advice_group_1.right_lane_advice      = test_data_target_lane_advice_2;                       \
        test_data_target_lane_advice_group_1.current_lane_advice    = test_data_target_lane_advice_3;                       \
        test_data_target_lane_advice_group_1.link_type              = holo::map::CommonLinkType::LINK_TYPE_MAX;             \
        test_data_target_lane_advice_group_1.link_id                = 1234567890987654321;                                  \
        test_data_target_lane_advice_group_1.confidence             = 1.0;                                                  \
    } while (false);

#define TEST_DATA_TARGET_LINK_ADVICE_1 holo::map::TargetLinkAdvice test_data_target_link_advice_1;                  \
    do {                                                                                                            \
        test_data_target_link_advice_1.type                 = holo::map::CrossingType::ENUM_MODEL_TYPE_MAX;         \
        test_data_target_link_advice_1.link_id              = 1234567890987654321;                                  \
        test_data_target_link_advice_1.distance_to_start    = 123456789.123456;                                     \
        test_data_target_link_advice_1.distance_to_end      = 987654321.654321;                                     \
        test_data_target_link_advice_1.confidence           = 100.0;                                                \
    } while (false);

#define TEST_DATA_TARGET_LINK_ADVICE_2 holo::map::TargetLinkAdvice test_data_target_link_advice_2;                  \
    do {                                                                                                            \
        test_data_target_link_advice_2.type                 = holo::map::CrossingType::MOTORWAY_PASS_BY_ENTRANCE;   \
        test_data_target_link_advice_2.link_id              = 1234567890987654321;                                  \
        test_data_target_link_advice_2.distance_to_start    = 123456789.123456;                                     \
        test_data_target_link_advice_2.distance_to_end      = 987654321.654321;                                     \
        test_data_target_link_advice_2.confidence           = -100.0;                                               \
    } while (false);

#define TEST_DATA_TARGET_LINK_ADVICE_3 holo::map::TargetLinkAdvice test_data_target_link_advice_3;                  \
    do {                                                                                                            \
        test_data_target_link_advice_3.type                 = holo::map::CrossingType::DESTINATION;                 \
        test_data_target_link_advice_3.link_id              = 1234567890987654321;                                  \
        test_data_target_link_advice_3.distance_to_start    = 123456789.123456;                                     \
        test_data_target_link_advice_3.distance_to_end      = 987654321.654321;                                     \
        test_data_target_link_advice_3.confidence           = 100.0;                                                \
    } while (false);

#define TEST_DATA_TARGET_LINK_ADVICE_GROUP_1 holo::map::TargetLinkAdviceGroup test_data_target_link_advice_group_1; \
    do {                                                                                                            \
        TEST_DATA_TARGET_LINK_ADVICE_1;                                                                             \
        TEST_DATA_TARGET_LINK_ADVICE_2;                                                                             \
        TEST_DATA_TARGET_LINK_ADVICE_3;                                                                             \
        test_data_target_link_advice_group_1.advices = {                                                            \
            test_data_target_link_advice_1,                                                                         \
            test_data_target_link_advice_2,                                                                         \
            test_data_target_link_advice_3                                                                          \
        };                                                                                                          \
    } while (false);

TEST(OperatorEqual, TestCrossingInfo)
{
    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);
    
    TEST_DATA_CROSSING_INFO_1
    test_data_crossing_info_1.Serialize(serializer);

    EXPECT_EQ(test_data_crossing_info_1.GetSerializedSize(), serializer.GetSize());
}

TEST(TestGetSerializedSize, TestCrossingInfo)
{
    holo::map::CrossingInfo info1, info2;
    info1.crossing_type = holo::map::CrossingType::BRIDGE;
    EXPECT_NEAR(info1.distance, ::std::numeric_limits<::holo::float64_t>::max(), 0.000001);
   
    EXPECT_FALSE(info1 == info2);
}

TEST(TestSerialization, TestCrossingInfo)
{
    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);

    holo::map::CrossingInfo input;
    input.crossing_type = holo::map::CrossingType::BRIDGE;
    input.distance      = -99.9;
    input.Serialize(serializer);

    Deserializer deserializer(buffer, serializer.GetSize());
    holo::map::CrossingInfo output;
    output.Deserialize(deserializer);

    EXPECT_EQ(output.crossing_type, input.crossing_type);
    EXPECT_NEAR(output.distance, input.distance, 0.000001);
}

TEST(TestTargetLaneAdvice, TestFormatToString)
{
    const holo::map::TargetLaneAdvice target;
    const std::string str = holo::map::TargetLaneAdvice::FormatToString(target);

    const std::string criterion = "{\"valid\":0"
                                  ", \"lane_id\":0"
                                  ", \"lane_type\":0"
                                  ", \"lane_type_str\":\"LANE_TYPE_UNDEFINED\""
                                  ", \"type_with_left\":0"
                                  ", \"type_with_left_desc\":\"LANE_TRANS_TYPE_NO_ATTRIBUTE\""
                                  ", \"type_with_right\":0"
                                  ", \"type_with_right_desc\":\"LANE_TRANS_TYPE_NO_ATTRIBUTE\""
                                  ", \"type_with_current\":0"
                                  ", \"type_with_current_desc\":\"LANE_TRANS_TYPE_NO_ATTRIBUTE\""
                                  "}";

    EXPECT_EQ(str, criterion);
}

TEST(TestGetSerializedSize, TestTargetLaneAdvice)
{
    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);
    
    TEST_DATA_TARGET_LANE_ADVICE_1
    test_data_target_lane_advice_1.Serialize(serializer);

    EXPECT_EQ(test_data_target_lane_advice_1.GetSerializedSize(), serializer.GetSize());
}

TEST(TestSerialization, TestTargetLaneAdvice)
{
    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);

    holo::map::TargetLaneAdvice input;
    input.type_with_left    = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MAX;
    input.type_with_right   = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MAX;
    input.type_with_current = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MAX;
    input.lane_type         = holo::map::CommonLaneType::LANE_TYPE_MAX;
    input.lane_id           = 1234567890987654321;
    input.valid             = true;
    input.Serialize(serializer);

    Deserializer deserializer(buffer, serializer.GetSize());
    holo::map::TargetLaneAdvice output;
    output.Deserialize(deserializer);

    EXPECT_EQ(output.type_with_left, input.type_with_left);
    EXPECT_EQ(output.type_with_right, input.type_with_right);
    EXPECT_EQ(output.type_with_current, input.type_with_current);
    EXPECT_EQ(output.lane_type, input.lane_type);
    EXPECT_EQ(output.lane_id, input.lane_id);
    EXPECT_EQ(output.valid, input.valid);
}

TEST(TestTargetLaneAdviceGroup, TestFormatToString)
{
    const std::string sub_criterion = "{\"valid\":0"
                                  ", \"lane_id\":0"
                                  ", \"lane_type\":0"
                                  ", \"lane_type_str\":\"LANE_TYPE_UNDEFINED\""
                                  ", \"type_with_left\":0"
                                  ", \"type_with_left_desc\":\"LANE_TRANS_TYPE_NO_ATTRIBUTE\""
                                  ", \"type_with_right\":0"
                                  ", \"type_with_right_desc\":\"LANE_TRANS_TYPE_NO_ATTRIBUTE\""
                                  ", \"type_with_current\":0"
                                  ", \"type_with_current_desc\":\"LANE_TRANS_TYPE_NO_ATTRIBUTE\""
                                  "}";
    const std::string criterion = std::string("{\"link_id\":0") + std::string(", \"link_type\":0")
                                + std::string(", \"link_type_str\":\"") + std::string("LINK_TYPE_UNDEFINED") + "\""
                                + std::string(", \"left_lane_advice\":") + sub_criterion
                                + std::string(", \"right_lane_advice\":") + sub_criterion
                                + std::string(", \"current_lane_advice\":") + sub_criterion
                                + "}";

    const holo::map::TargetLaneAdviceGroup target;
    const std::string str = holo::map::TargetLaneAdviceGroup::FormatToString(target);
    EXPECT_EQ(str, criterion);
}

TEST(TestGetSerializedSize, TestTargetLaneAdviceGroup)
{
    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);
    
    TEST_DATA_TARGET_LANE_ADVICE_GROUP_1
    test_data_target_lane_advice_group_1.Serialize(serializer);

    EXPECT_EQ(test_data_target_lane_advice_group_1.GetSerializedSize(), serializer.GetSize());
}

TEST(TestSerialization, TestTargetLaneAdviceGroup)
{
    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);

    TEST_DATA_TARGET_LANE_ADVICE_GROUP_1;

    holo::map::TargetLaneAdviceGroup input = test_data_target_lane_advice_group_1;
    input.Serialize(serializer);

    Deserializer deserializer(buffer, serializer.GetSize());
    holo::map::TargetLaneAdviceGroup output;
    output.Deserialize(deserializer);

    EXPECT_EQ(output.left_lane_advice, input.left_lane_advice);
    EXPECT_EQ(output.right_lane_advice, input.right_lane_advice);
    EXPECT_EQ(output.current_lane_advice, input.current_lane_advice);
    EXPECT_EQ(output.link_type, input.link_type);
    EXPECT_EQ(output.link_id, input.link_id);
    EXPECT_NEAR(output.confidence, input.confidence, 0.000001);
}

TEST(TestTargetLinkAdvice, TestFormatToString)
{
    const std::string  criterion = "{\"type\":49"
                                   ", \"description\":\"NO_MODEL\""
                                   ", \"distance_to_start\":0"
                                   ", \"distance_to_end\":0"
                                   ", \"link_id\":0"
                                   "}";

    const holo::map::TargetLinkAdvice target;
    const std::string str = holo::map::TargetLinkAdvice::FormatToString(target);

    EXPECT_EQ(str, criterion);
}

TEST(TestGetSerializedSize, TestTargetLinkAdvice)
{
    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);
    
    TEST_DATA_TARGET_LINK_ADVICE_1
    test_data_target_link_advice_1.Serialize(serializer);

    EXPECT_EQ(test_data_target_link_advice_1.GetSerializedSize(), serializer.GetSize());
}

TEST(TestSerialization, TestTargetLinkAdvice)
{
    TEST_DATA_TARGET_LINK_ADVICE_1;

    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);

    holo::map::TargetLinkAdvice input = test_data_target_link_advice_1;
    input.Serialize(serializer);

    Deserializer deserializer(buffer, serializer.GetSize());
    holo::map::TargetLinkAdvice output;
    output.Deserialize(deserializer);

    EXPECT_EQ(output.type, input.type);
    EXPECT_EQ(output.link_id, input.link_id);
    EXPECT_NEAR(output.confidence, input.confidence, 0.000001);
    EXPECT_NEAR(output.distance_to_start, input.distance_to_start, 0.000001);
    EXPECT_NEAR(output.distance_to_end, input.distance_to_end, 0.000001);
}

TEST(TestTargetLinkAdviceGroup, TestFormatToString)
{
    const std::string  sub_criterion = "{\"type\":49"
                                       ", \"description\":\"NO_MODEL\""
                                       ", \"distance_to_start\":0"
                                       ", \"distance_to_end\":0"
                                       ", \"link_id\":0"
                                       "}";
    const std::string criterion = std::string("[") + sub_criterion + std::string("]");

    holo::map::TargetLinkAdviceGroup targets;
    targets.advices.emplace_back(holo::map::TargetLinkAdvice());

    const std::string str = holo::map::TargetLinkAdviceGroup::FormatToString(targets);

    EXPECT_EQ(str, criterion);
}

TEST(TestTargetLinkAdviceGroup, OperatorEqual)
{
    holo::map::TargetLinkAdvice old_link_advice_1;
    old_link_advice_1.type = holo::map::CrossingType::TOLL_ENTRANCE;
    old_link_advice_1.link_id = 987654;
    old_link_advice_1.confidence = 0.0;
    old_link_advice_1.distance_to_start = 3.141592;
    old_link_advice_1.distance_to_end = 3.141592;

    holo::map::TargetLinkAdvice old_link_advice_2;
    old_link_advice_2.type = holo::map::CrossingType::TOLL_STOP;
    old_link_advice_2.link_id = 987654;
    old_link_advice_2.confidence = 0.0;
    old_link_advice_2.distance_to_start = 3.141592;
    old_link_advice_2.distance_to_end = 3.141592;

    holo::map::TargetLinkAdvice old_link_advice_3;
    old_link_advice_3.type = holo::map::CrossingType::MOTORWAY_MIDDLE_EXPANDED;
    old_link_advice_3.link_id = 987654;
    old_link_advice_3.confidence = 0.0;
    old_link_advice_3.distance_to_start = 3.141592;
    old_link_advice_3.distance_to_end = 3.141592;

    holo::map::TargetLinkAdvice old_link_advice_4;
    old_link_advice_4.type = holo::map::CrossingType::RESTRICT_ROAD;
    old_link_advice_4.link_id = 987654;
    old_link_advice_4.confidence = 0.0;
    old_link_advice_4.distance_to_start = 3.141592;
    old_link_advice_4.distance_to_end = 3.141592;

    holo::map::TargetLinkAdvice old_link_advice_5;
    old_link_advice_5.type = holo::map::CrossingType::NO_MODEL;
    old_link_advice_5.link_id = 987654;
    old_link_advice_5.confidence = 0.0;
    old_link_advice_5.distance_to_start = 3.141592;
    old_link_advice_5.distance_to_end = 3.141592;

    holo::map::TargetLinkAdviceGroup link_advice_group;
    link_advice_group.advices = std::vector<holo::map::TargetLinkAdvice>{old_link_advice_1,
                                                                             old_link_advice_2,
                                                                             old_link_advice_3,
                                                                             old_link_advice_4,
                                                                             old_link_advice_5};

    holo::map::TargetLinkAdviceGroup link_advice_group2;
    link_advice_group2.advices = std::vector<holo::map::TargetLinkAdvice>{old_link_advice_1,
                                                                             old_link_advice_2,
                                                                             old_link_advice_3};

    holo::map::TargetLinkAdviceGroup link_advice_group3;
    link_advice_group3.advices = std::vector<holo::map::TargetLinkAdvice>{old_link_advice_3,
                                                                             old_link_advice_3,
                                                                             old_link_advice_3,
                                                                             old_link_advice_5,
                                                                             old_link_advice_4};

    EXPECT_FALSE(link_advice_group == link_advice_group2);
    EXPECT_FALSE(link_advice_group == link_advice_group3);

}


TEST(TestGetSerializedSize, TestTargetLinkAdviceGroup)
{
    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);
    
    TEST_DATA_TARGET_LINK_ADVICE_GROUP_1
    test_data_target_link_advice_group_1.Serialize(serializer);

    EXPECT_EQ(test_data_target_link_advice_group_1.GetSerializedSize(), serializer.GetSize());
}

TEST(TestSerialization, TestTargetLinkAdviceGroup)
{
    TEST_DATA_TARGET_LINK_ADVICE_GROUP_1;

    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);

    holo::map::TargetLinkAdviceGroup input = test_data_target_link_advice_group_1;
    input.Serialize(serializer);

    Deserializer deserializer(buffer, serializer.GetSize());
    holo::map::TargetLinkAdviceGroup output;
    output.Deserialize(deserializer);

    EXPECT_EQ(output.advices, input.advices);
}

TEST(TestAdvice, Test_MapMsgBase_Valid)
{
    ::holo::map::Advice adv;
    ASSERT_TRUE(adv.IsValid());

    auto indicator_size = adv.GetValidIndicatorSize();
    adv.SetValidIndicatorSize(100);
    ASSERT_FALSE(adv.IsValid());
    adv.SetValidIndicatorSize(indicator_size);
    ASSERT_TRUE(adv.IsValid());

    auto uint32_size = adv.GetValidUint32Size();
    adv.SetValidUint32Size(100);
    ASSERT_FALSE(adv.IsValid());
    adv.SetValidUint32Size(uint32_size);
    ASSERT_TRUE(adv.IsValid());

    auto float32_size = adv.GetValidFloat32Size();
    adv.SetValidFloat32Size(100);
    ASSERT_FALSE(adv.IsValid());
    adv.SetValidFloat32Size(float32_size);
    ASSERT_TRUE(adv.IsValid());
}

TEST(TestAdvice, Test_Convert_Uint)
{
    // ::holo::map::Advice adv;
    // now we have not any uint32 member variables.
    ASSERT_TRUE(true);

}

TEST(TestAdvice, Test_Convert_Float)
{
    ::holo::map::Advice adv;
    ::std::vector<::holo::float32_t> float32_values;
    // set current lane width
    float32_values.push_back(3.75);
    // set distance to speed limit change
    float32_values.push_back(100.33);
    // set remaining distance to crossing
    float32_values.push_back(200.11);
    // set current speed limit
    float32_values.push_back(33.33);
    // set target speed ahead
    float32_values.push_back(20.22);

    ::std::vector<::holo::float32_t> float32_values_rvalue = float32_values;
    adv.SetValuesFloat32(float32_values);

    auto& float32_values_getter = adv.GetValuesFloat32();
    for(::std::size_t i = 0; i < float32_values.size(); i++)
    {
        ASSERT_NEAR(float32_values.at(i), float32_values_getter.at(i), 0.01);
    }

    adv.SetValuesFloat32(::std::move(float32_values_rvalue));
    auto& float32_values_rvalue_getter = adv.GetValuesFloat32();
    for(::std::size_t i = 0; i < float32_values.size(); i++)
    {
        ASSERT_NEAR(float32_values.at(i), float32_values_rvalue_getter.at(i), 0.01);
    }

}

TEST(TestAdvice, Test_Convert_Indicators_By_value)
{
    ::holo::map::Advice adv;
    ::holo::uint32_t value = 0;
    adv.SetIndicatorsByValue(value);
    ASSERT_FALSE(adv.IsOnRoute());
    ASSERT_FALSE(adv.IsOnBifurcation());

    // value -> "111"
    value = 7;
    adv.SetIndicatorsByValue(value);
    ASSERT_TRUE(adv.IsOnRoute());
    ASSERT_TRUE(adv.IsOnBifurcation());

    ASSERT_EQ(value, adv.GetIndicatorsByValue());
}

TEST(TestAdvice, Test_Convert_Indicators)
{
    ::holo::map::Advice adv;
    const ::std::bitset<::holo::map::MapMsgBase::kHoloMapBitset_32> bit("101");
    adv.SetIndicators(bit);

    ASSERT_TRUE(adv.IsOnRoute());
    ASSERT_TRUE(adv.IsOnBifurcation());

}

TEST(TestAdvice, Test_PTR)
{
    ::holo::map::Advice::PtrAdvice adv = ::std::make_shared<::holo::map::Advice>();
    ASSERT_TRUE(::std::fabs(adv->GetDistanceToNextCrossing() < 0.0001f));
    adv->SetDistanceToNextCrossing(120.12);
    ASSERT_NEAR(adv->GetDistanceToNextCrossing(), 120.12, 0.1);
}

TEST(TestAdvice, Test_DistanceToNextCrossing)
{
    ::holo::map::Advice adv;
    ASSERT_TRUE(::std::fabs(adv.GetDistanceToNextCrossing() < 0.0001f));
    adv.SetDistanceToNextCrossing(120.12);
    ASSERT_NEAR(adv.GetDistanceToNextCrossing(), 120.12, 0.1);
}

TEST(TestAdvice, Test_SequenceOfNextCrossing)
{
    ::holo::map::Advice adv;
    ASSERT_TRUE(adv.GetSequenceOfNextCrossing().empty());

    ::std::vector<::holo::int8_t> seq = {-1, 0, 1};
    adv.SetSequenceOfNextCrossing(seq);
    ASSERT_TRUE(seq.size() == 3);
    ASSERT_TRUE(adv.GetSequenceOfNextCrossing().size() == 3);
    for (::std::size_t i = 0; i < 3; i++)
    {
        ASSERT_EQ(seq.at(i), adv.GetSequenceOfNextCrossing().at(i));
    }

    // SetSequenceOfNextCrossing rvalue
    adv.GetSequenceOfNextCrossing().clear();
    ASSERT_TRUE(adv.GetSequenceOfNextCrossing().empty());
    adv.SetSequenceOfNextCrossing(::std::move(seq));
    ASSERT_TRUE(seq.empty());
    ASSERT_EQ(adv.GetSequenceOfNextCrossing().size(), 3);
}

TEST(TestAdvice, Test_LaneSequence)
{
    ::holo::map::Advice adv;
    ASSERT_TRUE(adv.GetCurrentLaneSequence().empty());

    ::std::vector<::holo::int8_t> seq = {-1, 0, 1};
    adv.SetCurrentLaneSequence(seq);
    ASSERT_TRUE(seq.size() == 3);
    ASSERT_TRUE(adv.GetCurrentLaneSequence().size() == 3);
    for (::std::size_t i = 0; i < 3; i++)
    {
        ASSERT_EQ(seq.at(i), adv.GetCurrentLaneSequence().at(i));
    }

    // SetCurrentLaneSequence rvalue
    adv.GetCurrentLaneSequence().clear();
    ASSERT_TRUE(adv.GetCurrentLaneSequence().empty());
    adv.SetCurrentLaneSequence(::std::move(seq));
    ASSERT_TRUE(seq.empty());
    ASSERT_EQ(adv.GetCurrentLaneSequence().size(), 3);
}

TEST(TestAdvice, Test_CrossingInfo)
{
    ::holo::map::Advice       adv;
    ::holo::map::CrossingInfo ci1, ci2, ci3;
    ci1.crossing_type = ::holo::map::CrossingType::DECELERATION_LANE;
    ci1.distance      = 10.0;

    ci2.crossing_type = ::holo::map::CrossingType::JCT;
    ci2.distance      = 20.0;

    ci3.crossing_type = ::holo::map::CrossingType::JCT_BOTH_SIDE_EXPANDED;
    ci3.distance      = 14.0;

    adv.AddCrossingInfo(ci1);
    adv.AddCrossingInfo(ci2);
    adv.AddCrossingInfo(ci3);

    ASSERT_NEAR(adv.GetCrossingInfoList().at(0).distance, 10.0, 0.01);
    ASSERT_EQ(adv.GetCrossingInfoList().at(0).crossing_type, ::holo::map::CrossingType::DECELERATION_LANE);

    ASSERT_NEAR(adv.GetCrossingInfoList().at(1).distance, 14.0, 0.01);
    ASSERT_EQ(adv.GetCrossingInfoList().at(1).crossing_type, ::holo::map::CrossingType::JCT_BOTH_SIDE_EXPANDED);

    ASSERT_NEAR(adv.GetCrossingInfoList().at(2).distance, 20.0, 0.01);
    ASSERT_EQ(adv.GetCrossingInfoList().at(2).crossing_type, ::holo::map::CrossingType::JCT);
}

TEST(TestAdvice, Test_IsOnBifurcation)
{
    ::holo::map::Advice adv;
    ASSERT_FALSE(adv.IsOnBifurcation());
    adv.SetIsOnBifurcation(true);
    ASSERT_TRUE(adv.IsOnBifurcation());
}
TEST(TestAdvice, Test_IsOnRoute)
{
    ::holo::map::Advice adv;
    ASSERT_FALSE(adv.IsOnRoute());
    adv.SetIsOnRoute(true);
    ASSERT_TRUE(adv.IsOnRoute());
}

TEST(TestAdvice, Test_IsOnHDMap)
{
    ::holo::map::Advice adv;
    ASSERT_FALSE(adv.IsOnHDMap());
    adv.SetIsOnHDMap(true);
    ASSERT_TRUE(adv.IsOnHDMap());
}

TEST(TestAdvice, Test_Clear)
{
    ::holo::map::Advice adv;

    ::holo::map::CrossingInfo ci1, ci2, ci3;
    ci1.crossing_type = ::holo::map::CrossingType::DECELERATION_LANE;
    ci1.distance      = 10.0;
    adv.AddCrossingInfo(ci1);

    ::std::vector<::holo::geometry::Point3d> points = {{1, 1, 1}, {2, 2, 2}};
    ::std::vector<::holo::int8_t> seq = {1, 2, 3};
    adv.SetCurrentLaneSequence(seq);
    adv.SetSequenceOfNextCrossing(::std::move(seq));
    adv.SetDistanceToNextCrossing(111.0);
    adv.SetIsOnRoute(true);
    adv.SetIsOnBifurcation(true);
    adv.SetIsOnHDMap(true);

    adv.Clear();
    const holo::common::Timestamp& timestamp = adv.GetTimestamp();
    ASSERT_TRUE(timestamp.IsZero());
    ASSERT_TRUE(::std::fabs(adv.GetDistanceToNextCrossing()) < 0.0001f);
    ASSERT_TRUE(adv.GetSequenceOfNextCrossing().empty());
    const ::std::vector<::holo::int8_t>& lane_seq = adv.GetCurrentLaneSequence();
    ASSERT_TRUE(lane_seq.empty());
    ASSERT_TRUE(true);
    const ::std::vector<::holo::map::CrossingInfo>& crossing_list = adv.GetCrossingInfoList();
    ASSERT_TRUE(crossing_list.empty());
    bool is_on_route = adv.IsOnRoute();
    ASSERT_FALSE(is_on_route);
    bool is_on_bifurcation = adv.IsOnBifurcation();
    ASSERT_FALSE(is_on_bifurcation);
    const bool is_on_hdmap = adv.IsOnHDMap();
    ASSERT_FALSE(is_on_hdmap);
}

TEST(TestAdvice, Test_SetGet)
{
    ::holo::map::Advice adv;

    ::holo::map::CrossingInfo ci1, ci2, ci3;
    ci1.crossing_type = ::holo::map::CrossingType::DECELERATION_LANE;
    ci1.distance      = 10.0;

    ci2.crossing_type = ::holo::map::CrossingType::JCT;
    ci2.distance      = 20.0;

    ci3.crossing_type = ::holo::map::CrossingType::JCT_BOTH_SIDE_EXPANDED;
    ci3.distance      = 14.0;

    adv.AddCrossingInfo(ci1);
    adv.AddCrossingInfo(ci2);
    adv.AddCrossingInfo(ci3);

    ASSERT_NEAR(static_cast<const ::std::vector<::holo::map::CrossingInfo>&>(adv.GetCrossingInfoList()).at(0).distance,
                10.0, 0.01);
    ASSERT_NEAR(adv.GetCrossingInfoList().at(1).distance, 14.0, 0.01);
    ASSERT_NEAR(adv.GetCrossingInfoList().at(2).distance, 20.0, 0.01);


    ::std::vector<::holo::int8_t> seq = {1, 2, 3};
    adv.SetCurrentLaneSequence(seq);
    adv.SetSequenceOfNextCrossing(::std::move(seq));
    ASSERT_TRUE(seq.empty());
    ASSERT_TRUE(adv.GetSequenceOfNextCrossing().size() == 3);
    adv.SetDistanceToNextCrossing(111.0);
    ASSERT_NEAR(adv.GetDistanceToNextCrossing(), 111.0, 0.01);
    adv.SetIsOnRoute(true);
    ASSERT_TRUE(adv.IsOnRoute());
    adv.SetIsOnHDMap(true);
    ASSERT_TRUE(adv.IsOnHDMap());

}

TEST(TestAdvice, Test_RValueAssignment)
{
    ::holo::map::Advice adv;

    ::std::vector<::holo::int8_t> seq_next_crossing(4, 3);
    ::holo::int64_t               address_next_crossing = (::holo::int64_t)(&(seq_next_crossing[0]));
    adv.SetSequenceOfNextCrossing(::std::move(seq_next_crossing));
    ASSERT_EQ(address_next_crossing, (::holo::int64_t)(&(adv.GetSequenceOfNextCrossing()[0])));

    ::holo::map::Advice other;
    other = ::std::move(adv);
    ASSERT_EQ(address_next_crossing, (::holo::int64_t)(&(other.GetSequenceOfNextCrossing()[0])));
}

TEST(TestAdvice, Test_RValueCopyConstructor)
{
    ::holo::map::Advice adv;

    ::std::vector<::holo::int8_t> seq_next_crossing(4, 3);
    ::holo::int64_t               address_next_crossing = (::holo::int64_t)(&(seq_next_crossing[0]));
    adv.SetSequenceOfNextCrossing(::std::move(seq_next_crossing));
    ASSERT_EQ(address_next_crossing, (::holo::int64_t)(&(adv.GetSequenceOfNextCrossing()[0])));

    ::std::vector<::holo::int8_t> lane_seq(4, 3);
    ::holo::int64_t               address_lane_seq = (::holo::int64_t)(&(lane_seq[0]));
    adv.SetCurrentLaneSequence(::std::move(lane_seq));
    ASSERT_EQ(address_lane_seq, (::holo::int64_t)(&(adv.GetCurrentLaneSequence()[0])));

    ::std::vector<::holo::map::CrossingInfo> crossing_list;
    for (int i = 0; i < 4; i++)
    {
        ::holo::map::CrossingInfo cr;
        cr.crossing_type = ::holo::map::CrossingType::JCT;
        cr.distance      = 100.0;
        crossing_list.push_back(cr);
    }

    ::std::vector<::holo::geometry::Point3d> point_list    = {::holo::geometry::Point3d(1, 2, 3), ::holo::geometry::Point3d(2, 3, 4),
                                                 ::holo::geometry::Point3d(3, 4, 5)};

    ::holo::map::Advice other(::std::move(adv));
    ASSERT_EQ(address_next_crossing, (::holo::int64_t)(&(other.GetSequenceOfNextCrossing()[0])));

    ASSERT_EQ(address_lane_seq, (::holo::int64_t)(&(other.GetCurrentLaneSequence()[0])));

}

TEST(TestAdvice, Test_Initialization)
{
    ::holo::map::Advice adv;

    const holo::common::Timestamp& timestamp = adv.GetTimestamp();
    ASSERT_TRUE(timestamp.IsZero());
    ASSERT_TRUE(true);

    const ::holo::float64_t dis_to_next_crossing = adv.GetDistanceToNextCrossing();
    ASSERT_TRUE(::std::fabs(dis_to_next_crossing) < 0.0001f);

    const ::std::vector<::holo::int8_t>& seq_to_next_crossing = adv.GetSequenceOfNextCrossing();
    ASSERT_TRUE(seq_to_next_crossing.empty());

    const ::std::vector<::holo::int8_t>& lane_seq = adv.GetCurrentLaneSequence();
    ASSERT_TRUE(lane_seq.empty());

    const ::std::vector<::holo::map::CrossingInfo>& crossing_list = adv.GetCrossingInfoList();
    ASSERT_TRUE(crossing_list.empty());

    bool is_on_route = adv.IsOnRoute();
    ASSERT_FALSE(is_on_route);

    bool is_on_bifurcation = adv.IsOnBifurcation();
    ASSERT_FALSE(is_on_bifurcation);

    const bool is_on_hdmap = adv.IsOnHDMap();
    ASSERT_FALSE(is_on_hdmap);

}

TEST(TestAdvice, TestGetSetLaneAdviceWithCopy)
{
    holo::map::TargetLaneAdviceType old_left_advice;
    old_left_advice.valid = true;
    old_left_advice.lane_id = 911;
    old_left_advice.lane_type = holo::map::CommonLaneType::LANE_TYPE_REGULAR;
    old_left_advice.type_with_left = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_NO_ATTRIBUTE;
    old_left_advice.type_with_right = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGE_TO_LEFT_FORBIDDEN;
    old_left_advice.type_with_current = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGE_TO_RIGHT_FORBIDDEN;

    holo::map::TargetLaneAdviceType old_right_advice;
    old_right_advice.valid = true;
    old_right_advice.lane_id = 119;
    old_right_advice.lane_type = holo::map::CommonLaneType::LANE_TYPE_ACCELERATION;
    old_right_advice.type_with_left = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGE_TO_LEFT_OPTIONAL;
    old_right_advice.type_with_right = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGE_TO_LEFT_FORCED;
    old_right_advice.type_with_current = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGE_TO_RIGHT_OPTIONAL;

    holo::map::TargetLaneAdviceType old_current_advice;
    old_current_advice.valid = true;
    old_current_advice.lane_id = 191;
    old_current_advice.lane_type = holo::map::CommonLaneType::LANE_TYPE_DECELERATION;
    old_current_advice.type_with_left = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGE_TO_RIGHT_FORCED;
    old_current_advice.type_with_right = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGED_BY_LEFT;
    old_current_advice.type_with_current = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGED_BY_RIGHT;

    holo::map::TargetLaneAdviceGroup old_advice;
    old_advice.link_id = 999;
    old_advice.link_type = holo::map::CommonLinkType::LINK_TYPE_MOTORWAY;
    old_advice.confidence = 0.0;
    old_advice.left_lane_advice = old_left_advice;
    old_advice.right_lane_advice = old_right_advice;
    old_advice.current_lane_advice = old_current_advice;

    holo::map::Advice advice;
    advice.SetTargetLaneAdviceGroup(old_advice);

    const holo::map::TargetLaneAdviceGroup& new_advice = advice.GetTargetLaneAdviceGroup();

    EXPECT_EQ(new_advice.link_id, old_advice.link_id);
    EXPECT_EQ(new_advice.link_type, old_advice.link_type);
    EXPECT_FLOAT_EQ(new_advice.confidence, old_advice.confidence);

    EXPECT_EQ(new_advice.left_lane_advice.valid, old_left_advice.valid);
    EXPECT_EQ(new_advice.left_lane_advice.lane_id, old_left_advice.lane_id);
    EXPECT_EQ(new_advice.left_lane_advice.lane_type, old_left_advice.lane_type);
    EXPECT_EQ(new_advice.left_lane_advice.type_with_left, old_left_advice.type_with_left);
    EXPECT_EQ(new_advice.left_lane_advice.type_with_right, old_left_advice.type_with_right);
    EXPECT_EQ(new_advice.left_lane_advice.type_with_current, old_left_advice.type_with_current);

    EXPECT_EQ(new_advice.right_lane_advice.valid, old_right_advice.valid);
    EXPECT_EQ(new_advice.right_lane_advice.lane_id, old_right_advice.lane_id);
    EXPECT_EQ(new_advice.right_lane_advice.lane_type, old_right_advice.lane_type);
    EXPECT_EQ(new_advice.right_lane_advice.type_with_left, old_right_advice.type_with_left);
    EXPECT_EQ(new_advice.right_lane_advice.type_with_right, old_right_advice.type_with_right);
    EXPECT_EQ(new_advice.right_lane_advice.type_with_current, old_right_advice.type_with_current);

    EXPECT_EQ(new_advice.current_lane_advice.valid, old_current_advice.valid);
    EXPECT_EQ(new_advice.current_lane_advice.lane_id, old_current_advice.lane_id);
    EXPECT_EQ(new_advice.current_lane_advice.lane_type, old_current_advice.lane_type);
    EXPECT_EQ(new_advice.current_lane_advice.type_with_left, old_current_advice.type_with_left);
    EXPECT_EQ(new_advice.current_lane_advice.type_with_right, old_current_advice.type_with_right);
    EXPECT_EQ(new_advice.current_lane_advice.type_with_current, old_current_advice.type_with_current);
}

TEST(TestAdvice, TestGetSetLaneAdviceWithMove)
{
    holo::map::TargetLaneAdviceType old_left_advice;
    old_left_advice.valid = true;
    old_left_advice.lane_id = 911;
    old_left_advice.lane_type = holo::map::CommonLaneType::LANE_TYPE_REGULAR;
    old_left_advice.type_with_left = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_NO_ATTRIBUTE;
    old_left_advice.type_with_right = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGE_TO_LEFT_FORBIDDEN;
    old_left_advice.type_with_current = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGE_TO_RIGHT_FORBIDDEN;

    holo::map::TargetLaneAdviceType old_right_advice;
    old_right_advice.valid = true;
    old_right_advice.lane_id = 119;
    old_right_advice.lane_type = holo::map::CommonLaneType::LANE_TYPE_ACCELERATION;
    old_right_advice.type_with_left = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGE_TO_LEFT_OPTIONAL;
    old_right_advice.type_with_right = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGE_TO_LEFT_FORCED;
    old_right_advice.type_with_current = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGE_TO_RIGHT_OPTIONAL;

    holo::map::TargetLaneAdviceType old_current_advice;
    old_current_advice.valid = true;
    old_current_advice.lane_id = 191;
    old_current_advice.lane_type = holo::map::CommonLaneType::LANE_TYPE_DECELERATION;
    old_current_advice.type_with_left = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGE_TO_RIGHT_FORCED;
    old_current_advice.type_with_right = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGED_BY_LEFT;
    old_current_advice.type_with_current = holo::map::CommonLaneTransType::LANE_TRANS_TYPE_MERGED_BY_RIGHT;

    holo::map::TargetLaneAdviceGroup old_advice;
    old_advice.link_id = 999;
    old_advice.link_type = holo::map::CommonLinkType::LINK_TYPE_MOTORWAY;
    old_advice.confidence = 0.0;
    old_advice.left_lane_advice = old_left_advice;
    old_advice.right_lane_advice = old_right_advice;
    old_advice.current_lane_advice = old_current_advice;

    holo::map::Advice advice;
    holo::map::TargetLaneAdviceGroup another_advice = old_advice;
    advice.SetTargetLaneAdviceGroup(std::move(another_advice));

    const holo::map::TargetLaneAdviceGroup& new_advice = advice.GetTargetLaneAdviceGroup();

    EXPECT_EQ(new_advice.link_id, old_advice.link_id);
    EXPECT_EQ(new_advice.link_type, old_advice.link_type);
    EXPECT_FLOAT_EQ(new_advice.confidence, old_advice.confidence);

    EXPECT_EQ(new_advice.left_lane_advice.valid, old_left_advice.valid);
    EXPECT_EQ(new_advice.left_lane_advice.lane_id, old_left_advice.lane_id);
    EXPECT_EQ(new_advice.left_lane_advice.lane_type, old_left_advice.lane_type);
    EXPECT_EQ(new_advice.left_lane_advice.type_with_left, old_left_advice.type_with_left);
    EXPECT_EQ(new_advice.left_lane_advice.type_with_right, old_left_advice.type_with_right);
    EXPECT_EQ(new_advice.left_lane_advice.type_with_current, old_left_advice.type_with_current);

    EXPECT_EQ(new_advice.right_lane_advice.valid, old_right_advice.valid);
    EXPECT_EQ(new_advice.right_lane_advice.lane_id, old_right_advice.lane_id);
    EXPECT_EQ(new_advice.right_lane_advice.lane_type, old_right_advice.lane_type);
    EXPECT_EQ(new_advice.right_lane_advice.type_with_left, old_right_advice.type_with_left);
    EXPECT_EQ(new_advice.right_lane_advice.type_with_right, old_right_advice.type_with_right);
    EXPECT_EQ(new_advice.right_lane_advice.type_with_current, old_right_advice.type_with_current);

    EXPECT_EQ(new_advice.current_lane_advice.valid, old_current_advice.valid);
    EXPECT_EQ(new_advice.current_lane_advice.lane_id, old_current_advice.lane_id);
    EXPECT_EQ(new_advice.current_lane_advice.lane_type, old_current_advice.lane_type);
    EXPECT_EQ(new_advice.current_lane_advice.type_with_left, old_current_advice.type_with_left);
    EXPECT_EQ(new_advice.current_lane_advice.type_with_right, old_current_advice.type_with_right);
    EXPECT_EQ(new_advice.current_lane_advice.type_with_current, old_current_advice.type_with_current);
}

TEST(TestAdvice, TestGetSetLinkAdviceWithCopy)
{
    holo::map::TargetLinkAdvice old_link_advice_1;
    old_link_advice_1.type = holo::map::CrossingType::TOLL_ENTRANCE;
    old_link_advice_1.link_id = 987654;
    old_link_advice_1.confidence = 0.0;
    old_link_advice_1.distance_to_start = 3.141592;
    old_link_advice_1.distance_to_end = 3.141592;

    holo::map::TargetLinkAdvice old_link_advice_2;
    old_link_advice_2.type = holo::map::CrossingType::TOLL_STOP;
    old_link_advice_2.link_id = 987654;
    old_link_advice_2.confidence = 0.0;
    old_link_advice_2.distance_to_start = 3.141592;
    old_link_advice_2.distance_to_end = 3.141592;

    holo::map::TargetLinkAdvice old_link_advice_3;
    old_link_advice_3.type = holo::map::CrossingType::MOTORWAY_MIDDLE_EXPANDED;
    old_link_advice_3.link_id = 987654;
    old_link_advice_3.confidence = 0.0;
    old_link_advice_3.distance_to_start = 3.141592;
    old_link_advice_3.distance_to_end = 3.141592;

    holo::map::TargetLinkAdvice old_link_advice_4;
    old_link_advice_4.type = holo::map::CrossingType::RESTRICT_ROAD;
    old_link_advice_4.link_id = 987654;
    old_link_advice_4.confidence = 0.0;
    old_link_advice_4.distance_to_start = 3.141592;
    old_link_advice_4.distance_to_end = 3.141592;

    holo::map::TargetLinkAdvice old_link_advice_5;
    old_link_advice_5.type = holo::map::CrossingType::NO_MODEL;
    old_link_advice_5.link_id = 987654;
    old_link_advice_5.confidence = 0.0;
    old_link_advice_5.distance_to_start = 3.141592;
    old_link_advice_5.distance_to_end = 3.141592;

    holo::map::TargetLinkAdviceGroup old_link_advice_group;
    old_link_advice_group.advices = std::vector<holo::map::TargetLinkAdvice>{old_link_advice_1,
                                                                             old_link_advice_2,
                                                                             old_link_advice_3,
                                                                             old_link_advice_4,
                                                                             old_link_advice_5};

    holo::map::Advice advice;
    advice.SetTargetLinkAdviceGroup(old_link_advice_group);
    const holo::map::TargetLinkAdviceGroup& new_link_advice_group = advice.GetTargetLinkAdviceGroup();

    ASSERT_EQ(old_link_advice_group.advices.size(), new_link_advice_group.advices.size());

    const std::size_t count = new_link_advice_group.advices.size();
    for (std::size_t i = 0; i < count; ++i)
    {
        EXPECT_EQ(new_link_advice_group.advices[i].type, old_link_advice_group.advices[i].type);
        EXPECT_EQ(new_link_advice_group.advices[i].link_id, old_link_advice_group.advices[i].link_id);
        EXPECT_EQ(new_link_advice_group.advices[i].confidence, old_link_advice_group.advices[i].confidence);
        EXPECT_EQ(new_link_advice_group.advices[i].distance_to_start, old_link_advice_group.advices[i].distance_to_start);
        EXPECT_EQ(new_link_advice_group.advices[i].distance_to_end, old_link_advice_group.advices[i].distance_to_end);
    }
}

TEST(TestAdvice, TestGetSetLinkAdviceWithMove)
{
    holo::map::TargetLinkAdvice old_link_advice_1;
    old_link_advice_1.type = holo::map::CrossingType::TOLL_ENTRANCE;
    old_link_advice_1.link_id = 987654;
    old_link_advice_1.confidence = 0.0;
    old_link_advice_1.distance_to_start = 3.141592;
    old_link_advice_1.distance_to_end = 3.141592;

    holo::map::TargetLinkAdvice old_link_advice_2;
    old_link_advice_2.type = holo::map::CrossingType::TOLL_STOP;
    old_link_advice_2.link_id = 987654;
    old_link_advice_2.confidence = 0.0;
    old_link_advice_2.distance_to_start = 3.141592;
    old_link_advice_2.distance_to_end = 3.141592;

    holo::map::TargetLinkAdvice old_link_advice_3;
    old_link_advice_3.type = holo::map::CrossingType::MOTORWAY_MIDDLE_EXPANDED;
    old_link_advice_3.link_id = 987654;
    old_link_advice_3.confidence = 0.0;
    old_link_advice_3.distance_to_start = 3.141592;
    old_link_advice_3.distance_to_end = 3.141592;

    holo::map::TargetLinkAdvice old_link_advice_4;
    old_link_advice_4.type = holo::map::CrossingType::RESTRICT_ROAD;
    old_link_advice_4.link_id = 987654;
    old_link_advice_4.confidence = 0.0;
    old_link_advice_4.distance_to_start = 3.141592;
    old_link_advice_4.distance_to_end = 3.141592;

    holo::map::TargetLinkAdvice old_link_advice_5;
    old_link_advice_5.type = holo::map::CrossingType::NO_MODEL;
    old_link_advice_5.link_id = 987654;
    old_link_advice_5.confidence = 0.0;
    old_link_advice_5.distance_to_start = 3.141592;
    old_link_advice_5.distance_to_end = 3.141592;

    holo::map::TargetLinkAdviceGroup old_link_advice_group;
    old_link_advice_group.advices = std::vector<holo::map::TargetLinkAdvice>{old_link_advice_1,
                                                                             old_link_advice_2,
                                                                             old_link_advice_3,
                                                                             old_link_advice_4,
                                                                             old_link_advice_5};

    holo::map::TargetLinkAdviceGroup another_link_advice_group;
    another_link_advice_group.advices = old_link_advice_group.advices;

    holo::map::Advice advice;
    advice.SetTargetLinkAdviceGroup(std::move(another_link_advice_group));

    const holo::map::TargetLinkAdviceGroup& new_link_advice_group = advice.GetTargetLinkAdviceGroup();

    EXPECT_TRUE(another_link_advice_group.advices.empty());
    ASSERT_EQ(old_link_advice_group.advices.size(), new_link_advice_group.advices.size());

    const std::size_t count = new_link_advice_group.advices.size();
    for (std::size_t i = 0; i < count; ++i)
    {
        EXPECT_EQ(new_link_advice_group.advices[i].type, old_link_advice_group.advices[i].type);
        EXPECT_EQ(new_link_advice_group.advices[i].link_id, old_link_advice_group.advices[i].link_id);
        EXPECT_EQ(new_link_advice_group.advices[i].confidence, old_link_advice_group.advices[i].confidence);
        EXPECT_EQ(new_link_advice_group.advices[i].distance_to_start, old_link_advice_group.advices[i].distance_to_start);
        EXPECT_EQ(new_link_advice_group.advices[i].distance_to_end, old_link_advice_group.advices[i].distance_to_end);
    }
}


TEST(TestSerialization, TestAdvice)
{
    TEST_DATA_CROSSING_INFO_GROUP_1;
    TEST_DATA_TARGET_LANE_ADVICE_GROUP_1;
    TEST_DATA_TARGET_LINK_ADVICE_GROUP_1;

    std::vector<holo::geometry::Point3d> const points = {holo::geometry::Point3d{0,                0,                0},
                                               holo::geometry::Point3d{0.1,              0.2,              0.3},
                                               holo::geometry::Point3d{123456789.123456, 987654321.654321, 0.987654}};
    std::vector<holo::map::SeqValue> const seq1 = {1, 2, 3};
    std::vector<holo::map::SeqValue> const seq2 = {-1, -2, -3};

    ::holo::map::CrossingInfo ci1, ci2, ci3;
    ci1.crossing_type = ::holo::map::CrossingType::DECELERATION_LANE;
    ci1.distance      = 10.0;

    ci2.crossing_type = ::holo::map::CrossingType::JCT;
    ci2.distance      = 20.0;

    ci3.crossing_type = ::holo::map::CrossingType::JCT_BOTH_SIDE_EXPANDED;
    ci3.distance      = 14.0;

    holo::map::Advice input, output;
    input.SetCurrentLaneSequence(seq1);
    input.SetSequenceOfNextCrossing(seq2);
    input.SetTargetLaneAdviceGroup(test_data_target_lane_advice_group_1);
    input.SetTargetLinkAdviceGroup(test_data_target_link_advice_group_1);
    input.AddCrossingInfo(ci1);
    input.AddCrossingInfo(ci2);
    input.AddCrossingInfo(ci3);

    auto default_node = input.GetRoadLogicGraph().GetDefaultLane();
    default_node->SetExternalId(1U);
    auto right_node = input.GetRoadLogicGraph().AddLaneToRight(default_node);
    right_node->SetExternalId(2U);

    uint8_t buffer[1280];
    holo::serialization::Serializer<>          serializer(buffer, 1280);
    serializer << input;
    ASSERT_EQ(input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> output;

    EXPECT_EQ(output.GetTimestamp(), input.GetTimestamp());
    EXPECT_EQ(output.GetCurrentLaneSequence(), input.GetCurrentLaneSequence());
    EXPECT_EQ(output.GetSequenceOfNextCrossing(), input.GetSequenceOfNextCrossing());
    EXPECT_EQ(output.GetCrossingInfoList(), input.GetCrossingInfoList());
    EXPECT_EQ(output.GetTargetLaneAdviceGroup(), input.GetTargetLaneAdviceGroup());
    EXPECT_EQ(output.GetTargetLinkAdviceGroup(), input.GetTargetLinkAdviceGroup());
    EXPECT_EQ(output.GetRoadLogicGraph().size(), input.GetRoadLogicGraph().size());

    EXPECT_EQ(output.GetRoadLogicGraph().GetDefaultLane()->GetExternalId(),
              input.GetRoadLogicGraph().GetDefaultLane()->GetExternalId());
    EXPECT_EQ(output.GetRoadLogicGraph().GetDefaultLane().GetRight()->GetExternalId(),
              input.GetRoadLogicGraph().GetDefaultLane().GetRight()->GetExternalId());

}

TEST(TestAdvice, TestRoadSpeedLimits)
{
    holo::map::RoadSpeedLimits::LaneIndexType index = 5U;
    holo::map::RoadSpeedLimits::LaneSpeedLimits lane_limit(index);
    lane_limit.GetLaneIndex();
}

TEST(TestAdvice, TestRoadSpeedLimitsSerialize)
{
    holo::map::RoadSpeedLimits::LaneIndexType index = 5U;
    holo::map::RoadSpeedLimits::LaneSpeedLimits lane_limit(index);

    holo::map::RoadSpeedLimits::LaneIndexType index2 = 0U;
    holo::map::RoadSpeedLimits::LaneIndexType index3 = 2U;

    holo::map::RoadSpeedLimits road_limit, road_limit2;
    road_limit.SetLaneIndexRange(index2, index3);
    road_limit[0] = lane_limit;

    uint8_t buffer[1024];
    holo::serialization::Serializer<>           serializer(buffer, 1024);
    serializer << road_limit;
    ASSERT_EQ(road_limit.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> road_limit2;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
