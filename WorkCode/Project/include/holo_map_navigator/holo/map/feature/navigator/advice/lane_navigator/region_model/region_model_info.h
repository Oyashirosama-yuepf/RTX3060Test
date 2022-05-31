/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file region_model_info.h
 * @brief Region model info
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-10-08"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_REGION_MODEL_INFO_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_REGION_MODEL_INFO_H_

#include <sstream>
#include <vector>
#include <memory>

#include <holo/core/types.h>

#include <holo/map/feature/navigator/advice/lane_navigator/target_region.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class LanePath;
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

class RegionModelInfo
{
public:
    using RegionModelInfoSPtrType = std::shared_ptr<RegionModelInfo>;
    using RegionModelInfoSPtrVecType = std::vector<RegionModelInfoSPtrType>;
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
    enum ModelType : holo::uint8_t
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
    static std::string FormatToString(RegionModelInfo const& info);

    /**
     * @brief Format to JSON String
     *
     * @param advice A vector of RegionModelInfo
     * @return std::string JOSN string
     */
    static std::string FormatToString(RegionModelInfoSPtrVecType const& infos);

    /**
     * @brief Shrink region model infos
     * 
     * @param regions 
     * @return holo::bool_t 
     */
    static holo::bool_t Shrink(std::vector<RegionModelInfoSPtrType>& regions);

public:
    RegionModelInfo()                       = default;
    RegionModelInfo(RegionModelInfo const&) = default;
    RegionModelInfo(RegionModelInfo&&)      = default;
    RegionModelInfo& operator=(RegionModelInfo const&) = default;
    RegionModelInfo& operator=(RegionModelInfo&&) = default;
    ~RegionModelInfo()                            = default;

    /**
     * @brief Set the Id
     *
     * @param id Unique id
     */
    void SetId(holo::uint64_t const id);

    /**
     * @brief Get the Id
     *
     * @return Unique Id
     */
    holo::uint64_t GetId() const;

    /**
     * @brief Set the Model Type object
     *
     * @param type Model type for changing, spliting and merging
     */
    void SetModelType(ModelType type);

    /**
     * @brief Get the Model Type
     *
     * @return ModelType  Model type for changing, spliting and merging
     */
    ModelType GetModelType() const;

    /**
     * @brief Set the Ready Point
     *
     * @param dist The distance; Unit: meter
     */
    void SetReadyPoint(holo::float64_t const dist);

    /**
     * @brief Get the Ready Point
     *
     * @return The Distance; Unit: meter
     */
    holo::float64_t GetReadyPoint() const;

    /**
     * @brief Set the Risk Point
     *
     * @param dist The Distance; Unit: meter
     */
    void SetRiskPoint(holo::float64_t const dist);

    /**
     * @brief Get the Risk Point
     *
     * @return The Distance; Unit: meter
     */
    holo::float64_t GetRiskPoint() const;

    /**
     * @brief Set the Ultimate Point
     *
     * @param dist The Distance; Unit: meter
     */
    void SetUltimatePoint(holo::float64_t const dist);

    /**
     * @brief Get the Ultimate Point
     *
     * @return The Distance; Unit: meter
     */
    holo::float64_t GetUltimatePoint() const;

    /**
     * @brief Set the Join Path Id
     *
     * @param id Joined path id
     */
    void SetJoinPathId(holo::uint64_t const id);

    /**
     * @brief Get the Join Path Id
     *
     * @return Joined path id
     */
    holo::uint64_t GetJoinPathId() const;

    /**
     * @brief Set the Join Region Id
     *
     * @param id Joined region id
     */
    void SetJoinRegionId(holo::uint64_t const id);

    /**
     * @brief Get the Join Region Id
     *
     * @return Joined Region id
     */
    holo::uint64_t GetJoinRegionId() const;

    /**
     * @brief Set the Host Lane Path 
     * 
     * @param ptr 
     */
    void SetHostLanePath(std::shared_ptr<LanePath> ptr);

    /**
     * @brief Get the Host Lane Path
     * 
     * @return std::shared_ptr<LanePath> 
     */
    std::shared_ptr<LanePath> GetHostLanePath() const;

    /**
     * @brief Set the Region Indexs
     * 
     * @param idxs 
     */
    void SetRegionIndexs(std::vector<std::size_t> const& idxs);

    /**
     * @brief Get the Region Indexs
     * 
     * @return std::vector<std::size_t> const& 
     */
    std::vector<std::size_t> const& GetRegionIndexs() const;

    /**
     * @brief Set the Lane Begin Offset
     * 
     * @param offset 
     */
    void SetLaneBeginOffset(holo::float64_t offset);

    /**
     * @brief Get the Lane Begin Offset
     * 
     * @return holo::float64_t 
     */
    holo::float64_t GetLaneBeginOffset() const;

    /**
     * @brief Set the Lane Finished Offset
     * 
     * @param offset 
     */
    void SetLaneFinishOffset(holo::float64_t offset);

    /**
     * @brief Get the Lane Finish Offset
     * 
     * @return holo::float64_t 
     */
    holo::float64_t GetLaneFinishOffset() const;

    /**
     * @brief Create a Target Region
     * 
     * @return holo::bool_t 
     */
    holo::bool_t CreateTargetRegion(TargetRegion& target_region, holo::bool_t& has_target) const;

    /**
     * @brief Get the Matched Lane Ids
     * 
     * @return std::vector<holo::uint64_t> 
     */
    std::vector<holo::uint64_t> const GetMatchedLaneIds();

private:   
    /**
     * @brief Create a Target Region From Split Model
     *
     * @return holo::bool_t
     */
    holo::bool_t createTargetRegionFromSplitModel(holo::bool_t const transition_right, TargetRegion& target,
                                                  holo::bool_t& has_targe) const;

    /**
     * @brief Create a Target Region From Change Model 
     * 
     * @return holo::bool_t 
     */
    holo::bool_t createTargetRegionFromChangeModel(holo::bool_t const transition_right, TargetRegion& target,
                                                   holo::bool_t& has_targe) const;

    /**
     * @brief Create a Target Region From Merge Model 
     * 
     * @return holo::bool_t 
     */
    holo::bool_t createTargetRegionFromMergeModel(holo::bool_t const transition_right, TargetRegion& target,
                                                  holo::bool_t& has_targe) const;

public:
    /// The unique id for region model info
    holo::uint64_t id_ = std::numeric_limits<holo::uint64_t>::max();
    /// Region model info, which describe procedure
    ModelType model_type_ = ModelType::LANE_KEEP;
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
    ///  Another region model info, which you would refer to
    holo::uint64_t join_region_id_ = 0U;
    ///
    std::shared_ptr<LanePath> lane_path_;
    /// Score that the lane path should be prefered
    holo::float32_t score_ = 0.0f;
    /// A section of lane path covered by lanes, we record
    /// the index of the lane in lane path
    std::vector<holo::uint64_t> region_indexs_;
    /// The offset of first lane 
    ///      |  ----- lane1 ----- | -- lane2 --| ------ lane3 -------- | -- lane4 -- | --
    ///                   | --- Region Model Info  --- | 
    ///      [begin offset]                            [ finish offset ]
    holo::float64_t             lane_begin_offset_  = 0.0f;
    /// The offset of last lane, more details seen above
    holo::float64_t             lane_finish_offset_ = 0.0f;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_REGION_MODEL_INFO_H_ */
