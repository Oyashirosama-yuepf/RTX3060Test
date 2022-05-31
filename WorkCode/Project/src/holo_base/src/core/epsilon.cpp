/*!
 * @file epsilon.cpp
 * @brief epsilon
 * @author luopei (), luopei@holomatic.com
 * @date 2017-11-29
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/core/epsilon.h>

namespace holo
{
[[deprecated]] const bool      EpsilonT<bool>::value      = 0u;
[[deprecated]] const int32_t   EpsilonT<int32_t>::value   = 0;
[[deprecated]] const uint32_t  EpsilonT<uint32_t>::value  = 0u;
[[deprecated]] const uint64_t  EpsilonT<uint64_t>::value  = 0u;
[[deprecated]] const float32_t EpsilonT<float32_t>::value = 1e-5f;
[[deprecated]] const float64_t EpsilonT<float64_t>::value = 1e-10;
}  // namespace holo
