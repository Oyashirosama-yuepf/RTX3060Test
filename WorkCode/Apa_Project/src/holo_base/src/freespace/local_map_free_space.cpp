/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file local_map_free_space.cpp
 * @brief This src file instantiate LocalMapFreeSpace.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-27
 */

#include <holo/freespace/impl/local_map_free_space.hpp>

#define INSTANTIATE(Scalar) template class LocalMapFreeSpace<Scalar>;

namespace holo
{
INSTANTIATE(float32_t);
INSTANTIATE(float64_t);
}  // namespace holo