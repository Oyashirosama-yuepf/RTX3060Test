/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_segmentation_2d.cpp
 * @brief This file test Segmentation2DT.
 * @author liufangyuan(liufangyuan@holomaitc.com)
 * @date "2019-12-26"
 */

#include <gtest/gtest.h>

#include <holo/common/segmentation_2d.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Segmentation2DUnintTest, Struct_Info)
{
    const holo::common::SensorId      sensor_id(1U);
    const uint32_t                    num_classes = 2U;
    const uint32_t                    height      = 100U;
    const uint32_t                    width       = 200U;
    const holo::Segmentation2Df::Info info        = {sensor_id, num_classes, height, width};

    ASSERT_EQ(info.sensor_id, sensor_id);
    ASSERT_EQ(info.num_classes, num_classes);
    ASSERT_EQ(info.height, height);
    ASSERT_EQ(info.width, width);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Segmentation2DUnintTest, Struct_SemanticSegment)
{
    // create a traffic board
    const holo::Segmentation2Df::CategoryId category_id = holo::Segmentation2Df::CategoryId::BACK_GROUND;
    const holo::Segmentation2Df::InstanceId instance_id = 0U;
    const holo::Segmentation2Df::Confidence confidence  = 0.9f;

    // create some points
    const holo::geometry::Point2f pt_0(0.0f, 0.0f);
    const holo::geometry::Point2f pt_1(0.0f, 10.0f);
    const holo::geometry::Point2f pt_2(10.1f, 0.0f);
    const holo::geometry::Point2f pt_3(10.0f, 10.1f);

    // create contours
    const holo::Segmentation2Df::Contour  contour  = {pt_0, pt_1, pt_2, pt_3};
    const holo::Segmentation2Df::Contours contours = {contour};

    // create semantic segmentations
    const holo::Segmentation2Df::SemanticSegment  semantic_segment  = {category_id, instance_id, confidence, contours};
    const holo::Segmentation2Df::SemanticSegments semantic_segments = {semantic_segment};

    // create segmentation 2d with traffic board and default stamp,info,
    const holo::common::Timestamp             stamp;
    const holo::Segmentation2Df::Info info = {0U, 0U, 0U, 0U};
    const holo::Segmentation2Df       segmentation_2d(stamp, info, semantic_segments);

    ASSERT_EQ(segmentation_2d.semantic_segments().back().category_id, category_id);
    ASSERT_EQ(segmentation_2d.semantic_segments().back().instance_id, instance_id);
    ASSERT_EQ(segmentation_2d.semantic_segments().back().confidence, confidence);
    ASSERT_TRUE(segmentation_2d.semantic_segments().back().contours.back()[0].IsEqual(pt_0));
    ASSERT_TRUE(segmentation_2d.semantic_segments().back().contours.back()[1].IsEqual(pt_1));
    ASSERT_TRUE(segmentation_2d.semantic_segments().back().contours.back()[2].IsEqual(pt_2));
    ASSERT_TRUE(segmentation_2d.semantic_segments().back().contours.back()[3].IsEqual(pt_3));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Segmentation2DUnintTest, Timestamp)
{
    // create a traffic board
    const holo::Segmentation2Df::CategoryId category_id = holo::Segmentation2Df::CategoryId::BACK_GROUND;
    const holo::Segmentation2Df::InstanceId instance_id = 0U;
    const holo::Segmentation2Df::Confidence confidence  = 0.9f;

    // create some points
    const holo::geometry::Point2f pt_0(0.0f, 0.0f);
    const holo::geometry::Point2f pt_1(0.0f, 10.0f);
    const holo::geometry::Point2f pt_2(10.1f, 0.0f);
    const holo::geometry::Point2f pt_3(10.0f, 10.1f);

    // create contours
    const holo::Segmentation2Df::Contour  contour  = {pt_0, pt_1, pt_2, pt_3};
    const holo::Segmentation2Df::Contours contours = {contour};

    // create semantic segmentations
    const holo::Segmentation2Df::SemanticSegment  semantic_segment  = {category_id, instance_id, confidence, contours};
    const holo::Segmentation2Df::SemanticSegments semantic_segments = {semantic_segment};

    // create segmentation 2d with traffic board and default stamp,info,
    const holo::common::Timestamp             stamp(100U, 200U);
    const holo::Segmentation2Df::Info info = {0U, 0U, 0U, 0U};
    holo::Segmentation2Df             segmentation_2d(stamp, info, semantic_segments);

    ASSERT_EQ(segmentation_2d.GetTimestamp().ToString(), stamp.ToString());

    const holo::common::Timestamp stamp1(100U, 200U);
    segmentation_2d.SetTimestamp(stamp1);
    ASSERT_EQ(segmentation_2d.GetTimestamp().ToString(), stamp1.ToString());

    const holo::Segmentation2Df segmentation_2d2(stamp, info, semantic_segments);
    ASSERT_EQ(segmentation_2d2.GetTimestamp().ToString(), stamp1.ToString());
}

TEST(Segmentation2DUnintTest, info)
{
    // create a traffic board
    const holo::Segmentation2Df::CategoryId category_id = holo::Segmentation2Df::CategoryId::BACK_GROUND;
    const holo::Segmentation2Df::InstanceId instance_id = 0U;
    const holo::Segmentation2Df::Confidence confidence  = 0.9f;

    // create some points
    const holo::geometry::Point2f pt_0(0.0f, 0.0f);
    const holo::geometry::Point2f pt_1(0.0f, 10.0f);
    const holo::geometry::Point2f pt_2(10.1f, 0.0f);
    const holo::geometry::Point2f pt_3(10.0f, 10.1f);

    // create contours
    const holo::Segmentation2Df::Contour  contour  = {pt_0, pt_1, pt_2, pt_3};
    const holo::Segmentation2Df::Contours contours = {contour};

    // create semantic segmentations
    const holo::Segmentation2Df::SemanticSegment  semantic_segment  = {category_id, instance_id, confidence, contours};
    const holo::Segmentation2Df::SemanticSegments semantic_segments = {semantic_segment};

    // create segmentation 2d with traffic board and default stamp,info,
    const holo::common::Timestamp             stamp;
    const holo::Segmentation2Df::Info info = {0U, 0U, 0U, 0U};
    holo::Segmentation2Df       segmentation_2d(stamp, info, semantic_segments);

    holo::Segmentation2Df::Info info2 = segmentation_2d.info();
    segmentation_2d.info(info2);
    segmentation_2d.info(std::move(info2));

    const holo::Segmentation2Df segmentation_2d2(stamp, info, semantic_segments);
    ASSERT_EQ(segmentation_2d2.info().width, info.width);
}

TEST(Segmentation2DUnintTest, semantic_segments)
{
    // create a traffic board
    const holo::Segmentation2Df::CategoryId category_id = holo::Segmentation2Df::CategoryId::BACK_GROUND;
    const holo::Segmentation2Df::InstanceId instance_id = 0U;
    const holo::Segmentation2Df::Confidence confidence  = 0.9f;

    // create some points
    const holo::geometry::Point2f pt_0(0.0f, 0.0f);
    const holo::geometry::Point2f pt_1(0.0f, 10.0f);
    const holo::geometry::Point2f pt_2(10.1f, 0.0f);
    const holo::geometry::Point2f pt_3(10.0f, 10.1f);

    // create contours
    const holo::Segmentation2Df::Contour  contour  = {pt_0, pt_1, pt_2, pt_3};
    const holo::Segmentation2Df::Contours contours = {contour};

    // create semantic segmentations
    const holo::Segmentation2Df::SemanticSegment  semantic_segment  = {category_id, instance_id, confidence, contours};
    const holo::Segmentation2Df::SemanticSegments semantic_segments = {semantic_segment};

    // create segmentation 2d with traffic board and default stamp,info,
    const holo::common::Timestamp             stamp;
    const holo::Segmentation2Df::Info info = {0U, 0U, 0U, 0U};
    holo::Segmentation2Df       segmentation_2d(stamp, info, semantic_segments);

    auto sem = segmentation_2d.semantic_segments();
    segmentation_2d.semantic_segments(sem);
    segmentation_2d.semantic_segments(std::move(sem));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
