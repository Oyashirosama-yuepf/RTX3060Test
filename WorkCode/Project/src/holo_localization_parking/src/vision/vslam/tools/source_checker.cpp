/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file source_checker.cpp
 * @brief The instantiation of source state check.
 * @author guopeikai@holomatic.com
 * @date Sep 28, 2021
 */

#include <holo/localization/tools/source_checker.h>
#include <holo/localization/vision/vslam/common_types.h>

#include <holo/localization/tools/impl/source_checker.hpp>
using namespace holo::localization::vision::vslam;

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template class SourceCheckerT<PointFeaturePtrList>;
template class SourceCheckerT<ObstaclePtrList>;
template class SourceCheckerT<ParkingSlotFrameType>;
}  // namespace localization
}  // namespace holo
