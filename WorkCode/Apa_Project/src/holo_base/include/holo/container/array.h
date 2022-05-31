/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file array.h
 * @brief Wrapper for array type container
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-16
 */

#ifndef HOLO_CONTAINER_ARRAY_H_
#define HOLO_CONTAINER_ARRAY_H_

#include <array>

namespace holo
{

namespace container
{

template<typename T, size_t N>
using Array = std::array<T, N>;

} // namespace container

} // namespace holo

#endif

