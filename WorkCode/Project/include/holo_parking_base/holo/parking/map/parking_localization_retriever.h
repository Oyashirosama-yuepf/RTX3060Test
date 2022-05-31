/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_localization_retriever.h
 * @brief Define parking localization retriever
 * @author wangminghui@holomatic.com
 * @date "2021-11-04"
 */

#ifndef HOLO_PARKING_LOCALIZATION_RETRIVER_H_
#define HOLO_PARKING_LOCALIZATION_RETRIVER_H_

#include <cmath>
#include <limits>
#include <utility>
#include <vector>

#include <holo/common/coordinate.h>
#include <holo/common/parking_slot.h>
#include <holo/common/road_type.h>
#include <holo/common/timestamp.h>
#include <holo/container/details/vector.h>
#include <holo/core/epsilon.h>
#include <holo/core/types.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/point3.h>
#include <holo/parking/map/parking_map_common_types.h>

namespace holo
{
namespace parking
{
namespace map
{

/**
 * @brief Parking Localization Retriever.
 *
 * @ref Reference to: https://holomatic.feishu.cn/docs/doccnfJb1Fyov3IvmKnQlF5bpHb
 */

class ParkingLocalizationRetriever
{
public:
    using Scalar               = holo::float64_t;
    using MapPoint             = holo::parking::map::MapPoint;
    using MapPointPtr          = std::shared_ptr<MapPoint>;
    using Map                  = std::vector<MapPointPtr>;
    using Pose3                = holo::Pose3T<Scalar>;
    using KeyFrame             = holo::parking::map::KeyFrame;
    using ParkingSlot          = holo::common::ParkingSlotd;
    using ParkingSlotFrameType = holo::common::ParkingSlotFrame;
    using OdometryType         = holo::common::Odometryd;

    ParkingLocalizationRetriever()          = default;
    virtual ~ParkingLocalizationRetriever() = default;

    /**
     * @brief Define state code.
     */
    enum class StateCode : holo::uint8_t
    {
        OK = 0,              ///< No error.
        NONE,                ///< No target object.
        FAILED,              ///< An error occurs in map engine.
        IMPERFECT,           ///< Half successes and half failures.
        UNAVAILABLE,         ///< Map engine is unavailable.
        UNSUPPORTED,         ///< The operation is not supported.
        ENGINE_READY,        ///< Map engine is ready, we can request map data.
        ENGINE_UNREADY,      ///< Map engine is not ready, please wail for a moment.
        ENGINE_UNCONNECTED,  ///< Map engine client disconnect with server.
    };

    /**
     * @brief get the Retriever status
     *
     * @return State Type.
     */
    virtual StateCode GetStateCode() = 0;

    /**
     * @brief get the Map instance
     *
     * @return Map Type.
     */
    virtual Map const& GetWholeMap() = 0;

    /**
     * @brief get the KeyFramesDatabase instance
     *
     * @return KeyFramesDatabase Type.
     */
    virtual KeyFramesDatabase const& GetAllKeyFrames() = 0;

    /**
     * @brief get the visible map points from prior pose
     *
     * @param[in] odometry An odometry with position info and coordinate info.
     * @param[in] maximum_range max depth in meter
     * @param[in] fov maximum camera fov in vertical and horizontal direction
     * @param[out] visible_map the visible map
     */
    virtual holo::bool_t GetVisibleMap(OdometryType const& odometry, Scalar const& maximum_range, Scalar const& fov,
                                       MapPtr& visible_map) = 0;

    /**
     * @brief query candidate frames from keyframe database
     * @details use a prior pose to query candidate frame, all keyframes located in a certain range will served as
     * candidate frame.
     *
     * @param[in] odometry An odometry with position info and coordinate info.
     * @param dist_threshold distance threshold in meter
     * @param angle_threshold angle threshold in degree
     * @param keyframes a vector which include candidate frames
     * @return true: query success.
     *         false: query failure.
     */
    virtual holo::bool_t QueryCandidateFramesByPose(OdometryType const& odometry, Scalar const& dist_threshold,
                                                    Scalar const&                               angle_threshold,
                                                    std::vector<std::pair<uint64_t, KeyFrame>>& keyframes) = 0;
    /**
     * @brief query ParkingSlot from ParkingSlot database
     *
     * @param[in] odometry An odometry with position info and coordinate info.
     * @param radius distance threshold in meter
     * @param parking_slot_frame a vector which include ParkingSlot
     * @return true: query success.
     *         false: query failure.
     */
    virtual holo::bool_t QueryParkingSlotByPose(OdometryType const& odometry, holo::float32_t const& radius,
                                                ParkingSlotFrameType& parking_slot_frame) = 0;
};

}  // namespace map
}  // namespace parking
}  // namespace holo

#endif /* HOLO_PARKING_LOCALIZATION_RETRIVER_H_ */
