/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_feature.cpp
 * @brief the instantiation of template class PointFeatureT
 * @author lifeng@holomatic.com
 * @date 2021-01-07
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#include <holo/parking/vision/point_feature.h>

namespace holo
{
namespace parking
{
namespace vision
{
template class PointFeatureT<float32_t>;
template class PointFeatureT<float64_t>;
}  // namespace vision
}  // namespace parking
}  // namespace holo
