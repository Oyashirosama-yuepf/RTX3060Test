/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file landmark.cpp
 * @brief source file of landmark class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "Dec-12-2019"
 */

#include <holo/localization/vision/vslam/landmark.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief initialize next_id of landmark
 */
uint64_t Landmark::next_id_ = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Landmark Landmark::UpdateLandmark(const gtsam::Point3& point) const
{
    return Landmark(id_, point);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint64_t Landmark::Id() const noexcept
{
    return id_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const gtsam::Point3& Landmark::Point() const noexcept
{
    return point_;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo