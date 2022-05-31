/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file evaluator_factory.h
 * @brief A factory for making expector
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-01-27
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_EVALUATION_EVALUATOR_FACTORY_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_EVALUATION_EVALUATOR_FACTORY_H_

#include <vector>

#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_evaluation/evaluator_base.h>
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
class EvaluatorFactory
{
public:
    using EvaluatorSPtrType     = std::shared_ptr<EvaluatorBase>;
    using SceneSketchSPtrType  = std::shared_ptr<scene::SceneSketch>;
    using SceneCategoryType    = scene::SceneSketch::SceneCategory;

public:
    static EvaluatorSPtrType MakeEvaluator(SceneSketchSPtrType scene_sketch);
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_EVALUATION_EVALUATOR_FACTORY_H_ */