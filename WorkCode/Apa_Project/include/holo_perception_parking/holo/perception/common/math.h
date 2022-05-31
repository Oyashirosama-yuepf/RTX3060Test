/*!
 *  \brief
 *  \author huanglihong (huanglihong@holomatic.com)
 *  \date 2018-05-17
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_COMMON_MATH_
#define HOLO_PERCEPTION_COMMON_MATH_

#include <cmath>
#include <vector>

namespace holo
{
namespace perception
{

template <typename Scalar>
inline Scalar sigmoid(Scalar p)
{
    return 1.0 / (1.0 + exp(-p));
}

template <typename Scalar>
Scalar avg(const std::vector<Scalar>& v);

template <typename Scalar>
Scalar var(const std::vector<Scalar>& v, Scalar mean);

}
}

#endif
