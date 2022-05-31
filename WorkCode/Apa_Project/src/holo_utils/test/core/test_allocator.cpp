/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_deserializer_host_4.cpp
 * @brief Unit test for 4 byte aligned host byte order deserializer.
 * @author zhangjiannan(zhangjiannan@holomatic.com)
 * @date 2022-2-22
 */

#include <gtest/gtest.h>

#include <holo/core/allocator.h>
#include <holo/core/types.h>
#include <iostream>
#include <vector>
#include <map>
#include <list>

TEST(HoloAllocator, list_allocate)
{
    std::list<int, holo::core::Allocator<int, 10>> l1, l2;
    l1 = {1, 2, 3, 4, 5};
    ASSERT_EQ(10U, l1.max_size());
    ASSERT_EQ(10U, l2.max_size());
    ASSERT_EQ(5U, l1.size());
    ASSERT_EQ(0U, l2.size());
    l2 = l1;
    l2.insert(l2.end(), l1.begin(), l1.end());
    ASSERT_EQ(10U, l2.size());
    EXPECT_THROW(l2.push_back(10), std::bad_alloc);
    l1 = l2;
    std::list<int, holo::core::Allocator<int, 10>> l3;
    l3 = std::move(l1);
    ASSERT_EQ(10U, l3.size());
    ASSERT_EQ(10U, *l3.get_allocator().p_allocated_size_);
    std::list<int, holo::core::Allocator<int, 10>> l4 = {1,2,3,4};
    std::swap(l4, l3);
    EXPECT_EQ(10U, *l4.get_allocator().p_allocated_size_);
    EXPECT_EQ(4U, *l3.get_allocator().p_allocated_size_);
}

TEST(HoloAllocator, map_allocate)
{
    std::map<int, int, std::less<int>, holo::core::Allocator<std::pair<int, int>, 10>> m1, m2;
    m1 = {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1} };
    ASSERT_EQ(10U, m1.max_size());
    ASSERT_EQ(10U, m2.max_size());
    ASSERT_EQ(5U, m1.size());
    ASSERT_EQ(0U, m2.size());
    m2 = m1;
    m2.insert({{6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1} });
    ASSERT_EQ(10U, m2.size());
    EXPECT_THROW(m2.insert({11, 1}), std::bad_alloc);
    m1 = m2;
}

TEST(HoloAllocator, vector_allocate)
{
    std::vector<int, holo::core::Allocator<int, 10>> v1, v2;
    v1.reserve(10);
    v2.reserve(10);
    v1 = {1, 2, 3, 4, 5};
    ASSERT_EQ(10U, v1.max_size());
    ASSERT_EQ(10U, v2.max_size());
    ASSERT_EQ(5U, v1.size());
    ASSERT_EQ(0U, v2.size());
    //ASSERT_EQ(5U, *v1.get_allocator().p_allocated_size_);
    //ASSERT_EQ(0U, *v2.get_allocator().p_allocated_size_);
    v2 = v1;
    //ASSERT_EQ(5U, *v1.get_allocator().p_allocated_size_);
    //ASSERT_EQ(5U, *v2.get_allocator().p_allocated_size_);
    v2.insert(v2.end(), {6, 7, 8, 9, 10});
    ASSERT_EQ(10U, v2.size());
    EXPECT_THROW(v2.push_back(11), std::length_error);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
