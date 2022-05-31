/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_problem.cpp
 * @author luopei(luopei@holomaitc.com)
 * @date "2018-03-28"
 */

#include <holo/geometry/line2.h>
#include <holo/geometry/plane3.h>
#include <holo/probability/ransac/ransac_problem.h>
#include <holo/probability/ransac/impl/ransac_problem.hpp>

namespace holo
{
template class RansacProblemT<holo::geometry::Line2T<float32_t>>;
template class RansacProblemT<holo::geometry::Line2T<float64_t>>;
template class RansacProblemT<holo::geometry::Plane3T<float32_t>>;
template class RansacProblemT<holo::geometry::Plane3T<float64_t>>;

}  // namespace holo
