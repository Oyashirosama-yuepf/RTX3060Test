/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file segmentation_2d.cpp
 * @brief Instantiation of class Segmentation2DT.
 * @author liufangyuan(liufangyuan@holomaitc.com)
 * @date "2019-12-17"
 */

#include <holo/common/segmentation_2d.h>

#define INSTANTIATE(Scalar) template class Segmentation2DT<Scalar>;

namespace holo
{
INSTANTIATE(holo::float32_t);
INSTANTIATE(holo::float64_t);
}  // namespace holo

#undef INSTANTIATE
