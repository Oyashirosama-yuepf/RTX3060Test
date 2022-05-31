/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file no_succeed_terminator.h
 * @brief Terminator based on searching distance is used to stop extending of lane path
 * @author chanqiliang (chanqiliang@holomatic.com)
 * @date 2022-3-24
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_NO_SUCCEED_TERMINATOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_NO_SUCCEED_TERMINATOR_H_
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
class NoSucceedTerminator : public TerminatorBase
{
public:
    NoSucceedTerminator()          = default;
    virtual ~NoSucceedTerminator() = default;

    // remove copy assignment(we don't need copy a specific NoSucceedTerminator)
    NoSucceedTerminator(NoSucceedTerminator const&) = delete;
    NoSucceedTerminator(NoSucceedTerminator&&)      = delete;
    // remove operator =
    NoSucceedTerminator& operator=(NoSucceedTerminator const&) = delete;
    NoSucceedTerminator& operator=(NoSucceedTerminator&&) = delete;

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
    /**
     * @brief Check whether or not get  map dates given by ids
     *
     * @param ret map data handle
     * @param lane_ids all lane ids
     * @param is_cached  is cached
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t IsMapCached(RetrieverSPType ret, std::vector<IdType> const& lane_ids, bool& is_cached);
};
}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_NO_SUCCEED_TERMINATOR_H_