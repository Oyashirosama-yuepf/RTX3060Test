/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_item2.h
 * @brief New Lane Item
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-10-08"
 */

#ifndef HOLO_MAP_NAVIGATOR_BASE_BOUNDARY_ID_H_
#define HOLO_MAP_NAVIGATOR_BASE_BOUNDARY_ID_H_

#include <memory>

#include <holo/map/common/common_define.h>
#include <holo/map/base/feature_id/feature_id.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace base
{
class BoundaryId : public FeatureId
{
public:
    BoundaryId() = default;
    BoundaryId(holo::uint64_t val) : FeatureId(val)
    {
    }
};
}
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_LANE_ITEM2_H_ */
