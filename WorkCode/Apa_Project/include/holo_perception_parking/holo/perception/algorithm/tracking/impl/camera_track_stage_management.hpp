/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_track_stage_management.hpp
 * @brief This header file defines camera track stage management.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-01-02"
 */

#ifndef HOLO_PERCEPTION_TRACKING_CAMERA_TRACK_STAGE_MANAGEMENT_HPP_
#define HOLO_PERCEPTION_TRACKING_CAMERA_TRACK_STAGE_MANAGEMENT_HPP_

#include <holo/perception/algorithm/tracking/camera_track_stage_management.h>

namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
CameraTrackStageManagementT<T>::CameraTrackStageManagementT(const AgeType value_to_confirm,
                                                            const AgeType value_to_terminate)
{
    if (value_to_confirm < 1U || value_to_terminate < 1U)
    {
        throw std::runtime_error("value_to_confirm and value_to_terminate must be at least one");
    }
    StageManagementType::value_to_confirm_   = value_to_confirm;
    StageManagementType::value_to_terminate_ = value_to_terminate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CameraTrackStageManagementT<T>::UpdateTrackStage(TrackType& track)
{
    CameraTrackType& camera_track = dynamic_cast<CameraTrackType&>(track);

    if (camera_track.GetStage() == Stage::UNCONFIRMED)
    {
        // special case when value to terminate is one, and object only detected once
        if (camera_track.GetTimeSinceUpdate() >= StageManagementT<T>::value_to_terminate_)
        {
            camera_track.SetStage(Stage::TERMINATED);
        }
        else if (camera_track.GetHitNum() >= StageManagementT<T>::value_to_confirm_)
        {
            camera_track.SetStage(Stage::CONFIRMED);
        }
    }
    else if (camera_track.GetStage() == Stage::CONFIRMED)
    {
        if (camera_track.GetTimeSinceUpdate() > 0U)
        {
            camera_track.SetStage(Stage::LOST);
            // special case when the value_to_terminate is one
            if (camera_track.GetTimeSinceUpdate() >= StageManagementT<T>::value_to_terminate_)
            {
                camera_track.SetStage(Stage::TERMINATED);
            }
        }
    }
    else if (camera_track.GetStage() == Stage::LOST)
    {
        if (camera_track.GetHitNum() > 0U)
        {
            camera_track.SetStage(Stage::CONFIRMED);
        }
        else if (camera_track.GetTimeSinceUpdate() >= StageManagementT<T>::value_to_terminate_)
        {
            camera_track.SetStage(Stage::TERMINATED);
        }
    }
    // if the stage is terminated already, do nothing.
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_CAMERA_TRACK_STAGE_MANAGEMENT_HPP_
