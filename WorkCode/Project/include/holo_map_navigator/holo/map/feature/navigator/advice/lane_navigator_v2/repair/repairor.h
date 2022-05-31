/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file repairor.h
 * @brief Repair for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REPAIR_REPAIROR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REPAIR_REPAIROR_H_

#include <holo/core/types.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{

class Repairor
{
public:
    template <typename O>
    static holo::bool_t Repair(O& origin);

    template <typename O, typename T>
    static holo::bool_t Repair(O const& origin, T& target);
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REPAIR_REPAIROR_H_ */