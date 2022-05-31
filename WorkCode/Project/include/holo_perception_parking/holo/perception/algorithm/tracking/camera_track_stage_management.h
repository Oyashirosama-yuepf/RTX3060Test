/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_track_stage_management.h
 * @brief This header file defines camera track stage management.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2019-12-31"
 */

#ifndef HOLO_PERCEPTION_TRACKING_CAMERA_TRACK_STAGE_MANAGEMENT_H_
#define HOLO_PERCEPTION_TRACKING_CAMERA_TRACK_STAGE_MANAGEMENT_H_

#include <holo/perception/algorithm/tracking/camera_track.h>
#include <holo/perception/common/box_object.h>
#include <holo/perception/tracking/stage_management.h>
#include <holo/perception/tracking/track.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup tracking
 *
 * @{
 */

/**
 * @brief Camera track stage management
 *
 * @tparam T type of detected object
 *
 * @todo Currently the stage transition is using frame count, refactor to use clock time.
 */
template <typename T>
class CameraTrackStageManagementT : StageManagementT<T>
{
public:
    using CameraTrackType     = CameraTrackT<T>;
    using AgeType             = typename CameraTrackType::AgeType;
    using TrackType           = TrackT<BoxObjectT<T, 8U>>;
    using TrackPtr            = std::shared_ptr<TrackType>;
    using Stage               = typename CameraTrackType::Stage;
    using StageManagementType = StageManagementT<T>;

    /**
     * @brief Construct a new Camera Track Stage Management T object
     *
     * @param value_to_confirm time steps the object was continuously detected
     * @param value_to_terminate time steps the object was continuously lost
     * @throw std::runtime error if value_to_confirm or value_to_terminate is less than one
     */
    CameraTrackStageManagementT(const AgeType value_to_confirm, const AgeType value_to_terminate);

    /**
     * @brief update track stage
     *
     * @param[in, out] track camera detected object track
     *
     * @note This code assume all cameras have the same working frequency(eg. 10 hz)
     * The code won't work correctly if the assumption is not true.
     */
    void UpdateTrackStage(TrackType& track);
};
/**
 * @}
 *
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_CAMERA_TRACK_STAGE_MANAGEMENT_H_
