/*!
 *  @brief Defines intention class.
 *  @author xieshuai(xieshuai@holomatic.ai)
 *  @date "2019-12-05"
 *  @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/common/timestamp.h>
#include <holo/prediction/intention.h>

#include <stdexcept>
#include <string>

using namespace holo;
using namespace prediction;
using holo::prediction::Intention;
using holo::common::Timestamp;

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionTest, Default_Constructor)
{
    Intention intention;
    ASSERT_EQ(intention.GetStampStart(), Timestamp(0u, 0u));
    ASSERT_EQ(intention.GetStampEnd(), Timestamp(0u, 0u));
    ASSERT_EQ(intention.GetId(), 0u);
    ASSERT_EQ(intention.GetLateralIntention(), Intention::LateralIntention::UNKNOWN);
    ASSERT_EQ(intention.GetLongitudinalIntention(), Intention::LongitudinalIntention::UNKNOWN);
    ASSERT_EQ(intention.GetLateralConfidence(), 0.0f);
    ASSERT_EQ(intention.GetLongitudinalConfidence(), 0.0f);
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionTest, Constructor)
{
    Timestamp const stamp_start(100u, 100u);
    Timestamp const stamp_end(102u, 100u);
    uint32_t const  id                      = 10u;
    float32_t const lateral_confidence      = 1.0f;
    float32_t const longitudinal_confidence = 1.0f;
    Intention       intention(stamp_start, stamp_end, id, Intention::LateralIntention::CUT_IN_EGO,
                        Intention::LongitudinalIntention::SPEED_KEEP, lateral_confidence, longitudinal_confidence);
    ASSERT_EQ(intention.GetStampStart(), stamp_start);
    ASSERT_EQ(intention.GetStampEnd(), stamp_end);
    ASSERT_EQ(intention.GetId(), id);
    ASSERT_EQ(intention.GetLateralIntention(), Intention::LateralIntention::CUT_IN_EGO);
    ASSERT_EQ(intention.GetLongitudinalIntention(), Intention::LongitudinalIntention::SPEED_KEEP);
    ASSERT_EQ(intention.GetLateralConfidence(), lateral_confidence);
    ASSERT_EQ(intention.GetLongitudinalConfidence(), longitudinal_confidence);
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionTest, Constructor_With_ID)
{
    Intention intention(10u);
    ASSERT_EQ(intention.GetStampStart(), Timestamp(0u, 0u));
    ASSERT_EQ(intention.GetStampEnd(), Timestamp(0u, 0u));
    ASSERT_EQ(intention.GetId(), 10u);
    ASSERT_EQ(intention.GetLateralIntention(), Intention::LateralIntention::UNKNOWN);
    ASSERT_EQ(intention.GetLongitudinalIntention(), Intention::LongitudinalIntention::UNKNOWN);
    ASSERT_EQ(intention.GetLateralConfidence(), 0.0f);
    ASSERT_EQ(intention.GetLongitudinalConfidence(), 0.0f);
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionTest, Copy_Constructor)
{
    Timestamp const stamp_start(100u, 100u);
    Timestamp const stamp_end(102u, 100u);
    uint32_t const  id                      = 10u;
    float32_t const lateral_confidence      = 1.0f;
    float32_t const longitudinal_confidence = 1.0f;
    Intention       intention(stamp_start, stamp_end, id, Intention::LateralIntention::CUT_IN_EGO,
                        Intention::LongitudinalIntention::SPEED_KEEP, lateral_confidence, longitudinal_confidence);
    Intention       intention_copy(intention);
    ASSERT_EQ(intention_copy.GetStampStart(), intention.GetStampStart());
    ASSERT_EQ(intention_copy.GetStampEnd(), intention.GetStampEnd());
    ASSERT_EQ(intention_copy.GetId(), intention.GetId());
    ASSERT_EQ(intention_copy.GetLateralIntention(), intention.GetLateralIntention());
    ASSERT_EQ(intention_copy.GetLongitudinalIntention(), intention.GetLongitudinalIntention());
    ASSERT_EQ(intention_copy.GetLateralConfidence(), intention.GetLateralConfidence());
    ASSERT_EQ(intention_copy.GetLongitudinalConfidence(), intention.GetLongitudinalConfidence());
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionTest, Setter_Getter)
{
    Timestamp const stamp_start(100u, 100u);
    Timestamp const stamp_end(102u, 100u);
    uint32_t const  id                      = 10u;
    float32_t const lateral_confidence      = 1.0f;
    float32_t const longitudinal_confidence = 1.0f;
    Intention       intention;
    intention.SetStampStart(stamp_start);
    intention.SetStampEnd(stamp_end);
    intention.SetId(id);
    intention.SetLateralIntention(Intention::LateralIntention::CUT_IN_EGO);
    ASSERT_THROW(intention.SetLateralIntention(Intention::LateralIntention::INVALID), std::runtime_error);
    intention.SetLongitudinalIntention(Intention::LongitudinalIntention::SPEED_KEEP);
    ASSERT_THROW(intention.SetLongitudinalIntention(Intention::LongitudinalIntention::INVALID), std::runtime_error);
    intention.SetLateralConfidence(lateral_confidence);
    intention.SetLongitudinalConfidence(longitudinal_confidence);
    ASSERT_THROW(intention.SetLateralConfidence(-1.0f), std::runtime_error);
    ASSERT_THROW(intention.SetLateralConfidence(2.0f), std::runtime_error);
    ASSERT_THROW(intention.SetLongitudinalConfidence(-1.0f), std::runtime_error);
    ASSERT_THROW(intention.SetLongitudinalConfidence(2.0f), std::runtime_error);
    ASSERT_EQ(intention.GetStampStart(), stamp_start);
    ASSERT_EQ(intention.GetStampEnd(), stamp_end);
    ASSERT_EQ(intention.GetId(), id);
    ASSERT_EQ(intention.GetLateralIntention(), intention.GetLateralIntention());
    ASSERT_EQ(intention.GetLongitudinalIntention(), intention.GetLongitudinalIntention());
    ASSERT_EQ(intention.GetLateralConfidence(), lateral_confidence);
    ASSERT_EQ(intention.GetLongitudinalConfidence(), longitudinal_confidence);
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionTest, Type_Compare)
{
    Intention intention;
    intention.SetLateralIntention(Intention::LateralIntention::LANE_KEEP);
    ASSERT_TRUE(intention.IsLateralIntentionType(Intention::LateralIntention::LANE_KEEP));
    intention.SetLongitudinalIntention(Intention::LongitudinalIntention::SPEED_KEEP);
    ASSERT_TRUE(intention.IsLongitudinalIntentionType(Intention::LongitudinalIntention::SPEED_KEEP));
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionTest, IO)
{
    Intention intention;
    ASSERT_NO_THROW(intention.ToString());
    ASSERT_NO_THROW(std::cout << intention);
}

TEST(IntentionTest, GetSerializedSize)
{
    Intention                              intention;    
    ASSERT_EQ(32, intention.GetSerializedSize<4U>());
    ASSERT_EQ(32, intention.GetSerializedSize<8U>());
}

TEST(IntentionTest, SerializeAndDeserialize)
{
    Intention                              intention_input;
    Intention                              intention_output;

    Timestamp const                        stamp_start(100U, 100U);
    Timestamp const                        stamp_end(102U, 100U);
    uint32_t const                         id                      = 10U;
    Intention::LateralIntention const      lateral_intention       = Intention::LateralIntention::CUT_IN_EGO;
    Intention::LongitudinalIntention const longitudinal_intention  = Intention::LongitudinalIntention::SPEED_KEEP;
    float32_t const                        lateral_confidence      = 1.0f;
    float32_t const                        longitudinal_confidence = 1.0f;

    intention_input.SetStampStart(stamp_start);
    intention_input.SetStampEnd(stamp_end);
    intention_input.SetId(id);
    intention_input.SetLateralIntention(lateral_intention);
    intention_input.SetLongitudinalIntention(longitudinal_intention);
    intention_input.SetLateralConfidence(lateral_confidence);
    intention_input.SetLongitudinalConfidence(longitudinal_confidence);

    uint8_t buffer[512];
    holo::serialization::Serializer<>          serializer(buffer, 512);
    serializer << intention_input;
    ASSERT_EQ(intention_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> intention_output;

    ASSERT_EQ(intention_input.GetStampStart(), intention_output.GetStampStart());
    ASSERT_EQ(intention_input.GetStampEnd(), intention_output.GetStampEnd());
    ASSERT_EQ(intention_input.GetId(), intention_output.GetId());
    ASSERT_EQ(intention_input.GetLateralIntention(), intention_output.GetLateralIntention());
    ASSERT_EQ(intention_input.GetLongitudinalIntention(), intention_output.GetLongitudinalIntention());
    ASSERT_EQ(intention_input.GetLateralConfidence(), intention_output.GetLateralConfidence());
    ASSERT_EQ(intention_input.GetLongitudinalConfidence(), intention_output.GetLongitudinalConfidence());
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
