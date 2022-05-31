/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_point_feature_list_smb_writer.h
 * @brief Unit test for class PointFeatureListSMBWriter
 * @author guopeikai(guopeikai@holomaitc.com)
 * @date 2021-04-29
 */

#include <gtest/gtest.h>

#include <holo/core/epsilon.h>
#include <holo/common/sensor_id.h>
#include <holo/parking/vision/point_feature_list_smb.h>

using namespace holo::parking::vision;

TEST(PointFeatureListSMB, PointFeatureListSMB_WRITER)
{
    PointFeatureListSMBWriter point_feature_list_smb_writer("mlc_666", 4);

    uint32_t sec   = 300U;
    uint32_t conut = 0;
    while (true)
    {
        auto data_ptr_and_index = point_feature_list_smb_writer.GetSMBBlockPtrAndWriterIndexToSetData();
        PointFeaturefList_ST* input_point_feature_list = data_ptr_and_index.first;

        const int real_num                       = 500;
        input_point_feature_list->timestamp.sec  = sec++;
        input_point_feature_list->timestamp.nsec = 100U;
        input_point_feature_list->sensor_id      = holo::common::SensorId(15U);
        input_point_feature_list->size           = real_num;

        for (size_t i = 0; i < real_num; i++)
        {
            input_point_feature_list->point_features[i].position.x = 1.0;
            input_point_feature_list->point_features[i].position.y = 2.0;
            input_point_feature_list->point_features[i].dimension  = 128;
            input_point_feature_list->point_features[i].confidence = 3.0;

            for (size_t j = 0; j < 128; j++)
            {
                input_point_feature_list->point_features[i].descriptor[j] = j * 1.0;
            }
        }

        usleep(200000);
        std::cout << "the write msg sec is: " << sec - 1 << "\n";
        std::cout << "write msg num : " << ++conut << "\n";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}