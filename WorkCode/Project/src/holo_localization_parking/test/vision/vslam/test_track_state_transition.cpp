/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_track_state_transition.cpp
 * @brief test track state transition class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-16"
 */

#include <gtest/gtest.h>

#include <vision/vslam/fixtures/track_state_transition_fixture.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, ALLToFINISHED)
{
    /* check before optimizaiton */
    Tracker::State new_state = all_state_to_finished_.state;
    track_state_transition_.RunBeforeOptimization(new_state, all_state_to_finished_.values,
                                                  all_state_to_finished_.factor_graph);

    for (uint64_t i = 0u; i < static_cast<uint64_t>(new_state.tracks.size()); i++)
    {
        const FeatureTrack& track = new_state.tracks.at(i);
        ASSERT_EQ(FeatureTrack::State::FINISHED, track.GetState());
    }

    /* check after optimization */
    track_state_transition_.RunAfterOptimization(new_state, all_state_to_finished_.values,
                                                 all_state_to_finished_.factor_graph);

    for (uint64_t i = 0u; i < static_cast<uint64_t>(new_state.tracks.size()); i++)
    {
        const FeatureTrack& track = new_state.tracks.at(i);
        ASSERT_EQ(FeatureTrack::State::FINISHED, track.GetState());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, CANDIDATE)
{
    /* check before optimizaiton */
    Tracker::State new_state = candidates_.state;
    track_state_transition_.RunBeforeOptimization(new_state, candidates_.values);

    ASSERT_EQ(2u, static_cast<uint64_t>(new_state.tracks.size()));
    ASSERT_EQ(FeatureTrack::State::FRESH, new_state.tracks.at(0u).GetState());
    ASSERT_TRUE(new_state.tracks.at(0u).GetLandmark());
    ASSERT_EQ(landmark_, holo::localization::HoloGtsam::Convert(new_state.tracks.at(0u).GetLandmark()->Point()));
    ASSERT_EQ(FeatureTrack::State::BAD_BEFORE_OPTIMIZATION, new_state.tracks.at(1u).GetState());
    ASSERT_FALSE(new_state.tracks.at(1u).GetLandmark());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, FRESH)
{
    /* check before optimization */
    Tracker::State new_state = fresh_.state;
    track_state_transition_.RunBeforeOptimization(new_state, fresh_.values, fresh_.factor_graph);

    ASSERT_EQ(2u, static_cast<uint64_t>(new_state.tracks.size()));
    ASSERT_EQ(FeatureTrack::State::BAD_BEFORE_OPTIMIZATION, new_state.tracks.at(0u).GetState());
    ASSERT_EQ(FeatureTrack::State::LIVE, new_state.tracks.at(1u).GetState());

    /* check after optimization */
    Tracker::State new_state1 = fresh_.state;
    track_state_transition_.RunAfterOptimization(new_state1, fresh_.values, fresh_.factor_graph);

    ASSERT_EQ(2u, static_cast<uint64_t>(new_state1.tracks.size()));
    ASSERT_EQ(FeatureTrack::State::BAD_AFTER_OPTIMIZATION, new_state1.tracks.at(0u).GetState());
    ASSERT_EQ(FeatureTrack::State::FRESH, new_state1.tracks.at(1u).GetState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, LIVE)
{
    /* check before optimization */
    Tracker::State new_state = live_.state;
    track_state_transition_.RunBeforeOptimization(new_state, live_.values, live_.factor_graph);

    ASSERT_EQ(2u, static_cast<uint64_t>(new_state.tracks.size()));
    ASSERT_EQ(FeatureTrack::State::BAD_BEFORE_OPTIMIZATION, new_state.tracks.at(0u).GetState());
    ASSERT_EQ(FeatureTrack::State::LIVE, new_state.tracks.at(1u).GetState());

    /* check after optimization */
    Tracker::State new_state1 = live_.state;
    track_state_transition_.RunAfterOptimization(new_state1, live_.values, live_.factor_graph);

    ASSERT_EQ(2u, static_cast<uint64_t>(new_state1.tracks.size()));
    ASSERT_EQ(FeatureTrack::State::BAD_AFTER_OPTIMIZATION, new_state1.tracks.at(0u).GetState());
    ASSERT_EQ(FeatureTrack::State::LIVE, new_state1.tracks.at(1u).GetState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, LIVEWithUnit3Factors)
{
    /* check before optimization */
    Tracker::State new_state = live_with_unit3_factors_.state;
    track_state_transition_.RunBeforeOptimization(new_state, live_with_unit3_factors_.values,
                                                  live_with_unit3_factors_.factor_graph);

    ASSERT_EQ(2u, static_cast<uint64_t>(new_state.tracks.size()));
    ASSERT_EQ(FeatureTrack::State::BAD_BEFORE_OPTIMIZATION, new_state.tracks.at(0u).GetState());
    ASSERT_EQ(FeatureTrack::State::LIVE, new_state.tracks.at(1u).GetState());

    /* check after optimization */
    Tracker::State new_state1 = live_with_unit3_factors_.state;
    track_state_transition_.RunAfterOptimization(new_state1, live_with_unit3_factors_.values,
                                                 live_with_unit3_factors_.factor_graph);

    ASSERT_EQ(2u, static_cast<uint64_t>(new_state1.tracks.size()));
    ASSERT_EQ(FeatureTrack::State::BAD_AFTER_OPTIMIZATION, new_state1.tracks.at(0u).GetState());
    ASSERT_EQ(FeatureTrack::State::LIVE, new_state1.tracks.at(1u).GetState());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
