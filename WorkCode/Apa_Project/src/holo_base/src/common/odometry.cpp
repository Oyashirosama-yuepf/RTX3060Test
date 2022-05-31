/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file odometry.cpp
 * @brief the instantiation of template class Odometry
 * @author Li Chao (lichao@holomatic.com)
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date Sep 14, 2019
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */
#include <holo/common/odometry.h>
#include <holo/common/impl/odometry.hpp>

namespace holo
{
namespace common
{
template class OdometryT<float32_t>;

template class OdometryT<float64_t>;

}  // namespace common
}  // namespace holo
