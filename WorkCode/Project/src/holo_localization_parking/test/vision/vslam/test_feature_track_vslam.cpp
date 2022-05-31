/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_feature_track.cpp
 * @brief  test feature track class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-12"
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/vslam/feature_track.h>

using namespace holo;
using namespace holo::localization::vision::vslam;

namespace internal
{
/**
 * @brief function to help checking FeatureTrack::Measurement equal
 */
bool CompareMeasurement(const FeatureTrack::Measurement& lhs, const FeatureTrack::Measurement& rhs)
{
    // check id
    if (lhs.first != rhs.first)
    {
        return false;
    }

    // check number of associated camera
    if (lhs.second.size() != rhs.second.size())
    {
        return false;
    }

    // check associated camera
    for (auto iter_lhs = lhs.second.begin(), iter_rhs = rhs.second.begin();
         iter_lhs != lhs.second.end(), iter_rhs != rhs.second.end(); iter_lhs++, iter_rhs++)
    {
        // camera id
        if (iter_lhs->first != iter_rhs->first)
        {
            return false;
        }

        // check image point
        if (iter_lhs->second.image_point != iter_rhs->second.image_point)
        {
            return false;
        }

        // check normalized point
        if (!iter_lhs->second.normalized_point.IsEqual(iter_rhs->second.normalized_point))
        {
            return false;
        }

        // check descriptor
        if (iter_lhs->second.optional_descriptor)
        {
            if (!iter_rhs->second.optional_descriptor)
            {
                return false;
            }

            const cv::Mat lhs_desc = *iter_lhs->second.optional_descriptor;
            const cv::Mat rhs_desc = *iter_rhs->second.optional_descriptor;

            if (cv::norm(lhs_desc) != 1.0 || cv::norm(rhs_desc) != 1.0 || lhs_desc.dot(rhs_desc) != 1.0)
            {
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief function to help checking FeatureTrack::Parameters equal
 */
bool CompareParameters(const FeatureTrack::Parameters& lhs, const FeatureTrack::Parameters& rhs)
{
    return (lhs.throw_cheirality == rhs.throw_cheirality) && (lhs.verbose_cheirality == rhs.verbose_cheirality);
}
}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FeatureTrack, Parameters)
{
    const bool throw_cheirality   = true;
    const bool verbose_cheirality = true;

    /* check constructor */
    FeatureTrack::Parameters parameters(throw_cheirality, verbose_cheirality);

    ASSERT_EQ(throw_cheirality, parameters.throw_cheirality);
    ASSERT_EQ(verbose_cheirality, parameters.verbose_cheirality);

    /* check generate example */
    FeatureTrack::Parameters example = FeatureTrack::Parameters::Example();
    ASSERT_FALSE(example.throw_cheirality);
    ASSERT_FALSE(example.verbose_cheirality);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FeatureTrack, Basic)
{
    /* parameters */
    FeatureTrack::Parameters parameters = FeatureTrack::Parameters::Example();

    /* measurement */
    uint64_t                  frame_id  = 10u;
    uint16_t                  camera_id = 0u;
    Feature                   ft(cv::Point2f(2.0, 5.0), boost::none, Point3(1.0, 2.0, 5.0), camera_id);
    FeatureTrack::Measurement measurement =
        std::make_pair(frame_id, FeatureTrack::CameraIndexedFeature{{camera_id, ft}});

    /* check CreateNewTrack GetId GetLength GetState GetParams GetLandmark */
    FeatureTrack feature_track = FeatureTrack::CreateNewTrack(std::make_shared<FeatureTrack::Parameters>(parameters),
                                                              CameraParameters::Example(), measurement);
    ASSERT_EQ(0u, feature_track.Id());
    ASSERT_EQ(1u, feature_track.Length());
    ASSERT_EQ(FeatureTrack::State::CANDIDATE, feature_track.GetState());
    ASSERT_EQ(1u, feature_track.Measurements().size());
    ASSERT_TRUE(internal::CompareMeasurement(measurement, feature_track.Measurements().at(0)));
    ASSERT_TRUE(internal::CompareMeasurement(measurement, feature_track.Measurements(0)));
    ASSERT_TRUE(internal::CompareParameters(parameters, feature_track.Params()));
    ASSERT_EQ(frame_id, feature_track.Measurements(0).first);
    ASSERT_EQ(1u, feature_track.Measurements(0).second.size());
    ASSERT_FALSE(feature_track.GetLandmark());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FeatureTrack, CreateTrack_GetMeasurement_CreateFactor)
{
    /* parameters */
    FeatureTrack::Parameters parameters    = FeatureTrack::Parameters::Example();
    CameraParameters::Ptr    camera_params = CameraParameters::Example();

    /* camera id */
    uint16_t camera_index = 0;

    /* measurements */
    const uint64_t                         measurement_num = 3u;
    std::vector<FeatureTrack::Measurement> measurements;
    measurements.reserve(measurement_num);

    /* create measurement */
    for (uint64_t i = 0u; i < measurement_num; i++)
    {
        uint64_t frame_id = i;
        Feature  ft(cv::Point2f(static_cast<Scalar>(i) * 2.0, static_cast<Scalar>(i) * 5.0), boost::none,
                   Point3(static_cast<Scalar>(i) * 1.0, static_cast<Scalar>(i) * 2.0, static_cast<Scalar>(i) * 5.0),
                   camera_index);
        FeatureTrack::Measurement measurement =
            std::make_pair(frame_id, FeatureTrack::CameraIndexedFeature{{camera_index, ft}});
        measurements.push_back(measurement);
    }

    /* landmark point3 */
    const gtsam::Point3 landmark_point(1.0, 2.0, 3.0);

    FeatureTrack feature_track = FeatureTrack::CreateNewTrack(std::make_shared<FeatureTrack::Parameters>(parameters),
                                                              camera_params, measurements.at(0u));
    ASSERT_EQ(0u, static_cast<uint64_t>(feature_track.Unit3Factors().size()));
    ASSERT_EQ(measurements.at(0u).second.at(camera_index).image_point,
              feature_track.PredictNewPoints().at(camera_index));

    /* check CreateNewTrackByAddingNewestMeasurement GetMeasurements GetMeasurement GetOldestMeasurement
     * GetNewestMeasurement PredictNewMeasurement */
    FeatureTrack new_feature_track = feature_track.CreateNewTrackByAddingNewestMeasurement(
        measurements.at(1u).first, measurements.at(1u).second.at(camera_index));
    ASSERT_EQ(2u, new_feature_track.Length());
    ASSERT_EQ(2u, static_cast<uint64_t>(new_feature_track.Measurements().size()));
    ASSERT_TRUE(internal::CompareMeasurement(measurements.at(0u), new_feature_track.OldestMeasurement()));
    ASSERT_TRUE(internal::CompareMeasurement(measurements.at(1u), new_feature_track.NewestMeasurement()));
    ASSERT_TRUE(internal::CompareMeasurement(measurements.at(1u), new_feature_track.Measurements(1u)));
    ASSERT_EQ(measurements.at(1u).second.at(camera_index).image_point +
                  measurements.at(1u).second.at(camera_index).image_point -
                  measurements.at(0u).second.at(camera_index).image_point,
              new_feature_track.PredictNewPoints().at(camera_index));  /// < newest_pt + (newest_pt - second_newest_pt)
    ASSERT_EQ(0u, static_cast<uint64_t>(new_feature_track.Unit3Factors().size()));

    /* check CreateNewTrackByUpdatingState */
    FeatureTrack fresh_feature_track = new_feature_track.CreateNewTrackByUpdatingState(
        FeatureTrack::State::FRESH, boost::optional<gtsam::Point3>(landmark_point));
    ASSERT_EQ(FeatureTrack::State::FRESH, fresh_feature_track.GetState());
    ASSERT_EQ(landmark_point, fresh_feature_track.GetLandmark()->Point());

    /* check create projection factor for FRESH */
    const std::vector<Unit3FactorPtr> unit3_factors = fresh_feature_track.Unit3Factors();
    ASSERT_EQ(2u, static_cast<uint64_t>(unit3_factors.size()));

    for (uint64_t i = 0u; i < 2u; i++)
    {
        const auto&                      unit3_factor = unit3_factors.at(i);
        const FeatureTrack::Measurement& measurement  = measurements.at(i);
        ASSERT_EQ(gtsam::Point3(measurement.second.at(camera_index).normalized_point.GetX(),
                                measurement.second.at(camera_index).normalized_point.GetY(),
                                measurement.second.at(camera_index).normalized_point.GetZ()),
                  unit3_factor->GetFeatureMeasurement());
    }

    /* check create projection factor fro LIVE */
    FeatureTrack live_feature_track = fresh_feature_track.CreateNewTrackByUpdatingState(FeatureTrack::State::LIVE);
    ASSERT_EQ(1u, static_cast<uint64_t>(live_feature_track.Unit3Factors().size()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FeatureTrack, throw_case)
{
    /* parameters */
    FeatureTrack::Parameters parameters    = FeatureTrack::Parameters::Example();
    CameraParameters::Ptr    camera_params = CameraParameters::Example();

    /* camera id */
    uint16_t camera_index = 0;

    /* measurements */
    const uint64_t                         measurement_num = 3u;
    std::vector<FeatureTrack::Measurement> measurements;
    measurements.reserve(measurement_num);

    for (uint64_t i = 0u; i < measurement_num; i++)
    {
        uint64_t frame_id = i;
        Feature  ft(cv::Point2f(static_cast<Scalar>(i) * 2.0, static_cast<Scalar>(i) * 5.0), boost::none,
                   Point3(static_cast<Scalar>(i) * 1.0, static_cast<Scalar>(i) * 2.0, static_cast<Scalar>(i) * 5.0),
                   camera_index);
        FeatureTrack::Measurement measurement =
            std::make_pair(frame_id, FeatureTrack::CameraIndexedFeature{{camera_index, ft}});
        measurements.push_back(measurement);
    }

    FeatureTrack feature_track = FeatureTrack::CreateNewTrack(std::make_shared<FeatureTrack::Parameters>(parameters),
                                                              camera_params, measurements.at(0u));
    ASSERT_THROW(feature_track.Measurements(1u),
                 std::out_of_range);  /// < there is only one measurement, get the second measurement will cause throw
    ASSERT_THROW(feature_track.CreateNewTrackByUpdatingState(FeatureTrack::State::FRESH),
                 std::runtime_error);  /// < update state to FRESH, but do not give landmark point
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
