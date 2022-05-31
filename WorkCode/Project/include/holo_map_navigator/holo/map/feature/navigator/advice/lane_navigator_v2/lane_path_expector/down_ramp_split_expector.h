/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file down_ramp_split_expector.h
 * @brief Highway split to ramp expector
 * @author zhengshulei (yuhongbo@holomatic.com)
 * @date 2022-3-25
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_DOWN_RAMP_EXPECTOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_DOWN_RAMP_EXPECTOR_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_expector/expector_base.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_expector/step_expector.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/map_types.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/participant_group.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/key_lane_tracker.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class DownRampSplitExpector : public ExpectorBase
{
public:
    using LaneTrackerType       = scene::LaneTracker;
    using LaneTrackerSPtrType   = std::shared_ptr<LaneTrackerType>;
    using ParticipantType       = holo::map::navigator::advice::Participant;
    using SceneSketchType       = scene::SceneSketch;
    using KeyLaneSectionType    = scene::KeyLaneSection;
    using KeyLaneSectionVecType = std::vector<KeyLaneSectionType>;
    using SectionFormType       = KeyLaneSectionType::SectionForm;

    using RouteSceneType     = scene::RouteScene;
    using RouteSceneSPtrType = std::shared_ptr<RouteSceneType>;

    using StepExpectorType     = StepExpector;
    using StepExpectorSPtrType = std::shared_ptr<StepExpectorType>;

    class RecommandActivation
    {
    public:
        /**
         * @brief Different recommanding mode
         *
         */
        enum class RecommandActiveMode : holo::uint8_t
        {
            UNDEFINED = 0,
            DEFAULT_ACTIVE,
            STEP_RECOMMAND_ACTIVE,
            PRIORITY_RECOMMAND_ACTIVE,
            NEAREAST_RECOMMAND_ACTIVE,
            STEP_AND_PRIORITYE_RECOMMAND_ACTIVE,
            OTHERS = 255U
        };

    public:
        void SetStepRecommandActived(holo::bool_t const actived) const;

        void SetPriorityRecommandActived(holo::bool_t const actived) const;

        void SetNearesetRecommandActived(holo::bool_t const actived) const;

        RecommandActiveMode GetActivedMode() const;

    private:
        holo::bool_t isStepRecommandActived() const;
        holo::bool_t isPriorityRecommandActived() const;
        holo::bool_t isNearestRecommandActived() const;

    private:
        static const holo::uint8_t DEFAULT_ACTIVE_CODE            = 0U;
        static const holo::uint8_t STEP_RECOMMAND_ACTIVE_CODE     = 1U;
        static const holo::uint8_t PRIORITY_RECOMMAND_ACTIVE_CODE = 2U;
        static const holo::uint8_t NEAREAST_RECOMMAND_ACTIVE_CODE = 3U;
        
        // Recommand active mode value
        holo::uint8_t active_mode_value = 0U;
    };

public:
    DownRampSplitExpector(SceneSketchSPtrType scene_sketch, RouteSceneSPtrType route_scene);
    virtual ~DownRampSplitExpector() = default;

    /**
     * @brief Initialize function
     *
     * @return holo::bool_t
     */
    virtual holo::bool_t Init() override;

    /**
     * @brief Whether or not the expector is enabled
     *
     * @return holo::bool_t True, enabled; false, otherwise
     */
    virtual holo::bool_t Enabled() override;

    /**
     * @brief Calculate to recommend different lane paths in participant group
     *
     * @param group Participant group containing participants, where one
     *              participant correspond to one lane path
     * @return holo::bool_t True, succeed; false otherwise
     */
    virtual holo::bool_t Recommend(ParticipantGroupType& group);

    /**
     * @brief Whether or not terminate recommending calculation
     *
     * @return holo::bool_t True, need terminating; false, execute
     *                      next Expector calcuation
     */
    virtual holo::bool_t Terminate();

    void SetBestExpectedDistance(DistanceTypeV0 dist);

private:
    DistanceTypeV0 NEAREST_LANE_PATH_EXPECT_ACTIVATE_DISTANCE_METER = 300.0f;
    DistanceTypeV0 BEST_EXIT_POINT_EXPECT_ACTIVATE_DISTANCE_METER   = 500.0f;
    holo::uint64_t INVALID_LANE_PATH_ID                             = 0;

    holo::bool_t canActivateStepExpect(ParticipantGroup& group);

    /**
     * @brief Whether or not activate split expect
     *
     * @return holo::bool_t True, can activate split extect
     */
    holo::bool_t canActivateNearestLanePathExpect();
    /**
     * @brief Whether or not terminate recommending calculation
     *
     * @return holo::bool_t True, need terminating; false, execute
     *                      next Expector calcuation
     */
    holo::bool_t canActivateBestExitPointExpect();
    /**
     * @brief Whether or not terminate recommending calculation
     *
     * @return holo::bool_t True, need terminating; false, execute
     *                      next Expector calcuation
     */
    holo::bool_t setBestExitPoint();

    holo::bool_t getCanLeadLaneIds(RawFeatureIdVectorTypeV0& can_lead_lane_ids);

    holo::bool_t isNearestLanePath(ParticipantType const& lane_path);
    holo::bool_t setNearestLanePath(ParticipantGroupType& group);

    holo::bool_t getNextKeyScene(SceneSketchSPtrType& next_road_split_scene, DistanceTypeV0& distance);
    holo::bool_t getKlsOfLeadLane(RawFeatureIdTypeV0 const lead_lane_id, KeyLaneSectionType& kls);

    DistanceTypeV0 getMaxKlsLengthMeter();

    holo::bool_t defaultRecommend(ParticipantGroupType& group);
    holo::bool_t nearestLanePathRecommend(ParticipantGroupType& group);
    holo::bool_t bestExitPointRecommend(ParticipantGroupType& group);

    holo::bool_t canActivate();

private:
    /// step expect
    holo::bool_t can_activate_step_expect_ = false;
    holo::bool_t step_expect_activated_    = false;
    /// nearset lanepath expect
    holo::bool_t             can_activate_nearest_lanepath_expect_ = false;
    holo::bool_t             nearest_lanepath_expect_activeted_    = false;
    RawFeatureIdVectorTypeV0 nearest_lanepath_ids;

    /// best exit point expect
    holo::bool_t             can_activate_best_exit_point_expect_ = false;
    holo::bool_t             best_exit_point_expect_activeted_    = false;
    RawFeatureIdVectorTypeV0 best_exit_kls_lane_ids_;
    holo::bool_t             need_relate_kls_to_near_lane_path_ = false;
    RawFeatureIdVectorTypeV0 relate_kls_lane_ids_;

    RouteSceneSPtrType  rout_scene_ = nullptr;
    LaneTrackerSPtrType tracker_    = nullptr;

    StepExpectorSPtrType step_expector_ = nullptr;
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_DOWN_RAMP_EXPECTOR_H_ */
