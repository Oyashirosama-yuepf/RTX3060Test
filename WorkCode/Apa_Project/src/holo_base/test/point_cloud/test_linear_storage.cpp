/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_linear_storage.cpp
 * @brief Unit test for LinearStorage types.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-11-02
 */

#include <gtest/gtest.h>

#include <holo/core/types.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/point_cloud/details/linear_storage.h>

using PointType   = holo::geometry::Point3T<holo::float32_t>;
using StorageType = holo::point_cloud::details::LinearStorage<PointType, std::numeric_limits<size_t>::max(), sizeof(PointType)>;

/**
 * @brief Test Dynamic size LinearStorageBase:LinearStorageBase default constructor
 */
TEST(LinearStorageBaseDynamicSize, DefaultConstructor)
{
    StorageType storage;
    ASSERT_EQ(0U, storage.size());
}

/**
 * @brief Test Dynamic size LinearStorageBase:LinearStorageBase(size_type size)
 */
TEST(LinearStorageBaseDynamicSize, ConstructWithSize)
{
    StorageType storage(10U);
    ASSERT_EQ(10U, storage.size());
    for (size_t i = 0U; i < 10U; ++i)
    {
        ASSERT_EQ((PointType{}), storage[i]);
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:LinearStorageBase(size_type size, value_type csont& value)
 */
TEST(LinearStorageBaseDynamicSize, ConstructWithSizeAndValue)
{
    StorageType storage(10U, PointType{1, 2, 3});
    ASSERT_EQ(10U, storage.size());
    for (size_t i = 0U; i < 10U; ++i)
    {
        ASSERT_EQ((PointType{1, 2, 3}), storage[i]);
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:LinearStorageBase(InputIt first, InputIt last)
 */
TEST(LinearStorageBaseDynamicSize, ConstructWithInputIteratorRange)
{
    PointType   pts[] = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    StorageType storage(&pts[0], &pts[4]);
    ASSERT_EQ(4U, storage.size());
    for (size_t i = 0U; i < 4U; ++i)
    {
        ASSERT_EQ(pts[i], storage[i]);
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:LinearStorageBase(std::initializer_list<value_type> il)
 */
TEST(LinearStorageBaseDynamicSize, ConstructWithInitializerList)
{
    PointType   pts[]   = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    ASSERT_EQ(4U, storage.size());
    for (size_t i = 0U; i < 4U; ++i)
    {
        ASSERT_EQ(pts[i], storage[i]);
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:LinearStorageBase(LinearStorageBase<T_, SIZE_, STRIDE_>)
 */
TEST(LinearStorageBaseDynamicSize, ConstructWithAnotherLinearStorageType_1)
{
    using OtherStorageType         = holo::point_cloud::details::LinearStorage<holo::geometry::Point2T<holo::float32_t>, 10U, 32U>;
    OtherStorageType other_storage = {{1, 1}, {2, 2}, {3, 3}};
    PointType        pts[]         = {{1, 1, 0}, {2, 2, 0}, {3, 3, 0}};
    StorageType      storage(other_storage);

    ASSERT_EQ(3U, storage.size());
    for (size_t i = 0U; i < 3U; ++i)
    {
        ASSERT_EQ(pts[i], storage[i]);
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:assign(first, last)
 */
TEST(LinearStorageBaseDynamicSize, AssignWithIteratorRange)
{
    PointType   pts[] = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    StorageType storage;
    storage.assign(&pts[0], &pts[4]);
    ASSERT_EQ(4U, storage.size());
    for (size_t i = 0U; i < 4U; ++i)
    {
        ASSERT_EQ(pts[i], storage[i]);
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:assign(n, value)
 */
TEST(LinearStorageBaseDynamicSize, AssignWithValues)
{
    StorageType storage;
    storage.assign(3U, PointType{1, 1, 1});
    ASSERT_EQ(3U, storage.size());
    for (size_t i = 0U; i < 3U; ++i)
    {
        ASSERT_EQ((PointType{1, 1, 1}), storage[i]);
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:assign(ilist)
 */
TEST(LinearStorageBaseDynamicSize, AssignWithInitializerList)
{
    PointType   pts[] = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    StorageType storage;
    storage.assign({{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}});
    ASSERT_EQ(4U, storage.size());
    for (size_t i = 0U; i < 4U; ++i)
    {
        ASSERT_EQ(pts[i], storage[i]);
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:operator=(LinearStorageBase const& other)
 */
TEST(LinearStorageBaseDynamicSize, OperatorAssignWithValue)
{
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    StorageType storage2;
    storage2 = storage;
    ASSERT_EQ(storage.size(), storage2.size());
    for (size_t i = 0U; i < storage.size(); ++i)
    {
        ASSERT_EQ(storage[i], storage2[i]);
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:operator=(LinearStorageBase&& other)
 */
TEST(LinearStorageBaseDynamicSize, OperatorAssignWithRValue)
{
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    PointType*  addr    = &storage[0];
    StorageType storage2;
    storage2 = std::move(storage);
    ASSERT_EQ(addr, &storage2[0]);
}

/**
 * @brief Test Dynamic size LinearStorageBase:operator=(ilist)
 */
TEST(LinearStorageBaseDynamicSize, OperatorAssignWithInitializerList)
{
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    StorageType storage2;
    storage2 = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    ASSERT_EQ(storage.size(), storage2.size());
    for (size_t i = 0U; i < storage.size(); ++i)
    {
        ASSERT_EQ(storage[i], storage2[i]);
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:reference LinearStorageBase::at(size_t idx) normal case
 */
TEST(LinearStorageBaseDynamicSize, at_1)
{
    PointType   pts[]   = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    for (size_t i = 0U; i < 4U; ++i)
    {
        ASSERT_EQ(pts[i], storage.at(i));
        storage.at(i) = PointType{1, 1, 1};
        ASSERT_EQ((PointType{1, 1, 1}), storage.at(i));
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:reference LinearStorageBase::at(size_t idx) out of range
 */
TEST(LinearStorageBaseDynamicSize, at_2)
{
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    EXPECT_THROW(storage.at(4U), std::out_of_range);
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_reference LinearStorageBase::at(size_t idx) const normal case
 */
TEST(LinearStorageBaseDynamicSize, at_3)
{
    PointType         pts[]   = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    StorageType const storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    for (size_t i = 0U; i < 4U; ++i)
    {
        ASSERT_EQ(pts[i], storage.at(i));
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_reference LinearStorageBase::at(size_t idx) const out of range
 */
TEST(LinearStorageBaseDynamicSize, at_4)
{
    StorageType const storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    EXPECT_THROW(storage.at(4U), std::out_of_range);
}

/**
 * @brief Test Dynamic size LinearStorageBase:reference LinearStorageBase::operator[](size_t idx) normal case
 */
TEST(LinearStorageBaseDynamicSize, OperatorBracket_1)
{
    PointType   pts[]   = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    for (size_t i = 0U; i < 4U; ++i)
    {
        ASSERT_EQ(pts[i], storage[i]);
        storage[i] = PointType{1, 1, 1};
        ASSERT_EQ((PointType{1, 1, 1}), storage[i]);
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_reference LinearStorageBase::operator[](size_t idx) const normal
 * case
 */
TEST(LinearStorageBaseDynamicSize, OperatorBracket_2)
{
    PointType         pts[]   = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    StorageType const storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    for (size_t i = 0U; i < 4U; ++i)
    {
        ASSERT_EQ(pts[i], storage[i]);
    }
}

/**
 * @brief Test Dynamic size LinearStorageBase:reference LinearStorageBase::front()
 */
TEST(LinearStorageBaseDynamicSize, front_1)
{
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    ASSERT_EQ((PointType{1, 2, 3}), storage.front());
    storage.front() = PointType{1, 1, 1};
    ASSERT_EQ((PointType{1, 1, 1}), storage.front());
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_reference LinearStorageBase::front() const
 */
TEST(LinearStorageBaseDynamicSize, front_2)
{
    StorageType const storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    ASSERT_EQ((PointType{1, 2, 3}), storage.front());
}

/**
 * @brief Test Dynamic size LinearStorageBase:reference LinearStorageBase::back()
 */
TEST(LinearStorageBaseDynamicSize, back_1)
{
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    ASSERT_EQ((PointType{4, 5, 6}), storage.back());
    storage.back() = PointType{1, 1, 1};
    ASSERT_EQ((PointType{1, 1, 1}), storage.back());
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_reference LinearStorageBase::back() const
 */
TEST(LinearStorageBaseDynamicSize, back_2)
{
    StorageType const storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    ASSERT_EQ((PointType{4, 5, 6}), storage.back());
}

/**
 * @brief Test Dynamic size LinearStorageBase:iterator LinearStorageBase::begin() empty container
 */
TEST(LinearStorageBaseDynamicSize, begin_1)
{
    StorageType storage;
    ASSERT_EQ(storage.begin(), storage.end());
}

/**
 * @brief Test Dynamic size LinearStorageBase:iterator LinearStorageBase::begin() non empty container
 */
TEST(LinearStorageBaseDynamicSize, begin_2)
{
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    ASSERT_EQ((PointType{1, 2, 3}), *storage.begin());
    *storage.begin() = PointType{1, 1, 1};
    ASSERT_EQ((PointType{1, 1, 1}), *storage.begin());
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_iterator LinearStorageBase::begin() const empty container
 */
TEST(LinearStorageBaseDynamicSize, begin_3)
{
    StorageType const storage;
    ASSERT_EQ(storage.begin(), storage.end());
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_iterator LinearStorageBase::begin() const non empty container
 */
TEST(LinearStorageBaseDynamicSize, begin_4)
{
    StorageType const storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    ASSERT_EQ((PointType{1, 2, 3}), *storage.begin());
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_iterator LinearStorageBase::cbegin() const empty container
 */
TEST(LinearStorageBaseDynamicSize, cbegin_1)
{
    StorageType storage;
    ASSERT_EQ(storage.cbegin(), storage.cend());
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_iterator LinearStorageBase::begin() const non empty container
 */
TEST(LinearStorageBaseDynamicSize, cbegin_2)
{
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    ASSERT_EQ((PointType{1, 2, 3}), *storage.cbegin());
}

/**
 * @brief Test Dynamic size LinearStorageBase:iterator LinearStorageBase::end() empty container
 */
TEST(LinearStorageBaseDynamicSize, end_1)
{
    StorageType storage;
    ASSERT_EQ(storage.end(), storage.begin());
}

/**
 * @brief Test Dynamic size LinearStorageBase:iterator LinearStorageBase::end() non empty container
 */
TEST(LinearStorageBaseDynamicSize, end_2)
{
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    ASSERT_EQ((PointType{4, 5, 6}), *(storage.end() - 1));
    *(storage.end() - 1) = PointType{1, 1, 1};
    ASSERT_EQ((PointType{1, 1, 1}), *(storage.end() - 1));
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_iterator LinearStorageBase::end() const empty container
 */
TEST(LinearStorageBaseDynamicSize, end_3)
{
    StorageType const storage;
    ASSERT_EQ(storage.end(), storage.end());
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_iterator LinearStorageBase::end() const non empty container
 */
TEST(LinearStorageBaseDynamicSize, end_4)
{
    StorageType const storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    ASSERT_EQ((PointType{4, 5, 6}), *(storage.end() - 1));
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_iterator LinearStorageBase::cend() const empty container
 */
TEST(LinearStorageBaseDynamicSize, cend_1)
{
    StorageType storage;
    ASSERT_EQ(storage.cbegin(), storage.cend());
}

/**
 * @brief Test Dynamic size LinearStorageBase:const_iterator LinearStorageBase::end() const non empty container
 */
TEST(LinearStorageBaseDynamicSize, cend_2)
{
    StorageType storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
    ASSERT_EQ((PointType{4, 5, 6}), *(storage.cend() - 1));
}

/**
 * @brief Test Dynamic size LinearStorageBase:size_type size() const noexcept
 */
TEST(LinearStorageBaseDynamicSize, size)
{
    StorageType storage;
    ASSERT_EQ(0U, storage.size());
    storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    ASSERT_EQ(3U, storage.size());
}

/**
 * @brief Test Dynamic size LinearStorageBase:size_type max_size() const noexcept
 */
TEST(LinearStorageBaseDynamicSize, max_size)
{
    StorageType storage;
    ASSERT_LT(65535U, storage.max_size());
}

/**
 * @brief Test Dynamic size LinearStorageBase:reserve(size_type new_cap)
 */
TEST(LinearStorageBaseDynamicSize, reserve)
{
    StorageType storage;
    ASSERT_GE(storage.capacity(), 0U);
    storage.reserve(100U);
    ASSERT_GE(storage.capacity(), 100U);
    storage.reserve(100000U);
    ASSERT_GE(storage.capacity(), 100000U);
}

/**
 * @brief Test Dynamic size LinearStorageBase:capacity()
 */
TEST(LinearStorageBaseDynamicSize, capacity)
{
    StorageType storage;
    ASSERT_GE(storage.capacity(), 0U);
    storage.reserve(100U);
    ASSERT_GE(storage.capacity(), 100U);
    storage.reserve(100000U);
    ASSERT_GE(storage.capacity(), 100000U);
}

/**
 * @brief Test Dynamic size LinearStorageBase:shrink_to_fit()
 */
TEST(LinearStorageBaseDynamicSize, shrink_to_fit)
{
    StorageType storage;
    storage.reserve(65535U);
    storage.shrink_to_fit();
    ASSERT_GE(0U, storage.capacity());
    storage.reserve(65535U);
    storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    storage.shrink_to_fit();
    ASSERT_GE(3U, storage.capacity());
    storage = StorageType{10000U};
    storage.reserve(65535U);
    storage.shrink_to_fit();
    ASSERT_GE(10000U, storage.capacity());
}

/**
 * @brief Test Dynamic size LinearStorageBase:clear()
 */
TEST(LinearStorageBaseDynamicSize, clear)
{
    StorageType storage;
    storage.clear();
    ASSERT_EQ(0U, storage.size());

    storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    storage.clear();
    ASSERT_EQ(0U, storage.size());
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, value_type&) to an empty PointCloud
 */
TEST(LinearStorageBaseDynamicSize, insertSingleValue_1)
{
    StorageType           storage;
    PointType             pt{1, 1, 1};
    StorageType::iterator iter = storage.insert(storage.begin(), pt);
    ASSERT_EQ(pt, storage[0]);
    ASSERT_EQ(storage.begin(), iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, value_type&) before first element
 */
TEST(LinearStorageBaseDynamicSize, insertSingleValue_2)
{
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    PointType             pt{1, 1, 1};
    StorageType::iterator iter = storage.insert(storage.begin(), pt);
    ASSERT_EQ(pt, storage[0]);
    ASSERT_EQ((PointType{1, 2, 3}), storage[1]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[2]);
    ASSERT_EQ(storage.begin(), iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, value_type&) before past the end element
 */
TEST(LinearStorageBaseDynamicSize, insertSingleValue_3)
{
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    PointType             pt{1, 1, 1};
    StorageType::iterator iter = storage.insert(storage.end(), pt);
    ASSERT_EQ((PointType{1, 2, 3}), storage[0]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[1]);
    ASSERT_EQ(pt, storage[2]);
    ASSERT_EQ(storage.begin() + 2U, iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, value_type&) before any element
 */
TEST(LinearStorageBaseDynamicSize, insertSingleValue_4)
{
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    PointType             pt{1, 1, 1};
    StorageType::iterator iter = storage.insert(storage.begin() + 1, pt);
    ASSERT_EQ((PointType{1, 2, 3}), storage[0]);
    ASSERT_EQ(pt, storage[1]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[2]);
    ASSERT_EQ(storage.begin() + 1U, iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, value_type&&) to an empty PointCloud
 */
TEST(LinearStorageBaseDynamicSize, insertSingleRValue_1)
{
    StorageType           storage;
    StorageType::iterator iter = storage.insert(storage.begin(), PointType{1, 1, 1});
    ASSERT_EQ((PointType{1, 1, 1}), storage[0]);
    ASSERT_EQ(storage.begin(), iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, value_type&&) before first element
 */
TEST(LinearStorageBaseDynamicSize, insertSingleRValue_2)
{
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    StorageType::iterator iter    = storage.insert(storage.begin(), PointType{1, 1, 1});
    ASSERT_EQ((PointType{1, 1, 1}), storage[0]);
    ASSERT_EQ((PointType{1, 2, 3}), storage[1]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[2]);
    ASSERT_EQ(storage.begin(), iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, value_type&&) before past the end element
 */
TEST(LinearStorageBaseDynamicSize, insertSingleRValue_3)
{
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    StorageType::iterator iter    = storage.insert(storage.end(), PointType{1, 1, 1});
    ASSERT_EQ((PointType{1, 2, 3}), storage[0]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[1]);
    ASSERT_EQ((PointType{1, 1, 1}), storage[2]);
    ASSERT_EQ(storage.begin() + 2U, iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, value_type&&) before any element
 */
TEST(LinearStorageBaseDynamicSize, insertSingleRValue_4)
{
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    StorageType::iterator iter    = storage.insert(storage.begin() + 1, PointType{1, 1, 1});
    ASSERT_EQ((PointType{1, 2, 3}), storage[0]);
    ASSERT_EQ((PointType{1, 1, 1}), storage[1]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[2]);
    ASSERT_EQ(storage.begin() + 1U, iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, count, value) to an empty PointCloud
 */
TEST(LinearStorageBaseDynamicSize, insertMultipleValue_1)
{
    StorageType           storage;
    PointType             pt{1, 1, 1};
    StorageType::iterator iter = storage.insert(storage.begin(), 2U, pt);
    ASSERT_EQ(pt, storage[0]);
    ASSERT_EQ(pt, storage[1]);
    ASSERT_EQ(storage.begin(), iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, count, value) before first element
 */
TEST(LinearStorageBaseDynamicSize, insertMultipleValue_2)
{
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    PointType             pt{1, 1, 1};
    StorageType::iterator iter = storage.insert(storage.begin(), 2U, pt);
    ASSERT_EQ(pt, storage[0]);
    ASSERT_EQ(pt, storage[1]);
    ASSERT_EQ((PointType{1, 2, 3}), storage[2]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[3]);
    ASSERT_EQ(storage.begin(), iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, count, value) before past the end element
 */
TEST(LinearStorageBaseDynamicSize, insertMultipleValue_3)
{
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    PointType             pt{1, 1, 1};
    StorageType::iterator iter = storage.insert(storage.end(), 2U, pt);
    ASSERT_EQ((PointType{1, 2, 3}), storage[0]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[1]);
    ASSERT_EQ(pt, storage[2]);
    ASSERT_EQ(pt, storage[3]);
    ASSERT_EQ(storage.begin() + 2U, iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, count, value) before any element
 */
TEST(LinearStorageBaseDynamicSize, insertMultipleValue_4)
{
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    PointType             pt{1, 1, 1};
    StorageType::iterator iter = storage.insert(storage.begin() + 1, 2U, pt);
    ASSERT_EQ((PointType{1, 2, 3}), storage[0]);
    ASSERT_EQ(pt, storage[1]);
    ASSERT_EQ(pt, storage[2]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[3]);
    ASSERT_EQ(storage.begin() + 1U, iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, first, last) to an empty PointCloud
 */
TEST(LinearStorageBaseDynamicSize, insertIteratorRange_1)
{
    PointType             pts[] = {{1, 1, 1}, {2, 2, 2}};
    StorageType           storage;
    StorageType::iterator iter = storage.insert(storage.begin(), &pts[0], &pts[2]);
    ASSERT_EQ(pts[0], storage[0]);
    ASSERT_EQ(pts[1], storage[1]);
    ASSERT_EQ(storage.begin(), iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, first, last) before first element
 */
TEST(LinearStorageBaseDynamicSize, insertIteratorRange_2)
{
    PointType             pts[]   = {{1, 1, 1}, {2, 2, 2}};
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    StorageType::iterator iter    = storage.insert(storage.begin(), &pts[0], &pts[2]);
    ASSERT_EQ(pts[0], storage[0]);
    ASSERT_EQ(pts[1], storage[1]);
    ASSERT_EQ((PointType{1, 2, 3}), storage[2]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[3]);
    ASSERT_EQ(storage.begin(), iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, first, last) before past the end element
 */
TEST(LinearStorageBaseDynamicSize, insertIteratorRange_3)
{
    PointType             pts[]   = {{1, 1, 1}, {2, 2, 2}};
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    PointType             pt{1, 1, 1};
    StorageType::iterator iter = storage.insert(storage.end(), &pts[0], &pts[2]);
    ASSERT_EQ((PointType{1, 2, 3}), storage[0]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[1]);
    ASSERT_EQ(pts[0], storage[2]);
    ASSERT_EQ(pts[1], storage[3]);
    ASSERT_EQ(storage.begin() + 2U, iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, first, last) before any element
 */
TEST(LinearStorageBaseDynamicSize, insertIteratorRange_4)
{
    PointType             pts[]   = {{1, 1, 1}, {2, 2, 2}};
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    PointType             pt{1, 1, 1};
    StorageType::iterator iter = storage.insert(storage.begin() + 1, &pts[0], &pts[2]);
    ASSERT_EQ((PointType{1, 2, 3}), storage[0]);
    ASSERT_EQ(pts[0], storage[1]);
    ASSERT_EQ(pts[1], storage[2]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[3]);
    ASSERT_EQ(storage.begin() + 1U, iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, ilist) to an empty PointCloud
 */
TEST(LinearStorageBaseDynamicSize, insertInitializerList_1)
{
    PointType             pts[] = {{1, 1, 1}, {2, 2, 2}};
    StorageType           storage;
    StorageType::iterator iter = storage.insert(storage.begin(), {{1, 1, 1}, {2, 2, 2}});
    ASSERT_EQ(pts[0], storage[0]);
    ASSERT_EQ(pts[1], storage[1]);
    ASSERT_EQ(storage.begin(), iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, ilist) before first element
 */
TEST(LinearStorageBaseDynamicSize, insertInitializerList_2)
{
    PointType             pts[]   = {{1, 1, 1}, {2, 2, 2}};
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    StorageType::iterator iter    = storage.insert(storage.begin(), {{1, 1, 1}, {2, 2, 2}});
    ASSERT_EQ(pts[0], storage[0]);
    ASSERT_EQ(pts[1], storage[1]);
    ASSERT_EQ((PointType{1, 2, 3}), storage[2]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[3]);
    ASSERT_EQ(storage.begin(), iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, ilist) before past the end element
 */
TEST(LinearStorageBaseDynamicSize, insertInitializerList_3)
{
    PointType             pts[]   = {{1, 1, 1}, {2, 2, 2}};
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    PointType             pt{1, 1, 1};
    StorageType::iterator iter = storage.insert(storage.end(), {{1, 1, 1}, {2, 2, 2}});
    ASSERT_EQ((PointType{1, 2, 3}), storage[0]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[1]);
    ASSERT_EQ(pts[0], storage[2]);
    ASSERT_EQ(pts[1], storage[3]);
    ASSERT_EQ(storage.begin() + 2U, iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:insert(pos, ilist) before any element
 */
TEST(LinearStorageBaseDynamicSize, insertInitializerList_4)
{
    PointType             pts[]   = {{1, 1, 1}, {2, 2, 2}};
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    PointType             pt{1, 1, 1};
    StorageType::iterator iter = storage.insert(storage.begin() + 1, {{1, 1, 1}, {2, 2, 2}});
    ASSERT_EQ((PointType{1, 2, 3}), storage[0]);
    ASSERT_EQ(pts[0], storage[1]);
    ASSERT_EQ(pts[1], storage[2]);
    ASSERT_EQ((PointType{2, 3, 4}), storage[3]);
    ASSERT_EQ(storage.begin() + 1U, iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase:erase(pos) on a non-empty container.
 */
TEST(LinearStorageBaseDynamicSize, erase_1)
{
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}};
    StorageType::iterator iter    = storage.erase(storage.begin());
    ASSERT_EQ(1U, storage.size());
    ASSERT_EQ((PointType{2, 3, 4}), *iter);
    iter = storage.erase(storage.begin());
    ASSERT_EQ(iter, storage.end());
}

/**
 * @brief Test Dynamic size LinearStorageBase:erase(first, last) on a non-empty container.
 */
TEST(LinearStorageBaseDynamicSize, erase_2)
{
    StorageType           storage = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    StorageType::iterator iter    = storage.erase(storage.begin(), storage.begin() + 1);
    ASSERT_EQ(2U, storage.size());
    ASSERT_EQ((PointType{2, 3, 4}), *iter);
    iter = storage.erase(storage.begin(), storage.end());
    ASSERT_EQ(iter, storage.end());
}

/**
 * @brief Test Dynamic size LinearStorageBase:push_back(value const&)
 */
TEST(LinearStorageBaseDynamicSize, push_back_1)
{
    StorageType storage;
    PointType   pt{1, 1, 1};
    storage.push_back(pt);
    ASSERT_EQ(pt, storage[0]);
    ASSERT_EQ(1U, storage.size());

    pt = {2, 2, 2};
    storage.push_back(pt);
    ASSERT_EQ(pt, storage[1]);
    ASSERT_EQ(2U, storage.size());
}

/**
 * @brief Test Dynamic size LinearStorageBase:push_back(value&&)
 */
TEST(LinearStorageBaseDynamicSize, push_back_2)
{
    StorageType storage;
    storage.push_back(PointType{1, 1, 1});
    ASSERT_EQ((PointType{1, 1, 1}), storage[0]);
    ASSERT_EQ(1U, storage.size());

    storage.push_back(PointType{2, 2, 2});
    ASSERT_EQ((PointType{2, 2, 2}), storage[1]);
    ASSERT_EQ(2U, storage.size());
}

/**
 * @brief Test Dynamic size LinearStorageBase:emplace_back(args...)
 */
TEST(LinearStorageBaseDynamicSize, emplace_back_1)
{
    StorageType storage;
    storage.emplace_back(1, 1, 1);
    ASSERT_EQ((PointType{1, 1, 1}), storage[0]);
    ASSERT_EQ(1U, storage.size());

    storage.emplace_back(2, 2, 2);
    ASSERT_EQ((PointType{2, 2, 2}), storage[1]);
    ASSERT_EQ(2U, storage.size());
}

/**
 * @brief Test Dynamic size LinearStorageBase:pop_back()
 */
TEST(LinearStorageBaseDynamicSize, pop_back)
{
    StorageType storage = {{1, 1, 1}, {2, 2, 2}};
    storage.pop_back();
    ASSERT_EQ(1U, storage.size());
    ASSERT_EQ((PointType{1, 1, 1}), *(storage.end() - 1));

    storage.pop_back();
    ASSERT_EQ(0U, storage.size());
}

/**
 * @brief Test Dynamic size LinearStorageBase::GetSerializedSize
 */
TEST(LinearStorageBaseDynamicSize, GetSerializedSize)
{
    StorageType storage = {{1, 1, 1}, {2, 2, 2}};

    ASSERT_EQ(28U, storage.GetSerializedSize<4U>());
    ASSERT_EQ(40U, storage.GetSerializedSize<8U>());
}

/**
 * @brief Test Dynamic size LinearStorageBase:::Serialize and Deserialize
 */
TEST(LinearStorageBaseDynamicSize, SerializeAndDeserialize)
{
    StorageType           storage_input = {{1, 2, 3}, {2, 3, 4}};
    StorageType           storage_output;

    uint8_t buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << storage_input;
    ASSERT_EQ(storage_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> storage_output;

    ASSERT_EQ(storage_input[0], storage_output[0]);
    ASSERT_EQ(storage_input[1], storage_output[1]);
    ASSERT_EQ(storage_input.size(), storage_output.size());
}

/**
 * @brief Test Dynamic size LinearStorageBase iterator::operator==(iterator)
 */
TEST(LinearStorageDynamicSizeIterator, OperatorEqual)
{
    StorageType storage = {{1, 1, 1}, {2, 2, 2}};
    ASSERT_EQ(storage.begin(), storage.end() - 2);
}

/**
 * @brief Test Dynamic size LinearStorageBase iterator::operator!=(iterator)
 */
TEST(LinearStorageDynamicSizeIterator, OperatorNotEqual)
{
    StorageType storage = {{1, 1, 1}, {2, 2, 2}};
    ASSERT_NE(storage.begin(), storage.end());
}

/**
 * @brief Test Dynamic size LinearStorageBase iterator::operator<(iterator)
 */
TEST(LinearStorageDynamicSizeIterator, OperatorLessThan)
{
    StorageType storage = {{1, 1, 1}, {2, 2, 2}};
    ASSERT_LT(storage.begin(), storage.end() - 1U);
}

/**
 * @brief Test Dynamic size LinearStorageBase iterator::operator>(iterator)
 */
TEST(LinearStorageDynamicSizeIterator, OperatorGreaterThan)
{
    StorageType storage = {{1, 1, 1}, {2, 2, 2}};
    ASSERT_GT(storage.end(), storage.begin() - 1U);
}

/**
 * @brief Test Dynamic size LinearStorageBase iterator::operator<=(iterator)
 */
TEST(LinearStorageDynamicSizeIterator, OperatorLessEqual)
{
    StorageType storage = {{1, 1, 1}, {2, 2, 2}};
    ASSERT_LE(storage.begin(), storage.end() - 1U);
    ASSERT_LE(storage.begin(), storage.end() - 2U);
}

/**
 * @brief Test Dynamic size LinearStorageBase iterator::operator>=(iterator)
 */
TEST(LinearStorageDynamicSizeIterator, OperatorGreaterEqual)
{
    StorageType storage = {{1, 1, 1}, {2, 2, 2}};
    ASSERT_GE(storage.end(), storage.begin() - 1U);
    ASSERT_GE(storage.end(), storage.begin() - 2U);
}

/**
 * @brief Test Dynamic size LinearStorageBase iterator::operator++()
 */
TEST(LinearStorageDynamicSizeIterator, OperatorPrefixIncreament)
{
    StorageType           storage = {{1, 1, 1}, {2, 2, 2}};
    StorageType::iterator iter    = storage.begin();
    ASSERT_EQ(storage[0], *iter);
    ASSERT_EQ(storage[1], *(++iter));
    ASSERT_EQ(storage.end(), ++iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase iterator::operator++(int)
 */
TEST(LinearStorageDynamicSizeIterator, OperatorPostfixIncreament)
{
    StorageType           storage = {{1, 1, 1}, {2, 2, 2}};
    StorageType::iterator iter    = storage.begin();
    ASSERT_EQ(storage[0], *iter);
    iter++;
    ASSERT_EQ(storage[1], *iter);
    iter++;
    ASSERT_EQ(storage.end(), iter);
}

/**
 * @brief Test Dynamic size LinearStorageBase iterator::operator++()
 */
TEST(LinearStorageDynamicSizeIterator, OperatorPrefixDecreament)
{
    StorageType           storage = {{1, 1, 1}, {2, 2, 2}};
    StorageType::iterator iter    = storage.end();
    ASSERT_EQ(storage.end(), iter);
    ASSERT_EQ(storage[1], *(--iter));
    ASSERT_EQ(storage[0], *(--iter));
}

/**
 * @brief Test Dynamic size LinearStorageBase iterator::operator++(int)
 */
TEST(LinearStorageDynamicSizeIterator, OperatorPostfixDecreament)
{
    StorageType           storage = {{1, 1, 1}, {2, 2, 2}};
    StorageType::iterator iter    = storage.end();
    ASSERT_EQ(storage.end(), iter);
    iter--;
    ASSERT_EQ(storage[1], *iter);
    iter--;
    ASSERT_EQ(storage[0], *iter);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
