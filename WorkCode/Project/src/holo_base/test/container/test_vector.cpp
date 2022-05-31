/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_vector.cpp
 * @brief Unit test for holo::container::Vector.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-21
 */

#include <gtest/gtest.h>
#include <holo/container/vector.h>
#include <holo/geometry/point2.h>

template <typename T, size_t SIZE>
using Vector = holo::container::Vector<T, SIZE>;
using Point2 = holo::geometry::Point2f;
TEST(FixedSizeVector, DefaultConstructor)
{
    Vector<int, 10> vec;
}

TEST(FixedSizeVector, ConstructWithCountElements)
{
    Vector<int, 10> vec1(0, 0);
    Vector<int, 10> vec2(1, 1);
    Vector<int, 10> vec3(10, 1);
    try
    {
        Vector<int, 10> vec4(11, 1);
        FAIL() << "Expect throw exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
    Vector<int, 10> vec5(5);
    try
    {
        Vector<int, 10> vec6(120);
    }
    catch(...)
    {
    }
}

TEST(FixedSizeVector, ConstructorWithIterators)
{
    int             arr[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int, 10> vec1(&arr[0], &arr[0]);
    ASSERT_EQ(vec1, (Vector<int, 10>({})));
    Vector<int, 10> vec2(&arr[0], &arr[1]);
    ASSERT_EQ(vec2, (Vector<int, 10>({0})));
    Vector<int, 10> vec3(&arr[0], &arr[10]);
    ASSERT_EQ(vec3, (Vector<int, 10>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})));
    try
    {
        Vector<int, 10> vec4(&arr[0], &arr[11]);
        FAIL() << "Expect throw exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }

    try
    {
        Vector<int, 10> vec5(&arr[10], &arr[1]);
        FAIL() << "Expect throw exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(FixedSizeVector, CopyConstructor)
{
    Vector<int, 10> vec1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Vector<int, 10> vec2(vec1);
    ASSERT_EQ(vec2, vec1);

    try
    {
        Vector<int, 5> vec3(vec2);
        FAIL() << "Expect throw exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
}

TEST(FixedSizeVector, MoveConstructor)
{
    Vector<int, 10> vec1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int*            p = &vec1.front();
    Vector<int, 10> vec2(std::move(vec1));
    int*            p2 = &vec2.front();
    ASSERT_EQ(p, p2);

    try
    {
        Vector<int, 5> vec3(std::move(vec2));
        FAIL() << "Expect throw exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
}

TEST(FixedSizeVector, ConstructWithInitializerList)
{
    Vector<int, 10> vec1;
    for (size_t i = 0; i < 10; ++i)
    {
        vec1.push_back(i);
    }
    Vector<int, 10> vec2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_EQ(vec1, vec2);

    try
    {
        Vector<int, 5> vec2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        FAIL() << "Expect throw exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
}

TEST(FixedSizeVector, ConstructWithFixedSizeVectorOfDifferentSize)
{
    Vector<int, 10> vec1 = {1, 2, 3};
    Vector<int, 20> vec2(vec1);
    ASSERT_EQ((Vector<int, 20>{1, 2, 3}), vec2);
    Vector<int, 5> vec3(vec2);
    ASSERT_EQ((Vector<int, 5>{1, 2, 3}), vec3);
}

TEST(FixedSizeVector, ConstructWithFixedSizeVectorOfDifferentSizeRValue)
{
    Vector<int, 10> vec1 = {1, 2, 3};
    Vector<int, 20> vec2(std::move(vec1));
    ASSERT_EQ((Vector<int, 20>{1, 2, 3}), vec2);
    Vector<int, 5> vec3(std::move(vec2));
    ASSERT_EQ((Vector<int, 5>{1, 2, 3}), vec3);
}

TEST(FixedSizeVector, AssignOperatorLvalue)
{
    Vector<int, 10> vec1{1, 2, 3, 4, 5, 6, 7, 8};
    Vector<int, 10> vec2;
    vec2 = vec1;
    ASSERT_EQ(vec1, vec2);
}

TEST(FixedSizeVector, AssignOperatorRvalue)
{
    Vector<int, 10> vec1{1, 2, 3, 4, 5, 6, 7, 8};
    int*            p1 = &vec1[0];
    Vector<int, 10> vec2;
    vec2    = std::move(vec1);
    int* p2 = &vec2[0];
    ASSERT_EQ(p1, p2);
}

TEST(FixedSizeVector, AssignOperatorInitializerList)
{
    Vector<int, 10> vec1{1, 2, 3, 4, 5};
    Vector<int, 10> vec2;
    vec2 = {1, 2, 3, 4, 5};
    ASSERT_EQ(vec2, vec1);
    EXPECT_THROW((vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}), std::bad_alloc);
}

TEST(FixedSizeVector, AssignWithCountElements)
{
    Vector<int, 10> vec;
    vec.assign(1, 10);
    ASSERT_EQ(vec, (Vector<int, 10>{10}));
    vec.assign(2, 20);
    ASSERT_EQ(vec, (Vector<int, 10>{20, 20}));
    EXPECT_THROW(vec.assign(11, 1), std::bad_alloc);
}

TEST(FixedSizeVector, AssignWithInputIterator)
{
    int             arr[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12};
    Vector<int, 10> vec;
    vec.assign(&arr[0], &arr[0]);
    ASSERT_EQ(vec, (Vector<int, 10>{}));
    vec.assign(&arr[0], &arr[1]);
    ASSERT_EQ(vec, (Vector<int, 10>{1}));
    vec.assign(&arr[0], &arr[3]);
    ASSERT_EQ(vec, (Vector<int, 10>{1, 2, 3}));
    EXPECT_THROW((vec.assign(&arr[0], &arr[12])), std::bad_alloc);
    EXPECT_THROW((vec.assign(&arr[1], &arr[0])), std::bad_alloc);
}

TEST(FixedSizeVector, AssignWithInitializerList)
{
    Vector<int, 10> vec;
    vec.assign({});
    ASSERT_EQ(vec, (Vector<int, 10>{}));
    vec.assign({1});
    ASSERT_EQ(vec, (Vector<int, 10>{1}));
    vec.assign({1, 2, 3});
    ASSERT_EQ(vec, (Vector<int, 10>{1, 2, 3}));
    EXPECT_THROW(vec.assign({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}), std::bad_alloc);
}

TEST(FixedSizeVector, AssignWithFixedSizeVectorOfDifferentSize)
{
    Vector<int, 10> vec1 = {1, 2, 3};
    Vector<int, 20> vec2;
    vec2 = vec1;
    ASSERT_EQ((Vector<int, 20>{1, 2, 3}), vec2);
    Vector<int, 5> vec3;
    vec3 = vec2;
    ASSERT_EQ((Vector<int, 5>{1, 2, 3}), vec3);
}

TEST(FixedSizeVector, AssignWithFixedSizeVectorOfDifferentSizeRValue)
{
    Vector<int, 10> vec1 = {1, 2, 3};
    Vector<int, 20> vec2;
    vec2 = std::move(vec1);
    ASSERT_EQ((Vector<int, 20>{1, 2, 3}), vec2);
    Vector<int, 5> vec3;
    vec3 = std::move(vec2);
    ASSERT_EQ((Vector<int, 5>{1, 2, 3}), vec3);
}

TEST(FixedSizeVector, GetAllocator)
{
    Vector<int, 10> vec;
    vec.get_allocator();
}

TEST(FixedSizeVector, At)
{
    Vector<int, 10>        vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int, 10> const& vec2 = vec;
    ASSERT_EQ(1, vec.at(0));
    ASSERT_EQ(2, vec.at(1));
    ASSERT_EQ(10, vec.at(9));
    EXPECT_THROW(vec.at(10), std::out_of_range);

    ASSERT_EQ(1, vec2.at(0));
    ASSERT_EQ(2, vec2.at(1));
    ASSERT_EQ(10, vec2.at(9));
    EXPECT_THROW(vec2.at(10), std::out_of_range);
}

TEST(FixedSizeVector, BracketOperator)
{
    Vector<int, 10>        vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int, 10> const& vec2 = vec;
    ASSERT_EQ(1, vec[0]);
    ASSERT_EQ(2, vec[1]);
    ASSERT_EQ(10, vec[9]);
    ASSERT_EQ(1, vec2[0]);
    ASSERT_EQ(2, vec2[1]);
    ASSERT_EQ(10, vec2[9]);
}

TEST(FixedSizeVector, Front)
{
    Vector<int, 10>        vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int, 10> const& vec2 = vec;
    ASSERT_EQ(1, vec.front());
    ASSERT_EQ(1, vec2.front());
}

TEST(FixedSizeVector, Back)
{
    Vector<int, 10>        vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int, 10> const& vec2 = vec;
    ASSERT_EQ(10, vec.back());
    ASSERT_EQ(10, vec2.back());
}

TEST(FixedSizeVector, Data)
{
    Vector<int, 10> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(1, vec.data()[0]);
    ASSERT_EQ(2, vec.data()[1]);
    ASSERT_EQ(10, vec.data()[9]);
}

TEST(FixedSizeVector, Begin)
{
    Vector<int, 10> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(1, *vec.begin());
    ASSERT_EQ(1, *vec.cbegin());
    *vec.begin() = 2;
    ASSERT_EQ(2, *vec.begin());
    ASSERT_EQ(2, *vec.cbegin());
}

TEST(FixedSizeVector, End)
{
    Vector<int, 10> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(10, *(vec.end() - 1));
    ASSERT_EQ(10, *(vec.cend() - 1));
    *(vec.end() - 1) = 11;
    ASSERT_EQ(11, *(vec.end() - 1));
    ASSERT_EQ(11, *(vec.cend() - 1));
}

TEST(FixedSizeVector, Rbegin)
{
    Vector<int, 10> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(10, *vec.rbegin());
    ASSERT_EQ(10, *vec.crbegin());
    *vec.rbegin() = 11;
    ASSERT_EQ(11, *vec.rbegin());
    ASSERT_EQ(11, *vec.crbegin());
}

TEST(FixedSizeVector, Rend)
{
    Vector<int, 10> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(1, *(vec.rend() - 1));
    ASSERT_EQ(1, *(vec.crend() - 1));
    *(vec.rend() - 1) = 2;
    ASSERT_EQ(2, *(vec.rend() - 1));
    ASSERT_EQ(2, *(vec.crend() - 1));
}

TEST(FixedSizeVector, Empty)
{
    Vector<int, 10> vec;
    ASSERT_EQ(true, vec.empty());
    vec = {1};
    ASSERT_EQ(false, vec.empty());
}

TEST(FixedSizeVector, Size)
{
    Vector<int, 10> vec;
    ASSERT_EQ(0U, vec.size());
    vec.assign({1});
    ASSERT_EQ(1U, vec.size());
    vec.assign({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    ASSERT_EQ(10U, vec.size());
}

TEST(FixedSizeVector, MaxSize)
{
    Vector<int, 10> vec1;
    ASSERT_EQ(10U, vec1.max_size());
    Vector<int, 100> vec2;
    ASSERT_EQ(100U, vec2.max_size());
}

TEST(FixedSizeVector, Reserve)
{
    Vector<int, 10> vec;
    vec.reserve(8);
    EXPECT_THROW(vec.reserve(11), std::bad_alloc);
}

TEST(FixedSizeVector, Capacity)
{
    Vector<int, 0> vec1;
    ASSERT_EQ(0U, vec1.capacity());
    Vector<int, 10> vec2;
    ASSERT_EQ(10U, vec2.capacity());
}

TEST(FixedSizeVector, ShrinkToFit)
{
    Vector<int, 10> vec1;
    vec1.shrink_to_fit();
}

TEST(FixedSizeVector, Clear)
{
    Vector<int, 10> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vec.clear();
    ASSERT_EQ(0U, vec.size());
}

TEST(FixedSizeVector, InsertWithPosLvalue)
{
    Vector<int, 10> vec{1, 2, 3};
    int             value = 0;
    auto            it    = vec.insert(vec.begin(), value);
    ASSERT_EQ(0, *it);
    ASSERT_EQ(4U, vec.size());
    value = 4;
    it    = vec.insert(vec.end(), value);
    ASSERT_EQ(4, *it);
    ASSERT_EQ(5U, vec.size());

    Vector<int, 10> vec2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_THROW(vec2.insert(vec2.begin(), value), std::bad_alloc);
}

TEST(FixedSizeVector, InsertWithPosRvalue)
{
    Vector<int, 10> vec{1, 2, 3};
    int             value = 0;
    auto            it    = vec.insert(vec.begin(), std::move(value));
    ASSERT_EQ(0, *it);
    ASSERT_EQ(4U, vec.size());
    value = 4;
    it    = vec.insert(vec.end(), std::move(value));
    ASSERT_EQ(4, *it);
    ASSERT_EQ(5U, vec.size());

    Vector<int, 10> vec2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_THROW(vec2.insert(vec2.begin(), std::move(value)), std::bad_alloc);
}

TEST(FixedSizeVector, InsertWithPosInputIterator)
{
    int             arr[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int, 10> vec{5};

    auto it = vec.insert(vec.begin(), &arr[0], &arr[5]);
    ASSERT_EQ(0, *it);
    ASSERT_EQ(6, vec.size());

    it = vec.insert(vec.end(), &arr[6], &arr[10]);
    ASSERT_EQ(6, *it);
    ASSERT_EQ(10, vec.size());

    vec.assign({});
    EXPECT_THROW(vec.insert(vec.begin(), &arr[0], &arr[11]), std::bad_alloc);
}

TEST(FixedSizeVector, InsertWithInitializerList)
{
    Vector<int, 10> vec;
    auto            it = vec.insert(vec.begin(), {1, 2, 3});
    ASSERT_EQ(1, *it);
    ASSERT_EQ(3U, vec.size());
    it = vec.insert(vec.end(), {4, 5, 6});
    ASSERT_EQ(4, *it);
    ASSERT_EQ(6, vec.size());

    EXPECT_THROW(vec.insert(vec.begin(), {1, 2, 3, 4, 5}), std::bad_alloc);
}

TEST(FixedSizeVector, Emplace)
{
    Vector<int, 10> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    auto            it  = vec.emplace(vec.begin(), 0);
    ASSERT_EQ(0, *it);

    it = vec.emplace(vec.end(), 9);
    ASSERT_EQ(9, *it);

    EXPECT_THROW(vec.emplace(vec.end(), 10), std::bad_alloc);
}

TEST(FixedSizeVector, EraseWithPos)
{
    Vector<int, 10> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto            it  = vec.erase(vec.begin());
    ASSERT_EQ(1, *it);
    ASSERT_EQ(9U, vec.size());

    it = vec.erase(vec.end() - 1);
    ASSERT_EQ(vec.end(), it);
    ASSERT_EQ(8U, vec.size());
}

TEST(FixedSizeVector, EraseWithIteratorRange)
{
    Vector<int, 10> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto            it  = vec.erase(vec.begin(), vec.begin());
    ASSERT_EQ(0, *it);
    ASSERT_EQ(10U, vec.size());

    it = vec.erase(vec.begin(), vec.begin() + 1);
    ASSERT_EQ(1, *it);
    ASSERT_EQ(9U, vec.size());

    it = vec.erase(vec.end() - 1, vec.end());
    ASSERT_EQ(vec.end(), it);
    ASSERT_EQ(8U, vec.size());
}

TEST(FixedSizeVector, PushBack)
{
    Vector<int, 10> vec{0, 1, 2, 3, 4, 5, 6, 7, 8};
    int             value = 9;
    vec.push_back(value);
    ASSERT_EQ(value, *(vec.end() - 1));
    EXPECT_THROW(vec.push_back(value), std::bad_alloc);

    vec = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    vec.push_back(std::move(value));
    ASSERT_EQ(value, *(vec.end() - 1));
    EXPECT_THROW(vec.push_back(std::move(value)), std::bad_alloc);
}

TEST(FixedSizeVector, EmplaceBack)
{
    Vector<int, 10> vec{0, 1, 2, 3, 4, 5, 6, 7, 8};
    int             value = 9;
    vec.emplace_back(value);
    ASSERT_EQ(value, *(vec.end() - 1));
    EXPECT_THROW(vec.emplace_back(value), std::bad_alloc);
}

TEST(FixedSizeVector, PopBack)
{
    Vector<int, 10> vec{0, 1, 2, 3, 4};
    vec.pop_back();
    ASSERT_EQ(4U, vec.size());
}

TEST(FixedSizeVector, Resize)
{
    Vector<int, 10> vec = {0, 1, 2, 3};
    vec.resize(3);
    ASSERT_EQ((Vector<int, 10>{0, 1, 2}), vec);
    vec.resize(5);
    ASSERT_EQ((Vector<int, 10>{0, 1, 2, 0, 0}), vec);
    EXPECT_THROW(vec.resize(11), std::bad_alloc);
}

TEST(FixedSizeVector, Swap)
{
    Vector<int, 10> vec1 = {1, 2, 3, 4, 5};
    Vector<int, 10> vec2 = {6, 7, 8, 9, 10};
    Vector<int, 3> vec3 = {6, 7, 8};
    vec1.swap(vec2);
    ASSERT_EQ((Vector<int, 10>{6, 7, 8, 9, 10}), vec1);
    ASSERT_EQ((Vector<int, 10>{1, 2, 3, 4, 5}), vec2);
    EXPECT_THROW(vec3.swap(vec2), std::bad_alloc);
}

TEST(FixedSizeVector, SwapDifferentSize)
{
    Vector<int, 10>  vec1 = {1, 2, 3, 4, 5};
    Vector<int, 100> vec2 = {6, 7, 8, 9, 10};
    vec1.swap(vec2);
    ASSERT_EQ((Vector<int, 10>{6, 7, 8, 9, 10}), vec1);
    ASSERT_EQ((Vector<int, 10>{1, 2, 3, 4, 5}), vec2);
    ASSERT_EQ(10U, vec1.capacity());
    ASSERT_EQ(100U, vec2.capacity());
}

TEST(FixedSizeVectorStandaloneFunctions, Equals)
{
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} == Vector<int, 10>{1, 2, 3, 4, 5}));
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} == Vector<int, 10>{1, 2, 3, 4}));
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} == Vector<int, 10>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, EqualsDifferentSize)
{
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} == Vector<int, 20>{1, 2, 3, 4, 5}));
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} == Vector<int, 20>{1, 2, 3, 4}));
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} == Vector<int, 20>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, NotEqual)
{
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} != Vector<int, 10>{1, 2, 3, 4, 5}));
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} != Vector<int, 10>{1, 2, 3, 4}));
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} != Vector<int, 10>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, NotEqualDifferentSize)
{
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} != Vector<int, 20>{1, 2, 3, 4, 5}));
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} != Vector<int, 20>{1, 2, 3, 4}));
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} != Vector<int, 20>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, Greater)
{
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} > Vector<int, 10>{1, 2, 3, 4, 5}));
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} > Vector<int, 10>{1, 2, 3, 4}));
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} > Vector<int, 10>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, GreaterDifferentSize)
{
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} > Vector<int, 20>{1, 2, 3, 4, 5}));
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} > Vector<int, 20>{1, 2, 3, 4}));
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} > Vector<int, 20>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, GreaterEqual)
{
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} >= Vector<int, 10>{1, 2, 3, 4, 5}));
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} >= Vector<int, 10>{1, 2, 3, 4}));
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} >= Vector<int, 10>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, GreaterEqualDifferentSize)
{
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} >= Vector<int, 20>{1, 2, 3, 4, 5}));
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} >= Vector<int, 20>{1, 2, 3, 4}));
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} >= Vector<int, 20>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, Less)
{
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} < Vector<int, 10>{1, 2, 3, 4, 5}));
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} < Vector<int, 10>{1, 2, 3, 4}));
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} < Vector<int, 10>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, LessDifferentSize)
{
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} < Vector<int, 20>{1, 2, 3, 4, 5}));
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} < Vector<int, 20>{1, 2, 3, 4}));
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} < Vector<int, 20>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, LessEqual)
{
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} <= Vector<int, 10>{1, 2, 3, 4, 5}));
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} <= Vector<int, 10>{1, 2, 3, 4}));
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} <= Vector<int, 10>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, LessEqualDifferentSize)
{
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} <= Vector<int, 20>{1, 2, 3, 4, 5}));
    ASSERT_FALSE((Vector<int, 10>{1, 2, 3, 4, 5} <= Vector<int, 20>{1, 2, 3, 4}));
    ASSERT_TRUE((Vector<int, 10>{1, 2, 3, 4, 5} <= Vector<int, 20>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, Swap)
{
    Vector<int, 10> vec1 = {1, 2, 3, 4, 5};
    Vector<int, 10> vec2 = {6, 7, 8, 9, 10};
    swap(vec1, vec2);
    ASSERT_EQ((Vector<int, 10>{6, 7, 8, 9, 10}), vec1);
    ASSERT_EQ((Vector<int, 10>{1, 2, 3, 4, 5}), vec2);
}

TEST(ManualVector, DefaultConstructor)
{
    Vector<int, 0> vec;
}

TEST(ManualVector, ConstructWithCountElements)
{
    Vector<int, 0> vec1(0, 0);
    Vector<int, 0> vec2(1, 1);
    Vector<int, 0> vec3(10, 1);
    EXPECT_EQ(0U, vec1.capacity());
    EXPECT_EQ(1U, vec2.capacity());
    EXPECT_EQ(10U, vec3.capacity());
}

TEST(ManualVector, ConstructorWithIterators)
{
    int            arr[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int, 0> vec1(&arr[0], &arr[0]);
    EXPECT_EQ(vec1, (Vector<int, 0>({})));
    Vector<int, 0> vec2(&arr[0], &arr[1]);
    ASSERT_EQ(vec2, (Vector<int, 10>({0})));
    Vector<int, 0> vec3(&arr[0], &arr[10]);
}

TEST(ManualVector, CopyConstructor)
{
    Vector<int, 0> vec1(5, 30);
    Vector<int, 0> vec2(vec1);
    ASSERT_EQ(vec2, vec1);
}

TEST(ManualVector, MoveConstructor)
{
    Vector<int, 0> vec1(5, 20);
    int*           p = &vec1.front();
    Vector<int, 0> vec2(std::move(vec1));
    int*           p2 = &vec2.front();
    ASSERT_EQ(p, p2);
}

TEST(ManualVector, ConstructWithInitializerList)
{
    Vector<int, 0> vec1;
    vec1.reserve(10);
    for (size_t i = 0; i < 10; ++i)
    {
        vec1.push_back(i);
    }
    Vector<int, 0> vec2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_EQ(vec1, vec2);
}

TEST(ManualVector, ConstructWithManualVectorOfDifferentSize)
{
    Vector<int, 10> vec1 = {1, 2, 3};
    Vector<int, 0>  vec2(vec1);
    ASSERT_EQ((Vector<int, 0>{1, 2, 3}), vec2);
    Vector<int, 0> vec3(vec2);
    ASSERT_EQ((Vector<int, 5>{1, 2, 3}), vec3);
}

TEST(ManualVector, ConstructWithManualVectorOfDifferentSizeRValue)
{
    Vector<int, 10> vec1 = {1, 2, 3};
    Vector<int, 0>  vec2(std::move(vec1));
    ASSERT_EQ((Vector<int, 20>{1, 2, 3}), vec2);
    Vector<int, 0> vec3(std::move(vec2));
    ASSERT_EQ((Vector<int, 5>{1, 2, 3}), vec3);
}

TEST(ManualVector, AssignOperatorLvalue)
{
    Vector<int, 0> vec1{1, 2, 3, 4, 5, 6, 7, 8};
    Vector<int, 0> vec2;
    vec2.reserve(10U);
    vec2 = vec1;
    EXPECT_EQ(vec1, vec2);

    Vector<int, 0> vec3;
    EXPECT_THROW((vec3 = vec1), std::bad_alloc);
}

TEST(ManualVector, AssignOperatorRvalue)
{
    Vector<int, 0> vec1{1, 2, 3, 4, 5, 6, 7, 8};
    vec1.reserve(20U);
    int*           p1 = &vec1[0];
    Vector<int, 0> vec2;
    vec2.reserve(10U);
    vec2    = std::move(vec1);
    int* p2 = &vec2[0];
    EXPECT_EQ(p1, p2);

    Vector<int, 0> vec3;
    EXPECT_THROW((vec3 = std::move(vec2)), std::bad_alloc);
}

TEST(ManualVector, AssignOperatorInitializerList)
{
    Vector<int, 0> vec1{1, 2, 3, 4, 5};
    Vector<int, 0> vec2;
    vec2.reserve(10);
    vec2 = {1, 2, 3, 4, 5};
    vec2.reserve(10U);
    EXPECT_EQ(vec2, vec1);

    Vector<int, 0> vec3;
    EXPECT_THROW((vec3 = {1, 2, 3}), std::bad_alloc);
}

TEST(ManualVector, AssignWithCountElements)
{
    Vector<int, 0> vec;
    vec.reserve(10);
    vec.assign(1, 10);
    ASSERT_EQ(vec, (Vector<int, 10>{10}));
    vec.assign(2, 20);
    ASSERT_EQ(vec, (Vector<int, 10>{20, 20}));
    EXPECT_THROW(vec.assign(11, 1), std::bad_alloc);
}

TEST(ManualVector, AssignWithInputIterator)
{
    int            arr[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    Vector<int, 0> vec;
    vec.reserve(10);
    vec.assign(&arr[0], &arr[0]);
    ASSERT_EQ(vec, (Vector<int, 0>{}));
    vec.assign(&arr[0], &arr[1]);
    ASSERT_EQ(vec, (Vector<int, 0>{1}));
    vec.assign(&arr[0], &arr[3]);
    ASSERT_EQ(vec, (Vector<int, 10>{1, 2, 3}));
    EXPECT_THROW((vec.assign(&arr[0], &arr[12])), std::bad_alloc);
    EXPECT_THROW((vec.assign(&arr[1], &arr[0])), std::bad_alloc);
}

TEST(ManualVector, AssignWithInitializerList)
{
    Vector<int, 0> vec;
    vec.reserve(10);
    vec.assign({});
    ASSERT_EQ(vec, (Vector<int, 0>{}));
    vec.assign({1});
    ASSERT_EQ(vec, (Vector<int, 0>{1}));
    vec.assign({1, 2, 3});
    ASSERT_EQ(vec, (Vector<int, 0>{1, 2, 3}));
    EXPECT_THROW(vec.assign({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}), std::bad_alloc);
}

TEST(ManualVector, AssignWithVectorOfDifferentSize)
{
    Vector<int, 10> vec1 = {1, 2, 3};
    Vector<int, 0>  vec2;
    vec2.reserve(3);
    vec2 = vec1;
    ASSERT_EQ((Vector<int, 0>{1, 2, 3}), vec2);

    Vector<int, 10> vec3 = {1, 2, 3, 4, 5};
    EXPECT_THROW(vec2 = vec3, std::bad_alloc);
}

TEST(ManualVector, AssignWithVectorOfDifferentSizeRValue)
{
    Vector<int, 3> vec1 = {1, 2, 3};
    Vector<int, 0>  vec2;
    vec2.reserve(3);
    vec2 = std::move(vec1);
    ASSERT_EQ((Vector<int, 0>{1, 2, 3}), vec2);

    Vector<int, 10> vec3 = {1, 2, 3, 4, 5};
    EXPECT_THROW(vec2 = std::move(vec3), std::bad_alloc);
}

TEST(ManualVector, GetAllocator)
{
    Vector<int, 0> vec;
    vec.get_allocator();
}

TEST(ManualVector, At)
{
    Vector<int, 0>        vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int, 0> const& vec2 = vec;
    ASSERT_EQ(1, vec.at(0));
    ASSERT_EQ(2, vec.at(1));
    ASSERT_EQ(10, vec.at(9));
    EXPECT_THROW(vec.at(10), std::out_of_range);

    ASSERT_EQ(1, vec2.at(0));
    ASSERT_EQ(2, vec2.at(1));
    ASSERT_EQ(10, vec2.at(9));
    EXPECT_THROW(vec2.at(10), std::out_of_range);
}

TEST(ManualVector, BracketOperator)
{
    Vector<int, 0>        vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int, 0> const& vec2 = vec;
    ASSERT_EQ(1, vec[0]);
    ASSERT_EQ(2, vec[1]);
    ASSERT_EQ(10, vec[9]);
    ASSERT_EQ(1, vec2[0]);
    ASSERT_EQ(2, vec2[1]);
    ASSERT_EQ(10, vec2[9]);
}

TEST(ManualVector, Front)
{
    Vector<int, 0>        vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int, 0> const& vec2 = vec;
    ASSERT_EQ(1, vec.front());
    ASSERT_EQ(1, vec2.front());
}

TEST(ManualVector, Back)
{
    Vector<int, 0>        vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int, 0> const& vec2 = vec;
    ASSERT_EQ(10, vec.back());
    ASSERT_EQ(10, vec2.back());
}

TEST(ManualVector, Data)
{
    Vector<int, 0> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(1, vec.data()[0]);
    ASSERT_EQ(2, vec.data()[1]);
    ASSERT_EQ(10, vec.data()[9]);
}

TEST(ManualVector, Begin)
{
    Vector<int, 0> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(1, *vec.begin());
    ASSERT_EQ(1, *vec.cbegin());
    *vec.begin() = 2;
    ASSERT_EQ(2, *vec.begin());
    ASSERT_EQ(2, *vec.cbegin());
}

TEST(ManualVector, End)
{
    Vector<int, 0> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(10, *(vec.end() - 1));
    ASSERT_EQ(10, *(vec.cend() - 1));
    *(vec.end() - 1) = 11;
    ASSERT_EQ(11, *(vec.end() - 1));
    ASSERT_EQ(11, *(vec.cend() - 1));
}

TEST(ManualVector, Rbegin)
{
    Vector<int, 0> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(10, *vec.rbegin());
    ASSERT_EQ(10, *vec.crbegin());
    *vec.rbegin() = 11;
    ASSERT_EQ(11, *vec.rbegin());
    ASSERT_EQ(11, *vec.crbegin());
}

TEST(ManualVector, Rend)
{
    Vector<int, 0> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(1, *(vec.rend() - 1));
    ASSERT_EQ(1, *(vec.crend() - 1));
    *(vec.rend() - 1) = 2;
    ASSERT_EQ(2, *(vec.rend() - 1));
    ASSERT_EQ(2, *(vec.crend() - 1));
}

TEST(ManualVector, Empty)
{
    Vector<int, 0> vec;
    vec.reserve(1);
    ASSERT_EQ(true, vec.empty());
    vec = {1};
    ASSERT_EQ(false, vec.empty());
}

TEST(ManualVector, Size)
{
    Vector<int, 0> vec;
    vec.reserve(10);
    ASSERT_EQ(0U, vec.size());
    vec.assign({1});
    ASSERT_EQ(1U, vec.size());
    vec.assign({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    ASSERT_EQ(10U, vec.size());
}

TEST(ManualVector, MaxSize)
{
    Vector<int, 0> vec1;
    ASSERT_EQ(0U, vec1.max_size());
    Vector<int, 0> vec2;
    vec2.reserve(100U);
    ASSERT_EQ(100U, vec2.max_size());
}

TEST(ManualVector, Reserve)
{
    Vector<int, 0> vec;
    vec.reserve(8);
    EXPECT_EQ(8U, vec.capacity());
}

TEST(ManualVector, Capacity)
{
    Vector<int, 0> vec1;
    ASSERT_EQ(0U, vec1.capacity());
    Vector<int, 0> vec2;
    vec2.reserve(10);
    ASSERT_EQ(10U, vec2.capacity());
}

TEST(ManualVector, ShrinkToFit)
{
    Vector<int, 0> vec1 = {1, 2, 3};
    vec1.reserve(10);
    EXPECT_EQ(10, vec1.capacity());
    vec1.shrink_to_fit();
    EXPECT_EQ(3, vec1.capacity());
}

TEST(ManualVector, Clear)
{
    Vector<int, 0> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vec.clear();
    ASSERT_EQ(0U, vec.size());
}

TEST(ManualVector, InsertWithPosLvalue)
{
    Vector<int, 0> vec{1, 2, 3};
    vec.reserve(10);
    int  value = 0;
    auto it    = vec.insert(vec.begin(), value);
    ASSERT_EQ(0, *it);
    ASSERT_EQ(4U, vec.size());
    value = 4;
    it    = vec.insert(vec.end(), value);
    ASSERT_EQ(4, *it);
    ASSERT_EQ(5U, vec.size());

    Vector<int, 0> vec2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_THROW(vec2.insert(vec2.begin(), value), std::bad_alloc);
}

TEST(ManualVector, InsertWithPosRvalue)
{
    Vector<int, 0> vec{1, 2, 3};
    vec.reserve(10);
    int  value = 0;
    auto it    = vec.insert(vec.begin(), std::move(value));
    ASSERT_EQ(0, *it);
    ASSERT_EQ(4U, vec.size());
    value = 4;
    it    = vec.insert(vec.end(), std::move(value));
    ASSERT_EQ(4, *it);
    ASSERT_EQ(5U, vec.size());

    Vector<int, 0> vec2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_THROW(vec2.insert(vec2.begin(), std::move(value)), std::bad_alloc);
}

TEST(ManualVector, InsertWithPosInputIterator)
{
    int            arr[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector<int, 0> vec{5};
    vec.reserve(10);

    auto it = vec.insert(vec.begin(), &arr[0], &arr[5]);
    ASSERT_EQ(0, *it);
    ASSERT_EQ(6, vec.size());

    it = vec.insert(vec.end(), &arr[6], &arr[10]);
    ASSERT_EQ(6, *it);
    ASSERT_EQ(10, vec.size());

    vec.assign({});
    EXPECT_THROW(vec.insert(vec.begin(), &arr[0], &arr[11]), std::bad_alloc);
}

TEST(ManualVector, InsertWithInitializerList)
{
    Vector<int, 0> vec;
    vec.reserve(10);
    auto it = vec.insert(vec.begin(), {1, 2, 3});
    ASSERT_EQ(1, *it);
    ASSERT_EQ(3U, vec.size());
    it = vec.insert(vec.end(), {4, 5, 6});
    ASSERT_EQ(4, *it);
    ASSERT_EQ(6, vec.size());

    EXPECT_THROW(vec.insert(vec.begin(), {1, 2, 3, 4, 5}), std::bad_alloc);
}

TEST(ManualVector, Emplace)
{
    Vector<int, 0> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    vec.reserve(10);
    auto it = vec.emplace(vec.begin(), 0);
    ASSERT_EQ(0, *it);

    it = vec.emplace(vec.end(), 9);
    ASSERT_EQ(9, *it);

    EXPECT_THROW(vec.emplace(vec.end(), 10), std::bad_alloc);
}

TEST(ManualVector, EraseWithPos)
{
    Vector<int, 0> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vec.reserve(10);
    auto it = vec.erase(vec.begin());
    ASSERT_EQ(1, *it);
    ASSERT_EQ(9U, vec.size());

    it = vec.erase(vec.end() - 1);
    ASSERT_EQ(vec.end(), it);
    ASSERT_EQ(8U, vec.size());
}

TEST(ManualVector, EraseWithIteratorRange)
{
    Vector<int, 0> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vec.reserve(10);
    auto it = vec.erase(vec.begin(), vec.begin());
    ASSERT_EQ(0, *it);
    ASSERT_EQ(10U, vec.size());

    it = vec.erase(vec.begin(), vec.begin() + 1);
    ASSERT_EQ(1, *it);
    ASSERT_EQ(9U, vec.size());

    it = vec.erase(vec.end() - 1, vec.end());
    ASSERT_EQ(vec.end(), it);
    ASSERT_EQ(8U, vec.size());
}

TEST(ManualVector, PushBack)
{
    Vector<int, 0> vec{0, 1, 2, 3, 4, 5, 6, 7, 8};
    vec.reserve(10);
    int value = 9;
    vec.push_back(value);
    ASSERT_EQ(value, *(vec.end() - 1));
    EXPECT_THROW(vec.push_back(value), std::bad_alloc);

    vec = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    vec.push_back(std::move(value));
    ASSERT_EQ(value, *(vec.end() - 1));
    EXPECT_THROW(vec.push_back(std::move(value)), std::bad_alloc);
}

TEST(ManualVector, EmplaceBack)
{
    Vector<int, 0> vec{0, 1, 2, 3, 4, 5, 6, 7, 8};
    vec.reserve(10);
    int value = 9;
    vec.emplace_back(value);
    ASSERT_EQ(value, *(vec.end() - 1));
    EXPECT_THROW(vec.emplace_back(value), std::bad_alloc);
}

TEST(ManualVector, PopBack)
{
    Vector<int, 0> vec{0, 1, 2, 3, 4};
    vec.pop_back();
    ASSERT_EQ(4U, vec.size());
}

TEST(ManualVector, Resize)
{
    Vector<int, 0> vec = {0, 1, 2, 3};
    vec.reserve(10);
    vec.resize(3);
    ASSERT_EQ((Vector<int, 10>{0, 1, 2}), vec);
    vec.resize(5);
    ASSERT_EQ((Vector<int, 10>{0, 1, 2, 0, 0}), vec);
    EXPECT_THROW(vec.resize(11), std::bad_alloc);
}

TEST(ManualVector, Swap)
{
    Vector<int, 0> vec1 = {1, 2, 3, 4, 5};
    Vector<int, 0> vec2 = {6, 7, 8, 9, 10};
    vec1.swap(vec2);
    ASSERT_EQ((Vector<int, 10>{6, 7, 8, 9, 10}), vec1);
    ASSERT_EQ((Vector<int, 10>{1, 2, 3, 4, 5}), vec2);
    
    vec1.reserve(6);
    Vector<int, 10> vec3 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    EXPECT_THROW(vec1.swap(vec3), std::bad_alloc);
    Vector<int, 500> vec4 = {1, 2, 3, 4, 5};
    vec1.reserve(4);
    vec1.swap(vec4);
}

TEST(ManualVector, Swap_2)
{
    Vector<int, 0> vec1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    vec1.reserve(8);
    Vector<int, 20> vec2;
    for(size_t i=0;i<9;i++)
    {
        vec2.push_back(i);
    }
    vec1.swap(vec2);
}

TEST(ManualVector, SwapDifferentSize)
{
    Vector<int, 0> vec1 = {1, 2, 3, 4, 5};
    vec1.reserve(10);
    Vector<int, 100> vec2 = {6, 7, 8, 9, 10};
    vec1.swap(vec2);
    ASSERT_EQ((Vector<int, 0>{6, 7, 8, 9, 10}), vec1);
    ASSERT_EQ((Vector<int, 0>{1, 2, 3, 4, 5}), vec2);
    ASSERT_EQ(100U, vec1.capacity());
    ASSERT_EQ(10U, vec2.capacity());
}

TEST(ManualVector, SerializeAndDeserialize)
{
    
    Vector<Point2, 3> vec1 = {Point2(1.0, 2.0), Point2(1.0, 2.0)};
    Vector<Point2, 3> vec2;

    uint8_t buffer[1024];
    holo::serialization::Serializer<>           serializer(buffer, 1024);
    serializer << vec1;
    ASSERT_EQ(vec1.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> vec2;
    ASSERT_EQ(vec1, vec2);
}

TEST(ManualVector, SerializeAndDeserialize_2)
{
    Vector<Point2, 0> vec1 = {Point2(1.0, 2.0), Point2(1.0, 2.0)};
    Vector<Point2, 0> vec2 = {Point2(1.0, 2.0), Point2(1.0, 2.0)};
    // vec2.reserve(2);

    uint8_t buffer[1024];
    holo::serialization::Serializer<>           serializer(buffer, 1024);
    serializer << vec1;
    ASSERT_EQ(vec1.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> vec2;
    ASSERT_EQ(vec1, vec2);
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
