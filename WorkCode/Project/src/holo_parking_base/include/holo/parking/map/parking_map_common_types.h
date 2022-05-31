/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ParkingMapCommonTypes.h
 * @brief This header file defines common types of parking map.
 * @author guopeikai(guopeikai@holomaitc.com)
 * @date 2022-02-14
 */

#ifndef HOLO_PARKING_MAP_PARKING_MAP_COMMON_TYPES_H_
#define HOLO_PARKING_MAP_PARKING_MAP_COMMON_TYPES_H_

#include <boost/optional/optional.hpp>
#include <map>
#include <opencv2/core.hpp>
#include <vector>

#include <holo/common/parking_slot.h>
#include <holo/core/types.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>

namespace holo
{
namespace parking
{
namespace map
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define mappoint state
 */
enum class MapPointState : uint16_t
{
    CANDIDATE = 0,  ///< the initial state of prebuilt mappoint
    VISIBLE   = 1,  ///< the mappoint is visible but not matched with new features
    MATCHED   = 2,  ///< the mappoint is matched with new features

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define common basic types
 */
using Scalar = holo::float64_t;

using Matrix3 = holo::Matrix3T<Scalar>;
using Point3  = holo::Point3T<Scalar>;
using Pose3   = holo::Pose3T<Scalar>;
using Vector3 = holo::Vector3T<Scalar>;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define semantic label
 */
enum class SemanticLabel : uint16_t
{
    STATIC       = 0,  ///< the semantic label is static
    VEHICLE      = 1,  ///< the semantic label is car
    BYCICLE      = 2,  ///< the semantic label is bycicle
    PEDESTRIAN   = 3,  ///< the semantic label is people
    TRAFFIC_SIGN = 4,  ///< the semantic label is traffic sign
    ANIMAL       = 5,  ///< the semantic label is animal
    UNKNOWN      = 6,  ///< the semantic label is unknow

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief the struct represent feature point in feature map
 */
struct MapPoint
{
    /// @brief update remember rate of mappoint
    void UpdateRememberRate();

    /// @brief update mappoint state
    void UpdateState();

    /// @brief position of the point
    Point3 position;

    /// @brief view direction when triangulate the point
    Vector3 direction;

    /// @brief covariance of the point
    Matrix3 covariance;

    /// @brief associated descriptor
    cv::Mat descriptor;

    /// @brief reference observed camera pose in world frame
    Pose3 reference_pose;

    /// @brief reference frame id
    uint64_t reference_frame_id;

    /// @brief score
    Scalar score;

    /// @brief the remember_rate (the new remember rate can calculate from the old, so retain it to avoid repeated
    /// computation.)
    Scalar remember_rate;

    /// @brief the matching results for all localization times
    std::vector<MapPointState> life_long_states;

    /// @brief the reprojection errors in once localization
    std::vector<Scalar> reprojection_errors;

    ///@brief the mean reprojection error
    Scalar mean_reprojection_error;

    /// @brief the semantic of mappoint
    SemanticLabel semantic_label;
};

using MapPointPtr = std::shared_ptr<MapPoint>;
using Map         = std::vector<MapPointPtr>;
using MapPtr      = std::shared_ptr<Map>;
using ConstMapPtr = std::shared_ptr<const Map>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define feature information
 */
struct Feature
{
    /// @brief 2d point detected on image
    cv::Point2f image_point;

    /// @brief an optional descriptor of this point
    boost::optional<cv::Mat> optional_descriptor;

    /// @brief normalized point on normalized plane(z == 1)
    Point3 normalized_point;

    /// @brief camera id. indicate which camera does this feature comes from
    uint16_t camera_id;

    /// @brief confidence of this keypoint
    Scalar score;

    ///@brief the semantic label of this feature
    SemanticLabel semantic_label;

    /**
     * @brief Construct a new Feature object
     *
     * @param _image_point 2d point detected on image
     * @param _optional_descriptor an optional descriptor of this point
     * @param _normalized_point normalized point on normalized plane(z == 1)
     * @param _camera_id camera id
     */
    Feature(const cv::Point2f&             _image_point         = cv::Point2f(),
            const boost::optional<cv::Mat> _optional_descriptor = boost::none,
            const Point3& _normalized_point = Point3(), const uint16_t _camera_id = 0, const Scalar _score = -1.0,
            const SemanticLabel& _semantic_label = SemanticLabel::STATIC)
      : image_point(_image_point)
      , optional_descriptor(_optional_descriptor)
      , normalized_point(_normalized_point)
      , camera_id(_camera_id)
      , score(_score)
      , semantic_label(_semantic_label)
    {
    }
};
typedef std::vector<Feature> Features;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define key frame struct
 * @details A frame is the selected keyframe in prebuilt map
 */
struct KeyFrame
{
    /// @brief define single camera data of a frame
    struct SingleCameraData
    {
        /// @brief features extracted on this frame
        Features features;

        /// @brief camera pose of this frame
        Pose3 pose;

        /// @brief associated landmark ids, this vector is one-to-one cooresponding to features.
        /// @note. value less than zero mean this feature does not associated to any landmark.
        std::vector<int64_t> associated_landmarks;

        ///@brief associated 3d points, this vector is one-to-one cooresponding with features.
        std::vector<Point3> mappoints;
    };

    /// @brief frame id
    uint64_t frame_id;

    /// @brief vehicle pose
    Pose3 pose;

    /// @brief multi camera data
    std::vector<SingleCameraData> multi_camera_data;

    /// @brief constructor
    KeyFrame(const uint64_t _frame_id = 0, const Pose3& _pose = Pose3(), const uint64_t camera_num = 1)
      : frame_id(_frame_id), pose(_pose)
    {
        multi_camera_data.resize(camera_num);
    }
};
using KeyFramesDatabase = std::map<uint64_t, KeyFrame>;

}  // namespace map
}  // namespace parking
}  // namespace holo

#endif  // HOLO_PARKING_MAP_PARKING_MAP_COMMON_TYPES_H_
