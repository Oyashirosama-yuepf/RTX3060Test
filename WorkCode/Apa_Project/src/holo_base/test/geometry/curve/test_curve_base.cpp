/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_curve_parametric_base.cpp
 * @brief This header file test CurveParametricBaseT objects.
 * @author ZhangJiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-18
 */

#include <gtest/gtest.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>

#include <type_traits>

using PointType = holo::geometry::Point2T<holo::float64_t>;
template <size_t SIZE = 256U>
using CurveParametricLinearType = holo::geometry::CurveBezier<PointType, SIZE, 1U>;
template <size_t SIZE = 256U>
using CurveExplicitLinearType = holo::geometry::CurvePolynomial<PointType, SIZE, 1U>;

using Serializer      = holo::serialization::Serializer<false, 4>;
using Deserializer    = holo::serialization::Deserializer<false, 4>;

TEST(CurveBase, DefaultConstructor)
{
    CurveParametricLinearType<> curve;
    ASSERT_EQ(0U, curve.size());
}

TEST(CurveBase, ConstructWithIteratorRange)
{
    PointType                        pt[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<> curve(&pt[0], &pt[4]);
    ASSERT_EQ(4U, curve.size());

    try
    {
        CurveParametricLinearType<3> curve2(&pt[0], &pt[4]);
        FAIL() << "Expect throw std::bad_alloc exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(CurveBase, ConstructWithInitializerList)
{
    CurveParametricLinearType<> curve({{0, 0}, {1, 0}, {1, 1}, {2, 1}});
    ASSERT_EQ(4U, curve.size());

    try
    {
        CurveParametricLinearType<3> curve2({{0, 0}, {1, 0}, {1, 1}, {2, 1}});
        FAIL() << "Expect throw std::bad_alloc exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(CurveBase, ConstructWithCurveWithDifferentSize)
{
    CurveParametricLinearType<10U> curve1 = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<20U> curve2(curve1);
    ASSERT_EQ(4U, curve2.size());

    try
    {
        CurveParametricLinearType<10U> curve3 = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
        CurveParametricLinearType<3U>  curve4(curve3);
        FAIL() << "Expect throw std::bad_alloc exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(CurveBase, ConstructWithRValueCurveWithDifferentSize)
{
    CurveParametricLinearType<10U> curve1 = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<20U> curve2(std::move(curve1));
    ASSERT_EQ(4U, curve2.size());

    try
    {
        CurveParametricLinearType<10U> curve3 = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
        CurveParametricLinearType<3U>  curve4(std::move(curve3));
        FAIL() << "Expect throw std::bad_alloc exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(CurveBase, At)
{
    PointType                           pt[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<10U> curve(&pt[0], &pt[4]);
    for (size_t idx = 0; idx < 4; ++idx)
    {
        ASSERT_EQ(pt[idx], curve.at(idx));
    }
}

TEST(CurveBase, BracketOperator)
{
    PointType                           pt[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<10U> curve(&pt[0], &pt[4]);
    for (size_t idx = 0; idx < 4; ++idx)
    {
        ASSERT_EQ(pt[idx], curve[idx]);
    }
}

TEST(CurveBase, Front)
{
    PointType                           pt[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<10U> curve(&pt[0], &pt[4]);
    ASSERT_EQ(pt[0], curve.front());
}

TEST(CurveBase, Back)
{
    PointType                           pt[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<10U> curve(&pt[0], &pt[4]);
    ASSERT_EQ(pt[3], curve.back());
}

TEST(CurveBase, Begin)
{
    PointType                           pt[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<10U> curve(&pt[0], &pt[4]);
    ASSERT_EQ(pt[0], *curve.begin());
    ASSERT_EQ(pt[0], *curve.cbegin());
}

TEST(CurveBase, End)
{
    PointType                           pt[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<10U> curve(&pt[0], &pt[4]);
    ASSERT_EQ(pt[3], *(curve.end() - 1));
    ASSERT_EQ(pt[3], *(curve.cend() - 1));
}

TEST(CurveBase, RBegin)
{
    PointType                           pt[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<10U> curve(&pt[0], &pt[4]);
    ASSERT_EQ(pt[3], *curve.rbegin());
    ASSERT_EQ(pt[3], *curve.crbegin());
}

TEST(CurveBase, REnd)
{
    PointType                           pt[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<10U> curve(&pt[0], &pt[4]);
    ASSERT_EQ(pt[0], *(curve.rend() - 1));
    ASSERT_EQ(pt[0], *(curve.crend() - 1));
}

TEST(CurveBase, Empty)
{
    CurveParametricLinearType<10U> curve;
    ASSERT_TRUE(curve.empty());
    curve = {{0, 0}};
    ASSERT_FALSE(curve.empty());
}

TEST(CurveBase, Size)
{
    CurveParametricLinearType<10U> curve{{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    ASSERT_EQ(4U, curve.size());
}

TEST(CurveBase, MaxSize)
{
    CurveParametricLinearType<10U> curve{{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    ASSERT_EQ(10U, curve.max_size());
}

TEST(CurveBase, Capacity)
{
    CurveParametricLinearType<10U> curve{{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    ASSERT_EQ(10U, curve.capacity());
}

TEST(CurveBase, Clear)
{
    CurveParametricLinearType<10U> curve{{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    ASSERT_EQ(4U, curve.size());
    curve.clear();
    ASSERT_EQ(0U, curve.size());
}

TEST(CurveBase, Erase)
{
    CurveParametricLinearType<10U> curve{{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    ASSERT_EQ(4U, curve.size());
    auto it = curve.erase(curve.begin());
    ASSERT_EQ((PointType{1, 0}), *it);
    ASSERT_EQ(3U, curve.size());
}

TEST(CurveBase, EraseRange)
{
    CurveParametricLinearType<10U> curve{{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    ASSERT_EQ(4U, curve.size());
    auto it = curve.erase(curve.begin(), curve.begin() + 3);
    ASSERT_EQ((PointType{2, 1}), *it);
    ASSERT_EQ(1U, curve.size());
}

TEST(CurveBase, TestGetSerializedSize)
{
    PointType                   pt[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<> input_base(&pt[0], &pt[4]);
    input_base.SetStartCondition(::holo::geometry::details::ConditionType::FIRST_DERIVATIVE, {3, 5});
    input_base.SetEndCondition(::holo::geometry::details::ConditionType::DEFAULT, {0, 0});
    input_base.Update();
    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);
    input_base.Serialize(serializer);
    ASSERT_EQ(input_base.GetSerializedSize(), serializer.GetSize());
}

TEST(CurveBase, TestSerialization)
{
    PointType                   pt[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<> input_base(&pt[0], &pt[4]);
    input_base.SetStartCondition(::holo::geometry::details::ConditionType::FIRST_DERIVATIVE, {1, 3});
    input_base.SetEndCondition(::holo::geometry::details::ConditionType::DEFAULT, {0, 0});
    input_base.Update();

    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);
    input_base.Serialize(serializer);

    Deserializer deserializer(buffer, serializer.GetSize());
    CurveParametricLinearType<> output_base;
    output_base.Deserialize(deserializer);

    ASSERT_EQ(output_base.size(), input_base.size());
    ASSERT_EQ(output_base.GetStartType(), input_base.GetStartType());
    ASSERT_EQ(output_base.GetEndType(), input_base.GetEndType());
    for (size_t i = 0U; i < 4; ++i)
    {
        ASSERT_GT(1e-4, input_base.at(i).Dist(output_base.at(i)));
    }
    ASSERT_GT(1e-4, input_base.GetStartCondition().Dist(output_base.GetStartCondition()));
    ASSERT_GT(1e-4, input_base.GetEndCondition().Dist(output_base.GetEndCondition()));
}

/*
 * Tests for CurveParametricBaseT
 */

TEST(CurveParametricBase, DefaultConstructor)
{
    CurveParametricLinearType<> curve;
    ASSERT_EQ(0U, curve.size());
}

TEST(CurveParametricBase, ConstructWithIteratorRange)
{
    PointType                        pt[4] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<> curve(&pt[0], &pt[4]);
    ASSERT_EQ(4U, curve.size());

    try
    {
        CurveParametricLinearType<3> curve2(&pt[0], &pt[4]);
        FAIL() << "Expect throw std::bad_alloc exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(CurveParametricBase, ConstructWithInitializerList)
{
    CurveParametricLinearType<> curve({{0, 0}, {1, 0}, {1, 1}, {2, 1}});
    ASSERT_EQ(4U, curve.size());

    try
    {
        CurveParametricLinearType<3> curve2({{0, 0}, {1, 0}, {1, 1}, {2, 1}});
        FAIL() << "Expect throw std::bad_alloc exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(CurveParametricBase, ConstructWithCurveWithDifferentSize)
{
    CurveParametricLinearType<10U> curve1 = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<20U> curve2(curve1);
    ASSERT_EQ(4U, curve2.size());

    try
    {
        CurveParametricLinearType<10U> curve3 = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
        CurveParametricLinearType<3U>  curve4(curve3);
        FAIL() << "Expect throw std::bad_alloc exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(CurveParametricBase, ConstructWithRValueCurveWithDifferentSize)
{
    CurveParametricLinearType<10U> curve1 = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    CurveParametricLinearType<20U> curve2(std::move(curve1));
    ASSERT_EQ(4U, curve2.size());

    try
    {
        CurveParametricLinearType<10U> curve3 = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
        CurveParametricLinearType<3U>  curve4(std::move(curve3));
        FAIL() << "Expect throw std::bad_alloc exception";
    }
    catch (std::bad_alloc const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(CurveParametricBase, AssignIteratorRange)
{
    PointType pts1[4] = {{0, 0}, {1, 0}, {2, 1}, {3, 1}};
    PointType pts2[4] = {{0, 0}, {1, 0}, {0.5, 1}, {2, 1}};

    CurveParametricLinearType<10U> curve;
    curve.assign(&pts1[0], &pts1[4]);
    ASSERT_EQ(4U, curve.size());
    curve.assign(&pts2[0], &pts2[4]);
    ASSERT_EQ(4U, curve.size());

    CurveParametricLinearType<3U> curve2;
    EXPECT_THROW(curve2.assign(&pts1[0], &pts1[4]), std::bad_alloc);
}

TEST(CurveParametricBase, AssignInitializerList)
{
    CurveParametricLinearType<10U> curve;
    curve.assign({{0, 0}, {1, 0}, {2, 1}, {3, 1}});
    ASSERT_EQ(4U, curve.size());
    curve.assign({{0, 0}, {1, 0}, {0.5, 1}, {2, 1}});
    ASSERT_EQ(4U, curve.size());

    CurveParametricLinearType<3U> curve2;
    EXPECT_THROW(curve2.assign({{0, 0}, {1, 0}, {2, 1}, {3, 1}}), std::bad_alloc);
}

TEST(CurveParametricBase, InsertValue)
{
    CurveParametricLinearType<6U> curve{{0, 0}, {1, 0}, {2, 0}};
    PointType                          pt{1, 1};
    auto                               it = curve.insert(curve.begin(), pt);
    ASSERT_EQ((PointType{1, 1}), *it);
    ASSERT_EQ(4, curve.size());

    pt = {3, 1};
    it = curve.insert(curve.end(), pt);
    ASSERT_EQ((PointType{3, 1}), *it);
    ASSERT_EQ(5, curve.size());

    pt = {2, 1};
    it = curve.insert(curve.begin() + 3, pt);
    ASSERT_EQ((PointType{2, 1}), *it);
    ASSERT_EQ(6, curve.size());
    EXPECT_THROW(curve.insert(it, PointType{0, 0}), std::bad_alloc);
}

TEST(CurveParametricBase, InsertRValue)
{
    CurveParametricLinearType<6U> curve{{0, 0}, {1, 0}, {2, 0}};

    auto it = curve.insert(curve.begin(), PointType{1, 1});
    ASSERT_EQ((PointType{1, 1}), *it);
    ASSERT_EQ(4, curve.size());
    it = curve.insert(curve.end(), PointType{3, 1});
    ASSERT_EQ((PointType{3, 1}), *it);
    ASSERT_EQ(5, curve.size());
    it = curve.insert(curve.begin() + 3, PointType{2, 1});
    ASSERT_EQ((PointType{2, 1}), *it);
    ASSERT_EQ(6, curve.size());
    EXPECT_THROW(curve.insert(it, PointType{0, 0}), std::bad_alloc);
}

TEST(CurveParametricBase, InsertIteratorRange)
{
    PointType pt[10] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}};
    CurveParametricLinearType<10U> curve{};

    auto it = curve.insert(curve.begin(), &pt[0], &pt[3]);
    ASSERT_EQ(pt[0], *it);
    ASSERT_EQ(3, curve.size());

    it = curve.insert(curve.end(), &pt[7], &pt[10]);
    ASSERT_EQ(pt[7], *it);
    ASSERT_EQ(6, curve.size());

    it = curve.insert(it, &pt[3], &pt[7]);
    ASSERT_EQ(pt[3], *it);
    ASSERT_EQ(10, curve.size());

    it = curve.insert(it, &pt[0], &pt[0]);
    ASSERT_EQ(pt[3], *it);
    EXPECT_THROW(curve.insert(it, &pt[0], &pt[1]), std::bad_alloc);
}

TEST(CurveParametricBase, InsertInitializerList)
{
    PointType pt[10] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}};
    CurveParametricLinearType<10U> curve{};

    auto it = curve.insert(curve.begin(), {{0, 0}, {1, 0}, {2, 0}});
    ASSERT_EQ(pt[0], *it);
    ASSERT_EQ(3, curve.size());

    it = curve.insert(curve.end(), {{7, 0}, {8, 0}, {9, 0}});
    ASSERT_EQ(pt[7], *it);
    ASSERT_EQ(6, curve.size());

    it = curve.insert(it, {{3, 0}, {4, 0}, {5, 0}, {6, 0}});
    ASSERT_EQ(pt[3], *it);
    ASSERT_EQ(10, curve.size());

    it = curve.insert(it, {});
    ASSERT_EQ(pt[3], *it);
    EXPECT_THROW(curve.insert(it, {{10, 10}}), std::bad_alloc);
}

TEST(CurveParametricBase, Emplace)
{
    CurveParametricLinearType<6U> curve{{0, 0}, {1, 0}, {2, 0}};

    auto it = curve.emplace(curve.begin(), 1.0, 1.0);
    ASSERT_EQ((PointType{1, 1}), *it);
    ASSERT_EQ(4, curve.size());
    it = curve.emplace(curve.end(), 3.0, 1.0);
    ASSERT_EQ((PointType{3, 1}), *it);
    ASSERT_EQ(5, curve.size());
    it = curve.emplace(curve.begin() + 3, 2.0, 1.0);
    ASSERT_EQ((PointType{2, 1}), *it);
    ASSERT_EQ(6, curve.size());
    EXPECT_THROW(curve.emplace(it, 0.0, 0.0), std::bad_alloc);
}

TEST(CurveParametricBase, PushBack)
{
    CurveParametricLinearType<2U> curve;

    PointType pt{0, 0};
    curve.push_back(pt);
    ASSERT_EQ(1U, curve.size());

    pt = {1, 0};
    curve.push_back(std::move(pt));
    ASSERT_EQ(2U, curve.size());

    pt = {2, 0};
    EXPECT_THROW(curve.push_back(pt), std::bad_alloc);

    pt = {2, 0};
    EXPECT_THROW(curve.push_back(std::move(pt)), std::bad_alloc);
}

TEST(CurveParametricBase, EmplaceBack)
{
    CurveParametricLinearType<2U> curve;

    curve.emplace_back(0, 0);
    ASSERT_EQ(1U, curve.size());

    curve.emplace_back(1, 0);
    ASSERT_EQ(2U, curve.size());
    EXPECT_THROW(curve.emplace_back(2, 0), std::bad_alloc);
}

TEST(CurveParametricBase, UpdateKnot)
{
    CurveParametricLinearType<4U> curve = {{1, 0}, {2, 0}, {3, 0}};

    auto it = curve.UpdateKnot(curve.begin() + 2, {4, 0});
    ASSERT_EQ(3U, curve.size());
    ASSERT_EQ((PointType{4, 0}), *it);
    ASSERT_EQ((PointType{4, 0}), *(curve.begin() + 2));

    PointType pt = {6, 0};
    it = curve.UpdateKnot(curve.begin() + 1, pt);
    ASSERT_EQ(3U, curve.size());
    ASSERT_EQ(pt, *it);
    ASSERT_EQ(pt, *(curve.begin() + 1));
}

/*
 * Tests for CurveExplicitBaseT
 */

TEST(CurveExplicitBase, TestGetSerializedSize)
{
    CurveExplicitLinearType<> input_base({{0, 0}, {1, 0}, {2, 1}, {3, 1}});
    input_base.SetStartCondition(::holo::geometry::details::ConditionType::DEFAULT, {0, 0});
    input_base.SetEndCondition(::holo::geometry::details::ConditionType::SECOND_DERIVATIVE, {1, 2});
    input_base.Update();

    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);
    input_base.Serialize(serializer);
    ASSERT_EQ(input_base.GetSerializedSize(), serializer.GetSize());
}

TEST(CurveExplicitBase, TestSerialization)
{
    CurveExplicitLinearType<> input_base({{0, 0}, {1, 0}, {2, 1}, {3, 1}});
    input_base.SetStartCondition(::holo::geometry::details::ConditionType::DEFAULT, {0, 0});
    input_base.SetEndCondition(::holo::geometry::details::ConditionType::SECOND_DERIVATIVE, {1, 2});
    input_base.Update();

    uint8_t buffer[1024];
    Serializer serializer(buffer, 1024);
    input_base.Serialize(serializer);

    Deserializer deserializer(buffer, serializer.GetSize());
    CurveExplicitLinearType<> output_base;
    output_base.Deserialize(deserializer);

    ASSERT_EQ(output_base.size(), input_base.size());
    ASSERT_EQ(output_base.GetStartType(), input_base.GetStartType());
    ASSERT_EQ(output_base.GetEndType(), input_base.GetEndType());
    for (size_t i = 0U; i < 4; ++i)
    {
        ASSERT_GT(1e-4, input_base.at(i).Dist(output_base.at(i)));
    }
    ASSERT_GT(1e-4, input_base.GetStartCondition().Dist(output_base.GetStartCondition()));
    ASSERT_GT(1e-4, input_base.GetEndCondition().Dist(output_base.GetEndCondition()));
}

TEST(CurveExplicitBase, DefaultConstructor)
{
    CurveExplicitLinearType<> curve;
    ASSERT_EQ(0U, curve.size());
}

TEST(CurveExplicitBase, ConstructWithIteratorRange)
{
    PointType                      pt[5] = {{0, 0}, {1, 0}, {2, 1}, {3, 1}, {3, 2}};
    CurveExplicitLinearType<> curve(&pt[0], &pt[4]);
    ASSERT_EQ(4U, curve.size());

    try
    {
        CurveExplicitLinearType<3> curve2(&pt[0], &pt[4]);
        FAIL() << "Expect throw std::bad_alloc exception";
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
        CurveExplicitLinearType<4> curve2(&pt[1], &pt[5]);
        FAIL() << "Expect throw exception";
    }
    catch (holo::exception::BadKnotOrderException const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(CurveExplicitBase, ConstructWithInitializerList)
{
    CurveExplicitLinearType<> curve({{0, 0}, {1, 0}, {2, 1}, {3, 1}});
    ASSERT_EQ(4U, curve.size());

    try
    {
        CurveExplicitLinearType<3> curve2({{0, 0}, {1, 0}, {2, 1}, {3, 1}});
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
        CurveExplicitLinearType<4> curve2({{0, 0}, {1, 0}, {1, 1}, {3, 1}});
        FAIL() << "Expect throw exception";
    }
    catch (holo::exception::BadKnotOrderException const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(CurveExplicitBase, ConstructWithCurveWithDifferentSize)
{
    CurveExplicitLinearType<10U> curve1 = {{0, 0}, {1, 0}, {2, 1}, {3, 1}};
    CurveExplicitLinearType<20U> curve2(curve1);
    ASSERT_EQ(4U, curve2.size());

    try
    {
        CurveExplicitLinearType<10U> curve3 = {{0, 0}, {1, 0}, {2, 1}, {3, 1}};
        CurveExplicitLinearType<3U>  curve4(curve3);
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
        CurveParametricLinearType<10U> curve5 = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
        CurveExplicitLinearType<6U>    curve6(curve5);
        FAIL() << "Expect throw exception";
    }
    catch (holo::exception::BadKnotOrderException const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(CurveExplicitBase, ConstructWithRValueCurveWithDifferentSize)
{
    CurveExplicitLinearType<10U> curve1 = {{0, 0}, {1, 0}, {2, 1}, {3, 1}};
    CurveExplicitLinearType<20U> curve2(std::move(curve1));
    ASSERT_EQ(4U, curve2.size());

    try
    {
        CurveExplicitLinearType<10U> curve3 = {{0, 0}, {1, 0}, {2, 1}, {3, 1}};
        CurveExplicitLinearType<3U>  curve4(std::move(curve3));
        FAIL() << "Expect throw std::bad_alloc exception";
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
        CurveParametricLinearType<10U> curve5 = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
        CurveExplicitLinearType<6U>    curve6(std::move(curve5));
        FAIL() << "Expect throw exception";
    }
    catch (holo::exception::BadKnotOrderException const& e)
    {
    }
    catch (...)
    {
        FAIL() << "Caught unexpected exception";
    }
}

TEST(CurveExplicitBase, AssignIteratorRange)
{
    PointType pts1[4] = {{0, 0}, {1, 0}, {2, 1}, {3, 1}};
    PointType pts2[4] = {{0, 0}, {1, 0}, {0.5, 1}, {2, 1}};

    CurveExplicitLinearType<10U> curve;
    curve.assign(&pts1[0], &pts1[4]);
    ASSERT_EQ(4U, curve.size());
    EXPECT_THROW(curve.assign(&pts2[0], &pts2[4]), holo::exception::BadKnotOrderException);

    CurveExplicitLinearType<3U> curve2;
    EXPECT_THROW(curve2.assign(&pts1[0], &pts1[4]), std::bad_alloc);
}

TEST(CurveExplicitBase, AssignInitializerList)
{
    CurveExplicitLinearType<10U> curve;
    curve.assign({{0, 0}, {1, 0}, {2, 1}, {3, 1}});
    ASSERT_EQ(4U, curve.size());
    EXPECT_THROW(curve.assign({{0, 0}, {1, 0}, {0.5, 1}, {2, 1}}), holo::exception::BadKnotOrderException);

    CurveExplicitLinearType<3U> curve2;
    EXPECT_THROW(curve2.assign({{0, 0}, {1, 0}, {2, 1}, {3, 1}}), std::bad_alloc);
}

TEST(CurveExplicitBase, InsertValue)
{
    CurveExplicitLinearType<6U> curve;

    PointType pt{0, 0};
    auto      it = curve.insert(curve.begin(), pt);
    ASSERT_EQ(pt, *it);
    ASSERT_EQ(1, curve.size());

    curve = {{0, 0}, {1, 0}, {2, 0}};

    pt = {-1, 1};
    it = curve.insert(curve.begin(), pt);
    ASSERT_EQ(pt, *it);
    ASSERT_EQ(4, curve.size());

    pt = {-1, 2};
    EXPECT_THROW(curve.insert(it, pt), holo::exception::BadKnotOrderException);

    pt = {3, 1};
    it = curve.insert(curve.end(), pt);
    ASSERT_EQ(pt, *it);
    ASSERT_EQ(5, curve.size());

    pt = {0.5, 1};
    it = curve.insert(curve.begin() + 2, pt);
    ASSERT_EQ(pt, *it);
    ASSERT_EQ(6, curve.size());

    pt = {0.2, 1};
    EXPECT_THROW(curve.insert(it, pt), std::bad_alloc);

    pt = {4, 0};
    EXPECT_THROW(curve.insert(it, pt), holo::exception::BadKnotOrderException);
}

TEST(CurveExplicitBase, InsertRValue)
{
    CurveExplicitLinearType<6U> curve;

    auto it = curve.insert(curve.begin(), PointType{0, 0});
    ASSERT_EQ((PointType{0, 0}), *it);
    ASSERT_EQ(1, curve.size());

    curve = {{0, 0}, {1, 0}, {2, 0}};

    it = curve.insert(curve.begin(), PointType{-1, 1});
    ASSERT_EQ((PointType{-1, 1}), *it);
    ASSERT_EQ(4, curve.size());

    EXPECT_THROW(curve.insert(it, PointType{-1, 1}), holo::exception::BadKnotOrderException);

    it = curve.insert(curve.end(), PointType{3, 1});
    ASSERT_EQ((PointType{3, 1}), *it);
    ASSERT_EQ(5, curve.size());
    it = curve.insert(curve.begin() + 2, PointType{0.5, 1});
    ASSERT_EQ((PointType{0.5, 1}), *it);
    ASSERT_EQ(6, curve.size());

    EXPECT_THROW(curve.insert(it, PointType{0.2, 0}), std::bad_alloc);
    EXPECT_THROW(curve.insert(it, PointType{4, 0}), holo::exception::BadKnotOrderException);
}

TEST(CurveExplicitBase, InsertIteratorRange)
{
    PointType pt[11] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}};
    CurveExplicitLinearType<10U> curve{};

    auto it = curve.insert(curve.begin(), &pt[0], &pt[3]);
    ASSERT_EQ(pt[0], *it);
    ASSERT_EQ(3, curve.size());

    it = curve.insert(curve.end(), &pt[7], &pt[10]);
    ASSERT_EQ(pt[7], *it);
    ASSERT_EQ(6, curve.size());

    it = curve.insert(it, &pt[3], &pt[7]);
    ASSERT_EQ(pt[3], *it);
    ASSERT_EQ(10, curve.size());

    it = curve.insert(it, &pt[0], &pt[0]);
    ASSERT_EQ(pt[3], *it);
    EXPECT_THROW(curve.insert(curve.end(), &pt[10], &pt[11]), std::bad_alloc);
    EXPECT_THROW(curve.insert(it, &pt[1], &pt[2]), holo::exception::BadKnotOrderException);
}

TEST(CurveExplicitBase, InsertInitializerList)
{
    PointType pt[11] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}};
    CurveExplicitLinearType<10U> curve{};

    auto it = curve.insert(curve.begin(), {{0, 0}, {1, 0}, {2, 0}});
    ASSERT_EQ(pt[0], *it);
    ASSERT_EQ(3, curve.size());

    it = curve.insert(curve.end(), {{7, 0}, {8, 0}, {9, 0}});
    ASSERT_EQ(pt[7], *it);
    ASSERT_EQ(6, curve.size());

    it = curve.insert(it, {{3, 0}, {4, 0}, {5, 0}, {6, 0}});
    ASSERT_EQ(pt[3], *it);
    ASSERT_EQ(10, curve.size());

    it = curve.insert(it, {});
    ASSERT_EQ(pt[3], *it);
    EXPECT_THROW(curve.insert(curve.end(), {{10, 10}}), std::bad_alloc);
    EXPECT_THROW(curve.insert(it, {{1, 10}}), holo::exception::BadKnotOrderException);
}

TEST(CurveExplicitBase, Emplace)
{
    CurveExplicitLinearType<6U> curve;

    auto it = curve.emplace(curve.begin(), 0, 0);
    ASSERT_EQ((PointType{0, 0}), *it);
    ASSERT_EQ(1U, curve.size());

    curve = {{0, 0}, {1, 0}, {2, 0}};

    it = curve.emplace(curve.begin(), -1.0, 1.0);
    ASSERT_EQ((PointType{-1, 1}), *it);
    ASSERT_EQ(4, curve.size());
    it = curve.emplace(curve.end(), 3.0, 1.0);
    ASSERT_EQ((PointType{3, 1}), *it);
    ASSERT_EQ(5, curve.size());
    it = curve.emplace(curve.begin() + 3, 1.5, 1.0);
    ASSERT_EQ((PointType{1.5, 1}), *it);
    ASSERT_EQ(6, curve.size());
    EXPECT_THROW(curve.emplace(it, 1.2, 0.0), std::bad_alloc);
    EXPECT_THROW(curve.emplace(it, 1.8, 0.0), holo::exception::BadKnotOrderException);
}

TEST(CurveExplicitBase, PushBack)
{
    CurveExplicitLinearType<2U> curve;

    PointType pt{0, 0};
    curve.push_back(pt);
    ASSERT_EQ(1U, curve.size());

    pt = {-1, 0};
    EXPECT_THROW(curve.push_back(pt), holo::exception::BadKnotOrderException);

    pt = {1, 0};
    curve.push_back(pt);
    ASSERT_EQ(2U, curve.size());

    pt = {2, 0};
    EXPECT_THROW(curve.push_back(pt), std::bad_alloc);
}

TEST(CurveExplicitBase, PushBackRValue)
{
    CurveExplicitLinearType<2U> curve;

    PointType pt{0, 0};
    curve.push_back(std::move(pt));
    ASSERT_EQ(1U, curve.size());

    pt = {-1, 0};
    EXPECT_THROW(curve.push_back(std::move(pt)), holo::exception::BadKnotOrderException);

    pt = {1, 0};
    curve.push_back(std::move(pt));
    ASSERT_EQ(2U, curve.size());

    pt = {2, 0};
    EXPECT_THROW(curve.push_back(std::move(pt)), std::bad_alloc);
}

TEST(CurveExplicitBase, EmplaceBack)
{
    CurveExplicitLinearType<2U> curve;

    curve.emplace_back(0, 0);
    ASSERT_EQ(1U, curve.size());

    EXPECT_THROW(curve.emplace_back(-1, 0), holo::exception::BadKnotOrderException);

    curve.emplace_back(1, 0);
    ASSERT_EQ(2U, curve.size());
    EXPECT_THROW(curve.emplace_back(2, 0), std::bad_alloc);
}

TEST(CurveExplicitBase, UpdateKnot)
{
    CurveExplicitLinearType<4U> curve = {{1, 0}, {2, 0}, {3, 0}};

    auto it = curve.UpdateKnot(curve.begin() + 2, {4, 0});
    ASSERT_EQ(3U, curve.size());
    ASSERT_EQ((PointType{4, 0}), *it);
    ASSERT_EQ((PointType{4, 0}), *(curve.begin() + 2));

    PointType pt = {6, 0};
    EXPECT_THROW(curve.UpdateKnot(curve.begin() + 1, pt), holo::exception::BadKnotOrderException);
    pt = {3, 0};
    it = curve.UpdateKnot(curve.begin() + 1, pt);
    ASSERT_EQ(3U, curve.size());
    ASSERT_EQ(pt, *it);
    ASSERT_EQ(pt, *(curve.begin() + 1));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
