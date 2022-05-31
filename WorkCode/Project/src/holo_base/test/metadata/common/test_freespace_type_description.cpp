/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_freespace_type_description.cpp
 * @brief unit test for freespace type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-02-05
 */

#include <gtest/gtest.h>
#include <holo/common/freespace.h>
#include <holo/geometry/point2.h>
#include <holo/metadata/common/freespace_type_description.h>
#include <holo/metadata/geometry/point2_type_description.h>

using FreespaceInteriorPolygon =
    holo::common::details::FreespaceInteriorPolygon<holo::geometry::Point2T<holo::float32_t>, 32U>;
using FreespaceExteriorPolygon =
    holo::common::details::FreespaceExteriorPolygon<holo::geometry::Point2T<holo::float32_t>, 32U, 5U>;
using Freespace = holo::common::details::Freespace<holo::geometry::Point2T<holo::float32_t>, 32U>;

TEST(TypeDescription, FreespaceInteriorPolygon)
{
    auto desc = holo::metadata::TypeDescriptionResolver<FreespaceInteriorPolygon>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

TEST(TypeDescription, FreespaceExteriorPolygon)
{
    auto desc = holo::metadata::TypeDescriptionResolver<FreespaceExteriorPolygon>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

TEST(TypeDescription, Freespace)
{
    auto desc = holo::metadata::TypeDescriptionResolver<Freespace>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
