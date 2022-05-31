/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file struct.h
 * @brief Data model for lane navigation
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-12-08"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_ENTITY_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_ENTITY_H_

#include <memory>

#include <holo/common/road_type.h>
#include <holo/core/types.h>

#include <holo/map/common/common_define.h>

#include <holo/map/feature/navigator/advice/lane_navigator/target_region.h>
#include <holo/map/format/base/lane_group.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
using SceneCategory = holo::map::navigator::advice::TargetRegion::SceneType;

struct SceneSeed
{
    IdType current_lane_id = 0U;
    IdType main_link_id    = 0U;
    IdType branch_link_id  = 0U;

    std::string ToJSONString() const
    {
        std::stringstream out;
        out << "{";
        out << ", \"current_lane_id\": " << this->current_lane_id;
        out << ", \"main_link_id\": " << this->main_link_id;
        out << ", \"branch_link_id\": " << this->branch_link_id;
        out << "}";
        return out.str();
    }
};

struct SceneSketch
{
    SceneSketch()                          = default;
    IdType                    from_link_id = 0U;
    IdType                    to_link_id   = 0U;
    std::vector<IdType>       passed_lane_ids;
    SceneCategory             scene_catagory;
    holo::float64_t           distance_to_scene;
    std::vector<TargetRegion> target_regions;
    std::string               ToJSONString() const
    {
        std::stringstream out;
        out << "{";
        out << ", \"from_link_id\": " << this->from_link_id;
        out << ", \"to_link_id\": " << this->to_link_id;
        out << ", \"passed_lane_ids\": " << marshal::FormatToString(this->passed_lane_ids);
        out << ", \"scene_catagory\": " << static_cast<int>(this->scene_catagory);
        out << ", \"distance_to_scene\": " << this->distance_to_scene;
        out << ", \"target_regions: " << TargetRegion::FormatToString(this->target_regions);
        out << "}";
        return out.str();
    }
};

struct LinkSnap
{
    holo::map::format::PtrLaneGroup link = nullptr;
    holo::common::RoadType          road_category;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_ENTITY_H_ */
