/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intrinsic.cpp
 * @brief the instantiation of template class Intrinsic
 * @author lichao@holomatic.com
 * @date Sep 17, 2019
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */
#include <holo/common/intrinsic.h>
#include <holo/common/impl/intrinsic.hpp>

namespace holo
{
template class IntrinsicT<float32_t>;

template class IntrinsicT<float64_t>;

}  // namespace holo
