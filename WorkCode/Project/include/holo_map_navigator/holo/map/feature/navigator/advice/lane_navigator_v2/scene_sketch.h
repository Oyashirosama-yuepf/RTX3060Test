/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file scene_sketch.h
 * @brief Scene sketch extracted from route
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2022-02-22"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_SKETCH_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_SCENE_SKETCH_H_

#include <memory>

#include <holo/common/road_type.h>
#include <holo/core/types.h>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/key_lane_section.h>

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
class SceneSketch
{
public:
    using KeyLaneSectionType        = KeyLaneSection;
    using KeyLaneSectionVecType     = std::vector<KeyLaneSectionType>;
    using SceneSketchSPtrType       = std::shared_ptr<SceneSketch>;
    using SceneSketchSPtrVecType    = std::vector<SceneSketchSPtrType>;

    enum class SceneGroup : holo::uint8_t
    {
        UNDEFINED       = 0x00,
        SPLIT           = 0x10,
        MERGE           = 0x20,
        INNER           = 0x30,
        INTERSECTION    = 0x40,
        COMPOSITE       = 0x50,
        RESERVED        = 0x60,
        OTHERS          = 0xFF
    };

    enum class SceneCategory : holo::uint8_t
    {
        UNDEFINED                    = 0x00,  ///> Undefiend scene category
        SPLIT_TWO_MAIN_BRANCH        = 0x11,  ///> Split-flow to two ramp branches
        SPLIT_MAIN_DOWN_RAMP         = 0x12,  ///> Split-flow and drive along main road
        SPLIT_ALONG_MAIN_ROAD        = 0x13,  ///> Split-flow and drive along either branch
        SPLIT_TWO_RAMP_BRANCH        = 0x14,  ///> Split-flow to two main-road braches
        SPLIT_MULTI_BRANCH           = 0x15,  ///> More than two split-flow branches
        MERGE_MAIN                   = 0x21,  ///> Two main road merging
        MERGE_RAMP_UP_MAIN           = 0x22,  ///> Merging and drive from ramp to main road
        MERGE_ALONG_MAIN_ROAD        = 0x23,  ///> Mergint and drive along main road
        MERGE_RAMP                   = 0x24,  ///> Two ramp merging
        MERGE_MULTI_ROAD             = 0x25,  ///> More than two merging branches
        INNER_LANE_SPLIT             = 0x31,  ///> Inner lane spliting
        INNER_LANE_MERGE             = 0x32,  ///> Inner lane merging
        INNER_LANE_BREAKING          = 0x33,  ///> Inner lane breaking
        INNER_TOLL_AREA              = 0x34,  ///> Toll area
        INNER_NO_MARK                = 0x35,  ///> No mark area
        INNER_CHANGE_HIGHWAY_URBAN   = 0x36,  ///> Change between highway and urban
        INTERSECTION_CROSSROADS      = 0x41,  ///> Crossroads 
        INTERSECTION_T_JUNCTION      = 0x42,  ///> T-junction
        INTERSECTION_ROUNDABOUT      = 0x43,  ///> Roundabout
        COMPOSITE_JCT                = 0x51,  ///> From main road to ramp and going through jct, finally driving up to main road
        COMPOSITE_MULTI_INTERSECTION = 0x52,  ///> Two or more nearby intersections
        RESERVED_0                   = 0x61,  ///> First reserved enum value 
        RESERVED_1                   = 0x62,  ///> Second reserved enum value 
        RESERVED_2                   = 0x63,  ///> Third reserved enum value 
        RESERVED_3                   = 0x64,  ///> Forth reserved enum value 
        RESERVED_4                   = 0x65,  ///> Fifth reserved enum value 
        OTHERS                       = 0xFF   ///> Others
    };

public:
    static std::string FormatToString(SceneSketch const& sketch);

    static std::string FormatSequenceToString(std::vector<SceneSketchSPtrType> const& sketch);

public:
    SceneSketch()                   = default;
    virtual ~SceneSketch()          = default;
    SceneSketch(SceneSketch const&) = default;
    SceneSketch(SceneSketch&&)      = default;
    SceneSketch& operator=(SceneSketch const&) = default;
    SceneSketch& operator=(SceneSketch&&) = default;

    void   SetFromLinkId(IdType const link_id);
    IdType GetFromLinkId() const;

    void   SetToLinkId(IdType const link_id);
    IdType GetToLinkId() const;

    void            SetDistanceToSceneBegin(holo::float64_t const distance);
    holo::float64_t GetDistanceToSceneBegin() const;

    void            SetDistanceToSceneEnd(holo::float64_t const distance);
    holo::float64_t GetDistanceToSceneEnd() const;

    void          SetSceneCatagory(SceneCategory const category);
    SceneCategory GetSceneCategory() const;

    std::vector<IdType> const& GetSpecialLaneIds() const;
    std::vector<IdType>&       GetSpecialLaneIds();

    std::vector<IdType> const& GetLeadLaneIds() const;
    std::vector<IdType>&       GetLeadLaneIds();

    KeyLaneSectionVecType const& GetKeyLaneSections() const;
    KeyLaneSectionVecType&       GetKeyLaneSections();

    virtual std::string ToString();
    virtual std::string ToString() const;

    holo::bool_t IsSimpleScene() const;
    holo::bool_t IsRoadSplitScene() const;
    holo::bool_t IsRoadMergeScene() const;
    holo::bool_t IsIntersectionScene() const;

protected:
    IdType                    from_link_id_            = 0U;
    IdType                    to_link_id_              = 0U;
    holo::float64_t           distance_to_scene_begin_ = 0.0f;
    holo::float64_t           distance_to_scene_end_   = 0.0f;
    SceneCategory             scene_catagory_;
    std::vector<IdType>       special_lane_ids_; ///< special lanes(OPENNING/ENDING/BREAKUP) in scene
    std::vector<IdType>       lead_lane_ids_;    ///< scene lead lanes, start lane of key lane_sections
    KeyLaneSectionVecType     key_lane_sections_; ///< key section lanes(ACCELERATE/DECELERATE)
    holo::bool_t              is_simple_scene_ = true; ///< simple scene
};

class CompositeSceneSketch : public SceneSketch
{
public:
    using SceneSketchSPtrType    = std::shared_ptr<SceneSketch>;
    using SceneSketchSPtrVecType = std::vector<SceneSketchSPtrType>;

public:
    CompositeSceneSketch();

public:
    SceneSketchSPtrVecType const& GetSceneSketchs() const;
    SceneSketchSPtrVecType&       GetSceneSketchs();

public:
    virtual std::string ToString() override;
    virtual std::string ToString() const override;
private:
    SceneSketchSPtrVecType scene_sketches_;
};

class RouteScene
{
public:
    using SceneSketchType    = SceneSketch;
    using SceneSketchSPtrType    = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType = std::vector<SceneSketchSPtrType>;
    using CompositeSceneSketchType        = CompositeSceneSketch;
    using CompositeSceneSketchSPtrType    = std::shared_ptr<CompositeSceneSketchType>;
    using CompositeSceneSketchSPtrVecType = std::vector<CompositeSceneSketchSPtrType>;

public:
    RouteScene(SceneSketchSPtrVecType const& all_scenes);

public:
    SceneSketchSPtrVecType const& GetAllScenesOnRoute() const;
    SceneSketchSPtrVecType const GetAllSimpleScenesBeforeCar() const;
    SceneSketchSPtrType const GetFirstSimpleSceneBeforeCar(RouteScene::SceneSketchType::SceneCategory catagory) const;

private:
    SceneSketchSPtrVecType all_scenes_on_route_;
};


}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_SCENE_SKETCH_H_ */