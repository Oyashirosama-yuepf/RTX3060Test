/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_type_converter.h
 * @brief header file of image type converter
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-05-07"
 */

#ifndef HOLO_CMW_APPS_LOCALIZATION_VISION_IMAGE_TYPE_CONVERTER_H_
#define HOLO_CMW_APPS_LOCALIZATION_VISION_IMAGE_TYPE_CONVERTER_H_

#include <holo/common/image.h>

#ifdef USE_TDA4
#include <localization/vision/birdview/tda4_nv12torgb/TadlInference.h>
#endif

namespace holo
{
namespace vision
{
/**
 * @brief this class is used to convert yuv image to rgb image
 */
class ImageTypeConverter
{
public:
    /**
     * @brief constructor
     *
     * @param[in] height height of image
     * @param[in] width width of image
     */
    ImageTypeConverter(uint16_t const height, uint16_t const width);

    /**
     * @brief disable copy constructor
     *
     * @param[in] other
     */
    ImageTypeConverter(ImageTypeConverter const& other) = delete;

    /**
     * @brief disable assignment operator
     *
     * @param[in] other
     * @return ImageTypeConverter const&
     */
    ImageTypeConverter const& operator=(ImageTypeConverter const& other) = delete;

    /**
     * @brief desctrutor
     *
     */
    ~ImageTypeConverter();

    /**
     * @brief convert image from yuv to rgb
     *
     * @param[in] in the input image in yuv format
     * @return cv::Mat output image in rgb format
     */
    cv::Mat Compute(cv::Mat const& in) const;

protected:
#ifdef USE_TDA4
    std::shared_ptr<AppTadlPrec> app_prec_img_ptr_;       ///< tda4 image converter
    holo::uint64_t               num_bytes_per_channel_;  ///< number bytes of one rgb channel
    cv::Mat rgb_chw_mat_; ///< mat to store image in chw
    std::vector<cv::Mat> rgb_channels_; ///< r, g, b channel roi of rgb_chw_mat_
#endif
};  // ImageTypeConverter
}  // namespace vision
}  // namespace holo
#endif
