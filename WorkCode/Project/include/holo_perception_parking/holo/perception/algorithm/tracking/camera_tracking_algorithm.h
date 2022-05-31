/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_tracking_algorithm.h
 * @brief This header file defines camera detected object tracking algorithm.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2019-12-31"
 */

#ifndef HOLO_PERCEPTION_TRACKING_CAMERA_TRACKING_ALGORITHM_H_
#define HOLO_PERCEPTION_TRACKING_CAMERA_TRACKING_ALGORITHM_H_

#include <holo/perception/algorithm/tracking/camera_track.h>
#include <holo/perception/algorithm/tracking/camera_track_stage_management.h>
#include <holo/perception/tracking/hungarian_optimizer.h>
#include <holo/perception/tracking/track_container.h>
#include <holo/perception/utils/uid_generator.h>

#include <holo/perception/tracking/impl/track_container.hpp>
#include <memory>
#include <set>

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
 * @brief Camera detected object tracking algorithm
 * @details This class implement ideas of Simple Online and Realtime Tracking algorithm
 * @ref https://github.com/abewley/sort
 *
 * @tparam T data type
 */
template <typename T>
class CameraTrackingAlgorithmT
{
public:
    using CameraTrackType                = CameraTrackT<T>;
    using CameraTrackPtr                 = std::shared_ptr<CameraTrackType>;
    using CameraDetectedObjectType       = typename CameraTrackType::CameraDetectedObjectType;
    using CameraDetectedObjectPtr        = std::shared_ptr<CameraDetectedObjectType>;
    using CameraDetectedObjectList       = std::list<CameraDetectedObjectPtr>;
    using TrackType                      = TrackT<CameraDetectedObjectType>;
    using TrackPtr                       = std::shared_ptr<TrackType>;
    using TrackContainerType             = TrackContainerT<CameraDetectedObjectType>;
    using CameraTrackStageManagementType = CameraTrackStageManagementT<T>;
    using CameraTrackStageManagementPtr  = std::shared_ptr<CameraTrackStageManagementType>;
    using AssignmentType                 = int32_t;
    using HungarianOptimizerType         = HungarianOptimizer<AssignmentType, T>;
    using Stage                          = typename CameraTrackStageManagementType::Stage;
    using AgeType                        = typename CameraTrackType::AgeType;
    using Box2Type                       = typename CameraTrackType::Box2Type;
    using TrackId                        = typename TrackType::TrackId;
    using SensorId                       = holo::common::SensorId;

    /**
     * @brief Construct a new Camera Tracking Algorithm T object
     *
     * @param config_file config file
     */
    CameraTrackingAlgorithmT(std::string const& config_file, std::set<uint32_t> const& vehicle_cat_ids);

    /**
     * @brief Track bounding boxes of camera with sensor_id
     * @details pipline
     * 1. fetch tracks with sensor_id
     * 2. associate camera detected objects with tracks
     * 3. update stage using stage management
     * 4. remove terminated track using track container
     *
     * @param sensor_id camera sensor id
     * @param[in, out] det_obj_list camera detected object pointer list
     */
    void Track(const SensorId& sensor_id, CameraDetectedObjectList& det_obj_list);

    /**
     * @brief Get the Track By Id object
     * @details After Track(const SensorId&, CameraDetectedObjectList&) was called,
     * each object in the detected object list has a unique id(even between different cameras).
     * User can get the track by calling this API, using the unique id.
     *
     * @param id track id
     * @return const TrackPtr the track pointer
     */
    const TrackPtr GetTrackById(const TrackId id)
    {
        return track_container_.GetTrackById(id);
    }

private:
    /**
     * @brief Initialize the algorithm
     *
     * @param config_file config file
     */
    void initialize(std::string const& config_file);

    /**
     * @brief Associate camera detected objects with tracks
     * @details pipline
     * 1. fetch bbox for each camera detected object
     * 2. predict bbox for each track
     * 3. match by bbox
     * 4. create new track for unmatched object
     * 5. update track with matched object
     *
     * @param[in] sensor_id camera's sensor_id
     * @param[in, out] det_obj_list camera detected object pointer list
     * @param[in, out] current_tracks track pointer vector
     *
     * @throw std::runtime_error if the Assignment index out of range
     */
    void associateObjectsWithTracks(const SensorId& sensor_id, CameraDetectedObjectList& det_obj_list,
                                    std::vector<TrackPtr>& current_tracks);

    /**
     * @brief match objects with tracks
     * @details pipline
     * @param[in] matching_dets detections to match
     * @param[in] matching_tracks tracks to match
     * @param[out] unmatched_dets unmatched detections
     * @param[in] small_object small object
     */
    void matchStage(const std::vector<CameraDetectedObjectPtr>& matching_dets,
                    const std::vector<TrackPtr>& matching_tracks,
                    std::vector<CameraDetectedObjectPtr>& unmatched_dets,
                    bool small_object);

    /**
     * @brief match objects with tracks using bboxes
     * @details pipline
     * 1. compute cost matrix using IOU of objects' bboxes and tracks' bboxes
     * 2. match using hungarian algorithm
     *
     * @param det_bboxes detected bboxes
     * @param track_bboxes track predicted bboxes
     * @return std::vector<AssignmentType> assignment vector
     */
    std::vector<AssignmentType> matchByBBox(const std::vector<Box2Type>& det_bboxes,
                                            const std::vector<Box2Type>& track_bboxes);

    /**
     * @brief match objects with tracks using bboxes
     * @details pipline
     * 1. compute cost matrix using IOU of objects' bboxes and tracks' bboxes
     * 2. match using hungarian algorithm
     *
     * @param det_bboxes detected bboxes
     * @param track_bboxes track predicted bboxes
     * @param small_object small object
     * @return std::vector<AssignmentType> assignment vector
     */
    std::vector<AssignmentType> matchByBBox(const std::vector<Box2Type>& det_bboxes,
                                            const std::vector<Box2Type>& track_bboxes, bool_t small_object);

    /**
     * @brief match objects with tracks using bboxes
     * @details pipeline
     * 1. compute cost matrix using IOU of objects' bboxes and tracks' bboxes
     * 2. update the cost matrix
     * 3. match using hungarian algorithm
     *
     * @param det_obj_list, detected object list
     * @param current_track, current tracks
     * @return std::vector<AssignmentType>, assignment vector
     */
    std::vector<AssignmentType> matchByBBox(CameraDetectedObjectList&    det_obj_list,
                                            const std::vector<TrackPtr>& current_track);

    /**
     * @brief compute cost matrix
     *
     * @param det_bboxes bounding box of detections
     * @param track_bboxes bounding box of track prediction
     * @param cost_matrix const matrix
     */
    void computeCostMatrix(const std::vector<Box2Type>& det_bboxes, const std::vector<Box2Type>& track_bboxes,
                           holo::numerics::MatrixXT<T>& cost_matrix);

    /**
     * @brief compute cost matrix
     *
     * @param det_bboxes bounding box of detections
     * @param track_bboxes bounding box of track prediction
     * @param cost_matrix const matrix
     * @param small_object small object
     */
    void computeCostMatrix(const std::vector<Box2Type>& det_bboxes, const std::vector<Box2Type>& track_bboxes,
                           holo::numerics::MatrixXT<T>& cost_matrix, bool_t small_object);

    /**
     * @brief Update track stage
     *
     * @param sensor_id camera's sensor id
     */
    void updateTrackStage(const SensorId& sensor_id);

    /**
     * @brief judge whether the det_bbox and trk_bbox are in valid region in image
     *
     * @param det_bbox, detected bbox
     * @param trk_bbox, tracked_bbox
     * @return bool_t, true is in valid region, false is not
     */
    bool_t regionValid(Box2Type const& det_bbox, Box2Type const& trk_bbox) const;

    /**
     * @brief judge whether the bbox's size is valid
     *
     * @param bbox
     * @return bool_t
     */
    bool_t sizeValid(Box2Type const& bbox) const;

    /**
     * @brief judge whether the size change rate of bbox is valid
     *
     * @param det_bbox, detected bbox
     * @param trk_bbox, tracked bbox
     * @return bool_t
     */
    bool_t sizeChangeInValid(Box2Type const& det_bbox, Box2Type const& trk_bbox) const;

    /**
     * @brief judge whether the aspect_ratio of the bbox is valid
     *
     * @param det_bbox, detected bbox
     * @param trk_bbox, tracked bbox
     * @return bool_t
     */
    bool_t aspectRatioInValid(Box2Type const& det_bbox, Box2Type const& trk_bbox) const;

    /**
     * @brief
     *
     * @param lhs_box
     * @param rhs_box
     * @return T
     */
    T computeEIou(Box2Type const& lhs_box, Box2Type const& rhs_box) const;

private:
    T        min_iou_;             ///< min IOU of matched (object, track) pair
    T        min_giou_;            ///< min GIOU of matched (object, track) pair
    T        high_score_;          ///< high score threshold
    T        birth_score_;         ///< birth score threshold
    uint32_t min_hits_;            ///< min time steps the object should continuously detected
    uint32_t max_age_;             ///< max time steps the object can continuously lost
    T        min_size_;            ///< min size the bbox's max(height, width)
    uint32_t max_edge_;            ///< max edge size limit the valid region in image
    uint32_t image_width_;         ///< camera image's width
    T        max_aspect_ratio_;    ///< used to limit the car's orientation
    T        delta_aspect_ratio_;  ///< max aspect_ratio the same object in adjacent frames can diff
    T        distant_max_size_;    ///< used to distinguish distant objects
    T        max_change_ratio_;    ///< max size the object's change ratio can reach
    T        max_delta_occluded_;  ///< max value the same object's occluded_ratio in adjacent frames can diff
    T        max_occluded_ratio_;  ///< max occluded ratio the det_obj can reach

    std::set<uint32_t> vehicle_cat_ids_;

    size_t                        max_window_size_;    ///< max window size of FOAW
    T                             max_delta_;          ///< max delta of FOAW
    T                             min_forget_factor_;  ///< min forget factor of AWF
    CameraTrackStageManagementPtr stage_manage_ptr_;
    TrackContainerType            track_container_;
    HungarianOptimizerType        hungarian_optimizer_;
};
/**
 * @}
 *
 */
}  // namespace perception
}  // namespace holo

#endif  //! HOLO_PERCEPTION_TRACKING_CAMERA_TRACKING_ALGORIGHM_H_
