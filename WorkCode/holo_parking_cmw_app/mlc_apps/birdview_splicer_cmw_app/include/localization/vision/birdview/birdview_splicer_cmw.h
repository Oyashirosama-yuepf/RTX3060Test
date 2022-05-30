/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file birdview_splicer_cmw.h
 * @brief cmw node of birdview splicer.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-01-07"
 */

#ifndef HOLO_CMW_APPS_LOCALIZATION_VISION_BIRDVIEW_BIRDVIEW_SPLICER_CMW_H_
#define HOLO_CMW_APPS_LOCALIZATION_VISION_BIRDVIEW_BIRDVIEW_SPLICER_CMW_H_

#include <mutex>

#include <cmw_wrapper/cmw_bus.h>

#include <holo/common/details/timestamp.h>
#include <holo/sensors/camera/encoder/image_encoder_h26x.h>
#include <holo/sensors/camera/image_ipc.h>
#include <localization/vision/birdview/birdview_image_undistortion.h>
#include <localization/vision/birdview/birdview_show.h>
#include <localization/vision/birdview/image_type_converter.h>

using holo::vision::BirdviewImageUndistortion;
using holo::vision::BirdviewShow;

namespace holo_cmw
{
/**
 * @brief BirdviewSplicerCmw class
 */

class BirdviewSplicerCmw
{
public:
    /**
     * @brief handy type define
     */
    typedef cmw_wrapper::BusType               BusType;
    typedef holo::float64_t                    Scalar;
    typedef holo::Matrix3T<Scalar>             Matrix3;
    typedef holo::common::Timestamp            Timestamp;
    typedef holo::sensors::camera::ImagePacket ImagePacket;

    /**
     * @brief Construct a new Birdview Splicer Cmw object
     *
     * @param[in] argc
     * @param[in] argv
     * @param[in] config_file parameters needed in birdview splicer
     * @param[in] domain_id domain id to initialize ddsBus
     * @param[in] participant_namespace namespace for the domain participant tag
     */
    BirdviewSplicerCmw(holo::int32_t argc, char** argv, std::string const& config_file, uint32_t domain_id,
                       std::string participant_namespace);

    /**
     * @brief Destroy the Birdview Splicer Cmw object
     *
     */
    ~BirdviewSplicerCmw();

    /**
     * @brief Check if bus is running
     *
     * @return true
     * @return false
     */
    bool IsRunning();

    /**
     * @brief spin the node
     *
     */
    void Spin();

    /**
     * @brief Compute the Birdview Image
     *
     * @param[in][out] birdview_image birdview image
     * @return holo::bool_t true -> birdview_image is computed successfully false -> otherwise
     */
    holo::bool_t ComputeBirdviewImage(holo::Image& birdview_image);

    /**
     * @brief Publish the Birdview Image
     *
     * @param[in] image input image
     */
    void PublishBirdviewImage(holo::Image const& image);

private:
    /************** @brief methods **************/

    /**
     * @brief load parameters needed in birdview splicer
     *
     * @param[in] config_file parameters needed in birdview splicer
     */
    void setUp(std::string const& config_file);

    /**
     * @brief input image callback
     *
     * @param[in] i id of input image
     * @param[in] msg msg topic name
     */
    void inputImageCallback(size_t const i, holo::uint32_t msg);

    /**
     * @brief Get the Img Ipc object
     *
     * @param[in] sensor_id camera sensor id
     * @param[in] height height of input image
     * @param[in] width width of input image
     * @param[in] encoding encoding of input image
     * @return std::shared_ptr<holo::sensors::camera::ImageIpc>
     */
    std::shared_ptr<holo::sensors::camera::ImageIpc> getImgIpc(holo::common::SensorId sensor_id, uint32_t height,
                                                               uint32_t width, holo::Image::Encoding encoding);

    /**
     * @brief process encoded image with serivalizer
     *
     * @param[in] encoded image
     */
    void processEncodedImage(ImagePacket const& encoded_image);

    BusType                                                        bus_;                    ///< holo cmw
    std::shared_ptr<std::thread> bus_spin_thread_ptr_;
    std::vector<BusType::ReaderType<holo::uint32_t>>               images_readers_;         ///< cmw readers
    std::shared_ptr<holo::vision::BirdviewShow>                    birdview_show_ptr_;      ///< birdview image splicer
    std::vector<std::shared_ptr<holo::vision::ImageTypeConverter>> image_type_converters_;  ///< image type converters
    std::vector<std::shared_ptr<holo::sensors::camera::ImageIpc>>  image_ipcs_;             ///< ipc pointers
    std::unordered_map<holo::uint32_t, std::unordered_map<holo::uint16_t, cv::Mat>>
        timestamp_with_images_;                                                  ///< timestamp
                                                                                 ///< with a set
                                                                                 ///< of image
    std::mutex                                    timestamp_with_images_mutex_;  ///< mutex for timestamp_with_images_
    std::deque<holo::common::details::Timestamp>  image_timestamps_;             ///< timestamp of images
    bool                                          verbose_;                     ///< output more log information

    /**
     * @brief variables for image writer
     */
    std::shared_ptr<holo::sensors::camera::ImageIpc> birdview_image_ipc_;             ///< birdview ipc pointer
    std::shared_ptr<holo::uint8_t>                   encoded_birdview_image_buffer_;  ///< encoded birdview image buffer
    std::shared_ptr<holo::sensors::camera::H264Encoder> rgb_to_h264x_encoder_;        ///< rgb to h264x encoder
    BusType::WriterType<holo::uint32_t>                 birdview_image_writer_;       ///< cmw writer
    BusType::WriterType<holo::uint64_t>                 birdview_image_info_writer_;  ///< publish image info
    BusType::WriterType<holo::uint8_t*>                 birdview_image_encoded_writer_;  ///< publish encoded image
    uint64_t image_encode_size_max_;  ///< max size for image encode [unit: byte]
};

}  // namespace holo_cmw

#endif
