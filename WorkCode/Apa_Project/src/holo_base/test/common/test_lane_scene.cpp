/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_lane_scene.cpp
 * @brief Unit test for lane scene object.
 * @author tanghui(tanghui@holomaitc.com)
 * @date "2020-04-30"
 */

#include <gtest/gtest.h>
#include <holo/common/lane_scene.h>

using LaneScene = holo::common::LaneScene;
using Timestamp = holo::common::Timestamp;

TEST(LaneScene, ConstructDefault)
{
    LaneScene lane_scene;
    ASSERT_EQ(lane_scene.GetTimestamp(), Timestamp(0U, 0U));
    ASSERT_EQ(lane_scene.GetCurrent(), LaneScene::Type::UNKNOWN);
    ASSERT_EQ(lane_scene.GetLeft(), LaneScene::Type::UNKNOWN);
    ASSERT_EQ(lane_scene.GetRight(), LaneScene::Type::UNKNOWN);
}

TEST(LaneScene, ConstructFromParams)
{
    LaneScene lane_scene(Timestamp(1U, 0U), 9u);
    ASSERT_EQ(lane_scene.GetTimestamp(), Timestamp(1U, 0U));
    ASSERT_EQ(lane_scene.GetCurrent(), LaneScene::Type::FINE);
    ASSERT_EQ(lane_scene.GetLeft(), LaneScene::Type::FINE);
    ASSERT_EQ(lane_scene.GetRight(), LaneScene::Type::UNKNOWN);
}

TEST(LaneScene, CopyConstructor)
{
    LaneScene lane_scene(Timestamp(1U, 0U), 9u);
    LaneScene lane_scene_other(lane_scene);
    ASSERT_EQ(lane_scene_other.GetTimestamp(), lane_scene.GetTimestamp());
    ASSERT_EQ(lane_scene_other.GetCurrent(), lane_scene.GetCurrent());
    ASSERT_EQ(lane_scene_other.GetLeft(), lane_scene.GetLeft());
    ASSERT_EQ(lane_scene_other.GetRight(), lane_scene.GetRight());
}

TEST(LaneScene, MoveConstructor)
{
    LaneScene lane_scene(Timestamp(1U, 0U), 9u);
    LaneScene lane_scene_other(std::move(lane_scene));
    ASSERT_EQ(lane_scene_other.GetTimestamp(), Timestamp(1U, 0U));
    ASSERT_EQ(lane_scene_other.GetCurrent(), LaneScene::Type::FINE);
    ASSERT_EQ(lane_scene_other.GetLeft(), LaneScene::Type::FINE);
    ASSERT_EQ(lane_scene_other.GetRight(), LaneScene::Type::UNKNOWN);
}

TEST(LaneScene, Assign)
{
    LaneScene lane_scene(Timestamp(1U, 0U), 9u);
    LaneScene lane_scene_other = lane_scene;
    ASSERT_EQ(lane_scene.GetTimestamp(), lane_scene_other.GetTimestamp());
    ASSERT_EQ(lane_scene.GetValue(), lane_scene_other.GetValue());
}

TEST(LaneScene, MoveAssign)
{
    LaneScene lane_scene(Timestamp(1U, 0U), 9u);
    LaneScene lane_scene_other = std::move(lane_scene);
    ASSERT_EQ(lane_scene_other.GetTimestamp(), Timestamp(1U, 0U));
    ASSERT_EQ(lane_scene_other.GetCurrent(), LaneScene::Type::FINE);
    ASSERT_EQ(lane_scene_other.GetLeft(), LaneScene::Type::FINE);
    ASSERT_EQ(lane_scene_other.GetRight(), LaneScene::Type::UNKNOWN);
}

TEST(LaneScene, SetGetValue)
{
    LaneScene lane_scene;
    ASSERT_EQ(lane_scene.GetValue(), 0u);
    lane_scene.SetValue(9u);
    ASSERT_EQ(lane_scene.GetValue(), 9u);
}

TEST(LaneScene, SetGetCurrent)
{
    LaneScene lane_scene;
    ASSERT_EQ(lane_scene.GetCurrent(), LaneScene::Type::UNKNOWN);
    lane_scene.SetCurrent(LaneScene::Type::SNOW);
    ASSERT_EQ(lane_scene.GetCurrent(), LaneScene::Type::SNOW);
}

TEST(LaneScene, SetGetLeft)
{
    LaneScene lane_scene;
    ASSERT_EQ(lane_scene.GetLeft(), LaneScene::Type::UNKNOWN);
    lane_scene.SetLeft(LaneScene::Type::SNOW);
    ASSERT_EQ(lane_scene.GetLeft(), LaneScene::Type::SNOW);
}

TEST(LaneScene, SetGetRight)
{
    LaneScene lane_scene;
    ASSERT_EQ(lane_scene.GetRight(), LaneScene::Type::UNKNOWN);
    lane_scene.SetRight(LaneScene::Type::SNOW);
    ASSERT_EQ(lane_scene.GetRight(), LaneScene::Type::SNOW);
}

TEST(LaneScene, SetGetTimeStamp)
{
    LaneScene lane_scene;
    ASSERT_EQ(lane_scene.GetTimestamp(), Timestamp(0U, 0U));
    lane_scene.SetTimestamp(Timestamp(1U, 1U));
    ASSERT_EQ(lane_scene.GetTimestamp(), Timestamp(1U, 1U));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
