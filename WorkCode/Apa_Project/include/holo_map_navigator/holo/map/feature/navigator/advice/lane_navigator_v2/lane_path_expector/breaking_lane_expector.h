/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file breaking_lane_expector.h
 * @brief Expected is used to recommend lane paths going through certain link
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-02-24
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_EXPECTOR_BREAKING_LANE_EXPECTOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_EXPECTOR_BREAKING_LANE_EXPECTOR_H_

#include <vector>

#include <holo/map/common/common_define.h>
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
class BreakingLaneExpector : public ExpectorBase
{
public:
    BreakingLaneExpector(SceneSketchSPtrType scene_sketch);
    virtual ~BreakingLaneExpector() =  default;

    /**
     * @brief Initialize function
     * 
     * @return holo::bool_t 
     */
    virtual holo::bool_t Init() override;

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
    virtual holo::bool_t Recommend(ParticipantGroupType& group) override;

    /**
     * @brief Whether or not terminate recommending calculation
     *
     * @return holo::bool_t True, need terminating; false, execute
     *                      next Expector calcuation
     */
    virtual holo::bool_t Terminate() override;
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_EXPECTOR_BREAKING_LANE_EXPECTOR_H_ */