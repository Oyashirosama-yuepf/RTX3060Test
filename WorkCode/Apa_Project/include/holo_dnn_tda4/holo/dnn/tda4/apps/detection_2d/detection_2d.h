/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file detection_2d.h
 * @brief This header file defines detection 2d
 * @author huanglihong(huanglihong@holomatic.com)
 * @date "2020-10-21"
 */

#ifndef HOLO_APPS_DETECTION_2D_DETECTION_2D_H_
#define HOLO_APPS_DETECTION_2D_DETECTION_2D_H_

#include <holo/dnn/detection_2d_interface.h>
#include <holo/dnn/interface.h>
#include <holo/dnn/tda4/common/nms_tidl.h>
#include <holo/dnn/tda4/common/test_tidl_inference.h>
#include <holo/dnn/tda4/common/upsample_tidl.h>
#include <holo/perception/common/box2d.h>
#include <holo/perception/common/box_object.h>
#include <opencv2/imgproc/types_c.h>

#include "holo/dnn/tda4/common/functions.h"
#include "holo/dnn/tda4/common/tadl.h"

namespace holo
{
namespace dnn
{
namespace tda4
{
enum DecodeType
{
    DetectionObs,
    DetectionParkingSlot,
    DetectionLine,
    Freespace,
    SrvMultiTask,
    YoloXSrvMultiTask,
    FeaturePointDet,
    RawData,
    Detection2dYoloX
};
class Detection2d : public Detection2dInterface
{
public:
    using BBox          = holo::perception::Box2Df;
    using BoxObject     = holo::perception::BoxObjectf;
    using ClassifyInfo  = holo::perception::ClassifyInfo;
    using InputType     = std::vector<cv::Mat>;
    using OutputType    = std::vector<std::vector<BoxObject>>;
    using Scalar        = holo::float32_t;
    using CameraTypePtr = std::shared_ptr<holo::CameraFisheyeT<Scalar>>;

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
     * @return
     */
    holo::bool_t PreProcess(const void* const array_data_ptr) override;

    /**
     * @brief inference on target platform
     * @param array_data_ptr input
     * @param array_output_ptr output
     *
     * @param
     */
    holo::bool_t Inference(const void* const array_data_ptr, void* const array_output_ptr) override;

    /**
     * @brief post process
     * @param array_output_ptr output data pointer, maybe vector<bbox2d> type or something else
     * @return
     */
    holo::bool_t PostProcess(void* const array_output_ptr) override;

    /**
     * @brief show dnn env
     * @param
     * @return
     */
    void ShowDnnEnv() override;

    /**
     * @brief release resources such as memory and handles
     *
     * @param
     * @return
     */
    virtual ~Detection2d();

private:
    uint8_t*                                            data;
    std::shared_ptr<holo::perception::TidlInferenceDet> tidl_center_net_;
    std::shared_ptr<holo::perception::NmsTidl>          nms_tidl_;
    std::shared_ptr<holo::perception::UpSampleTidl>     upsample_tidl_;
    std::string                                         graph_cfg_;
    std::vector<std::string>                            decode_type_str_vector_ = {
        "DetectionObs",      "DetectionParkingSlot", "DetectionLine", "Freespace",       "SrvMultiTask",
        "YoloXSrvMultiTask", "FeaturePointDet",      "RawData",       "Detection2dYoloX"};
    std::string   decode_type_str_;
    DecodeType    decode_type_;
    int           set_data_index_;
    bool          copy_flag_;
    float32_t     bbox_score_ = 0.f;
    float32_t     nms_score_  = 0.f;
    size_t        bins_       = 0U;
    size_t        class_num_  = 0U;
    CameraTypePtr camera_model_;
};

}  // namespace tda4
}  // namespace dnn
}  // namespace holo
#endif  // !HOLO_APPS_DETECTION_2D_DETECTION_2D_H_
