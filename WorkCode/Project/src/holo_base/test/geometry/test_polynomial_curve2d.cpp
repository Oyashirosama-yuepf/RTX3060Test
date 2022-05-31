/*!
 *  \brief This file test PolynomialCurve2DT.
 *  \author lisongze(lisongze@holomaitc.com)
 *  \date "2019-09-20"
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <gtest/gtest.h>
#include <holo/geometry/polynomial_curve2d.h>

using namespace holo;
using holo::numerics::VectorXf;
using holo::numerics::VectorXd;
using holo::numerics::Vector3f;

////////////////////////////////////////////////////////////////////////////////
TEST(PolynomialCurve2DTTest, Constructor)
{
    // default constructor
    holo::geometry::PolynomialCurve2DT<float32_t> curve0;
    holo::numerics::VectorXT<float32_t>           coeffs(4);
    coeffs(0) = 1.0f;
    coeffs(1) = 2.0f;
    coeffs(2) = 3.0f;
    coeffs(3) = 4.0f;

    curve0.SetDegree(3U);
    curve0.SetRegionStart(1.0f);
    curve0.SetRegionEnd(100.0f);
    curve0.SetCoeffs(coeffs);

    ASSERT_EQ(curve0.GetDegree(), 3U);
    ASSERT_EQ(curve0.GetRegionStart(), 1.0f);
    ASSERT_EQ(curve0.GetRegionEnd(), 100.0f);
    ASSERT_EQ(curve0.GetCoeffs(), coeffs);
    ASSERT_EQ(curve0.GetCurveType(), CurveDescriptorT<float32_t>::CurveDescriptorType::POLYNOMIAL2D);

    // constructor with param
    holo::geometry::PolynomialCurve2DT<float32_t> curve1(3U, coeffs, 1.0f, 100.0f);
    ASSERT_EQ(curve1.GetDegree(), 3U);
    ASSERT_EQ(curve1.GetRegionStart(), 1.0f);
    ASSERT_EQ(curve1.GetRegionEnd(), 100.0f);
    ASSERT_EQ(curve1.GetCoeffs(), coeffs);
    ASSERT_EQ(curve1.GetCurveType(), CurveDescriptorT<float32_t>::CurveDescriptorType::POLYNOMIAL2D);

    // copy constructor
    holo::geometry::PolynomialCurve2DT<float32_t> curve2(curve0);
    ASSERT_EQ(curve2.GetDegree(), curve0.GetDegree());
    ASSERT_EQ(curve2.GetRegionStart(), curve0.GetRegionStart());
    ASSERT_EQ(curve2.GetRegionEnd(), curve0.GetRegionEnd());
    ASSERT_EQ(curve2.GetCoeffs(), curve0.GetCoeffs());
    ASSERT_EQ(curve2.GetCurveType(), CurveDescriptorT<float32_t>::CurveDescriptorType::POLYNOMIAL2D);

    // move constructor
    holo::geometry::PolynomialCurve2DT<float32_t> curve3(std::move(curve1));
    ASSERT_EQ(curve3.GetDegree(), curve0.GetDegree());
    ASSERT_EQ(curve3.GetRegionStart(), curve0.GetRegionStart());
    ASSERT_EQ(curve3.GetRegionEnd(), curve0.GetRegionEnd());
    ASSERT_EQ(curve3.GetCoeffs(), curve0.GetCoeffs());
    ASSERT_EQ(curve3.GetCurveType(), CurveDescriptorT<float32_t>::CurveDescriptorType::POLYNOMIAL2D);

    try
    {
        holo::geometry::PolynomialCurve2DT<float32_t> curve1(1U, coeffs, 1.0f, 100.0f);
    }
    catch(...)
    {
    }
    
}

////////////////////////////////////////////////////////////////////////////////
TEST(PolynomialCurve2DTTest, OperatorAssign)
{
    // default operator=
    holo::geometry::PolynomialCurve2DT<float32_t> curve0;
    holo::numerics::VectorXT<float32_t>           coeffs(4);
    coeffs(0) = 1.0f;
    coeffs(1) = 2.0f;
    coeffs(2) = 3.0f;
    coeffs(3) = 4.0f;

    curve0.SetDegree(3U);
    curve0.SetRegionStart(1.0f);
    curve0.SetRegionEnd(100.0f);
    curve0.SetCoeffs(coeffs);

    holo::geometry::PolynomialCurve2DT<float32_t> curve1 = curve0;
    ASSERT_EQ(curve1.GetDegree(), curve0.GetDegree());
    ASSERT_EQ(curve1.GetRegionStart(), curve0.GetRegionStart());
    ASSERT_EQ(curve1.GetRegionEnd(), curve0.GetRegionEnd());
    ASSERT_EQ(curve1.GetCoeffs(), curve0.GetCoeffs());
    ASSERT_EQ(curve1.GetCurveType(), CurveDescriptorT<float32_t>::CurveDescriptorType::POLYNOMIAL2D);

    // move assignment operator=
    holo::geometry::PolynomialCurve2DT<float32_t> curve2 = std::move(curve1);
    ASSERT_EQ(curve2.GetDegree(), curve0.GetDegree());
    ASSERT_EQ(curve2.GetRegionStart(), curve0.GetRegionStart());
    ASSERT_EQ(curve2.GetRegionEnd(), curve0.GetRegionEnd());
    ASSERT_EQ(curve2.GetCoeffs(), curve0.GetCoeffs());
    ASSERT_EQ(curve2.GetCurveType(), CurveDescriptorT<float32_t>::CurveDescriptorType::POLYNOMIAL2D);
}

////////////////////////////////////////////////////////////////////////////////
TEST(PolynomialCurve2DTTest, OperatorAccess)
{
    // default operator=
    holo::geometry::PolynomialCurve2DT<float32_t> curve0;
    holo::numerics::VectorXT<float32_t>           coeffs(4);
    coeffs(0) = 1.0f;
    coeffs(1) = 2.0f;
    coeffs(2) = 3.0f;
    coeffs(3) = 4.0f;

    curve0.SetDegree(3U);
    curve0.SetRegionStart(1.0f);
    curve0.SetRegionEnd(100.0f);
    curve0.SetCoeffs(coeffs);

    ASSERT_EQ(curve0[0], 1.0f);
    ASSERT_EQ(curve0[1], 2.0f);
    ASSERT_EQ(curve0[2], 3.0f);
    ASSERT_EQ(curve0[3], 4.0f);

    EXPECT_THROW(curve0[8], std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////
TEST(PolynomialCurve2DTTest, OperatorEqual)
{
    // default operator=
    holo::geometry::PolynomialCurve2DT<float32_t> curve0;
    holo::numerics::VectorXT<float32_t>           coeffs(4);
    coeffs(0) = 1.0f;
    coeffs(1) = 2.0f;
    coeffs(2) = 3.0f;
    coeffs(3) = 4.0f;

    curve0.SetDegree(3U);
    curve0.SetRegionStart(1.0f);
    curve0.SetRegionEnd(100.0f);
    curve0.SetCoeffs(coeffs);

    holo::geometry::PolynomialCurve2DT<float32_t> curve1 = curve0;
    ASSERT_EQ(curve0, curve1);

    curve0.SetDegree(4U);
    EXPECT_FALSE(curve0 == curve1);

    curve0.SetDegree(3U);
    curve0.SetRegionStart(2.0f);
    EXPECT_FALSE(curve0 == curve1);

    curve0.SetDegree(3U);
    curve0.SetRegionStart(1.0f);
    curve0.SetRegionEnd(101.0f);
    EXPECT_FALSE(curve0 == curve1);

    curve0.SetDegree(3U);
    curve0.SetRegionStart(1.0f);
    curve0.SetRegionEnd(100.0f);
    coeffs(3) = 5.0f;
    curve0.SetCoeffs(coeffs);
    EXPECT_FALSE(curve0 == curve1);
}

////////////////////////////////////////////////////////////////////////////////
TEST(PolynomialCurve2DTTest, ToString)
{
    // default operator=
    holo::geometry::PolynomialCurve2DT<float32_t> curve0;
    curve0.ToString();
}

TEST(PolynomialCurve2DTTest, GetSerializedSize)
{
    holo::geometry::PolynomialCurve2DT<float32_t> curve0;
    ASSERT_EQ(16, curve0.GetSerializedSize<4U>());
    ASSERT_EQ(24, curve0.GetSerializedSize<8U>());
}

TEST(PolynomialCurve2DTTest, SerializeAndDeserialize)
{
    srand(0);

    uint32_t vector_size0 = 10U + rand() % 10U;
    uint32_t vector_size1 = 10U + rand() % 10U;
    uint32_t i            = 0U;

    holo::geometry::PolynomialCurve2f input_curvef, output_curvef;

    VectorXf curvef_coeff;
    VectorXd curved_coeff;
    curvef_coeff.Resize(vector_size0);
    curved_coeff.Resize(vector_size1);

    for (i = 0U; i < vector_size0; ++i)
    {
        curvef_coeff[i] = static_cast<float32_t>(rand() % 1000);
    }
    for (i = 0U; i < vector_size1; ++i)
    {
        curved_coeff[i] = static_cast<float64_t>(rand() % 1000);
    }
    input_curvef.SetCoeffs(curvef_coeff);
    input_curvef.SetDegree(8U);
    input_curvef.SetRegionStart(static_cast<float32_t>(rand() % 1000));
    input_curvef.SetRegionEnd(static_cast<float32_t>(rand() % 1000));

    uint8_t buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << input_curvef;
    ASSERT_EQ(input_curvef.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> output_curvef;

    ASSERT_EQ(input_curvef.GetDegree(), output_curvef.GetDegree());
    ASSERT_EQ(input_curvef.GetCurveType(), output_curvef.GetCurveType());
    ASSERT_EQ(input_curvef.GetRegionStart(), output_curvef.GetRegionStart());
    ASSERT_EQ(input_curvef.GetRegionEnd(), output_curvef.GetRegionEnd());
    ASSERT_EQ(input_curvef.GetCoeffs().GetSize(), output_curvef.GetCoeffs().GetSize());
    for (i = 0U; i < input_curvef.GetCoeffs().GetSize(); ++i)
    {
        ASSERT_EQ(input_curvef.GetCoeffs()[i], output_curvef.GetCoeffs()[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
