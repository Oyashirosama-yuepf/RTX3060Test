/*
 * @Author: zhouchengwei
 */
/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_avm.h
 * @brief This header file defines avm camera config class.
 * @author zhouchengwei (zhouchengwei@holomatic.com)
 * @date "2021-04-29"
 */

#ifndef _HOLO_PERCEPTION_COMMON_CAMERA_AVM_H_
#define _HOLO_PERCEPTION_COMMON_CAMERA_AVM_H_

namespace holo
{
namespace perception
{
class CamAVMConfig
{
public:
    using Scalar = float32_t;

    CamAVMConfig(std::string name, float32_t project_scale, cv::Size2i input_size, cv::Size2i resize,
                 cv::Size2i crop_start, cv::Size2i crop_size, cv::Mat& ROI_mask, cv::Point2i avm_center,
                 uint32_t sensor_id)
      : name_(name)
      , project_scale_(project_scale)
      , input_size_(input_size)
      , resize_(resize)
      , crop_start_(crop_start)
      , crop_size_(crop_size)
      , ROI_mask_(ROI_mask)
      ,
      // mask_offset_(mask_offset),
      avm_center_(avm_center)
      , sensor_id_(sensor_id)
    {
        resize_scale_.width  = (float)resize_.width / (float)input_size_.width;
        resize_scale_.height = (float)resize_.height / (float)input_size_.height;
        MakeOutputMask();
    }

    void MakeOutputMask()
    {
        cv::resize(ROI_mask_, Input_mask_, cv::Size(resize_.height, resize_.width), 0, 0, CV_INTER_NN);
        cv::resize(ROI_mask_, Output_mask_, cv::Size(resize_.height / 4, resize_.width / 4), 0, 0, CV_INTER_NN);
    }

    std::string name_;
    float32_t   project_scale_;  // scale of avm pixels to really ground.

    cv::Size2i input_size_;  // input camera image size.
    cv::Size2i resize_;      // size need to resize, for network input.
    cv::Size2f resize_scale_;
    cv::Size2i crop_start_;  // start point of crop in origin image.
    cv::Size2i crop_size_;   // size of crop

    cv::Point2i avm_center_;  // the center point of avm image.
    cv::Mat     ROI_mask_;    // mask of car
    cv::Mat     Input_mask_;
    cv::Mat     Output_mask_;
    uint32_t    sensor_id_;
};
}  // namespace perception
}  // namespace holo

#endif
