/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file scene_assist.h
 * @brief Assist for scene
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-11-08"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_SCENE_ASSIST_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_SCENE_ASSIST_H_

#include <memory>

#include <holo/common/road_type.h>
#include <holo/core/types.h>

#include <holo/map/common/common_define.h>

#include <holo/map/feature/navigator/advice/lane_navigator/target_region.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class LaneItem;
class LanePath;
/**
 * @brief The basic element of lane path
 *
 */
class SceneAssist
{
public:
    using RoadCategory = holo::common::RoadType;

public:
    static holo::bool_t CheckLinkTurnTo(RetrieverSPType ret, IdType const main, IdType const branch,
                                 holo::bool_t const is_right, holo::bool_t& is_turn);

    static holo::bool_t GetRoadCategoryFromLink(IdType const link_id, RoadCategory& road_category);

    static holo::bool_t GetRestedRouteLinkIds(VecIdType const& link_ids, std::size_t const start_idx,
                                                    VecIdType& rested);
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_SCENE_ASSIST_H_ */
