/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file detection_obs_interface.h
 * @brief This header file defines detection obs interface
 * @author wanggang(wanggang@holomatic.com)
 * @date "2021-06-01"
 */

#ifndef HOLO_DNN_DETECTION_OBS_INTERFACE_H_
#define HOLO_DNN_DETECTION_OBS_INTERFACE_H_
#include <holo/perception/common/box2d.h>
#include <holo/perception/common/box_object.h>

#include <iostream>

#include "holo/dnn/interface.h"

namespace holo
{
namespace dnn
{
class DetectionObsInterface : public DnnInterface
{
public:
    using BBox         = holo::perception::Box2Df;
    using BoxObject    = holo::perception::BoxObjectf;
    using ClassifyInfo = holo::perception::ClassifyInfo;
    using OutputType   = std::vector<std::vector<BoxObject>>;

public:
    virtual ~DetectionObsInterface(){};
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
    void initConfig(const std::string& cfg_file);

    /**
     * @brief detection 2d decoder
     * @param array_output_ptr output
     * @param sigmoid_heatmap sigmoid heatmap
     * @param max_pooling_map max_pooling_map
     * @param wh wh
     * @param center_offset center_offset
     * @return
     */
    virtual void decoder(void* const array_output_ptr, float32_t* sigmoid_heatmap, float32_t* max_pooling_map,
                         float32_t* wh, float32_t* center_offset) const;

public:
    /// app config
    size_t      crop_start_x_;
    size_t      crop_start_y_;
    size_t      crop_width_;
    size_t      crop_height_;
    size_t      image_width_;
    size_t      image_height_;
    size_t      batch_size_;
    size_t      model_input_width_;
    size_t      model_input_height_;
    size_t      model_output_width_;
    size_t      model_output_height_;
    size_t      model_output_channel_;
    std::string model_path_;
    std::string model_name_;
    std::string platform_cfg_;
    size_t      feature_map_ratio_;
    float32_t   score_threshold_;
    float32_t   min_area_;
    float32_t   max_area_;
    uint32_t    init_resource_;
};

}  // namespace dnn
}  // namespace holo
#endif  // !HOLO_DNN_DETECTION_OBS_INTERFACE_H_
