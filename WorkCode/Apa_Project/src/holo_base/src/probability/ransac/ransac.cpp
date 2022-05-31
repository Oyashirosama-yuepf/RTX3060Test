/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_plane3_fitting_problem.cpp
 * @brief this class represents ransac solving specific fitting plane3 problem
 * @author luopei(luopei@holomaitc.com)
 * @date "2018-03-28"
 */

#include <holo/probability/ransac/ransac.h>
#include <holo/probability/ransac/ransac_line2_fitting_problem.h>
#include <holo/probability/ransac/ransac_plane3_fitting_problem.h>
#include <holo/probability/ransac/impl/ransac.hpp>

namespace holo
{
template class Ransac<RansacLine2FittingProblemT<float32_t>>;
template class Ransac<RansacLine2FittingProblemT<float64_t>>;
template class Ransac<RansacPlane3FittingProblemT<float32_t>>;
template class Ransac<RansacPlane3FittingProblemT<float64_t>>;

}  // namespace holo