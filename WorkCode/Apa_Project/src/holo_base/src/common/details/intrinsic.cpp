/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intrinsic.cpp
 * @brief the instantiation of template class Intrinsic
 * @author lifeng@holomatic.com
 * @date Dec 18, 2020
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */
#include <holo/common/details/intrinsic.h>
#include <holo/common/details/impl/intrinsic.hpp>

namespace holo
{
namespace common
{
namespace details
{
template class PinholeIntrinsicT<float32_t>;
template class PinholeIntrinsicT<float64_t>;

template class FisheyeIntrinsicT<float32_t>;
template class FisheyeIntrinsicT<float64_t>;

template class OmnidirectionalIntrinsicT<float32_t>;
template class OmnidirectionalIntrinsicT<float64_t>;
}  // namespace details
}  // namespace common
}  // namespace holo
