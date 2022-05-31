/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file evaluator_base.h
 * @brief Evalutator is used to score lane path
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-01-27
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_EVALUATION_EVALUATOR_BASE_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_EVALUATION_EVALUATOR_BASE_H_

#include <vector>

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
class EvaluatorBase
{
public:
    using ParticipantGroupType = holo::map::navigator::advice::ParticipantGroup;
    using EvaluatorSPtrType     = std::shared_ptr<EvaluatorBase>;
    using SceneSketchSPtrType  = std::shared_ptr<scene::SceneSketch>;

public:
    /**
     * @brief Whether or not the expector is enabled
     *
     * @return holo::bool_t
     */
    virtual holo::bool_t Enabled() = 0;

    /**
     * @brief Calculate to recommend different lane paths in participant group
     *
     * @param group Participant group containing participants, where one
     *              participant correspond to one lane path
     * @return holo::bool_t True, succeed; false otherwise
     */
    virtual holo::bool_t Evaluate(ParticipantGroupType& group) = 0;

    /**
     * @brief Whether or not terminate recommending calculation
     *
     * @return holo::bool_t True, need terminating; false, execute
     *                      next Expector calcuation
     */
    virtual holo::bool_t Terminate() = 0;

public:
    friend class EvaluatorManager;

protected:
    /// Scene sketch
    SceneSketchSPtrType scene_sketch_;
    /// Index absolutely
    std::size_t index_absolute_ = 0U;
    /// Index in same expect type
    std::size_t index_homogeneous_ = 0U;
    /// Maximum lane path expected distance
    holo::float64_t max_expected_distance_ = 1500.0f;
};

class CompositeEvaluatorBase : public EvaluatorBase
{
public:
private:
    std::deque<EvaluatorSPtrType> evaluators_;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_EVALUATION_EVALUATOR_BASE_H_ */