/*!
 * @file test_stamped.cpp
 * @brief the unit test for stamped template class.
 * @author lichao@holomatic.com
 * @date Oct 07, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <gtest/gtest.h>
#include <holo/common/gnss_position.h>
#include <holo/localization/common/stamped.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(StampedTimeCompareTest, NormalCase)
{
    holo::GnssPosition lhs;
    lhs.SetTimestamp(holo::Timestamp(2, 0));
    holo::GnssPosition rhs1;
    rhs1.SetTimestamp(holo::Timestamp(3, 0));
    holo::GnssPosition rhs2;
    rhs2.SetTimestamp(holo::Timestamp(2, 0));
    holo::GnssPosition rhs3;
    rhs3.SetTimestamp(holo::Timestamp(1, 0));

    holo::localization::StampedTimeCompareT<holo::GnssPosition> time_compare;
    ASSERT_TRUE(time_compare(lhs, rhs1));
    ASSERT_FALSE(time_compare(lhs, rhs2));
    ASSERT_FALSE(time_compare(lhs, rhs3));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(StampedTimeCompareWithLeftTimestampTest, NormalCase)
{
    holo::GnssPosition position;
    position.SetTimestamp(holo::Timestamp(2, 0));
    holo::Timestamp Timestamp1(3, 0);
    holo::Timestamp Timestamp2(2, 0);
    holo::Timestamp Timestamp3(1, 0);

    holo::localization::StampedTimeCompareT<holo::GnssPosition> time_compare;
    ASSERT_FALSE(time_compare(Timestamp1, position));
    ASSERT_FALSE(time_compare(Timestamp2, position));
    ASSERT_TRUE(time_compare(Timestamp3, position));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(StampedTimeCompareWithRightTimestampTest, NormalCase)
{
    holo::GnssPosition position;
    position.SetTimestamp(holo::Timestamp(2, 0));
    holo::Timestamp Timestamp1(3, 0);
    holo::Timestamp Timestamp2(2, 0);
    holo::Timestamp Timestamp3(1, 0);

    holo::localization::StampedTimeCompareT<holo::GnssPosition> time_compare;
    ASSERT_TRUE(time_compare(position, Timestamp1));
    ASSERT_FALSE(time_compare(position, Timestamp2));
    ASSERT_FALSE(time_compare(position, Timestamp3));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(StampedTDefaultConstructorTest, NormalCase)
{
    holo::localization::StampedT<uint8_t> stamped_value;
    ASSERT_TRUE(holo::Timestamp() == stamped_value.GetTimestamp());
    ASSERT_TRUE(0u == stamped_value.GetData());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(StampedTConstructorTest, NormalCase)
{
    const holo::Timestamp expected_timestamp(31, 0);
    const holo::uint8_t   expected_value(112u);

    holo::localization::StampedT<uint8_t> stamped_value(expected_timestamp, expected_value);
    ASSERT_TRUE(expected_timestamp == stamped_value.GetTimestamp());
    ASSERT_TRUE(expected_value == stamped_value.GetData());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetTimestampTest, NormalCase)
{
    const holo::Timestamp expected_timestamp(31, 0);

    holo::localization::StampedT<uint8_t> stamped_value;
    stamped_value.SetTimestamp(expected_timestamp);
    ASSERT_TRUE(expected_timestamp == stamped_value.GetTimestamp());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetDataTest, NormalCase)
{
    const holo::uint8_t expected_value(112u);

    holo::localization::StampedT<uint8_t> stamped_value;
    stamped_value.SetData(expected_value);
    ASSERT_TRUE(expected_value == stamped_value.GetData());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
