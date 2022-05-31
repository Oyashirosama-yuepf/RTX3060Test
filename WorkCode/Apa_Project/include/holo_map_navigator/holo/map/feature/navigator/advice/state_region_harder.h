/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file state_region_hard.h
 * @brief Hard code state region for lane navigation
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-12-08"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_STATE_REGION_HARDER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_STATE_REGION_HARDER_H_

#include <memory>

#include <holo/common/road_type.h>
#include <holo/core/types.h>

#include <holo/map/common/common_define.h>

#include <holo/map/feature/navigator/advice/lane_navigator/target_region.h>
#include <holo/map/format/base/lane_group.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/state_region_info/state_region.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class StateRegionHarder
{
public:
    using StateRegionType = holo::map::navigator::advice::StateRegion;
    using LanePathSPtrType = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType = std::vector<LanePathSPtrType>;

    enum class Model : holo::uint8_t
    {
        UNDEFINED = 0U,
        SPLIT = 1U,
        MERGE = 2  
    };

    struct Word 
    {
        Word(Model const& m, std::vector<IdType> const& ids)
        {
            this->model = m;
            this->lane_ids.insert(this->lane_ids.end(), ids.begin(), ids.end());
        }
        Model model = Model::UNDEFINED;
        std::vector<IdType> lane_ids;
    };

    using Dict = std::vector<Word>;

public:
    StateRegionHarder();

    holo::bool_t Calculate(LanePathSPtrVecType& paths);
    
private:
    holo::bool_t calcualteLanePathStateRegion(LanePathSPtrType path);

private:
    Dict dict_;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_STATE_REGION_H_ */
