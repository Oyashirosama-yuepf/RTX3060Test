/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file type_traits.h
 * @brief This file defines basic type traits.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-2-6
 */

#ifndef HOLO_CORE_TYPE_TRAITS_H_
#define HOLO_CORE_TYPE_TRAITS_H_

#include <type_traits>

#include "types.h"

namespace holo
{

/**
 * @addtogroup core
 * @{
 */

/**
 * @brief If all conditions B are true, provide member constant value equal to true. Otherwise value is false.
 *
 * @tparam B Bool type conditions.
 */
template<holo::bool_t... B>
struct And {};

template<holo::bool_t B, holo::bool_t... Rest>
struct And<B, Rest...> : std::integral_constant<holo::bool_t, B && And<Rest...>::value>
{};

template<holo::bool_t B>
struct And<B> : std::integral_constant<holo::bool_t, B>
{};


/**
 * @brief If all conditions B are false, provide member constant value equal to false. Otherwise value is true.
 *
 * @tparam B Bool type conditions.
 */
template<holo::bool_t... B>
struct Or {};

template<holo::bool_t B, holo::bool_t... Rest>
struct Or<B, Rest...> : std::integral_constant<holo::bool_t, B || Or<Rest...>::value>
{};

template<holo::bool_t B>
struct Or<B> : std::integral_constant<holo::bool_t, B>
{};

/**
 * @}
 */
}

#endif

