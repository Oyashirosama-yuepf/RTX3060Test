/*!
 * \brief Unit test for vslam tracker
 * \author Feng. Li, lifeng@holomatic.com
 * \date Mar-22-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>
#include <vision/vslam/fixtures/tracker_fixture.h>

///////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, Pipeline_Descriptor_FlowMatching)
{
    vslam::Tracker tracker(parameters_, camera_parameters_);

    // initial tracker state
    vslam::Tracker::State tracker_state(0, holo::Timestamp(), std::vector<vslam::FeatureTrack>{});

    // check images to ensure the test really work.
    ASSERT_TRUE(!images_and_features_and_pose_.empty());

    // run tracker pipeline
    for (size_t i = 0; i < images_and_features_and_pose_.size(); i++)
    {
        // get image and corresponding features and camera pose
        vslam::Image    new_image;
        vslam::Features new_features;
        vslam::Pose3    T_wc;
        std::tie(new_image, new_features, T_wc) = images_and_features_and_pose_.at(i);

        // run tracker with descriptor pipeline
        tracker.Run(tracker_state, new_image.GetTimestamp(), i, {new_features});

        // check result
        ASSERT_EQ(tracker_state.tracks.size(), 4);
        ASSERT_EQ(tracker_state.frame_id, i);
        ASSERT_EQ(tracker_state.timestamp.ToNsec(), i);
    }

    // check all feature track
    const auto& tracks = tracker_state.tracks;
    ASSERT_EQ(tracks.size(), 4);

    for (uint8_t i = 0; i < 4; i++)
    {
        const auto& track = tracks.at(i);
        ASSERT_EQ(track.Length(), images_and_features_and_pose_.size());

        for (uint8_t j = 0; j < images_and_features_and_pose_.size(); j++)
        {
            vslam::Image    gt_image;
            vslam::Features gt_features;
            vslam::Pose3    gt_pose;
            std::tie(gt_image, gt_features, gt_pose) = images_and_features_and_pose_.at(j);

            const auto& gt_feature = gt_features.at(i).image_point;
            const auto& es_feature = track.Measurements(j).second.at(camera_index_).image_point;
            ASSERT_FLOAT_EQ(es_feature.x, gt_feature.x);
            ASSERT_FLOAT_EQ(es_feature.y, gt_feature.y);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
