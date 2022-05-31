/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_curve_bezier.cpp
 * @brief This header file test CurveBezier objects.
 * @author ZhangJiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-18
 */

#include <gtest/gtest.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>

#include <type_traits>
#include <iostream>

using ScalarType = holo::float64_t;
using PointType  = holo::geometry::Point2T<ScalarType>;
template <size_t SIZE = 256U>
using CurveCubicBezierType =
    holo::geometry::CurveBezier<PointType, SIZE, 3U>;

template <size_t SIZE = 256U>
using CurveLinearBezierType =
    holo::geometry::CurveBezier<PointType, SIZE, 1U>;

TEST(CurveLinearBezier, GetLength)
{
    CurveLinearBezierType<> curve;

    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}};
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}, {0, 0}};
    EXPECT_THROW(curve.GetLength(), holo::exception::BadCurveStateException);
    curve.Update();
    ASSERT_NEAR(static_cast<ScalarType>(0), curve.GetLength(), 1e-3);
    EXPECT_THROW(curve.GetLength(2), holo::exception::OutOfRangeException);

    curve = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    EXPECT_THROW(curve.GetLength(), holo::exception::BadCurveStateException);
    curve.Update();
    ASSERT_NEAR(static_cast<ScalarType>(3), curve.GetLength(), 1e-3);

    
}

TEST(CurveLinearBezier, GetSampleByArcLength)
{
    CurveLinearBezierType<> curve;
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}};
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}, {0, 0}};
    EXPECT_THROW(curve.GetSampleByArcLength(0), holo::exception::BadCurveStateException);
    curve.Update();
    ASSERT_NEAR((PointType{0, 0}).Dist(curve.GetSampleByArcLength(0)), 0, 1e-3);
    EXPECT_THROW(curve.GetSampleByArcLength(1), holo::exception::OutOfRangeException);

    curve = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    EXPECT_THROW(curve.GetSampleByArcLength(0), holo::exception::BadCurveStateException);
    curve.Update();
    ASSERT_NEAR((PointType{0, 0}).Dist(curve.GetSampleByArcLength(0)), 0, 1e-3);
    ASSERT_NEAR((PointType{0.5, 0}).Dist(curve.GetSampleByArcLength(0.5)), 0, 1e-3);
    ASSERT_NEAR((PointType{1, 0}).Dist(curve.GetSampleByArcLength(1)), 0, 1e-3);
    ASSERT_NEAR((PointType{1, 0.5}).Dist(curve.GetSampleByArcLength(1.5)), 0, 1e-3);
    ASSERT_NEAR((PointType{1, 1}).Dist(curve.GetSampleByArcLength(2)), 0, 1e-3);
    ASSERT_NEAR((PointType{1.5, 1}).Dist(curve.GetSampleByArcLength(2.5)), 0, 1e-3);
    ASSERT_NEAR((PointType{2, 1}).Dist(curve.GetSampleByArcLength(3)), 0, 1e-3);
}

TEST(CurveLinearBezier, GetSampleByArcLengthWithIteratorRange)
{
    PointType                        res[10]   = {};
    ScalarType                       lens[10]  = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
    ScalarType                       lens2[10] = {0.0, 1.0, 2.0, 3.0, 0.5, 1.5, 2.5};
    CurveLinearBezierType<> curve;
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}};
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}, {0, 0}};
    EXPECT_THROW(curve.GetSampleByArcLength(0), holo::exception::BadCurveStateException);
    curve.Update();
    curve.GetSampleByArcLength(&lens[1], &lens[1], &res[0]);
    ASSERT_EQ((PointType{0, 0}), res[0]);
    curve.GetSampleByArcLength(&lens[0], &lens[1], &res[0]);
    ASSERT_EQ((PointType{0, 0}), res[0]);
    EXPECT_THROW(curve.GetSampleByArcLength(&lens[0], &lens[2], &res[0]), holo::exception::OutOfRangeException);

    curve = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    EXPECT_THROW(curve.GetSampleByArcLength(0), holo::exception::BadCurveStateException);
    curve.Update();
    PointType expected[10] = {{0, 0}, {0.5, 0}, {1, 0}, {1, 0.5}, {1, 1}, {1.5, 1}, {2, 1}};
    curve.GetSampleByArcLength(&lens[0], &lens[7], &res[0]);
    for (size_t i = 0; i < 7U; ++i)
    {
        ASSERT_NEAR(expected[i].Dist(res[i]), 0, 1e-3);
    }

    PointType expected2[10] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {0.5, 0}, {1, 0.5}, {1.5, 1}};
    curve.GetSampleByArcLength(&lens2[0], &lens2[7], &res[0]);
    for (size_t i = 0; i < 7U; ++i)
    {
        ASSERT_NEAR(expected2[i].Dist(res[i]), 0, 1e-3);
    }
}

TEST(CurveCubicBezier, GetLength)
{
    CurveCubicBezierType<> curve;
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}};
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}, {0, 0}};
    EXPECT_THROW(curve.GetLength(), holo::exception::BadCurveStateException);
    curve.Update();
    ASSERT_NEAR(static_cast<ScalarType>(0), curve.GetLength(), 1e-5);

    curve = {{0, 0}, {3, 0}};
    curve.Update();
    ASSERT_NEAR(static_cast<ScalarType>(3), curve.GetLength(), 1e-5);
    EXPECT_THROW(curve.GetLength(2), holo::exception::OutOfRangeException);

    curve = {{0, 0}, {3, 0}, {6, 0}};
    curve.Update();
    ASSERT_NEAR(static_cast<ScalarType>(6), curve.GetLength(), 1e-5);

    curve = {{0, 0}, {3, 0}, {6, 0}, {9, 0}};
    curve.Update();
    ASSERT_NEAR(static_cast<ScalarType>(9), curve.GetLength(), 1e-5);
}

TEST(CurveCubicBezier, GetSampleByArcLength)
{
    CurveCubicBezierType<> curve = {{0,0}, {0,0}};
    EXPECT_THROW(curve.GetSampleByArcLength(0), holo::exception::BadCurveStateException);
    curve.Update();
    ASSERT_NEAR((PointType{0, 0}).Dist(curve.GetSampleByArcLength(0)), 0, 1e-3);
    EXPECT_THROW(curve.GetSampleByArcLength(1), holo::exception::OutOfRangeException);

    curve = {{0,0}, {3,0}};
    EXPECT_THROW(curve.GetSampleByArcLength(0), holo::exception::BadCurveStateException);
    curve.Update();
    ASSERT_NEAR((PointType{0, 0}).Dist(curve.GetSampleByArcLength(0)), 0, 1e-3);
    ASSERT_NEAR((PointType{1, 0}).Dist(curve.GetSampleByArcLength(1)), 0, 1e-3);
    ASSERT_NEAR((PointType{2, 0}).Dist(curve.GetSampleByArcLength(2)), 0, 1e-3);
    ASSERT_NEAR((PointType{3, 0}).Dist(curve.GetSampleByArcLength(3)), 0, 1e-3);
    EXPECT_THROW(curve.GetSampleByArcLength(3.1), holo::exception::OutOfRangeException);
}

TEST(CurveCubicBezier, BoundaryCondition2Points)
{
    // curve1 to curve4 are a bezier spline of 2 knots {0, 0} and {1, 0}
    // control points: {0, 1} and {1, 1}
    CurveCubicBezierType<> curve1 = {{0, 0}, {1, 0}};
    CurveCubicBezierType<> curve2 = {{0, 0}, {1, 0}};
    CurveCubicBezierType<> curve3 = {{0, 0}, {1, 0}};
    CurveCubicBezierType<> curve4 = {{0, 0}, {1, 0}};
    
    // boundary conditions are first derivatives
    curve1.SetStartCondition(CurveCubicBezierType<>::ConditionType::FIRST_DERIVATIVE, {0, 3});
    curve1.SetEndCondition(CurveCubicBezierType<>::ConditionType::FIRST_DERIVATIVE, {0, -3});

    // boundary conditions are first derivative and second derivative
    curve2.SetStartCondition(CurveCubicBezierType<>::ConditionType::FIRST_DERIVATIVE, {0, 3});
    curve2.SetEndCondition(CurveCubicBezierType<>::ConditionType::SECOND_DERIVATIVE, {-6, -6});

    // boundary conditions are second derivative and first derivative
    curve3.SetStartCondition(CurveCubicBezierType<>::ConditionType::SECOND_DERIVATIVE, {6, -6});
    curve3.SetEndCondition(CurveCubicBezierType<>::ConditionType::FIRST_DERIVATIVE, {0, -3});

    // boundary conditions are second derivatives
    curve4.SetStartCondition(CurveCubicBezierType<>::ConditionType::SECOND_DERIVATIVE, {6, -6});
    curve4.SetEndCondition(CurveCubicBezierType<>::ConditionType::SECOND_DERIVATIVE, {-6, -6});

    curve1.Update();
    curve2.Update();
    curve3.Update();
    curve4.Update();

    auto len = curve1.GetLength();
    for (size_t i = 0; i <= 64U; ++i)
    {
        ScalarType t = (1.0 / 64.0) * i * len;
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<0>(t).Dist(curve2.GetDerivativeByArcLength<0>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<0>(t).Dist(curve3.GetDerivativeByArcLength<0>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<0>(t).Dist(curve4.GetDerivativeByArcLength<0>(t)), 0.0, 1e-5);

        ASSERT_NEAR(curve1.GetDerivativeByArcLength<1>(t).Dist(curve2.GetDerivativeByArcLength<1>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<1>(t).Dist(curve3.GetDerivativeByArcLength<1>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<1>(t).Dist(curve4.GetDerivativeByArcLength<1>(t)), 0.0, 1e-5);

        ASSERT_NEAR(curve1.GetDerivativeByArcLength<2>(t).Dist(curve2.GetDerivativeByArcLength<2>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<2>(t).Dist(curve3.GetDerivativeByArcLength<2>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<2>(t).Dist(curve4.GetDerivativeByArcLength<2>(t)), 0.0, 1e-5);
    }
}

TEST(CurveCubicBezier, BoundaryCondition3Points)
{
    // curve1 to curve4 are a bezier spline of 3 knots {0, 0} {1, 0} and {2, 0}
    // control points: {0, 1} {1/2, 1/2} and {3/2, -1/2} , {2, -1}
    CurveCubicBezierType<> curve1 = {{0, 0}, {1, 0}, {2, 0}};
    CurveCubicBezierType<> curve2 = {{0, 0}, {1, 0}, {2, 0}};
    CurveCubicBezierType<> curve3 = {{0, 0}, {1, 0}, {2, 0}};
    CurveCubicBezierType<> curve4 = {{0, 0}, {1, 0}, {2, 0}};
    
    // boundary conditions are first derivatives
    curve1.SetStartCondition(CurveCubicBezierType<>::ConditionType::FIRST_DERIVATIVE, {0, 3});
    curve1.SetEndCondition(CurveCubicBezierType<>::ConditionType::FIRST_DERIVATIVE, {0, 3});

    // boundary conditions are first derivative and second derivative
    curve2.SetStartCondition(CurveCubicBezierType<>::ConditionType::FIRST_DERIVATIVE, {0, 3});
    curve2.SetEndCondition(CurveCubicBezierType<>::ConditionType::SECOND_DERIVATIVE, {-3, 9});

    // boundary conditions are second derivative and first derivative
    curve3.SetStartCondition(CurveCubicBezierType<>::ConditionType::SECOND_DERIVATIVE, {3, -9});
    curve3.SetEndCondition(CurveCubicBezierType<>::ConditionType::FIRST_DERIVATIVE, {0, 3});

    // boundary conditions are second derivatives
    curve4.SetStartCondition(CurveCubicBezierType<>::ConditionType::SECOND_DERIVATIVE, {3, -9});
    curve4.SetEndCondition(CurveCubicBezierType<>::ConditionType::SECOND_DERIVATIVE, {-3, 9});

    curve1.Update();
    curve2.Update();
    curve3.Update();
    curve4.Update();

    auto len = curve1.GetLength();

    for (size_t i = 0; i <= 64U; ++i)
    {
        ScalarType t = (1.0 / 64.0) * i * len;
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<0>(t).Dist(curve2.GetDerivativeByArcLength<0>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<0>(t).Dist(curve3.GetDerivativeByArcLength<0>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<0>(t).Dist(curve4.GetDerivativeByArcLength<0>(t)), 0.0, 1e-5);

        ASSERT_NEAR(curve1.GetDerivativeByArcLength<1>(t).Dist(curve2.GetDerivativeByArcLength<1>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<1>(t).Dist(curve3.GetDerivativeByArcLength<1>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<1>(t).Dist(curve4.GetDerivativeByArcLength<1>(t)), 0.0, 1e-5);

        ASSERT_NEAR(curve1.GetDerivativeByArcLength<2>(t).Dist(curve2.GetDerivativeByArcLength<2>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<2>(t).Dist(curve3.GetDerivativeByArcLength<2>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByArcLength<2>(t).Dist(curve4.GetDerivativeByArcLength<2>(t)), 0.0, 1e-5);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

