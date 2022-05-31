/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_point_feature.h
 * @brief Unit test for class PointFeatureT
 * @author lifeng(lifeng@holomaitc.com)
 * @date 2021-01-07
 */

#include <gtest/gtest.h>

#include <holo/core/epsilon.h>
#include <holo/parking/vision/point_feature.h>
#include <holo/serialization/serialization.h>
#include <holo/utils/serialization_exception.h>
#include <holo/utils/serializer.h>
#include <holo/utils/deserializer.h>
#include <holo/utils/buffer.h>

using namespace holo::parking::vision;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PointFeatured, Constructor)
{
    PointFeatured::Point2Type     point(1.0, 2.0);
    PointFeatured::ScalarType     confidence = 3.0;
    PointFeatured::DescriptorType desc;
    uint32_t                      dimension = 256;
    desc.resize(dimension);

    for (size_t i = 0; i < 256; i++)
    {
        desc[i] = i * 1.0;
    }
    PointFeatured point_feature(point, desc, confidence);

    // check results
    using EpsilonType = holo::EpsilonT<PointFeatured::ScalarType>;
    ASSERT_NEAR(point.GetX(), point_feature.GetPointPosition().GetX(), EpsilonType::value);
    ASSERT_NEAR(point.GetY(), point_feature.GetPointPosition().GetY(), EpsilonType::value);
    ASSERT_NEAR(confidence, point_feature.GetConfidence(), EpsilonType::value);

    for (size_t i = 0; i < point_feature.GetDescriptorDimension(); i++)
    {
        ASSERT_NEAR(i, point_feature.GetDescriptor().at(i), EpsilonType::value);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PointFeatured, Assign)
{
    PointFeatured::Point2Type     point(1.0, 2.0);
    PointFeatured::ScalarType     confidence = 3.0;
    PointFeatured::DescriptorType desc;
    uint32_t                      dimension = 256;
    desc.resize(dimension);
    for (size_t i = 0; i < 256; i++)
    {
        desc[i] = i * 1.0;
    }

    PointFeatured point_feature1(point, desc, confidence);
    PointFeatured point_feature2(point_feature1);

    // check results
    using EpsilonType = holo::EpsilonT<PointFeatured::ScalarType>;
    ASSERT_NEAR(point_feature1.GetPointPosition().GetX(), point_feature2.GetPointPosition().GetX(), EpsilonType::value);
    ASSERT_NEAR(point_feature1.GetPointPosition().GetY(), point_feature2.GetPointPosition().GetY(), EpsilonType::value);
    ASSERT_NEAR(point_feature1.GetConfidence(), point_feature2.GetConfidence(), EpsilonType::value);
    ASSERT_EQ(point_feature1.GetDescriptorDimension(), point_feature2.GetDescriptorDimension());

    for (size_t i = 0; i < point_feature1.GetDescriptorDimension(); i++)
    {
        ASSERT_NEAR(point_feature1.GetDescriptor().at(i), point_feature2.GetDescriptor().at(i), EpsilonType::value);
    }
}

TEST(PointFeaturef, PointFeatureF32_Serializer_Deserializer_4ByteAligned)
{
    PointFeaturef::Point2Type     point(1.0, 2.0);
    uint32_t                      dimension  = 256;
    PointFeaturef::ScalarType     confidence = 3.0;
    PointFeaturef::DescriptorType desc;
    desc.resize(dimension);
    for (size_t i = 0; i < 256; i++)
    {
        desc[i] = i * 1.0;
    }

    PointFeaturef input_point_feature(point, desc, confidence);
    PointFeaturef output_point_feature;

    static const uint32_t SERIALIZED_BUF_LEN = 8192U;

    holo::utils::FixedSizeBuffer<SERIALIZED_BUF_LEN, 4> buf0;
    holo::utils::FixedSizeBuffer<SERIALIZED_BUF_LEN, 4> buf1;
    holo::utils::FixedSizeBuffer<32, 4>                 buf_short;
    holo::utils::Serializer<true, 4>                    serializer0(buf0);
    holo::utils::Serializer<true, 4>                    serializer1(buf1);
    holo::utils::Serializer<true, 4>                    serializer_short(buf_short);
    uint32_t                                            serialization_result   = 0U;
    uint32_t                                            deserialization_result = 0U;
    uint32_t                                            expected_size = input_point_feature.GetSerializedSize<4U>();
    try
    {
        serialization_result = (serializer0 << input_point_feature).Tellp();
    }
    catch (holo::exception::SerializationBufferOverflowException& e)
    {
        ASSERT_EQ(e.GetSize(), 0U);
    }
    catch (...)
    {
        FAIL() << "serialization Unexpected exception caught";
    }
    holo::utils::Deserializer<true, 4> deserializer(serializer0);
    try
    {
        deserialization_result = (deserializer >> output_point_feature).Tellg();
    }
    catch (holo::exception::DeserializationBufferUnderflowException& e)
    {
        ASSERT_LE(e.GetSize(), expected_size);
    }
    catch (...)
    {
        FAIL() << "deserialization Unexpected exception caught";
    }
    ASSERT_EQ(expected_size, serialization_result);
    ASSERT_EQ(deserialization_result, serialization_result);
    ASSERT_TRUE(input_point_feature.GetPointPosition() == output_point_feature.GetPointPosition());
    std::cout << "input size: " << input_point_feature.GetDescriptorDimension()
              << " output size: " << output_point_feature.GetDescriptorDimension() << std::endl;
    ASSERT_TRUE(input_point_feature.GetDescriptorDimension() == output_point_feature.GetDescriptorDimension());
    for (size_t i = 0; i < dimension; i++)
    {
        ASSERT_TRUE(input_point_feature.GetDescriptor()[i] == output_point_feature.GetDescriptor()[i]);
    }
    ASSERT_TRUE(input_point_feature.GetConfidence() == output_point_feature.GetConfidence());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
