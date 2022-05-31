/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spline_fitting.cpp
 * @brief spline fitting class
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @date April 08, 2020
 */

#include <holo/localization/tools/spline_fitting.h>
#include <holo/localization/tools/impl/spline_fitting.hpp>

namespace holo
{
namespace localization
{
template class SplineFittingT<2u, 5u>;
template class SplineFittingT<6u, 3u>;

}  // namespace localization
}  // namespace holo
