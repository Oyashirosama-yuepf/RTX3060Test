/*!
 * \brief Unit test for descriptor matcher in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date 2019-Dec-12
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <time.h>
#include <random>

#include <gtest/gtest.h>

#define private public
#include <vision/vslam/fixtures/descriptor_matcher_fixture.h>

namespace vslam = holo::localization::vision::vslam;

///////////////////////////////////////////////////////////////////////////////
TEST(DescriptorMatcher, DescriptorDistance)
{
    // construct three descriptor.[1, 0], [0, 1], and [-1, 0]
    cv::Mat d1 = cv::Mat::zeros(1, 2, CV_32FC1);
    d1.col(0)  = 1;

    cv::Mat d2 = cv::Mat::zeros(1, 2, CV_32FC1);
    d2.col(1)  = 1;

    cv::Mat d3 = cv::Mat::zeros(1, 2, CV_32FC1);
    d3.col(0)  = -1;

    // check result
    const auto dist11 = vslam::DescriptorMatcher::DescriptorDistance(d1, d1);
    ASSERT_FLOAT_EQ(dist11, 0);

    const auto dist12 = vslam::DescriptorMatcher::DescriptorDistance(d1, d2);
    ASSERT_FLOAT_EQ(dist12, std::sqrt(2));

    const auto dist13 = vslam::DescriptorMatcher::DescriptorDistance(d1, d3);
    ASSERT_FLOAT_EQ(dist13, 2);

    const auto dist23 = vslam::DescriptorMatcher::DescriptorDistance(d2, d3);
    ASSERT_FLOAT_EQ(dist23, std::sqrt(2));

    // throw case
    d3.col(1) = 1;
    ASSERT_THROW(vslam::DescriptorMatcher::DescriptorDistance(d2, d3),
                 std::runtime_error);  /// < descriptor was not normalized.
}

///////////////////////////////////////////////////////////////////////////////
TEST(DescriptorMatcher, OneToOneFiltering)
{
    // construct many-to-one matching result
    std::unordered_map<uint16_t, std::pair<uint16_t, vslam::Scalar>> many_to_one_match_result;
    many_to_one_match_result.emplace(0, std::make_pair(0, 0.0));
    many_to_one_match_result.emplace(1, std::make_pair(0, 0.1));
    many_to_one_match_result.emplace(3, std::make_pair(0, 0.3));
    many_to_one_match_result.emplace(4, std::make_pair(0, 0.4));

    many_to_one_match_result.emplace(8, std::make_pair(1, 0.0));
    many_to_one_match_result.emplace(7, std::make_pair(1, 0.1));
    many_to_one_match_result.emplace(6, std::make_pair(1, 0.3));
    many_to_one_match_result.emplace(5, std::make_pair(1, 0.4));

    many_to_one_match_result.emplace(9, std::make_pair(2, 0.0));
    many_to_one_match_result.emplace(10, std::make_pair(2, 0.1));
    many_to_one_match_result.emplace(11, std::make_pair(2, 0.3));
    many_to_one_match_result.emplace(12, std::make_pair(2, 0.4));

    many_to_one_match_result.emplace(66, std::make_pair(3, 0.0));
    many_to_one_match_result.emplace(30, std::make_pair(3, 0.1));
    many_to_one_match_result.emplace(78, std::make_pair(3, 0.3));
    many_to_one_match_result.emplace(33, std::make_pair(3, 0.4));

    const auto match_pairs = vslam::DescriptorMatcher::OneToOneFiltering(many_to_one_match_result);

    // check result
    ASSERT_TRUE(match_pairs.size() == 4);

    std::vector<std::pair<uint16_t, uint16_t>> result;
    for (const auto& pair : match_pairs)
    {
        result.emplace_back(std::make_pair(pair.first, pair.second));
    }

    // sort
    std::sort(result.begin(), result.end(),
              [](std::pair<uint16_t, uint16_t> a, std::pair<uint16_t, uint16_t> b) { return a.first < b.first; });

    // ont-to-one best match result: 0-0; 8-1;9-2; 66-3;
    ASSERT_EQ(result[0].first, 0);
    ASSERT_EQ(result[0].second, 0);

    ASSERT_EQ(result[1].first, 8);
    ASSERT_EQ(result[1].second, 1);

    ASSERT_EQ(result[2].first, 9);
    ASSERT_EQ(result[2].second, 2);

    ASSERT_EQ(result[3].first, 66);
    ASSERT_EQ(result[3].second, 3);
}

///////////////////////////////////////////////////////////////////////////////
TEST(MatchingMessage, Basic)
{
    // construct two descriptor.[1, 0], [0, 1]
    cv::Mat d1 = cv::Mat::zeros(1, 2, CV_32FC1);
    d1.col(0)  = 1;

    cv::Mat d2 = cv::Mat::zeros(1, 2, CV_32FC1);
    d2.col(1)  = 1;

    // construct MatchingMessage
    vslam::MatchingMessage message(d1, 1);

    const vslam::Scalar descriptor_dist_th = 0.1;
    const vslam::Scalar ratio_test_th      = 0.2;

    // check result
    ASSERT_EQ(message.train_index, 1u);
    ASSERT_EQ(message.train_desc.dims, 2u);
    ASSERT_FLOAT_EQ(message.minimum_distance, 999.0);
    ASSERT_FLOAT_EQ(message.minor_distance, 999.0);
    ASSERT_EQ(message.best_query_index, 0u);
    ASSERT_FALSE(message.IsMatchingAcceptable(descriptor_dist_th, ratio_test_th));

    // update message
    message = message.UpdateMessage(message, d2, 2);
    ASSERT_FLOAT_EQ(message.minimum_distance, std::sqrt(2));
    ASSERT_FLOAT_EQ(message.minor_distance, 999.0);
    ASSERT_EQ(message.best_query_index, 2u);
    ASSERT_FALSE(message.IsMatchingAcceptable(descriptor_dist_th, ratio_test_th));

    // update again
    message = message.UpdateMessage(message, d1, 3);
    ASSERT_FLOAT_EQ(message.minimum_distance, 0.0);
    ASSERT_FLOAT_EQ(message.minor_distance, std::sqrt(2));
    ASSERT_EQ(message.best_query_index, 3u);
    ASSERT_TRUE(message.IsMatchingAcceptable(descriptor_dist_th, ratio_test_th));
}

///////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, BruteForceMatching)
{
    // construct two set of descriptors
    std::vector<cv::Mat> desc0;
    desc0.reserve(gt_features0_.size());
    for (size_t i = 0; i < gt_features0_.size(); i++)
    {
        desc0.emplace_back(*(gt_features0_.at(i).optional_descriptor));
    }

    std::vector<cv::Mat> desc1;
    desc1.reserve(gt_features1_.size());
    for (size_t i = 0; i < gt_features1_.size(); i++)
    {
        desc1.emplace_back(*(gt_features1_.at(i).optional_descriptor));
    }

    // call BruteForceMatching
    const vslam::Scalar dist_th       = 0.1;
    const vslam::Scalar ratio_test_th = 0.1;
    auto                match_pair = vslam::DescriptorMatcher::BruteForceMatching(desc0, desc1, dist_th, ratio_test_th);

    // sort
    std::sort(match_pair.begin(), match_pair.end(),
              [](std::pair<uint16_t, uint16_t> a, std::pair<uint16_t, uint16_t> b) { return a.first < b.first; });

    // check result
    ASSERT_EQ(match_pair.size(), 4);
    ASSERT_EQ(match_pair.at(0).first, 0);
    ASSERT_EQ(match_pair.at(0).second, 0);

    ASSERT_EQ(match_pair.at(1).first, 1);
    ASSERT_EQ(match_pair.at(1).second, 1);

    ASSERT_EQ(match_pair.at(2).first, 2);
    ASSERT_EQ(match_pair.at(2).second, 2);

    ASSERT_EQ(match_pair.at(3).first, 3);
    ASSERT_EQ(match_pair.at(3).second, 3);
}

///////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, FlowMatching)
{
    // call FlowMatching()
    const uint16_t      window_size   = 30.0;
    const vslam::Scalar dist_th       = 0.1;
    const vslam::Scalar ratio_test_th = 0.1;
    auto                match_pair =
        vslam::DescriptorMatcher::FlowMatching(gt_features0_, gt_features1_, window_size, dist_th, ratio_test_th);

    // sort
    std::sort(match_pair.begin(), match_pair.end(),
              [](std::pair<uint16_t, uint16_t> a, std::pair<uint16_t, uint16_t> b) { return a.first < b.first; });

    // check result
    ASSERT_EQ(match_pair.size(), 4);
    ASSERT_EQ(match_pair.at(0).first, 0);
    ASSERT_EQ(match_pair.at(0).second, 0);

    ASSERT_EQ(match_pair.at(1).first, 1);
    ASSERT_EQ(match_pair.at(1).second, 1);

    ASSERT_EQ(match_pair.at(2).first, 2);
    ASSERT_EQ(match_pair.at(2).second, 2);

    ASSERT_EQ(match_pair.at(3).first, 3);
    ASSERT_EQ(match_pair.at(3).second, 3);
}

///////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, MappointsToFeaturesMatching)
{
    // call MappointsToFeaturesMatching()
    const uint16_t      window_size        = 30.0;
    const vslam::Scalar descriptor_dist_th = 0.1;
    const vslam::Scalar ratio_test_th      = 0.1;
    const vslam::Scalar view_distance_th   = 10.0;
    const vslam::Scalar view_direction_th  = 10.0;
    auto                match_pair         = vslam::DescriptorMatcher::MappointsToFeaturesMatching(
        std::make_shared<const vslam::Map>(gt_map_), gt_features1_, intrinsic_, gt_pose1_, window_size,
        descriptor_dist_th, ratio_test_th, view_distance_th, view_direction_th, DescriptorMatcher::IsKernelInit());

    // sort
    std::sort(match_pair.begin(), match_pair.end(),
              [](std::pair<uint16_t, uint16_t> a, std::pair<uint16_t, uint16_t> b) { return a.first < b.first; });

    // check result
    ASSERT_EQ(match_pair.size(), 4);
    ASSERT_EQ(match_pair.at(0).first, 0);
    ASSERT_EQ(match_pair.at(0).second, 0);

    ASSERT_EQ(match_pair.at(1).first, 1);
    ASSERT_EQ(match_pair.at(1).second, 1);

    ASSERT_EQ(match_pair.at(2).first, 2);
    ASSERT_EQ(match_pair.at(2).second, 2);

    ASSERT_EQ(match_pair.at(3).first, 3);
    ASSERT_EQ(match_pair.at(3).second, 3);
}

///////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, EpipolarLineMatching)
{
    // construct input data
    vslam::DescriptorMatcher::FeaturesWithObservedPoses data0;
    data0.reserve(gt_features0_.size());
    for (size_t i = 0; i < gt_features0_.size(); i++)
    {
        data0.emplace_back(gt_features0_.at(i), gt_pose0_);
    }

    vslam::DescriptorMatcher::FeaturesWithObservedPoses data1;
    data1.reserve(gt_features1_.size());
    for (size_t i = 0; i < gt_features1_.size(); i++)
    {
        data1.emplace_back(gt_features1_.at(i), gt_pose1_);
    }

    // call EpipolarLineMatching()
    const vslam::Scalar epipolar_dist_th   = 2.0 / intrinsic_.GetK()(0, 0);
    const vslam::Scalar descriptor_dist_th = 0.1;
    const vslam::Scalar ratio_test_th      = 0.1;
    auto match_pair = vslam::DescriptorMatcher::EpipolarLineMatching(data0, data1, epipolar_dist_th, descriptor_dist_th,
                                                                     ratio_test_th);

    // sort
    std::sort(match_pair.begin(), match_pair.end(),
              [](std::pair<uint16_t, uint16_t> a, std::pair<uint16_t, uint16_t> b) { return a.first < b.first; });

    // check result
    ASSERT_EQ(match_pair.size(), 4);
    ASSERT_EQ(match_pair.at(0).first, 0);
    ASSERT_EQ(match_pair.at(0).second, 0);

    ASSERT_EQ(match_pair.at(1).first, 1);
    ASSERT_EQ(match_pair.at(1).second, 1);

    ASSERT_EQ(match_pair.at(2).first, 2);
    ASSERT_EQ(match_pair.at(2).second, 2);

    ASSERT_EQ(match_pair.at(3).first, 3);
    ASSERT_EQ(match_pair.at(3).second, 3);
}

///////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, EpipolarLineMatching2)
{
    // pure rotation, degenerated case
    // construct input data
    vslam::DescriptorMatcher::FeaturesWithObservedPoses data0;
    data0.reserve(gt_features0_.size());
    for (size_t i = 0; i < gt_features0_.size(); i++)
    {
        data0.emplace_back(gt_features0_.at(i), gt_pose0_);
    }

    vslam::DescriptorMatcher::FeaturesWithObservedPoses data1;
    data1.reserve(gt_features2_.size());
    for (size_t i = 0; i < gt_features2_.size(); i++)
    {
        data1.emplace_back(gt_features2_.at(i), gt_pose2_);
    }

    // call EpipolarLineMatching()
    const vslam::Scalar epipolar_dist_th   = 2.0 / intrinsic_.GetK()(0, 0);
    const vslam::Scalar descriptor_dist_th = 0.1;
    const vslam::Scalar ratio_test_th      = 0.1;
    auto match_pair = vslam::DescriptorMatcher::EpipolarLineMatching(data0, data1, epipolar_dist_th, descriptor_dist_th,
                                                                     ratio_test_th);

    // sort
    std::sort(match_pair.begin(), match_pair.end(),
              [](std::pair<uint16_t, uint16_t> a, std::pair<uint16_t, uint16_t> b) { return a.first < b.first; });

    // check result
    ASSERT_EQ(match_pair.size(), 4);
    ASSERT_EQ(match_pair.at(0).first, 0);
    ASSERT_EQ(match_pair.at(0).second, 0);

    ASSERT_EQ(match_pair.at(1).first, 1);
    ASSERT_EQ(match_pair.at(1).second, 1);

    ASSERT_EQ(match_pair.at(2).first, 2);
    ASSERT_EQ(match_pair.at(2).second, 2);

    ASSERT_EQ(match_pair.at(3).first, 3);
    ASSERT_EQ(match_pair.at(3).second, 3);
}

///////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
