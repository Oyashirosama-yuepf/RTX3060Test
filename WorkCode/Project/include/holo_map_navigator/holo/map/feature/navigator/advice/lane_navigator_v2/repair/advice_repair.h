/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file advice_repair.h
 * @brief Repair advice for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-31
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REPAIR_ADVICE_REPAIROR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REPAIR_ADVICE_REPAIROR_H_

#include <holo/map/adaptation/data_engine/data_engine.h>
#include <holo/map/feature/navigator/advice/advice.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/repair/repairor.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/repair/lane_path_repair.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
using LanePathType        = holo::map::navigator::advice::LanePath;
using LanePathSPtrType    = std::shared_ptr<holo::map::navigator::advice::LanePath>;
using LanePathSPtrVecType = std::vector<LanePathSPtrType>;

using RelatedEndPointType = LanePath::RelateEndpointType;
using LaneItemSPtrType    = std::shared_ptr<holo::map::navigator::advice::LaneItem>;
using LaneItemSPtrVecType = std::vector<LaneItemSPtrType>;

static holo::bool_t FindLanePathByIdExcept(LanePathSPtrVecType paths, IdType const find_id, holo::bool_t& has,
                                           LanePathSPtrType& find_path)
{
    has = false;
    for (LanePathSPtrType path : paths)
    {
        if(nullptr == path)
        {
            LOG(ERROR) << "FindLanePathByIdExcept fails, invalid path";
            return false;
        }
        if(path->GetId() == find_id)
        {
            has = true;
            find_path = path;
        }
    }
    return true;
}

template <>
holo::bool_t Repairor::Repair<Advice2>(Advice2& advice)
{
    LanePathSPtrVecType& lane_paths      = advice.GetLanePaths();
    std::size_t const    size_lane_paths = lane_paths.size();
    IdType               max_path_id     = 0;
    for (std::size_t i = 0U; i < size_lane_paths; ++i)
    {
        LanePathSPtrType new_path = std::make_shared<LanePath>(*lane_paths[i]);
        if(nullptr == new_path)
        {
            LOG(ERROR) << "Advisor2::runRepairing fails, Repairor::Repair fails, index=" << i;
            return false;
        }
        if (!Repairor::Repair(*new_path))
        {
            LOG(ERROR) << "Advisor2::runRepairing fails, Repairor::Repair fails, index=" << i;
            return false;
        }
        lane_paths[i] = new_path;
        if (max_path_id < lane_paths[i]->GetId())
        {
            max_path_id = lane_paths[i]->GetId();
        }
    }
    for (LanePathSPtrType path : lane_paths)
    {
        if (false && path->GetRelateEndpoint().is_relate_lane_path_id)
        {
            holo::bool_t has_find = false;
            LanePathSPtrType find_path = nullptr;
            if (!FindLanePathByIdExcept(lane_paths, path->GetRelateEndpoint().relate_lane_path_id, has_find, find_path))
            {
                LOG(ERROR) << "Repairor::Repair fails, FindLanePathByIdExcept fails, find_id="
                           << path->GetRelateEndpoint().relate_lane_path_id;
                return false;
            }
            if (has_find)
            {
                find_path->SetId(++max_path_id);
            }
            path->SetId(path->GetRelateEndpoint().relate_lane_path_id);
        }
    }

    return true;
}

template <>
holo::bool_t Repairor::Repair<std::vector<LanePathSPtrType>, Advice2>(
    std::vector<LanePathSPtrType> const& history_paths, Advice2& advice)
{
    if (!Repairor::Repair(advice))
    {
        LOG(ERROR) << "Repairor::Repair fails, LanePath::TrackAllPaths fails";
        return false;
    }

    for (LanePathSPtrType p : advice.GetLanePaths())
    {
        if (!p->ClearHistoryTrace())
        {
            LOG(ERROR) << "Repairor::Repair fails, ClearHistoryTrace fails, invaid";
            return false;
        }
    }

    std::map<std::size_t, std::size_t> lookup;
    if (!LanePath::TrackAllPaths(history_paths, advice.GetLanePaths(), lookup))
    {
        LOG(ERROR) << "Repairor::Repair fails, LanePath::TrackAllPaths fails";
        return false;
    }
    std::vector<IdType> expected_path_ids;
    for (IdType id : advice.GetExpectedLanePaths())
    {
        auto iter = lookup.find(id);
        if (iter != lookup.end())
        {
            expected_path_ids.push_back(iter->second);
        }
        else
        {
            expected_path_ids.push_back(id);
        }
    }
    advice.GetExpectedLanePaths().clear();
    advice.GetExpectedLanePaths().insert(advice.GetExpectedLanePaths().end(), expected_path_ids.begin(),
                                         expected_path_ids.end());
    return true;
}

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REPAIR_ADVICE_REPAIROR_H_ */