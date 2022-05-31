/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file queue.h
 * @brief Wrapper for queue type container
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-16
 */

#ifndef HOLO_CONTAINER_QUEUE_H_
#define HOLO_CONTAINER_QUEUE_H_

#include <queue>
#include <holo/core/allocator.h>
#include <holo/container/deque.h>

namespace holo
{

namespace container
{

template<typename T, size_t N, typename Container = holo::container::Deque<T, N> >
using Queue = std::queue<T, Container>;

template<typename T,
         size_t N,
         typename Container = holo::container::Deque<T, N>,
         typename Compare = std::less<typename Container::value_type> >
using PriorityQueue = std::priority_queue<T, Container, Compare>;

} // namespace container

} // namespace holo

#endif
