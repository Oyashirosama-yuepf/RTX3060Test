/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_road_speed_limits_type_description.cpp
 * @brief unit test for road speed limits type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-23
 */

#include <gtest/gtest.h>
#include <holo/metadata/map/road_speed_limits_type_description.h>

TEST(TypeDescription, RoadSpeedLimits)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::map::RoadSpeedLimits>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
