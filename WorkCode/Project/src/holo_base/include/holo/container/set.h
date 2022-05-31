/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file set.h
 * @brief Wrapper for set type container
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-16
 */

#ifndef HOLO_CONTAINER_SET_H_
#define HOLO_CONTAINER_SET_H_

#include <set>
#include <holo/core/allocator.h>

namespace holo
{

namespace container
{

template<typename Key, std::size_t N, typename Compare = std::less<Key> >
using Set = std::set<Key, Compare, holo::core::Allocator<Key, N>>;

template<typename Key, std::size_t N, typename Compare = std::less<Key> >
using Multiset = std::multiset<Key, Compare, holo::core::Allocator<Key, N>>;

} // namespace container

} // namespace holo

#endif
