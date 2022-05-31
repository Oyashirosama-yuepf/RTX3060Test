/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_fundamental_matrix_problem.cpp
 * @brief
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-24"
 */

#include <holo/localization/vision/geometry/ransac_fundamental_matrix_problem.h>
#include <holo/probability/ransac/ransac.h>
#include <holo/probability/ransac/ransac_problem.h>
#include <holo/localization/vision/geometry/impl/ransac_fundamental_matrix_problem.hpp>
#include <holo/probability/ransac/impl/ransac.hpp>
#include <holo/probability/ransac/impl/ransac_problem.hpp>

namespace holo
{
template class holo::RansacProblemT<Matrix3T<float32_t> >;
template class holo::RansacProblemT<Matrix3T<float64_t> >;

namespace localization
{
namespace vision
{
template class holo::localization::vision::RansacFundamentalMatrixProblemT<float32_t>;
template class holo::localization::vision::RansacFundamentalMatrixProblemT<float64_t>;

}  // namespace vision
}  // namespace localization

template class holo::Ransac<holo::localization::vision::RansacFundamentalMatrixProblemT<float32_t> >;
template class holo::Ransac<holo::localization::vision::RansacFundamentalMatrixProblemT<float64_t> >;

}  // namespace holo
