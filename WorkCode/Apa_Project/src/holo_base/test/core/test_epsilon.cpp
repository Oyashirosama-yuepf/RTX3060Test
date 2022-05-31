/*!
 * @file test_epsilon.cpp
 * @brief epsilon unit test
 * @author duyanwei@holomatic.com
 * @date 2019-11-15
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>

#include <holo/core/epsilon.h>

///////////////////////////////////////////////////////////////////////////////
TEST(EpsilonT, Value)
{
    ASSERT_EQ(holo::EpsilonT<holo::bool_t>::value, 0u);
    ASSERT_EQ(holo::EpsilonT<holo::int32_t>::value, 0);
    ASSERT_EQ(holo::EpsilonT<holo::uint32_t>::value, 0u);
    ASSERT_EQ(holo::EpsilonT<holo::uint64_t>::value, 0u);
    ASSERT_EQ(holo::EpsilonT<holo::float32_t>::value, 1e-5f);
    ASSERT_EQ(holo::EpsilonT<holo::float64_t>::value, 1e-10);
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
