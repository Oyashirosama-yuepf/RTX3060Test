/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_type_converter.cpp
 * @brief source file of image_type_converter
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-05-07"
 */
#include <glog/logging.h>

#include <opencv2/core.hpp>

#include <localization/vision/birdview/image_type_converter.h>

namespace holo
{
namespace vision
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImageTypeConverter::ImageTypeConverter(uint16_t const height, uint16_t const width)
{
    (void)height;
    (void)width;

#ifdef USE_TDA4
    LOG(INFO) << "ImageTypeConverter -- use tda4 to convert yuv to rgb!!!";
    app_prec_img_ptr_      = std::make_shared<AppTadlPrec>(height, width, "RGB");
    num_bytes_per_channel_ = height * width;
    rgb_chw_mat_ = cv::Mat(height * 3u, width, CV_8UC1);
    rgb_channels_.push_back(rgb_chw_mat_.rowRange(0u, height));
    rgb_channels_.push_back(rgb_chw_mat_.rowRange(height, height * 2u));
    rgb_channels_.push_back(rgb_chw_mat_.rowRange(height * 2u, height * 3u));
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImageTypeConverter::~ImageTypeConverter()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat ImageTypeConverter::Compute(cv::Mat const& in) const
{
    cv::Mat out;
#ifdef USE_TDA4
    app_prec_img_ptr_->ReadArr(in.data, app_prec_img_ptr_->dl_height_, 0u);
    app_prec_img_ptr_->GetConvertData(rgb_chw_mat_.data);
    cv::merge(rgb_channels_, out);
#else
    cv::cvtColor(in, out, cv::COLOR_YUV2RGB_NV12);
#endif
    return out;
}
}  // namespace vision
}  // namespace holo
