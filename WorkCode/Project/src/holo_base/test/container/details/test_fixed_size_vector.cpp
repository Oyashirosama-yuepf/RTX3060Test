/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_fixed_size_vector.cpp
 * @brief Unit test for FixedSizeVector.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-12
 */

#include <gtest/gtest.h>
#include <holo/container/details/fixed_size_vector.h>

template <typename T, size_t SIZE>
using VectorT = holo::container::details::FixedSizeVector<T, SIZE>;

TEST(FixedSizeVector, DefaultConstructor)
{
    VectorT<int, 10> vec;
}

TEST(FixedSizeVector, ConstructWithCountElements)
{
    VectorT<int, 10> vec1(0, 0);
    VectorT<int, 10> vec2(1, 1);
    VectorT<int, 10> vec3(10, 1);
    try
    {
        VectorT<int, 10> vec4(11, 1);
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

TEST(FixedSizeVector, ConstructorWithIterators)
{
    int              arr[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    VectorT<int, 10> vec1(&arr[0], &arr[0]);
    ASSERT_EQ(vec1, (VectorT<int, 10>({})));
    VectorT<int, 10> vec2(&arr[0], &arr[1]);
    ASSERT_EQ(vec2, (VectorT<int, 10>({0})));
    VectorT<int, 10> vec3(&arr[0], &arr[10]);
    ASSERT_EQ(vec3, (VectorT<int, 10>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})));
    try
    {
        VectorT<int, 10> vec4(&arr[0], &arr[11]);
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
        VectorT<int, 10> vec5(&arr[10], &arr[1]);
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
    VectorT<int, 10> vec1(5, 30);
    VectorT<int, 10> vec2(vec1);
    VectorT<int, 3> vec3{5, 30, 20};

    ASSERT_EQ(vec2, vec1);
    try
    {
        VectorT<int, 2> vec4(vec3);
    }
    catch(std::bad_alloc const& e)
    {
    }   
}

TEST(FixedSizeVector, MoveConstructor)
{
    VectorT<int, 10> vec1(5, 20);
    int*             p = &vec1.front();
    VectorT<int, 10> vec2(std::move(vec1));
    int*             p2 = &vec2.front();
    VectorT<int, 12> vec3{5, 30, 20, 10};
    ASSERT_EQ(p, p2);
    try
    {
        VectorT<int, 2> vec4(vec3);
    }
    catch(std::bad_alloc const& e)
    {
    } 
}

TEST(FixedSizeVector, MoveAssignException)
{
    VectorT<int, 10> vec1 = {1, 2, 3};
    VectorT<int, 2> vec2;
    EXPECT_THROW(vec2 = std::move(vec1), std::bad_alloc);
}

TEST(FixedSizeVector, ConstructWithInitializerList)
{
    VectorT<int, 10> vec1;
    for (size_t i = 0; i < 10; ++i)
    {
        vec1.push_back(i);
    }
    VectorT<int, 10> vec2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_EQ(vec1, vec2);
}

TEST(FixedSizeVector, ConstructWithFixedSizeVectorOfDifferentSize)
{
    VectorT<int, 10> vec1 = {1, 2, 3};
    VectorT<int, 20> vec2(vec1);
    ASSERT_EQ((VectorT<int, 20>{1, 2, 3}), vec2);
    VectorT<int, 5> vec3(vec2);
    ASSERT_EQ((VectorT<int, 5>{1, 2, 3}), vec3);
}

TEST(FixedSizeVector, ConstructWithFixedSizeVectorOfDifferentSizeRValue)
{
    VectorT<int, 10> vec1 = {1, 2, 3};
    VectorT<int, 20> vec2(std::move(vec1));
    ASSERT_EQ((VectorT<int, 20>{1, 2, 3}), vec2);
    VectorT<int, 5> vec3(std::move(vec2));
    ASSERT_EQ((VectorT<int, 5>{1, 2, 3}), vec3);
}

TEST(FixedSizeVector, AssignOperatorLvalue)
{
    VectorT<int, 10> vec1{1, 2, 3, 4, 5, 6, 7, 8};
    VectorT<int, 10> vec2;
    vec2 = vec1;
    ASSERT_EQ(vec1, vec2);
}

TEST(FixedSizeVector, AssignOperatorRvalue)
{
    VectorT<int, 10> vec1{1, 2, 3, 4, 5, 6, 7, 8};
    int*             p1 = &vec1[0];
    VectorT<int, 10> vec2;
    vec2    = std::move(vec1);
    int* p2 = &vec2[0];
    ASSERT_EQ(p1, p2);
}

TEST(FixedSizeVector, AssignOperatorInitializerList)
{
    VectorT<int, 10> vec1{1, 2, 3, 4, 5};
    VectorT<int, 10> vec2;
    vec2 = {1, 2, 3, 4, 5};
    ASSERT_EQ(vec2, vec1);
    EXPECT_THROW((vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}), std::bad_alloc);
}

TEST(FixedSizeVector, AssignWithCountElements)
{
    VectorT<int, 10> vec;
    vec.assign(1, 10);
    ASSERT_EQ(vec, (VectorT<int, 10>{10}));
    vec.assign(2, 20);
    ASSERT_EQ(vec, (VectorT<int, 10>{20, 20}));
    EXPECT_THROW(vec.assign(11, 1), std::bad_alloc);
}

TEST(FixedSizeVector, AssignWithInputIterator)
{
    int              arr[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    VectorT<int, 10> vec;
    vec.assign(&arr[0], &arr[0]);
    ASSERT_EQ(vec, (VectorT<int, 10>{}));
    vec.assign(&arr[0], &arr[1]);
    ASSERT_EQ(vec, (VectorT<int, 10>{1}));
    vec.assign(&arr[0], &arr[3]);
    ASSERT_EQ(vec, (VectorT<int, 10>{1, 2, 3}));
    EXPECT_THROW((vec.assign(&arr[0], &arr[12])), std::bad_alloc);
    EXPECT_THROW((vec.assign(&arr[1], &arr[0])), std::bad_alloc);
}

TEST(FixedSizeVector, AssignWithInitializerList)
{
    VectorT<int, 10> vec;
    vec.assign({});
    ASSERT_EQ(vec, (VectorT<int, 10>{}));
    vec.assign({1});
    ASSERT_EQ(vec, (VectorT<int, 10>{1}));
    vec.assign({1, 2, 3});
    ASSERT_EQ(vec, (VectorT<int, 10>{1, 2, 3}));
    EXPECT_THROW(vec.assign({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}), std::bad_alloc);
}

TEST(FixedSizeVector, AssignWithFixedSizeVectorOfDifferentSize)
{
    VectorT<int, 10> vec1 = {1, 2, 3};
    VectorT<int, 20> vec2;
    vec2 = vec1;
    ASSERT_EQ((VectorT<int, 20>{1, 2, 3}), vec2);
    VectorT<int, 5> vec3;
    vec3 = vec2;
    ASSERT_EQ((VectorT<int, 5>{1, 2, 3}), vec3);
}

TEST(FixedSizeVector, AssignWithFixedSizeVectorOfDifferentSizeRValue)
{
    VectorT<int, 10> vec1 = {1, 2, 3};
    VectorT<int, 20> vec2;
    vec2 = std::move(vec1);
    ASSERT_EQ((VectorT<int, 20>{1, 2, 3}), vec2);
    VectorT<int, 5> vec3;
    vec3 = std::move(vec2);
    ASSERT_EQ((VectorT<int, 5>{1, 2, 3}), vec3);
}

TEST(FixedSizeVector, GetAllocator)
{
    VectorT<int, 10> vec;
    vec.get_allocator();
}

TEST(FixedSizeVector, At)
{
    VectorT<int, 10>        vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    VectorT<int, 10> const& vec2 = vec;
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
    VectorT<int, 10>        vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    VectorT<int, 10> const& vec2 = vec;
    ASSERT_EQ(1, vec[0]);
    ASSERT_EQ(2, vec[1]);
    ASSERT_EQ(10, vec[9]);
    ASSERT_EQ(1, vec2[0]);
    ASSERT_EQ(2, vec2[1]);
    ASSERT_EQ(10, vec2[9]);
}

TEST(FixedSizeVector, Front)
{
    VectorT<int, 10>        vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    VectorT<int, 10> const& vec2 = vec;
    ASSERT_EQ(1, vec.front());
    ASSERT_EQ(1, vec2.front());
}

TEST(FixedSizeVector, Back)
{
    VectorT<int, 10>        vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    VectorT<int, 10> const& vec2 = vec;
    ASSERT_EQ(10, vec.back());
    ASSERT_EQ(10, vec2.back());
}

TEST(FixedSizeVector, Data)
{
    VectorT<int, 10> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(1, vec.data()[0]);
    ASSERT_EQ(2, vec.data()[1]);
    ASSERT_EQ(10, vec.data()[9]);
}

TEST(FixedSizeVector, Begin)
{
    VectorT<int, 10> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(1, *vec.begin());
    ASSERT_EQ(1, *vec.cbegin());
    *vec.begin() = 2;
    ASSERT_EQ(2, *vec.begin());
    ASSERT_EQ(2, *vec.cbegin());
}

TEST(FixedSizeVector, End)
{
    VectorT<int, 10> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(10, *(vec.end() - 1));
    ASSERT_EQ(10, *(vec.cend() - 1));
    *(vec.end() - 1) = 11;
    ASSERT_EQ(11, *(vec.end() - 1));
    ASSERT_EQ(11, *(vec.cend() - 1));
}

TEST(FixedSizeVector, Rbegin)
{
    VectorT<int, 10> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(10, *vec.rbegin());
    ASSERT_EQ(10, *vec.crbegin());
    *vec.rbegin() = 11;
    ASSERT_EQ(11, *vec.rbegin());
    ASSERT_EQ(11, *vec.crbegin());
}

TEST(FixedSizeVector, Rend)
{
    VectorT<int, 10> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(1, *(vec.rend() - 1));
    ASSERT_EQ(1, *(vec.crend() - 1));
    *(vec.rend() - 1) = 2;
    ASSERT_EQ(2, *(vec.rend() - 1));
    ASSERT_EQ(2, *(vec.crend() - 1));
}

TEST(FixedSizeVector, Empty)
{
    VectorT<int, 10> vec;
    ASSERT_EQ(true, vec.empty());
    vec = {1};
    ASSERT_EQ(false, vec.empty());
}

TEST(FixedSizeVector, Size)
{
    VectorT<int, 10> vec;
    ASSERT_EQ(0U, vec.size());
    vec.assign({1});
    ASSERT_EQ(1U, vec.size());
    vec.assign({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    ASSERT_EQ(10U, vec.size());
}

TEST(FixedSizeVector, MaxSize)
{
    VectorT<int, 10> vec1;
    ASSERT_EQ(10U, vec1.max_size());
    VectorT<int, 100> vec2;
    ASSERT_EQ(100U, vec2.max_size());
    VectorT<int, 0> vec3;
    ASSERT_EQ(0U, vec3.max_size());
}

TEST(FixedSizeVector, Reserve)
{
    VectorT<int, 10> vec;
    vec.reserve(8);
    EXPECT_THROW(vec.reserve(11), std::bad_alloc);
}

TEST(FixedSizeVector, Capacity)
{
    VectorT<int, 0> vec1;
    ASSERT_EQ(0U, vec1.capacity());
    VectorT<int, 10> vec2;
    ASSERT_EQ(10U, vec2.capacity());
}

TEST(FixedSizeVector, ShrinkToFit)
{
    VectorT<int, 10> vec1;
    vec1.shrink_to_fit();
}

TEST(FixedSizeVector, Clear)
{
    VectorT<int, 10> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vec.clear();
    ASSERT_EQ(0U, vec.size());
}

TEST(FixedSizeVector, InsertWithPosLvalue)
{
    VectorT<int, 10> vec{1, 2, 3};
    int              value = 0;
    auto             it    = vec.insert(vec.begin(), value);
    ASSERT_EQ(0, *it);
    ASSERT_EQ(4U, vec.size());
    value = 4;
    it    = vec.insert(vec.end(), value);
    ASSERT_EQ(4, *it);
    ASSERT_EQ(5U, vec.size());

    VectorT<int, 10> vec2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_THROW(vec2.insert(vec2.begin(), value), std::bad_alloc);
}

TEST(FixedSizeVector, InsertWithPosRvalue)
{
    VectorT<int, 10> vec{1, 2, 3};
    int              value = 0;
    auto             it    = vec.insert(vec.begin(), std::move(value));
    ASSERT_EQ(0, *it);
    ASSERT_EQ(4U, vec.size());
    value = 4;
    it    = vec.insert(vec.end(), std::move(value));
    ASSERT_EQ(4, *it);
    ASSERT_EQ(5U, vec.size());

    VectorT<int, 10> vec2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_THROW(vec2.insert(vec2.begin(), std::move(value)), std::bad_alloc);
}

TEST(FixedSizeVector, InsertWithPosInputIterator)
{
    int              arr[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    VectorT<int, 10> vec{5};

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
    VectorT<int, 10> vec;
    auto             it = vec.insert(vec.begin(), {1, 2, 3});
    ASSERT_EQ(1, *it);
    ASSERT_EQ(3U, vec.size());
    it = vec.insert(vec.end(), {4, 5, 6});
    ASSERT_EQ(4, *it);
    ASSERT_EQ(6, vec.size());

    EXPECT_THROW(vec.insert(vec.begin(), {1, 2, 3, 4, 5}), std::bad_alloc);
}

TEST(FixedSizeVector, Emplace)
{
    VectorT<int, 10> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    auto             it  = vec.emplace(vec.begin(), 0);
    ASSERT_EQ(0, *it);

    it = vec.emplace(vec.end(), 9);
    ASSERT_EQ(9, *it);

    EXPECT_THROW(vec.emplace(vec.end(), 10), std::bad_alloc);
}

TEST(FixedSizeVector, EraseWithPos)
{
    VectorT<int, 10> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto             it  = vec.erase(vec.begin());
    ASSERT_EQ(1, *it);
    ASSERT_EQ(9U, vec.size());

    it = vec.erase(vec.end() - 1);
    ASSERT_EQ(vec.end(), it);
    ASSERT_EQ(8U, vec.size());
}

TEST(FixedSizeVector, EraseWithIteratorRange)
{
    VectorT<int, 10> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto             it  = vec.erase(vec.begin(), vec.begin());
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
    VectorT<int, 10> vec{0, 1, 2, 3, 4, 5, 6, 7, 8};
    int              value = 9;
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
    VectorT<int, 10> vec{0, 1, 2, 3, 4, 5, 6, 7, 8};
    int              value = 9;
    vec.emplace_back(value);
    ASSERT_EQ(value, *(vec.end() - 1));
    EXPECT_THROW(vec.emplace_back(value), std::bad_alloc);
}

TEST(FixedSizeVector, PopBack)
{
    VectorT<int, 10> vec{0, 1, 2, 3, 4};
    vec.pop_back();
    ASSERT_EQ(4U, vec.size());
}

TEST(FixedSizeVector, Resize)
{
    VectorT<int, 10> vec = {0, 1, 2, 3};
    vec.resize(3);
    ASSERT_EQ((VectorT<int, 10>{0, 1, 2}), vec);
    vec.resize(5);
    ASSERT_EQ((VectorT<int, 10>{0, 1, 2, 0, 0}), vec);
    EXPECT_THROW(vec.resize(80, 0), std::bad_alloc);
}

TEST(FixedSizeVector, Resize_1)
{
    VectorT<int, 10> vec = {0, 1, 2, 3};
    try
    {
        vec.resize(80);
    }
    catch(...)
    {
    }
}

TEST(FixedSizeVector, Swap)
{
    VectorT<int, 10> vec1 = {1, 2, 3, 4, 5};
    VectorT<int, 11> vec2 = {6, 7, 8, 9, 10};
    VectorT<int, 11> vec3 = {6, 7, 8, 9, 10, 6, 7, 8, 9, 10, 11};

    vec1.swap(vec2);
    ASSERT_EQ((VectorT<int, 10>{6, 7, 8, 9, 10}), vec1);
    ASSERT_EQ((VectorT<int, 10>{1, 2, 3, 4, 5}), vec2);
    EXPECT_THROW(vec1.swap(vec3), std::bad_alloc);

}

TEST(FixedSizeVector, SwapDifferentSize)
{
    VectorT<int, 10> vec1 = {1, 2, 3, 4, 5};
    VectorT<int, 100> vec2 = {6, 7, 8, 9, 10};
    vec1.swap(vec2);
    ASSERT_EQ((VectorT<int, 10>{6, 7, 8, 9, 10}), vec1);
    ASSERT_EQ((VectorT<int, 10>{1, 2, 3, 4, 5}), vec2);
    ASSERT_EQ(10U, vec1.capacity());
    ASSERT_EQ(100U, vec2.capacity());
}

TEST(FixedSizeVectorStandaloneFunctions, Equals)
{
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} == VectorT<int, 10>{1, 2, 3, 4, 5}));
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} == VectorT<int, 10>{1, 2, 3, 4}));
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} == VectorT<int, 10>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, EqualsDifferentSize)
{
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} == VectorT<int, 20>{1, 2, 3, 4, 5}));
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} == VectorT<int, 20>{1, 2, 3, 4}));
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} == VectorT<int, 20>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, NotEqual)
{
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} != VectorT<int, 10>{1, 2, 3, 4, 5}));
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} != VectorT<int, 10>{1, 2, 3, 4}));
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} != VectorT<int, 10>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, NotEqualDifferentSize)
{
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} != VectorT<int, 20>{1, 2, 3, 4, 5}));
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} != VectorT<int, 20>{1, 2, 3, 4}));
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} != VectorT<int, 20>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, Greater)
{
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} > VectorT<int, 10>{1, 2, 3, 4, 5}));
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} > VectorT<int, 10>{1, 2, 3, 4}));
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} > VectorT<int, 10>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, GreaterDifferentSize)
{
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} > VectorT<int, 20>{1, 2, 3, 4, 5}));
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} > VectorT<int, 20>{1, 2, 3, 4}));
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} > VectorT<int, 20>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, GreaterEqual)
{
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} >= VectorT<int, 10>{1, 2, 3, 4, 5}));
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} >= VectorT<int, 10>{1, 2, 3, 4}));
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} >= VectorT<int, 10>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, GreaterEqualDifferentSize)
{
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} >= VectorT<int, 20>{1, 2, 3, 4, 5}));
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} >= VectorT<int, 20>{1, 2, 3, 4}));
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} >= VectorT<int, 20>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, Less)
{
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} < VectorT<int, 10>{1, 2, 3, 4, 5}));
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} < VectorT<int, 10>{1, 2, 3, 4}));
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} < VectorT<int, 10>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, LessDifferentSize)
{
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} < VectorT<int, 20>{1, 2, 3, 4, 5}));
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} < VectorT<int, 20>{1, 2, 3, 4}));
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} < VectorT<int, 20>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, LessEqual)
{
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} <= VectorT<int, 10>{1, 2, 3, 4, 5}));
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} <= VectorT<int, 10>{1, 2, 3, 4}));
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} <= VectorT<int, 10>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, LessEqualDifferentSize)
{
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} <= VectorT<int, 20>{1, 2, 3, 4, 5}));
    ASSERT_FALSE((VectorT<int, 10>{1, 2, 3, 4, 5} <= VectorT<int, 20>{1, 2, 3, 4}));
    ASSERT_TRUE((VectorT<int, 10>{1, 2, 3, 4, 5} <= VectorT<int, 20>{1, 2, 3, 4, 6}));
}

TEST(FixedSizeVectorStandaloneFunctions, Swap)
{
    VectorT<int, 10> vec1 = {1, 2, 3, 4, 5};
    VectorT<int, 10> vec2 = {6, 7, 8, 9, 10};
    swap(vec1, vec2);
    ASSERT_EQ((VectorT<int, 10>{6, 7, 8, 9, 10}), vec1);
    ASSERT_EQ((VectorT<int, 10>{1, 2, 3, 4, 5}), vec2);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
