/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file unique_succeed_generator.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_ITEM_UNIQUE_SUCCEED_GENERATOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_ITEM_UNIQUE_SUCCEED_GENERATOR_H_

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/lane_item_generator/lane_item_generator_base.h>

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
class LaneItemUniqueSucceedGenerator : public LaneItemGeneratorBase
{
public:
    /**
     * @brief Generate Lane Item from one to another
     *
     * @details The 'to' item may be successive to 'from' or is not.
     *          They may be has the relation as followed:
     *
     *          Case 1: Just Succeessive to another item
     *                  Item1 -> Item2
     *                   (to)     (from)
     *
     *          Case 2: Multi-item exists,
     *                   Item1 -> Item2 -> Item3 -> Item4 -> Item5
     *                   (to)                              (from)
     *
     * @param from The start item to generate
     * @param to The end item that has been generated
     * @return holo::bool_t True, exists; false, not exists
     */
    virtual holo::bool_t Generate(Seed const& seed, NewBornVecType& newborns) override;

    /**
     * @brief Whether or not the Generator is exclusive
     *
     * @return holo::bool_t True, no other Generators need to be executed;
     *                      False, need to execute other Generators
     */
    virtual holo::bool_t Exclusive() override;

    /**
     * @brief Whether or not priority other generater
     *
     * @param other Another generator
     * @return holo::bool_t True, prior to another; false, no priority
     */
    virtual holo::bool_t Priority(GeneratorSPtrType other) override;

    /**
     * @brief Get the Mode 
     * 
     * @return GeneratorMode 
     */
    virtual GeneratorMode GetMode() const override;
};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_ITEM_UNIQUE_SUCCEED_GENERATOR_H_ */