/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file list.h
 * @brief Wrapper for list type container
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-16
 */

#ifndef HOLO_CONTAINER_LIST_H_
#define HOLO_CONTAINER_LIST_H_

#include <list>
#include <holo/core/allocator.h>

namespace holo
{

namespace container
{

template<typename T, size_t N>
using List = std::list<T, holo::core::Allocator<T, N>>;

} // namespace container

} // namespace holo

#endif
