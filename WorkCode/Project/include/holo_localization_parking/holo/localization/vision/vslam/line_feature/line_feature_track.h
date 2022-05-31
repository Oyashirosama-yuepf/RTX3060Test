/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line_feature_track.h
 * @brief This header file defines line feature track class.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2022-03-07"
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_LINE_FEATURE_LINE_FEATURE_TRACK_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_LINE_FEATURE_LINE_FEATURE_TRACK_H_

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/line_feature/feature_track_base.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * @brief line feature track class
 * @details It contains many feature measurements that belong to one track
 */
class LineFeatureTrack : public FeatureTrackBase<LineFeature, GTPluckerLine>
{
public:
    LineFeatureTrack(const Parameters::ConstPtr& parameters, const CameraParameters::Ptr& camera_parameters,
                     const uint64_t id, const std::vector<Measurement>& measurements, const State state,
                     const boost::optional<Landmark>& landmark = boost::none)
      : FeatureTrackBase(parameters, camera_parameters, id, measurements, state, landmark)
    {
    }

private:
};
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo