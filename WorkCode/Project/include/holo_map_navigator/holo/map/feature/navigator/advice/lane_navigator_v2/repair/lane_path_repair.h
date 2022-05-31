/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_path_repairor.h
 * @brief Repairing lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REPAIR_LANE_PATH_REPAIROR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REPAIR_LANE_PATH_REPAIROR_H_

#include <holo/map/feature/navigator/advice/lane_navigator_v2/repair/repairor.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/adaptation/data_engine/data_engine.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
using RelatedEndPointType = LanePath::RelateEndpointType;
using LaneItemSPtrType    = std::shared_ptr<holo::map::navigator::advice::LaneItem>;
using LaneItemSPtrVecType    = std::vector<LaneItemSPtrType>;

template <>
holo::bool_t Repairor::Repair<LanePath>(LanePath& path)
{
    RelatedEndPointType const& mount = path.GetRelateEndpoint();
    if (mount.is_valid)
    {
        LaneItemSPtrVecType valid_lane_items;
        std::size_t const   size_items = path.Size();
        for (std::size_t i = 0U; i < size_items; ++i)
        {
            LaneItemSPtrType item = path[i];
            if (nullptr == item)
            {
                LOG(ERROR) << "Repairor::Repair fails, invalid items, index=" << i;
                return false;
            }
            valid_lane_items.push_back(item);
            if (item->GetLaneId() == mount.from_lane_id)
            {
                break;
            }
        }
        for (IdType lane_id : mount.to_lane_ids)
        {
            LaneItemSPtrType new_item = nullptr;
            if (!LaneItem::CreateItem(adaptation::DataEngine::Instance()->GetRetriver(), lane_id, new_item))
            {
                LOG(ERROR) << "Repairor::Repair fails, CreateItem invalid items, lane_id=" << lane_id;
                return false;
            }
            new_item->SetIsPredicted(true);
            valid_lane_items.push_back(new_item);
        }
        path.Clear();
        for (LaneItemSPtrType item : valid_lane_items)
        {
            path.PushBack(item);
        }
    }
    return true;
}

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REPAIR_LANE_PATH_REPAIROR_H_ */