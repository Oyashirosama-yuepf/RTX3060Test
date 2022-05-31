/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_imu_bias_type_description.cpp
 * @brief unit test for imu bias type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-03
 */

#include <gtest/gtest.h>
#include <holo/metadata/common/imu_bias_type_description.h>

TEST(TypeDescription, Imuf)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::details::ImuBiasT<holo::float32_t>>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
