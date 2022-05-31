/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file detection_point_cloud_interface.h
 * @brief This header file defines detection point cloud interface
 * @author liangyong(liangyong@holomatic.com)
 * @date "2021-09-26"
 */

#ifndef HOLO_DNN_DETECTION_LIDAR_INTERFACE_H_
#define HOLO_DNN_DETECTION_LIDAR_INTERFACE_H_
#include <holo/perception/common/box2d.h>
#include <holo/perception/common/box_object.h>

#include <iostream>

#include "holo/dnn/interface.h"

namespace holo
{
namespace dnn
{
class DetectionLidarInterface : public DnnInterface
{
public:
    using BBox         = holo::perception::Box2Df;
    using BoxObject    = holo::perception::BoxObjectf;
    using ClassifyInfo = holo::perception::ClassifyInfo;
    using OutputType   = std::vector<std::vector<BoxObject>>;

public:
    virtual ~DetectionLidarInterface(){};
    /**
     * @brief init dnn with app on target platform based on yaml config
     *
     * @param config_yaml_path config_yaml_path app config yaml path
     * @return success or fail
     */
    virtual holo::bool_t Init(std::string const& config_yaml_path) = 0;

    /**
     * @brief preprocess data
     *
     * @param array_data_ptr data pointer, maybe opencv mat or raw nv12 data
     * @return
     */
    virtual holo::bool_t PreProcess(const void* const array_data_ptr) = 0;

    /**
     * @brief inference on target platform
     * @param array_data_ptr input
     * @param array_output_ptr output
     *
     * @param
     */
    virtual holo::bool_t Inference(const void* const array_data_ptr, void* const array_output_ptr) = 0;

    /**
     * @brief post process
     * @param array_output_ptr output data pointer, maybe vector<bbox2d> type or something else
     * @return
     */
    virtual holo::bool_t PostProcess(void* const array_output_ptr) = 0;

    /**
     * @brief show dnn env
     * @param
     * @return
     */
    virtual void ShowDnnEnv() override;

    /**
     * @brief init dnn with app on target platform based on yaml config
     *
     * @param cfg_file config_yaml_path app config yaml path
     * @return success or fail
     */
    void InitConfig(const std::string& cfg_file);

    /**
     * @brief detection 2d decoder
     * @param array_output_ptr output
     * @param sigmoid_heatmap sigmoid heatmap
     * @param max_pooling_map max_pooling_map
     * @param wh wh
     * @param center_offset center_offset
     * @return
     */

public:
    /// app config
    uint32_t                 max_pillars_;
    uint32_t                 max_points_in_pillar_;
    uint32_t                 feature_num_;
    size_t                   preprocess_thread_num_;
    size_t                   batch_size_;
    std::string              model_path_;
    std::string              model_name_;
    std::string              platform_cfg_;
    uint32_t                 init_resource_;
    float32_t                x_min_;
    float32_t                x_max_;
    float32_t                y_min_;
    float32_t                y_max_;
    float32_t                z_min_;
    float32_t                z_max_;
    float32_t                dx_;
    float32_t                dy_;
    uint32_t                 feature_h_;
    uint32_t                 feature_w_;
    uint32_t                 task_num_;
    uint32_t                 num_heads_per_task_;
    std::vector<uint32_t>    num_cls_of_each_task_;
    std::vector<float32_t>   nms_min_radius_;
    std::vector<float32_t>   post_center_range_;
    float32_t                box_threshold_;
    uint32_t                 out_size_factor_;
    uint32_t                 post_max_size_;
};

}  // namespace dnn
}  // namespace holo
#endif  // !HOLO_DNN_DETECTION_LIDAR_INTERFACE_H_
