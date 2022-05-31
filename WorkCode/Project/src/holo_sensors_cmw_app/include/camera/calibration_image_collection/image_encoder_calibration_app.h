/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_encoder_calibration_app.h
 * @brief main function for camera driver
 * @author chuan.yong @ yongchuan@holomatic.com
 * @date 2021-3-1
 */

#ifndef HOLO_CMW_APPS_CAMERA_GENERAL_IMAGE_ENCODER_CALIBRATION_APP_H
#define HOLO_CMW_APPS_CAMERA_GENERAL_IMAGE_ENCODER_CALIBRATION_APP_H

#include <iostream>

#include <cmw_wrapper/cmw_bus.h>
#include <holo/core/exception.h>
#include <holo/sensors/camera/encoder/image_encoder.h>
#include <holo/sensors/camera/image_ipc.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo_base_msg/traits.h>

namespace cmw_wrapper
{
using holo::sensors::camera::H264Encoder;
using holo::sensors::camera::IMAGE_ENCODE_SIZE_MAX;
using holo::sensors::camera::ImagePacket;
using holo::sensors::camera::ImageType;
using holo::sensors::camera::Nv12ToH264Encoder;

/**
 * @brief class
 */
template <typename Tenc>
class CameraCalibrationEncoder
{
public:
    using bool_t   = holo::bool_t;
    using Image    = holo::Image;
    using ImageIpc = holo::sensors::camera::ImageIpc;
    using CMW      = cmw_wrapper::BusType;
    template <typename T>
    using PublisherT = typename CMW::WriterType<T>;
    template <typename T>
    using SubscriberT = typename CMW::ReaderType<T>;

    /**
     * @brief constructor
     *
     * @param[in] argc number args
     * @param[in] argv pointer of arg array
     * @param[in] config_file configure file
     * @param[in] id domain id for cmw
     * @param[in] ns namespace for cmw
     */
    CameraCalibrationEncoder(holo::int32_t argc, char** argv, const std::string& config_file,
                             const holo::uint32_t id = 34u, const std::string& ns = "CameraCalibrationEncoder");
    /**
     * @brief Destruction
     */
    ~CameraCalibrationEncoder();

protected:
    /**
     * @brief Get all parameters
     * @param config_file_path get yaml file path, and read some parameters
     * @return bool
     */
    bool getParameters(std::string const& config_file_path);

    /**
     * @brief Setup, main function entry
     *
     * @param config_file, init the class of driver with some parametes, such as sensor_id, topic
     */
    void setUp(std::string const& config_file);

    /**
     * @brief input image callback
     *
     * @param[in] cmw msg counter for image
     */
    void inputImageCallback(std::string const& camera_name, std::shared_ptr<ImageIpc> const& ipc,
                            std::shared_ptr<Tenc> encode, uint64_t msg);
    /**
     * @brief publish encoded data
     *
     * @param[in] encoded_image encoded image data, such as h264 or h265
     */
    void imageEncoderHandler(const ImagePacket& encoded_image);

private:
    /**
     * @brief Camera
     */
    struct Camera
    {
        /**
         * @brief camera name
         */
        std::string name;

        /**
         * @brief camera topic
         */
        std::string topic;

        /**
         * @brief image ipc
         */
        std::shared_ptr<ImageIpc> image_ipc_ptr;

        /**
         * @brief image encoder
         */
        std::shared_ptr<Tenc> image_encoder_ptr;

    };  // camera

    /**
     * @brief Cameras
     */
    Camera camera_;

    /**
     * @brief All image subscribers
     */
    SubscriberT<holo::uint64_t> camera_img_sub_;

    /**
     * @brief buffer to save the decompressed data
     */
    std::shared_ptr<uint8_t> output_;

    /**
     * @brief Communication middleware
     */
    CMW cmw_;

    /**
     * @brief Publish encoded image data
     */
    PublisherT<uint8_t*> pub_encoded_;
};  // CameraCalibrationEncoder
}  // namespace cmw_wrapper
#endif