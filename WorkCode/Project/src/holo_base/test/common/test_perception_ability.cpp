/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_perception_ability.cpp
 * @brief This header file defines .
 * @author sunzhenqiang(sunzhenqiang@holomaitc.com)
 * @date "2020-04-22"
 */

#include <gtest/gtest.h>
#include <holo/common/perception_ability.h>

using PerceptionAbility = holo::common::PerceptionAbility;

TEST(PerceptionAbility, ConstructDefault)
{
    PerceptionAbility perception_ability;
    ASSERT_EQ(perception_ability.GetZoneAbility(), 0U);
}

TEST(PerceptionAbility, ConstructFromUint32)
{
    PerceptionAbility perception_ability(0U);
    ASSERT_EQ(perception_ability.GetZoneAbility(), 0U);
}

TEST(PerceptionAbility, ConstructFromParams)
{
    PerceptionAbility perception_ability(1U, 2U, 3U, 1U, 1U, 2U, 1U, 0U,
                                         0U);  // 0000 0000 0000 0000 00 01 10 01 01 11 10 01 -> 6521
    ASSERT_EQ(perception_ability.GetZoneAbility(), 6521U);
}

TEST(PerceptionAbility, AssignUint32)
{
    PerceptionAbility perception_ability;
    perception_ability = 6521U;
    ASSERT_EQ(perception_ability.GetZoneAbility(), 6521U);
}

TEST(PerceptionAbility, CastUint32)
{
    PerceptionAbility perception_ability(6521U);
    uint32_t          value = perception_ability;
    ASSERT_EQ(value, 6521U);
}

TEST(PerceptionAbility, merge)
{
    PerceptionAbility perception_ability;
    PerceptionAbility perception_ability_new(6521U);
    PerceptionAbility perception_ability_high(65535U);  // 65535->00000000000000001111111111111111
    ASSERT_EQ(perception_ability.Merge(perception_ability_new).GetZoneAbility(), 6521U);
    ASSERT_EQ(perception_ability_high.Merge(perception_ability_new).GetZoneAbility(), 65535U);
}

TEST(PerceptionAbility, Get)
{
    PerceptionAbility perception_ability;
    perception_ability = 6521U;
    ASSERT_EQ(perception_ability.GetZoneAbility(), 6521U);
    ASSERT_EQ(perception_ability.GetFrontFarZoneAbility(), PerceptionAbility::PerceptionAbilityLevel::LOW);
    ASSERT_EQ(perception_ability.GetFrontNearZoneAbility(), PerceptionAbility::PerceptionAbilityLevel::HIGH);
    ASSERT_EQ(perception_ability.GetFrontWideFarZoneAbility(), PerceptionAbility::PerceptionAbilityLevel::LOW);
    ASSERT_EQ(perception_ability.GetFrontWideNearZoneAbility(), PerceptionAbility::PerceptionAbilityLevel::LOW);
    ASSERT_EQ(perception_ability.GetFrontLeftZoneAbility(), PerceptionAbility::PerceptionAbilityLevel::LOW);
    ASSERT_EQ(perception_ability.GetFrontRightZoneAbility(), PerceptionAbility::PerceptionAbilityLevel::LOW);
    ASSERT_EQ(perception_ability.GetLeftZoneAbility(), PerceptionAbility::PerceptionAbilityLevel::LOW);
    ASSERT_EQ(perception_ability.GetRightZoneAbility(), PerceptionAbility::PerceptionAbilityLevel::NONE);
    ASSERT_EQ(perception_ability.GetLeftNearZoneAbility(), PerceptionAbility::PerceptionAbilityLevel::LOW);
    ASSERT_EQ(perception_ability.GetRightNearZoneAbility(), PerceptionAbility::PerceptionAbilityLevel::NONE);
}

TEST(PerceptionAbility, GetPerceptionAbility)
{
    PerceptionAbility perception_ability{6521U};  ///< 0000 0000 0000 0000 00 01 10 01 01 11 10 01 -> 6521
    ASSERT_EQ(perception_ability.GetPerceptionAbility(115.0f, 1.5f), PerceptionAbility::PerceptionAbilityLevel::LOW);
    ASSERT_EQ(perception_ability.GetPerceptionAbility(65.0f,  7.5f), PerceptionAbility::PerceptionAbilityLevel::MIDDLE);
    ASSERT_EQ(perception_ability.GetPerceptionAbility(9.8f,  -1.5f), PerceptionAbility::PerceptionAbilityLevel::HIGH);
    ASSERT_EQ(perception_ability.GetPerceptionAbility(65.0f, -7.5f), PerceptionAbility::PerceptionAbilityLevel::LOW);
    ASSERT_EQ(perception_ability.GetPerceptionAbility(5.6f,  11.8f), PerceptionAbility::PerceptionAbilityLevel::LOW);
    ASSERT_EQ(perception_ability.GetPerceptionAbility(5.6f, -11.5f), PerceptionAbility::PerceptionAbilityLevel::MIDDLE);
    ASSERT_EQ(perception_ability.GetPerceptionAbility(-93.4f, 1.2f), PerceptionAbility::PerceptionAbilityLevel::LOW);
    ASSERT_EQ(perception_ability.GetPerceptionAbility(-7.0f, -1.2f), PerceptionAbility::PerceptionAbilityLevel::NONE);
    ASSERT_EQ(perception_ability.GetPerceptionAbility(6.7f,   0.0f), PerceptionAbility::PerceptionAbilityLevel::NONE);

    ASSERT_THROW(perception_ability.GetPerceptionAbility(-110.0f,   0.0f), std::range_error);
    ASSERT_THROW(perception_ability.GetPerceptionAbility(220.0f,    0.0f), std::range_error);
    ASSERT_THROW(perception_ability.GetPerceptionAbility(158.0f,   17.8f), std::range_error);
    ASSERT_THROW(perception_ability.GetPerceptionAbility(158.0f,  -17.2f), std::range_error);
    ASSERT_THROW(perception_ability.GetPerceptionAbility(-180.0f, 250.0f), std::range_error);
}

TEST(PerceptionAbility, GetFrontWideFarZoneAbility)
{
    PerceptionAbility perception_ability(3U, 2U, 1U, 0U, 2U, 2U, 2U, 1U, 0U);
    auto level = perception_ability.GetFrontWideFarZoneAbility();
}

TEST(PerceptionAbility, GetFrontWideNearZoneAbility)
{
    PerceptionAbility perception_ability(3U, 2U, 1U, 0U, 2U, 2U, 2U, 1U, 0U);
    auto level = perception_ability.GetFrontWideNearZoneAbility();
}

TEST(PerceptionAbility, GetFrontLeftZoneAbility)
{
    PerceptionAbility perception_ability(3U, 2U, 1U, 0U, 2U, 2U, 2U, 1U, 0U);
    auto level = perception_ability.GetFrontLeftZoneAbility();
}

TEST(PerceptionAbility, GetFrontRightZoneAbility)
{
    PerceptionAbility perception_ability(3U, 2U, 1U, 0U, 2U, 2U, 2U, 1U, 0U);
    auto level = perception_ability.GetFrontRightZoneAbility();
}

TEST(PerceptionAbility, GetLeftZoneAbility)
{
    PerceptionAbility perception_ability(3U, 2U, 1U, 0U, 0U, 2U, 2U, 1U, 0U);
    auto level = perception_ability.GetLeftZoneAbility();

    PerceptionAbility perception_ability2(3U, 2U, 2U, 0U, 1U, 0U, 0U, 0U, 0U);
    auto level2 = perception_ability2.GetLeftZoneAbility();
}

TEST(PerceptionAbility, GetRightZoneAbility)
{
    PerceptionAbility perception_ability(3U, 2U, 1U, 0U, 2U, 2U, 2U, 1U, 0U);
    auto level = perception_ability.GetRightZoneAbility();

    PerceptionAbility perception_ability2(3U, 3U, 2U, 2U, 0U, 1U, 0U, 0U, 0U);
    auto level2 = perception_ability2.GetRightZoneAbility();
}

TEST(PerceptionAbility, GetLeftNearZoneAbility)
{
    PerceptionAbility perception_ability(3U, 2U, 1U, 0U, 2U, 2U, 2U, 1U, 0U);
    auto level = perception_ability.GetLeftNearZoneAbility();

    PerceptionAbility perception_ability2(3U, 2U, 1U, 0U, 1U, 0U, 0U, 0U, 0U);
    auto level2 = perception_ability2.GetLeftNearZoneAbility();
}

TEST(PerceptionAbility, GetRightNearZoneAbility)
{
    PerceptionAbility perception_ability(3U, 2U, 1U, 0U, 2U, 2U, 2U, 1U, 0U);
    auto level = perception_ability.GetRightNearZoneAbility();

    PerceptionAbility perception_ability2(3U, 2U, 3U, 2U, 0U, 1U, 0U, 0U, 0U);
    auto level2 = perception_ability2.GetRightNearZoneAbility();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
