/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_checker.h
 * @brief Checker about lane's topology/xingtai/
 * @author zhengshulei(zhengshulei@holomatic.com)
 * @date 2022-4-1
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_LANE_CHECKER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_LANE_CHECKER_H_

#include <holo/map/feature/navigator/advice/lane_navigator_v2/map_types.h>

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
class LaneChecker
{
public:
    LaneChecker();
    ~LaneChecker();

    holo::bool_t InitByLaneId(RawFeatureIdTypeV0 const& lane_id);
    holo::bool_t InitBySPtrLane(RawLaneSPtrTypeV0 ptr_lane);
    holo::bool_t InitByLane(RawLaneTypeV0 const lane);

    holo::bool_t IsInitialized();

public:
    holo::bool_t IsNormal(holo::bool_t& is);
    holo::bool_t IsRestricted(holo::bool_t& is);
    holo::bool_t IsStepWide(holo::bool_t& is);
    holo::bool_t IsStepNarraw(holo::bool_t& is);
    holo::bool_t IsOpening(holo::bool_t& is);
    holo::bool_t IsClosing(holo::bool_t& is);
    holo::bool_t IsSpliting(holo::bool_t& is);
    holo::bool_t IsMerging(holo::bool_t& is);
    holo::bool_t IsLeftCanPassed(holo::bool_t& is);
    holo::bool_t IsRightCanPassed(holo::bool_t& is);

public:
    holo::bool_t GetLane(RawLaneTypeV0&);

    holo::bool_t GetAllPrecedingIds(holo::bool_t& ok, RawFeatureIdVectorTypeV0& preceding_lanes);
    holo::bool_t GetAllSuccedingIds(holo::bool_t& ok, RawFeatureIdVectorTypeV0& succeding_lanes);

    holo::bool_t GetAllPreceding(holo::bool_t& ok, RawLaneSPtrVectorTypeV0& preceding_lanes);
    holo::bool_t GetAllSucceding(holo::bool_t& ok, RawLaneSPtrVectorTypeV0& succeding_lanes);

    holo::bool_t GetNormalConnectPreceding(holo::bool_t& ok, RawLaneSPtrTypeV0& preceding_lane);
    holo::bool_t GetNormalConnectSucceding(holo::bool_t& ok, RawLaneSPtrTypeV0& succeding_lane);

    holo::bool_t GetLeftSibling(holo::bool_t& ok, RawLaneSPtrTypeV0& left_lane);
    holo::bool_t GetRightSibling(holo::bool_t& ok, RawLaneSPtrTypeV0& right_lane);

private:
    holo::bool_t initRetriver();
    
private:
    RawRetrieverSPtrType retriever_ = nullptr;
    RawLaneTypeV0 lane_;
    holo::bool_t initialized_ = false;

};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_CONSTRAINT_LANE_CHECKER_H_ */