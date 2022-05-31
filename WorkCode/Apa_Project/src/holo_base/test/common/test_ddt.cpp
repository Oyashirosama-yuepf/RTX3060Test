/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_ddt.cpp
 * @brief Unit test for odm related types.
 * @author zhouhuishuang(zhouhuishuang@holomatic.com)
 * @date 2020-11-16
 */

#include <gtest/gtest.h>
#include <holo/common/ddt.h>

using holo::common::DdtState;
using holo::common::DdtStates;
using holo::common::Timestamp;

/**
 * @brief Test DdtStates::DdtStates()
 */
TEST(DdtStates, DefaultConstructor)
{
    DdtStates<10> ddt;
    ASSERT_EQ(ddt.size(), 0);
}

/**
 * @brief Test DdtStates::GetTimestamp and DdtStates::SetTimestamp
 */
TEST(DdtStates, GetAndSetTimestamp)
{
    DdtStates<10> ddt;
    Timestamp     timestamp(50U, 30U);
    ddt.SetTimestamp(timestamp);
    ASSERT_EQ(timestamp, ddt.GetTimestamp());
}

/**
 * @brief Test DdtStates::[]operator overloading
 */
TEST(DdtStates, DdtQuery_1)
{
    DdtStates<10> ddt;
    ddt[3].SetPredictedDistance(10);
    ddt[4].SetPredictedDistance(10);
    ASSERT_EQ(10, ddt[3].GetPredictedDistance());
}

/**
 * @brief Test DdtStates::[]operator overloading boundary value
 */
TEST(DdtStates, DdtQuery_2)
{
    DdtStates<10> ddt;
    for (int i = 1; i <= 10; i++)
    {
        ddt[i].SetPredictedDistance(10);
    }
    EXPECT_THROW(ddt[20], std::bad_alloc);
}

/**
 * @brief Test DdtStates::at()
 */
TEST(DdtStates, DdtQueryWithAt_1)
{
    DdtStates<10> ddt;
    ddt[3].SetPredictedDistance(10);
    ASSERT_EQ(10, ddt.at(3).GetPredictedDistance());
}

/**
 * @brief Test DdtStates::at()
 */
TEST(DdtStates, DdtQueryWithAt_2)
{
    DdtStates<10> ddt;
    EXPECT_THROW(ddt.at(5), std::out_of_range);
}

/**
 * @brief Test DdtStates:: size()
 */
TEST(DdtStates, GetSize_1)
{
    DdtStates<10> ddt;
    ddt[3].SetPredictedDistance(10);
    ddt[4].SetPredictedDistance(10);
    ASSERT_EQ(2, ddt.size());
}

/**
 * @brief Test DdtStates:: size()
 */
TEST(DdtStates, GetSize_2)
{
    DdtStates<10> ddt;
    for (int i = 1; i <= 10; i++)
    {
        ddt[i].SetPredictedDistance(10);
    }
    ddt.RemoveDdtState(5);
    ASSERT_EQ(9, ddt.size());
}

/**
 * @brief Test DdtStates::HasDdtState()
 */
TEST(DdtStates, HasDdtState_1)
{
    DdtStates<10> ddt;
    ddt[3].SetPredictedDistance(10);
    ASSERT_EQ(true, ddt.HasDdtState(3));
}

/**
 * @brief Test DdtStates::HasDdtState()
 */
TEST(DdtStates, HasDdtState_2)
{
    DdtStates<10> ddt;
    ddt[3].SetPredictedDistance(10);
    ASSERT_EQ(false, ddt.HasDdtState(5));
}

/**
 * @brief Test DdtStates::RemoveDdtState
 */
TEST(DdtStates, RemoveDdtState_1)
{
    DdtStates<10> ddt;
    ddt[1].SetPredictedDistance(10);
    ASSERT_EQ(true, ddt.RemoveDdtState(1));
}

/**
 * @brief Test DdtStates::RemoveDdtState
 */
TEST(DdtStates, RemoveDdtState_2)
{
    DdtStates<10> ddt;
    ddt[1].SetPredictedDistance(10);
    ASSERT_EQ(false, ddt.RemoveDdtState(3));
}

/**
 * @brief Test DdtStates::RemoveDdtState
 */
TEST(DdtStates, RemoveDdtState_3)
{
    DdtStates<10> ddt;
    for (int i = 1; i <= 10; i++)
    {
        ddt[i].SetPredictedDistance(10);
    }
    ddt.RemoveDdtState(5);
    ddt[20].SetPredictedDistance(50);
    ASSERT_EQ(50, ddt[20].GetPredictedDistance());
}

/**
 * @brief Test DdtStates::GetSerializedSize
 */
TEST(DdtStates, GetSerializedSize)
{
    DdtStates<3> ddt;

    ASSERT_EQ(8, ddt[2].GetSerializedSize<4U>());
    ASSERT_EQ(8, ddt[2].GetSerializedSize<8U>());
}

/**
 * @brief Test DdtStates::Serialize and Deserialize
 */
TEST(DdtStates, SerializeAndDeserialize)
{
    DdtStates<4> ddts, ddts2;
    Timestamp    timestamp(30U, 50U);
    ddts.SetTimestamp(timestamp);

    ddts[2].Enable();
    ddts[2].SetAlarm(135U);
    ddts[2].SetPredictedDistance(80);
    ddts[2].EnablePredictedDistance();
    ddts[2].DisablePredictedTime();

    ddts[5].Enable();
    ddts[5].SetAlarm(135U);
    ddts[5].SetPredictedDistance(100);
    ddts[5].EnablePredictedTime();
    ddts[5].DisablePredictedDistance();

    uint8_t buffer[128];
    holo::serialization::Serializer<>          serializer(buffer, 128);
    serializer << ddts;
    ASSERT_EQ(ddts.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> ddts2;

    ASSERT_EQ(2, ddts2.size());
    ASSERT_EQ(true, ddts2.HasDdtState(2));
    ASSERT_EQ(true, ddts2.HasDdtState(5));
    ASSERT_EQ(false, ddts2.HasDdtState(8));
    ASSERT_EQ(ddts.GetTimestamp(), ddts2.GetTimestamp());

    ASSERT_EQ(ddts[2].IsEnabled(), ddts2[2].IsEnabled());
    ASSERT_EQ(ddts[2].GetAlarm(), ddts2[2].GetAlarm());
    ASSERT_EQ(ddts[2].IsPredictedDistanceEnabled(), ddts2[2].IsPredictedDistanceEnabled());
    ASSERT_EQ(ddts[2].IsPredictedTimeEnabled(), ddts2[2].IsPredictedTimeEnabled());
    ASSERT_EQ(ddts[2].IsPredictedDistanceEnabled(), ddts2[2].IsPredictedDistanceEnabled());
    ASSERT_EQ(ddts[2].GetPredictedDistance(), ddts2[2].GetPredictedDistance());

    ASSERT_EQ(ddts[5].IsEnabled(), ddts2[5].IsEnabled());
    ASSERT_EQ(ddts[5].GetAlarm(), ddts2[5].GetAlarm());
    ASSERT_EQ(ddts[5].IsPredictedDistanceEnabled(), ddts2[5].IsPredictedDistanceEnabled());
    ASSERT_EQ(ddts[5].IsPredictedTimeEnabled(), ddts2[5].IsPredictedTimeEnabled());
    ASSERT_EQ(ddts[5].IsPredictedDistanceEnabled(), ddts2[5].IsPredictedDistanceEnabled());
    ASSERT_EQ(ddts[5].GetPredictedDistance(), ddts2[5].GetPredictedDistance());
}

/**
 * @brief Test DdtState::GetType()
 */
TEST(DdtState, GetType)
{
    DdtStates<10> ddt;
    ddt[5].Enable();
    ASSERT_EQ(5, ddt[5].GetType());
}

/**
 * @brief Test DdtState::Enable() and DdtState::IsEnabled()
 */
TEST(DdtState, EnableAndIsEnabled)
{
    DdtStates<10> ddt;
    ddt[5].Enable();
    ASSERT_EQ(true, ddt[5].IsEnabled());
}

/**
 * @brief Test DdtState::Disable() and DdtState::IsEnabled()
 */
TEST(DdtState, DisableAndIsEnabled)
{
    DdtStates<10> ddt;
    ddt[5].Disable();
    ASSERT_EQ(false, ddt[5].IsEnabled());
}

/**
 * @brief Test DdtState::EnablePredictedDistance() and DdtState::IsPredictedDistanceEnabled()
 */
TEST(DdtState, EnableAndIsPredictedDistanceEnabled)
{
    DdtStates<10> ddt;
    ddt[5].EnablePredictedDistance();
    ASSERT_EQ(true, ddt[5].IsPredictedDistanceEnabled());
}

/**
 * @brief Test DdtState::DisablePredictedDistance() and DdtState::IsPredictedDistanceEnabled()
 */
TEST(DdtState, DisableAndIsPredictedDistanceEnabled)
{
    DdtStates<10> ddt;
    ddt[5].DisablePredictedDistance();
    ASSERT_EQ(false, ddt[5].IsPredictedDistanceEnabled());
}

/**
 * @brief Test DdtState::EnablePredictedTime() and DdtState::IsPredictedTimeEnabled()
 */
TEST(DdtState, EnableAndIsPredictedTimeEnabled)
{
    DdtStates<10> ddt;
    ddt[5].EnablePredictedTime();
    ASSERT_EQ(true, ddt[5].IsPredictedTimeEnabled());
}

/**
 * @brief Test DdtState::DisablePredictedTime() and DdtState::IsPredictedTimeEnabled()
 */
TEST(DdtState, DisableAndIsPredictedTimeEnabled)
{
    DdtStates<10> ddt;
    ddt[5].DisablePredictedTime();
    ASSERT_EQ(false, ddt[5].IsPredictedTimeEnabled());
}

/**
 * @brief Test DdtState::SetAlarm(uint16_t alarm) and DdtState::GetAlarm()
 */
TEST(DdtState, SetAndGetAlarm)
{
    DdtStates<10> ddt;
    ddt[5].SetAlarm(135U);
    ASSERT_EQ(135U, ddt[5].GetAlarm());
}

/**
 * @brief Test DdtState::SetPredictedDistance(uint16_t) and DdtState::GetPredictedDistance()
 */
TEST(DdtState, SetAndGetPredictedDistance)
{
    DdtStates<10> ddt;
    ddt[5].SetPredictedDistance(50);
    ASSERT_EQ(50, ddt[5].GetPredictedDistance());
}

/**
 * @brief Test DdtState::SetPredictedTime(uint16_t) and DdtState::GetPredictedTime()
 */
TEST(DdtState, SetAndGetPredictedTime)
{
    DdtStates<10> ddt;
    ddt[5].SetPredictedTime(50);
    ASSERT_EQ(50, ddt[5].GetPredictedTime());
}

/**
 * @brief Test DdtState::GetSerializedSize
 */
TEST(DdtState, GetSerializedSize)
{
    DdtStates<3> ddt;
    ASSERT_EQ(12, ddt.GetSerializedSize<4U>());
    ASSERT_EQ(16, ddt.GetSerializedSize<8U>());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
