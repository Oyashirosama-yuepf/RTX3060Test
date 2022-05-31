/*!
 *  \brief
 *  \author huanglihong (huanglihong@holomatic.com)
 *  \date 2018-05-17
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_COMMON_MATH_HPP_
#define HOLO_PERCEPTION_COMMON_MATH_HPP_

#include <holo/perception2/common/math.h>
#include <algorithm>
#include <numeric>
#include <functional>

namespace holo
{
namespace perception
{

template <typename Scalar>
Scalar avg(const std::vector<Scalar>& v)
{
    Scalar sum = std::accumulate(std::begin(v), std::end(v), 0.0);
    return sum / v.size();
}

template <typename Scalar>
Scalar var(const std::vector<Scalar>& v, Scalar m)
{
    Scalar accum = 0.0;
    std::for_each (std::begin(v), std::end(v), [&](const Scalar d) 
    {
        accum += (d - m) * (d - m);
    });
    return accum / v.size();
}

}
}

#endif
