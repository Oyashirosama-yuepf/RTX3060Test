/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_tracker.h
 * @brief Lane tracker for track lane along one direction.
 * @author zhengshulei(zhengshulei@holomatic.com)
 * @date 2022-3-8
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_LANE_TRACKER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_LANE_TRACKER_H_

#include <holo/map/feature/navigator/advice/lane_navigator_v2/map_types.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
#include <vector>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
namespace scene
{
/**
 * @brief Lane tracker for track lane along one direction
 *
 * @details using lane's topology to track lane
 */
class LaneTracker
{
public:
    using SectionFormType           = holo::map::navigator::advice::scene::KeyLaneSection::SectionForm;
    using KeyLaneSectionType        = holo::map::navigator::advice::scene::KeyLaneSection;
    using KeyLaneSectionSPtrType    = std::shared_ptr<KeyLaneSectionType>;
    using KeyLaneSectionSPtrVecType = std::vector<KeyLaneSectionSPtrType>;
    using SceneSketchType           = holo::map::navigator::advice::scene::SceneSketch;
    using SceneSketchSPtrType       = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType    = std::vector<SceneSketchSPtrType>;
    using SceneCategoryType         = SceneSketchType::SceneCategory;
    using SceneGroupType            = SceneSketchType::SceneGroup;

public:
    LaneTracker(RetrieverSPtrType ret);
    ~LaneTracker();

public:
    const holo::float64_t MAX_KLS_TRACK_DISTANCE_IN_METERS = 200.f;
    /**
     * @brief Track kls(key lane section) for split/merge scene.
     * @param scene split/merge scene
     *
     * @return if success, return true
     */
    holo::bool_t TrackKLS(SceneSketchSPtrType scene);
    holo::bool_t TrackKLSWithSpeclalLaneEnd(SceneSketchSPtrType scene, holo::bool_t& track_ok,
                                            KeyLaneSectionSPtrVecType& kls_container);
    holo::bool_t TrackLane(RawFeatureIdTypeV0 const lead_lane_id, RawFeatureIdVectorTypeV0& container,
                           DistanceTypeV0 const max_track_length_meters, holo::bool_t along_driving_direction);
    holo::bool_t CanLeadToScene(RawFeatureIdTypeV0 const lead_lane_id, SceneSketchSPtrType scene,
                                DistanceTypeV0 const max_track_length_meters, holo::bool_t const along_driving_direction, 
                                holo::bool_t& can_lead_to);
    holo::bool_t GetVerbose() const noexcept;
    void         SetVerbose(holo::bool_t const v) noexcept;

private:
    holo::bool_t isSplitScene(SceneSketchSPtrType scene);
    holo::bool_t isMergeScene(SceneSketchSPtrType scene);
    holo::bool_t isInnerScene(SceneSketchSPtrType scene);
    holo::bool_t isOpeningLane(RawLaneTypeV0 const& lane);
    holo::bool_t isEndingLane(RawLaneTypeV0 const& lane);
    holo::bool_t isLaneBoundaryTailCrossed(RawLaneTypeV0 const& lane);
    holo::bool_t isLaneBoundaryHeadCrossed(RawLaneTypeV0 const& lane);
    holo::bool_t isLaneNarrow(RawLaneSPtrTypeV0  lane);
    holo::bool_t isSpecialLane(RawLaneTypeV0 const& lane);
    holo::bool_t isInsectionLane(RawLaneTypeV0 const& lane);
    holo::bool_t getConnectedLaneIds(RawLaneSPtrTypeV0 in_lane, RawFeatureIdVectorTypeV0& track_ids,
                                     holo::bool_t along_driving_direction);
    holo::bool_t makeKLS(RawLaneSPtrVectorTypeV0& container,
                         KeyLaneSectionSPtrType& kls, holo::bool_t along_driving_direction);
    holo::bool_t trackFromNormalLane(RawLaneSPtrTypeV0 lead_lane, KeyLaneSectionSPtrType kls,
                                     holo::bool_t along_driving_direction);
    holo::bool_t trackFromSpecialLane(RawLaneSPtrTypeV0 lead_lane, KeyLaneSectionSPtrVecType& kls,
                                      holo::bool_t along_driving_direction);
    holo::bool_t trackLane(RawLaneSPtrTypeV0 lead_lane, RawLaneSPtrVectorTypeV0& container,
                           DistanceTypeV0 max_track_length_meters, holo::bool_t track_along_driving_direction = false);
    holo::bool_t getTracedLane(RawLaneSPtrTypeV0 input_lane, holo::bool_t along_driving_direction, 
                                RawLaneSPtrTypeV0& tracked_lane);

private:
    /// map engine's retriver instance
    RawRetrieverSPtrType raw_retriever_ = nullptr;

    /// If true, print debugging messages to log.
    holo::bool_t verbose_ = true;
};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_ANALYSIS_LANE_TRACKER_H_ */
