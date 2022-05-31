/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_tracking_algorithm.hpp
 * @brief This header file defines camera tracking algorithm.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-01-02"
 */

#ifndef HOLO_PERCEPTION_TRACKING_CAMERA_TRACKING_ALGORITHM_HPP_
#define HOLO_PERCEPTION_TRACKING_CAMERA_TRACKING_ALGORITHM_HPP_

#include <holo/perception/algorithm/tracking/camera_tracking_algorithm.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
CameraTrackingAlgorithmT<T>::CameraTrackingAlgorithmT(std::string const&        config_file,
                                                      std::set<uint32_t> const& vehicle_cat_ids)
{
    initialize(config_file);
    stage_manage_ptr_ = std::make_shared<CameraTrackStageManagementType>(min_hits_, max_age_);
    vehicle_cat_ids_  = vehicle_cat_ids;
    LOG(INFO) << "initialize CameraTrackingAlgorithmT ~~~~~~~~~~~~~``";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CameraTrackingAlgorithmT<T>::Track(const SensorId& sensor_id, CameraDetectedObjectList& det_obj_list)
{
    // fetch tracks with sensor_id
    std::vector<std::shared_ptr<TrackT<CameraDetectedObjectType>>> current_tracks;
    track_container_.GetTracks(sensor_id, current_tracks);

    for (auto track : current_tracks)
    {
        dynamic_cast<CameraTrackType*>(track.get())->Predict(false);
    }

    CameraDetectedObjectList high_det_obj_list;
    CameraDetectedObjectList low_det_obj_list;

    for (auto det: det_obj_list)
    {
        if (det->GetClassifyInfo().GetConfidence() > high_score_)
        {
            high_det_obj_list.push_back(det);
        }
        else
        {
            low_det_obj_list.push_back(det);
        }
    }
    // associate camera detected objects with tracks
    associateObjectsWithTracks(sensor_id, high_det_obj_list, current_tracks);

    std::vector<std::shared_ptr<TrackT<CameraDetectedObjectType>>> unmatched_tracks;
    for (auto track: current_tracks)
    {
        if (dynamic_cast<CameraTrackType*>(track.get())->GetTimeSinceUpdate() != 0 && 
            track->GetSensorId() == sensor_id)
        {
            unmatched_tracks.push_back(track);
        }
    }

    associateObjectsWithTracks(sensor_id, low_det_obj_list, unmatched_tracks);

    // update stage
    updateTrackStage(sensor_id);

    // remove terminated track
    track_container_.RemoveTerminatedTrack();

    det_obj_list.clear();

    std::vector<TrackPtr> results;
    track_container_.GetConfirmedTracks(sensor_id, results);
    for (auto track: results)
    {
        CameraDetectedObjectPtr obs_ptr = std::make_shared<CameraDetectedObjectType>(
            const_cast<CameraDetectedObjectType &>(*track->GetNewestObjPtr()));
        det_obj_list.push_back(obs_ptr);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CameraTrackingAlgorithmT<T>::initialize(std::string const& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(GetConfigFileAbsolutePath(config_file));
        min_iou_              = node["min_iou"].as<T>();
        min_giou_             = node["min_giou"].as<T>();
        high_score_           = node["high_score"].as<T>();
        birth_score_          = node["birth_score"].as<T>();
        min_hits_             = node["min_hits"].as<uint32_t>();
        max_age_              = node["max_age"].as<uint32_t>();
        min_size_             = node["min_size"].as<T>();
        max_edge_             = node["max_edge"].as<uint32_t>();
        image_width_          = node["image_width"].as<uint32_t>();
        max_aspect_ratio_     = node["max_aspect_ratio"].as<T>();
        delta_aspect_ratio_   = node["delta_aspect_ratio"].as<T>();
        distant_max_size_     = node["distant_max_size"].as<T>();
        max_change_ratio_     = node["max_change_ratio"].as<T>();
        max_delta_occluded_   = node["max_delta_occluded"].as<T>();
        max_occluded_ratio_   = node["max_occluded_ratio"].as<T>();
        max_window_size_      = node["max_window_size"].as<size_t>();
        max_delta_            = node["max_delta"].as<T>();
        min_forget_factor_    = node["min_forget_factor"].as<T>();
    }
    catch (const std::exception& e)
    {
        LOG(FATAL) << "Camera tracking algorithm initialize failed : " << config_file << e.what();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CameraTrackingAlgorithmT<T>::associateObjectsWithTracks(const SensorId&           sensor_id,
                                                             CameraDetectedObjectList& det_obj_list,
                                                             std::vector<TrackPtr>&    current_tracks)
{
    std::map<uint32_t, CameraDetectedObjectList> det_map;
    std::map<uint32_t, std::vector<TrackPtr>>    trk_map;
    for (auto const& det : det_obj_list)
    {
        if (det->IsFiltered())
        {
            continue;
        }
        uint32_t cls = det->GetClassifyInfo().GetCategoryId();
        if (det_map.find(cls) != det_map.end())
        {
            det_map[cls].push_back(det);
        }
        else
        {
            det_map[cls] = CameraDetectedObjectList{det};
        }
    }
    for (auto const& trk : current_tracks)
    {
        if (trk->GetSensorId() != sensor_id)
        {
            continue;
        }

        auto his_list = trk->GetTrack();
        if (his_list.size() > 0U)
        {
            auto cls = his_list.front()->GetClassifyInfo().GetCategoryId();
            if (trk_map.find(cls) != trk_map.end())
            {
                trk_map[cls].push_back(trk);
            }
            else
            {
                trk_map[cls] = std::vector<TrackPtr>{trk};
            }
        }
    }

    for (auto det_iter = det_map.cbegin(); det_iter != det_map.end(); det_iter++)
    {
        auto cls = det_iter->first;
        bool_t small_object;
        if (cls < 3U)
        {
            small_object = false;
        }
        else
        {
            small_object = true;
        }
        if (det_map.find(cls) == det_map.end())
        {
            det_map[cls] = CameraDetectedObjectList{};
        }
        CameraDetectedObjectList det_list = det_map[cls];
        std::vector<TrackPtr>    trk_list = trk_map[cls];

        std::vector<CameraDetectedObjectPtr> det_objs;
        for (auto det: det_list)
        {
            det_objs.push_back(det);
        }

        std::vector<TrackPtr> confirmed_track;
        std::vector<TrackPtr> unconfirmed_track;
        std::vector<TrackPtr> lost_track;

        for (auto track : trk_list)
        {
            if (track->GetStage() == Stage::UNCONFIRMED)
            {
                unconfirmed_track.push_back(track);
            }
            else if (track->GetStage() == Stage::CONFIRMED)
            {
                confirmed_track.push_back(track);
            }
            else if (track->GetStage() == Stage::LOST){
                lost_track.push_back(track);
            }
        }

        // match tracks with detected objects
        std::vector<CameraDetectedObjectPtr> unmatched_dets;
        std::vector<CameraDetectedObjectPtr> matching_dets = det_objs;
        std::vector<TrackPtr> matching_tracks = confirmed_track;

        matchStage(matching_dets, matching_tracks, unmatched_dets, small_object);

        matching_dets = unmatched_dets;
        matching_tracks = unconfirmed_track;
        unmatched_dets.clear();
        matchStage(matching_dets, matching_tracks, unmatched_dets, small_object);

        matching_dets = unmatched_dets;
        matching_tracks = lost_track;
        unmatched_dets.clear();
        matchStage(matching_dets, matching_tracks, unmatched_dets, small_object);

        for(auto det: unmatched_dets)
        {
            if (det->GetClassifyInfo().GetConfidence() > birth_score_)
            {
                TrackId  uid = static_cast<TrackId>(UidGenerator::GetInstance().GetUid());
                TrackPtr new_track_ptr =
                    std::make_shared<CameraTrackType>(uid, Stage::UNCONFIRMED, sensor_id, det->GetTimestamp(),
                                                    det, max_window_size_, max_delta_, min_forget_factor_);
                // add to track container
                track_container_.AddTrack(new_track_ptr);
                det->SetObjectId(uid);
            }
        }

    }
}

template <typename T>
void CameraTrackingAlgorithmT<T>::matchStage(const std::vector<CameraDetectedObjectPtr>& matching_dets,
                                             const std::vector<TrackPtr>& matching_tracks,
                                             std::vector<CameraDetectedObjectPtr>& unmatched_dets,
                                             bool small_object)
{
    // fetch detected object bboxes
    std::vector<Box2Type> det_bboxes;
    for (auto det_obj_ptr : matching_dets)
    {
        const Box2Type box = det_obj_ptr->GetBox2();
        det_bboxes.push_back(box);
    }

    // each track predict a new bbox
    std::vector<Box2Type> track_bboxes;
    for (auto & track : matching_tracks)
    {
        const Box2Type box = track->GetNewestObjPtr()->GetBox2();
        track_bboxes.push_back(box);
    }
    std::vector<AssignmentType> assignment = matchByBBox(det_bboxes, track_bboxes, small_object);
    assert(assignment.size() == det_bboxes.size());

    std::vector<TrackPtr> matched_tracks;

    for (size_t i = 0U; i < assignment.size(); ++i)
    {
        if (assignment[i] < 0)
        {
            unmatched_dets.push_back(matching_dets[i]);
        }
        else
        {
            // find the matched track and update with the object
            size_t track_index = static_cast<size_t>(assignment[i]);
            if (track_index < matching_tracks.size())
            {
                bool_t timestamp_newer =
                    dynamic_cast<CameraTrackType*>(matching_tracks[track_index].get())->Update(matching_dets[i], false);

                if (timestamp_newer == true)
                {
                    // if the timestamp is newer, set id for the object
                    matching_dets[i]->SetObjectId(matching_tracks[track_index]->GetId());
                    matching_dets[i]->SetAge(dynamic_cast<CameraTrackType*>(matching_tracks[track_index].get())->GetAge());
                }
            }
            else
            {
                throw std::runtime_error("Assignment index out of range");
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::vector<typename CameraTrackingAlgorithmT<T>::AssignmentType> CameraTrackingAlgorithmT<T>::matchByBBox(
    const std::vector<Box2Type>& det_bboxes, const std::vector<Box2Type>& track_bboxes)
{
    // special cases
    if (det_bboxes.empty() == true)
    {
        return std::vector<AssignmentType>();
    }
    if (track_bboxes.empty() == true)
    {
        return std::vector<AssignmentType>(det_bboxes.size(), -1);
    }

    holo::numerics::MatrixXT<T> cost_matrix(det_bboxes.size(), track_bboxes.size());
    computeCostMatrix(det_bboxes, track_bboxes, cost_matrix);

    return hungarian_optimizer_.FindOptimalAssignment(cost_matrix);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::vector<typename CameraTrackingAlgorithmT<T>::AssignmentType> CameraTrackingAlgorithmT<T>::matchByBBox(
    const std::vector<Box2Type>& det_bboxes, const std::vector<Box2Type>& track_bboxes, bool_t small_object)
{
    // special cases
    if (det_bboxes.empty() == true)
    {
        return std::vector<AssignmentType>();
    }
    if (track_bboxes.empty() == true)
    {
        return std::vector<AssignmentType>(det_bboxes.size(), -1);
    }

    holo::numerics::MatrixXT<T> cost_matrix(det_bboxes.size(), track_bboxes.size());

    computeCostMatrix(det_bboxes, track_bboxes, cost_matrix, small_object);

    return hungarian_optimizer_.FindOptimalAssignment(cost_matrix);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::vector<typename CameraTrackingAlgorithmT<T>::AssignmentType> CameraTrackingAlgorithmT<T>::matchByBBox(
    CameraDetectedObjectList& det_obj_list, const std::vector<TrackPtr>& current_tracks)
{
    // special cases
    if (det_obj_list.empty() == true)
    {
        return std::vector<AssignmentType>();
    }
    if (current_tracks.empty() == true)
    {
        return std::vector<AssignmentType>(det_obj_list.size(), -1);
    }

    // fetch detected object bboxes
    std::vector<Box2Type> det_bboxes;
    for (auto det_obj_ptr : det_obj_list)
    {
        const Box2Type box = det_obj_ptr->GetBox2();
        det_bboxes.push_back(box);
        if (det_obj_ptr->GetOccludedRatio() > max_occluded_ratio_ || !sizeValid(box))
        {
            det_obj_ptr->SetFiltered(true);
        }
    }

    // each track predict a new bbox
    std::vector<Box2Type> track_bboxes;
    for (auto track : current_tracks)
    {
        const Box2Type box = dynamic_cast<CameraTrackType*>(track.get())->Predict(false);
        track_bboxes.push_back(box);
    }

    holo::numerics::MatrixXT<T> cost_matrix(det_bboxes.size(), track_bboxes.size());
    computeCostMatrix(det_bboxes, track_bboxes, cost_matrix);

    // update cost_matrix
    size_t i = 0U;
    for (auto det_obj_ptr : det_obj_list)
    {
        Box2Type det_bbox = det_obj_ptr->GetBox2();
        for (size_t j = 0U; j < current_tracks.size(); j++)
        {
            Box2Type  trk_bbox = track_bboxes[j];
            float32_t occluded_ratio_diff =
                std::abs(det_obj_ptr->GetOccludedRatio() - current_tracks[j]->GetNewestObjPtr()->GetOccludedRatio());
            if (cost_matrix.At(i, j) < (1 - min_iou_) && regionValid(det_bbox, trk_bbox) && sizeValid(det_bbox) &&
                sizeValid(trk_bbox) &&
                (occluded_ratio_diff > max_delta_occluded_ || aspectRatioInValid(det_bbox, trk_bbox) ||
                 sizeChangeInValid(det_bbox, trk_bbox)))
            {
                cost_matrix.At(i, j) = std::numeric_limits<T>::infinity();
            }
        }
        i++;
    }

    return hungarian_optimizer_.FindOptimalAssignment(cost_matrix);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CameraTrackingAlgorithmT<T>::computeCostMatrix(const std::vector<Box2Type>& det_bboxes,
                                                    const std::vector<Box2Type>& track_bboxes,
                                                    holo::numerics::MatrixXT<T>& cost_matrix)
{
    for (size_t i = 0U; i < det_bboxes.size(); ++i)
    {
        for (size_t j = 0U; j < track_bboxes.size(); ++j)
        {
            T iou_value = det_bboxes[i].ComputeIoU(track_bboxes[j]);

            if (iou_value > static_cast<T>(1.0))
            {
                iou_value = static_cast<T>(1.0);
            }
            cost_matrix(i, j) =
                (iou_value > min_iou_) ? static_cast<T>(1.0) - iou_value : std::numeric_limits<T>::infinity();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CameraTrackingAlgorithmT<T>::computeCostMatrix(const std::vector<Box2Type>& det_bboxes,
                                                    const std::vector<Box2Type>& track_bboxes,
                                                    holo::numerics::MatrixXT<T>& cost_matrix, bool_t small_object)
{
    if (!small_object)
    {
        for (size_t i = 0U; i < det_bboxes.size(); ++i)
        {
            for (size_t j = 0U; j < track_bboxes.size(); ++j)
            {
                T iou_value = det_bboxes[i].ComputeIoU(track_bboxes[j]);
                if (iou_value > static_cast<T>(1.0))
                {
                    iou_value = static_cast<T>(1.0);
                }
                cost_matrix(i, j) =
                    (iou_value > min_iou_) ? static_cast<T>(1.0) - iou_value : std::numeric_limits<T>::infinity();
            }
        }
    }
    else
    {
        for (size_t i = 0U; i < det_bboxes.size(); ++i)
        {
            for (size_t j = 0U; j < track_bboxes.size(); ++j)
            {
                T iou_value = det_bboxes[i].ComputeGIoU(track_bboxes[j]);
                if (iou_value > static_cast<T>(1.0))
                {
                    iou_value = static_cast<T>(1.0);
                }
                cost_matrix(i, j) =
                    (iou_value > min_giou_) ? static_cast<T>(1.0) - iou_value : std::numeric_limits<T>::infinity();
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CameraTrackingAlgorithmT<T>::updateTrackStage(const SensorId& sensor_id)
{
    std::vector<TrackPtr> current_tracks;
    track_container_.GetTracks(sensor_id, current_tracks);
    for (auto track : current_tracks)
    {
        stage_manage_ptr_->UpdateTrackStage(*track);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t CameraTrackingAlgorithmT<T>::regionValid(Box2Type const& det_bbox, Box2Type const& trk_bbox) const
{
    bool_t valid_det =
        (det_bbox.GetX() > max_edge_) && (det_bbox.GetX() + det_bbox.GetWidth()) < (image_width_ - max_edge_);
    bool_t valid_trk =
        (trk_bbox.GetX() > max_edge_) && (trk_bbox.GetX() + trk_bbox.GetWidth()) < (image_width_ - max_edge_);
    return valid_det && valid_trk;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t CameraTrackingAlgorithmT<T>::sizeValid(Box2Type const& bbox) const
{
    return (std::max(bbox.GetWidth(), bbox.GetHeight()) >= min_size_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t CameraTrackingAlgorithmT<T>::sizeChangeInValid(Box2Type const& det_bbox, Box2Type const& trk_bbox) const
{
    bool_t small_enough = std::max(det_bbox.GetWidth(), det_bbox.GetHeight()) < distant_max_size_ ||
                          std::max(trk_bbox.GetWidth(), trk_bbox.GetHeight()) < distant_max_size_;

    float32_t change_ratio = std::max(std::abs(det_bbox.GetWidth() - trk_bbox.GetWidth()) / det_bbox.GetWidth(),
                                      std::abs(det_bbox.GetHeight() - trk_bbox.GetHeight()) / det_bbox.GetHeight());
    return small_enough && (change_ratio > max_change_ratio_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t CameraTrackingAlgorithmT<T>::aspectRatioInValid(Box2Type const& det_bbox, Box2Type const& trk_bbox) const
{
    T det_aspect_ratio   = det_bbox.GetWidth() / det_bbox.GetHeight();
    T trk_aspect_ratio   = trk_bbox.GetWidth() / trk_bbox.GetHeight();
    T delta_aspect_ratio = std::abs(det_aspect_ratio - trk_aspect_ratio);
    return (det_aspect_ratio < max_aspect_ratio_ || trk_aspect_ratio < max_aspect_ratio_) &&
           (delta_aspect_ratio > delta_aspect_ratio_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
T CameraTrackingAlgorithmT<T>::computeEIou(Box2Type const& det_bbox, Box2Type const& trk_bbox) const
{
    T    iou              = det_bbox.ComputeIoU(trk_bbox);
    auto det_center_point = det_bbox.GetCenterPoint();
    auto trk_center_point = trk_bbox.GetCenterPoint();
    T    dis_center       = pow(det_center_point.GetX() - trk_center_point.GetX(), 2) +
                   pow(det_center_point.GetY() - trk_center_point.GetY(), 2);
    auto convex_box = det_bbox.GetMinConvexBox(trk_bbox);
    auto c2         = pow(convex_box.GetWidth(), 2) + pow(convex_box.GetHeight(), 2);
    T    w_dis      = pow(det_bbox.GetWidth() - trk_bbox.GetWidth(), 2);
    T    h_dis      = pow(det_bbox.GetHeight() - trk_bbox.GetHeight(), 2);
    T    cw2        = pow(convex_box.GetWidth(), 2);
    T    ch2        = pow(convex_box.GetHeight(), 2);

    return iou - (dis_center / c2 + w_dis / cw2 + h_dis / ch2);
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_CAMERA_TRACKING_ALGORITHM_HPP_
