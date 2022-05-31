/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file multi_intersection_evaluator.h
 * @brief The evaulator is used to score by multi-intersection scene
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-02-24
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_EVALUATION_MULTI_INTERSECTION_EVALUATOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_EVALUATION_MULTI_INTERSECTION_EVALUATOR_H_

#include <vector>

#include <holo/map/common/common_define.h>
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
class MultiIntersectionEvaluator : public EvaluatorBase
{
public:
    MultiIntersectionEvaluator(SceneSketchSPtrType scene_sketch);

    /**
     * @brief Whether or not the expector is enabled
     *
     * @return holo::bool_t True, enabled; false, otherwise
     */
    virtual holo::bool_t Enabled() override;

    /**
     * @brief Calculate to recommend different lane paths in participant group
     *
     * @param group Participant group containing participants, where one
     *              participant correspond to one lane path
     * @return holo::bool_t True, succeed; false otherwise
     */
    virtual holo::bool_t Evaluate(ParticipantGroupType& group);

    /**
     * @brief Whether or not terminate recommending calculation
     *
     * @return holo::bool_t True, need terminating; false, execute
     *                      next Expector calcuation
     */
    virtual holo::bool_t Terminate();

private:
    std::vector<EvaluatorSPtrType> evaluators_;
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_EVALUATION_MULTI_INTERSECTION_EVALUATOR_H_ */