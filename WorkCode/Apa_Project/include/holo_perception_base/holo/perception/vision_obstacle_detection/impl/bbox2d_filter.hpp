/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bbox2d_filter.hpp
 * @brief The implementation of template class FilterBbox2dT
 * @author pengcheng(pengcheng1@holomaitc.com)
 * @date "2021-06-15"
 */
#ifndef HOLO_PERCEPTION_VISION_OBSTACLE_DETECTION_IMPL_BBOX2D_FILTER_HPP_
#define HOLO_PERCEPTION_VISION_OBSTACLE_DETECTION_IMPL_BBOX2D_FILTER_HPP_

#include <glog/logging.h>
#include <holo/perception/vision_obstacle_detection/bbox2d_filter.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <limits>

namespace holo
{
namespace perception
{
template <typename T, size_t KeyPointsMaxSize>
void FilterBbox2dT<T, KeyPointsMaxSize>::initConfigFC(std::string const& cfg_file) noexcept
{
    std::string filter_bbox_car_ego_edge_cfg;
    try
    {
        holo::yaml::Node node                      = holo::yaml::LoadFile(GetConfigFileAbsolutePath(cfg_file));
        filter_bbox_min_pixel_thresh_              = node["filter_bbox_min_pixel_thresh"].as<T>();
        filter_bbox_iou_score_weight_              = node["filter_bbox_iou_score_weight"].as<T>();
        filter_bbox_edge_score_weight_             = node["filter_bbox_edge_score_weight"].as<T>();
        filter_bbox_online_occlude_threshold_      = node["filter_bbox_online_occlude_threshold"].as<T>();
        filter_bbox_predict_occlude_threshold_     = node["filter_bbox_predict_occlude_threshold"].as<T>();
        filter_bbox_max_occlude_ratio_             = node["filter_bbox_max_occlude_ratio"].as<T>();
        filter_bbox_online_mix_filted_pixel_       = node["filter_bbox_online_mix_filted_pixel"].as<T>();
        filter_bbox_max_retain_                    = node["filter_bbox_max_retain"].as<size_t>();
        filter_bbox_truncated_judge_threshold_     = node["filter_bbox_truncated_judge_threshold"].as<T>();
        filter_bbox_truncated_w_h_ratio_threshold_ = node["filter_bbox_truncated_w_h_ratio_threshold"].as<T>();
        filter_bbox_imgae_width_                   = node["filter_bbox_imgae_width"].as<size_t>();
    }
    catch (const std::exception& e)
    {
        LOG(FATAL) << "InitConfig Failure: " << cfg_file << e.what() << std::endl;
    }
}

template <typename T, size_t KeyPointsMaxSize>
void FilterBbox2dT<T, KeyPointsMaxSize>::initConfig(std::string const& cfg_file) noexcept
{
    std::string filter_bbox_car_ego_edge_cfg;
    try
    {
        holo::yaml::Node node                         = holo::yaml::LoadFile(GetConfigFileAbsolutePath(cfg_file));
        filter_bbox_min_pixel_thresh_                 = node["filter_bbox_min_pixel_thresh"].as<T>();
        filter_bbox_iou_score_weight_                 = node["filter_bbox_iou_score_weight"].as<T>();
        filter_bbox_edge_score_weight_                = node["filter_bbox_edge_score_weight"].as<T>();
        filter_bbox_online_occlude_threshold_         = node["filter_bbox_online_occlude_threshold"].as<T>();
        filter_bbox_predict_occlude_threshold_        = node["filter_bbox_predict_occlude_threshold"].as<T>();
        filter_bbox_max_occlude_ratio_                = node["filter_bbox_max_occlude_ratio"].as<T>();
        filter_bbox_ego_area_occlude_ratio_threshold_ = node["filter_bbox_ego_area_occlude_ratio_threshold"].as<T>();
        filter_bbox_ego_hori_occlude_ratio_threshold_ = node["filter_bbox_ego_hori_occlude_ratio_threshold"].as<T>();
        filter_bbox_online_mix_filted_pixel_          = node["filter_bbox_online_mix_filted_pixel"].as<T>();
        filter_bbox_max_retain_                       = node["filter_bbox_max_retain"].as<size_t>();
        filter_bbox_car_ego_edge_cfg                  = node["filter_bbox_car_ego_edge_cfg"].as<std::string>();
        filter_muti_camera_weights_                   = node["filter_muti_camera_weights"].as<std::vector<T>>();
        filter_mutil_camera_max_retain_               = node["filter_mutil_camera_max_retain"].as<size_t>();
        filter_bbox_truncated_judge_threshold_        = node["filter_bbox_truncated_judge_threshold"].as<T>();
        filter_bbox_truncated_w_h_ratio_threshold_    = node["filter_bbox_truncated_w_h_ratio_threshold"].as<T>();
        filter_bbox_imgae_width_                      = node["filter_bbox_imgae_width"].as<size_t>();
        node = holo::yaml::LoadFile(GetConfigFileAbsolutePath(filter_bbox_car_ego_edge_cfg));
        filter_bbox_car_ego_edge_left_points_ = node["filter_bbox_car_ego_edge_left_points"].as<std::vector<size_t>>();
        filter_bbox_car_ego_edge_right_points_ =
            node["filter_bbox_car_ego_edge_right_points"].as<std::vector<size_t>>();
    }
    catch (const std::exception& e)
    {
        LOG(FATAL) << "InitConfig Failure: " << cfg_file << e.what() << std::endl;
    }
}

template <typename T, size_t KeyPointsMaxSize>
holo::bool_t FilterBbox2dT<T, KeyPointsMaxSize>::filterBBox2dByPixelSize(CameraDetectedObjPtr const& det_obj,
                                                                         std::set<uint32_t> const&   filter_cate_id)
{
    holo::bool_t min_pixel_filter = std::max(det_obj->GetBox2().GetHeight(), det_obj->GetBox2().GetWidth()) <=
                                            (filter_bbox_min_pixel_thresh_ / 4.0f) ?
                                        true :
                                        false;

    uint32_t     category_id      = det_obj->GetClassifyInfo().GetCategoryId();
    holo::bool_t truncated_filter = false;
    if (0 != filter_cate_id.count(category_id))
    {
        min_pixel_filter =
            std::min(det_obj->GetBox2().GetHeight(), det_obj->GetBox2().GetWidth()) <= filter_bbox_min_pixel_thresh_ ?
                true :
                false;
        T            left         = det_obj->GetBox2().GetX();
        T            width        = det_obj->GetBox2().GetWidth();
        T            height       = det_obj->GetBox2().GetHeight();
        T            right        = left + width;
        holo::bool_t is_truncated = (left <= filter_bbox_truncated_judge_threshold_) ||
                                    (abs(right - filter_bbox_imgae_width_) <= filter_bbox_truncated_judge_threshold_);
        if (is_truncated)
        {
            truncated_filter = (1.f * height / width) > filter_bbox_truncated_w_h_ratio_threshold_ ? true : false;
        }
    }
    holo::bool_t predict_occlude_filter =
        det_obj->GetOccludedRatio() > filter_bbox_predict_occlude_threshold_ ? true : false;
    return (min_pixel_filter || predict_occlude_filter || truncated_filter);
}

template <typename T, size_t KeyPointsMaxSize>
void FilterBbox2dT<T, KeyPointsMaxSize>::onlineComputeOccludeRatio(CameraDetectedObjsPtrList const& det_obj_list,
                                                                   OccludeRatioArray&               area_occlude_ratio,
                                                                   OccludeRatioArray& edge_occlude_ratio) const
{
    size_t objs_size = det_obj_list.size();
    if (objs_size == 0U)
    {
        return;
    }
    area_occlude_ratio.clear();
    edge_occlude_ratio.clear();
    std::vector<CameraDetectedObjPtr> det_obj_array;
    for (auto iter = det_obj_list.begin(); iter != det_obj_list.end(); iter++)
    {
        det_obj_array.push_back(*iter);
    }
    for (size_t i = 0U; i < objs_size; i++)
    {
        T occlude_area_occlude_ratio = static_cast<T>(0.0);
        T occlude_edge_occlude_ratio = static_cast<T>(0.0);
        for (size_t j = i + 1U; j < objs_size; j++)
        {
            CameraDetectedObjPtr bbox_ref = det_obj_array[i];
            CameraDetectedObjPtr bbox_cur = det_obj_array[j];

            T intersection_area = bbox_ref->GetBox2().GetIntersectionArea(bbox_cur->GetBox2());
            T inter_width       = bbox_ref->GetBox2().GetIntersectionBox(bbox_cur->GetBox2()).GetWidth();
            occlude_edge_occlude_ratio += inter_width / bbox_ref->GetBox2().GetWidth();
            occlude_area_occlude_ratio += intersection_area / bbox_ref->GetBox2().GetArea();
        }
        area_occlude_ratio.push_back(occlude_area_occlude_ratio);
        edge_occlude_ratio.push_back(occlude_edge_occlude_ratio);
    }
}

template <typename T, size_t KeyPointsMaxSize>
holo::bool_t FilterBbox2dT<T, KeyPointsMaxSize>::filterEgoOcclude(CameraDetectedObjPtr const& obj,
                                                                  T& horizontal_occlusion_ratio,
                                                                  T& area_occlusion_ratio) const
{
    T left   = obj->GetBox2().GetX();
    T top    = obj->GetBox2().GetY();
    T height = obj->GetBox2().GetHeight();
    T width  = obj->GetBox2().GetWidth();
    T right  = left + width;
    T bottom = top + height;
    T ref_x  = static_cast<T>(0.0);
    if ("CAMERA_SIDE_REAR_LEFT" == camera_name_)
    {
        ref_x = left;
    }
    else if ("CAMERA_SIDE_REAR_RIGHT" == camera_name_)
    {
        ref_x = right;
    }
    else
    {
        return false;
    }
    T max_horizontal_occlusion = static_cast<T>(0.0);
    T occlusion_integral       = static_cast<T>(0.0);
    for (size_t height_index = top; height_index <= bottom; height_index++)
    {
        T intersect = static_cast<T>(0.0);
        if ("CAMERA_SIDE_REAR_LEFT" == camera_name_)
        {
            intersect = static_cast<T>(filter_bbox_car_ego_edge_left_points_[height_index]) - ref_x;
        }
        else
        {
            intersect = ref_x - static_cast<T>(filter_bbox_car_ego_edge_right_points_[height_index]);
        }
        occlusion_integral += std::max(intersect, static_cast<T>(0.0));
        max_horizontal_occlusion = std::max(max_horizontal_occlusion, intersect);
    }
    horizontal_occlusion_ratio = max_horizontal_occlusion / width;
    area_occlusion_ratio       = occlusion_integral / (width * height);
    return true;
}

template <typename T, size_t KeyPointsMaxSize>
void FilterBbox2dT<T, KeyPointsMaxSize>::retainNFilteredResult(CameraDetectedObjsPtrList& det_obj_list)
{
    det_obj_list.sort([](const CameraDetectedObjPtr det1, const CameraDetectedObjPtr det2) {
        T area1    = det1->GetBox2().GetArea();
        T area2    = det2->GetBox2().GetArea();
        T occlude1 = static_cast<T>(1.0) - det1->GetOccludedRatio();
        T occlude2 = static_cast<T>(1.0) - det2->GetOccludedRatio();
        if (det1->GetOccludedRatio() < 1e-3)
        {
            return true;
        }
        else if (det2->GetOccludedRatio() < 1e-3)
        {
            return false;
        }
        else
        {
            return (occlude1 * area1) > (occlude2 * area2);
        }
    });
    size_t retain_size = 1U;
    for (typename CameraDetectedObjsPtrList::iterator iter = det_obj_list.begin(); iter != det_obj_list.end(); ++iter)
    {
        if ((*iter)->IsFiltered())
        {
            continue;
        }
        if (retain_size > filter_bbox_max_retain_)
        {
            (*iter)->SetFiltered(true);
            (*iter)->SetOccludedRatio(static_cast<T>(1.f));
            continue;
        }
        ++retain_size;
    }
}

template <typename T, size_t KeyPointsMaxSize>
void FilterBbox2dT<T, KeyPointsMaxSize>::Filter(holo::common::SensorId const& sensor_id,
                                                CameraDetectedObjsPtrList&    det_obj_list,
                                                std::set<uint32_t> const&     filter_cate_id)
{
    if (sensor_id.GetCategory() != holo::common::SensorId::Category::CAMERA)
    {
        LOG(WARNING) << "the filter only using for image bbox2d";
        return;
    }
    if (sensor_id.GetLocation().GetLocationX() == holo::common::VehicleLocation::Location::LEFT &&
        sensor_id.GetLocation().GetPlane() == holo::common::VehicleLocation::Plane::LEFT)
    {
        camera_name_ = "CAMERA_SIDE_REAR_LEFT";
    }
    else if (sensor_id.GetLocation().GetLocationX() == holo::common::VehicleLocation::Location::RIGHT &&
             sensor_id.GetLocation().GetPlane() == holo::common::VehicleLocation::Plane::RIGHT)
    {
        camera_name_ = "CAMERA_SIDE_REAR_RIGHT";
    }
    else
    {
        camera_name_ = "CAMERA_UNKOWN";
    }
    det_obj_list.sort([](const CameraDetectedObjPtr det1, const CameraDetectedObjPtr det2) {
        T bottom1 = det1->GetBox2().GetY() + det1->GetBox2().GetHeight();
        T bottom2 = det2->GetBox2().GetY() + det2->GetBox2().GetHeight();
        return bottom1 < bottom2;
    });
    OccludeRatioArray occlude_iou_ratio;
    OccludeRatioArray occlude_edge_ratio;
    onlineComputeOccludeRatio(det_obj_list, occlude_iou_ratio, occlude_edge_ratio);
    size_t obj_id = 0U;
    for (typename std::list<CameraDetectedObjPtr>::iterator iter = det_obj_list.begin(); iter != det_obj_list.end();
         ++iter, ++obj_id)
    {
        if (filterBBox2dByPixelSize(*iter, filter_cate_id))
        {
            (*iter)->SetFiltered(true);
            (*iter)->SetOccludedRatio(static_cast<T>(1.f));
            continue;
        }
        uint32_t category_id = (*iter)->GetClassifyInfo().GetCategoryId();

        T occlude_ratio = (filter_bbox_edge_score_weight_ * occlude_edge_ratio[obj_id] +
                           filter_bbox_iou_score_weight_ * occlude_iou_ratio[obj_id]) /
                          (filter_bbox_edge_score_weight_ + filter_bbox_iou_score_weight_);

        T bbox2d_width  = (*iter)->GetBox2().GetWidth();
        T new_threshold = filter_bbox_online_occlude_threshold_ *
                          std::log2f(bbox2d_width / filter_bbox_online_mix_filted_pixel_);  // when the width of bbox
                                                                                            // 15 pixel, the
                                                                                            // new_threshold is 0.0
        new_threshold = std::max<T>(new_threshold, static_cast<T>(0.0f));
        if (new_threshold < static_cast<T>(0.0f))
        {
            new_threshold = static_cast<T>(0.0f);
        }
        if (new_threshold >= filter_bbox_max_occlude_ratio_)
        {
            new_threshold = filter_bbox_max_occlude_ratio_;
        }

        if (occlude_ratio > new_threshold && 0U != filter_cate_id.count(category_id))
        {
            (*iter)->SetFiltered(true);
            (*iter)->SetOccludedRatio(static_cast<T>(1.f));
        }
        else if (0U == filter_cate_id.count(category_id))
        {
            (*iter)->SetFiltered(false);
            (*iter)->SetOccludedRatio(std::min<T>(occlude_ratio, static_cast<T>(0.5f)));
        }
        else
        {
            T horizontal_occlusion_ratio = static_cast<T>(0.0f);
            T area_occlusion_ratio       = static_cast<T>(0.0f);
            if (filterEgoOcclude(*iter, horizontal_occlusion_ratio, area_occlusion_ratio))
            {
                holo::bool_t filtered_status =
                    horizontal_occlusion_ratio > filter_bbox_ego_hori_occlude_ratio_threshold_ &&
                            area_occlusion_ratio > filter_bbox_ego_area_occlude_ratio_threshold_ ?
                        true :
                        false;
                if (true == filtered_status)
                {
                    (*iter)->SetFiltered(true);
                    (*iter)->SetOccludedRatio(static_cast<T>(1.f));
                }
                else
                {
                    (*iter)->SetOccludedRatio(std::max<T>(
                        occlude_ratio, (horizontal_occlusion_ratio + area_occlusion_ratio) / static_cast<T>(2.f)));
                    (*iter)->SetFiltered(false);
                }
            }
            else
            {
                (*iter)->SetOccludedRatio(occlude_ratio);
                (*iter)->SetFiltered(false);
            }
        }
    }
    retainNFilteredResult(det_obj_list);
}

template <typename T, size_t KeyPointsMaxSize>
void FilterBbox2dT<T, KeyPointsMaxSize>::MutilCameraFilter(std::vector<CameraDetectedObjsPtrList>& det_obj_lists,
                                                           std::set<uint32_t> const&               filter_cate_id)
{
    std::map<std::pair<size_t, size_t>, T> multil_camera_merge_scores;
    for (size_t camera_id = 0U; camera_id < det_obj_lists.size(); ++camera_id)
    {
        auto   iter  = det_obj_lists[camera_id].begin();
        size_t index = 0;
        while (iter != det_obj_lists[camera_id].end())
        {
            CameraDetectedObjPtr camera_det_instance_ptr = *iter;
            uint32_t             category_id             = camera_det_instance_ptr->GetClassifyInfo().GetCategoryId();
            if ((!(*iter)->IsFiltered()) && (0U != filter_cate_id.count(category_id)))
            {
                // (void)canera_det_instance_ptr;
                T score = static_cast<T>(0.0f);
                if (camera_id == 3U && (camera_det_instance_ptr->GetOccludedRatio() < 0.8f))
                {
                    score = std::numeric_limits<T>::max();
                }
                else
                {
                    score = camera_det_instance_ptr->GetBox2().GetArea() *
                            (static_cast<T>(1.0f) - camera_det_instance_ptr->GetOccludedRatio()) *
                            filter_muti_camera_weights_[camera_id];
                }

                multil_camera_merge_scores.insert(std::make_pair(std::make_pair(camera_id, index), score));
            }
            ++iter;
            ++index;
        }
    }
    if (multil_camera_merge_scores.size() <= filter_mutil_camera_max_retain_)
    {
        return;
    }
    std::multimap<T, std::pair<size_t, size_t>, std::greater<T>> reverse_map;
    for (auto iter = multil_camera_merge_scores.begin(); iter != multil_camera_merge_scores.end(); ++iter)
    {
        reverse_map.insert(std::make_pair(iter->second, iter->first));
    }
    size_t skip_counter = 0U;
    for (auto iter = reverse_map.begin(); iter != reverse_map.end(); ++iter, ++skip_counter)
    {
        if (skip_counter < filter_mutil_camera_max_retain_)
        {
            continue;
        }
        std::pair<size_t, size_t> position    = iter->second;
        size_t                    camera_id   = position.first;
        size_t                    instance_id = position.second;
        auto                      it          = det_obj_lists[camera_id].begin();
        size_t                    counter     = 0U;
        while (counter < instance_id)
        {
            ++it;
            ++counter;
        }
        (*it)->SetFiltered(true);
    }
}
}  // namespace perception
}  // namespace holo
#endif  // !HOLO_PERCEPTION_VISION_OBSTACLE_DETECTION_IMPL_BBOX2D_FILTER_HPP_
