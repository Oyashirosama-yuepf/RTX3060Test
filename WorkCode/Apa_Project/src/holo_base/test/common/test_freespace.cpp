/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_freespace.cpp
 * @brief Unit test for Freespace object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-21
 */

#include <gtest/gtest.h>
#include <holo/common/freespace.h>
#include <holo/geometry/point2.h>

using FreespacePolygon = holo::common::details::FreespacePolygonBaseT<holo::geometry::Point2T<holo::float32_t>, 32U>;

TEST(FreespacePolygon, Constructor)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};
    ASSERT_EQ(11U, poly.size());
}

TEST(FreespacePolygon, SetBoundaryType_0)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    EXPECT_EQ(0U, poly.GetBoundarySize());

    poly.SetBoundaryType(0U, 0U, 1U);
    EXPECT_EQ(1U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(0U, 0U)), poly.GetBoundaryRangeByIndex(0U));
}

TEST(FreespacePolygon, SetBoundaryType_1)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(0, 1U);

    EXPECT_EQ(2U, poly.GetBoundarySize());
    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(0U, 1U)), poly.GetBoundaryRangeByIndex(0U));
    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 0U)), poly.GetBoundaryRangeByIndex(1U));
}

TEST(FreespacePolygon, SetBoundaryType_2)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(1U, 1U);
    EXPECT_EQ(2U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 2U)), poly.GetBoundaryRangeByIndex(0U));
    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 1U)), poly.GetBoundaryRangeByIndex(1U));
}

TEST(FreespacePolygon, SetBoundaryType_3)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(1U, 1U, 1U);
    EXPECT_EQ(1U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(0U, 0U)), poly.GetBoundaryRangeByIndex(0U));
}

TEST(FreespacePolygon, SetBoundaryType_4)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(3U, 1U, 1U);
    EXPECT_EQ(2U, poly.GetBoundarySize());

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 3U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(3U, 1U)), poly.GetBoundaryRangeByIndex(1U));
}

TEST(FreespacePolygon, SetBoundaryType_5)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(1, 8U, 1U);
    poly.SetBoundaryType(2, 4U, 2U);
    EXPECT_EQ(4U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 2U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 4U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 8U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 1U)), poly.GetBoundaryRangeByIndex(3U));
}

TEST(FreespacePolygon, SetBoundaryType_6)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(1, 8U, 1U);
    poly.SetBoundaryType(1, 4U, 2U);
    EXPECT_EQ(3U, poly.GetBoundarySize());

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 4U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 8U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 1U)), poly.GetBoundaryRangeByIndex(2U));
}

TEST(FreespacePolygon, SetBoundaryType_7)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(1, 8U, 1U);
    poly.SetBoundaryType(4, 8U, 2U);
    EXPECT_EQ(3U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 4U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 8U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 1U)), poly.GetBoundaryRangeByIndex(2U));
}

TEST(FreespacePolygon, SetBoundaryType_8)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(1, 8U, 1U);
    poly.SetBoundaryType(1, 8U, 2U);
    EXPECT_EQ(2U, poly.GetBoundarySize());

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 8U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 1U)), poly.GetBoundaryRangeByIndex(1U));
}

TEST(FreespacePolygon, SetBoundaryType_9)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(1U, 8U, 1U);
    poly.SetBoundaryType(0U, 9U, 2U);
    EXPECT_EQ(2U, poly.GetBoundarySize());

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(0U, 9U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(9U, 0U)), poly.GetBoundaryRangeByIndex(1U));
}

TEST(FreespacePolygon, SetBoundaryType_10)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(4U, 8U, 1U);
    poly.SetBoundaryType(1U, 3U, 2U);
    EXPECT_EQ(4U, poly.GetBoundarySize());

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 3U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(3U, 4U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 8U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 1U)), poly.GetBoundaryRangeByIndex(3U));
}

TEST(FreespacePolygon, SetBoundaryType_11)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(4U, 8U, 1U);
    poly.SetBoundaryType(1U, 4U, 2U);
    EXPECT_EQ(3U, poly.GetBoundarySize());

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 4U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 8U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 1U)), poly.GetBoundaryRangeByIndex(2U));
}

TEST(FreespacePolygon, SetBoundaryType_12)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(4U, 8U, 1U);
    poly.SetBoundaryType(9U, 10U, 2U);
    EXPECT_EQ(4U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 8U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 9U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(9U, 10U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(10U, 4U)), poly.GetBoundaryRangeByIndex(3U));
}

TEST(FreespacePolygon, SetBoundaryType_13)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(4U, 8U, 1U);
    poly.SetBoundaryType(8U, 10U, 2U);
    EXPECT_EQ(3U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 8U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 10U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(10U, 4U)), poly.GetBoundaryRangeByIndex(2U));
}

TEST(FreespacePolygon, SetBoundaryType_14)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(3U, 7U, 10U);
    EXPECT_EQ(4U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 3U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(3U, 7U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(7U, 8U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 2U)), poly.GetBoundaryRangeByIndex(3U));
}

TEST(FreespacePolygon, SetBoundaryType_15)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(2U, 7U, 10U);
    EXPECT_EQ(3U, poly.GetBoundarySize());

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 7U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(7U, 8U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 2U)), poly.GetBoundaryRangeByIndex(2U));
}

TEST(FreespacePolygon, SetBoundaryType_16)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(3U, 8U, 10U);
    EXPECT_EQ(3U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 3U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(3U, 8U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 2U)), poly.GetBoundaryRangeByIndex(2U));
}

TEST(FreespacePolygon, SetBoundaryType_17)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(2U, 8U, 10U);
    EXPECT_EQ(2U, poly.GetBoundarySize());

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 8U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 2U)), poly.GetBoundaryRangeByIndex(1U));
}

TEST(FreespacePolygon, SetBoundaryType_18)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(7U, 7U, 10U);
    EXPECT_EQ(1U, poly.GetBoundarySize());

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(0U, 0U)), poly.GetBoundaryRangeByIndex(0U));
}

TEST(FreespacePolygon, SetBoundaryType_19)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(9U, 1U, 10U);
    EXPECT_EQ(6U, poly.GetBoundarySize());

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 2U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 4U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 8U)), poly.GetBoundaryRangeByIndex(3U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(4U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 9U)), poly.GetBoundaryRangeByIndex(4U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(5U));
    EXPECT_EQ((std::pair<size_t, size_t>(9U, 1U)), poly.GetBoundaryRangeByIndex(5U));
}

TEST(FreespacePolygon, SetBoundaryType_20)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(8U, 1U, 10U);
    EXPECT_EQ(5U, poly.GetBoundarySize());

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 2U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 4U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 8U)), poly.GetBoundaryRangeByIndex(3U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(4U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 1U)), poly.GetBoundaryRangeByIndex(4U));
}

TEST(FreespacePolygon, SetBoundaryType_21)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(9U, 2U, 10U);
    EXPECT_EQ(5U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 4U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 8U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 9U)), poly.GetBoundaryRangeByIndex(3U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(4U));
    EXPECT_EQ((std::pair<size_t, size_t>(9U, 2U)), poly.GetBoundaryRangeByIndex(4U));
}

TEST(FreespacePolygon, SetBoundaryType_22)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(8U, 2U, 10U);
    EXPECT_EQ(4U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 4U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 8U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 2U)), poly.GetBoundaryRangeByIndex(3U));
}

TEST(FreespacePolygon, SetBoundaryType_23)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(7U, 1U, 10U);
    EXPECT_EQ(5U, poly.GetBoundarySize());

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 2U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 4U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 7U)), poly.GetBoundaryRangeByIndex(3U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(4U));
    EXPECT_EQ((std::pair<size_t, size_t>(7U, 1U)), poly.GetBoundaryRangeByIndex(4U));
}

TEST(FreespacePolygon, SetBoundaryType_24)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(7U, 2U, 10U);
    EXPECT_EQ(4U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 4U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 7U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(7U, 2U)), poly.GetBoundaryRangeByIndex(3U));
}

TEST(FreespacePolygon, SetBoundaryType_25)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(6U, 1U, 10U);
    EXPECT_EQ(4U, poly.GetBoundarySize());

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(1U, 2U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 4U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 1U)), poly.GetBoundaryRangeByIndex(3U));
}

TEST(FreespacePolygon, SetBoundaryType_26)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(6U, 2U, 10U);
    EXPECT_EQ(3U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(2U, 4U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 2U)), poly.GetBoundaryRangeByIndex(2U));
}

TEST(FreespacePolygon, SetBoundaryType_27)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(9U, 3U, 10U);
    EXPECT_EQ(5U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(3U, 4U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 8U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 9U)), poly.GetBoundaryRangeByIndex(3U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(4U));
    EXPECT_EQ((std::pair<size_t, size_t>(9U, 3U)), poly.GetBoundaryRangeByIndex(4U));
}

TEST(FreespacePolygon, SetBoundaryType_28)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(8U, 3U, 10U);
    EXPECT_EQ(4U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(3U, 4U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 8U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 3U)), poly.GetBoundaryRangeByIndex(3U));
}

TEST(FreespacePolygon, SetBoundaryType_29)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(9U, 4U, 10U);
    EXPECT_EQ(4U, poly.GetBoundarySize());

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 8U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(0U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 9U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(9U, 4U)), poly.GetBoundaryRangeByIndex(3U));
}

TEST(FreespacePolygon, SetBoundaryType_30)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(8U, 4U, 10U);
    EXPECT_EQ(3U, poly.GetBoundarySize());

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 8U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(8U, 4U)), poly.GetBoundaryRangeByIndex(2U));
}

TEST(FreespacePolygon, SetBoundaryType_31)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(7U, 3U, 10U);
    EXPECT_EQ(4U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(3U, 4U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 7U)), poly.GetBoundaryRangeByIndex(2U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(3U));
    EXPECT_EQ((std::pair<size_t, size_t>(7U, 3U)), poly.GetBoundaryRangeByIndex(3U));
}

TEST(FreespacePolygon, SetBoundaryType_32)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(6U, 3U, 10U);
    EXPECT_EQ(3U, poly.GetBoundarySize());

    EXPECT_EQ(1U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(3U, 4U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 3U)), poly.GetBoundaryRangeByIndex(2U));
}

TEST(FreespacePolygon, SetBoundaryType_33)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(7U, 4U, 10U);
    EXPECT_EQ(3U, poly.GetBoundarySize());

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(3U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 7U)), poly.GetBoundaryRangeByIndex(1U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(2U));
    EXPECT_EQ((std::pair<size_t, size_t>(7U, 4U)), poly.GetBoundaryRangeByIndex(2U));
}

TEST(FreespacePolygon, SetBoundaryType_34)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(6U, 4U, 10U);
    EXPECT_EQ(2U, poly.GetBoundarySize());

    EXPECT_EQ(2U, poly.GetBoundaryTypeByIndex(0U));
    EXPECT_EQ((std::pair<size_t, size_t>(4U, 6U)), poly.GetBoundaryRangeByIndex(0U));

    EXPECT_EQ(10U, poly.GetBoundaryTypeByIndex(1U));
    EXPECT_EQ((std::pair<size_t, size_t>(6U, 4U)), poly.GetBoundaryRangeByIndex(1U));
}

TEST(FreespacePolygon, BasicSerializeDeserialize_1)
{
    uint8_t buffer[1024];
    FreespacePolygon                   src, dst;

    holo::serialization::Serializer<>   serializer(buffer, 1024);

    serializer << src;

    ASSERT_EQ(serializer.GetSize(), src.GetSerializedSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> dst;
    ASSERT_EQ(deserializer.GetOffset(), dst.GetSerializedSize());

    EXPECT_EQ(src.size(), dst.size());
    EXPECT_EQ(src.GetBoundarySize(), dst.GetBoundarySize());
}

TEST(FreespacePolygon, BasicSerializeDeserialize_2)
{
    uint8_t buffer[1024];
    FreespacePolygon                   src, dst;

    src = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    holo::serialization::Serializer<>   serializer(buffer, 1024);

    serializer << src;

    ASSERT_EQ(serializer.GetSize(), src.GetSerializedSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> dst;
    ASSERT_EQ(deserializer.GetOffset(), dst.GetSerializedSize());

    EXPECT_EQ(src.size(), dst.size());
    for (size_t i = 0U; i < src.size(); ++i)
    {
        EXPECT_EQ(src[i], dst[i]);
    }

    EXPECT_EQ(src.GetBoundarySize(), dst.GetBoundarySize());
}

TEST(FreespacePolygon, BasicSerializeDeserialize_3)
{
    uint8_t buffer[1024];
    FreespacePolygon                   src, dst;

    src = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};
    src.SetBoundaryType(1, 4, 10);

    holo::serialization::Serializer<>   serializer(buffer, 1024);

    serializer << src;

    ASSERT_EQ(serializer.GetSize(), src.GetSerializedSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> dst;
    ASSERT_EQ(deserializer.GetOffset(), dst.GetSerializedSize());

    EXPECT_EQ(src.size(), dst.size());
    for (size_t i = 0U; i < src.size(); ++i)
    {
        EXPECT_EQ(src[i], dst[i]);
    }

    EXPECT_EQ(src.GetBoundarySize(), dst.GetBoundarySize());
    for (size_t i = 0U; i < src.GetBoundarySize(); ++i)
    {
        EXPECT_EQ(src.GetBoundaryTypeByIndex(i), dst.GetBoundaryTypeByIndex(i));
        EXPECT_EQ(src.GetBoundaryRangeByIndex(i), dst.GetBoundaryRangeByIndex(i));
    }
}

template <size_t POINT_SIZE, size_t INTERIOR_SIZE>
using Exterior = holo::common::FreespaceExterior<holo::geometry::Point2f, POINT_SIZE, INTERIOR_SIZE>;

TEST(FixedSizeFreespaceExterior, Construct)
{
    Exterior<3U, 3U> exterior = {{1, 2}, {2, 4}, {7, 3}};

    EXPECT_EQ(3U, exterior.size());
    EXPECT_THROW(exterior.emplace_back(6, 6), std::bad_alloc);
}

TEST(FixedSizeFreespaceExterior, AddInteriorLvalue)
{
    Exterior<3U, 3U> exterior = {{1, 2}, {2, 4}, {7, 3}};

    Exterior<3U, 3U>::InteriorType i1, i2, i3;

    exterior.AddInterior(i1);
    exterior.AddInterior(i2);
    exterior.AddInterior(i3);
    EXPECT_THROW(exterior.AddInterior(i3), std::bad_alloc);
}

TEST(FixedSizeFreespaceExterior, AddInteriorRvalue)
{
    Exterior<3U, 3U> exterior = {{1, 2}, {2, 4}, {7, 3}};

    Exterior<3U, 3U>::InteriorType i1, i2, i3, i4;

    exterior.AddInterior(std::move(i1));
    exterior.AddInterior(std::move(i2));
    exterior.AddInterior(std::move(i3));
    EXPECT_THROW(exterior.AddInterior(std::move(i4)), std::bad_alloc);
}

TEST(FixedSizeFreespaceExterior, AddInteriorArgs)
{
    Exterior<3U, 3U> exterior = {{1, 2}, {2, 4}, {7, 3}};

    exterior.AddInterior({{1, 2}, {2, 3}, {3, 1}});
    exterior.AddInterior(3);
    exterior.AddInterior(3, holo::geometry::Point2f{1, 1});
    EXPECT_THROW(exterior.AddInterior(), std::bad_alloc);
}

TEST(FixedSizeFreespaceExterior, GetInteriorSize)
{
    Exterior<3U, 3U> exterior = {{1, 2}, {2, 4}, {7, 3}};

    exterior.AddInterior({{1, 2}, {2, 3}, {3, 1}});
    exterior.AddInterior(3);
    exterior.AddInterior(3U, holo::geometry::Point2f{1, 1});
    EXPECT_EQ(3U, exterior.GetInteriorSize());
}

TEST(FixedSizeFreespaceExterior, ClearInterior)
{
    Exterior<3U, 3U> exterior = {{1, 2}, {2, 4}, {7, 3}};

    exterior.AddInterior({{1, 2}, {2, 3}, {3, 1}});
    exterior.AddInterior(3);
    exterior.AddInterior(3U, holo::geometry::Point2f{1, 1});
    EXPECT_EQ(3U, exterior.GetInteriorSize());
    exterior.ClearInterior();
    EXPECT_EQ(0U, exterior.GetInteriorSize());
}

TEST(FixedSizeFreespaceExterior, GetInterior)
{
    Exterior<3U, 3U> exterior = {{1, 2}, {2, 4}, {7, 3}};

    exterior.AddInterior({{1, 2}, {2, 3}, {3, 1}});
    exterior.AddInterior(3);
    exterior.AddInterior(3U, holo::geometry::Point2f{1, 1});
    EXPECT_EQ((Exterior<3U, 3U>::InteriorType({{1, 2}, {2, 3}, {3, 1}})), exterior.GetInterior(0U));
    EXPECT_EQ((Exterior<3U, 3U>::InteriorType(3)), exterior.GetInterior(1U));
    EXPECT_EQ((Exterior<3U, 3U>::InteriorType(3, {1, 1})), exterior.GetInterior(2U));

    Exterior<3U, 3U> const& exterior2 = exterior;
    EXPECT_EQ((Exterior<3U, 3U>::InteriorType({{1, 2}, {2, 3}, {3, 1}})), exterior2.GetInterior(0U));
    EXPECT_EQ((Exterior<3U, 3U>::InteriorType(3)), exterior2.GetInterior(1U));
    EXPECT_EQ((Exterior<3U, 3U>::InteriorType(3, {1, 1})), exterior2.GetInterior(2U));
}

TEST(FixedSizeFreespaceExterior, EraseInterior)
{
    Exterior<3U, 3U> exterior = {{1, 2}, {2, 4}, {7, 3}};

    exterior.AddInterior({{1, 2}, {2, 3}, {3, 1}});
    exterior.AddInterior(3);
    exterior.AddInterior(3U, holo::geometry::Point2f{1, 1});
    EXPECT_EQ(3U, exterior.GetInteriorSize());
    exterior.EraseInterior(0U);
    EXPECT_EQ(2U, exterior.GetInteriorSize());
    EXPECT_EQ((Exterior<3U, 3U>::InteriorType(3)), exterior.GetInterior(0U));
}

TEST(AutoFreespaceExterior, Constructor)
{
    Exterior<std::numeric_limits<size_t>::max(), 3U> exterior(10, {1, 1});
    EXPECT_EQ(10U, exterior.size());
}

TEST(AutoFreespaceExterior, DynamicSize)
{
    Exterior<std::numeric_limits<size_t>::max(), 3U> exterior(10, {1, 1});
    EXPECT_EQ(10U, exterior.size());
    exterior.resize(20, {2, 2});
    EXPECT_EQ(20U, exterior.size());
}

TEST(AutoFreespaceExterior, DynamicInteriorPointSize)
{
    Exterior<std::numeric_limits<size_t>::max(), 3U> exterior(10, {1, 1});
    exterior.AddInterior(10, holo::geometry::Point2f{2, 2});
    EXPECT_EQ(10U, exterior.GetInterior(0U).size());
    exterior.GetInterior(0U).emplace_back(3, 4);
    EXPECT_EQ(11U, exterior.GetInterior(0U).size());
}

TEST(AutoFreespaceExterior, DynamicInteriorSize)
{
    Exterior<std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max()> exterior(10, {1, 1});
    for (size_t i = 0; i < 100U; ++i)
    {
        exterior.AddInterior(10, holo::geometry::Point2f{2, 2});
    }
    EXPECT_EQ(100U, exterior.GetInteriorSize());
}

TEST(AutoFreespace, BasicSerializeDeserialize_1)
{
    uint8_t buffer[1024];
    holo::common::AutoFreespace<holo::geometry::Point2f> src, dst;

    holo::serialization::Serializer<>   serializer(buffer, 1024);

    serializer << src;

    ASSERT_EQ(serializer.GetSize(), src.GetSerializedSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> dst;
    ASSERT_EQ(deserializer.GetOffset(), dst.GetSerializedSize());

    ASSERT_EQ(src.size(), dst.size());        // exterior size should be equal
    for (size_t i = 0U; i < src.size(); ++i)  // for each exterior
    {
        ASSERT_EQ(src[i].size(), dst[i].size());  // size of vertices should be equal
        for (size_t pt_idx = 0U; pt_idx < src[i].size(); ++pt_idx)
        {
            EXPECT_EQ(src[i][pt_idx], dst[i][pt_idx]);  // each vertice should be equal
        }
        EXPECT_EQ(src[i].GetBoundarySize(), dst[i].GetBoundarySize());  // exterior boundary size should be equal
        for (size_t bd_idx = 0U; bd_idx < src[i].GetBoundarySize(); ++bd_idx)
        {
            // exterior boundary should be equal
            EXPECT_EQ(src[i].GetBoundaryTypeByIndex(bd_idx), dst[i].GetBoundaryTypeByIndex(bd_idx));
            EXPECT_EQ(src[i].GetBoundaryRangeByIndex(bd_idx), dst[i].GetBoundaryRangeByIndex(bd_idx));
        }

        ASSERT_EQ(src[i].GetInteriorSize(),
                  dst[i].GetInteriorSize());  // interior size of each exterior should be equal
        for (size_t it_idx = 0U; it_idx < src[i].GetInteriorSize(); ++it_idx)
        {
            ASSERT_EQ(src[i].GetInterior(it_idx).size(), dst[i].GetInterior(it_idx).size());
            for (size_t it_pt_idx = 0U; it_pt_idx < src[i].GetInterior(it_idx).size(); ++it_pt_idx)
            {
                EXPECT_EQ(src[i].GetInterior(it_idx)[it_pt_idx], dst[i].GetInterior(it_idx)[it_pt_idx]);
            }
            EXPECT_EQ(src[i].GetInterior(it_idx).GetBoundarySize(), dst[i].GetInterior(it_idx).GetBoundarySize());
            for (size_t it_bd_idx = 0U; it_bd_idx < src[i].GetInterior(it_idx).GetBoundarySize(); ++it_bd_idx)
            {
                // interior boundary should be equal
                EXPECT_EQ(src[i].GetInterior(it_idx).GetBoundaryTypeByIndex(it_bd_idx),
                          dst[i].GetInterior(it_idx).GetBoundaryTypeByIndex(it_bd_idx));
                EXPECT_EQ(src[i].GetInterior(it_idx).GetBoundaryRangeByIndex(it_bd_idx),
                          dst[i].GetInterior(it_idx).GetBoundaryRangeByIndex(it_bd_idx));
            }
        }
    }
}

TEST(AutoFreespace, BasicSerializeDeserialize_2)
{
    uint8_t buffer[1024];
    holo::common::AutoFreespace<holo::geometry::Point2f> src, dst;

    src = {{{1, 2}, {3, 4}, {5, 6}, {7, 8}}, {{8, 7}, {6, 5}, {4, 3}, {2, 1}}};

    src[0].AddInterior({{1, 1}, {2, 2}, {3, 3}, {4, 4}});
    src[1].AddInterior({{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}});

    holo::serialization::Serializer<>   serializer(buffer, 1024);

    serializer << src;

    ASSERT_EQ(serializer.GetSize(), src.GetSerializedSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> dst;
    ASSERT_EQ(deserializer.GetOffset(), dst.GetSerializedSize());

    ASSERT_EQ(src.size(), dst.size());        // exterior size should be equal
    for (size_t i = 0U; i < src.size(); ++i)  // for each exterior
    {
        ASSERT_EQ(src[i].size(), dst[i].size());  // size of vertices should be equal
        for (size_t pt_idx = 0U; pt_idx < src[i].size(); ++pt_idx)
        {
            EXPECT_EQ(src[i][pt_idx], dst[i][pt_idx]);  // each vertice should be equal
        }
        EXPECT_EQ(src[i].GetBoundarySize(), dst[i].GetBoundarySize());  // exterior boundary size should be equal
        for (size_t bd_idx = 0U; bd_idx < src[i].GetBoundarySize(); ++bd_idx)
        {
            // exterior boundary should be equal
            EXPECT_EQ(src[i].GetBoundaryTypeByIndex(bd_idx), dst[i].GetBoundaryTypeByIndex(bd_idx));
            EXPECT_EQ(src[i].GetBoundaryRangeByIndex(bd_idx), dst[i].GetBoundaryRangeByIndex(bd_idx));
        }

        ASSERT_EQ(src[i].GetInteriorSize(),
                  dst[i].GetInteriorSize());  // interior size of each exterior should be equal
        for (size_t it_idx = 0U; it_idx < src[i].GetInteriorSize(); ++it_idx)
        {
            ASSERT_EQ(src[i].GetInterior(it_idx).size(), dst[i].GetInterior(it_idx).size());
            for (size_t it_pt_idx = 0U; it_pt_idx < src[i].GetInterior(it_idx).size(); ++it_pt_idx)
            {
                EXPECT_EQ(src[i].GetInterior(it_idx)[it_pt_idx], dst[i].GetInterior(it_idx)[it_pt_idx]);
            }
            EXPECT_EQ(src[i].GetInterior(it_idx).GetBoundarySize(), dst[i].GetInterior(it_idx).GetBoundarySize());
            for (size_t it_bd_idx = 0U; it_bd_idx < src[i].GetInterior(it_idx).GetBoundarySize(); ++it_bd_idx)
            {
                // interior boundary should be equal
                EXPECT_EQ(src[i].GetInterior(it_idx).GetBoundaryTypeByIndex(it_bd_idx),
                          dst[i].GetInterior(it_idx).GetBoundaryTypeByIndex(it_bd_idx));
                EXPECT_EQ(src[i].GetInterior(it_idx).GetBoundaryRangeByIndex(it_bd_idx),
                          dst[i].GetInterior(it_idx).GetBoundaryRangeByIndex(it_bd_idx));
            }
        }
    }
}

TEST(FreespacePolygon, insertPositiveOrderWithIterators)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 0U);
    poly.SetBoundaryType(2, 6U, 2U);
    poly.SetBoundaryType(2, 8U, 2U);
    poly.SetBoundaryType(4, 6U, 10U);
}

TEST(FreespacePolygon, insertNegativeOrderWithIterators)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(4U, 4U, 10U);
    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);
    poly.SetBoundaryType(9U, 2U, 10U);
    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(8U, 2U, 10U);
}

TEST(FreespacePolygon, insertNegativeOrder)
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};
 
    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(6, 1U, 3U);
    poly.SetBoundaryType(9U, 3U, 10U);
}

TEST(FreespacePolygon, insertPositiveOrderSegment) //333
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);
    poly.SetBoundaryType(6, 6U, 2U);
}

TEST(FreespacePolygon, insertPositiveOrderSegment_2xxx)///444
{
    FreespacePolygon poly = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}, {2, 4}, {1, 5}, {0, 6}, {-1, 3}, {-2, 3}, {-3, 1}};

    poly.SetBoundaryType(2, 4U, 1U);
    poly.SetBoundaryType(4, 6U, 2U);
    poly.SetBoundaryType(6, 8U, 3U);

    poly.SetBoundaryType(3U, 7U, 10U);
    poly.SetBoundaryType(7U, 7U, 10U);

}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
