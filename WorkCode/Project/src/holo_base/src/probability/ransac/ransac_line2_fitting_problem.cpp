/*!
 * @file ransac_line2_fitting_problem.cpp
 * @brief ransac line2 fitting problem cpp file
 * @author luopei (), luopei@holomatic.com
 * @date 2018-03-28
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/probability/ransac/ransac.h>
#include <holo/probability/ransac/ransac_line2_fitting_problem.h>
#include <holo/probability/ransac/ransac_problem.h>
#include <holo/probability/ransac/impl/ransac.hpp>
#include <holo/probability/ransac/impl/ransac_line2_fitting_problem.hpp>
#include <holo/probability/ransac/impl/ransac_problem.hpp>

#define INSTANTIATE(Scalar)                                                                                            \
    template class RansacLine2FittingProblemT<Scalar>;                                                                 \
    template class RansacProblemT<holo::geometry::Line2T<Scalar> >;                                                                    \
    template class Ransac<RansacLine2FittingProblemT<Scalar> >;

namespace holo
{
INSTANTIATE(float32_t);
INSTANTIATE(float64_t);
}  // namespace holo
