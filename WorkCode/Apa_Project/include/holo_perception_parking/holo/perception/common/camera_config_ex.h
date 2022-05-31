/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vision_parkingslot.h
 * @brief This header file defines base vision parkingslot class.
 * @author lizhijian (lizhijian@holomatic.com)
 * @date "2019-09-17"
 */
#ifndef HOLO_PERCEPTION_LIB_CAMERA_CONFIG_EX_H_
#define HOLO_PERCEPTION_LIB_CAMERA_CONFIG_EX_H_

#include <holo/common/extrinsic.h>
#include <holo/common/image.h>
#include <holo/common/intrinsic.h>
#include <holo/common/lane_scene.h>
#include <holo/common/odometry.h>
#include <holo/common/path.h>
#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/utils/dg_port.h>
#include <holo/perception/utils/utility.h>

#include <string>
#include <vector>

namespace holo
{
namespace perception
{
class CamConfig
{
public:
    typedef float32_t ScalarType;

    /**
     * @brief the constructor
     * @param name camera device name.
     * @param intrinsic camera intrinsic.
     * @param extrinsic camera extrinsic.
     * @param input_size input image size.
     * @param input_resize resize the input image to the specified size.
     * @param crop_start crop the resized image from the specified location.
     * @param crop_size crop the image with the size of this parameter.
     * @param ROI_mask ROI mask that will applied on the input image.
     * @param output_mask_offset apply the ROI mask on the output image with this offset.
     * @param visible_radius how far the 3D boundry is after IPM process, in meter.
     * @param radian_range_start sector start within the specified radian range.
     * @param radian_range_end sector end within the specified radian range.
     * @param type what ipm extrinsic is to use. 1: cam-body; 2:H matrix; 3: cam-ground
     */
    CamConfig(std::string name, std::string intrinsic, std::string extrinsic, cv::Size2i input_size,
              cv::Size2i input_resize, cv::Size2i crop_start, cv::Size2i crop_size, cv::Mat& ROI_mask,
              uint32_t output_mask_offset, float32_t visible_radius, float32_t radian_range_start,
              float32_t radian_range_end, int type = 0)
      : name_(name)
      //, intrinsic_(intrinsic)
      //, extrinsic_(extrinsic)
      , input_size_(input_size)
      , input_resize_(input_resize)
      , crop_start_(crop_start)
      , crop_size_(crop_size)
      , ROI_mask_(ROI_mask)
      , output_mask_offset_(output_mask_offset)
      , visible_radius_(visible_radius)
      , radian_range_start_(radian_range_start)
      , radian_range_end_(radian_range_end)
    {
        scale_.width  = (float)input_resize_.width / (float)input_size_.width;
        scale_.height = (float)input_resize_.height / (float)input_size_.height;
        MakeOutputMask();
        type_ = type;

        // to determin the intrinsic type.
        if (access(intrinsic.c_str(), R_OK) != 0)
        {
            std::stringstream ss;
            ss << intrinsic << " dose not exist";
            LOG(ERROR) << ss.str();
            throw std::runtime_error(ss.str());
        }
        // all intrinsic parameters
        // fisheye
        // uint32_t   coord  = 0u;

        uint32_t sensor_id = 0u;

        uint32_t   model  = 0xFFFF;
        ScalarType fx     = 0.0f;
        ScalarType fy     = 0.0f;
        ScalarType cx     = 0.0f;
        ScalarType cy     = 0.0f;
        ScalarType skew   = 0.0f;
        ScalarType k1     = 0.0f;
        ScalarType k2     = 0.0f;
        ScalarType p1     = 0.0f;
        ScalarType p2     = 0.0f;
        ScalarType k3     = 0.0f;
        ScalarType k4     = 0.0f;
        ScalarType k5     = 0.0f;
        ScalarType k6     = 0.0f;
        uint32_t   width  = 0u;
        uint32_t   height = 0u;

        /// ocam
        ScalarType              c                      = 0.0f;
        ScalarType              d                      = 0.0f;
        ScalarType              e                      = 0.0f;
        uint32_t                distortion_coeffs_size = 5;
        uint32_t                polynomial_size        = 11;
        std::vector<ScalarType> vec_a;
        std::vector<ScalarType> vec_p;

        try
        {
            yaml::Node node_root = yaml::LoadFile(intrinsic);

            std::string model = node_root["model"].as<std::string>();
            sensor_id         = node_root["sensor_id"].as<uint32_t>();
            sensor_id_        = sensor_id;

            ///
            if (model == "FISHEYE" || model == "16")
            {
                // coord  = node_root["coord"].as<uint32_t>();
                fx     = node_root["fx"].as<ScalarType>();
                fy     = node_root["fy"].as<ScalarType>();
                cx     = node_root["cx"].as<ScalarType>();
                cy     = node_root["cy"].as<ScalarType>();
                skew   = node_root["skew"].as<ScalarType>();
                k1     = node_root["k1"].as<ScalarType>();
                k2     = node_root["k2"].as<ScalarType>();
                p1     = node_root["p1"].as<ScalarType>(0.0);
                p2     = node_root["p2"].as<ScalarType>(0.0);
                k3     = node_root["k3"].as<ScalarType>();
                k4     = node_root["k4"].as<ScalarType>();
                k5     = node_root["k5"].as<ScalarType>(0.0);
                k6     = node_root["k6"].as<ScalarType>(0.0);
                width  = node_root["width"].as<uint32_t>(0.0);
                height = node_root["height"].as<uint32_t>(0.0);

                camera_model_ = holo::common::details::CameraIntrinsicBaseT<holo::float32_t>::Model::FISHEYE;

                fisheye_intrinsic_.SetDimension(width, height);
                fisheye_intrinsic_.SetDistortionParameter(k1, k2, k3, k4);
                fisheye_intrinsic_.SetFocalLength(fx, fy);
                fisheye_intrinsic_.SetPrinciplePoint(cx, cy);
                fisheye_intrinsic_.SetSkew(skew);
            }
            else if (model == "OCAM" || model == "32")
            {
                c  = node_root["c"].as<ScalarType>();
                d  = node_root["d"].as<ScalarType>();
                e  = node_root["e"].as<ScalarType>();
                cx = node_root["cx"].as<ScalarType>();
                cy = node_root["cy"].as<ScalarType>();
                distortion_coeffs_size =
                    node_root["distortion coeffs size"] ? node_root["distortion coeffs size"].as<uint32_t>() : 5;
                polynomial_size = node_root["polynomial size"] ? node_root["polynomial size"].as<uint32_t>() : 11;

                for (uint32_t i = 0; i < distortion_coeffs_size; i++)
                {
                    char skey[8] = {0};
                    snprintf(skey, 7, "a%d", i);
                    vec_a.push_back(node_root[skey] ? node_root[skey].as<ScalarType>() : 0.0f);
                }
                for (uint32_t i = 0; i < polynomial_size; i++)
                {
                    char skey[8] = {0};
                    snprintf(skey, 7, "p%d", i);
                    vec_p.push_back(node_root[skey] ? node_root[skey].as<ScalarType>() : 0.0f);
                }
                width  = node_root["width"].as<uint32_t>();
                height = node_root["height"].as<uint32_t>();

                camera_model_ = holo::common::details::CameraIntrinsicBaseT<holo::float32_t>::Model::OMNIDIRECTIONAL;

                ocam_intrinsic_.SetDimension(width, height);
                ocam_intrinsic_.SetAffineTransformation(c, d, e);
                ocam_intrinsic_.SetPrinciplePoint(cx, cy);
                ocam_intrinsic_.SetUnprojectPolynomial({vec_a[0], vec_a[1], vec_a[2], vec_a[3], vec_a[4]},
                                                       {vec_p[0], vec_p[1], vec_p[2], vec_p[3], vec_p[4], vec_p[5],
                                                        vec_p[6], vec_p[7], vec_p[8], vec_p[9], vec_p[10]});
            }
            else
            {
                LOG(FATAL) << "Reading camera intrinsic fails. Not supported: " << model;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            LOG(FATAL) << "Load intrinsic yaml failure: " << intrinsic << "\n" << e.what();
        }

        extrinsic_ = holo::Extrinsicf::LoadYaml(extrinsic);
    }

    /**
     * @brief MakeOutputMask that generates output-mask from the input mask
     */
    void MakeOutputMask()
    {
        Output_mask_ = ROI_mask_.clone();
        for (int col = Output_mask_.size().width - 1; col >= 0; col--)
        {
            for (int row = Output_mask_.size().height - 1; row >= 3; row--)
            {
                cv::Vec3b pixel = Output_mask_.at<cv::Vec3b>(row, col);
                if (pixel[0] != 0 && pixel[1] != 0 && pixel[2] != 0)
                {
                    // tmp.
                    // todo: make this configurable.
                    for (uint32_t t = 0; t < output_mask_offset_; t++)
                        Output_mask_.at<cv::Vec3b>(row--, col) = cv::Vec3b(0, 0, 0);
                    break;
                }
            }
        }
    }

    int         type_;  // 0:body-cam pose; 1: Mapping using H,K; 2: ground-cam pose
    std::string name_;

    // holo::Intrinsicf intrinsic_;  // ready to delete.

    holo::common::FisheyeIntrinsicf         fisheye_intrinsic_;
    holo::common::OmnidirectionalIntrinsicf ocam_intrinsic_;

    // holo::common::details::CameraIntrinsicBaseT<holo::float32_t>T<holo::float32_t>::Model camera_model_;
    holo::common::details::CameraIntrinsicBaseT<holo::float32_t>::Model camera_model_;

    holo::Extrinsicf extrinsic_;

    // holo::Extrinsicf camera_ground_extrinsic_;

    cv::Size2i input_size_;
    cv::Size2i input_resize_;
    cv::Size2i crop_start_;
    cv::Size2i crop_size_;

    cv::Mat   ROI_mask_;
    uint32_t  output_mask_offset_;
    cv::Mat   Output_mask_;
    float32_t visible_radius_;

    float32_t radian_range_start_;
    float32_t radian_range_end_;

    cv::Size2f scale_;
    cv::Mat    h_, k_;

    uint32_t sensor_id_;
};
}  // namespace perception
}  // namespace holo

#endif