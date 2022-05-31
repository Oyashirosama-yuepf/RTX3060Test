/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_path_combination_origin.h
 * @brief Generate lane path for lane-level navigation base on given generator,constraint and terminator
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_GENERATOR_DEFAULT_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_GENERATOR_DEFAULT_H_

#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/lane_path_generator/lane_path_generator_base.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
namespace lanepath
{

class LanePathGeneratorDefault : public LanePathGeneratorBase
{
public:
    using LanePathSPtrType             = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType          = std::vector<LanePathSPtrType>;
    using LaneItemSPtrType             = std::shared_ptr<LaneItem>;
    using LaneItemSPtrVecType          = std::vector<LaneItemSPtrType>;
    using GeneratorSPtrType            = std::shared_ptr<holo::map::navigator::advice::lanepath::LaneItemGeneratorBase>;
    using SceneSketchType              = holo::map::navigator::advice::scene::SceneSketch;
    using CompositeSceneSketchType     = holo::map::navigator::advice::scene::CompositeSceneSketch;
    using SceneSketchSPtrType          = std::shared_ptr<SceneSketchType>;
    using CompositeSceneSketchSPtrType = std::shared_ptr<CompositeSceneSketchType>;
    using SceneSketchSPtrVecType       = std::vector<SceneSketchSPtrType>;
    using GeneratorModeType            = LaneItemGeneratorBase::GeneratorMode;

public:
    LanePathGeneratorDefault() = default;
    ~LanePathGeneratorDefault() = default;
    
    /**
     * @brief Construct constraints and terminators by scene
     */
    virtual holo::bool_t UpdateScenes(std::vector<SceneSketchSPtrType> const& scenes) override;

    /**
     * @brief Get the Mode
     *
     * @return Lane path generator mode
     */
    virtual LanePathGeneratorMode GetMode() const override;

    /**
     * @brief Check if this lane path generator is enable
     */
    virtual holo::bool_t IsEnable(LanePathGeneratorBase::Input const& input) override;

protected:
    virtual holo::bool_t DoInit() override;
};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_GENERATOR_DEFAULT_H_ */