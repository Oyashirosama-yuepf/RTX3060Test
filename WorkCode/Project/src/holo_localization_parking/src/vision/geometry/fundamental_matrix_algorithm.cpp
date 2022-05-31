/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fundamental_matrix_algorithm.cpp
 * @brief source file of fundamental matrix algorightm
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-23"
 */

#include <holo/localization/vision/geometry/fundamental_matrix_algorithm.h>
#include <holo/localization/vision/geometry/impl/fundamental_matrix_algorithm.hpp>

namespace holo
{
namespace localization
{
namespace vision
{
template class FundamentalMatrix8PointsT<holo::float32_t>;
template class FundamentalMatrix8PointsT<holo::float64_t>;
}  // namespace vision
}  // namespace localization
}  // namespace holo
