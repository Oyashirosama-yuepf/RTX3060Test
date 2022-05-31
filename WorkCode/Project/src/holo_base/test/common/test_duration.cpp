/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_duration.cpp
 * @brief unit test for duration class
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-03
 */

#include <gtest/gtest.h>
#include <holo/common/timestamp.h>

using float64_t         = holo::float64_t;
using Duration          = holo::common::Duration;
using OverflowException = holo::common::OverflowException;

/**
 * @brief Test Duration()
 */
TEST(Duration, DefaultConstructor)
{
    Duration duration;
    ASSERT_EQ(0, duration.GetSec());
    ASSERT_EQ(0, duration.GetNsec());
}

/**
 * @brief Test Duration(int32_t sec, int32_t nsec) minimum value
 */
TEST(Duration, ConstructWithSecNsec_1)
{
    Duration duration(0, 0);
    ASSERT_EQ(0, duration.GetSec());
    ASSERT_EQ(0, duration.GetNsec());
}

/**
 * @brief Test Duration(int32_t sec, int32_t nsec) normal positive value
 */
TEST(Duration, ConstructWithSecNsec_2)
{
    Duration duration(1, 100);
    ASSERT_EQ(1, duration.GetSec());
    ASSERT_EQ(100, duration.GetNsec());
}

/**
 * @brief Test Duration(int32_t sec, int32_t nsec) normal negative value
 */
TEST(Duration, ConstructWithSecNsec_3)
{
    Duration duration(-5, -100);
    ASSERT_EQ(-6, duration.GetSec());
    ASSERT_EQ(Duration::NSEC_PER_SEC - 100, duration.GetNsec());
}

/**
 * @brief Test Duration(int32_t sec, int32_t nsec) nsec positive boundary value
 */
TEST(Duration, ConstructWithSecNsec_4)
{
    Duration duration(4, Duration::NSEC_PER_SEC);
    ASSERT_EQ(5, duration.GetSec());
    ASSERT_EQ(0, duration.GetNsec());
}

/**
 * @brief Test Duration(int32_t sec, int32_t nsec) nsec negative boundary value
 */
TEST(Duration, ConstructWithSecNsec_5)
{
    Duration duration(4, -Duration::NSEC_PER_SEC);
    ASSERT_EQ(3, duration.GetSec());
    ASSERT_EQ(0, duration.GetNsec());
}

/**
 * @brief Test Duration(int32_t sec, int32_t nsec) nsec positive boundary value
 */
TEST(Duration, ConstructWithSecNsec_6)
{
    Duration duration(-4, Duration::NSEC_PER_SEC);
    ASSERT_EQ(-3, duration.GetSec());
    ASSERT_EQ(0, duration.GetNsec());
}

/**
 * @brief Test Duration(int32_t sec, int32_t nsec) nsec negative boundary value
 */
TEST(Duration, ConstructWithSecNsec_7)
{
    Duration duration(-4, -Duration::NSEC_PER_SEC);
    ASSERT_EQ(-5, duration.GetSec());
    ASSERT_EQ(0, duration.GetNsec());
}

/**
 * @brief Test Duration(int32_t sec, int32_t nsec) biggest boundary value
 */
TEST(Duration, ConstructWithSecNsec_8)
{
    Duration duration(std::numeric_limits<int32_t>::max(), Duration::NSEC_PER_SEC - 1);
    ASSERT_EQ(std::numeric_limits<int32_t>::max(), duration.GetSec());
    ASSERT_EQ(Duration::NSEC_PER_SEC - 1, duration.GetNsec());
}

/**
 * @brief Test Duration(int32_t sec, int32_t nsec) minimum boundary value
 */
TEST(Duration, ConstructWithSecNsec_9)
{
    Duration duration(std::numeric_limits<int32_t>::min(), 0);
    ASSERT_EQ(std::numeric_limits<int32_t>::min(), duration.GetSec());
    ASSERT_EQ(0, duration.GetNsec());
}

/**
 * @brief Test Duration(int32_t sec, int32_t nsec)  biggest boundary overflow
 */
TEST(Duration, ConstructWithSecNsec_10)
{
    EXPECT_THROW(Duration duration(std::numeric_limits<int32_t>::max(), Duration::NSEC_PER_SEC + 1), OverflowException);
}

/**
 * @brief Test Duration(int32_t sec, int32_t nsec) minimum boundary overflow
 */
TEST(Duration, ConstructWithSecNsec_11)
{
    EXPECT_THROW(Duration duration(std::numeric_limits<int32_t>::min(), -5), OverflowException);
}

/**
 * @brief Test Duration(float64_t t) minimum value
 */
TEST(Duration, ConstructWithFloat64Sec_1)
{
    Duration duration(0.0f);
    ASSERT_EQ(0, duration.GetSec());
    ASSERT_EQ(0, duration.GetNsec());
}

/**
 * @brief Test Duration(float64_t t) normal positive value
 */
TEST(Duration, ConstructWithFloat64Sec_2)
{
    Duration duration(5 + static_cast<float64_t>(6000) / Duration::NSEC_PER_SEC);
    ASSERT_EQ(5, duration.GetSec());
    ASSERT_EQ(6000, duration.GetNsec());
}

/**
 * @brief Test Duration(float64_t t) normal negative value
 */
TEST(Duration, ConstructWithFloat64Sec_3)
{
    Duration duration(-5 + static_cast<float64_t>(-6000) / Duration::NSEC_PER_SEC);
    ASSERT_EQ(-6, duration.GetSec());
    ASSERT_EQ(Duration::NSEC_PER_SEC - 6000, duration.GetNsec());
}

/**
 * @brief Test Duration(float64_t t) overflow
 */
TEST(Duration, ConstructWithFloat64Sec_4)
{
    try
    {
        Duration duration(static_cast<float64_t>(Duration::DURATION_MAX_NSEC / Duration::NSEC_PER_SEC + 1U));
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
 * @brief Test Duration(float64_t t) underflow
 */
TEST(Duration, ConstructWithFloat64Sec_5)
{
    try
    {
        Duration duration(static_cast<float64_t>(Duration::DURATION_MIN_NSEC / Duration::NSEC_PER_SEC - 1U));
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
 * @brief Test Duration(int64_t t) minimum value
 */
TEST(Duration, ConstructWithInt64Nsec_1)
{
    Duration duration(static_cast<int64_t>(0));
    ASSERT_EQ(0, duration.GetSec());
    ASSERT_EQ(0, duration.GetNsec());
}

/**
 * @brief Test Duration(int64_t t) positive normal value
 */
TEST(Duration, ConstructWithInt64Nsec_2)
{
    Duration duration(static_cast<int64_t>(2000000500));
    ASSERT_EQ(2, duration.GetSec());
    ASSERT_EQ(500 % Duration::NSEC_PER_SEC, duration.GetNsec());
}

/**
 * @brief Test Duration(int64_t t) negative normal value
 */
TEST(Duration, ConstructWithInt64Nsec_3)
{
    Duration duration(static_cast<int64_t>(-2000000500));
    ASSERT_EQ(-3, duration.GetSec());
    ASSERT_EQ(Duration::NSEC_PER_SEC - 500, duration.GetNsec());
}

/**
 * @brief Test Duration(int64_t t) biggest boundary value
 */
TEST(Duration, ConstructWithInt64Nsec_4)
{
    Duration duration(Duration::DURATION_MAX_NSEC);
    ASSERT_EQ(Duration::DURATION_MAX_NSEC / Duration::NSEC_PER_SEC, duration.GetSec());
    ASSERT_EQ(Duration::DURATION_MAX_NSEC % Duration::NSEC_PER_SEC, duration.GetNsec());
}

/**
 * @brief Test Duration(int64_t t) minimum boundary value
 */
TEST(Duration, ConstructWithInt64Nsec_5)
{
    Duration duration(Duration::DURATION_MIN_NSEC);
    ASSERT_EQ(std::numeric_limits<int32_t>::min(), duration.GetSec());
    ASSERT_EQ(0, duration.GetNsec());
}

/**
 * @brief Test Duration::operator+(Duration const& rhs) const both normal positive
 */
TEST(Duration, AdditionOperator_1)
{
    Duration lhs(2, 2);
    Duration rhs(1, 1);
    Duration expected_duration(3, 3);
    ASSERT_EQ(expected_duration, lhs + rhs);
}

/**
 * @brief Test Duration::operator+(Duration const& rhs) const both boundary value
 */
TEST(Duration, AdditionOperator_2)
{
    Duration lhs(std::numeric_limits<int32_t>::max(), Duration::NSEC_PER_SEC - 1);
    Duration rhs(std::numeric_limits<int32_t>::max(), Duration::NSEC_PER_SEC - 1);
    EXPECT_THROW(lhs + rhs, OverflowException);
}

/**
 * @brief Test Duration::operator+(Duration const& rhs) const both normal value
 */
TEST(Duration, AdditionOperator_3)
{
    Duration lhs(2, 2);
    Duration rhs(-1, -1);
    Duration expected_duration(1, 1);
    ASSERT_EQ(expected_duration, lhs + rhs);
}

/**
 * @brief Test Duration::operator+(Duration const& rhs) const both normal value
 */
TEST(Duration, AdditionOperator_4)
{
    Duration lhs(-2, -2);
    Duration rhs(5, 5);
    Duration expected_duration(3, 3);
    ASSERT_EQ(expected_duration, lhs + rhs);
}

/**
 * @brief Test Duration::operator+(Duration const& rhs) const both normal value
 */
TEST(Duration, AdditionOperator_5)
{
    Duration lhs(-2, -2);
    Duration rhs(-5, -5);
    Duration expected_duration(-7, -7);
    ASSERT_EQ(expected_duration, lhs + rhs);
}

/**
 * @brief Test Duration::operator+(Duration const& rhs) const expect duration overflow
 */
TEST(Duration, AdditionOperator_6)
{
    Duration lhs(-2, -2);
    Duration rhs(std::numeric_limits<int32_t>::min(), 0);
    EXPECT_THROW(lhs + rhs, OverflowException);
}

/**
 * @brief Test Duration::operator-(Duration const& rhs) const normal value
 */
TEST(Duration, SubtractOperator_1)
{
    Duration lhs(7, 7);
    Duration rhs(5, 5);
    Duration expected_duration(2, 2);
    ASSERT_EQ(expected_duration, lhs - rhs);
}

/**
 * @brief Test Duration::operator-(Duration const& rhs) const normal value
 */
TEST(Duration, SubtractOperator_2)
{
    Duration lhs(7, 7);
    Duration rhs(-5, -5);
    Duration expected_duration(12, 12);
    ASSERT_EQ(expected_duration, lhs - rhs);
}

/**
 * @brief Test Duration::operator-(Duration const& rhs) const expect duration overflow
 */
TEST(Duration, SubtractOperator_3)
{
    Duration lhs(7, 7);
    Duration rhs(std::numeric_limits<int32_t>::min(), 0);
    EXPECT_THROW(lhs - rhs, OverflowException);
}

/**
 * @brief Test Duration::operator-(Duration const& rhs) const normal value
 */
TEST(Duration, SubtractOperator_4)
{
    Duration lhs(-7, -7);
    Duration rhs(5, 5);
    Duration expected_duration(-12, -12);
    ASSERT_EQ(expected_duration, lhs - rhs);
}

/**
 * @brief Test Duration::operator-(Duration const& rhs) const expect duration overflow
 */
TEST(Duration, SubtractOperator_5)
{
    Duration lhs(-7, -7);
    Duration rhs(std::numeric_limits<int32_t>::max(), Duration::NSEC_PER_SEC - 1);
    EXPECT_THROW(lhs - rhs, OverflowException);
}

/**
 * @brief Test Duration::operator-(Duration const& rhs) const normal value
 */
TEST(Duration, SubtractOperator_6)
{
    Duration lhs(-7, -7);
    Duration rhs(-5, -5);
    Duration expected_duration(-2, -2);
    ASSERT_EQ(expected_duration, lhs - rhs);
}

/**
 * @brief Test Duration::operator-() minimum value
 */
TEST(Duration, Negate_1)
{
    Duration lhs(0, 0);
    Duration expected_duration(0, 0);
    ASSERT_EQ(expected_duration, -lhs);
}

/**
 * @brief Test Duration::operator-() negative to positive
 */
TEST(Duration, Negate_2)
{
    Duration lhs(-7, -7);
    Duration expected_duration(7, 7);
    ASSERT_EQ(expected_duration, -lhs);
}

/**
 * @brief Test Duration::operator-() positive to negative
 */
TEST(Duration, Negate_3)
{
    Duration lhs(7, 7);
    Duration expected_duration(-7, -7);
    ASSERT_EQ(expected_duration, -lhs);
}

/**
 * @brief Test Duration::operator*(float64_t rhs)  minimum value
 */
TEST(Duration, ScaleOperator_1)
{
    Duration lhs(0, 0);
    Duration expected_duration(0, 0);
    ASSERT_EQ(expected_duration, lhs * 2.0f);
}

/**
 * @brief Test Duration::operator*(float64_t rhs)  normal value
 *
 */
TEST(Duration, ScaleOperator_2)
{
    Duration lhs(2, 3);
    Duration expected_duration(4, 6);
    ASSERT_EQ(expected_duration, lhs * 2.0f);
}

/**
 * @brief Test Duration::operator*(float64_t rhs)  boundary value overflow
 *
 */
TEST(Duration, ScaleOperator_3)
{
    Duration lhs(std::numeric_limits<int32_t>::max(), Duration::NSEC_PER_SEC - 1);
    EXPECT_THROW(lhs * 2.0f, OverflowException);
}

/**
 * @brief Test friend Duration::operator*(float64_t lhs, Duration const& rhs) minimum value
 */
TEST(Duration, FriendScaleOperator_1)
{
    Duration rhs(0, 0);
    Duration expected_duration(0, 0);
    ASSERT_EQ(expected_duration, 2.0f * rhs);
}

/**
 * @brief Test friend Duration::operator*(float64_t lhs, Duration const& rhs) normal value
 */
TEST(Duration, FriendScaleOperator_2)
{
    Duration rhs(2, 3);
    Duration expected_duration(4, 6);
    ASSERT_EQ(expected_duration, 2.0f * rhs);
}

/**
 * @brief Test friend Duration::operator*(float64_t lhs, Duration const& rhs) boundary value overflow
 */
TEST(Duration, FriendScaleOperator_3)
{
    Duration rhs(std::numeric_limits<int32_t>::max(), Duration::NSEC_PER_SEC - 1);
    EXPECT_THROW(2.0f * rhs, OverflowException);
}

/**
 * @brief Test Duration::operator+=(Duration const& rhs) normal value
 */
TEST(Duration, AdditionEqualOperator_1)
{
    Duration lhs(7, 7);
    Duration rhs(5, 5);
    Duration expected_duration(12, 12);
    lhs += rhs;
    ASSERT_EQ(expected_duration, lhs);
}

/**
 * @brief Test Duration::operator+=(Duration const& rhs) boundary value overflow
 */
TEST(Duration, AdditionEqualOperator_2)
{
    Duration lhs(7, 7);
    Duration rhs(std::numeric_limits<int32_t>::max(), Duration::NSEC_PER_SEC - 1);
    EXPECT_THROW(lhs += rhs, OverflowException);
}

/**
 * @brief Test Duration::operator+=(Duration const& rhs) normal value
 */
TEST(Duration, AdditionEqualOperator_3)
{
    Duration lhs(7, 7);
    Duration rhs(-5, -5);
    Duration expected_duration(2, 2);
    lhs += rhs;
    ASSERT_EQ(expected_duration, lhs);
}

/**
 * @brief Test Duration::operator+=(Duration const& rhs) normal value
 */
TEST(Duration, AdditionEqualOperator_4)
{
    Duration lhs(-7, -7);
    Duration rhs(5, 5);
    Duration expected_duration(-2, -2);
    lhs += rhs;
    ASSERT_EQ(expected_duration, lhs);
}

/**
 * @brief Test Duration::operator+=(Duration const& rhs) normal value
 */
TEST(Duration, AdditionEqualOperator_5)
{
    Duration lhs(-7, -7);
    Duration rhs(-5, -5);
    Duration expected_duration(-12, -12);
    lhs += rhs;
    ASSERT_EQ(expected_duration, lhs);
}

/**
 * @brief Test Duration::operator+=(Duration const& rhs) boundary value overflow
 */
TEST(Duration, AdditionEqualOperator_6)
{
    Duration lhs(-7, -7);
    Duration rhs(std::numeric_limits<int32_t>::min(), 0);
    EXPECT_THROW(lhs += rhs, OverflowException);
}

/**
 * @brief Test Duration::operator-=(Duration const& rhs) normal value
 */
TEST(Duration, SubtractEqualOperator_1)
{
    Duration lhs(7, 7);
    Duration rhs(5, 5);
    Duration expected_duration(2, 2);
    lhs -= rhs;
    ASSERT_EQ(expected_duration, lhs);
}

/**
 * @brief Test Duration::operator-=(Duration const& rhs) normal value
 */
TEST(Duration, SubtractEqualOperator_2)
{
    Duration lhs(7, 7);
    Duration rhs(-5, -5);
    Duration expected_duration(12, 12);
    lhs -= rhs;
    ASSERT_EQ(expected_duration, lhs);
}

/**
 * @brief Test Duration::operator-=(Duration const& rhs) minimum boundary value overflow
 */
TEST(Duration, SubtractEqualOperator_3)
{
    Duration lhs(7, 7);
    Duration rhs(std::numeric_limits<int32_t>::min(), 0);
    EXPECT_THROW(lhs -= rhs, OverflowException);
}

/**
 * @brief Test Duration::operator-=(Duration const& rhs) normal value
 */
TEST(Duration, SubtractEqualOperator_4)
{
    Duration lhs(-7, -7);
    Duration rhs(5, 5);
    Duration expected_duration(-12, -12);
    lhs -= rhs;
    ASSERT_EQ(expected_duration, lhs);
}

/**
 * @brief Test Duration::operator-=(Duration const& rhs) biggest boundary value overflow
 */
TEST(Duration, SubtractEqualOperator_5)
{
    Duration lhs(-7, -7);
    Duration rhs(std::numeric_limits<int32_t>::max(), 5);
    EXPECT_THROW(lhs -= rhs, OverflowException);
}

/**
 * @brief Test Duration::operator-=(Duration const& rhs) normal value
 */
TEST(Duration, SubtractEqualOperator_6)
{
    Duration lhs(-7, -7);
    Duration rhs(-5, -5);
    Duration expected_duration(-2, -2);
    lhs -= rhs;
    ASSERT_EQ(expected_duration, lhs);
}

/**
 * @brief Test Duration::operator*=(float64_t scale) normal value
 */
TEST(Duration, MultiplyEqualOperator_1)
{
    Duration lhs(7, 5);
    Duration expected_duration(0, 0);
    lhs *= 0.0f;
    ASSERT_EQ(expected_duration, lhs);
}

/**
 * @brief Test Duration::operator*=(float64_t scale) normal value
 */
TEST(Duration, MultiplyEqualOperator_2)
{
    Duration lhs(7, 5);
    Duration expected_duration(14, 10);
    lhs *= 2.0f;
    ASSERT_EQ(expected_duration, lhs);
}

/**
 * @brief Test Duration::operator==(Duration const& rhs) normal value
 */
TEST(Duration, EqualOperator_1)
{
    Duration const lhs(2, 700);
    Duration const rhs(2, 700);
    ASSERT_TRUE(lhs == rhs);
}

/**
 * @brief Test Duration::operator==(Duration const& rhs) normal value
 */
TEST(Duration, EqualOperator_2)
{
    Duration const lhs(2, 700);
    Duration const rhs(2, 350);
    ASSERT_FALSE(lhs == rhs);
}

/**
 * @brief Test Duration::operator!=(Duration const& rhs) normal value
 */
TEST(Duration, InequalOperator_1)
{
    Duration const lhs(2, 700);
    Duration const rhs(2, 500);
    ASSERT_TRUE(lhs != rhs);
}

/**
 * @brief Test Duration::operator!=(Duration const& rhs) normal value
 */
TEST(Duration, InequalOperator_2)
{
    Duration const lhs(2, 700);
    Duration const rhs(2, 700);
    ASSERT_FALSE(lhs != rhs);
}

/**
 * @brief Test Duration::operator>(Duration const& rhs) normal value
 */
TEST(Duration, GreaterThanOperator_1)
{
    Duration const lhs(2, 700);
    Duration const rhs(2, 700);
    ASSERT_FALSE(lhs > rhs);
}

/**
 * @brief Test Duration::operator>(Duration const& rhs) normal value
 */
TEST(Duration, GreaterThanOperator_2)
{
    Duration const lhs(2, 900);
    Duration const rhs(2, 700);
    ASSERT_TRUE(lhs > rhs);
}

/**
 * @brief Test Duration::operator>(Duration const& rhs) normal value
 */
TEST(Duration, GreaterThanOperator_3)
{
    Duration const lhs(2, 500);
    Duration const rhs(2, 700);
    ASSERT_FALSE(lhs > rhs);
}

/**
 * @brief Test Duration::operator<(Duration const& rhs) normal value
 */
TEST(Duration, LessThanOperator_1)
{
    Duration const lhs(2, 700);
    Duration const rhs(2, 700);
    ASSERT_FALSE(lhs < rhs);
}

/**
 * @brief Test Duration::operator<(Duration const& rhs) normal value
 */
TEST(Duration, LessThanOperator_2)
{
    Duration const lhs(2, 700);
    Duration const rhs(2, 500);
    ASSERT_FALSE(lhs < rhs);
}

/**
 * @brief Test Duration::operator<(Duration const& rhs) normal value
 */
TEST(Duration, LessThanOperator_3)
{
    Duration const lhs(2, 500);
    Duration const rhs(2, 700);
    ASSERT_TRUE(lhs < rhs);
}

/**
 * @brief Test Duration::operator>=(Duration const& rhs) normal value
 */
TEST(Duration, GreaterThanEqualOperator_1)
{
    Duration const lhs(2, 700);
    Duration const rhs(2, 700);
    ASSERT_TRUE(lhs >= rhs);
}

/**
 * @brief Test Duration::operator>=(Duration const& rhs) normal value
 */
TEST(Duration, GreaterThanEqualOperator_2)
{
    Duration const lhs(2, 700);
    Duration const rhs(2, 500);
    ASSERT_TRUE(lhs >= rhs);
}

/**
 * @brief Test Duration::operator>=(Duration const& rhs) normal value
 */
TEST(Duration, GreaterThanEqualOperator_3)
{
    Duration const lhs(2, 500);
    Duration const rhs(2, 700);
    ASSERT_FALSE(lhs >= rhs);
}

/**
 * @brief Test Duration::operator<=(Duration const& rhs) normal value
 */
TEST(Duration, LessThanEqualOperator_1)
{
    Duration const lhs(2, 700);
    Duration const rhs(2, 700);
    ASSERT_TRUE(lhs <= rhs);
}

/**
 * @brief Test Duration::operator<=(Duration const& rhs) normal value
 */
TEST(Duration, LessThanEqualOperator_2)
{
    Duration const lhs(2, 500);
    Duration const rhs(2, 700);
    ASSERT_TRUE(lhs <= rhs);
}

/**
 * @brief Test Duration::operator<=(Duration const& rhs) normal value
 */
TEST(Duration, LessThanEqualOperator_3)
{
    Duration const lhs(2, 700);
    Duration const rhs(2, 500);
    ASSERT_FALSE(lhs <= rhs);
}

/**
 * @brief Test Duration::ToSec()
 */
TEST(Duration, ToSec)
{
    Duration const duration(2, 50000);
    ASSERT_EQ(2.00005, duration.ToSec());
}

/**
 * @brief Test Duration::ToNsec()
 */
TEST(Duration, ToNsec)
{
    Duration const duration(2, 500);
    ASSERT_EQ(2000000500U, duration.ToNsec());
}

/**
 * @brief  Test Duration::IsZero()
 */
TEST(Duration, IsZero_1)
{
    Duration duration(0.0f);
    ASSERT_TRUE(duration.IsZero());
}

/**
 * @brief Test Duration::IsZero()
 */
TEST(Duration, IsZero_2)
{
    Duration duration(100.00f);
    ASSERT_FALSE(duration.IsZero());
}

/**
 * @brief Test Duration::IsEqual(Duration const& rhs, uint32_t tolerance_nsec = 0)
 */
TEST(Duration, IsEqual_1)
{
    Duration lhs(4, 700);
    Duration rhs(4, 500);
    ASSERT_TRUE(lhs.IsEqual(rhs, 300));
}

/**
 * @brief Test Duration::IsEqual(Duration const& rhs, uint32_t tolerance_nsec = 0)
 */
TEST(Duration, IsEqual_2)
{
    Duration lhs(4, 700);
    Duration rhs(4, 400);
    ASSERT_TRUE(lhs.IsEqual(rhs, 300));
}

/**
 * @brief Test Duration::IsEqual(Duration const& rhs, uint32_t tolerance_nsec = 0)
 *
 */
TEST(Duration, IsEqual_3)
{
    Duration lhs(4, 900);
    Duration rhs(4, 400);
    ASSERT_FALSE(lhs.IsEqual(rhs, 300));
}

/**
 * @brief Test Duration::GetSec()
 *
 */
TEST(Duration, GetSec_1)
{
    Duration duration(5, 30);
    ASSERT_EQ(5, duration.GetSec());
}

/**
 * @brief Test Duration::GetSec()
 *
 */
TEST(Duration, GetSec_2)
{
    Duration duration(5, -30);
    ASSERT_EQ(4, duration.GetSec());
}

/**
 * @brief Test Duration::GetNsec()
 *
 */
TEST(Duration, GetNsec_1)
{
    Duration duration(5, 30);
    ASSERT_EQ(30, duration.GetNsec());
}

/**
 * @brief Test Duration::GetNsec()
 *
 */
TEST(Duration, GetNsec_2)
{
    Duration duration(5, -30);
    ASSERT_EQ(Duration::NSEC_PER_SEC - 30, duration.GetNsec());
}

/**
 * @brief Test Duration::SetSec(int32_t const seconds) normal value;
 *
 */
TEST(Duration, SetSec_1)
{
    Duration duration;
    duration.SetSec(50);
    ASSERT_EQ(50, duration.GetSec());
}

/**
 * @brief Test Duration::SetSec(int32_t const seconds) boundary value
 *
 */
TEST(Duration, SetSec_2)
{
    Duration duration;
    duration.SetSec(std::numeric_limits<int32_t>::max());
    ASSERT_EQ(std::numeric_limits<int32_t>::max(), duration.GetSec());
}

/**
 * @brief Test Duration::SetNsec(int32_t const nseconds) normal value
 *
 */
TEST(Duration, SetNsec_1)
{
    Duration duration;
    duration.SetNsec(50);
    ASSERT_EQ(50U, duration.GetNsec());
}

/**
 * @brief Test Duration::SetNsec(int32_t const nseconds) boundary value overflow
 *
 */
TEST(Duration, SetNsec_2)
{
    Duration duration;
    EXPECT_THROW(duration.SetNsec(Duration::NSEC_PER_SEC + 50), OverflowException);
}

/**
 * @brief Test Duration::ToString() normal value
 *
 */
TEST(Duration, ToString)
{
    const Duration duration(3, 500);
    std::string    expected_str("Duration: (");
    expected_str.append(std::to_string(3));
    expected_str.append(", ");
    expected_str.append(std::to_string(500));
    expected_str.append(")\n");
    ASSERT_EQ(expected_str, duration.ToString());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
