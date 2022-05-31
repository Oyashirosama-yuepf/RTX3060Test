/*!
 * @file navstate.cpp
 * @brief the implementation of navstate class
 * @author lichao@holomatic.com
 * @date Oct 07, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */
#include <holo/localization/common/navstate.h>

namespace holo
{
namespace localization
{
template class NavstateT<float32_t>;
template class NavstateT<float64_t>;

template class AdvancedNavstateT<float32_t>;
template class AdvancedNavstateT<float64_t>;
}  // namespace localization

}  // namespace holo

#undef INSTANTIATE
#undef INSTANTIATE_MEASUREMENT
