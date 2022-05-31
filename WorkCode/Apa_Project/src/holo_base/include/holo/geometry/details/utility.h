/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file utility.h
 * @brief This header file defines utility functions related to curve module.
 * @author ZhangJiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-18
 */

#ifndef HOLO_GEOMETRY_DETAILS_UTILITY_H_
#define HOLO_GEOMETRY_DETAILS_UTILITY_H_

#include <holo/core/exception.h>

namespace holo
{
namespace geometry
{
namespace details
{
namespace utility
{
/**
 * @brief Find section in a sorted container a key lays in.
 * @details Get the index value that satisfis compare(container[index], key) and compare(key, container[index + 1])
 * using binary search algorithm.
 * The elements in container shall be sorted, That means the following conditions
 * should be true: for each index in [0, size() - 2) and any Key type value.
 * - if compare(container[index], value) == false, then compare(container[index + 1], value) == false
 * - if compare(container[index + 1], value) == true, then compare(container[index], value) == true
 *
 * @tparam Container Container type
 * @tparam Key Key type
 * @tparam Compare Compare method functor.
 * @param container The container contains section info.
 * @param key Key value to find.
 * @param compare compare container element and key method.
 *
 * @return start index of section.
 *
 * @throws holo::exception::OutOfRangeException
 */
template <typename Container, typename Key, typename Compare>
size_t SearchSection(Container const& container, Key key, Compare compare)
{
    size_t first = 0;
    size_t last  = container.size() - 1;
    if (!(compare(container[first], key) && compare(key, container[last])))
    {
        throw holo::exception::OutOfRangeException("");
    }
    while (last - first > 1)
    {
        if (compare(key, container[(last + first) / 2]))
        {
            last = (last + first) / 2;
        }
        else
        {
            first = (last + first) / 2;
        }
    }
    return first;
}

/**
 * @brief Search in forward direction for section a key lays in with index hint.
 *
 * @tparam Container Container type
 * @tparam Key Key type
 * @tparam Compare Compare method functor.
 * @param idx Index hint to search from
 * @param container The container contains section info.
 * @param key Key value to find.
 * @param compare compare container element and key method.
 *
 * @return start index of section
 *
 * @throws holo::exception::OutOfRangeException if arc length is out of curve length range
 */
template <typename Container, typename Key, typename Compare>
size_t SearchSectionForward(size_t idx, Container const& container, Key key, Compare compare)
{
    for (; idx < container.size() - 1; ++idx)
    {
        if (compare(container[idx], key) && compare(key, container[idx + 1]))
        {
            return idx;
        }
    }
    throw holo::exception::OutOfRangeException("");
}

/**
 * @brief Search in backward direction for section a key lays in with index hint.
 *
 * @tparam Container Container type
 * @tparam Key Key type
 * @tparam Compare Compare method functor.
 * @param idx Index hint to search from
 * @param container The container contains section info.
 * @param key Key value to find.
 * @param compare compare container element and key method.
 *
 * @return start index of section
 *
 * @throws holo::exception::OutOfRangeException if arc length is out of curve length range
 */
template <typename Container, typename Key, typename Compare>
size_t SearchSectionBackward(size_t idx, Container const& container, Key key, Compare compare)
{
    for (; idx > 0; --idx)
    {
        if (compare(container[idx - 1], key) && compare(key, container[idx]))
        {
            return --idx;
        }
    }
    throw holo::exception::OutOfRangeException("");
}

/**
 * @brief Find section in a sorted container a key lays in with index hint.
 *
 * @tparam Container Container type
 * @tparam Key Key type
 * @tparam Compare Compare method functor.
 * @param idx Index hint to search from
 * @param container The container contains section info.
 * @param key Key value to find.
 * @param compare compare container element and key method.
 *
 * @return start index of section
 *
 * @throws holo::exception::OutOfRangeException if arc length is out of curve length range
 */
template <typename Container, typename Key, typename Compare>
size_t SearchSectionWithHint(size_t idx, Container const& container, Key key, Compare compare)
{
    if (compare(container[idx], key))
    {
        return SearchSectionForward(idx, container, key, compare);
    }
    else
    {
        return SearchSectionBackward(idx, container, key, compare);
    }
}

}  // namespace utility
}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif
