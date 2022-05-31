/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file deque.h
 * @brief Wrapper for deque type container
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-16
 */

#ifndef HOLO_CONTAINER_DEQUE_H_
#define HOLO_CONTAINER_DEQUE_H_

#include <holo/core/allocator.h>
#include <deque>
#include "details/deque.h"

namespace holo
{

namespace container
{

template<typename T, std::size_t N>
using DequeT [[deprecated]] = holo::container::details::Deque<T, N>;

template<typename T, std::size_t N>
using Deque = holo::container::details::Deque<T, N>;

} // namespace container

} // namespace holo

#endif
