/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file unordered_set.h
 * @brief Wrapper for unordered_set type container
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-16
 */

#ifndef HOLO_CONTAINER_UNORDERED_SET_H_
#define HOLO_CONTAINER_UNORDERED_SET_H_

#include <unordered_set>
#include <holo/core/allocator.h>

namespace holo
{

namespace container
{

template<typename Key, size_t N, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key> >
using UnorderedSet = std::unordered_set<Key, Hash, KeyEqual, holo::core::Allocator<Key, N>>;

template<typename Key, size_t N, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key> >
using UnorderedMultiset = std::unordered_multiset<Key, Hash, KeyEqual, holo::core::Allocator<Key, N>>;

} // namespace container

} // namespace holo

#endif
