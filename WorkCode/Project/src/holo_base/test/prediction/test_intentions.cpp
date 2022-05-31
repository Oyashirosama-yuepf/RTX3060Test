/**
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_intentions.cpp
 * @brief Implements unit test on Intentions class.
 * @author xieshuai(xieshuai@holomatic.com)
 * @date "2019-12-26"
 */

#include <gtest/gtest.h>
#include <holo/common/timestamp.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/prediction/intention.h>
#include <holo/prediction/intentions.h>

using namespace holo;
using namespace prediction;
using holo::prediction::Intentions;
using holo::common::Timestamp;

static uint32_t const INTENTION_SERIALIZED_SIZE_4B = 32u;
static uint32_t const INTENTION_SERIALIZED_SIZE_8B = 40u;
static uint32_t const TEST_SIZE                    = 256u;

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, Default_Constructor)
{
    Intentions intentions;
    ASSERT_EQ(intentions.GetTimestamp(), Timestamp(0, 0));
    ASSERT_EQ(intentions.size(), 0u);
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, Copy_Constructor)
{
    Intentions intentions;

    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        Intention const source(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention,
                               lateral_confidence, longitudinal_confidence);
        intentions.Insert(source);
    }

    Intentions copied_intentions(intentions);
    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        auto const      copied_intention        = copied_intentions.At(i);
        ASSERT_EQ(copied_intention.GetStampStart(), stamp_start);
        ASSERT_EQ(copied_intention.GetStampEnd(), stamp_end);
        ASSERT_EQ(copied_intention.GetId(), id);
        ASSERT_EQ(copied_intention.GetLateralIntention(), lateral_intention);
        ASSERT_EQ(copied_intention.GetLongitudinalIntention(), longitudinal_intention);
        ASSERT_EQ(copied_intention.GetLateralConfidence(), lateral_confidence);
        ASSERT_EQ(copied_intention.GetLongitudinalConfidence(), longitudinal_confidence);
    }
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, Move_Constructor)
{
    Intentions intentions;

    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        Intention const source(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention,
                               lateral_confidence, longitudinal_confidence);
        intentions.Insert(source);
    }
    auto const address_map = &*intentions.begin();
    Intentions moved_intentions(std::move(intentions));
    ASSERT_EQ(&*moved_intentions.begin(), address_map);
    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        auto const      moved_intention         = moved_intentions.At(i);
        ASSERT_EQ(moved_intention.GetStampStart(), stamp_start);
        ASSERT_EQ(moved_intention.GetStampEnd(), stamp_end);
        ASSERT_EQ(moved_intention.GetId(), id);
        ASSERT_EQ(moved_intention.GetLateralIntention(), lateral_intention);
        ASSERT_EQ(moved_intention.GetLongitudinalIntention(), longitudinal_intention);
        ASSERT_EQ(moved_intention.GetLateralConfidence(), lateral_confidence);
        ASSERT_EQ(moved_intention.GetLongitudinalConfidence(), longitudinal_confidence);
    }
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, Timestamp_Setter_Getter)
{
    Intentions      intentions;
    Timestamp const stamp(0u, 0u);
    intentions.SetTimestamp(stamp);
    ASSERT_EQ(intentions.GetTimestamp(), stamp);
    ASSERT_EQ(intentions.size(), 0u);
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, At)
{
    Intentions intentions;
    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        Intention const source(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention,
                               lateral_confidence, longitudinal_confidence);
        intentions.Insert(source);
        auto const& intention = intentions.At(i);
        ASSERT_EQ(intention.GetStampStart(), stamp_start);
        ASSERT_EQ(intention.GetStampEnd(), stamp_end);
        ASSERT_EQ(intention.GetId(), id);
        ASSERT_EQ(intention.GetLateralIntention(), lateral_intention);
        ASSERT_EQ(intention.GetLongitudinalIntention(), longitudinal_intention);
        ASSERT_EQ(intention.GetLateralConfidence(), lateral_confidence);
        ASSERT_EQ(intention.GetLongitudinalConfidence(), longitudinal_confidence);
    }
    ASSERT_THROW(intentions.At(TEST_SIZE), holo::exception::OutOfRangeException);
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, Find)
{
    Intentions intentions;
    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        Intention const source(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention,
                               lateral_confidence, longitudinal_confidence);
        intentions.Insert(source);
    }
    for (auto iter = intentions.begin(); iter != intentions.end(); iter++)
    {
        ASSERT_EQ(intentions.Find(iter->GetId()), iter);
    }
    ASSERT_EQ(intentions.Find(TEST_SIZE), intentions.end());
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, Iterator)
{
    Intentions intentions;
    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        Intention const source(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention,
                               lateral_confidence, longitudinal_confidence);
        // intentions.Insert(source);
    }

    for (auto iter = intentions.begin(); iter != intentions.end(); iter++)
    {
        uint32_t const&                        i = iter->GetId();
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        ASSERT_EQ(iter->GetStampStart(), stamp_start);
        ASSERT_EQ(iter->GetStampEnd(), stamp_end);
        ASSERT_EQ(iter->GetLateralIntention(), lateral_intention);
        ASSERT_EQ(iter->GetLongitudinalIntention(), longitudinal_intention);
        ASSERT_EQ(iter->GetLateralConfidence(), lateral_confidence);
        ASSERT_EQ(iter->GetLongitudinalConfidence(), longitudinal_confidence);
    }
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, Insert)
{
    Intentions intentions;
    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        Intention const source(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention,
                               lateral_confidence, longitudinal_confidence);
        intentions.Insert(source);
        auto const& intention = intentions.At(i);
        ASSERT_EQ(intention.GetStampStart(), stamp_start);
        ASSERT_EQ(intention.GetStampEnd(), stamp_end);
        ASSERT_EQ(intention.GetId(), id);
        ASSERT_EQ(intention.GetLateralIntention(), lateral_intention);
        ASSERT_EQ(intention.GetLongitudinalIntention(), longitudinal_intention);
        ASSERT_EQ(intention.GetLateralConfidence(), lateral_confidence);
        ASSERT_EQ(intention.GetLongitudinalConfidence(), longitudinal_confidence);
    }
    Intention intention_duplicate;
    intention_duplicate.SetId(1u);
    ASSERT_FALSE(intentions.Insert(intention_duplicate));
    ASSERT_NE(intentions.At(1u).GetId(), 0u);
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, Emplace)
{
    Intentions intentions;
    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        intentions.Emplace(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention, lateral_confidence,
                           longitudinal_confidence);
        auto const& intention = intentions.At(i);
        ASSERT_EQ(intention.GetStampStart(), stamp_start);
        ASSERT_EQ(intention.GetStampEnd(), stamp_end);
        ASSERT_EQ(intention.GetId(), id);
        ASSERT_EQ(intention.GetLateralIntention(), lateral_intention);
        ASSERT_EQ(intention.GetLongitudinalIntention(), longitudinal_intention);
        ASSERT_EQ(intention.GetLateralConfidence(), lateral_confidence);
        ASSERT_EQ(intention.GetLongitudinalConfidence(), longitudinal_confidence);
    }
    ASSERT_FALSE(intentions.Emplace(Timestamp(), Timestamp(), 1u, Intention::LateralIntention::CUT_IN_EGO,
                                    Intention::LongitudinalIntention::SPEED_KEEP, 0.0, 0.0));
    ASSERT_NE(intentions.At(1u).GetId(), 0u);
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, Erase)
{
    Intentions intentions;
    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        Intention const source(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention,
                               lateral_confidence, longitudinal_confidence);
        intentions.Insert(source);
        bool_t const erased = intentions.Erase(source.GetId());
        ASSERT_EQ(erased, true);
        ASSERT_EQ(intentions.size(), 0u);
    }
    ASSERT_NO_THROW(intentions.Erase(0u));
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, size)
{
    Intentions intentions;
    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        Intention const source(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention,
                               lateral_confidence, longitudinal_confidence);
        intentions.Insert(source);
        ASSERT_EQ(intentions.size(), i + 1);
    }
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, clear)
{
    Intentions intentions;
    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        Intention const source(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention,
                               lateral_confidence, longitudinal_confidence);
        intentions.Insert(source);
    }
    intentions.clear();
    ASSERT_EQ(intentions.size(), 0u);
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, Copy_Assignment_Operator)
{
    Intentions intentions;

    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        Intention const source(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention,
                               lateral_confidence, longitudinal_confidence);
        intentions.Insert(source);
    }

    Intentions copied_intentions = intentions;
    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        auto const      copied_intention        = copied_intentions.At(i);
        ASSERT_EQ(copied_intention.GetStampStart(), stamp_start);
        ASSERT_EQ(copied_intention.GetStampEnd(), stamp_end);
        ASSERT_EQ(copied_intention.GetId(), id);
        ASSERT_EQ(copied_intention.GetLateralIntention(), lateral_intention);
        ASSERT_EQ(copied_intention.GetLongitudinalIntention(), longitudinal_intention);
        ASSERT_EQ(copied_intention.GetLateralConfidence(), lateral_confidence);
        ASSERT_EQ(copied_intention.GetLongitudinalConfidence(), longitudinal_confidence);
    }
}

////////////////////////////////////////////////////////////////////////////////
TEST(IntentionsTest, Move_Assignment_Operator)
{
    Intentions intentions;

    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        Intention const source(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention,
                               lateral_confidence, longitudinal_confidence);
        intentions.Insert(source);
    }
    auto const address_map      = &*intentions.begin();
    Intentions moved_intentions = std::move(intentions);
    ASSERT_EQ(&*moved_intentions.begin(), address_map);
    for (uint32_t i = 0; i < TEST_SIZE; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        auto const      moved_intention         = moved_intentions.At(i);
        ASSERT_EQ(moved_intention.GetStampStart(), stamp_start);
        ASSERT_EQ(moved_intention.GetStampEnd(), stamp_end);
        ASSERT_EQ(moved_intention.GetId(), id);
        ASSERT_EQ(moved_intention.GetLateralIntention(), lateral_intention);
        ASSERT_EQ(moved_intention.GetLongitudinalIntention(), longitudinal_intention);
        ASSERT_EQ(moved_intention.GetLateralConfidence(), lateral_confidence);
        ASSERT_EQ(moved_intention.GetLongitudinalConfidence(), longitudinal_confidence);
    }
}

TEST(IntentionTest, GetSerializedSize)
{
    Intentions intentions;    
    ASSERT_EQ(12, intentions.GetSerializedSize<4U>());
    ASSERT_EQ(16, intentions.GetSerializedSize<8U>());
}

TEST(IntentionTest, SerializeAndDeserialize)
{
    Intentions                              input_intentions;
    Intentions                              output_intentions;
    for (uint32_t i = 0; i < 10; i++)
    {
        Timestamp const                        stamp_start(i, i);
        Timestamp const                        stamp_end(i, i);
        uint32_t const                         id                     = i;
        Intention::LateralIntention const      lateral_intention      = Intention::LateralIntention::CUT_IN_EGO;
        Intention::LongitudinalIntention const longitudinal_intention = Intention::LongitudinalIntention::SPEED_KEEP;
        float32_t const lateral_confidence      = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        float32_t const longitudinal_confidence = 0.0f + static_cast<float32_t>(i) / static_cast<float32_t>(TEST_SIZE);
        Intention const intention(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention,
                                  lateral_confidence, longitudinal_confidence);
        input_intentions.Insert(intention);
    }

    uint8_t buffer[1280];
    holo::serialization::Serializer<>          serializer(buffer, 1280);
    serializer << input_intentions;
    ASSERT_EQ(input_intentions.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> output_intentions;

    ASSERT_EQ(output_intentions.GetTimestamp(), input_intentions.GetTimestamp());
    ASSERT_EQ(output_intentions.size(), input_intentions.size());
    for (uint32_t i = 0; i < input_intentions.size(); i++)
    {
        const auto& source = input_intentions.At(i);
        const auto& target = output_intentions.At(i);
        ASSERT_EQ(target.GetStampStart(), source.GetStampStart());
        ASSERT_EQ(target.GetStampEnd(), source.GetStampEnd());
        ASSERT_EQ(target.GetId(), source.GetId());
        ASSERT_EQ(target.GetLateralIntention(), source.GetLateralIntention());
        ASSERT_EQ(target.GetLongitudinalIntention(), source.GetLongitudinalIntention());
        ASSERT_EQ(target.GetLateralConfidence(), source.GetLateralConfidence());
        ASSERT_EQ(target.GetLongitudinalConfidence(), source.GetLongitudinalConfidence());
    }
}


////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
