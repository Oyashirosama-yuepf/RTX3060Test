/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_keypoint2.h
 * @brief Unit test for keypoint2.h
 * @author tanghui(tanghui@holomaitc.com)
 * @date 2019-12-10
 */

#include <cmath>

#include <gtest/gtest.h>

#include <holo/vision/keypoint2.h>

using namespace holo::vision;

const holo::float32_t tolf = holo::EpsilonT<holo::float32_t>::value;
const holo::float64_t told = holo::EpsilonT<holo::float64_t>::value;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(KeyPoint2UnitTest, DefaultConstructor)
{
    KeyPoint2d keypoint;
    keypoint.SetConfidence(1.0f);
    keypoint.SetVisibility(true);

    // check results
    ASSERT_NEAR(keypoint.GetConfidence(), 1.0, tolf);
    ASSERT_EQ(keypoint.IsVisible(), true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(KeyPoint2UnitTest, Constructor)
{
    KeyPoint2d keypoint(1.0, 2.0, 0.98, true);

    // check results
    ASSERT_NEAR(keypoint.GetX(), 1.0, told);
    ASSERT_NEAR(keypoint.GetY(), 2.0, told);
    ASSERT_NEAR(keypoint.GetConfidence(), 0.98, tolf);
    ASSERT_EQ(keypoint.IsVisible(), true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(KeyPoint2UnitTest, Assign)
{
    KeyPoint2d p(1.0, 2.0, 1.0, true);
    KeyPoint2d q = p;
    ASSERT_NEAR(q.GetX(), 1.0, told);
    ASSERT_NEAR(q.GetY(), 2.0, told);
    ASSERT_NEAR(q.GetConfidence(), 1.0, tolf);
    ASSERT_EQ(q.IsVisible(), true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(KeyPoint2UnitTest, Dist)
{
    KeyPoint2d      p(1.0, 2.0, 1.0, true);
    KeyPoint2d      q(2.0, 4.0, 1.0, true);
    holo::float64_t d1 = p.DistSqr(q);
    holo::float64_t d2 = p.Dist(q);
    holo::float64_t c  = std::sqrt(5.0);
    ASSERT_NEAR(d1, 5.0, tolf);
    ASSERT_NEAR(d2, c, tolf);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(KeyPoint2UnitTest, Equal)
{
    KeyPoint2d kp1(1.0, 2.0, 1.0, true);
    KeyPoint2d kp2(1.0, 2.0, 1.0, true);
    KeyPoint2d kp3(2.0, 2.0, 1.0, true);
    KeyPoint2d kp4(1.0, 1.0, 1.0, true);
    KeyPoint2d kp5(1.0, 2.0, 0.5, true);
    KeyPoint2d kp6(1.0, 2.0, 1.0, false);
    ASSERT_TRUE(kp1 == kp2);
    ASSERT_FALSE(kp1 == kp3);
    ASSERT_FALSE(kp1 == kp4);
    ASSERT_FALSE(kp1 == kp5);
    ASSERT_FALSE(kp1 == kp6);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(KeyPoint2UnitTest, GetSerializedSize)
{
    KeyPoint2f pt2f(1.0f, 2.0f, 1.0f, true);
    ASSERT_EQ(16, pt2f.GetSerializedSize<4U>());
    ASSERT_EQ(16, pt2f.GetSerializedSize<8U>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(KeyPoint2UnitTest, SerializeAndDeserialize)
{
    KeyPoint2f pt2f_input(1.0f, 2.0f, 1.0f, true), pt2f_output;
    uint8_t buffer[128];
    holo::serialization::Serializer<>          serializer(buffer, 128U);
    serializer << pt2f_input;
    ASSERT_EQ(pt2f_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> pt2f_output;

    ASSERT_EQ(pt2f_input, pt2f_output);
}

TEST(KeyPoint2UnitTest, OperatorEqual)
{
    KeyPoint2T<holo::float32_t> kp1, kp2;
    kp1 = kp2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
