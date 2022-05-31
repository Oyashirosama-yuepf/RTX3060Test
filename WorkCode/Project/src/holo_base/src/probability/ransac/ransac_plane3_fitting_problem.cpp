/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_plane3_fitting_problem.cpp
 * @brief this class represents ransac solving specific fitting plane3 problem
 * @author luopei(luopei@holomaitc.com)
 * @date "2022-01-12"
 */
#include <holo/probability/ransac/ransac_plane3_fitting_problem.h>
#include <holo/probability/ransac/impl/ransac_plane3_fitting_problem.hpp>

namespace holo
{
template class RansacPlane3FittingProblemT<float32_t>;
template class RansacPlane3FittingProblemT<float64_t>;

}  // namespace holo
