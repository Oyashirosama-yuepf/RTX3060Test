/**
 * @file test_feature2d.cpp
 * @brief test feature2d class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-06"
 */

#include <gtest/gtest.h>
#include <holo/localization/vision/feature/feature2d.h>

using DescriptorType = holo::localization::DescriptorType;
using Descriptor     = holo::localization::Descriptor;
using Feature2DBase  = holo::localization::Feature2DBase;
using Mat            = Feature2DBase::Mat;
using KeyPoint2f     = Feature2DBase::KeyPoint2f;
using Mask           = Feature2DBase::Mask;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Feature2DBase, basic)
{
    Feature2DBase feature2d_base;

    ASSERT_EQ(DescriptorType::UNKNOWN, feature2d_base.GetDescriptorType());
    ASSERT_EQ(0u, feature2d_base.GetDescriptorSize());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Feature2DBase, detect_and_compute)
{
    Feature2DBase feature2d_base;

    Mat                     image;
    Mask                    mask;
    std::vector<KeyPoint2f> keypoints;
    std::vector<Descriptor> descriptors;

    ASSERT_FALSE(feature2d_base.Detect(image, keypoints, holo::OptionalT<Mask>(mask)));
    ASSERT_FALSE(feature2d_base.Detect(image, keypoints));
    ASSERT_FALSE(feature2d_base.Compute(image, keypoints, descriptors));
    ASSERT_FALSE(
        feature2d_base.DetectAndCompute(image, keypoints, descriptors, true, true, holo::OptionalT<Mask>(mask)));
    ASSERT_FALSE(feature2d_base.DetectAndCompute(image, keypoints, descriptors, true, true));
    ASSERT_FALSE(feature2d_base.DetectAndCompute(image, keypoints, descriptors, true, false));
    ASSERT_FALSE(feature2d_base.DetectAndCompute(image, keypoints, descriptors, false, true));
    ASSERT_FALSE(feature2d_base.DetectAndCompute(image, keypoints, descriptors, false, false));

    /* keypoints is not empty */
    keypoints.resize(1u);
    ASSERT_FALSE(feature2d_base.DetectAndCompute(image, keypoints, descriptors, false, true));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
