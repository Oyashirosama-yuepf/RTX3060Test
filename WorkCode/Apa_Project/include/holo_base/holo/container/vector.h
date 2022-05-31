/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vector.h
 * @brief Wrapper for vector type container
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-16
 */

#ifndef HOLO_CONTAINER_VECTOR_H_
#define HOLO_CONTAINER_VECTOR_H_

#include "details/fixed_size_vector.h"
#include "details/vector.h"

namespace holo
{
namespace container
{

template <typename T, size_t N, typename Allocator = std::allocator<T>>
using VectorT [[deprecated]] = holo::container::details::FixedSizeVector<T, N, Allocator>;

/**
 * @brief Vector container with predefined maximum element size.
 *
 * @tparam T Type of the elements
 * @tparam SIZE Max size of the vector.
 * @tparam Allocator An allocator that is used to acquire/release memory and construct/destroy the elements.
 */
template <typename T, size_t N, typename Allocator = std::allocator<T>>
using Vector = holo::container::details::Vector<T, N, Allocator>;

template <typename T, typename Allocator = std::allocator<T>>
using AutoVector = holo::container::details::Vector<T, std::numeric_limits<size_t>::max(), Allocator>;

template <typename T, typename Allocator = std::allocator<T>>
using ManualVector = holo::container::details::Vector<T, 0U, Allocator>;

}  // namespace container
}  // namespace holo

#endif
