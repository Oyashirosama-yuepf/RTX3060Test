/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_timestamp.cpp
 * @brief unit test for timestamp class
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-03
 */

#include <gtest/gtest.h>
#include <holo/common/timestamp.h>
#include <iostream>

using Duration          = holo::common::Duration;
using Timestamp         = holo::common::Timestamp;
using OverflowException = holo::common::OverflowException;
using float64_t         = holo::float64_t;

/**
 * @brief Test Timestamp()
 */
TEST(Timestamp, DefaultConstructor)
{
    Timestamp timestamp;
    ASSERT_EQ(0U, timestamp.GetSec());
    ASSERT_EQ(0U, timestamp.GetNsec());
}

/**
 * @brief Test Timestamp(uint32_t sec, uint32_t nsec) minimum value
 */
TEST(Timestamp, ConstructWithSecNsec_1)
{
    Timestamp timestamp(0U, 0U);
    ASSERT_EQ(0U, timestamp.GetSec());
    ASSERT_EQ(0U, timestamp.GetNsec());
}

/**
 * @brief Test Timestamp(uint32_t sec, uint32_t nsec) normal value
 */
TEST(Timestamp, ConstructWithSecNsec_2)
{
    Timestamp timestamp(1U, 100U);
    ASSERT_EQ(1U, timestamp.GetSec());
    ASSERT_EQ(100U, timestamp.GetNsec());
}

/**
 * @brief Test Timestamp(uint32_t sec, uint32_t nsec) boundary value
 */
TEST(Timestamp, ConstructWithSecNsec_3)
{
    Timestamp timestamp(1U, Timestamp::NSEC_PER_SEC);
    ASSERT_EQ(2U, timestamp.GetSec());
    ASSERT_EQ(0U, timestamp.GetNsec());
}

/**
 * @brief Test Timestamp(uint32_t sec, uint32_t nsec) boundary value overflow
 */
TEST(Timestamp, ConstructWithSecNsec_4)
{
    EXPECT_THROW(Timestamp timestamp(std::numeric_limits<uint32_t>::max(), Timestamp::NSEC_PER_SEC), OverflowException);
}

/**
 * @brief Test Timestamp(float64_t t) minimum value
 */
TEST(Timestamp, ConstructWithFloat64Sec_1)
{
    Timestamp timestamp(0.0f);
    ASSERT_EQ(0U, timestamp.GetSec());
    ASSERT_EQ(0U, timestamp.GetNsec());
}

/**
 * @brief Test Timestamp(float64_t t) normal value
 */
TEST(Timestamp, ConstructWithFloat64Sec_2)
{
    Timestamp timestamp(5U + (static_cast<float64_t>(6000U) / Timestamp::NSEC_PER_SEC));
    ASSERT_EQ(5U, timestamp.GetSec());
    ASSERT_EQ(6000U, timestamp.GetNsec());
}

/**
 * @brief Test Timestamp(float64_t t) boundary value overflow
 */
TEST(Timestamp, ConstructWithFloat64Sec_3)
{
    try
    {
        Timestamp timestamp(static_cast<float64_t>(Timestamp::TIMESTAMP_MAX_NSEC / Timestamp::NSEC_PER_SEC + 1U));
    }
    catch (OverflowException&)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception!";
    }
}

/**
 * @brief Test Timestamp(float64_t t) boundary value overflow
 */
TEST(Timestamp, ConstructWithFloat64Sec_4)
{
    float64_t value = 4294967295.999999;
    Timestamp timestamp(value);
    ASSERT_NEAR(1000, Timestamp::TIMESTAMP_MAX_NSEC, timestamp.ToNsec());
}

/**
 * @brief Test Timestamp(float64_t t) boundary value overflow
 */
TEST(Timestamp, ConstructWithFloat64Sec_5)
{
    try
    {
        Timestamp timestamp(std::numeric_limits<float64_t>::max());
    }
    catch (OverflowException&)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception!";
    }
}

/**
 * @brief Test Timestamp(uint64_t t) minimum value
 */
TEST(Timestamp, ConstructWithUint64Nsec_1)
{
    Timestamp timestamp(static_cast<uint64_t>(0U));
    ASSERT_EQ(0U, timestamp.GetSec());
    ASSERT_EQ(0U, timestamp.GetNsec());
}

/**
 * @brief Test Timestamp(uint64_t t) normal value
 */
TEST(Timestamp, ConstructWithUint64Nsec_2)
{
    Timestamp timestamp(static_cast<uint64_t>(Timestamp::NSEC_PER_SEC) * 200U + 8000U);
    ASSERT_EQ(200U, timestamp.GetSec());
    ASSERT_EQ(8000U, timestamp.GetNsec());
}

/**
 * @brief Test Timestamp(uint64_t t) boundary value
 */
TEST(Timestamp, ConstructWithUint64Nsec_3)
{
    Timestamp timestamp(static_cast<uint64_t>(Timestamp::TIMESTAMP_MAX_NSEC));
    ASSERT_EQ(std::numeric_limits<uint32_t>::max(), timestamp.GetSec());
    ASSERT_EQ(Timestamp::NSEC_PER_SEC - 1, timestamp.GetNsec());
}

/**
 * @brief Test Timestamp(uint64_t t) boundary value overflow
 */
TEST(Timestamp, ConstructWithUint64Nsec_4)
{
    EXPECT_THROW(Timestamp timestamp(static_cast<uint64_t>(Timestamp::TIMESTAMP_MAX_NSEC + 1)), OverflowException);
}

/**
 * @brief Test Timestamp::operator+(Duration const& rhs) normal value
 */
TEST(Timestamp, AdditionOperatorDuration_1)
{
    Timestamp const lhs(2U, 2U);
    Duration const  rhs(5U, 5U);
    Timestamp const expected_timestamp(7U, 7U);
    ASSERT_EQ(expected_timestamp, lhs + rhs);
}

/**
 * @brief Test Timestamp::operator+(Duration const& rhs) normal value
 */
TEST(Timestamp, AdditionOperatorDuration_2)
{
    Timestamp const lhs(2U, 2U);
    Duration const  rhs(-1U, -1U);
    Timestamp const expected_timestamp(1U, 1U);
    ASSERT_EQ(expected_timestamp, lhs + rhs);
}

/**
 * @brief Test Timestamp::operator+(Duration const& rhs) wrong value overflow
 */
TEST(Timestamp, AdditionOperatorDuration_3)
{
    Timestamp const lhs(2U, 2U);
    Duration const  rhs(-5U, -5U);
    EXPECT_THROW(lhs + rhs, OverflowException);
}

/**
 * @brief Test Timestamp::operator-(Timestamp const& rhs) normal value
 */
TEST(Timestamp, SubtractOperatorTimestamp_1)
{
    Timestamp const lhs(2U, 2U);
    Timestamp const rhs(1U, 1U);
    Duration const  expected_duration(1U, 1U);
    ASSERT_EQ(expected_duration, lhs - rhs);
}

/**
 * @brief Test Timestamp::operator-(Timestamp const& rhs) normal value
 */
TEST(Timestamp, SubtractOperatorTimestamp_2)
{
    Timestamp const lhs(2U, 2U);
    Timestamp const rhs(5U, 5U);
    Duration const  expected_duration(-3U, -3U);
    ASSERT_EQ(expected_duration, lhs - rhs);
}

/**
 * @brief Test Timestamp::operator-(Duration const& rhs) normal value
 */
TEST(Timestamp, SubtractOperatorDuration_1)
{
    Timestamp const lhs(2U, 2U);
    Duration const  rhs(1U, 1U);
    Timestamp const expected_timestamp(1U, 1U);
    ASSERT_EQ(expected_timestamp, (lhs - rhs));
}

/**
 * @brief Test Timestamp::operator-(Duration const& rhs) wrong value overflow
 */
TEST(Timestamp, SubtractOperatorDuration_2)
{
    Timestamp const lhs(2U, 2U);
    Duration const  rhs(5U, 5U);
    EXPECT_THROW(lhs - rhs, OverflowException);
}

/**
 * @brief Test Timestamp::operator-(Duration const& rhs) normal value
 */
TEST(Timestamp, SubtractOperatorDuration_3)
{
    Timestamp const lhs(2U, 2U);
    Duration const  rhs(-1U, -1U);
    Timestamp const expected_timestamp(3U, 3U);
    ASSERT_EQ(expected_timestamp, (lhs - rhs));
}

/**
 * @brief Test Timestamp::operator+=(Duration const& rhs) normal value
 */
TEST(Timestamp, AdditionEqualOperatorDuration_1)
{
    Timestamp       lhs(2U, 2U);
    Duration const  rhs(1, 1);
    Timestamp const expected_timestamp(3U, 3U);
    lhs += rhs;
    ASSERT_EQ(expected_timestamp, lhs);
}

/**
 * @brief Test Timestamp::operator+=(Duration const& rhs) normal value
 */
TEST(Timestamp, AdditionEqualOperatorDuration_2)
{
    Timestamp       lhs(2U, 2U);
    Duration const  rhs(-1, -1);
    Timestamp const expected_timestamp(1U, 1U);
    lhs += rhs;
    ASSERT_EQ(expected_timestamp, lhs);
}

/**
 * @brief Test Timestamp::operator+=(Duration const& rhs) wrong value overflow
 */
TEST(Timestamp, AdditionEqualOperatorDuration_3)
{
    Timestamp      lhs(2U, 2U);
    Duration const rhs(-3, -3);
    EXPECT_THROW(lhs += rhs, OverflowException);
}

/**
 * @brief Test Timestamp::operator-=(Duration const& rhs) normal value
 */
TEST(Timestamp, SubtractEqualOperatorDuration_1)
{
    Timestamp       lhs(2U, 2U);
    Duration const  rhs(1, 1);
    Timestamp const expected_timestamp(1U, 1U);
    lhs -= rhs;
    ASSERT_EQ(expected_timestamp, lhs);
}

/**
 * @brief Test Timestamp::operator-=(Duration const& rhs) wrong value overflow
 */
TEST(Timestamp, SubtractEqualOperatorDuration_2)
{
    Timestamp      lhs(2U, 2U);
    Duration const rhs(5, 5);
    EXPECT_THROW(lhs -= rhs, OverflowException);
}

/**
 * @brief Test Timestamp::operator-=(Duration const& rhs) normal value
 */
TEST(Timestamp, SubtractEqualOperatorDuration_3)
{
    Timestamp       lhs(2U, 2U);
    Duration const  rhs(-1, -1);
    Timestamp const expected_timestamp(3U, 3U);
    lhs -= rhs;
    ASSERT_EQ(expected_timestamp, lhs);
}

/**
 * @brief Test Timestamp::operator==(Timestamp const& rhs) normal value
 */
TEST(Timestamp, EqualOperatorTimestamp_1)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 700U);
    ASSERT_TRUE(lhs_timestamp == rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator==(Timestamp const& rhs) normal value
 */
TEST(Timestamp, EqualOperatorTimestamp_2)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 350U);
    ASSERT_FALSE(lhs_timestamp == rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator!=(Timestamp const& rhs) normal value
 */
TEST(Timestamp, InequalOperatorTimestamp_1)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 500U);
    ASSERT_TRUE(lhs_timestamp != rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator!=(Timestamp const& rhs) normal value
 */
TEST(Timestamp, InequalOperatorTimestamp_2)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 700U);
    ASSERT_FALSE(lhs_timestamp != rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator>(Timestamp const& rhs) normal value
 */
TEST(Timestamp, GreaterThanOperatorTimestamp_1)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 700U);
    ASSERT_FALSE(lhs_timestamp > rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator>(Timestamp const& rhs) normal value
 */
TEST(Timestamp, GreaterThanOperatorTimestamp_2)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 350U);
    ASSERT_TRUE(lhs_timestamp > rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator>(Timestamp const& rhs) normal value
 */
TEST(Timestamp, GreaterThanOperatorTimestamp_3)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 850U);
    ASSERT_FALSE(lhs_timestamp > rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator<(Timestamp const& rhs) normal value
 */
TEST(Timestamp, LessThanOperatorTimestamp_1)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 700U);
    ASSERT_FALSE(lhs_timestamp < rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator<(Timestamp const& rhs) normal value
 */
TEST(Timestamp, LessThanOperatorTimestamp_2)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 850U);
    ASSERT_TRUE(lhs_timestamp < rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator<(Timestamp const& rhs) normal value
 */
TEST(Timestamp, LessThanOperatorTimestamp_3)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 500U);
    ASSERT_FALSE(lhs_timestamp < rhs_timestamp);
}

/**
 * @brief  Test Timestamp::operator>=(Timestamp const& rhs) normal value
 */
TEST(Timestamp, GreaterThanEqualOperatorTimestamp_1)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 700U);
    ASSERT_TRUE(lhs_timestamp >= rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator>=(Timestamp const& rhs) normal value
 */
TEST(Timestamp, GreaterThanEqualOperatorTimestamp_2)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 500U);
    ASSERT_TRUE(lhs_timestamp >= rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator>=(Timestamp const& rhs) normal value
 */
TEST(Timestamp, GreaterThanEqualOperatorTimestamp_3)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 800U);
    ASSERT_FALSE(lhs_timestamp >= rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator<=(Timestamp const& rhs) normal value
 */
TEST(Timestamp, LessThanEqualOperatorTimestamp_1)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 700U);
    ASSERT_TRUE(lhs_timestamp <= rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator<=(Timestamp const& rhs) normal value
 */
TEST(Timestamp, LessThanEqualOperatorTimestamp_2)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 500U);
    ASSERT_FALSE(lhs_timestamp <= rhs_timestamp);
}

/**
 * @brief Test Timestamp::operator<=(Timestamp const& rhs) normal value
 */
TEST(Timestamp, LessThanEqualOperatorTimestamp_3)
{
    Timestamp const lhs_timestamp(2U, 700U);
    Timestamp const rhs_timestamp(2U, 900U);
    ASSERT_TRUE(lhs_timestamp <= rhs_timestamp);
}

/**
 * @brief Test Timestamp::ToSec() normal value
 */
TEST(Timestamp, ToSec)
{
    Timestamp timestamp(2U, 600000000U);
    ASSERT_EQ(2.6, timestamp.ToSec());
}

/**
 * @brief Test Timestamp::ToNsec() normal value
 */
TEST(Timestamp, ToNsec)
{
    Timestamp timestamp(2U, 600U);
    ASSERT_EQ(2U * Timestamp::NSEC_PER_SEC + 600U, timestamp.ToNsec());
}

/**
 * @brief Test Timestamp::IsZero() normal value
 */
TEST(Timestamp, IsZero_1)
{
    Timestamp timestamp(static_cast<uint64_t>(0));
    ASSERT_TRUE(timestamp.IsZero());
}

/**
 * @brief Test Timestamp::IsZero() normal value
 */
TEST(Timestamp, IsZero_2)
{
    Timestamp timestamp(static_cast<uint64_t>(100));
    ASSERT_FALSE(timestamp.IsZero());
}

/**
 * @brief Test Timestamp::IsEqual(Timestamp const& rhs, uint32_t tolerance_nsec = 0) normal value
 */
TEST(Timestamp, IsEqual_1)
{
    Timestamp lhs(4U, 700U);
    Timestamp rhs(4U, 500U);
    ASSERT_TRUE(lhs.IsEqual(rhs, 300U));
}

/**
 * @brief Test Timestamp::IsEqual(Timestamp const& rhs, uint32_t tolerance_nsec = 0) normal value
 */
TEST(Timestamp, IsEqual_2)
{
    Timestamp lhs(4U, 700U);
    Timestamp rhs(4U, 400U);
    ASSERT_TRUE(lhs.IsEqual(rhs, 300U));
}

/**
 * @brief Test Timestamp::IsEqual(Timestamp const& rhs, uint32_t tolerance_nsec = 0) normal value
 */
TEST(Timestamp, IsEqual_3)
{
    Timestamp lhs(4U, 700U);
    Timestamp rhs(4U, 100U);
    ASSERT_FALSE(lhs.IsEqual(rhs, 300U));
}

/**
 * @brief Test Timestamp::GetSec() normal value
 */
TEST(Timestamp, GetSec)
{
    Timestamp timestamp(5U, 30U);
    ASSERT_EQ(5U, timestamp.GetSec());
}

/**
 * @brief Test Timestamp::GetNsec() normal value
 */
TEST(Timestamp, GetNsec)
{
    Timestamp timestamp(5U, 30U);
    ASSERT_EQ(30U, timestamp.GetNsec());
}

/**
 * @brief Test Timestamp::SetSec(uint32_t const seconds) normal value
 */
TEST(Timestamp, SetSec_1)
{
    Timestamp timestamp;
    timestamp.SetSec(50U);
    ASSERT_EQ(50U, timestamp.GetSec());
}

/**
 * @brief Test Timestamp::SetSec(uint32_t const seconds) boundary value
 */
TEST(Timestamp, SetSec_2)
{
    Timestamp timestamp;
    timestamp.SetSec(std::numeric_limits<uint32_t>::max());
    ASSERT_EQ(std::numeric_limits<uint32_t>::max(), timestamp.GetSec());
}

/**
 * @brief Test Timestamp::SetNsec(uint32_t const nseconds) normal value
 */
TEST(Timestamp, SetNsec_1)
{
    Timestamp timestamp;
    timestamp.SetNsec(50U);
    ASSERT_EQ(50U, timestamp.GetNsec());
}

/**
 * @brief Test Timestamp::SetNsec(uint32_t const nseconds) boundary value overflow
 */
TEST(Timestamp, SetNsec_2)
{
    Timestamp timestamp;
    EXPECT_THROW(timestamp.SetNsec(std::numeric_limits<uint32_t>::max()), OverflowException);
}

/**
 * @brief Test Timestamp::ToString() normal value
 */
TEST(Timestamp, ToStringTest)
{
    const Timestamp timestamp(3, 500);

    std::string expected_str("Timestamp: (");
    expected_str.append(std::to_string(3));
    expected_str.append(", ");
    expected_str.append(std::to_string(500));
    expected_str.append(")\n");
    ASSERT_EQ(expected_str, timestamp.ToString());
}

/**
 * @brief Test Timestamp::UtcToGps(Timestamp const& utc, Timestamp& gps)
 */
TEST(Timestamp, UtcToGps)
{
    Timestamp utc(0, 0);
    Timestamp gps;
    ASSERT_FALSE(holo::Timestamp::UtcToGps(utc, gps));
    ASSERT_EQ(gps.GetSec(), 0);
    ASSERT_EQ(gps.GetNsec(), 0);

    utc.SetSec(1467341198);
    utc.SetNsec(10000);
    ASSERT_TRUE(Timestamp::UtcToGps(utc, gps));
    ASSERT_EQ(gps.GetSec(), 1151376416);
    ASSERT_EQ(gps.GetNsec(), 10000);
}

/**
 * @brief Test Timestamp::GpsToUtc(Timestamp const& gps, Timestamp& utc)
 */
TEST(Timestamp, GpsToUtc)
{
    Timestamp gps(200, 300);
    Timestamp utc;
    ASSERT_FALSE(Timestamp::GpsToUtc(gps, utc));
    ASSERT_EQ(utc.GetSec(), 0);
    ASSERT_EQ(utc.GetNsec(), 0);

    gps.SetSec(1151375304);
    gps.SetNsec(11111);
    ASSERT_TRUE(Timestamp::GpsToUtc(gps, utc));
    ASSERT_EQ(utc.GetSec(), 1467340086);
    ASSERT_EQ(utc.GetNsec(), 11111);
}

/**
 * @brief Test Timestamp::GetSerializedSize
 */
TEST(Timestamp, GetSerializedSize)
{
    Timestamp timestamp;
    ASSERT_EQ(8, timestamp.GetSerializedSize<4U>());
    ASSERT_EQ(8, timestamp.GetSerializedSize<8U>());
}

/**
 * @brief Test Timestamp::Serialize and Deserialize
 */
TEST(Timestamp, SerializeAndDeserialize)
{
    Timestamp                          timestamp1(5U, 30U);
    uint8_t buffer[1024];
    holo::serialization::Serializer<>           serializer(buffer, 1024);
    serializer << timestamp1;
    ASSERT_EQ(timestamp1.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    Timestamp                   timestamp2;
    deserializer >> timestamp2;

    ASSERT_EQ(timestamp1.GetSec(), timestamp2.GetSec());
    ASSERT_EQ(timestamp1.GetNsec(), timestamp2.GetNsec());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
