/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_split_grading.h
 * @brief update lane path attributes
 * @author zhegnshulei (zhegnshulei@holomatic.com)
 * @date 2022-4-29
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_GRADING_ROAD_MERGE_GRADING_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_GRADING_ROAD_MERGE_GRADING_H_

#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/lane_path_grading/grading_base.h>

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

class RoadMergeGrading : public GradingBase
{
public:
    RoadMergeGrading() = default;
    virtual ~RoadMergeGrading() = default;

public:
    /**
     * @brief Update all lane path attribute, include level, candidate lane id, etc. 
     *
     * @param all_lane_paths all lane paths need update attribute
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t UpdateAllLanePath(LanePathSPtrVecType& all_lane_paths) override;

};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_PATH_GRADING_ROAD_MERGE_GRADING_H_ */