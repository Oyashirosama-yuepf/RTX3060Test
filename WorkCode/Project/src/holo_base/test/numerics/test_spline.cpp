/*!
 * @file test_spline.cpp
 * @brief Unit test for spline
 * @author duyanwei@holomatic.com
 * @date 2019-12-06
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <random>

#include <gtest/gtest.h>

#include <holo/numerics/spline.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Spline, DIM_3)
{
    /**
     * @brief typedefs
     *
     */
    using Scalar      = holo::float64_t;
    using MatrixXType = holo::numerics::MatrixXT<Scalar>;
    using VectorXType = holo::numerics::VectorXT<Scalar>;
    using SplineType  = holo::Spline3;

    /**
     * define a 3d smooth curve
     * x(t) = 2*t^2 + 3;
     * y(t) = 3*t^3 + 1.5*t^2 + 0.1;
     * z(t) = t;
     */
    const uint8_t num = 100u;
    MatrixXType   data(num, 3u);
    MatrixXType   first_derivatives(num, 3u);
    MatrixXType   second_derivatives(num, 3u);
    VectorXType   knots(num);
    for (uint8_t i = 0u; i < 100u; ++i)
    {
        const Scalar t = (Scalar)i / num;
        knots(i)       = t;
        data(i, 0u)    = (Scalar)2.0 * t * t + (Scalar)3.0;
        data(i, 1u)    = (Scalar)3.0 * t * t * t + (Scalar)1.5 * t * t + (Scalar)0.1;
        data(i, 2u)    = t;

        first_derivatives(i, 0u) = (Scalar)4.0 * t;
        first_derivatives(i, 1u) = (Scalar)9.0 * t * t + (Scalar)3.0 * t;
        first_derivatives(i, 2u) = (Scalar)1.0;

        second_derivatives(i, 0u) = (Scalar)4.0;
        second_derivatives(i, 1u) = (Scalar)18.0 * t + (Scalar)3.0;
        second_derivatives(i, 2u) = (Scalar)0.0;
    }

    // create spline
    const uint8_t    degree = 3u;
    const SplineType spline(data, degree, knots);

    // call interpolate and check results
    for (uint8_t i = 1u; i < num; ++i)
    {
        const Scalar      t      = (Scalar)i / num;
        const VectorXType actual = spline.Interpolate(t);
        ASSERT_NEAR(data(i, 0u), actual(0u), 1e-7);
        ASSERT_NEAR(data(i, 1u), actual(1u), 1e-7);
        ASSERT_NEAR(data(i, 2u), actual(2u), 1e-7);

        const MatrixXType actual_1 = spline.Derivatives(t, 1u);
        ASSERT_NEAR(first_derivatives(i, 0u), actual_1(0u, 1u), 1e-7);
        ASSERT_NEAR(first_derivatives(i, 1u), actual_1(1u, 1u), 1e-7);
        ASSERT_NEAR(first_derivatives(i, 2u), actual_1(2u, 1u), 1e-7);

        const MatrixXType actual_2 = spline.Derivatives(t, 2u);
        ASSERT_NEAR(second_derivatives(i, 0u), actual_2(0u, 2u), 1e-7);
        ASSERT_NEAR(second_derivatives(i, 1u), actual_2(1u, 2u), 1e-7);
        ASSERT_NEAR(second_derivatives(i, 2u), actual_2(2u, 2u), 1e-7);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Spline, DIM_2)
{
    /**
     * @brief typedefs
     *
     */
    using Scalar      = holo::float64_t;
    using MatrixXType = holo::numerics::MatrixXT<Scalar>;
    using VectorXType = holo::numerics::VectorXT<Scalar>;
    using SplineType  = holo::Spline2;

    /**
     * define a 3d smooth curve
     * x(t) = 2*t^2 + 3;
     * y(t) = 3*t^3 + 1.5*t^2 + 0.1;
     * z(t) = t;
     */
    const uint8_t num = 100u;
    MatrixXType   data(num, 2u);
    MatrixXType   first_derivatives(num, 2u);
    MatrixXType   second_derivatives(num, 2u);
    VectorXType   knots(num);
    for (uint8_t i = 0u; i < 100u; ++i)
    {
        const Scalar t = (Scalar)i / num;
        knots(i)       = t;
        data(i, 0u)    = (Scalar)2.0 * t * t + (Scalar)3.0;
        data(i, 1u)    = (Scalar)3.0 * t * t * t + (Scalar)1.5 * t * t + (Scalar)0.1;

        first_derivatives(i, 0u) = (Scalar)4.0 * t;
        first_derivatives(i, 1u) = (Scalar)9.0 * t * t + (Scalar)3.0 * t;

        second_derivatives(i, 0u) = (Scalar)4.0;
        second_derivatives(i, 1u) = (Scalar)18.0 * t + (Scalar)3.0;
    }

    // create spline
    const uint8_t    degree = 3u;
    const SplineType spline(data, degree, knots);

    // call interpolate and check results
    for (uint8_t i = 1u; i < num; ++i)
    {
        const Scalar      t      = (Scalar)i / num;
        const VectorXType actual = spline.Interpolate(t);
        ASSERT_NEAR(data(i, 0u), actual(0u), 1e-7);
        ASSERT_NEAR(data(i, 1u), actual(1u), 1e-7);

        const MatrixXType actual_1 = spline.Derivatives(t, 1u);
        ASSERT_NEAR(first_derivatives(i, 0u), actual_1(0u, 1u), 1e-7);
        ASSERT_NEAR(first_derivatives(i, 1u), actual_1(1u, 1u), 1e-7);

        const MatrixXType actual_2 = spline.Derivatives(t, 2u);
        ASSERT_NEAR(second_derivatives(i, 0u), actual_2(0u, 2u), 1e-7);
        ASSERT_NEAR(second_derivatives(i, 1u), actual_2(1u, 2u), 1e-7);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Spline, GetBoundaryMaxAndMin)
{
    /**
     * @brief typedefs
     *
     */
    using Scalar      = holo::float64_t;
    using MatrixXType = holo::numerics::MatrixXT<Scalar>;
    using VectorXType = holo::numerics::VectorXT<Scalar>;
    using SplineType  = holo::Spline2;

    /**
     * define a 3d smooth curve
     * x(t) = 2*t^2 + 3;
     * y(t) = 3*t^3 + 1.5*t^2 + 0.1;
     * z(t) = t;
     */
    const uint8_t num = 100u;
    MatrixXType   data(num, 2u);
    MatrixXType   first_derivatives(num, 2u);
    MatrixXType   second_derivatives(num, 2u);
    VectorXType   knots(num);
    for (uint8_t i = 0u; i < 100u; ++i)
    {
        const Scalar t = (Scalar)i / num;
        knots(i)       = t;
        data(i, 0u)    = (Scalar)2.0 * t * t + (Scalar)3.0;
        data(i, 1u)    = (Scalar)3.0 * t * t * t + (Scalar)1.5 * t * t + (Scalar)0.1;

        first_derivatives(i, 0u) = (Scalar)4.0 * t;
        first_derivatives(i, 1u) = (Scalar)9.0 * t * t + (Scalar)3.0 * t;

        second_derivatives(i, 0u) = (Scalar)4.0;
        second_derivatives(i, 1u) = (Scalar)18.0 * t + (Scalar)3.0;
    }

    // create spline
    const uint8_t    degree = 3u;
    const SplineType spline(data, degree, knots);

    spline.GetBoundaryMin();
    spline.GetBoundaryMax();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
