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
#include <holo/parking/vision/point_feature_list_ipc.h>
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
    const int                                     real_num = 500;
    point_feature_list_ptrs.resize(real_num);
    input_point_feature_list.SetSize(real_num);

    for (size_t i = 0; i < real_num; i++)
    {
        PointFeaturef::Point2Type     point(1.0, 2.0);
        uint32_t                      dimension  = 128;
        PointFeaturef::ScalarType     confidence = 3.0;
        PointFeaturef::DescriptorType desc;
        desc.resize(dimension);
        for (size_t i = 0; i < 128; i++)
        {
            desc[i] = i * 1.0;
        }

        PointFeaturef input_point_feature(point, desc, confidence);
        point_feature_list_ptrs[i] = std::make_shared<PointFeaturef>(input_point_feature);
    }

    input_point_feature_list.SetPointFeatureList(point_feature_list_ptrs);

    PointFeatureListIpc point_feature_list_ipc_server(holo::common::SensorId(123456));
    PointFeatureListIpc point_feature_list_ipc_client(holo::common::SensorId(123456));
    while (true)
    {
        point_feature_list_ipc_server.SetPointFeatureListData(input_point_feature_list);
        point_feature_list_ipc_client.GetPointFeatureListData(output_point_feature_list);
        std::cout << "buffer size: " << output_point_feature_list.GetSerializedSize() << std::endl;
        std::cout << "timestamp: " << output_point_feature_list.GetTimestamp().ToString() << std::endl;
        std::cout << "list size: " << output_point_feature_list.GetSize() << std::endl;
        std::cout << "sensor id: " << output_point_feature_list.GetSensorId() << std::endl;
        // for (size_t i = 0; i < output_point_feature_list.GetSize(); i++)
        // {
        //     const auto& point_feature = output_point_feature_list.GetPointFeatureList()[i];
        //     std::cout << point_feature->GetPointPosition() << std::endl;
        //     std::cout << point_feature->GetDescriptorDimension() << std::endl;
        //     for (size_t j = 0; j < point_feature->GetDescriptorDimension(); j++)
        //     {
        //         std::cout << "des: " << point_feature->GetDescriptor().at(j) << std::endl;
        //     }
        //     std::cout << "confidence: " << point_feature->GetConfidence() << std::endl;
        // }
        usleep(200000);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}