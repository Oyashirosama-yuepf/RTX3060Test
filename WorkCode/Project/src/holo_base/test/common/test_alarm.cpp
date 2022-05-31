
/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_alarm.cpp
 * @brief unit test for alarm class
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-25
 */
#include <gtest/gtest.h>
#include <holo/common/alarm.h>

using Alarm = holo::common::Alarm;

/**
 * @brief Test Alarm() default constructor
 */
TEST(Alarm, DefaultConstructor)
{
    Alarm alarm;
    ASSERT_EQ(0U, static_cast<uint16_t>(alarm));
}

/**
 * @brief Test Alarm(UnderlyingType value)
 */
TEST(Alarm, ConstructorWithUnderlyingType)
{
    Alarm::UnderlyingType value = 0;
    value = static_cast<Alarm::UnderlyingType>(Alarm::Level::FATAL_1) << 13;
    value += 12U;
    Alarm alarm(value);
    ASSERT_EQ(value, static_cast<uint16_t>(alarm));
}

/**
 * @brief Test Alarm::operator=(UnderlyingType value)
 */
TEST(Alarm, EqualOperatorOverloading)
{
    Alarm::UnderlyingType value = 128U;
    Alarm alarm(value);
    Alarm alarm2;
    ASSERT_EQ(alarm, alarm2 = alarm);
}

/**
 * @brief Test Alarm::operator==(UnderlyingType lhs, Alarm rhs)
 */
TEST(Alarm, EqualOperatorWithUnderlyingTypeAndAlarm_1)
{
    Alarm::UnderlyingType value = 128U;
    Alarm alarm(value);
    ASSERT_TRUE(value == alarm);
}

/**
 * @brief Test Alarm::operator==(UnderlyingType lhs, Alarm rhs)
 */
TEST(Alarm, EqualOperatorWithUnderlyingTypeAndAlarm_2)
{
    Alarm::UnderlyingType value = 128U;
    Alarm alarm(value);
    value += 5;
    ASSERT_FALSE(value == alarm);
}

/**
 * @brief Test Alarm::operator==(UnderlyingType const& rhs)
 */
TEST(Alarm, EqualOperatorWithUnderlyingType_1)
{
    Alarm::UnderlyingType value = 128U;
    Alarm alarm(value);
    ASSERT_TRUE(alarm == value);
}

/**
 * @brief Test Alarm::operator==(UnderlyingType const& rhs)
 */
TEST(Alarm, EqualOperatorWithUnderlyingType_2)
{
    Alarm::UnderlyingType value = 128U;
    Alarm alarm(value);
    value += 5;
    ASSERT_FALSE(alarm == value);
}

/**
 * @brief Test Alarm::operator==(Alarm const& rhs)
 */
TEST(Alarm, EqualOperatorWithAlarm_1)
{
    Alarm::UnderlyingType value = 128U;
    Alarm alarm(value);
    Alarm alarm2 = alarm;
    ASSERT_TRUE(alarm == alarm2);
}

/**
 * @brief Test Alarm::operator==(Alarm const& rhs)
 */
TEST(Alarm, EqualOperatorWithAlarm_2)
{
    Alarm::UnderlyingType value = 128U;
    Alarm::UnderlyingType value2 = 100U;
    Alarm alarm(value);
    Alarm alarm2(value2);
    ASSERT_FALSE(alarm == alarm2);
}

/**
 * @brief Test Alarm::operator!=(UnderlyingType const& lhs, Alarm const& rhs)
 */
TEST(Alarm, InequalOperatorWithUnderlyingTypeAndAlarm_1)
{
    Alarm::UnderlyingType value = 128U;
    Alarm alarm(value);
    value += 5;
    ASSERT_TRUE(value != alarm);
}

/**
 * @brief Test Alarm::operator!=(UnderlyingType const& lhs, Alarm const& rhs)
 */
TEST(Alarm, InequalOperatorWithUnderlyingTypeAndAlarm_2)
{
    Alarm::UnderlyingType value = 128U;
    Alarm alarm(value);
    ASSERT_FALSE(value != alarm);
}

/**
 * @brief Test Alarm::operator!=(UnderlyingType const& rhs)
 */
TEST(Alarm, InequalOperatorWithUnderlyingType_1)
{
    Alarm::UnderlyingType value = 128U;
    Alarm alarm(value);
    value += 5;
    ASSERT_TRUE(alarm != value);
}

/**
 * @brief Test Alarm::operator!=(UnderlyingType const& rhs)
 */
TEST(Alarm, InequalOperatorWithUnderlyingType_2)
{
    Alarm::UnderlyingType value = 128U;
    Alarm alarm(value);
    ASSERT_FALSE(alarm != value);
}

/**
 * @brief Test Alarm::operator!=(Alarm const& rhs)
 */
TEST(Alarm, InequalOperatorWithAlarm_1)
{
    Alarm::UnderlyingType value = 128U;
    Alarm::UnderlyingType value2 = 120U;
    Alarm alarm(value);
    Alarm alarm2(value2);
    ASSERT_TRUE(alarm != alarm2);
}

/**
 * @brief Test Alarm::operator!=(Alarm const& rhs)
 */
TEST(Alarm, InequalOperatorWithAlarm_2)
{
    Alarm::UnderlyingType value = 128U;
    Alarm::UnderlyingType value2 = 120U;
    Alarm alarm(value);
    Alarm alarm2 = alarm;
    ASSERT_FALSE(alarm != alarm2);
}

/**
 * @brief Test Alarm::operator UnderlyingType()
 */
TEST(Alarm, OperatorUnderlyingType)
{
    Alarm::UnderlyingType value = 0;
    value = static_cast<Alarm::UnderlyingType>(Alarm::Level::FATAL_1) << 13;
    value += 12U;
    Alarm alarm(value);
    ASSERT_EQ(value, static_cast<uint16_t>(alarm));
}

/**
 * @brief Test Alarm::GetLevel()
 */
TEST(Alarm, GetLevel)
{
    Alarm::UnderlyingType value = 0;
    value = static_cast<Alarm::UnderlyingType>(Alarm::Level::FATAL_1) << 13;
    value += 12U;
    Alarm alarm(value);
    ASSERT_EQ(Alarm::Level::FATAL_1, alarm.GetLevel());
}

/**
 * @brief Test Alarm::GetSerializedSize
 */
TEST(Alarm, GetSerializedSize)
{
    Alarm alarm;
    ASSERT_EQ(2, alarm.GetSerializedSize<4U>());
    ASSERT_EQ(2, alarm.GetSerializedSize<8U>());
}

/**
 * @brief Test Alarm::Serialize and Deserialize
 */
TEST(Alarm, SerializeAndDeserialize)
{
    Alarm::UnderlyingType value = 0;
    value = static_cast<Alarm::UnderlyingType>(Alarm::Level::FATAL_1) << 13;
    value += 12U;
    Alarm alarm(value);

    uint8_t buffer[128];
    holo::serialization::Serializer<>          serializer(buffer, 128);
    serializer << alarm  << holo::serialization::align;

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    Alarm alarm2;
    deserializer >> alarm2 >> holo::serialization::align;

    ASSERT_EQ(alarm.GetLevel(), alarm2.GetLevel());
    ASSERT_EQ(alarm, alarm2);

}

TEST(Alarm, DefaultConstructor_1)
{
    Alarm alarm;
    ASSERT_EQ(0U, static_cast<uint16_t>(alarm));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
