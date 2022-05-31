/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file detection_lane_interface.h
 * @brief This header file defines lane detection interface
 * @author zhaijindong(zhaijindong@holomatic.com)
 * @date "2022-03-26"
 */

#ifndef HOLO_DNN_DETECTION_LANE_INTERFACE_H_
#define HOLO_DNN_DETECTION_LANE_INTERFACE_H_

#include <iostream>

#include <holo/common/image.h>
#include "holo/dnn/interface.h"
#include <holo/perception/common/road.h>

namespace holo
{
namespace dnn
{
class DetectionLaneInterface : public DnnInterface
{
public:
    using KeyType            = holo::uint32_t;
    using ScalarType         = holo::float32_t;
    using PointType          = holo::geometry::Point2T<ScalarType>;
    using KeypointType       = holo::perception::road::Keypoint2T<KeyType, ScalarType>;
    using PolylineType       = holo::perception::road::Polyline2T<KeyType, ScalarType>;
    using LaneBoundaryType   = holo::perception::road::LaneBoundary2T<KeyType, ScalarType>;
    using LaneBoundariesType = ::std::vector<LaneBoundaryType>;
    using OutputType         = std::vector<LaneBoundariesType>;


public:
    virtual ~DetectionLaneInterface(){};
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
     * @param lane_heatmap Tensor to decode.
     */
    virtual void decoder(void* const array_output_ptr, float32_t*  lane_heatmap) const;

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
    size_t      lane_output_height_;
    size_t      lane_output_width_;
    size_t      lane_output_channel_;
    size_t      kpt_conf_output_channel_;
    size_t      kpt_offset_output_channel_;
    size_t      kpt_type_output_channel_;
    size_t      kpt_output_height_;
    size_t      kpt_output_width_;
    size_t      sample_height_block_;
    size_t      sample_height_select_index_;
    size_t      init_resource_;
    float32_t   probability_threshold_;
    std::string model_path_;
    std::string model_name_;
    std::string platform_cfg_;

    std::vector<float32_t> offsets_;
};

}  // namespace dnn
}  // namespace holo
#endif  // !HOLO_DNN_DETECTION_LANE_INTERFACE_H_
