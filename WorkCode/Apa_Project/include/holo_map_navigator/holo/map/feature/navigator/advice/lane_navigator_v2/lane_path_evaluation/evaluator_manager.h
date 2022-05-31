/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file evaluator_manager.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-11-27
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_EVALUATOR_EVALUATOR_MANAGER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_EVALUATOR_EVALUATOR_MANAGER_H_

#include <vector>

#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_evaluation/evaluator_base.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/participant_group.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class EvaluatorManager
{
public:
    using EvaluatorSPtrType     = std::shared_ptr<holo::map::navigator::advice::EvaluatorBase>;
    using ParticipantGroupType = holo::map::navigator::advice::ParticipantGroup;

public:
    holo::bool_t AddInstance(EvaluatorSPtrType evaluator);

    holo::bool_t Evaluate(ParticipantGroupType& group);

    void Clear();

private:
    std::vector<EvaluatorSPtrType> evaluators_;
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_EXPECTOR_EXPECTOR_MANAGER_H_ */