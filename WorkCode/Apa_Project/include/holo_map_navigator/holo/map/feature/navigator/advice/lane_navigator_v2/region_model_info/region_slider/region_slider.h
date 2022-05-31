/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file region_slider.h
 * @brief A sliding block for lane path to generate region model info
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-03-31
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_SLIDER_REGION_SLIDER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_SLIDER_REGION_SLIDER_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
/**
 * @brief Region slider of lane path
 * 
 * @details The region slider is as 'slider' to slide on two
 *          related lane path
 *          When sliding, it would calculate and update, so 
 *          generate the final RegionModelInfo
 * 
 */
class RegionSliderBase
{
public:
    using LanePathSPtrType       = std::shared_ptr<holo::map::navigator::advice::LanePath>;
    using LanePathSPtrVecType    = std::vector<LanePathSPtrType>;

    /**
     * @brief Adjoint status of two different lane paths
     *
     */
    enum class AdjointStatus : holo::uint8_t
    {
        UNDEFINED = 0,
        /// Origin LanePath is on the left of target,
        /// they are NEXT to each other
        ORIGIN_ON_LEFT_TO_TARGET,
        /// Origin LanePath is on the right of target,
        /// they are NEXT To each other
        ORIGIN_ON_RIGHT_TO_TARGET,
        /// Origin LanePath is on the left side of target,
        /// they may NOT be NEXT to each other
        ORIGIN_TO_LEFT_SIDE_OF_TARGET,
        /// Origin LanePath is on the right side of target,
        /// they may not be neighbor to each other
        ORIGIN_TO_RIGHT_SIDE_OF_TARGET,
        /// No adjoint
        NO_ADJOINT
    };
    /**
     * @brief Reason of terminating of slider
     * 
     */
    enum class SliderStatus : holo::uint8_t
    {
        UNDEFINED = 0,
        COMPLETED,                                 ///> All have been calculated
        LANE_PATH_NOT_ENOUGH,                      ///> The LanePath is too short to slide
        NEED_SLIDING,                              ///> We need execute sliding
        BOUNDARY_NOT_MATCHED,                      ///> The boundary of origin and target LanePath not mached
        BOUNDARY_NOT_MATCHED_AND_PATH_NOT_ENOUTH,  ///> Boudnary not matched and path not enough
        SEARCH_JOINT_OUT_DISTANCE,                 ///> Execute spliting and merging and out search distance
        REGION_LENGTH_OUT_MAX_LENGTH,               ///> Region length is larger certain max length
        LANE_NARROW_AND_JOINT_NOT_FIND             ///> Lane narrowing and can not find joint
    };

    using SlidingTerminatedMode = SliderStatus;

    enum class SlidingStatus : holo::uint8_t
    {
        UNDEFINED = 0U,
        JOINT_ITEM_NOT_FIND,
        JOINT_ITEM_FIND_VANISHED_ITEM_FIND,
        JOINT_ITEM_FIND_VANISHED_ITEM_NOT_FIND
    };

    /**
     * @brief Check whether or not the lane is left next to another
     *
     * @param left_id Left lane id
     * @param right_id Right lane id
     * @param yes True, is; false, not is
     * @return holo::bool_t True, succeed; false, otherwise
     */
    static holo::bool_t IsLaneLeftToLane(IdType const left_id, IdType const right_id, holo::bool_t& yes);

    /**
     * @brief Check whether or not the lane is on left side of another lane
     * 
     * @note The two lane may not have common bondary with each other 
     *
     * @param left_id Left lane id
     * @param right_id Right lane id
     * @param yes True, is; false, not is
     * @return holo::bool_t True, succeed; false, otherwise
     */
    static holo::bool_t IsLaneOnLeftSideOfLane(IdType const left_id, IdType const right_id, holo::bool_t& yes);

    RegionSliderBase()                        = default;
    RegionSliderBase(RegionSliderBase const&) = default;
    RegionSliderBase(RegionSliderBase&&)      = default;
    RegionSliderBase& operator=(RegionSliderBase const&) = default;
    RegionSliderBase& operator=(RegionSliderBase&&) = default;

    virtual ~RegionSliderBase() = default;

    holo::bool_t Load(LanePathSPtrType source, LanePathSPtrType target);

    /**
     * @brief Reset the inner attributes
     * 
     * @details After calculation of Region Model Info of two related 
     *          lane paths, we need to load another pair of paths.
     *          So need to reset the inner attributes
     * 
     */
    void Reset();

    /**
     * @brief Whether or not need to slide
     *
     * @return holo::bool_t True, need sliding; false, not to slide
     */
    holo::bool_t CheckNeedSliding();

    /**
     * @brief Slide lane in lane path
     *
     * @details
     *          lane path: lane item1 -> lane item2 -> lane item3 -> lane item4 -> lane item5 -> lane item6
     *                                                                   |              |            slider (Time1)
     *                                                                   |            slider (Time2)
     *                                                                 slider (Time3)
     *            ...
     *          the position of slider will move forward one item by one item when sliding
     *          After sliding, the distance to first item would slide one item
     *
     * @return holo::bool_t True, succeed;
     *                      false, otherwise
     */
    virtual holo::bool_t Slide();

    /**
     * @brief Check whether or not the region slider should be active
     *
     * @return holo::bool_t True, actved, so make it take effect;
     *                      false, not actived
     */
    virtual holo::bool_t Active() = 0;

    /**
     * @brief Check whether or not the result of slider is valid
     * 
     * @details After sliding, there may not be one valid lane path
     * 
     * @return holo::bool_t True, false
     */
    virtual holo::bool_t ResultValid() = 0;

    /**
     * @brief Assemble the region model info onto lanepath
     * 
     * @return holo::bool_t 
     */
    virtual holo::bool_t Assemble() = 0;

protected:
    /**
     * @brief Get the Current Origin Item
     * 
     * @return Current origin lane item 
     */
    LaneItem& GetCurrentOriginItem();

    /**
     * @brief Get the Current Target Item 
     * 
     * @return Current target lane item 
     */
    LaneItem& GetCurrentTargetItem();

    /**
     * @brief Get the Base Origin Lane Item 
     * 
     * @return Base origin lane item 
     */
    LaneItem& GetBaseOriginLaneItem();

    /**
     * @brief Initialize after loading lane paths
     *
     * @return holo::bool_t True, succeed; false, otherwise
     */
    virtual holo::bool_t doNextLoading() = 0;

    /**
     * @brief Inner module for checking slider
     * 
     * @return holo::bool_t 
     */
    virtual holo::bool_t doNextCheckNeedSliding() = 0;

    /**
     * @brief Do next reset
     * 
     * @return holo::bool_t 
     */
    virtual void doNextReset();

protected:
    /// Origint lane path, we would change lane from it
    LanePathSPtrType origin_path_           = nullptr;
    /// Target lane path, we would change lane to it
    LanePathSPtrType target_path_           = nullptr;
    /// The index of origin lane path
    std::size_t      position_origin_index_ = 0U;
    /// The index of target lane path
    std::size_t      position_target_index_ = 0U;
    ///
    std::size_t position_base_origin_index_ = 0U;
    ///
    holo::float64_t distance_current_item_to_baseline_ = 0.0f;
    ///
    holo::float64_t distance_current_item_to_candidate_ = 0.0f;
    /// Whether or not need sliding
    holo::bool_t need_sliding_ = true;
    /// left or right
    AdjointStatus adjoint_status_ = AdjointStatus::UNDEFINED;
    ///
    std::vector<IdType> slided_lanes_;
    //
    SlidingTerminatedMode slider_status_ = SlidingTerminatedMode::UNDEFINED;
    //
    SlidingStatus sliding_status_ = SlidingStatus::UNDEFINED;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_REGION_MODEL_INFO_REGION_SLIDER_REGION_SLIDER_H_ */