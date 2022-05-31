/*!
 * @file test_diagnostics.cpp
 * @brief the unit test for diagnostics
 * @author lichao@holomatic.com
 * @date Oct 13, 2019
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>
#include <holo/localization/common/diagnostics.h>

using Diagnostics = holo::localization::Diagnostics;

///////////////////////////////////////////////////////////////////////////////
TEST(ConstructorTest, NormalCase)
{
    Diagnostics diagnostics;
    ASSERT_TRUE(diagnostics.GetTimestamp() == holo::common::Timestamp(0, 0));
    ASSERT_EQ(diagnostics.GetSystemTimestamp(), holo::common::Timestamp(0, 0));
    ASSERT_EQ(diagnostics.GetStatus(), 0u);
}

///////////////////////////////////////////////////////////////////////////////
TEST(DestructorTest, NormalCase)
{
    Diagnostics* diagnostics(new Diagnostics());
    delete diagnostics;
}

///////////////////////////////////////////////////////////////////////////////
TEST(ToStringTest, NormalCase)
{
    Diagnostics diagnostics;
    std::string expected_string;
    expected_string.append("Good");

    std::string unexpected_string;
    unexpected_string.append("ImuNotGood;");
    ASSERT_TRUE(diagnostics.ToString() == expected_string);
    ASSERT_TRUE(diagnostics.ToString() != unexpected_string);

    diagnostics.SetStatus(Diagnostics::kImuNotGood_);
    std::string expected_string2 = unexpected_string;
    ASSERT_TRUE(diagnostics.ToString() == expected_string2);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ToStringTest, ImuNotGood)
{
    Diagnostics diagnostics;
    diagnostics.SetStatus(Diagnostics::kImuNotGood_);
    std::string unexpected_string;
    unexpected_string.append("Good");

    std::string expected_string;
    expected_string.append("ImuNotGood;");
    ASSERT_TRUE(diagnostics.ToString() == expected_string);
    ASSERT_TRUE(diagnostics.ToString() != unexpected_string);

    diagnostics.SetStatus(Diagnostics::kGood_);
    std::string expected_string2 = unexpected_string;
    ASSERT_TRUE(diagnostics.ToString() == expected_string2);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ToStringTest, GpsNotGood)
{
    Diagnostics diagnostics;
    diagnostics.SetStatus(Diagnostics::kGpsNotGood_);
    std::string unexpected_string;
    unexpected_string.append("Good");

    std::string expected_string;
    expected_string.append("GpsNotGood;");
    ASSERT_TRUE(diagnostics.ToString() == expected_string);
    ASSERT_TRUE(diagnostics.ToString() != unexpected_string);

    diagnostics.SetStatus(Diagnostics::kGood_);
    std::string expected_string2 = unexpected_string;
    ASSERT_TRUE(diagnostics.ToString() == expected_string2);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ToStringTest, ImageNotGood)
{
    Diagnostics diagnostics;
    diagnostics.SetStatus(Diagnostics::kImageNotGood_);
    std::string unexpected_string;
    unexpected_string.append("Good");

    std::string expected_string;
    expected_string.append("ImageNotGood;");
    ASSERT_TRUE(diagnostics.ToString() == expected_string);
    ASSERT_TRUE(diagnostics.ToString() != unexpected_string);

    diagnostics.SetStatus(Diagnostics::kGood_);
    std::string expected_string2 = unexpected_string;
    ASSERT_TRUE(diagnostics.ToString() == expected_string2);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ToStringTest, ChassisStateNotGood_)
{
    Diagnostics diagnostics;
    diagnostics.SetStatus(Diagnostics::kChassisStateNotGood_);
    std::string unexpected_string;
    unexpected_string.append("Good");

    std::string expected_string;
    expected_string.append("ChassisStateNotGood;");
    ASSERT_TRUE(diagnostics.ToString() == expected_string);
    ASSERT_TRUE(diagnostics.ToString() != unexpected_string);

    diagnostics.SetStatus(Diagnostics::kGood_);
    std::string expected_string2 = unexpected_string;
    ASSERT_TRUE(diagnostics.ToString() == expected_string2);
}

///////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetStatusTest, NormalCase)
{
    Diagnostics diagnostics;

    uint32_t status = Diagnostics::kGood_;
    status |= Diagnostics::kImuNotGood_;
    status |= Diagnostics::kChassisStateNotGood_;
    diagnostics.SetStatus(status);
    ASSERT_TRUE(diagnostics.GetStatus() != Diagnostics::kGood_);
    ASSERT_TRUE(diagnostics.GetStatus() & Diagnostics::kImuNotGood_);
    ASSERT_FALSE(diagnostics.GetStatus() & Diagnostics::kGpsNotGood_);
    ASSERT_FALSE(diagnostics.GetStatus() & Diagnostics::kImageNotGood_);
    ASSERT_TRUE(diagnostics.GetStatus() & Diagnostics::kChassisStateNotGood_);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ToStringTest, WaitCase)
{
    Diagnostics diagnostics;
    diagnostics.SetStatus(Diagnostics::kWaitState_);
    std::string unexpected_string;
    unexpected_string.append("Good");

    std::string expected_string;
    expected_string.append("Wait;");
    ASSERT_TRUE(diagnostics.ToString() == expected_string);
    ASSERT_TRUE(diagnostics.ToString() != unexpected_string);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ToStringTest, ReadyCase)
{
    Diagnostics diagnostics;
    diagnostics.SetStatus(Diagnostics::kReadyState_);
    std::string unexpected_string;
    unexpected_string.append("Good");

    std::string expected_string;
    expected_string.append("Ready;");
    ASSERT_TRUE(diagnostics.ToString() == expected_string);
    ASSERT_TRUE(diagnostics.ToString() != unexpected_string);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ToStringTest, IdleCase)
{
    Diagnostics diagnostics;
    diagnostics.SetStatus(Diagnostics::kIdleState_);
    std::string unexpected_string;
    unexpected_string.append("Good");

    std::string expected_string;
    expected_string.append("Idle;");
    ASSERT_TRUE(diagnostics.ToString() == expected_string);
    ASSERT_TRUE(diagnostics.ToString() != unexpected_string);
}

///////////////////////////////////////////////////////////////////////////////
TEST(ToStringTest, RunCase)
{
    Diagnostics diagnostics;
    diagnostics.SetStatus(Diagnostics::kRunState_);
    std::string unexpected_string;
    unexpected_string.append("Good");

    std::string expected_string;
    expected_string.append("Run;");
    ASSERT_TRUE(diagnostics.ToString() == expected_string);
    ASSERT_TRUE(diagnostics.ToString() != unexpected_string);
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
