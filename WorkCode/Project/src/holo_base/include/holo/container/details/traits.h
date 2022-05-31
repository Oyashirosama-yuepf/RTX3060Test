/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file traits.h
 * @brief Useful type traits for container module
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-12
 */

#ifndef HOLO_CONTAINER_INTERNAL_TRAITS_H_
#define HOLO_CONTAINER_INTERNAL_TRAITS_H_

#include <holo/core/types.h>

#include <type_traits>

namespace holo
{
namespace container
{
template <typename Iter>
using IsInputIterator =
    std::integral_constant<holo::bool_t, std::is_convertible<typename std::iterator_traits<Iter>::iterator_category,
                                                             std::input_iterator_tag>::value>;
}
}  // namespace holo

#endif
