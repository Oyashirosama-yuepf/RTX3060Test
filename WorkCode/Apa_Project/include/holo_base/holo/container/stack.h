/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file stack.h
 * @brief Wrapper for stack type container
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-16
 */

#ifndef HOLO_CONTAINER_STACK_H_
#define HOLO_CONTAINER_STACK_H_

#include <holo/container/deque.h>
#include <stack>

namespace holo
{

namespace container
{

template<typename T, size_t N, Container = holo::container::Deque<T, N> >
using Stack = std::stack<T, Container>;

} // namespace container

} // namespace holo

#endif
