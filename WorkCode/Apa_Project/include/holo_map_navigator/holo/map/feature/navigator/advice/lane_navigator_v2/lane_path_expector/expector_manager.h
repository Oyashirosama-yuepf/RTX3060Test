/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_path_expector.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2021-11-27
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_EXPECTOR_EXPECTOR_MANAGER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_EXPECTOR_EXPECTOR_MANAGER_H_

#include <vector>

#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_expector/expector_base.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/participant_group.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class ExpectorManager
{
public:
    using ExpectorSPtrType     = std::shared_ptr<holo::map::navigator::advice::ExpectorBase>;
    using ParticipantGroupType = holo::map::navigator::advice::ParticipantGroup;
    using SceneSketchType      = scene::SceneSketch;
    using SceneSketchSPtrType  = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType  = std::vector<SceneSketchSPtrType>;

public:
    ExpectorManager() = default;
    ~ExpectorManager() = default;

public:
    holo::bool_t Reset(SceneSketchSPtrVecType const& scene_sketchs);
    holo::bool_t Expect(ParticipantGroupType& group);

private:
    void clear();
    holo::bool_t add(ExpectorSPtrType expector);

private:
    std::vector<ExpectorSPtrType> expectors_;
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_EXPECTOR_EXPECTOR_MANAGER_H_ */