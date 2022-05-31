/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fundamental_matrix_solver.cpp
 * @brief source file of fundamental matrix solver class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-24"
 */

#include <holo/localization/vision/geometry/fundamental_matrix_solver.h>
#include <holo/localization/vision/geometry/impl/fundamental_matrix_solver.hpp>

namespace holo
{
namespace localization
{
namespace vision
{
template class FundamentalMatrixSolverT<holo::float32_t>;
template class FundamentalMatrixSolverT<holo::float64_t>;
}  // namespace vision
}  // namespace localization
}  // namespace holo
