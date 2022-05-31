/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_base.cpp
 * @brief This file instantiate CameraBaseT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-12-10
 */

#include <holo/common/impl/camera_base.hpp>

#define INSTANTIATE(Scalar) template class CameraBaseT<Scalar>;

namespace holo
{
INSTANTIATE(float32_t);
// INSTANTIATE(float64_t);  // TODO: to be implement after IntrinsicT support float64_t
}  // namespace holo
