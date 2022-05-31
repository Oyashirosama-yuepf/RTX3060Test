/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_road_frame_type_description.cpp
 * @brief unit test for road_frame type descriptions
 * @author zhouhuishuang@holomatic.com
 * @date 2021-01-28
 */

#include <gtest/gtest.h>
#include <holo/metadata/common/road_frame_type_description.h>
#include <holo/metadata/geometry/curve_type_description.h>

using ScalarType       = holo::float64_t;
using PointType        = holo::geometry::Point2T<ScalarType>;
using CurveType        = holo::geometry::CurvePolynomial<PointType, 64U, 3U>;
using CurveTypePol     = holo::numerics::Polynomial<ScalarType, 3U>;
using RoadFrameType    = holo::common::RoadFrame<CurveType>;
using RoadFramePolType = holo::common::RoadFrame<CurveTypePol>;

TEST(TypeDescription, RoadFrameT)
{
    auto desc = holo::metadata::TypeDescriptionResolver<RoadFrameType>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}

TEST(TypeDescription, RoadFramePolynomialT)
{
    auto desc = holo::metadata::TypeDescriptionResolver<RoadFramePolType>::Get();
    std::cout << desc->PrintToString(2) << std::endl;
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
