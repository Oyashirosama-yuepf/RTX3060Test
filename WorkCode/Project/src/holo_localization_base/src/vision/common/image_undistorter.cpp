/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_undistorter.cpp
 * @brief source file of image undistorter
 * @author Shuaijie Li @ lishuaijie@holomatic.com
 * @date 2021-09-26
 */

#include <holo/localization/vision/common/image_undistorter.h>
#include <holo/localization/vision/common/impl/image_undistorter.hpp>

namespace holo
{
namespace localization
{
template class ImageUndistorterT<holo::common::details::CameraIntrinsicBaseT<float32_t>>;
template class ImageUndistorterT<holo::common::details::CameraIntrinsicBaseT<float64_t>>;
}  // namespace localization
}  // namespace holo

