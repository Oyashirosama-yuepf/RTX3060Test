/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file stage_management.h
 * @brief This header file defines stage management class, mainly used to manage track class.
 * @author sunzhenqiang(sunzhenqiang@holomaitc.com)
 * @date "2019-12-23"
 */

#ifndef HOLO_PERCEPTION_TRACKING_STAGE_MANAGEMENT_H_
#define HOLO_PERCEPTION_TRACKING_STAGE_MANAGEMENT_H_

#include <holo/perception/tracking/track.h>
#include <holo/perception/tracking/track_container.h>

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
 * @brief Manage track stage according to some transform rule
 * @details this class is the base class of stage management classes, and the user should derive this class for
 * different sensor type and set private class member respectively.
 *
 * @tparam T data type of measured object
 */
template <typename T>
class StageManagementT
{
public:
    /**
     * @brief smart pointer
     *
     */
    using Ptr      = std::shared_ptr<StageManagementT<T> >;
    using ConstPtr = std::shared_ptr<const StageManagementT<T> >;
    using Track    = TrackT<T>;

    /**
     * @brief update track stage
     *
     * @param track [in][out] current managed track
     */
    virtual void UpdateTrackStage(Track& track)
    {
        (void)track;
    }

protected:
    uint32_t value_to_confirm_;
    uint32_t value_to_lost_;
    uint32_t value_to_terminate_;
};

/**
 * @}
 *
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_STAGE_MANAGEMENT_H_
