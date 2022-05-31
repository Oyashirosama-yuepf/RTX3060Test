/**
 *  @file path.cpp
 *  @brief Instantiation of the path with double and float
 *  @author lijiawen(lijiawen@holomatic.com)
 *  @date 2019-10-28
 *  @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/common/details/path.h>

namespace holo
{
namespace common
{
namespace details
{
#define INSTANTIATE(Scalar)                                                                                            \
    template class PathPointT<Scalar>;                                                                                 \
    template class PathT<Scalar>;

INSTANTIATE(float32_t);
INSTANTIATE(float64_t);
}
}
}  // namespace holo
