/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file keypoint_detetion.h
 * @brief This header file defines keypoint detetion
 * @author zhaijindong(zhaijindong@holomatic.com)
 * @date "2021-08-26"
 */

#ifndef HOLO_APPS_KEYPOINT_DETECTION_KEYPOINT_DETECTION_CLASSIFICATION_H_
#define HOLO_APPS_KEYPOINT_DETECTION_KEYPOINT_DETECTION_CLASSIFICATION_H_

// #include <acl/acl.h>
#include <holo/dnn/keypoint_detection_inference.h>
#include <holo/dnn/interface.h>
#include <holo/perception/common/box2d.h>
#include <holo/perception/common/box_object.h>
#include <opencv2/imgproc/types_c.h>

#include <holo/dnn/tda4/common/test_tidl_inference.h>

namespace holo
{
namespace dnn
{
namespace tda4
{
class KeypointDetection : public KeypointDetectionInterface
{
public:
    using Keypointf     = holo::perception::KeyPointf;
    struct KeyPoint2Object
    {
        ::std::vector<Keypointf>  points;
        int32_t                   category;
        float32_t                 confidence;
    };
    using OutputType    = std::vector<KeyPoint2Object>;
    using InputType     = std::vector<cv::Mat>;

    /**
     * @brief init dnn with app on target platform based on yaml config
     *
     * @param config_yaml_path config_yaml_path app config yaml path
     * @return success or fail
     */
    holo::bool_t Init(std::string const& config_yaml_path) override;

    /**
     * @brief preprocess data
     *
     * @param array_data_ptr data pointer, maybe opencv mat or raw nv12 data
     * @return holo::bool_t true for success, false for failure.
     */
    holo::bool_t PreProcess(const void* const array_data_ptr) override;

    /**
     * @brief Inference on target platform.
     *
     * @param array_data_ptr Input.
     * @param array_output_ptr Output.
     * @return holo::bool_t true for success, false for failure.
     */
    holo::bool_t Inference(const void* const array_data_ptr, void* const array_output_ptr) override;

    /**
     * @brief post process
     * @param array_output_ptr output data pointer, maybe vector<bbox2d> type or something else
     * @return
     */
    holo::bool_t PostProcess(void* const array_output_ptr) override;

    /**
     * @brief Show dnn environment.
     *
     */
    void ShowDnnEnv() override;

    /**
     * @brief Destroy the Classification object.
     *
     */
    virtual ~KeypointDetection();

private:
    /// nv12 image --> copy --> aligned nv12 image --> dvpp --> aligned model input
    // std::shared_ptr<AlignedNV12Tensor> aligned_image_input_;
    // std::shared_ptr<AlignedNV12Tensor> aligned_model_input_;

    // aclrtContext context_;
    // aclrtStream  stream_;

    uint32_t            modelId_         = 0U;
    uint32_t            group_id_        = 0U;
    uint32_t            hi_dvpp_channel_ = 101U;
    uint32_t            device_id_       = 0U;
    holo::bool_t        loadFlag_        = false;    // model load flag
    size_t              modelWorkSize_   = 0U;       // model work memory buffer size
    size_t              modelWeightSize_ = 0U;       // model weight memory buffer size
    void*               modelWorkPtr_    = nullptr;  // model work memory buffer
    void*               modelWeightPtr_  = nullptr;  // model weight memory buffer

    std::shared_ptr<holo::perception::TidlInferenceDet> tidl_center_net_;
};

}  // namespace mdc
}  // namespace dnn
}  // namespace holo
#endif  // !HOLO_APPS_KEYPOINT_DETECTION_KEYPOINT_DETECTION_CLASSIFICATION_H_
