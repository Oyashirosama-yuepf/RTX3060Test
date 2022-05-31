/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_planning_state.cpp
 * @brief Unit test for planning state object.
 * @author Zhang Yuchen(zhangyuchen@holomatic.com)
 * @date 2020-05-09
 */

#include <gtest/gtest.h>
#include <holo/planning/planning_state.h>

using namespace holo;
using namespace holo::planning;

enum class Value : uint32_t
{
    ACC      = 0,
    ICA      = 1,
    ICP      = 2,
    TJA      = 3,
    TJP      = 4,
    ALCL     = 5,
    ALCR     = 6,
    LC       = 7,
    HSA      = 8,
    EMSS     = 9,
    INACTIVE = 10,
};

enum class Error : uint32_t
{
    ODO_ERROR = 0x01,
    OBS_ERROR = 0x02,
    LANE_ERROR = 0x04,
};

TEST(PlanningState, default_constructor)
{
    PlanningState state;

    ASSERT_EQ(state.GetModeNum(), 0);
    ASSERT_EQ(state.GetCurrentState(), 0);

    const uint32_t mode_num = 10;
    state.SetModeNum(mode_num);
    ASSERT_EQ(state.GetModeNum(), mode_num);
}

TEST(PlanningState, construct_with_mode_num)
{
    const uint32_t mode_num = 10;
    PlanningState state(mode_num);

    // mode num
    ASSERT_EQ(state.GetModeNum(), mode_num);

    // current state
    ASSERT_EQ(state.GetCurrentState(), 0);

    // activatable mode
    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::ACC)), false);
    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::ICA)), false);
    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::ICP)), false);
    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::TJA)), false);
    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::TJP)), false);
    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::ALCL)), false);
    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::ALCR)), false);
    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::LC)), false);
    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::HSA)), false);
    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::EMSS)), false);

    // error code
    ASSERT_EQ(state.GetErrorCode(static_cast<uint32_t>(Value::ACC)), 0);
    ASSERT_EQ(state.GetErrorCode(static_cast<uint32_t>(Value::ICA)), 0);
    ASSERT_EQ(state.GetErrorCode(static_cast<uint32_t>(Value::ICP)), 0);
    ASSERT_EQ(state.GetErrorCode(static_cast<uint32_t>(Value::TJA)), 0);
    ASSERT_EQ(state.GetErrorCode(static_cast<uint32_t>(Value::TJP)), 0);
    ASSERT_EQ(state.GetErrorCode(static_cast<uint32_t>(Value::ALCL)), 0);
    ASSERT_EQ(state.GetErrorCode(static_cast<uint32_t>(Value::ALCR)), 0);
    ASSERT_EQ(state.GetErrorCode(static_cast<uint32_t>(Value::LC)), 0);
    ASSERT_EQ(state.GetErrorCode(static_cast<uint32_t>(Value::HSA)), 0);
    ASSERT_EQ(state.GetErrorCode(static_cast<uint32_t>(Value::EMSS)), 0);

    //following obs ids
    ASSERT_EQ(state.GetFollowingObsIds().empty(), true);

    // cut in obs ids
    ASSERT_EQ(state.GetCutInObsIds().empty(), true);

    // cut in obs ids
    ASSERT_EQ(state.GetAvoidingObsIds().empty(), true);

    // cut in obs ids
    ASSERT_EQ(state.GetLaneChangeObsIds().empty(), true);
}

TEST(PlanningState, current_state)
{
    const uint32_t mode_num = 10;
    PlanningState state(mode_num);

    const uint32_t curr_state = 5;
    state.SetCurrentState(curr_state);

    ASSERT_EQ(state.GetCurrentState(), curr_state);
}

TEST(PlanningState, activatable_mode)
{
    const uint32_t mode_num = 10;
    PlanningState state(mode_num);

    uint32_t mode = 0;
    mode |= 1 << static_cast<uint32_t>(Value::ACC);
    mode |= 1 << static_cast<uint32_t>(Value::ALCR);

    state.SetActivatableMode(mode);

    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::ACC)), true);
    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::ALCR)), true);
    ASSERT_EQ(state.IsActivatable(static_cast<uint32_t>(Value::ICP)), false);
}

TEST(PlanningState, error_code)
{
    const uint32_t mode_num = 10;
    PlanningState state(mode_num);

    uint32_t error = 0;
    error |= static_cast<uint32_t>(Error::ODO_ERROR);
    error |= static_cast<uint32_t>(Error::LANE_ERROR);

    state.SetErrorCode(error, static_cast<uint32_t>(Value::ACC));

    ASSERT_EQ(state.GetErrorCode(static_cast<uint32_t>(Value::ACC)), error);
    ASSERT_EQ(state.GetErrorCode(static_cast<uint32_t>(Value::ICA)), 0);
}

TEST(PlanningState, following_obs_ids)
{
    const uint32_t mode_num = 10;
    PlanningState state(mode_num);

    std::vector<uint32_t> ids = {12, 24};

    state.SetFollowingObsIds(ids);

    auto const& following_obs_ids = state.GetFollowingObsIds();

    ASSERT_EQ(following_obs_ids.size(), 2);
    ASSERT_EQ(following_obs_ids[0], ids[0]);
    ASSERT_EQ(following_obs_ids[1], ids[1]);

    state.GetFollowingObsIds().push_back(33);
    ASSERT_EQ(state.GetFollowingObsIds().size(), 3);
    ASSERT_EQ(state.GetFollowingObsIds()[2], 33);
}

TEST(PlanningState, cut_in_obs_ids)
{
    const uint32_t mode_num = 10;
    PlanningState state(mode_num);

    std::vector<uint32_t> ids = {12, 24};

    state.SetFollowingObsIds(ids);

    auto const& cut_in_obs_ids = state.GetFollowingObsIds();

    ASSERT_EQ(cut_in_obs_ids.size(), 2);
    ASSERT_EQ(cut_in_obs_ids[0], ids[0]);
    ASSERT_EQ(cut_in_obs_ids[1], ids[1]);

    state.GetFollowingObsIds().push_back(33);
    ASSERT_EQ(state.GetFollowingObsIds().size(), 3);
    ASSERT_EQ(state.GetFollowingObsIds()[2], 33);
}

TEST(PlanningState, avoiding_obs_ids)
{
    const uint32_t mode_num = 10;
    PlanningState state(mode_num);

    std::vector<uint32_t> ids = {12, 24};

    state.SetFollowingObsIds(ids);

    auto const& avoiding_obs_ids = state.GetFollowingObsIds();

    ASSERT_EQ(avoiding_obs_ids.size(), 2);
    ASSERT_EQ(avoiding_obs_ids[0], ids[0]);
    ASSERT_EQ(avoiding_obs_ids[1], ids[1]);

    state.GetFollowingObsIds().push_back(33);
    ASSERT_EQ(state.GetFollowingObsIds().size(), 3);
    ASSERT_EQ(state.GetFollowingObsIds()[2], 33);
}

TEST(PlanningState, lane_change_obs_ids)
{
    const uint32_t mode_num = 10;
    PlanningState state(mode_num);

    std::vector<uint32_t> ids = {12, 24};

    state.SetFollowingObsIds(ids);

    auto const& lane_change_obs_ids = state.GetFollowingObsIds();

    ASSERT_EQ(lane_change_obs_ids.size(), 2);
    ASSERT_EQ(lane_change_obs_ids[0], ids[0]);
    ASSERT_EQ(lane_change_obs_ids[1], ids[1]);

    state.GetFollowingObsIds().push_back(33);
    ASSERT_EQ(state.GetFollowingObsIds().size(), 3);
    ASSERT_EQ(state.GetFollowingObsIds()[2], 33);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
