/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file expector_factory.h
 * @brief A factory for making expector
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-01-27
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_EXPECTOR_EXPECTOR_FACTORY_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_EXPECTOR_EXPECTOR_FACTORY_H_

#include <vector>

#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_expector/expector_base.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/participant_group.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class ExpectorFactory
{
public:
    using ExpectorSPtrType     = std::shared_ptr<ExpectorBase>;
    using SceneSketchSPtrType  = std::shared_ptr<scene::SceneSketch>;
    using SceneCategoryType    = scene::SceneSketch::SceneCategory;

    using RouteSceneType     = scene::RouteScene;
    using RouteSceneSPtrType = std::shared_ptr<RouteSceneType>;

public:
    static ExpectorSPtrType MakeExpector(SceneSketchSPtrType scene_sketch, RouteSceneSPtrType route_scene);
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_EXPECTOR_EXPECTOR_FACTORY_H_ */