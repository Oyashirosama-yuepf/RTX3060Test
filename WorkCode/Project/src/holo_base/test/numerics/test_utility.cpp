/*!
 * @file test_utility.cpp
 * @brief unit test for data statistics
 * @author Heiko Yu
 * @date 2019-08-16
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/core/epsilon.h>
#include <holo/core/types.h>
#include <holo/numerics/utility.h>

namespace numerics = holo::numerics;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Utility, ComputeMeanAndStdev)
{
    const std::vector<holo::float64_t> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    holo::float64_t                    mean, stdev;
    numerics::ComputeMeanAndStdev(data, mean, stdev);

    ASSERT_EQ(3.0, mean);
    ASSERT_EQ(std::sqrt(2.0), stdev);

    const std::vector<holo::float64_t> data2;
    numerics::ComputeMeanAndStdev(data2, mean, stdev);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Utility, ComputeMaxAndMinValue)
{
    const std::vector<holo::float64_t> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    holo::float64_t                    max_value, min_value;
    numerics::ComputeMaxAndMinValue(data, max_value, min_value);

    ASSERT_EQ(5.0, max_value);
    ASSERT_EQ(1.0, min_value);

    const std::vector<holo::float64_t> data2;
    numerics::ComputeMaxAndMinValue(data2, max_value, min_value);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Utility, ComputeRMS)
{
    using Scalar = holo::float64_t;

    std::vector<Scalar> v1(100u, 0.0);
    Scalar              rms = numerics::ComputeRMS<Scalar>(v1);
    ASSERT_NEAR(rms, 0.0, 1e-5);

    std::vector<Scalar> v2  = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    Scalar              sum = 0.0;
    for (size_t i = 0u; i < v2.size(); i++)
    {
        sum += std::pow(v2[i], 2);
    }
    Scalar expected_rms = std::sqrt(sum / v2.size());

    rms = numerics::ComputeRMS<Scalar>(v2);
    ASSERT_NEAR(rms, expected_rms, 1e-5);

    const std::vector<holo::float64_t> data2;
    rms = numerics::ComputeRMS<Scalar>(data2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Utility, ComputeCovariance)
{
    holo::numerics::MatrixXd samples(4u, 2u);
    samples(0u, 0u) = 0.0;
    samples(0u, 1u) = 0.0;
    samples(1u, 0u) = -0.5;
    samples(1u, 1u) = 0.5;
    samples(2u, 0u) = 0.0;
    samples(2u, 1u) = 1.0;
    samples(3u, 0u) = 0.5;
    samples(3u, 1u) = 0.5;

    holo::numerics::VectorXd mean;
    holo::numerics::MatrixXd covariance;
    holo::numerics::ComputeCovarianceMatrix(samples, mean, covariance);

    ASSERT_EQ(0.0, mean(0u));
    ASSERT_EQ(0.5, mean(1u));
    ASSERT_EQ(0.5, covariance(0u, 0u));
    ASSERT_EQ(0.0, covariance(0u, 1u));
    ASSERT_EQ(0.0, covariance(1u, 0u));
    ASSERT_EQ(0.5, covariance(1u, 1u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Utility, ComputePoynomialRoots)
{
    // polynomial (x+1)(x+2)(x+3)(x+4) = 0
    holo::numerics::VectorX coeffs(5u);
    coeffs(0u) = 24.0;
    coeffs(1u) = 50.0;
    coeffs(2u) = 35.0;
    coeffs(3u) = 10.0;
    coeffs(4u) = 1.0;

    // call method
    std::set<std::pair<holo::float64_t, holo::float64_t> > roots;
    numerics::ComputePolynomialRoots(coeffs, roots);

    // expected results
    const holo::numerics::Vector4 expected(-4.0, -3.0, -2.0, -1.0);

    // check results
    uint8_t i = 0u;
    for (const auto& root : roots)
    {
        ASSERT_NEAR(expected(i), root.first, holo::EpsilonT<holo::float64_t>::value);
        ASSERT_NEAR(0.0, root.second, holo::EpsilonT<holo::float64_t>::value);
        i++;
    }

    holo::numerics::VectorX coeffs2;
    numerics::ComputePolynomialRoots(coeffs2, roots);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(UtilityBernsteinPolynomial, Properties)
{
    holo::numerics::BernsteinPolynomial<holo::float64_t, 0, 3> B03;
    holo::numerics::BernsteinPolynomial<holo::float64_t, 1, 3> B13;
    holo::numerics::BernsteinPolynomial<holo::float64_t, 2, 3> B23;
    holo::numerics::BernsteinPolynomial<holo::float64_t, 3, 3> B33;

    for (holo::float64_t t = 0.0; t < 1.0; t += 0.01)
    {
        ASSERT_NEAR(1.0, B03[t] + B13[t] + B23[t] + B33[t], 1e-6);
        ASSERT_NEAR(
            0.0, B03.GetDerivative<1>(t) + B13.GetDerivative<1>(t) + B23.GetDerivative<1>(t) + B33.GetDerivative<1>(t),
            1e-6);
        ASSERT_NEAR(
            0.0, B03.GetDerivative<2>(t) + B13.GetDerivative<2>(t) + B23.GetDerivative<2>(t) + B33.GetDerivative<2>(t),
            1e-6);
        ASSERT_NEAR(B03.GetDerivative<1>(t), -B33.GetDerivative<1>(1 - t), 1e-6);
        ASSERT_NEAR(B13.GetDerivative<1>(t), -B23.GetDerivative<1>(1 - t), 1e-6);
        ASSERT_NEAR(B23.GetDerivative<1>(t), -B13.GetDerivative<1>(1 - t), 1e-6);
        ASSERT_NEAR(B33.GetDerivative<1>(t), -B03.GetDerivative<1>(1 - t), 1e-6);

        ASSERT_NEAR(B03.GetDerivative<2>(t), B33.GetDerivative<2>(1 - t), 1e-6);
        ASSERT_NEAR(B13.GetDerivative<2>(t), B23.GetDerivative<2>(1 - t), 1e-6);
        ASSERT_NEAR(B23.GetDerivative<2>(t), B13.GetDerivative<2>(1 - t), 1e-6);
        ASSERT_NEAR(B33.GetDerivative<2>(t), B03.GetDerivative<2>(1 - t), 1e-6);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(UtilityBernsteinPolynomial, GetValue)
{

    holo::numerics::BernsteinPolynomial<holo::float64_t, 0, 0> B00;
    holo::numerics::BernsteinPolynomial<holo::float64_t, 0, 1> B01;

    holo::numerics::BernsteinPolynomial<holo::float64_t, 0, 3> B03;
    holo::numerics::BernsteinPolynomial<holo::float64_t, 1, 3> B13;
    holo::numerics::BernsteinPolynomial<holo::float64_t, 2, 3> B23;
    holo::numerics::BernsteinPolynomial<holo::float64_t, 3, 3> B33;

    for (holo::float64_t t = 0.0; t < 1.0; t += 0.01)
    {
        ASSERT_NEAR(1.0, B03[t] + B13[t] + B23[t] + B33[t], 1e-6);
        ASSERT_NEAR(
            0.0, B03.GetDerivative<1>(t) + B13.GetDerivative<1>(t) + B23.GetDerivative<1>(t) + B33.GetDerivative<1>(t),
            1e-6);
        ASSERT_NEAR(
            0.0, B03.GetDerivative<2>(t) + B13.GetDerivative<2>(t) + B23.GetDerivative<2>(t) + B33.GetDerivative<2>(t),
            1e-6);
        ASSERT_NEAR(B03.GetDerivative<1>(t), -B33.GetDerivative<1>(1 - t), 1e-6);
        ASSERT_NEAR(B13.GetDerivative<1>(t), -B23.GetDerivative<1>(1 - t), 1e-6);
        ASSERT_NEAR(B23.GetDerivative<1>(t), -B13.GetDerivative<1>(1 - t), 1e-6);
        ASSERT_NEAR(B33.GetDerivative<1>(t), -B03.GetDerivative<1>(1 - t), 1e-6);

        ASSERT_NEAR(B03.GetDerivative<2>(t), B33.GetDerivative<2>(1 - t), 1e-6);
        ASSERT_NEAR(B13.GetDerivative<2>(t), B23.GetDerivative<2>(1 - t), 1e-6);
        ASSERT_NEAR(B23.GetDerivative<2>(t), B13.GetDerivative<2>(1 - t), 1e-6);
        ASSERT_NEAR(B33.GetDerivative<2>(t), B03.GetDerivative<2>(1 - t), 1e-6);
    }

    ASSERT_NEAR(1.0, B01.GetDerivative<0>(0), 1e-6);

    ASSERT_NEAR(1.0, B03.GetDerivative<0>(0), 1e-6);
    ASSERT_NEAR(0.0, B13.GetDerivative<0>(0), 1e-6);
    ASSERT_NEAR(0.0, B23.GetDerivative<0>(0), 1e-6);
    ASSERT_NEAR(0.0, B33.GetDerivative<0>(0), 1e-6);

    ASSERT_NEAR(0.125, B03.GetDerivative<0>(0.5), 1e-6);
    ASSERT_NEAR(0.375, B13.GetDerivative<0>(0.5), 1e-6);
    ASSERT_NEAR(0.375, B23.GetDerivative<0>(0.5), 1e-6);
    ASSERT_NEAR(0.125, B33.GetDerivative<0>(0.5), 1e-6);

    ASSERT_NEAR(0.0, B03.GetDerivative<0>(1), 1e-6);
    ASSERT_NEAR(0.0, B13.GetDerivative<0>(1), 1e-6);
    ASSERT_NEAR(0.0, B23.GetDerivative<0>(1), 1e-6);
    ASSERT_NEAR(1.0, B33.GetDerivative<0>(1), 1e-6);

    ASSERT_NEAR(1.0, B03.GetValue(0), 1e-6);
    ASSERT_NEAR(0.0, B13.GetValue(0), 1e-6);
    ASSERT_NEAR(0.0, B23.GetValue(0), 1e-6);
    ASSERT_NEAR(0.0, B33.GetValue(0), 1e-6);

    ASSERT_NEAR(0.125, B03.GetValue(0.5), 1e-6);
    ASSERT_NEAR(0.375, B13.GetValue(0.5), 1e-6);
    ASSERT_NEAR(0.375, B23.GetValue(0.5), 1e-6);
    ASSERT_NEAR(0.125, B33.GetValue(0.5), 1e-6);

    ASSERT_NEAR(0.0, B03.GetValue(1), 1e-6);
    ASSERT_NEAR(0.0, B13.GetValue(1), 1e-6);
    ASSERT_NEAR(0.0, B23.GetValue(1), 1e-6);
    ASSERT_NEAR(1.0, B33.GetValue(1), 1e-6);

    ASSERT_NEAR(1.0, B03[0], 1e-6);
    ASSERT_NEAR(0.0, B13[0], 1e-6);
    ASSERT_NEAR(0.0, B23[0], 1e-6);
    ASSERT_NEAR(0.0, B33[0], 1e-6);

    ASSERT_NEAR(0.125, B03[0.5], 1e-6);
    ASSERT_NEAR(0.375, B13[0.5], 1e-6);
    ASSERT_NEAR(0.375, B23[0.5], 1e-6);
    ASSERT_NEAR(0.125, B33[0.5], 1e-6);

    ASSERT_NEAR(0.0, B03[1], 1e-6);
    ASSERT_NEAR(0.0, B13[1], 1e-6);
    ASSERT_NEAR(0.0, B23[1], 1e-6);
    ASSERT_NEAR(1.0, B33[1], 1e-6);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(UtilityBernsteinPolynomial, GetDerivative)
{
    holo::numerics::BernsteinPolynomial<holo::float64_t, 0, 1> B01;

    holo::numerics::BernsteinPolynomial<holo::float64_t, 0, 3> B03;
    holo::numerics::BernsteinPolynomial<holo::float64_t, 1, 3> B13;
    holo::numerics::BernsteinPolynomial<holo::float64_t, 2, 3> B23;
    holo::numerics::BernsteinPolynomial<holo::float64_t, 3, 3> B33;

    for (holo::float64_t t = 0.0; t < 1.0; t += 0.01)
    {
        ASSERT_NEAR(1.0, B03[t] + B13[t] + B23[t] + B33[t], 1e-6);
        ASSERT_NEAR(
            0.0, B03.GetDerivative<1>(t) + B13.GetDerivative<1>(t) + B23.GetDerivative<1>(t) + B33.GetDerivative<1>(t),
            1e-6);
        ASSERT_NEAR(
            0.0, B03.GetDerivative<2>(t) + B13.GetDerivative<2>(t) + B23.GetDerivative<2>(t) + B33.GetDerivative<2>(t),
            1e-6);
        ASSERT_NEAR(B03.GetDerivative<1>(t), -B33.GetDerivative<1>(1 - t), 1e-6);
        ASSERT_NEAR(B13.GetDerivative<1>(t), -B23.GetDerivative<1>(1 - t), 1e-6);
        ASSERT_NEAR(B23.GetDerivative<1>(t), -B13.GetDerivative<1>(1 - t), 1e-6);
        ASSERT_NEAR(B33.GetDerivative<1>(t), -B03.GetDerivative<1>(1 - t), 1e-6);

        ASSERT_NEAR(B03.GetDerivative<2>(t), B33.GetDerivative<2>(1 - t), 1e-6);
        ASSERT_NEAR(B13.GetDerivative<2>(t), B23.GetDerivative<2>(1 - t), 1e-6);
        ASSERT_NEAR(B23.GetDerivative<2>(t), B13.GetDerivative<2>(1 - t), 1e-6);
        ASSERT_NEAR(B33.GetDerivative<2>(t), B03.GetDerivative<2>(1 - t), 1e-6);
    }

    ASSERT_NEAR(1.0, B01.GetDerivative<0>(0), 1e-6);
    ASSERT_NEAR(-1.0, B01.GetDerivative<1>(0), 1e-6);

    ASSERT_NEAR(-3.0, B03.GetDerivative<1>(0), 1e-6);
    ASSERT_NEAR(3.0, B13.GetDerivative<1>(0), 1e-6);
    ASSERT_NEAR(0.0, B23.GetDerivative<1>(0), 1e-6);
    ASSERT_NEAR(0.0, B33.GetDerivative<1>(0), 1e-6);

    ASSERT_NEAR(-0.75, B03.GetDerivative<1>(0.5), 1e-6);
    ASSERT_NEAR(-0.75, B13.GetDerivative<1>(0.5), 1e-6);
    ASSERT_NEAR(0.75, B23.GetDerivative<1>(0.5), 1e-6);
    ASSERT_NEAR(0.75, B33.GetDerivative<1>(0.5), 1e-6);

    ASSERT_NEAR(0.0, B03.GetDerivative<1>(1), 1e-6);
    ASSERT_NEAR(0.0, B13.GetDerivative<1>(1), 1e-6);
    ASSERT_NEAR(-3.0, B23.GetDerivative<1>(1), 1e-6);
    ASSERT_NEAR(3.0, B33.GetDerivative<1>(1), 1e-6);

    ASSERT_NEAR(6.0, B03.GetDerivative<2>(0), 1e-6);
    ASSERT_NEAR(-12.0, B13.GetDerivative<2>(0), 1e-6);
    ASSERT_NEAR(6.0, B23.GetDerivative<2>(0), 1e-6);
    ASSERT_NEAR(0.0, B33.GetDerivative<2>(0), 1e-6);

    ASSERT_NEAR(3.0, B03.GetDerivative<2>(0.5), 1e-6);
    ASSERT_NEAR(-3.0, B13.GetDerivative<2>(0.5), 1e-6);
    ASSERT_NEAR(-3.0, B23.GetDerivative<2>(0.5), 1e-6);
    ASSERT_NEAR(3.0, B33.GetDerivative<2>(0.5), 1e-6);

    ASSERT_NEAR(0.0, B03.GetDerivative<2>(1), 1e-6);
    ASSERT_NEAR(6.0, B13.GetDerivative<2>(1), 1e-6);
    ASSERT_NEAR(-12.0, B23.GetDerivative<2>(1), 1e-6);
    ASSERT_NEAR(6.0, B33.GetDerivative<2>(1), 1e-6);

    //ASSERT_NEAR(-6.0, B03.GetDerivative<3>(0), 1e-6);
    //ASSERT_NEAR(-6.0, B13.GetDerivative<3>(0), 1e-6);
    //ASSERT_NEAR(-6.0, B23.GetDerivative<3>(0), 1e-6);
    //ASSERT_NEAR(-6.0, B33.GetDerivative<3>(0), 1e-6);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(UtilityPolynomial, DefaultConstructor)
{
    holo::numerics::Polynomial<holo::float64_t, 0> P1;
    ASSERT_NEAR(0.0, P1.GetCoefficient<0>(), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 1> P2;
    ASSERT_NEAR(0.0, P2.GetCoefficient<0>(), 1e-6);
    ASSERT_NEAR(0.0, P2.GetCoefficient<1>(), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 2> P3;
    ASSERT_NEAR(0.0, P3.GetCoefficient<0>(), 1e-6);
    ASSERT_NEAR(0.0, P3.GetCoefficient<1>(), 1e-6);
    ASSERT_NEAR(0.0, P3.GetCoefficient<2>(), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 3> P4;
    ASSERT_NEAR(0.0, P4.GetCoefficient<0>(), 1e-6);
    ASSERT_NEAR(0.0, P4.GetCoefficient<1>(), 1e-6);
    ASSERT_NEAR(0.0, P4.GetCoefficient<2>(), 1e-6);
    ASSERT_NEAR(0.0, P4.GetCoefficient<3>(), 1e-6);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(UtilityPolynomial, ConstructWithCoefficients)
{
    holo::numerics::Polynomial<holo::float64_t, 0> P1(1.0);
    ASSERT_NEAR(1.0, P1.GetCoefficient<0>(), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 1> P2(1.0, 2.0);
    ASSERT_NEAR(1.0, P2.GetCoefficient<0>(), 1e-6);
    ASSERT_NEAR(2.0, P2.GetCoefficient<1>(), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 2> P3(1, 2, 3);
    ASSERT_NEAR(1.0, P3.GetCoefficient<0>(), 1e-6);
    ASSERT_NEAR(2.0, P3.GetCoefficient<1>(), 1e-6);
    ASSERT_NEAR(3.0, P3.GetCoefficient<2>(), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 3> P4(1, 2, 3.0, 4.0);
    ASSERT_NEAR(1.0, P4.GetCoefficient<0>(), 1e-6);
    ASSERT_NEAR(2.0, P4.GetCoefficient<1>(), 1e-6);
    ASSERT_NEAR(3.0, P4.GetCoefficient<2>(), 1e-6);
    ASSERT_NEAR(4.0, P4.GetCoefficient<3>(), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 3> P5(1, 2);
    ASSERT_NEAR(1.0, P5.GetCoefficient<0>(), 1e-6);
    ASSERT_NEAR(2.0, P5.GetCoefficient<1>(), 1e-6);
    ASSERT_NEAR(0.0, P5.GetCoefficient<2>(), 1e-6);
    ASSERT_NEAR(0.0, P5.GetCoefficient<3>(), 1e-6);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(UtilityPolynomial, GetValue)
{
    holo::numerics::Polynomial<holo::float64_t, 0> P1(1.0);
    ASSERT_NEAR(1.0, P1.GetValue(0), 1e-6);
    ASSERT_NEAR(1.0, P1.GetValue(1), 1e-6);
    ASSERT_NEAR(1.0, P1.GetValue(2), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 1> P2(1.0, 2.0);
    ASSERT_NEAR(1.0, P2.GetValue(0), 1e-6);
    ASSERT_NEAR(3.0, P2.GetValue(1), 1e-6);
    ASSERT_NEAR(5.0, P2.GetValue(2), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 2> P3(1, 2, 3);
    ASSERT_NEAR(1.0, P3.GetValue(0), 1e-6);
    ASSERT_NEAR(6.0, P3.GetValue(1), 1e-6);
    ASSERT_NEAR(17.0, P3.GetValue(2), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 3> P4(1, 2, 3.0, 4.0);
    ASSERT_NEAR(1.0, P4.GetValue(0), 1e-6);
    ASSERT_NEAR(10.0, P4.GetValue(1), 1e-6);
    ASSERT_NEAR(49, P4.GetValue(2), 1e-6);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(UtilityPolynomial, GetDerivative)
{
    holo::numerics::Polynomial<holo::float64_t, 0> P1(1.0);
    ASSERT_NEAR(0.0, P1.GetDerivative<1>(0), 1e-6);
    ASSERT_NEAR(0.0, P1.GetDerivative<1>(1), 1e-6);
    ASSERT_NEAR(0.0, P1.GetDerivative<1>(2), 1e-6);

    ASSERT_NEAR(0.0, P1.GetDerivative<2>(0), 1e-6);
    ASSERT_NEAR(0.0, P1.GetDerivative<2>(1), 1e-6);
    ASSERT_NEAR(0.0, P1.GetDerivative<2>(2), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 1> P2(1.0, 2.0);
    ASSERT_NEAR(2.0, P2.GetDerivative<1>(0), 1e-6);
    ASSERT_NEAR(2.0, P2.GetDerivative<1>(1), 1e-6);
    ASSERT_NEAR(2.0, P2.GetDerivative<1>(2), 1e-6);

    ASSERT_NEAR(0.0, P2.GetDerivative<2>(0), 1e-6);
    ASSERT_NEAR(0.0, P2.GetDerivative<2>(1), 1e-6);
    ASSERT_NEAR(0.0, P2.GetDerivative<2>(2), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 2> P3(1, 2, 3);
    ASSERT_NEAR(2.0, P3.GetDerivative<1>(0), 1e-6);
    ASSERT_NEAR(8.0, P3.GetDerivative<1>(1), 1e-6);
    ASSERT_NEAR(14.0, P3.GetDerivative<1>(2), 1e-6);

    ASSERT_NEAR(6.0, P3.GetDerivative<2>(0), 1e-6);
    ASSERT_NEAR(6.0, P3.GetDerivative<2>(1), 1e-6);
    ASSERT_NEAR(6.0, P3.GetDerivative<2>(2), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 3> P4(1, 2, 3.0, 4.0);
    ASSERT_NEAR(2.0, P4.GetDerivative<1>(0), 1e-6);
    ASSERT_NEAR(20.0, P4.GetDerivative<1>(1), 1e-6);
    ASSERT_NEAR(62.0, P4.GetDerivative<1>(2), 1e-6);

    ASSERT_NEAR(6.0, P4.GetDerivative<2>(0), 1e-6);
    ASSERT_NEAR(30.0, P4.GetDerivative<2>(1), 1e-6);
    ASSERT_NEAR(54.0, P4.GetDerivative<2>(2), 1e-6);

    holo::numerics::Polynomial<holo::float64_t, 3> P5(0, 1.5, 0, 0);
    ASSERT_NEAR(0.0, P5.GetDerivative<0>(0), 1e-6);
    ASSERT_NEAR(1.5, P5.GetDerivative<0>(1), 1e-6);
    ASSERT_NEAR(3.0, P5.GetDerivative<0>(2), 1e-6);

    ASSERT_NEAR(1.5, P5.GetDerivative<1>(0), 1e-6);
    ASSERT_NEAR(1.5, P5.GetDerivative<1>(1), 1e-6);
    ASSERT_NEAR(1.5, P5.GetDerivative<1>(2), 1e-6);

    ASSERT_NEAR(0, P5.GetDerivative<2>(0), 1e-6);
    ASSERT_NEAR(0, P5.GetDerivative<2>(1), 1e-6);
    ASSERT_NEAR(0, P5.GetDerivative<2>(2), 1e-6);
}

TEST(UtilityPolynomial, GetDerivativePolynomial)
{
    holo::numerics::Polynomial<holo::float64_t, 0U> P0(1.0);
    auto poly0 = P0.GetDerivativePolynomial<0U>();
    ASSERT_EQ(1.0, poly0.GetCoefficient<0U>());

    holo::numerics::Polynomial<holo::float64_t, 1U> P1(1.0, 2.0);
    auto poly10 = P1.GetDerivativePolynomial<0U>();
    auto poly11 = P1.GetDerivativePolynomial<1U>();
    ASSERT_EQ(1.0, poly10.GetCoefficient<0U>());
    ASSERT_EQ(2.0, poly10.GetCoefficient<1U>());
    ASSERT_EQ(2.0, poly11.GetCoefficient<0U>());

    holo::numerics::Polynomial<holo::float64_t, 2U> P2(1.0, 2.0, 3.0);
    auto poly20 = P2.GetDerivativePolynomial<0U>();
    auto poly21 = P2.GetDerivativePolynomial<1U>();
    auto poly22 = P2.GetDerivativePolynomial<2U>();
    ASSERT_EQ(1.0, poly20.GetCoefficient<0U>());
    ASSERT_EQ(2.0, poly20.GetCoefficient<1U>());
    ASSERT_EQ(3.0, poly20.GetCoefficient<2U>());
    ASSERT_EQ(2.0, poly21.GetCoefficient<0U>());
    ASSERT_EQ(6.0, poly21.GetCoefficient<1U>());
    ASSERT_EQ(6.0, poly22.GetCoefficient<0U>());

    holo::numerics::Polynomial<holo::float64_t, 3U> P3(1.0, 2.0, 3.0, 4.0);
    auto poly30 = P3.GetDerivativePolynomial<0U>();
    auto poly31 = P3.GetDerivativePolynomial<1U>();
    auto poly32 = P3.GetDerivativePolynomial<2U>();
    auto poly33 = P3.GetDerivativePolynomial<3U>();
    ASSERT_EQ(1.0, poly30.GetCoefficient<0U>());
    ASSERT_EQ(2.0, poly30.GetCoefficient<1U>());
    ASSERT_EQ(3.0, poly30.GetCoefficient<2U>());
    ASSERT_EQ(4.0, poly30.GetCoefficient<3U>());
    ASSERT_EQ(2.0, poly31.GetCoefficient<0U>());
    ASSERT_EQ(6.0, poly31.GetCoefficient<1U>());
    ASSERT_EQ(12.0, poly31.GetCoefficient<2U>());
    ASSERT_EQ(6.0, poly32.GetCoefficient<0U>());
    ASSERT_EQ(24.0, poly32.GetCoefficient<1U>());
    ASSERT_EQ(24.0, poly33.GetCoefficient<0U>());
}

TEST(Utility, ComputeCovarianceMatrix)
{
    holo::numerics::MatrixXd samples(0u, 0u);

    holo::numerics::VectorXd mean;
    holo::numerics::MatrixXd covariance;
    holo::numerics::ComputeCovarianceMatrix(samples, mean, covariance);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
