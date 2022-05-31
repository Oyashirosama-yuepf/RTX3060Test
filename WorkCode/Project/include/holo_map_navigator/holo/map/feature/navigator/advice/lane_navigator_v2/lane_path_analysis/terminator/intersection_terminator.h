/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intersection_terminator.h
 * @brief Terminator based on searching distance is used to stop extending of lane path
 * @author chanqiliang (chanqiliang@holomatic.com)
 * @date 2022-3-25
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_INTERSECTION_TERMINATOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_INTERSECTION_TERMINATOR_H_
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/terminator/terminator_base.h>

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
class IntersectionTerminator : public TerminatorBase
{
public:
    IntersectionTerminator()          = default;
    virtual ~IntersectionTerminator() = default;

    // remove copy assignment(we don't need copy a specific IntersectionTerminator)
    IntersectionTerminator(IntersectionTerminator const&) = delete;
    IntersectionTerminator(IntersectionTerminator&&)      = delete;
    // remove operator =
    IntersectionTerminator& operator=(IntersectionTerminator const&) = delete;
    IntersectionTerminator& operator=(IntersectionTerminator&&) = delete;

public:
    /**
     * @brief Whethor or not the terminator take effect
     *
     * @return holo::bool_t True, take effect; false, no effect
     */
    virtual holo::bool_t Enable() override;

    /**
     * @brief Compared with another terminator
     *
     * @param terminator Another terminator
     * @return holo::bool_t True, take priority over another; false, not prior, may equally
     */
    virtual holo::bool_t HavePriorityOver(TerminatorSPtrType terminator) override;

    /**
     * @brief Get the Category
     *
     * @return TerminatorCategory
     */
    virtual TerminatorCategory GetCategory() override;


protected:
    /**
     * @brief Check the whether or not the target should be stop to extend
     *
     * @param targets Targets that should be checked
     * @return holo::bool_t True, succeed; false, otherwise
     */
    virtual holo::bool_t doCheck(TerminatorTarget& target) override;

private:
    holo::bool_t match(LaneItemSPtrType const& lane_item_to_match, holo::bool_t& in_scope,
                       SceneSketchSPtrType& match_scene);

private:
    holo::float64_t    distance_to_first_intersection_ = 0.0;
};
}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_INTERSECTION_TERMINATOR_H_