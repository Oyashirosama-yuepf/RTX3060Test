/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_fisheye.cpp
 * @brief This file instantiate CameraFisheyeT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-12-10
 */

#include <holo/common/impl/camera_fisheye.hpp>

#define INSTANTIATE(Scalar) template class CameraFisheyeT<Scalar>;

namespace holo
{
INSTANTIATE(float32_t);
// INSTANTIATE(float64_t);  // TODO: to be implement after IntrinsicT support float64_t
}  // namespace holo
