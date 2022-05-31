/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_bspline.h
 * @brief unit test for BSpline classes
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-3-18
 */

/*
 * The following types must be defined
 * - ScalarType
 * - PointType
 *
 * The following values must be defined
 * - size_t DegreeValue
 * - bool_t UniformValue
 *
 * The following macros must be defined
 * - SUITENAME
 *
 * The following test data must be defined
 * class TestData
 * {
 * public:
 *     std::vector<ScalarType> knots;
 *     std::vector<PointType> control_points;
 *     std::pair<ScalarType, ScalarType> range;
 *     std::vector<ScalarType> param_list;
 *     std::vector<PointType> value_list;
 *     std::vector<PointType> first_derivation_list;
 *     std::vector<PointType> second_derivation_list;
 * };
 *
 * - std::vector<TestData> test_data;
 *
 * The following functions must be defined
 * - bool_t Pred(PointType pt1, PointType pt2); // judge if pt1 == pt2
 *
 */

#include <gtest/gtest.h>

using BSplineType = holo::numerics::BSpline<ScalarType, PointType, DegreeValue, UniformValue>;

TEST(SUITENAME, Constructor)
{
    BSplineType spline({0,0,0,0,1,1,1,1}, std::vector<PointType>(4, PointType{}));
    ASSERT_EQ(8u, spline.GetKnots().size());
    ASSERT_EQ(4u, spline.GetControlPoints().size());
}

TEST(SUITENAME, SetGetKnots)
{
    BSplineType spline({0,0,0,0,1,1,1,1}, std::vector<PointType>(4, PointType{}));

    spline.SetKnots({0,1,2,3,4,5,6,7});
    ASSERT_EQ((std::vector<ScalarType>{0,1,2,3,4,5,6,7}), spline.GetKnots());
}

TEST(SUITENAME, SetGetControlPoints)
{
    BSplineType spline({0,0,0,0,1,1,1,1}, std::vector<PointType>(4, PointType{}));
    spline.SetControlPoints({{},{},{},{}});
    ASSERT_EQ((std::vector<PointType>(4, PointType{})), spline.GetControlPoints());
}

TEST(SUITENAME, TestData)
{
    for(auto const& data: test_data)
    {
        BSplineType spline(data.knots, data.control_points);
        auto range = spline.GetParamRange();
        ASSERT_NEAR(data.range.first, range.first, holo::EpsilonT<ScalarType>::value);
        ASSERT_NEAR(data.range.second, range.second, holo::EpsilonT<ScalarType>::value);
        for(size_t i = 0; i < data.param_list.size(); ++i)
        {
            ASSERT_TRUE(Pred(data.value_list[i], spline.GetValue(data.param_list[i])));
            ASSERT_TRUE(Pred(data.value_list[i], spline.GetDerivation<0>(data.param_list[i])));
            ASSERT_TRUE(Pred(data.first_derivation_list[i], spline.GetDerivation<1>(data.param_list[i])));
            ASSERT_TRUE(Pred(data.second_derivation_list[i], spline.GetDerivation<2>(data.param_list[i])));
        }
    }
}


