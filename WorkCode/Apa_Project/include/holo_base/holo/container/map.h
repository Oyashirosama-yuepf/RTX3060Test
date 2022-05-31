/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map.h
 * @brief Wrapper for map type container
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-16
 */

#ifndef HOLO_CONTAINER_MAP_H_
#define HOLO_CONTAINER_MAP_H_

#include <map>
#include <holo/core/allocator.h>

namespace holo
{

namespace container
{

template<typename Key, typename T, size_t N, typename Compare = std::less<Key>>
using Map = std::map<Key, T, Compare, holo::core::Allocator<std::pair<Key, T>, N>>;

template<typename Key, typename T, size_t N, typename Compare = std::less<Key>>
using Multimap = std::multimap<Key, T, Compare, holo::core::Allocator<std::pair<Key, T>, N>>;

} // namespace container

} // namespace holo

#endif
