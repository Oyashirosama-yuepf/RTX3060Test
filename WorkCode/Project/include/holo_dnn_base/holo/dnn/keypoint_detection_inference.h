/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file keypoint_detection_inference.h
 * @brief This header file defines keypoint detection inference
 * @author zhaijindong(zhaijindong@holomatic.com)
 * @date "2021-08-26"
 */

#ifndef HOLO_DNN_KEYPOINT_DETECTION_INFERENCE_H_
#define HOLO_DNN_KEYPOINT_DETECTION_INFERENCE_H_
#include <holo/perception/common/keypoint.h>

#include <iostream>

#include <holo/common/image.h>
#include "holo/dnn/interface.h"

namespace holo
{
namespace dnn
{
class KeypointDetectionInterface : public DnnInterface
{
public:
    using keypointf = holo::perception::KeyPointf;
    struct KeyPoint2Object{
        ::std::vector<keypointf> points;
        int32_t                  category;
        float32_t                confidence;
    };
    using OutputType    = std::vector<KeyPoint2Object>;
    using InputType     = std::vector<cv::Mat>;

public:
    virtual ~KeypointDetectionInterface(){};
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
     * @brief keypoint detect decoder
     * @param array_output_ptr output
     * @param classes_heatmap
     * @param keypoints_heatmap
     * @return
     */
    virtual void decoder(void* const array_output_ptr,
                         float32_t* classes_heatmap, float32_t* keypoints_heatmap) const;

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
    size_t      classes_output_width_;
    size_t      classes_output_height_;
    size_t      classes_output_channel_;
    size_t      keypoints_output_width_;
    size_t      keypoints_output_height_;
    size_t      keypoints_output_channel_;
    std::string model_path_;
    std::string model_name_;
    std::string platform_cfg_;
    size_t      feature_map_ratio_;
    float32_t   score_threshold_;
    float32_t   min_area_;
    float32_t   max_area_;
    float32_t   roi_box_w;
    float32_t   roi_box_h;
    uint32_t init_resource_;
};

}  // namespace dnn
}  // namespace holo
#endif  // !HOLO_DNN_KEYPOINT_DETECTION_INFERENCE_H_
