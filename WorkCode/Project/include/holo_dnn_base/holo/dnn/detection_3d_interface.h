/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file detection_3d_interface.h
 * @brief This header file defines detection 3d interface
 * @author wanggang(wanggang@holomatic.com)
 * @date "2021-03-10"
 */

#ifndef HOLO_DNN_DETECTION_3D_INTERFACE_H_
#define HOLO_DNN_DETECTION_3D_INTERFACE_H_
#include <holo/common/camera_fisheye.h>
#include <holo/obstacle/obstacle_vision.h>
#include <holo/perception/common/box2d.h>
#include <holo/perception/common/box_object.h>
#include <opencv2/imgproc/types_c.h>

#include <iostream>
#include <opencv2/opencv.hpp>

#include "holo/dnn/interface.h"

namespace holo
{
namespace dnn
{
class Detection3dInterface : public DnnInterface
{
public:
    using ObstacleVisionType = holo::obstacle::ObstacleVisionT<holo::float32_t>;
    using OutputType         = std::vector<std::vector<ObstacleVisionType>>;

public:
    virtual ~Detection3dInterface(){};
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
     * @param node config_yaml_path app config yaml path
     * @return success or fail
     */
    void initConfig(const std::string& cfg_file);

    /**
     * @brief recover angle_holo
     * @param roi_conf_ptr roi_conf_ptr
     * @param roi_offset_ptr roi_offset_ptr
     * @param bin_num bin_num
     * @return recovered angle
     */
    float32_t recover_angle_holo(const float32_t* roi_conf_ptr, const float32_t* roi_offset_ptr, size_t bin_num) const;

    /**
     * @brief compute orientaion
     * @param recover_alpha recover_alpha
     * @param px px
     * @return orientaion
     */
    float32_t compute_orientaion(float32_t recover_alpha, float32_t px) const;

    /**
     * @brief decoder_occluded
     * @param occluded_ptr occluded_ptr
     * @return occluded
     */
    float32_t decoder_occluded(const float32_t* occluded_ptr) const;

    /**
     * @brief detection 3d decoder
     * @param array_output_ptr output
     * @param h_offset_ptr h_offset_ptr
     * @param w_offset_ptr w_offset_ptr
     * @param l_offset_ptr l_offset_ptr
     * @param ori_offset_ptr ori_offset_ptr
     * @param ori_conf_ptr ori_conf_ptr
     * @param kp_offset_ptr kp_offset_ptr
     * @param occluded_ptr occluded_ptr
     * @param indexs reg obs indexs
     * @param tensor_dims tensor_dims
     * @return
     */

    virtual void decoder(void* const array_output_ptr, float32_t* h_offset_ptr, float32_t* w_offset_ptr,
                         float32_t* l_offset_ptr, float32_t* ori_offset_ptr, float32_t* ori_conf_ptr,
                         float32_t* kp_offset_ptr, float32_t* occluded_ptr, float32_t* kps_class_ptr,
                         float32_t* kps_offset_ptr, std::vector<std::vector<size_t>>& indexs,
                         std::vector<int32_t>& tensor_dims);

public:
    /// app config
    int32_t     init_resource_;
    size_t      image_width_;
    size_t      image_height_;
    size_t      batch_size_;
    size_t      model_input_width_;
    size_t      model_input_height_;
    size_t      image_frames_;
    std::string model_path_;
    std::string model_name_;
    std::string platform_cfg_;
    size_t      feature_map_ratio_;
    float32_t   dims_avg_[3];
    float32_t   dims_min_[3];
    float32_t   dims_max_[3];
    float32_t   front_center_rx_;
    float32_t   front_center_rz_;
    float32_t   front_left_rx_;
    float32_t   front_left_ry_;
    float32_t   front_left_rz_;
    float32_t   front_right_rx_;
    float32_t   front_right_ry_;
    float32_t   front_right_rz_;
    float32_t   rear_center_rx_;
    float32_t   rear_center_rz_;
    float32_t   rear_left_rx_;
    float32_t   rear_left_rz_;
    float32_t   rear_right_rx_;
    float32_t   rear_right_rz_;
    float32_t   front_telephoto_rx_;
    float32_t   front_telephoto_rz_;
    float32_t   rx_;
    float32_t   rz_;
    float32_t   min_width_;
    float32_t   min_height_;
    float32_t   scale_;
    size_t      bin_num_;

    using Scalar                        = holo::float32_t;
    using KeyPointType                  = holo::vision::KeyPoint2T<Scalar>;
    using Point3Type                    = holo::geometry::Point3T<Scalar>;
    using Point2Type                    = holo::geometry::Point2T<Scalar>;
    using Rot3Type                      = holo::geometry::Rot3T<Scalar>;
    using Pose3Type                     = holo::geometry::Pose3T<Scalar>;
    using CameraTypePtr                 = std::shared_ptr<holo::CameraFisheyeT<Scalar>>;
    holo::numerics::Matrix3T<Scalar> K_ = holo::numerics::Matrix3T<Scalar>::Zero();
    holo::numerics::Vector8T<Scalar> D_ = holo::numerics::Vector8T<Scalar>::Zero();
    CameraTypePtr                    camera_model_;
    CameraTypePtr                    front_center_camera_model_;
    CameraTypePtr                    front_left_camera_model_;
    CameraTypePtr                    front_right_camera_model_;
    CameraTypePtr                    rear_center_camera_model_;
    CameraTypePtr                    rear_left_camera_model_;
    CameraTypePtr                    rear_right_camera_model_;
    CameraTypePtr                    front_telephoto_camera_model_;
};

}  // namespace dnn
}  // namespace holo
#endif  // !HOLO_DNN_DETECTION_3D_INTERFACE_H_
