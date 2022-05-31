/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_road_category_type_description.cpp
 * @brief unit test for road_category type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-12-10
 */

#include <gtest/gtest.h>
#include <holo/metadata/common/road_category_type_description.h>

TEST(TypeDescription, RoadCategory)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::RoadCategory>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

TEST(TypeDescription, LaneCategory)
{
    auto desc = holo::metadata::TypeDescriptionResolver<holo::common::LaneCategory>::Get();
    EXPECT_EQ("bitfield<holo::common::LaneCategory>", desc->GetName());
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
