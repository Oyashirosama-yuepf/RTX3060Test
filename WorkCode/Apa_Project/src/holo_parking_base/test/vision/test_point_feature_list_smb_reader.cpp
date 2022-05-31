/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_point_feature_list_smb_reader.h
 * @brief Unit test for class PointFeatureListSMBReader
 * @author guopeikai(guopeikai@holomaitc.com)
 * @date 2021-04-29
 */

#include <gtest/gtest.h>

#include <gtest/gtest.h>

#include <holo/core/epsilon.h>
#include <holo/common/sensor_id.h>
#include <holo/parking/vision/point_feature_list_smb.h>

using namespace holo::parking::vision;

TEST(PointFeatureListSMB, PointFeatureListSMB_READER)
{
    PointFeaturefList_ST* output_point_feature_list = nullptr;
    std::cout << "begin to init smb ...\n";
    PointFeatureListSMBReader point_feature_list_smb("mlc_666");
    uint32_t                  conut = 0;
    usleep(100000);
    while (true)
    {
        for (int i = 0; i < 4; ++i)
        {
            output_point_feature_list = point_feature_list_smb.GetPointFeatureListDataPtr(i);
            std::cout << "buffer size: " << sizeof(output_point_feature_list) << std::endl;
            std::cout << "timestamp: " << output_point_feature_list->timestamp.sec << " "
                      << output_point_feature_list->timestamp.nsec << "\n";
            std::cout << "list size: " << output_point_feature_list->size << std::endl;
            std::cout << "sensor id: " << output_point_feature_list->sensor_id << std::endl;

            std::cout << "read msg num : " << ++conut << "\n";
        }
        usleep(200000);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}