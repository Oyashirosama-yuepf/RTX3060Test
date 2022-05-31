/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bbox2d_filter.h
 * @brief This header file defines bbox2d filters.
 * @author pengcheng(pengcheng1@holomaitc.com)
 * @date "20201-06-15"
 */

#ifndef HOLO_PERCEPTION_VISION_OBSTACLE_DETECTION_BBOX2D_FILTER_H_
#define HOLO_PERCEPTION_VISION_OBSTACLE_DETECTION_BBOX2D_FILTER_H_

#include <holo/common/sensor_id.h>
#include <holo/perception/common/box_object.h>

#include <algorithm>
#include <list>
#include <map>
#include <memory>
#include <set>

namespace holo
{
namespace perception
{
/**
 * @addtogroup bbox2f filter
 *
 * @{
 */

/**
 * @brief This class define a method to filter some occlude bboxes
 *
 * @tparam T data type
 */
template <typename T, size_t KeyPointsMaxSize>
class FilterBbox2dT
{
public:
    using Ptr                       = std::shared_ptr<FilterBbox2dT<T, KeyPointsMaxSize>>;
    using ConstPtr                  = std::shared_ptr<const FilterBbox2dT<T, KeyPointsMaxSize>>;
    using CameraDetcetedObjType     = BoxObjectT<T, KeyPointsMaxSize>;
    using CameraDetectedObjPtr      = std::shared_ptr<CameraDetcetedObjType>;
    using CameraDetectedObjsPtrList = std::list<CameraDetectedObjPtr>;
    using OccludeRatioArray         = std::vector<T>;

public:
    /**
     * @brief Construct a new FilterBbox2dT object
     *
     * @param config_file config file
     */
    explicit FilterBbox2dT(std::string const& config_file, bool_t only_fc = false)
    {
        if (only_fc)
        {
            initConfigFC(config_file);
        }
        else
        {
            initConfig(config_file);
        }
    }

    /**
     * @brief filter some 2d bbox by the rule(https://holomatic.feishu.cn/docs/doccnHSmeIGv0ruCV7rL1s6AR9b)
     * @param sensor_id sensor_id
     * @param[in, out]  det_obj_list, detected object list
     * @param filter_cate_id the filter categorys
     */
    void Filter(holo::common::SensorId const& sensor_id, CameraDetectedObjsPtrList& det_obj_list,
                std::set<uint32_t> const& filter_cate_id);

    /**
     * @brief filter some bbox for mutil camera image
     * @param det_obj_lists, the input and output
     * @param filter_cate_id the filter categorys
     */
    void MutilCameraFilter(std::vector<CameraDetectedObjsPtrList>& det_obj_lists,
                           std::set<uint32_t> const&               filter_cate_id);

private:
    /**
     * @brief Initialize from config file
     * @details the config file should provide the following things
     * 1. camera names and corresponding camera configuration files
     * 2. tracking configureation file
     *
     * @param cfg_file configuration file
     */
    void initConfig(std::string const& cfg_file) noexcept;

    /**
     * @brief Initialize for front center camera
     *
     * @param cfg_file
     */
    void initConfigFC(std::string const& cfg_file) noexcept;

    /**
     * @brief filter some 2d bbox by the pixels size are less than a threshold
     *
     * @param obj, a 2d detextion object
     * @param filter_cate_id the filter categorys
     * @return holo::bool_t true if the bbox will be filtered out
     */
    holo::bool_t filterBBox2dByPixelSize(CameraDetectedObjPtr const& det_obj, std::set<uint32_t> const& filter_cate_id);

    /**
     * @brief Calculate the occlusion rate of bboxes online
     *
     * @param det_obj_list, detected object list
     * @param[out] iou_ratio, The area occlusion rate of the other bboxes and the bbox
     * @param[out] edge_ratio, The horizontal occlusion rate of the other bboxes and the bbox
     */
    void onlineComputeOccludeRatio(CameraDetectedObjsPtrList const& det_obj_list, OccludeRatioArray& area_occlude_ratio,
                                   OccludeRatioArray& edge_occlude_ratio) const;

    /**
     * @brief Filter out the bbox occluded by the vehicle itself
     *
     * @param obj, a 2d detextion object
     * @param[out] horizontal_occlusion_ratio, The lateral occlusion rate of the vehicle itself and the bbox
     * @param[out] area_occlusion_ratio, The area occlusion rate of the vehicle itself and the bbox
     */
    holo::bool_t filterEgoOcclude(CameraDetectedObjPtr const& det_obj, T& horizontal_occlusion_ratio,
                                  T& area_occlusion_ratio) const;
    /**
     * @brief Keep n filtering results
     *
     * @param det_obj_list，detected object list
     */
    void retainNFilteredResult(CameraDetectedObjsPtrList& det_obj_list);

private:
    T                   filter_bbox_min_pixel_thresh_;
    T                   filter_bbox_iou_score_weight_;
    T                   filter_bbox_edge_score_weight_;
    T                   filter_bbox_online_occlude_threshold_;
    T                   filter_bbox_predict_occlude_threshold_;
    T                   filter_bbox_max_occlude_ratio_;
    T                   filter_bbox_ego_area_occlude_ratio_threshold_;
    T                   filter_bbox_ego_hori_occlude_ratio_threshold_;
    T                   filter_bbox_online_mix_filted_pixel_;
    T                   filter_bbox_truncated_judge_threshold_;
    T                   filter_bbox_truncated_w_h_ratio_threshold_;
    size_t              filter_bbox_max_retain_;
    size_t              filter_mutil_camera_max_retain_;
    size_t              filter_bbox_imgae_width_;
    std::string         camera_name_;
    std::vector<size_t> filter_bbox_car_ego_edge_left_points_;
    std::vector<size_t> filter_bbox_car_ego_edge_right_points_;
    std::vector<T>      filter_muti_camera_weights_;
};

/**
 * @}
 *
 */

}  // namespace perception
}  // namespace holo
#endif  // !HOLO_PERCEPTION_VISION_OBSTACLE_DETECTION_BBOX2D_FILTER_H_
