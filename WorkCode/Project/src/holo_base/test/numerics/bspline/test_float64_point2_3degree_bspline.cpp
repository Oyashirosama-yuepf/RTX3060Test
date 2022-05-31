/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_float64_point2_3degree_bspline.cpp
 * @brief unit test for BSpline class
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-3-18
 */

#include <vector>

#include <holo/core/types.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/bspline.h>

using ScalarType = holo::float64_t;
using PointType = holo::geometry::Point2d;

static size_t const DegreeValue = 3;
static holo::bool_t const UniformValue = false;

#define SUITENAME BSPLINE_FLOAT64_POINT2_3DEGREE

class TestData
{
public:
    std::vector<ScalarType> knots;
    std::vector<PointType> control_points;
    std::pair<ScalarType, ScalarType> range;
    std::vector<ScalarType> param_list;
    std::vector<PointType> value_list;
    std::vector<PointType> first_derivation_list;
    std::vector<PointType> second_derivation_list;
};

std::vector<TestData> test_data = 
{
    {
        {0, 1, 2, 3, 4, 5, 6, 7}, //knots
        {{-4, -4}, {-2, 4}, {2, -4}, {4, 4}}, //control_points
        {3, 4}, //value range
        {3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0}, //sample points
        {
            { -1.66666667e+00,   1.33333333e+00},
            { -1.35733333e+00,   1.25866667e+00},
            { -1.03200000e+00,   1.05600000e+00},
            { -6.94666667e-01,   7.57333333e-01},
            { -3.49333333e-01,   3.94666667e-01},
            {  6.93889390e-17,   6.93889390e-17},
            {  3.49333333e-01,  -3.94666667e-01},
            {  6.94666667e-01,  -7.57333333e-01},
            {  1.03200000e+00,  -1.05600000e+00},
            {  1.35733333e+00,  -1.25866667e+00},
            {  1.66666667e+00,  -1.33333333e+00}
        }, // sample value
        {
            { 3.  ,  0.  },
            { 3.18, -1.44},
            { 3.32, -2.56},
            { 3.42, -3.36},
            { 3.48, -3.84},
            { 3.5 , -4.  },
            { 3.48, -3.84},
            { 3.42, -3.36},
            { 3.32, -2.56},
            { 3.18, -1.44},
            { 3.  ,  0.  }
        }, // sample value for first derivation
        {
            {  2. , -16. },
            {  1.6, -12.8},
            {  1.2,  -9.6},
            {  0.8,  -6.4},
            {  0.4,  -3.2},
            {  0. ,   0. },
            { -0.4,   3.2},
            { -0.8,   6.4},
            { -1.2,   9.6},
            { -1.6,  12.8},
            { -2. ,  16. }
        }, // sample value for second derivation
    },

    {
        {0, 0, 0, 0, 1, 1, 1, 1}, //knots
        {{-4, -4}, {-2, 4}, {2, -4}, {4, 4}}, //control_points
        {0, 1}, //value range
        {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0}, //sample points
        {
            {-4.   , -4.   },
            {-3.344, -2.048},
            {-2.592, -0.864},
            {-1.768, -0.256},
            {-0.896, -0.032},
            { 0.   ,  0.   },
            { 0.896,  0.032},
            { 1.768,  0.256},
            { 2.592,  0.864},
            { 3.344,  2.048},
            { 4.   ,  4.   }
        }, // sample value
        {
            {  6.  ,  24.  },
            {  7.08,  15.36},
            {  7.92,   8.64},
            {  8.52,   3.84},
            {  8.88,   0.96},
            {  9.  ,   0.  },
            {  8.88,   0.96},
            {  8.52,   3.84},
            {  7.92,   8.64},
            {  7.08,  15.36},
            {  6.  ,  24.  }
        }, // sample value for first derivation
        {
            { 12. , -96. },
            {  9.6, -76.8},
            {  7.2, -57.6},
            {  4.8, -38.4},
            {  2.4, -19.2},
            {  0. ,   0. },
            { -2.4,  19.2},
            { -4.8,  38.4},
            { -7.2,  57.6},
            { -9.6,  76.8},
            {-12. ,  96. }
        }, // sample value for second derivation
    },

    {
        {0, 0, 0, 0, 2, 2, 2, 2}, //knots
        {{-4, -4}, {-2, 4}, {2, -4}, {4, 4}}, //control_points
        {0, 2}, //value range
        {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0}, //sample points
        {
            {-4.   , -4.   },
            {-3.344, -2.048},
            {-2.592, -0.864},
            {-1.768, -0.256},
            {-0.896, -0.032},
            { 0.   ,  0.   },
            { 0.896,  0.032},
            { 1.768,  0.256},
            { 2.592,  0.864},
            { 3.344,  2.048},
            { 4.   ,  4.   }
        }, // sample value
        {
            {  3.  ,  12.  },
            {  3.54,   7.68},
            {  3.96,   4.32},
            {  4.26,   1.92},
            {  4.44,   0.48},
            {  4.5 ,   0.  },
            {  4.44,   0.48},
            {  4.26,   1.92},
            {  3.96,   4.32},
            {  3.54,   7.68},
            {  3.  ,  12.  }
        }, // sample value for first derivation
        {
            {  3. , -24. },
            {  2.4, -19.2},
            {  1.8, -14.4},
            {  1.2,  -9.6},
            {  0.6,  -4.8},
            {  0. ,   0. },
            { -0.6,   4.8},
            { -1.2,   9.6},
            { -1.8,  14.4},
            { -2.4,  19.2},
            { -3. ,  24. }
        }, // sample value for second derivation
    },
};

holo::bool_t Pred(PointType const& pt1, PointType const& pt2)
{
    return pt1.IsEqual(pt2, 1e-8);
}

#include "test_bspline.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

