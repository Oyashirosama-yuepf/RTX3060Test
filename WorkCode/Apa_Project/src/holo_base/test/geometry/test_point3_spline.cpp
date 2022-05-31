/*!
 * @file test_spline.cpp
 * @brief Unit test for spline
 * @author duyanwei@holomatic.com
 * @date 2019-09-28
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <random>

#include <gtest/gtest.h>

#include <holo/geometry/point3_spline.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Spline, Constructor)
{
    /**
     * @brief typedefs
     *
     */
    using Scalar     = holo::float64_t;
    using SplineType = holo::Point3Spline;
    using Point3Type = holo::geometry::Point3T<Scalar>;

    /**
     * define a 3d smooth curve
     * x(t) = 2*t^2 + 3;
     * y(t) = 3*t^3 + 1.5*t^2 + 0.1;
     * z(t) = t;
     */
    const uint8_t                               num = 100u;
    std::vector<std::pair<Scalar, Point3Type> > data;
    data.reserve(num);
    for (uint8_t i = 0u; i < 100u; ++i)
    {
        const Scalar t = (Scalar)i / num;
        const Scalar x = (Scalar)2.0 * t * t + (Scalar)3.0;
        const Scalar y = (Scalar)3.0 * t * t * t + (Scalar)1.5 * t * t + (Scalar)0.1;
        const Scalar z = t;
        data.emplace_back(t, Point3Type(x, y, z));
    }

    // create spline
    const SplineType spline(data);

    // call interpolate and check results
    for (uint8_t i = 0u; i < 100u; ++i)
    {
        const Scalar     t      = (Scalar)i / num;
        const Point3Type actual = spline.Interpolate(t);
        const Point3Type expected(data.at(i).second);
        ASSERT_TRUE(expected == actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Spline, ConstructorWithOffset)
{
    /**
     * @brief typedefs
     *
     */
    using Scalar     = holo::float64_t;
    using SplineType = holo::Point3Spline;
    using Point3Type = holo::geometry::Point3T<Scalar>;

    /**
     * define a 3d smooth curve
     * x(t) = 2*t^2 + 3;
     * y(t) = 3*t^3 + 1.5*t^2 + 0.1;
     * z(t) = t;
     */
    const uint8_t                               num = 100u;
    std::vector<std::pair<Scalar, Point3Type> > data;
    data.reserve(num);
    for (uint8_t i = 0u; i < 100u; ++i)
    {
        const Scalar t = (Scalar)i / num;
        const Scalar x = (Scalar)2.0 * t * t + (Scalar)3.0;
        const Scalar y = (Scalar)3.0 * t * t * t + (Scalar)1.5 * t * t + (Scalar)0.1;
        const Scalar z = t;
        data.emplace_back(t, Point3Type(x, y, z));
    }

    // create spline
    const Point3Type offset(data.at(0u).second.GetX(), data.at(1u).second.GetY(), data.at(2u).second.GetZ());
    const SplineType spline(data, offset);

    // call interpolate and check results
    for (uint8_t i = 0u; i < 100u; ++i)
    {
        const Scalar     t             = (Scalar)i / num;
        const Point3Type global_actual = spline.Interpolate(t, false);
        const Point3Type local_actual  = spline.Interpolate(t, true);
        const Point3Type global_expected(data.at(i).second);
        const Point3Type local_expected(global_expected - offset);
        ASSERT_TRUE(global_expected == global_actual);
        ASSERT_TRUE(local_expected == local_actual);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Spline, SmoothingSpline)
{
    /**
     * @brief typedefs
     *
     */
    using Scalar     = holo::float64_t;
    using SplineType = holo::Point3Spline;
    using Point3Type = holo::geometry::Point3T<Scalar>;

    // Define random generator with Gaussian distribution
    const Scalar                     mean   = static_cast<Scalar>(0.0);
    const Scalar                     stddev = static_cast<Scalar>(1.0);
    std::default_random_engine       generator;
    std::normal_distribution<Scalar> dist(mean, stddev);

    /**
     * define a 3d smooth curve
     * x(t) = 2*t^2 + 3;
     * y(t) = 3*t^3 + 1.5*t^2 + 0.1;
     * z(t) = 0;
     */
    const uint8_t                               num = 100u;
    std::vector<std::pair<Scalar, Point3Type> > data;
    data.reserve(num);
    std::vector<Point3Type> gts;
    for (uint8_t i = 0u; i < 100u; ++i)
    {
        const Scalar t = (Scalar)i / num;
        const Scalar x = (Scalar)2.0 * t * t + (Scalar)3.0;
        const Scalar y = (Scalar)3.0 * t * t * t + (Scalar)1.5 * t * t + (Scalar)0.1;
        const Scalar z = (Scalar)0.0;

        gts.emplace_back(x, y, z);

        // @todo timestamp value should be "t" while not "i", i does NOT make sense here
        data.emplace_back(i, Point3Type(x, y, z));

        // add noise to x and y value
        data.at(i).second += Point3Type(dist(generator), dist(generator), 0.0);
    }

    // create offset
    const Point3Type offset = Point3Type::Zero();

    // create spline
    const SplineType spline1(data, offset);
    const SplineType spline2(data, offset, static_cast<Scalar>(0.2));
    const SplineType spline3(data, offset, static_cast<Scalar>(0.8));

    std::vector<Scalar> terrors;
    std::vector<Scalar> st2errors;
    std::vector<Scalar> st8errors;

    for (uint8_t i = 0u; i < num; ++i)
    {
        const Scalar     time    = data.at(i).first;
        const Point3Type actual1 = spline1.Interpolate(time);
        const Point3Type actual2 = spline2.Interpolate(time);
        const Point3Type actual3 = spline3.Interpolate(time);

        {
            // error
            terrors.emplace_back(gts.at(i).Dist(actual1));
            st2errors.emplace_back(gts.at(i).Dist(actual2));
            st8errors.emplace_back(gts.at(i).Dist(actual3));
        }
    }

    const Scalar tmax   = *std::max_element(terrors.begin(), terrors.end());
    const Scalar st2max = *std::max_element(st2errors.begin(), st2errors.end());
    const Scalar st8max = *std::max_element(st8errors.begin(), st8errors.end());

    // check results
    ASSERT_LT(st2max, tmax);
    ASSERT_LT(st8max, st2max);
}


TEST(Spline, Operator)
{
    using Scalar     = holo::float64_t;
    using SplineType = holo::Point3Spline;
    using Point3Type = holo::geometry::Point3T<Scalar>;

    const uint8_t                               num = 100u;
    std::vector<std::pair<Scalar, Point3Type> > data;
    data.reserve(num);
    for (uint8_t i = 0u; i < 100u; ++i)
    {
        const Scalar t = (Scalar)i / num;
        const Scalar x = (Scalar)2.0 * t * t + (Scalar)3.0;
        const Scalar y = (Scalar)3.0 * t * t * t + (Scalar)1.5 * t * t + (Scalar)0.1;
        const Scalar z = t;
        data.emplace_back(t, Point3Type(x, y, z));
    }

    const Point3Type offset = Point3Type::Zero();
    const SplineType spline1(data, offset);
    spline1(0, false);
}

TEST(Spline, ConstructorWithOffset_2)
{
    using Scalar     = holo::float64_t;
    using SplineType = holo::Point3Spline;
    using Point3Type = holo::geometry::Point3T<Scalar>;

    const uint8_t                               num = 100u;
    std::vector<std::pair<Scalar, Point3Type> > data;

    // create spline
    const Point3Type offset;
    try
    {
        const SplineType spline(data, offset);
    }
    catch(...)
    {
    }

    try
    {
            const SplineType spline2(data, offset, static_cast<Scalar>(0.2));
    }
    catch(...)
    {
    } 
}

TEST(Spline, Interpolate)
{
    using Scalar     = holo::float64_t;
    using SplineType = holo::Point3Spline;
    using Point3Type = holo::geometry::Point3T<Scalar>;

    const uint8_t                               num = 100u;
    std::vector<std::pair<Scalar, Point3Type> > data;
    data.reserve(num);
    for (uint8_t i = 3u; i < 10u; ++i)
    {
        const Scalar t = i-3;
        const Scalar x = i;
        const Scalar y = i;
        const Scalar z = i;
        data.emplace_back(t, Point3Type(x, y, z));
    }

    const Point3Type offset(data.at(0u).second.GetX(), data.at(1u).second.GetY(), data.at(2u).second.GetZ());
    const SplineType spline(data, offset);

    try
    {
        spline.Interpolate(7, false);
    }
    catch(...)
    {
    } 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
