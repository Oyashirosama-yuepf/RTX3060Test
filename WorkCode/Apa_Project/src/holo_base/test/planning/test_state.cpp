/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_state.cpp
 * @brief Unit test for state object.
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2020-12-07
 */

#include <gtest/gtest.h>
#include <holo/planning/state.h>

using holo::common::Alarm;
using holo::planning::State;

/**
 * @brief Test State default constructor
 */
TEST(State, DefaultConstructor)
{
    State state;

    ASSERT_EQ(State::MainState::INACTIVE, state.GetMainState());
    ASSERT_EQ(State::LongitudinalState::NOT_APPLICABLE, state.GetLongitudinalState());
    ASSERT_EQ(State::LateralState::NOT_APPLICABLE, state.GetLateralState());
    ASSERT_EQ(0, state.GetFunctionStateSize());
    ASSERT_EQ(0, state.GetFollowingObsIds().size());
    ASSERT_EQ(0, state.GetCutInObsIds().size());
    ASSERT_EQ(0, state.GetAvoidingObsIds().size());
    ASSERT_EQ(0, state.GetLaneChangeObsIds().size());
}

/**
 * @brief Test State::SetMainState(MainState state) and State::GetMainState()
 */
TEST(State, SetAndGetMainState)
{
    State state;
    state.SetMainState(State::MainState::ASSIST);

    ASSERT_EQ(State::MainState::ASSIST, state.GetMainState());
}

/**
 * @brief Test State::SetLateralState(LateralState state) and State::GetLateralState()
 */
TEST(State, SetAndGetLateralState)
{
    State state;
    state.SetLateralState(State::LateralState::FOLLOW_LEFT_BOUND);

    ASSERT_EQ(State::LateralState::FOLLOW_LEFT_BOUND, state.GetLateralState());
}

/**
 * @brief Test State::SetLongitudinalState(LongitudinalState state) and State::GetLongitudinalState()
 */
TEST(State, SetAndGetLongitudinalState)
{
    State state;
    state.SetLongitudinalState(State::LongitudinalState::ACCELERATE_SPEED);

    ASSERT_EQ(State::LongitudinalState::ACCELERATE_SPEED, state.GetLongitudinalState());
}

/**
 * @brief Test State::GetFunctionStateSize()
 */
TEST(State, GetFunctionStateSize)
{
    State state;
    state.SetFunctionAlarm(State::MainState::ACC, 10);
    state.SetFunctionAlarm(State::MainState::ACC_HOLD, 20);
    state.SetFunctionAlarm(State::MainState::ASSIST, 30);

    ASSERT_EQ(3U, state.GetFunctionStateSize());
}

/**
 * @brief Test State::GetFunctionStateCapacity()
 */
TEST(State, GetFunctionStateCapacity)
{
    State state;
    state.SetFunctionAlarm(State::MainState::ACC, 10);
    state.SetFunctionAlarm(State::MainState::ACC_HOLD, 20);
    state.SetFunctionAlarm(State::MainState::ASSIST, 30);

    ASSERT_EQ(16U, state.GetFunctionStateCapacity());
}

/**
 * @brief Test State::ClearFunctionState()
 */
TEST(State, ClearFunctionState)
{
    State state;
    state.SetFunctionAlarm(State::MainState::ACC, 10);
    state.SetFunctionAlarm(State::MainState::ACC_HOLD, 20);
    state.SetFunctionAlarm(State::MainState::ASSIST, 30);
    state.ClearFunctionState();
    ASSERT_EQ(0U, state.GetFunctionStateSize());
}

/**
 * @brief Test State::GetFunctionState(size_t index)
 */
TEST(State, GetFunctionState_1)
{
    State state;
    state.SetFunctionAlarm(State::MainState::ACC, 10);
    state.SetFunctionAlarm(State::MainState::ACC_HOLD, 20);
    state.SetFunctionAlarm(State::MainState::ASSIST, 30);

    std::pair<State::MainState, Alarm> data1(State::MainState::ACC, Alarm(10));
    std::pair<State::MainState, Alarm> data2(State::MainState::ACC_HOLD, Alarm(20));
    std::pair<State::MainState, Alarm> data3(State::MainState::ASSIST, Alarm(30));

    ASSERT_EQ(data1, state.GetFunctionState(0U));
    ASSERT_EQ(data2, state.GetFunctionState(1U));
    ASSERT_EQ(data3, state.GetFunctionState(2U));
}

/**
 * @brief Test State::GetFunctionState(size_t index) with exception
 */
TEST(State, GetFunctionState_2)
{
    State state;
    state.SetFunctionAlarm(State::MainState::ACC, 10);
    state.SetFunctionAlarm(State::MainState::ACC_HOLD, 20);
    state.SetFunctionAlarm(State::MainState::ASSIST, 30);

    EXPECT_THROW(state.GetFunctionState(3), std::out_of_range);
}

/**
 * @brief Test State::SetFunctionAlarm(uint16_t function,holo::common::Alarm alarm) And
 * State::GetFunctionAlarm(uint16_t function)
 */
TEST(State, SetAndGetFunctionAlarm_1)
{
    State state;
    state.SetFunctionAlarm(State::MainState::ACC, 10);
    state.SetFunctionAlarm(State::MainState::ACC_HOLD, 20);
    state.SetFunctionAlarm(State::MainState::ASSIST, 30);
    state.SetFunctionAlarm(State::MainState::ASSIST_HOLD, 40);

    ASSERT_EQ(Alarm(10), state.GetFunctionAlarm(State::MainState::ACC));
    ASSERT_EQ(Alarm(20), state.GetFunctionAlarm(State::MainState::ACC_HOLD));
    ASSERT_EQ(Alarm(30), state.GetFunctionAlarm(State::MainState::ASSIST));
    ASSERT_EQ(Alarm(40), state.GetFunctionAlarm(State::MainState::ASSIST_HOLD));
    ASSERT_EQ(Alarm(0xFFFF), state.GetFunctionAlarm(State::MainState::PILOT));

    state.SetFunctionAlarm(State::MainState::ACC_HOLD, 40);
    ASSERT_EQ(Alarm(40), state.GetFunctionAlarm(State::MainState::ACC_HOLD));
}

/**
 * @brief Test State::IsFunctionActivable(uint16_t function)
 */
TEST(State, IsFunctionActivable)
{
    State state;
    state.SetFunctionAlarm(State::MainState::ACC, 10);
    state.SetFunctionAlarm(State::MainState::ACC_HOLD, 0);
    state.SetFunctionAlarm(State::MainState::ASSIST, 30);

    ASSERT_EQ(true, state.IsFunctionActivable(State::MainState::ACC_HOLD));
    ASSERT_EQ(false, state.IsFunctionActivable(State::MainState::ASSIST));
    ASSERT_EQ(false, state.IsFunctionActivable(State::MainState::PILOT));
}

/**
 * @brief Test State::RemoveFunction(uint16_t function)
 */
TEST(State, RemoveFunction)
{
    State state;
    state.SetFunctionAlarm(State::MainState::ACC, 10);
    state.SetFunctionAlarm(State::MainState::ACC_HOLD, 20);
    state.SetFunctionAlarm(State::MainState::ASSIST, 0);

    ASSERT_EQ(true, state.RemoveFunction(State::MainState::ASSIST));
    ASSERT_EQ(false, state.RemoveFunction(State::MainState::PILOT));
    ASSERT_EQ(false, state.IsFunctionActivable(State::MainState::ASSIST));
    ASSERT_EQ(2, state.GetFunctionStateSize());
}

/**
 * @brief Test State::SetFollowingObsIds(VectorType const& list) and State::GetFollowingObsIds()
 */
TEST(State, SetAndGetFollowingObsIdsWithCopyConstruct)
{
    State::VectorType vector_list;
    vector_list.push_back(10);
    vector_list.push_back(20);
    vector_list.push_back(30);
    State state;
    state.SetFollowingObsIds(vector_list);

    ASSERT_EQ(vector_list, state.GetFollowingObsIds());
}

/**
 * @brief Test State::SetFollowingObsIds(VectorType&& list) and State::GetFollowingObsIds()
 */
TEST(State, SetAndGetFollowingObsIdsWithMoveConstruct)
{
    State::VectorType vector_list;
    State::VectorType vector_list2;
    vector_list.push_back(10);
    vector_list.push_back(20);
    vector_list2.push_back(10);
    vector_list2.push_back(20);
    State state;
    state.SetFollowingObsIds(std::move(vector_list));

    ASSERT_EQ(vector_list2, state.GetFollowingObsIds());
}

/**
 * @brief Test State::SetFollowingObsIds(InputIt first, InputIt last) and State::GetFollowingObsIds()
 */
TEST(State, SetAndGetFollowingObsIdsWithRange_1)
{
    State::VectorType vector_list;
    vector_list.push_back(10);
    vector_list.push_back(20);
    vector_list.push_back(30);
    State state;
    state.SetFollowingObsIds<State::VectorType::iterator>(vector_list.begin(), vector_list.begin() + 3);

    ASSERT_EQ(vector_list, state.GetFollowingObsIds());
}

/**
 * @brief Test State::SetFollowingObsIds(InputIt first, InputIt last) and State::GetFollowingObsIds()
 * with exception
 */
TEST(State, SetAndGetFollowingObsIdsWithRange_2)
{
    holo::container::details::FixedSizeVector<uint32_t, 15> vector_list = {1, 2,  3,  4,  5,  6,  7, 8,
                                                                           9, 10, 11, 12, 13, 14, 15};
    State                                                   state;
    EXPECT_THROW(state.SetFollowingObsIds(vector_list.begin(), vector_list.end()), std::bad_alloc);
}

/**
 * @brief Test State::SetFollowingObsIds with initializer_list and State::GetFollowingObsIds()
 */
TEST(State, SetAndGetFollowingObsIdsWithInitializerList)
{
    State state;
    state.SetFollowingObsIds({1, 2, 3});

    ASSERT_EQ(1, state.GetFollowingObsIds().at(0));
    ASSERT_EQ(2, state.GetFollowingObsIds().at(1));
    ASSERT_EQ(3, state.GetFollowingObsIds().at(2));
    EXPECT_THROW(state.SetFollowingObsIds({1, 2, 3, 4, 5, 6, 7, 8, 9}), std::bad_alloc);
}

/**
 * @brief Test State::SetCutInObsIds(VectorType const& list) and State::GetCutInObsIds()
 */
TEST(State, SetAndGetCutInObsIdsWithCopyConstruct)
{
    State::VectorType vector_list;
    vector_list.push_back(10);
    vector_list.push_back(20);
    vector_list.push_back(30);
    State state;
    state.SetCutInObsIds(vector_list);

    ASSERT_EQ(vector_list, state.GetCutInObsIds());
}

/**
 * @brief Test State::SetCutInObsIds(VectorType&& list) and State::GetCutInObsIds()
 */
TEST(State, SetAndGetCutInObsIdsWithMoveConstruct)
{
    State::VectorType vector_list;
    State::VectorType vector_list2;
    vector_list.push_back(10);
    vector_list.push_back(20);
    vector_list2.push_back(10);
    vector_list2.push_back(20);
    State state;
    state.SetCutInObsIds(std::move(vector_list));

    ASSERT_EQ(vector_list2, state.GetCutInObsIds());
}

/**
 * @brief Test State::SetCutInObsIds(InputIt first, InputIt last) and State::GetCutInObsIds()
 */
TEST(State, SetAndGetCutInObsIdsWithRange_1)
{
    State::VectorType vector_list;
    vector_list.push_back(10);
    vector_list.push_back(20);
    vector_list.push_back(30);
    State state;
    state.SetCutInObsIds<State::VectorType::iterator>(vector_list.begin(), vector_list.begin() + 3);

    ASSERT_EQ(vector_list, state.GetCutInObsIds());
}

/**
 * @brief Test State::SetCutInObsIds(InputIt first, InputIt last) and State::GetCutInObsIds() exception
 */
TEST(State, SetAndGetCutInObsIdsWithRange_2)
{
    holo::container::details::FixedSizeVector<uint32_t, 15> vector_list = {1, 2,  3,  4,  5,  6,  7, 8,
                                                                           9, 10, 11, 12, 13, 14, 15};
    State                                                   state;
    EXPECT_THROW(state.SetCutInObsIds(vector_list.begin(), vector_list.end()), std::bad_alloc);
}

/**
 * @brief Test State::SetCutInObsIds with initializer_list and State::GetCutInObsIds()
 */
TEST(State, SetAndGetCutInObsIdsWithInitializerList)
{
    State state;
    state.SetCutInObsIds({1, 2, 3});

    ASSERT_EQ(1, state.GetCutInObsIds().at(0));
    ASSERT_EQ(2, state.GetCutInObsIds().at(1));
    ASSERT_EQ(3, state.GetCutInObsIds().at(2));
    EXPECT_THROW(state.SetCutInObsIds({1, 2, 3, 4, 5, 6, 7, 8, 9}), std::bad_alloc);
}

/**
 * @brief Test State::SetAvoidingObsIds(VectorType const& list) and State::GetAvoidingObsIds()
 */
TEST(State, SetAndGetAvoidingObsIdsWithCopyConstruct)
{
    State::VectorType vector_list;
    vector_list.push_back(10);
    vector_list.push_back(20);
    vector_list.push_back(30);
    State state;
    state.SetAvoidingObsIds(vector_list);

    ASSERT_EQ(vector_list, state.GetAvoidingObsIds());
}

/**
 * @brief Test State::SetAvoidingObsIds(VectorType&& list) and State::GetAvoidingObsIds()
 */
TEST(State, SetAndGetAvoidingObsIdsWithMoveConstruct)
{
    State::VectorType vector_list;
    State::VectorType vector_list2;
    vector_list.push_back(10);
    vector_list.push_back(20);
    vector_list2.push_back(10);
    vector_list2.push_back(20);
    State state;
    state.SetAvoidingObsIds(vector_list);

    ASSERT_EQ(vector_list2, state.GetAvoidingObsIds());
}

/**
 * @brief Test State::SetAvoidingObsIds(InputIt first, InputIt last) and State::GetAvoidingObsIds()
 */
TEST(State, SetAndGetAvoidingObsIdsWithRange_1)
{
    State::VectorType vector_list;
    vector_list.push_back(10);
    vector_list.push_back(20);
    vector_list.push_back(30);
    State state;
    state.SetAvoidingObsIds<State::VectorType::iterator>(vector_list.begin(), vector_list.begin() + 3);

    ASSERT_EQ(vector_list, state.GetAvoidingObsIds());
}

/**
 * @brief Test State::SetAvoidingObsIds(InputIt first, InputIt last) and State::GetAvoidingObsIds()
 * exception
 */
TEST(State, SetAndGetCutAvoidingObsIdsWithRange_2)
{
    holo::container::details::FixedSizeVector<uint32_t, 15> vector_list = {1, 2,  3,  4,  5,  6,  7, 8,
                                                                           9, 10, 11, 12, 13, 14, 15};
    State                                                   state;
    EXPECT_THROW(state.SetAvoidingObsIds(vector_list.begin(), vector_list.end()), std::bad_alloc);
}

/**
 * @brief Test State::SetAvoidingObsIds with initializer_list and State::GetAvoidingObsIds()
 */
TEST(State, SetAndGetAvoidingObsIdsWithInitializerList)
{
    State state;
    state.SetAvoidingObsIds({1, 2, 3});

    ASSERT_EQ(1, state.GetAvoidingObsIds().at(0));
    ASSERT_EQ(2, state.GetAvoidingObsIds().at(1));
    ASSERT_EQ(3, state.GetAvoidingObsIds().at(2));
    EXPECT_THROW(state.SetAvoidingObsIds({1, 2, 3, 4, 5, 6, 7, 8, 9}), std::bad_alloc);
}

/**
 * @brief Test State::SetLaneChangeObsIds(VectorType const& list) and State::GetLaneChangeObsIds()
 */
TEST(State, SetAndGetLaneChangeObsIdsWithCopyConstruct)
{
    State::VectorType vector_list;
    vector_list.push_back(10);
    vector_list.push_back(20);
    vector_list.push_back(30);
    State state;
    state.SetLaneChangeObsIds(vector_list);

    ASSERT_EQ(vector_list, state.GetLaneChangeObsIds());
}

/**
 * @brief Test State::SetLaneChangeObsIds(VectorType&& list) and State::GetLaneChangeObsIds()
 */
TEST(State, SetAndGetLaneChangeObsIdsWithMoveConstruct)
{
    State::VectorType vector_list;
    State::VectorType vector_list2;
    vector_list.push_back(10);
    vector_list.push_back(20);
    vector_list2.push_back(10);
    vector_list2.push_back(20);
    State state;
    state.SetLaneChangeObsIds(std::move(vector_list));

    ASSERT_EQ(vector_list2, state.GetLaneChangeObsIds());
}

/**
 * @brief Test State::SetLaneChangeObsIds(InputIt first, InputIt last) and State::GetLaneChangeObsIds()
 */
TEST(State, SetAndGetLaneChangeObsIdsWithRange_1)
{
    State::VectorType vector_list;
    vector_list.push_back(10);
    vector_list.push_back(20);
    vector_list.push_back(30);
    State state;
    state.SetLaneChangeObsIds<State::VectorType::iterator>(vector_list.begin(), vector_list.begin() + 3);

    ASSERT_EQ(vector_list, state.GetLaneChangeObsIds());
}

/**
 * @brief Test State::SetLaneChangeObsIds(InputIt first, InputIt last) and State::GetLaneChangeObsIds()
 * exception
 */
TEST(State, SetAndGetLaneChangeObsIdsWithRange_2)
{
    holo::container::details::FixedSizeVector<uint32_t, 15> vector_list = {1, 2,  3,  4,  5,  6,  7, 8,
                                                                           9, 10, 11, 12, 13, 14, 15};
    State                                                   state;
    EXPECT_THROW(state.SetLaneChangeObsIds(vector_list.begin(), vector_list.end()), std::bad_alloc);
}

/**
 * @brief Test State::SetLaneChangeObsIds with initializer_list and State::GetLaneChangeObsIds()
 */
TEST(State, SetAndGetLaneChangeObsIdsWithInitializerList)
{
    State state;
    state.SetLaneChangeObsIds({1, 2, 3});

    ASSERT_EQ(1, state.GetLaneChangeObsIds().at(0));
    ASSERT_EQ(2, state.GetLaneChangeObsIds().at(1));
    ASSERT_EQ(3, state.GetLaneChangeObsIds().at(2));
    EXPECT_THROW(state.SetLaneChangeObsIds({1, 2, 3, 4, 5, 6, 7, 8, 9}), std::bad_alloc);
}

/**
 * @brief Test State::GetSerializedSize
 */
TEST(State, GetSerializedSize)
{
    State state;
    ASSERT_EQ(24, state.GetSerializedSize<4U>());
    ASSERT_EQ(40, state.GetSerializedSize<8U>());
}

/**
 * @brief Test State::Serialize and Deserialize
 */
TEST(State, SerializeAndDeserialize)
{
    State::VectorType vector_list;
    vector_list.push_back(10);
    vector_list.push_back(20);

    State state1;
    state1.SetMainState(State::MainState::ACC);
    state1.SetLateralState(State::LateralState::FOLLOW_LANE);
    state1.SetLongitudinalState(State::LongitudinalState::BRAKE);
    state1.SetFunctionAlarm(State::MainState::ASSIST, 10);
    state1.SetFunctionAlarm(State::MainState::ASSIST_HOLD, 11);
    state1.SetFollowingObsIds(vector_list);
    vector_list[0U] = 11U;
    state1.SetCutInObsIds(vector_list);
    vector_list[0U] = 12U;
    state1.SetCutInObsIds(vector_list);
    vector_list[0U] = 13U;
    state1.SetAvoidingObsIds(vector_list);
    vector_list[0U] = 14U;
    state1.SetLaneChangeObsIds(vector_list);

    uint8_t buffer[1024];
    holo::serialization::Serializer<>          serializer(buffer, 1024);
    serializer << state1;

    ASSERT_EQ(serializer.GetSize(), state1.GetSerializedSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    State                       state2;
    deserializer >> state2;

    ASSERT_EQ(state1.GetMainState(), state2.GetMainState());
    ASSERT_EQ(state1.GetLateralState(), state2.GetLateralState());
    ASSERT_EQ(state1.GetLongitudinalState(), state2.GetLongitudinalState());
    ASSERT_EQ(state1.GetFunctionStateSize(), state2.GetFunctionStateSize());
    ASSERT_EQ(state1.GetFunctionStateCapacity(), state2.GetFunctionStateCapacity());
    ASSERT_EQ(state1.GetFollowingObsIds(), state2.GetFollowingObsIds());
    ASSERT_EQ(state1.GetCutInObsIds(), state2.GetCutInObsIds());
    ASSERT_EQ(state1.GetAvoidingObsIds(), state2.GetAvoidingObsIds());
    ASSERT_EQ(state1.GetLaneChangeObsIds(), state2.GetLaneChangeObsIds());

    for (size_t i = 0; i < state1.GetFunctionStateSize(); i++)
    {
        std::pair<State::MainState, Alarm> data(static_cast<State::MainState>(i + 3), Alarm(10 + i));
        ASSERT_EQ(data.first, state2.GetFunctionState(i).first);
        ASSERT_EQ(data.second, state2.GetFunctionState(i).second);
    }
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
