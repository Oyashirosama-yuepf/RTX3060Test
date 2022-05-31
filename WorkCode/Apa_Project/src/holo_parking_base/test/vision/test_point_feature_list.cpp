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
#include <holo/parking/vision/point_feature_list.h>
#include <holo/serialization/serialization.h>
#include <holo/utils/serialization_exception.h>
#include <holo/utils/serializer.h>
#include <holo/utils/deserializer.h>
#include <holo/utils/buffer.h>

using namespace holo::parking::vision;

TEST(PointFeatureListf, PointFeatureListF32_Serializer_Deserializer_4ByteAligned)
{
    PointFeaturePtrListf input_point_feature_list, output_point_feature_list;
    input_point_feature_list.SetTimestamp(holo::Timestamp(300U, 100U));
    input_point_feature_list.SetSensorId(holo::common::SensorId(15U));
    PointFeaturePtrListf::PointFeaturePtrListType point_feature_list_ptrs;
    const int                                     real_num = 2;
    point_feature_list_ptrs.resize(real_num);
    input_point_feature_list.SetSize(real_num);

    for (size_t i = 0; i < real_num; i++)
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
        point_feature_list_ptrs[i] = std::make_shared<PointFeaturef>(input_point_feature);
    }
    input_point_feature_list.SetPointFeatureList(point_feature_list_ptrs);

    static const uint32_t SERIALIZED_BUF_LEN = 8192U;

    holo::utils::FixedSizeBuffer<SERIALIZED_BUF_LEN, 4> buf0;
    holo::utils::FixedSizeBuffer<SERIALIZED_BUF_LEN, 4> buf1;
    holo::utils::FixedSizeBuffer<32, 4>                 buf_short;
    holo::utils::Serializer<true, 4>                    serializer0(buf0);
    holo::utils::Serializer<true, 4>                    serializer1(buf1);
    holo::utils::Serializer<true, 4>                    serializer_short(buf_short);
    uint32_t                                            serialization_result   = 0U;
    uint32_t                                            deserialization_result = 0U;
    uint32_t expected_size = input_point_feature_list.GetSerializedSize<4U>();
    try
    {
        serialization_result = (serializer0 << input_point_feature_list).Tellp();
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
        deserialization_result = (deserializer >> output_point_feature_list).Tellg();
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
    ASSERT_TRUE(input_point_feature_list.GetTimestamp() == output_point_feature_list.GetTimestamp());
    ASSERT_TRUE(input_point_feature_list.GetSensorId() == output_point_feature_list.GetSensorId());
    ASSERT_TRUE(input_point_feature_list.GetSize() == output_point_feature_list.GetSize());

    PointFeaturePtrListf::PointFeaturePtrListType input_point_feature_list_ptrs, output_point_feature_list_ptrs;
    input_point_feature_list_ptrs  = input_point_feature_list.GetPointFeatureList();
    output_point_feature_list_ptrs = output_point_feature_list.GetPointFeatureList();

    for (size_t i = 0; i < real_num; i++)
    {
        ASSERT_TRUE(input_point_feature_list_ptrs[i]->GetPointPosition() ==
                    output_point_feature_list_ptrs[i]->GetPointPosition());

        ASSERT_TRUE(input_point_feature_list_ptrs[i]->GetDescriptorDimension() ==
                    output_point_feature_list_ptrs[i]->GetDescriptorDimension());
        for (size_t j = 0; j < 256; j++)
        {
            ASSERT_TRUE(input_point_feature_list_ptrs[i]->GetDescriptor()[j] ==
                        output_point_feature_list_ptrs[i]->GetDescriptor()[j]);
        }
        ASSERT_TRUE(input_point_feature_list_ptrs[i]->GetConfidence() ==
                    output_point_feature_list_ptrs[i]->GetConfidence());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
