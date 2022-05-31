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

#include <iostream>
#include <fstream>
#include <type_traits>

using ScalarType      = holo::float64_t;
using PointType       = holo::geometry::Point2T<ScalarType>;
using CurveBezier     = holo::geometry::CurveBezier<PointType>;
using CurvePolynomial = holo::geometry::CurvePolynomial<PointType>;

TEST(Curve, Shape2Points)
{
    CurveBezier     bezier = {{0, 0}, {2, 5}};
    CurvePolynomial poly   = bezier;
    bezier.Update();
    poly.Update();
}

TEST(Curve, Shape3Points)
{
    CurveBezier     bezier = {{0, 0}, {2, 5}, {6, 3}};
    CurvePolynomial poly   = bezier;
    bezier.Update();
    poly.Update();

    holo::container::VectorT<PointType, 257> bezier_samples;
    holo::container::VectorT<PointType, 257> poly_samples;

    size_t segments = 256;
    for (size_t i = 0; i <= 256; ++i)
    {
        PointType pt1;
        PointType pt2;
        PointType pt3;
        PointType dpt1;
        PointType dpt2;
        PointType dpt3;
        PointType ddpt1;
        PointType ddpt2;
        PointType ddpt3;

        ScalarType len1 = (1.0 / segments) * i * bezier.GetLength();
        ScalarType len2 = (1.0 / segments) * i * poly.GetLength();
        auto       r    = poly.GetCoordinateRange();
        ScalarType x    = (1.0 / segments) * i * (r.second - r.first);

        pt1 = bezier.GetDerivativeByArcLength<0>(len1);
        pt2 = poly.GetDerivativeByArcLength<0>(len2);
        pt3 = poly.GetDerivativeByCoordinate<0>(x);

        dpt1 = bezier.GetDerivativeByArcLength<1>(len1);
        dpt2 = poly.GetDerivativeByArcLength<1>(len2);
        dpt3 = poly.GetDerivativeByCoordinate<1>(x);

        ddpt1 = bezier.GetDerivativeByArcLength<2>(len1);
        ddpt2 = poly.GetDerivativeByArcLength<2>(len2);
        ddpt3 = poly.GetDerivativeByCoordinate<2>(x);
        bezier_samples.push_back(pt1);
        poly_samples.push_back(pt2);
    }

}

TEST(Curve, Shape4Points)
{
    CurveBezier     bezier = {{0, 0}, {2, 5}, {6, 3}, {11, 10}};
    CurvePolynomial poly   = bezier;
    bezier.Update();
    poly.Update();


    holo::container::VectorT<PointType, 257> bezier_samples;
    holo::container::VectorT<PointType, 257> poly_samples;

    size_t segments = 256;
    for (size_t i = 0; i <= 256; ++i)
    {
        PointType pt1;
        PointType pt2;
        PointType pt3;
        PointType dpt1;
        PointType dpt2;
        PointType dpt3;
        PointType ddpt1;
        PointType ddpt2;
        PointType ddpt3;

        ScalarType len1 = (1.0 / segments) * i * bezier.GetLength();
        ScalarType len2 = (1.0 / segments) * i * poly.GetLength();
        auto       r    = poly.GetCoordinateRange();
        ScalarType x    = (1.0 / segments) * i * (r.second - r.first);

        pt1 = bezier.GetDerivativeByArcLength<0>(len1);
        pt2 = poly.GetDerivativeByArcLength<0>(len2);
        pt3 = poly.GetDerivativeByCoordinate<0>(x);

        dpt1 = bezier.GetDerivativeByArcLength<1>(len1);
        dpt2 = poly.GetDerivativeByArcLength<1>(len2);
        dpt3 = poly.GetDerivativeByCoordinate<1>(x);

        ddpt1 = bezier.GetDerivativeByArcLength<2>(len1);
        ddpt2 = poly.GetDerivativeByArcLength<2>(len2);
        ddpt3 = poly.GetDerivativeByCoordinate<2>(x);
        bezier_samples.push_back(pt1);
        poly_samples.push_back(pt2);
    }

}

TEST(Curve, ShapeNPoints)
{
    holo::geometry::CurveBezier<PointType, 256U, 1U> bezier1d = {{0, 0}, {2, 1}, {6, 4}, {8, 3}, {12, 2}, {15, 0}};
    holo::geometry::CurveBezier<PointType, 256U, 3U> bezier3d = bezier1d;
    holo::geometry::CurvePolynomial<PointType, 256U, 3U> poly3d = bezier1d;
    bezier1d.Update();
    bezier3d.Update();
    poly3d.Update();

    size_t i = 0U;

    std::ofstream f("draw_curve.py");
    f << "#!/usr/bin/python" << std::endl;

    f << "knotx = [";
    for(i = 0; i < bezier1d.size() - 1; ++i)
    {
        f << bezier1d[i][0] << ", ";
    }
    f << bezier1d[i][0] << "]" << std::endl;

    f << "knoty = [";
    for(i = 0; i < bezier1d.size() - 1; ++i)
    {
        f << bezier1d[i][1] << ", ";
    }
    f << bezier1d[i][1] << "]" << std::endl;

    holo::container::VectorT<PointType, 257> bezier1d_samples;
    holo::container::VectorT<PointType, 257> bezier3d_samples;
    holo::container::VectorT<PointType, 257> poly3d_samples;

    size_t segments = 256;
    for (size_t i = 0; i <= 256; ++i)
    {
        PointType pt1;
        PointType pt2;
        PointType pt3;

        ScalarType len1 = (1.0 / segments) * i * bezier1d.GetLength();
        ScalarType len2 = (1.0 / segments) * i * bezier3d.GetLength();
        ScalarType len3 = (1.0 / segments) * i * poly3d.GetLength();

        pt1 = bezier1d.GetDerivativeByArcLength<0>(len1);
        pt2 = bezier3d.GetDerivativeByArcLength<0>(len2);
        pt3 = poly3d.GetDerivativeByArcLength<0>(len3);

        bezier1d_samples.push_back(pt1);
        bezier3d_samples.push_back(pt2);
        poly3d_samples.push_back(pt3);
    }

    f << "bezier1dx = [";
    for(i = 0; i < bezier1d_samples.size() - 1; ++i)
    {
        f << bezier1d_samples[i][0] << ", ";
    }
    f << bezier1d_samples[i][0] << "]" << std::endl;

    f << "bezier1dy = [";
    for(i = 0; i < bezier1d_samples.size() - 1; ++i)
    {
        f << bezier1d_samples[i][1] << ", ";
    }
    f << bezier1d_samples[i][1] << "]" << std::endl;

    f << "bezier3dx = [";
    for(i = 0; i < bezier3d_samples.size() - 1; ++i)
    {
        f << bezier3d_samples[i][0] << ", ";
    }
    f << bezier3d_samples[i][0] << "]" << std::endl;

    f << "bezier3dy = [";
    for(i = 0; i < bezier3d_samples.size() - 1; ++i)
    {
        f << bezier3d_samples[i][1] << ", ";
    }
    f << bezier3d_samples[i][1] << "]" << std::endl;

    f << "poly3dx = [";
    for(i = 0; i < poly3d_samples.size() - 1; ++i)
    {
        f << poly3d_samples[i][0] << ", ";
    }
    f << poly3d_samples[i][0] << "]" << std::endl;

    f << "poly3dy = [";
    for(i = 0; i < poly3d_samples.size() - 1; ++i)
    {
        f << poly3d_samples[i][1] << ", ";
    }
    f << poly3d_samples[i][1] << "]" << std::endl;
    f.close();
}

TEST(Curve, BezierNPoints)
{
    holo::geometry::CurveBezier<PointType, 256U, 1U> bezier1d = {{0, 0}, {3, 1}, {3, 3}, {1, 2}, {6, 0}};
    holo::geometry::CurveBezier<PointType, 256U, 3U> bezier3d = bezier1d;
    bezier1d.Update();
    bezier3d.Update();

    size_t i = 0U;

    std::ofstream f("draw_bezier_curve.py");
    f << "#!/usr/bin/python" << std::endl;

    f << "knotx = [";
    for(i = 0; i < bezier1d.size() - 1; ++i)
    {
        f << bezier1d[i][0] << ", ";
    }
    f << bezier1d[i][0] << "]" << std::endl;

    f << "knoty = [";
    for(i = 0; i < bezier1d.size() - 1; ++i)
    {
        f << bezier1d[i][1] << ", ";
    }
    f << bezier1d[i][1] << "]" << std::endl;

    holo::container::VectorT<PointType, 257> bezier1d_samples;
    holo::container::VectorT<PointType, 257> bezier3d_samples;

    size_t segments = 256;
    for (size_t i = 0; i <= 256; ++i)
    {
        PointType pt1;
        PointType pt2;

        ScalarType len1 = (1.0 / segments) * i * bezier1d.GetLength();
        ScalarType len2 = (1.0 / segments) * i * bezier3d.GetLength();

        pt1 = bezier1d.GetDerivativeByArcLength<0>(len1);
        pt2 = bezier3d.GetDerivativeByArcLength<0>(len2);

        bezier1d_samples.push_back(pt1);
        bezier3d_samples.push_back(pt2);
    }

    f << "bezier1dx = [";
    for(i = 0; i < bezier1d_samples.size() - 1; ++i)
    {
        f << bezier1d_samples[i][0] << ", ";
    }
    f << bezier1d_samples[i][0] << "]" << std::endl;

    f << "bezier1dy = [";
    for(i = 0; i < bezier1d_samples.size() - 1; ++i)
    {
        f << bezier1d_samples[i][1] << ", ";
    }
    f << bezier1d_samples[i][1] << "]" << std::endl;

    f << "bezier3dx = [";
    for(i = 0; i < bezier3d_samples.size() - 1; ++i)
    {
        f << bezier3d_samples[i][0] << ", ";
    }
    f << bezier3d_samples[i][0] << "]" << std::endl;

    f << "bezier3dy = [";
    for(i = 0; i < bezier3d_samples.size() - 1; ++i)
    {
        f << bezier3d_samples[i][1] << ", ";
    }
    f << bezier3d_samples[i][1] << "]" << std::endl;

    f.close();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
