/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_curve_polynomial.cpp
 * @brief This header file test CurvePolynomial objects.
 * @author ZhangJiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-18
 */

#include <gtest/gtest.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>

#include <iostream>
#include <type_traits>

using ScalarType = holo::float64_t;
using PointType  = holo::geometry::Point2T<ScalarType>;
template <size_t SIZE = 256U>
using CurveCubicPolynomialType = holo::geometry::CurvePolynomial<PointType, SIZE, 3U>;

template <size_t SIZE = 256U>
using CurveLinearPolynomialType = holo::geometry::CurvePolynomial<PointType, SIZE, 1U>;

TEST(CurveLinearPolynomial, GetLength)
{
    CurveLinearPolynomialType<> curve;
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}};
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}, {1, 0}, {2, 1}, {3, 1}};
    EXPECT_THROW(curve.GetLength(), holo::exception::BadCurveStateException);
    curve.Update();
    ASSERT_NEAR(static_cast<ScalarType>(3.414213562), curve.GetLength(), 1e-3);
}

TEST(CurveLinearPolynomial, GetSampleByArcLength)
{
    CurveLinearPolynomialType<> curve;
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}};
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}, {1, 0}, {2, 1}, {3, 1}};
    EXPECT_THROW(curve.GetSampleByArcLength(0), holo::exception::BadCurveStateException);
    curve.Update();
    ASSERT_NEAR((PointType{0, 0}).Dist(curve.GetSampleByArcLength(0)), 0, 1e-3);
    ASSERT_NEAR((PointType{0.5, 0}).Dist(curve.GetSampleByArcLength(0.5)), 0, 1e-3);
    ASSERT_NEAR((PointType{1, 0}).Dist(curve.GetSampleByArcLength(1)), 0, 1e-3);
    ASSERT_NEAR((PointType{1.5, 0.5}).Dist(curve.GetSampleByArcLength(1.707106781)), 0, 1e-3);
    ASSERT_NEAR((PointType{2, 1}).Dist(curve.GetSampleByArcLength(2.414213562)), 0, 1e-3);
    ASSERT_NEAR((PointType{2.5, 1}).Dist(curve.GetSampleByArcLength(2.914213562)), 0, 1e-3);
    ASSERT_NEAR((PointType{3, 1}).Dist(curve.GetSampleByArcLength(3.414213562)), 0, 1e-3);
}

TEST(CurveLinearPolynomial, GetSampleByArcLengthWithIteratorRange)
{
    PointType                   res[10]   = {};
    ScalarType                  lens[10]  = {0.0, 0.5, 1.0, 1.707106781, 2.414213562, 2.914213562, 3.414213562};
    ScalarType                  lens2[10] = {0.0, 1.0, 2.414213562, 3.414213562, 0.5, 1.707106781, 2.914213562};
    CurveLinearPolynomialType<> curve;
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}};
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}, {1, 0}, {2, 1}, {3, 1}};
    EXPECT_THROW(curve.GetSampleByArcLength(0), holo::exception::BadCurveStateException);
    curve.Update();
    PointType expected[10] = {{0, 0}, {0.5, 0}, {1, 0}, {1.5, 0.5}, {2, 1}, {2.5, 1}, {3, 1}};
    curve.GetSampleByArcLength(&lens[0], &lens[7], &res[0]);
    for (size_t i = 0; i < 7U; ++i)
    {
        ASSERT_NEAR(expected[i].Dist(res[i]), 0, 1e-3);
    }

    PointType expected2[10] = {{0, 0}, {1, 0}, {2, 1}, {3, 1}, {0.5, 0}, {1.5, 0.5}, {2.5, 1}};
    curve.GetSampleByArcLength(&lens2[0], &lens2[7], &res[0]);
    for (size_t i = 0; i < 7U; ++i)
    {
        ASSERT_NEAR(expected2[i].Dist(res[i]), 0, 1e-3);
    }
}

TEST(CurveLinearPolynomial, GetSampleByCoordinate)
{
    CurveLinearPolynomialType<> curve;
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}};
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}, {1, 0}, {2, 1}, {3, 1}};
    EXPECT_THROW(curve.GetSampleByCoordinate(0), holo::exception::BadCurveStateException);
    curve.Update();
    ASSERT_NEAR((PointType{0, 0}).Dist(curve.GetSampleByCoordinate(0)), 0, 1e-3);
    ASSERT_NEAR((PointType{0.5, 0}).Dist(curve.GetSampleByCoordinate(0.5)), 0, 1e-3);
    ASSERT_NEAR((PointType{1, 0}).Dist(curve.GetSampleByCoordinate(1)), 0, 1e-3);
    ASSERT_NEAR((PointType{1.5, 0.5}).Dist(curve.GetSampleByCoordinate(1.5)), 0, 1e-3);
    ASSERT_NEAR((PointType{2, 1}).Dist(curve.GetSampleByCoordinate(2)), 0, 1e-3);
    ASSERT_NEAR((PointType{2.5, 1}).Dist(curve.GetSampleByCoordinate(2.5)), 0, 1e-3);
    ASSERT_NEAR((PointType{3, 1}).Dist(curve.GetSampleByCoordinate(3)), 0, 1e-3);
}

TEST(CurveLinearPolynomial, GetSampleByCoordinateWithIteratorRange)
{
    PointType                   res[10]     = {};
    ScalarType                  coords[10]  = {0.0, 0.5, 1.0, 1.5, 2, 2.5, 3};
    ScalarType                  coords2[10] = {0.0, 1.0, 2, 3, 0.5, 1.5, 2.5};
    CurveLinearPolynomialType<> curve;
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}};
    EXPECT_THROW(curve.Update(), holo::exception::BadKnotNumberException);

    curve = {{0, 0}, {1, 0}, {2, 1}, {3, 1}};
    EXPECT_THROW(curve.GetSampleByCoordinate(0), holo::exception::BadCurveStateException);
    curve.Update();
    PointType expected[10] = {{0, 0}, {0.5, 0}, {1, 0}, {1.5, 0.5}, {2, 1}, {2.5, 1}, {3, 1}};
    curve.GetSampleByCoordinate(&coords[0], &coords[7], &res[0]);
    for (size_t i = 0; i < 7U; ++i)
    {
        ASSERT_NEAR(expected[i].Dist(res[i]), 0, 1e-3);
    }

    PointType expected2[10] = {{0, 0}, {1, 0}, {2, 1}, {3, 1}, {0.5, 0}, {1.5, 0.5}, {2.5, 1}};
    curve.GetSampleByCoordinate(&coords2[0], &coords2[7], &res[0]);
    for (size_t i = 0; i < 7U; ++i)
    {
        ASSERT_NEAR(expected2[i].Dist(res[i]), 0, 1e-3);
    }
}

TEST(CurveCubicPolynomial, BoundaryCondition2Points)
{
    // curve1 to curve4 are a cubic spline of 2 knots
    // Polynomial= 3x^3+2x^2+x+1
    CurveCubicPolynomialType<> curve1 = {{0, 1}, {3, 103}};
    CurveCubicPolynomialType<> curve2 = {{0, 1}, {3, 103}};
    CurveCubicPolynomialType<> curve3 = {{0, 1}, {3, 103}};
    CurveCubicPolynomialType<> curve4 = {{0, 1}, {3, 103}};
    
    // boundary conditions are first derivatives
    curve1.SetStartCondition(CurveCubicPolynomialType<>::ConditionType::FIRST_DERIVATIVE, {0, 1});
    curve1.SetEndCondition(CurveCubicPolynomialType<>::ConditionType::FIRST_DERIVATIVE, {3, 94});

    // boundary conditions are first derivative and second derivative
    curve2.SetStartCondition(CurveCubicPolynomialType<>::ConditionType::FIRST_DERIVATIVE, {0, 1});
    curve2.SetEndCondition(CurveCubicPolynomialType<>::ConditionType::SECOND_DERIVATIVE, {3, 58});

    // boundary conditions are second derivative and first derivative
    curve3.SetStartCondition(CurveCubicPolynomialType<>::ConditionType::SECOND_DERIVATIVE, {0, 4});
    curve3.SetEndCondition(CurveCubicPolynomialType<>::ConditionType::FIRST_DERIVATIVE, {3, 94});

    // boundary conditions are second derivatives
    curve4.SetStartCondition(CurveCubicPolynomialType<>::ConditionType::SECOND_DERIVATIVE, {0, 4});
    curve4.SetEndCondition(CurveCubicPolynomialType<>::ConditionType::SECOND_DERIVATIVE, {3, 58});

    curve1.Update();
    curve2.Update();
    curve3.Update();
    curve4.Update();

    auto range = curve1.GetCoordinateRange();
    for (size_t i = 0; i <= 64U; ++i)
    {
        ScalarType t = range.first + (1.0 / 64.0) * i * range.second;
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<0>(t).Dist(curve2.GetDerivativeByCoordinate<0>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<0>(t).Dist(curve3.GetDerivativeByCoordinate<0>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<0>(t).Dist(curve4.GetDerivativeByCoordinate<0>(t)), 0.0, 1e-5);

        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<1>(t).Dist(curve2.GetDerivativeByCoordinate<1>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<1>(t).Dist(curve3.GetDerivativeByCoordinate<1>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<1>(t).Dist(curve4.GetDerivativeByCoordinate<1>(t)), 0.0, 1e-5);

        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<2>(t).Dist(curve2.GetDerivativeByCoordinate<2>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<2>(t).Dist(curve3.GetDerivativeByCoordinate<2>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<2>(t).Dist(curve4.GetDerivativeByCoordinate<2>(t)), 0.0, 1e-5);
    }
}

TEST(CurveCubicPolynomial, BoundaryCondition3Points)
{
    // curve1 to curve4 are a cubic spline of 2 knots
    // Polynomial= 3x^3+2x^2+x+1
    CurveCubicPolynomialType<> curve1 = {{0, 1}, {3, 103}, {6, 673}};
    CurveCubicPolynomialType<> curve2 = {{0, 1}, {3, 103}, {6, 673}};
    CurveCubicPolynomialType<> curve3 = {{0, 1}, {3, 103}, {6, 673}};
    CurveCubicPolynomialType<> curve4 = {{0, 1}, {3, 103}, {6, 673}};
    
    // boundary conditions are first derivatives
    curve1.SetStartCondition(CurveCubicPolynomialType<>::ConditionType::FIRST_DERIVATIVE, {0, 1});
    curve1.SetEndCondition(CurveCubicPolynomialType<>::ConditionType::FIRST_DERIVATIVE, {6, 295});

    // boundary conditions are first derivative and second derivative
    curve2.SetStartCondition(CurveCubicPolynomialType<>::ConditionType::FIRST_DERIVATIVE, {0, 1});
    curve2.SetEndCondition(CurveCubicPolynomialType<>::ConditionType::SECOND_DERIVATIVE, {6, 76});

    // boundary conditions are second derivative and first derivative
    curve3.SetStartCondition(CurveCubicPolynomialType<>::ConditionType::SECOND_DERIVATIVE, {0, 4});
    curve3.SetEndCondition(CurveCubicPolynomialType<>::ConditionType::FIRST_DERIVATIVE, {6, 295});

    // boundary conditions are second derivatives
    curve4.SetStartCondition(CurveCubicPolynomialType<>::ConditionType::SECOND_DERIVATIVE, {0, 4});
    curve4.SetEndCondition(CurveCubicPolynomialType<>::ConditionType::SECOND_DERIVATIVE, {6, 76});

    curve1.Update();
    curve2.Update();
    curve3.Update();
    curve4.Update();

    auto range = curve1.GetCoordinateRange();
    for (size_t i = 0; i <= 64U; ++i)
    {
        ScalarType t = range.first + (1.0 / 64.0) * i * range.second;
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<0>(t).Dist(curve2.GetDerivativeByCoordinate<0>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<0>(t).Dist(curve3.GetDerivativeByCoordinate<0>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<0>(t).Dist(curve4.GetDerivativeByCoordinate<0>(t)), 0.0, 1e-5);

        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<1>(t).Dist(curve2.GetDerivativeByCoordinate<1>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<1>(t).Dist(curve3.GetDerivativeByCoordinate<1>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<1>(t).Dist(curve4.GetDerivativeByCoordinate<1>(t)), 0.0, 1e-5);

        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<2>(t).Dist(curve2.GetDerivativeByCoordinate<2>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<2>(t).Dist(curve3.GetDerivativeByCoordinate<2>(t)), 0.0, 1e-5);
        ASSERT_NEAR(curve1.GetDerivativeByCoordinate<2>(t).Dist(curve4.GetDerivativeByCoordinate<2>(t)), 0.0, 1e-5);
    }
}

TEST(CurveCubicPolynomial, BadControlPointNumberException)
{
    try
    {
        throw holo::exception::BadControlPointNumberException();
    }
    catch(...)
    {
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
