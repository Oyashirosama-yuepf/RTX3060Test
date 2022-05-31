/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file landmark.h
 * @brief This header file defines landmark class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "Sep-2-2019"
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_LANDMARK_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_LANDMARK_H_

#include <holo/localization/vision/vslam/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * @addtogroup vslam
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define landmark class
 */
class Landmark
{
public:
    /**
     * @brief Construct a new Landmark object with default id and point3
     *
     * @param id default id 0
     * @param point default point3 [0 0 0]
     */
    Landmark(const uint64_t id = 0, const gtsam::Point3& point = gtsam::Point3()) : id_(id), point_(point)
    {
    }

    /**
     * @brief Construct a new Landmark object with the given point3
     *
     * @param point the given point3 to construct a landmark
     */
    Landmark(const gtsam::Point3& point) : Landmark(next_id_++, point)
    {
    }

    /**
     * @brief update the point3 of this landmark
     *
     * @param point the given point3 used to replace the old one
     * @return Landmark with new point3 and old id
     */
    Landmark UpdateLandmark(const gtsam::Point3& point) const;

    /**
     * @brief get landmark id
     *
     * @return landmark id
     */
    uint64_t Id() const noexcept;

    /**
     * @brief get landmark point3
     *
     * @return landmark point3
     */
    const gtsam::Point3& Point() const noexcept;

protected:
    uint64_t      id_;     ///< landmark id
    gtsam::Point3 point_;  ///< landmark piont in vio map frame

    static uint64_t next_id_;  ///< id for next landmark
};                             // Landmark

/**
 * @}
 *
 */
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_LANDMARK_H_