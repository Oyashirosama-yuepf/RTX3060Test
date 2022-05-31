/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spline.cpp
 * @brief holo spline cpp file
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-12-06
 */

#include <holo/numerics/spline.h>
#include <holo/numerics/impl/spline.hpp>

namespace holo
{
template class SplineT<2>;
template class SplineT<3>;
}  // namespace holo
