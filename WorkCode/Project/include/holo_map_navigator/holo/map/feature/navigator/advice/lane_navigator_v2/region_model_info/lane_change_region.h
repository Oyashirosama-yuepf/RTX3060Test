/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_change_region.h
 * @brief Region model info
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-10-08"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_LANE_CHANGE_REGION_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_LANE_CHANGE_REGION_H_

#include <sstream>
#include <vector>
#include <memory>
#include <limits>

#include <holo/core/types.h>
#include <holo/map/common/common_define.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
/**
 * @brief Guide procedure for changing, merging or spliting
 *
 * @details The procedure would describe where to change lane and change to
 *          which lane path. And the ready point, risk point and ultimate
 *          point are refered to the start of lane path rather than the
 *          current positioning point;
 *
 *         |--- lane item1 ---|---lane item2 ---|---lane item3 ---|---lane item4 ---|---lane item5 ---|
 *
 *                *(Odometry)     |----------------    RegionModelInfo    -----------------|
 *                                *                       *                                *
 *         |----------------------|(ready point)
 *         |----------------------------------------------|(risk point)
 *         |-------------------------------------------------------------------------------|(ultimat point)
 */

class LaneChangeRegion
{
public:
    using LaneChangeRegionSPtrType   = std::shared_ptr<LaneChangeRegion>;
    using LaneChangeRegionSPtrVecType = std::vector<LaneChangeRegionSPtrType>;
    /**
     * @brief Description for changing, merging or spliting
     *
     * @details The model type of CHANGE_* would be explained as followed:
     *          -----------------------------------------------------------
     *           |   [P]      (region 1)                    |
     *          -----------------------------------------------------------
     *           |            (region 2)              [T]   |
     *          -----------------------------------------------------------
     *          The car[P] drives from (region 1) to [T] in (region 2),
     *          The region 1(Region model info) is CHANGE_TO_RIGHT; the
     *          region 2(defined as target region) is CHANGE_FROM_LEFT
     *
     *          The model type of SPLIT_* would be explained as followed:
     *          -----------------------------------------------------------
     *           |            (region 1)             |       (region 3)
     *          -----------------------------------------------------------
     *           |            (region 2)             | [P]   (region 4)
     *          ------------------------------------------------------------
     *                                                 \     (region 5) [T]
     *                                                  \_ _ _ _ _ _ _ _ _ _
     *          The car[P] drives from (region 4) to [T] in (region 5)
     *          The region 4(region model info) is SPLIT_TO_RIGHT; and
     *          region 5(target region) is SPLIT_FROM_LEFT
     *
     *          The model type of MERGE_* would be explained as followed:
     *          ----------------------------------------------------------
     *                 (region 1)        |
     *          ----------------------------------------------------------
     *                 (region 2) [T]    |
     *          ----------------------------------------------------------
     *             [P] (region 3)       /
     *          -----------------------/
     *          The car[P] drives from (region 3) to [T] in (region 2)
     *          The region 2(region model info) would be MERGE_FROM_RIGHT;
     *          and region 3(target region) would be MERGE_TO_LEFT
     *
     */
    enum LaneChangeMode : holo::uint8_t
    {
        LANE_KEEP,         ///> Keep driving along current lane
        CHANGE_TO_RIGHT,   ///> Change to right lane
        CHANGE_TO_LEFT,    ///> Change to left lane
        MERGE_TO_RIGHT,    ///> Merge to right lane
        MERGE_TO_LEFT,     ///> Merge to left lane
        SPLIT_TO_RIGHT,    ///> Split to right lane
        SPLIT_TO_LEFT,     ///> Split to left lane
        CHANGE_FROM
    };

public:
    /**
     * @brief Format RegionModelInfo to JSON string
     *
     * @param info RegionModelInfo
     * @return std::string
     */
    static std::string FormatToString(LaneChangeRegion const& info);

    /**
     * @brief Format to JSON String
     *
     * @param advice A vector of RegionModelInfo
     * @return std::string JOSN string
     */
    static std::string FormatToString(LaneChangeRegionSPtrVecType const& infos);

    /**
     * @brief Shrink region model infos
     * 
     * @param regions 
     * @return holo::bool_t 
     */
    static holo::bool_t Shrink(std::vector<LaneChangeRegionSPtrType>& regions);

public:
    LaneChangeRegion()                      = default;
    LaneChangeRegion(LaneChangeRegion const&) = default;
    LaneChangeRegion(LaneChangeRegion&&)      = default;
    LaneChangeRegion& operator=(LaneChangeRegion const&) = default;
    LaneChangeRegion& operator=(LaneChangeRegion&&) = default;
    ~LaneChangeRegion()                             = default;

    void SetId(holo::uint64_t const id);
    holo::uint64_t GetId() const;

    void SetLaneChangeMode(LaneChangeMode const mode);
    LaneChangeMode GetLaneChangeMode() const;

    void SetReadyPoint(holo::float64_t const d);
    holo::float64_t GetReadyPoint() const;

    void SetRiskPoint(holo::float64_t const d);
    holo::float64_t GetRiskPoint() const;

    void SetUltimatePoint(holo::float64_t const d);
    holo::float64_t GetUltimatePoint() const;

    void SetJointPathId(IdType const id);
    IdType GetJointPathId() const;

    void SetReadyDistanceToBaseline(holo::float64_t const d);
    holo::float64_t GetReadyDistanceToBaseline() const;

    void            SetRiskDistanceToBaseline(holo::float64_t const d);
    holo::float64_t GetRiskDistanceToBaseline() const;

    void            SetUltimateDistanceToBaseline(holo::float64_t const d);
    holo::float64_t GetUltimateDistanceToBaseline() const;

    std::vector<IdType>& GetRelatedLaneIds();

    holo::bool_t Track(LaneChangeRegion const& other);

    holo::bool_t Update(LaneChangeRegion const& other);

private:
    void updateDistanceToBaseline();

private:
    /// The unique id for region model info
    holo::uint64_t id_ = std::numeric_limits<holo::uint64_t>::max();
    /// Region model info, which describe procedure
    LaneChangeMode lane_change_mode_ = LaneChangeMode::LANE_KEEP;
    /// One point where you can execute procedure, the point
    /// would be represented as distance to start of lane path.
    /// Unit: meter
    holo::float32_t ready_point_ = 0.0;
    /// One point where you should finish executing procedure; the
    /// point would be represented as distance to start of lane path.
    /// Unit: meter
    holo::float32_t risk_point_ = 0.0;
    /// One point where you should consider another lane-level guide route;
    /// the point would be represented as distance to start of lane path.
    /// Unit: meter
    holo::float32_t ultimate_point_ = 0.0;
    ///  Another lane path, which you would refer to
    holo::uint64_t join_path_id_ = 0U;
    ///
    holo::float64_t ready_distance_to_baseline_ = 0;
    holo::float64_t risk_distance_to_baseline_ = 0;
    holo::float64_t ultimate_distance_to_baseline_ = 0;
    /// Related lane ids
    std::vector<IdType> related_lane_ids_;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_REGION_MODEL_INFO_H_ */
