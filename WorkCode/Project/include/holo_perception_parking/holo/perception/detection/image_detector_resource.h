/*!
 *  \brief
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2018-11-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_DETECTION_IMAGE_DETECTOR_RESOURCE_H_
#define HOLO_PERCEPTION_DETECTION_IMAGE_DETECTOR_RESOURCE_H_

#include <memory>
#include <string>

#include <boost/circular_buffer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread/thread.hpp>

#include <holo/utils/holo_root.h>
#include "holo/perception/common/camera_model.h"
#include "holo/perception/common/image_bbox2d.h"

namespace holo
{

namespace perception
{

class ImageDetectorResource
{
public:
    ImageDetectorResource(const std::string& camera_config, const int buf_num);

    /**
     * read parameter from config file
    */
    void InitConfig(const std::string& cfg_file);

    /**
     * pre-process, image crop
     * param[in] in - input image to be processed
     * param[out] out - output image
    */
    void PreProcess(const cv::Mat& in, cv::Mat& out);

    /**
     * clear circular buffer
    */
    void ClearBuffer();

    /**
     * whether has data in circular buffer
    */
    bool HasData() const;

    /**
     * get camera_model pointer
    */
    std::shared_ptr<CameraModel<float32_t> > GetCameraModelPtr() const;

    /**
     * push distorted image into circular buffer
     * param[in] image - input image to push in
    */
    void PushbackDistortedImage(const cv::Mat& image);

    /**
     * push undistorted image into circular buffer
     * param[in] image - input image to push in
    */
    void PushbackUndistortedImage(const cv::Mat& image);

    /**
     * get back element of cb_distorted_image_
     * param[return] - back element
    */
    const cv::Mat& GetBackDistortedImage() const;

    /**
     * get back element of cb_undistorted_image_
     * param[return] - back element
    */
    const cv::Mat& GetBackUndistortedImage() const;

    /**
     * get image for algorithm
     * param[return] - image for algorithm
    */
    const cv::Mat& GetAlgorithmImage() const;

    /**
     * get crop op x start coord
    */
    int32_t GetCropXStart() const { return crop_x_start_; }

    /**
     * get crop op y end coord
    */
    int32_t GetCropYStart() const { return crop_y_start_; }

    /**
     * get crop op window width 
    */
    int32_t GetCropWidth() const { return crop_width_; }

    /**
     * get crop op window height
    */
    int32_t GetCropHeight() const { return crop_height_; }

private:
    /**
     * crop operation
     * param[in] in - input image
     * param[out] out - output image
    */
    void CropOp(const cv::Mat& in, cv::Mat& out);

    /// Rotation operation
    /**
     * rotation operation
     * param[in] in - input image
     * param[out] out - output image
    */
    void RotationOp(const cv::Mat& in, cv::Mat& out);

private:
    /// storagy
    boost::circular_buffer<cv::Mat> cb_distorted_image_;
    boost::circular_buffer<cv::Mat> cb_undistorted_image_;

    /// camera model
    std::shared_ptr<holo::perception::CameraModel<float32_t> > camera_model_;
  
    std::string camera_name_;

    /// params for image operation
    bool do_crop_;
    bool do_rot_;
    int32_t crop_x_start_;
    int32_t crop_y_start_;
    int32_t crop_width_;
    int32_t crop_height_;
    cv::Mat image_rot_mat_; /// 2d image rotation matrix
    cv::Mat algorithm_image_;

public:
    std::string camera_intrinsic_file_;
    std::string camera_extrinsic_file_;
};

}   /// end namespace perception

}   /// end namespace holo

#endif  /// HOLO_PERCEPTION_DETECTION_IMAGE_DETECTOR_RESOURCE_H_
