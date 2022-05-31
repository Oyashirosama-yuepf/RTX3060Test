/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file target region.h
 * @brief Target region in new lane path
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-10-08"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_TARGET_REGION_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_TARGET_REGION_H_

#include <queue>
#include <sstream>
#include <vector>

#include <holo/common/road_type.h>
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
#define ENUM_REGION_MODEL_CATEGORY       \
    X(UNDEFINED)                         \
    X(CHANGE_FROM_LEFT)                  \
    X(CHANGE_FROM_RIGHT)                 \
    X(MERGE_FROM_LEFT)                   \
    X(MERGE_FROM_RIGHT)                  \
    X(SPLIT_FROM_LEFT)                   \
    X(SPLIT_FROM_RIGHT)

#define ENUM_REGION_SCENE_CATEGORY                                                                                     \
    X(UNDEFINED)                                                                                                       \
    X(DIRECT_DOWN_RAMP)                                                                                                \
    X(PARALLEL_OR_CORRESPOND_DOWN_RAMP)                                                                                 \
    X(PARALLEL_DOWN_RAMP)                                                                                              \
    X(CORRESPOND_DOWN_RAMP)                                                                                            \
    X(DIRECT_UP_MAIN_ROAD)                                                                                             \
    X(PARALLEL_UP_MAIN_ROAD)                                                                                           \
    X(CORRESPOND_UP_MAIN_ROAD)                                                                                         \
    X(MAIN_DOWN_TO_RAMP)                                                                                               \
    X(RAMP_UP_TO_MAIN)                                                                                               \
    X(RAMP_SPLITING)                                                                                                   \
    X(RAMP_SPLITING_LEFT)                                                                                              \
    X(RAMP_SPLITING_RIGHT)                                                                                             \
    X(RAMP_MERGING)                                                                                                    \
    X(RAMP_MERGING_LEFT)                                                                                               \
    X(RAMP_MERGING_RIGHT)                                                                                              \
    X(MAIN_ROAD_SPLITING)                                                                                              \
    X(MAIN_ROAD_SPLITING_LEFT)                                                                                         \
    X(MAIN_ROAD_SPLITING_RIGHT)                                                                                        \
    X(MAIN_ROAD_MERGING)                                                                                               \
    X(INTERSECTION)                                                                                                    \
    X(SPLITING)                                                                                                        \
    X(MERGING)                                                                                                         \
    X(BREAKING_ROAD)

class LanePath;
/**
 * @brief Target region, which describe target region which should be changed to
 *
 *  @details The target region and region model info is ONE to ONE, the expression is as followed:
 *
 *
 *          | LI1 |   LI2 |   LI3  |   LI4   |  LI5   |  LI6  |  LI7   |  LI8   | <-- lane path 1
 *                              |-------region model info--------|
 *
 *          | LI5 |   LI6 |   LI7  |   LI8   |  LI9   |  LI10 |  LI11  |  LI12  | <-- lane path 2
 *                              |-----   target region ----------|
 *
 *          Expression: LT represents Lane Item, LT1 is Lane Item 1
 *
 *          As you can see, the change procedure would be executed from 'region model info' in lane
 *          path 1 to 'target region' in lane path2. So we also consider target region as the
 *          object region for changing lane.
 *          One more word, we could create region model info from target region. And we alse could
 *          create target region from region model info. Seen as followed:
 *
 *          | LI1 |   LI2 |   LI3  |   LI4   |  LI5   |  LI6  |  LI7   |  LI8   | <-- lane path 1
 *               |-----   target region ----------|-------region model info--------|
 *
 *          we could deduce target region from region model info with model type.
 */
class TargetRegion
{
public:
    using TargetRegionSPtrType = std::shared_ptr<TargetRegion>;
    using LanePathSPtrType     = std::shared_ptr<LanePath>;
    /**
     * @brief Model type of target region
     *
     * @details The model type in 'Target region' is opposite to that in 'Region Model Info'.
     *          For example, the SPLIT_FROM_LEFT of Target Region is corresponding to the
     *          SPLIT_TO_RIGHT of Region Model Info.
     *
     */

    enum class ModelType : holo::uint8_t
    {
#define X(type) type,
        ENUM_REGION_MODEL_CATEGORY
#undef X
    };

    enum class SceneType : holo::uint8_t
    {
#define X(type) type,
        ENUM_REGION_SCENE_CATEGORY
#undef X
    };

public:
    /**
     * @brief Format to JOSN string
     *
     * @param target TargetRegion
     * @return std::string The formated string
     */
    static std::string FormatToString(TargetRegion const& target);

    /**
     * @brief Format to JOSN string
     * 
     * @param targets 
     * @return std::string 
     */
    static std::string FormatToString(std::vector<TargetRegion> const& targets);

    TargetRegion() = default;
    ~TargetRegion() = default;
    TargetRegion(TargetRegion const&) = default;
    TargetRegion& operator=(TargetRegion const&) = default;
    TargetRegion(TargetRegion&&)                 = default;
    TargetRegion& operator=(TargetRegion&&) = default;

    /**
     * @brief Find index of lane boudnary by boundary id
     *
     * @param boundary_id
     * @param right
     * @param idx
     * @return holo::bool_t
     */
    holo::bool_t FindBoundaryIdx(LaneBoundaryIdType boundary_id, holo::bool_t const right, std::size_t& idx) const;

    /**
     * @brief
     *
     * @return std::string
     */
    std::string ToJSONString() const;

    /**
     * @brief Get the Lane Ids
     *
     * @return VecLaneIdType const&
     */
    VecLaneIdType const& GetLaneIds() const;

    /**
     * @brief Get the Lane Ids
     *
     * @return VecIdType const
     */
    VecLaneIdType& GetLaneIds();

    /**
     * @brief Get the Left Boundary Ids
     *
     * @return VecIdType
     */
    VecLaneBoundaryIdType const& GetLeftBoundaryIds() const;

    /**
     * @brief Get the Left Boundary Ids
     *
     * @return VecIdType
     */
    VecLaneBoundaryIdType& GetLeftBoundaryIds();

    /**
     * @brief Get the Right Boundary Ids
     *
     * @return VecIdType
     */
    VecLaneBoundaryIdType const& GetRightBoundaryIds() const;

    /**
     * @brief Get the Right Boundary Ids
     *
     * @return VecIdType
     */
    VecLaneBoundaryIdType& GetRightBoundaryIds();

    /**
     * @brief Set the Begin Lane Offset
     *
     * @param offset
     */
    void SetBeginLaneOffset(holo::float64_t offset);

    /**
     * @brief Get the Begin Lane Offset
     *
     * @return Distance const
     */
    holo::float64_t GetBeginLaneOffset() const;

    /**
     * @brief Set the Finish Lane Offset
     *
     * @param offset
     */
    void SetFinishLaneOffset(Distance offset);

    /**
     * @brief Get the Finish Lane Offset
     *
     * @return Distance const
     */
    holo::float64_t GetFinishLaneOffset() const;

    /**
     * @brief Set the Model Type
     *
     * @param model_type
     */
    void SetModelType(ModelType model_type);

    /**
     * @brief Get the Model Type
     *
     * @return ModelType
     */
    ModelType GetModelType() const;

    /**
     * @brief Set the Host Lane Path
     *
     * @param path
     */
    void SetHostLanePath(LanePathSPtrType path);

    /**
     * @brief Get the Host Lane Path
     *
     * @return LanePathSPtrType
     */
    LanePathSPtrType GetHostLanePath() const;

    /**
     * @brief Set the Scene Type
     *
     */
    void SetSceneType(SceneType type);

    /**
     * @brief Get the Scene Type
     *
     * @return SceneType
     */
    SceneType GetSceneType();

    /**
     * @brief Get the Hosted Paths
     * 
     * @return std::vector<LanePathSPtrType> const& 
     */
    std::vector<LanePathSPtrType> const& GetHostedPaths() const;

    /**
     * @brief Get the Hosted Paths 
     * 
     * @return std::vector<LanePathSPtrType>& 
     */
    std::vector<LanePathSPtrType>& GetHostedPaths();

    /**
     * @brief Set the Target Length
     * 
     * @param len 
     */
    void SetTargetLength(holo::float64_t len);

    /**
     * @brief Get the Target Length
     * 
     * @return holo::float64_t 
     */
    holo::float64_t GetTargetLength() const;

private:
    /// Ids of lanes covered by target region
    VecIdType lane_ids_;
    /// Ids of left boundarys covered by target region,
    /// we could judge neighbor relationship of different
    /// lanes and sections of different lane paths
    VecIdType left_boundary_ids_;
    /// Ids of right boundarys covered by target region
    VecIdType right_boundary_ids_;
    /// Begin offset of first lane
    Distance begin_lane_offset_ = 0.0f;
    /// Finish offset of last lane
    Distance finish_lane_offset_ = 0.0f;
    /// The hosted lane path
    LanePathSPtrType lane_path_;
    /// Model type
    ModelType model_type_;
    /// Scene type
    SceneType scene_type_;
    /// A vector of hosted lane path
    std::vector<LanePathSPtrType> hosted_lane_paths_;
    /// Calculate length target region
    holo::float64_t region_length_ = 0.0f;
};

char const* const RegionModelCategoryNames[7] = {
#define X(name) #name,
    ENUM_REGION_MODEL_CATEGORY
#undef X
};

char const* const SceneCategoryNames[13] = {
#define X(name) #name,
    ENUM_REGION_MODEL_CATEGORY
#undef X
};

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_LANE_PATH_H_ */
