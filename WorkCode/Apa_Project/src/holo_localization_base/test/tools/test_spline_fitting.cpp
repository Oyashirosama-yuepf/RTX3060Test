/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_pose_spline.cpp
 * @brief pose spline uint test
 * @author duyanwei@holomatic.com
 * @date April-08-2020
 */

#include <gtest/gtest.h>

#include <holo/localization/tools/spline_fitting.h>
#include <holo/localization/tools/impl/spline_fitting.hpp>

namespace holo
{
namespace localization
{
namespace spline_test
{
using Vector2d = holo::numerics::Vector2d;
using Vector6d = holo::numerics::Vector6d;
/**
 * @brief define ground truth data
 *
 */
struct GroundTruthData
{
    float64_t t;
    Vector2d  xy;
    Vector2d  vxy;
    Vector2d  axy;
    Vector2d  jxy;
};

/**
 * @brief generate ground truth data
 *
 * @param start
 * @param num
 * @param dt
 * @return std::vector<GroundTruthData>
 */
std::vector<GroundTruthData> GenerateDataset(const float64_t start, const uint32_t num, const float64_t dt)
{
    std::vector<GroundTruthData> results;

    /**
     * @brief define a 2d smooth curve
     * x(t) = a[0] + a[1]*t + a[2]*t^2 + a[3]*t3 + a[4]*t^4
     * y(t) = b[0] + b[1]*t + b[2]*t^2 + b[3]*t3 + b[4]*t^4
     */

    const std::vector<float64_t> a{1.0, 2.0, 3.0, 4.0, 5.0};
    const std::vector<float64_t> b{10.0, 80.0, 20.0, 90.0, 40.0};

    // create data
    float64_t t = start - dt;
    for (uint32_t i = 0u; i < num; i++)
    {
        t += dt;
        const float64_t t2 = t * t;
        const float64_t t3 = t2 * t;
        const float64_t t4 = t3 * t;

        GroundTruthData m;

        // t
        m.t = t;

        // x
        m.xy(0u)  = a[0] + a[1] * t + a[2] * t2 + a[3] * t3 + a[4] * t4;
        m.vxy(0u) = a[1] + 2.0 * a[2] * t + 3.0 * a[3] * t2 + 4.0 * a[4] * t3;
        m.axy(0u) = 2.0 * a[2] + 6.0 * a[3] * t + 12.0 * a[4] * t2;
        m.jxy(0u) = 6.0 * a[3] + 24.0 * a[4] * t;

        // y
        m.xy(1u)  = b[0] + b[1] * t + b[2] * t2 + b[3] * t3 + b[4] * t4;
        m.vxy(1u) = b[1] + 2.0 * b[2] * t + 3.0 * b[3] * t2 + 4.0 * b[4] * t3;
        m.axy(1u) = 2.0 * b[2] + 6.0 * b[3] * t + 12.0 * b[4] * t2;
        m.jxy(1u) = 6.0 * b[3] + 24.0 * b[4] * t;

        // create one piece of data
        results.emplace_back(m);
    }

    return results;
}

/**
 * @brief Create a Input From Ground Truth Data object
 *
 * @param data
 * @return std::tuple<std::vector<float64_t>, std::vector<Vector2d>>
 */
std::tuple<std::vector<float64_t>, std::vector<Vector2d>>
CreateInputFromGroundTruthData(const std::vector<GroundTruthData>& data)
{
    std::vector<float64_t> times;
    times.reserve(data.size());
    std::vector<Vector2d> xy;
    xy.reserve(data.size());

    for (const auto& val : data)
    {
        times.emplace_back(val.t);
        xy.emplace_back(val.xy);
    }
    return std::make_tuple(times, xy);
}

}  // namespace spline_test
}  // namespace localization
}  // namespace holo

using namespace holo::localization;
using namespace holo::localization::spline_test;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SplineFitting, Destructor)
{
    // s1. create ground truth
    const auto gt = spline_test::GenerateDataset(0.0, 1000u, 0.01);

    // s2. create input
    std::vector<holo::float64_t> times;
    std::vector<Vector2d>        data;
    std::tie(times, data) = spline_test::CreateInputFromGroundTruthData(gt);

    // s3. test destructor of SplineFittingT<2u, 5u>
    std::vector<Vector2d>         data2      = data;
    const SplineFittingT<2u, 5u>* spline_2_5 = new SplineFittingT<2u, 5u>(times, data2, 0.0, 50u);
    delete spline_2_5;

    // s4. test desctrctor of SplineFittingT<6u, 3u>
    std::vector<Vector6d> data6;
    data6.reserve(data.size());

    for (uint16_t i = 0; i < data.size(); i++)
    {
        Vector6d temp;
        temp.SetSegment(0u, data.at(i));
        temp.SetSegment(2u, data.at(i));
        temp.SetSegment(4u, data.at(i));
        data6.push_back(temp);
    }

    const SplineFittingT<6u, 3u>* spline_6_3 = new SplineFittingT<6u, 3u>(times, data6, 0.0, 50u);
    delete spline_6_3;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SplineFitting, NormalTest)
{
    // s1. create ground truth
    const auto gt = spline_test::GenerateDataset(0.0, 1000u, 0.01);

    // s2. create input
    std::vector<holo::float64_t> times;
    std::vector<Vector2d>        data;
    std::tie(times, data) = spline_test::CreateInputFromGroundTruthData(gt);

    // s3. create spline
    const SplineFittingT<2u, 5u> spline(times, data, 0.0, 50u);

    // check results
    for (uint32_t i = 0u; i < gt.size(); i++)
    {
        const auto& g = gt.at(i);

        // check value
        const Vector2d est_xy = spline.GetValue(g.t);
        ASSERT_TRUE((est_xy - g.xy).GetNorm() < 1e-5);

        // check 1st derivative
        const Vector2d est_vxy = spline.GetDerivation<1u>(g.t);
        ASSERT_TRUE((est_vxy - g.vxy).GetNorm() < 1e-5);

        // check 2nd derivative
        const Vector2d est_axy = spline.GetDerivation<2u>(g.t);
        ASSERT_TRUE((est_axy - g.axy).GetNorm() < 1e-5);

        // check 3rd derivative
        const Vector2d est_jxy = spline.GetDerivation<3u>(g.t);
        ASSERT_TRUE((est_jxy - g.jxy).GetNorm() < 2e-4);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SplineFitting, averageKnots)
{
    // s1. create ground truth
    const auto gt = spline_test::GenerateDataset(0.0, 1000u, 0.01);

    // s2. create input
    std::vector<holo::float64_t> times;
    std::vector<Vector2d>        data;
    std::tie(times, data) = spline_test::CreateInputFromGroundTruthData(gt);

    // s3. create spline
    const SplineFittingT<2u, 5u>* spline = new SplineFittingT<2u, 5u>(times, data, 0.0, times.size());

    // check results
    for (uint32_t i = 0u; i < gt.size(); i++)
    {
        const auto& g = gt.at(i);

        // check value
        const Vector2d est_xy = spline->GetValue(g.t);
        ASSERT_TRUE((est_xy - g.xy).GetNorm() < 1e-5);
    }

    delete spline;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SplineFitting, ConvertMatrix)
{
    holo::numerics::MatrixXd                           mat    = holo::numerics::MatrixXd::One(3u, 3u);
    holo::localization::spline_internal::EigenMatrixXd result = holo::localization::spline_internal::Convert(mat);

    // check results
    for (uint32_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint32_t j = 0u; j < mat.GetCols(); j++)
        {
            ASSERT_EQ(result(i, j), mat(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SplineFitting, Throw)
{
    std::vector<holo::float64_t> empty_times;
    std::vector<holo::float64_t> times({1.0});
    std::vector<Vector2d>        empty_data;

    // check results
    ///< case: times.size() < 2u
    ASSERT_THROW((SplineFittingT<2u, 5u>(empty_times, empty_data)), std::out_of_range);
    ///< case: times.size() != data.size()
    ASSERT_THROW((SplineFittingT<2u, 5u>(times, empty_data)), std::out_of_range);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
