/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_odm.cpp
 * @brief Unit test for odm related types.
 * @author lichao@holomatic.com
 * @date Mar 03, 2020
 */

#include <gtest/gtest.h>
#include <holo/common/odm.h>

using holo::common::Timestamp;
using holo::common::OdmState;
using holo::common::OdmStates;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmState, ConStructorFromUint32T)
{
    // Prepare the value of ODM State.
    // Compute expected result which is (2^23) + (2^22) + (30*2^15) + (2^14) + (250) = 13582586.
    const uint32_t kValue = 13582586u;

    // Construct OdmState by uint32_t.
    OdmState odm_state(kValue);

    // Check result.
    ASSERT_TRUE(odm_state.IsEnabled());
    ASSERT_TRUE(odm_state.IsPredictedDistanceValid());
    ASSERT_TRUE(odm_state.IsPredictedTimeValid());
    ASSERT_TRUE(odm_state.GetPredictedDistance() == 250u);
    ASSERT_TRUE(odm_state.GetPredictedTime() == 30u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmState, Enable)
{
    OdmState odm_state;
    ASSERT_NO_THROW(odm_state.Enable());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmState, Disable)
{
    OdmState odm_state;
    ASSERT_NO_THROW(odm_state.Disable());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmState, SetPredDistance)
{
    OdmState odm_state;
    // Test valid input
    ASSERT_NO_THROW(odm_state.SetPredDistance(100u));
    // Test invalid input
    ASSERT_THROW(odm_state.SetPredDistance(100000u), holo::exception::OutOfRangeException);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmState, SetPredTime)
{
    OdmState odm_state;
    // Test valid input
    ASSERT_NO_THROW(odm_state.SetPredTime(50u));
    // Test invalid input
    ASSERT_THROW(odm_state.SetPredTime(200u), holo::exception::OutOfRangeException);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmState, IsEnabled)
{
    OdmState odm_state;
    // Test enabled case.
    odm_state.Enable();
    ASSERT_TRUE(odm_state.IsEnabled());
    // Test disabled case.
    odm_state.Disable();
    ASSERT_FALSE(odm_state.IsEnabled());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmState, IsPredictDistanceValid)
{
    OdmState odm_state;
    ASSERT_FALSE(odm_state.IsPredictedDistanceValid());
    odm_state.SetPredDistance(100u);
    ASSERT_TRUE(odm_state.IsPredictedDistanceValid());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmState, IsPredictTimeValid)
{
    OdmState odm_state;
    ASSERT_FALSE(odm_state.IsPredictedTimeValid());
    odm_state.SetPredTime(30u);
    ASSERT_TRUE(odm_state.IsPredictedTimeValid());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmState, GetPredDistance)
{
    uint32_t const expected_predict_distance = 50u;
    OdmState       odm_state;
    odm_state.SetPredDistance(expected_predict_distance);
    ASSERT_EQ(odm_state.GetPredictedDistance(), expected_predict_distance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmState, GetPredTime)
{
    uint32_t const expected_predict_time = 30u;
    OdmState       odm_state;
    odm_state.SetPredTime(expected_predict_time);
    ASSERT_EQ(odm_state.GetPredictedTime(), expected_predict_time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmState, OperatorUint32T)
{
    OdmState odm_state;
    ASSERT_EQ((uint32_t)odm_state, 0u);
    odm_state.Enable();
    odm_state.SetPredDistance(250u);
    odm_state.SetPredTime(30u);
    // Compute expected result which is (2^23) + (2^22) + (30*2^15) + (2^14) + (250) = 13582586.
    ASSERT_EQ((uint32_t)odm_state, 13582586u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmStates, Reserved_Get_Set)
{
    OdmState odm_state;

    {
        const uint32_t old_odm_val = static_cast<uint32_t>(odm_state);
        ASSERT_EQ(0U, old_odm_val);

        {
            // Get reserved
            const uint32_t reserved_val = old_odm_val >> 24U;
            ASSERT_EQ(0U, reserved_val);
        }

        // Set reserved, should not change value of other parts
        const uint32_t val_used_to_clear = (static_cast<holo::uint32_t>(-1) >> 8U);
        const uint32_t val_to_set = 128;
        const uint32_t new_odm_val = (old_odm_val & val_used_to_clear) | (val_to_set << 24U); 

        {
            // Get reserved
            const uint32_t reserved_val = new_odm_val >> 24U;
            ASSERT_EQ(128U, reserved_val);
        }

        OdmState new_odm_state(new_odm_val);
        ASSERT_EQ(new_odm_state.IsEnabled(), false);
        ASSERT_EQ(new_odm_state.IsPredictedDistanceValid(), false);
        ASSERT_EQ(new_odm_state.GetPredictedDistance(), 0U);
    }

    // Set reserved, should not change value of other parts
    odm_state.Enable();
    odm_state.SetPredDistance(500U);

    {
        const uint32_t old_odm_val = static_cast<uint32_t>(odm_state);
        const uint32_t expect_odm_val = 500U + (1U << 14) + (1U << 23U);
        ASSERT_EQ(expect_odm_val, old_odm_val);
        
        {
            // Get reserved
            const uint32_t reserved_val = old_odm_val >> 24U;
            ASSERT_EQ(0U, reserved_val);
        }

        // Set reserved, should not change value of other parts
        const uint32_t val_used_to_clear = (static_cast<holo::uint32_t>(-1) >> 8U);
        const uint32_t val_to_set = 128;
        const uint32_t new_odm_val = (old_odm_val & val_used_to_clear) | (val_to_set << 24U); 

        {
            // Get reserved
            const uint32_t reserved_val = new_odm_val >> 24U;
            ASSERT_EQ(128U, reserved_val);
        }

        OdmState new_odm_state(new_odm_val);
        ASSERT_EQ(new_odm_state.IsEnabled(), true);
        ASSERT_EQ(new_odm_state.IsPredictedDistanceValid(), true);
        ASSERT_EQ(new_odm_state.GetPredictedDistance(), 500U);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmStates, GetTimestamp)
{
    Timestamp const excepted_timestamp(1000u, 1000u);
    OdmStates       odm_states;
    odm_states.SetTimestamp(excepted_timestamp);
    ASSERT_TRUE(odm_states.GetTimestamp() == excepted_timestamp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OdmStates, OperatorAccess)
{
    OdmStates odm_states;

    // create odmstate for ACC
    OdmState odm_state_acc;
    odm_state_acc.Enable();
    odm_state_acc.SetPredDistance(250u);
    odm_states[OdmStates::Ddt::ACC] = odm_state_acc;

    // create odmstate for EMSS
    OdmState odm_state_emss;
    odm_state_emss.Enable();
    odm_state_emss.SetPredTime(50u);
    odm_states[OdmStates::Ddt::EMSS] = odm_state_emss;

    // create odmstate for HSA
    OdmState odm_state_hsa;
    odm_state_hsa.Disable();
    odm_states[OdmStates::Ddt::HSA] = odm_state_hsa;

    // check odmstate of each ACC
    ASSERT_TRUE(odm_states[OdmStates::Ddt::ACC].IsEnabled());
    ASSERT_TRUE(odm_states[OdmStates::Ddt::ACC].IsPredictedDistanceValid());
    ASSERT_EQ(odm_states[OdmStates::Ddt::ACC].GetPredictedDistance(), 250u);
    ASSERT_FALSE(odm_states[OdmStates::Ddt::ACC].IsPredictedTimeValid());

    // check odmstate of each ICP
    ASSERT_FALSE(odm_states[OdmStates::Ddt::ICP].IsEnabled());
    ASSERT_FALSE(odm_states[OdmStates::Ddt::ICP].IsPredictedTimeValid());
    ASSERT_FALSE(odm_states[OdmStates::Ddt::ICP].IsPredictedDistanceValid());

    // check odmstate of each EMSS
    ASSERT_TRUE(odm_states[OdmStates::Ddt::EMSS].IsEnabled());
    ASSERT_TRUE(odm_states[OdmStates::Ddt::EMSS].IsPredictedTimeValid());
    ASSERT_EQ(odm_states[OdmStates::Ddt::EMSS].GetPredictedTime(), 50u);
    ASSERT_FALSE(odm_states[OdmStates::Ddt::EMSS].IsPredictedDistanceValid());

    // check odmstate of each HSA
    ASSERT_FALSE(odm_states[OdmStates::Ddt::HSA].IsEnabled());
    ASSERT_FALSE(odm_states[OdmStates::Ddt::HSA].IsPredictedDistanceValid());
    ASSERT_FALSE(odm_states[OdmStates::Ddt::HSA].IsPredictedTimeValid());
}

TEST(OdmStates, GetSerializedSize)
{
    OdmStates odmstates;
    ASSERT_EQ(44, odmstates.GetSerializedSize<4U>());
    ASSERT_EQ(48, odmstates.GetSerializedSize<8U>());
}

TEST(OdmStates, SerializeAndDeserialize)
{
    OdmStates expected_odmstates, actual_odmstates;
    expected_odmstates.SetTimestamp(holo::Timestamp(20, 30));
    for (size_t i = 0u; i < OdmStates::kDdtNumValue_; ++i)
    {
        OdmState odmstate;

        if (i % 2u == 0u)
        {
            odmstate.Enable();
        }

        odmstate.SetPredDistance(i * 10u);
        expected_odmstates[static_cast<OdmStates::Ddt>(i)] = odmstate;
    }

    uint8_t buffer[1024];
    holo::serialization::Serializer<>          serializer(buffer, 1024);
    serializer << expected_odmstates;
    ASSERT_EQ(expected_odmstates.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> actual_odmstates;

    ASSERT_EQ(expected_odmstates.GetTimestamp(), actual_odmstates.GetTimestamp());
    for (size_t i = 0u; i < OdmStates::kDdtNumValue_; ++i)
    {
        const OdmState expected_odmstate = expected_odmstates[static_cast<OdmStates::Ddt>(i)];
        const OdmState actual_odmstate   = actual_odmstates[static_cast<OdmStates::Ddt>(i)];
        ASSERT_EQ(expected_odmstate.IsEnabled(), actual_odmstate.IsEnabled());
        ASSERT_EQ(expected_odmstate.IsPredictedDistanceValid(), actual_odmstate.IsPredictedDistanceValid());
        ASSERT_EQ(expected_odmstate.IsPredictedTimeValid(), actual_odmstate.IsPredictedTimeValid());
        ASSERT_EQ(expected_odmstate.GetPredictedTime(), actual_odmstate.GetPredictedTime());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
