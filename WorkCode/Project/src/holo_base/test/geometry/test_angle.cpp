/*!
 * @file test_angle.cpp
 * @brief angle unit test
 * @author duyanwei@holomatic.com
 * @date 2017-07-11
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>

#include <holo/geometry/angle.h>

using namespace holo;

///////////////////////////////////////////////////////////////////////////////
TEST(AngleTest, DegreeRadian)
{
    ASSERT_EQ(holo::geometry::Radian(180.0), M_PI);
    ASSERT_EQ(holo::geometry::Degree(M_PI), 180.0);

    ASSERT_EQ(holo::geometry::Radian(540.0), 3.0 * M_PI);
    ASSERT_EQ(holo::geometry::Degree(3.0 * M_PI), 540.0);

    ASSERT_EQ(holo::geometry::Radian(-90.0), -0.5 * M_PI);
    ASSERT_EQ(holo::geometry::Degree(-0.5 * M_PI), -90.0);
}

///////////////////////////////////////////////////////////////////////////////
TEST(AngleTest, DegreeRadian2)
{
    ASSERT_EQ(holo::geometry::Radian2(180.0), M_PI);
    ASSERT_EQ(holo::geometry::Degree2(M_PI), 180.0);

    ASSERT_EQ(holo::geometry::Radian2(540.0), M_PI);
    ASSERT_EQ(holo::geometry::Degree2(3.0 * M_PI), 180.0);

    ASSERT_EQ(holo::geometry::Radian2(-90.0), 1.5 * M_PI);
    ASSERT_EQ(holo::geometry::Degree2(-0.5 * M_PI), 270.0);
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
