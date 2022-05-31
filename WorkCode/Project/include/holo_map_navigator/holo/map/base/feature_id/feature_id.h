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

#ifndef HOLO_MAP_NAVIGATOR_BASE_FEATURE_ID_H_
#define HOLO_MAP_NAVIGATOR_BASE_FEATURE_ID_H_

#include <memory>

#include <holo/map/common/common_define.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace base
{
class FeatureId
{
public:
    FeatureId() = default;
    FeatureId(holo::uint64_t val)
    {
        this->value_ = val;
    }
    FeatureId const& operator=(holo::uint64_t val)
    {
        this->value_ = val;
        return *this;
    }
    holo::bool_t operator==(holo::uint64_t val)
    {
        return this->value_ == val;
    }
    holo::uint64_t Value()
    {
        return this->value_;
    }

protected:
    holo::uint64_t value_;
};
}
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_LANE_ITEM2_H_ */
