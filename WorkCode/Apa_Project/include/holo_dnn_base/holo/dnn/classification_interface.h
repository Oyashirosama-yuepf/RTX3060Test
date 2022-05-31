/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file classification.h
 * @brief This header file defines classification.h
 * @author wangzhengjun(wangzhengjun@holomatic.com)
 * @date "2021-06-17"
 */

#ifndef HOLO_DNN_CLASSIFICATION_INTERFACE_H_
#define HOLO_DNN_CLASSIFICATION_INTERFACE_H_

#include <iostream>

#include "holo/dnn/interface.h"

namespace holo
{
namespace dnn
{
class ClassificationInterface : public DnnInterface
{
public:
    using ClassifyInfo = holo::perception::ClassifyInfo;
    using OutputType   = std::vector<ClassifyInfo>;

public:
    virtual ~ClassificationInterface(){};
    /**
     * @brief init dnn with app on target platform based on yaml config
     *
     * @param config_yaml_path app config yaml path
     * @return success or fail
     */
    virtual bool Init(std::string const& config_yaml_path) = 0;

    /**
     * @brief preprocess data
     *
     * @param array_data_ptr data pointer, maybe opencv mat or raw nv12 data
     * @return
     */
    virtual bool PreProcess(const void* const array_data_ptr) = 0;

    /**
     * @brief inference on target platform
     * @param array_data_ptr input
     * @param array_output_ptr output
     *
     * @param
     */
    virtual bool Inference(const void* const array_data_ptr, void* const array_output_ptr) = 0;

    /**
     * @brief post process
     * @param array_output_ptr output data pointer, maybe vector<ClassifyInfo> type or something else
     * @return
     */
    virtual bool PostProcess(void* const array_output_ptr) = 0;

    /**
     * @brief Show dnn environment.
     *
     */
    virtual void ShowDnnEnv() override;

    /**
     * @brief Init with the config file.
     *
     * @param cfg_file Configure file.
     */
    void initConfig(const std::string& cfg_file);

    /**
     * @brief Decode input tensor to output type.
     *
     * @param array_output_ptr Output pointer.
     * @param tensor Tensor to decode.
     */
    virtual void decoder(void* const array_output_ptr, float32_t* tensor) const;

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

    std::vector<float32_t> offsets_;
};

}  // namespace dnn
}  // namespace holo
#endif  // !HOLO_DNN_CLASSIFICATION_INTERFACE_H_