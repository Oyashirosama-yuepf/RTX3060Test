/*!
 * @file test_polyfit2.cpp
 * @brief unit test for fitting polynomial curve in 2D space
 * @author jiaxing.zhao
 * @date 2017-08-15
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notic.
 */

#include <gtest/gtest.h>
#include <holo/geometry/polyfit2.h>

using namespace holo;

///////////////////////////////////////////////////////////////////////////////
namespace internal
{
using Scalar       = float64_t;
using Point2Type   = holo::geometry::Point2T<Scalar>;
using VectorXType  = holo::numerics::VectorXT<Scalar>;
using Pose2Type    = holo::geometry::Pose2T<Scalar>;
using Polyfit2Type = holo::geometry::Polyfit2T<Scalar>;
const Scalar tol   = 1e-6;
}  // namespace internal

///////////////////////////////////////////////////////////////////////////////
TEST(Polyfit2, CubicPolynomial)
{
    std::vector<internal::Point2Type> points;
    {
        points.reserve(8u);
        points.push_back(internal::Point2Type(-3.0, -20.0));
        points.push_back(internal::Point2Type(-2.0, -5.0));
        points.push_back(internal::Point2Type(-1.0, 0.0));
        points.push_back(internal::Point2Type(0.0, 1.0));
        points.push_back(internal::Point2Type(1.0, 4.0));
        points.push_back(internal::Point2Type(2.0, 15.0));
        points.push_back(internal::Point2Type(3.0, 40.0));
        points.push_back(internal::Point2Type(4.0, 85.0));
    }

    /* create polynomial */
    internal::Polyfit2Type poly(3u);

    /* fit a polynomial */
    {
        const bool_t fit_status = poly.Fit(points);
        ASSERT_TRUE(fit_status);

        /* expect polynomial y = x^3 + x^2 + x + 1 */
        const internal::VectorXType& coeffs = poly.GetCoeffs();
        ASSERT_NEAR(1.0, coeffs(0u), internal::tol);
        ASSERT_NEAR(1.0, coeffs(1u), internal::tol);
        ASSERT_NEAR(1.0, coeffs(2u), internal::tol);
        ASSERT_NEAR(1.0, coeffs(3u), internal::tol);

        /* expected residual */
        ASSERT_NEAR(0.0, poly.GetResidual(), internal::tol);
    }

    /* interpolate a new point */
    {
        internal::Point2Type actual;
        const bool_t         interpolate_status = poly.Interpolate(0.5, actual);
        ASSERT_TRUE(interpolate_status);

        ASSERT_NEAR(0.5, actual.GetX(), internal::tol);
        ASSERT_NEAR(1.875, actual.GetY(), internal::tol);
    }

    /* compute distance to curve*/
    {
        internal::Point2Type max_point;
        internal::Point2Type min_point;
        poly.Interpolate(poly.GetMaxX(), max_point);
        poly.Interpolate(poly.GetMinX(), min_point);

        // compute
        internal::Scalar     actual = 0.0;
        internal::Point2Type point(-40.0, -30.0);
        poly.ComputePointDistanceToCurve(point, actual, true);
        const internal::Scalar distance_to_min_point = point.Dist(min_point);
        const internal::Scalar distance_to_max_point = point.Dist(max_point);
        const internal::Scalar expected              = std::min(distance_to_min_point, distance_to_max_point);

        ASSERT_NEAR(expected, actual, internal::tol);
    }
}

TEST(Polyfit2, ConstructorException)
{
    internal::VectorXType coeffs_x_y(0u);
    try
    {
        internal::Polyfit2Type poly(coeffs_x_y);
    }
    catch (...)
    {
    }
}

TEST(Polyfit2, Fit)
{
    internal::Polyfit2Type            poly(2u);
    std::vector<internal::Point2Type> points;
    try
    {
        const bool_t status = poly.Fit(points);
    }
    catch (...)
    {
    }
}

TEST(Polyfit2, Fit_OutOfMatrixSize)
{
    internal::Polyfit2Type            poly(2u);
    std::vector<internal::Point2Type> points(300, internal::Point2Type::Zero());
    try
    {
        const bool_t status = poly.Fit(points);
    }
    catch (...)
    {
    }
}

TEST(Polyfit2, Interpolate)
{
    internal::Polyfit2Type poly(2u);
    internal::Point2Type   actual;

    std::vector<internal::Point2Type> points;
    {
        points.reserve(8u);
        points.push_back(internal::Point2Type(-3.0, -20.0));
        points.push_back(internal::Point2Type(-2.0, -5.0));
        points.push_back(internal::Point2Type(-1.0, 0.0));
        points.push_back(internal::Point2Type(0.0, 1.0));
        points.push_back(internal::Point2Type(1.0, 4.0));
        points.push_back(internal::Point2Type(2.0, 15.0));
        points.push_back(internal::Point2Type(3.0, 40.0));
        points.push_back(internal::Point2Type(4.0, 85.0));
    }

    poly.Fit(points);
    const bool_t status = poly.Interpolate(10, actual);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Polyfit2, BinomialPolynomial)
{
    std::vector<internal::Point2Type> points;
    {
        points.push_back(internal::Point2Type(-3.0, 10.0));
        points.push_back(internal::Point2Type(-2.0, 3.0));
        points.push_back(internal::Point2Type(-1.0, 0.0));
        points.push_back(internal::Point2Type(0.0, 1.0));
        points.push_back(internal::Point2Type(1.0, 6.0));
        points.push_back(internal::Point2Type(2.0, 15.0));
        points.push_back(internal::Point2Type(3.0, 28.0));
    }

    /* create polygonmial */
    internal::Polyfit2Type poly(2u);

    /* fit a polynomial */
    {
        const bool_t status = poly.Fit(points);
        ASSERT_TRUE(status);

        /* expect polynomial y = 2 * x^2 + 3 * x + 1 */
        const internal::VectorXType& coeffs = poly.GetCoeffs();
        ASSERT_NEAR(1.0, coeffs(0u), internal::tol);
        ASSERT_NEAR(3.0, coeffs(1u), internal::tol);
        ASSERT_NEAR(2.0, coeffs(2u), internal::tol);
        ASSERT_NEAR(0.0, poly.GetResidual(), internal::tol);
    }

    /* interpolate a point */
    {
        internal::Point2Type actual;
        const bool_t         status = poly.Interpolate(0.5, actual);

        ASSERT_TRUE(status);
        ASSERT_NEAR(0.5, actual.GetX(), internal::tol);
        ASSERT_NEAR(3.0, actual.GetY(), internal::tol);
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(Polyfit2, LinearPolynomial)
{
    std::vector<internal::Point2Type> points;
    {
        points.push_back(internal::Point2Type(-3.0, -2.0));
        points.push_back(internal::Point2Type(-2.0, -1.0));
        points.push_back(internal::Point2Type(-1.0, 0.0));
        points.push_back(internal::Point2Type(0.0, 1.0));
        points.push_back(internal::Point2Type(1.0, 2.0));
        points.push_back(internal::Point2Type(2.0, 3.0));
        points.push_back(internal::Point2Type(3.0, 4.0));
    }

    /* create a polynomial */
    internal::Polyfit2Type poly(1u);

    /* fit a polynomial */
    {
        const bool_t status = poly.Fit(points);
        ASSERT_TRUE(status);

        /* expect polynomial x + 1 = y */
        const internal::VectorXType& coeffs = poly.GetCoeffs();
        ASSERT_EQ(2u, coeffs.GetSize());
        ASSERT_NEAR(1.0, coeffs(0u), internal::tol);
        ASSERT_NEAR(1.0, coeffs(1u), internal::tol);
        ASSERT_NEAR(0.0, poly.GetResidual(), internal::tol);
    }

    /* interpolate */
    {
        internal::Point2Type actual;
        const bool_t         status = poly.Interpolate(0.5, actual);
        ASSERT_TRUE(status);
        ASSERT_NEAR(0.5, actual.GetX(), internal::tol);
        ASSERT_NEAR(1.5, actual.GetY(), internal::tol);
    }

    /* compute distance to curve*/
    {
        internal::Point2Type max_point;
        internal::Point2Type min_point;
        poly.Interpolate(poly.GetMaxX(), max_point);
        poly.Interpolate(poly.GetMinX(), min_point);

        // compute
        internal::Scalar     actual = 0.0;
        internal::Point2Type point(-40.0, -39.0);
        poly.ComputePointDistanceToCurve(point, actual, true);
        const internal::Scalar distance_to_min_point = point.Dist(min_point);
        const internal::Scalar distance_to_max_point = point.Dist(max_point);
        const internal::Scalar expected              = std::min(distance_to_min_point, distance_to_max_point);

        ASSERT_NEAR(expected, actual, internal::tol);
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(Polyfit2, QuarticPolynomial)
{
    std::vector<internal::Point2Type> points;
    {
        points.push_back(internal::Point2Type(-3.0, 61.0));
        points.push_back(internal::Point2Type(-2.0, 11.0));
        points.push_back(internal::Point2Type(-1.0, 1.0));
        points.push_back(internal::Point2Type(0.0, 1.0));
        points.push_back(internal::Point2Type(1.0, 5.0));
        points.push_back(internal::Point2Type(2.0, 31.0));
        points.push_back(internal::Point2Type(3.0, 121.0));
    }

    /* create a polynomial */
    internal::Polyfit2Type poly(4u);

    /* fit a polynomial */
    {
        const bool_t status = poly.Fit(points);
        ASSERT_TRUE(status);

        /* expect polynomial x^4 + x^3 + x^2 + x + 1 = y */
        const internal::VectorXType& coeffs = poly.GetCoeffs();
        ASSERT_TRUE(status);
        ASSERT_NEAR(1.0, coeffs(0u), internal::tol);
        ASSERT_NEAR(1.0, coeffs(1u), internal::tol);
        ASSERT_NEAR(1.0, coeffs(2u), internal::tol);
        ASSERT_NEAR(1.0, coeffs(3u), internal::tol);
        ASSERT_NEAR(1.0, coeffs(4u), internal::tol);
        ASSERT_NEAR(0.0, poly.GetResidual(), internal::tol);
    }

    /* interpolate */
    {
        internal::Point2Type actual;
        const bool_t         status = poly.Interpolate(0.5, actual);
        ASSERT_TRUE(status);
        ASSERT_NEAR(0.5, actual.GetX(), internal::tol);
        ASSERT_NEAR(1.9375, actual.GetY(), internal::tol);
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(Polyfit2, ComputeDistancePointsToCurveTest1)
{
    internal::VectorXType coeffs_x_y(4u);
    {
        coeffs_x_y(0u) = 1.0;
        coeffs_x_y(1u) = 1.0;
        coeffs_x_y(2u) = 0.0;
        coeffs_x_y(3u) = 0.0;
    }

    std::vector<internal::Point2Type> points;
    const internal::Point2Type        point1(0.0, 0.0);
    const internal::Point2Type        point2(-1.0, 0.0);
    points.push_back(point1);
    points.push_back(point2);

    internal::Polyfit2Type poly(coeffs_x_y);

    internal::Scalar              dist1;
    internal::Scalar              dist2;
    std::vector<internal::Scalar> dists;

    /* curve function y = x + 1 */
    const bool_t status1 = poly.ComputePointDistanceToCurve(point1, dist1);
    const bool_t status2 = poly.ComputePointDistanceToCurve(point2, dist2);
    const bool_t status3 = poly.ComputePointDistanceToCurve(points, dists);

    ASSERT_TRUE(status1);
    ASSERT_NEAR(0.707107, dist1, internal::tol);
    ASSERT_TRUE(status2);
    ASSERT_NEAR(0.0, dist2, internal::tol);
    ASSERT_TRUE(status3);
    ASSERT_NEAR(0.707106, dists[0u], internal::tol);
    ASSERT_NEAR(0.0, dists[1u], internal::tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Polyfit2, ComputeDistancePointsToCurveTest2)
{
    internal::VectorXType coeffs_x_y(4u);
    coeffs_x_y(0u) = 1.0;
    coeffs_x_y(1u) = -2.0;
    coeffs_x_y(2u) = 1.0;
    coeffs_x_y(3u) = 0.0;

    std::vector<internal::Point2Type> points;
    internal::Point2Type              point1(1.0, 0.0);
    internal::Point2Type              point2(1.0, -1.0);
    points.push_back(point1);
    points.push_back(point2);

    /* fit a polynominal */
    internal::Polyfit2Type poly(coeffs_x_y);

    internal::Scalar              dist1;
    internal::Scalar              dist2;
    std::vector<internal::Scalar> dists;

    // curve function y = x^2 -2 * x + 1
    const bool_t status1 = poly.ComputePointDistanceToCurve(point1, dist1);
    const bool_t status2 = poly.ComputePointDistanceToCurve(point2, dist2);
    const bool_t status3 = poly.ComputePointDistanceToCurve(points, dists);

    ASSERT_TRUE(status1);
    ASSERT_NEAR(0.0, dist1, internal::tol);
    ASSERT_TRUE(status2);
    ASSERT_NEAR(1.0, dist2, internal::tol);
    ASSERT_TRUE(status3);
    ASSERT_NEAR(0.0, dists[0u], internal::tol);
    ASSERT_NEAR(1.0, dists[1u], internal::tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Polyfit2, ComputeDistancePointsToCurveTest3)
{
    internal::VectorXType coeffs_x_y(4u);
    coeffs_x_y(0u) = 0.0;
    coeffs_x_y(1u) = 0.0;
    coeffs_x_y(2u) = 1.0;
    coeffs_x_y(3u) = 0.0;

    std::vector<internal::Point2Type> points;
    internal::Point2Type              point1(0.0, 0.0);
    internal::Point2Type              point2(0.0, -1.0);
    points.push_back(point1);
    points.push_back(point2);

    internal::Polyfit2Type poly(coeffs_x_y);

    internal::Scalar              dist1;
    internal::Scalar              dist2;
    std::vector<internal::Scalar> dists;

    // curve function y = x^2
    const bool_t status1 = poly.ComputePointDistanceToCurve(point1, dist1);
    const bool_t status2 = poly.ComputePointDistanceToCurve(point2, dist2);
    const bool_t status3 = poly.ComputePointDistanceToCurve(points, dists);

    ASSERT_TRUE(status1);
    ASSERT_NEAR(0.0, dist1, internal::tol);
    ASSERT_TRUE(status2);
    ASSERT_NEAR(1.0, dist2, internal::tol);
    ASSERT_TRUE(status3);
    ASSERT_NEAR(0.0, dists[0u], internal::tol);
    ASSERT_NEAR(1.0, dists[1u], internal::tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Polyfit2, ComputeDistancePointsToCurveTest4)
{
    internal::VectorXType coeffs_x_y(4u);
    coeffs_x_y(0u) = 0.0;
    coeffs_x_y(1u) = 0.0;
    coeffs_x_y(2u) = 0.0;
    coeffs_x_y(3u) = 1.0;

    internal::Point2Type   point1(0.0, 0.0);
    internal::Polyfit2Type poly(coeffs_x_y);

    internal::Scalar dist1;

    // curve function y = x^3
    poly.ComputePointDistanceToCurve(point1, dist1);
    ASSERT_NEAR(dist1, 0.0, internal::tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Polyfit2, DistanceInrerpolationMaxMinCoef)
{
    internal::VectorXType coeffs_x_y(4u);
    coeffs_x_y(0u) = -1.0;
    coeffs_x_y(1u) = 0.0;
    coeffs_x_y(2u) = 1.0;
    coeffs_x_y(3u) = 0.0;

    internal::Point2Type   point1(0.0, -1.0);
    internal::Polyfit2Type poly(coeffs_x_y);

    internal::Scalar dist1;

    // curve function y = x^2 - 1
    poly.ComputePointDistanceToCurve(point1, dist1);
    ASSERT_NEAR(dist1, 0.0, internal::tol);

    internal::Point2Type point;
    bool_t               status1 = poly.Interpolate(0.0, point);

    const internal::VectorXType& coeffs = poly.GetCoeffs();
    ASSERT_TRUE(status1);
    ASSERT_NEAR(coeffs(0u), -1.0, internal::tol);
    ASSERT_NEAR(coeffs(1u), 0.0, internal::tol);
    ASSERT_NEAR(coeffs(2u), 1.0, internal::tol);
    ASSERT_NEAR(coeffs(3u), 0.0, internal::tol);
    ASSERT_NEAR(point.GetY(), -1.0, internal::tol);
    ASSERT_NEAR(poly.GetMaxX(), std::numeric_limits<internal::Scalar>::max(), internal::tol);
    ASSERT_NEAR(poly.GetMinX(), -std::numeric_limits<internal::Scalar>::max(), internal::tol);
}

TEST(PolynomialCurve2DTTest, GetSerializedSize)
{
    internal::VectorXType coeffs_x_y(4u);
    coeffs_x_y(0u) = 0.0;
    coeffs_x_y(1u) = 0.0;
    coeffs_x_y(2u) = 0.0;
    coeffs_x_y(3u) = 1.0;

    internal::Polyfit2Type poly(coeffs_x_y);

    ASSERT_EQ(64, poly.GetSerializedSize<4U>());
    ASSERT_EQ(72, poly.GetSerializedSize<8U>());
}

TEST(PolynomialCurve2DTTest, SerializeAndDeserialize)
{
    srand(time(0));

    int32_t                   degree0    = 2;
    int32_t                   degree1    = 3;
    uint32_t                  point_cnt0 = 100 + rand() % 100;
    uint32_t                  point_cnt1 = 100 + rand() % 100;
    uint32_t                  i          = 0;
    holo::geometry::Polyfit2f input_pf(degree0), output_pf(degree0);

    std::vector<holo::geometry::Point2f> pointsf;

    for (i = 0; i < point_cnt0; ++i)
    {
        pointsf.push_back(holo::geometry::Point2f((float32_t)(rand() % 1000), (float32_t)(rand() % 1000)));
    }
    input_pf.Fit(pointsf);

    uint8_t                           buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << input_pf;
    ASSERT_EQ(input_pf.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> output_pf;

    ASSERT_EQ(input_pf.GetDegree(), output_pf.GetDegree());
    ASSERT_EQ(input_pf.GetResidual(), output_pf.GetResidual());
    ASSERT_EQ(input_pf.GetCoeffs().GetSize(), input_pf.GetCoeffs().GetSize());
    for (i = 0; i < input_pf.GetCoeffs().GetSize(); ++i)
    {
        ASSERT_EQ(input_pf.GetCoeffs()[i], output_pf.GetCoeffs()[i]);
    }
    ASSERT_EQ(input_pf.GetMaxX(), output_pf.GetMaxX());
    ASSERT_EQ(input_pf.GetMinX(), output_pf.GetMinX());
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
