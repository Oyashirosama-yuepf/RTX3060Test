/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file keypoint2.cpp
 * @brief Instantiation of keypoint2
 * @author tanghui(tanghui@holomaitc.com)
 * @date 2019-12-09
 */

#include <holo/vision/keypoint2.h>

#define INSTANTIATE(Scalar) template class KeyPoint2T<Scalar>;

namespace holo
{
namespace vision
{
INSTANTIATE(float32_t);
INSTANTIATE(float64_t);
}  // namespace vision
}  // namespace holo
