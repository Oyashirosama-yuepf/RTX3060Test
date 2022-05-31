/**
 * @file   ransac_problem_data_container_adapter.cpp
 * @brief  ransac_problem_data_container_adapter.cpp
 * @author luopei (), luopei@holomatic.com
 * @date 2018-03-28
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/probability/ransac/impl/ransac_problem_data_container_adapter.hpp>

#define INSTANTIATE(SampleType)                                                                                        \
    template class RansacProblemDataContainerAdapterStdVectorT<SampleType>;                                            \

namespace holo
{
INSTANTIATE(holo::geometry::Point2T<float32_t>);
INSTANTIATE(holo::geometry::Point2T<float64_t>);
INSTANTIATE(holo::geometry::Point3T<float32_t>);
INSTANTIATE(holo::geometry::Point3T<float64_t>);
}  // namespace holo
