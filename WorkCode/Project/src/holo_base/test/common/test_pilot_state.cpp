/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *  @file test_pilot_state.cpp
 *  @brief This is used to test PilotState object
 *  @author zhang Yuchen(zhangyuchen@holomatic.com)
 *  @date 2020-03-26
 */

#include <gtest/gtest.h>
#include <holo/common/pilot_state.h>

using namespace holo::common;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PilotState, construct)
{
    PilotState pilot_state1;
    const uint32_t& state1 = pilot_state1;
    ASSERT_EQ(state1, 0);

    PilotState pilot_state2(2);
    const uint32_t& state2 = pilot_state2;
    ASSERT_EQ(state2, 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PilotState, assign_operator)
{
    PilotState pilot_state;
    pilot_state = 1;
    const uint32_t& state = pilot_state;
    ASSERT_EQ(state, 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PilotState, cast_operator)
{
    PilotState pilot_state(3);
    uint32_t& state1 = pilot_state;
    state1 = 4;
    const uint32_t& state2 = pilot_state;
    ASSERT_EQ(state2, 4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PilotState, serialize_deserialize)
{
    PilotState pilot_state1(3);

    uint8_t buffer[1024];
    holo::serialization::Serializer<>          serializer(buffer, 1024);

    ASSERT_EQ(4U, pilot_state1.GetSerializedSize());

    serializer << pilot_state1;
    holo::serialization::Deserializer<true, 4> deserializer(buffer, serializer.GetSize());

    PilotState pilot_state2;

    ASSERT_EQ(4U, (deserializer >> pilot_state2).GetOffset());
    ASSERT_EQ(pilot_state1 == pilot_state2, true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
