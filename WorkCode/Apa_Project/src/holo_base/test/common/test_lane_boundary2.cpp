/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_lane_boundary2.h
 * @brief This file tests LaneBoundary object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-07
 */

#include <gtest/gtest.h>
#include <holo/common/lane_boundary2.h>
#include <holo/core/types.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/point2.h>

using ScalarType       = holo::float64_t;
using PointType        = holo::geometry::Point2T<ScalarType>;
using CurveType        = holo::geometry::CurvePolynomial<PointType, 64U, 1U>;
using CurvePtrType     = std::shared_ptr<CurveType>;
using LaneBoundaryType = holo::common::LaneBoundary<CurveType>;

TEST(LaneBoundary, ConstructWithCurve)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();

    LaneBoundaryType boundary(0, 0, curve);
    ASSERT_EQ(0U, boundary.GetLength());
    ASSERT_EQ(1U, boundary.size());
}

TEST(LaneBoundary, ConstructWithCurveAndRange)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();

    LaneBoundaryType boundary(0, 0, curve, 0, curve->size());
    ASSERT_EQ(9U, boundary.GetLength());
    ASSERT_EQ(5U, boundary.size());
}

TEST(LaneBoundary, AccessBoundaryKnot)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();

    LaneBoundaryType boundary(0, 0, curve, 0, curve->size());
    for (size_t i = 0; i < curve->size(); ++i)
    {
        ASSERT_EQ(boundary[i], (*curve)[i]);
    }

    boundary.SetKnotRange(1, 3);
    for (size_t i = 0; i < boundary.size(); ++i)
    {
        ASSERT_EQ(boundary[i], (*curve)[i + 1U]);
    }
}

TEST(LaneBoundary, SetGetKnotRange)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();

    LaneBoundaryType boundary(0, 0, curve);

    boundary.SetKnotRange(1, 4);
    auto range = boundary.GetKnotRange();
    ASSERT_EQ(1U, range.first);
    ASSERT_EQ(4U, range.second);
    ASSERT_EQ(5U, boundary.GetLength());
}

TEST(LaneBoundary, GetCoordinateRange)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();

    LaneBoundaryType boundary(0, 0, curve);

    boundary.SetKnotRange(1, 4);
    auto range = boundary.GetCoordinateRange();

    ASSERT_EQ(3, range.first);
    ASSERT_EQ(8, range.second);
}

TEST(LaneBoundary, GetDerivativeByArcLength)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();

    LaneBoundaryType boundary(0, 0, curve);

    boundary.SetKnotRange(1, 4);
    ASSERT_EQ(5U, boundary.GetLength());

    ASSERT_NEAR((PointType{3, 0}).Dist(boundary.GetDerivativeByArcLength<0>(0)), 0, 1e-5);
    ASSERT_NEAR((PointType{3.5, 0}).Dist(boundary.GetDerivativeByArcLength<0>(0.5)), 0, 1e-5);
    ASSERT_NEAR((PointType{4, 0}).Dist(boundary.GetDerivativeByArcLength<0>(1)), 0, 1e-5);
    ASSERT_NEAR((PointType{4.5, 0}).Dist(boundary.GetDerivativeByArcLength<0>(1.5)), 0, 1e-5);
    ASSERT_NEAR((PointType{5, 0}).Dist(boundary.GetDerivativeByArcLength<0>(2)), 0, 1e-5);
}

TEST(LaneBoundary, GetDerivativeByCoordinate)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();

    LaneBoundaryType boundary(0, 0, curve);

    boundary.SetKnotRange(1, 4);
    ASSERT_EQ(5U, boundary.GetLength());

    ASSERT_NEAR((PointType{3, 0}).Dist(boundary.GetDerivativeByCoordinate<0>(3)), 0, 1e-5);
    ASSERT_NEAR((PointType{3.5, 0}).Dist(boundary.GetDerivativeByCoordinate<0>(3.5)), 0, 1e-5);
    ASSERT_NEAR((PointType{4, 0}).Dist(boundary.GetDerivativeByCoordinate<0>(4)), 0, 1e-5);
    ASSERT_NEAR((PointType{4.5, 0}).Dist(boundary.GetDerivativeByCoordinate<0>(4.5)), 0, 1e-5);
    ASSERT_NEAR((PointType{5, 0}).Dist(boundary.GetDerivativeByCoordinate<0>(5)), 0, 1e-5);
}

TEST(LaneBoundary, PushBack)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();

    LaneBoundaryType boundary(0, 0, curve);

    boundary.SetKnotRange(1, 4);
    EXPECT_THROW(boundary.push_back({8.5, 0}), holo::exception::OperationNotPermittedException);

    boundary.SetKnotRange(2, 5);
    boundary.push_back({10, 0});
    ASSERT_EQ(4U, boundary.size());
    ASSERT_EQ((PointType{10, 0}), boundary.back());

    boundary.push_back({11, 0});
    ASSERT_EQ(5U, boundary.size());
    ASSERT_EQ((PointType{11, 0}), boundary.back());
}

TEST(LaneBoundary, UpdateKnot)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();

    LaneBoundaryType boundary(0, 0, curve);

    boundary.SetKnotRange(1, 4);

    EXPECT_THROW(boundary.UpdateKnot(1U, {9, 0}), holo::exception::BadKnotOrderException);
    boundary.UpdateKnot(1U, {7, 0});
    ASSERT_EQ((PointType{7, 0}), boundary[1U]);
}

TEST(LaneBoundary, ConstructWithCurveAndRangeException)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();

    try
    {
        LaneBoundaryType boundary(0, 0, curve, curve->size()+1, curve->size());
    }
    catch(const std::exception& e)
    {
    }
}

TEST(LaneBoundary, AtException)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();
    LaneBoundaryType boundary(0, 0, curve, 0, curve->size());

    try
    {
        boundary.at(100);
    }
    catch(const std::exception& e)
    {
    }
}

TEST(LaneBoundary, SetKnotRangeException)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();
    LaneBoundaryType boundary(0, 0, curve, 0, curve->size());

    try
    {
        boundary.SetKnotRange(3U, 2U);
    }
    catch(const std::exception& e)
    {
    }
}

TEST(LaneBoundary, UpdateKnotException)
{
    CurvePtrType curve = std::make_shared<CurveType>(std::initializer_list<PointType>({{0, 0}, {3, 0}, {6, 0}, {8, 0}, {9, 0}}));
    curve->Update();
    LaneBoundaryType boundary(0, 0, curve, 0, curve->size());

    try
    {
        boundary.UpdateKnot(100U, {7, 0});
    }
    catch(const std::exception& e)
    {
    }
}

TEST(LaneBoundaryPolynomial, Constructor)
{
    holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float64_t, 3U>> boundary0(
        holo::numerics::Polynomial<holo::float64_t, 3U>({1, 2, 3, 4}));
    ASSERT_FALSE(boundary0.IsValid());

    holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float64_t, 3U>> boundary1(
        holo::numerics::Polynomial<holo::float64_t, 3U>({1, 2, 3, 4}), 0, 3);
    ASSERT_TRUE(boundary1.IsValid());
}

TEST(LaneBoundaryPolynomial, GetLength)
{
    holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float64_t, 3U>> boundary(
        holo::numerics::Polynomial<holo::float64_t, 3U>({1, 2, 3, 4}), 0, 3);

    auto            range  = boundary.GetCoordinateRange();
    auto            pt1    = boundary.GetSampleByCoordinate(range.first);
    auto            pt2    = boundary.GetSampleByCoordinate(range.first + (range.second - range.first) / 256U);
    holo::float64_t length = 0;
    length += pt2.Dist(pt1);
    for (size_t i = 1U; i <= 256U; ++i)
    {
        pt1 = pt2;
        pt2 = boundary.GetSampleByCoordinate(range.first + (range.second - range.first) / 256U * i);
        length += pt2.Dist(pt1);
    }

    ASSERT_NEAR(length, boundary.GetLength(), length / 100);
}

TEST(LaneBoundaryPolynomial, SetGetCoordinateRange)
{
    holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float64_t, 3U>> boundary(
        holo::numerics::Polynomial<holo::float64_t, 3U>({1, 2, 3, 4}));
    ASSERT_FALSE(boundary.IsValid());

    boundary.SetCoordinateRange(0, 1);
    auto range = boundary.GetCoordinateRange();
    ASSERT_EQ(0.0, range.first);
    ASSERT_EQ(1.0, range.second);

    EXPECT_THROW(boundary.SetCoordinateRange(1, 0), holo::exception::OutOfRangeException);
}

TEST(LaneBoundaryPolynomial, GetDerivativeByArcLength)
{
    holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float64_t, 3U>> boundary(
        holo::numerics::Polynomial<holo::float64_t, 3U>({1, 2, 3, 4}), 0, 3);
    ASSERT_NEAR(PointType(0, 1).Dist(boundary.GetDerivativeByArcLength<0>(0)), 0, 1e-5);
    ASSERT_NEAR(PointType(3, 142).Dist(boundary.GetDerivativeByArcLength<0>(boundary.GetLength())), 0, 1e-5);
    ASSERT_NEAR(PointType(0, 2).Dist(boundary.GetDerivativeByArcLength<1>(0)), 0, 1e-5);
    ASSERT_NEAR(PointType(3, 128).Dist(boundary.GetDerivativeByArcLength<1>(boundary.GetLength())), 0, 1e-5);
    ASSERT_NEAR(PointType(0, 6).Dist(boundary.GetDerivativeByArcLength<2>(0)), 0, 1e-5);
    ASSERT_NEAR(PointType(3, 78).Dist(boundary.GetDerivativeByArcLength<2>(boundary.GetLength())), 0, 1e-5);
}

TEST(LaneBoundaryPolynomial, GetSampleByArcLength)
{
    holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float64_t, 3U>> boundary(
        holo::numerics::Polynomial<holo::float64_t, 3U>({1, 2, 3, 4}), 0, 3);
    ASSERT_NEAR(PointType(0, 1).Dist(boundary.GetSampleByArcLength(0)), 0, 1e-5);
    ASSERT_NEAR(PointType(3, 142).Dist(boundary.GetSampleByArcLength(boundary.GetLength())), 0, 1e-5);
}

TEST(LaneBoundaryPolynomial, GetDerivativeByCoordinate)
{
    holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float64_t, 3U>> boundary(
        holo::numerics::Polynomial<holo::float64_t, 3U>({1, 2, 3, 4}), 0, 3);
    ASSERT_NEAR(PointType(0, 1).Dist(boundary.GetDerivativeByCoordinate<0>(0)), 0, 1e-5);
    ASSERT_NEAR(PointType(3, 142).Dist(boundary.GetDerivativeByCoordinate<0>(3)), 0, 1e-5);
    ASSERT_NEAR(PointType(0, 2).Dist(boundary.GetDerivativeByCoordinate<1>(0)), 0, 1e-5);
    ASSERT_NEAR(PointType(3, 128).Dist(boundary.GetDerivativeByCoordinate<1>(3)), 0, 1e-5);
    ASSERT_NEAR(PointType(0, 6).Dist(boundary.GetDerivativeByCoordinate<2>(0)), 0, 1e-5);
    ASSERT_NEAR(PointType(3, 78).Dist(boundary.GetDerivativeByCoordinate<2>(3)), 0, 1e-5);
}

TEST(LaneBoundaryPolynomial, GetSampleByCoordinate)
{
    holo::common::LaneBoundary<holo::numerics::Polynomial<holo::float64_t, 3U>> boundary(
        holo::numerics::Polynomial<holo::float64_t, 3U>({1, 2, 3, 4}), 0, 3);
    ASSERT_NEAR(PointType(0, 1).Dist(boundary.GetSampleByCoordinate(0)), 0, 1e-5);
    ASSERT_NEAR(PointType(3, 142).Dist(boundary.GetSampleByCoordinate(3)), 0, 1e-5);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

