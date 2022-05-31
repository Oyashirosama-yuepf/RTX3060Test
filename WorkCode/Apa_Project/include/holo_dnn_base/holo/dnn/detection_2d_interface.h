/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file detection_2d_interface.h
 * @brief This header file defines detection 2d interface
 * @author huanglihong(huanglihong@holomatic.com)
 * @date "2020-10-21"
 */

#ifndef HOLO_DNN_DETECTION_2D_INTERFACE_H_
#define HOLO_DNN_DETECTION_2D_INTERFACE_H_
#include <holo/perception/common/box2d.h>
#include <holo/perception/common/box_object.h>

#include <iostream>

#include "holo/dnn/interface.h"

namespace holo
{
namespace dnn
{
class Detection2dInterface : public DnnInterface
{
public:
    using BBox         = holo::perception::Box2Df;
    using BoxObject    = holo::perception::BoxObjectf;
    using ClassifyInfo = holo::perception::ClassifyInfo;
    using OutputType   = std::vector<std::vector<BoxObject>>;

public:
    virtual ~Detection2dInterface(){};
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
     * @brief the decoder inference
     * @param array_output_ptr output
     * @param model_output the outputs of the model's heads
     * @param head_name the name of model'head
     */
    virtual void decoder(void* const array_output_ptr, std::vector<float32_t*> model_output,
                         std::string const head_name = "CenterNet") const;

    /**
     * @brief detection 2d decoder for centernet
     * @param array_output_ptr output
     * @param sigmoid_heatmap sigmoid heatmap
     * @param max_pooling_map max_pooling_map
     * @param wh wh
     * @param center_offset center_offset
     * @return
     */
    virtual void decoder_centernet(void* const array_output_ptr, float32_t* sigmoid_heatmap, float32_t* max_pooling_map,
                                   float32_t* wh, float32_t* center_offset) const;

    /**
     * @brief detection 2d decoder for yolox
     * @param array_output_ptr output
     * @param prob model's head output
     * @return
     */
    virtual void decoder_yolox(void* const array_output_ptr, float32_t* prob) const;

    /**
     * @brief detection 2d decoder for yolox
     * @param array_output_ptr output
     * @param prob model's head output
     * @param with_kp have keypoint
     * @return
     */
    virtual void decoder_yolox_kp(void* const array_output_ptr, float32_t* prob) const;

protected:
    /// app config
    std::vector<size_t>    crop_width_;
    std::vector<size_t>    crop_height_;
    size_t                 image_width_;
    size_t                 image_height_;
    size_t                 batch_size_;
    size_t                 model_input_width_;
    size_t                 model_input_height_;
    size_t                 model_output_width_;
    size_t                 model_output_height_;
    size_t                 model_output_channel_;
    size_t                 num_class_;
    std::string            model_path_;
    std::string            model_name_;
    std::string            platform_cfg_;
    size_t                 feature_map_ratio_;
    float32_t              score_threshold_;
    float32_t              min_area_;
    float32_t              nms_threshold_;
    float32_t              min_box_threshold_;
    float32_t              scale_ratio_w_;
    float32_t              scale_ratio_h_;
    uint32_t               init_resource_;
    holo::bool_t           filter_truncated_;
    holo::bool_t           have_keypoints_;
    float32_t              max_gap_truncated_;  // define a boox's edge to the image's dege as truncated
    std::vector<float32_t> offsets_x_;
    std::vector<float32_t> offsets_y_;
};

}  // namespace dnn
}  // namespace holo
#endif  // !HOLO_DNN_DETECTION_2D_INTERFACE_H_
