/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_gridding_feature_extractor.cpp
 * @brief test gridding feature extractor class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-10"
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/feature/fast.h>
#include <holo/localization/vision/feature/gridding_feature_extractor.h>

using GriddingFeatureExtractor = holo::localization::GriddingFeatureExtractor;
using Feature2DBase            = holo::localization::Feature2DBase;
using FAST                     = holo::localization::FAST;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GriddingFeatureExtractor_Parameters, normal)
{
    Feature2DBase::Ptr                   feature_ptr(new Feature2DBase());
    GriddingFeatureExtractor::Parameters parameters(feature_ptr, 400u, 300u, 200u, 100u, 10u);
    ASSERT_EQ(feature_ptr, parameters.feature_ptr);
    ASSERT_EQ(400u, parameters.image_size.GetWidth());
    ASSERT_EQ(300u, parameters.image_size.GetHeight());
    ASSERT_EQ(200u, parameters.grid_x);
    ASSERT_EQ(100u, parameters.grid_y);
    ASSERT_EQ(2u, parameters.grid_cols);
    ASSERT_EQ(3u, parameters.grid_rows);
    ASSERT_EQ(10u, parameters.min_feature_distance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GriddingFeatureExtractor_Parameters, boundary)
{
    Feature2DBase::Ptr                   feature_ptr(new Feature2DBase());
    GriddingFeatureExtractor::Parameters parameters(feature_ptr, 400u, 300u, 0u, 301u, 10u);
    ASSERT_EQ(feature_ptr, parameters.feature_ptr);
    ASSERT_EQ(400u, parameters.image_size.GetWidth());
    ASSERT_EQ(300u, parameters.image_size.GetHeight());
    ASSERT_EQ(400u, parameters.grid_x);
    ASSERT_EQ(300u, parameters.grid_y);
    ASSERT_EQ(1u, parameters.grid_cols);
    ASSERT_EQ(1u, parameters.grid_rows);
    ASSERT_EQ(10u, parameters.min_feature_distance);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GriddingFeatureExtractor_Parameters, exception)
{
    /* invalid feature detector pointer */
    ASSERT_THROW(GriddingFeatureExtractor::Parameters(nullptr, 300u, 300u, 100u, 100u, 10u), std::runtime_error);

    /* invalid image size */
    Feature2DBase::Ptr feature_ptr(new Feature2DBase());
    ASSERT_THROW(GriddingFeatureExtractor::Parameters(feature_ptr, 0u, 0u, 100u, 100u, 10u), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GriddingFeatureExtractor, Image)
{
    /* constuct gridding feature extractor */
    Feature2DBase::Ptr                   feature_ptr(new Feature2DBase());
    GriddingFeatureExtractor::Parameters parameters(feature_ptr, 200u, 200u, 100u, 100u, 0u);
    GriddingFeatureExtractor             gridding_feature_extractor(parameters);

    /* check empty image */
    GriddingFeatureExtractor::Mat                     empty_image;
    std::vector<GriddingFeatureExtractor::KeyPoint2f> keypoints;
    std::vector<GriddingFeatureExtractor::Descriptor> descriptors;
    ASSERT_FALSE(gridding_feature_extractor.Detect(empty_image, keypoints));
    ASSERT_FALSE(gridding_feature_extractor.Compute(empty_image, keypoints, descriptors));
    ASSERT_FALSE(gridding_feature_extractor.DetectAndCompute(empty_image, keypoints, descriptors));

    /* check image size */
    GriddingFeatureExtractor::Mask image1(100u, 200u);  /// < wrong width
    ASSERT_FALSE(gridding_feature_extractor.Detect(image1, keypoints));
    ASSERT_FALSE(gridding_feature_extractor.DetectAndCompute(image1, keypoints, descriptors));

    GriddingFeatureExtractor::Mask image2(200u, 100u);  /// < wrong height
    ASSERT_FALSE(gridding_feature_extractor.Detect(image2, keypoints));
    ASSERT_FALSE(gridding_feature_extractor.DetectAndCompute(image2, keypoints, descriptors));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GriddingFeatureExtractor, DetectAndComputeWithFeature2DBase)
{
    /* constuct gridding feature extractor */
    Feature2DBase::Ptr                   feature_ptr(new Feature2DBase());
    GriddingFeatureExtractor::Parameters parameters(feature_ptr, 200u, 200u, 100u, 100u, 10u);
    GriddingFeatureExtractor             gridding_feature_extractor(parameters);

    /// @brief use mask to construct a image because we can operate on Mat directly
    GriddingFeatureExtractor::Mask                    image(200u, 200u, 0u);
    std::vector<GriddingFeatureExtractor::KeyPoint2f> keypoints;
    std::vector<GriddingFeatureExtractor::Descriptor> descriptors;

    uint16_t step = 30u;  /// < the step size between the point

    for (uint16_t i = 1u; i < 7u; i++)
    {
        for (uint16_t j = 1u; j < 7u; j++)
        {
            image.At(i * step, j * step) = 255u;
        }
    }

    ASSERT_FALSE(gridding_feature_extractor.Detect(image, keypoints, 10u));  /// < failed to detect
                                                                             /// features
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GriddingFeatureExtractor, DetectAndComputeWithFAST)
{
    /* constuct gridding feature extractor */
    Feature2DBase::Ptr                   feature_ptr(new FAST(10, true, FAST::Type::TYPE_9_16));
    GriddingFeatureExtractor::Parameters parameters(feature_ptr, 200u, 200u, 100u, 100u, 10u);
    GriddingFeatureExtractor             gridding_feature_extractor(parameters);

    /// @brief use mask to construct a image because we can operate on Mat directly
    GriddingFeatureExtractor::Mask                    image(200u, 200u, 0u);
    std::vector<GriddingFeatureExtractor::KeyPoint2f> keypoints;
    std::vector<GriddingFeatureExtractor::Descriptor> descriptors;

    ASSERT_FALSE(gridding_feature_extractor.Detect(image, keypoints, 10u));  /// < detected 0 features

    uint16_t step = 30u;  /// < the step size between the point

    for (uint16_t i = 1u; i < 7u; i++)
    {
        for (uint16_t j = 1u; j < 7u; j++)
        {
            image.At(i * step, j * step) = 255u;
        }
    }

    ASSERT_FALSE(gridding_feature_extractor.Detect(image, keypoints, 0u));  /// < 0 features
    ASSERT_FALSE(
        gridding_feature_extractor.DetectAndCompute(image, keypoints, descriptors, 0u, true, true));  /// < 0 features
    ASSERT_FALSE(gridding_feature_extractor.DetectAndCompute(image, keypoints, descriptors, 1000u, false,
                                                             false));        /// < do nothing
    ASSERT_TRUE(gridding_feature_extractor.Detect(image, keypoints, 300u));  /// < detect 36 features
    ASSERT_EQ(36u, keypoints.size());

    ASSERT_TRUE(gridding_feature_extractor.Detect(image, keypoints, 3u));  /// < limit keypoints with max_num_features
    ASSERT_EQ(3u, keypoints.size());

    keypoints.clear();
    ASSERT_FALSE(gridding_feature_extractor.DetectAndCompute(image, keypoints, descriptors, 10u, false,
                                                             true));  /// < compute without keypoints and return false
    keypoints.resize(1u);
    ASSERT_FALSE(gridding_feature_extractor.DetectAndCompute(image, keypoints, descriptors, 10u, false,
                                                             true));  /// < failed to compute descriptors
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
