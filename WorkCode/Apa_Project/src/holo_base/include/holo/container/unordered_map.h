/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file unordered_map.h
 * @brief Wrapper for unordered_map type container
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-16
 */

#ifndef HOLO_CONTAINER_UNORDERED_MAP_H_
#define HOLO_CONTAINER_UNORDERED_MAP_H_

#include <unordered_map>
#include <holo/core/allocator.h>

namespace holo
{

namespace container
{

template<typename Key, typename T, size_t N, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key> >
using UnorderedMap = std::unordered_map<Key, T, Hash, KeyEqual, holo::core::Allocator<std::pair<Key const, T>, N>>;

template<typename Key, typename T, size_t N, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
using UnorderedMultimap = std::unordered_multimap<Key, T, Hash, KeyEqual, holo::core::Allocator<std::pair<Key const, T>, N>>;

} // namespace container

} // namespace holo

#endif
